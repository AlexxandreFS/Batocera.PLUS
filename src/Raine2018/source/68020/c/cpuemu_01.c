#include "raine.h"
#include "newmem.h"
#include "readcpu.h"
#include "newcpu.h"
#include "cputbl.h"

#pragma warning( disable : 4702 4100 )

unsigned long op_0_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_10_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_18_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_20_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_28_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_30_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_38_0(UINT32 opcode) /* OR */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_39_0(UINT32 opcode) /* OR */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_3c_0(UINT32 opcode) /* ORSR */
{
	(void)(opcode);
{
	MakeSR();
{
	INT16 src = get_iword(2);
	src &= 0xFF;
	regs.sr |= src;
	MakeFromSR();
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_40_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_50_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_58_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_60_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_68_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_70_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_78_0(UINT32 opcode) /* OR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_79_0(UINT32 opcode) /* OR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_7c_0(UINT32 opcode) /* ORSR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel18; }
{
	MakeSR();
{
	INT16 src = get_iword(2);
	regs.sr |= src;
	MakeFromSR();
}
}
}
m68k_incpc(4);
endlabel18: ;
return 4;
}
unsigned long op_80_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_90_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_98_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_a0_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 15;
}
unsigned long op_a8_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_b0_0(UINT32 opcode) /* OR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
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
return 17;
}
unsigned long op_b8_0(UINT32 opcode) /* OR */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_b9_0(UINT32 opcode) /* OR */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
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
m68k_incpc(10);
return 18;
}
unsigned long op_d0_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel27; }
}
}
}
}
m68k_incpc(4);
endlabel27: ;
return 4;
}
unsigned long op_e8_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel28; }
}
}
}
}
m68k_incpc(6);
endlabel28: ;
return 6;
}
unsigned long op_f0_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel29; }
}
}
}
}
}
endlabel29: ;
return 7;
}
unsigned long op_f8_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel30; }
}
}
}
}
m68k_incpc(6);
endlabel30: ;
return 6;
}
unsigned long op_f9_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel31; }
}
}
}
}
m68k_incpc(8);
endlabel31: ;
return 8;
}
unsigned long op_fa_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel32; }
}
}
}
}
m68k_incpc(6);
endlabel32: ;
return 6;
}
unsigned long op_fb_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT8)cpu_readmem24(dsta); upper = (INT32)(INT8)cpu_readmem24(dsta+1);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT8)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel33; }
}
}
}
}
}
endlabel33: ;
return 7;
}
unsigned long op_100_0(UINT32 opcode) /* BTST */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_108_0(UINT32 opcode) /* MVPMR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int memp = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	UINT16 val = (cpu_readmem24(memp) << 8) + cpu_readmem24(memp + 2);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_110_0(UINT32 opcode) /* BTST */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_118_0(UINT32 opcode) /* BTST */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_120_0(UINT32 opcode) /* BTST */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_128_0(UINT32 opcode) /* BTST */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_130_0(UINT32 opcode) /* BTST */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
}
return 7;
}
unsigned long op_138_0(UINT32 opcode) /* BTST */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_139_0(UINT32 opcode) /* BTST */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_13a_0(UINT32 opcode) /* BTST */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_getpc () + 2;
	dsta += (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_13b_0(UINT32 opcode) /* BTST */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
}
return 7;
}
unsigned long op_13c_0(UINT32 opcode) /* BTST */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	INT8 dst = get_ibyte(2);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_140_0(UINT32 opcode) /* BCHG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	m68k_dreg(regs, dstreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_148_0(UINT32 opcode) /* MVPMR */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int memp = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	UINT32 val = (cpu_readmem24(memp) << 24) + (cpu_readmem24(memp + 2) << 16)
              + (cpu_readmem24(memp + 4) << 8) + cpu_readmem24(memp + 6);
	m68k_dreg(regs, dstreg) = (val);
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_150_0(UINT32 opcode) /* BCHG */
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
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_158_0(UINT32 opcode) /* BCHG */
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
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_160_0(UINT32 opcode) /* BCHG */
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
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_168_0(UINT32 opcode) /* BCHG */
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
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_170_0(UINT32 opcode) /* BCHG */
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
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 9;
}
unsigned long op_178_0(UINT32 opcode) /* BCHG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_179_0(UINT32 opcode) /* BCHG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_17a_0(UINT32 opcode) /* BCHG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_getpc () + 2;
	dsta += (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_17b_0(UINT32 opcode) /* BCHG */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 9;
}
unsigned long op_180_0(UINT32 opcode) /* BCLR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	m68k_dreg(regs, dstreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_188_0(UINT32 opcode) /* MVPRM */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
	unsigned int memp = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	cpu_writemem24(memp, src >> 8); cpu_writemem24(memp + 2, src);
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_190_0(UINT32 opcode) /* BCLR */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_198_0(UINT32 opcode) /* BCLR */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_1a0_0(UINT32 opcode) /* BCLR */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_1a8_0(UINT32 opcode) /* BCLR */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_1b0_0(UINT32 opcode) /* BCLR */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 9;
}
unsigned long op_1b8_0(UINT32 opcode) /* BCLR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_1b9_0(UINT32 opcode) /* BCLR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_1ba_0(UINT32 opcode) /* BCLR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_getpc () + 2;
	dsta += (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_1bb_0(UINT32 opcode) /* BCLR */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 9;
}
unsigned long op_1c0_0(UINT32 opcode) /* BSET */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	m68k_dreg(regs, dstreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_1c8_0(UINT32 opcode) /* MVPRM */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
	unsigned int memp = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	cpu_writemem24(memp, src >> 24); cpu_writemem24(memp + 2, src >> 16);
	cpu_writemem24(memp + 4, src >> 8); cpu_writemem24(memp + 6, src);
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_1d0_0(UINT32 opcode) /* BSET */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_1d8_0(UINT32 opcode) /* BSET */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_1e0_0(UINT32 opcode) /* BSET */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_1e8_0(UINT32 opcode) /* BSET */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_1f0_0(UINT32 opcode) /* BSET */
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
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 9;
}
unsigned long op_1f8_0(UINT32 opcode) /* BSET */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_1f9_0(UINT32 opcode) /* BSET */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_1fa_0(UINT32 opcode) /* BSET */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_getpc () + 2;
	dsta += (INT32)(INT16)get_iword(2);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_1fb_0(UINT32 opcode) /* BSET */
{
	UINT32 srcreg = ((opcode >> 9) & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 9;
}
unsigned long op_200_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_210_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_218_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_220_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_228_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_230_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_238_0(UINT32 opcode) /* AND */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_239_0(UINT32 opcode) /* AND */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_23c_0(UINT32 opcode) /* ANDSR */
{
	(void)(opcode);
{
	MakeSR();
{
	INT16 src = get_iword(2);
	src |= 0xFF00;
	regs.sr &= src;
	MakeFromSR();
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_240_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_250_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_258_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_260_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_268_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_270_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_278_0(UINT32 opcode) /* AND */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_279_0(UINT32 opcode) /* AND */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_27c_0(UINT32 opcode) /* ANDSR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel96; }
{
	MakeSR();
{
	INT16 src = get_iword(2);
	regs.sr &= src;
	MakeFromSR();
}
}
}
m68k_incpc(4);
endlabel96: ;
return 4;
}
unsigned long op_280_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_290_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_298_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_2a0_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 15;
}
unsigned long op_2a8_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_2b0_0(UINT32 opcode) /* AND */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
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
return 17;
}
unsigned long op_2b8_0(UINT32 opcode) /* AND */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_2b9_0(UINT32 opcode) /* AND */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
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
m68k_incpc(10);
return 18;
}
unsigned long op_2d0_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel105; }
}
}
}
}
m68k_incpc(4);
endlabel105: ;
return 4;
}
unsigned long op_2e8_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel106; }
}
}
}
}
m68k_incpc(6);
endlabel106: ;
return 6;
}
unsigned long op_2f0_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel107; }
}
}
}
}
}
endlabel107: ;
return 7;
}
unsigned long op_2f8_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel108; }
}
}
}
}
m68k_incpc(6);
endlabel108: ;
return 6;
}
unsigned long op_2f9_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel109; }
}
}
}
}
m68k_incpc(8);
endlabel109: ;
return 8;
}
unsigned long op_2fa_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel110; }
}
}
}
}
m68k_incpc(6);
endlabel110: ;
return 6;
}
unsigned long op_2fb_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=(INT32)(INT16)cpu_readmem24_word(dsta); upper = (INT32)(INT16)cpu_readmem24_word(dsta+2);
	if ((extra & 0x8000) == 0) reg = (INT32)(INT16)reg;
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel111; }
}
}
}
}
}
endlabel111: ;
return 7;
}
unsigned long op_400_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_410_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_418_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_420_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_428_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_430_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_438_0(UINT32 opcode) /* SUB */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_439_0(UINT32 opcode) /* SUB */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_440_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_450_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_458_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_460_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_468_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_470_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_478_0(UINT32 opcode) /* SUB */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_479_0(UINT32 opcode) /* SUB */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_480_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_490_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_498_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_4a0_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 15;
}
unsigned long op_4a8_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_4b0_0(UINT32 opcode) /* SUB */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
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
return 17;
}
unsigned long op_4b8_0(UINT32 opcode) /* SUB */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_4b9_0(UINT32 opcode) /* SUB */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
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
m68k_incpc(10);
return 18;
}
unsigned long op_4d0_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel136; }
}
}
}
}
m68k_incpc(4);
endlabel136: ;
return 4;
}
unsigned long op_4e8_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel137; }
}
}
}
}
m68k_incpc(6);
endlabel137: ;
return 6;
}
unsigned long op_4f0_0(UINT32 opcode) /* CHK2 */
{
	UINT32 dstreg = opcode & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel138; }
}
}
}
}
}
endlabel138: ;
return 7;
}
unsigned long op_4f8_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel139; }
}
}
}
}
m68k_incpc(6);
endlabel139: ;
return 6;
}
unsigned long op_4f9_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel140; }
}
}
}
}
m68k_incpc(8);
endlabel140: ;
return 8;
}
unsigned long op_4fa_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel141; }
}
}
}
}
m68k_incpc(6);
endlabel141: ;
return 6;
}
unsigned long op_4fb_0(UINT32 opcode) /* CHK2 */
{
	(void)(opcode);
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
	{INT32 upper,lower,reg = regs.regs[(extra >> 12) & 15];
	lower=cpu_readmem24_dword(dsta); upper = cpu_readmem24_dword(dsta+4);
	SET_ZFLG (upper == reg || lower == reg);
	SET_CFLG (lower <= upper ? reg < lower || reg > upper : reg > upper || reg < lower);
	if ((extra & 0x800) && GET_CFLG) { Exception(6,oldpc); goto endlabel142; }
}
}
}
}
}
endlabel142: ;
return 7;
}
unsigned long op_600_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_610_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_618_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_620_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_628_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_630_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_638_0(UINT32 opcode) /* ADD */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_639_0(UINT32 opcode) /* ADD */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_640_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_650_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_658_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_660_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_668_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_670_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_678_0(UINT32 opcode) /* ADD */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_679_0(UINT32 opcode) /* ADD */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_680_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_690_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_698_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_6a0_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 15;
}
unsigned long op_6a8_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_6b0_0(UINT32 opcode) /* ADD */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
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
return 17;
}
unsigned long op_6b8_0(UINT32 opcode) /* ADD */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_6b9_0(UINT32 opcode) /* ADD */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
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
m68k_incpc(10);
return 18;
}
unsigned long op_6c0_0(UINT32 opcode) /* RTM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6c8_0(UINT32 opcode) /* RTM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6d0_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6e8_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6f0_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6f8_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6f9_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6fa_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_6fb_0(UINT32 opcode) /* CALLM */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_800_0(UINT32 opcode) /* BTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_810_0(UINT32 opcode) /* BTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_818_0(UINT32 opcode) /* BTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_820_0(UINT32 opcode) /* BTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(4);
return 7;
}
unsigned long op_828_0(UINT32 opcode) /* BTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_830_0(UINT32 opcode) /* BTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
}
return 9;
}
unsigned long op_838_0(UINT32 opcode) /* BTST */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_839_0(UINT32 opcode) /* BTST */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(8);
return 10;
}
unsigned long op_83a_0(UINT32 opcode) /* BTST */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_83b_0(UINT32 opcode) /* BTST */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
}
}
return 9;
}
unsigned long op_83c_0(UINT32 opcode) /* BTST */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	INT8 dst = get_ibyte(4);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_840_0(UINT32 opcode) /* BCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	m68k_dreg(regs, dstreg) = (dst);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_850_0(UINT32 opcode) /* BCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_858_0(UINT32 opcode) /* BCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_860_0(UINT32 opcode) /* BCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_868_0(UINT32 opcode) /* BCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_870_0(UINT32 opcode) /* BCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 11;
}
unsigned long op_878_0(UINT32 opcode) /* BCHG */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_879_0(UINT32 opcode) /* BCHG */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_87a_0(UINT32 opcode) /* BCHG */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_87b_0(UINT32 opcode) /* BCHG */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (((UINT32)dst & (1 << src)) >> src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 11;
}
unsigned long op_880_0(UINT32 opcode) /* BCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	m68k_dreg(regs, dstreg) = (dst);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_890_0(UINT32 opcode) /* BCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_898_0(UINT32 opcode) /* BCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8a0_0(UINT32 opcode) /* BCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_8a8_0(UINT32 opcode) /* BCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8b0_0(UINT32 opcode) /* BCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 11;
}
unsigned long op_8b8_0(UINT32 opcode) /* BCLR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8b9_0(UINT32 opcode) /* BCLR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_8ba_0(UINT32 opcode) /* BCLR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8bb_0(UINT32 opcode) /* BCLR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 11;
}
unsigned long op_8c0_0(UINT32 opcode) /* BSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	src &= 31;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	m68k_dreg(regs, dstreg) = (dst);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_8d0_0(UINT32 opcode) /* BSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8d8_0(UINT32 opcode) /* BSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_8e0_0(UINT32 opcode) /* BSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_8e8_0(UINT32 opcode) /* BSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8f0_0(UINT32 opcode) /* BSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 11;
}
unsigned long op_8f8_0(UINT32 opcode) /* BSET */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8f9_0(UINT32 opcode) /* BSET */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_8fa_0(UINT32 opcode) /* BSET */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_8fb_0(UINT32 opcode) /* BSET */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
	src &= 7;
	SET_ZFLG (1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	cpu_writemem24(dsta,dst);
}
}
}
}
}
return 11;
}
unsigned long op_a00_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 4;
}
unsigned long op_a10_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_a18_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_a20_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_a28_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_a30_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
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
return 11;
}
unsigned long op_a38_0(UINT32 opcode) /* EOR */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_a39_0(UINT32 opcode) /* EOR */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_a3c_0(UINT32 opcode) /* EORSR */
{
	(void)(opcode);
{
	MakeSR();
{
	INT16 src = get_iword(2);
	src &= 0xFF;
	regs.sr ^= src;
	MakeFromSR();
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_a40_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 4;
}
unsigned long op_a50_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_a58_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_a60_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 9;
}
unsigned long op_a68_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_a70_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
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
return 11;
}

