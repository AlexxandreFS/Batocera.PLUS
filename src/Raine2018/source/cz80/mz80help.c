#include "deftypes.h"
#include "mz80help.h"
#include "raine.h"
#include "debug.h"
#include "savegame.h"
#include <SDL_endian.h>

static UINT8 *z80_data[MAX_Z80];

cz80_struc	Z80_context[MAX_Z80];
struct MemoryReadByte	Z80_memory_rb[MAX_Z80][MAX_Z80_DATA];
struct MemoryWriteByte	Z80_memory_wb[MAX_Z80][MAX_Z80_DATA];
struct z80PortRead	Z80_port_rb[MAX_Z80][MAX_Z80_PORT];
struct z80PortWrite	Z80_port_wb[MAX_Z80][MAX_Z80_PORT];
int MZ80Engine,latch;
int cyclesRemaining; // dummy to workaround some mz80 bug !
int Z80Has16bitsPorts;
int z80_offdata; // for kabuki encryption, not supported yet

static UINT32 memory_count_rb[MAX_Z80];
static UINT32 memory_count_wb[MAX_Z80];

static UINT32 port_count_rb[MAX_Z80];
static UINT32 port_count_wb[MAX_Z80];

UINT8 *Z80RAM;

int latch;

UINT8 soundlatch_lo_r(UINT32 offset) {
  return latch & 0xff;
}

static UINT8 my_z80_readb(UINT32 ctx,UINT16 adr) {
    int n;
    for (n=0; n<memory_count_rb[ctx]; n++) {
	if (Z80_memory_rb[ctx][n].lowAddr <= adr &&
		adr <= Z80_memory_rb[ctx][n].highAddr) {
	    if (Z80_memory_rb[ctx][n].memoryCall)
		return (Z80_memory_rb[ctx][n].memoryCall)(adr);
	    else
		return Z80_memory_rb[ctx][n].pUserArea[adr];
	}
    }
    print_debug("my_Z80BadRead(%04x) [%04x]\n",adr,mz80GetPC());
    return(0xFF);
}

static void my_z80_writeb(UINT32 ctx,UINT16 adr,UINT8 data) {
    int n;
    for (n=0; n<memory_count_wb[ctx]; n++) {
	if (Z80_memory_wb[ctx][n].lowAddr <= adr &&
		adr <= Z80_memory_wb[ctx][n].highAddr) {
	    if (Z80_memory_wb[ctx][n].memoryCall)
		(Z80_memory_wb[ctx][n].memoryCall)(adr,data);
	    else
		Z80_memory_wb[ctx][n].pUserArea[adr] = data;
	    return;
	}
    }
    print_debug("Z80BadWrite(%04x,%x) [%04x]\n",adr,data,mz80GetPC());
}

// the z80 has the same byte order as the x86, for now I just ignore the order
static UINT16 my_z80_readw(UINT32 ctx,UINT16 adr) {
    int n;
    for (n=0; n<memory_count_rb[ctx]; n++) {
	if (Z80_memory_rb[ctx][n].lowAddr <= adr &&
		adr <= Z80_memory_rb[ctx][n].highAddr) {
	    if (Z80_memory_rb[ctx][n].memoryCall)
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		return ((Z80_memory_rb[ctx][n].memoryCall)(adr) << 8)|
		    (Z80_memory_rb[ctx][n].memoryCall)(adr+1);
#else
		return (Z80_memory_rb[ctx][n].memoryCall)(adr) |
		((Z80_memory_rb[ctx][n].memoryCall)(adr+1) << 8);
#endif
	    else
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		return ReadWord68k(&Z80_memory_rb[ctx][n].pUserArea[adr]);
#else
		return ReadWord(&Z80_memory_rb[ctx][n].pUserArea[adr]);
#endif
	}
    }
    print_debug("Z80BadReadWord(%04x) [%04x]\n",adr,mz80GetPC());
    return(0xFFff);
}

