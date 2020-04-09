/*

This is untested

*/

#include "raine.h"
#include "m6502.h"
#include "m6502hlp.h"
#include "savegame.h"
#include "debug.h"
#include "cpumain.h"

UINT8 *M6502ROM;
int M6502Engine;
static int c1,c2,c3,c4;
static int b1,b2,b3,b4;
static int e1,e2,e3,e4;

typedef struct M6502_BANKLIST
{
   UINT8 list[32];
   int count;
} M6502_BANKLIST;

typedef struct M6502_DATA			// Information about 1 chip
{
   M6502_BANKLIST read_bank;
   M6502_BANKLIST write_bank;
   UINT8 *base_ram;
} M6502_DATA;

struct M6502_DATA m6502_data[3];

/*
 *  Fill in the basic structures via these functions...
 */

#ifdef MAME_6502
typedef UINT32(*read_func)(UINT32);
typedef void(*write_func)(UINT32,UINT32);

UINT8 m6502_readop(UINT32 adr) {
    return m6502.m6502Base[adr];
}

UINT8 m6502_readop_arg(UINT32 adr) {
    return m6502.m6502Base[adr];
}

UINT16 m6502_readop_arg16(UINT32 adr) {
    return ReadWord(m6502.m6502Base+adr);
}

UINT8 m6502_read8(UINT32 adr) {
    int cpu = current_cpu_num[CPU_M6502_0 >> 4];
    int n;
    // I didn't see the memory maps were not in arrays
    // which forces me to make a case...
    // this emu would benefit from memory handlers in the struct
    // rather than globally like that...
    switch(cpu) {
    case 0:
	for (n=0; n<c1; n++) {
	    if (M6502A_memoryreadbyte[n].lowAddr <= adr &&
		    adr <= M6502A_memoryreadbyte[n].highAddr) {
		if (M6502A_memoryreadbyte[n].memoryCall)
		    return ((read_func)(M6502A_memoryreadbyte[n].memoryCall))(adr);
		else
		    return ((UINT8*)M6502A_memoryreadbyte[n].pUserArea)[adr];
	    }
	}
	break;
    case 1:
	for (n=0; n<b1; n++) {
	    if (M6502B_memoryreadbyte[n].lowAddr <= adr &&
		    adr <= M6502B_memoryreadbyte[n].highAddr) {
		if (M6502B_memoryreadbyte[n].memoryCall)
		    return ((read_func)(M6502B_memoryreadbyte[n].memoryCall))(adr);
		else
		    return ((UINT8*)M6502B_memoryreadbyte[n].pUserArea)[adr];
	    }
	}
	break;
    case 2:
	for (n=0; n<e1; n++) {
	    if (M6502C_memoryreadbyte[n].lowAddr <= adr &&
		    adr <= M6502C_memoryreadbyte[n].highAddr) {
		if (M6502C_memoryreadbyte[n].memoryCall)
		    return ((read_func)(M6502C_memoryreadbyte[n].memoryCall))(adr);
		else
		    return ((UINT8*)M6502C_memoryreadbyte[n].pUserArea)[adr];
	    }
	}
	break;
    }
    return m6502_readop(adr);
}

void m6502_write8(UINT32 adr,UINT8 data) {
    int cpu = current_cpu_num[CPU_M6502_0 >> 4];
    int n;
    switch(cpu) {
    case 0:
	for (n=0; n<c2; n++) {
	    if (M6502A_memorywritebyte[n].lowAddr <= adr &&
		    adr <= M6502A_memorywritebyte[n].highAddr) {
		if (M6502A_memorywritebyte[n].memoryCall) {
		    ((write_func)(M6502A_memorywritebyte[n].memoryCall))(adr,data);
		    return;
		} else {
		    ((UINT8*)M6502A_memorywritebyte[n].pUserArea)[adr] = data;
		    return;
		}
	    }
	}
	break;
    case 1:
	for (n=0; n<b2; n++) {
	    if (M6502B_memorywritebyte[n].lowAddr <= adr &&
		    adr <= M6502B_memorywritebyte[n].highAddr) {
		if (M6502B_memorywritebyte[n].memoryCall) {
		    ((write_func)(M6502B_memorywritebyte[n].memoryCall))(adr,data);
		    return;
		} else {
		    ((UINT8*)M6502B_memorywritebyte[n].pUserArea)[adr] = data;
		    return;
		}
	    }
	}
	break;
    case 2:
	for (n=0; n<e2; n++) {
	    if (M6502C_memorywritebyte[n].lowAddr <= adr &&
		    adr <= M6502C_memorywritebyte[n].highAddr) {
		if (M6502C_memorywritebyte[n].memoryCall) {
		    ((write_func)(M6502C_memorywritebyte[n].memoryCall))(adr,data);
		    return;
		} else {
		    ((UINT8*)M6502C_memorywritebyte[n].pUserArea)[adr] = data;
		    return;
		}
	    }
	}
	break;
    }

}
#endif

