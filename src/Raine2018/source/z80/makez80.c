/* search for [kayamon] for the fixed part */

/* Multi-Z80 32 Bit emulator */

/* Copyright 1996, 1997, 1998, 1999, 2000 Neil Bradley, All rights reserved
 * This version is hacked for the kabuki encryption (separation of code
 * and data when decoding instructions).
 *
 * License agreement:
 *
 * (MZ80 Refers to both the assembly code emitted by makeZ80.c and makeZ80.c
 * itself)
 *
 * MZ80 May be distributed in unmodified form to any medium.
 *
 * MZ80 May not be sold, or sold as a part of a commercial package without
 * the express written permission of Neil Bradley (neil@synthcom.com). This
 * includes shareware.
 *
 * Modified versions of MZ80 may not be publicly redistributed without author
 * approval (neil@synthcom.com). This includes distributing via a publicly
 * accessible LAN. You may make your own source modifications and distribute
 * MZ80 in source or object form, but if you make modifications to MZ80
 * then it should be noted in the top as a comment in makeZ80.c.
 *
 * MZ80 Licensing for commercial applications is available. Please email
 * neil@synthcom.com for details.
 *
 * Synthcom Systems, Inc, and Neil Bradley will not be held responsible for
 * any damage done by the use of MZ80. It is purely "as-is".
 *
 * If you use MZ80 in a freeware application, credit in the following text:
 *
 * "Multi-Z80 CPU emulator by Neil Bradley (neil@synthcom.com)"
 *
 * must accompany the freeware application within the application itself or
 * in the documentation.
 *
 * Legal stuff aside:
 *
 * If you find problems with MZ80, please email the author so they can get
 * resolved. If you find a bug and fix it, please also email the author so
 * that those bug fixes can be propogated to the installed base of MZ80
 * users. If you find performance improvements or problems with MZ80, please
 * email the author with your changes/suggestions and they will be rolled in
 * with subsequent releases of MZ80.
 *
 * The whole idea of this emulator is to have the fastest available 32 bit
 * Multi-Z80 emulator for the PC, giving maximum performance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Use word access for push/pop words (not working for some reason)
#define WORD_ACCESS

// This version uses some code from v3.4...
#define VERSION 			"3.4raine3"
// Notice : this version is closer to mz80 3.4 now (better !)

// SEPARATION_CODE_DATA : usefull when you need to fetch code from an area
// and data from another (like in kabuki encryption). It will of course slow
// down the emulation (a very little).
#define SEPARATION_CODE_DATA
/* 3.4raine3 : add ed6b instruction (ld (hl),adr !
 * Actually I just branch to the mischandler opcode 2a to execute the standard
 * instruction, not sure it's the best way to do it, but it works ! */

/* 3.4raine2 : now supports the variable Z80Has16bitsPorts. Set it to 1 to
 * enable 16 bits ports (neogeo mainly). in a,(8) is correctly handled as
 * access to port A*256+8 now when this variable is set to 1 */

#define TRUE				0xff
#define FALSE				0x0
#define INVALID 			0xff

#define UINT32				unsigned long int
#define UINT8				unsigned char

#define TIMING_REGULAR			0x00
#define TIMING_XXCB				0x01
#define TIMING_CB				0xcb
#define TIMING_DDFD				0xdd
#define TIMING_ED				0xed
#define TIMING_EXCEPT			0x02

FILE *fp = NULL;
char string[150];
char cpubasename[150];
char mz80Index[50];
char majorOp[50];
char procname[150];
UINT32 dwGlobalLabel = 0;

UINT8 bPlain = FALSE;
UINT8 bNoTiming = FALSE;
UINT8 bUseStack = FALSE;
UINT8 bSingleStep = FALSE;
UINT8 bCurrentMode = TIMING_REGULAR;	// Current timing mode
UINT8 bThroughCallHandler = FALSE;

void ProcBegin(UINT32 dwOpcode);

static char *pbLocalReg[8] =
{
	"ch",
	"cl",
	"dh",
	"dl",
	"bh",
	"bl",
	"dl",
	"al"
};

#ifndef WORD_ACCESS
static char *pbPushReg[8] =
{
	"cl",
	"ch",
	"byte [_z80de]",
	"byte [_z80de + 1]",
	"bl",
	"bh",
	"ah",
	"al"
};
#endif

static char *pbFlags[8] =
{
	"nz",
	"z",
	"nc",
	"c",
	"po",
	"pe",
	"ns",
	"s"
};

static char *pbMathReg[8] =
{
	"ch",
	"cl",
	"byte [_z80de + 1]",
	"byte [_z80de]",
	"bh",
	"bl",
	"INVALID",
	"al"
};

static char *pbRegPairs[4] =
{
	"cx",   // BC
	"word [_z80de]", // DE
	"bx",   // HL
	"word [_z80sp]"  // SP
};

static char *pbPopRegPairs[4] =
{
	"cx",   // BC
	"word [_z80de]", // DE
	"bx",   // HL
	"ax"  // SP
};

static char *pbIndexedRegPairs[4] =
{
	"cx",   // BC
	"word [_z80de]", // DE
	"di",   // IX/IY
	"word [_z80sp]"  // SP
};

// Timing tables

UINT8 bTimingRegular[0x100] =
{
	0x04, 0x0a, 0x07, 0x06, 0x04, 0x04, 0x07, 0x04, 0x04, 0x0b, 0x07, 0x06, 0x04, 0x04, 0x07, 0x04,
	0x08, 0x0a, 0x07, 0x06, 0x04, 0x04, 0x07, 0x04, 0x0c, 0x0b, 0x07, 0x06, 0x04, 0x04, 0x07, 0x04,
	0x07, 0x0a, 0x10, 0x06, 0x04, 0x04, 0x07, 0x04, 0x07, 0x0b, 0x10, 0x06, 0x04, 0x04, 0x07, 0x04,
	0x07, 0x0a, 0x0d, 0x06, 0x0b, 0x0b, 0x0a, 0x04, 0x07, 0x0b, 0x0d, 0x06, 0x04, 0x04, 0x07, 0x04,

	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,

	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x04,

	0x05, 0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x07, 0x0b, 0x05, 0x0a, 0x0a, 0x00, 0x0a, 0x11, 0x07, 0x0b,
	0x05, 0x0a, 0x0a, 0x0b, 0x0a, 0x0b, 0x07, 0x0b, 0x05, 0x04, 0x0a, 0x0b, 0x0a, 0x00, 0x07, 0x0b,
	0x05, 0x0a, 0x0a, 0x13, 0x0a, 0x0b, 0x07, 0x0b, 0x05, 0x04, 0x0a, 0x04, 0x0a, 0x00, 0x07, 0x0b,
	0x05, 0x0a, 0x0a, 0x04, 0x0a, 0x0b, 0x07, 0x0b, 0x05, 0x06, 0x0a, 0x04, 0x0a, 0x00, 0x07, 0x0b
};

UINT8 bTimingCB[0x100] =
{
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,

	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08
};

UINT8 bTimingXXCB[0x100] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00
};

UINT8 bTimingDDFD[0x100] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0e, 0x14, 0x0a, 0x09, 0x09, 0x09, 0x00, 0x00, 0x0f, 0x14, 0x0a, 0x09, 0x09, 0x09, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x17, 0x17, 0x13, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,

	0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x13, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x13, 0x09,
	0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x13, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0e, 0x00, 0x17, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

UINT8 bTimingED[0x100] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 /* ed6b, translated to misc 2a, ld (hl),adr */, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x0e, 0x08, 0x09, 0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x0e, 0x08, 0x09,
	0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x08, 0x08, 0x09, 0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x08, 0x08, 0x09,
	0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x08, 0x08, 0x12, 0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x08, 0x08, 0x12,
	0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x08, 0x08, 0x00, 0x0c, 0x0c, 0x0f, 0x14, 0x08, 0x08, 0x08, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void EDHandler(UINT32 dwOpcode);
void DDHandler(UINT32 dwOpcode);
void FDHandler(UINT32 dwOpcode);
void CBHandler(UINT32 dwOpcode);

void PushPopOperations(UINT32 dwOpcode);
void AddRegpairOperations(UINT32 dwOpcode);
void CallHandler(UINT32 dwOpcode);
void MiscHandler(UINT32 dwOpcode);
void IMHandler(UINT32 dwOpcode);
void IRHandler(UINT32 dwOpcode);
void LdRegPairImmediate(UINT32 dwOpcode);
void LoadImmediate(UINT32 dwOpcode);
void LdRegpairPtrByte(UINT32 dwOpcode);
void MathOperation(UINT32 dwOpcode);
void RegIntoMemory(UINT32 dwOpcode);
void JpHandler(UINT32 dwOpcode);
void LdRegImmediate(UINT32 dwOpcode);
void IncRegister(UINT32 dwOpcode);
void DecRegister(UINT32 dwOpcode);
void IncDecRegpair(UINT32 dwOpcode);
void LdRegReg(UINT32 dwOpcode);
void MathOperationDirect(UINT32 dwOpcode);
void JrHandler(UINT32 dwOpcode);
void RetHandler(UINT32 dwOpcode);
void RestartHandler(UINT32 dwOpcode);
void ToRegFromHl(UINT32);
void RraRlaHandler(UINT32);
void LdByteRegpair(UINT32);
void IncDecHLPtr(UINT32 dwOpcode);
void InOutHandler(UINT32 dwOpcode);
void RLCRRCRLRRSLASRASRLHandler(UINT32 dwOpcode);
void BITHandler(UINT32 dwOpcode);
void RESSETHandler(UINT32 dwOpcode);
void PushPopOperationsIndexed(UINT32 dwOpcode);
void LDILDRLDIRLDDRHandler(UINT32);
void LdRegpair(UINT32 dwOpcode);
void ExtendedRegIntoMemory(UINT32 dwOpcode);
void NegHandler(UINT32 dwOpcode);
void ExtendedInHandler(UINT32 dwOpcode);
void ExtendedOutHandler(UINT32 dwOpcode);
void RetIRetNHandler(UINT32 dwOcode);
void AdcSbcRegpair(UINT32 dwOpcode);
void CPICPDCPIRCPDRHandler(UINT32 dwOpcode);
void RRDRLDHandler(UINT32 dwOpcode);
void UndocRegToIndex(UINT32 dwOpcode);
void UndocIndexToReg(UINT32 dwOpcode);
void MathOperationIndexed(UINT32 dwOpcode);
void IncDecIndexed(UINT32 dwOpcode);
void DDFDCBHandler(UINT32 dwOpcode);
void JPIXIYHandler(UINT32 dwOpcode);
void AddIndexHandler(UINT32 dwOpcode);
void SPToIndex(UINT32 dwOpcode);
void LdByteToIndex(UINT32 dwOpcode);
void LdRegIndexOffset(UINT32 dwOpcode);
void IncDecIndexReg(UINT32 dwOpcode);
void ExIndexed(UINT32 dwOpcode);
void UndocIncDecIndexReg(UINT32 dwOpcode);
void UndocLoadHalfIndexReg(UINT32 dwOpcode);
void UndocMathIndex(UINT32 dwOpcode);
void ddcbBitWise(UINT32 dwOpcode);
void LdIndexPtrReg(UINT32 dwOpcode);
void StoreIndexReg(UINT32 dwOpcode);
void LoadIndexReg(UINT32 dwOpcode);
void OTIROTDROUTIOUTDHandler(UINT32 dwOpcode);
void INIRINDRINIINDHandler(UINT32 dwOpcode);

struct sOp
{
	UINT32 bOpCode;
	void (*Emitter)(UINT32);
};

struct sOp StandardOps[] =
{
	{0xd3,	InOutHandler},		// V
	{0xdb,	InOutHandler},		// V

	{0x0a, LdByteRegpair},		// V
	{0x1a, LdByteRegpair},		// V

	{0x17,	RraRlaHandler}, 	// V
	{0x1f,	RraRlaHandler}, 	// V

	{0x05,	DecRegister},		// V
	{0x0d,	DecRegister},		// V
	{0x15,	DecRegister},		// V
	{0x1d,	DecRegister},		// V
	{0x25,	DecRegister},		// V
	{0x2d,	DecRegister},		// V
	{0x3d,	DecRegister},		// V

	{0x04,	IncRegister},		// V
	{0x0c,	IncRegister},		// V
	{0x14,	IncRegister},		// V
	{0x1c,	IncRegister},		// V
	{0x24,	IncRegister},		// V
	{0x2c,	IncRegister},		// V
	{0x3c,	IncRegister},		// V

	{0x32,	RegIntoMemory}, // V
	{0x22,	RegIntoMemory}, // V

	{0xc3,	JpHandler},			// V
	{0xc2, JpHandler},			// V
	{0xca, JpHandler},			// V
	{0xd2, JpHandler},			// V
	{0xda, JpHandler},			// V
	{0xe2, JpHandler},			// V
	{0xea, JpHandler},			// V
	{0xf2, JpHandler},			// V
	{0xfa, JpHandler},			// V


	{0x06, LdRegImmediate}, 	// V
	{0x0e, LdRegImmediate}, 	// V
	{0x16, LdRegImmediate}, 	// V
	{0x1e, LdRegImmediate}, 	// V
	{0x26, LdRegImmediate}, 	// V
	{0x2e, LdRegImmediate}, 	// V
	{0x3e, LdRegImmediate}, 	// V

	{0x0b,	IncDecRegpair}, 	// V
	{0x1b,	IncDecRegpair}, 	// V
	{0x2b,	IncDecRegpair}, 	// V
	{0x3b,	IncDecRegpair}, 	// V

	{0x03,	IncDecRegpair}, 	// V
	{0x13,	IncDecRegpair}, 	// V
	{0x23,	IncDecRegpair}, 	// V
	{0x33,	IncDecRegpair}, 	// V

	{0x34,	IncDecHLPtr},		// V
	{0x35,	IncDecHLPtr},		// V

	{0xcb,	CBHandler},
	{0xdd,	DDHandler},
	{0xed,	EDHandler},
	{0xfd,	FDHandler},

	{0x01,	LdRegPairImmediate},	// V
	{0x11,	LdRegPairImmediate},	// V
	{0x21,	LdRegPairImmediate},	// V
	{0x31,	LdRegPairImmediate},	// V

	{0xe3,	MiscHandler},	// V
	{0x2a,	MiscHandler},	// V
	{0xfb,	MiscHandler},	// V
	{0xf9,	MiscHandler},	// V
	{0xd9,	MiscHandler},	// V
	{0x76,	MiscHandler},	// V
	{0x3f,	MiscHandler},	// V
	{0x37,	MiscHandler},	// V
	{0x27,	MiscHandler},	// V
	{0x07,	MiscHandler},	// V
	{0x08,	MiscHandler},	// V
	{0x00,	MiscHandler},	// V
	{0xe9,	MiscHandler},	// V
	{0xeb,	MiscHandler},	// V
	{0xf3,	MiscHandler},	// V
	{0x3a,	MiscHandler},	// V
	{0x10,	MiscHandler},	// V
	{0x2f,	MiscHandler},	// V
	{0x0f,	MiscHandler},	// V

	{0x02, LdRegpairPtrByte},	// V
	{0x12, LdRegpairPtrByte},	// V

	{0x70, LdRegpairPtrByte},	// V
	{0x71, LdRegpairPtrByte},	// V
	{0x72, LdRegpairPtrByte},	// V
	{0x73, LdRegpairPtrByte},	// V
	{0x74, LdRegpairPtrByte},	// V
	{0x75, LdRegpairPtrByte},	// V
	{0x77, LdRegpairPtrByte},	// V

	{0x36, LdRegpairPtrByte},	// V

	{0x80,	MathOperation}, // V
	{0x81,	MathOperation}, // V
	{0x82,	MathOperation}, // V
	{0x83,	MathOperation}, // V
	{0x84,	MathOperation}, // V
	{0x85,	MathOperation}, // V
	{0x86,	MathOperation}, // V
	{0x87,	MathOperation}, // V
	{0x88,	MathOperation}, // V
	{0x89,	MathOperation}, // V
	{0x8a,	MathOperation}, // V
	{0x8b,	MathOperation}, // V
	{0x8c,	MathOperation}, // V
	{0x8d,	MathOperation}, // V
	{0x8e,	MathOperation}, // V
	{0x8f,	MathOperation}, // V
	{0x90,	MathOperation}, // V
	{0x91,	MathOperation}, // V
	{0x92,	MathOperation}, // V
	{0x93,	MathOperation}, // V
	{0x94,	MathOperation}, // V
	{0x95,	MathOperation}, // V
	{0x96,	MathOperation}, // V
	{0x97,	MathOperation}, // V
	{0x98,	MathOperation}, // V
	{0x99,	MathOperation}, // V
	{0x9a,	MathOperation}, // V
	{0x9b,	MathOperation}, // V
	{0x9c,	MathOperation}, // V
	{0x9d,	MathOperation}, // V
	{0x9e,	MathOperation}, // V
	{0x9f,	MathOperation}, // V
	{0xa0,	MathOperation}, // V
	{0xa1,	MathOperation}, // V
	{0xa2,	MathOperation}, // V
	{0xa3,	MathOperation}, // V
	{0xa4,	MathOperation}, // V
	{0xa5,	MathOperation}, // V
	{0xa6,	MathOperation}, // V
	{0xa7,	MathOperation}, // V
	{0xa8,	MathOperation}, // V
	{0xa9,	MathOperation}, // V
	{0xaa,	MathOperation}, // V
	{0xab,	MathOperation}, // V
	{0xac,	MathOperation}, // V
	{0xad,	MathOperation}, // V
	{0xae,	MathOperation}, // V
	{0xaf,	MathOperation}, // V
	{0xb0,	MathOperation}, // V
	{0xb1,	MathOperation}, // V
	{0xb2,	MathOperation}, // V
	{0xb3,	MathOperation}, // V
	{0xb4,	MathOperation}, // V
	{0xb5,	MathOperation}, // V
	{0xb6,	MathOperation}, // V
	{0xb7,	MathOperation}, // V
	{0xb8,	MathOperation}, // V
	{0xb9,	MathOperation}, // V
	{0xba,	MathOperation}, // V
	{0xbb,	MathOperation}, // V
	{0xbc,	MathOperation}, // V
	{0xbd,	MathOperation}, // V
	{0xbe,	MathOperation}, // V
	{0xbf,	MathOperation}, // V

	{0x40, LdRegReg},	// V
	{0x41, LdRegReg},	// V
	{0x42, LdRegReg},	// V
	{0x43, LdRegReg},	// V
	{0x44, LdRegReg},	// V
	{0x45, LdRegReg},	// V
	{0x47, LdRegReg},	// V
	{0x48, LdRegReg},	// V
	{0x49, LdRegReg},	// V
	{0x4a, LdRegReg},	// V
	{0x4b, LdRegReg},	// V
	{0x4c, LdRegReg},	// V
	{0x4d, LdRegReg},	// V
	{0x4f, LdRegReg},	// V
	{0x50, LdRegReg},	// V
	{0x51, LdRegReg},	// V
	{0x52, LdRegReg},	// V
	{0x53, LdRegReg},	// V
	{0x54, LdRegReg},	// V
	{0x55, LdRegReg},	// V
	{0x57, LdRegReg},	// V
	{0x58, LdRegReg},	// V
	{0x59, LdRegReg},	// V
	{0x5a, LdRegReg},	// V
	{0x5b, LdRegReg},	// V
	{0x5c, LdRegReg},	// V
	{0x5d, LdRegReg},	// V
	{0x5f, LdRegReg},	// V
	{0x60, LdRegReg},	// V
	{0x61, LdRegReg},	// V
	{0x62, LdRegReg},	// V
	{0x63, LdRegReg},	// V
	{0x64, LdRegReg},	// V
	{0x65, LdRegReg},	// V
	{0x67, LdRegReg},	// V
	{0x68, LdRegReg},	// V
	{0x69, LdRegReg},	// V
	{0x6a, LdRegReg},	// V
	{0x6b, LdRegReg},	// V
	{0x6c, LdRegReg},	// V
	{0x6d, LdRegReg},	// V
	{0x6f, LdRegReg},	// V
	{0x78, LdRegReg},	// V
	{0x79, LdRegReg},	// V
	{0x7a, LdRegReg},	// V
	{0x7b, LdRegReg},	// V
	{0x7c, LdRegReg},	// V
	{0x7d, LdRegReg},	// V
	{0x7f, LdRegReg},	// V

	{0xc6,	MathOperationDirect},	// V
	{0xce,	MathOperationDirect},	// V
	{0xd6,	MathOperationDirect},	// V
	{0xde,	MathOperationDirect},	// V
	{0xe6,	MathOperationDirect},	// V
	{0xee,	MathOperationDirect},	// V
	{0xf6,	MathOperationDirect},	// V
	{0xfe,	MathOperationDirect},	// V

	{0x18,	JrHandler},	// V
	{0x20,	JrHandler},	// V
	{0x28,	JrHandler},	// V
	{0x30,	JrHandler},	// V
	{0x38,	JrHandler},

	{0xc4, CallHandler},	// V
	{0xcc, CallHandler},	// V
	{0xcd, CallHandler},	// V
	{0xd4, CallHandler},	// V
	{0xdc, CallHandler},	// V
	{0xe4, CallHandler},	// V
	{0xec, CallHandler},	// V
	{0xf4, CallHandler},	// V
	{0xfc, CallHandler},	// V

	{0xc9,	RetHandler},	// V
	{0xc0,	RetHandler},	// V
	{0xc8,	RetHandler},	// V
	{0xd0,	RetHandler},	// V
	{0xd8,	RetHandler},	// V
	{0xe0,	RetHandler},	// V
	{0xe8,	RetHandler},	// V
	{0xf0,	RetHandler},	// V
	{0xf8,	RetHandler},	// V

	{0xc7,	RestartHandler}, // V
	{0xcf,	RestartHandler}, // V
	{0xd7,	RestartHandler}, // V
	{0xdf,	RestartHandler}, // V
	{0xe7,	RestartHandler}, // V
	{0xef,	RestartHandler}, // V
	{0xf7,	RestartHandler}, // V
	{0xff,	RestartHandler}, // V

	{0x46,	ToRegFromHl},	// V
	{0x4e,	ToRegFromHl},	// V
	{0x56,	ToRegFromHl},	// V
	{0x5e,	ToRegFromHl},	// V
	{0x66,	ToRegFromHl},	// V
	{0x6e,	ToRegFromHl},	// V
	{0x7e,	ToRegFromHl},

	{0x09,	AddRegpairOperations},	// V
	{0x19,	AddRegpairOperations},	// V
	{0x29,	AddRegpairOperations},	// V
	{0x39,	AddRegpairOperations},	// V

	{0xc5,	PushPopOperations},	// V
	{0xd5,	PushPopOperations},	// V
	{0xe5,	PushPopOperations},	// V
	{0xf5,	PushPopOperations},	// V
	{0xc1,	PushPopOperations},	// V
	{0xd1,	PushPopOperations},	// V
	{0xe1,	PushPopOperations},	// V
	{0xf1,	PushPopOperations},	// V

	// Terminator

	{0xffffffff, NULL}
};

struct sOp CBOps[] =
{
	{0x00,	RLCRRCRLRRSLASRASRLHandler},
	{0x01,	RLCRRCRLRRSLASRASRLHandler},
	{0x02,	RLCRRCRLRRSLASRASRLHandler},
	{0x03,	RLCRRCRLRRSLASRASRLHandler},
	{0x04,	RLCRRCRLRRSLASRASRLHandler},
	{0x05,	RLCRRCRLRRSLASRASRLHandler},
	{0x06,	RLCRRCRLRRSLASRASRLHandler},
	{0x07,	RLCRRCRLRRSLASRASRLHandler},
	{0x08,	RLCRRCRLRRSLASRASRLHandler},
	{0x09,	RLCRRCRLRRSLASRASRLHandler},
	{0x0a,	RLCRRCRLRRSLASRASRLHandler},
	{0x0b,	RLCRRCRLRRSLASRASRLHandler},
	{0x0c,	RLCRRCRLRRSLASRASRLHandler},
	{0x0d,	RLCRRCRLRRSLASRASRLHandler},
	{0x0e,	RLCRRCRLRRSLASRASRLHandler},
	{0x0f,	RLCRRCRLRRSLASRASRLHandler},

	{0x10,	RLCRRCRLRRSLASRASRLHandler},
	{0x11,	RLCRRCRLRRSLASRASRLHandler},
	{0x12,	RLCRRCRLRRSLASRASRLHandler},
	{0x13,	RLCRRCRLRRSLASRASRLHandler},
	{0x14,	RLCRRCRLRRSLASRASRLHandler},
	{0x15,	RLCRRCRLRRSLASRASRLHandler},
	{0x16,	RLCRRCRLRRSLASRASRLHandler},
	{0x17,	RLCRRCRLRRSLASRASRLHandler},
	{0x18,	RLCRRCRLRRSLASRASRLHandler},
	{0x19,	RLCRRCRLRRSLASRASRLHandler},
	{0x1a,	RLCRRCRLRRSLASRASRLHandler},
	{0x1b,	RLCRRCRLRRSLASRASRLHandler},
	{0x1c,	RLCRRCRLRRSLASRASRLHandler},
	{0x1d,	RLCRRCRLRRSLASRASRLHandler},
	{0x1e,	RLCRRCRLRRSLASRASRLHandler},
	{0x1f,	RLCRRCRLRRSLASRASRLHandler},

	{0x20,	RLCRRCRLRRSLASRASRLHandler},
	{0x21,	RLCRRCRLRRSLASRASRLHandler},
	{0x22,	RLCRRCRLRRSLASRASRLHandler},
	{0x23,	RLCRRCRLRRSLASRASRLHandler},
	{0x24,	RLCRRCRLRRSLASRASRLHandler},
	{0x25,	RLCRRCRLRRSLASRASRLHandler},
	{0x26,	RLCRRCRLRRSLASRASRLHandler},
	{0x27,	RLCRRCRLRRSLASRASRLHandler},
	{0x28,	RLCRRCRLRRSLASRASRLHandler},
	{0x29,	RLCRRCRLRRSLASRASRLHandler},
	{0x2a,	RLCRRCRLRRSLASRASRLHandler},
	{0x2b,	RLCRRCRLRRSLASRASRLHandler},
	{0x2c,	RLCRRCRLRRSLASRASRLHandler},
	{0x2d,	RLCRRCRLRRSLASRASRLHandler},
	{0x2e,	RLCRRCRLRRSLASRASRLHandler},
	{0x2f,	RLCRRCRLRRSLASRASRLHandler},

	{0x30,	RLCRRCRLRRSLASRASRLHandler},
	{0x31,	RLCRRCRLRRSLASRASRLHandler},
	{0x32,	RLCRRCRLRRSLASRASRLHandler},
	{0x33,	RLCRRCRLRRSLASRASRLHandler},
	{0x34,	RLCRRCRLRRSLASRASRLHandler},
	{0x35,	RLCRRCRLRRSLASRASRLHandler},
	{0x36,	RLCRRCRLRRSLASRASRLHandler},
	{0x37,	RLCRRCRLRRSLASRASRLHandler},