static void my_z80_writew(UINT32 ctx,UINT16 adr,UINT16 data) {
    int n;
    for (n=0; n<memory_count_wb[ctx]; n++) {
	if (Z80_memory_wb[ctx][n].lowAddr <= adr &&
		adr <= Z80_memory_wb[ctx][n].highAddr) {
	    if (Z80_memory_wb[ctx][n].memoryCall) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		(Z80_memory_wb[ctx][n].memoryCall)(adr+1,data & 0xff);
		(Z80_memory_wb[ctx][n].memoryCall)(adr,data >> 8);
#else
		(Z80_memory_wb[ctx][n].memoryCall)(adr,data & 0xff);
		(Z80_memory_wb[ctx][n].memoryCall)(adr+1,data >> 8);
#endif
	    } else
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		WriteWord68k(&Z80_memory_wb[ctx][n].pUserArea[adr], data);
#else
		WriteWord(&Z80_memory_wb[ctx][n].pUserArea[adr], data);
#endif
	    return;
	}
    }
    print_debug("Z80BadWriteWord(%04x,%x) [%04x]\n",adr,data,mz80GetPC());
}

static UINT8 my_z80_port_rb(UINT32 ctx,UINT16 adr) {
    int n;
    if (!Z80Has16bitsPorts) adr &= 0xff;
    for (n=0; n<port_count_rb[ctx]; n++) {
	if (Z80_port_rb[ctx][n].lowIoAddr <= adr &&
		adr <= Z80_port_rb[ctx][n].highIoAddr) {
	    if (Z80_port_rb[ctx][n].IOCall)
		return (Z80_port_rb[ctx][n].IOCall)(adr);
	    else
		return Z80_port_rb[ctx][n].pUserArea[adr];
	}
    }
    print_debug("my_Z80BadPortRead(%04x) [%04x]\n",adr,mz80GetPC());
    return(0xFF);
}

static void my_z80_port_wb(UINT32 ctx,UINT16 adr,UINT8 data) {
    int n;
    if (!Z80Has16bitsPorts) adr &= 0xff;
    for (n=0; n<port_count_wb[ctx]; n++) {
	if (Z80_port_wb[ctx][n].lowIoAddr <= adr &&
		adr <= Z80_port_wb[ctx][n].highIoAddr) {
	    if (Z80_port_wb[ctx][n].IOCall)
		(Z80_port_wb[ctx][n].IOCall)(adr,data);
	    else
		Z80_port_wb[ctx][n].pUserArea[adr] = data;
	    return;
	}
    }
    print_debug("Z80BadWrite(%04x,%x) [%04x]\n",adr,data,mz80GetPC());
}

static void z80_load_update(int n) {
    Cz80_Set_ReadB(&Z80_context[n],&my_z80_readb);
    Cz80_Set_WriteB(&Z80_context[n],&my_z80_writeb);
    Cz80_Set_ReadW(&Z80_context[n],&my_z80_readw);
    Cz80_Set_WriteW(&Z80_context[n],&my_z80_writew);
    Cz80_Set_INPort(&Z80_context[n],&my_z80_port_rb);
    Cz80_Set_OUTPort(&Z80_context[n],&my_z80_port_wb);
}

static void Z80A_load_update() {
    z80_load_update(0);
}

static void Z80B_load_update() {
    z80_load_update(1);
}

#define SAVE_CZ80_0            ASCII_ID('C','Z','8',0x00)
#define SAVE_CZ80_1            ASCII_ID('C','Z','8',0x01)
#define SAVE_CZ80_2            ASCII_ID('C','Z','8',0x02)
#define SAVE_CZ80_3            ASCII_ID('C','Z','8',0x03)

void AddZ80AInit(void)
{
    Cz80_Set_Ctx(&Z80_context[0],0);
    Z80A_load_update();

   AddLoadCallback(Z80A_load_update);
   AddSaveData(SAVE_CZ80_0, (UINT8 *) &Z80_context[0], sizeof(Z80_context[0]));

   if (MZ80Engine < 1) MZ80Engine=1;
}

