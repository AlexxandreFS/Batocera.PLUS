#include "raine.h"
#include "newmem.h"
#include "readcpu.h"
#include "newcpu.h"
#include "cputbl.h"

#pragma warning( disable : 4702 4100 )

unsigned long op_4c40_0(UINT32 opcode) /* DIVL */
{
	UINT32 dstreg = opcode & 7;
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
return 4;
}
unsigned long op_4c50_0(UINT32 opcode) /* DIVL */
{
	UINT32 dstreg = opcode & 7;
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(2);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 8;
}
unsigned long op_4c58_0(UINT32 opcode) /* DIVL */
{
	UINT32 dstreg = opcode & 7;
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
m68k_incpc(2);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 8;
}
unsigned long op_4c60_0(UINT32 opcode) /* DIVL */
{
	UINT32 dstreg = opcode & 7;
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
m68k_incpc(2);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 9;
}
unsigned long op_4c68_0(UINT32 opcode) /* DIVL */
{
	UINT32 dstreg = opcode & 7;
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(4);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 10;
}
unsigned long op_4c70_0(UINT32 opcode) /* DIVL */
{
	UINT32 dstreg = opcode & 7;
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
}
return 11;
}
unsigned long op_4c78_0(UINT32 opcode) /* DIVL */
{
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(4);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 10;
}
unsigned long op_4c79_0(UINT32 opcode) /* DIVL */
{
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(6);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 12;
}
unsigned long op_4c7a_0(UINT32 opcode) /* DIVL */
{
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	unsigned int dsta = m68k_getpc () + 2;
	dsta += (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(4);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
return 10;
}
unsigned long op_4c7b_0(UINT32 opcode) /* DIVL */
{
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
}
}
return 11;
}
unsigned long op_4c7c_0(UINT32 opcode) /* DIVL */
{
{
m68k_incpc(2);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(0);
{
	INT32 dst = get_ilong(2);
m68k_incpc(6);
	m68k_divl(opcode, dst, extra, oldpc);
}
}
}
}
return 8;
}
unsigned long op_4c90_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4c98_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
	m68k_areg(regs, dstreg) = srca;
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4ca8_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4cb0_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
m68k_incpc(4);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
}
return 7;
}
unsigned long op_4cb8_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = (INT32)(INT16)get_iword(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4cb9_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = get_ilong(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_4cba_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_getpc () + 4;
	srca += (INT32)(INT16)get_iword(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4cbb_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = (INT32)(INT16)cpu_readmem24_word(srca); srca += 2; amask = movem_next[amask]; }
}
}
}
}
return 7;
}
unsigned long op_4cd0_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4cd8_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
	m68k_areg(regs, dstreg) = srca;
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4ce8_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4cf0_0(UINT32 opcode) /* MVMEL */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
m68k_incpc(4);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
}
return 7;
}
unsigned long op_4cf8_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = (INT32)(INT16)get_iword(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4cf9_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = get_ilong(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_4cfa_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
	unsigned int srca = m68k_getpc () + 4;
	srca += (INT32)(INT16)get_iword(4);
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4cfb_0(UINT32 opcode) /* MVMEL */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	while (dmask) { m68k_dreg(regs, movem_index1[dmask]) = cpu_readmem24_dword(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg(regs, movem_index1[amask]) = cpu_readmem24_dword(srca); srca += 4; amask = movem_next[amask]; }
}
}
}
}
return 7;
}
unsigned long op_4e40_0(UINT32 opcode) /* TRAP */
{
	UINT32 srcreg = (opcode & 15);
{
{
	UINT32 src = srcreg;
m68k_incpc(2);
	Exception(src+32,0);
}
}
return 2;
}
unsigned long op_4e50_0(UINT32 opcode) /* LINK */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int olda = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = olda;
{
	INT32 src = m68k_areg(regs, srcreg);
	cpu_writemem24_dword(olda,src);
	m68k_areg(regs, srcreg) = (m68k_areg(regs, 7));
{
	INT16 offs = get_iword(2);
	m68k_areg(regs, 7) += offs;
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_4e58_0(UINT32 opcode) /* UNLK */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_areg(regs, srcreg);
	m68k_areg(regs, 7) = src;
{
	unsigned int olda = m68k_areg(regs, 7);
{
	INT32 old = cpu_readmem24_dword(olda);
	m68k_areg(regs, 7) += 4;
	m68k_areg(regs, srcreg) = (old);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4e60_0(UINT32 opcode) /* MVR2USP */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel901; }
{
{
	INT32 src = m68k_areg(regs, srcreg);
	regs.usp = src;
}
}
}
m68k_incpc(2);
endlabel901: ;
return 2;
}
unsigned long op_4e68_0(UINT32 opcode) /* MVUSP2R */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel902; }
{
{
	m68k_areg(regs, srcreg) = (regs.usp);
}
}
}
m68k_incpc(2);
endlabel902: ;
return 2;
}
unsigned long op_4e70_0(UINT32 opcode) /* RESET */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel903; }
}
m68k_incpc(2);
endlabel903: ;
return 2;
}
unsigned long op_4e71_0(UINT32 opcode) /* NOP */
{
	(void)(opcode);
{
}
m68k_incpc(2);
return 2;
}
unsigned long op_4e72_0(UINT32 opcode) /* STOP */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel905; }
{
{
	INT16 src = get_iword(2);
	regs.sr = src;
	MakeFromSR();
	m68k_setstopped(1);
}
}
}
m68k_incpc(4);
endlabel905: ;
return 4;
}
unsigned long op_4e73_0(UINT32 opcode) /* RTE */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel906; }
{
	UINT16 newsr; UINT32 newpc; for (;;) {
{
	unsigned int sra = m68k_areg(regs, 7);
{
	INT16 sr = cpu_readmem24_word(sra);
	m68k_areg(regs, 7) += 2;
{
	unsigned int pca = m68k_areg(regs, 7);
{
	INT32 pc = cpu_readmem24_dword(pca);
	m68k_areg(regs, 7) += 4;
{
	unsigned int formata = m68k_areg(regs, 7);
{
	INT16 format = cpu_readmem24_word(formata);
	m68k_areg(regs, 7) += 2;
	newsr = sr; newpc = pc;
	if ((format & 0xF000) == 0x0000) { break; }
	else if ((format & 0xF000) == 0x1000) { ; }
	else if ((format & 0xF000) == 0x2000) { m68k_areg(regs, 7) += 4; break; }
	else if ((format & 0xF000) == 0x8000) { m68k_areg(regs, 7) += 50; break; }
	else if ((format & 0xF000) == 0x9000) { m68k_areg(regs, 7) += 12; break; }
	else if ((format & 0xF000) == 0xa000) { m68k_areg(regs, 7) += 24; break; }
	else if ((format & 0xF000) == 0xb000) { m68k_areg(regs, 7) += 84; break; }
	else { Exception(14,0); goto endlabel906; }
	regs.sr = newsr; MakeFromSR();
}
}
}
}
}
}
}
	regs.sr = newsr; MakeFromSR();
	m68k_setpc_rte(newpc);
}
}
endlabel906: ;
return 10;
}
unsigned long op_4e74_0(UINT32 opcode) /* RTD */
{
	(void)(opcode);
{
{
	unsigned int pca = m68k_areg(regs, 7);
{
	INT32 pc = cpu_readmem24_dword(pca);
	m68k_areg(regs, 7) += 4;
{
	INT16 offs = get_iword(2);
	m68k_areg(regs, 7) += offs;
	m68k_setpc_rte(pc);
}
}
}
}
return 8;
}
unsigned long op_4e75_0(UINT32 opcode) /* RTS */
{
	(void)(opcode);
{
	m68k_do_rts();
}
return 2;
}
unsigned long op_4e76_0(UINT32 opcode) /* TRAPV */
{
	(void)(opcode);
{
m68k_incpc(2);
	if (GET_VFLG) { Exception(7,m68k_getpc()); goto endlabel909; }
}
endlabel909: ;
return 2;
}
unsigned long op_4e77_0(UINT32 opcode) /* RTR */
{
	(void)(opcode);
{
	MakeSR();
{
	unsigned int sra = m68k_areg(regs, 7);
{
	INT16 sr = cpu_readmem24_word(sra);
	m68k_areg(regs, 7) += 2;
{
	unsigned int pca = m68k_areg(regs, 7);
{
	INT32 pc = cpu_readmem24_dword(pca);
	m68k_areg(regs, 7) += 4;
	regs.sr &= 0xFF00; sr &= 0xFF;
	regs.sr |= sr; m68k_setpc(pc);
	MakeFromSR();
}
}
}
}
}
return 8;
}
unsigned long op_4e7a_0(UINT32 opcode) /* MOVEC2 */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel911; }
{
{
	INT16 src = get_iword(2);
{
	int regno = (src >> 12) & 15;
	UINT32 *regp = regs.regs + regno;
	if (! m68k_movec2(src & 0xFFF, regp)) goto endlabel911;
}
}
}
}
m68k_incpc(4);
endlabel911: ;
return 4;
}
unsigned long op_4e7b_0(UINT32 opcode) /* MOVE2C */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel912; }
{
{
	INT16 src = get_iword(2);
{
	int regno = (src >> 12) & 15;
	UINT32 *regp = regs.regs + regno;
	if (! m68k_move2c(src & 0xFFF, regp)) goto endlabel912;
}
}
}
}
m68k_incpc(4);
endlabel912: ;
return 4;
}
unsigned long op_4e90_0(UINT32 opcode) /* JSR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_do_jsr(m68k_getpc() + 2, srca);
}
}
return 2;
}
unsigned long op_4ea8_0(UINT32 opcode) /* JSR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	m68k_do_jsr(m68k_getpc() + 4, srca);
}
}
return 4;
}
unsigned long op_4eb0_0(UINT32 opcode) /* JSR */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	m68k_do_jsr(m68k_getpc() + 0, srca);
}
}
}
return 5;
}
unsigned long op_4eb8_0(UINT32 opcode) /* JSR */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	m68k_do_jsr(m68k_getpc() + 4, srca);
}
}
return 4;
}
unsigned long op_4eb9_0(UINT32 opcode) /* JSR */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
	m68k_do_jsr(m68k_getpc() + 6, srca);
}
}
return 6;
}
unsigned long op_4eba_0(UINT32 opcode) /* JSR */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
	m68k_do_jsr(m68k_getpc() + 4, srca);
}
}
return 4;
}
unsigned long op_4ebb_0(UINT32 opcode) /* JSR */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
	m68k_do_jsr(m68k_getpc() + 0, srca);
}
}
}
return 5;
}
unsigned long op_4ed0_0(UINT32 opcode) /* JMP */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_setpc(srca);
}
}
return 2;
}
unsigned long op_4ee8_0(UINT32 opcode) /* JMP */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	m68k_setpc(srca);
}
}
return 4;
}
unsigned long op_4ef0_0(UINT32 opcode) /* JMP */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	m68k_setpc(srca);
}
}
}
return 5;
}
unsigned long op_4ef8_0(UINT32 opcode) /* JMP */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	m68k_setpc(srca);
}
}
return 4;
}
unsigned long op_4ef9_0(UINT32 opcode) /* JMP */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
	m68k_setpc(srca);
}
}
return 6;
}
unsigned long op_4efa_0(UINT32 opcode) /* JMP */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
	m68k_setpc(srca);
}
}
return 4;
}
unsigned long op_4efb_0(UINT32 opcode) /* JMP */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
	m68k_setpc(srca);
}
}
}
return 5;
}