	{0x38,	RLCRRCRLRRSLASRASRLHandler},
	{0x39,	RLCRRCRLRRSLASRASRLHandler},
	{0x3a,	RLCRRCRLRRSLASRASRLHandler},
	{0x3b,	RLCRRCRLRRSLASRASRLHandler},
	{0x3c,	RLCRRCRLRRSLASRASRLHandler},
	{0x3d,	RLCRRCRLRRSLASRASRLHandler},
	{0x3e,	RLCRRCRLRRSLASRASRLHandler},
	{0x3f,	RLCRRCRLRRSLASRASRLHandler},

	{0x40,	BITHandler},
	{0x41,	BITHandler},
	{0x42,	BITHandler},
	{0x43,	BITHandler},
	{0x44,	BITHandler},
	{0x45,	BITHandler},
	{0x46,	BITHandler},
	{0x47,	BITHandler},
	{0x48,	BITHandler},
	{0x49,	BITHandler},
	{0x4a,	BITHandler},
	{0x4b,	BITHandler},
	{0x4c,	BITHandler},
	{0x4d,	BITHandler},
	{0x4e,	BITHandler},
	{0x4f,	BITHandler},

	{0x50,	BITHandler},
	{0x51,	BITHandler},
	{0x52,	BITHandler},
	{0x53,	BITHandler},
	{0x54,	BITHandler},
	{0x55,	BITHandler},
	{0x56,	BITHandler},
	{0x57,	BITHandler},
	{0x58,	BITHandler},
	{0x59,	BITHandler},
	{0x5a,	BITHandler},
	{0x5b,	BITHandler},
	{0x5c,	BITHandler},
	{0x5d,	BITHandler},
	{0x5e,	BITHandler},
	{0x5f,	BITHandler},

	{0x60,	BITHandler},
	{0x61,	BITHandler},
	{0x62,	BITHandler},
	{0x63,	BITHandler},
	{0x64,	BITHandler},
	{0x65,	BITHandler},
	{0x66,	BITHandler},
	{0x67,	BITHandler},
	{0x68,	BITHandler},
	{0x69,	BITHandler},
	{0x6a,	BITHandler},
	{0x6b,	BITHandler},
	{0x6c,	BITHandler},
	{0x6d,	BITHandler},
	{0x6e,	BITHandler},
	{0x6f,	BITHandler},

	{0x70,	BITHandler},
	{0x71,	BITHandler},
	{0x72,	BITHandler},
	{0x73,	BITHandler},
	{0x74,	BITHandler},
	{0x75,	BITHandler},
	{0x76,	BITHandler},
	{0x77,	BITHandler},
	{0x78,	BITHandler},
	{0x79,	BITHandler},
	{0x7a,	BITHandler},
	{0x7b,	BITHandler},
	{0x7c,	BITHandler},
	{0x7d,	BITHandler},
	{0x7e,	BITHandler},
	{0x7f,	BITHandler},

	// RES

	{0x80,	RESSETHandler},
	{0x81,	RESSETHandler},
	{0x82,	RESSETHandler},
	{0x83,	RESSETHandler},
	{0x84,	RESSETHandler},
	{0x85,	RESSETHandler},
	{0x86,	RESSETHandler},
	{0x87,	RESSETHandler},
	{0x88,	RESSETHandler},
	{0x89,	RESSETHandler},
	{0x8a,	RESSETHandler},
	{0x8b,	RESSETHandler},
	{0x8c,	RESSETHandler},
	{0x8d,	RESSETHandler},
	{0x8e,	RESSETHandler},
	{0x8f,	RESSETHandler},

	{0x90,	RESSETHandler},
	{0x91,	RESSETHandler},
	{0x92,	RESSETHandler},
	{0x93,	RESSETHandler},
	{0x94,	RESSETHandler},
	{0x95,	RESSETHandler},
	{0x96,	RESSETHandler},
	{0x97,	RESSETHandler},
	{0x98,	RESSETHandler},
	{0x99,	RESSETHandler},
	{0x9a,	RESSETHandler},
	{0x9b,	RESSETHandler},
	{0x9c,	RESSETHandler},
	{0x9d,	RESSETHandler},
	{0x9e,	RESSETHandler},
	{0x9f,	RESSETHandler},

	{0xa0,	RESSETHandler},
	{0xa1,	RESSETHandler},
	{0xa2,	RESSETHandler},
	{0xa3,	RESSETHandler},
	{0xa4,	RESSETHandler},
	{0xa5,	RESSETHandler},
	{0xa6,	RESSETHandler},
	{0xa7,	RESSETHandler},
	{0xa8,	RESSETHandler},
	{0xa9,	RESSETHandler},
	{0xaa,	RESSETHandler},
	{0xab,	RESSETHandler},
	{0xac,	RESSETHandler},
	{0xad,	RESSETHandler},
	{0xae,	RESSETHandler},
	{0xaf,	RESSETHandler},

	{0xb0,	RESSETHandler},
	{0xb1,	RESSETHandler},
	{0xb2,	RESSETHandler},
	{0xb3,	RESSETHandler},
	{0xb4,	RESSETHandler},
	{0xb5,	RESSETHandler},
	{0xb6,	RESSETHandler},
	{0xb7,	RESSETHandler},
	{0xb8,	RESSETHandler},
	{0xb9,	RESSETHandler},
	{0xba,	RESSETHandler},
	{0xbb,	RESSETHandler},
	{0xbc,	RESSETHandler},
	{0xbd,	RESSETHandler},
	{0xbe,	RESSETHandler},
	{0xbf,	RESSETHandler},

	// SET

	{0xc0,	RESSETHandler},
	{0xc1,	RESSETHandler},
	{0xc2,	RESSETHandler},
	{0xc3,	RESSETHandler},
	{0xc4,	RESSETHandler},
	{0xc5,	RESSETHandler},
	{0xc6,	RESSETHandler},
	{0xc7,	RESSETHandler},
	{0xc8,	RESSETHandler},
	{0xc9,	RESSETHandler},
	{0xca,	RESSETHandler},
	{0xcb,	RESSETHandler},
	{0xcc,	RESSETHandler},
	{0xcd,	RESSETHandler},
	{0xce,	RESSETHandler},
	{0xcf,	RESSETHandler},

	{0xd0,	RESSETHandler},
	{0xd1,	RESSETHandler},
	{0xd2,	RESSETHandler},
	{0xd3,	RESSETHandler},
	{0xd4,	RESSETHandler},
	{0xd5,	RESSETHandler},
	{0xd6,	RESSETHandler},
	{0xd7,	RESSETHandler},
	{0xd8,	RESSETHandler},
	{0xd9,	RESSETHandler},
	{0xda,	RESSETHandler},
	{0xdb,	RESSETHandler},
	{0xdc,	RESSETHandler},
	{0xdd,	RESSETHandler},
	{0xde,	RESSETHandler},
	{0xdf,	RESSETHandler},

	{0xe0,	RESSETHandler},
	{0xe1,	RESSETHandler},
	{0xe2,	RESSETHandler},
	{0xe3,	RESSETHandler},
	{0xe4,	RESSETHandler},
	{0xe5,	RESSETHandler},
	{0xe6,	RESSETHandler},
	{0xe7,	RESSETHandler},
	{0xe8,	RESSETHandler},
	{0xe9,	RESSETHandler},
	{0xea,	RESSETHandler},
	{0xeb,	RESSETHandler},
	{0xec,	RESSETHandler},
	{0xed,	RESSETHandler},
	{0xee,	RESSETHandler},
	{0xef,	RESSETHandler},

	{0xf0,	RESSETHandler},
	{0xf1,	RESSETHandler},
	{0xf2,	RESSETHandler},
	{0xf3,	RESSETHandler},
	{0xf4,	RESSETHandler},
	{0xf5,	RESSETHandler},
	{0xf6,	RESSETHandler},
	{0xf7,	RESSETHandler},
	{0xf8,	RESSETHandler},
	{0xf9,	RESSETHandler},
	{0xfa,	RESSETHandler},
	{0xfb,	RESSETHandler},
	{0xfc,	RESSETHandler},
	{0xfd,	RESSETHandler},
	{0xfe,	RESSETHandler},
	{0xff,	RESSETHandler},

	// Terminator

	{0xffffffff, NULL}
};

static void LDHLHandler() {
    MiscHandler(0x2a); // branch to ld (hl),adr handler
}

struct sOp EDOps[] =
{
    {0x6b, LDHLHandler},
	{0x67,	RRDRLDHandler},
	{0x6f,	RRDRLDHandler},
	{0x42,	AdcSbcRegpair},
	{0x4a,	AdcSbcRegpair},
	{0x52,	AdcSbcRegpair},
	{0x5a,	AdcSbcRegpair},
	{0x62,	AdcSbcRegpair},
	{0x6a,	AdcSbcRegpair},
	{0x72,	AdcSbcRegpair},
	{0x7a,	AdcSbcRegpair},
	{0x45,	RetIRetNHandler},
	{0x4d,	RetIRetNHandler},
	{0x44,	NegHandler},
	{0xa0,	LDILDRLDIRLDDRHandler},
	{0xa8,	LDILDRLDIRLDDRHandler},
	{0xb0,	LDILDRLDIRLDDRHandler},
	{0xb8,	LDILDRLDIRLDDRHandler},
	{0x57, IRHandler},
	{0x5F, IRHandler},
	{0x47, IRHandler},
	{0x4F, IRHandler},
	{0x46,	IMHandler},
	{0x56,	IMHandler},
	{0x5e,	IMHandler},
	{0x4b,	LdRegpair},
	{0x5b,	LdRegpair},
	{0x7b,	LdRegpair},
	{0x43,	ExtendedRegIntoMemory},
	{0x53,	ExtendedRegIntoMemory},
	{0x63,	ExtendedRegIntoMemory},
	{0x73,	ExtendedRegIntoMemory},
	{0x40, ExtendedInHandler},
	{0x48, ExtendedInHandler},
	{0x50, ExtendedInHandler},
	{0x58, ExtendedInHandler},
	{0x60, ExtendedInHandler},
	{0x68, ExtendedInHandler},
	{0x78, ExtendedInHandler},
	{0x41, ExtendedOutHandler},
	{0x49, ExtendedOutHandler},
	{0x51, ExtendedOutHandler},
	{0x59, ExtendedOutHandler},
	{0x61, ExtendedOutHandler},
	{0x69, ExtendedOutHandler},
	{0x79, ExtendedOutHandler},
	{0xa1,	CPICPDCPIRCPDRHandler},
	{0xa9,	CPICPDCPIRCPDRHandler},
	{0xb1,	CPICPDCPIRCPDRHandler},
	{0xb9,	CPICPDCPIRCPDRHandler},

	{0xbb,	OTIROTDROUTIOUTDHandler},			// OTDR
	{0xb3,	OTIROTDROUTIOUTDHandler},			// OTIR
	{0xab,	OTIROTDROUTIOUTDHandler},			// OUTD
	{0xa3,	OTIROTDROUTIOUTDHandler},			// OUTI

	{0xb2,	INIRINDRINIINDHandler}, 			// INIR
	{0xba,	INIRINDRINIINDHandler}, 			// INDR
	{0xa2,	INIRINDRINIINDHandler}, 			// INI
	{0xaa,	INIRINDRINIINDHandler}, 			// IND

	// Terminator

	{0xffffffff, NULL}
};

struct sOp DDFDOps[] =
{
	{0x35,	IncDecIndexed},
	{0x34,	IncDecIndexed},
	{0xcb,	DDFDCBHandler},
	{0x86,	MathOperationIndexed},
	{0x8e,	MathOperationIndexed},
	{0x96,	MathOperationIndexed},
	{0x9e,	MathOperationIndexed},
	{0xa6,	MathOperationIndexed},
	{0xae,	MathOperationIndexed},
	{0xb6,	MathOperationIndexed},
	{0xbe,	MathOperationIndexed},

	{0xe1,	PushPopOperationsIndexed},
	{0xe5,	PushPopOperationsIndexed},
	{0x21,	LoadImmediate},
	{0xe9,	JPIXIYHandler},
	{0x09,	AddIndexHandler},
	{0x19,	AddIndexHandler},
	{0x29,	AddIndexHandler},
	{0x39,	AddIndexHandler},
	{0xf9,	SPToIndex},
	{0x36,	LdByteToIndex},
	{0x46,	LdRegIndexOffset},
	{0x4e,	LdRegIndexOffset},
	{0x56,	LdRegIndexOffset},
	{0x5e,	LdRegIndexOffset},
	{0x66,	LdRegIndexOffset},
	{0x6e,	LdRegIndexOffset},
	{0x7e,	LdRegIndexOffset},

	{0x70,	LdIndexPtrReg},
	{0x71,	LdIndexPtrReg},
	{0x72,	LdIndexPtrReg},
	{0x73,	LdIndexPtrReg},
	{0x74,	LdIndexPtrReg},
	{0x75,	LdIndexPtrReg},
	{0x77,	LdIndexPtrReg},

	{0x23,	IncDecIndexReg},
	{0x2b,	IncDecIndexReg},

	{0x22,	StoreIndexReg},
	{0x2a,	LoadIndexReg},
	{0xe3,	ExIndexed},

	{0x44,	UndocRegToIndex},
	{0x45,	UndocRegToIndex},
	{0x4c,	UndocRegToIndex},
	{0x4d,	UndocRegToIndex},
	{0x54,	UndocRegToIndex},
	{0x55,	UndocRegToIndex},
	{0x5c,	UndocRegToIndex},
	{0x5d,	UndocRegToIndex},
	{0x7c,	UndocRegToIndex},
	{0x7d,	UndocRegToIndex},

	{0x60,	UndocIndexToReg},
	{0x61,	UndocIndexToReg},
	{0x62,	UndocIndexToReg},
	{0x63,	UndocIndexToReg},
	{0x64,	UndocIndexToReg},
	{0x65,	UndocIndexToReg},
	{0x67,	UndocIndexToReg},
	{0x68,	UndocIndexToReg},
	{0x69,	UndocIndexToReg},
	{0x6a,	UndocIndexToReg},
	{0x6b,	UndocIndexToReg},
	{0x6c,	UndocIndexToReg},
	{0x6d,	UndocIndexToReg},
	{0x6f,	UndocIndexToReg},

	{0x24,	UndocIncDecIndexReg},
	{0x25,	UndocIncDecIndexReg},
	{0x2c,	UndocIncDecIndexReg},
	{0x2d,	UndocIncDecIndexReg},

	{0x26,	UndocLoadHalfIndexReg},
	{0x2e,	UndocLoadHalfIndexReg},

	{0x84,	UndocMathIndex},
	{0x85,	UndocMathIndex},
	{0x8c,	UndocMathIndex},
	{0x8d,	UndocMathIndex},

	{0x94,	UndocMathIndex},
	{0x95,	UndocMathIndex},
	{0x9c,	UndocMathIndex},
	{0x9d,	UndocMathIndex},

	{0xa4,	UndocMathIndex},
	{0xa5,	UndocMathIndex},
	{0xac,	UndocMathIndex},
	{0xad,	UndocMathIndex},

	{0xb4,	UndocMathIndex},
	{0xb5,	UndocMathIndex},
	{0xbc,	UndocMathIndex},
	{0xbd,	UndocMathIndex},

	// Terminator

	{0xffffffff, NULL}
};

struct sOp DDFDCBOps[] =
{
	{0x06,	ddcbBitWise},
	{0x0e,	ddcbBitWise},
	{0x16,	ddcbBitWise},
	{0x1e,	ddcbBitWise},
	{0x26,	ddcbBitWise},
	{0x2e,	ddcbBitWise},
	{0x3e,	ddcbBitWise},
	{0x46,	ddcbBitWise},
	{0x4e,	ddcbBitWise},
	{0x56,	ddcbBitWise},
	{0x5e,	ddcbBitWise},
	{0x66,	ddcbBitWise},
	{0x6e,	ddcbBitWise},
	{0x76,	ddcbBitWise},
	{0x7e,	ddcbBitWise},
	{0x86,	ddcbBitWise},
	{0x8e,	ddcbBitWise},
	{0x96,	ddcbBitWise},
	{0x9e,	ddcbBitWise},
	{0xa6,	ddcbBitWise},
	{0xae,	ddcbBitWise},
	{0xb6,	ddcbBitWise},
	{0xbe,	ddcbBitWise},
	{0xc6,	ddcbBitWise},
	{0xce,	ddcbBitWise},
	{0xd6,	ddcbBitWise},
	{0xde,	ddcbBitWise},
	{0xe6,	ddcbBitWise},
	{0xee,	ddcbBitWise},
	{0xf6,	ddcbBitWise},
	{0xfe,	ddcbBitWise},

	// Terminator

	{0xffffffff, NULL}
};

UINT32 Timing(UINT8 bWho, UINT32 dwOpcode)
{
	UINT32 dwTiming = 0;

	assert(dwOpcode < 0x100);

	if (TIMING_REGULAR == bWho)	// Regular?
		dwTiming = bTimingRegular[dwOpcode];
	else
	if (TIMING_CB == bWho)
		dwTiming = bTimingCB[dwOpcode];
	else
	if (TIMING_DDFD == bWho)
		dwTiming = bTimingDDFD[dwOpcode];
	else
	if (TIMING_ED == bWho)
		dwTiming = bTimingED[dwOpcode];
	else
	if (TIMING_XXCB == bWho)
		dwTiming = bTimingXXCB[dwOpcode];
	else
	if (TIMING_EXCEPT == bWho)
		dwTiming = dwOpcode;
	else
		assert(0);

	if (0 == dwTiming)
	{
		fprintf(stderr, "Opcode: %.2x:%.2x - Not zero!\n", bWho, (UINT8) dwOpcode);
		fclose(fp);
		exit(1);
	}

	return(dwTiming);
}

static void FetchDataB(char *reg) {
#ifdef SEPARATION_CODE_DATA
  fprintf(fp, "         add esi,[z80_offdata]\n");
#endif
  fprintf(fp, "         mov     %s, [esi]\n",reg);
#ifdef SEPARATION_CODE_DATA
  fprintf(fp, "         sub esi,[z80_offdata]\n");
#endif
  fprintf(fp, "         inc     esi             ; Move past the offset\n");
}

static void FetchDataW(char *reg) {
#ifdef SEPARATION_CODE_DATA
  fprintf(fp, "         add esi,[z80_offdata]\n");
#endif
  fprintf(fp, "         mov     %s, [esi]\n",reg);
  if (strcmp(reg,"si")) { // if dest is not si then restore it !
#ifdef SEPARATION_CODE_DATA
    fprintf(fp, "         sub esi,[z80_offdata]\n");
#endif
    fprintf(fp, "               add     esi, 2  ; Skip over it so we don't execute it\n");
  }
}

static void IndexedOffset(char *Localmz80Index)
{
  FetchDataB("dl"); // Fetch our offset
	fprintf(fp, "           or      dl, dl          ; Is this bad boy signed?\n");
	fprintf(fp, "           jns     notSigned%ld    ; Nope!\n", dwGlobalLabel);
	fprintf(fp, "           dec     dh                      ; Make it FFable\n");
	fprintf(fp, "notSigned%ld:\n", dwGlobalLabel);
	fprintf(fp, "           add     dx, [_z80%s]    ; Our offset!\n", Localmz80Index);
	++dwGlobalLabel;
}

#define INC_RCOUNTER fprintf(fp, "           inc     byte [_z80rCounter]\n")

void FetchNextInstruction(UINT32 dwOpcode)
{
	if (0xffffffff != dwOpcode)
	{
		fprintf(fp, "           sub     edi, byte %ld\n", Timing(bCurrentMode, dwOpcode));

		fprintf(fp, "           js      near noMoreExec\n");
	}
	fprintf(fp, "           mov     dl, byte [esi]  ; Get our next instruction\n");
	INC_RCOUNTER;
	fprintf(fp, "           inc     esi             ; Increment PC\n");
	fprintf(fp, "           jmp     dword [z80regular+edx*4]\n\n");
}

void CBHandler(UINT32 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Handler for all CBxx instructions\n");
	fprintf(fp, ";\n");
	sprintf(string, "RegInst%.2x", (UINT8) dwOpcode);
	ProcBegin(0xffffffff);
	fprintf(fp, "           mov     [_baseFixup], dword 1\n");
	fprintf(fp, "           mov     dl,[esi]\n");
	fprintf(fp, "           inc     esi\n");
	INC_RCOUNTER;

	fprintf(fp,	"       jmp     dword [z80PrefixCB+edx*4]\n\n");
	fprintf(fp, "\n\n");
}

void EDHandler(UINT32 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Handler for all EDxx instructions\n");
	fprintf(fp, ";\n");
	sprintf(string, "RegInst%.2x", (UINT8) dwOpcode);
	ProcBegin(0xffffffff);
	fprintf(fp, "           mov     [_baseFixup], dword 1\n");
	fprintf(fp, "           mov     dl,[esi]\n");
	fprintf(fp, "           inc     esi\n");
	INC_RCOUNTER;

	fprintf(fp,	"       jmp     dword [z80PrefixED+edx*4]\n\n");
	fprintf(fp, "\n\n");
}

void DDHandler(UINT32 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Handler for all DDxx instructions\n");
	fprintf(fp, ";\n");
	sprintf(string, "RegInst%.2x", (UINT8) dwOpcode);
	ProcBegin(0xffffffff);
	fprintf(fp, "           mov     [_baseFixup], dword 1\n");
	fprintf(fp, "           mov     dl,[esi]\n");
	fprintf(fp, "           inc     esi\n");
	INC_RCOUNTER;

	fprintf(fp,	"       jmp     dword [z80PrefixDD+edx*4]\n\n");
	fprintf(fp, "\n\n");
}

void FDHandler(UINT32 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Handler for all FDxx instructions\n");
	fprintf(fp, ";\n");
	sprintf(string, "RegInst%.2x", (UINT8) dwOpcode);
	ProcBegin(0xffffffff);
	fprintf(fp, "           mov     [_baseFixup], dword 1\n");
	fprintf(fp, "           mov     dl,[esi]\n");
	fprintf(fp, "           inc     esi\n");
	INC_RCOUNTER;

	fprintf(fp,	"       jmp     dword [z80PrefixFD+edx*4]\n\n");
	fprintf(fp, "\n\n");
}

void StandardHeader(void)
{
	fprintf(fp,"; For assembly by NASM only\n");
	fprintf(fp,"bits 32\n\n");

	fprintf(fp,"; Theory of operation\n\n");
	fprintf(fp,"; EDI=General purpose\n");
	fprintf(fp,"; ESI=Program counter + base address\n");
	fprintf(fp,"; EBP=mz80Base\n");
	fprintf(fp,"; AX=AF\n");
	fprintf(fp,"; flas in AF (for mz80) :\n");
	fprintf(fp,"; bit 0 : C (carry)\n");
	fprintf(fp,";     1 : N\n");
	fprintf(fp,";     2 : P/V\n");
	fprintf(fp,";     3 : ?\n");

	fprintf(fp,";     4 : H (half-carry)\n");
	fprintf(fp,";     5 : ?\n");
	fprintf(fp,";     6 : Z\n");
	fprintf(fp,";     7 : S\n");

	fprintf(fp,"; BX=HL\n");
	fprintf(fp,"; CX=BC\n");
	fprintf(fp,"; DX=General purpose\n\n");

	if (bUseStack)
		fprintf(fp, "; Using stack calling conventions\n");
	else
		fprintf(fp, "; Using register calling conventions\n");

	if (bSingleStep)
		fprintf(fp, "; Single step version (debug)\n");

	/* The IFF case : */
	/* Maybe it would seem easy for an expert of the z80, but I learned */
	/* these registers yesterday, so... */
	/* iff1 and iff2 ar normally 2 interrupt state registers of 1 bit */
	/* each. So they are emulated by 1 8 bits register with the 2 */
	/* following values. IFF2 is a backup of IFF1 while in NMI. */
	/* IFF1 is 0 when in an interrupt (to disable interrupts), and IFF2 */
	/* can be read by "ld a,i" and "ld a,r" (see further) */

	fprintf(fp, "IFF1               equ     01h\n");
	fprintf(fp, "IFF2               equ     02h\n");

	fprintf(fp, "\n\n");
}

void Alignment(void)
{
	fprintf(fp, "\ntimes ($$-$) & 3 nop     ; pad with NOPs to 4-byte boundary\n\n");
}

void ProcBegin(UINT32 dwOpcode)
{
	Alignment();
	fprintf(fp, "%s:\n", procname);

}

void SetOverflow(void)
{
	fprintf(fp, "           seto    dl\n");
	fprintf(fp, "           and     ah, 0fbh        ; Knock out parity/overflow\n");
	fprintf(fp, "           shl     dl, 2\n");
	fprintf(fp, "           or              ah, dl\n");
}

