/*
	Z80 Disassembler Module v1.50
		Copyright 1996-2001 Mark Incley.
*/


#ifdef WIN32
#include <windows.h>
#endif

#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "types.h"

#include "dissz80.h"
#include "dissz80p.h"

#define ADDTODIS(str)	strcat(d->disBuf, str)
#define	MARKBLANKLINE	d->lineCmd |= LC_BLANKLINE

int GetNextOpCode(DISZ80 *d)
{	
	char		buf[8];

	assert(d != NULL);

	d->op = d->Z80MemBase[d->PC++];
	sprintf(buf, "%02x", (BYTE)d->op);
	strcat(d->hexDisBuf, buf);

	d->bytesProcessed++;
	return d->op;
}

char *dz80_GetVersionString(void)
{
	return VersionString;
}


/*
	void dZ80_SetDefaultOptions(DISZ80 *d)

	Set the default radix (hex), comment marker and DB directive string.
*/

void dZ80_SetDefaultOptions(DISZ80 *d)
{
	assert(d != NULL);

/* Standard comment and DB */
	d->layoutComment = "; ";
	d->layoutDefineByte = "db";

/* Hex by default */
	dZ80_SetDisassemblyRadix(d, DZ80RADIX_HEX);
	return;
}


void dZ80_InheritRadix(DISZ80 *dst, DISZ80 *src)
{
	assert(dst != NULL && src != NULL);

	dst->layoutRadix = src->layoutRadix;
	dst->layoutComment = src->layoutComment;
	dst->layoutDefineByte = src->layoutDefineByte;
	dst->layoutNumberPrefix = src->layoutNumberPrefix;
	dst->layoutNumberSuffix = src->layoutNumberSuffix;
	return;
}

void dZ80_SetDisassemblyRadix(DISZ80 *d, int Radix)
{
	assert(d != NULL);
	assert(Radix >= 0 && Radix < DZ80RADIX_TOTAL);

	d->layoutNumberPrefix = d->layoutNumberSuffix = NULL;
	d->layoutRadix = Radix;

	switch(Radix)
		{
		case DZ80RADIX_OCTAL:
			d->layoutNumberPrefix = "0";
			break;

		case DZ80RADIX_DECIMAL:
			break;

		case DZ80RADIX_HEX:
			d->layoutNumberPrefix = "$";
			break;
		}

	return;
}



void PrepareDisInstruction(DISZ80 *d)
{
	assert(d != NULL);
	
	d->hexDisBuf[0] = d->disBuf[0] = d->commentBuf[0] = 0;
	d->Z80Flags = d->numRecursions = 0; 	/* Clear and IX/IY prefixes, etc. */
	d->lineCmd = 0; 						/* Clear out line commands */
	d->haveTabbed = FALSE;
	return;
}
		
int dZ80_Disassemble(DISZ80 *d)
{
	int 	i, err, writingOut;
	char	buf[256];

	assert(d != NULL);

	if (d->mem0Start == NULL)
		return DERR_INVALIDPARAMS;

	d->createdRefOK = FALSE;
	d->numInstructions = 0;
	d->Z80MemBase = d->mem0Start;
	d->totalPasses = 1;
	d->labelledOutput = FALSE;
	d->outStream =	NULL;
	
	d->pComment = (d->layoutComment != NULL) ? d->layoutComment : "; ";

	if (d->flags & DISFLAG_SINGLE)
		d->flags |= DISFLAG_QUIET;

	if ( (!(d->flags & DISFLAG_SINGLE)) && ((d->flags & DISFLAG_CONSOLE) || (d->outFileName == NULL)) )
		d->dissingToConsole = TRUE;
	else
		d->dissingToConsole = FALSE;

/* Has labelled output been requested? */
	if (d->flags & DISFLAG_LABELLED)
		{
		d->totalPasses = 2;
		d->labelledOutput = TRUE;
		}

	d->fnMap = d->opMap = NULL;
	d->outStream = NULL;
	for(i=0; i < DISREF_TOTAL; i++)
		{
		d->pRefHead[i] = NULL;
		d->numRefs[i] = 0;
		}

/* If creating assembler output, switch off the opcode and address dump */
	if (d->labelledOutput == TRUE)
		d->flags &= ~(DISFLAG_ADDRDUMP | DISFLAG_OPCODEDUMP);

	d->disStart = d->start;
	d->disEnd = d->end;

	if (d->disEnd < d->disStart)
		{
		d->lastPC = d->disStart;
		d->disStart = d->disEnd;
		d->disEnd = d->lastPC;
		}

	d->bytesToProcess = ((DWORD)d->disEnd	- (DWORD)d->disStart + 1) * d->totalPasses;
	d->bytesProcessed = 0;

	if (!(d->flags & DISFLAG_QUIET))
		{
		sprintf(buf, "Starting address: %u", d->disStart);
		dZ80_ShowMsg(d, buf);

		sprintf(buf, "  Ending address: %u", d->disEnd);
		dZ80_ShowMsg(d, buf);

		sprintf(buf, "     Output file: %s", (d->outFileName != NULL) ? d->outFileName : "(none)");
		dZ80_ShowMsg(d, buf);
		}

/* Using an opcode map file ? */
	if (!PrepareOpMap(d))
		return FALSE;

/* Assembler output (2 passes) ? */
	if (d->labelledOutput == TRUE)
		{
		if ((d->fnMap = AllocateMap(d, "Couldn't allocate memory for the function map.", Z80MEMSIZE))	== NULL)
			{
			DisZ80CleanUp(d);
			return DERR_OUTOFMEM;
			}
		}

/* If a destination file has been given, disassemble to file. */
	if (!CreateOutputASMFile(d))
		return DERR_COULDNTCREATEFILE;

/* Draw the progress indicator */
	DoProgress(d, TRUE);

/* Ok, at last, here's the disassembly loop! */
	for (d->currentPass = d->totalPasses; d->currentPass > 0; d->currentPass--)
		{
		for (i=0; i < 8; i++)
			FlagFn(d, i << 3); 					/* Flag the RST addresses */

		writingOut = (d->currentPass == 1);

		if (!(d->flags & DISFLAG_QUIET))
			{
			sprintf(buf, "Pass %d of %d", d->totalPasses - d->currentPass + 1, d->totalPasses);
			dZ80_ShowMsg(d, buf);
			}

		d->numInstructions = 0; 				/* Number of instructions disassembled */
		d->PC = d->disStart;
		d->lastDisPC = d->lastPC = d->PC;
		while (d->PC <= d->disEnd)
			{
			if (d->lastPC > d->PC)				/* Check for PC wraparound */
				break;

			d->lastPC = d->PC;
			DoProgress(d, FALSE);

/* Clear the disassembly buffer */
			PrepareDisInstruction(d);

/* And do the deeds */
			DisassembleInstruction(d);
			d->numInstructions++;				/* Another line disassembled */

/* If we're building up the FnMap, don't disassemble */
			if (writingOut)
				{
/* Clear out the disline (where the disassembly is built up) */
				err = WriteDisLine(d, d->lastPC);
				if (err)
					{
					DisZ80CleanUp(d);
					return err;
					}
				
				d->progressCounter--;
				}
			}					/* Next instruction */

		DoProgress(d, TRUE);
		}						/* Next pass */

	if (!(d->flags & DISFLAG_QUIET))
		{
		sprintf(buf, "\nDisassembled %u instructions.",	d->numInstructions);
		dZ80_ShowMsg(d, buf);
		}

	WriteReferenceFile(d);
	DisZ80CleanUp(d);
	return DERR_NONE;			/* Disassembled OK */
}