unsigned long op_a78_0(UINT32 opcode) /* EOR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_a79_0(UINT32 opcode) /* EOR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 12;
}
unsigned long op_a7c_0(UINT32 opcode) /* EORSR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel234; }
{
	MakeSR();
{
	INT16 src = get_iword(2);
	regs.sr ^= src;
	MakeFromSR();
}
}
}
m68k_incpc(4);
endlabel234: ;
return 4;
}
unsigned long op_a80_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 6;
}
unsigned long op_a90_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_a98_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 14;
}
unsigned long op_aa0_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 15;
}
unsigned long op_aa8_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_ab0_0(UINT32 opcode) /* EOR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
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
return 17;
}
unsigned long op_ab8_0(UINT32 opcode) /* EOR */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 16;
}
unsigned long op_ab9_0(UINT32 opcode) /* EOR */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
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
m68k_incpc(10);
return 18;
}
unsigned long op_ad0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ad8_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ae0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 dst = cpu_readmem24(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_ae8_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_af0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 dst = cpu_readmem24(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
}
return 11;
}
unsigned long op_af8_0(UINT32 opcode) /* CAS */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT8 dst = cpu_readmem24(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_af9_0(UINT32 opcode) /* CAS */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT8 dst = cpu_readmem24(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT8)(dst)) - ((INT8)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT8)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT8)(dst)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_ZFLG (((INT8)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT8)(m68k_dreg(regs, rc))) > ((UINT8)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_c00_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_c10_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
unsigned long op_c18_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
m68k_incpc(4);
return 6;
}
unsigned long op_c20_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
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
return 7;
}
unsigned long op_c28_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_c30_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
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
return 9;
}
unsigned long op_c38_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_c39_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 10;
}
unsigned long op_c3a_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
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
unsigned long op_c3b_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
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
return 9;
}
unsigned long op_c40_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_c50_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
unsigned long op_c58_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
m68k_incpc(4);
return 6;
}
unsigned long op_c60_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
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
return 7;
}
unsigned long op_c68_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_c70_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
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
return 9;
}
unsigned long op_c78_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_c79_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
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
m68k_incpc(8);
return 10;
}
unsigned long op_c7a_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
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
unsigned long op_c7b_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
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
return 9;
}
unsigned long op_c80_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
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
unsigned long op_c90_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
unsigned long op_c98_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
m68k_incpc(6);
return 10;
}
unsigned long op_ca0_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
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
return 11;
}
unsigned long op_ca8_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 12;
}
unsigned long op_cb0_0(UINT32 opcode) /* CMP */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
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
return 13;
}
unsigned long op_cb8_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 12;
}
unsigned long op_cb9_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
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
m68k_incpc(10);
return 14;
}
unsigned long op_cba_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_getpc () + 6;
	dsta += (INT32)(INT16)get_iword(6);
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
m68k_incpc(8);
return 12;
}
unsigned long op_cbb_0(UINT32 opcode) /* CMP */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
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
return 13;
}
unsigned long op_cd0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_cd8_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg(regs, dstreg) += 2;
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ce0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
{
	INT16 dst = cpu_readmem24_word(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_ce8_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_cf0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 dst = cpu_readmem24_word(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
}
return 11;
}
unsigned long op_cf8_0(UINT32 opcode) /* CAS */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_cf9_0(UINT32 opcode) /* CAS */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT16 dst = cpu_readmem24_word(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT16)(dst)) - ((INT16)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT16)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT16)(dst)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, rc))) > ((UINT16)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_word(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_cfc_0(UINT32 opcode) /* CAS2 */
{
	(void)(opcode);
{
{
	INT32 extra = get_ilong(2);
	UINT32 rn1 = regs.regs[(extra >> 28) & 15];
	UINT32 rn2 = regs.regs[(extra >> 12) & 15];
	UINT16 dst1 = cpu_readmem24_word(rn1), dst2 = cpu_readmem24_word(rn2);
{
UINT32 newv = ((INT16)(dst1)) - ((INT16)(m68k_dreg(regs, (extra >> 16) & 7)));
{
	int flgs = ((INT16)(m68k_dreg(regs, (extra >> 16) & 7))) < 0;
	int flgo = ((INT16)(dst1)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, (extra >> 16) & 7))) > ((UINT16)(dst1)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG) {
{
UINT32 newv = ((INT16)(dst2)) - ((INT16)(m68k_dreg(regs, extra & 7)));
{
	int flgs = ((INT16)(m68k_dreg(regs, extra & 7))) < 0;
	int flgo = ((INT16)(dst2)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_ZFLG (((INT16)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT16)(m68k_dreg(regs, extra & 7))) > ((UINT16)(dst2)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG) {
	cpu_writemem24_word(rn1, m68k_dreg(regs, (extra >> 22) & 7));
	cpu_writemem24_word(rn1, m68k_dreg(regs, (extra >> 6) & 7));
	}}
}
}
}
}
	if (! GET_ZFLG) {
	m68k_dreg(regs, (extra >> 22) & 7) = (m68k_dreg(regs, (extra >> 22) & 7) & ~0xffff) | (dst1 & 0xffff);
	m68k_dreg(regs, (extra >> 6) & 7) = (m68k_dreg(regs, (extra >> 6) & 7) & ~0xffff) | (dst2 & 0xffff);
	}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e10_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel288; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	cpu_writemem24(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	INT8 src = cpu_readmem24(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel288: ;
return 8;
}
unsigned long op_e18_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel289; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	cpu_writemem24(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel289: ;
return 8;
}
unsigned long op_e20_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel290; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	cpu_writemem24(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, dstreg) = srca;
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel290: ;
return 10;
}
unsigned long op_e28_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel291; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	cpu_writemem24(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
{
	INT8 src = cpu_readmem24(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
m68k_incpc(8);
endlabel291: ;
return 12;
}
unsigned long op_e30_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel292; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	cpu_writemem24(dsta,src);
}
}
}
else{
{
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
}
endlabel292: ;
return 14;
}
unsigned long op_e38_0(UINT32 opcode) /* MOVES */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel293; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	cpu_writemem24(dsta,src);
}
}
else{
{
	unsigned int srca = (INT32)(INT16)get_iword(6);
{
	INT8 src = cpu_readmem24(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
m68k_incpc(8);
endlabel293: ;
return 12;
}
unsigned long op_e39_0(UINT32 opcode) /* MOVES */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel294; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = get_ilong(4);
	cpu_writemem24(dsta,src);
}
}
else{
{
	unsigned int srca = get_ilong(8);
{
	INT8 src = cpu_readmem24(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT8)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xff) | ((src) & 0xff);
	}
}
}
}
}
}
}
m68k_incpc(12);
endlabel294: ;
return 16;
}
unsigned long op_e50_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel295; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	cpu_writemem24_word(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	INT16 src = cpu_readmem24_word(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel295: ;
return 8;
}
unsigned long op_e58_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel296; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
	cpu_writemem24_word(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, dstreg) += 2;
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel296: ;
return 8;
}
unsigned long op_e60_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel297; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	cpu_writemem24_word(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, dstreg) = srca;
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel297: ;
return 10;
}
unsigned long op_e68_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel298; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	cpu_writemem24_word(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
{
	INT16 src = cpu_readmem24_word(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
m68k_incpc(8);
endlabel298: ;
return 12;
}
unsigned long op_e70_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel299; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	cpu_writemem24_word(dsta,src);
}
}
}
else{
{
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
}
endlabel299: ;
return 14;
}
unsigned long op_e78_0(UINT32 opcode) /* MOVES */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel300; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	cpu_writemem24_word(dsta,src);
}
}
else{
{
	unsigned int srca = (INT32)(INT16)get_iword(6);
{
	INT16 src = cpu_readmem24_word(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
m68k_incpc(8);
endlabel300: ;
return 12;
}
unsigned long op_e79_0(UINT32 opcode) /* MOVES */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel301; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = get_ilong(4);
	cpu_writemem24_word(dsta,src);
}
}
else{
{
	unsigned int srca = get_ilong(8);
{
	INT16 src = cpu_readmem24_word(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = (INT32)(INT16)src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (m68k_dreg(regs, (extra >> 12) & 7) & ~0xffff) | ((src) & 0xffff);
	}
}
}
}
}
}
}
m68k_incpc(12);
endlabel301: ;
return 16;
}
unsigned long op_e90_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel302; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	cpu_writemem24_dword(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel302: ;
return 12;
}
unsigned long op_e98_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel303; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
	cpu_writemem24_dword(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, dstreg) += 4;
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel303: ;
return 12;
}
unsigned long op_ea0_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel304; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	cpu_writemem24_dword(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, dstreg) = srca;
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
m68k_incpc(4);
endlabel304: ;
return 14;
}
unsigned long op_ea8_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel305; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	cpu_writemem24_dword(dsta,src);
}
}
else{
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
{
	INT32 src = cpu_readmem24_dword(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
m68k_incpc(8);
endlabel305: ;
return 16;
}
unsigned long op_eb0_0(UINT32 opcode) /* MOVES */
{
	UINT32 dstreg = opcode & 7;
{
if (!regs.s) { Exception(8,0); goto endlabel306; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	cpu_writemem24_dword(dsta,src);
}
}
}
else{
{
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
}
endlabel306: ;
return 18;
}
unsigned long op_eb8_0(UINT32 opcode) /* MOVES */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel307; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	cpu_writemem24_dword(dsta,src);
}
}
else{
{
	unsigned int srca = (INT32)(INT16)get_iword(6);
{
	INT32 src = cpu_readmem24_dword(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
m68k_incpc(8);
endlabel307: ;
return 16;
}
unsigned long op_eb9_0(UINT32 opcode) /* MOVES */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel308; }
{
{
	INT16 extra = get_iword(2);
	if (extra & 0x800)
{
	UINT32 src = regs.regs[(extra >> 12) & 15];
{
	unsigned int dsta = get_ilong(4);
	cpu_writemem24_dword(dsta,src);
}
}
else{
{
	unsigned int srca = get_ilong(8);
{
	INT32 src = cpu_readmem24_dword(srca);
	if (extra & 0x8000) {
	m68k_areg(regs, (extra >> 12) & 7) = src;
	} else {
	m68k_dreg(regs, (extra >> 12) & 7) = (src);
	}
}
}
}
}
}
}
m68k_incpc(12);
endlabel308: ;
return 20;
}
unsigned long op_ed0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ed8_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ee0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_ee8_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ef0_0(UINT32 opcode) /* CAS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
}
return 15;
}
unsigned long op_ef8_0(UINT32 opcode) /* CAS */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
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
unsigned long op_ef9_0(UINT32 opcode) /* CAS */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
{
	int ru = (src >> 6) & 7;
	int rc = src & 7;
{
UINT32 newv = ((INT32)(dst)) - ((INT32)(m68k_dreg(regs, rc)));
{
	int flgs = ((INT32)(m68k_dreg(regs, rc))) < 0;
	int flgo = ((INT32)(dst)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, rc))) > ((UINT32)(dst)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG){
	cpu_writemem24_dword(dsta,(m68k_dreg(regs, ru)));
}
else{
m68k_dreg(regs, rc) = dst;
}
}
}
}
}
}
}
}
m68k_incpc(8);
return 16;
}
unsigned long op_efc_0(UINT32 opcode) /* CAS2 */
{
	(void)(opcode);
{
{
	INT32 extra = get_ilong(2);
	UINT32 rn1 = regs.regs[(extra >> 28) & 15];
	UINT32 rn2 = regs.regs[(extra >> 12) & 15];
	UINT32 dst1 = cpu_readmem24_dword(rn1), dst2 = cpu_readmem24_dword(rn2);
{
UINT32 newv = ((INT32)(dst1)) - ((INT32)(m68k_dreg(regs, (extra >> 16) & 7)));
{
	int flgs = ((INT32)(m68k_dreg(regs, (extra >> 16) & 7))) < 0;
	int flgo = ((INT32)(dst1)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, (extra >> 16) & 7))) > ((UINT32)(dst1)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG) {
{
UINT32 newv = ((INT32)(dst2)) - ((INT32)(m68k_dreg(regs, extra & 7)));
{
	int flgs = ((INT32)(m68k_dreg(regs, extra & 7))) < 0;
	int flgo = ((INT32)(dst2)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_ZFLG (((INT32)(newv)) == 0);
	SET_VFLG ((flgs != flgo) && (flgn != flgo));
	SET_CFLG (((UINT32)(m68k_dreg(regs, extra & 7))) > ((UINT32)(dst2)));
	SET_NFLG (flgn != 0);
	if (GET_ZFLG) {
	cpu_writemem24_dword(rn1, m68k_dreg(regs, (extra >> 22) & 7));
	cpu_writemem24_dword(rn1, m68k_dreg(regs, (extra >> 6) & 7));
	}}
}
}
}
}
	if (! GET_ZFLG) {
	m68k_dreg(regs, (extra >> 22) & 7) = dst1;
	m68k_dreg(regs, (extra >> 6) & 7) = dst2;
	}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_1000_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
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
unsigned long op_1010_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
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
unsigned long op_1018_0(UINT32 opcode) /* MOVE */
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
unsigned long op_1020_0(UINT32 opcode) /* MOVE */
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
unsigned long op_1028_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
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
unsigned long op_1030_0(UINT32 opcode) /* MOVE */
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
unsigned long op_1038_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
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
unsigned long op_1039_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
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
unsigned long op_103a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
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
unsigned long op_103b_0(UINT32 opcode) /* MOVE */
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
unsigned long op_103c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
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
unsigned long op_1080_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_1090_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_1098_0(UINT32 opcode) /* MOVE */
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
unsigned long op_10a0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10a8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10b0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10b8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10b9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10ba_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10bb_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_10bc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_10c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_10d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10d8_0(UINT32 opcode) /* MOVE */
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
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10e0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10f0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10f8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10f9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10fa_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10fb_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
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
unsigned long op_10fc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += areg_byteinc[dstreg];
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_1100_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_1110_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
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
unsigned long op_1118_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
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
unsigned long op_1120_0(UINT32 opcode) /* MOVE */
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
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(2);
return 8;
}
unsigned long op_1128_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_1130_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 10;
}
unsigned long op_1138_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_1139_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_113a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_113b_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 10;
}
unsigned long op_113c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(4);
return 7;
}
unsigned long op_1140_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_1150_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
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
unsigned long op_1158_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
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
unsigned long op_1160_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_1168_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_1170_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_1178_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_1179_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_117a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_117b_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_117c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_1180_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
return 7;
}
unsigned long op_1190_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
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
unsigned long op_1198_0(UINT32 opcode) /* MOVE */
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
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
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
unsigned long op_11a0_0(UINT32 opcode) /* MOVE */
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
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 10;
}
unsigned long op_11a8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 11;
}
unsigned long op_11b0_0(UINT32 opcode) /* MOVE */
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
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
}
return 12;
}
unsigned long op_11b8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 11;
}
unsigned long op_11b9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
m68k_incpc(6);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 13;
}
unsigned long op_11ba_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
return 11;
}
unsigned long op_11bb_0(UINT32 opcode) /* MOVE */
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
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
}
return 12;
}
unsigned long op_11bc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT8 src = get_ibyte(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
return 9;
}
unsigned long op_11c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_11d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
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
unsigned long op_11d8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
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
unsigned long op_11e0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_11e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_11f0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_11f8_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_11f9_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_11fa_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_11fb_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_11fc_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_13c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_13d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(2);
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
unsigned long op_13d8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	unsigned int dsta = get_ilong(2);
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
unsigned long op_13e0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_13e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_13f0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_13f8_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_13f9_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(10);
return 14;
}
unsigned long op_13fa_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_13fb_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	unsigned int dsta = get_ilong(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_13fc_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	cpu_writemem24(dsta,src);
}
}
}
m68k_incpc(8);
return 10;
}
unsigned long op_2000_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
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
unsigned long op_2008_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
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
unsigned long op_2010_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
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
unsigned long op_2018_0(UINT32 opcode) /* MOVE */
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
unsigned long op_2020_0(UINT32 opcode) /* MOVE */
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
unsigned long op_2028_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
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
unsigned long op_2030_0(UINT32 opcode) /* MOVE */
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
unsigned long op_2038_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
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
unsigned long op_2039_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
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
unsigned long op_203a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
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
unsigned long op_203b_0(UINT32 opcode) /* MOVE */
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
unsigned long op_203c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
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
unsigned long op_2040_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_2048_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_2050_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_2058_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_2060_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_2068_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_2070_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
}
return 9;
}
unsigned long op_2078_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_2079_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_207a_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_207b_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
}
return 9;
}
unsigned long op_207c_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	UINT32 val = src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_2080_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_2088_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_2090_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_2098_0(UINT32 opcode) /* MOVE */
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
unsigned long op_20a0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20a8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20b0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20b8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20b9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20ba_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20bb_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_20bc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_20c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_20c8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_20d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20d8_0(UINT32 opcode) /* MOVE */
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
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20e0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20f0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20f8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20f9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20fa_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20fb_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
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
unsigned long op_20fc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 4;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_2100_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_2108_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_2110_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
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
unsigned long op_2118_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
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
unsigned long op_2120_0(UINT32 opcode) /* MOVE */
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
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(2);
return 12;
}
unsigned long op_2128_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_2130_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 14;
}
unsigned long op_2138_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_2139_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(6);
return 15;
}
unsigned long op_213a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_213b_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 14;
}