// FIRST EMULATED M6502

void AddM6502AROMBase(UINT8 *d0)
{
#ifdef MAME_6502
    if (!m6502.insn) {
	printf("AddM6502AROMBase: call 1st m6502_init or m65c02_init !\n");
	exit(1);
    }
   m6502.m6502Base = d0;
   m6502_get_context(&M6502_context[0]);
#else
   M6502_context[0].m6502Base = d0;
   m6502_data[0].base_ram = M6502_context[0].m6502Base;
#endif
}

// Unused so far in raine, code probably adapted from z80 !
#ifndef MAME_6502
void M6502ASetBank(UINT8 *src)
{
   int ta,tb;

   // Update base pointer (if called during emulation)

   m6502Base = src;

   // Update base pointer (if called outside emulation)

   M6502_context[0].m6502Base = src;

   m6502_data[0].base_ram = M6502_context[0].m6502Base;

   for(ta=0; ta<m6502_data[0].read_bank.count; ta++){
      tb = m6502_data[0].read_bank.list[ta];			// Get bank pos
      M6502A_memoryreadbyte[tb].pUserArea = src;			// Write new pointer
   }
   for(ta=0; ta<m6502_data[0].write_bank.count; ta++){
      tb = m6502_data[0].write_bank.list[ta];			// Get bank pos
      M6502A_memorywritebyte[tb].pUserArea = src;			// Write new pointer
   }
}

void M6502BSetBank(UINT8 *src)
{
   int ta,tb;

   // Update base pointer (if called during emulation)

   m6502Base = src;

   // Update base pointer (if called outside emulation)

   M6502_context[1].m6502Base = src;

   m6502_data[1].base_ram = M6502_context[1].m6502Base;

   for(ta=0; ta<m6502_data[1].read_bank.count; ta++){
      tb = m6502_data[1].read_bank.list[ta];			// Get bank pos
      M6502B_memoryreadbyte[tb].pUserArea = src;			// Write new pointer
   }
   for(ta=0; ta<m6502_data[1].write_bank.count; ta++){
      tb = m6502_data[1].write_bank.list[ta];			// Get bank pos
      M6502B_memorywritebyte[tb].pUserArea = src;			// Write new pointer
   }
}

void M6502CSetBank(UINT8 *src)
{
   int ta,tb;

   // Update base pointer (if called during emulation)

   m6502Base = src;

   // Update base pointer (if called outside emulation)

   M6502_context[2].m6502Base = src;

   m6502_data[2].base_ram = M6502_context[2].m6502Base;

   for(ta=0; ta<m6502_data[2].read_bank.count; ta++){
      tb = m6502_data[2].read_bank.list[ta];			// Get bank pos
      M6502C_memoryreadbyte[tb].pUserArea = src;			// Write new pointer
   }
   for(ta=0; ta<m6502_data[2].write_bank.count; ta++){
      tb = m6502_data[2].write_bank.list[ta];			// Get bank pos
      M6502C_memorywritebyte[tb].pUserArea = src;			// Write new pointer
   }
}
#endif

void AddM6502AReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   int ta;

   if(d2==NULL){
      if(d3==NULL){
         d3 = M6502_context[0].m6502Base;
         ta = m6502_data[0].read_bank.count;	// Add to bankswitching queue
         m6502_data[0].read_bank.list[ta] = c1;
         m6502_data[0].read_bank.count++;
      }
      else{
      d3 = d3 - d0;
      }
   }
   M6502A_memoryreadbyte[c1].lowAddr=d0;
   M6502A_memoryreadbyte[c1].highAddr=d1;
   M6502A_memoryreadbyte[c1].memoryCall=d2;
   M6502A_memoryreadbyte[c1].pUserArea=d3;
   c1++;
}