int WriteDisLine(DISZ80 *d, unsigned int Addr)
{
	int 	i;
	char	disLine[256], buf[128];
	
	disLine[0] = 0;

/* Add the instruction's address ? */
	if (d->flags & DISFLAG_ADDRDUMP)
		{
		MakeLJustified16BitNum(d, buf, Addr);
		strcat(buf, " ");
		strcat(disLine, buf);
		}

/* Add the hex dump? */
	if (d->flags & DISFLAG_OPCODEDUMP)
		{
		sprintf(buf, "%-8s  ", d->hexDisBuf);
		strcat(disLine, buf);
		}

/* Add the disassembly. */
	if (d->labelledOutput && IsFnUsed(d, Addr))
		sprintf(disLine, "l%04x:  ", Addr);
	else
		if ((d->flags & (DISFLAG_OPCODEDUMP | DISFLAG_ADDRDUMP)) == 0)
			strcat(disLine, "        ");

	strcat(disLine, d->disBuf);

/* Make uppercase if necessary (only up to the comment) */
	if (d->flags & DISFLAG_UPPER)
		dZ80_StringToUpper(disLine);

/* Add any comment */
	if (d->commentBuf[0])
		{
		i = strlen(disLine);
		if (i < COMMENTCOLUMN)
			{
			memset(buf, ' ', COMMENTCOLUMN-i);
			buf[COMMENTCOLUMN - i] = 0;
			strcat(disLine, buf);
			}
		strcat(disLine, d->commentBuf);
		}

/* Finally, add the new-line */
	strcat(disLine,"\n");

/* Really finally, process any line commands */
	if (!(d->flags & DISFLAG_NOLINECMDS))
		{
		if (d->lineCmd & LC_BLANKLINE)
			strcat(disLine, "\n");
		}

	if (d->dissingToConsole)
		{
		printf("%s", disLine);
		}
	else
		{
		if (d->outStream != NULL)
			{
			if (!fwrite(disLine, strlen(disLine), 1, d->outStream))
				{
				DisZ80CleanUp(d);
				return DERR_COULDNTWRITETOFILE;
				}
			}
		}

	return DERR_NONE;
}



/* Release allocated memory, close open files, etc.. */

void DisZ80CleanUp(DISZ80 *d)
{
	int 		i;
	DISREF		*dr, *drLast;
	DISREFADDR	*ra, *raLast;

	assert(d != NULL);

	if (d->outStream != NULL)
		{
		fclose(d->outStream);
		d->outStream =	NULL;
		}

	for(i=0; i < DISREF_TOTAL; i++)
		{
		dr = d->pRefHead[i];
		while(dr != NULL)
			{
			ra = dr->pRefAddrHead;
			while (ra != NULL)
				{
				raLast = ra;
				ra = ra->pNext;
				free(raLast);
				}
			drLast = dr;
			dr = dr->pNext;
			free(drLast);
			}
		d->pRefHead[i] = NULL;
		}
	
	if (d->opMap != NULL)
		{
		free(d->opMap);
		d->opMap = NULL;
		}

	if (d->fnMap != NULL)
		{
		free(d->fnMap);
		d->fnMap = NULL;
		}

	return;
}


/* Time to disassemble an instruction */

void DisassembleInstruction(DISZ80 *d)
{
	int		o;
	char	buf[8];

	if (++d->numRecursions > 3)
		{
		AddToDisUnknown(d, NULL);
		return;
		}

/* Get initial opcode */
	o = GetNextOpCode(d);

/* If we're using an opcode map file, check if we should skip this */
	if (d->opMapFileName != NULL)
		{
		if ((d->opMap[d->lastPC >> 3] & (1 << (d->lastPC & 7))) == 0)
			{
			AddToDisTabDB(d);
			Make8BitNum(d, buf, d->mem0Start[d->lastPC]);
			ADDTODIS(buf);
			return;
			}
		}

	switch (o)
		{
		case 0xcb:		/* Disassemble the Rotates, SETs and RES's */
			d->Z80Flags |= Z80CB;
			DisCB(d);
			return;

		case 0xed:
			if (d->cpuType == DCPU_Z80GB)
				{
				AddToDisUndocNop(d);
				}
			else
				{
				d->Z80Flags |= Z80ED;
				DisED(d);
				}
			return;

		case 0xdd:
			if (d->cpuType == DCPU_Z80GB)
				{
				AddToDisUndocNop(d);
				}
			else
				{
				d->Z80Flags |= Z80IX;		/* Signal IX prefix */
				d->Z80Flags &= ~Z80IY; 	/* Clear IY prefix */
				DisassembleInstruction(d);
				}
			return;

		case 0xfd:
			if (d->cpuType == DCPU_Z80GB)
				{
				AddToDisUndocNop(d);
				}
			else
				{
				d->Z80Flags |= Z80IY;		/* Signal IY prefix */
				d->Z80Flags &= ~Z80IX; 	/* Clear IX prefix */
				DisassembleInstruction(d);
				}
			return;
		}

	d->realop = d->op;

	if (o < 0x40)
		{
		Dis00to3F(d);
		return;
		}

	if (o >= 0x40 && o <= 0x7f)
		{
		Dis40to7F(d);			/* All the LD's */
		return;
		}

	if (o >= 0x80 && o <= 0xbf)
		{
		Dis80toBF(d);
		return;
		}

	if (o >= 0xc0)
		{
		DisC0toFF(d);
		return;
		}

	AddToDisUnknown(d, NULL);
	return;
}


void DisCB(DISZ80 *d)
{
	char			num[3];
	int				o, oi;

/*
	If there's an IX IY prefix, then the displacement comes *BEFORE* the
	final opcode. LD (IX+dd),nn is a similar case.
*/

	if (d->Z80Flags & Z80IXIY)
		GetIXIYDisplacement(d);

	o = GetNextOpCode(d);

/* Test for undocumented DDCB stuff */

	if (d->Z80Flags & Z80IXIY)
		if ((o & 7) != REG_HL)
			{
			DisDDCB(d);
			return;
			}

	if (o < 0x40)
		{
/* Do the rotates */
		oi = o >> 3;
		if ((oi == 6) && (d->cpuType == DCPU_Z80GB))
			AddToDisTab(d, "swap");
		else
			AddToDisTab(d, (char *)CBRotType[oi & 7]);

		AddToDisReg8(d, o, FALSE);
		}
	else
		{
		switch (o >> 6)
			{
			case 1:
				AddToDisTab(d, "bit");
				break;

			case 2:
				AddToDisTab(d, "res");
				break;

			case 3:
				AddToDisTab(d, "set");
				break;
			}

		num[0] = (char)('0'+ ((o >> 3) & 7));
		num[1] = ',';
		num[2] = 0;
		ADDTODIS(num);

/* Finally, add the register component. */
		AddToDisReg8(d, o, FALSE);
		}
}


