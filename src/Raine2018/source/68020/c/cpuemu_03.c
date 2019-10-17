#include "raine.h"
#include "newmem.h"
#include "readcpu.h"
#include "newcpu.h"
#include "cputbl.h"

#pragma warning( disable : 4702 4100 )

unsigned long op_e2d8_0(UINT32 opcode) /* LSRW */
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
unsigned long op_e2e0_0(UINT32 opcode) /* LSRW */
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
return 7;
}
unsigned long op_e2e8_0(UINT32 opcode) /* LSRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_e2f0_0(UINT32 opcode) /* LSRW */
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
}
return 9;
}
unsigned long op_e2f8_0(UINT32 opcode) /* LSRW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
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
m68k_incpc(4);
return 8;
}
unsigned long op_e2f9_0(UINT32 opcode) /* LSRW */
{
{
{
	unsigned int dataa = get_ilong(2);
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
m68k_incpc(6);
return 10;
}
unsigned long op_e3d0_0(UINT32 opcode) /* LSLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e3d8_0(UINT32 opcode) /* LSLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e3e0_0(UINT32 opcode) /* LSLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_e3e8_0(UINT32 opcode) /* LSLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e3f0_0(UINT32 opcode) /* LSLW */
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
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
}
return 9;
}
unsigned long op_e3f8_0(UINT32 opcode) /* LSLW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e3f9_0(UINT32 opcode) /* LSLW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_e4d0_0(UINT32 opcode) /* ROXRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
unsigned long op_e4d8_0(UINT32 opcode) /* ROXRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
unsigned long op_e4e0_0(UINT32 opcode) /* ROXRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
return 7;
}
unsigned long op_e4e8_0(UINT32 opcode) /* ROXRW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
m68k_incpc(4);
return 8;
}
unsigned long op_e4f0_0(UINT32 opcode) /* ROXRW */
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
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
}
return 9;
}
unsigned long op_e4f8_0(UINT32 opcode) /* ROXRW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
m68k_incpc(4);
return 8;
}
unsigned long op_e4f9_0(UINT32 opcode) /* ROXRW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG) val |= 0x8000;
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
m68k_incpc(6);
return 10;
}
unsigned long op_e5d0_0(UINT32 opcode) /* ROXLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e5d8_0(UINT32 opcode) /* ROXLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e5e0_0(UINT32 opcode) /* ROXLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_e5e8_0(UINT32 opcode) /* ROXLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e5f0_0(UINT32 opcode) /* ROXLW */
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
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
}
return 9;
}
unsigned long op_e5f8_0(UINT32 opcode) /* ROXLW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e5f9_0(UINT32 opcode) /* ROXLW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG) val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	COPY_CARRY;
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_e6d0_0(UINT32 opcode) /* RORW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e6d8_0(UINT32 opcode) /* RORW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e6e0_0(UINT32 opcode) /* RORW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_e6e8_0(UINT32 opcode) /* RORW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e6f0_0(UINT32 opcode) /* RORW */
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
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
}
return 9;
}
unsigned long op_e6f8_0(UINT32 opcode) /* RORW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e6f9_0(UINT32 opcode) /* RORW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_e7d0_0(UINT32 opcode) /* ROLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e7d8_0(UINT32 opcode) /* ROLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg);
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg(regs, srcreg) += 2;
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 6;
}
unsigned long op_e7e0_0(UINT32 opcode) /* ROLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) - 2;
{
	INT16 data = cpu_readmem24_word(dataa);
	m68k_areg (regs, srcreg) = dataa;
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(2);
return 7;
}
unsigned long op_e7e8_0(UINT32 opcode) /* ROLW */
{
	UINT32 srcreg = (opcode & 7);
{
{
	unsigned int dataa = m68k_areg(regs, srcreg) + (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e7f0_0(UINT32 opcode) /* ROLW */
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
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
}
return 9;
}
unsigned long op_e7f8_0(UINT32 opcode) /* ROLW */
{
{
{
	unsigned int dataa = (INT32)(INT16)get_iword(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(4);
return 8;
}
unsigned long op_e7f9_0(UINT32 opcode) /* ROLW */
{
{
{
	unsigned int dataa = get_ilong(2);
{
	INT16 data = cpu_readmem24_word(dataa);
{
	UINT16 val = data;
	UINT32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	CLEAR_CZNV;
	SET_ZFLG (((INT16)(val)) == 0);
	SET_NFLG (((INT16)(val)) < 0);
SET_CFLG (carry >> 15);
	cpu_writemem24_word(dataa,val);
}
}
}
}
m68k_incpc(6);
return 10;
}
unsigned long op_e8c0_0(UINT32 opcode) /* BFTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_e8d0_0(UINT32 opcode) /* BFTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_e8e8_0(UINT32 opcode) /* BFTST */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e8f0_0(UINT32 opcode) /* BFTST */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
}
return 7;
}
unsigned long op_e8f8_0(UINT32 opcode) /* BFTST */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e8f9_0(UINT32 opcode) /* BFTST */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_e8fa_0(UINT32 opcode) /* BFTST */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e8fb_0(UINT32 opcode) /* BFTST */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
}
}
}
}
}
return 7;
}
unsigned long op_e9c0_0(UINT32 opcode) /* BFEXTU */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_e9d0_0(UINT32 opcode) /* BFEXTU */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_e9e8_0(UINT32 opcode) /* BFEXTU */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e9f0_0(UINT32 opcode) /* BFEXTU */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
}
return 7;
}
unsigned long op_e9f8_0(UINT32 opcode) /* BFEXTU */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e9f9_0(UINT32 opcode) /* BFEXTU */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_e9fa_0(UINT32 opcode) /* BFEXTU */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_e9fb_0(UINT32 opcode) /* BFEXTU */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
}
return 7;
}
unsigned long op_eac0_0(UINT32 opcode) /* BFCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = ~tmp;
	tmp <<= (32 - width);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ((offset & 0x1f) == 0 ? 0 :
		(0xffffffff << (32 - (offset & 0x1f))))) |
		(tmp >> (offset & 0x1f)) |
		(((offset & 0x1f) + width) >= 32 ? 0 :
 (m68k_dreg(regs, dstreg) & ((UINT32)0xffffffff >> ((offset & 0x1f) + width))));
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_ead0_0(UINT32 opcode) /* BFCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = ~tmp;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_eae8_0(UINT32 opcode) /* BFCHG */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = ~tmp;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_eaf0_0(UINT32 opcode) /* BFCHG */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = ~tmp;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
}
return 7;
}
unsigned long op_eaf8_0(UINT32 opcode) /* BFCHG */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = ~tmp;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_eaf9_0(UINT32 opcode) /* BFCHG */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = ~tmp;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_ebc0_0(UINT32 opcode) /* BFEXTS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_ebd0_0(UINT32 opcode) /* BFEXTS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_ebe8_0(UINT32 opcode) /* BFEXTS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_ebf0_0(UINT32 opcode) /* BFEXTS */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
}
return 7;
}
unsigned long op_ebf8_0(UINT32 opcode) /* BFEXTS */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_ebf9_0(UINT32 opcode) /* BFEXTS */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_ebfa_0(UINT32 opcode) /* BFEXTS */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_ebfb_0(UINT32 opcode) /* BFEXTS */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	if (GET_NFLG) tmp |= width == 32 ? 0 : (-1 << width);
	m68k_dreg(regs, (extra >> 12) & 7) = tmp;
}
}
}
}
}
return 7;
}
unsigned long op_ecc0_0(UINT32 opcode) /* BFCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp <<= (32 - width);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ((offset & 0x1f) == 0 ? 0 :
		(0xffffffff << (32 - (offset & 0x1f))))) |
		(tmp >> (offset & 0x1f)) |
		(((offset & 0x1f) + width) >= 32 ? 0 :
 (m68k_dreg(regs, dstreg) & ((UINT32)0xffffffff >> ((offset & 0x1f) + width))));
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_ecd0_0(UINT32 opcode) /* BFCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_ece8_0(UINT32 opcode) /* BFCLR */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_ecf0_0(UINT32 opcode) /* BFCLR */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
}
return 7;
}
unsigned long op_ecf8_0(UINT32 opcode) /* BFCLR */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_ecf9_0(UINT32 opcode) /* BFCLR */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_edc0_0(UINT32 opcode) /* BFFFO */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_edd0_0(UINT32 opcode) /* BFFFO */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_ede8_0(UINT32 opcode) /* BFFFO */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_edf0_0(UINT32 opcode) /* BFFFO */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
}
return 7;
}
unsigned long op_edf8_0(UINT32 opcode) /* BFFFO */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_edf9_0(UINT32 opcode) /* BFFFO */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_edfa_0(UINT32 opcode) /* BFFFO */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_getpc () + 4;
	dsta += (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_edfb_0(UINT32 opcode) /* BFFFO */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	{ UINT32 mask = 1 << (width-1);
	while (mask) { if (tmp & mask) break; mask >>= 1; offset++; }}
	m68k_dreg(regs, (extra >> 12) & 7) = offset;
}
}
}
}
}
return 7;
}
unsigned long op_eec0_0(UINT32 opcode) /* BFSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffff;
	tmp <<= (32 - width);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ((offset & 0x1f) == 0 ? 0 :
		(0xffffffff << (32 - (offset & 0x1f))))) |
		(tmp >> (offset & 0x1f)) |
		(((offset & 0x1f) + width) >= 32 ? 0 :
 (m68k_dreg(regs, dstreg) & ((UINT32)0xffffffff >> ((offset & 0x1f) + width))));
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_eed0_0(UINT32 opcode) /* BFSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffff;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_eee8_0(UINT32 opcode) /* BFSET */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffff;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_eef0_0(UINT32 opcode) /* BFSET */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffff;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
}
return 7;
}
unsigned long op_eef8_0(UINT32 opcode) /* BFSET */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffff;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_eef9_0(UINT32 opcode) /* BFSET */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = 0xffffffff;
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(8);
return 8;
}
unsigned long op_efc0_0(UINT32 opcode) /* BFINS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp = m68k_dreg(regs, dstreg) << (offset & 0x1f);
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg(regs, (extra >> 12) & 7);
	tmp <<= (32 - width);
	m68k_dreg(regs, dstreg) = (m68k_dreg(regs, dstreg) & ((offset & 0x1f) == 0 ? 0 :
		(0xffffffff << (32 - (offset & 0x1f))))) |
		(tmp >> (offset & 0x1f)) |
		(((offset & 0x1f) + width) >= 32 ? 0 :
 (m68k_dreg(regs, dstreg) & ((UINT32)0xffffffff >> ((offset & 0x1f) + width))));
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_efd0_0(UINT32 opcode) /* BFINS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg(regs, (extra >> 12) & 7);
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(4);
return 4;
}
unsigned long op_efe8_0(UINT32 opcode) /* BFINS */
{
	UINT32 dstreg = opcode & 7;
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = m68k_areg(regs, dstreg) + (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg(regs, (extra >> 12) & 7);
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_eff0_0(UINT32 opcode) /* BFINS */
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
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg(regs, (extra >> 12) & 7);
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
}
return 7;
}
unsigned long op_eff8_0(UINT32 opcode) /* BFINS */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = (INT32)(INT16)get_iword(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg(regs, (extra >> 12) & 7);
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(6);
return 6;
}
unsigned long op_eff9_0(UINT32 opcode) /* BFINS */
{
{
{
	INT16 extra = get_iword(2);
{
	unsigned int dsta = get_ilong(4);
{
	INT32 offset = extra & 0x800 ? m68k_dreg(regs, (extra >> 6) & 7) : (extra >> 6) & 0x1f;
	int width = (((extra & 0x20 ? m68k_dreg(regs, extra & 7) : extra) -1) & 0x1f) +1;
	UINT32 tmp,bf0,bf1;
	dsta += (offset >> 3) | (offset & 0x80000000 ? ~0x1fffffff : 0);
	bf0 = cpu_readmem24_dword(dsta);bf1 = cpu_readmem24(dsta+4) & 0xff;
	tmp = (bf0 << (offset & 7)) | (bf1 >> (8 - (offset & 7)));
	tmp >>= (32 - width);
	SET_NFLG (tmp & (1 << (width-1)) ? 1 : 0);
	SET_ZFLG (tmp == 0); SET_VFLG (0); SET_CFLG (0);
	tmp = m68k_dreg(regs, (extra >> 12) & 7);
	tmp <<= (32 - width);
	bf0 = (bf0 & (0xff000000 << (8 - (offset & 7)))) |
		(tmp >> (offset & 7)) |
		(((offset & 7) + width) >= 32 ? 0 :
		 (bf0 & ((UINT32)0xffffffff >> ((offset & 7) + width))));
	cpu_writemem24_dword(dsta,bf0 );
	if (((offset & 7) + width) > 32) {
		bf1 = (bf1 & (0xff >> (width - 32 + (offset & 7)))) |
			(tmp << (8 - (offset & 7)));
		cpu_writemem24(dsta+4,bf1);
	}
}
}
}
}
m68k_incpc(8);
return 8;
}
