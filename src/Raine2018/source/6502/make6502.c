/* Raine changes (2004) :
    - added zero page indirect addressing mode (instructions of type 2 in the list)
    - added Absolute Indexed Indirect Addressing [(Absolute,X)] (Jump Instruction Only)
    - The memory read and memory writes now allow direct ram access to areas outside
   cpubase (like AddM6502ARead(0x800,0x800,NULL,&latch); )

   1.6raine2 : add the missing addressing modes for the BIT instruction
   - fixed bad inc instruction
 */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define	VERSION 	"1.6raine2"

#define TRUE            0xff
#define FALSE           0x0
#define	INVALID	0xff

#define UINT32          unsigned long int
#define UINT16          unsigned short int
#define UINT8                   unsigned char

FILE *fp = NULL;
char string[150];
char cpubasename[150];
UINT32 dwPageLabel = 0;
UINT32 dwGlobalLabel = 0;
UINT32 dwAnotherLabel = 0;
UINT8 bPlain = FALSE;				// Do we use plain global names?
UINT8 bUseStack = FALSE;			// Use stack calling conventions
UINT8 bZeroDirect = FALSE;			// Zero page direct
UINT8 bSingleStep = FALSE;			// Here if we want to single step the CPU
UINT8 bBankswitch = FALSE;			// Here if we want bankswitching
UINT8 bInvalidAsNop = FALSE;		// Treat invalid instructions as NOP
UINT8 bNoDecimal = FALSE;			// Set if we don't want decimal mode
UINT8 b6510Instructions = FALSE;	// TRUE If we include 6510 instructions
UINT32 dwBankSize = 12;				// 4K Default
static UINT8 bUsed[256];

static void BrkHandler(UINT16 dwOpcode);
static void LdxHandler(UINT16 dwOpcode);
static void LdyHandler(UINT16 dwOpcode);
static void LdaHandler(UINT16 dwOpcode);
static void TxsHandler(UINT16 dwOpcode);
static void TsxHandler(UINT16 dwOpcode);
static void TaxHandler(UINT16 dwOpcode);
static void TxaHandler(UINT16 dwOpcode);
static void TayHandler(UINT16 dwOpcode);
static void TyaHandler(UINT16 dwOpcode);
static void DecxyHandler(UINT16 dwOpcode);
static void IncxyHandler(UINT16 dwOpcode);
static void StaHandler(UINT16 dwOpcode);
static void StxHandler(UINT16 dwOpcode);
static void StyHandler(UINT16 dwOpcode);
static void BranchHandler(UINT16 dwOpcode);
static void AndHandler(UINT16 dwOpcode);
static void AslHandler(UINT16 dwOpcode);
static void LsrHandler(UINT16 dwOpcode);
static void OraHandler(UINT16 dwOpcode);
static void EorHandler(UINT16 dwOpcode);
static void JmpHandler(UINT16 dwOpcode);
static void JsrHandler(UINT16 dwOpcode);
static void RtsHandler(UINT16 dwOpcode);
static void IncHandler(UINT16 dwOpcode);
static void DecHandler(UINT16 dwOpcode);
static void CmpHandler(UINT16 dwOpcode);
static void CpyHandler(UINT16 dwOpcode);
static void CpxHandler(UINT16 dwOpcode);
static void ClcCldCliClvHandler(UINT16 dwOpcode);
static void AdcHandler(UINT16 dwOpcode);
static void SbcHandler(UINT16 dwOpcode);
static void RolHandler(UINT16 dwOpcode);
static void RorHandler(UINT16 dwOpcode);
static void BitHandler(UINT16 dwOpcode);
static void PhaPhpHandler(UINT16 dwOpcode);
static void PlaPlpHandler(UINT16 dwOpcode);
static void RtiHandler(UINT16 dwOpcode);
static void NopHandler(UINT16 dwOpcode);

static void DeaInaHandler(UINT16 dwOpcode);
static void StzHandler(UINT16 dwOpcode);
static void TrbHandler(UINT16 dwOpcode);
static void TsbHandler(UINT16 dwOpcode);
static void BraHandler(UINT16 dwOpcode);

struct sOp
{
	UINT16 bOpCode;
	void (*Emitter)(UINT16);
	UINT8 b6510Instruction;
};

struct sOp StandardOps[] =
{
	{0x00,	BrkHandler,	FALSE},		// Bank mod *

	{0x81,	StaHandler,	FALSE},
	{0x85,	StaHandler,	FALSE},
	{0x8d,	StaHandler,	FALSE},
	{0x91,	StaHandler,	FALSE},
	{0x95,	StaHandler,	FALSE},
	{0x92,  StaHandler,     2},
	{0x99,	StaHandler,	FALSE},
	{0x9d,	StaHandler,	FALSE},

	{0x8e,	StxHandler,	FALSE},
	{0x86,	StxHandler,	FALSE},
	{0x96,	StxHandler,	FALSE},

	{0x8c,	StyHandler,	FALSE},
	{0x84,	StyHandler,	FALSE},
	{0x94,	StyHandler,	FALSE},

	{0xa9,	LdaHandler,	FALSE},
	{0xad,	LdaHandler,	FALSE},
	{0xa5,	LdaHandler,	FALSE},
	{0xbd,	LdaHandler,	FALSE},
	{0xb9,	LdaHandler,	FALSE},
	{0xa1,	LdaHandler,	FALSE},
	{0xb1,	LdaHandler,	FALSE},
	{0xb2,	LdaHandler,	2},
	{0xb5,	LdaHandler,	FALSE},

	{0xae,	LdxHandler,	FALSE},
	{0xa6,	LdxHandler,	FALSE},
	{0xa2,	LdxHandler,	FALSE},
	{0xbe,	LdxHandler,	FALSE},
	{0xb6,	LdxHandler,	FALSE},

	{0xac,	LdyHandler,	FALSE},
	{0xa4,	LdyHandler,	FALSE},
	{0xa0,	LdyHandler,	FALSE},
	{0xbc,	LdyHandler,	FALSE},
	{0xb4,	LdyHandler,	FALSE},

	{0x88,	DecxyHandler,	FALSE},
	{0xca,	DecxyHandler,	FALSE},

	{0xe8,	IncxyHandler,	FALSE},
	{0xc8,	IncxyHandler,	FALSE},

	{0x8a,	TxaHandler,	FALSE},
	{0x98,	TyaHandler,	FALSE},
	{0x9a,	TxsHandler,	FALSE},
	{0xa8,	TayHandler,	FALSE},
	{0xaa,	TaxHandler,	FALSE},
	{0xba,	TsxHandler,	FALSE},

	{0x10,	BranchHandler,	FALSE},		// Bank mod *
	{0x30,	BranchHandler,	FALSE},		// Bank mod *
	{0x50,	BranchHandler,	FALSE},		// Bank mod *
	{0x70,	BranchHandler,	FALSE},		// Bank mod *
	{0x90,	BranchHandler,	FALSE},		// Bank mod *
	{0xb0,	BranchHandler,	FALSE},		// Bank mod *
	{0xd0,	BranchHandler,	FALSE},		// Bank mod *
	{0xf0,	BranchHandler,	FALSE},		// Bank mod *

	{0x2d,	AndHandler,	FALSE},
	{0x25,	AndHandler,	FALSE},
	{0x29,	AndHandler,	FALSE},
	{0x3d,	AndHandler,	FALSE},
	{0x39,	AndHandler,	FALSE},
	{0x21,	AndHandler,	FALSE},
	{0x31,	AndHandler,	FALSE},
	{0x32,	AndHandler,	2},
	{0x35,	AndHandler,	FALSE},

	{0x0a,	AslHandler,	FALSE},
	{0x0e,	AslHandler,	FALSE},
	{0x06,	AslHandler,	FALSE},
	{0x1e,	AslHandler,	FALSE},
	{0x16,	AslHandler,	FALSE},

	{0x4a,	LsrHandler,	FALSE},
	{0x4e,	LsrHandler,	FALSE},
	{0x46,	LsrHandler,	FALSE},
	{0x5e,	LsrHandler,	FALSE},
	{0x56,	LsrHandler,	FALSE},

	{0x0d,	OraHandler,	FALSE},
	{0x05,	OraHandler,	FALSE},
	{0x09,	OraHandler,	FALSE},
	{0x1d,	OraHandler,	FALSE},
	{0x19,	OraHandler,	FALSE},
	{0x01,	OraHandler,	FALSE},
	{0x11,	OraHandler,	FALSE},
	{0x12,  OraHandler,     2},
	{0x15,	OraHandler,	FALSE},

	{0x4d,	EorHandler,	FALSE},
	{0x45,	EorHandler,	FALSE},
	{0x49,	EorHandler,	FALSE},
	{0x5d,	EorHandler,	FALSE},
	{0x59,	EorHandler,	FALSE},
	{0x41,	EorHandler,	FALSE},
	{0x51,	EorHandler,	FALSE},
	{0x52,	EorHandler,	2},
	{0x55,	EorHandler,	FALSE},

	{0xee,	IncHandler,	FALSE},
	{0xe6,	IncHandler,	FALSE},
	{0xfe,	IncHandler,	FALSE},
	{0xf6,	IncHandler,	FALSE},

	{0xce,	DecHandler,	FALSE},
	{0xc6,	DecHandler,	FALSE},
	{0xde,	DecHandler,	FALSE},
	{0xd6,	DecHandler,	FALSE},

	{0xcd,	CmpHandler,	FALSE},
	{0xc5,	CmpHandler,	FALSE},
	{0xc9,	CmpHandler,	FALSE},
	{0xdd,	CmpHandler,	FALSE},
	{0xd9,	CmpHandler,	FALSE},
	{0xc1,	CmpHandler,	FALSE},
	{0xd1,	CmpHandler,	FALSE},
	{0xd2,	CmpHandler,	2},
	{0xd5,	CmpHandler,	FALSE},

	{0xcc,	CpyHandler,	FALSE},
	{0xc4,	CpyHandler,	FALSE},
	{0xc0,	CpyHandler,	FALSE},

	{0xec,	CpxHandler,	FALSE},
	{0xe4,	CpxHandler,	FALSE},
	{0xe0,	CpxHandler,	FALSE},

	{0x4c,	JmpHandler,	FALSE},			// Bank mod *
	{0x6c,	JmpHandler,	FALSE},			// Bank mod *
	{0x7c,	JmpHandler,	FALSE},			// Bank mod *

	{0x20,	JsrHandler,	FALSE},			// Bank mod *
	{0x60,	RtsHandler,	FALSE},			// Bank mod *

	{0x18,	ClcCldCliClvHandler,	FALSE},
	{0x58,	ClcCldCliClvHandler,	FALSE},
	{0xb8,	ClcCldCliClvHandler,	FALSE},
	{0xd8,	ClcCldCliClvHandler,	FALSE},
	{0x38,	ClcCldCliClvHandler,	FALSE},
	{0x78,	ClcCldCliClvHandler,	FALSE},
	{0xf8,	ClcCldCliClvHandler,	FALSE},

	{0x6d,	AdcHandler,	FALSE},
	{0x65,	AdcHandler,	FALSE},
	{0x69,	AdcHandler,	FALSE},
	{0x7d,	AdcHandler,	FALSE},
	{0x79,	AdcHandler,	FALSE},
	{0x61,	AdcHandler,	FALSE},
	{0x71,	AdcHandler,	FALSE},
	{0x72,	AdcHandler,	2},
	{0x75,	AdcHandler,	FALSE},

	{0xed,	SbcHandler,	FALSE},
	{0xe5,	SbcHandler,	FALSE},
	{0xe9,	SbcHandler,	FALSE},
	{0xfd,	SbcHandler,	FALSE},
	{0xf9,	SbcHandler,	FALSE},
	{0xe1,	SbcHandler,	FALSE},
	{0xf1,	SbcHandler,	FALSE},
	{0xf2,	SbcHandler,	2},
	{0xf5,	SbcHandler,	FALSE},

	{0x2a,	RolHandler,	FALSE},
	{0x2e,	RolHandler,	FALSE},
	{0x26,	RolHandler,	FALSE},
	{0x3e,	RolHandler,	FALSE},
	{0x36,	RolHandler,	FALSE},

	{0x6a,	RorHandler,	FALSE},
	{0x6e,	RorHandler,	FALSE},
	{0x66,	RorHandler,	FALSE},
	{0x7e,	RorHandler,	FALSE},
	{0x76,	RorHandler,	FALSE},

	{0x2c,	BitHandler,	FALSE},
	{0x24,	BitHandler,	FALSE},
	{0x34,	BitHandler,	2},
	{0x89,	BitHandler,	2}, // immediate
	{0x3c,	BitHandler,	2}, // Absolute,x

	{0x48,	PhaPhpHandler,	FALSE},
	{0x08,	PhaPhpHandler,	FALSE},

	{0x68,	PlaPlpHandler,	FALSE},
	{0x28,	PlaPlpHandler,	FALSE},

	{0x40,	RtiHandler,	FALSE},			// Bank mod *
	{0xea,	NopHandler,	FALSE},

	// The remaining instructions are part of the 6510 - not the basic 6502

	{0x3a,	DeaInaHandler,	TRUE},
	{0x1a,	DeaInaHandler,	TRUE},

	{0xda,	PhaPhpHandler,	TRUE},
	{0x5a,	PhaPhpHandler,	TRUE},

	{0xfa,	PlaPlpHandler,	TRUE},
	{0x7a,	PlaPlpHandler,	TRUE},

	{0x64,	StzHandler,	TRUE},
	{0x74,	StzHandler,	TRUE},
	{0x9c,	StzHandler,	TRUE},
	{0x9e,	StzHandler,	TRUE},

	{0x80,	BraHandler,	TRUE},				// Bank mod

	{0x04,	TsbHandler,	TRUE},
	{0x0c,	TsbHandler,	TRUE},

	{0x14,	TrbHandler,	TRUE},
	{0x1c,	TrbHandler,	TRUE},

	// Terminator

	{0xffff, NULL}
};

UINT8 bTimingTable[256] =
{
	0x07, 0x06, 0x02, 0x02, 0x03, 0x03, 0x05, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x06, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x03, 0x04, 0x06, 0x02, 0x02, 0x04, 0x02, 0x02, 0x04, 0x04, 0x07, 0x02,
	0x06, 0x06, 0x02, 0x02, 0x02, 0x03, 0x05, 0x02, 0x04, 0x02, 0x02, 0x02, 0x03, 0x04, 0x06, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x02, 0x04, 0x06, 0x02, 0x02, 0x04, 0x02, 0x02, 0x03, 0x04, 0x07, 0x02,
	0x06, 0x06, 0x02, 0x02, 0x02, 0x03, 0x05, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x04, 0x06, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x02, 0x04, 0x06, 0x02, 0x02, 0x04, 0x03, 0x02, 0x02, 0x04, 0x07, 0x02,
	0x06, 0x06, 0x02, 0x02, 0x03, 0x03, 0x05, 0x02, 0x04, 0x02, 0x02, 0x02, 0x05, 0x04, 0x06, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x04, 0x04, 0x06, 0x02, 0x02, 0x04, 0x04, 0x02, 0x06, 0x04, 0x07, 0x02,
	0x02, 0x06, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x02,
	0x03, 0x06, 0x03, 0x02, 0x04, 0x04, 0x04, 0x02, 0x02, 0x05, 0x02, 0x02, 0x04, 0x05, 0x05, 0x02,
	0x02, 0x06, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x04, 0x04, 0x04, 0x02, 0x02, 0x04, 0x02, 0x02, 0x04, 0x04, 0x04, 0x02,
	0x02, 0x06, 0x02, 0x02, 0x03, 0x03, 0x05, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x06, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x02, 0x04, 0x06, 0x02, 0x02, 0x04, 0x03, 0x02, 0x02, 0x04, 0x07, 0x02,
	0x02, 0x06, 0x02, 0x02, 0x03, 0x03, 0x05, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x06, 0x02,
	0x03, 0x05, 0x03, 0x02, 0x02, 0x04, 0x06, 0x02, 0x02, 0x04, 0x04, 0x02, 0x02, 0x04, 0x07, 0x02 };