/* Decode the DDCB instruction */

void DisDDCB(DISZ80 *d)
{
	char	num[4];
	int		BitResSet;

	if (d->op < 0x40)
		{
/* Do the undocumented rotates */
		AddToDisTabLD(d, "");
		AddToDisReg8(d, d->op, REG_HL);		/* REG_HL stops L->IXl, etc.. */
		ADDTODIS(",");
		ADDTODIS(CBRotType[(d->op >> 3) & 7]);
		ADDTODIS(" ");
		AddToDisReg8(d, REG_HL, FALSE);
		return;
		}

	BitResSet = d->op >> 6;

	if (BitResSet >= 2)
		{
		AddToDisTabLD(d, "");
		AddToDisReg8(d, d->op, REG_HL);		/* REG_HL stops L->IXl, etc.. */
		ADDTODIS(",");
		}

	switch (BitResSet)
		{
		case 1:
			AddToDisTab(d, "bit");
			break;
		case 2:
			AddToDisTab(d, "res");
			break;
		case 3:
			AddToDisTab(d, "set");
			break;
		}

	num[0] = ' ';
	num[1] = (char)('0'+ ((d->op >> 3) & 7));
	num[2] = ',';
	num[3] = 0;
	
	ADDTODIS(num + (BitResSet < 2) );

/* Finally, add the register component. */
	AddToDisReg8(d, REG_HL, FALSE);

	if (BitResSet == 1)
		AddToDisUndoc(d);

	return;
}


void DisED(DISZ80 *d)
{
	int		o;

	o = GetNextOpCode(d);

/* Catch the solitary SLT pseudo-opcode */
   switch (o)
		  {
		  case 0xFB:
			AddToDisUnknown(d, "Super Loader Trap");
			return;
		  }

	if (o <= 0x3f)
	   if (DisED00to3F(d))
		  return;

	if (o >= 0x40 && o <= 0x7f)
	   if (DisED40to7F(d))
		  return;

	if (o >= 0x80 && o <= 0xbf)
		if (DisED80toBF(d))
		   return;

/* Unknown EDxx opcode */
	AddToDisUnknown(d, "Undocumented 8 T-State NOP");
	return;
}

/* ED00 - ED3F are currently only Z180 instructions */

int DisED00to3F(DISZ80 *d)
{
	int 	r, bb;

	if (d->cpuType < DCPU_Z180)
		return FALSE;

	bb = d->op & 7;
	r = (d->op >> 3) & 7;

	switch (bb)
		{
		case 0: 	/* ED 0x00 - 0x38 */
			AddToDisTab(d, "in0");
			ADDTODIS(Reg8Idx[r]);
			ADDTODIS(",(");
			AddToDis8BitAbs(d, FALSE);
			ADDTODIS(")");
			AddToDisCommentZ180(d);
			return TRUE;

		case 1: 	/* ED 0x01 - 0x39 */
			AddToDisTab(d, "out0");
			ADDTODIS("(");
			AddToDis8BitAbs(d, FALSE);
			ADDTODIS("),");
			ADDTODIS(Reg8Idx[r]);
			AddToDisCommentZ180(d);
			return TRUE;

		case 4: 	/* ED 0x04 - 0x3c */
			AddToDisTab(d, "tst");
			ADDTODIS(Reg8Idx[r]);
			AddToDisCommentZ180(d);
			return TRUE;
		}

	return FALSE;
}


int DisED40to7F(DISZ80 *d)
{
	char	Address[16];
	int		EDop;

/* First, let's get those nasty special case opcodes. */

	EDop = d->op;

	switch (EDop)
		{
		case 0x76:		/* This is SLP which clashes with the undocumented Z80's IM 1 */
			if (d->cpuType >= DCPU_Z180)
				{
				AddToDisTab(d, "slp");
				AddToDisCommentZ180(d);
				return TRUE;
				}
			break;

		case 0x4c:		/* The Z180's MLT instructions */
		case 0x5c:
		case 0x6c:
		case 0x7c:
			if (d->cpuType < DCPU_Z180)
				return FALSE;

			AddToDisTab(d, "mlt");
			ADDTODIS(Reg16Idx[(EDop >> 4) & 3]);
			AddToDisCommentZ180(d);
			return TRUE;

		case 0x64:		/* Z180's TST nn */
			if (d->cpuType < DCPU_Z180)
				return FALSE;

			AddToDisTab(d, "tst");
			AddToDis8BitAbs(d, FALSE);
			AddToDisCommentZ180(d);
			return TRUE;

		case 0x74:
			if (d->cpuType < DCPU_Z180)
				return FALSE;

			AddToDisTab(d, "tstio");
			ADDTODIS("(");
			AddToDis8BitAbs(d, FALSE);
			ADDTODIS(")");
			AddToDisCommentZ180(d);
			return TRUE;

/* Back to the regular Z80's stuff */

		case 0x45:
			AddToDisTab(d, "retn");
			MARKBLANKLINE;
			return TRUE;

		case 0x47:
			AddToDisTabLD(d, "i,a");
			return TRUE;

		case 0x4d:
			AddToDisTab(d, "reti");
			MARKBLANKLINE;
			return TRUE;

		case 0x4f:
			AddToDisTabLD(d, "r,a");
			return TRUE;

		case 0x57:
			AddToDisTabLD(d, "a,i");
			return TRUE;

		case 0x5f:
			AddToDisTabLD(d, "a,r");
			return TRUE;

		case 0x67:
			AddToDisTab(d, "rrd");
			return TRUE;

		case 0x6f:
			AddToDisTab(d, "rld");
			return TRUE;
		}

	switch (EDop & 7)
		{
		case 0:
			AddToDisTab(d, "in");
			ADDTODIS(Reg8AFIdx[(EDop >> 3) & 7] );
			ADDTODIS(",(c)");
			return TRUE;

		case 1:
			AddToDisTab(d, "out");
			ADDTODIS("(c),");
			ADDTODIS(Reg8AFIdx[(EDop >> 3) & 7] );
			return TRUE;

		case 2:
			AddToDisTab(d, (EDop & 0x8) ? "adc" : "sbc");
			AddToDisHLIXIY(d);
			ADDTODIS(",");
			AddToDisReg16(d, EDop >> 4);
			return TRUE;

		case 3:
			Make16BitNum(d, Address, Get16BitParam(d));
			AddRefEntry(d, d->lastRefAddr, d->lastPC, DISREF_ADDR);
			AddToDisTabLD(d, "");
			if (EDop & 8)
				{
				AddToDisReg16(d, EDop >> 4);
				ADDTODIS(",");
				ADDTODIS("(");
				ADDTODIS(Address);
				ADDTODIS(")");
				}
			else
				{
				ADDTODIS("(");
				ADDTODIS(Address);
				ADDTODIS(")");
				ADDTODIS(",");
				AddToDisReg16(d, EDop >> 4);
				}
			return TRUE;

		case 4:
			AddToDisTab(d, "neg"); 	/* It's a NEG */
			if (EDop != 0x44)
				AddToDisUndoc(d);	/* But undocumented? */
			return TRUE;

		case 5:
			AddToDisTab(d, "ret");
			AddToDisUndoc(d);
			MARKBLANKLINE;
			return TRUE;

		case 6:
			AddToDisTab(d, "im");		/* Interrupt mode... */
			ADDTODIS(IMModes[(EDop & 0x18) >> 3] );
			if ((EDop == 0x4e) || (EDop >= 0x60))
				AddToDisUndoc(d);
			return TRUE;
		}

	return FALSE;
}