void WriteValueToMemory(char *pszAddress, char *pszValue)
{
    fprintf(fp, "               mov     [cyclesRemaining], edi\n");
	fprintf(fp, "           mov     [_z80af], ax    ; Store AF\n");

	// First off, load our byte to write into al after we've saved AF

	if (strcmp(pszValue, "al") != 0 && strcmp(pszValue,"[esi]") != 0)
		fprintf(fp, "           mov     al, %s  ; And our data to write\n", pszValue);
	if (strcmp(pszValue, "[esi]") == 0)     // Immediate value?
	  FetchDataB("al");

	// Now get the address in DX - regardless of what it is

	if (strcmp(pszAddress, "[_z80de]") == 0 ||
		 strcmp(pszAddress, "[_orgval]") == 0 ||
		 strcmp(pszAddress, "[_z80ix]") == 0 ||
		 strcmp(pszAddress, "[_z80iy]") == 0)
		fprintf(fp, "           mov     dx, %s\n", pszAddress);

	fprintf(fp, "           mov     edi, [_z80MemWrite]     ; Point to the write array\n\n");
	fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);

	if (strcmp(pszAddress, "[_z80de]") == 0 ||
		 strcmp(pszAddress, "[_orgval]") == 0 ||
		 strcmp(pszAddress, "[_z80ix]") == 0 ||
		 strcmp(pszAddress, "[_z80iy]") == 0)
		fprintf(fp, "           cmp     dx, [edi]       ; Are we smaller?\n");
	else
		fprintf(fp, "           cmp     %s, [edi]       ; Are we smaller?\n", pszAddress);

	fprintf(fp, "           jb      nextAddr%ld     ; Yes... go to the next addr\n", dwGlobalLabel);

	if (strcmp(pszAddress, "[_z80de]") == 0 ||
		 strcmp(pszAddress, "[_orgval]") == 0 ||
		 strcmp(pszAddress, "[_z80ix]") == 0 ||
		 strcmp(pszAddress, "[_z80iy]") == 0)
		fprintf(fp, "           cmp     dx, [edi+4]     ; Are we smaller?\n");
	else
		fprintf(fp, "           cmp     %s, [edi+4]     ; Are we smaller?\n", pszAddress);

	fprintf(fp, "           jbe     callRoutine%ld  ; If not, go call it!\n\n", dwGlobalLabel);

	fprintf(fp, "           cmp     [edi], word 0ffffh ; End of our list?\n");
	fprintf(fp, "           je      memoryWrite%ld  ; Yes - go write it!\n", dwGlobalLabel);

	fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
	fprintf(fp, "           add     edi, 10h                ; Next structure, please\n");
	fprintf(fp, "           jmp     short checkLoop%ld\n\n", dwGlobalLabel);
	fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);

	// Check internal/external write

	fprintf(fp, "           cmp     dword[edi+8],byte 0     ; [J3d!] Use internal write?\n");
	fprintf(fp, "           jne     callWrite%ld\n", dwGlobalLabel);

	// ---- Internal write -------------------------------------------------

	fprintf(fp, "memoryWrite%ld:\n", dwGlobalLabel);

	fprintf(fp, "           mov     edi, [edi+12]           ; [J3d!] Get offset\n");

	if (strcmp(pszValue, "[esi]") == 0)
		fprintf(fp, "           mov     [edi + e%s], al         ; Store our direct value\n", pszAddress);
	else
	{
		if (pszValue[0] == 'b' && pszValue[1] == 'y' && pszValue[2] == 't')
		{
			fprintf(fp, "           push    edx\n");
			assert(strcmp(pszValue, "dl") != 0);

			if (strcmp(pszAddress, "dx") == 0){
				fprintf(fp, "           add     edi, edx\n");
				fprintf(fp, "           mov     dl, %s\n", pszValue);
				fprintf(fp, "           mov     [edi], dl\n");
			}
			else{
				fprintf(fp, "           mov     dl, %s\n", pszValue);
				fprintf(fp, "           mov     [edi + e%s], dl\n", pszAddress);
			}
			fprintf(fp, "           pop     edx\n");
		}
		else
		{
			if (strcmp(pszAddress, "[_z80de]") != 0 &&
				 strcmp(pszAddress, "[_orgval]") != 0 &&
				 strcmp(pszAddress, "[_z80ix]") != 0 &&
				 strcmp(pszAddress, "[_z80iy]") != 0)
				fprintf(fp, "           mov     [edi + e%s], %s\n", pszAddress, pszValue);
			else
				fprintf(fp, "           mov     [edi + edx], al\n");
		}
	}

	fprintf(fp, "           mov     ax, [_z80af] ; Get our accumulator and flags\n");

	fprintf(fp, "           jmp     WriteMacroExit%ld\n", dwGlobalLabel);

	// ---- External write -------------------------------------------------

	fprintf(fp, "callWrite%ld:\n", dwGlobalLabel);

	if ((strcmp(pszAddress, "dx") != 0) && (strcmp(pszAddress, "[_z80de]") != 0) &&
		 (strcmp(pszAddress, "[_z80ix]") != 0) &&
		 (strcmp(pszAddress, "[_orgval]") != 0) &&
		 (strcmp(pszAddress, "[_z80iy]") != 0))
		fprintf(fp, "           mov     dx, %s  ; Get our address to target\n", pszAddress);

	fprintf(fp, "           call    WriteMemoryByte ; Go write the data!\n");

	// Exit

	fprintf(fp, "WriteMacroExit%ld:\n", dwGlobalLabel);
	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");

	++dwGlobalLabel;
}

#ifdef WORD_ACCESS

void WriteWordToMemory(char *pszAddress, char *pszTarget)
{
  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
  fprintf(fp, "         mov     edi, [_z80MemWrite]     ; Point to the write array\n\n");
  fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
  fprintf(fp, "         cmp     [edi], word 0ffffh ; End of the list?\n");
  fprintf(fp, "         je              memoryWrite%ld\n", dwGlobalLabel);
  fprintf(fp, "         cmp     %s, [edi]       ; Are we smaller?\n", pszAddress);
  fprintf(fp, "         jb              nextAddr%ld             ; Yes, go to the next address\n", dwGlobalLabel);
  fprintf(fp, "         cmp     %s, [edi+4]     ; Are we bigger?\n", pszAddress);
  fprintf(fp, "         jbe     callRoutine%ld\n\n", dwGlobalLabel);
  fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
  fprintf(fp, "         add     edi, 10h                ; Next structure!\n");
  fprintf(fp, "         jmp     short checkLoop%ld\n\n", dwGlobalLabel);

  fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);
  // Incredible, the mz80 author simply forgot the internal/external test...

  // Check internal/external write

  fprintf(fp, "         cmp     dword[edi+8],byte 0     ; [J3d!] Use internal read?\n");
  fprintf(fp, "         je      memoryWrite%ld\n", dwGlobalLabel);

  // ---- External write --------------------------------------------------
  fprintf(fp, "         push    ax              ; Save this for later\n");

  // Write the LSB

  fprintf(fp, "         push    dx\n");

  if (strcmp(pszTarget, "ax") != 0)
    {
      fprintf(fp, "             mov     ax, %s\n", pszTarget);
    }
  else
    {
      fprintf(fp, "             xchg    ah, al\n");
    }

  fprintf(fp, "         call    WriteMemoryByte\n");
  fprintf(fp, "         pop     dx\n");
  fprintf(fp, "         pop     ax\n");
  fprintf(fp, "         inc     dx\n\n");

  fprintf(fp, "         push    ax\n");
  fprintf(fp, "         push    dx\n");

  /* And now write the msb, please... !!!! */
  if (strcmp(pszTarget, "ax") != 0)
    {
      fprintf(fp, "             mov     ax, %s\n", pszTarget);
      fprintf(fp, "             xchg    ah, al\n");
    }

  fprintf(fp, "         call    WriteMemoryByte\n");
  fprintf(fp, "         pop     dx\n");
  fprintf(fp, "         pop     ax      ; Restore us!\n");

  fprintf(fp, "         jmp     writeExit%ld\n\n", dwGlobalLabel);

  fprintf(fp, "memoryWrite%ld:\n", dwGlobalLabel);


  fprintf(fp, "         mov     edi, [edi+12]           ; [J3d!] Get offset\n");
  if (strlen(pszTarget) != 2)
    {
      fprintf(fp, "             push    ax\n");
      fprintf(fp, "             mov     ax, %s\n", pszTarget);
      fprintf(fp, "             mov     [edi + e%s], ax ; Store our word\n", pszAddress);
      fprintf(fp, "             pop     ax\n");
    }
  else
    {
      if (strcmp(pszTarget, "ax") != 0)
	{
	  fprintf(fp, "         mov     [edi + e%s], %s ; Store our word\n", pszAddress, pszTarget);
	}
      else
	{
	  fprintf(fp, "         xchg    ah, al  ; Swap for later\n");
	  fprintf(fp, "         mov     [edi + e%s], %s ; Store our word\n", pszAddress, pszTarget);
	  fprintf(fp, "         xchg    ah, al  ; Restore\n");
	}
    }

  fprintf(fp, "writeExit%ld:\n", dwGlobalLabel);
  fprintf(fp, "         mov     edi, [cyclesRemaining]\n");
  // Same as ReadWord : edx not cleared, because it's cleared by the caller
  dwGlobalLabel++;
}

#endif

void WriteValueToIo(char *pszIoAddress, char *pszValue)
{
  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
  fprintf(fp, "         mov     [_z80af], ax    ; Store AF\n");

	if (strcmp(pszValue, "al") != 0 || strcmp(pszValue,"[esi]") != 0)
		fprintf(fp, "           mov     al, %s  ; And our data to write\n", pszValue);
	if (strcmp(pszValue, "[esi]") == 0)     // Immediate value?
	  FetchDataB("al");

	fprintf(fp, "           mov     edi, [_z80IoWrite]      ; Point to the I/O write array\n\n");
	fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
	fprintf(fp, "           cmp     [edi], word 0ffffh ; End of our list?\n");
	fprintf(fp, "           je      WriteMacroExit%ld       ; Yes - ignore it!\n", dwGlobalLabel);
	fprintf(fp, "           cmp     %s, [edi]       ; Are we smaller?\n", pszIoAddress);
	fprintf(fp, "           jb      nextAddr%ld     ; Yes... go to the next addr\n", dwGlobalLabel);
	fprintf(fp, "           cmp     %s, [edi+2]     ; Are we bigger?\n", pszIoAddress);
	fprintf(fp, "           jbe     callRoutine%ld  ; If not, go call it!\n\n", dwGlobalLabel);
	fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
	fprintf(fp, "           add     edi, 0ch                ; Next structure, please\n");
	fprintf(fp, "           jmp     short checkLoop%ld\n\n", dwGlobalLabel);
	fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);

	// Save off our registers!

	if (strcmp(pszIoAddress, "dx") != 0)
		fprintf(fp, "           mov     dx, %s  ; Get our address to target\n", pszIoAddress);

	fprintf(fp, "           call    WriteIOByte     ; Go write the data!\n");

	fprintf(fp, "WriteMacroExit%ld:\n", dwGlobalLabel);

	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");
	++dwGlobalLabel;
}

void ReadValueFromMemory(char *pszAddress, char *pszTarget)
{
  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
	fprintf(fp, "           mov     edi, [_z80MemRead]      ; Point to the read array\n\n");
	fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
	fprintf(fp, "           cmp     %s, [edi]               ; Are we smaller?\n", pszAddress);
	fprintf(fp, "           jb      nextAddr%ld             ; Yes, go to the next address\n", dwGlobalLabel);
	fprintf(fp, "           cmp     %s, [edi+4]             ; Are we bigger?\n", pszAddress);
	fprintf(fp, "           jbe     callRoutine%ld\n\n", dwGlobalLabel);
	fprintf(fp, "           cmp     [edi], word 0ffffh      ; End of the list?\n");
	fprintf(fp, "           je      memoryRead%ld\n", dwGlobalLabel);
	fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
	fprintf(fp, "           add     edi, 10h                ; Next structure!\n");
	fprintf(fp, "           jmp     short checkLoop%ld\n\n", dwGlobalLabel);
	fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);


	// Check internal/external read

	fprintf(fp, "           cmp     dword[edi+8],byte 0     ; [J3d!] Use internal read?\n");
	fprintf(fp, "           jne     callRead%ld\n", dwGlobalLabel);

	// ---- Internal read --------------------------------------------------

	fprintf(fp, "memoryRead%ld:\n", dwGlobalLabel);

	fprintf(fp, "           mov     edi, [edi+12]           ; [J3d!] Get offset\n");

	if (pszTarget[0] == 'b' && pszTarget[1] == 'y' && pszTarget[2] == 't')
	{
		fprintf(fp, "           push    edx\n");
		fprintf(fp, "           mov     dl, [edi + e%s]\n", pszAddress);
		fprintf(fp, "           mov     %s, dl\n", pszTarget);
		fprintf(fp, "           pop     edx\n");
	}
	else
		fprintf(fp, "           mov     %s, [edi + e%s] ; Get our data\n\n", pszTarget, pszAddress);

	fprintf(fp, "           jmp     readExit%ld\n\n", dwGlobalLabel);

	// ---- External read --------------------------------------------------

	fprintf(fp, "callRead%ld:\n", dwGlobalLabel);

	if (strcmp(pszAddress, "dx") != 0)
		fprintf(fp, "           mov     dx, %s          ; Get our address\n", pszAddress);

	fprintf(fp, "           call    ReadMemoryByte  ; Standard read routine\n");

	// Yes, these are intentionally reversed!
	if (strcmp(pszTarget, "al") == 0)
		fprintf(fp, "           mov     [_z80af], al    ; Save our new accumulator\n");
	else
	if (strcmp(pszTarget, "ah") == 0)
		fprintf(fp, "           mov     [_z80af + 1], al        ; Save our new flags\n");
	else
		fprintf(fp, "           mov     %s, al  ; Put our returned value here\n", pszTarget);

	// And are properly restored HERE:
	fprintf(fp, "           mov     ax, [_z80af]    ; Get our AF back\n");

	// Exit

	fprintf(fp, "readExit%ld:\n", dwGlobalLabel);
	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");

	dwGlobalLabel++;
}

#ifdef WORD_ACCESS

void ReadWordFromMemory(char *pszAddress, char *pszTarget)
{
  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
  fprintf(fp, "         mov     edi, [_z80MemRead]      ; Point to the read array\n\n");
  fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
  fprintf(fp, "         cmp     [edi], word 0ffffh ; End of the list?\n");
  fprintf(fp, "         je              memoryRead%ld\n", dwGlobalLabel);
  fprintf(fp, "         cmp     %s, [edi]       ; Are we smaller?\n", pszAddress);
  fprintf(fp, "         jb              nextAddr%ld             ; Yes, go to the next address\n", dwGlobalLabel);
  fprintf(fp, "         cmp     %s, [edi+4]     ; Are we bigger?\n", pszAddress);
  fprintf(fp, "         jbe     callRoutine%ld\n\n", dwGlobalLabel);
  fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
  fprintf(fp, "         add     edi, 10h                ; Next structure!\n");
  fprintf(fp, "         jmp     short checkLoop%ld\n\n", dwGlobalLabel);
  fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);

  // Incredible, the mz80 author simply forgot the internal/external test...

  // Check internal/external read

  fprintf(fp, "         cmp     dword[edi+8],byte 0     ; [J3d!] Use internal read?\n");
  fprintf(fp, "         je      memoryRead%ld\n", dwGlobalLabel);

	// ---- External read --------------------------------------------------

	fprintf(fp, "callRead%ld:\n", dwGlobalLabel);


  if (strcmp(pszAddress, "dx") != 0)
    fprintf(fp, "               mov     dx, %s  ; Get our address\n", pszAddress);

  if (strcmp(pszTarget, "ax") != 0)
    fprintf(fp, "               push    ax              ; Save this for later\n");

  fprintf(fp, "         push    dx              ; Save address\n");
  fprintf(fp, "         call    ReadMemoryByte  ; Standard read routine\n");
  fprintf(fp, "         pop     dx              ; Restore our address\n");

  fprintf(fp, "         inc     dx              ; Next byte, please\n");

  fprintf(fp, "         push    ax              ; Save returned byte\n");
  fprintf(fp, "         call    ReadMemoryByte  ; Standard read routine\n");
  fprintf(fp, "         xchg    ah, al  ; Swap for endian's sake\n");
  fprintf(fp, "         pop     dx      ; Restore LSB\n");

  fprintf(fp, "         mov     dh, ah  ; Our word is now in DX\n");

  // DX Now has our data and our address is toast

  if (strcmp(pszTarget, "ax") != 0)
    {
      fprintf(fp, "             pop     ax              ; Restore this\n");

      if (strcmp(pszTarget, "dx") != 0)
	{
	  fprintf(fp, "         mov     %s, dx  ; Store our word\n", pszTarget);
	}
    }
  else {
    fprintf(fp, "               mov     ax, dx\n");
    fprintf(fp, "               xchg    ah, al\n");
  }

  fprintf(fp, "         jmp     readExit%ld\n\n", dwGlobalLabel);

  fprintf(fp, "memoryRead%ld:\n", dwGlobalLabel);

  fprintf(fp, "         mov     edi, [edi+12]           ; [J3d!] Get offset\n");
  if (strlen(pszTarget) == 2)
    {
      fprintf(fp, "             mov     %s, [edi + e%s]\n", pszTarget, pszAddress);
      if (strcmp(pszTarget, "ax") == 0)
	{
	  fprintf(fp, "         xchg    ah, al\n");
	}
    }
  else
    {
      fprintf(fp, "             mov     dx, [edi + e%s]\n", pszAddress);
      fprintf(fp, "             mov     %s, dx\n", pszTarget);
    }

  fprintf(fp, "readExit%ld:\n", dwGlobalLabel);
  fprintf(fp, "         mov     edi, [cyclesRemaining]\n");
  // edx is not cleared because it's either the target or it's cleared
  // by the calling function...
  dwGlobalLabel++;
}

#endif

void ReadValueFromIo(char *pszIoAddress, char *pszTarget)
{
  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
  fprintf(fp, "         mov     edi, [_z80IoRead]       ; Point to the read array\n\n");
	fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
	fprintf(fp, "           cmp     [edi], word 0ffffh ; End of the list?\n");
	fprintf(fp, "           je              ioRead%ld\n", dwGlobalLabel);
	fprintf(fp, "           cmp     %s, [edi]       ; Are we smaller?\n", pszIoAddress);
	fprintf(fp, "           jb              nextAddr%ld             ; Yes, go to the next address\n", dwGlobalLabel);
	fprintf(fp, "           cmp     %s, [edi+2]     ; Are we bigger?\n", pszIoAddress);
	fprintf(fp, "           jbe     callRoutine%ld\n\n", dwGlobalLabel);
	fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
	fprintf(fp, "           add     edi, 0ch                ; Next structure!\n");
	fprintf(fp, "           jmp     short checkLoop%ld\n\n", dwGlobalLabel);
	fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);

	if (strcmp(pszIoAddress, "dx") != 0)
		fprintf(fp, "           mov     dx, %s  ; Get our address\n", pszIoAddress);

	fprintf(fp, "           call    ReadIOByte      ; Standard read routine\n");

	// Yes, these are intentionally reversed!

	if (strcmp(pszTarget, "al") == 0)
		fprintf(fp, "           mov     [_z80af], al    ; Save our new accumulator\n");
	else
	if (strcmp(pszTarget, "ah") == 0)
		fprintf(fp, "           mov     [_z80af + 1], ah        ; Save our new flags\n");
	else
	if (strcmp(pszTarget, "dl") == 0)
		fprintf(fp, "           mov     [_z80de], al    ; Put it in E\n");
	else
	if (strcmp(pszTarget, "dh") == 0)
		fprintf(fp, "           mov     [_z80de + 1], al ; Put it in D\n");
	else
	if (strcmp(pszTarget, "*dl") == 0)
		fprintf(fp, "           mov     dl, al  ; Put it in DL for later consumption\n");
	else
		fprintf(fp, "           mov     %s, al  ; Put our returned value here\n", pszTarget);

	// And are properly restored HERE:

	fprintf(fp, "           mov     ax, [_z80af]    ; Get our AF back\n");

	// Restore registers here...

	fprintf(fp, "           jmp     short readExit%ld\n\n", dwGlobalLabel);
	fprintf(fp, "ioRead%ld:\n", dwGlobalLabel);

	if (strcmp(pszTarget, "*dl") == 0)
		fprintf(fp, "           mov     dl, 0ffh        ; An unreferenced read\n");
	else
		fprintf(fp, "           mov     %s, 0ffh        ; An unreferenced read\n", pszTarget);
	fprintf(fp, "readExit%ld:\n", dwGlobalLabel);

	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");
	dwGlobalLabel++;
}

// Basic instruction set area

void MiscHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode == 0xe3)
	{
		if (bThroughCallHandler)
		{
			fprintf(fp, "           call    PopWord\n");
#ifdef WORD_ACCESS
			fprintf(fp, "           mov     [_wordval],dx\n");
#endif
			fprintf(fp, "           xchg    bx, [_wordval]\n");
			fprintf(fp, "           call    PushWord\n");
		}
		else
		{
			fprintf(fp, "           mov     dx, word [_z80sp]\n");
			fprintf(fp, "           xchg    bx, [ebp+edx]\n");
			fprintf(fp, "           xor     edx, edx\n");
		}
	}

	if (dwOpcode == 0x2a)
	{
	  FetchDataW("dx");

#ifdef WORD_ACCESS
		ReadWordFromMemory("dx", "bx");
#else
		ReadValueFromMemory("dx", "bl");
		fprintf(fp, "           inc     dx\n");
		ReadValueFromMemory("dx", "bh");
#endif
		fprintf(fp, "           xor     edx, edx\n");
	}

	if (dwOpcode == 0xfb) // EI
	{
	  fprintf(fp, "myei:\n");
	  fprintf(fp, "         or      dword [_z80iff], (IFF1+IFF2)    ; Indicate interrupts are enabled now\n");
	  fprintf(fp, "         sub     edi, 4  ; Takes 4 cycles!\n");
	  fprintf(fp, "         mov     [dwEITiming], edi       ; Snapshot our current timing\n");
	  fprintf(fp, "         mov     [bEIExit], byte 1       ; Indicate we're exiting because of an EI\n");
	  fprintf(fp, "         mov     edi, 4\n");
	  // Keep enough cycles to execute next instruction (4 cycles for ei)
	  // byte %ld\n", Timing(bCurrentMode, dwOpcode));
	  // Go to FetchNextInstruction... (and exit)
	}

	if (dwOpcode == 0xf9)
		fprintf(fp, "           mov     word [_z80sp], bx\n");

	if (dwOpcode == 0xd9)
	{
	  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
	  fprintf(fp, "         mov     di, [_z80de]\n");
	  fprintf(fp, "         xchg    cx, [_z80bcprime]\n");
	  fprintf(fp, "         xchg    di, [_z80deprime]\n");
	  fprintf(fp, "         xchg    bx, [_z80hlprime]\n");
	  fprintf(fp, "         mov     [_z80de], di\n");
	  fprintf(fp, "         mov     edi, [cyclesRemaining]\n");
	}

	if (dwOpcode == 0x76)
	{
		fprintf(fp, "           mov     word [_z80halted], 1   ; We've halted the chip!\n");
		if (FALSE == bNoTiming)
		{
		  fprintf(fp, "         xor     edi, edi\n");
		  fprintf(fp, "         mov     [cyclesRemaining], edi\n");
		}

		fprintf(fp, "           jmp     noMoreExec\n");
	}

	if (dwOpcode == 0x3f)
	{
		fprintf(fp, "           mov     dl, ah\n");
		fprintf(fp, "           and     dl, 01h\n");
		fprintf(fp, "           shl     dl, 4\n");
		fprintf(fp, "           xor     ah, 01h\n");
		fprintf(fp, "           and     ah, 0edh\n");
		fprintf(fp, "           or      ah, dl\n");
	}

	if (dwOpcode == 0x37)
	{
		fprintf(fp, "           or      ah, 1\n");
		fprintf(fp, "           and     ah,0edh\n");
	}

	if (dwOpcode == 0x27)
	{
		fprintf(fp, "           mov     dh, ah\n");
		fprintf(fp, "           and     dh, 02ah\n");
		fprintf(fp, "           test    ah, 02h ; Were we doing a subtraction?\n");
		fprintf(fp, "           jnz     handleNeg ; Nope!\n");
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           daa\n");
		fprintf(fp, "           lahf\n");
		fprintf(fp, "           jmp     short endDaa\n");
		fprintf(fp, "handleNeg:\n");
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           das\n");
		fprintf(fp, "           lahf\n");
		fprintf(fp, "endDaa:\n");
		fprintf(fp, "           and     ah, 0d5h\n");
		fprintf(fp, "           or      ah, dh\n");
		fprintf(fp, "           xor     edx, edx\n");
	}

	if (dwOpcode == 0x08)
	{
		fprintf(fp, "           xchg    ah, al\n");
		fprintf(fp, "           xchg    ax, [_z80afprime]\n");
		fprintf(fp, "           xchg    ah, al\n");
	}

	if (dwOpcode == 0x07)
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           rol     al, 1\n");
		fprintf(fp, "           lahf\n");
		fprintf(fp, "           and     ah, 0edh\n");
	}

	if (dwOpcode == 0x0f)
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           ror     al, 1\n");
		fprintf(fp, "           lahf\n");
		fprintf(fp, "           and     ah, 0edh\n");
	}

	if (dwOpcode == 0xe9)
	{
		fprintf(fp, "           mov     si, bx\n");
		fprintf(fp, "           and     esi, 0ffffh\n");
		fprintf(fp, "           add     esi, ebp\n");
	}

	if (dwOpcode == 0xeb)
		fprintf(fp, "           xchg    [_z80de], bx    ; Exchange DE & HL\n");

	if (dwOpcode == 0x2f)
	{
		fprintf(fp, "           not     al\n");
		fprintf(fp, "           or      ah, 012h        ; N And H are now on!\n");
	}

	if (dwOpcode == 0x10)	// DJNZ
	{
	  FetchDataB("dl");
		fprintf(fp, "           dec     ch      ; Decrement B\n");
		fprintf(fp, "           jz      noJump  ; Don't take the jump if it's done!\n");
		fprintf(fp, "; Otherwise, take the jump\n");

		fprintf(fp, "           sub     edi, 5\n");

		fprintf(fp, "           xchg    ax, dx\n");
		fprintf(fp, "           cbw\n");
		fprintf(fp, "           xchg    ax, dx\n");
		fprintf(fp, "           sub     esi, ebp\n");
		fprintf(fp, "           add     si, dx\n");
		fprintf(fp, "           add     esi, ebp\n");
		fprintf(fp, "noJump:\n");
		fprintf(fp, "           xor     edx, edx\n");
	}

	if (dwOpcode == 0x3a)	// LD A,(xxxx)
	{
	  FetchDataW("dx");
	  ReadValueFromMemory("dx", "al");
	  fprintf(fp, "         xor     edx, edx        ; Make sure we don't hose things\n");
	}

	if (dwOpcode == 0xf3)	// DI
	{
	  fprintf(fp, "         and     dword [_z80iff], (~(IFF1+IFF2)) ; Not in an interrupt\n");
	}

	FetchNextInstruction(dwOpcode);
}

void LdRegPairImmediate(UINT32 dwOpcode)
{
	UINT8 bOp = 0;

	ProcBegin(dwOpcode);

	bOp = (dwOpcode >> 4) & 0x3;

	if (bOp == 0)
	  FetchDataW("cx");
	else
	if (bOp == 2)
	  FetchDataW("bx");
	else
	if (bOp == 1)
	{
	  FetchDataW("dx");
		fprintf(fp, "           mov     word [_z80de], dx ; Store DE\n");
		fprintf(fp, "           xor     edx, edx\n");
	}
	else
	if (bOp == 3)
	{
	  FetchDataW("dx");
	  fprintf(fp, "         mov     word [_z80sp], dx       ; Store it!\n");
	  fprintf(fp, "         xor     edx, edx\n");
	}

	FetchNextInstruction(dwOpcode);
}