void AddM6502AWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   int ta;

   if(d2==NULL){
      if(d3==NULL){
         d3 = M6502_context[0].m6502Base;
         ta = m6502_data[0].write_bank.count;	// Add to bankswitching queue
         m6502_data[0].write_bank.list[ta] = c2;
         m6502_data[0].write_bank.count++;
      }
      else{
      d3 = d3 - d0;
      }
   }
   M6502A_memorywritebyte[c2].lowAddr=d0;
   M6502A_memorywritebyte[c2].highAddr=d1;
   M6502A_memorywritebyte[c2].memoryCall=d2;
   M6502A_memorywritebyte[c2].pUserArea=d3;
   c2++;
}

void AddM6502ARW(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  AddM6502ARead(d0,d1,d2,d3);
  AddM6502AWrite(d0,d1,d2,d3);
}

void AddM6502AInit(void)
{
#ifdef MAME_6502
   AddSaveData(SAVE_M6502_0, (UINT8 *) &M6502_context[0], (UINT8*)&M6502_context[9].m6502Base - (UINT8*)&M6502_context[0]);
#else
   M6502_context[0].m6502MemoryRead  = M6502A_memoryreadbyte;
   M6502_context[0].m6502MemoryWrite = M6502A_memorywritebyte;

   AddLoadCallback(M6502A_load_update);
   AddSaveData(SAVE_M6502_0, (UINT8 *) &M6502_context[0], sizeof(M6502_context[0]));
#endif

   M6502Engine=1;
}

/*
 *  Fill in the basic structures via these functions...
 */

// SECOND EMULATED M6502

void AddM6502BROMBase(UINT8 *d0)
{
#ifdef MAME_6502
    if (!m6502.insn) {
	printf("AddM6502BROMBase: call 1st m6502_init or m65c02_init !\n");
	exit(1);
    }
   m6502.m6502Base = d0;
   m6502_get_context(&M6502_context[1]);
#else
   m6502_data[1].base_ram = M6502_context[1].m6502Base;
   M6502_context[1].m6502Base=d0;
#endif
}

void AddM6502BReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   int ta;

   if(d2==NULL){
      if(d3==NULL){
         d3 = M6502_context[1].m6502Base;
         ta = m6502_data[1].read_bank.count;	// Add to bankswitching queue
         m6502_data[1].read_bank.list[ta] = b1;
         m6502_data[1].read_bank.count++;
      }
      else{
      d3 = d3 - d0;
      }
   }
   M6502B_memoryreadbyte[b1].lowAddr=d0;
   M6502B_memoryreadbyte[b1].highAddr=d1;
   M6502B_memoryreadbyte[b1].memoryCall=d2;
   M6502B_memoryreadbyte[b1].pUserArea=d3;
   b1++;
}

void AddM6502BWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   int ta;

   if(d2==NULL){
      if(d3==NULL){
         d3 = M6502_context[1].m6502Base;
         ta = m6502_data[1].write_bank.count;	// Add to bankswitching queue
         m6502_data[1].write_bank.list[ta] = b2;
         m6502_data[1].write_bank.count ++;
      }
      else{
      d3 = d3 - d0;
      }
   }
   M6502B_memorywritebyte[b2].lowAddr=d0;
   M6502B_memorywritebyte[b2].highAddr=d1;
   M6502B_memorywritebyte[b2].memoryCall=d2;
   M6502B_memorywritebyte[b2].pUserArea=d3;
   b2++;
}

void AddM6502BInit(void)
{
#ifdef MAME_6502
   AddSaveData(SAVE_M6502_0, (UINT8 *) &M6502_context[0], (UINT8*)&M6502_context[9].m6502Base - (UINT8*)&M6502_context[0]);
#else
   M6502_context[1].m6502MemoryRead  = M6502B_memoryreadbyte;
   M6502_context[1].m6502MemoryWrite = M6502B_memorywritebyte;

   AddLoadCallback(M6502B_load_update);
   AddSaveData(SAVE_M6502_1, (UINT8 *) &M6502_context[1], sizeof(M6502_context[1]));
#endif

   M6502Engine=2;
}