UINT8 bBit6502tox86[8] = {0, 6, 	  1, 0xff, 0xff, 0xff, 4, 7};
UINT8 bBitx86to6502[8] = {0, 0xff, 0xff, 0xff, 	  6, 0xff, 1, 7};

static void Flags6502toX86()
{
	fprintf(fp, "		xor	edx, edx\n");
	fprintf(fp, "		mov	dl, ah\n");
	fprintf(fp, "		mov	[_altFlags], dl\n");
	fprintf(fp, "		and	[_altFlags], byte 3ch;\n");
	fprintf(fp, "		mov	ah, [bit6502tox86+edx]\n");
}

static void FlagsX86to6502()
{
	fprintf(fp, "		xor	edx, edx\n");
	fprintf(fp, "		mov	dl, ah\n");
	fprintf(fp, "		mov	ah, [bitx86to6502+edx]\n");
	fprintf(fp, "		or		ah, [_altFlags]\n");
}

static void SetZeroSign(char *pszRegister)
{
	fprintf(fp, "		mov	dl, ah	; Save flags\n");
	fprintf(fp, "		or	%s, %s	; OR Our new value\n", pszRegister, pszRegister);
	fprintf(fp, "		lahf		; Restore flags\n");
	fprintf(fp, "		and	dl, 03fh	; Original value\n");
	fprintf(fp, "		and	ah, 0c0h	; Only zero and sign\n");
	fprintf(fp, "		or	ah, dl		; New flags with the old!\n");
}

static void SetZero(char *pszRegister)
{
	fprintf(fp, "		mov	dl, ah	; Save flags\n");
	fprintf(fp, "		or	%s, %s	; OR Our new value\n", pszRegister, pszRegister);
	fprintf(fp, "		lahf		; Restore flags\n");
	fprintf(fp, "		and	dl, 0bfh	; Original value\n");
	fprintf(fp, "		and	ah, 040h	; Only zero\n");
	fprintf(fp, "		or	ah, dl		; New flags with the old!\n");
}

static void DecSetZeroSign(char *pszRegister)
{
	fprintf(fp, "		mov	dl, ah	; Save flags\n");
	fprintf(fp, "		dec	%s	; Decrement\n", pszRegister);
	fprintf(fp, "		lahf		; Restore flags\n");
	fprintf(fp, "		and	dl, 03fh	; Original value\n");
	fprintf(fp, "		and	ah, 0c0h	; Only zero and sign\n");
	fprintf(fp, "		or	ah, dl		; New flags with the old!\n");
}

static void IncSetZeroSign(char *pszRegister)
{
	fprintf(fp, "		mov	dl, ah	; Save flags\n");
	fprintf(fp, "		inc	%s	; Increment\n", pszRegister);
	fprintf(fp, "		lahf		; Restore flags\n");
	fprintf(fp, "		and	dl, 03fh	; Original value\n");
	fprintf(fp, "		and	ah, 0c0h	; Only zero and sign\n");
	fprintf(fp, "		or	ah, dl		; New flags with the old!\n");
}

static void PCToPage()
{
	fprintf(fp, "		mov	edi, esi	; Here, too\n");
	fprintf(fp, "		and	edi, 0%.4xh	; Knock off the unimportant stuff\n", (1 << dwBankSize) - 1);
	fprintf(fp, "		and	esi, 0%.4xh	; Knock out the detailed stuff\n", ~((1 << dwBankSize) - 1));
	fprintf(fp, "		mov	[_%sBasePage], esi	; Store our base page\n", cpubasename);
	fprintf(fp, "		shr	esi, %ld	; Get rid of the data we don't need\n", dwBankSize);
	fprintf(fp, "		mov	esi, [_%spbBankSwitch+esi*4]	; Get our base address\n", cpubasename);
	fprintf(fp, "		mov	[_%sBaseAddr], esi	; Save our base pointer (possibly)\n", cpubasename);
	fprintf(fp, "		add	esi, edi	; Add our offset - depaged\n");
	fprintf(fp, ";\n; Warning! edi is trashed at this point!\n;\n");
	++dwPageLabel;
}

static void PageToPC()
{
	fprintf(fp, "		sub	esi, [_%sBaseAddr]	; Normalize it!\n", cpubasename);
	fprintf(fp, "		add	esi, [_%sBasePage]	; And our base page!\n", cpubasename);
}

static void StandardHeader()
{
	fprintf(fp,"; For assembly by NASM only\n");
	fprintf(fp,"bits 32\n");

	fprintf(fp, ";\n; %s - V%s - Copyright 1998, Neil Bradley (neil@synthcom.com)\n;\n;\n\n", cpubasename, VERSION);
	if (bUseStack)
		fprintf(fp, "; Using stack calling conventions\n");
	else
		fprintf(fp, "; Using register calling conventions\n");

	if (bBankswitch)
		fprintf(fp, "; Bank switch version - %d byte banks\n", (1 << dwBankSize));

	if (bZeroDirect)
		fprintf(fp, "; Zero page version (all zero page accesses are direct)\n");
	else
		fprintf(fp, "; Non-zero page version (all zero page accesses through handlers)\n");

	if (bSingleStep)
		fprintf(fp, "; Single step version (debug)\n");

	fprintf(fp, "\n\n");
}

static void Alignment()
{
	fprintf(fp, "\ntimes ($$-$) & 3 nop	; pad with NOPs to 4-byte boundary\n\n");
}

static void ProcBegin(char *procname, UINT32 dwOpcode)
{
	Alignment();
	fprintf(fp, "%s:\n", procname);

	if (0xffffffff != dwOpcode)
	{
		if (FALSE == bSingleStep)
		{
			fprintf(fp, "		sub	dword [cyclesRemaining], byte %d\n", bTimingTable[dwOpcode]);
			fprintf(fp, "		jc	near noMoreExec	; Can't execute anymore!\n");
		}
		else
		{
			fprintf(fp, "		dec	dword [cyclesRemaining]	; Single stepping (debugger)\n");
			fprintf(fp, "		jz	near noMoreExec ; No more code!\n");
		}

		fprintf(fp, "		add	dword [dwElapsedTicks], byte %d\n", bTimingTable[dwOpcode]);
	}
}

static void ProcEnd(char *procname)
{
}

static void FetchInstructionByte()
{
	fprintf(fp,	"		mov	dl, [esi]		; Get the next instruction\n");
	fprintf(fp, "		inc	esi		; Advance PC!\n");
}

static void FetchAndExec(UINT32 dwClock)
{
	fprintf(fp, "		xor	edx, edx\n");
	fprintf(fp, "		mov	dl, [esi]\n");
	fprintf(fp, "		inc	esi\n");
	fprintf(fp, "		jmp	dword [%sregular+edx*4]\n\n", cpubasename);
}

static void ReadMemoryByte(char *pszTargetReg, char *pszAddress)
{
	fprintf(fp, "		mov	edi, [_%sMemRead]	; Point to the read array\n\n", cpubasename);
	fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
	fprintf(fp, "		cmp	[edi], word 0ffffh ; End of the list?\n");
	fprintf(fp, "		je		memoryRead%ld\n", dwGlobalLabel);
	fprintf(fp, "		cmp	%s, [edi]	; Are we smaller?\n", pszAddress);
	fprintf(fp, "		jb		nextAddr%ld		; Yes, go to the next address\n", dwGlobalLabel);
	fprintf(fp, "		cmp	%s, [edi+4]	; Are we bigger?\n", pszAddress);
	fprintf(fp, "		jbe	callRoutine%ld\n\n", dwGlobalLabel);
	fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
	fprintf(fp, "		add	edi, 10h		; Next structure!\n");
	fprintf(fp, "		jmp	short checkLoop%ld\n\n", dwGlobalLabel);
	fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);

	// Check internal read
	fprintf(fp, "           cmp     dword[edi+8],0     ; [J3d!] Use internal write?\n");
#if 1
	fprintf(fp, "           jne     callHandler%ld\n", dwGlobalLabel);

	fprintf(fp, "		mov	ebp, [edi+12]	; memory base to read\n");
	fprintf(fp, "		mov	%s, [ebp + e%s]	; Get our data\n\n", pszTargetReg, pszAddress);

	fprintf(fp, "		mov	ebp, [_%sBase]	; Get our base pointer back\n", cpubasename);
	fprintf(fp, "		jmp	readExit%ld\n\n", dwGlobalLabel);
	// Use a handler
	fprintf(fp, "callHandler%ld:\n", dwGlobalLabel);
#else
	fprintf(fp, "           je     memoryRead%ld\n", dwGlobalLabel);
#endif

	assert(strcmp(pszAddress, "dx") == 0);

	fprintf(fp, "		call	ReadMemoryByte	; Standard read routine\n");

	if (strcmp(pszTargetReg, "bl") != 0)
		fprintf(fp, "		mov	bl, [_%sx]	; Get X back\n", cpubasename);
	if (strcmp(pszTargetReg, "cl") != 0)
		fprintf(fp, "		mov	cl, [_%sy]	; Get Y back\n", cpubasename);

	if (strcmp(pszTargetReg, "al") != 0)
	{
		fprintf(fp, "		mov	%s, al	; Get our value\n", pszTargetReg);
		fprintf(fp, "		mov	ax, [_%saf]	; Get our flags & stuff back\n", cpubasename);
	}
	else
		fprintf(fp, "		mov	ah, [_%saf + 1] ; Get our flags back\n", cpubasename);

	fprintf(fp, "		jmp	readExit%ld\n\n", dwGlobalLabel);
	fprintf(fp, "memoryRead%ld:\n", dwGlobalLabel);

	if (bBankswitch)
	{
		fprintf(fp, "		mov	ebp, e%s	; Save our original address in EBP\n", pszAddress);
		fprintf(fp, "		and	ebp, 0ffffh ; Mask off the upper bits\n");
		fprintf(fp, "		mov	edi, ebp	; Get our address\n");
		fprintf(fp, "		shr	edi, %ld	; Find which bank we belong to\n", dwBankSize);
		fprintf(fp, "		mov	edi, [_%spbBankSwitch+edi*4] ; Get our base address for this bank\n", cpubasename);
		fprintf(fp, "		or	edi, edi	; NULL?\n");
		fprintf(fp, "		jz	regularRead%ld	; If so, we're not banking!\n", dwGlobalLabel);

		// This is the code that fetches the data from the proper address

		fprintf(fp, "		and	ebp, 0%.4xh	; Mask out the unimportant stuff\n", (1 << dwBankSize) - 1);
		fprintf(fp, "		mov	%s, [ebp+edi]	; Get our banked data\n", pszTargetReg);
		fprintf(fp, "		mov	ebp, [_%sBase]	; Get our base pointer back\n", cpubasename);
		fprintf(fp, "		jmp	readExit%ld\n", dwGlobalLabel);

		fprintf(fp, "regularRead%ld:\n", dwGlobalLabel);
		fprintf(fp, "		mov	ebp, [_%sBase]	; Get our base pointer back\n", cpubasename);
	}

	fprintf(fp, "		mov	%s, [ebp + e%s]	; Get our data\n\n", pszTargetReg, pszAddress);

	fprintf(fp, "readExit%ld:\n", dwGlobalLabel);

	dwGlobalLabel++;
}

static void ReadMemoryWord()
{
	fprintf(fp, "		push	edx	; Save address\n");
	fprintf(fp, "		mov	[_%saf], ax	; Store AF\n", cpubasename);
	ReadMemoryByte("al", "dx");
	fprintf(fp, "		pop	edx	; Restore address\n");
	fprintf(fp, "		inc	dx	; Next address\n");
	fprintf(fp, "		push	eax	; Save it for later\n");
	fprintf(fp, "		mov	ax, [_%saf]	; Restore AF because it gets used later\n", cpubasename);
	ReadMemoryByte("dh", "dx");
	fprintf(fp, "		pop	eax	; Restore it!\n");
	fprintf(fp, "		mov	dl, al	; Restore our word into DX\n");
	fprintf(fp, "		mov	ax, [_%saf]	; Restore AF\n", cpubasename);
}

static void WriteMemoryByte(char *pszSourceReg, char *pszAddress)
{
	fprintf(fp, "		mov	edi, [_%sMemWrite]	; Point to the write array\n\n", cpubasename);
	fprintf(fp, "checkLoop%ld:\n", dwGlobalLabel);
	fprintf(fp, "		cmp	[edi], word 0ffffh ; End of our list?\n");
	fprintf(fp, "		je	near memoryWrite%ld	; Yes - go write it!\n", dwGlobalLabel);
	fprintf(fp, "		cmp	%s, [edi]	; Are we smaller?\n", pszAddress);
	fprintf(fp, "		jb	nextAddr%ld	; Yes... go to the next addr\n", dwGlobalLabel);
	fprintf(fp, "		cmp	%s, [edi+4]	; Are we bigger?\n", pszAddress);
	fprintf(fp, "		jbe	callRoutine%ld	; If not, go call it!\n\n", dwGlobalLabel);
	fprintf(fp, "nextAddr%ld:\n", dwGlobalLabel);
	fprintf(fp, "		add	edi, 10h		; Next structure, please\n");
	fprintf(fp, "		jmp	short checkLoop%ld\n\n", dwGlobalLabel);
	fprintf(fp, "callRoutine%ld:\n", dwGlobalLabel);

	// Check internal/external write

	fprintf(fp, "           cmp     dword[edi+8],0     ; [J3d!] Use internal write?\n");
#if 1
	fprintf(fp, "           jne     callHandler%ld\n", dwGlobalLabel);
	fprintf(fp, "		mov	ebp, [edi+12]	; memory base to read\n");
	fprintf(fp, "		mov	[ebp + e%s], %s ; Store the byte\n\n", pszAddress, pszSourceReg);

	fprintf(fp, "		mov	ebp, [_%sBase]	; Get our base pointer back\n", cpubasename);
	fprintf(fp, "		jmp	writeMacroExit%ld\n", dwGlobalLabel);

	fprintf(fp, "callHandler%ld:\n", dwGlobalLabel);
#else
	fprintf(fp, "           je     short memoryWrite%ld\n", dwGlobalLabel);
#endif
	// Save off our registers!

	fprintf(fp, "		mov	[_%sx], bl	; Save X\n", cpubasename);
	fprintf(fp, "		mov	[_%sy], cl	; Save Y\n", cpubasename);
	fprintf(fp, "		mov	[_%saf], ax	; Save Accumulator & flags\n", cpubasename);

	if (bBankswitch)
		PageToPC();
	else
		fprintf(fp, "		sub	esi, ebp	; Our program counter\n");

	fprintf(fp, "		mov	[_%spc], si	; Save our program counter\n", cpubasename);

	if (bUseStack)
	{
		fprintf(fp, "		push	edi	; Pointer to MemoryWriteByte structure\n");
		if (strcmp(pszSourceReg, "bl") == 0)
			fprintf(fp, "		push	ebx	; The byte value\n");
		if (strcmp(pszSourceReg, "bh") == 0)
		{
			fprintf(fp, "		mov	bl, bh	; Put a copy here\n");
			fprintf(fp, "		push	ebx	; The byte value\n");
		}
		if (strcmp(pszSourceReg, "cl") == 0)
			fprintf(fp, "		push	ecx	; The byte value\n");
		if (strcmp(pszSourceReg, "al") == 0)
			fprintf(fp, "		push	eax	; The byte value\n");

		fprintf(fp, "		and	e%s, 0ffffh	; Only lower 16 bits\n", pszAddress);
		fprintf(fp, "		push	e%s	; The address\n", pszAddress);
	}
	else		// Register calling convention
	{
		if ((strcmp(pszSourceReg, "al") == 0) &&
			 (strcmp(pszAddress, "dx") == 0))
			fprintf(fp, "		xchg	eax, edx	; Swap 'em\n");
		else
		{
			if (strcmp(pszAddress, "bx") == 0)
				fprintf(fp, "		mov	eax, ebx	; Address\n");
			if (strcmp(pszAddress, "cx") == 0)
				fprintf(fp, "		mov	eax, ebx	; Address\n");
			if (strcmp(pszAddress, "dx") == 0)
				fprintf(fp, "		mov	eax, edx	; Address\n");
			if (strcmp(pszSourceReg, "bh") == 0)
			{
				fprintf(fp, "		mov	bl, bh	; Put a copy here\n");
				fprintf(fp, "		mov	edx, ebx	; The byte value\n");
			}
			if (strcmp(pszSourceReg, "bl") == 0)
				fprintf(fp, "		mov	edx, ebx	; The byte value\n");
			if (strcmp(pszSourceReg, "cl") == 0)
				fprintf(fp, "		mov	edx, ecx	; The byte value\n");
			if (strcmp(pszSourceReg, "al") == 0)
				fprintf(fp, "		mov	edx, eax	; The byte value\n");
		}
		fprintf(fp, "		mov	ebx, edi	; MemoryWriteByte structure\n");
	}

	fprintf(fp, "		call	dword [edi + 8] ; Go call our handler\n");
	if (bUseStack)
		fprintf(fp, "		add	esp, 12	; Get rid of our stack\n");

	fprintf(fp, "		xor	ebx, ebx	; Zero this\n");
	fprintf(fp, "		xor	ecx, ecx	; This too!\n");
	fprintf(fp, "		mov	bl, [_%sx]	; Get X back\n", cpubasename);
	fprintf(fp, "		mov	cl, [_%sy]	; Get Y back\n", cpubasename);
	fprintf(fp, "		xor	esi, esi	; Zero it!\n");
	fprintf(fp, "		mov	si, [_%spc]	; Get our program counter back\n", cpubasename);
	fprintf(fp, "		mov	ebp, [_%sBase] ; Base pointer comes back\n", cpubasename);

	if (bBankswitch)
		PCToPage();
	else
		fprintf(fp, "		add	esi, ebp	; Rebase it properly\n");

	fprintf(fp, "		mov	ax, [_%saf]	; Get our flags & stuff back\n", cpubasename);

	fprintf(fp, "		jmp	writeMacroExit%ld\n\n", dwGlobalLabel);
	fprintf(fp, "memoryWrite%ld:\n", dwGlobalLabel);
	fprintf(fp, "		mov	[ebp + e%s], %s ; Store the byte\n\n", pszAddress, pszSourceReg);
	fprintf(fp, "writeMacroExit%ld:\n", dwGlobalLabel);
	++dwGlobalLabel;
}

