#include <stdio.h>
#include "memory.h"
#include "mz80help.h"

extern UINT8 *Z80ROM;

void mame_addportsa(struct IO_ReadPort *rp,struct IO_WritePort *wp) {
  while (!IS_MEMPORT_END(rp)) {
    if (rp->start < 0xff) {
      fprintf(stderr,"adding read port %d\n",rp->start);
      AddZ80AReadPort((UINT16)rp->start, (UINT16)rp->end, rp->handler,    NULL);
    } else {
      fprintf(stderr,"Ignore read port %d\n",rp->start);
    }
    rp++;
  }
  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,               NULL);
  AddZ80AReadPort(  -1,   -1, NULL,                        NULL);

  while (!IS_MEMPORT_END(wp)) { 
    if (wp->start < 0xff) {
      fprintf(stderr,"adding write port %d\n",wp->start);
      AddZ80AWritePort((UINT16)wp->start, (UINT16)wp->end, wp->handler,    NULL);
    }
    wp++;
  }
  AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,              NULL);
  AddZ80AWritePort(  -1,   -1, NULL,                        NULL);
}

void mame_addz80mema(struct Memory_ReadAddress *rm,
		     struct Memory_WriteAddress *wm) {
  while (!IS_MEMPORT_END(rm)) {
    if (rm->start < 0xffff) {
      fprintf(stderr,"adding read mem %d\n",rm->start);
      switch(rm->type) {
      case MRA_RAM :
	AddZ80AReadByte(rm->start,rm->end,NULL,Z80RAM+rm->start);
	break;
      case MRA_ROM:
      case MRA_BANK1:
	AddZ80AReadByte(rm->start,rm->end,NULL,Z80ROM+rm->start);
	break;
      default:
	/* Error !!! */
		  break;
      }
    }
    rm++;
  }
  //  AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,       NULL);
  AddZ80AReadByte(    -1,     -1, NULL,                NULL);
  
  while (!IS_MEMPORT_END(wm)) {
    if (wm->start < 0xffff) {
      fprintf(stderr,"adding read mem %d\n",wm->start);
      switch(wm->type) {
      case MWA_RAM :
	AddZ80AWriteByte(wm->start,wm->end,NULL,Z80RAM+wm->start);
	break;
      case MWA_ROM:
	AddZ80AWriteByte(wm->start,wm->end,DefBadWriteZ80,     NULL);
	break;
      default:
	/* Error !!! */
		  break;
      }
      AddZ80AWriteByte(    -1,     -1, NULL,               NULL);    
    }
    wm++;
  }
}