/*
 *  Fill in the basic structures via these functions...
 */

// THIRD EMULATED M6502

void AddM6502CROMBase(UINT8 *d0)
{
#ifdef MAME_6502
    if (!m6502.insn) {
	printf("AddM6502CROMBase: call 1st m6502_init or m65c02_init !\n");
	exit(1);
    }
   m6502.m6502Base = d0;
   m6502_get_context(&M6502_context[2]);
#else
   m6502_data[2].base_ram = M6502_context[2].m6502Base;
   M6502_context[2].m6502Base=d0;
#endif
}

void AddM6502CReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   int ta;

   if(d2==NULL){
      if(d3==NULL){
         d3 = M6502_context[2].m6502Base;
         ta = m6502_data[2].read_bank.count;	// Add to bankswitching queue
         m6502_data[2].read_bank.list[ta] = e1;
         m6502_data[2].read_bank.count++;
      }
      else{
      d3 = d3 - d0;
      }
   }
   M6502C_memoryreadbyte[e1].lowAddr=d0;
   M6502C_memoryreadbyte[e1].highAddr=d1;
   M6502C_memoryreadbyte[e1].memoryCall=d2;
   M6502C_memoryreadbyte[e1].pUserArea=d3;
   e1++;
}

void AddM6502CWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   int ta;

   if(d2==NULL){
      if(d3==NULL){
         d3 = M6502_context[2].m6502Base;
         ta = m6502_data[2].write_bank.count;	// Add to bankswitching queue
         m6502_data[2].write_bank.list[ta] = e2;
         m6502_data[2].write_bank.count++;
      }
      else{
      d3 = d3 - d0;
      }
   }
   M6502C_memorywritebyte[e2].lowAddr=d0;
   M6502C_memorywritebyte[e2].highAddr=d1;
   M6502C_memorywritebyte[e2].memoryCall=d2;
   M6502C_memorywritebyte[e2].pUserArea=d3;
   e2++;
}

void AddM6502CInit(void)
{
#ifdef MAME_6502
   AddSaveData(SAVE_M6502_0, (UINT8 *) &M6502_context[0], (UINT8*)&M6502_context[9].m6502Base - (UINT8*)&M6502_context[0]);
#else
   M6502_context[2].m6502MemoryRead  = M6502C_memoryreadbyte;
   M6502_context[2].m6502MemoryWrite = M6502C_memorywritebyte;

   AddLoadCallback(M6502C_load_update);
   AddSaveData(SAVE_M6502_2, (UINT8 *) &M6502_context[2], sizeof(M6502_context[2]));
#endif

   M6502Engine=3;
}

#ifndef MAME_6502
void M6502A_load_update(void)
{
   #ifdef RAINE_DEBUG
   print_debug("M6502A Load Callback()\n");
   #endif

   M6502_context[0].m6502MemoryRead  = M6502A_memoryreadbyte;
   M6502_context[0].m6502MemoryWrite = M6502A_memorywritebyte;
   M6502_context[0].m6502Base     = m6502_data[0].base_ram;
}

void M6502B_load_update(void)
{
   #ifdef RAINE_DEBUG
   print_debug("M6502B Load Callback()\n");
   #endif

   M6502_context[1].m6502MemoryRead  = M6502B_memoryreadbyte;
   M6502_context[1].m6502MemoryWrite = M6502B_memorywritebyte;
   M6502_context[1].m6502Base     = m6502_data[1].base_ram;
}

void M6502C_load_update(void)
{
   #ifdef RAINE_DEBUG
   print_debug("M6502C Load Callback()\n");
   #endif

   M6502_context[2].m6502MemoryRead  = M6502C_memoryreadbyte;
   M6502_context[2].m6502MemoryWrite = M6502C_memorywritebyte;
   M6502_context[2].m6502Base     = m6502_data[2].base_ram;
}
#endif