static void ReadMemoryByteHandler()
{
	Alignment();
	fprintf(fp, "; This is a generic read memory byte handler when a foreign\n");
	fprintf(fp, "; handler is to be called\n\n");
	fprintf(fp, "ReadMemoryByte:\n");
	fprintf(fp, "		mov	[_%sx], bl	; Save X\n", cpubasename);
	fprintf(fp, "		mov	[_%sy], cl	; Save Y\n", cpubasename);
	fprintf(fp, "		mov	[_%saf], ax	; Save Accumulator & flags\n", cpubasename);

	if (bBankswitch)
		PageToPC();
	else
		fprintf(fp, "		sub	esi, ebp	; Our program counter\n");

	fprintf(fp, "		mov	[_%spc], si	; Save our program counter\n", cpubasename);

	if (bUseStack)
	{
		fprintf(fp, "		push	edi	; Save our structure address\n");
		fprintf(fp, "		and	edx, 0ffffh	; Only the lower 16 bits\n");
		fprintf(fp, "		push	edx	; And our desired address\n");
	}
	else
	{
		fprintf(fp, "		mov	eax, edx	; Get our desired address reg\n");
		fprintf(fp, "		mov	edx, edi	; Pointer to the structure\n");
	}

	fprintf(fp, "		call	dword [edi + 8]	; Go call our handler\n");

	if (bUseStack)
		fprintf(fp, "		add	esp, 8	; Get the junk off the stack\n");

	fprintf(fp, "		xor	ebx, ebx	; Zero X\n");
	fprintf(fp, "		xor	ecx, ecx	; Zero Y\n");
	fprintf(fp, "		xor	esi, esi	; Zero it!\n");
	fprintf(fp, "		mov	si, [_%spc]	; Get our program counter back\n", cpubasename);
	fprintf(fp, "		mov	ebp, [_%sBase] ; Base pointer comes back\n", cpubasename);

	if (bBankswitch)
		PCToPage();
	else
		fprintf(fp, "		add	esi, ebp	; Rebase it properly\n");

	fprintf(fp, "		ret\n\n");
	++dwGlobalLabel;
}

static void FetchInstructionWord()
{
	fprintf(fp, "		mov	dx, [esi]	; Get our address\n");
	fprintf(fp, "		add	esi, 2	; Increment past instruction\n");
}

static void Absolute()
{
	FetchInstructionWord();
}

static void ZeroPage()
{
	FetchInstructionByte();
}

static void ZeroPageX()
{
	FetchInstructionByte();
	fprintf(fp, "		add	dl, bl	; Add X\n");
}

static void ZeroPageY()
{
	FetchInstructionByte();
	fprintf(fp, "		add	dl, cl	; Add Y\n");
}

static void ZeroPageIndirect() {
	FetchInstructionByte();
	if (bZeroDirect)
		fprintf(fp, "		mov	dx, [ebp+edx]	; Get our 16 bit address\n");
	else
		ReadMemoryWord();
}

static void AbsoluteX()
{
	FetchInstructionWord();
	fprintf(fp, "		add	dx, bx	 ; Add X\n");
}

static void AbsoluteY()
{
	FetchInstructionWord();
	fprintf(fp, "		add	dx, cx	 ; Add Y\n");
}

static void IndirectX()
{
	FetchInstructionByte();
	fprintf(fp, "		add	dl, bl	; Add in X\n");

	if (bZeroDirect)
		fprintf(fp, "		mov	dx, [ebp+edx]	; Get our 16 bit address\n");
	else
		ReadMemoryWord();

}

static void IndirectY()
{
	FetchInstructionByte();

	if (bZeroDirect)
		fprintf(fp, "		mov	dx, [ebp+edx]	; Get our 16 bit address\n");
	else
		ReadMemoryWord();

	fprintf(fp, "		add	dx, cx	; Add in Y\n");
}

static void DataSegment()
{
	UINT32 dwLoop = 0;
	UINT32 dwBit = 0;
	UINT8 bValue = 0;

	fprintf(fp, "		section	.data\n");
	Alignment();

	if (bPlain) {
		fprintf(fp, "		global	%spc\n\n",cpubasename);
	} else {
		fprintf(fp, "		global	_%spc\n\n",cpubasename);
	}

	fprintf(fp, "		global	%spbBankSwitch_, _%spbBankSwitch\n\n", cpubasename, cpubasename);
	fprintf(fp, "_%scontextBegin:\n", cpubasename);
	fprintf(fp, "\n");
	fprintf(fp, "; DO NOT CHANGE THE ORDER OF THE FOLLOWING REGISTERS!\n");
	fprintf(fp, "\n");
	fprintf(fp, "_%sBase	dd	0	; Base address for 6502 stuff\n", cpubasename);
	fprintf(fp, "_%sMemRead	dd	0	; Offset of memory read structure array\n", cpubasename);
	fprintf(fp, "_%sMemWrite	dd	0	; Offset of memory write structure array\n", cpubasename);

	if (bBankswitch)
	{
		fprintf(fp, "_%spbBankSwitch:\n", cpubasename);

		for (dwLoop = 0; dwLoop < 32; dwLoop++)
		{
			if (dwLoop * (1 << dwBankSize) < 65536)
				fprintf(fp, "		dd	0	; Addr=$%.4lx\n", dwLoop * (1 << dwBankSize));
			else
				fprintf(fp, "		dd	0	; Filler\n");
		}
	}

	fprintf(fp, "_%saf	dw	0	; A register and flags\n", cpubasename);

	fprintf(fp, "_%spc:\n", cpubasename);
	fprintf(fp, "%spc	dw	0	; 6502 Program counter\n", cpubasename);

	fprintf(fp, "_%sx		db	0	; X\n", cpubasename);
	fprintf(fp, "_%sy		db	0	; Y\n", cpubasename);
	fprintf(fp, "_%ss		db	0	; s\n", cpubasename);
	fprintf(fp, "_irqPending	db	0	; Non-zero if an IRQ is pending\n");
	fprintf(fp, "\n");
	fprintf(fp, "_%scontextEnd:\n", cpubasename);

	if (bBankswitch)
	{
		fprintf(fp, "_%sBaseAddr	dd	0	; Temporary base address\n", cpubasename);
		fprintf(fp, "_%sBasePage	dd	0	; What page are we on? (ready for use)\n", cpubasename);
	}

	fprintf(fp, "\n");
	Alignment();
	fprintf(fp, "_tempAddr	dd	0	; Temporary address storage\n");
	fprintf(fp, "dwElapsedTicks	dd 0	; Elapsed ticks!\n");
	fprintf(fp, "cyclesRemaining	dd	0	; # Of cycles remaining\n");
	fprintf(fp, "_altFlags	db	0	; Storage for I, D, and B\n");


	// Now we write out our tables

	Alignment();

	for (dwLoop = 0; dwLoop < 256; dwLoop++)
		bUsed[dwLoop] = 0;

	// Create flag translation tables

	fprintf(fp,	"bit6502tox86:\n");

	for (dwLoop = 0; dwLoop < 256; dwLoop++)
	{
		bValue = 0;

		for (dwBit = 0; dwBit < 8; dwBit++)
		{
			if (bBit6502tox86[dwBit] != 0xff)
			{
				if ((1 << dwBit) & dwLoop)
					bValue |= (1 << bBit6502tox86[dwBit]);
			}
		}

		if ((dwLoop & 0x0f) == 0)
			fprintf(fp, "		db	");

		if (bValue < 0xa0)
			fprintf(fp, "%.2xh", bValue);
		else
			fprintf(fp, "0%.2xh", bValue);

		if ((dwLoop & 0x0f) != 0xf)
			fprintf(fp, ", ");
		else
			fprintf(fp, "\n");
	}

	// Create flag translation tables

	fprintf(fp,	"\nbitx86to6502:\n");

	for (dwLoop = 0; dwLoop < 256; dwLoop++)
	{
		bValue = 0;

		for (dwBit = 0; dwBit < 8; dwBit++)
		{
			if (bBitx86to6502[dwBit] != 0xff)
			{
				if ((1 << dwBit) & dwLoop)
					bValue |= (1 << bBitx86to6502[dwBit]);
			}
		}

		if ((dwLoop & 0x0f) == 0)
			fprintf(fp, "		db	");

		if (bValue < 0xa0)
			fprintf(fp, "%.2xh", bValue);
		else
			fprintf(fp, "0%.2xh", bValue);

		if ((dwLoop & 0x0f) != 0xf)
			fprintf(fp, ", ");
		else
			fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	// Now rip through and find out what is and isn't used

	dwLoop = 0;

	while (StandardOps[dwLoop].Emitter)
	{
		assert(StandardOps[dwLoop].bOpCode < 0x100);
		if (bUsed[StandardOps[dwLoop].bOpCode])
		{
			fprintf(stderr, "Oops! %.2x\n", StandardOps[dwLoop].bOpCode);
			exit(1);
		}

		if (b6510Instructions)
			bUsed[StandardOps[dwLoop].bOpCode] = 1;
		else
		{
			if (StandardOps[dwLoop].b6510Instruction == FALSE)
				bUsed[StandardOps[dwLoop].bOpCode] = 1;
		}

		dwLoop++;
	}

	fprintf(stderr, "%ld Unique opcodes\n", dwLoop);

	// Now that that's taken care of, emit the table

	fprintf(fp, "%sregular:\n", cpubasename);

	dwLoop = 0;

	while (dwLoop < 0x100)
	{
		fprintf(fp, "		dd	");
		if (bUsed[dwLoop])
			fprintf(fp, "Reg02Inst%.2lx", dwLoop);
		else
		{
			if (bInvalidAsNop)
				fprintf(fp, "Reg02Instea");
			else
				fprintf(fp, "invalidInsByte");
		}

		fprintf(fp, "\n");
		dwLoop++;
	}
	fprintf(fp, "\n");
}

static void CodeSegmentBegin()
{
	fprintf(fp, "		section	.text\n");
}

static void CodeSegmentEnd()
{
}

static void ProgramEnd()
{
}

static void EmitRegularInstructions()
{
	UINT32 dwLoop = 0;
	UINT32 dwLoop2 = 0;

	while (dwLoop < 0x100)
	{
		dwLoop2 = 0;

		while (StandardOps[dwLoop2].bOpCode != dwLoop && StandardOps[dwLoop2].bOpCode != 0xffff)
			dwLoop2++;

		assert(dwLoop2 < 0x100);
		if (StandardOps[dwLoop2].Emitter
			&& StandardOps[dwLoop2].bOpCode != 0xffff &&
			bUsed[dwLoop])
			StandardOps[dwLoop2].Emitter((UINT16) dwLoop);

		dwLoop++;
	}
}

static void Immediate(char *pszRegister)
{
	fprintf(fp, "		mov	%s, [esi]	; Get our next byte\n", pszRegister);
	fprintf(fp, "		inc	esi		; Increment to our next byte\n");
}

// LDX Handler

static void LdxHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; LDX\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xa2 == dwOpcode)
		Immediate("bl");
	else
	if (0xae == dwOpcode)
		Absolute();
	else
	if (0xa6 == dwOpcode)
		ZeroPage();
	else
	if (0xbe == dwOpcode)
		AbsoluteY();
	else
	if (0xb6 == dwOpcode)
		ZeroPageY();
	else
		assert(0);

	if (0xa2 != dwOpcode)
	{
		if ((0xa6 != dwOpcode && 0xb6 != dwOpcode) || (FALSE == bZeroDirect))
			ReadMemoryByte("bl", "dx");
		else
			fprintf(fp, "		mov	bl, [ebp + edx]	; Zero page!\n");
	}

	SetZeroSign("bl");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// LDY Handler

static void LdyHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; LDY\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xa0 == dwOpcode)
		Immediate("cl");
	else
	if (0xac == dwOpcode)
		Absolute();
	else
	if (0xa4 == dwOpcode)
		ZeroPage();
	else
	if (0xbc == dwOpcode)
		AbsoluteX();
	else
	if (0xb4 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	if (0xa0 != dwOpcode)
	{
		if ((0xa4 != dwOpcode && 0xb4 != dwOpcode) || (FALSE == bZeroDirect))
			ReadMemoryByte("cl", "dx");
		else
			fprintf(fp, "		mov	cl, [ebp + edx]	; Zero page!\n");
	}

	SetZeroSign("cl");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// DEC Handler

static void DecxyHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	if (0x88 == dwOpcode)
		fprintf(fp, "; DEY\n");
	else
		fprintf(fp, "; DEX\n");

	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x88 == dwOpcode)
		DecSetZeroSign("cl");		// Decrement & do Y
	else
	if (0xca == dwOpcode)
		DecSetZeroSign("bl");		// Decrement & do X
	else
		assert(0);

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// DeaIna Handler

static void DeaInaHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	if (0x3a == dwOpcode)
		fprintf(fp, "; DEA\n");
	else
		fprintf(fp, "; INA\n");

	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x3a == dwOpcode)
		DecSetZeroSign("al");		// Decrement
	else
	if (0x1a == dwOpcode)
		IncSetZeroSign("al");		// Decrement
	else
		assert(0);

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// INC Handler

static void IncxyHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	if (0xc8 == dwOpcode)
		fprintf(fp, "; INY\n");
	else
		fprintf(fp, "; INX\n");

	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xc8 == dwOpcode)
		IncSetZeroSign("cl");		// Increment & do Y
	else
	if (0xe8 == dwOpcode)
		IncSetZeroSign("bl");		// Increment & do X
	else
		assert(0);

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// INC Handler