int DisED80toBF(DISZ80 *d)
{
	int		op;

	op = d->op;

	if (d->cpuType >= DCPU_Z180)
		{
		switch (op)
			{
			case 0x83:		/* otim */
			case 0x8b:		/* otdm */
			case 0x93:		/* otimr */
			case 0x9b:		/* otdmr */
				AddToDisTab(d, Z180RepeatOps[(op >> 3) & 3]);
				AddToDisCommentZ180(d);
				return TRUE;
			}
		}

	if (op >= 0xA0)
		{
		if ((op & 7) > 3)
			return FALSE;		/* Don't know this! */

		AddToDisTab(d, RepeatOps[(op & 3)+((op & 0x18) >> 1)] );
		return TRUE;
		}

	return FALSE;
}


void Dis00to3F(DISZ80 *d)
{
	int		op;

	op = d->op;

	if (d->cpuType == DCPU_Z80GB)
		{
		switch(op)
			{
			case 0x08:			// ld (nn),sp
				AddToDisTabLD(d, "(");
				AddToDis16BitAbs(d, FALSE);
				ADDTODIS("),sp");
				AddRefEntry(d, d->lastRefAddr, d->lastPC, DISREF_INDIRECT);
				return;

			case 0x10:
				ADDTODIS("stop");
				return;

			case 0x22:
				AddToDisTabLD(d, "(hli),a");
				return;

			case 0x2a:
				AddToDisTabLD(d, "a,(hli)");
				return;

			case 0x32:
				AddToDisTabLD(d, "(hld),a");
				return;

			case 0x3a:
				AddToDisTabLD(d, "a,(hld)");
				return;
			}
		}

	switch (op & 0x0f)
		{
		case 0:
		case 8:
			switch ((op >> 3) & 7)
				{
				case 0: 	/* 0x00 */
					AddToDisTab(d, "nop");
					return;

				case 1: 	/* 0x08 */
					AddToDisTab(d, "ex");
					ADDTODIS("af,af'");
					return;

				case 2: 	/* 0x10 */ 
					AddToDisTab(d, "djnz");
					FlagFn(d, AddToDisRel8(d, FALSE));
					return;

				case 3: 	/* 0x18 */
					AddToDisTab(d, "jr");
					FlagFn(d, AddToDisRel8(d, FALSE));
					return;

				default:
					AddToDisTab(d, "jr");
					ADDTODIS(Conditions[(op >> 3) & 3] );
					FlagFn(d, AddToDisRel8(d, TRUE));
					return;
				}
		case 1:
			AddToDisTabLD(d, "");
			AddToDisReg16(d, op >> 4);
			AddToDis16BitAbs(d, TRUE);
			AddRefEntry(d, d->lastRefAddr, d->lastPC, DISREF_ADDR);
			return;

		case 2:
			switch ((op >> 4) & 3)
				{
				case 0: 	/* ld (bc),a */
				case 1: 	/* ld (de),a */
					AddToDisTabLD(d, "(");
					ADDTODIS(Reg16Idx[(op >> 4) & 1] );
					ADDTODIS("),a");
					return;

				case 2: 	/* 0x22 = ld (nn),hl */
				case 3: 	/* 0x32 = ld (nn),a */
					AddToDisTabLD(d, "(");
					AddToDis16BitAbs(d, FALSE);
					ADDTODIS("),");
						
					if (d->realop & 0x10)
						{
						ADDTODIS("a");
						}
					else
						{
						AddToDisHLIXIY(d);
						}

					AddRefEntry(d, d->lastRefAddr, d->lastPC, DISREF_INDIRECT);
					return;
				}

		case 3:
			AddToDisTab(d, "inc");
			AddToDisReg16(d, op>>4);
			return;

		case 4:
			AddToDisTab(d, "inc");
			AddToDisReg8(d, op>>3, op>>3);
			return;

		case 5:
			AddToDisTab(d, "dec");
			AddToDisReg8(d, op>>3, op>>3);
			return;

		case 6:
		case 0x0e:
			AddToDisTabLD(d, "");
			AddToDisReg8(d, op>>3, op>>3);
			AddToDis8BitAbs(d, TRUE);
			return;

		case 7:
		case 0x0f:
			AddToDisTab(d, AccRotType[(op>>3) & 7] );
			return;

		case 9:
			AddToDisTab(d, "add");
			AddToDisHLIXIY(d);
			ADDTODIS(",");
			AddToDisReg16(d, (op>>4) & 3);
			return;

		case 0x0a:
			switch ((op >> 4) & 3)
				{
				case 0:
				case 1:
					AddToDisTabLD(d, "a,(");
					ADDTODIS(Reg16Idx[(op >> 4) & 1] );
					ADDTODIS(")");
					return;

				case 2:
				case 3:
					if (op & 0x10)
						AddToDisTabLD(d, "a");
					else
						{
						AddToDisTabLD(d, "");
						AddToDisHLIXIY(d);
						}
					ADDTODIS(",(");
					AddToDis16BitAbs(d, FALSE);
					ADDTODIS(")");
					AddRefEntry(d, d->lastRefAddr, d->lastPC, DISREF_INDIRECT);
					return;
				}

		case 0xb:
			AddToDisTab(d, "dec");
			AddToDisReg16(d, (op>>4) & 3);
			return;


		case 0xc:
			AddToDisTab(d, "inc");
			AddToDisReg8(d, op>>3, op>>3);
			return;

		case 0xd:
			AddToDisTab(d, "dec");
			AddToDisReg8(d, op>>3, op>>3);
			return;
		}

	AddToDisUnknown(d, NULL);
	return;
}