void M6502_disp_context(int nb) {
#ifndef MAME_6502
  struct m6502context *ctx = &M6502_context[nb];
  // printf("base %x\n",ctx->m6502Base);
  printf("registers :\n");
  printf("A:%02x X:%02x Y:%02x S:%02x F:%02x\n",ctx->m6502af & 0xff,ctx->m6502x,ctx->m6502y,
	 ctx->m6502s,ctx->m6502af >> 8);
  printf("PC:%4x\n",ctx->m6502pc);
  printf("pending: %x\n",ctx->irqPending);
#endif
}

void ClearM6502List(void)
{
   c1=0;
   c2=0;
   c3=0;
   c4=0;
   b1=0;
   b2=0;
   b3=0;
   b4=0;
   e1=0;
   e2=0;
   e3=0;
   e4=0;

   m6502_data[0].read_bank.count = 0;
   m6502_data[0].write_bank.count = 0;
   m6502_data[1].read_bank.count = 0;
   m6502_data[1].write_bank.count = 0;
   m6502_data[2].read_bank.count = 0;
   m6502_data[2].write_bank.count = 0;
}

void StopM6502(UINT16 address, UINT8 data)
{
	(void)(address);
	(void)(data);
   print_debug("[StopM6502]\n");
   m6502ReleaseTimeslice();
}


static UINT16 StopAddress=0;

void SetStopM6502Mode2(UINT16 address)
{
   StopAddress=address;
}

void StopM6502Mode2(UINT16 address, UINT8 data)
{
	(void)(address);
	(void)(data);
   print_debug("[StopM6502]\n");
   m6502pc=StopAddress;
   m6502ReleaseTimeslice();
}

static UINT16 StopAddressB=0;

void SetStopM6502BMode2(UINT16 address)
{
   StopAddressB=address;
}

void StopM6502BMode2(UINT16 address, UINT8 data)
{
	(void)(address);
	(void)(data);
   print_debug("[StopM6502B]\n");
   m6502pc=StopAddressB;
   m6502ReleaseTimeslice();
}

static UINT16 StopAddressC=0;

void SetStopM6502CMode2(UINT16 address)
{
   StopAddressC=address;
}

void StopM6502CMode2(UINT16 address, UINT8 data)
{
  (void)(address);
  (void)(data);
  print_debug("[StopM6502C]\n");
  m6502pc=StopAddressC;
  m6502ReleaseTimeslice();
}

UINT8 DefBadReadM6502(UINT16 offset)
{
  print_debug("M6502BadRead(%04x) [%04x]\n",offset,m6502pc);
   return(0xFF);
}

void DefBadWriteM6502(UINT16 offset, UINT8 data)
{
  print_debug("M6502BadWrite(%04x,%02x) [%04x]\n",offset,data,m6502pc);
}

UINT8 M6502ReadByte(UINT32 address)
{
  // Normally we should be able to choose the cpu, but for that we need
  // to change the arrays to include the cpu number.
  // for now, we will just handle cpu #0, which should be enough for cheats and hiscores

  int ta;

  for(ta=0;ta<99;ta++){
    if((M6502A_memoryreadbyte[ta].lowAddr)==-1){
      // reached the end
      return ReadByte( M6502_context[0].m6502Base + address);
    }
    else{
      if((address>=M6502A_memoryreadbyte[ta].lowAddr)&&(M6502A_memoryreadbyte[ta].highAddr>=address)){
	if(M6502A_memoryreadbyte[ta].memoryCall==NULL){
	  return ReadByte( ((UINT8 *) M6502A_memoryreadbyte[ta].pUserArea) + address);
	}
      }
    }
  }

  return 0x00;
}

void M6502WriteByte(UINT32 address, UINT16 data)
{
  // Normally we should be able to choose the cpu, but for that we need
  // to change the arrays to include the cpu number.
  // for now, we will just handle cpu #0, which should be enough for cheats and hiscores

  int ta;

  for(ta=0;ta<99;ta++){
    if((M6502A_memorywritebyte[ta].lowAddr)==-1){
      WriteByte( M6502_context[0].m6502Base + address,data);
      return;
    }
    else{
      if((address>=M6502A_memorywritebyte[ta].lowAddr)&&(M6502A_memorywritebyte[ta].highAddr>=address)){
	if(M6502A_memorywritebyte[ta].memoryCall==NULL){
	  WriteByte( ((UINT8 *) M6502A_memorywritebyte[ta].pUserArea) + address,data);
	}
      }
    }
  }
}