static void IncHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; INC\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xee == dwOpcode || 0xfe == dwOpcode)
	{
		if (0xee == dwOpcode)
			Absolute();
		else
			AbsoluteX();
		fprintf(fp, "		push	edx	; Save this for later\n");
		ReadMemoryByte("dl", "dx");
		fprintf(fp, "		mov	bh, dl	; Save the data we just got\n");
	}
	else
	if (0xe6 == dwOpcode || 0xf6 == dwOpcode)
	{
		if (0xe6 == dwOpcode)
			ZeroPage();
		else
			ZeroPageX();

		if (FALSE == bZeroDirect)
		{
			fprintf(fp, "		push	edx	; Save this for later\n");
			ReadMemoryByte("dl", "dx");
			fprintf(fp, "		mov	bh, dl	; Save the data we just got\n");
		}
	}
	else
		assert(0);

	// Handle the increment

	fprintf(fp, "		mov	ch, ah	; Save flags\n");
	fprintf(fp, "		and	ch, 03fh	; No sign or zero flags\n");

	if (((0xe6 == dwOpcode) || (0xf6 == dwOpcode)) && (bZeroDirect))
		fprintf(fp, "		inc	byte [edx+ebp]	; Increment our zero page stuff\n");
	else
		fprintf(fp, "		inc	bh		; Increment!\n");

	fprintf(fp, "		lahf\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign &  zero flags\n");
	fprintf(fp, "		or	ah, ch	; Merge the two flags together\n");

	if ( (0xee == dwOpcode || 0xfe == dwOpcode) ||
		  (((0xe6 == dwOpcode) || (0xf6 == dwOpcode)) && (FALSE == bZeroDirect)) )
	{
		fprintf(fp, "		pop	edx	; Restore our address\n");
		WriteMemoryByte("bh", "dx");
	}

	fprintf(fp, "		xor	bh, bh	; Zero this so we don't totally screw things up\n");
	fprintf(fp, "		xor	ch, ch	; Zero this as well\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// DEC Handler

static void DecHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; DEC\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xce == dwOpcode || 0xde == dwOpcode)
	{
		if (0xce == dwOpcode)
			Absolute();
		else
			AbsoluteX();

		fprintf(fp, "		push	edx	; Save this for later\n");
		ReadMemoryByte("dl", "dx");
		fprintf(fp, "		mov	bh, dl	; Save the data we just got\n");
	}
	else
	if (0xc6 == dwOpcode || 0xd6 == dwOpcode)
	{
		if (0xc6 == dwOpcode)
			ZeroPage();
		else
			ZeroPageX();

		if (FALSE == bZeroDirect)
		{
			fprintf(fp, "		push	edx	; Save this for later\n");
			ReadMemoryByte("dl", "dx");
			fprintf(fp, "		mov	bh, dl	; Save the data we just got\n");
		}
	}
	else
		assert(0);

	// Handle the increment

	fprintf(fp, "		mov	ch, ah	; Save flags\n");
	fprintf(fp, "		and	ch, 03fh	; No sign or zero flags\n");

	if (((0xc6 == dwOpcode) || (0xd6 == dwOpcode)) && (bZeroDirect))
		fprintf(fp, "		dec	byte [edx+ebp]	; Increment our zero page stuff\n");
	else
		fprintf(fp, "		dec	bh		; Decrement!\n");

	fprintf(fp, "		lahf\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign &  zero flags\n");
	fprintf(fp, "		or	ah, ch	; Merge the two flags together\n");

	if ( (0xce == dwOpcode || 0xde == dwOpcode) ||
		  (((0xc6 == dwOpcode) || (0xd6 == dwOpcode)) && (FALSE == bZeroDirect)) )
	{
		fprintf(fp, "		pop	edx	; Restore our address\n");
		WriteMemoryByte("bh", "dx");
	}

	fprintf(fp, "		xor	bh, bh	; Zero this so we don't totally screw things up\n");
	fprintf(fp, "		xor	ch, ch	; Zero this as well\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// AND Handler

static void AndHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; AND\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x2d == dwOpcode)
		Absolute();
	else
	if (0x25 == dwOpcode)
		ZeroPage();
	else
	if (0x29 == dwOpcode)
		Immediate("dl");
	else
	if (0x3d == dwOpcode)
		AbsoluteX();
	else
	if (0x39 == dwOpcode)
		AbsoluteY();
	else
	if (0x21 == dwOpcode)
		IndirectX();
	else
	if (0x31 == dwOpcode)
		IndirectY();
	else
	if (0x32 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0x35 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	if ((bZeroDirect) && ((0x25 == dwOpcode) || (0x35 == dwOpcode) || (0x32 == dwOpcode)))
		fprintf(fp, "		and	al, [ebp+edx]	; And it!\n");
	else
	{
		if (0x29 != dwOpcode)
			ReadMemoryByte("dl", "dx");
		fprintf(fp, "		and	al, dl	; And it\n");
	}

	fprintf(fp, "		mov	bh, ah	; Save flags for later\n");
	fprintf(fp, "		lahf			; Get the flags\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign and zero flag\n");
	fprintf(fp, "		and	bh, 03fh	; Kill sign and zero flag\n");
	fprintf(fp, "		or	ah, bh	; Get our original (other) flags back\n");
	fprintf(fp, "		xor	bh, bh	; Kill it so we don't screw X up for later\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// ASL Handler

static void AslHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Asl\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x0a == dwOpcode)
	{
		fprintf(fp, "		sahf		; Restore flags\n");
		fprintf(fp, "		mov	dl, ah	; Store our original flags\n");
		fprintf(fp, "		shl	al, 1	; Shift left by 1\n");
		fprintf(fp, "		lahf	; Load the flags back in\n");
		fprintf(fp, "		and	dl, 03eh	; No carry, zero, or sign\n");
		fprintf(fp, "		and	ah, 0c1h	; Only carry, zero and sign\n");
		fprintf(fp, "		or	ah, dl		; Or it into our flags\n");
	}
	else
	if (0x0e == dwOpcode)	// Absolute
		Absolute();
	else
	if (0x06 == dwOpcode)	// Zero page
		ZeroPage();
	else
	if (0x1e == dwOpcode)	// Absolute X
		AbsoluteX();
	else
	if (0x16 == dwOpcode)	// Zero page X
		ZeroPageX();
	else
		assert(0);

	// We have the address. Now fetch the info!

	if (0x0a != dwOpcode)
	{
		// Read the data

		if (((0x16 == dwOpcode) || (0x06 == dwOpcode)) && bZeroDirect)
			fprintf(fp, "		mov	bh, [ebp+edx]	; Get our zero page stuff\n");
		else
		{
			fprintf(fp, "		push	edx	; Save our address\n");
			ReadMemoryByte("bh", "dx");
			fprintf(fp, "		pop	edx	; Restore our address\n");
		}

		// Process the data

		fprintf(fp, "		sahf		; Restore flags\n");
		fprintf(fp, "		mov	ch, ah	; Store our original flags\n");
		fprintf(fp, "		shl	bh, 1	; Shift left by 1\n");
		fprintf(fp, "		lahf	; Load the flags back in\n");
		fprintf(fp, "		and	ch, 03eh	; No carry, zero, or sign\n");
		fprintf(fp, "		and	ah, 0c1h	; Only carry, zero and sign\n");
		fprintf(fp, "		or	ah, ch		; Or it into our flags\n");
		fprintf(fp, "		xor	ch, ch	; Clear it!\n");

		// Write the data back

		if (((0x16 == dwOpcode) || (0x06 == dwOpcode)) && bZeroDirect)
			fprintf(fp, "		mov	[ebp+edx], bh	; Set our zero page byte\n");
		else
			WriteMemoryByte("bh", "dx");
		fprintf(fp, "		xor	bh, bh	; Prevent us from being hosed later\n");
	}

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// LSR Handler

static void LsrHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Lsr\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x4a == dwOpcode)
	{
		fprintf(fp, "		sahf		; Restore flags\n");
		fprintf(fp, "		mov	dl, ah	; Store our original flags\n");
		fprintf(fp, "		shr	al, 1	; Shift right by 1\n");
		fprintf(fp, "		lahf	; Load the flags back in\n");
		fprintf(fp, "		and	dl, 03eh	; No carry, zero, or sign\n");
		fprintf(fp, "		and	ah, 0c1h	; Only carry, zero and sign\n");
		fprintf(fp, "		or	ah, dl		; Or it into our flags\n");
	}
	else
	if (0x4e == dwOpcode)	// Absolute
		Absolute();
	else
	if (0x46 == dwOpcode)	// Zero page
		ZeroPage();
	else
	if (0x5e == dwOpcode)	// Absolute X
		AbsoluteX();
	else
	if (0x56 == dwOpcode)	// Zero page X
		ZeroPageX();
	else
		assert(0);

	// We have the address. Now fetch the info!

	if (0x4a != dwOpcode)
	{
		// Read the data

		fprintf(fp, "		push	edx		; Save our address away\n");

		if (((0x56 == dwOpcode) || (0x46 == dwOpcode)) && bZeroDirect)
			fprintf(fp, "		mov	bh, [ebp+edx]	; Get our zero page stuff\n");
		else
			ReadMemoryByte("bh", "dx");

		// Process the data

		fprintf(fp, "		sahf		; Restore flags\n");
		fprintf(fp, "		mov	ch, ah	; Store our original flags\n");
		fprintf(fp, "		shr	bh, 1	; Shift right by 1\n");
		fprintf(fp, "		lahf	; Load the flags back in\n");
		fprintf(fp, "		and	ch, 03eh	; No carry, zero, or sign\n");
		fprintf(fp, "		and	ah, 0c1h	; Only carry, zero and sign\n");
		fprintf(fp, "		or	ah, ch		; Or it into our flags\n");
		fprintf(fp, "		xor	ch, ch	; Clear it!\n");

		// Write the data back

		fprintf(fp, "		pop	edx	; Restore our address\n");
		if (((0x56 == dwOpcode) || (0x46 == dwOpcode)) && bZeroDirect)
			fprintf(fp, "		mov	[ebp+edx], bh	; Set our zero page byte\n");
		else
			WriteMemoryByte("bh", "dx");
		fprintf(fp, "		xor	bh, bh	; Zero the upper part so we don't host X!\n");
	}

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// ORA Handler

static void OraHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Ora\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x0d == dwOpcode)
		Absolute();
	else
	if (0x05 == dwOpcode)
		ZeroPage();
	else
	if (0x09 == dwOpcode)
		Immediate("dl");
	else
	if (0x1d == dwOpcode)
		AbsoluteX();
	else
	if (0x19 == dwOpcode)
		AbsoluteY();
	else
	if (0x01 == dwOpcode)
		IndirectX();
	else
	if (0x11 == dwOpcode)
		IndirectY();
	else
	if (0x12 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0x15 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	// Address is now in DX to read

	if (0x09 != dwOpcode)
	{
		if ((0x05 == dwOpcode || 0x15 == dwOpcode || 0x12 == dwOpcode) && (bZeroDirect))
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// Let's do the OR with A, shall we?

	fprintf(fp, "		mov	dh, ah	; Get the flags\n");
	fprintf(fp, "		or	al, dl		; OR In our value\n");
	fprintf(fp, "		lahf			; Get the flag settings\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign and zero flag\n");
	fprintf(fp, "		and	dh, 03fh	; Clear sign & zero flags\n");
	fprintf(fp, "		or	ah, dh		; Merge the affected flags together\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// EOR Handler

static void EorHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Eor\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x4d == dwOpcode)
		Absolute();
	else
	if (0x45 == dwOpcode)
		ZeroPage();
	else
	if (0x49 == dwOpcode)
		Immediate("dl");
	else
	if (0x5d == dwOpcode)
		AbsoluteX();
	else
	if (0x59 == dwOpcode)
		AbsoluteY();
	else
	if (0x41 == dwOpcode)
		IndirectX();
	else
	if (0x51 == dwOpcode)
		IndirectY();
	else
	if (0x52 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0x55 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	// Address is now in DX to read

	if (0x49 != dwOpcode)
	{
		if ((0x45 == dwOpcode || 0x55 == dwOpcode || 0x52 == dwOpcode) && (bZeroDirect))
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// Let's do the XOR with A, shall we?

	fprintf(fp, "		mov	dh, ah	; Get the flags\n");
	fprintf(fp, "		xor	al, dl		; XOR In our value\n");
	fprintf(fp, "		lahf			; Get the flag settings\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign and zero flag\n");
	fprintf(fp, "		and	dh, 03fh	; Clear sign & zero flags\n");
	fprintf(fp, "		or	ah, dh		; Merge the affected flags together\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// STA Handler

static void StaHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; STA\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x9d == dwOpcode)
		AbsoluteX();
	else
	if (0x99 == dwOpcode)
		AbsoluteY();
	else
	if (0x8d == dwOpcode)
		Absolute();
	else
	if (0x85 == dwOpcode)
		ZeroPage();
	else
	if (0x81 == dwOpcode)
		IndirectX();
	else
	if (0x91 == dwOpcode)
		IndirectY();
	else
	if (0x95 == dwOpcode)
		ZeroPageX();
	else
	  if (0x92 == dwOpcode)
	    ZeroPageIndirect();
	else
		assert(0);

	if ((0x85 == dwOpcode || 0x95 == dwOpcode || 0x92 == dwOpcode) && bZeroDirect)
		fprintf(fp, "		mov	[ebp+edx], al	; Store A\n");
	else
		WriteMemoryByte("al", "dx");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// STX Handler

static void StxHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; STX\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x8e == dwOpcode)
		Absolute();
	else
	if (0x86 == dwOpcode)
		ZeroPage();
	else
	if (0x96 == dwOpcode)
		ZeroPageY();
	else
		assert(0);

	if ((0x86 == dwOpcode || 0x96 == dwOpcode) && bZeroDirect)
		fprintf(fp, "		mov	[ebp+edx], bl	; Store X\n");
	else
		WriteMemoryByte("bl", "dx");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// STY Handler

static void StyHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; STY\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x8c == dwOpcode)
		Absolute();
	else
	if (0x84 == dwOpcode)
		ZeroPage();
	else
	if (0x94 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	if ((0x86 == dwOpcode || 0x96 == dwOpcode) && bZeroDirect)
		fprintf(fp, "		mov	[ebp+edx], cl	; Store Y\n");
	else
		WriteMemoryByte("cl", "dx");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// LDA Handler

static void LdaHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; LDA\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xa9 == dwOpcode)
		Immediate("al");
	else
	if (0xad == dwOpcode)
		Absolute();
	else
	if (0xa5 == dwOpcode)
		ZeroPage();
	else
	if (0xbd == dwOpcode)
		AbsoluteX();
	else
	if (0xb9 == dwOpcode)
		AbsoluteY();
	else
	if (0xa1 == dwOpcode)
		IndirectX();
	else
	if (0xb1 == dwOpcode)
		IndirectY();
	else
	if (0xb2 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0xb5 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	if (0xa9 != dwOpcode)
	{
		if (bZeroDirect && (0xb5 == dwOpcode || 0xa5 == dwOpcode || 0xb2 == dwOpcode))
			fprintf(fp, "		mov	al, [ebp+edx]	; Get our zero page byte\n");
		else
			ReadMemoryByte("al", "dx");
	}

	SetZeroSign("al");			// Set flags according to A

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// TXS

static void TxsHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TXS\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp, "		mov	[_%ss], bl	; X -> S\n", cpubasename);

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// TSX

static void TsxHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TSX\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp, "		mov	bl, [_%ss]	; S -> X\n", cpubasename);

	SetZeroSign("bl");			// Set flags according to X
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// TAX

static void TaxHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TAX\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp,	"		mov	bl, al	; X = A\n");

	SetZeroSign("bl");			// Set flags according to X
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// TXA

static void TxaHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TXA\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp,	"		mov	al, bl	; A = X\n");

	SetZeroSign("al");			// Set flags according to A
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// TAY

static void TayHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TAY\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp,	"		mov	cl, al	; Y = A\n");

	SetZeroSign("cl");			// Set flags according to Y
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// TYA