unsigned long op_213c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_2140_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_2148_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_2150_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
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
unsigned long op_2158_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
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
unsigned long op_2160_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_2168_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_2170_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 15;
}
unsigned long op_2178_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_2179_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(8);
return 16;
}
unsigned long op_217a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_217b_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 15;
}
unsigned long op_217c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_2180_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
return 9;
}
unsigned long op_2188_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
return 9;
}
unsigned long op_2190_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
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
unsigned long op_2198_0(UINT32 opcode) /* MOVE */
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
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
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
unsigned long op_21a0_0(UINT32 opcode) /* MOVE */
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
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 14;
}
unsigned long op_21a8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 15;
}
unsigned long op_21b0_0(UINT32 opcode) /* MOVE */
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
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
}
return 16;
}
unsigned long op_21b8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 15;
}
unsigned long op_21b9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
m68k_incpc(6);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 17;
}
unsigned long op_21ba_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
return 15;
}
unsigned long op_21bb_0(UINT32 opcode) /* MOVE */
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
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
}
return 16;
}
unsigned long op_21bc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT32 src = get_ilong(2);
{
m68k_incpc(6);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
return 13;
}
unsigned long op_21c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_21c8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_21d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
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
unsigned long op_21d8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
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
unsigned long op_21e0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_21e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_21f0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 15;
}
unsigned long op_21f8_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_21f9_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(8);
return 16;
}
unsigned long op_21fa_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_21fb_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 15;
}
unsigned long op_21fc_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_23c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_23c8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_23d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(2);
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
unsigned long op_23d8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	unsigned int dsta = get_ilong(2);
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
unsigned long op_23e0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(6);
return 15;
}
unsigned long op_23e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(8);
return 16;
}
unsigned long op_23f0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
m68k_incpc(4);
return 17;
}
unsigned long op_23f8_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(8);
return 16;
}
unsigned long op_23f9_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(10);
return 18;
}
unsigned long op_23fa_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
m68k_incpc(8);
return 16;
}
unsigned long op_23fb_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	unsigned int dsta = get_ilong(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
}
}
m68k_incpc(4);
return 17;
}
unsigned long op_23fc_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
{
	unsigned int dsta = get_ilong(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
	cpu_writemem24_dword(dsta,src);
}
}
}
m68k_incpc(10);
return 14;
}
unsigned long op_3000_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
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
unsigned long op_3008_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
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
unsigned long op_3010_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
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
unsigned long op_3018_0(UINT32 opcode) /* MOVE */
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
unsigned long op_3020_0(UINT32 opcode) /* MOVE */
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
unsigned long op_3028_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
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
unsigned long op_3030_0(UINT32 opcode) /* MOVE */
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
unsigned long op_3038_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
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
unsigned long op_3039_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
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
unsigned long op_303a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
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
unsigned long op_303b_0(UINT32 opcode) /* MOVE */
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
unsigned long op_303c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
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
unsigned long op_3040_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_3048_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_3050_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_3058_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_3060_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_3068_0(UINT32 opcode) /* MOVEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_3070_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
}
return 7;
}
unsigned long op_3078_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_3079_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_307a_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_307b_0(UINT32 opcode) /* MOVEA */
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
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
}
}
return 7;
}
unsigned long op_307c_0(UINT32 opcode) /* MOVEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	UINT32 val = (INT32)(INT16)src;
	m68k_areg(regs, dstreg) = (val);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_3080_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_3088_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_3090_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_3098_0(UINT32 opcode) /* MOVE */
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
unsigned long op_30a0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30a8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30b0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30b8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30b9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30ba_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30bb_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
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
unsigned long op_30bc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_30c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_30c8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_30d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30d8_0(UINT32 opcode) /* MOVE */
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
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30e0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30f0_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30f8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30f9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30fa_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30fb_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
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
unsigned long op_30fc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
	m68k_areg(regs, dstreg) += 2;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_3100_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_3108_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_3110_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
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
unsigned long op_3118_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
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
unsigned long op_3120_0(UINT32 opcode) /* MOVE */
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
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(2);
return 8;
}
unsigned long op_3128_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_3130_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 10;
}
unsigned long op_3138_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_3139_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_313a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_313b_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 10;
}
unsigned long op_313c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 2;
	m68k_areg (regs, dstreg) = dsta;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 7;
}
unsigned long op_3140_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_3148_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_3150_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
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
unsigned long op_3158_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
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
unsigned long op_3160_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_3168_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_3170_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_3178_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_3179_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_317a_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
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
unsigned long op_317b_0(UINT32 opcode) /* MOVE */
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
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_317c_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_3180_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
return 7;
}
unsigned long op_3188_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
return 7;
}
unsigned long op_3190_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
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
unsigned long op_3198_0(UINT32 opcode) /* MOVE */
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
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
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
unsigned long op_31a0_0(UINT32 opcode) /* MOVE */
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
m68k_incpc(2);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 10;
}
unsigned long op_31a8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 11;
}
unsigned long op_31b0_0(UINT32 opcode) /* MOVE */
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
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
}
return 12;
}
unsigned long op_31b8_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 11;
}
unsigned long op_31b9_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
m68k_incpc(6);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 13;
}
unsigned long op_31ba_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
return 11;
}
unsigned long op_31bb_0(UINT32 opcode) /* MOVE */
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
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
}
return 12;
}
unsigned long op_31bc_0(UINT32 opcode) /* MOVE */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	INT16 src = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
return 9;
}
unsigned long op_31c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_31c8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_31d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
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
unsigned long op_31d8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
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
unsigned long op_31e0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_31e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_31f0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_31f8_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_31f9_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_31fa_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
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
unsigned long op_31fb_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = (INT32)(INT16)get_iword(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_31fc_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_33c0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_33c8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_areg(regs, srcreg);
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_33d0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(2);
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
unsigned long op_33d8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	unsigned int dsta = get_ilong(2);
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
unsigned long op_33e0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	unsigned int dsta = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_33e8_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_33f0_0(UINT32 opcode) /* MOVE */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_33f8_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_33f9_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(6);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(10);
return 14;
}
unsigned long op_33fa_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
m68k_incpc(8);
return 12;
}
unsigned long op_33fb_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	unsigned int dsta = get_ilong(0);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
}
}
m68k_incpc(4);
return 13;
}
unsigned long op_33fc_0(UINT32 opcode) /* MOVE */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
	cpu_writemem24_word(dsta,src);
}
}
}
m68k_incpc(8);
return 10;
}
unsigned long op_4000_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((newv) & 0xff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4010_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4018_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4020_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4028_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4030_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
}
return 9;
}
unsigned long op_4038_0(UINT32 opcode) /* NEGX */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4039_0(UINT32 opcode) /* NEGX */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4040_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((newv) & 0xffff);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4050_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4058_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4060_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4068_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4070_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
}
return 9;
}
unsigned long op_4078_0(UINT32 opcode) /* NEGX */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4079_0(UINT32 opcode) /* NEGX */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT16)(newv)) == 0));
	SET_NFLG (((INT16)(newv)) < 0);
	cpu_writemem24_word(srca,newv);
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4080_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	m68k_dreg(regs, srcreg) = (newv);
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4090_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_4098_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_40a0_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_40a8_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_40b0_0(UINT32 opcode) /* NEGX */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
}
return 13;
}
unsigned long op_40b8_0(UINT32 opcode) /* NEGX */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_40b9_0(UINT32 opcode) /* NEGX */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 newv = 0 - src - (GET_XFLG ? 1 : 0);
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(newv)) < 0;
	SET_VFLG ((flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY;
	SET_ZFLG (GET_ZFLG & (((INT32)(newv)) == 0));
	SET_NFLG (((INT32)(newv)) < 0);
	cpu_writemem24_dword(srca,newv);
}
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_40c0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel645; }
{
{
	MakeSR();
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((regs.sr) & 0xffff);
}
}
}
m68k_incpc(2);
endlabel645: ;
return 2;
}
unsigned long op_40d0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel646; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
m68k_incpc(2);
endlabel646: ;
return 4;
}
unsigned long op_40d8_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel647; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += 2;
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
m68k_incpc(2);
endlabel647: ;
return 4;
}
unsigned long op_40e0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel648; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
	m68k_areg (regs, srcreg) = srca;
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
m68k_incpc(2);
endlabel648: ;
return 5;
}
unsigned long op_40e8_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel649; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
m68k_incpc(4);
endlabel649: ;
return 6;
}
unsigned long op_40f0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel650; }
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
}
endlabel650: ;
return 7;
}
unsigned long op_40f8_0(UINT32 opcode) /* MVSR2 */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel651; }
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
m68k_incpc(4);
endlabel651: ;
return 6;
}
unsigned long op_40f9_0(UINT32 opcode) /* MVSR2 */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel652; }
{
{
	unsigned int srca = get_ilong(2);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr);
}
}
}
m68k_incpc(6);
endlabel652: ;
return 8;
}
unsigned long op_4100_0(UINT32 opcode) /* CHK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel653; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel653; }
}
}
}
m68k_incpc(2);
endlabel653: ;
return 2;
}
unsigned long op_4110_0(UINT32 opcode) /* CHK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel654; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel654; }
}
}
}
}
m68k_incpc(2);
endlabel654: ;
return 6;
}
unsigned long op_4118_0(UINT32 opcode) /* CHK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel655; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel655; }
}
}
}
}
m68k_incpc(2);
endlabel655: ;
return 6;
}
unsigned long op_4120_0(UINT32 opcode) /* CHK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel656; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel656; }
}
}
}
}
m68k_incpc(2);
endlabel656: ;
return 7;
}
unsigned long op_4128_0(UINT32 opcode) /* CHK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel657; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel657; }
}
}
}
}
m68k_incpc(4);
endlabel657: ;
return 8;
}
unsigned long op_4130_0(UINT32 opcode) /* CHK */
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
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel658; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel658; }
}
}
}
}
}
endlabel658: ;
return 9;
}
unsigned long op_4138_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel659; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel659; }
}
}
}
}
m68k_incpc(4);
endlabel659: ;
return 8;
}
unsigned long op_4139_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel660; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel660; }
}
}
}
}
m68k_incpc(6);
endlabel660: ;
return 10;
}
unsigned long op_413a_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel661; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel661; }
}
}
}
}
m68k_incpc(4);
endlabel661: ;
return 8;
}
unsigned long op_413b_0(UINT32 opcode) /* CHK */
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
	INT32 src = cpu_readmem24_dword(srca);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel662; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel662; }
}
}
}
}
}
endlabel662: ;
return 9;
}
unsigned long op_413c_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT32 src = get_ilong(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel663; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel663; }
}
}
}
m68k_incpc(6);
endlabel663: ;
return 6;
}
unsigned long op_4180_0(UINT32 opcode) /* CHK */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel664; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel664; }
}
}
}
m68k_incpc(2);
endlabel664: ;
return 2;
}
unsigned long op_4190_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel665; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel665; }
}
}
}
}
m68k_incpc(2);
endlabel665: ;
return 4;
}
unsigned long op_4198_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel666; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel666; }
}
}
}
}
m68k_incpc(2);
endlabel666: ;
return 4;
}
unsigned long op_41a0_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel667; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel667; }
}
}
}
}
m68k_incpc(2);
endlabel667: ;
return 5;
}
unsigned long op_41a8_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel668; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel668; }
}
}
}
}
m68k_incpc(4);
endlabel668: ;
return 6;
}
unsigned long op_41b0_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel669; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel669; }
}
}
}
}
}
endlabel669: ;
return 7;
}
unsigned long op_41b8_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel670; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel670; }
}
}
}
}
m68k_incpc(4);
endlabel670: ;
return 6;
}
unsigned long op_41b9_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel671; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel671; }
}
}
}
}
m68k_incpc(6);
endlabel671: ;
return 8;
}
unsigned long op_41ba_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel672; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel672; }
}
}
}
}
m68k_incpc(4);
endlabel672: ;
return 6;
}
unsigned long op_41bb_0(UINT32 opcode) /* CHK */
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
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel673; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel673; }
}
}
}
}
}
endlabel673: ;
return 7;
}
unsigned long op_41bc_0(UINT32 opcode) /* CHK */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
	unsigned int oldpc = m68k_getpc();
{
	INT16 src = get_iword(2);
{
	INT16 dst = m68k_dreg(regs, dstreg);
	if ((INT32)dst < 0) { SET_NFLG (1); Exception(6,oldpc); goto endlabel674; }
	else if (dst > src) { SET_NFLG (0); Exception(6,oldpc); goto endlabel674; }
}
}
}
m68k_incpc(4);
endlabel674: ;
return 4;
}
unsigned long op_41d0_0(UINT32 opcode) /* LEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_41e8_0(UINT32 opcode) /* LEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_41f0_0(UINT32 opcode) /* LEA */
{
	UINT32 srcreg = (opcode & 7);
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
}
return 5;
}
unsigned long op_41f8_0(UINT32 opcode) /* LEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_41f9_0(UINT32 opcode) /* LEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = get_ilong(2);
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_41fa_0(UINT32 opcode) /* LEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_41fb_0(UINT32 opcode) /* LEA */
{
	UINT32 dstreg = (opcode >> 9) & 7;
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	m68k_areg(regs, dstreg) = (srca);
}
}
}
}
return 5;
}
unsigned long op_4200_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((0) & 0xff);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4210_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4218_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4220_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_4228_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4230_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
}
return 7;
}
unsigned long op_4238_0(UINT32 opcode) /* CLR */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4239_0(UINT32 opcode) /* CLR */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(0)) == 0);
	SET_NFLG (((INT8)(0)) < 0);
	cpu_writemem24(srca,0);
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_4240_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((0) & 0xffff);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4250_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4258_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += 2;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4260_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_4268_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
m68k_incpc(4);
return 6;
}

