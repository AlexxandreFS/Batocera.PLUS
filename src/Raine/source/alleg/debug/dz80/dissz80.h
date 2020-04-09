/* dZ80 Disassembler Header */

#ifndef _MIDISSZ80_
#define _MIDISSZ80_

#ifdef __cplusplus
extern "C" {
#endif

#define Z80MEMSIZE				65536
#define	Z80DIRECTIVEMAXLEN		8			/* For user "db" and ";"'s */

#define DISFLAG_OPCODEDUMP		0x01
#define DISFLAG_ADDRDUMP		0x02
#define DISFLAG_UPPER			0x04
#define DISFLAG_CONSOLE 		0x08
#define DISFLAG_VERBOSE 		0x10
#define DISFLAG_QUIET			0x20
#define DISFLAG_LABELLED		0x40
#define DISFLAG_REFINPORT		0x80
#define DISFLAG_REFOUTPORT		0x100
#define DISFLAG_REFADDR 		0x200
#define DISFLAG_REFINDIRECT 	0x400
#define DISFLAG_REFLIMITRANGE	0x800
#define DISFLAG_USELABELADDRS	0x1000
#define DISFLAG__SPARE1__	 	0x2000	/* Spare */
#define DISFLAG_NOLINECMDS		0x4000	/* Ignore line commands */
#define	DISFLAG_SINGLE			0x8000	/* Disassemble a single instruction */

/* These options are used by the Windows version of dZ80 */
#define DISFLAG_AUTOOUTFILENAME 0x40000000	/* Auto write to (src).asm */
#define DISFLAG_SHOWASM 		0x80000000	/* Show the assembly when done */

/* Reference listing stuff */
#define DISFLAG_ANYREF			(DISFLAG_REFINPORT | DISFLAG_REFOUTPORT | DISFLAG_REFADDR | DISFLAG_REFINDIRECT)


enum dz80Cpus
	{
	DCPU_Z80GB,
	DCPU_Z80,
	DCPU_Z180,

	DCPU_TOTAL
	};


enum dz80Passes
	{
	DPASS_NONE,
	DPASS_WRITINGOUT,
	DPASS_SCANNING,

	DPASS_TOTAL
	};



enum dz80Errors
	{
	DERR_NONE,
	DERR_OUTOFMEM,
	DERR_COULDNTCREATEFILE,
	DERR_COULDNTWRITETOFILE,
	DERR_BADOPCODELENGTH,
	DERR_INVALIDPARAMS,

	DERR_TOTAL
	};

enum DZ80RADIX
{
	DZ80RADIX_HEX,
	DZ80RADIX_DECIMAL,
	DZ80RADIX_OCTAL,		

	DZ80RADIX_TOTAL
};

#define	DZ80RADIX_DEFAULT	DZ80RADIX_HEX



enum DISREF_TYPES
{
	DISREF_INPORT,
	DISREF_OUTPORT,
	DISREF_ADDR,
	DISREF_INDIRECT,

	DISREF_TOTAL
};


typedef struct DISREFADDR
{
	WORD				RefAddress;
	struct DISREFADDR	*pNext;
} DISREFADDR;

typedef struct DISREF
{
	WORD		RefType;				/* Reference type */
	WORD		Addr;					/* Memory or port address */
	WORD		Hits;					/* Number of times referenced */
	DISREFADDR	*pRefAddrHead;			/* Pointer to the list of referenced addresses */
	DISREFADDR	*pRefAddrTail;			/* Pointer to the last referenced address */

	struct DISREF *pPrev;
	struct DISREF *pNext;
} DISREF;


typedef struct DISZ80
{
	BYTE		*mem0Start; 			/* Pointer to Z80's zero address */
	WORD		start;					/* Starting disassembler address */
	WORD		end;					/* Ending disassembler address */
	int			flags;					/* See DISFLAG_ defines */
	int 		numInstructions;		/* How many instructions were disassembled */
	int 		createdRefOK;			/* Set to TRUE if created .ref file OK */
	char		*srcFileName;			/* Used only to display the source filename in the report header */
	char		*outFileName;			/* Destination assembler file */
	char		*opMapFileName; 		/* Opcode map file name */
	char		*refFileName;			/* Reference file name */

/* New CPU type */
	BYTE		cpuType;				/* See the DCPU_ enums */
	
/* New flexible number formats */
	BYTE		layoutRadix;			/* Do ya want hex with that? */
	char		*layoutComment; 		/* The string used as a comment marker */
	char		*layoutNumberPrefix;		
	char		*layoutNumberSuffix; 
	char		*layoutDefineByte;		/* Default of "db" */

/* Pointer to the function callbacks */
	void		(*fnProgressCallback)(struct DISZ80 *d);
	void		(*fnPopupMessage)(char *msg);
	void		(*fnOutputMessage)(char *msg);

/* dZ80 private workspace stuff - hands off ;) */
	char		hexDisBuf[32];			/* Holds the hex. disassembly (easy one!) */
	char		disBuf[128];			/* Holds the disassembly */
	char		commentBuf[128];
	WORD		lastDisPC, lastRefAddr, disStart, disEnd;
	int			op,	realop, lineCmd;
	BYTE		*Z80MemBase;
	char		IXIYDisp;				/* The IXIY displacement (-128 to 127) */
	int			Z80Flags;
	int			currentPass, totalPasses;
	int			numRecursions;
	BYTE		*fnMap,	*opMap;
	DISREF		*pRefHead[DISREF_TOTAL];
	unsigned int numRefs[DISREF_TOTAL];
	DWORD		bytesToProcess,	bytesProcessed;
	FILE		*outStream,	*refStream;
	int			labelledOutput, dissingToConsole, haveTabbed;
	int			progressCounter;
	WORD		PC, lastPC;
	char		*pComment;				/* Pointer to the customisable comment string */
	
} DISZ80;



void	dZ80_SetDefaultOptions(DISZ80 *Dis);
int 	dZ80_Disassemble(DISZ80 *Dis);
void	dZ80_SetDisassemblyRadix(DISZ80 *Dis, int Radix);
int		dZ80_SingleDisassembly(DISZ80 *Dis);
void	dZ80_InheritRadix(DISZ80 *dst, DISZ80 *src);
char	*dz80_GetVersionString(void);
void	dZ80_StringToLower(char *s);
void	dZ80_StringToUpper(char *s);


extern char *cpuTypeNames[DCPU_TOTAL];

#ifdef __cplusplus
};
#endif

#endif		/* _MIDISSZ80_ */