unsigned long op_5000_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5010_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5018_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5020_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_5028_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5030_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_5038_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5039_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_5040_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5048_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5050_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5058_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5060_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_5068_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5070_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_5078_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5079_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_5080_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5088_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5090_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_5098_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_50a0_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_50a8_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_50b0_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
}
return 13;
}
unsigned long op_50b8_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_50b9_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_50c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(0) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_50c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(0)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_50d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_50d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_50e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_50e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_50f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_50f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_50f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(0) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_50fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(0)) { Exception(7,m68k_getpc()); goto endlabel962; }
}
}
m68k_incpc(4);
endlabel962: ;
return 4;
}
unsigned long op_50fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(0)) { Exception(7,m68k_getpc()); goto endlabel963; }
}
}
m68k_incpc(6);
endlabel963: ;
return 6;
}
unsigned long op_50fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(0)) { Exception(7,m68k_getpc()); goto endlabel964; }
}
m68k_incpc(2);
endlabel964: ;
return 2;
}
unsigned long op_5100_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5110_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5118_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5120_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_5128_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5130_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_5138_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5139_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_5140_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5148_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5150_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5158_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_5160_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_5168_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5170_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_5178_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_5179_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_5180_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5188_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5190_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_5198_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_51a0_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_51a8_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_51b0_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 src = srcreg;
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
}
return 13;
}
unsigned long op_51b8_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_51b9_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
{
{
	UINT32 src = srcreg;
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_51c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(1) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_51c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(1)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_51d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_51d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_51e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_51e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_51f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_51f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_51f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(1) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_51fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(1)) { Exception(7,m68k_getpc()); goto endlabel1000; }
}
}
m68k_incpc(4);
endlabel1000: ;
return 4;
}
unsigned long op_51fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(1)) { Exception(7,m68k_getpc()); goto endlabel1001; }
}
}
m68k_incpc(6);
endlabel1001: ;
return 6;
}
unsigned long op_51fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(1)) { Exception(7,m68k_getpc()); goto endlabel1002; }
}
m68k_incpc(2);
endlabel1002: ;
return 2;
}
unsigned long op_52c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(2) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_52c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(2)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_52d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_52d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_52e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_52e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_52f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_52f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_52f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(2) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_52fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(2)) { Exception(7,m68k_getpc()); goto endlabel1012; }
}
}
m68k_incpc(4);
endlabel1012: ;
return 4;
}
unsigned long op_52fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(2)) { Exception(7,m68k_getpc()); goto endlabel1013; }
}
}
m68k_incpc(6);
endlabel1013: ;
return 6;
}
unsigned long op_52fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(2)) { Exception(7,m68k_getpc()); goto endlabel1014; }
}
m68k_incpc(2);
endlabel1014: ;
return 2;
}
unsigned long op_53c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(3) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_53c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(3)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_53d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_53d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_53e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_53e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_53f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_53f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_53f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(3) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_53fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(3)) { Exception(7,m68k_getpc()); goto endlabel1024; }
}
}
m68k_incpc(4);
endlabel1024: ;
return 4;
}
unsigned long op_53fb_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(3)) { Exception(7,m68k_getpc()); goto endlabel1025; }
}
}
m68k_incpc(6);
endlabel1025: ;
return 6;
}
unsigned long op_53fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(3)) { Exception(7,m68k_getpc()); goto endlabel1026; }
}
m68k_incpc(2);
endlabel1026: ;
return 2;
}
unsigned long op_54c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(4) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_54c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(4)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_54d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_54d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_54e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_54e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_54f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_54f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_54f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(4) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_54fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(4)) { Exception(7,m68k_getpc()); goto endlabel1036; }
}
}
m68k_incpc(4);
endlabel1036: ;
return 4;
}
unsigned long op_54fb_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(4)) { Exception(7,m68k_getpc()); goto endlabel1037; }
}
}
m68k_incpc(6);
endlabel1037: ;
return 6;
}
unsigned long op_54fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(4)) { Exception(7,m68k_getpc()); goto endlabel1038; }
}
m68k_incpc(2);
endlabel1038: ;
return 2;
}
unsigned long op_55c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(5) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_55c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(5)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_55d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_55d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_55e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_55e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_55f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_55f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_55f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(5) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_55fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(5)) { Exception(7,m68k_getpc()); goto endlabel1048; }
}
}
m68k_incpc(4);
endlabel1048: ;
return 4;
}
unsigned long op_55fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(5)) { Exception(7,m68k_getpc()); goto endlabel1049; }
}
}
m68k_incpc(6);
endlabel1049: ;
return 6;
}
unsigned long op_55fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(5)) { Exception(7,m68k_getpc()); goto endlabel1050; }
}
m68k_incpc(2);
endlabel1050: ;
return 2;
}
unsigned long op_56c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(6) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_56c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(6)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_56d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_56d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_56e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_56e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_56f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_56f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_56f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(6) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_56fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(6)) { Exception(7,m68k_getpc()); goto endlabel1060; }
}
}
m68k_incpc(4);
endlabel1060: ;
return 4;
}
unsigned long op_56fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(6)) { Exception(7,m68k_getpc()); goto endlabel1061; }
}
}
m68k_incpc(6);
endlabel1061: ;
return 6;
}
unsigned long op_56fc_0(UINT32 opcode) /* TRAPcc */
{
{
	if (cctrue(6)) { Exception(7,m68k_getpc()); goto endlabel1062; }
}
m68k_incpc(2);
endlabel1062: ;
return 2;
}
unsigned long op_57c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(7) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_57c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(7)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_57d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_57d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_57e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_57e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_57f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_57f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_57f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(7) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_57fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(7)) { Exception(7,m68k_getpc()); goto endlabel1072; }
}
}
m68k_incpc(4);
endlabel1072: ;
return 4;
}
unsigned long op_57fb_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(7)) { Exception(7,m68k_getpc()); goto endlabel1073; }
}
}
m68k_incpc(6);
endlabel1073: ;
return 6;
}
unsigned long op_57fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(7)) { Exception(7,m68k_getpc()); goto endlabel1074; }
}
m68k_incpc(2);
endlabel1074: ;
return 2;
}
unsigned long op_58c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(8) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_58c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(8)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_58d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_58d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_58e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_58e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_58f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_58f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_58f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(8) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_58fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(8)) { Exception(7,m68k_getpc()); goto endlabel1084; }
}
}
m68k_incpc(4);
endlabel1084: ;
return 4;
}
unsigned long op_58fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(8)) { Exception(7,m68k_getpc()); goto endlabel1085; }
}
}
m68k_incpc(6);
endlabel1085: ;
return 6;
}
unsigned long op_58fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(8)) { Exception(7,m68k_getpc()); goto endlabel1086; }
}
m68k_incpc(2);
endlabel1086: ;
return 2;
}
unsigned long op_59c0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(9) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_59c8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(9)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_59d0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_59d8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_59e0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_59e8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_59f0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_59f8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_59f9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(9) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_59fa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(9)) { Exception(7,m68k_getpc()); goto endlabel1096; }
}
}
m68k_incpc(4);
endlabel1096: ;
return 4;
}
unsigned long op_59fb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(9)) { Exception(7,m68k_getpc()); goto endlabel1097; }
}
}
m68k_incpc(6);
endlabel1097: ;
return 6;
}
unsigned long op_59fc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(9)) { Exception(7,m68k_getpc()); goto endlabel1098; }
}
m68k_incpc(2);
endlabel1098: ;
return 2;
}
unsigned long op_5ac0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(10) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5ac8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(10)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5ad0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5ad8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5ae0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_5ae8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5af0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_5af8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5af9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(10) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_5afa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(10)) { Exception(7,m68k_getpc()); goto endlabel1108; }
}
}
m68k_incpc(4);
endlabel1108: ;
return 4;
}
unsigned long op_5afb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(10)) { Exception(7,m68k_getpc()); goto endlabel1109; }
}
}
m68k_incpc(6);
endlabel1109: ;
return 6;
}
unsigned long op_5afc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(10)) { Exception(7,m68k_getpc()); goto endlabel1110; }
}
m68k_incpc(2);
endlabel1110: ;
return 2;
}
unsigned long op_5bc0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(11) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5bc8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(11)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5bd0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5bd8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5be0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_5be8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5bf0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_5bf8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5bf9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(11) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_5bfa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(11)) { Exception(7,m68k_getpc()); goto endlabel1120; }
}
}
m68k_incpc(4);
endlabel1120: ;
return 4;
}
unsigned long op_5bfb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(11)) { Exception(7,m68k_getpc()); goto endlabel1121; }
}
}
m68k_incpc(6);
endlabel1121: ;
return 6;
}
unsigned long op_5bfc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(11)) { Exception(7,m68k_getpc()); goto endlabel1122; }
}
m68k_incpc(2);
endlabel1122: ;
return 2;
}
unsigned long op_5cc0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(12) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5cc8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(12)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5cd0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5cd8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5ce0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_5ce8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5cf0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_5cf8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5cf9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(12) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_5cfa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(12)) { Exception(7,m68k_getpc()); goto endlabel1132; }
}
}
m68k_incpc(4);
endlabel1132: ;
return 4;
}
unsigned long op_5cfb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(12)) { Exception(7,m68k_getpc()); goto endlabel1133; }
}
}
m68k_incpc(6);
endlabel1133: ;
return 6;
}
unsigned long op_5cfc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(12)) { Exception(7,m68k_getpc()); goto endlabel1134; }
}
m68k_incpc(2);
endlabel1134: ;
return 2;
}
unsigned long op_5dc0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(13) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5dc8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(13)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5dd0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5dd8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5de0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_5de8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5df0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_5df8_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5df9_0(UINT32 opcode) /* Scc */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(13) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_5dfa_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(13)) { Exception(7,m68k_getpc()); goto endlabel1144; }
}
}
m68k_incpc(4);
endlabel1144: ;
return 4;
}
unsigned long op_5dfb_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
{
	if (cctrue(13)) { Exception(7,m68k_getpc()); goto endlabel1145; }
}
}
m68k_incpc(6);
endlabel1145: ;
return 6;
}
unsigned long op_5dfc_0(UINT32 opcode) /* TRAPcc */
{
	(void)(opcode);
{
	if (cctrue(13)) { Exception(7,m68k_getpc()); goto endlabel1146; }
}
m68k_incpc(2);
endlabel1146: ;
return 2;
}
unsigned long op_5ec0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(14) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5ec8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(14)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5ed0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5ed8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5ee0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_5ee8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5ef0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_5ef8_0(UINT32 opcode) /* Scc */
{
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5ef9_0(UINT32 opcode) /* Scc */
{
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(14) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_5efa_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(14)) { Exception(7,m68k_getpc()); goto endlabel1156; }
}
}
m68k_incpc(4);
endlabel1156: ;
return 4;
}
unsigned long op_5efb_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(14)) { Exception(7,m68k_getpc()); goto endlabel1157; }
}
}
m68k_incpc(6);
endlabel1157: ;
return 6;
}