void LdRegpairPtrByte(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode == 0x36)	// Immediate into (HL)
		WriteValueToMemory("bx", "[esi]");

	if (dwOpcode == 0x12)
		WriteValueToMemory("[_z80de]", "al");   // (DE), A

	if (dwOpcode == 0x2)		// (BC), A
		WriteValueToMemory("cx", "al");

	if (dwOpcode >= 0x70 && dwOpcode < 0x78)
		WriteValueToMemory("bx", pbMathReg[dwOpcode & 0x07]);

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void MathOperation(UINT32 dwOrgOpcode)
{
	UINT8 bRegister;
	UINT32 dwOpcode;
	char tempstr[150];

	ProcBegin(dwOrgOpcode);

	dwOpcode = dwOrgOpcode;
	bRegister = dwOpcode & 0x07;
	dwOpcode &= 0xf8;

	if (dwOpcode == 0x80)
		strcpy(tempstr, "add");
	if (dwOpcode == 0x88)
		strcpy(tempstr, "adc");
	if (dwOpcode == 0x90)
		strcpy(tempstr, "sub");
	if (dwOpcode == 0x98)
		strcpy(tempstr, "sbb");
	if (dwOpcode == 0xa0)
		strcpy(tempstr, "and");
	if (dwOpcode == 0xa8)
		strcpy(tempstr, "xor");
	if (dwOpcode == 0xb0)
		strcpy(tempstr, "or");
	if (dwOpcode == 0xb8)
		strcpy(tempstr, "cmp");

	// Let's see if we have to deal with (HL) or #xxh

	if (bRegister == 0x6)
	{
		// We have to deal with (HL)

		ReadValueFromMemory("bx", "dl");
	}

	if (bRegister != 0x06 && bRegister < 0xff)
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           %s      al, %s\n", tempstr, pbMathReg[bRegister]);
		fprintf(fp, "           lahf\n");
	}
	else	// If it's (HL)....
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           %s      al, dl\n", tempstr);
		fprintf(fp, "           lahf\n");
	}

	if (dwOpcode != 0xa8 && dwOpcode != 0xa0 && dwOpcode != 0xb0)
		SetOverflow();

	if (dwOpcode == 0xa8)
		fprintf(fp, "           and     ah, 0ech        ; Only these flags matter!\n");

	if (dwOpcode == 0xa0)
	{
		fprintf(fp, "           and     ah, 0ech        ; Only these flags matter!\n");
		fprintf(fp, "           or      ah, 010h        ; Half carry gets set\n");
	}

	if (dwOpcode == 0xb0)
		fprintf(fp, "           and     ah, 0ech ; No H, N, or C\n");

	if (dwOpcode == 0xb8)
		fprintf(fp, "           or      ah, 02h ; Set N for compare!\n");

	if (dwOpcode == 0x80 || dwOpcode == 0x88)
		fprintf(fp, "           and     ah, 0fdh ; No N!\n");

	if (dwOpcode == 0x90 || dwOpcode == 0x98)
		fprintf(fp, "           or      ah, 02h ; N Gets set!\n");

	if (bRegister == 0x6)
	  fprintf(fp, "         xor     edx, edx        ; Zero this...\n");

	FetchNextInstruction(dwOpcode);
}

void RegIntoMemory(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataW("dx");

	if (0x32 == dwOpcode)		// LD (xxxx), A
		WriteValueToMemory("dx", "al");
	if (0x22 == dwOpcode)		// LD (xxxx), HL
	{
#ifdef WORD_ACCESS
		WriteWordToMemory("dx", "bx");
#else
		WriteValueToMemory("dx", "bl");
		fprintf(fp, "           inc     dx\n");
		WriteValueToMemory("dx", "bh");
#endif
	}

	fprintf(fp, "           xor     edx, edx        ; Zero our upper byte\n");
	FetchNextInstruction(dwOpcode);
}

void JpHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (0xc3 == dwOpcode)	// If it's a straight jump...
	{
	  FetchDataW("si");
		fprintf(fp, "           and     esi, 0ffffh     ; Only the lower 16 bits\n");
		fprintf(fp, "           add     esi, ebp                ; Our new address!\n");
	}
	else	// It's a conditional handler...
	{
	  if (0xf2 == dwOpcode) // Test parity....
	    fprintf(fp,"; JP P,xxx\n");
	  fprintf(fp, "         sahf            ; Restore our flags\n");
	  fprintf(fp, "         j%s     takeJump%ld     ; We're going to take a jump\n", pbFlags[(dwOpcode >> 3) & 0x07], dwGlobalLabel);
	  fprintf(fp, "         add     esi, 2          ; Skip past the address\n");
	  fprintf(fp, "         jmp     nextInst%ld        ; Go execute the next instruction\n", dwGlobalLabel);
	  fprintf(fp, "takeJump%ld:\n", dwGlobalLabel);


	  FetchDataW("si");

	  fprintf(fp, "         and     esi, 0ffffh     ; Only the lower INT16 is valid\n");
	  fprintf(fp, "         add     esi, ebp                ; Our new address!\n");
	  fprintf(fp, "nextInst%ld:\n", dwGlobalLabel);
	  ++dwGlobalLabel;
	}

	FetchNextInstruction(dwOpcode);
}

void LdRegImmediate(UINT32 dwOpcode)
{
	UINT8 bOp;

	ProcBegin(dwOpcode);

	bOp = (dwOpcode >> 3) & 0x7;

	if (bOp != 2 && bOp != 3)
	  FetchDataB(pbMathReg[bOp]);
	else
	{
	  FetchDataB("dl");
		fprintf(fp, "           mov     %s, dl  ; Store our new value\n", pbMathReg[bOp]);
	}

	FetchNextInstruction(dwOpcode);
}

void IncRegister(UINT32 dwOpcode)
{
	UINT32 dwOpcode1 = 0;

	ProcBegin(dwOpcode);

	fprintf(fp, "           sahf\n");
	dwOpcode1 = (dwOpcode >> 3) & 0x07;
	fprintf(fp,	"               inc     %s\n", pbMathReg[dwOpcode1]);
	fprintf(fp,	"               lahf\n");
	SetOverflow();
	fprintf(fp, "           and     ah, 0fdh        ; Knock out N!\n");

	FetchNextInstruction(dwOpcode);
}

void DecRegister(UINT32 dwOpcode)
{
	UINT32 dwOpcode1 = 0;

	ProcBegin(dwOpcode);

	fprintf(fp, "           sahf\n");
	dwOpcode1 = (dwOpcode >> 3) & 0x07;
	fprintf(fp,	"               dec     %s\n", pbMathReg[dwOpcode1]);
	fprintf(fp,	"               lahf\n");
	SetOverflow();
	fprintf(fp, "           or      ah, 02h ; Set negative!\n");

	FetchNextInstruction(dwOpcode);
}

void IncDecRegpair(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if ((dwOpcode & 0x0f) == 3)	// Increment?
		fprintf(fp,	"               inc     %s\n", pbRegPairs[(dwOpcode >> 4) & 0x03]);
	else
		fprintf(fp,	"               dec     %s\n", pbRegPairs[(dwOpcode >> 4) & 0x03]);

	FetchNextInstruction(dwOpcode);
}

void LdRegReg(UINT32 dwOpcode)
{
	UINT8 bDestination;
	UINT8 bSource;

	bDestination = (dwOpcode >> 3) & 0x07;
	bSource = (dwOpcode) & 0x07;

	ProcBegin(dwOpcode);

	if (bSource != bDestination)
	{
		if (bSource == 2 && bDestination == 3)
		{
			fprintf(fp, "           mov     dl, byte [_z80de + 1]\n");
			fprintf(fp, "           mov     [_z80de], dl\n");
		}
		else
		if (bSource == 3 && bDestination == 2)
		{
			fprintf(fp, "           mov     dl, byte [_z80de]\n");
			fprintf(fp, "           mov     [_z80de + 1], dl\n");
		}
		else
			fprintf(fp, "           mov     %s, %s\n", pbMathReg[bDestination], pbMathReg[bSource]);
	}

	FetchNextInstruction(dwOpcode);
}

void MathOperationDirect(UINT32 dwOpcode)
{
	char tempstr[4];

	if (dwOpcode == 0xc6)
		strcpy(tempstr, "add");
	if (dwOpcode == 0xce)
		strcpy(tempstr, "adc");
	if (dwOpcode == 0xd6)
		strcpy(tempstr, "sub");
	if (dwOpcode == 0xde)
		strcpy(tempstr, "sbb");
	if (dwOpcode == 0xe6)
		strcpy(tempstr, "and");
	if (dwOpcode == 0xee)
		strcpy(tempstr, "xor");
	if (dwOpcode == 0xf6)
		strcpy(tempstr, "or");
	if (dwOpcode == 0xfe)
		strcpy(tempstr, "cmp");

	ProcBegin(dwOpcode);

	// Let's see if we have to deal with (HL) or #xxh

	FetchDataB("dl");
	fprintf(fp, "           sahf\n");
	fprintf(fp, "           %s      al, dl\n", tempstr);
	fprintf(fp, "           lahf\n");

	if (dwOpcode != 0xee && dwOpcode != 0xe6 && dwOpcode != 0xf6)
	{
		SetOverflow();
	}

	if (dwOpcode == 0xe6)
	{
		fprintf(fp, "           and     ah, 0ech ; Only parity, half carry, sign, zero\n");
		fprintf(fp, "           or      ah, 10h ; Half carry\n");
	}

	if (dwOpcode == 0xc6 || dwOpcode == 0xce)
		fprintf(fp, "           and     ah, 0fdh ; Knock out N!\n");

	if (dwOpcode == 0xd6 || dwOpcode == 0xde || dwOpcode == 0xfe)
		fprintf(fp, "           or      ah, 02h ; Set negative!\n");

	if (dwOpcode == 0xf6 || dwOpcode == 0xee)
		fprintf(fp, "           and     ah, 0ech        ; No H, N, or C\n");
	// fprintf(fp,"            xor edx,edx\n");

	FetchNextInstruction(dwOpcode);
}

// JR cc, addr

void JrHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataB("dl");

	if (dwOpcode != 0x18)
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp,	"               j%s     takeJump%ld\n", pbFlags[(dwOpcode >> 3) & 0x3], dwGlobalLabel);
		fprintf(fp, "           jmp     noJumpMan%ld\n", dwGlobalLabel);
		fprintf(fp, "takeJump%ld:\n", dwGlobalLabel);

		if (FALSE == bNoTiming)
		  {
		    fprintf(fp, "               sub     edi, 5\n");
		  }

	}
	else	// It's a JR
	{
		fprintf(fp, "           cmp     dl, 0feh        ; Jump to self?\n");
		fprintf(fp, "           je              yesJrMan        ; Yup! Bail out!\n");
	}

	fprintf(fp, "           xchg    eax, edx\n");
	fprintf(fp, "           cbw\n");
	fprintf(fp, "           xchg    eax, edx\n");
	fprintf(fp, "           sub     esi, ebp\n");
	fprintf(fp, "           add     si, dx\n");
	fprintf(fp, "           and     esi, 0ffffh     ; Only the lower 16 bits\n");
	fprintf(fp, "           add     esi, ebp\n");
	fprintf(fp, "           xor     dh, dh\n");
	fprintf(fp, "noJumpMan%ld:\n", dwGlobalLabel++);

	FetchNextInstruction(dwOpcode);

	if (0x18 == dwOpcode)
	{
		fprintf(fp,"yesJrMan:\n");

		fprintf(fp, "           xor     edx, edx                ; Zero me for later\n");
		fprintf(fp, "           mov     edi, edx\n");
		fprintf(fp, "           mov     [cyclesRemaining], edx\n");
		fprintf(fp, "           sub     esi, 2  ; Back to the instruction again\n");
		fprintf(fp, "           jmp     noMoreExec\n\n");
	}
}

void CallHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode != 0xcd)
	{
		fprintf(fp, "           sahf            ; Restore our flags\n");
		fprintf(fp, "           j%s     takeJump%ld     ; We're going call in this case\n", pbFlags[(dwOpcode >> 3) & 0x07], dwGlobalLabel);
		fprintf(fp, "           add     esi, 2          ; Skip past the address\n");
		fprintf(fp, "           jmp     noCallTaken%ld     ; Go execute the next instruction\n", dwGlobalLabel);
		fprintf(fp, "takeJump%ld:\n", dwGlobalLabel);

		fprintf(fp, "           sub     edi, 7\n");
	}


	if (bThroughCallHandler)
	{
	  FetchDataW("dx");
		fprintf(fp, "           mov     [_z80pc], dx ; Store our new program counter\n");
		fprintf(fp, "           sub     esi, ebp                ; Value to push onto the \"stack\"\n");
		fprintf(fp, "           mov     [_wordval], si  ; Store our return address on the stack\n");
		fprintf(fp, "           mov     si, dx          ; Our new address\n");
		fprintf(fp, "           add     esi, ebp        ; And our base address\n");
		fprintf(fp, "           call    PushWord        ; Go push our orgval to the stack\n");
	}
	else
	{
	  FetchDataW("dx");
		fprintf(fp, "           mov     [_z80pc], dx ; Store our new program counter\n");
		fprintf(fp, "           sub     esi, ebp                ; Value to push onto the \"stack\"\n");
		fprintf(fp, "           mov     dx, word [_z80sp] ; Get the current stack pointer\n");
		fprintf(fp, "           sub     dx, 2           ; Back up two bytes\n");
		fprintf(fp, "           mov     [ebp+edx], si ; PUSH It!\n");
		fprintf(fp, "           mov     word [_z80sp], dx       ; Store our new stack pointer\n");
		fprintf(fp, "           mov     si, [_z80pc] ; Get our new program counter\n");
		fprintf(fp, "           add     esi, ebp                ; Naturalize it!\n");
	}

	if (dwOpcode != 0xcd)
		fprintf(fp, "noCallTaken%ld:\n", dwGlobalLabel++);

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void RetHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode != 0xc9)
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           j%s     takeReturn%ld\n", pbFlags[(dwOpcode >> 3) & 0x07], dwGlobalLabel);
		fprintf(fp, "           jmp     retNotTaken%ld\n", dwGlobalLabel);
		fprintf(fp, "takeReturn%ld:\n", dwGlobalLabel);

		if (FALSE == bNoTiming)
		  {
		    fprintf(fp, "               sub     edi, byte 6\n");
		  }
	}


	if (bThroughCallHandler)
	{
		fprintf(fp, "           call    PopWord\n");
		fprintf(fp, "           xor     esi, esi\n");
		fprintf(fp, "           mov     si, dx\n");
		fprintf(fp,	"               add     esi, ebp\n");
		fprintf(fp, "           xor     edx, edx\n");
	}
	else
	{
		fprintf(fp, "           mov     dx, word [_z80sp]       ; Get our current stack pointer\n");
		fprintf(fp, "           mov     si, [edx+ebp]   ; Get our return address\n");
		fprintf(fp, "           and     esi, 0ffffh             ; Only within 64K!\n");
		fprintf(fp, "           add     esi, ebp                        ; Add in our base address\n");
		fprintf(fp, "           add     word [_z80sp], 02h      ; Remove our two bytes from the stack\n");
		fprintf(fp, "           xor     edx, edx\n");
	}

	if (dwOpcode != 0xc9)
		fprintf(fp, "retNotTaken%ld:\n", dwGlobalLabel++);

	FetchNextInstruction(dwOpcode);
}