void Dis40to7F(DISZ80 *d)
{
	if (d->op == 0x76)
		{
		AddToDisTab(d, "halt");
		return;
		}

	AddToDisTabLD(d, "");
	AddToDisReg8(d, d->realop >> 3, d->realop);
	ADDTODIS(",");
	AddToDisReg8(d, d->realop, d->realop >> 3);
	return;
}


void Dis80toBF(DISZ80 *d)
{
	int GenOp;

	GenOp = (d->op >> 3) & 7;
	AddToDisTab(d, BasicOps[GenOp]);

	if (GenOp < 2 || GenOp == 3)
		ADDTODIS("a,");

	AddToDisReg8(d, d->op, d->op);
	return;
}


void DisC0toFF(DISZ80 *d)
{
	int 	GenOp, op;
	char	port[32], buf[128], num[16], num2[16];
	char	offset;
	WORD	addr;

	op = d->op;

	if (d->cpuType == DCPU_Z80GB)
		{
		switch(op)
			{
			case 0xd3:
			case 0xdb:
			case 0xe3:
			case 0xe4:
			case 0xeb:
			case 0xec:
			case 0xf2:
			case 0xf4:
			case 0xfc:
				AddToDisUndocNop(d);
				return;

			case 0xd9:
				ADDTODIS("reti");
				return;

			case 0xe0:			// ld ($ff00+n),a
			case 0xf0:			// ld a,($ff00+n)
				addr = 0xff00 + GetNextOpCode(d);
				Make16BitNum(d, num, 0xff00);
				Make8BitNum(d, num2, addr & 0xff);
				
				AddToDisTabLD(d,"");
				if (op == 0xe0)
					sprintf(buf, "(%s+%s),a", num, num2);
				else
					sprintf(buf, "a,(%s+%s)", num, num2);
				ADDTODIS(buf);
				AddRefEntry(d, addr, d->lastPC, DISREF_INDIRECT);
				return;

			case 0xe2:			// ld ($ff00+c),a
				AddToDisTabLD(d, "");
				Make16BitNum(d, num, 0xff00);
				sprintf(buf, "(%s+c),a", num);
				ADDTODIS(buf);
				return;

			case 0xe8:				// add sp,nn
				AddToDisTab(d, "add");
				ADDTODIS("sp");
				AddToDis16BitAbs(d, TRUE);
				return;

			case 0xea:
				addr = Get16BitParam(d);
				Make16BitNum(d, num, addr);
				sprintf(buf, "(%s),a", num);
				AddToDisTabLD(d, buf);
				AddRefEntry(d, addr, d->lastPC, DISREF_INDIRECT);
				return;

			case 0xf8:
				offset = GetNextOpCode(d);
				AddToDisTab(d, "ldhl");
				ADDTODIS("sp,");
				if (offset >= 0)
					{
					Make8BitNum(d, num, offset);
					sprintf(buf, "%s", num);
					}
				else
					{
					Make8BitNum(d, num, -offset);
					sprintf(buf, "-%s", num);
					}
				ADDTODIS(buf);
				return;

			case 0xfa:
				addr = Get16BitParam(d);
				Make16BitNum(d, num, addr);
				sprintf(buf, "a,(%s)", num);
				AddToDisTabLD(d, buf);
				AddRefEntry(d, addr, d->lastPC, DISREF_INDIRECT);
				return;
			
			}
		}

	GenOp = (d->op >> 3) & 7;

	switch (op & 0xf)		/* Break it down into eight basics */
		{
		case 0:
		case 8:
			AddToDisTab(d, "ret");
			ADDTODIS(Conditions[GenOp]);
			MARKBLANKLINE;
			return;

		case 1: 		/* POP rr */
		case 5: 		/* PUSH rr */
			AddToDisTab(d, (op & 4) ? "push" : "pop");
			AddToDisReg16NoAnd(d, ((op >> 4) & 3) + (op >= 0xf0));
			return;

		case 2:
		case 0x0a:
			AddToDisTab(d, "jp");
			ADDTODIS(Conditions[GenOp]);
			FlagFn(d, AddToDis16BitAbs(d, TRUE));
			return;

		case 4:
		case 0x0c:
			AddToDisTab(d, "call");
			ADDTODIS(Conditions[GenOp]);
			FlagFn(d, AddToDis16BitAbs(d, TRUE));
			return;

		case 3:
			switch ((op >> 4) & 3)
				{
				case 0: 	/* 0xc3 */
					AddToDisTab(d, "jp");
					FlagFn(d, AddToDis16BitAbs(d, FALSE));
					return;

				case 1: 	/* 0xd3 */
					AddToDisTab(d, "out");
					Make8BitNum(d, port, GetNextOpCode(d));
					sprintf(buf, "(%s),a", port);
					ADDTODIS(buf);
					AddRefEntry(d, d->op, d->lastPC, DISREF_OUTPORT);
					return;

				case 2: 	/* 0xe3 */
					AddToDisTab(d, "ex");
					ADDTODIS("(sp),");
					AddToDisHLIXIY(d);
					return;

				case 3: 	/* 0xf3 */
					AddToDisTab(d, "di");
					return;
				}

		case 6:
		case 0x0e:
			AddToDisTab(d, BasicOps[GenOp] );
			if (GenOp < 2 || GenOp == 3)
				ADDTODIS("a,");
			AddToDis8BitAbs(d, FALSE);
			return;

		case 7:
		case 0x0f:
			AddToDisTab(d, "rst");
			Add8BitNum(d, op & (7	<< 3));
			return;

		case 9:
			switch ((op >> 4) & 3)
				{
				case 0: 	/* 0xc9 */
					AddToDisTab(d, "ret");
					MARKBLANKLINE;
					return;

				case 1: 	/* 0xd9 */
					AddToDisTab(d, "exx");
					return;

				case 2: 	/* 0xe9 */
					AddToDisTab(d, "jp");
					ADDTODIS("(");
					AddToDisHLIXIY(d);
					ADDTODIS(")");
					return;

				case 3: 	/* 0xf9 */
					AddToDisTabLD(d, "sp,");
					AddToDisHLIXIY(d);
					return;
				}


		case 0x0b:
			switch ((op >> 4) & 3)
				{
				case 1: 	/* 0xdb */
					AddToDisTab(d, "in");
					Make8BitNum(d, port, GetNextOpCode(d));
					sprintf(buf,"a,(%s)", port);
					ADDTODIS(buf);
					AddRefEntry(d, d->op, d->lastPC, DISREF_INPORT);
					return;

				case 2: 	/* 0xeb */
					AddToDisTab(d, "ex");
					ADDTODIS("de,hl");
					return;

				case 3: 	/* 0xfb */
					AddToDisTab(d, "ei");
					return;
				}



		case 0x0d:			/* N.B. this can only get here with #cd */
			AddToDisTab(d, "call");
			FlagFn(d, AddToDis16BitAbs(d, FALSE));
			return;
		}

	AddToDisUnknown(d, NULL);
}