unsigned long op_4270_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
}
return 7;
}
unsigned long op_4278_0(UINT32 opcode) /* CLR */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4279_0(UINT32 opcode) /* CLR */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(0)) == 0);
	SET_NFLG (((INT16)(0)) < 0);
	cpu_writemem24_word(srca,0);
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_4280_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	m68k_dreg(regs, srcreg) = (0);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4290_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4298_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += 4;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_42a0_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_42a8_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_42b0_0(UINT32 opcode) /* CLR */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
}
return 9;
}
unsigned long op_42b8_0(UINT32 opcode) /* CLR */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_42b9_0(UINT32 opcode) /* CLR */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(0)) == 0);
	SET_NFLG (((INT32)(0)) < 0);
	cpu_writemem24_dword(srca,0);
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_42c0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
{
	MakeSR();
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((regs.sr & 0xff) & 0xffff);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_42d0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_42d8_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
	m68k_areg(regs, srcreg) += 2;
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_42e0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
	m68k_areg (regs, srcreg) = srca;
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_42e8_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_42f0_0(UINT32 opcode) /* MVSR2 */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
}
return 7;
}
unsigned long op_42f8_0(UINT32 opcode) /* MVSR2 */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_42f9_0(UINT32 opcode) /* MVSR2 */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
	MakeSR();
	cpu_writemem24_word(srca,regs.sr & 0xff);
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_4400_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((dst) & 0xff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4410_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4418_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4420_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4428_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4430_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
}
return 9;
}
unsigned long op_4438_0(UINT32 opcode) /* NEG */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4439_0(UINT32 opcode) /* NEG */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
{
UINT32 dst = ((INT8)(0)) - ((INT8)(src));
{
	int flgs = ((INT8)(src)) < 0;
	int flgo = ((INT8)(0)) < 0;
	int flgn = ((INT8)(dst)) < 0;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT8)(src)) > ((UINT8)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4440_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4450_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4458_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4460_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4468_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4470_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
}
return 9;
}
unsigned long op_4478_0(UINT32 opcode) /* NEG */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4479_0(UINT32 opcode) /* NEG */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
{
UINT32 dst = ((INT16)(0)) - ((INT16)(src));
{
	int flgs = ((INT16)(src)) < 0;
	int flgo = ((INT16)(0)) < 0;
	int flgn = ((INT16)(dst)) < 0;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT16)(src)) > ((UINT16)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4480_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	m68k_dreg(regs, srcreg) = (dst);
}
}
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4490_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_4498_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_44a0_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_44a8_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_44b0_0(UINT32 opcode) /* NEG */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
}
return 13;
}
unsigned long op_44b8_0(UINT32 opcode) /* NEG */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_44b9_0(UINT32 opcode) /* NEG */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
{
UINT32 dst = ((INT32)(0)) - ((INT32)(src));
{
	int flgs = ((INT32)(src)) < 0;
	int flgo = ((INT32)(0)) < 0;
	int flgn = ((INT32)(dst)) < 0;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_VFLG ((flgs ^ flgo) & (flgn ^ flgo));
	SET_CFLG (((UINT32)(src)) > ((UINT32)(0)));
	COPY_CARRY;
	SET_NFLG (flgn != 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_44c0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_44d0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_44d8_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_44e0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_44e8_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_44f0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
}
return 7;
}
unsigned long op_44f8_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_44f9_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_44fa_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_44fb_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
}
}
return 7;
}
unsigned long op_44fc_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
	MakeSR();
	regs.sr &= 0xFF00;
	regs.sr |= src & 0xFF;
	MakeFromSR();
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4600_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((dst) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4610_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4618_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4620_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4628_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4630_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
}
return 9;
}
unsigned long op_4638_0(UINT32 opcode) /* NOT */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4639_0(UINT32 opcode) /* NOT */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(dst)) == 0);
	SET_NFLG (((INT8)(dst)) < 0);
	cpu_writemem24(srca,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4640_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4650_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4658_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4660_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4668_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4670_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
}
return 9;
}
unsigned long op_4678_0(UINT32 opcode) /* NOT */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4679_0(UINT32 opcode) /* NOT */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	cpu_writemem24_word(srca,dst);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4680_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4690_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_4698_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
m68k_incpc(2);
return 10;
}
unsigned long op_46a0_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
m68k_incpc(2);
return 11;
}
unsigned long op_46a8_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_46b0_0(UINT32 opcode) /* NOT */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
}
return 13;
}
unsigned long op_46b8_0(UINT32 opcode) /* NOT */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
m68k_incpc(4);
return 12;
}
unsigned long op_46b9_0(UINT32 opcode) /* NOT */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
{
	UINT32 dst = ~src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	cpu_writemem24_dword(srca,dst);
}
}
}
}
m68k_incpc(6);
return 14;
}
unsigned long op_46c0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel773; }
{
{
	INT16 src = m68k_dreg(regs, srcreg);
	regs.sr = src;
	MakeFromSR();
}
}
}
m68k_incpc(2);
endlabel773: ;
return 2;
}
unsigned long op_46d0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel774; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(2);
endlabel774: ;
return 4;
}
unsigned long op_46d8_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel775; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(2);
endlabel775: ;
return 4;
}
unsigned long op_46e0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel776; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(2);
endlabel776: ;
return 5;
}
unsigned long op_46e8_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel777; }
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(4);
endlabel777: ;
return 6;
}
unsigned long op_46f0_0(UINT32 opcode) /* MV2SR */
{
	UINT32 srcreg = (opcode & 7);
{
if (!regs.s) { Exception(8,0); goto endlabel778; }
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
}
endlabel778: ;
return 7;
}
unsigned long op_46f8_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel779; }
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(4);
endlabel779: ;
return 6;
}
unsigned long op_46f9_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel780; }
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(6);
endlabel780: ;
return 8;
}
unsigned long op_46fa_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel781; }
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
m68k_incpc(4);
endlabel781: ;
return 6;
}
unsigned long op_46fb_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel782; }
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	regs.sr = src;
	MakeFromSR();
}
}
}
}
}
endlabel782: ;
return 7;
}
unsigned long op_46fc_0(UINT32 opcode) /* MV2SR */
{
	(void)(opcode);
{
if (!regs.s) { Exception(8,0); goto endlabel783; }
{
{
	INT16 src = get_iword(2);
	regs.sr = src;
	MakeFromSR();
}
}
}
m68k_incpc(4);
endlabel783: ;
return 4;
}
unsigned long op_4800_0(UINT32 opcode) /* NBCD */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((newv) & 0xff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4808_0(UINT32 opcode) /* LINK */
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
	INT32 offs = get_ilong(2);
	m68k_areg(regs, 7) += offs;
}
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_4810_0(UINT32 opcode) /* NBCD */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4818_0(UINT32 opcode) /* NBCD */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4820_0(UINT32 opcode) /* NBCD */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4828_0(UINT32 opcode) /* NBCD */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4830_0(UINT32 opcode) /* NBCD */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
}
return 9;
}
unsigned long op_4838_0(UINT32 opcode) /* NBCD */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4839_0(UINT32 opcode) /* NBCD */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
{
	UINT16 newv_lo = - (src & 0xF) - (GET_XFLG ? 1 : 0);
	UINT16 newv_hi = - (src & 0xF0);
	UINT16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	SET_CFLG (cflg = (newv_hi & 0x1F0) > 0x90);
	COPY_CARRY;
	if (cflg) newv -= 0x60;
	SET_ZFLG (GET_ZFLG & (((INT8)(newv)) == 0));
	SET_NFLG (((INT8)(newv)) < 0);
	cpu_writemem24(srca,newv);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4840_0(UINT32 opcode) /* SWAP */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT32 dst = ((src >> 16)&0xFFFF) | ((src&0xFFFF)<<16);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4848_0(UINT32 opcode) /* BKPT */
{
{
m68k_incpc(2);
	op_illg(opcode);
}
return 2;
}
unsigned long op_4850_0(UINT32 opcode) /* PEA */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4868_0(UINT32 opcode) /* PEA */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_4870_0(UINT32 opcode) /* PEA */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
}
return 10;
}
unsigned long op_4878_0(UINT32 opcode) /* PEA */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_4879_0(UINT32 opcode) /* PEA */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
m68k_incpc(6);
return 11;
}
unsigned long op_487a_0(UINT32 opcode) /* PEA */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
m68k_incpc(4);
return 9;
}
unsigned long op_487b_0(UINT32 opcode) /* PEA */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	unsigned int dsta = m68k_areg(regs, 7) - 4;
	m68k_areg (regs, 7) = dsta;
	cpu_writemem24_dword(dsta,srca);
}
}
}
}
return 10;
}
unsigned long op_4880_0(UINT32 opcode) /* EXT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT16 dst = (INT16)(INT8)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(dst)) == 0);
	SET_NFLG (((INT16)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4890_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_word(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_word(srca, m68k_areg(regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_48a0_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = m68k_areg(regs, dstreg) - 0;
{
	UINT16 amask = mask & 0xff, dmask = (mask >> 8) & 0xff;
	while (amask) { srca -= 2; cpu_writemem24_word(srca, m68k_areg(regs, movem_index2[amask])); amask = movem_next[amask]; }
	while (dmask) { srca -= 2; cpu_writemem24_word(srca, m68k_dreg(regs, movem_index2[dmask])); dmask = movem_next[dmask]; }
	m68k_areg(regs, dstreg) = srca;
}
}
}
m68k_incpc(4);
return 5;
}
unsigned long op_48a8_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_word(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_word(srca, m68k_areg(regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_48b0_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_word(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_word(srca, m68k_areg(regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}
}
}
}
return 7;
}
unsigned long op_48b8_0(UINT32 opcode) /* MVMLE */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = (INT32)(INT16)get_iword(4);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_word(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_word(srca, m68k_areg(regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_48b9_0(UINT32 opcode) /* MVMLE */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = get_ilong(4);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_word(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_word(srca, m68k_areg(regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_48c0_0(UINT32 opcode) /* EXT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT32 dst = (INT32)(INT16)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_48d0_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = m68k_areg(regs, dstreg);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_dword(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_dword(srca, m68k_areg(regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_48e0_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = m68k_areg(regs, dstreg) - 0;
{
	UINT16 amask = mask & 0xff, dmask = (mask >> 8) & 0xff;
	while (amask) { srca -= 4; cpu_writemem24_dword(srca, m68k_areg(regs, movem_index2[amask])); amask = movem_next[amask]; }
	while (dmask) { srca -= 4; cpu_writemem24_dword(srca, m68k_dreg(regs, movem_index2[dmask])); dmask = movem_next[dmask]; }
	m68k_areg(regs, dstreg) = srca;
}
}
}
m68k_incpc(4);
return 5;
}
unsigned long op_48e8_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_dword(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_dword(srca, m68k_areg(regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_48f0_0(UINT32 opcode) /* MVMLE */
{
	UINT32 dstreg = opcode & 7;
{
	UINT16 mask = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_dword(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_dword(srca, m68k_areg(regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}
}
}
}
return 7;
}
unsigned long op_48f8_0(UINT32 opcode) /* MVMLE */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = (INT32)(INT16)get_iword(4);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_dword(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_dword(srca, m68k_areg(regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_48f9_0(UINT32 opcode) /* MVMLE */
{
	(void)(opcode);
{
	UINT16 mask = get_iword(2);
{
	unsigned int srca = get_ilong(4);
{
	UINT16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { cpu_writemem24_dword(srca, m68k_dreg(regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { cpu_writemem24_dword(srca, m68k_areg(regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_49c0_0(UINT32 opcode) /* EXT */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
{
	UINT32 dst = (INT32)(INT8)src;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(dst)) == 0);
	SET_NFLG (((INT32)(dst)) < 0);
	m68k_dreg(regs, srcreg) = (dst);
}
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4a00_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4a10_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4a18_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4a20_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_4a28_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4a30_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
}
return 7;
}
unsigned long op_4a38_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4a39_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_4a3a_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4a3b_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
}
}
return 7;
}
unsigned long op_4a3c_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	INT8 src = get_ibyte(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4a40_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_dreg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4a48_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT16 src = m68k_areg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4a50_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4a58_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg(regs, srcreg) += 2;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(2);
return 4;
}
unsigned long op_4a60_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 2;
{
	INT16 src = cpu_readmem24_word(srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(2);
return 5;
}
unsigned long op_4a68_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4a70_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
}
return 7;
}
unsigned long op_4a78_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4a79_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(6);
return 8;
}
unsigned long op_4a7a_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
m68k_incpc(4);
return 6;
}
unsigned long op_4a7b_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT16 src = cpu_readmem24_word(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
}
}
return 7;
}
unsigned long op_4a7c_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	INT16 src = get_iword(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(src)) == 0);
	SET_NFLG (((INT16)(src)) < 0);
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_4a80_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_dreg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4a88_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT32 src = m68k_areg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4a90_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4a98_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg(regs, srcreg) += 4;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4aa0_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - 4;
{
	INT32 src = cpu_readmem24_dword(srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4aa8_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4ab0_0(UINT32 opcode) /* TST */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
}
return 9;
}
unsigned long op_4ab8_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4ab9_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4aba_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	unsigned int srca = m68k_getpc () + 2;
	srca += (INT32)(INT16)get_iword(2);
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4abb_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
m68k_incpc(2);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int srca = get_disp_ea_020(tmppc, next_iword());
{
	INT32 src = cpu_readmem24_dword(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
}
}
return 9;
}
unsigned long op_4abc_0(UINT32 opcode) /* TST */
{
	(void)(opcode);
{
{
	INT32 src = get_ilong(2);
	CLEAR_CZNV;
	SET_ZFLG (((INT32)(src)) == 0);
	SET_NFLG (((INT32)(src)) < 0);
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_4ac0_0(UINT32 opcode) /* TAS */
{
	UINT32 srcreg = (opcode & 7);
{
{
	INT8 src = m68k_dreg(regs, srcreg);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	m68k_dreg(regs, srcreg) = (m68k_dreg(regs, srcreg) & ~0xff) | ((src) & 0xff);
}
}
m68k_incpc(2);
return 2;
}
unsigned long op_4ad0_0(UINT32 opcode) /* TAS */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4ad8_0(UINT32 opcode) /* TAS */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg);
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg(regs, srcreg) += areg_byteinc[srcreg];
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_4ae0_0(UINT32 opcode) /* TAS */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) - areg_byteinc[srcreg];
{
	INT8 src = cpu_readmem24(srca);
	m68k_areg (regs, srcreg) = srca;
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_4ae8_0(UINT32 opcode) /* TAS */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int srca = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4af0_0(UINT32 opcode) /* TAS */
{
	UINT32 srcreg = (opcode & 7);
{
{
m68k_incpc(2);
{
	unsigned int srca = get_disp_ea_020(m68k_areg(regs, srcreg), next_iword());
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
}
return 9;
}
unsigned long op_4af8_0(UINT32 opcode) /* TAS */
{
	(void)(opcode);
{
{
	unsigned int srca = (INT32)(INT16)get_iword(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_4af9_0(UINT32 opcode) /* TAS */
{
	(void)(opcode);
{
{
	unsigned int srca = get_ilong(2);
{
	INT8 src = cpu_readmem24(srca);
	CLEAR_CZNV;
	SET_ZFLG (((INT8)(src)) == 0);
	SET_NFLG (((INT8)(src)) < 0);
	src |= 0x80;
	cpu_writemem24(srca,src);
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_4c00_0(UINT32 opcode) /* MULL */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	INT32 dst = m68k_dreg(regs, dstreg);
m68k_incpc(4);
	m68k_mull(opcode, dst, extra);
}
}
}
return 4;
}
unsigned long op_4c10_0(UINT32 opcode) /* MULL */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(4);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 8;
}
unsigned long op_4c18_0(UINT32 opcode) /* MULL */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg(regs, dstreg) += 4;
m68k_incpc(4);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 8;
}
unsigned long op_4c20_0(UINT32 opcode) /* MULL */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) - 4;
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_areg (regs, dstreg) = dsta;
m68k_incpc(4);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 9;
}
unsigned long op_4c28_0(UINT32 opcode) /* MULL */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(6);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 10;
}
unsigned long op_4c30_0(UINT32 opcode) /* MULL */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int dsta = get_disp_ea_020(m68k_areg(regs, dstreg), next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_mull(opcode, dst, extra);
}
}
}
}
}
return 11;
}
unsigned long op_4c38_0(UINT32 opcode) /* MULL */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(6);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 10;
}
unsigned long op_4c39_0(UINT32 opcode) /* MULL */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(8);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 12;
}
unsigned long op_4c3a_0(UINT32 opcode) /* MULL */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT32 dst = cpu_readmem24_dword(dsta);
m68k_incpc(6);
	m68k_mull(opcode, dst, extra);
}
}
}
}
return 10;
}
unsigned long op_4c3b_0(UINT32 opcode) /* MULL */
{
{
{
	INT16 extra = get_iword(2);
{
m68k_incpc(4);
{
	unsigned int tmppc = m68k_getpc();
	unsigned int dsta = get_disp_ea_020(tmppc, next_iword());
{
	INT32 dst = cpu_readmem24_dword(dsta);
	m68k_mull(opcode, dst, extra);
}
}
}
}
}
return 11;
}
unsigned long op_4c3c_0(UINT32 opcode) /* MULL */
{
{
{
	INT16 extra = get_iword(2);
{
	INT32 dst = get_ilong(4);
m68k_incpc(8);
	m68k_mull(opcode, dst, extra);
}
}
}
return 8;
}