void AddZ80BInit(void)
{
    Cz80_Set_Ctx(&Z80_context[1],1);
    Z80B_load_update();

   AddLoadCallback(Z80B_load_update);
   AddSaveData(SAVE_CZ80_1, (UINT8 *) &Z80_context[1], sizeof(Z80_context[1]));

   if (MZ80Engine < 2) MZ80Engine=2;
}

void AddZ80CInit(void)
{
    Cz80_Set_Ctx(&Z80_context[2],2);
    Z80B_load_update();

   AddLoadCallback(Z80B_load_update);
   AddSaveData(SAVE_CZ80_2, (UINT8 *) &Z80_context[2], sizeof(Z80_context[2]));

   if (MZ80Engine < 3) MZ80Engine=2;
}

void AddZ80DInit(void)
{
    Cz80_Set_Ctx(&Z80_context[3],3);
    Z80B_load_update();

   AddLoadCallback(Z80B_load_update);
   AddSaveData(SAVE_CZ80_3, (UINT8 *) &Z80_context[3], sizeof(Z80_context[3]));

   if (MZ80Engine < 4) MZ80Engine=2;
}

void AddZ80AROMBase(UINT8 *d0, UINT16 d1, UINT16 d2)
{
    Cz80_Init(&Z80_context[0]);
    // Cz80_Set_Fetch(&Z80_context[0], 0x0000, 0xfFFF, (UINT32*) d0);
    z80_data[0] = d0;
}

void AddZ80BROMBase(UINT8 *d0, UINT16 d1, UINT16 d2)
{
    Cz80_Init(&Z80_context[1]);
    // Cz80_Set_Fetch(&Z80_context[0], 0x0000, 0xfFFF, (UINT32*) d0);
    z80_data[1] = d0;
}

static void add_mz80_memory_region_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   if (d2 == &DefBadReadZ80) return;
   if(!d2){
      if(!d3){					// Add to bankswitching queue
         d3 = z80_data[cpu];
         // z80_data[cpu].read_bank.list[z80_data[cpu].read_bank.count] = memory_count_rb[cpu];
         // z80_data[cpu].read_bank.count++;
      }
      else{
	  Cz80_Set_Fetch(&Z80_context[cpu], d0, d1, d3);
	  d3 = d3 - d0;
      }
   }

   Z80_memory_rb[cpu][memory_count_rb[cpu]].lowAddr    = d0;
   Z80_memory_rb[cpu][memory_count_rb[cpu]].highAddr   = d1;
   Z80_memory_rb[cpu][memory_count_rb[cpu]].memoryCall = d2;
   Z80_memory_rb[cpu][memory_count_rb[cpu]].pUserArea  = d3;
   memory_count_rb[cpu]++;
}

void z80_get_ram(UINT32 cpu, UINT32 *range, UINT32 *count) {
  *count = 0;
  int max = memory_count_rb[cpu];
  int n;
  for (n=0; n<max; n++) {
    if (!Z80_memory_rb[cpu][n].memoryCall &&
         Z80_memory_rb[cpu][n].pUserArea &&
	 (Z80_memory_rb[cpu][n].lowAddr & 0xff000000) == 0) {
	range[(*count)++] = Z80_memory_rb[cpu][n].lowAddr;
	range[(*count)++] = Z80_memory_rb[cpu][n].highAddr;
    }
  }
}

UINT8 *z80_get_userdata(UINT32 cpu, UINT32 adr) {
  int max = memory_count_rb[cpu];
  int n;
  for (n=0; n<max; n++) {
    if (!Z80_memory_rb[cpu][n].memoryCall &&
         Z80_memory_rb[cpu][n].pUserArea &&
	 Z80_memory_rb[cpu][n].lowAddr <= adr &&
	 Z80_memory_rb[cpu][n].highAddr >= adr) {
      return Z80_memory_rb[cpu][n].pUserArea;
    }
  }
  return NULL;
}