void AddToDisTab(DISZ80 *d, char *str)
{
	int		l;
	char	buf[64];

	ADDTODIS(str);

	if (d->haveTabbed == FALSE)
		{
		l = strlen(d->disBuf);
		memset(buf, ' ', TABSIZE - l);
		buf[TABSIZE - l] = 0;
		ADDTODIS(buf);

		d->haveTabbed = TRUE;
		}
		
	return;
}

void AddToDisTabDB(DISZ80 *d)
{
	AddToDisTab(d, (d->layoutDefineByte == NULL) ? "db" : d->layoutDefineByte);
	return;
}


void AddToDisTabLD(DISZ80 *d, char *str)
{
	AddToDisTab(d, "ld");
	ADDTODIS(str);
	return;
}


void AddToDisCommentZ180(DISZ80 *d)
{
	AddToDisComment(d, "Z180 instruction");
	return;
}

void AddToDisComment(DISZ80 *d, char *str)
{
	if (!(d->Z80Flags & Z80COMMENT))
		{
		strcpy(d->commentBuf, d->pComment);
		d->Z80Flags |= Z80COMMENT;
		}

	assert((strlen(d->commentBuf) + strlen(str)) < sizeof(d->commentBuf));

	strcat(d->commentBuf, str);
	return;
}

void AddToDisHLIXIY(DISZ80 *d)
{
	if (d->Z80Flags & Z80IXIY)
		{
		ADDTODIS( (d->Z80Flags & Z80IX) ? "ix" : "iy");
		}
	else
		{
		ADDTODIS("hl");
		}

	return;
}


/*	AddToDisReg8(opcode)

	Adds b,c,d,e,h,l,(hl) or a to disassembly, taking into consideration
	the IX and IY prefixes. "op2" is used to determine whether a "IXl"
	reference is valid or not.
*/

void AddToDisReg8(DISZ80 *d, int op, int op2)
{
	char	num[16];
	char	buf[64];

	op &= 7;

	if (d->Z80Flags & Z80IXIY)
		{
		op2 &= 7;

		if (!(op & (Z80CB | Z80ED)) && (op2 != REG_HL) )
			{
			if (op == REG_L)
				{
				ADDTODIS((d->Z80Flags & Z80IX) ? "ixl" : "iyl");
				return;
				}
		
			if (op == REG_H)
				{
				ADDTODIS((d->Z80Flags & Z80IX) ? "ixh" : "iyh");
				return;
				}
			}

		if (op == REG_HL)
			{
			GetIXIYDisplacement(d);

			if (d->IXIYDisp >= 0)
				{
				Make8BitNum(d, num, d->IXIYDisp);
				sprintf(buf, "(%s+%s)", ((d->Z80Flags & Z80IX) ? "ix" : "iy"), num);
				}
			else
				{
				Make8BitNum(d, num, -d->IXIYDisp);
				sprintf(buf, "(%s-%s)", ((d->Z80Flags & Z80IX) ? "ix" : "iy"), num);
				}

			ADDTODIS(buf);
			return;
			}
		}

	ADDTODIS(Reg8Idx[op]);
	return;
}


/*	AddToDisReg16(opcode)

	Adds bc,de,hl or sp to disassembly, taking into consideration
	the IX and IY prefixes
*/

void AddToDisReg16(DISZ80 *d, int op)
{
	op &= 3;
	if ( (op == 2) && (d->Z80Flags & Z80IXIY) )
		AddToDisHLIXIY(d);
	else
		ADDTODIS(Reg16Idx[op]);
	return;
}

void AddToDisReg16NoAnd(DISZ80 *d, int op)
{
	if ( (op == 2) && (d->Z80Flags & Z80IXIY) )
		AddToDisHLIXIY(d);
	else
		ADDTODIS(Reg16Idx[op]);
	return;
}


WORD AddToDisRel8(DISZ80 *d, int CommaFlag)
{
	char	buf[64], num[16], o;

	if (CommaFlag)
		ADDTODIS(",");

	o = (char)GetNextOpCode(d);

	d->lastRefAddr = (WORD)(d->PC + o);
	Add16BitAddress(d, d->lastRefAddr);

	Make8BitNum(d, num, (o >= 0) ? o : -o);
	sprintf(buf, "(%s%s)", (o >= 0) ? "+" : "-", num);
	AddToDisComment(d, buf);
	return d->lastRefAddr;
}

void AddToDis8BitAbs(DISZ80 *d, int CommaFlag)
{
	if (CommaFlag)
		ADDTODIS(",");

	GetNextOpCode(d);
	Add8BitNum(d, d->op);
	return;
}

WORD AddToDis16BitAbs(DISZ80 *d, int CommaFlag)
{
	if (CommaFlag)
		ADDTODIS(",");

	Get16BitParam(d);
	Add16BitAddress(d, d->lastRefAddr);
	return d->lastRefAddr;
}

void	AddToDisUndoc(DISZ80 *d)
{
	AddToDisComment(d, "Undocumented");
	return;
}

void	AddToDisUndocNop(DISZ80 *d)
{
	ADDTODIS("nop");
	AddToDisComment(d, "Undocumented");
	return;
}



/*
	void AddToDisUnknown(char *Comment) 

	Handles the dumping of an unknown opcode sequence
*/

void AddToDisUnknown(DISZ80 *d, char *Comment)
{
	int 	i, numOpCodes;
	char	buf[64];
	
	AddToDisTabDB(d);
	
	numOpCodes = abs(d->PC - d->lastPC);
	d->PC = d->lastPC;

/* We're going to rewind back to the start of the bad opcode, so clear the hex stream dump */
	d->hexDisBuf[0] = 0;			

	for (i = 0; i < numOpCodes; i++)
		{
		Make8BitNum(d, buf, GetNextOpCode(d));
		if (i < (numOpCodes-1))
			strcat(buf, ", ");
		ADDTODIS(buf);
		}

	if (Comment == NULL)
		AddToDisComment(d, "Unknown opcode");
	else
		AddToDisComment(d, Comment);

	return;
}

char GetIXIYDisplacement(DISZ80 *d)
{
	if (!(d->Z80Flags & Z80GOTIXIYDISP))		/* Already got IXIY displacement? */
		{
		d->IXIYDisp = (char)GetNextOpCode(d);
		d->Z80Flags |= Z80GOTIXIYDISP;
		}

	return d->IXIYDisp;
}


WORD Get16BitParam(DISZ80 *d)
{
	d->lastRefAddr = (WORD)GetNextOpCode(d);
	d->lastRefAddr |= (GetNextOpCode(d) << 8);
	return d->lastRefAddr;
}


void FlagFn(DISZ80 *d, unsigned int Addr)
{
	if (d->labelledOutput == FALSE || d->currentPass < 2)
		return;

	assert(d->fnMap != NULL);
	assert(Addr < Z80MEMSIZE);
	d->fnMap[Addr] = TRUE;
	return;
}


int IsFnUsed(DISZ80 *d, unsigned int Addr)
{
	assert(d->fnMap != NULL);
	assert(Addr < Z80MEMSIZE);
	return (d->fnMap[Addr]);
}



