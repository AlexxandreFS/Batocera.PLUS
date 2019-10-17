// Interface for raine to dz80.
// Thanks to the author for making things so easy (example.c)

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "types.h"
#include "dissz80.h"
#include "deftypes.h"
#include "dz80.h"

static DISZ80	*pDis = NULL;	/* Pointer to the Disassembly structure */

int process_adr(UINT8 *base, UINT16 dAddr, dz80_buff buff)
{
  int		line, err;		/* line count */

  if (!pDis) {
    pDis = malloc(sizeof(DISZ80));
    if (pDis == NULL)
      {
	printf("Cannot allocate %d bytes\n", sizeof(DISZ80));
	exit(1);
      }
    
    /* Set up dZ80's structure - not a lot */
    memset(pDis, 0, sizeof(DISZ80));
    dZ80_SetDefaultOptions(pDis);
    pDis->cpuType = DCPU_Z80;
    pDis->flags |= DISFLAG_SINGLE;
  }
  pDis->mem0Start = base;
  
  /* And we're off! */ 
  for(line=0; line < NBLINES; line++)
    {
      pDis->start = pDis->end = dAddr;
		
      err = dZ80_Disassemble(pDis);
      if (err != DERR_NONE)
	{
	  break;
	}
		
      /* Display the disassembled line */
      sprintf(buff[line],"%04x %-8s %s", dAddr, pDis->hexDisBuf, pDis->disBuf);
		
      /* Point to the next instruction */
      dAddr += (WORD)pDis->bytesProcessed;
    }
  return err;
}