unsigned long op_5efc_0(UINT32 opcode) /* TRAPcc */
{
{
	if (cctrue(14)) { Exception(7,m68k_getpc()); goto endlabel1158; }
}
m68k_incpc(2);
endlabel1158: ;
return 2;
}
unsigned long op_5fc0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
{
	int val = cctrue(15) ? 0xff : 0;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((val) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_5fc8_0(UINT32 opcode) /* DBcc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 offs = get_iword(2);
	if (!cctrue(15)) {
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			m68k_incpc((INT32)offs + 2);
		return 6;
		}
	}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5fd0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5fd8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_5fe0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_5fe8_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5ff0_0(UINT32 opcode) /* Scc */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
}
return 7;
}
unsigned long op_5ff8_0(UINT32 opcode) /* Scc */
{
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_5ff9_0(UINT32 opcode) /* Scc */
{
{
{
	unsigned int srca = get_ilong(2);
{
	int val = cctrue(15) ? 0xff : 0;
	cpu_writemem24(srca,val);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_5ffa_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(15)) { Exception(7,m68k_getpc()); goto endlabel1168; }
}
}
m68k_incpc(4);
endlabel1168: ;
return 4;
}
unsigned long op_5ffb_0(UINT32 opcode) /* TRAPcc */
{
{
{
	if (cctrue(15)) { Exception(7,m68k_getpc()); goto endlabel1169; }
}
}
m68k_incpc(6);
endlabel1169: ;
return 6;
}
unsigned long op_5ffc_0(UINT32 opcode) /* TRAPcc */
{
{
	if (cctrue(15)) { Exception(7,m68k_getpc()); goto endlabel1170; }
}
m68k_incpc(2);
endlabel1170: ;
return 2;
}
unsigned long op_6000_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(0)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6001_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(0)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_60ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(0)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6100_0(UINT32 opcode) /* BSR */
{
{
{
	INT16 src = get_iword(2);
	INT32 s = (INT32)src + 2;
	m68k_do_bsr(m68k_getpc() + 4, s);
}
}
return 4;
}
unsigned long op_6101_0(UINT32 opcode) /* BSR */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	INT32 s = (INT32)src + 2;
	m68k_do_bsr(m68k_getpc() + 2, s);
}
}
return 2;
}
unsigned long op_61ff_0(UINT32 opcode) /* BSR */
{
{
{
	INT32 src = get_ilong(2);
	INT32 s = (INT32)src + 2;
	m68k_do_bsr(m68k_getpc() + 6, s);
}
}
return 6;
}
unsigned long op_6200_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(2)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6201_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(2)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_62ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(2)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6300_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(3)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6301_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(3)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_63ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(3)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6400_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(4)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6401_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(4)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_64ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(4)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6500_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(5)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6501_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(5)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_65ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(5)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6600_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(6)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6601_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(6)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_66ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(6)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6700_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(7)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6701_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(7)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_67ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(7)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6800_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(8)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6801_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(8)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_68ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(8)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6900_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(9)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6901_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(9)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_69ff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(9)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6a00_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(10)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6a01_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(10)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_6aff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(10)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6b00_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(11)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6b01_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(11)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_6bff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(11)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6c00_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(12)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6c01_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(12)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_6cff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(12)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6d00_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(13)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6d01_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(13)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_6dff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(13)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6e00_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(14)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6e01_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(14)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_6eff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(14)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_6f00_0(UINT32 opcode) /* Bcc */
{
{
{
	INT16 src = get_iword(2);
	if (!cctrue(15)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_6f01_0(UINT32 opcode) /* Bcc */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
{
{
	UINT32 src = srcreg;
	if (!cctrue(15)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_6fff_0(UINT32 opcode) /* Bcc */
{
{
{
	INT32 src = get_ilong(2);
	if (!cctrue(15)) goto didnt_jump;
	m68k_incpc ((INT32)src + 2);
	return 5;
didnt_jump:;
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_7000_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (INT32)(INT8)(opcode & 255);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	UINT32 src = srcreg;
{
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_8000_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_8010_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_8018_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_8020_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_8028_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_8030_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
}
return 7;
}
unsigned long op_8038_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_8039_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_803a_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_803b_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
}
return 7;
}
unsigned long op_803c_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_8040_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_8050_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_8058_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_8060_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_8068_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_8070_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
}
return 7;
}
unsigned long op_8078_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_8079_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_807a_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_807b_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
}
return 7;
}
unsigned long op_807c_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_8080_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_8090_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_8098_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_80a0_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_80a8_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_80b0_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
}
return 9;
}
unsigned long op_80b8_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_80b9_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_80ba_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_80bb_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
}
return 9;
}
unsigned long op_80bc_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_80c0_0(UINT32 opcode) /* DIVU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1253; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
endlabel1253: ;
return 70;
}
unsigned long op_80d0_0(UINT32 opcode) /* DIVU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1254; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1254: ;
return 72;
}
unsigned long op_80d8_0(UINT32 opcode) /* DIVU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1255; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1255: ;
return 72;
}
unsigned long op_80e0_0(UINT32 opcode) /* DIVU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1256; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1256: ;
return 73;
}
unsigned long op_80e8_0(UINT32 opcode) /* DIVU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1257; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1257: ;
return 74;
}
unsigned long op_80f0_0(UINT32 opcode) /* DIVU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1258; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
}
endlabel1258: ;
return 75;
}
unsigned long op_80f8_0(UINT32 opcode) /* DIVU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1259; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1259: ;
return 74;
}
unsigned long op_80f9_0(UINT32 opcode) /* DIVU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(6);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1260; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1260: ;
return 76;
}
unsigned long op_80fa_0(UINT32 opcode) /* DIVU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1261; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1261: ;
return 74;
}
unsigned long op_80fb_0(UINT32 opcode) /* DIVU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1262; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
}
endlabel1262: ;
return 75;
}
unsigned long op_80fc_0(UINT32 opcode) /* DIVU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception (5, oldpc); goto endlabel1263; } else {
	UINT32 newv = (UINT32)dst / (UINT32)(UINT16)src;
	UINT32 rem = (UINT32)dst % (UINT32)(UINT16)src;
	if (newv > 0xffff) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
endlabel1263: ;
return 72;
}
unsigned long op_8100_0(UINT32 opcode) /* SBCD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
	UINT16 newv_lo = (dst & 0xF) - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = (dst & 0xF0) - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_8108_0(UINT32 opcode) /* SBCD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT16 newv_lo = (dst & 0xF) - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = (dst & 0xF0) - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_8110_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_8118_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_8120_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_8128_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8130_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 9;
}
unsigned long op_8138_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8139_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8140_0(UINT32 opcode) /* PACK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	UINT16 val = m68k_dreg(regs, srcreg) + get_iword(2);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & 0xffffff00) | ((val >> 4) & 0xf0) | (val & 0xf);
}
m68k_incpc(4);
return 4;
}
unsigned long op_8148_0(UINT32 opcode) /* PACK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	UINT16 val;
	m68k_areg(regs, srcreg) -= areg_byteinc[srcreg];
	val = (UINT16)cpu_readmem24(m68k_areg(regs, srcreg));
	m68k_areg(regs, srcreg) -= areg_byteinc[srcreg];
	val = (val | ((UINT16)cpu_readmem24(m68k_areg(regs, srcreg)) << 8)) + get_iword(2);
	m68k_areg(regs, dstreg) -= areg_byteinc[dstreg];
	cpu_writemem24(m68k_areg(regs, dstreg),((val >> 4) & 0xf0) | (val & 0xf));
}
m68k_incpc(4);
return 4;
}
unsigned long op_8150_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_8158_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_8160_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_8168_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8170_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 9;
}
unsigned long op_8178_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8179_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8180_0(UINT32 opcode) /* UNPK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	UINT16 val = m68k_dreg(regs, srcreg);
	val = (((val << 4) & 0xf00) | (val & 0xf)) + get_iword(2);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & 0xffff0000) | (val & 0xffff);
}
m68k_incpc(4);
return 4;
}
unsigned long op_8188_0(UINT32 opcode) /* UNPK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	UINT16 val;
	m68k_areg(regs, srcreg) -= areg_byteinc[srcreg];
	val = (UINT16)cpu_readmem24(m68k_areg(regs, srcreg));
	val = (((val << 4) & 0xf00) | (val & 0xf)) + get_iword(2);
	m68k_areg(regs, dstreg) -= areg_byteinc[dstreg];
	cpu_writemem24(m68k_areg(regs, dstreg),val);
	m68k_areg(regs, dstreg) -= areg_byteinc[dstreg];
	cpu_writemem24(m68k_areg(regs, dstreg),val >> 8);
}
m68k_incpc(4);
return 4;
}
unsigned long op_8190_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_8198_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_81a0_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_81a8_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_81b0_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 13;
}
unsigned long op_81b8_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_81b9_0(UINT32 opcode) /* OR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src |= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_81c0_0(UINT32 opcode) /* DIVS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1291; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
endlabel1291: ;
return 79;
}
unsigned long op_81d0_0(UINT32 opcode) /* DIVS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1292; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1292: ;
return 81;
}
unsigned long op_81d8_0(UINT32 opcode) /* DIVS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1293; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1293: ;
return 81;
}
unsigned long op_81e0_0(UINT32 opcode) /* DIVS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(2);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1294; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1294: ;
return 82;
}
unsigned long op_81e8_0(UINT32 opcode) /* DIVS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1295; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1295: ;
return 83;
}
unsigned long op_81f0_0(UINT32 opcode) /* DIVS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1296; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
}
endlabel1296: ;
return 84;
}
unsigned long op_81f8_0(UINT32 opcode) /* DIVS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1297; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1297: ;
return 83;
}
unsigned long op_81f9_0(UINT32 opcode) /* DIVS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(6);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1298; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1298: ;
return 85;
}
unsigned long op_81fa_0(UINT32 opcode) /* DIVS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1299; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
endlabel1299: ;
return 83;
}
unsigned long op_81fb_0(UINT32 opcode) /* DIVS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1300; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
}
}
endlabel1300: ;
return 84;
}
unsigned long op_81fc_0(UINT32 opcode) /* DIVS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	if (src == 0) { SET_VFLG (0); Exception(5,oldpc); goto endlabel1301; } else {
	INT32 newv = (INT32)dst / (INT32)(INT16)src;
	UINT16 rem = (INT32)dst % (INT32)(INT16)src;
	if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) { SET_VFLG (1); SET_NFLG (1); SET_CFLG (0); } else
	{
	if (((INT16)rem < 0) != ((INT32)dst < 0)) rem = -rem;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_NFLG (((INT16)(newv)) < 0);
	newv = (newv & 0xffff) | ((UINT32)rem << 16);
	m68k_dreg(regs, dstreg) = (newv);
	}
	}
}
}
}
endlabel1301: ;
return 81;
}
unsigned long op_9000_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9010_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_9018_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_9020_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_9028_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_9030_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_9038_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_9039_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_903a_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_903b_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_903c_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_9040_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9048_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9050_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_9058_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_9060_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_9068_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_9070_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_9078_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_9079_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_907a_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_907b_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_907c_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_9080_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9088_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9090_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_9098_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_90a0_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_90a8_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_90b0_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_90b8_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_90b9_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_90ba_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_90bb_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_90bc_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_90c0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_90c8_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_90d0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_90d8_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_90e0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_90e8_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_90f0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 7;
}
unsigned long op_90f8_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_90f9_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_90fa_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_90fb_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 7;
}
unsigned long op_90fc_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_9100_0(UINT32 opcode) /* SUBX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = dst - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9108_0(UINT32 opcode) /* SUBX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT32 newv = dst - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_9110_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_9118_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_9120_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_9128_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_9130_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_9138_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_9139_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_9140_0(UINT32 opcode) /* SUBX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = dst - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9148_0(UINT32 opcode) /* SUBX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT32 newv = dst - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_9150_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_9158_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_9160_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_9168_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_9170_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_9178_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_9179_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_9180_0(UINT32 opcode) /* SUBX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = dst - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_9188_0(UINT32 opcode) /* SUBX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT32 newv = dst - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 16;
}
unsigned long op_9190_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_9198_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_91a0_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_91a8_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_91b0_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
}
return 13;
}
unsigned long op_91b8_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_91b9_0(UINT32 opcode) /* SUB */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_91c0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_91c8_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_91d0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_91d8_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_91e0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_91e8_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_91f0_0(UINT32 opcode) /* SUBA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 9;
}
unsigned long op_91f8_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_91f9_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_91fa_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_91fb_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 9;
}
unsigned long op_91fc_0(UINT32 opcode) /* SUBA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst - src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_b000_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b010_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}

unsigned long op_b018_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_b020_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_b028_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b030_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_b038_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b039_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_b03a_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b03b_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_b03c_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_b040_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b048_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b050_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_b058_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_b060_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_b068_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b070_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_b078_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b079_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_b07a_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b07b_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_b07c_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_b080_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b088_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b090_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b098_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b0a0_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_b0a8_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b0b0_0(UINT32 opcode) /* CMP */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_b0b8_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b0b9_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_b0ba_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b0bb_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_b0bc_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_b0c0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b0c8_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b0d0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_b0d8_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_b0e0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_b0e8_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b0f0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_b0f8_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b0f9_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_b0fa_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_b0fb_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_b0fc_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_b100_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b108_0(UINT32 opcode) /* CMPM */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
{
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b110_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b118_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b120_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_b128_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b130_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 9;
}
unsigned long op_b138_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b139_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_b140_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b148_0(UINT32 opcode) /* CMPM */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
{
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b150_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b158_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b160_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_b168_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b170_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 9;
}
unsigned long op_b178_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b179_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_b180_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b188_0(UINT32 opcode) /* CMPM */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_b190_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_b198_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_b1a0_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_b1a8_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_b1b0_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 13;
}
unsigned long op_b1b8_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_b1b9_0(UINT32 opcode) /* EOR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src ^= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_b1c0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b1c8_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_b1d0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b1d8_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_b1e0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_b1e8_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b1f0_0(UINT32 opcode) /* CMPA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_b1f8_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b1f9_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_b1fa_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_b1fb_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_b1fc_0(UINT32 opcode) /* CMPA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
}
}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_c000_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c010_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_c018_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_c020_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_c028_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_c030_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
}
return 7;
}
unsigned long op_c038_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_c039_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_c03a_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_c03b_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
}
}
return 7;
}
unsigned long op_c03c_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	INT8 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((src) & 0xff);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_c040_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c050_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_c058_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_c060_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_c068_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_c070_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
}
return 7;
}
unsigned long op_c078_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_c079_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_c07a_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_c07b_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
}
}
return 7;
}
unsigned long op_c07c_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_c080_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c090_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_c098_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_c0a0_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_c0a8_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c0b0_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
}
return 9;
}
unsigned long op_c0b8_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c0b9_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_c0ba_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c0bb_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
}
}
return 9;
}
unsigned long op_c0bc_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_c0c0_0(UINT32 opcode) /* MULU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 35;
}
unsigned long op_c0d0_0(UINT32 opcode) /* MULU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 37;
}
unsigned long op_c0d8_0(UINT32 opcode) /* MULU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 37;
}
unsigned long op_c0e0_0(UINT32 opcode) /* MULU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 38;
}
unsigned long op_c0e8_0(UINT32 opcode) /* MULU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 39;
}
unsigned long op_c0f0_0(UINT32 opcode) /* MULU */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 40;
}
unsigned long op_c0f8_0(UINT32 opcode) /* MULU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 39;
}
unsigned long op_c0f9_0(UINT32 opcode) /* MULU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(6);
return 41;
}
unsigned long op_c0fa_0(UINT32 opcode) /* MULU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 39;
}
unsigned long op_c0fb_0(UINT32 opcode) /* MULU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 40;
}
unsigned long op_c0fc_0(UINT32 opcode) /* MULU */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (UINT32)(UINT16)dst * (UINT32)(UINT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(4);
return 37;
}
unsigned long op_c100_0(UINT32 opcode) /* ABCD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
	UINT16 newv_lo = (src & 0xF) + (dst & 0xF) + (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = (src & 0xF0) + (dst & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo +=6; }
	newv = newv_hi + newv_lo;	SET_CFLG (cflg = (newv & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv += 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c108_0(UINT32 opcode) /* ABCD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT16 newv_lo = (src & 0xF) + (dst & 0xF) + (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = (src & 0xF0) + (dst & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo +=6; }
	newv = newv_hi + newv_lo;	SET_CFLG (cflg = (newv & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv += 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_c110_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_c118_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_c120_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_c128_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c130_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 9;
}
unsigned long op_c138_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c139_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_c140_0(UINT32 opcode) /* EXG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	m68k_dreg(regs, srcreg) = (dst);
	m68k_dreg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c148_0(UINT32 opcode) /* EXG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
	m68k_areg(regs, srcreg) = (dst);
	m68k_areg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c150_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_c158_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_c160_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_c168_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c170_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 9;
}
unsigned long op_c178_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_c179_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_c188_0(UINT32 opcode) /* EXG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
	m68k_dreg(regs, srcreg) = (dst);
	m68k_areg(regs, dstreg) = (src);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_c190_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_c198_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_c1a0_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_c1a8_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_c1b0_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 13;
}
unsigned long op_c1b8_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_c1b9_0(UINT32 opcode) /* AND */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	src &= dst;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_c1c0_0(UINT32 opcode) /* MULS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 35;
}
unsigned long op_c1d0_0(UINT32 opcode) /* MULS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 37;
}
unsigned long op_c1d8_0(UINT32 opcode) /* MULS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 37;
}
unsigned long op_c1e0_0(UINT32 opcode) /* MULS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 38;
}
unsigned long op_c1e8_0(UINT32 opcode) /* MULS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 39;
}
unsigned long op_c1f0_0(UINT32 opcode) /* MULS */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 40;
}
unsigned long op_c1f8_0(UINT32 opcode) /* MULS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 39;
}
unsigned long op_c1f9_0(UINT32 opcode) /* MULS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(6);
return 41;
}
unsigned long op_c1fa_0(UINT32 opcode) /* MULS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 39;
}
unsigned long op_c1fb_0(UINT32 opcode) /* MULS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 40;
}
unsigned long op_c1fc_0(UINT32 opcode) /* MULS */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = (INT32)(INT16)dst * (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(4);
return 37;
}
unsigned long op_d000_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d010_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_d018_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_d020_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_d028_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d030_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_d038_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d039_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_d03a_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d03b_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_d03c_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_d040_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d048_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d050_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_d058_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_d060_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_d068_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d070_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_d078_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d079_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_d07a_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d07b_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
}
}
return 7;
}
unsigned long op_d07c_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_d080_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d088_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d090_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d098_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d0a0_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_d0a8_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d0b0_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_d0b8_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d0b9_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_d0ba_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d0bb_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_d0bc_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_d0c0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d0c8_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d0d0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_d0d8_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_d0e0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_d0e8_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d0f0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 7;
}
unsigned long op_d0f8_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d0f9_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_d0fa_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_d0fb_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 7;
}
unsigned long op_d0fc_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_d100_0(UINT32 opcode) /* ADDX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = dst + src + (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d108_0(UINT32 opcode) /* ADDX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT32 newv = dst + src + (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_d110_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d118_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d120_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_d128_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d130_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_d138_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d139_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
{
{
UINT32 newv = ((INT8)(dst)) + ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT8)(~dst)) < ((UINT8)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_d140_0(UINT32 opcode) /* ADDX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = dst + src + (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d148_0(UINT32 opcode) /* ADDX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT32 newv = dst + src + (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_d150_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d158_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d160_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_d168_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d170_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
}
return 9;
}
unsigned long op_d178_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d179_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
{
UINT32 newv = ((INT16)(dst)) + ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT16)(~dst)) < ((UINT16)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_d180_0(UINT32 opcode) /* ADDX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
{
	UINT32 newv = dst + src + (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 2;
}

unsigned long op_d188_0(UINT32 opcode) /* ADDX */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	UINT32 newv = dst + src + (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 16;
}
unsigned long op_d190_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_d198_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_d1a0_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_d1a8_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_d1b0_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
}
return 13;
}
unsigned long op_d1b8_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_d1b9_0(UINT32 opcode) /* ADD */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
{
UINT32 newv = ((INT32)(dst)) + ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (((UINT32)(~dst)) < ((UINT32)(src)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(dsta,newv);
}
}
}
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_d1c0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d1c8_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_d1d0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d1d8_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_d1e0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_d1e8_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d1f0_0(UINT32 opcode) /* ADDA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 9;
}
unsigned long op_d1f8_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d1f9_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_d1fa_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_d1fb_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
}
}
return 9;
}
unsigned long op_d1fc_0(UINT32 opcode) /* ADDA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_areg(regs, dstreg);
{
	UINT32 newv = dst + src;
	m68k_areg(regs, dstreg) = (newv);
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e000_0(UINT32 opcode) /* ASR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	UINT32 sign = (0x80 & val) >> 7;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		val = 0xff & (UINT32)-sign;
		SET_CFLG (sign);
	COPY_CARRY;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
		val |= (0xff << (8 - cnt)) & (UINT32)-sign;
		val &= 0xff;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e008_0(UINT32 opcode) /* LSR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		SET_CFLG ((cnt == 8) & (val >> 7));
	COPY_CARRY;
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e010_0(UINT32 opcode) /* ROXR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
{	cnt--;
	{
	UINT32 carry;
	UINT32 hival = (val << 1) | GET_XFLG;
	hival <<= (7 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e018_0(UINT32 opcode) /* ROR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
{	UINT32 hival;
	cnt &= 7;
	hival = val << (8 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xff;
	SET_CFLG ((val & 0x80) >> 7);
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e020_0(UINT32 opcode) /* ASR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	UINT32 sign = (0x80 & val) >> 7;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		val = 0xff & (UINT32)-sign;
		SET_CFLG (sign);
	COPY_CARRY;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
		val |= (0xff << (8 - cnt)) & (UINT32)-sign;
		val &= 0xff;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e028_0(UINT32 opcode) /* LSR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		SET_CFLG ((cnt == 8) & (val >> 7));
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e030_0(UINT32 opcode) /* ROXR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 36) cnt -= 36;
	if (cnt >= 18) cnt -= 18;
	if (cnt >= 9) cnt -= 9;
	if (cnt > 0) {
	cnt--;
	{
	UINT32 carry;
	UINT32 hival = (val << 1) | GET_XFLG;
	hival <<= (7 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e038_0(UINT32 opcode) /* ROR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt > 0) {	UINT32 hival;
	cnt &= 7;
	hival = val << (8 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xff;
	SET_CFLG ((val & 0x80) >> 7);
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e040_0(UINT32 opcode) /* ASR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = (0x8000 & val) >> 15;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		val = 0xffff & (UINT32)-sign;
		SET_CFLG (sign);
	COPY_CARRY;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
		val |= (0xffff << (16 - cnt)) & (UINT32)-sign;
		val &= 0xffff;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e048_0(UINT32 opcode) /* LSR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		SET_CFLG ((cnt == 16) & (val >> 15));
	COPY_CARRY;
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e050_0(UINT32 opcode) /* ROXR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
{	cnt--;
	{
	UINT32 carry;
	UINT32 hival = (val << 1) | GET_XFLG;
	hival <<= (15 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e058_0(UINT32 opcode) /* ROR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
{	UINT32 hival;
	cnt &= 15;
	hival = val << (16 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffff;
	SET_CFLG ((val & 0x8000) >> 15);
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e060_0(UINT32 opcode) /* ASR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = (0x8000 & val) >> 15;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		val = 0xffff & (UINT32)-sign;
		SET_CFLG (sign);
	COPY_CARRY;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
		val |= (0xffff << (16 - cnt)) & (UINT32)-sign;
		val &= 0xffff;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e068_0(UINT32 opcode) /* LSR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		SET_CFLG ((cnt == 16) & (val >> 15));
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e070_0(UINT32 opcode) /* ROXR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 34) cnt -= 34;
	if (cnt >= 17) cnt -= 17;
	if (cnt > 0) {
	cnt--;
	{
	UINT32 carry;
	UINT32 hival = (val << 1) | GET_XFLG;
	hival <<= (15 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e078_0(UINT32 opcode) /* ROR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt > 0) {	UINT32 hival;
	cnt &= 15;
	hival = val << (16 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffff;
	SET_CFLG ((val & 0x8000) >> 15);
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e080_0(UINT32 opcode) /* ASR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	UINT32 sign = (0x80000000 & val) >> 31;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		val = 0xffffffff & (UINT32)-sign;
		SET_CFLG (sign);
	COPY_CARRY;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
		val |= (0xffffffff << (32 - cnt)) & (UINT32)-sign;
		val &= 0xffffffff;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e088_0(UINT32 opcode) /* LSR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		SET_CFLG ((cnt == 32) & (val >> 31));
	COPY_CARRY;
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e090_0(UINT32 opcode) /* ROXR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
{	cnt--;
	{
	UINT32 carry;
	UINT32 hival = (val << 1) | GET_XFLG;
	hival <<= (31 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e098_0(UINT32 opcode) /* ROR */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
{	UINT32 hival;
	cnt &= 31;
	hival = val << (32 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffffffff;
	SET_CFLG ((val & 0x80000000) >> 31);
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e0a0_0(UINT32 opcode) /* ASR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	UINT32 sign = (0x80000000 & val) >> 31;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		val = 0xffffffff & (UINT32)-sign;
		SET_CFLG (sign);
	COPY_CARRY;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
		val |= (0xffffffff << (32 - cnt)) & (UINT32)-sign;
		val &= 0xffffffff;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e0a8_0(UINT32 opcode) /* LSR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		SET_CFLG ((cnt == 32) & (val >> 31));
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (val & 1);
	COPY_CARRY;
		val >>= 1;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e0b0_0(UINT32 opcode) /* ROXR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 33) cnt -= 33;
	if (cnt > 0) {
	cnt--;
	{
	UINT32 carry;
	UINT32 hival = (val << 1) | GET_XFLG;
	hival <<= (31 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e0b8_0(UINT32 opcode) /* ROR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt > 0) {	UINT32 hival;
	cnt &= 31;
	hival = val << (32 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffffffff;
	SET_CFLG ((val & 0x80000000) >> 31);
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e0d0_0(UINT32 opcode) /* ASRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e0d8_0(UINT32 opcode) /* ASRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e0e0_0(UINT32 opcode) /* ASRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_e0e8_0(UINT32 opcode) /* ASRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e0f0_0(UINT32 opcode) /* ASRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int dataa = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
}
return 9;
}
unsigned long op_e0f8_0(UINT32 opcode) /* ASRW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e0f9_0(UINT32 opcode) /* ASRW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 cflg = val & 1;
	val = (val >> 1) | sign;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	SET_CFLG (cflg);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_e100_0(UINT32 opcode) /* ASL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 8 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else {
		UINT32 mask = (0xff << (7 - cnt)) & 0xff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80) >> 7);
	COPY_CARRY;
		val <<= 1;
		val &= 0xff;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e108_0(UINT32 opcode) /* LSL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		SET_CFLG (cnt == 8 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80) >> 7);
	COPY_CARRY;
		val <<= 1;
	val &= 0xff;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e110_0(UINT32 opcode) /* ROXL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
{	cnt--;
	{
	UINT32 carry;
	UINT32 loval = val >> (7 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e118_0(UINT32 opcode) /* ROL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
{	UINT32 loval;
	cnt &= 7;
	loval = val >> (8 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e120_0(UINT32 opcode) /* ASL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 8 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		UINT32 mask = (0xff << (7 - cnt)) & 0xff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80) >> 7);
	COPY_CARRY;
		val <<= 1;
		val &= 0xff;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e128_0(UINT32 opcode) /* LSL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 8) {
		SET_CFLG (cnt == 8 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80) >> 7);
	COPY_CARRY;
		val <<= 1;
	val &= 0xff;
	}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e130_0(UINT32 opcode) /* ROXL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 36) cnt -= 36;
	if (cnt >= 18) cnt -= 18;
	if (cnt >= 9) cnt -= 9;
	if (cnt > 0) {
	cnt--;
	{
	UINT32 carry;
	UINT32 loval = val >> (7 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e138_0(UINT32 opcode) /* ROL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT8 cnt = m68k_dreg(regs, srcreg);
{
	INT8 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT8)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt > 0) {
	UINT32 loval;
	cnt &= 7;
	loval = val >> (8 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((INT8)(val)) == 0);
	SET_NFLG (((INT8)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xff) | ((val) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e140_0(UINT32 opcode) /* ASL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 16 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else {
		UINT32 mask = (0xffff << (15 - cnt)) & 0xffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x8000) >> 15);
	COPY_CARRY;
		val <<= 1;
		val &= 0xffff;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e148_0(UINT32 opcode) /* LSL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		SET_CFLG (cnt == 16 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x8000) >> 15);
	COPY_CARRY;
		val <<= 1;
	val &= 0xffff;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e150_0(UINT32 opcode) /* ROXL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
{	cnt--;
	{
	UINT32 carry;
	UINT32 loval = val >> (15 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e158_0(UINT32 opcode) /* ROL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
{	UINT32 loval;
	cnt &= 15;
	loval = val >> (16 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e160_0(UINT32 opcode) /* ASL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 16 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		UINT32 mask = (0xffff << (15 - cnt)) & 0xffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x8000) >> 15);
	COPY_CARRY;
		val <<= 1;
		val &= 0xffff;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e168_0(UINT32 opcode) /* LSL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 16) {
		SET_CFLG (cnt == 16 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x8000) >> 15);
	COPY_CARRY;
		val <<= 1;
	val &= 0xffff;
	}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e170_0(UINT32 opcode) /* ROXL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 34) cnt -= 34;
	if (cnt >= 17) cnt -= 17;
	if (cnt > 0) {
	cnt--;
	{
	UINT32 carry;
	UINT32 loval = val >> (15 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e178_0(UINT32 opcode) /* ROL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 cnt = m68k_dreg(regs, srcreg);
{
	INT16 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = (UINT16)data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt > 0) {
	UINT32 loval;
	cnt &= 15;
	loval = val >> (16 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e180_0(UINT32 opcode) /* ASL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 32 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else {
		UINT32 mask = (0xffffffff << (31 - cnt)) & 0xffffffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80000000) >> 31);
	COPY_CARRY;
		val <<= 1;
		val &= 0xffffffff;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e188_0(UINT32 opcode) /* LSL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		SET_CFLG (cnt == 32 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80000000) >> 31);
	COPY_CARRY;
		val <<= 1;
	val &= 0xffffffff;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e190_0(UINT32 opcode) /* ROXL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
{	cnt--;
	{
	UINT32 carry;
	UINT32 loval = val >> (31 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e198_0(UINT32 opcode) /* ROL */
{
	UINT32 srcreg = imm8_table[((opcode >> 9) & 7)];
	UINT32 dstreg = opcode & 7;
{
{
	UINT32 cnt = srcreg;
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
{	UINT32 loval;
	cnt &= 31;
	loval = val >> (32 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffffffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e1a0_0(UINT32 opcode) /* ASL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		SET_VFLG (val != 0);
		SET_CFLG (cnt == 32 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		UINT32 mask = (0xffffffff << (31 - cnt)) & 0xffffffff;
		SET_VFLG ((val & mask) != mask && (val & mask) != 0);
		val <<= cnt - 1;
		SET_CFLG ((val & 0x80000000) >> 31);
	COPY_CARRY;
		val <<= 1;
		val &= 0xffffffff;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e1a8_0(UINT32 opcode) /* LSL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 32) {
		SET_CFLG (cnt == 32 ? val & 1 : 0);
	COPY_CARRY;
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG ((val & 0x80000000) >> 31);
	COPY_CARRY;
		val <<= 1;
	val &= 0xffffffff;
	}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e1b0_0(UINT32 opcode) /* ROXL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt >= 33) cnt -= 33;
	if (cnt > 0) {
	cnt--;
	{
	UINT32 carry;
	UINT32 loval = val >> (31 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG) << cnt) | (loval >> 1);
	SET_XFLG (carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (GET_XFLG);
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e1b8_0(UINT32 opcode) /* ROL */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 cnt = m68k_dreg(regs, srcreg);
{
	INT32 data = m68k_dreg(regs, dstreg);
{
	UINT32 val = data;
	cnt &= 63;
	CLEAR_CZNV;
	if (cnt > 0) {
	UINT32 loval;
	cnt &= 31;
	loval = val >> (32 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffffffff;
	SET_CFLG (val & 1);
}
	SET_ZFLG (((INT32)(val)) == 0);
	SET_NFLG (((INT32)(val)) < 0);
	m68k_dreg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_e1d0_0(UINT32 opcode) /* ASLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e1d8_0(UINT32 opcode) /* ASLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e1e0_0(UINT32 opcode) /* ASLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_e1e8_0(UINT32 opcode) /* ASLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e1f0_0(UINT32 opcode) /* ASLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int dataa = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
}
return 9;
}
unsigned long op_e1f8_0(UINT32 opcode) /* ASLW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e1f9_0(UINT32 opcode) /* ASLW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 sign = 0x8000 & val;
	UINT32 sign2;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
	sign2 = 0x8000 & val;
	SET_CFLG (sign != 0);
	COPY_CARRY;
	SET_VFLG (GET_VFLG | (sign2 != sign));
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_e2d0_0(UINT32 opcode) /* LSRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT32 val = (UINT16)data;
	UINT32 carry = val & 1;
	val >>= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