BYTE* AllocateMap(DISZ80 *d, char *ErrorStr, unsigned int BytesWanted)
{
	BYTE	*MapPtr;

	MapPtr = (BYTE *)malloc(BytesWanted);

	if (MapPtr == NULL)
		{
		dZ80_Error(d, ErrorStr);
		}
	else
		{
		memset(MapPtr, 0, BytesWanted); 	/* Clear the map */
		}
		
	return MapPtr;
}


/* Create the output .asm file and header */

int CreateOutputASMFile(DISZ80 *d)
{
	char	MsgBuf[_MAX_PATH + 80];
	char	buf[256];
	time_t	secs_now;
	struct	tm *time_now;

/* Set up the time structures */

	time(&secs_now);
	time_now = localtime(&secs_now);

	if (d->outFileName != NULL)
		{
		d->outStream = fopen(d->outFileName, "wt");

		if (d->outStream == NULL)
			{
			sprintf(buf, "Couldn't create the output file %s", d->outFileName);
			dZ80_Error(d, buf);
			DisZ80CleanUp(d);
			return FALSE;
			}

		sprintf(MsgBuf, "%sDisassembly of the file \"%s\"\n%s\n", d->pComment, d->srcFileName, d->pComment);
		fwrite(MsgBuf, strlen(MsgBuf), 1, d->outStream);

		sprintf(MsgBuf, "%sCPU Type: %s\n%s\n", d->pComment, cpuTypeNames[d->cpuType], d->pComment);
		fwrite(MsgBuf, strlen(MsgBuf), 1, d->outStream);

		if (d->opMapFileName != NULL)
			{
			sprintf(MsgBuf, "%sUsing the opcode map file \"%s\"\n%s\n", d->pComment, d->opMapFileName, d->pComment);
			fwrite(MsgBuf, strlen(MsgBuf), 1, d->outStream);
			}

		sprintf(MsgBuf, "%sCreated with dZ80 %s\n%s\n%s", d->pComment, VersionString, d->pComment, d->pComment);
		fwrite(MsgBuf, strlen(MsgBuf), 1, d->outStream);

		strftime(MsgBuf, sizeof(MsgBuf), "on %A, %d of %B %Y at %I:%M %p", time_now);
		fwrite(MsgBuf, strlen(MsgBuf), 1, d->outStream);

		sprintf(MsgBuf, "\n%s\n", d->pComment);
		fwrite(MsgBuf, strlen(MsgBuf), 1, d->outStream);

		if (d->labelledOutput)
			{
			PrepareDisInstruction(d);
			AddToDisTab(d, "org");
			Make16BitNum(d, MsgBuf, d->disStart);
			strcat(MsgBuf,"\n");
			ADDTODIS(MsgBuf);
			WriteDisLine(d, d->lastPC);
			}
		}

	return TRUE;
}


int PrepareOpMap(DISZ80 *d)
{
	char	buf[256];
	FILE	*opStream;

	if (!(d->flags & DISFLAG_SINGLE))
		{
		if (d->opMapFileName != NULL)
			{
			if ((d->opMap = AllocateMap(d, "Couldn't allocate memory for the opcode map.", Z80MEMSIZE/8)) == NULL)
				{
				DisZ80CleanUp(d);
				return FALSE;
				}

			opStream = fopen(d->opMapFileName, "rb");

			if (opStream == NULL)
				{
				sprintf(buf, "Couldn't open the opcode map file %s.", d->opMapFileName);
				dZ80_Error(d, buf);
				DisZ80CleanUp(d);
				return FALSE;
				}

			if (fread(d->opMap, 1, Z80MEMSIZE / 8, opStream) < (Z80MEMSIZE / 8) )
				dZ80_Error(d, "Warning: Couldn't read the entire opcode map file");

			fclose(opStream);
			}
		}

	return TRUE;
}



void WriteReferenceFile(DISZ80 *d)
{
	unsigned int	t, n;
	char			MsgBuf[80 + _MAX_PATH];
	char			*TypeMsg;
	char			num1[32], num2[32];
	DISREF			*p;
	DISREFADDR		*ra;
	DISZ80			qd;
	FILE			*refStream;

	if ((d->flags & DISFLAG_SINGLE) || !(d->flags & DISFLAG_ANYREF))
		return;

	if (d->refFileName == NULL)
		{
		dZ80_Error(d, "Missing reference filename.");
		DisZ80CleanUp(d);
		return;
		}

	refStream = fopen(d->refFileName, "wt");
	if (refStream == NULL)
		{
		sprintf(MsgBuf, "Couldn't create the reference file \"%s\".", d->refFileName);
		dZ80_Error(d, MsgBuf);
		return;
		}

	sprintf(MsgBuf,"dZ80 %s Reference file from the disassembly of \"%s\".\n\n", VersionString, d->srcFileName);
	fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);

	for(t = 0; t < DISREF_TOTAL; t++)
		{
		switch(t)
			{
			case DISREF_INPORT:
				TypeMsg = "Input Port";
				break;

			case DISREF_OUTPORT:
				TypeMsg = "Output Port";
				break;

			case DISREF_ADDR:
				TypeMsg = "Direct address";
				break;
			
			case DISREF_INDIRECT:
				TypeMsg = "Indirect address";
				break;

			default:
				TypeMsg = "wah?";
				break;
			}

		n = d->numRefs[t];
		if (n)
			{
			sprintf(MsgBuf, "%s Reference (%d entries)\n", TypeMsg, n);
			fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);
			UnderlineText(refStream, MsgBuf);

			p = d->pRefHead[t];
			while(p != NULL)
				{
				Make16BitNum(d, num1, p->Addr);
				sprintf(MsgBuf, "%s %s. %u references:\n", TypeMsg, num1, p->Hits);
				fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);
				UnderlineText(refStream, MsgBuf);
				
				ra = p->pRefAddrHead;
				while (ra != NULL)
					{
					memset(&qd, 0, sizeof(qd));
					qd.mem0Start = d->mem0Start;
					qd.start = qd.end = ra->RefAddress;
					qd.flags = d->flags | DISFLAG_SINGLE;
					qd.cpuType = d->cpuType;
					dZ80_InheritRadix(&qd, d);
		
					dZ80_Disassemble(&qd);
					
					Make16BitNum(d, num2, ra->RefAddress);
					sprintf(MsgBuf, "    %s: %s\n", num2, qd.disBuf);
					fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);

					ra = ra->pNext;
					}

				sprintf(MsgBuf, "\n");
				fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);
				p = p->pNext;
				}

			sprintf(MsgBuf, "\n");
			fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);
			}
		}

	sprintf(MsgBuf, "End of reference file for \"%s\"\n\n", d->srcFileName);
	fwrite(MsgBuf, 1, strlen(MsgBuf), refStream);

	fclose(refStream);
	d->createdRefOK = TRUE;
	return;
}