static void TyaHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TYA\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp,	"		mov	al, cl	; A = Y\n");

	SetZeroSign("al");			// Set flags according to A
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// Branch handler

static void BranchHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; Branch\n");
	fprintf(fp, ";\n");

	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	// Put test case here

	if (0xd0 == dwOpcode)	// BNE
	{
		fprintf(fp, "		test	ah, 40h	; Are we non-zero?\n");
		fprintf(fp, "		jz	takeJump%.2x	; Do it!\n", dwOpcode);
	}
	else
	if (0x30 == dwOpcode)	// BMI
	{
		fprintf(fp, "		test	ah, 80h	; Are we minus?\n");
		fprintf(fp, "		jnz	takeJump%.2x	; Do it!\n", dwOpcode);
	}
	else
	if (0xb0 == dwOpcode)	// BCS
	{
		fprintf(fp, "		test	ah, 1h	; Is carry set?\n");
		fprintf(fp, "		jnz	takeJump%.2x	; Do it!\n", dwOpcode);
	}
	else
	if (0x10 == dwOpcode)	// BPL
	{
		fprintf(fp, "		test	ah, 80h	; Are we plus?\n");
		fprintf(fp, "		jz		takeJump%.2x ; Do it!\n", dwOpcode);
	}
	else
	if (0x70 == dwOpcode)	// BVS
	{
		fprintf(fp, "		test	ah, 10h	; Overflow set?\n");
		fprintf(fp, "		jnz	takeJump%.2x ; Do it!\n", dwOpcode);
	}
	else
	if (0x50 == dwOpcode)	// BVC
	{
		fprintf(fp, "		test	ah, 10h	; Overflow not set?\n");
		fprintf(fp, "		jz	takeJump%.2x ; Do it!\n", dwOpcode);
	}
	else
	if (0xf0 == dwOpcode)	// BEQ
	{
		fprintf(fp, "		test	ah, 40h	; Non-zero set?\n");
		fprintf(fp, "		jnz	takeJump%.2x ; Do it!\n", dwOpcode);
	}
	else
	if (0x90 == dwOpcode)	// BCC
	{
		fprintf(fp, "		test	ah, 1h	; Carry not set?\n");
		fprintf(fp, "		jz		takeJump%.2x ; Do it!\n", dwOpcode);
	}
	else
		assert(0);

	fprintf(fp, "		inc	esi	; Skip past the offset\n");
	FetchAndExec(bTimingTable[dwOpcode] - 1);

	fprintf(fp, "takeJump%.2x:\n", dwOpcode);
	FetchInstructionByte();		// Go get our offset just in case

	fprintf(fp, "		movsx	dx, dl\n");

	if (bBankswitch)
	{
		PageToPC();
		fprintf(fp, "		add	si, dx\n");
		fprintf(fp, "		mov	[_%spc], si\n", cpubasename);
		PCToPage();
	}
	else
	{
		fprintf(fp, "		sub	esi, ebp\n");
		fprintf(fp, "		add	si, dx\n");
		fprintf(fp, "		add	esi, ebp\n");
	}

	++dwGlobalLabel;
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// JMP

static void JmpHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; JMP\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	FetchInstructionWord();

	if (0x6c == dwOpcode) {
	  ReadMemoryWord();
	}
	if (0x7c == dwOpcode) {
	  fprintf(fp, "		add	dx, bx	; Add X\n");
	  ReadMemoryWord();
	}

	if (bBankswitch)
	{
		fprintf(fp, "		xor	esi, esi\n");
		fprintf(fp, "		mov	si, dx\n");
		fprintf(fp, "		mov	[_%spc], si\n", cpubasename);
		PCToPage();
	}
	else
	{
		fprintf(fp, "		add	edx, ebp	; Add in our base\n");
		fprintf(fp, "		mov	esi, edx	; Put it here for execution\n");
	}

	++dwGlobalLabel;
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// Brk

static void BrkHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; BRK\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (bBankswitch)
		PageToPC();
	else
		fprintf(fp, "		sub	esi, ebp	 ; Get our real program counter\n");

	fprintf(fp, "		inc	si	; Move to the next position\n");
	fprintf(fp, "		or	[_altFlags], byte 14h	; Indicate a break happened\n");

	FlagsX86to6502();

	fprintf(fp, "		mov	dl, [_%ss]	; Get our stack pointer\n", cpubasename);
	fprintf(fp, "		add	dx, 0ffh		; Stack area is 100-1ffh\n");
	fprintf(fp, "		mov	[edx+ebp], si	; Store our PC\n");
	fprintf(fp, "		dec	dx		; Back up for flag storage\n");

	fprintf(fp, "		mov	[edx+ebp], ah	; Store our flags\n");
	fprintf(fp, "		dec	dx		; Back up for flag storage\n");
	fprintf(fp, "		mov	[_%ss], dl	; Store our new stack area\n", cpubasename);
	fprintf(fp, "		xor	esi, esi	; Zero our program counter\n");
	fprintf(fp, "		mov	si, [ebp+0fffeh]	; Get our break handler\n");

	if (bBankswitch)
	{
		fprintf(fp, "		mov	[_%spc], si\n", cpubasename);
		PCToPage();
	}
	else
		fprintf(fp, "		add	esi, ebp	; Add our base pointer back in\n");

	++dwGlobalLabel;
	Flags6502toX86();
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// JSR

static void JsrHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; JSR\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	FetchInstructionWord();

	if (bBankswitch)
		PageToPC();
	else
	{
		fprintf(fp, "		sub	esi, ebp	 ; Get our real program counter\n");
	}

	fprintf(fp, "		dec	si		; Our offset to return to\n");
	fprintf(fp, "		sub	[_%ss], byte 2	; Back up 2 byte for stack push\n", cpubasename);
	fprintf(fp, "		mov	di, word [_%ss]	; Our stack area\n", cpubasename);
	fprintf(fp, "		and	edi, 0ffh	; Only the lower byte matters\n");
	fprintf(fp, "		add	edi, 101h	; Make sure it's on the stack page\n");
	fprintf(fp, "		mov	[edi+ebp], si	; Store our return address\n");

	if (bBankswitch)
	{
		fprintf(fp, "		xor	esi, esi\n");
		fprintf(fp, "		mov	si, dx	; Get our address\n");
		fprintf(fp, "		mov	[_%spc], si	; Store our new PC\n", cpubasename);
		PCToPage();
	}
	else
	{
		fprintf(fp, "		add	edx, ebp	; Our new address\n");
		fprintf(fp, "		mov	esi, edx	; Put it in here for the fetch\n");
	}

	dwGlobalLabel++;
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// RTS

static void RtsHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; RTS\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp, "		xor	esi, esi	; Zero ESI for later\n");
	fprintf(fp, "		mov	dl, [_%ss]	; Get our stack\n", cpubasename);
	fprintf(fp, "		add	[_%ss], byte 2	; Pop off a word\n", cpubasename);
	fprintf(fp, "		inc	dl	; Increment our stack page\n");
	fprintf(fp, "		inc	dh	; Our stack page\n");
	fprintf(fp, "		mov	si, [ebp+edx]	; Get our stack area\n");
	fprintf(fp, "		inc	si	; Increment!\n");

	if (bBankswitch)
	{
		fprintf(fp, "		mov	[_%spc], si\n", cpubasename);
		PCToPage();
	}
	else
		fprintf(fp, "		add	esi, ebp	; Add in our base address\n");

	++dwGlobalLabel;
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// CMP Handler