void RestartHandler(UINT32 dwOpcode)
{
	UINT32 dwOpcode1 = 0;

	ProcBegin(dwOpcode);
	dwOpcode1 = dwOpcode & 0x38;


	if (bThroughCallHandler)
	{
		fprintf(fp, "           sub     esi, ebp\n");
		fprintf(fp, "           mov     [_wordval], si  ; Store our return address\n");
		fprintf(fp, "           call    PushWord\n");
		fprintf(fp, "           xor     esi, esi\n");
		fprintf(fp, "           mov     si, %.4lxh\n", dwOpcode1);
		fprintf(fp, "           add     esi, ebp\n");
	}
	else
	{
		fprintf(fp, "           mov     dx, word [_z80sp]       ; Get our stack pointer\n");
		fprintf(fp, "           sub     dx, 2           ; Make room for the new value!\n");
		fprintf(fp, "           mov     word [_z80sp], dx       ; Store our new stack pointer\n");
		fprintf(fp, "           sub     esi, ebp                ; Get our real PC\n");
		fprintf(fp, "           mov     [ebp+edx], si   ; Our return address\n");
		fprintf(fp, "           mov     si, 0%.2xh      ; Our new call address\n", (UINT8) dwOpcode1);
		fprintf(fp, "           add     esi, ebp        ; Back to the base!\n");
	}

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void ToRegFromHl(UINT32 dwOpcode)
{
	UINT8 bReg;

	ProcBegin(dwOpcode);

	bReg = (dwOpcode >> 3) & 0x07;

	if (bReg != 2 && bReg != 3)
		ReadValueFromMemory("bx", pbMathReg[bReg]);
	else
	{
		ReadValueFromMemory("bx", pbLocalReg[bReg]);
		fprintf(fp, "           mov     %s, %s\n", pbMathReg[bReg], pbLocalReg[bReg]);
	}

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void AddRegpairOperations(UINT32 dwOpcode)
{
	UINT8 bRegpair;

	bRegpair = (dwOpcode >> 4) & 0x3;

	ProcBegin(dwOpcode);

	fprintf(fp, "           mov     dh, ah  ; Get our flags\n");
	fprintf(fp, "           and     dh, 0ech        ; Preserve the top three and bits 2 & 3\n");

	fprintf(fp, "           mov     [_orgval], bx   ; Store our original value\n");
	fprintf(fp, "           add     bx, %s\n", pbRegPairs[bRegpair]);
	fprintf(fp, "           lahf\n");

	fprintf(fp, "           mov     [cyclesRemaining], edi\n");
	fprintf(fp, "           mov     di, [_orgval]   ; Get original\n");
	fprintf(fp, "           xor     di, bx ; XOR It with our computed value\n");
	fprintf(fp, "           xor     di, %s\n", pbRegPairs[bRegpair]);
	fprintf(fp, "           and     di, 1000h       ; Just our half carry\n");
	fprintf(fp, "           or              dx, di  ; Or in our flags\n");
	fprintf(fp, "           and     ah, 01h ; Just carry\n");
	fprintf(fp, "           or      ah, dh\n");
	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void PushPopOperations(UINT32 dwOpcode)
{
	UINT8 bRegPair;

	bRegPair = ((dwOpcode >> 4) & 0x3) << 1;
	ProcBegin(dwOpcode);

	if ((dwOpcode & 0xcf) == 0xc5)	// Push
	{
		fprintf(fp, "           sub     word [_z80sp], 2\n");
		fprintf(fp, "           mov     dx, [_z80sp]\n");
#ifdef WORD_ACCESS
		  WriteWordToMemory("dx", pbPopRegPairs[bRegPair >> 1]);
#else
		WriteValueToMemory("dx", pbPushReg[bRegPair]);
		fprintf(fp, "           inc     dx\n");
		WriteValueToMemory("dx", pbPushReg[bRegPair + 1]);
#endif
	}
	else	// Pop
	{
	  fprintf(fp, "         mov     dx, [_z80sp]\n");
#ifdef WORD_ACCESS
	    ReadWordFromMemory("dx", pbPopRegPairs[bRegPair >> 1]);
#else
		ReadValueFromMemory("dx", pbPushReg[bRegPair]);
		fprintf(fp, "           inc     dx\n");
		ReadValueFromMemory("dx", pbPushReg[bRegPair + 1]);
#endif
		fprintf(fp, "           add     word [_z80sp], 2\n");
	}

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void RraRlaHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           sahf\n");
	if (dwOpcode == 0x1f)
		fprintf(fp, "           rcr     al, 1\n");
	else
		fprintf(fp, "           rcl     al, 1\n");

	fprintf(fp, "           lahf\n");
	fprintf(fp, "           and     ah, 0edh\n");

	FetchNextInstruction(dwOpcode);
}

void LdByteRegpair(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode == 0x0a)
		ReadValueFromMemory("cx", "al");
	if (dwOpcode == 0x1a)
	{
		fprintf(fp, "           mov     dx, [_z80de]\n");
		ReadValueFromMemory("dx", "al");
	}

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void IncDecHLPtr(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	ReadValueFromMemory("bx", "dl");

	fprintf(fp, "           sahf\n");

	if (dwOpcode == 0x34)
		fprintf(fp, "           inc     dl\n");
	else
		fprintf(fp, "           dec     dl\n");
	fprintf(fp, "           lahf\n");

	fprintf(fp, "           o16     pushf\n");
	fprintf(fp, "           shl     edx, 16\n");
	fprintf(fp, "           and     ah, 0fbh        ;       Knock out parity/overflow\n");
	fprintf(fp, "           pop     dx\n");
	fprintf(fp, "           and     dh, 08h ; Just the overflow\n");
	fprintf(fp, "           shr     dh, 1   ; Shift it into position\n");
	fprintf(fp, "           or      ah, dh  ; OR It in with the real flags\n");
	fprintf(fp, "           shr     edx, 16\n");

	if (dwOpcode == 0x34)
		fprintf(fp, "           and     ah, 0fdh        ; Knock out N!\n");
	else
		fprintf(fp, "           or              ah, 02h ; Make it N!\n");

	WriteValueToMemory("bx", "dl");
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void InOutHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataB("dl");
	fprintf(fp, "           cmp     [Z80Has16bitsPorts],byte 0\n");
	fprintf(fp, "           je      ignoreal%ld\n",dwGlobalLabel);
	fprintf(fp,"            mov dh,al\n"); //z80 documented 4.4
	fprintf(fp, "ignoreal%ld:\n",dwGlobalLabel++);

	if (0xd3 == dwOpcode)
		WriteValueToIo("dx", "al");
	else
		ReadValueFromIo("dx", "al");

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

// CB Area

void RESSETHandler(UINT32 dwOpcode)
{
	UINT8 op = 0;

	ProcBegin(dwOpcode);

	op = dwOpcode & 0x07;

	if ((2 == op) || (3 == op))
		fprintf(fp, "           mov     dx, [_z80de]    ; Move DE into something half usable\n");

	if ((dwOpcode & 0x07) == 6)	// (HL)?
		ReadValueFromMemory("bx", "dl");

	if ((dwOpcode & 0xc0) == 0x80)
		fprintf(fp, "           and %s, 0%.2xh  ; Reset a bit\n",
						pbLocalReg[op],
						0xff - (1 << ((dwOpcode >> 3) & 0x7)));

	if ((dwOpcode & 0xc0) == 0xc0)
		fprintf(fp, "           or      %s, 0%.2xh      ; Set a bit\n",
						pbLocalReg[op],
						(1 << ((dwOpcode >> 3) & 0x7)));

	if ((2 == op) || (3 == op))
	{
		fprintf(fp, "           mov     [_z80de], dx    ; Once modified, put it back\n");
		fprintf(fp, "           xor     edx, edx\n");
	}

	if ((dwOpcode & 0x07) == 6)	// (HL)?
	{
		WriteValueToMemory("bx", "dl");
		fprintf(fp, "           xor     edx, edx\n");
	}

	FetchNextInstruction(dwOpcode);
}

void BITHandler(UINT32 dwOpcode)
{
	UINT8 op = 0;

	ProcBegin(dwOpcode);

	op = dwOpcode & 0x07;

	if ((dwOpcode & 0x07) == 6)	// (HL)?
		ReadValueFromMemory("bx", "dl");

	fprintf(fp, "           mov     byte [_z80af], ah ; Store F\n");
	fprintf(fp, "           sahf\n");

	if ((dwOpcode & 0x07) == 6)
		fprintf(fp, "           test    dl, 0%.2xh      ; Do a bitwise check\n", 1 << ((dwOpcode >> 3) & 0x7));
	else
		fprintf(fp, "           test %s, 0%.2xh ; Do a bitwise check\n", pbMathReg[op], 1 << ((dwOpcode >> 3) & 0x7));

	fprintf(fp, "           lahf\n");
	fprintf(fp, "           and     ah, 0c0h        ; Only care about Z and S\n");
	fprintf(fp, "           or      ah, 10h ; Set half carry to 1\n");

	fprintf(fp, "           and     byte [_z80af], 029h             ; Only zero/non-zero!\n");
	fprintf(fp, "           or      ah, byte [_z80af]       ; Put it in with the real flags\n");

	if (6 == (dwOpcode & 0x07))	// (HL)?
	  fprintf(fp, "         xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void RLCRRCRLRRSLASRASRLHandler(UINT32 dwOpcode)
{
	UINT8 op = 0;

	ProcBegin(dwOpcode);
	op = dwOpcode & 0x07;

	if ((2 == op) || (3 == op))
		fprintf(fp, "           mov     dx, [_z80de]    ; Move DE into something half usable\n");

	if ((dwOpcode & 0x07) == 6)	// (HL)?
		ReadValueFromMemory("bx", "dl");

	fprintf(fp, "           sahf\n");

	if ((dwOpcode & 0xf8) == 0)
		fprintf(fp, "           rol     %s, 1\n", pbLocalReg[op]);
	else
	if ((dwOpcode & 0xf8) == 0x08)
		fprintf(fp, "           ror     %s, 1\n", pbLocalReg[op]);
	else
	if ((dwOpcode & 0xf8) == 0x10)
		fprintf(fp, "           rcl     %s, 1\n", pbLocalReg[op]);
	else
	if ((dwOpcode & 0xf8) == 0x18)
		fprintf(fp, "           rcr     %s, 1\n", pbLocalReg[op]);
	else
	if ((dwOpcode & 0xf8) == 0x20 || (dwOpcode & 0xf8) == 0x30)
		fprintf(fp, "           shl     %s, 1\n", pbLocalReg[op]);
	else
	if ((dwOpcode & 0xf8) == 0x28)
		fprintf(fp, "           sar     %s, 1\n", pbLocalReg[op]);
	else
	if ((dwOpcode & 0xf8) == 0x38)
		fprintf(fp, "           shr     %s, 1\n", pbLocalReg[op]);
	else
		assert(0);

	fprintf(fp, "           lahf\n");

	if ((dwOpcode & 0xf8) >= 0x20)
	{
		if ((dwOpcode & 0xf8) == 0x30)
			fprintf(fp, "           or      %s, 1   ; Slide in a 1 bit (SLIA)\n", pbLocalReg[op]);
		fprintf(fp, "           and     ah, 0edh        ; Clear H and N\n");
	}
	else
	{
		fprintf(fp, "           and     ah, 029h        ; Clear H and N\n");
		fprintf(fp, "           mov     byte [_z80af], ah\n");

		fprintf(fp, "           or      %s, %s\n", pbLocalReg[op], pbLocalReg[op]);

		fprintf(fp,	"               lahf\n");
		fprintf(fp, "           and     ah, 0c4h        ; Sign, zero, and parity\n");
		fprintf(fp, "           or      ah, byte [_z80af]\n");
	}

	if ((2 == op) || (3 == op))
	{
		fprintf(fp, "           mov     [_z80de], dx    ; Once modified, put it back\n");
		fprintf(fp, "           xor     edx, edx\n");
	}

	if ((dwOpcode & 0x07) == 6)	// (HL)?
	{
		WriteValueToMemory("bx", "dl");
		fprintf(fp, "           xor     edx, edx\n");
	}

	FetchNextInstruction(dwOpcode);
}

// ED Area

void RRDRLDHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	ReadValueFromMemory("bx", "dl");        // Get (HL)
	fprintf(fp, "           mov     dh, dl  ; Put a copy in DH\n");

	if (0x6f == dwOpcode)	// RLD
	{
		fprintf(fp, "           shr     dh, 4   ; Get our upper nibble in position\n");
		fprintf(fp, "           shl     dl, 4   ; Get our lower nibble into the higher position\n");
		fprintf(fp, "           shl     ecx, 16 ; Save this for later\n");
		fprintf(fp, "           mov     cl, al\n");
		fprintf(fp, "           and     cl, 0fh\n       ; Only the lower nibble\n");
		fprintf(fp, "           or      dl, cl  ; OR In A->(HL) transfer\n");
		fprintf(fp, "           and     al, 0f0h        ; Only the upper 4 bits remain\n");
		fprintf(fp, "           or      al, dh  ; OR It in to our accumulator\n");
		fprintf(fp, "           shr     ecx, 16 ; Restore this\n");
	}
	else			//	RRD
	if (0x67 == dwOpcode)
	{
		fprintf(fp, "           shr     dl, 4   ; Upper nibble to lower nibble\n");
		fprintf(fp, "           shl     ecx, 16 ; Save this\n");
		fprintf(fp, "           mov     cl, al\n");
		fprintf(fp, "           shl     cl, 4\n");
		fprintf(fp, "           or      dl, cl  ; OR In what was in A\n");
		fprintf(fp, "           and     al, 0f0h        ; Knock out lower part\n");
		fprintf(fp, "           and     dh, 0fh ; Only the lower nibble\n");
		fprintf(fp, "           or      al, dh  ; OR In our nibble\n");
		fprintf(fp, "           shr     ecx, 16 ; Restore this\n");
	}
	else	// Whoops!
		assert(0);

	// This routine assumes that the new value to be placed at (HL) is in DL

	fprintf(fp, "           and     ah, 29h ; Retain carry & two undefined bits\n");
	fprintf(fp, "           mov     dh, ah  ; Store our flags away for later\n");

	fprintf(fp, "           or      al, al  ; Get our flags\n");
	fprintf(fp, "           lahf\n");
	fprintf(fp, "           and     ah,0c4h ; Only partiy, zero, and sign\n");
	fprintf(fp, "           or      ah, dh  ; OR In our old flags\n");

	// Now go write the value back

	WriteValueToMemory("bx", "dl");
	fprintf(fp, "           xor     edx, edx        ; Zero out this for later\n");

	FetchNextInstruction(dwOpcode);
}

void CPICPDCPIRCPDRHandler(UINT32 dwOpcode)
{
	UINT32 dwRepeatOb = 0;

	ProcBegin(dwOpcode);

	if (dwOpcode == 0xb1 || dwOpcode == 0xb9)
	{
		fprintf(fp, "cpRepeat%ld:\n", dwGlobalLabel);
		dwRepeatOb = dwGlobalLabel;
		++dwGlobalLabel;
	}

	// Now go get the data from the source

	ReadValueFromMemory("bx", "dl");

	// Target data is in DL

	fprintf(fp, "           mov     byte [_z80af], ah\n");
	fprintf(fp, "           sahf\n");
	fprintf(fp, "           cmp     al, dl  ; Do our comparison\n");
	fprintf(fp, "           lahf\n");
	fprintf(fp, "           and     ah, 0fah        ; No P/V or carry!\n");
	fprintf(fp, "           dec     cx      ; Dec BC\n");
	fprintf(fp, "           jz      notBcZero%ld\n", dwGlobalLabel);
	fprintf(fp, "           or      ah, 04h ; P/V set when BC not zero\n");
	fprintf(fp, "notBcZero%ld:\n", dwGlobalLabel);
	fprintf(fp, "           or      ah, 02h ; N Gets set when we do compares\n");
	fprintf(fp, "           mov     dl, byte [_z80af]\n");
	fprintf(fp, "           and     dl, 01h\n");
	fprintf(fp, "           or      ah, dl  ; Preserve carry!\n");

	if (dwOpcode == 0xa1 || dwOpcode == 0xb1)
		fprintf(fp, "           inc     bx      ; Increment!\n");
	if (dwOpcode == 0xa9 || dwOpcode == 0xb9)
		fprintf(fp, "           dec     bx      ; Decrement!\n");

	// Let's see if we repeat...

	if (dwOpcode == 0xb1 || dwOpcode == 0xb9)
	{
		fprintf(fp, "           sahf\n");
		fprintf(fp, "           jz      BCDone%ld\n", dwRepeatOb);
		fprintf(fp, "           jnp     BCDone%ld\n", dwRepeatOb);

		if (FALSE == bNoTiming)
		  {
		    fprintf(fp, "               sub     edi, dword 21\n");
		    fprintf(fp, "               js              BCDoneExit%ld\n", dwRepeatOb);
		  }
		fprintf(fp, "           jmp     cpRepeat%ld\n", dwRepeatOb);

		fprintf(fp, "BCDoneExit%ld:\n", dwRepeatOb);
		fprintf(fp, "           sub     esi, 2  ;       Back up to the instruction again\n");
		fprintf(fp, "           jmp     noMoreExec\n\n");
		fprintf(fp, "BCDone%ld:\n", dwRepeatOb);

	}
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);

}

void INIRINDRINIINDHandler(UINT32 dwOpcode)
{
	UINT32 dwTempLabel = 0;

	ProcBegin(dwOpcode);

	dwTempLabel = dwGlobalLabel;
	dwGlobalLabel++;

	if (0xba == dwOpcode || 0xb2 == dwOpcode)
		fprintf(fp, "loopIt%ld:\n", dwTempLabel);

	// First we decrement B

	//fprintf(fp, "         dec     ch      ; Decrement B (of C)\n");

	// Fetch what's at (C) and put it in (HL)

	fprintf(fp, "           push    cx      ; Save BC\n");
	fprintf(fp, "           cmp     [Z80Has16bitsPorts],byte 1\n");
	fprintf(fp, "           je      keepch%ld\n",dwTempLabel);
	fprintf(fp, "           xor     ch, ch ; We want 8 bit ports\n");
	fprintf(fp, "keepch%ld:\n",dwTempLabel);
	ReadValueFromIo("cx", "*dl");           // Put our value in DL
	fprintf(fp, "           pop     cx      ; Restore BC\n");

	WriteValueToMemory("bx", "dl");

	if (0xa2 == dwOpcode || 0xb2 == dwOpcode)
		fprintf(fp, "           inc     bx      ; Increment HL\n");
	else
	if (0xaa == dwOpcode || 0xba == dwOpcode)
		fprintf(fp, "           dec     bx      ; Decrement HL\n");

	// Now we decrement B

	fprintf(fp, "           dec     ch      ; Decrement B (of C)\n");

	// Emit this instruction if we repeat

	if (0xba == dwOpcode || 0xb2 == dwOpcode)
		fprintf(fp, "           jnz     near loopIt%ld\n", dwTempLabel);

	// Now let's fix up the flags

	fprintf(fp, "           jnz     clearFlag%ld\n", dwTempLabel);
	fprintf(fp, "           or      ah, 040h        ; Set the Zero flag!\n");
	fprintf(fp, "           jmp     short continue%ld\n", dwTempLabel);
	fprintf(fp, "clearFlag%ld:\n", dwTempLabel);
	fprintf(fp, "           and     ah, 0bfh        ; Clear the zero flag\n");
	fprintf(fp, "continue%ld:\n", dwTempLabel);
	fprintf(fp, "           or      ah, 02h ; Set negative!\n");
	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void OTIROTDROUTIOUTDHandler(UINT32 dwOpcode)
{
	UINT32 dwTempLabel = 0;

	ProcBegin(dwOpcode);

	dwTempLabel = dwGlobalLabel;
	dwGlobalLabel++;

	if (0xbb == dwOpcode || 0xb3 == dwOpcode)
		fprintf(fp, "loopIt%ld:\n", dwTempLabel);

	// Now we decrement B

	//fprintf(fp, "         dec     ch      ; Decrement B (of C)\n");

	// Fetch what's at (HL) and put it in DL

	ReadValueFromMemory("bx", "dl");

	fprintf(fp, "           push    cx      ; Save BC\n");
	fprintf(fp, "           cmp     [Z80Has16bitsPorts],byte 1\n");
	fprintf(fp, "           je      keepch%ld\n",dwTempLabel);
	fprintf(fp, "           xor     ch, ch  ; No 16 bit for this instruction!\n");
	fprintf(fp, "keepch%ld:\n",dwTempLabel);
	WriteValueToIo("cx", "dl");
	fprintf(fp, "           pop     cx      ; Restore BC now that it has been \"OUT\"ed\n");

	if (0xa3 == dwOpcode || 0xb3 == dwOpcode)
		fprintf(fp, "           inc     bx      ; Increment HL\n");
	else
	if (0xab == dwOpcode || 0xbb == dwOpcode)
		fprintf(fp, "           dec     bx      ; Decrement HL\n");

	// Now we decrement B

	fprintf(fp, "           dec     ch      ; Decrement B (of C)\n");

	// Emit this instruction if we repeat

	if (0xbb == dwOpcode || 0xb3 == dwOpcode)
		fprintf(fp, "           jnz     near loopIt%ld\n", dwTempLabel);

	// Now let's fix up the flags

	fprintf(fp, "           jnz     clearFlag%ld\n", dwTempLabel);
	fprintf(fp, "           or      ah, 040h        ; Set the Zero flag!\n");
	fprintf(fp, "           jmp     short continue%ld\n", dwTempLabel);
	fprintf(fp, "clearFlag%ld:\n", dwTempLabel);
	fprintf(fp, "           and     ah, 0bfh        ; Clear the zero flag\n");
	fprintf(fp, "continue%ld:\n", dwTempLabel);
	fprintf(fp, "           or      ah, 02h ; Set negative!\n");
	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

// HIGHLY SUSPECT - ADC/SBC

void AdcSbcRegpair(UINT32 dwOpcode)
{
	UINT8 bOp = 0;

	ProcBegin(dwOpcode);

	bOp = dwOpcode >> 4;

	fprintf(fp, "           mov     dx, %s  ; Get our original register\n", pbRegPairs[bOp & 0x03]);
	fprintf(fp, "           mov     [_orgval], dx   ; Store this for later half carry computation\n");
	fprintf(fp, "           mov     [_orgval2], bx  ; Store this, too\n");
	fprintf(fp, "           sahf            ; Restore our flags\n");

	if ((dwOpcode & 0xcf) == 0x4a)
		fprintf(fp, "           adc     bx, dx  ; Do the operation!\n");
	else
		fprintf(fp, "           sbb     bx, dx  ; Do the operation!\n");

	fprintf(fp, "           lahf            ; Get our new flags\n");

	if ((dwOpcode & 0xcf) != 0x4a)
	{
		SetOverflow();
		fprintf(fp, "           and     ah, 0edh        ; Knock out negative & half carry flags\n");
		fprintf(fp, "           or      ah, 02h ; Negative!\n");
		fprintf(fp, "           mov     [_z80hl], bx\n");
		fprintf(fp, "           xor     bx, [_orgval]\n");
		fprintf(fp, "           xor     bx, [_orgval2]\n");
		fprintf(fp, "           and     bh, 10h ; Half carry?\n");
		fprintf(fp, "           or      ah, bh  ; OR It in if so\n");
		fprintf(fp, "           mov     bx, [_z80hl]\n");
	}
	else
	{
		SetOverflow();
		fprintf(fp, "           and     ah, 0edh        ; Knock out negative & half carry flags\n");
		fprintf(fp, "           mov     [_z80hl], bx\n");
		fprintf(fp, "           xor     bx, [_orgval]\n");
		fprintf(fp, "           xor     bx, [_orgval2]\n");
		fprintf(fp, "           and     bh, 10h ; Half carry?\n");
		fprintf(fp, "           or      ah, bh  ; OR It in if so\n");
		fprintf(fp, "           mov     bx, [_z80hl]\n");
	}

	fprintf(fp, "           xor     edx, edx        ; Make sure we don't hose things\n");
	FetchNextInstruction(dwOpcode);
}

void RetIRetNHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);


	if (bThroughCallHandler)
	{
		fprintf(fp, "           call    PopWord\n");
		fprintf(fp, "           xor     esi, esi\n");
		fprintf(fp, "           mov     si, dx\n");
		fprintf(fp, "           add     esi, ebp\n");
	}
	else
	{
		fprintf(fp, "           mov     dx, word [_z80sp]       ; Get our current stack pointer\n");
		fprintf(fp, "           mov     si, [edx+ebp]   ; Get our return address\n");
		fprintf(fp, "           and     esi, 0ffffh             ; Only within 64K!\n");
		fprintf(fp, "           add     esi, ebp                        ; Add in our base address\n");
		fprintf(fp, "           add     word [_z80sp], 02h      ; Remove our two bytes from the stack\n");
	}

//	if (dwOpcode == 0x45) // RETN
	  { // This is where IFF1 becomes IFF2
	    fprintf(fp, "               xor     edx, edx\n");
	    fprintf(fp, "               mov     dl, [_z80iff]   ; Get interrupt flags\n");
	    fprintf(fp, "               shr     dl, 1           ; Move IFF2->IFF1\n");
	    fprintf(fp, "               or     dword [_z80iff], edx\n");
	  } // IFF2 is maintained (to allow nested nmis).

	  // From the z80 undocumented : reti = retn in all the cases
	  // the only case where reti is different is where there is a special
	  // external pio to handle interrupts, in this case it detects reti
	  // and sends the next interrupt in queue when it's executed.

	fprintf(fp, "           xor     edx, edx        ; Make sure we don't hose things\n");
	FetchNextInstruction(dwOpcode);
}

void ExtendedOutHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           mov     dl, cl  ; Address in DX... (C)\n");
	fprintf(fp, "           cmp     [Z80Has16bitsPorts],byte 0\n");
	fprintf(fp, "           je      ignorech%ld\n",dwGlobalLabel);
	fprintf(fp, "           mov     dx, cx  ; Address in DX... (BC)\n");
	fprintf(fp, "ignorech%ld:\n",dwGlobalLabel++);

	WriteValueToIo("dx", pbMathReg[(dwOpcode >> 3) & 0x07]);

	fprintf(fp, "           xor     edx, edx\n");
	FetchNextInstruction(dwOpcode);
}

void ExtendedInHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           mov     dl, cl  ; Address in DX... (C)\n");
	fprintf(fp, "           cmp     [Z80Has16bitsPorts],byte 0\n");
	fprintf(fp, "           je      ignorech%ld\n",dwGlobalLabel);
	fprintf(fp, "           mov     dx, cx  ; Address in DX... (BC)\n");
	fprintf(fp, "ignorech%ld:\n",dwGlobalLabel++);

	ReadValueFromIo("dx", pbMathReg[(dwOpcode >> 3) & 0x07]);

	fprintf(fp, ";\n; Remember, this variant of the IN instruction modifies the flags\n;\n\n");
	fprintf(fp, "           sahf    ; Restore our flags\n");
	fprintf(fp, "           mov     dh, ah  ; Save flags for later\n");

	if (0x50 == dwOpcode || 0x58 == dwOpcode)
	{
		fprintf(fp, "           mov     dl, %s\n", pbMathReg[(dwOpcode >> 3) & 0x07]);
		fprintf(fp, "           or      dl, dl\n");
	}
	else
		fprintf(fp, "           or      %s, %s;\n", pbMathReg[(dwOpcode >> 3) & 0x07], pbMathReg[(dwOpcode >> 3) & 0x07]);

	fprintf(fp, "           lahf\n");
	fprintf(fp, "           and     dh, 029h        ; Only keep carry and two unused flags\n");
	fprintf(fp, "           and     ah, 0d4h\n");
	fprintf(fp, "           or      ah, dh\n");

	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void NegHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           sahf\n");
	fprintf(fp, "           sub     dh, al\n");
	fprintf(fp, "           lahf\n");
	fprintf(fp, "           mov     al, dh\n");

	SetOverflow();
	fprintf(fp, "           or      ah, 02h\n");
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void ExtendedRegIntoMemory(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataW("dx");

	if (dwOpcode == 0x43)
		WriteValueToMemory("dx", "cl");
	if (dwOpcode == 0x53)
		WriteValueToMemory("dx", "byte [_z80de]");
	if (dwOpcode == 0x63)
		WriteValueToMemory("dx", "bl");
	if (dwOpcode == 0x73)
		WriteValueToMemory("dx", "byte [_z80sp]");

	fprintf(fp, "           inc     dx\n");

	if (dwOpcode == 0x43)
		WriteValueToMemory("dx", "ch");
	if (dwOpcode == 0x53)
		WriteValueToMemory("dx", "byte [_z80de + 1]");
	if (dwOpcode == 0x63)
		WriteValueToMemory("dx", "bh");
	if (dwOpcode == 0x73)
		WriteValueToMemory("dx", "byte [_z80sp + 1]");


	fprintf(fp, "           xor     edx, edx        ; Zero our upper word\n");
	FetchNextInstruction(dwOpcode);
}

void LdRegpair(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataW("dx");

	if (dwOpcode == 0x4b)
		ReadValueFromMemory("dx", "cl");
	if (dwOpcode == 0x5b)
		ReadValueFromMemory("dx", "byte [_z80de]");
	if (dwOpcode == 0x7b)
		ReadValueFromMemory("dx", "byte [_z80sp]");

	fprintf(fp, "           inc     dx\n");

	if (dwOpcode == 0x4b)
		ReadValueFromMemory("dx", "ch");
	if (dwOpcode == 0x5b)
		ReadValueFromMemory("dx", "byte [_z80de + 1]");
	if (dwOpcode == 0x7b)
		ReadValueFromMemory("dx", "byte [_z80sp + 1]");

	fprintf(fp, "           xor     edx, edx        ; Zero our upper word\n");

	FetchNextInstruction(dwOpcode);
}

void LDILDRLDIRLDDRHandler(UINT32 dwOpcode)
{
	UINT32 dwOrgGlobal = 0;

	ProcBegin(dwOpcode);

	// The ldir block reexecutes the same instruction increasing R
	// everytime. Since it's a prefix instruction it gets twice the number
	// of loops
	fprintf(fp,"dec cx\n");
	fprintf(fp,"add [_z80rCounter],cl\n");
	fprintf(fp,"add [_z80rCounter],cl\n");
	fprintf(fp,"inc cx\n");

	if (dwOpcode == 0xb0 || dwOpcode == 0xb8)
	{
		dwOrgGlobal = dwGlobalLabel;
		fprintf(fp, "ldRepeat%ld:\n", dwGlobalLabel);
	}

	ReadValueFromMemory("bx", "dl");

	// Here we write the byte back to the target

	WriteValueToMemory("[_z80de]", "dl");

	// Now we decide what to do

	if ((dwOpcode & 0x0f) == 0)
	{
		fprintf(fp, "           inc     bx      ; Increment HL\n");
		fprintf(fp, "           inc     word [_z80de]   ; Increment DE\n");
	}
	else
	{
		fprintf(fp, "           dec     bx      ; Decrement HL\n");
		fprintf(fp, "           dec     word [_z80de]   ; Decrement DE\n");
	}

	fprintf(fp, "           dec     cx      ; Decrement BC\n");

	if (dwOpcode == 0xb0 || dwOpcode == 0xb8)
	{
	  if (FALSE == bNoTiming)
	    {
	      fprintf(fp, "             jz      noMore%ld\n", dwGlobalLabel);
	      fprintf(fp, "             sub     edi, dword 16   ; 16 T-States per iteration\n");
	      fprintf(fp, "             js      noMore%ld\n", dwGlobalLabel);
	    }
	  else
	    {
	      fprintf(fp, "             jz      noMore%ld\n", dwGlobalLabel);
	    }

	  fprintf(fp, "         jmp     ldRepeat%ld ; Loop until we're done!\n", dwOrgGlobal);
	  fprintf(fp, "noMore%ld:\n", dwGlobalLabel);
	}

	fprintf(fp, "           and     ah, 0e9h ; Knock out H & N and P/V\n");
	fprintf(fp, "           or              cx, cx  ; Flag BC\n");
	fprintf(fp, "           jz      atZero%ld ; We're done!\n", dwGlobalLabel);

	if (dwOpcode == 0xb0 || dwOpcode == 0xb8)
	  {
	    // It's a repeat, so let's readjust ESI, shall we?

	    fprintf(fp, "               or      ah, 04h ; Non-zero - we're still going!\n");
	    fprintf(fp, "               sub     esi, 2  ; Adjust back to the beginning of the instruction\n");
	    fprintf(fp, "               jmp     noMoreExec\n\n");
	  }
	else
	  if (dwOpcode == 0xa0 || dwOpcode == 0xa8)
	    {
	      fprintf(fp, "             or      ah, 04h ; Non-zero - we're still going!\n");
	    }

	fprintf(fp, "atZero%ld:\n", dwGlobalLabel);
	++dwGlobalLabel;

	fprintf(fp, "           xor     edx, edx        ; Make sure we don't hose things\n");
	FetchNextInstruction(dwOpcode);
}

void IMHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode == 0x46)
		fprintf(fp, "           mov     dword [_z80interruptMode], 0 ; IM 0\n");

	if (dwOpcode == 0x56)
	{
		fprintf(fp, "           mov     dword [_z80interruptMode], 1 ; Interrupt mode 1\n");
		fprintf(fp, "           mov     word [_z80intAddr], 038h        ; Interrupt mode 1 cmd!\n");
	}

	if (dwOpcode == 0x5e)
		fprintf(fp, "           mov     dword [_z80interruptMode], 2 ; IM 2\n");

	FetchNextInstruction(dwOpcode);
}

#define CLEAR_DH() fprintf(fp, "                xor     edx, edx\n")

void IRHandler(UINT32 dwOpcode)
{
   char *src, *dst;

   dst = "";
   src = "";

   switch(dwOpcode) {
   case 0x57:
		dst = "al"; src="[_z80i]"; break;
   case 0x5F:
		dst = "al"; src="[_z80r]"; break;
   case 0x47:
		dst = "[_z80i]"; src="al"; break;
   case 0x4F:
		dst = "[_z80r]"; src="al"; break;
   }

   ProcBegin(dwOpcode);

   fprintf(fp, "           mov     %s, %s\n",dst,src);

   if (dwOpcode == 0x5f || dwOpcode == 0x57)
     // From the Z80 Manual : ld a,i or ld a,r copy iff2 to
     // the parity flag !
     {
       fprintf(fp, "            and     ah, 029h        ; No N, H, Z, or S!\n");
       fprintf(fp, "            or      al,al   ; Get appropriate flags\n");
       fprintf(fp, "            o16 pushf\n");
       fprintf(fp, "            pop     dx\n");
       fprintf(fp, "            and     dl, 0c0h\n");
       fprintf(fp, "            or      ah, dl  ; OR In our S & Z flags\n");

       fprintf(fp, "            mov     dl, [_z80iff]\n");
       fprintf(fp, "            and     dl, IFF2\n");
       fprintf(fp, "            shl     dl, 1\n");
       fprintf(fp, "            or      ah, dl\n");
     }

   // R is not random anymore. We try a precise emulation this time...

   if (dwOpcode == 0x5f) {

     fprintf(fp, "              mov     dl, [_z80rCounter]\n");
     fprintf(fp, "              and     edx, 07fh\n");
     fprintf(fp, "              and     byte [_z80r], 80h\n");
     fprintf(fp, "              or      byte [_z80r], dl\n");
   }
   if (dwOpcode == 0x5f || dwOpcode == 0x57)
     fprintf(fp, "              xor     edx, edx\n");

   FetchNextInstruction(dwOpcode);
}

// DD/FD Area

void DDFDCBHandler(UINT32 dwOpcode)
{
	fprintf(fp, "%sInst%.2x:\n", majorOp, (UINT8) dwOpcode);
	fprintf(fp, "           mov     [_baseFixup], dword 3\n");

	FetchDataW("dx");

	fprintf(fp, "           mov     byte [_orgval], dl ; Store our value\n");
	fprintf(fp, "           or      dl, dl\n");
	fprintf(fp, "           js      notNeg%ld\n", dwGlobalLabel);
	fprintf(fp, "           mov     byte [_orgval + 1], 00h;\n");

	fprintf(fp, "           jmp     jumpHandler%ld\n", dwGlobalLabel);
	fprintf(fp, "notNeg%ld:\n", dwGlobalLabel);
	fprintf(fp, "           mov     byte [_orgval + 1], 0ffh;       It's negative\n");
	fprintf(fp, "jumpHandler%ld:\n", dwGlobalLabel++);
	fprintf(fp, "           shl     ebx, 16 ; Save BX away\n");
	fprintf(fp, "           mov     bx, [_z80%s]\n", mz80Index);
	fprintf(fp, "           add     [_orgval], bx\n");
	fprintf(fp, "           shr     ebx, 16 ; Restore BX\n");
	fprintf(fp, "           mov     dl, dh  ; Get our instruction\n");
	fprintf(fp, "           xor     dh, dh  ; Zero this\n");
	fprintf(fp, "           jmp     dword [z80ddfdcbInstructions+edx*4]\n\n");
}

void LoadIndexReg(UINT32 dwOpcode)
{
	char string[150];

	ProcBegin(dwOpcode);

	sprintf(string, "[_z80%s]", mz80Index);

	FetchDataW("dx");

#ifdef WORD_ACCESS
	ReadWordFromMemory("dx", string);
#else
	fprintf(fp, "           mov     [_orgval], dx\n");

	ReadValueFromMemory("dx", "dl");
	fprintf(fp, "           mov     [_z80%s], dl\n", mz80Index);
	fprintf(fp, "           inc     word [_orgval]\n");
	fprintf(fp, "           mov     dx, [_orgval]\n");
	ReadValueFromMemory("dx", "dl");
	fprintf(fp, "           mov     [_z80%s + 1], dl\n", mz80Index);
#endif
	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

void StoreIndexReg(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataW("dx");
	fprintf(fp, "           mov     [_orgval], dx\n");

	fprintf(fp, "           mov     dl, [_z80%s]\n", mz80Index);
	WriteValueToMemory("[_orgval]", "dl");

	fprintf(fp, "           inc     word [_orgval]\n");

	fprintf(fp, "           mov     dl, [_z80%s + 1]\n", mz80Index);
	WriteValueToMemory("[_orgval]", "dl");
	CLEAR_DH();

	FetchNextInstruction(dwOpcode);
}

void LdIndexPtrReg(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	IndexedOffset(mz80Index);

	// DX Contains the address

	WriteValueToMemory("dx", pbMathReg[dwOpcode & 0x07]);
	CLEAR_DH();

	FetchNextInstruction(dwOpcode);
}

void UndocMathIndex(UINT32 dwOpcode)
{
	UINT32 dwOpcode1 = 0;

	ProcBegin(dwOpcode);

	if (dwOpcode & 1)
		fprintf(fp, "           mov     dl, byte [_z80%s]\n", mz80Index);
	else
		fprintf(fp, "           mov     dl, byte [_z80%s + 1]\n", mz80Index);

	// Info is in DL - let's do the math operation

	fprintf(fp, "           sahf            ; Store our flags in x86 flag reg\n");

	dwOpcode1 = (dwOpcode & 0xf8);	// Only the operation

	if (dwOpcode1 == 0x80)
		fprintf(fp, "           add     al, dl\n");
	else
	if (dwOpcode1 == 0x88)
		fprintf(fp, "           adc     al, dl\n");
	else
	if (dwOpcode1 == 0x90)
		fprintf(fp, "           sub     al, dl\n");
	else
	if (dwOpcode1 == 0x98)
		fprintf(fp, "           sbb     al, dl\n");
	else
	if (dwOpcode1 == 0xa0)
		fprintf(fp, "           and     al, dl\n");
	else
	if (dwOpcode1 == 0xa8)
		fprintf(fp, "           xor     al, dl\n");
	else
	if (dwOpcode1 == 0xb0)
		fprintf(fp, "           or      al, dl\n");
	else
	if (dwOpcode1 == 0xb8)
		fprintf(fp, "           cmp     al, dl\n");
	else
		assert(0);

	fprintf(fp, "           lahf            ; Get flags back into AH\n");

	if (dwOpcode1 != 0xa8 && dwOpcode1 != 0xa0 && dwOpcode1 != 0xb0)
	{
		SetOverflow();
	}

	if (dwOpcode1 == 0xa8)
		fprintf(fp, "           and     ah, 0ech        ; Only these flags matter!\n");

	if (dwOpcode1 == 0xa0)
	{
		fprintf(fp, "           and     ah, 0ech        ; Only these flags matter!\n");
		fprintf(fp, "           or      ah, 010h        ; Half carry gets set\n");
	}

	if (dwOpcode1 == 0xb0)
		fprintf(fp, "           and     ah, 0ech ; No H, N, or C\n");

	if (dwOpcode1 == 0xb8)
		fprintf(fp, "           or      ah, 02h ; Negative gets set on a compare\n");

	if (dwOpcode1 == 0x80 || dwOpcode1 == 0x88)
		fprintf(fp, "           and     ah, 0fdh ; No N!\n");

	if (dwOpcode1 == 0x90 || dwOpcode1 == 0x98)
		fprintf(fp, "           or      ah, 02h ; N Gets set!\n");

	if (dwOpcode1 == 0xb0)
		fprintf(fp, "           and     ah, 0ech ; No H, N, or C\n");

	FetchNextInstruction(dwOpcode);
}

void UndocLoadHalfIndexReg(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataB("dl");

	if (dwOpcode == 0x26)
		fprintf(fp, "           mov     byte [_z80%s + 1], dl\n", mz80Index);
	if (dwOpcode == 0x2e)
		fprintf(fp, "           mov     byte [_z80%s], dl\n", mz80Index);

	FetchNextInstruction(dwOpcode);
}

void UndocIncDecIndexReg(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           sahf\n");

	if (dwOpcode == 0x24)
		fprintf(fp, "           inc     byte [_z80%s + 1]\n", mz80Index);
	if (dwOpcode == 0x25)
		fprintf(fp, "           dec     byte [_z80%s + 1]\n", mz80Index);

	if (dwOpcode == 0x2c)
		fprintf(fp, "           inc     byte [_z80%s]\n", mz80Index);
	if (dwOpcode == 0x2d)
		fprintf(fp, "           dec     byte [_z80%s]\n", mz80Index);

	fprintf(fp,	"               lahf\n");
	SetOverflow();
	CLEAR_DH();

	if ((0x24 == dwOpcode) || (0x2c == dwOpcode))
		fprintf(fp, "           and     ah, 0fdh        ; Knock out N!\n");
	else
		fprintf(fp, "           or      ah, 02h ; Set negative!\n");

	FetchNextInstruction(dwOpcode);
}

void ExIndexed(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if( bThroughCallHandler )
	{
		fprintf(fp, "           mov dx, word [_z80%s]\n", mz80Index);
		fprintf(fp, "           push dx\n");
		fprintf(fp, "           call PopWord\n");
		fprintf(fp, "           mov     [_z80%s], dx\n", mz80Index);
		fprintf(fp, "           pop dx\n");
		fprintf(fp, "           mov [_wordval], dx\n" );
		fprintf(fp, "           call PushWord\n" );
	}
	else
	{
		fprintf(fp, "           mov     dx, word [_z80sp]\n");
		fprintf(fp, "           xor     edi, edi\n");
		fprintf(fp, "           mov     di, [_z80%s]\n", mz80Index);
		fprintf(fp, "           xchg    di, [ebp+edx]\n");
		fprintf(fp, "           mov     [_z80%s], di\n", mz80Index);
		fprintf(fp, "           xor     edx, edx\n");
		fprintf(fp, "           mov     edi, [cyclesRemaining]\n");
	}

	FetchNextInstruction(dwOpcode);
}

void IncDecIndexReg(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if (dwOpcode == 0x23)
		fprintf(fp, "           inc     word [_z80%s]   ; Increment our mz80Index register\n", mz80Index);
	else
		fprintf(fp, "           dec     word [_z80%s]   ; Increment our mz80Index register\n", mz80Index);

	FetchNextInstruction(dwOpcode);
}

void LdRegIndexOffset(UINT32 dwOpcode)
{
	UINT32 dwOpcode1 = 0;

	ProcBegin(dwOpcode);

	IndexedOffset(mz80Index);

	dwOpcode1 = (dwOpcode & 0x38) >> 3;

	ReadValueFromMemory("dx", pbMathReg[dwOpcode1]);

	fprintf(fp, "           xor     edx, edx        ; Make sure we don't hose things\n");
	dwGlobalLabel++;
	FetchNextInstruction(dwOpcode);
}

void LdByteToIndex(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataW("dx");
	fprintf(fp, "           mov     [cyclesRemaining], edi\n");
	fprintf(fp, "           mov     di, dx  ; Store it here for later\n");
	fprintf(fp, "           xor     dh, dh\n");
	fprintf(fp, "           or      dl, dl\n");
	fprintf(fp, "           jns     noNegate%ld\n", dwGlobalLabel);
	fprintf(fp, "           dec     dh\n");
	fprintf(fp, "noNegate%ld:\n", dwGlobalLabel);
	fprintf(fp, "           add     dx, [_z80%s]    ; Add in our index\n", mz80Index);
	fprintf(fp, "           mov     [_orgval], dx   ; Store our address to write to\n");
	fprintf(fp, "           mov     dx, di\n");
	fprintf(fp, "           xchg    dh, dl\n");
	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");

	WriteValueToMemory("[_orgval]", "dl");

	CLEAR_DH();
	++dwGlobalLabel;
	FetchNextInstruction(dwOpcode);
}


void SPToIndex(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           mov     dx, [_z80%s] ; Get our source register\n", mz80Index);
	fprintf(fp, "           mov     word [_z80sp], dx       ; Store our new SP\n");
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void AddIndexHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           mov     dh, ah  ; Get our flags\n");
	fprintf(fp, "           and     dh, 0ech        ; Preserve the top three and bits 2 & 3\n");

	fprintf(fp, "           mov     [cyclesRemaining], edi\n");
	fprintf(fp, "           mov     di, [_z80%s]    ; Get our value\n", mz80Index);
	fprintf(fp, "           mov     [_orgval], di   ; Store our original value\n");
	fprintf(fp, "           add     di, %s\n", pbIndexedRegPairs[(dwOpcode & 0x30) >> 4]);
	fprintf(fp, "           lahf\n");
	fprintf(fp, "           mov     [_z80%s], di    ; Store our register back\n", mz80Index);

	fprintf(fp, "           mov     di, [_orgval]   ; Get original\n");
	fprintf(fp, "           xor     di, word [_z80%s] ; XOR It with our computed value\n", mz80Index);
	fprintf(fp, "           xor     di, %s\n", pbIndexedRegPairs[(dwOpcode & 0x30) >> 4]);
	fprintf(fp, "           and     di, 1000h       ; Just our half carry\n");
	fprintf(fp, "           or      dx, di  ; Or in our flags\n");
	fprintf(fp, "           and     ah, 01h ; Just carry\n");
	fprintf(fp, "           or      ah, dh\n");
	fprintf(fp, "           mov     edi, [cyclesRemaining]\n");
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void JPIXIYHandler(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	fprintf(fp, "           mov     dx, [_z80%s]    ; Get our value\n", mz80Index);
	fprintf(fp, "           mov     esi, edx                ; New PC!\n");
	fprintf(fp, "           add     esi, ebp                ; Add in our base\n");
	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

void IncDecIndexed(UINT32 dwOpcode)
{
	//UINT8 szIndex[30];

	ProcBegin(dwOpcode);

	IndexedOffset(mz80Index);

	fprintf(fp, "           mov     [_orgval], dx\n");

	ReadValueFromMemory("dx", "dl");

	fprintf(fp, "           sahf\n");

	if (dwOpcode == 0x34)
		fprintf(fp, "           inc     dl\n");
	else
		fprintf(fp, "           dec     dl\n");
	fprintf(fp, "           lahf\n");

	fprintf(fp, "           o16     pushf\n");
	fprintf(fp, "           shl     edx, 16\n");
	fprintf(fp, "           and     ah, 0fbh        ;       Knock out parity/overflow\n");
	fprintf(fp, "           pop     dx\n");
	fprintf(fp, "           and     dh, 08h ; Just the overflow\n");
	fprintf(fp, "           shr     dh, 1   ; Shift it into position\n");
	fprintf(fp, "           or      ah, dh  ; OR It in with the real flags\n");
	fprintf(fp, "           shr     edx, 16\n");

	if (dwOpcode == 0x34)
		fprintf(fp, "           and     ah, 0fdh        ; Knock out N!\n");
	else
		fprintf(fp, "           or              ah, 02h ; Make it N!\n");

	WriteValueToMemory("[_orgval]", "dl");

	CLEAR_DH();

	FetchNextInstruction(dwOpcode);
}

void MathOperationIndexed(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	IndexedOffset(mz80Index);
	ReadValueFromMemory("dx", "dl");

	fprintf(fp, "           sahf\n");

	if (dwOpcode == 0x86)		// Add
		fprintf(fp, "           add     al, dl\n");
	if (dwOpcode == 0x8e)		// Adc
		fprintf(fp, "           adc     al, dl\n");
	if (dwOpcode == 0x96)		// Sub
		fprintf(fp, "           sub     al, dl\n");
	if (dwOpcode == 0x9e)		// Sbc
		fprintf(fp, "           sbb     al, dl\n");
	if (dwOpcode == 0xa6)		// And
		fprintf(fp, "           and     al, dl\n");
	if (dwOpcode == 0xae)		// Xor
		fprintf(fp, "           xor     al, dl\n");
	if (dwOpcode == 0xb6)		//	Or
		fprintf(fp, "           or      al, dl\n");
	if (dwOpcode == 0xbe)		// Cp
		fprintf(fp, "           cmp     al, dl\n");

	fprintf(fp, "           lahf\n");

	if (dwOpcode == 0x86 || dwOpcode == 0x8e)
	{
		SetOverflow();
		fprintf(fp, "           and     ah, 0fdh        ; Knock out negative\n");
	}

	if (dwOpcode == 0x96 || dwOpcode == 0x9e || dwOpcode == 0xbe)
	{
		SetOverflow();
		fprintf(fp, "           or      ah, 02h ; Set negative\n");
	}

	if (dwOpcode == 0xae || dwOpcode == 0xb6)
		fprintf(fp, "           and     ah, 0ech        ; Knock out H, N, and C\n");

	if (dwOpcode == 0xa6)
	{
		fprintf(fp, "           and     ah,0fch ; Knock out N & C\n");
		fprintf(fp, "           or      ah, 10h ; Set half carry\n");
	}

	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

void UndocIndexToReg(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if ((dwOpcode & 0x07) == 2 || (dwOpcode & 0x07) == 3)
		fprintf(fp, "   mov     dx, [_z80de]    ; Get DE\n");

	if ((dwOpcode & 0x07) == 4)
		fprintf(fp, "   mov     dh, byte [_z80%s + 1]\n", mz80Index);
	if ((dwOpcode & 0x07) == 5)
		fprintf(fp, "   mov     dl, byte [_z80%s]\n", mz80Index);

	fprintf(fp, "           mov   byte [_z80%s + %ld], %s\n", mz80Index, 1 - ((dwOpcode & 0x08) >> 3), pbLocalReg[dwOpcode & 0x07]);
	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

void UndocRegToIndex(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	if ((dwOpcode & 0x38) == 0x10 || (dwOpcode & 0x38) == 0x18)
		fprintf(fp, "           mov     dx, [_z80de]    ; Get a usable copy of DE here\n");

	fprintf(fp, "           mov     %s, byte [_z80%s + %ld]\n", pbLocalReg[(dwOpcode >> 3) & 0x07], mz80Index, 1 - (dwOpcode & 1));

	if ((dwOpcode & 0x38) == 0x10 || (dwOpcode & 0x38) == 0x18)
		fprintf(fp, "           mov     [_z80de], dx    ; Put it back!\n");

	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

void LoadImmediate(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	FetchDataW("dx");
	fprintf(fp, "           mov     [_z80%s], dx ; Store our new value\n", mz80Index);
	fprintf(fp, "           xor     edx, edx\n");

	FetchNextInstruction(dwOpcode);
}

void PushPopOperationsIndexed(UINT32 dwOpcode)
{
	//UINT8 bRegPair;
	char bRegBaseLsb[25];
	char bRegBaseMsb[25];
	char string[150];

	sprintf(bRegBaseLsb, "byte [_z80%s]", mz80Index);
	sprintf(bRegBaseMsb, "byte [_z80%s + 1]", mz80Index);

	sprintf(string, "[_z80%s]", mz80Index);

	ProcBegin(dwOpcode);

	if (dwOpcode == 0xe5)	// Push IX/IY
	{
		fprintf(fp, "           sub     word [_z80sp], 2\n");
		fprintf(fp, "           mov     dx, [_z80sp]\n");

#ifdef WORD_ACCESS
		WriteWordToMemory("dx", string);
#else
		WriteValueToMemory("dx", bRegBaseLsb);
		fprintf(fp, "           inc     dx\n");
		WriteValueToMemory("dx", bRegBaseMsb);
#endif
	}
	else	// Pop
	{
		fprintf(fp, "           mov     dx, [_z80sp]\n");
#ifdef WORD_ACCESS
		ReadWordFromMemory("dx", string);
#else
		ReadValueFromMemory("dx", bRegBaseLsb);
		fprintf(fp, "           inc     dx\n");
		ReadValueFromMemory("dx", bRegBaseMsb);
#endif
		fprintf(fp, "           add     word [_z80sp], 2\n");
	}

	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

// DDFD XXCB Instructions

void ddcbBitWise(UINT32 dwOpcode)
{
	ProcBegin(dwOpcode);

	// NOTE: _orgval contains the address to get from. It includes the offset
	// already computed plus the mz80Index register.

	// Read our byte

	fprintf(fp, "           mov     dx, [_orgval]   ; Get our target address\n");
	ReadValueFromMemory("dx", "dl");

	// Do the operation

	if (dwOpcode != 0x06 && dwOpcode != 0x0e &&
		 dwOpcode != 0x16 && dwOpcode != 0x1e &&
		 dwOpcode != 0x26 && dwOpcode != 0x2e &&
		 dwOpcode != 0x3e && (dwOpcode & 0xc7) != 0x86 &&
		 (dwOpcode & 0xc7) != 0xc6)
	{
		fprintf(fp, "           mov     dh, ah  ; Store our original flags\n");
		fprintf(fp, "           and     dh, 29h ; Keep our old flags\n");
	}

	if ((dwOpcode & 0xc7) != 0x86 && (dwOpcode & 0xc7) != 0xc6)
		fprintf(fp, "           sahf            ; Restore our flags\n");

	if (dwOpcode == 0x06)
		fprintf(fp, "           rol     dl, 1\n");
	if (dwOpcode == 0x0e)
		fprintf(fp, "           ror     dl, 1\n");
	if (dwOpcode == 0x16)
		fprintf(fp, "           rcl     dl, 1\n");
	if (dwOpcode == 0x1e)
		fprintf(fp, "           rcr     dl, 1\n");
	if (dwOpcode == 0x26)
		fprintf(fp, "           shl     dl, 1\n");
	if (dwOpcode == 0x2e)
		fprintf(fp, "           sar     dl, 1\n");
	if (dwOpcode == 0x3e)
		fprintf(fp, "           shr     dl, 1\n");

	// BIT, AND, and OR

	if ((dwOpcode & 0xc7) == 0x46)
		fprintf(fp, "           test    dl, 0%.2xh      ; Is it set?\n", (1 << ((dwOpcode >> 3) & 0x07)));
	else
	if ((dwOpcode & 0xc7) == 0x86)
		fprintf(fp, "           and     dl, 0%.2xh      ; Reset the bit\n",
					0xff - (1 << ((dwOpcode >> 3) & 0x07)));
	else
	if ((dwOpcode & 0xc7) == 0xc6)
		fprintf(fp, "           or      dl, 0%.2xh      ; Set the bit\n",
					(1 << ((dwOpcode >> 3) & 0x07)));

	if ((dwOpcode & 0xc7) != 0x86 && (dwOpcode & 0xc7) != 0xc6)
		fprintf(fp, "           lahf            ; Get our flags back\n");

	// Do the flag fixup (if any)

	if (dwOpcode == 0x26 || dwOpcode == 0x2e || ((dwOpcode & 0xc7) == 0x46))
		fprintf(fp, "           and     ah, 0edh        ; No Half carry or negative!\n");

	if (dwOpcode == 0x06 || dwOpcode == 0x0e ||
		 dwOpcode == 0x16 || dwOpcode == 0x1e ||
		 dwOpcode == 0x3e)
		fprintf(fp, "           and     ah, 0edh        ; Knock out H & N\n");

	// BIT!

	if ((dwOpcode & 0xc7) == 0x46)
	{
		fprintf(fp, "           or      ah, 10h ; OR In our half carry\n");
		fprintf(fp, "           and     ah, 0d0h ; New flags\n");
		fprintf(fp, "           or      ah, dh  ; OR In our old flags\n");
	}

	// Now write our data back if it's not a BIT instruction

	if ((dwOpcode & 0xc7) != 0x46)	// If it's not a BIT, write it back
		WriteValueToMemory("[_orgval]", "dl");

	CLEAR_DH();
	FetchNextInstruction(dwOpcode);
}

void GetTicksCode(void)
{
	fprintf(fp, "           global  _%sGetElapsedTicks\n", cpubasename);
	fprintf(fp, "           global  %sGetElapsedTicks_\n", cpubasename);
	fprintf(fp, "           global  %sGetElapsedTicks\n", cpubasename);

	Alignment();
	sprintf(procname, "%sGetElapsedTicks_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%sGetElapsedTicks:\n", cpubasename);
	fprintf(fp, "%sGetElapsedTicks:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "           mov     eax, [esp+4]    ; Get our context address\n");

	fprintf(fp, "           or      eax, eax        ; Should we clear it?\n");
	fprintf(fp, "           jz      getTicks\n");
	fprintf(fp, "           xor     eax, eax\n");
	fprintf(fp, "           xchg    eax, [dwElapsedTicks]\n");
	fprintf(fp, "           ret\n");
	fprintf(fp, "getTicks:\n");
	fprintf(fp, "           mov     eax, [dwElapsedTicks]\n");
	fprintf(fp, "           ret\n");
}

void ReleaseTimesliceCode(void)
{
	fprintf(fp, "           global  _%sReleaseTimeslice\n", cpubasename);
	fprintf(fp, "           global  %sReleaseTimeslice_\n", cpubasename);
	fprintf(fp, "           global  %sReleaseTimeslice\n", cpubasename);

	Alignment();
	sprintf(procname, "%sReleaseTimeslice_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%sReleaseTimeslice:\n", cpubasename);
	fprintf(fp, "%sReleaseTimeslice:\n", cpubasename);

	if (bSingleStep)
		fprintf(fp, "           mov     [cyclesRemaining], dword 0\n");
	else
	{
	  /* [Kayamon] - this modification allows speed hacks to work.
	   *		 It should technically be compatible with
	   *		 everything else as it doesn't violate any MZ80 rules (AFAIK).
	   */
	  fprintf(fp, "     mov   [bEIExit], byte 0\n");

	  // This will allow the timers to consider the frame to be executed
	  // after a speed hack...
	  // fprintf(fp, "              mov     eax, [cyclesRemaining]\n");
	  // fprintf(fp, "              sub     [dwOriginalExec], eax\n");
		fprintf(fp, "           mov     [cyclesRemaining], dword 1\n");
	}

	fprintf(fp, "           ret\n\n");
}

void DataSegment(void)
{
	UINT32 dwLoop = 0;
	UINT8 bUsed[256];

	fprintf(fp, "           section .data\n");
	Alignment();
	fprintf(fp,"            global z80_offdata\n");
	fprintf(fp,"            global _z80_offdata\n");
	fprintf(fp,"_z80_offdata:\n");
	fprintf(fp, "z80_offdata     dd  0\n");

	fprintf(fp, "           global  _%scontextBegin\n", cpubasename);
	fprintf(fp, "_%scontextBegin:\n", cpubasename);

	fprintf(fp, "           global  _z80pc\n");
	fprintf(fp, "           global  z80pc_\n");

	if (bPlain)
		fprintf(fp, "           global  z80pc\n");
	fprintf(fp, "           global _z80sp\n");
	fprintf(fp, "           global z80sp\n");

	if (bPlain)
	  fprintf(fp, "           global  z80Base\n");           // [J3d!]
	else
	  fprintf(fp, "           global  _z80Base\n");           // [J3d!]
	fprintf(fp, "           global  _z80nmiAddr\n");
	fprintf(fp, "           global  _z80intAddr\n");
	fprintf(fp, "           global  _z80ix\n");
	fprintf(fp, "           global  _z80de\n");
	fprintf(fp, "           global  _z80bc\n");
	fprintf(fp, "           global  _z80hl\n");
	fprintf(fp, "           global  __z80iff\n");
	fprintf(fp, "           global  _z80iff\n");
	fprintf(fp, "           global  _z80intPending\n");
	fprintf(fp, "           global  z80intPending\n");
	fprintf(fp, "           global cyclesRemaining\n");
	fprintf(fp, "           global _cyclesRemaining\n");
	fprintf(fp, "           global ExitOnEI\n");
	fprintf(fp, "           global _ExitOnEI\n");
	fprintf(fp, "           global Z80Has16bitsPorts\n");
	fprintf(fp, "           global _Z80Has16bitsPorts\n");
	fprintf(fp, "           global dwElapsedTicks\n");
	fprintf(fp, "           global _dwElapsedTicks\n");
	fprintf(fp, "\n");
	fprintf(fp, "; DO NOT CHANGE THE ORDER OF AF, BC, DE, HL and THE PRIME REGISTERS!\n");
	fprintf(fp, "\n");
	if (bPlain)
	  fprintf(fp, "z80Base:\n");
	fprintf(fp, "_z80Base   dd      0       ; Base address for Z80 stuff\n");
	fprintf(fp, "_z80MemRead        dd      0       ; Offset of memory read structure array\n");
	fprintf(fp, "_z80MemWrite       dd      0       ; Offset of memory write structure array\n");
	fprintf(fp, "_z80IoRead dd      0       ; Base address for I/O reads list\n");
	fprintf(fp, "_z80IoWrite        dd      0       ; Base address for I/O write list\n");
	fprintf(fp, "_dwElapsedTicks:\n");
	fprintf(fp, "dwElapsedTicks     dd      0       ; # Of ticks elapsed\n");
	fprintf(fp, "__z80iff:\n");
	fprintf(fp, "_z80iff    dd      0       ; Non-zero if we're in an interrupt\n");
	fprintf(fp, "_z80interruptMode dd       0       ; Interrupt mode\n");
	fprintf(fp, "z80intPending:\n");
	fprintf(fp, "_z80intPending     dd      0       ; Non-zero if an interrupt is pending (contains the number of the interrupt)\n");
	fprintf(fp, "_z80halted dd      0       ; 0=Not halted, 1=Halted\n");
#ifdef MZ80_TRAP
	fprintf(fp, "_z80trapList       dd      0       ; pointer to trap list\n");
	fprintf(fp, "_z80trapAddr       dw      0       ; PC where trap occurred\n");
#endif
	fprintf(fp, "_z80af             dw      0       ; A Flag & Flags\n");
	fprintf(fp, "_z80bc             dw      0       ; BC\n");
	fprintf(fp, "_z80de             dw      0       ; DE\n");
	fprintf(fp, "_z80hl             dw      0       ; HL\n");
	fprintf(fp, "_z80afprime        dw      0       ; A Flag & Flags prime\n");
	fprintf(fp, "_z80bcprime        dw      0       ; BC prime\n");
	fprintf(fp, "_z80deprime        dw      0       ; DE prime\n");
	fprintf(fp, "_z80hlprime        dw      0       ; HL prime\n");
	fprintf(fp, "\n");
	fprintf(fp, "; The order of the following registers can be changed without adverse\n");
	fprintf(fp, "; effect. Keep the INT16 and DWORDs on boundaries of two for faster access\n");
	fprintf(fp, "\n");
	fprintf(fp, "_z80ix             dw      0       ; IX\n");
	fprintf(fp, "_z80iy             dw      0       ; IY\n");
	fprintf(fp, "z80sp:\n");
	fprintf(fp, "_z80sp             dw      0       ; Stack pointer\n");

	if (bPlain)
		fprintf(fp,"z80pc:\n");

	fprintf(fp, "z80pc_:\n");
	fprintf(fp, "_z80pc             dw      0       ; PC\n");
	fprintf(fp, "_z80nmiAddr        dw      0       ; Address to jump to for NMI\n");
	fprintf(fp, "_z80intAddr        dw      0       ; Address to jump to for INT\n");
	fprintf(fp, "_z80i              db      0       ; I register\n");
	fprintf(fp, "_z80r              db      0       ; R register\n");
	fprintf(fp, "_z80rCounter       db      0       ; R Register counter\n");
	fprintf(fp, "\n");
	fprintf(fp, "_%scontextEnd:\n", cpubasename);
	Alignment();
	fprintf(fp, "_cyclesRemaining:\n");
	fprintf(fp, "cyclesRemaining    dd      0       ; # Of cycles remaining\n");
	fprintf(fp, "dwOriginalExec     dd      0       ; # Of cycles originally executing\n");
	fprintf(fp, "dwEITiming dd      0       ; Used when we cause an interrupt\n");

	fprintf(fp, "_orgval    dw      0       ; Scratch area\n");
	fprintf(fp, "_orgval2   dw      0       ; Scratch area\n");
	fprintf(fp, "_wordval   dw      0       ; Scratch area\n");
	fprintf(fp, "_intData   db      0       ; Interrupt data when an interrupt is pending\n");
	fprintf(fp, "bEIExit    db      0       ; Are we exiting because of an EI instruction?\n");
	fprintf(fp,"_ExitOnEI:\n");
	fprintf(fp,"ExitOnEI         db 0\n");
	fprintf(fp,"_Z80Has16bitsPorts:\n");
	fprintf(fp,"Z80Has16bitsPorts:         db 0\n");
	fprintf(fp, "_baseFixup dd      0       ; Our base fixup for when we're out of time\n");
	fprintf(fp, "_z80stoponintend   dd      0       ; int patch\n");
	fprintf(fp, "\n");

	// Debugger junk

	fprintf(fp, "RegTextIFF1        db      'IFF1',0\n");
	fprintf(fp, "RegTextIFF2        db      'IFF2',0\n\n");

	// Timing for interrupt modes

	fprintf(fp, "intModeTStates:\n");
	fprintf(fp, "           db      13      ; IM 0 - 13 T-States\n");
	fprintf(fp, "           db      11      ; IM 1 - 11 T-States\n");
	fprintf(fp, "           db      11      ; IM 2 - 11 T-States\n\n");

	// Now we write out our tables

	Alignment();

	for (dwLoop = 0; dwLoop < 256; dwLoop++)
		bUsed[dwLoop] = 0;

	// Now rip through and find out what is and isn't used

	dwLoop = 0;

	while (StandardOps[dwLoop].Emitter)
	{
		assert(StandardOps[dwLoop].bOpCode < 0x100);
		if (bUsed[StandardOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops! %.2x\n", (UINT8) dwLoop);
			fclose(fp);
			exit(1);
		}
		bUsed[StandardOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	// Now that that's taken care of, emit the table

	fprintf(fp, "z80regular:\n");

	dwLoop = 0;

	while (dwLoop < 0x100)
	{
		fprintf(fp, "           dd      ");
		if (bUsed[dwLoop])
			fprintf(fp, "RegInst%.2x", (UINT8) dwLoop);
		else
			fprintf(fp, "invalidInsByte");
		fprintf(fp, "\n");
		dwLoop++;
	}
	fprintf(fp, "\n");

	// Now rip through and find out what is and isn't used (CB Ops)

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	dwLoop = 0;

	while (CBOps[dwLoop].Emitter)
	{
		assert(CBOps[dwLoop].bOpCode < 0x100);
		if (bUsed[CBOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops CB! %.2x\n", (UINT8) dwLoop);
			fclose(fp);
			exit(1);
		}
		bUsed[CBOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	dwLoop = 0;

	// Let's emit the CB prefixes

	fprintf(fp, "z80PrefixCB:\n");

	while (dwLoop < 0x100)
	{
		fprintf(fp, "           dd      ");
		if (bUsed[dwLoop])
			fprintf(fp, "CBInst%.2x", (UINT8) dwLoop);
		else
			fprintf(fp, "invalidInsWord");
		fprintf(fp, "\n");
		dwLoop++;
	}
	fprintf(fp, "\n");

	// Now rip through and find out what is and isn't used (ED Ops)

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	dwLoop = 0;

	while (EDOps[dwLoop].Emitter)
	{
		assert(EDOps[dwLoop].bOpCode < 0x100);
		if (bUsed[EDOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops ED! %.2x\n", (UINT8) dwLoop);
			fclose(fp);
			exit(1);
		}
		bUsed[EDOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	dwLoop = 0;

	// Let's emit the ED prefixes

	fprintf(fp, "z80PrefixED:\n");

	while (dwLoop < 0x100)
	{
		fprintf(fp, "           dd      ");
		if (bUsed[dwLoop])
			fprintf(fp, "EDInst%.2x", (UINT8) dwLoop);
		else
			fprintf(fp, "invalidInsWord");
		fprintf(fp, "\n");
		dwLoop++;
	}
	fprintf(fp, "\n");

	// Now rip through and find out what is and isn't used (DD Ops)

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	dwLoop = 0;

	while (DDFDOps[dwLoop].Emitter)
	{
		assert(DDFDOps[dwLoop].bOpCode < 0x100);
		if (bUsed[DDFDOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops DD! %.2x\n", bUsed[DDFDOps[dwLoop].bOpCode]);
			fclose(fp);
			exit(1);
		}
		bUsed[DDFDOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	dwLoop = 0;

	// Let's emit the DD prefixes

	fprintf(fp, "z80PrefixDD:\n");

	while (dwLoop < 0x100)
	{
		fprintf(fp, "           dd      ");
		if (bUsed[dwLoop])
			fprintf(fp, "DDInst%.2x", (UINT8) dwLoop);
		else
			fprintf(fp, "invalidInsWord");
		fprintf(fp, "\n");
		dwLoop++;
	}
	fprintf(fp, "\n");

	// Now rip through and find out what is and isn't used (FD Ops)

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	dwLoop = 0;

	while (DDFDOps[dwLoop].Emitter)
	{
		assert(DDFDOps[dwLoop].bOpCode < 0x100);
		if (bUsed[DDFDOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops FD! %.2x\n", (UINT8) dwLoop);
			fclose(fp);
			exit(1);
		}
		bUsed[DDFDOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	// Let's emit the DDFD prefixes

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	dwLoop = 0;

	while (DDFDOps[dwLoop].Emitter)
	{
		assert(DDFDOps[dwLoop].bOpCode < 0x100);
		if (bUsed[DDFDOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops FD! %.2x\n", (UINT8) dwLoop);
			exit(1);
		}
		bUsed[DDFDOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	dwLoop = 0;

	// Let's emit the DDFD prefixes

	fprintf(fp, "z80PrefixFD:\n");

	while (dwLoop < 0x100)
	{
		fprintf(fp, "           dd      ");
		if (bUsed[dwLoop])
			fprintf(fp, "FDInst%.2x", (UINT8) dwLoop);
		else
			fprintf(fp, "invalidInsWord");
		fprintf(fp, "\n");
		dwLoop++;
	}

	for (dwLoop = 0; dwLoop < 0x100; dwLoop++)
		bUsed[dwLoop] = 0;

	dwLoop = 0;

	while (DDFDCBOps[dwLoop].Emitter)
	{
		assert(DDFDCBOps[dwLoop].bOpCode < 0x100);
		if (bUsed[DDFDCBOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops CBFDDD! %.2x\n", bUsed[DDFDCBOps[dwLoop].bOpCode]);
			fclose(fp);
			exit(1);
		}
		bUsed[DDFDCBOps[dwLoop].bOpCode] = 1;
		dwLoop++;
	}

	// Let's emit the DDFD prefixes

	dwLoop = 0;

	fprintf(fp, "z80ddfdcbInstructions:\n");

	while (dwLoop < 0x100)
	{
		fprintf(fp, "           dd      ");
		if (bUsed[dwLoop])
			fprintf(fp, "DDFDCBInst%.2x", (UINT8) dwLoop);
		else
			fprintf(fp, "invalidInsWord");
		fprintf(fp, "\n");
		dwLoop++;
	}
	fprintf(fp, "\n");
}

void CodeSegmentBegin(void)
{
	fprintf(fp, "           section .text\n");
}

void CodeSegmentEnd(void)
{
}

void ProgramEnd(void)
{
}

void EmitRegularInstructions(void)
{
	UINT32 dwLoop = 0;
	UINT32 dwLoop2 = 0;

	bCurrentMode = TIMING_REGULAR;

	while (dwLoop < 0x100)
	{
		dwLoop2 = 0;
		sprintf(procname, "RegInst%.2x", (UINT8) dwLoop);

		while (StandardOps[dwLoop2].bOpCode != dwLoop && StandardOps[dwLoop2].bOpCode != 0xffffffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (StandardOps[dwLoop2].Emitter
			&& StandardOps[dwLoop2].bOpCode != 0xffffffff)
			StandardOps[dwLoop2].Emitter((UINT32) dwLoop);

		dwLoop++;
	}
}

void EmitCBInstructions(void)
{
	UINT32 dwLoop = 0;
	UINT32 dwLoop2 = 0;

	bCurrentMode = TIMING_CB;

	while (dwLoop < 0x100)
	{
		sprintf(procname, "CBInst%.2x", (UINT8) dwLoop);
		dwLoop2 = 0;

		while (CBOps[dwLoop2].bOpCode != dwLoop && CBOps[dwLoop2].bOpCode != 0xffffffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (CBOps[dwLoop2].Emitter && CBOps[dwLoop2].bOpCode != 0xffffffff)
			CBOps[dwLoop2].Emitter((UINT32) dwLoop);

		dwLoop++;
	}
}

void EmitEDInstructions(void)
{
	UINT32 dwLoop = 0;
	UINT32 dwLoop2 = 0;

	bCurrentMode = TIMING_ED;

	while (dwLoop < 0x100)
	{
		sprintf(procname, "EDInst%.2x", (UINT8) dwLoop);
		dwLoop2 = 0;

		while (EDOps[dwLoop2].bOpCode != dwLoop && EDOps[dwLoop2].bOpCode != 0xffffffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (EDOps[dwLoop2].Emitter && EDOps[dwLoop2].bOpCode != 0xffffffff)
			EDOps[dwLoop2].Emitter((UINT32) dwLoop);

		dwLoop++;
	}
}

void EmitDDInstructions(void)
{
	UINT32 dwLoop = 0;
	UINT32 dwLoop2 = 0;

	bCurrentMode = TIMING_DDFD;

	while (dwLoop < 0x100)
	{
		sprintf(procname, "DDInst%.2x", (UINT8) dwLoop);
		dwLoop2 = 0;

		while (DDFDOps[dwLoop2].bOpCode != dwLoop && DDFDOps[dwLoop2].bOpCode != 0xffffffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (DDFDOps[dwLoop2].Emitter && DDFDOps[dwLoop2].bOpCode != 0xffffffff)
			DDFDOps[dwLoop2].Emitter((UINT32) dwLoop);

		dwLoop++;
	}

	bCurrentMode = TIMING_XXCB;

	dwLoop = 0;

	while (dwLoop < 0x100)
	{
		sprintf(procname, "DDFDCBInst%.2x", (UINT8) dwLoop);
		dwLoop2 = 0;

		while (DDFDCBOps[dwLoop2].bOpCode != dwLoop && DDFDCBOps[dwLoop2].bOpCode != 0xffffffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (DDFDCBOps[dwLoop2].Emitter && DDFDCBOps[dwLoop2].bOpCode != 0xffffffff)
			DDFDCBOps[dwLoop2].Emitter((UINT32) dwLoop);

		dwLoop++;
	}
}

void EmitFDInstructions(void)
{
	UINT32 dwLoop = 0;
	UINT32 dwLoop2 = 0;

	bCurrentMode = TIMING_DDFD;

	while (dwLoop < 0x100)
	{
		sprintf(procname, "FDInst%.2x", (UINT8) dwLoop);
		dwLoop2 = 0;

		while (DDFDOps[dwLoop2].bOpCode != dwLoop && DDFDOps[dwLoop2].bOpCode != 0xffffffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (DDFDOps[dwLoop2].Emitter && DDFDOps[dwLoop2].bOpCode != 0xffffffff)
			DDFDOps[dwLoop2].Emitter((UINT32) dwLoop);

		dwLoop++;
	}
}

/* These are the meta routines */

#ifdef DARWIN
static void align_stack(char *reg1, char *reg2) {
	fprintf(fp, "           push   ebp\n");
	fprintf(fp, "           mov    ebp,esp\n");
	fprintf(fp, "           sub    esp,32     ; stack aligned on 32\n");
	fprintf(fp, "           and    esp,0xffffffc0 \n");
	fprintf(fp, "           mov    [esp],%s \n",reg1);
	if (reg2)
	  fprintf(fp, "           mov    [esp+4],%s \n",reg2);
}

static void restore_stack(char *reg) {
	fprintf(fp, "           mov    %s,[esp] \n",reg);
	fprintf(fp, "           leave\n");
}
#endif

static void ReadMemoryByteHandler(void)
{
	Alignment();
	fprintf(fp, "; This is a generic read memory byte handler when a foreign\n");
	fprintf(fp, "; handler is to be called\n\n");
	fprintf(fp, "; EDI=Handler address, EDX=Address\n");
	fprintf(fp, "; On return, EDX & EDI are undisturbed and AL=Byte read\n\n");
	fprintf(fp, "ReadMemoryByte:\n");

	fprintf(fp, "           mov     [_z80af], ax    ; Save AF\n");
	fprintf(fp, "           mov     [_z80hl], bx    ; Save HL\n");
	fprintf(fp, "           mov     [_z80bc], cx    ; Save BC\n");

	fprintf(fp, "           sub     esi, ebp        ; Our program counter\n");
	fprintf(fp, "           mov     [_z80pc], si    ; Save our program counter\n");

	// Now adjust the proper timing

	fprintf(fp, "           mov     esi, [dwOriginalExec]   \n");
	fprintf(fp, "           sub     esi, [cyclesRemaining]\n");
	fprintf(fp, "           add     [dwElapsedTicks], esi\n");
	fprintf(fp, "           sub     [dwOriginalExec], esi\n");

	fprintf(fp, "           push    edi     ; Save our structure address\n");
#ifdef DARWIN
	align_stack("edx",NULL);
#else
	fprintf(fp, "           push    edx     ; And our desired address\n");
#endif

	if (FALSE == bUseStack)
	{
		fprintf(fp, "           mov     eax, edx        ; Get our desired address reg\n");
		fprintf(fp, "           mov     edx, edi        ; Pointer to the structure\n");
	}

	fprintf(fp, "           call    dword [edi + 8] ; Go call our handler\n");

#ifdef DARWIN
	restore_stack("edx");
#else
	fprintf(fp, "           pop     edx     ; Restore our address\n");
#endif
	fprintf(fp, "           pop     edi     ; Restore our handler's address\n");

	fprintf(fp, "           xor     ebx, ebx        ; Zero our future HL\n");
	fprintf(fp, "           xor     esi, esi        ; Zero it!\n");
	fprintf(fp, "           mov     ebp, [_z80Base] ; Base pointer comes back\n");
	fprintf(fp, "           mov     si, [_z80pc]    ; Get our program counter back\n");
	fprintf(fp, "           xor     ecx, ecx        ; Zero our future BC\n");
	fprintf(fp, "           add     esi, ebp        ; Rebase it properly\n");

	fprintf(fp, "           mov     bx, [_z80hl]    ; Get HL back\n");
	fprintf(fp, "           mov     cx, [_z80bc]    ; Get BC back\n");

// Note: the callee must restore AF!

	fprintf(fp, "           ret\n\n");
}

void WriteMemoryByteHandler(void)
{
	Alignment();
	fprintf(fp, "; This is a generic read memory byte handler when a foreign\n");
	fprintf(fp, "; handler is to be called.\n");
	fprintf(fp, "; EDI=Handler address, AL=Byte to write, EDX=Address\n");
	fprintf(fp, "; EDI and EDX Are undisturbed on exit\n\n");
	fprintf(fp, "WriteMemoryByte:\n");

	fprintf(fp, "           mov     [_z80hl], bx    ; Save HL\n");
	fprintf(fp, "           mov     [_z80bc], cx    ; Save BX\n");

	fprintf(fp, "           sub     esi, ebp        ; Our program counter\n");
	fprintf(fp, "           mov     [_z80pc], si    ; Save our program counter\n");

		// Now adjust the proper timing

		fprintf(fp, "           mov     esi, [dwOriginalExec]   \n");
		fprintf(fp, "           sub     esi, [cyclesRemaining]\n");
		fprintf(fp, "           add     [dwElapsedTicks], esi\n");
		fprintf(fp, "           sub     [dwOriginalExec], esi\n");

	fprintf(fp, "           push    edi     ; Save our structure address\n");
#ifdef DARWIN
	align_stack("edx","eax");
#else
	if (bUseStack)
		fprintf(fp, "           push    eax     ; Data to write\n");

	fprintf(fp, "           push    edx     ; And our desired address\n");
#endif

	if (FALSE == bUseStack)
	{
		fprintf(fp, "           xchg    eax, edx ; Swap address/data around\n");
		fprintf(fp, "           mov     ebx, edi        ; Our MemoryWriteByte structure address\n");
	}

	fprintf(fp, "           call    dword [edi + 8] ; Go call our handler\n");

#ifdef DARWIN
	restore_stack("edx");
#else
	fprintf(fp, "           pop     edx     ; Restore our address\n");

	if (bUseStack)
		fprintf(fp, "           pop     eax     ; Restore our data written\n");
#endif

	fprintf(fp, "           pop     edi     ; Save our structure address\n");

	fprintf(fp, "           xor     ebx, ebx        ; Zero our future HL\n");
	fprintf(fp, "           xor     ecx, ecx        ; Zero our future BC\n");
	fprintf(fp, "           mov     bx, [_z80hl]    ; Get HL back\n");
	fprintf(fp, "           mov     cx, [_z80bc]    ; Get BC back\n");
	fprintf(fp, "           mov     ax, [_z80af]    ; Get AF back\n");
	fprintf(fp, "           xor     esi, esi        ; Zero it!\n");
	fprintf(fp, "           mov     si, [_z80pc]    ; Get our program counter back\n");
	fprintf(fp, "           mov     ebp, [_z80Base] ; Base pointer comes back\n");
	fprintf(fp, "           add     esi, ebp        ; Rebase it properly\n");

	fprintf(fp, "           ret\n\n");
}

void PushWordHandler(void)
{
	Alignment();

	fprintf(fp, ";\n");
	fprintf(fp, "; DX=Top of SP, [_wordval]=word value to push\n");
	fprintf(fp, ";\n\n");
	fprintf(fp, "PushWord:\n");
	fprintf(fp, "           mov     dx, [_z80sp]\n");
	fprintf(fp, "           dec     dx\n");
	WriteValueToMemory("dx", "byte [_wordval+1]");
	fprintf(fp, "           dec     dx\n");
	WriteValueToMemory("dx", "byte [_wordval]");
	fprintf(fp, "           sub     [_z80sp], word 2\n");
	fprintf(fp, "           xor     edx, edx\n");
	fprintf(fp, "           ret\n\n");
}

void PopWordHandler(void)
{
	Alignment();

	fprintf(fp, ";\n");
	fprintf(fp, "; [_z80sp]=Top of SP, DX=Word value read\n");
	fprintf(fp, ";\n\n");
	fprintf(fp, "PopWord:\n");
	fprintf(fp, "           mov     dx, [_z80sp]\n");

#ifdef WORD_ACCESS
	ReadWordFromMemory("dx", "dx");
#else
	ReadValueFromMemory("dx", "byte [_wordval]");
	fprintf(fp, "           inc     dx\n");
	ReadValueFromMemory("dx", "byte [_wordval+1]");
	fprintf(fp, "           mov     dx, [_wordval]\n");
#endif
	fprintf(fp, "           add     [_z80sp], word 2\n");
	fprintf(fp, "           ret\n\n");
}

void ReadIoHandler(void)
{
	Alignment();

	fprintf(fp, "; This is a generic I/O read byte handler for when a foreign\n");
	fprintf(fp, "; handler is to be called\n");

	fprintf(fp, "; EDI=Handler address, EDX=I/O Address\n");
	fprintf(fp, "; On return, EDX & EDI are undisturbed and AL=Byte read\n\n");
	fprintf(fp, "ReadIOByte:\n");

	fprintf(fp, "           mov     [_z80af], ax    ; Save AF\n");
	fprintf(fp, "           mov     [_z80hl], bx    ; Save HL\n");
	fprintf(fp, "           mov     [_z80bc], cx    ; Save BC\n");

	fprintf(fp, "           sub     esi, ebp        ; Our program counter\n");
	fprintf(fp, "           mov     [_z80pc], si    ; Save our program counter\n");
		// Now adjust the proper timing

		fprintf(fp, "           mov     esi, [dwOriginalExec]   \n");
		fprintf(fp, "           sub     esi, [cyclesRemaining]\n");
		fprintf(fp, "           add     [dwElapsedTicks], esi\n");
		fprintf(fp, "           sub     [dwOriginalExec], esi\n");


	fprintf(fp, "           push    edi     ; Save our structure address\n");
#ifdef DARWIN
	align_stack("edx",NULL);
#else
	fprintf(fp, "           push    edx     ; And our desired I/O port\n");
#endif

	if (FALSE == bUseStack)
	{
	  fprintf(fp, "         mov     eax, edx        ; Get our desired address reg\n");
	  fprintf(fp, "         mov     edx, edi        ; Pointer to the structure\n");
	}

	fprintf(fp, "           call    dword [edi + 4] ; Go call our handler\n");

#ifdef DARWIN
	restore_stack("edx");
#else
	fprintf(fp, "           pop     edx     ; Restore our address\n");
#endif
	fprintf(fp, "           pop     edi     ; Restore our handler's address\n");

	fprintf(fp, "           xor     ebx, ebx        ; Zero our future HL\n");
	fprintf(fp, "           xor     ecx, ecx        ; Zero our future BC\n");
	fprintf(fp, "           xor     esi, esi        ; Zero it!\n");
	fprintf(fp, "           mov     si, [_z80pc]    ; Get our program counter back\n");
	fprintf(fp, "           mov     ebp, [_z80Base] ; Base pointer comes back\n");
	fprintf(fp, "           add     esi, ebp        ; Rebase it properly\n");

	fprintf(fp, "           mov     bx, [_z80hl]    ; Get HL back\n");
	fprintf(fp, "           mov     cx, [_z80bc]    ; Get BC back\n");

// Note: the callee must restore AF!

	fprintf(fp, "           ret\n\n");
}

void WriteIoHandler(void)
{
	Alignment();

	fprintf(fp, "; This is a generic write I/O byte handler when a foreign handler is to\n");
	fprintf(fp, "; be called\n");
	fprintf(fp, "; EDI=Handler address, AL=Byte to write, EDX=I/O Address\n");
	fprintf(fp, "; EDI and EDX Are undisturbed on exit\n\n");
	fprintf(fp, "WriteIOByte:\n");

	fprintf(fp, "           mov     [_z80hl], bx    ; Save HL\n");
	fprintf(fp, "           mov     [_z80bc], cx    ; Save BX\n");

	fprintf(fp, "           sub     esi, ebp        ; Our program counter\n");
	fprintf(fp, "           mov     [_z80pc], si    ; Save our program counter\n");

		// Now adjust the proper timing

		fprintf(fp, "           mov     esi, [dwOriginalExec]   \n");
		fprintf(fp, "           sub     esi, [cyclesRemaining]\n");
		fprintf(fp, "           add     [dwElapsedTicks], esi\n");
		fprintf(fp, "           sub     [dwOriginalExec], esi\n");

	fprintf(fp, "           push    edi     ; Save our structure address\n");

#ifdef DARWIN
	align_stack("edx","eax");
#else
	if (bUseStack)
		fprintf(fp, "           push    eax     ; Data to write\n");

	fprintf(fp, "           push    edx     ; And our desired I/O address\n");
#endif

	if (FALSE == bUseStack)
	{
		fprintf(fp, "           xchg    eax, edx ; Swap address/data around\n");
		fprintf(fp, "           mov     ebx, edi        ; Our z80IoWrite structure address\n");
	}

	fprintf(fp, "           call    dword [edi + 4] ; Go call our handler\n");

#ifdef DARWIN
	restore_stack("edx");
#else
	fprintf(fp, "           pop     edx     ; Restore our address\n");

	if (bUseStack)
		fprintf(fp, "           pop     eax     ; Restore our data written\n");
#endif

	fprintf(fp, "           pop     edi     ; Save our structure address\n");

	fprintf(fp, "           xor     ebx, ebx        ; Zero our future HL\n");
	fprintf(fp, "           xor     ecx, ecx        ; Zero our future BC\n");
	fprintf(fp, "           mov     bx, [_z80hl]    ; Get HL back\n");
	fprintf(fp, "           mov     cx, [_z80bc]    ; Get BC back\n");
	fprintf(fp, "           mov     ax, [_z80af]    ; Get AF back\n");
	fprintf(fp, "           xor     esi, esi        ; Zero it!\n");
	fprintf(fp, "           mov     si, [_z80pc]    ; Get our program counter back\n");
	fprintf(fp, "           mov     ebp, [_z80Base] ; Base pointer comes back\n");
	fprintf(fp, "           add     esi, ebp        ; Rebase it properly\n");

	fprintf(fp, "           ret\n\n");
}

void ExecCode(void)
{
	fprintf(fp, "           global  _%sexec\n", cpubasename);
	fprintf(fp, "           global  %sexec_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %sexec\n", cpubasename);

	sprintf(procname, "%sexec_", cpubasename);
	ProcBegin(0xffffffff);

	fprintf(fp, "_%sexec:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%sexec:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "           mov     eax, [esp+4]    ; Get our execution cycle count\n");

	fprintf(fp, "           push    ebx                     ; Save all registers we use\n");
	fprintf(fp, "           push    ecx\n");
	fprintf(fp, "           push    edx\n");
	fprintf(fp, "           push    ebp\n");
	fprintf(fp, "           push    esi\n");
	fprintf(fp, "           push    edi\n");
	fprintf(fp, "\n");

	fprintf(fp, "           mov     edi, eax\n");
	fprintf(fp, "           mov     dword [cyclesRemaining], eax    ; Store # of instructions to\n");
	fprintf(fp, "           mov     [dwOriginalExec], eax   ; Store this!\n");

	fprintf(fp, "                                           ; execute\n");
	fprintf(fp, "           cmp     word [_z80halted], 0\n");
	fprintf(fp, "           je      goCpu\n");
	fprintf(fp, "           mov     eax, dword [cyclesRemaining]\n");

	if (FALSE == bNoTiming)
	{
		if (FALSE == bSingleStep)
			fprintf(fp, "           add     dword [dwElapsedTicks], eax\n");
		else
			fprintf(fp, "           add     dword [dwElapsedTicks], 7\n");
	}

	fprintf(fp, "           mov     dword [cyclesRemaining], 0      ; Nothing left!\n");
	fprintf(fp, "           mov     eax, 80000000h  ; Successful exection\n");
	fprintf(fp, "           jmp     popReg\n");
	fprintf(fp, "goCpu:\n");
	fprintf(fp, "           cld                             ; Go forward!\n");
	fprintf(fp, "\n");
	fprintf(fp, "           xor     eax, eax                ; Zero EAX 'cause we use it!\n");
	fprintf(fp, "           xor     ebx, ebx                ; Zero EBX, too\n");
	fprintf(fp, "           xor     ecx, ecx                ; Zero ECX\n");
	fprintf(fp, "           xor     edx, edx                ; And EDX\n");
	fprintf(fp, "           xor     esi, esi                ; Zero our source address\n");
	fprintf(fp, "\n");
	fprintf(fp, "           mov     ax, [_z80af]            ; Accumulator & flags\n");
	fprintf(fp, "           xchg    ah, al          ; Swap these for later\n");
	fprintf(fp, "           mov     bx, [_z80hl]            ; Get our HL value\n");
	fprintf(fp, "           mov     cx, [_z80bc]            ; And our BC value\n");
	fprintf(fp, "           mov     ebp, [_z80Base]         ; Get the base address\n");
	fprintf(fp, "           mov     si, [_z80pc]            ; Get our program counter\n");
	fprintf(fp, "           add     esi, ebp                ; Add in our base address\n");

	fprintf(fp, "           cmp     [_z80intPending], byte 0        ; Interrupt pending?\n");
	fprintf(fp, "           jz              masterExecTarget\n\n");
	fprintf(fp, "           call    causeInternalInterrupt\n\n");
	fprintf(fp, "masterExecTarget:\n");
	FetchNextInstruction(0xffffffff);

	fprintf(fp, "; We get to invalidInsWord if it's a double byte invalid opcode\n");
	fprintf(fp, "\n");
	fprintf(fp, "invalidInsWord:\n");

	fprintf(fp, "; Apparently, this is equivalent to 8 nops\n");
	FetchNextInstruction(0xffffffff);

	fprintf(fp, "           dec     esi\n");
	fprintf(fp, "\n");
	fprintf(fp, "; We get to invalidInsByte if it's a single byte invalid opcode\n");
	fprintf(fp, "\n");

	fprintf(fp, "invalidInsByte:\n");
	fprintf(fp, "           xchg    ah, al          ; Swap them back so they look good\n");
	fprintf(fp, "           mov     [_z80af], ax            ; Store A & flags\n");
	fprintf(fp, "           dec     esi                     ; Back up one instruction...\n");
	fprintf(fp, "           mov     edx, esi                ; Get our address in EAX\n");
	fprintf(fp, "           sub     edx, ebp                ; And subtract our base for\n");
	fprintf(fp, "                                           ; an invalid instruction\n");
	fprintf(fp, "           jmp     emulateEnd\n");
	fprintf(fp, "\n");
	fprintf(fp, "noMoreExec2:\n");
	fprintf(fp, "           sub     esi, [_baseFixup]\n");
	fprintf(fp, "noMoreExec:\n");
	fprintf(fp, "           cmp     [bEIExit], byte 0       ; Are we exiting because of an EI?\n");
	fprintf(fp, "           jne     checkEI\n");
	fprintf(fp, "noMoreExecNoEI:\n");
	fprintf(fp, "           xchg    ah, al          ; Swap these for later\n");
	fprintf(fp, "           mov     [_z80af], ax            ; Store A & flags\n");

	if (FALSE == bSingleStep)
	{
		fprintf(fp, "           mov     edx, [dwOriginalExec]   ; Original exec time\n");
		fprintf(fp, "           sub     edx, edi                ; Subtract # of cycles remaining\n");
		fprintf(fp, "           add     [dwElapsedTicks], edx   ; Add our executed time\n");
	}

	fprintf(fp, "           mov     edx, 80000000h          ; Indicate successful exec\n");
	fprintf(fp, "           jmp     emulateEnd        ; All finished!\n");
	fprintf(fp, "\n");
	fprintf(fp, "; Now let's tuck away the virtual registers for next time\n");
	fprintf(fp, "\n");
	fprintf(fp, "storeFlags:\n");
	fprintf(fp, "           xchg    ah, al          ; Swap these for later\n");
	fprintf(fp, "           mov     [_z80af], ax            ; Store A & flags\n");
	fprintf(fp, "emulateEnd:\n");
	fprintf(fp, "           mov     [_z80hl], bx            ; Store HL\n");
	fprintf(fp, "           mov     [_z80bc], cx            ; Store BC\n");
	fprintf(fp, "           sub     esi, [_z80Base]         ; Knock off physical address\n");
	fprintf(fp, "           mov     [_z80pc], si            ; And store virtual address\n");
	fprintf(fp, "           mov     eax, edx                ; Result code return\n");
	fprintf(fp, "\n");
	fprintf(fp, "popReg:\n");
	fprintf(fp, "           pop     edi                     ; Restore registers\n");
	fprintf(fp, "           pop     esi\n");
	fprintf(fp, "           pop     ebp\n");
	fprintf(fp, "           pop     edx\n");
	fprintf(fp, "           pop     ecx\n");
	fprintf(fp, "           pop     ebx\n");
	fprintf(fp, "\n");
	fprintf(fp, "           ret\n");
	fprintf(fp, "\n");

	/* checkEI : If an interrupt arrives and ints are disabled, then
	   z80intPending is set. When ei is executed, it resets the remaining
	   cycles and we arrive here. */

	fprintf(fp, "checkEI:\n");
	fprintf(fp, "           xor     edx, edx\n");
	fprintf(fp, "           mov     [bEIExit], byte 0\n");

	fprintf(fp, "           cmp     word [_z80halted], 0\n");
	fprintf(fp, "           jne     noMoreExecNoEI\n");

	fprintf(fp, "           sub     edx, edi        ; Find out how much time has passed\n");

	fprintf(fp, "           mov     edi, [dwEITiming]\n");
	fprintf(fp, "           sub     edi, edx\n");
	fprintf(fp, "           js              noMoreExecNoEI\n");

	// Do we want to exit at the end of an interrupt ???
	fprintf(fp, "checkexitonei:\n");
	fprintf(fp, "           cmp     [ExitOnEI],byte 1\n");
	fprintf(fp, "           je      noMoreExecNoEI\n");

	fprintf(fp, "checkei2:\n");
	fprintf(fp, "           xor     edx, edx\n");

	fprintf(fp, "           cmp     [_z80intPending], byte 0\n");
	fprintf(fp, "           je      near masterExecTarget\n");
	fprintf(fp, "           call    causeInternalInterrupt\n");
	fprintf(fp, "           jmp     masterExecTarget\n\n");

	Alignment();
	fprintf(fp, "causeInternalInterrupt:\n");
	fprintf(fp, "           mov     word [_z80halted], 0   ; We're not halted anymore!\n");
	fprintf(fp, "           test    [_z80iff], byte IFF1    ; Interrupt enabled yet?\n");
	fprintf(fp, "           jz              near internalInterruptsDisabled\n");
	fprintf(fp, "\n; Interrupts enabled. Clear IFF1 and IFF2\n\n");

	fprintf(fp, "           mov     [_z80intPending], byte 0\n");
	fprintf(fp, "           mov     [_z80iff],byte 0\n");

	fprintf(fp, "\n; Save off our active register sets\n\n");

	fprintf(fp, "           xchg    ah, al          ; Swap these for later\n");
	fprintf(fp, "           mov     [_z80af], ax            ; Store A & flags\n");
	fprintf(fp, "           mov     [_z80hl], bx            ; Store HL\n");
	fprintf(fp, "           mov     [_z80bc], cx            ; Store BC\n");
	fprintf(fp, "           sub     esi, ebp                        ; Knock off physical address\n");
	fprintf(fp, "           mov     [_z80pc], si            ; And store virtual address\n");

	fprintf(fp, "           xor     eax, eax\n");
	fprintf(fp, "           mov     al, [_intData]\n\n");

	fprintf(fp, "\n");
	fprintf(fp, "           push    edi\n");
	fprintf(fp, "\n");

	if (bThroughCallHandler)
	  {
	    fprintf(fp, "       pushad\n" );
	    fprintf(fp, "               xor edx, edx\n" );
	    fprintf(fp, "               mov     ax, [_z80pc]\n");
	    fprintf(fp, "               mov     [_wordval], ax\n");
	    fprintf(fp, "               push    ecx\n");
	    fprintf(fp, "               push    ebx\n");
	    fprintf(fp, "               push    esi\n");

	    fprintf(fp, "       mov ax, [_z80af]\n");   // Get AF
	    fprintf(fp, "       mov     bx, [_z80hl]\n");       // Get HL
	    fprintf(fp, "       mov     cx, [_z80bc]\n");       // Get BC
	    fprintf(fp, "               call    PushWord\n");

	    fprintf(fp, "               pop     esi\n");
	    fprintf(fp, "               pop     ebx\n");
	    fprintf(fp, "               pop     ecx\n");
	    fprintf(fp, "       popad\n" );
	  }
	else
	  {
	    fprintf(fp, "               mov     dx, [_z80pc]\n");
	    fprintf(fp, "               xor     edi, edi\n");
	    fprintf(fp, "               mov     di, word [_z80sp]\n");
	    fprintf(fp, "               sub     di, 2\n");
	    fprintf(fp, "               mov     word [_z80sp], di\n");
	    fprintf(fp, "               mov     [ebp+edi], dx\n");
	  }

	fprintf(fp, "           cmp     dword [_z80interruptMode], 2 ; Are we lower than mode 2?\n");
	fprintf(fp, "           jb              internalJustModeTwo\n");
	fprintf(fp, "           mov     ah, [_z80i]     ; Get our high address here\n");
	fprintf(fp, "           and     eax, 0ffffh ; Only the lower part\n");
	fprintf(fp, "           mov     ax, [eax+ebp] ; Get our vector\n");
	fprintf(fp, "           jmp     internalSetNewVector ; Go set it!\n");
	fprintf(fp, "internalJustModeTwo:\n");
	fprintf(fp, "           mov     ax, word [_z80intAddr]\n");
	fprintf(fp, "internalSetNewVector:\n");
	fprintf(fp, "           mov     [_z80pc], ax\n");
	fprintf(fp, "\n");
	fprintf(fp, "           pop     edi\n");
	fprintf(fp, "\n");
	fprintf(fp, "           xor     eax, eax        ; Zero this so we can use it as an index\n");

	fprintf(fp, "           mov     al, [_z80interruptMode]\n");
	fprintf(fp, "           mov     al, [intModeTStates+eax]\n");
	fprintf(fp, "           sub     edi, eax\n");

	fprintf(fp, "\n; Restore all the registers and whatnot\n\n");

	fprintf(fp, "           mov     ax, [_z80af]            ; Accumulator & flags\n");
	fprintf(fp, "           xchg    ah, al          ; Swap these for later\n");
	fprintf(fp, "           mov     bx, [_z80hl]            ; Get our HL value\n");
	fprintf(fp, "           mov     cx, [_z80bc]            ; And our BC value\n");
	fprintf(fp, "           mov     ebp, [_z80Base]         ; Get the base address\n");
	fprintf(fp, "           mov     si, [_z80pc]            ; Get our program counter\n");
	fprintf(fp, "           add     esi, ebp                ; Add in our base address\n");
	fprintf(fp, "internalInterruptsDisabled:\n");

	fprintf(fp, "           xor     edx, edx\n");
	fprintf(fp, "           ret\n\n");
}

void SetStopAtIntEnd(void)
{
	fprintf(fp, "           global  _%s_set_stop_at_int_end\n", cpubasename);
	fprintf(fp, "           global  %s_set_stop_at_int_end_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %s_set_stop_at_int_end\n", cpubasename);

	sprintf(procname, "%s_set_stop_at_int_end_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%s_set_stop_at_int_end:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%s_set_stop_at_int_end:\n", cpubasename);

	fprintf(fp, "           mov     dword [_z80stoponintend], 1\n");
	fprintf(fp, "           ret\n");
}

void NmiCode(void)
{
	fprintf(fp, "           global  _%snmi\n", cpubasename);
	fprintf(fp, "           global  %snmi_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %snmi\n", cpubasename);

	sprintf(procname, "%snmi_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%snmi:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%snmi:\n", cpubasename);


	fprintf(fp, "           mov     word [_z80halted], 0   ; We're not halted anymore!\n");
	fprintf(fp, "           mov     al, [_z80iff]   ; Get our IFF setting\n");

	/* Apparently from the undocumented z80 */
	/* (http://www.msxnet.org/tech/z80-documented.pdf) the z80 can */
	/* handle nested nmis, and it is not supposed to do that if you */
	/* just read the official documentation ! */
	fprintf(fp, "           and     al, IFF1+IFF2   ; Check nested nmi...\n");
	fprintf(fp, "           cmp     al, IFF2        ; nested outside int!\n");
	fprintf(fp, "           je      noflipflop\n");

	fprintf(fp, "           and     al, IFF1        ; Just IFF 1\n");
	fprintf(fp, "           shl     al, 1   ; Makes IFF1->IFF2 and zeros IFF1\n");
	fprintf(fp, "           mov     [_z80iff], al   ; Store it back to the interrupt state!\n");
	fprintf(fp, "\n");
	fprintf(fp, "noflipflop:\n");
	fprintf(fp, "           push    ebp\n");
	fprintf(fp, "           push    edi\n");
	fprintf(fp, "           mov     ebp, [_z80Base]\n");
	fprintf(fp, "\n");

	fprintf(fp, "           xor     eax, eax\n");
	fprintf(fp, "           mov     ax, [_z80pc]\n");


	if (bThroughCallHandler)
	  {
	    fprintf(fp, "               push    esi\n");
	    fprintf(fp, "               push    ebx\n");
	    fprintf(fp, "               push    ecx\n");

	    fprintf(fp, "               mov     [_wordval], ax\n");
	    fprintf(fp, "               mov     esi, ebp\n");
	    fprintf(fp, "               add     esi, eax\n");
	    fprintf(fp, "       mov ax, [_z80af]\n");   // Get AF
	    fprintf(fp, "       mov     bx, [_z80hl]\n");       // Get HL
	    fprintf(fp, "       mov     cx, [_z80bc]\n");       // Get BC
	    fprintf(fp, "               push    ebx\n");
	    fprintf(fp, "               push    ecx\n");
	    fprintf(fp, "               push    edx\n");
	    fprintf(fp, "               push    esi\n");
	    fprintf(fp, "               push    eax\n");
	    fprintf(fp, "           xor     edx,edx\n");
	    fprintf(fp, "               xor     edi,edi\n");
	    fprintf(fp, "               call    PushWord\n");
	    fprintf(fp, "               pop     eax\n");
	    fprintf(fp, "               pop     esi\n");
	    fprintf(fp, "               pop     edx\n");
	    fprintf(fp, "               pop     ecx\n");
	    fprintf(fp, "               pop     ebx\n");

	    fprintf(fp, "               pop     ecx\n");
	    fprintf(fp, "               pop     ebx\n");
	    fprintf(fp, "               pop     esi\n");
	  }
	else
	  {
	    fprintf(fp, "               xor     edi, edi\n");
	    fprintf(fp, "               mov     di, word [_z80sp]\n");
	    fprintf(fp, "               sub     di, 2\n");
	    fprintf(fp, "               mov     word [_z80sp], di\n");
	    fprintf(fp, "               mov     [ebp+edi], ax\n");
	  }

	fprintf(fp, "           mov     ax, [_z80nmiAddr]\n");
	fprintf(fp, "           mov     [_z80pc], ax\n");
	fprintf(fp, "\n");
	fprintf(fp, "           add     [dwElapsedTicks], dword 11      ; 11 T-States for NMI\n");
	INC_RCOUNTER;
	fprintf(fp, "           pop     edi\n");
	fprintf(fp, "           pop     ebp\n");
	fprintf(fp, "\n");
	fprintf(fp, "           xor     eax, eax        ; Indicate we took the interrupt\n");
	fprintf(fp, "           ret\n");
}

void IntCode(void)
{
	fprintf(fp, "           global  _%sint\n", cpubasename);
	fprintf(fp, "           global  %sint_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %sint\n", cpubasename);

	sprintf(procname, "%sint_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%sint:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%sint:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "           mov     eax, [esp+4]    ; Get our (potential) lower interrupt address\n");

	fprintf(fp, "           mov     ah, IFF1        ; Is IFF1 enabled?\n");
	fprintf(fp, "           and     ah, [_z80iff]   ; Well, is it?\n");
	fprintf(fp, "           jz              near interruptsDisabled\n");
	fprintf(fp, "\n");

	fprintf(fp, "\n; Interrupts enabled. Clear IFF1 and IFF2\n\n");

	fprintf(fp, "           and     dword [_z80iff], ~(IFF1 | IFF2);\n\n");
	fprintf(fp, "           mov     word [_z80halted], 0   ; We're not halted!\n");
	fprintf(fp, "\n");
	fprintf(fp, "           push    ebp\n");
	fprintf(fp, "           push    edi\n");
	fprintf(fp, "           push    edx\n");
	fprintf(fp, "           mov     ebp, [_z80Base]\n");
	fprintf(fp, "\n");
	fprintf(fp, "           mov     [_z80intPending], word 0\n");

	if (bThroughCallHandler)
	{
		fprintf(fp, "       pushad\n" );
		fprintf(fp, "           xor edx, edx\n" );
		fprintf(fp, "           mov     ax, [_z80pc]\n");
		fprintf(fp, "           mov     [_wordval], ax\n");
		fprintf(fp, "           push    ecx\n");
		fprintf(fp, "           push    ebx\n");
		fprintf(fp, "           push    esi\n");

		fprintf(fp, "       mov ax, [_z80af]\n");       // Get AF
		fprintf(fp, "       mov bx, [_z80hl]\n");       // Get HL
		fprintf(fp, "       mov cx, [_z80bc]\n");       // Get BC
		fprintf(fp, "       xor edi,edi\n");
		fprintf(fp, "           call    PushWord\n");

		fprintf(fp, "           pop     esi\n");
		fprintf(fp, "           pop     ebx\n");
		fprintf(fp, "           pop     ecx\n");
		fprintf(fp, "       popad\n" );
	}
	else
	{
		fprintf(fp, "           mov     dx, [_z80pc]\n");
		fprintf(fp, "           xor     edi, edi\n");
		fprintf(fp, "           mov     di, word [_z80sp]\n");
		fprintf(fp, "           sub     di, 2\n");
		fprintf(fp, "           mov     word [_z80sp], di\n");
		fprintf(fp, "           mov     [ebp+edi], dx\n");
	}

	fprintf(fp, "           cmp     dword [_z80interruptMode], 2 ; Are we lower than mode 2?\n");
	fprintf(fp, "           jb              justModeTwo\n");
	fprintf(fp, "           mov     ah, [_z80i]     ; Get our high address here\n");
	fprintf(fp, "           and     eax, 0ffffh ; Only the lower part\n");
	fprintf(fp, "           mov     ax, [eax+ebp] ; Get our vector\n");
	fprintf(fp, "           jmp     setNewVector ; Go set it!\n");
	fprintf(fp, "justModeTwo:\n");
	fprintf(fp, "           mov     ax, word [_z80intAddr]\n");
	fprintf(fp, "setNewVector:\n");
	fprintf(fp, "           mov     [_z80pc], ax\n");
	fprintf(fp, "\n");
	fprintf(fp, "           pop     edx\n");
	fprintf(fp, "           pop     edi\n");
	fprintf(fp, "           pop     ebp\n");
	fprintf(fp, "\n");
	fprintf(fp, "           xor     eax, eax        ; Indicate we took the interrupt\n");
	fprintf(fp, "           mov     al, [_z80interruptMode]\n");
	fprintf(fp, "           add     [dwElapsedTicks], eax\n");
	INC_RCOUNTER;
	fprintf(fp, "           xor     eax, eax        ; Indicate we took the interrupt\n");
	fprintf(fp, "           jmp     z80intExit\n");
	fprintf(fp, "\n");
	fprintf(fp, "interruptsDisabled:\n");
	fprintf(fp, "\n");
	fprintf(fp, "           mov     [_z80intPending], byte 1\n");
	fprintf(fp, "           mov     [_intData], al  ; Save this info for later\n");
	fprintf(fp, "           mov     eax, 0ffffffffh         ; Indicate we didn't take it\n");
	fprintf(fp, "\n");
	fprintf(fp, "z80intExit:\n");
	fprintf(fp, "           ret\n");
}

void ResetCode(void)
{
	fprintf(fp, "           global  _%sreset\n", cpubasename);
	fprintf(fp, "           global  %sreset_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %sreset\n", cpubasename);
	sprintf(procname, "%sreset_", cpubasename);
	ProcBegin(0xffffffff);

	fprintf(fp, "_%sreset:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%sreset:\n", cpubasename);

	fprintf(fp, "           xor     eax, eax        ; Zero AX\n");
	fprintf(fp, "\n");
	fprintf(fp, "           mov     word [_z80halted], ax ; We're not halted anymore!\n");
	fprintf(fp, "           mov     word [_z80intPending], ax     ; We're not halted anymore!\n");
	fprintf(fp, "           mov     word [_z80af], ax       ; Zero A & flags\n");
	fprintf(fp, "           mov     word [_z80bc], ax       ; Zero BC\n");
	fprintf(fp, "           mov     word [_z80de],  ax      ; Zero DE\n");
	fprintf(fp, "           mov     word [_z80hl], ax       ; Zero HL\n");
	fprintf(fp, "           mov     word [_z80afprime], ax  ; Zero AF Prime\n");
	fprintf(fp, "           mov     word [_z80bcprime], ax  ; Zero BC prime\n");
	fprintf(fp, "           mov     word [_z80deprime], ax ; Zero DE prime\n");
	fprintf(fp, "           mov     word [_z80hlprime], ax ; Zero HL prime\n");
	fprintf(fp, "           mov     byte [_z80i], al        ; Zero Interrupt register\n");
	fprintf(fp, "           mov     byte [_z80r], al        ; Zero refresh register\n");
	fprintf(fp, "           mov     word [_z80ix], 0ffffh   ; Default mz80Index register\n");
	fprintf(fp, "           mov     word [_z80iy], 0ffffh   ; Default mz80Index register\n");
	fprintf(fp, "           mov     word [_z80pc], ax       ; Zero program counter\n");
	fprintf(fp, "           mov     word [_z80sp], ax       ; And the stack pointer\n");
	fprintf(fp, "           mov     dword [_z80interruptMode], eax ; Clear our interrupt mode (0)\n");
	fprintf(fp, "           mov     byte [_z80rCounter], al ; Clear our interrupt mode (0)\n");
	fprintf(fp, "           mov     dword [_z80iff], eax ; IFF1/IFF2 disabled!\n");
	// These 2 are set by mz80SeetRomBase. No need to touch them in a
	// reset...
	// fprintf(fp, "                mov     word [_z80intAddr], 38h ; Set default interrupt address\n");
	// fprintf(fp, "                mov     word [_z80nmiAddr], 66h ; Set default nmi addr\n");
	fprintf(fp, "\n");
	fprintf(fp, "           ret\n");
	fprintf(fp, "\n");
}

void SetContextCode(void)
{
	fprintf(fp, "           global  _%sSetContext\n", cpubasename);
	fprintf(fp, "           global  %sSetContext_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %sSetContext\n", cpubasename);

	sprintf(procname, "%sSetContext_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%sSetContext:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%sSetContext:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "           mov     eax, [esp+4]    ; Get our context address\n");

	fprintf(fp, "           push    esi             ; Save registers we use\n");
	fprintf(fp, "           push    edi\n");
	fprintf(fp, "           push    ecx\n");
//	fprintf(fp, "           push    es\n");
//	fprintf(fp, "           mov     di, ds\n");
//	fprintf(fp, "           mov     es, di\n");
	fprintf(fp, "           mov     edi, _%scontextBegin\n", cpubasename);
	fprintf(fp, "           mov     esi, eax        ; Source address in ESI\n");
	fprintf(fp, "           mov     ecx, _%scontextEnd - _%scontextBegin\n", cpubasename, cpubasename);
	fprintf(fp, "           rep     movsb\n");
//	fprintf(fp, "           pop     es\n");
	fprintf(fp, "           pop     ecx\n");
	fprintf(fp, "           pop     edi\n");
	fprintf(fp, "           pop     esi\n");
	fprintf(fp, "           ret                     ; No return code\n");
}

void GetContextCode(void)
{
	fprintf(fp, "           global  _%sGetContext\n", cpubasename);
	fprintf(fp, "           global  %sGetContext_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %sGetContext\n", cpubasename);

	sprintf(procname, "%sGetContext_", cpubasename);
	ProcBegin(0xffffffff);
	fprintf(fp, "_%sGetContext:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%sGetContext:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "           mov     eax, [esp+4]    ; Get our context address\n");

	fprintf(fp, "           push    esi             ; Save registers we use\n");
	fprintf(fp, "           push    edi\n");
	fprintf(fp, "           push    ecx\n");
//	fprintf(fp, "           push    es\n");
//	fprintf(fp, "           mov     di, ds\n");
//	fprintf(fp, "           mov     es, di\n");
	fprintf(fp, "           mov     ecx, _%scontextEnd - _%scontextBegin\n", cpubasename, cpubasename);
	fprintf(fp, "           mov     esi, _%scontextBegin\n", cpubasename);
	fprintf(fp, "           mov     edi, eax        ; Source address in ESI\n");
	fprintf(fp, "           rep     movsb           ; Move it as fast as we can!\n");
//	fprintf(fp, "           pop     es\n");
	fprintf(fp, "           pop     ecx\n");
	fprintf(fp, "           pop     edi\n");
	fprintf(fp, "           pop     esi\n");
	fprintf(fp, "           ret                     ; No return code\n");
}

void GetContextSizeCode(void)
{
	fprintf(fp, "           global  _%sGetContextSize\n", cpubasename);
	fprintf(fp, "           global  %sGetContextSize_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "           global  %sGetContextSize\n", cpubasename);

	sprintf(procname, "%sGetContextSize_", cpubasename);
	ProcBegin(0xffffffff);

	fprintf(fp, "_%sGetContextSize:\n", cpubasename);

	if (bPlain)
		fprintf(fp, "%sGetContextSize:\n", cpubasename);

	fprintf(fp, "           mov     eax, _%scontextEnd - _%scontextBegin\n", cpubasename, cpubasename);
	fprintf(fp, "           ret\n\n");
}

void EmitCode(void)
{
	CodeSegmentBegin();
	EmitRegularInstructions();
	EmitCBInstructions();
	EmitEDInstructions();
	strcpy(mz80Index, "ix");
	strcpy(majorOp, "DD");
	EmitDDInstructions();
	strcpy(mz80Index, "iy");
	strcpy(majorOp, "FD");
	EmitFDInstructions();
	ReadMemoryByteHandler();
	WriteMemoryByteHandler();

	if (bThroughCallHandler)
	{
		PushWordHandler();
		PopWordHandler();
	}

	ReadIoHandler();
	WriteIoHandler();
	GetContextCode();
	SetContextCode();
	GetContextSizeCode();
	GetTicksCode();
	ReleaseTimesliceCode();
	ResetCode();
	IntCode();
	NmiCode();
	SetStopAtIntEnd();
	ExecCode();
	CodeSegmentEnd();
}

int main(int argc, char **argv)
{
	UINT32 dwLoop = 0;

	printf("MakeZ80 - V%s - Copyright 1998, Neil Bradley (neil@synthcom.com)\n", VERSION);

	if (argc < 2)
	{
		printf("Usage: %s outfile [option1] [option2] ....\n", argv[0]);
		printf("\n   -s  - Stack calling conventions (DJGPP, MSVC, Borland)\n");
		printf("   -ss - Create MZ80.ASM to execute a single instruction at a time\n");
		printf("   -cs - All stack operations go through handlers\n");
		printf("   -16 - Treat all I/O input and output as 16 bit (BC) instead of (C)\n");
		printf("   -l  - Create 'plain' labels - ones without leading or trailing _'s\n");
		printf("   -nt - No timing additions occur\n");
		exit(1);
	}

	dwLoop = 1;

	while (dwLoop < argc)
	{
		if (strcmp("-cs", argv[dwLoop]) == 0 || strcmp("-cs", argv[dwLoop]) == 0)
			bThroughCallHandler = TRUE;
		if (strcmp("-ss", argv[dwLoop]) == 0 || strcmp("-ss", argv[dwLoop]) == 0)
			bSingleStep = TRUE;
		if (strcmp("-s", argv[dwLoop]) == 0 || strcmp("-S", argv[dwLoop]) == 0)
			bUseStack = TRUE;
		if (strcmp("-l", argv[dwLoop]) == 0 || strcmp("-L", argv[dwLoop]) == 0)
			bPlain = TRUE;
		if (strcmp("-nt", argv[dwLoop]) == 0)
		{
			bNoTiming = TRUE;
			bSingleStep = TRUE;
		}

		dwLoop++;
	}

	for (dwLoop = 1; dwLoop < argc; dwLoop++)
		if (argv[dwLoop][0] != '-')
		{
			fp = fopen(argv[dwLoop], "w");
			break;
		}

	if (NULL == fp)
	{
		fprintf(stderr, "Can't open %s for writing\n", argv[1]);
		exit(1);
	}

	strcpy(cpubasename, "mz80");

	StandardHeader();
	DataSegment();
	EmitCode();
	ProgramEnd();

	fclose(fp);

	return 0;
}