static void add_mz80_memory_region_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   if(!d2){
      if(!d3){					// Add to bankswitching queue
         d3 = z80_data[cpu];
         // z80_data[cpu].write_bank.list[z80_data[cpu].write_bank.count] = memory_count_wb[cpu];
         // z80_data[cpu].write_bank.count++;
      }
      else{
         d3 = d3 - d0;
      }
   }

   if (d2 == &DefBadWriteZ80) return;

   Z80_memory_wb[cpu][memory_count_wb[cpu]].lowAddr    = d0;
   Z80_memory_wb[cpu][memory_count_wb[cpu]].highAddr   = d1;
   Z80_memory_wb[cpu][memory_count_wb[cpu]].memoryCall = d2;
   Z80_memory_wb[cpu][memory_count_wb[cpu]].pUserArea  = d3;
   memory_count_wb[cpu]++;
}

static void add_mz80_port_region_rb(UINT32 cpu, UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   if (d2 == &DefBadReadPortZ80) return;
   Z80_port_rb[cpu][port_count_rb[cpu]].lowIoAddr  = d0;
   Z80_port_rb[cpu][port_count_rb[cpu]].highIoAddr = d1;
   Z80_port_rb[cpu][port_count_rb[cpu]].IOCall     = d2;
   Z80_port_rb[cpu][port_count_rb[cpu]].pUserArea  = d3;
   port_count_rb[cpu]++;
}

static void add_mz80_port_region_wb(UINT32 cpu, UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   if (d2 == &DefBadWritePortZ80) return;
   Z80_port_wb[cpu][port_count_wb[cpu]].lowIoAddr  = d0;
   Z80_port_wb[cpu][port_count_wb[cpu]].highIoAddr = d1;
   Z80_port_wb[cpu][port_count_wb[cpu]].IOCall     = d2;
   Z80_port_wb[cpu][port_count_wb[cpu]].pUserArea  = d3;
   port_count_wb[cpu]++;
}
void AddZ80AReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_rb(0, d0, d1, d2, d3);
}

void AddZ80AWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_wb(0, d0, d1, d2, d3);
}

void AddZ80AReadPort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_rb(0, d0, d1, d2, d3);
}

void AddZ80AWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_wb(0, d0, d1, d2, d3);
}

void AddZ80BReadPort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_rb(1, d0, d1, d2, d3);
}

void AddZ80BWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_wb(1, d0, d1, d2, d3);
}

void AddZ80BReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_rb(1, d0, d1, d2, d3);
}

void AddZ80BWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_wb(1, d0, d1, d2, d3);
}

static UINT16 StopAddress;
static UINT16 StopAddressB;
static UINT16 StopAddressC;
static UINT16 StopAddressD;

void ClearZ80List(void)
{
   UINT32 ta;

   for(ta = 0; ta < MAX_Z80; ta ++){

      memory_count_rb[ta] = 0;
      memory_count_wb[ta] = 0;

      port_count_rb[ta] = 0;
      port_count_wb[ta] = 0;

      // z80_data[ta].read_bank.count = 0;
      // z80_data[ta].write_bank.count = 0;

      z80_data[0] = NULL;
   }
   StopAddress = StopAddressB = StopAddressC = StopAddressD = 0;
}

UINT16 DefBadReadZ80(UINT16 offset)
{
    printf("defbadreadz80 should not be called\n");
    exit(1);
   return(0xFF);
}

UINT16 DefBadReadPortZ80(UINT16 offset)
{
    printf("defbadreadportz80 should not be called\n");
    exit(1);
   return(0xFF);
}

void DefBadWriteZ80(UINT16 offset, UINT8 data)
{
    printf("DefBadWriteZ80 should not be called\n");
    exit(1);
}

void DefBadWritePortZ80(UINT16 offset, UINT8 data)
{
  printf("DefBadWritePortZ80 should not be called\n");
  exit(1);
}

static void prepare_cpu_adr(int *cpu, UINT32 *address) {
  // Hack : to access the 1 cpu, pass address + 0x1000000
  // 2nd is address + 0x2000000, etc...
  // From very vague memory this hack is used mainly for some region byte...
  *cpu = 0;
  while (*address >= 0x1000000) {
    *cpu = *cpu + 1;
    *address -= 0x1000000;
  }
  if (*cpu == 0) {
    // Antiriad programmed many games with a fake z80 #0...
    if (!z80_data[0])
	*cpu = 1;
  }

  if (*cpu > MZ80Engine-1) {
    *cpu = MZ80Engine -1;
  }
}