static void CmpHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; CMP\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xcd == dwOpcode)
		Absolute();
	else
	if (0xc5 == dwOpcode)
		ZeroPage();
	else
	if (0xc9 == dwOpcode)
		Immediate("dl");
	else
	if (0xdd == dwOpcode)
		AbsoluteX();
	else
	if (0xd9 == dwOpcode)
		AbsoluteY();
	else
	if (0xc1 == dwOpcode)
		IndirectX();
	else
	if (0xd1 == dwOpcode)
		IndirectY();
	else
	if (0xd2 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0xd5 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	// Now that we have the address of what we want in DX, let's go fetch the
	// data

	if (0xc9 != dwOpcode)	// Make sure it's not immediate
	{
		if (((0xc5 == dwOpcode) || (0xd5 == dwOpcode) || 0xd2 == dwOpcode) && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// We have our value in DL. Now do the work!

	fprintf(fp, "		mov	dh, ah	; Get our flags\n");
	fprintf(fp, "		cmp	al, dl	; Compare!\n");
	fprintf(fp, "		cmc			; Compliment carry flag\n");
	fprintf(fp, "		lahf\n");
	fprintf(fp, "		and	ah, 0c1h	; Sign, zero, and carry\n");
	fprintf(fp, "		and	dh, 03eh	; Everything but sign, zero and carry\n");
	fprintf(fp, "		or		ah, dh	; OR In our new flags\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// CPY Handler

static void CpyHandler(UINT16 dwOpcode)
{

	fprintf(fp, ";\n");
	fprintf(fp, "; CPY\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xcc == dwOpcode)
		Absolute();
	else
	if (0xc4 == dwOpcode)
		ZeroPage();
	else
	if (0xc0 == dwOpcode)
		Immediate("dl");
	else
		assert(0);

	// Now that we have the address of what we want in DX, let's go fetch the
	// data

	if (0xc0 != dwOpcode)	// Make sure it's not immediate
	{
		if (0xc4 == dwOpcode && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// We have our value in DL. Now do the work!

	fprintf(fp, "		mov	dh, ah	; Get our flags\n");
	fprintf(fp, "		cmp	cl, dl	; Compare with Y!\n");
	fprintf(fp, "		cmc			; Compliment carry flag\n");
	fprintf(fp, "		lahf\n");
	fprintf(fp, "		and	ah, 0c1h	; Sign, zero, and carry\n");
	fprintf(fp, "		and	dh, 03eh	; Everything but sign, zero and carry\n");
	fprintf(fp, "		or		ah, dh	; OR In our new flags\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

// CPX Handler

static void CpxHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; CPX\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xec == dwOpcode)
		Absolute();
	else
	if (0xe4 == dwOpcode)
		ZeroPage();
	else
	if (0xe0 == dwOpcode)
		Immediate("dl");
	else
		assert(0);

	// Now that we have the address of what we want in DX, let's go fetch the
	// data

	if (0xe0 != dwOpcode)	// Make sure it's not immediate
	{
		if (0xe4 == dwOpcode && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// We have our value in DL. Now do the work!

	fprintf(fp, "		mov	dh, ah	; Get our flags\n");
	fprintf(fp, "		cmp	bl, dl	; Compare with X!\n");
	fprintf(fp, "		cmc			; Compliment carry flag\n");
	fprintf(fp, "		lahf\n");
	fprintf(fp, "		and	ah, 0c1h	; Sign, zero, and carry\n");
	fprintf(fp, "		and	dh, 03eh	; Everything but sign, zero and carry\n");
	fprintf(fp, "		or		ah, dh	; OR In our new flags\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void ClcCldCliClvHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");

	if (0x58 == dwOpcode)
		fprintf(fp, "; CLI\n");
	else
	if (0xd8 == dwOpcode)
		fprintf(fp, "; CLD\n");
	else
	if (0xb8 == dwOpcode)
		fprintf(fp, "; CLV\n");
	else
	if (0x18 == dwOpcode)
		fprintf(fp, "; CLC\n");
	else
	if (0x38 == dwOpcode)
		fprintf(fp, "; SEC\n");
	else
	if (0xf8 == dwOpcode)
		fprintf(fp, "; SED\n");
	else
	if (0x78 == dwOpcode)
		fprintf(fp, "; SEI\n");
	else
		assert(0);

	fprintf(fp, ";\n");

	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x58 == dwOpcode)
	{

		fprintf(fp, "		and	[_altFlags], byte 0fbh	; No interrupts!\n");
		fprintf(fp, "		cmp	[_irqPending], byte 0 ; IRQ pending?\n");
		fprintf(fp, "		je		near notEnabledCli\n");

		if (bBankswitch)
			PageToPC();
		else
			fprintf(fp, "		sub	esi, ebp	 ; Get our real program counter\n");

		fprintf(fp, "		mov	[_%spc], si\n", cpubasename);

		FlagsX86to6502();
		fprintf(fp, "		mov	[_%saf], ax	; Save this\n", cpubasename);

		fprintf(fp, "		push	eax		; Save this - we need it\n");
		fprintf(fp, "		call	_%sint	; Go do an interrupt\n", cpubasename);
		fprintf(fp, "		pop	eax		; Restore this - we need it!\n");

		fprintf(fp, "		mov	si, [_%spc]	; Get our program counter\n", cpubasename);
		fprintf(fp, "		and	esi, 0ffffh	; Only the lower 16 bits\n");

		if (bBankswitch)
		{
			fprintf(fp, "		mov	[_%spc], si\n", cpubasename);
			PCToPage();
		}
		else
			fprintf(fp, "		add	esi, ebp ; So it properly points to the code\n");

		fprintf(fp, "		mov	ax, [_%saf] ; Restore this\n", cpubasename);
		Flags6502toX86();

		fprintf(fp, "notEnabledCli:\n");
	}
	else
	if (0xd8 == dwOpcode)
		fprintf(fp, "		and	[_altFlags], byte 0f7h	; Binary mode\n");
	else
	if (0xb8 == dwOpcode)
		fprintf(fp, "		and	ah, 0efh	; Clear out overflow\n");
	else
	if (0x18 == dwOpcode)
		fprintf(fp, "		and	ah, 0feh	; No carry\n");
	else
	if (0x38 == dwOpcode)
		fprintf(fp, "		or	ah, 01h	; Carry!\n");
	else
	if (0xf8 == dwOpcode)
		fprintf(fp, "		or		[_altFlags], byte 08h	; Decimal mode\n");
	else
	if (0x78 == dwOpcode)
		fprintf(fp, "		or		[_altFlags], byte 04h	; Interrupts!\n");
	else
		assert(0);

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void AdcHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; ADC\n");
	fprintf(fp, ";\n");

	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x6d == dwOpcode)
		Absolute();
	else
	if (0x65 == dwOpcode)
		ZeroPage();
	else
	if (0x69 == dwOpcode)
		Immediate("dl");
	else
	if (0x7d == dwOpcode)
		AbsoluteX();
	else
	if (0x79 == dwOpcode)
		AbsoluteY();
	else
	if (0x61 == dwOpcode)
		IndirectX();
	else
	if (0x71 == dwOpcode)
		IndirectY();
	else
	if (0x72 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0x75 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	// We've got our address (or byte if immediate) in DL now

	if (0x69 != dwOpcode)	// Make sure it's not immediate
	{
		if (((0x65 == dwOpcode) || (0x75 == dwOpcode) || 0x72 == dwOpcode) && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	if (FALSE == bNoDecimal)
	{
		fprintf(fp, "		test	[_altFlags], byte 08h ; Are we in decimal mode?\n");
		fprintf(fp, "		je		binaryMode%ld	; It's binary mode\n", dwAnotherLabel);
		fprintf(fp, "		jmp	decimalMode%ld		; Yup - go handle dec mode\n", dwAnotherLabel);
		fprintf(fp, "binaryMode%ld:\n", dwAnotherLabel);
	}

	// Now let's ADC, man!

	fprintf(fp, "		sahf		; Restore our flags for the adc\n");
	fprintf(fp, "		adc	al, dl	; Add in our value\n");
	fprintf(fp, "		o16 pushf	; Push our flags (and overflow)\n");
	fprintf(fp, "		and	ah, 02eh	; No carry, overflow, zero or sign\n");
	fprintf(fp, "		pop	dx	; Restore our flags into DX\n");
	fprintf(fp, "		shl	dh, 1	; Shift overflow into position\n");
	fprintf(fp, "		and	dh, 10h	; Only the overflow\n");
	fprintf(fp, "		and	dl, 0c1h	; Only carry, sign, and zero\n");
	fprintf(fp, "		or		ah, dl	; OR In our new flags\n");
	fprintf(fp, "		or		ah, dh	; OR In overflow\n");

	FetchAndExec(bTimingTable[dwOpcode]);

	if (FALSE == bNoDecimal)
	{
		fprintf(fp, "decimalMode%ld:\n", dwAnotherLabel);

// On the way in:
// AH=x86 Flags (0x01 = Carry)
// AL=Accumulator value
// DL=Value to add to

		fprintf(fp, "		xor	di, di	; Zero DI for later\n");
		fprintf(fp, "		sahf\n");
		fprintf(fp, "		adc	di, 0		; Increment if carry is set\n");
		fprintf(fp, "		and	ah, 03ch	; Knock out carry, zero, sign, and overflow\n");
		fprintf(fp, "		mov	[_%sx], bl	; Save X\n", cpubasename);
		fprintf(fp, "		mov	[_%sy], cl	; Save Y\n", cpubasename);

		fprintf(fp, "		mov	bl, al	; Get Accumulator\n");
		fprintf(fp, "		mov	bh, dl	; Original value\n");
		fprintf(fp, "		mov	cx, bx	; Put it here for later\n");
		fprintf(fp, "		and	bx, 0f0fh	; Only the nibbles\n");
		fprintf(fp, "		add	bl, bh	; Add it to the lower value\n");
		fprintf(fp, "		add	bx, di	; Add in our carry\n");

		fprintf(fp, "		shr	cx, 4		; Upper nibbles only\n");
		fprintf(fp, "		and	cx, 0f0fh	; Only the lower nibbles now\n");
		fprintf(fp, "		add	cl, ch	; Add in the original value\n");
		fprintf(fp, "		mov	bh, cl	; Put our upper nibble in BH\n");
		fprintf(fp, "		xor	cx, cx	; Zero the upper part\n");

		fprintf(fp, "		cmp	bl, 9		; Digit overflow?\n");
		fprintf(fp, "		jbe	notOverflowed%ld\n", dwAnotherLabel);
		fprintf(fp, "		inc	bh			; Increment - we've overflowed\n");
		fprintf(fp, "		add	bl, 6		; Fix the lower nibble\n");
		fprintf(fp, "notOverflowed%ld:\n", dwAnotherLabel);

		fprintf(fp, "		mov	cl, al	; Get the accumulator\n");
		fprintf(fp, "		xor	cl, dl	; XOR It with the original value\n");
		fprintf(fp, "		not	cl			; Invert & add 1\n");

		fprintf(fp, "		mov	ch, bh	; Get our high BCD\n");
		fprintf(fp, "		shl	ch, 4		; Move into position\n");
		fprintf(fp, "		and	ch, cl	; And 'em together\n");
		fprintf(fp, "		or		ch, ch	; See if we've overflowed\n");
		fprintf(fp, "		jns	noOv%ld\n", dwAnotherLabel);
		fprintf(fp, "		or		ah, 040h	; Set overflow\n");
		fprintf(fp, "noOv%ld:\n", dwAnotherLabel);

		fprintf(fp, "		cmp	bh, 9		; Greater than 9?\n");
		fprintf(fp, "		jbe	noOvTwo%ld\n", dwAnotherLabel);
		fprintf(fp, "		add	bh, 6		; Digit fixup\n");
		fprintf(fp, "noOvTwo%ld:\n", dwAnotherLabel);

		fprintf(fp, "		mov	al, bh	; Get most significant nibble\n");
		fprintf(fp, "		shl	al, 4		; Put it into position\n");
		fprintf(fp, "		and	bl, 0fh	; Only the lower nibble matters now\n");
		fprintf(fp, "		or		al, bl	; Put it in the accumulator\n");

		fprintf(fp, "		test	bh, 0f0h	; Carry?\n");
		fprintf(fp, "		jz		noCarry%ld\n", dwAnotherLabel);
		fprintf(fp, "		or		ah, 01h	; Set carry\n");
		fprintf(fp, "noCarry%ld:\n", dwAnotherLabel);

		SetZeroSign("al");

		fprintf(fp, "		xor	bx, bx	; Zero\n");
		fprintf(fp, "		xor	cx, cx\n");
		fprintf(fp, "		mov	bl, [_%sx]	; X!\n", cpubasename);
		fprintf(fp, "		mov	cl, [_%sy]	; Y!\n", cpubasename);

		FetchAndExec(bTimingTable[dwOpcode]);
	}

	dwAnotherLabel++;
	ProcEnd(string);
}

static void SbcHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; SBC\n");
	fprintf(fp, ";\n");

	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0xed == dwOpcode)
		Absolute();
	else
	if (0xe5 == dwOpcode)
		ZeroPage();
	else
	if (0xe9 == dwOpcode)
		Immediate("dl");
	else
	if (0xfd == dwOpcode)
		AbsoluteX();
	else
	if (0xf9 == dwOpcode)
		AbsoluteY();
	else
	if (0xe1 == dwOpcode)
		IndirectX();
	else
	if (0xf1 == dwOpcode)
		IndirectY();
	else
	if (0xf2 == dwOpcode)
	  ZeroPageIndirect();
	else
	if (0xf5 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	// We've got our address (or byte if immediate) in DL now

	if (0xe9 != dwOpcode)	// Make sure it's not immediate
	{
		if (((0xe5 == dwOpcode) || (0xf5 == dwOpcode) || 0xf2 == dwOpcode) && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page data\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	if (FALSE == bNoDecimal)
	{
		fprintf(fp, "		test	[_altFlags], byte 08h ; Are we in decimal mode?\n");
		fprintf(fp, "		jz		binaryMode%ld	; It's binary mode\n", dwAnotherLabel);
		fprintf(fp, "		jmp	decimalMode%ld		; Yup - go handle dec mode\n", dwAnotherLabel);
		fprintf(fp, "binaryMode%ld:\n", dwAnotherLabel);
	}

	// Now let's SBC, man!

	fprintf(fp, "		sahf		; Restore our flags for the adc\n");
	fprintf(fp, "		cmc\n");
	fprintf(fp, "		sbb	al, dl	; Subtract our value\n");
	fprintf(fp, "		cmc\n");
	fprintf(fp, "		o16 pushf	; Push our flags (and overflow)\n");
	fprintf(fp, "		and	ah, 02eh	; No carry, overflow, zero or sign\n");
	fprintf(fp, "		pop	dx	; Restore our flags into DX\n");
	fprintf(fp, "		shl	dh, 1	; Shift overflow into position\n");
	fprintf(fp, "		and	dh, 10h	; Only the overflow\n");
	fprintf(fp, "		and	dl, 0c1h	; Only carry, sign, and zero\n");
	fprintf(fp, "		or		ah, dl	; OR In our new flags\n");
	fprintf(fp, "		or		ah, dh	; OR In overflow\n");

	FetchAndExec(bTimingTable[dwOpcode]);

	if (FALSE == bNoDecimal)
	{
		fprintf(fp, "decimalMode%ld:\n", dwAnotherLabel);

		fprintf(fp, "		xor	di, di	; Zero our carry flag surrogate\n");
		fprintf(fp, "		xor	ah, 01h	; Toggle carry - intentional\n");
		fprintf(fp, "		sahf\n");
		fprintf(fp, "		adc	di, 0	; Make 1 if carry is set\n");
		fprintf(fp, "		xor	ah, ah	; Clear our flag register\n");

		fprintf(fp, "		mov	[_%sx], bl	; Save X\n", cpubasename);
		fprintf(fp, "		mov	[_%sy], cl	; Save Y\n", cpubasename);

		fprintf(fp, "		xor	dh, dh		; Just in case we want to add with it later\n");
		fprintf(fp, "		mov	cx, ax		; This is our sum\n");
		fprintf(fp, "		sub	cx, dx		; Subtract our value\n");
		fprintf(fp, "		sub	cx, di		; And our carry status\n");

		fprintf(fp, "		mov	bl, al		; Get accumulator\n");
		fprintf(fp, "		xor	bl, dl		; XOR With our value\n");
		fprintf(fp, "		mov	bh, al		; Get accumulator\n");
		fprintf(fp, "		xor	bh, cl		; XOR With our sum\n");
		fprintf(fp, "		and	bl, bh		; See if we overflow\n");
		fprintf(fp,	"		and	bl, 80h		; Only the top bit\n");
		fprintf(fp, "		jns	noOverflow%ld ; No overflow\n", dwAnotherLabel);
		fprintf(fp, "		or		ah, 40h		; Indicate an overflow\n");
		fprintf(fp, "noOverflow%ld:\n", dwAnotherLabel);

		fprintf(fp, "		mov	bl, al		; Get our low value\n");
		fprintf(fp, "		mov	bh, dl		; Original value\n");
		fprintf(fp, "		and	bx, 0f0fh	; Only the lower nibbles\n");
		fprintf(fp, "		sub	bl, bh		; Subtract\n");
		fprintf(fp, "		xor	bh, bh		; Zero this\n");
		fprintf(fp, "		sub	bx, di		; Subtract our !Carry flag\n");

		fprintf(fp, "		test	bl, 0f0h		; Did we underflow?\n");
		fprintf(fp, "		jz		noUnderFlow%ld\n", dwAnotherLabel);
		fprintf(fp, "		sub	bl, 6		; BCD Fixup\n");
		fprintf(fp, "noUnderFlow%ld:\n", dwAnotherLabel);

		fprintf(fp, "		shr	al, 4		; Upper BCD\n");
		fprintf(fp, "		shr	dl, 4		; Upper BCD for the value\n");
		fprintf(fp, "		mov	bh, al	; A\n");
		fprintf(fp, "		sub	bh, dl	; Subtract our bigger BCD\n");

		fprintf(fp, "		or		bl, bl	; Set flags\n");
		fprintf(fp, "		jns	noHighNeg%ld\n", dwAnotherLabel);
		fprintf(fp, "		dec	bh			; Borrow\n");
		fprintf(fp, "noHighNeg%ld:\n", dwAnotherLabel);

		fprintf(fp, "		test	bh, 0f0h	; Upper nibble? Underflow?\n");
		fprintf(fp, "		jz		noUpperUnderflow%ld\n", dwAnotherLabel);
		fprintf(fp,	"		sub	bh, 6		; BCD Fixup\n");
		fprintf(fp, "noUpperUnderflow%ld:\n", dwAnotherLabel);

		fprintf(fp, "		or		ch, ch	; Did we underflow on our sum?\n");
		fprintf(fp, "		jnz	noUnderflow%ld ; Nope!\n", dwAnotherLabel);
		fprintf(fp, "		or		ah, 01h	; Set carry\n");
		fprintf(fp, "noUnderflow%ld:\n", dwAnotherLabel);

		fprintf(fp, "		and	bl, 0fh	; Only the lower nibble\n");
		fprintf(fp, "		mov	al, bl	; Low part\n");
		fprintf(fp, "		shl	bh, 4		; Move to upper BCD\n");
		fprintf(fp, "		or		al, bh	; OR It in!\n");

		SetZeroSign("al");

		fprintf(fp, "		xor	bx, bx	; Zero\n");
		fprintf(fp, "		xor	cx, cx\n");
		fprintf(fp, "		mov	bl, [_%sx]	; X!\n", cpubasename);
		fprintf(fp, "		mov	cl, [_%sy]	; Y!\n", cpubasename);

		FetchAndExec(bTimingTable[dwOpcode]);
	}

	dwAnotherLabel++;
	ProcEnd(string);
}

static void RolHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; ROL\n");
	fprintf(fp, ";\n");

	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x2e == dwOpcode)
		Absolute();
	else
	if (0x26 == dwOpcode)
		ZeroPage();
	else
	if (0x3e == dwOpcode)
		AbsoluteX();
	else
	if (0x36 == dwOpcode)
		ZeroPageX();

	// Now that we've got the address (or whatever) let's fetch it!

	if (0x2a != dwOpcode)	// Make sure it's not the accumulator
	{
		fprintf(fp, "		push	edx		; Save our address\n");
		if (((0x36 == dwOpcode) || (0x26 == dwOpcode)) && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page byte\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// We've got the data in DL (or in AL if accumulator shift)

	fprintf(fp, "		mov	dh, ah	; Save off our original flags\n");
	fprintf(fp, "		and	dh, 3eh	; No carry, zero, or sign\n");
	fprintf(fp, "		sahf		; Restore flags\n");

	if (0x2a == dwOpcode)
		fprintf(fp, "		rcl	al, 1	; Through carry rotate\n");
	else
		fprintf(fp, "		rcl	dl, 1	; Through carry rotate\n");

	// Do the flag fixup here

	fprintf(fp, "		lahf		; Get the current flags back\n");
	fprintf(fp, "		mov	bh, ah ; Store it here for later\n");

	// DH Contains our original flags, BH Contains the live carry flag

	fprintf(fp, "		and	bh, 1	; Only the carry matters\n");

	if (0x2a == dwOpcode)
		fprintf(fp, "		or		al, al	; Set sign/zero\n");
	else
		fprintf(fp, "		or		dl, dl	; Set sign/zero\n");

	fprintf(fp, "		lahf		; Get the flags\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign and zero\n");
	fprintf(fp, "		or		ah, bh	; Or In our carry\n");
	fprintf(fp, "		or		ah, dh	; Or in our original flags\n");

	if (0x2a != dwOpcode)	// Make sure it's not the accumulator
	{
		fprintf(fp, "		mov	bh, dl	; Get our byte to write\n");
		fprintf(fp, "		pop	edx		; Restore the address\n");
		if (((0x36 == dwOpcode) || (0x26 == dwOpcode)) && (bZeroDirect))
			fprintf(fp, "		mov	[ebp+edx], bh	; Set our zero page byte\n");
		else
			WriteMemoryByte("bh", "dx");
	}

	fprintf(fp, "		xor	bh, bh	; Zero this so we don't screw up things\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void RorHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; ROR\n");
	fprintf(fp, ";\n");

	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x6e == dwOpcode)
		Absolute();
	else
	if (0x66 == dwOpcode)
		ZeroPage();
	else
	if (0x7e == dwOpcode)
		AbsoluteX();
	else
	if (0x76 == dwOpcode)
		ZeroPageX();

	// Now that we've got the address (or whatever) let's fetch it!

	if (0x6a != dwOpcode)	// Make sure it's not the accumulator
	{
		fprintf(fp, "		push	edx		; Save our address\n");
		if (((0x76 == dwOpcode) || (0x66 == dwOpcode)) && bZeroDirect)
			fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page byte\n");
		else
			ReadMemoryByte("dl", "dx");
	}

	// We've got the data in DL (or in AL if accumulator shift)

	fprintf(fp, "		mov	dh, ah	; Save off our original flags\n");
	fprintf(fp, "		and	dh, 3eh	; No carry, zero, or sign\n");
	fprintf(fp, "		sahf		; Restore flags\n");

	if (0x6a == dwOpcode)
		fprintf(fp, "		rcr	al, 1	; Through carry rotate\n");
	else
		fprintf(fp, "		rcr	dl, 1	; Through carry rotate\n");

	// Do the flag fixup here

	fprintf(fp, "		lahf		; Get the current flags back\n");
	fprintf(fp, "		mov	bh, ah ; Store it here for later\n");

	// DH Contains our original flags, BH Contains the live carry flag

	fprintf(fp, "		and	bh, 1	; Only the carry matters\n");

	if (0x6a == dwOpcode)
		fprintf(fp, "		or		al, al	; Set sign/zero\n");
	else
		fprintf(fp, "		or		dl, dl	; Set sign/zero\n");

	fprintf(fp, "		lahf		; Get the flags\n");
	fprintf(fp, "		and	ah, 0c0h	; Only sign and zero\n");
	fprintf(fp, "		or		ah, bh	; Or In our carry\n");
	fprintf(fp, "		or		ah, dh	; Or in our original flags\n");

	if (0x6a != dwOpcode)	// Make sure it's not the accumulator
	{
		fprintf(fp, "		mov	bh, dl	; Get our byte to write\n");
		fprintf(fp, "		pop	edx		; Restore the address\n");
		if (((0x76 == dwOpcode) || (0x66 == dwOpcode)) && (bZeroDirect))
			fprintf(fp, "		mov	[ebp+edx], bh	; Set our zero page byte\n");
		else
			WriteMemoryByte("bh", "dx");
	}

	fprintf(fp, "		xor	bh, bh	; Zero this so we don't screw up things\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void BitHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; BIT\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x2c == dwOpcode)
		Absolute();
	else if (0x89 == dwOpcode)
	  Immediate("dl");
	else if (0x3c == dwOpcode)
	  AbsoluteX();
	else if (0x24 == dwOpcode)
		ZeroPage();
	else
	if (0x34 == dwOpcode)
		ZeroPageX();
	else
		assert(0);

	if (dwOpcode != 0x89) { // it's not immediate
	  if ((0x2c == dwOpcode) || 0x3c == dwOpcode || ((0x24 == dwOpcode || 0x34 == dwOpcode) && (FALSE == bZeroDirect)))
	    ReadMemoryByte("dl", "dx");
	  else
	    fprintf(fp, "		mov	dl, [ebp+edx]	; Get our zero page byte\n");
	}

	fprintf(fp, "		mov	dh, dl	; Save this, too\n");
	if (dwOpcode != 0x89) // bits N & V untouched in immediate mode
	  fprintf(fp, "		and	ah, 2fh	; Kill sign, zero, and overflow\n");
	fprintf(fp, "		mov	bh, ah	; Put it here for later\n");

	fprintf(fp, "		and	dl, al	; And this value with the accumulator\n");
	fprintf(fp, "		lahf			; Get our flags\n");
	fprintf(fp, "		and	ah, 040h	; Only the zero matters\n");
	fprintf(fp, "		or		ah, bh	; Get our other original flags back\n");
	if (dwOpcode != 0x89) { // bits N & V untouched in immediate mode
	  fprintf(fp, "		mov	dl, dh	; Get our value back\n");
	  fprintf(fp, "		and	dl, 80h	; Only the negative flag\n");
	  fprintf(fp, "		or		ah, dl	; OR It in with the original\n");
	  fprintf(fp, "		and	dh, 40h	; What we do with the 6th bit\n");
	  fprintf(fp, "		shr	dh, 2		; Save this for later\n");
	  fprintf(fp, "		or		ah, dh	; OR In our \"overflow\"\n");
	}

	fprintf(fp, "		xor	bh, bh	; Zero this!\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void PhaPhpHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");

	if (0x48 == dwOpcode)
		fprintf(fp, "; PHA\n");
	else
	if (0x08 == dwOpcode)
		fprintf(fp, "; PHP\n");
	else
	if (0xda == dwOpcode)
		fprintf(fp, "; PHX\n");
	else
	if (0x5a == dwOpcode)
		fprintf(fp, "; PHY\n");
	else
		assert(0);

	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x08 == dwOpcode)
		FlagsX86to6502();

	fprintf(fp, "		inc	dh		; Stack page\n");
	fprintf(fp, "		mov	dl, [_%ss]	; Stack pointer\n", cpubasename);

	if (0x08 == dwOpcode)
		fprintf(fp, "		mov	[ebp+edx], ah\n");
	else
	if (0x48 == dwOpcode)
		fprintf(fp, "		mov	[ebp+edx], al\n");
	else
	if (0xda == dwOpcode)
		fprintf(fp, "		mov	[ebp+edx], bl\n");	// X
	else
	if (0x5a == dwOpcode)
		fprintf(fp, "		mov	[ebp+edx], cl\n");	// Y

	fprintf(fp, "		dec	byte [_%ss]	; Decrement our stack pointer\n", cpubasename);

	if (0x08 == dwOpcode)
		Flags6502toX86();

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void PlaPlpHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");

	if (0x28 == dwOpcode)
		fprintf(fp, "; PLP\n");
	else
	if (0x68 == dwOpcode)
		fprintf(fp, "; PLA\n");
	else
	if (0x7a == dwOpcode)
		fprintf(fp, "; PLY\n");
	else
	if (0xfa == dwOpcode)
		fprintf(fp, "; PLX\n");
	else
		assert(0);

	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp, "		inc	dh		; Stack page\n");
	fprintf(fp, "		inc	byte [_%ss]	; Increment our stack pointer\n", cpubasename);
	fprintf(fp, "		mov	dl, [_%ss]	; Stack pointer\n", cpubasename);

	if (0x28 == dwOpcode)		// PLP
	{
		fprintf(fp, "		mov	ah, [ebp+edx]\n");
		Flags6502toX86();
	}
	else
	{
		if (0x68 == dwOpcode)
			fprintf(fp, "		mov	al, [ebp+edx]\n");
		else
		if (0x7a == dwOpcode)		// PLY
			fprintf(fp, "		mov	cl, [ebp+edx]\n");
		else
		if (0xfa == dwOpcode)		// PLX
			fprintf(fp, "		mov	bl, [ebp+edx]\n");
		else
			assert(0);

		fprintf(fp, "		mov	dl, ah\n");
		fprintf(fp, "		and	dl, 03fh\n");

		if (0x68 == dwOpcode)
			fprintf(fp, "		or		al, al\n");
		else
		if (0x7a == dwOpcode)
			fprintf(fp, "		or		cl, cl\n");	// PLY
		else
		if (0xfa == dwOpcode)
			fprintf(fp, "		or		bl, bl\n"); // PLX
		else
			assert(0);

		fprintf(fp, "		lahf\n");
		fprintf(fp, "		and	ah, 0c0h\n");
		fprintf(fp, "		or		ah, dl\n");
	}

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void RtiHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; RTI\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	fprintf(fp, "		mov	dl, [_%ss]	; Get our stack pointer\n", cpubasename);
	fprintf(fp, "		add	[_%ss], byte 3	; Restore our stack\n", cpubasename);

	fprintf(fp, "		inc	dh		; Increment to the stack page\n");
	fprintf(fp, "		inc	dl		; And our pointer to the flags\n");
	fprintf(fp, "		mov	ah, [ebp+edx]	; Get our flags\n");
	fprintf(fp, "		inc	dl		; Next address\n");
	fprintf(fp, "		mov	si, [ebp+edx]	; Get our new address\n");
	fprintf(fp, "		mov	[_%spc], si	; Store our program counter\n", cpubasename);

	fprintf(fp, "		or	ah, 20h	; This bit is always 1\n");
	fprintf(fp, "		mov	[_%saf + 1], ah	; Store our flags\n", cpubasename);
	fprintf(fp, "		test	ah, 04h	; Interrupts reenabled?\n");
	fprintf(fp, "		jnz	notEnabled\n");
	fprintf(fp, "		cmp	[_irqPending], byte 0 ; IRQ pending?\n");
	fprintf(fp, "		je		notEnabled\n");

	fprintf(fp, "		push	eax		; Save this - we need it\n");
	fprintf(fp, "		call	_%sint	; Go do an interrupt\n", cpubasename);
	fprintf(fp, "		pop	eax		; Restore this - we need it!\n");

	fprintf(fp, "notEnabled:\n");
	fprintf(fp, "		xor	esi, esi\n");
	fprintf(fp, "		mov	si, [_%spc]	; Get our program counter\n", cpubasename);

	if (bBankswitch)
		PCToPage();
	else
		fprintf(fp, "		add	esi, ebp ; So it properly points to the code\n");

	Flags6502toX86();

	++dwGlobalLabel;
	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void NopHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; NOP\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void StzHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; STZ\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	// 64 - Zero page
	// 74 - Zero page X
	// 9c - Absolute
	// 9e - Absolute X

	// First fetch the info

	if (0x64 == dwOpcode)
	{
		ZeroPage();

		if (FALSE != bZeroDirect)
			fprintf(fp, "		mov	[ebp+edx], byte 0	; Zero it!\n");
	}
	else
	if (0x74 == dwOpcode)
		ZeroPageX();
	else
	if (0x9c == dwOpcode)
		Absolute();
	else
	if (0x9e == dwOpcode)
		AbsoluteX();

	// Now we have the address in DX - let's see what we do with it

	if ((0x64 != dwOpcode) || (FALSE == bZeroDirect))
		WriteMemoryByte("bh", "dx");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void BraHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; BRA\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	FetchInstructionByte();		// Go get our offset just in case
	fprintf(fp, "		movsx	dx, dl\n");

	if (bBankswitch)
		PageToPC();
	else
		fprintf(fp, "		sub	esi, ebp	 ; Get our real program counter\n");

	fprintf(fp, "		add	si, dx\n");

	if (bBankswitch)
	{
		fprintf(fp, "		mov	[_%spc], si\n", cpubasename);
		PCToPage();
	}
	else
		fprintf(fp, "		add	esi, ebp\n");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void TsbHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TSB\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x04 == dwOpcode)	// Zero page
		ZeroPage();
	else
	if (0x0c == dwOpcode)	// Absolute
		Absolute();
	else
		assert(0);

	// Address is now in EDX

	if ((FALSE != bZeroDirect) && (0x04 == dwOpcode))	// If it's zero page, just do the work!
	{
		fprintf(fp, "		or	[ebp+edx], al	; OR In accumulator\n");
		fprintf(fp, "		mov	dh, [ebp+edx]	; Get the data\n");
	}
	else	// We go through our handlers
	{
		fprintf(fp, "		mov	[_tempAddr], edx	; Store our address for later\n");
		ReadMemoryByte("dh", "dx");
		fprintf(fp, "		or	dh, al	; OR In our value\n");
		fprintf(fp, "		mov	bh, dh	; Our value\n");
		fprintf(fp, "		push	edx	; Save this for later\n");
		WriteMemoryByte("bh", "dx");
		fprintf(fp, "		pop	edx	; Restore our data (in DL)\n");
		fprintf(fp, "		xor	bh, bh	; Zero this\n");
	}

	// Now we have our value in DH - set the zero flag accordingly

	SetZero("dh");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

static void TrbHandler(UINT16 dwOpcode)
{
	fprintf(fp, ";\n");
	fprintf(fp, "; TRB\n");
	fprintf(fp, ";\n");
	sprintf(string, "Reg02Inst%.2x", dwOpcode);
	ProcBegin(string, dwOpcode);

	if (0x14 == dwOpcode)	// Zero page
		ZeroPage();
	else
	if (0x1c == dwOpcode)	// Absolute
		Absolute();
	else
		assert(0);

	// Address is now in EDX

	fprintf(fp, "		mov	bh, al\n");
	fprintf(fp, "		xor	bh, 0ffh\n");

	if ((FALSE != bZeroDirect) && (0x04 == dwOpcode))	// If it's zero page, just do the work!
	{
		fprintf(fp, "		and	[ebp+edx], bh	; AND In the appropriate value\n");
		fprintf(fp, "		mov	dh, [ebp+edx]	; Get the data\n");
	}
	else	// We go through our handlers
	{
		fprintf(fp, "		mov	[_tempAddr], edx	; Store our address for later\n");
		ReadMemoryByte("dh", "dx");
		fprintf(fp, "		and	dh, bh	; AND In our value\n");
		fprintf(fp, "		mov	bh, dh	; Our value\n");
		fprintf(fp, "		push	edx	; Save this for later\n");
		WriteMemoryByte("bh", "dx");
		fprintf(fp, "		pop	edx	; Restore our data (in DL)\n");
	}

	// Now we have our value in DH - set the zero flag accordingly

	fprintf(fp, "		xor	bh, bh	; Zero this\n");
	SetZero("dh");

	FetchAndExec(bTimingTable[dwOpcode]);
	ProcEnd(string);
}

/* These are the meta routines */

static void ExecCode()
{
	fprintf(fp, "		global	_%sexec\n", cpubasename);
	fprintf(fp, "		global	%sexec_\n", cpubasename);

	if (bPlain)
		fprintf(fp, "		global	%sexec\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sexec", cpubasename);
	else
		sprintf(string, "%sexec_", cpubasename);
	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%sexec:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "		mov	eax, [esp+4]	; Get our execution cycle count\n");

	fprintf(fp, "		push	ebx			; Save all registers we use\n");
	fprintf(fp, "		push	ecx\n");
	fprintf(fp, "		push	edx\n");
	fprintf(fp, "		push	ebp\n");
	fprintf(fp, "		push	esi\n");
	fprintf(fp, "		push	edi\n");
	fprintf(fp, "\n");

	if (bSingleStep)
		fprintf(fp, "		mov	eax, 2	; No longer cycles - now instructions!\n");

	fprintf(fp, "		mov	dword [cyclesRemaining], eax	; Store # of instructions to\n");
	fprintf(fp, "		cld				; Go forward!\n");
	fprintf(fp, "\n");
	fprintf(fp, "		xor	eax, eax		; Zero EAX 'cause we use it!\n");
	fprintf(fp, "		xor	ebx, ebx		; Zero EBX, too\n");
	fprintf(fp, "		xor	ecx, ecx		; Zero ECX\n");
	fprintf(fp, "		xor	esi, esi		; Zero our source address\n");
	fprintf(fp, "\n");

	fprintf(fp, "		mov	bl, [_%sx]	; Get X\n", cpubasename);
	fprintf(fp, "		mov	cl, [_%sy]	; Get Y\n", cpubasename);
	fprintf(fp, "		mov	ax, [_%saf]	; Get our flags and accumulator\n", cpubasename);
	fprintf(fp, "		mov	si, [_%spc]	; Get our program counter\n", cpubasename);
	fprintf(fp, "		mov	ebp, [_%sBase]	; Get our base address register\n", cpubasename);

	if (bBankswitch)
		PCToPage();
	else
		fprintf(fp, "		add	esi, ebp		; Add in our base address\n");

	fprintf(fp, "		xor	edx, edx		; And EDX\n");
	fprintf(fp, "		xor	edi, edi		; Zero EDI as well\n");

	Flags6502toX86();

	FetchAndExec(0);

	fprintf(fp, "invalidInsWord:\n");
	fprintf(fp, "		dec	esi\n");
	fprintf(fp, "\n");
	fprintf(fp, "; We get to invalidInsByte if it's a single byte invalid opcode\n");
	fprintf(fp, "\n");

	fprintf(fp, "invalidInsByte:\n");
	fprintf(fp, "		dec	esi			; Back up one instruction...\n");

	if (FALSE == bBankswitch)
	{
		fprintf(fp, "		mov	edx, esi		; Get our address in EAX\n");
		fprintf(fp, "		sub	edx, ebp		; And subtract our base for\n");
	}
	else
	{
		PageToPC();
		fprintf(fp, "		mov	edx, esi\n");
	}

	fprintf(fp, "						; an invalid instruction\n");
	fprintf(fp, "		jmp	emulateEnd\n");
	fprintf(fp, "\n");
	fprintf(fp, "noMoreExec:\n");
	fprintf(fp, "		dec	esi\n");

	if (bBankswitch)
		PageToPC();

	// Put any register storing here

	fprintf(fp, "		mov	edx, 80000000h		; Indicate successful exec\n");

	// Store all the registers here

	fprintf(fp, "emulateEnd:\n");

	fprintf(fp, "		push	edx		; Save this for the return\n");
	FlagsX86to6502();
	fprintf(fp, "		mov	[_%sx], bl	; Store X\n", cpubasename);
	fprintf(fp, "		mov	[_%sy], cl	; Store Y\n", cpubasename);
	fprintf(fp, "		mov	[_%saf], ax	; Store A & flags\n", cpubasename);

	if (FALSE == bBankswitch)
		fprintf(fp, "		sub	esi, ebp	; Get our PC back\n");

	fprintf(fp, "		mov	[_%spc], si	; Store PC\n", cpubasename);
	fprintf(fp, "		pop	edx		; Restore EDX for later\n");

	fprintf(fp, "\n");
	fprintf(fp, "popReg:\n");
	fprintf(fp, "		mov	eax, edx	; Get our result code\n");
	fprintf(fp, "		pop	edi			; Restore registers\n");
	fprintf(fp, "		pop	esi\n");
	fprintf(fp, "		pop	ebp\n");
	fprintf(fp, "		pop	edx\n");
	fprintf(fp, "		pop	ecx\n");
	fprintf(fp, "		pop	ebx\n");
	fprintf(fp, "\n");
	fprintf(fp, "		ret\n");
	fprintf(fp, "\n");
	ProcEnd(string);
}

static void CpuInit()
{
	fprintf(fp, "		global	_%sinit\n", cpubasename);
	fprintf(fp, "		global	%sinit_\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sinit", cpubasename);
	else
		sprintf(string, "%sinit_", cpubasename);

	ProcBegin(string, 0xffffffff);
	fprintf(fp, "_%sinit:\n", cpubasename);

	fprintf(fp, "		ret\n");

	ProcEnd(string);
}

static void NmiCode()
{
	fprintf(fp, "		global	_%snmi\n", cpubasename);
	fprintf(fp, "		global	%snmi\n", cpubasename);

	if (bPlain)
		sprintf(string, "%snmi", cpubasename);
	else
		sprintf(string, "%snmi_", cpubasename);

	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%snmi:\n", cpubasename);

	fprintf(fp, "		push    edi\n");
	fprintf(fp, "		push    ebx\n");
	fprintf(fp, "\n");
	fprintf(fp, "		mov     ebx, 0100h              ; Point to stack page\n");
	fprintf(fp, "\n");
	fprintf(fp, "		mov     edi, [_%sBase]       ; Get pointer to game image\n", cpubasename);
	fprintf(fp, "		mov     bl, [_%ss]           ; Get our S reg pointer\n",cpubasename);
	fprintf(fp, "		mov     ax, [_%spc]          ; Get our PC\n",cpubasename);
	fprintf(fp, "\n");
	fprintf(fp, "		mov     [edi + ebx], ah         ; Store it!\n");
	fprintf(fp, "		dec     bl\n");
	fprintf(fp, "		mov     [edi + ebx], al         ; Store it!\n");
	fprintf(fp, "		dec     bl\n");
	fprintf(fp, "\n");
	fprintf(fp, "		mov     al, byte [_%saf+1] ; Get our flags\n", cpubasename);
	fprintf(fp, "\n");
	fprintf(fp, "\n");
	fprintf(fp, "		mov     [edi + ebx], al         ; Store flags\n");
	fprintf(fp, "		dec     bl\n");
	fprintf(fp, "		mov     ax, [edi+0fffah]        ; Get our start vector!\n");
	fprintf(fp, "\n");
	fprintf(fp, "		mov     [_%ss], bl             ; Store S reg pointer\n", cpubasename);
	fprintf(fp, "		and     [_%saf + 1], byte 0efh      ; Knock out source of interrupt bit\n", cpubasename);
	fprintf(fp, "		or      [_%saf + 1], byte 24h       ; Turn on something\n", cpubasename);
	fprintf(fp, "		mov     [_%spc], ax            ; Store our new PC\n", cpubasename);
	fprintf(fp, "\n");
	fprintf(fp, "		pop     ebx\n");
	fprintf(fp, "		pop     edi\n");
	fprintf(fp, "\n");
	fprintf(fp, "		xor	eax, eax		; Indicate that we took the NMI\n");
	fprintf(fp, "		ret\n");

	ProcEnd(string);
}

static void IntCode()
{
	fprintf(fp, "		global	_%sint\n", cpubasename);
	fprintf(fp, "		global	%sint\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sint", cpubasename);
	else
		sprintf(string, "%sint_", cpubasename);

	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%sint:\n", cpubasename);

	fprintf(fp, "		test	[_%saf + 1], byte 04h	; Are interrupts disabled?\n", cpubasename);
	fprintf(fp, "		jnz	intNotTaken	; Nope! Make it pending!\n");
	fprintf(fp, "		mov	[_irqPending], byte 00h	; No longer pending\n");

	fprintf(fp, "		push    edi\n");
	fprintf(fp, "		push    ebx\n");
	fprintf(fp, "		push    ax\n");

	fprintf(fp, "		mov     ebx, 0100h              ; Point to stack page\n");
	fprintf(fp, "		mov	  edi, [_%sBase]	; Get pointer to game image\n", cpubasename);

	fprintf(fp, "		mov     bl, [_%ss]           ; Get our S reg pointer\n", cpubasename);
	fprintf(fp, "		mov     ax, [_%spc]          ; Get our PC\n", cpubasename);

	fprintf(fp, "		mov     [edi + ebx], ah         ; Store it!\n");
	fprintf(fp, "		dec     bl\n");
	fprintf(fp, "		mov     [edi + ebx], al         ; Store it!\n");
	fprintf(fp, "		dec     bl\n");

	fprintf(fp, "		mov     al, byte [_%saf+1] ; Get our flags\n", cpubasename);

	fprintf(fp, "		mov     [edi + ebx], al         ; Store flags\n");
	fprintf(fp, "		dec     bl\n");
	fprintf(fp, "		mov     ax, [edi+0fffeh]        ; Get our start vector!\n");

	fprintf(fp, "		mov     [_%ss], bl             ; Store S reg pointer\n", cpubasename);
	fprintf(fp, "		and	  [_%saf + 1], byte 0efh		; Knock out source of interrupt bit\n", cpubasename);
	fprintf(fp, "		or		  [_%saf + 1], byte 24h		; Turn on something\n", cpubasename);
	fprintf(fp, "		mov     [_%spc], ax            ; Store our new PC\n", cpubasename);

	fprintf(fp, "		pop     ax                      ; Restore used registers\n");
	fprintf(fp, "		pop     ebx\n");
	fprintf(fp, "		pop     edi\n");

	fprintf(fp, "		xor	eax, eax		; Indicate we've taken the interrupt\n");
	fprintf(fp, "		mov	[_irqPending], al	; No more IRQ pending!\n");
	fprintf(fp, "		ret\n");

	fprintf(fp, "intNotTaken:\n");
	fprintf(fp, "		mov	eax, 1		; Indicate we didn't take it\n");
	fprintf(fp, "		mov	[_irqPending], al ; Indicate we have a pending IRQ\n");
	fprintf(fp, "		ret\n");

	ProcEnd(string);
}

static void GetTicksCode()
{
	fprintf(fp, "		global	_%sGetElapsedTicks\n", cpubasename);
	fprintf(fp, "		global	%sGetElapsedTicks_\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sGetElapsedTicks", cpubasename);
	else
		sprintf(string, "%sGetElapsedTicks_", cpubasename);

	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%sGetElapsedTicks:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "		mov	eax, [esp+4]	; Get our context address\n");

	fprintf(fp, "		or	eax, eax	; Should we clear it?\n");
	fprintf(fp, "		jz	getTicks\n");
	fprintf(fp, "		xor	eax, eax\n");
	fprintf(fp, "		xchg	eax, [dwElapsedTicks]\n");
	fprintf(fp, "		ret\n");
	fprintf(fp, "getTicks:\n");
	fprintf(fp, "		mov	eax, [dwElapsedTicks]\n");
	fprintf(fp, "		ret\n");

	ProcEnd(string);
}

static void ReleaseTimesliceCode()
{
	fprintf(fp, "		global	_%sReleaseTimeslice\n", cpubasename);
	if (bPlain)
	  fprintf(fp, "		global	%sReleaseTimeslice\n", cpubasename);
	else
	  fprintf(fp, "		global	%sReleaseTimeslice_\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sReleaseTimeslice", cpubasename);
	else
		sprintf(string, "%sReleaseTimeslice_", cpubasename);

	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%sReleaseTimeslice:\n", cpubasename);

	fprintf(fp, "		mov	[cyclesRemaining], dword 1\n");
	fprintf(fp, "		ret\n");

	ProcEnd(string);
}

static void ResetCode()
{
	fprintf(fp, "		global	_%sreset\n", cpubasename);
	fprintf(fp, "		global	%sreset_\n", cpubasename);
	fprintf(fp, "		global	%sreset\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sreset", cpubasename);
	else
		sprintf(string, "%sreset_", cpubasename);

	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%sreset:\n", cpubasename);

	fprintf(fp, "		push	ebp	; Save our important register\n");
	fprintf(fp, "		xor	eax, eax\n");
	fprintf(fp, "		mov	ebp, [_%sBase]\n", cpubasename);
	fprintf(fp, "		mov	[_%sx], al\n", cpubasename);
	fprintf(fp, "		mov	[_%sy], al\n", cpubasename);
	fprintf(fp, "		mov	[_irqPending], al\n");
	fprintf(fp, "		mov	[_%ss], byte 0ffh\n", cpubasename);
	fprintf(fp, "		mov	[_%saf], word 2200h\n", cpubasename);
	fprintf(fp, "		mov	ax, [ebp + 0fffch] ; Get reset address\n");
	fprintf(fp, "		mov	[_%spc], ax\n", cpubasename);
	fprintf(fp,	"		pop	ebp\n");
	fprintf(fp, "		ret\n");
	fprintf(fp, "\n");
	ProcEnd(string);
}

static void SetContextCode()
{
	fprintf(fp, "		global	_%sSetContext\n", cpubasename);
	fprintf(fp, "		global	%sSetContext_\n", cpubasename);
	fprintf(fp, "		global	%sSetContext\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sSetContext", cpubasename);
	else
		sprintf(string, "%sSetContext_", cpubasename);

	ProcBegin(string, 0xffffffff);
	fprintf(fp, "_%sSetContext:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "		mov	eax, [esp+4]	; Get our context address\n");

	fprintf(fp, "		push	esi		; Save registers we use\n");
	fprintf(fp, "		push	edi\n");
	fprintf(fp, "		push	ecx\n");
	fprintf(fp, "		mov     ecx, _%scontextEnd - _%scontextBegin\n", cpubasename, cpubasename);
	fprintf(fp, "		mov	edi, _%scontextBegin\n", cpubasename);
	fprintf(fp, "		mov	esi, eax	; Source address in ESI\n");
	fprintf(fp, "		rep	movsb		; Move it as fast as we can!\n");
	fprintf(fp, "		pop	ecx\n");
	fprintf(fp, "		pop	edi\n");
	fprintf(fp, "		pop	esi\n");
	fprintf(fp, "		ret			; No return code\n");
	ProcEnd(string);
}

static void GetContextCode()
{
	fprintf(fp, "		global	_%sGetContext\n", cpubasename);
	fprintf(fp, "		global	%sGetContext_\n", cpubasename);
	fprintf(fp, "		global	%sGetContext\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sGetContext", cpubasename);
	else
		sprintf(string, "%sGetContext_", cpubasename);

	ProcBegin(string, 0xffffffff);

	fprintf(fp, "_%sGetContext:\n", cpubasename);

	if (bUseStack)
		fprintf(fp, "		mov	eax, [esp+4]	; Get our context address\n");

	fprintf(fp, "		push	esi		; Save registers we use\n");
	fprintf(fp, "		push	edi\n");
	fprintf(fp, "		push	ecx\n");
	fprintf(fp, "		mov     ecx, _%scontextEnd - _%scontextBegin\n", cpubasename, cpubasename);
	fprintf(fp, "		mov	esi, _%scontextBegin\n", cpubasename);
	fprintf(fp, "		mov	edi, eax	; Source address in ESI\n");
	fprintf(fp, "		rep	movsb		; Move it as fast as we can!\n");
	fprintf(fp, "		pop	ecx\n");
	fprintf(fp, "		pop	edi\n");
	fprintf(fp, "		pop	esi\n");
	fprintf(fp, "		ret			; No return code\n");
	ProcEnd(string);
}

static void GetContextSizeCode()
{
	fprintf(fp, "		global	_%sGetContextSize\n", cpubasename);
	fprintf(fp, "		global	%sGetContextSize_\n", cpubasename);
	fprintf(fp, "		global	%sGetContextSize\n", cpubasename);

	if (bPlain)
		sprintf(string, "%sGetContextSize", cpubasename);
	else
		sprintf(string, "%sGetContextSize_", cpubasename);

	ProcBegin(string, 0xffffffff);
	fprintf(fp, "_%sGetContextSize:\n", cpubasename);
	fprintf(fp, "		mov     eax, _%scontextEnd - _%scontextBegin\n", cpubasename, cpubasename);
	fprintf(fp, "		ret\n");
	ProcEnd(string);
}

static void EmitCode()
{
	CodeSegmentBegin();
	ReadMemoryByteHandler();
	EmitRegularInstructions();
	GetContextCode();
	SetContextCode();
	GetContextSizeCode();
	CpuInit();
	GetTicksCode();
	ReleaseTimesliceCode();
	ResetCode();
	IntCode();
	NmiCode();
	ExecCode();
	CodeSegmentEnd();
}

int main(int argc, char **argv)
{
	UINT32 dwLoop = 0;

	printf("Make6502 - V%s - Copyright 1998, Neil Bradley (neil@synthcom.com)\n", VERSION);

	if (argc < 2)
	{
		printf("Usage: %s outfile [option1] [option2] ....\n", argv[0]);
		printf("\n  -ss   - Create m6502(zp) to execute one instruction per m6502exec()\n");
		printf("  -s    - Stack calling conventions (DJGPP, MSVC, Borland)\n");
		printf("  -z    - Create zero page version of m6502 (see documentation)\n");
		printf("  -bs   - Create boundary bank switched version (8K page default)\n");
		printf("  -l    - Create 'plain' function names with no leading or trailing _'s\n");
		printf("  -#    - -2=2K bank switch, -4=4K Banks, -8=8K Banks, -16=16K Banks\n");
		printf("  -i    - Treat invalid instructions as NOPs\n");
		printf("  -d    - No decimal mode\n");
		printf("  -6510 - Include 6510 instructions\n");
		exit(1);
	}

	dwLoop = 1;

	while (dwLoop < (UINT32)argc)
	{
		if (strcmp("-l", argv[dwLoop]) == 0)
			bPlain = TRUE;
		if (strcmp("-2", argv[dwLoop]) == 0)
			dwBankSize = 11;
		if (strcmp("-4", argv[dwLoop]) == 0)
			dwBankSize = 12;
		if (strcmp("-8", argv[dwLoop]) == 0)
			dwBankSize = 13;
		if (strcmp("-16", argv[dwLoop]) == 0)
			dwBankSize = 14;
		if (strcmp("-bs", argv[dwLoop]) == 0 || strcmp("-BS", argv[dwLoop]) == 0)
			bBankswitch = 1;
		if (strcmp("-ss", argv[dwLoop]) == 0 || strcmp("-S", argv[dwLoop]) == 0)
			bSingleStep = 1;
		if (strcmp("-s", argv[dwLoop]) == 0 || strcmp("-S", argv[dwLoop]) == 0)
			bUseStack = 1;
		if (strcmp("-z", argv[dwLoop]) == 0 || strcmp("-Z", argv[dwLoop]) == 0)
			bZeroDirect = (UINT8) TRUE;
		if (strcmp("-i", argv[dwLoop]) == 0 || strcmp("-I", argv[dwLoop]) == 0)
			bInvalidAsNop = (UINT8) TRUE;
		if (strcmp("-d", argv[dwLoop]) == 0 || strcmp("-D", argv[dwLoop]) == 0)
			bNoDecimal = (UINT8) TRUE;
		if (strcmp("-6510", argv[dwLoop]) == 0)
			b6510Instructions = (UINT8) TRUE;
		dwLoop++;
	}

	if (bBankswitch)
		strcpy(cpubasename, "m6502bs");
	else
	if (bZeroDirect)
		strcpy(cpubasename, "m6502zp");
	else
		strcpy(cpubasename, "m6502");

	for (dwLoop = 1; dwLoop < (UINT32)argc; dwLoop++)
		if (argv[dwLoop][0] != '-')
		{
			fp = fopen(argv[dwLoop], "w");
			break;
		}

	if (NULL == fp)
	{
		fprintf(stderr, "Can't open %s for writing\n", argv[1]);
	}

	StandardHeader();
	DataSegment();
	EmitCode();
	ProgramEnd();

	fclose(fp);
	return 0;
}