void UnderlineText(FILE *stream, char *text)
{
	int 	l;
	char	buf[256];

	l = strlen(text) - 1;
	memset(buf, '-', l);
	buf[l] = 0;
	strcat(buf, "\n\n");
	fwrite(buf, 1, strlen(buf), stream);
	return;
}


void AddRefEntry(DISZ80 *d, int Addr, int PC, int RefType)
{
	DISREF			*p, *pLast, *pPrev;

/* Don't add reference entries if we're scanning for functions */
	if (d->currentPass != 1)
		return;

	switch (RefType)
		{
		case DISREF_INPORT:
			if (!(d->flags & DISFLAG_REFINPORT))
				return;
			break;

		case DISREF_OUTPORT:
			if (!(d->flags & DISFLAG_REFOUTPORT))
				return;
			break;

		case DISREF_ADDR:
		case DISREF_INDIRECT:
			if (d->flags & DISFLAG_REFLIMITRANGE)
				{
				if (Addr >= d->disStart && Addr <= d->disEnd)
					return;
				}

			if ((RefType == DISREF_ADDR) && !(d->flags & DISFLAG_REFADDR))
				return;

			if ((RefType == DISREF_INDIRECT) && !(d->flags & DISFLAG_REFINDIRECT))
				return;

			break;

		default:
			assert(FALSE);
			dZ80_Error(d, "Unexpected reference type.");
			return;
		}

/* 
	Locate the insertion point of this new entry, or if
	  there's already an existing one, use that
*/
	pLast = d->pRefHead[RefType];
	pPrev = NULL;

	while (pLast != NULL)
		{
		if (pLast->Addr == Addr)
			{
			AddReferenceAddr(d, pLast, PC);
			return;
			}
		else
			{
			if (pLast->Addr > Addr)
				break;
			}

		pPrev = pLast;
		pLast = pLast->pNext;
		}

/* We have a brand new entry (either at the head or tail of the list, or needs to be crow-barred in :) */

	p = malloc(sizeof(DISREF));
	if (p == NULL)
		return;

	memset(p, 0, sizeof(DISREF));
	
	p->pPrev = pPrev;					/* Link to previous entry (if any) */
	p->pNext = pLast;					/* Link the next to the..erm..next */

	if (pPrev != NULL)
		pPrev->pNext = p;				/* Link the following entry to this one (barge in)  */
	else
		d->pRefHead[RefType] = p;		/* Must be the first in the list */

	if (pLast != NULL)
		pLast->pPrev = p;				/* Link the following entry to me */

	p->RefType = RefType;
	p->Addr = (WORD)Addr;
	p->Hits = 0;
	
	AddReferenceAddr(d, p, PC);
	return;
}


void AddReferenceAddr(DISZ80 *d, DISREF *p, int PC)
{
	DISREFADDR	*n, *t;

	n = malloc(sizeof(DISREFADDR));
	if (n == NULL)
		return;

	memset(n, 0, sizeof(DISREFADDR));

	t = p->pRefAddrTail;

	if (t == NULL)
		{
		p->pRefAddrHead = p->pRefAddrTail = n;
		}
	else
		{
		assert(t->RefAddress < PC);
		t->pNext = n;
		p->pRefAddrTail = n;
		}

	n->RefAddress = (WORD)PC;
	p->Hits++;

	d->numRefs[p->RefType]++;
	return;
}


void DoProgress(DISZ80 *d, int forceUpdate)
{
	if (!(d->flags & DISFLAG_QUIET))
		{
		if (d->fnProgressCallback != NULL)
			{
			d->progressCounter--;
			if ((forceUpdate) || d->progressCounter <= 0)
				{
				d->fnProgressCallback(d);
				d->progressCounter = PROGRESSUPDATEFREQ;
				}
			}
		}
	
	return;
}


void Add16BitAddress(DISZ80 *d, WORD Addr)
{
	char	buf[32];

	if ((d->labelledOutput == TRUE) && (d->currentPass == 1) && (d->flags & DISFLAG_USELABELADDRS))
		{
		if (IsFnUsed(d, Addr))
			{
			sprintf(buf, "l%04x", Addr);
			ADDTODIS(buf);
			return;
			}
		}

	Add16BitNum(d, Addr);
	return;
}

void Add8BitNum(DISZ80 *d, int Num)
{
	char	buf[32];

	Make8BitNum(d, buf, Num);
	ADDTODIS(buf);
	return;
}

void Make8BitNum(DISZ80 *d, char *Dst, int Num)
{
	char	num[16];

	switch(d->layoutRadix)
		{
		case DZ80RADIX_OCTAL:
			sprintf(num, "%o", Num);
			break;

		case DZ80RADIX_DECIMAL:
			sprintf(num, "%d", Num);
			break;

		case DZ80RADIX_HEX:
			sprintf(num, "%02x", Num);
			break;
		}

	sprintf(Dst, "%s%s%s",
		(d->layoutNumberPrefix != NULL) ? d->layoutNumberPrefix : "",
		num,
		(d->layoutNumberSuffix != NULL) ? d->layoutNumberSuffix : ""
		);

	return;
}

void Add16BitNum(DISZ80 *d, int Num)
{
	char	buf[32];

	Make16BitNum(d, buf, Num);
	ADDTODIS(buf);
	return;
}

void Make16BitNum(DISZ80 *d, char *Dst, int Num)
{
	char	num[8];

	switch(d->layoutRadix)
		{
		case DZ80RADIX_OCTAL:
			sprintf(num, "%o", Num);
			break;

		case DZ80RADIX_DECIMAL:
			sprintf(num, "%d", Num);
			break;

		case DZ80RADIX_HEX:
			sprintf(num, "%04x", Num);
			break;
		}

	sprintf(Dst, "%s%s%s",
		(d->layoutNumberPrefix != NULL) ? d->layoutNumberPrefix : "",
		num,
		(d->layoutNumberSuffix != NULL) ? d->layoutNumberSuffix : ""
		);
	
	return;
}

void MakeLJustified16BitNum(DISZ80 *d, char *Dst, int Num)
{
	switch(d->layoutRadix)
		{
		case DZ80RADIX_OCTAL:
			sprintf(Dst, "%6o", Num);
			break;

		case DZ80RADIX_DECIMAL:
			sprintf(Dst, "%5d", Num);
			break;

		case DZ80RADIX_HEX:
			sprintf(Dst, "%04x", Num);
			break;
		}

	return;
}


void dZ80_StringToLower(char *s)
{
	while (*s)
		*s++ = (char)tolower(*s);

	return;
}

void dZ80_StringToUpper(char *s)
{
	while (*s)
		*s++ = (char)toupper(*s);

	return;
}

void dZ80_Error(DISZ80 *d, char *msg)
{
	if (d->fnPopupMessage != NULL)
		d->fnPopupMessage(msg);

	return;
}

void dZ80_ShowMsg(DISZ80 *d, char *msg)
{
	if(d->fnOutputMessage != NULL)
		d->fnOutputMessage(msg);

	return;
}