UINT8 ReadMZ80Byte(UINT32 address)
{
    int cpu;
    prepare_cpu_adr(&cpu,&address);
    return my_z80_readb(cpu,address);
}

void WriteMZ80Byte(UINT32 address, UINT8 data)
{
  int cpu;
  prepare_cpu_adr(&cpu,&address);
  my_z80_writeb(cpu,address,data);
}

/* Context switches : since it's a C core, there is no real context switch
 * the current context is always updated in real time. But since mz80 uses
 * a global context and doesn't pass any context to function calls, we'll use
 * this to find out which cpu is active ! */

static cz80_struc *curz;

void mz80GetContext(cz80_struc *c) {
}

void mz80SetContext(cz80_struc *c) {
    int current_z80 = c-&Z80_context[0];
    curz = &Z80_context[current_z80];
}

void mz80reset(void) {
    Cz80_Reset(curz);
    curz->dwElapsedTicks = 0;
}

UINT32 mz80int(UINT32 irq) {
    Cz80_Set_IRQ(curz,irq);
    return 0;
}

UINT32 mz80nmi(void) {
    Cz80_Set_NMI(curz);
    return 0;
}

UINT32 mz80exec(unsigned long int cycles) {
    UINT32 c = Cz80_Exec(curz,cycles);
    curz->dwElapsedTicks += c;
    return c;
}

UINT32 mz80GetPC() {
    return curz->PC-curz->BasePC;
}

UINT8* mz80GetBase(int cpu) {
    return z80_data[cpu];
}

void mz80ReleaseIRQ(int cpu) {
    Cz80_Clear_IRQ(&Z80_context[cpu]);
}

void mz80ClearTimers() {
    int n;
    for (n=0; n<MAX_Z80; n++)
	Z80_context[n].dwElapsedTicks = 0;
}

UINT32 mz80GetCyclesDone() {
    if (!(curz->Status & CZ80_RUNNING))
	return curz->dwElapsedTicks;
    else
	return curz->dwElapsedTicks+Cz80_Get_CycleDone(curz);
}

int mz80GetCyclesRemaining() {
    return Cz80_Get_CycleRemaining(curz);
}

void reset_z80_banks() {
}

void StopZ80Mode2(UINT16 address, UINT8 data)
{
   print_debug("[StopZ80]\n");
   if (StopAddress)
     Cz80_Set_PC(&Z80_context[0],StopAddress);
   Cz80_Release_Cycle(&Z80_context[0]);
}

void StopZ80BMode2(UINT16 address, UINT8 data)
{
   print_debug("[StopZ80B]\n");
   if (StopAddressB)
     Cz80_Set_PC(&Z80_context[1],StopAddressB);
   Cz80_Release_Cycle(&Z80_context[1]);
}

void StopZ80CMode2(UINT16 address, UINT8 data)
{
   print_debug("[StopZ80B]\n");
   if (StopAddressB)
     Cz80_Set_PC(&Z80_context[2],StopAddressB);
   Cz80_Release_Cycle(&Z80_context[2]);
}

void mz80AddCyclesDone(int cycles) {
    curz->dwElapsedTicks += cycles;
}

void finish_conf_z80(int cpu) {
   add_mz80_memory_region_rb(cpu,0x0000, 0xFFFF, DefBadReadZ80, NULL);
   add_mz80_memory_region_wb(cpu,0x0000, 0xFFFF, DefBadWriteZ80, NULL);

   switch(cpu) {
   case 0: AddZ80AInit(); break;
   case 1: AddZ80BInit(); break;
   case 2: AddZ80CInit(); break;
   case 3: AddZ80DInit(); break;
   }
}

static int allow_wb = 0; // always 0 except when writing region !

void allow_writebank(int allow) {
    allow_wb = allow;
    // Not handled for now
}

