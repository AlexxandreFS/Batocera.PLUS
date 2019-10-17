/******************************************************************************/
/*                                                                            */
/*                          RAINE INTERFACE FOR MZ80                          */
/*                                                                            */
/******************************************************************************/

/*

Raine version of MZ80 has a changed (improved and faster) memory interface.
When calling AddZ80xReadByte() / AddZ80xReadByte():

------+------+--------------------------------+---------------------------------
 call | user | Old MZ80                       | Raine MZ80
------+------+--------------------------------+---------------------------------
 NULL | NULL | -                              | Internal read on current z80Base
 xxxx | NULL | Call with user = NULL          | Call with user = NULL
 xxxx | xxxx | Call with user = xxxx          | Call with user = xxxx
 NULL | xxxx | -                              | Internal read on xxxx base
------+------+--------------------------------+---------------------------------

Call Z80xSetBank() to switch the z80Base address.

puser is relative to 0x0000

*/

#include "raine.h"
#include "mz80help.h"
#include "savegame.h"
#include "loadroms.h" // regions definitions
#include "newmem.h"
#include "cpumain.h" // Z80_0
#include "version.h" // to force a recompilation if RAINE_DEBUG is defined

struct mz80context	Z80_context[MAX_Z80];
struct MemoryReadByte	Z80_memory_rb[MAX_Z80][MAX_Z80_DATA];
struct MemoryWriteByte	Z80_memory_wb[MAX_Z80][MAX_Z80_DATA];
struct z80PortRead	Z80_port_rb[MAX_Z80][MAX_Z80_PORT];
struct z80PortWrite	Z80_port_wb[MAX_Z80][MAX_Z80_PORT];
int MZ80Engine,latch;

static UINT32 memory_count_rb[MAX_Z80];
static UINT32 memory_count_wb[MAX_Z80];

static UINT32 port_count_rb[MAX_Z80];
static UINT32 port_count_wb[MAX_Z80];

UINT8 *Z80RAM;

typedef struct Z80_BANKLIST
{
   UINT8 list[32];
   UINT32 count;
} Z80_BANKLIST;

typedef struct Z80_DATA			// Information about 1 chip
{
   Z80_BANKLIST read_bank;
   Z80_BANKLIST write_bank;
   UINT8 *base_ram;
} Z80_DATA;

struct Z80_DATA z80_data[MAX_Z80];

#ifdef RAINE_DEBUG
int add_z80_debug_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2) {
  if (memory_count_rb[cpu] < MAX_Z80_DATA) {
    memmove(&Z80_memory_rb[cpu][1],&Z80_memory_rb[cpu][0],
	    sizeof(struct MemoryReadByte)*memory_count_rb[cpu]);
    Z80_memory_rb[cpu][0].lowAddr    = d0;
    Z80_memory_rb[cpu][0].highAddr   = d1;
    Z80_memory_rb[cpu][0].memoryCall = d2;
    Z80_memory_rb[cpu][0].pUserArea  = NULL;
    memory_count_rb[cpu]++;
    return 1; // ok
  }
  return 0;
}

void remove_z80_debug_rb(UINT32 cpu, int index) {
  int n = index;
  memmove(&Z80_memory_rb[cpu][n],&Z80_memory_rb[cpu][n+1],
	  sizeof(struct MemoryReadByte)*(memory_count_rb[cpu]-n-1));
  memory_count_rb[cpu]--;
}

void add_z80_port_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2) {
  if (port_count_wb[cpu] < MAX_Z80_DATA) {
    memmove(&Z80_port_wb[cpu][1],&Z80_port_wb[cpu][0],
	    sizeof(struct z80PortWrite)*port_count_wb[cpu]);
    Z80_port_wb[cpu][0].lowIoAddr    = d0;
    Z80_port_wb[cpu][0].highIoAddr   = d1;
    Z80_port_wb[cpu][0].IOCall = d2;
    Z80_port_wb[cpu][0].pUserArea  = NULL;
    port_count_wb[cpu]++;
  }
}

void remove_z80_port_wb(UINT32 cpu, int index) {
  int n = index;
  memmove(&Z80_port_wb[cpu][n],&Z80_port_wb[cpu][n+1],
	  sizeof(struct z80PortWrite)*(port_count_wb[cpu]-n-1));
  port_count_wb[cpu]--;
}

#endif

static void add_mz80_memory_region_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   if(!d2){
      if(!d3){					// Add to bankswitching queue
         d3 = Z80_context[cpu].z80Base;
         z80_data[cpu].read_bank.list[z80_data[cpu].read_bank.count] = memory_count_rb[cpu];
         z80_data[cpu].read_bank.count++;
      }
      else{
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
         d3 = Z80_context[cpu].z80Base;
         z80_data[cpu].write_bank.list[z80_data[cpu].write_bank.count] = memory_count_wb[cpu];
         z80_data[cpu].write_bank.count++;
      }
      else{
         d3 = d3 - d0;
      }
   }

   Z80_memory_wb[cpu][memory_count_wb[cpu]].lowAddr    = d0;
   Z80_memory_wb[cpu][memory_count_wb[cpu]].highAddr   = d1;
   Z80_memory_wb[cpu][memory_count_wb[cpu]].memoryCall = d2;
   Z80_memory_wb[cpu][memory_count_wb[cpu]].pUserArea  = d3;
   memory_count_wb[cpu]++;
}

static void add_mz80_port_region_rb(UINT32 cpu, UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   Z80_port_rb[cpu][port_count_rb[cpu]].lowIoAddr  = d0;
   Z80_port_rb[cpu][port_count_rb[cpu]].highIoAddr = d1;
   Z80_port_rb[cpu][port_count_rb[cpu]].IOCall     = d2;
   Z80_port_rb[cpu][port_count_rb[cpu]].pUserArea  = d3;
   port_count_rb[cpu]++;
}

static void add_mz80_port_region_wb(UINT32 cpu, UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   Z80_port_wb[cpu][port_count_wb[cpu]].lowIoAddr  = d0;
   Z80_port_wb[cpu][port_count_wb[cpu]].highIoAddr = d1;
   Z80_port_wb[cpu][port_count_wb[cpu]].IOCall     = d2;
   Z80_port_wb[cpu][port_count_wb[cpu]].pUserArea  = d3;
   port_count_wb[cpu]++;
}

void Z80SetDataBank(int cpu,UINT8 *src) {
   UINT32 ta,tb;
   for(ta=0; ta<z80_data[cpu].read_bank.count; ta++){
      tb = z80_data[cpu].read_bank.list[ta];			// Get bank pos
      Z80_memory_rb[cpu][tb].pUserArea = src;			// Write new pointer
   }
   for(ta=0; ta<z80_data[cpu].write_bank.count; ta++){
      tb = z80_data[cpu].write_bank.list[ta];			// Get bank pos
      Z80_memory_wb[cpu][tb].pUserArea = src;			// Write new pointer
   }
}

void Z80SetBank(int cpu,UINT8 *src)
{
   // Update base pointer (if called during emulation)

   z80Base = src;
   // Update base pointer (if called outside emulation)

   Z80_context[cpu].z80Base = src;

   z80_data[cpu].base_ram = Z80_context[cpu].z80Base;

   Z80SetDataBank(cpu,src);
}

/*
 *  Fill in the basic structures via these functions...
 */

// FIRST EMULATED Z80

void AddZ80AROMBase(UINT8 *d0, UINT16 d1, UINT16 d2)
{
   Z80_context[0].z80Base = d0;
   z80_data[0].base_ram = Z80_context[0].z80Base;
   Z80_context[0].z80intAddr = d1;
   Z80_context[0].z80nmiAddr = d2;
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

void AddZ80AInit(void)
{
   Z80_context[0].z80MemRead  = Z80_memory_rb[0];
   Z80_context[0].z80MemWrite = Z80_memory_wb[0];
   Z80_context[0].z80IoRead   = Z80_port_rb[0];
   Z80_context[0].z80IoWrite  = Z80_port_wb[0];

   AddLoadCallback(Z80A_load_update);
   AddSaveData(SAVE_Z80_0, (UINT8 *) &Z80_context[0], sizeof(Z80_context[0]));

   MZ80Engine=1;
}

/*
 *  Fill in the basic structures via these functions...
 */

// SECOND EMULATED Z80

void AddZ80BROMBase(UINT8 *d0, UINT16 d1, UINT16 d2)
{
   Z80_context[1].z80Base=d0;
   z80_data[1].base_ram = Z80_context[1].z80Base;
   Z80_context[1].z80intAddr=d1;
   Z80_context[1].z80nmiAddr=d2;
}

void AddZ80BReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_rb(1, d0, d1, d2, d3);
}

void AddZ80BWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_wb(1, d0, d1, d2, d3);
}

void AddZ80BReadPort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_rb(1, d0, d1, d2, d3);
}

void AddZ80BWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_wb(1, d0, d1, d2, d3);
}

void AddZ80BInit(void)
{
   Z80_context[1].z80MemRead  = Z80_memory_rb[1];
   Z80_context[1].z80MemWrite = Z80_memory_wb[1];
   Z80_context[1].z80IoRead   = Z80_port_rb[1];
   Z80_context[1].z80IoWrite  = Z80_port_wb[1];

   AddLoadCallback(Z80B_load_update);
   AddSaveData(SAVE_Z80_1, (UINT8 *) &Z80_context[1], sizeof(Z80_context[1]));

   MZ80Engine=2;
}

/*
 *  Fill in the basic structures via these functions...
 */

// THIRD EMULATED Z80

void AddZ80CROMBase(UINT8 *d0, UINT16 d1, UINT16 d2)
{
   Z80_context[2].z80Base=d0;
   z80_data[2].base_ram = Z80_context[2].z80Base;
   Z80_context[2].z80intAddr=d1;
   Z80_context[2].z80nmiAddr=d2;
}

void AddZ80CReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_rb(2, d0, d1, d2, d3);
}

void AddZ80CWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_wb(2, d0, d1, d2, d3);
}

void AddZ80CReadPort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_rb(2, d0, d1, d2, d3);
}

void AddZ80CWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_wb(2, d0, d1, d2, d3);
}

void AddZ80CInit(void)
{
   Z80_context[2].z80MemRead  = Z80_memory_rb[2];
   Z80_context[2].z80MemWrite = Z80_memory_wb[2];
   Z80_context[2].z80IoRead   = Z80_port_rb[2];
   Z80_context[2].z80IoWrite  = Z80_port_wb[2];

   AddLoadCallback(Z80C_load_update);
   AddSaveData(SAVE_Z80_2, (UINT8 *) &Z80_context[2], sizeof(Z80_context[2]));

   MZ80Engine=3;
}

/*
 *  Fill in the basic structures via these functions...
 */

// FOURTH EMULATED Z80

void AddZ80DROMBase(UINT8 *d0, UINT16 d1, UINT16 d2)
{
   Z80_context[3].z80Base=d0;
   z80_data[3].base_ram = Z80_context[3].z80Base;
   Z80_context[3].z80intAddr=d1;
   Z80_context[3].z80nmiAddr=d2;
}

void AddZ80DReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_rb(3, d0, d1, d2, d3);
}

void AddZ80DWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_mz80_memory_region_wb(3, d0, d1, d2, d3);
}

void AddZ80DReadPort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_rb(3, d0, d1, d2, d3);
}

void AddZ80DWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3)
{
   add_mz80_port_region_wb(3, d0, d1, d2, d3);
}

void AddZ80DInit(void)
{
   Z80_context[3].z80MemRead  = Z80_memory_rb[3];
   Z80_context[3].z80MemWrite = Z80_memory_wb[3];
   Z80_context[3].z80IoRead   = Z80_port_rb[3];
   Z80_context[3].z80IoWrite  = Z80_port_wb[3];

   AddLoadCallback(Z80D_load_update);
   AddSaveData(SAVE_Z80_3, (UINT8 *) &Z80_context[3], sizeof(Z80_context[3]));

   MZ80Engine=4;
}

static void convert_savegame_type1(int cpu) {
  if (Z80_context[cpu].z80intPending) // interruptstate in 2.7
    Z80_context[cpu].z80iff = 3;
  else
    Z80_context[cpu].z80iff = 0; // ints disabled
  Z80_context[cpu].z80intPending = 0; // No sense with mz80 2.7 !
}

static void z80_load_update(int cpu) {
  print_debug("Z80%c Load Callback()\n",65+cpu);

  if (savegame_version == SAVE_FILE_TYPE_1)
    convert_savegame_type1(cpu);
  Z80_context[cpu].z80MemRead  = Z80_memory_rb[cpu];
  Z80_context[cpu].z80MemWrite = Z80_memory_wb[cpu];
  Z80_context[cpu].z80IoRead   = Z80_port_rb[cpu];
  Z80_context[cpu].z80IoWrite  = Z80_port_wb[cpu];
  Z80_context[cpu].z80Base     = z80_data[cpu].base_ram;
}

void Z80A_load_update(void)
{
  z80_load_update(0);
}

void Z80B_load_update(void)
{
  z80_load_update(1);
}

void Z80C_load_update(void)
{
  z80_load_update(2);
}

void Z80D_load_update(void)
{
  z80_load_update(3);
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

      z80_data[ta].read_bank.count = 0;
      z80_data[ta].write_bank.count = 0;

      Z80_context[0].z80Base = NULL;
      z80_data[0].base_ram = NULL;
   }
   StopAddress = StopAddressB = StopAddressC = StopAddressD = 0;
}

void StopZ80(UINT16 address, UINT8 data)
{
   print_debug("[StopZ80]\n");
   mz80ReleaseTimeslice();
}

void SetStopZ80Mode2(UINT16 address)
{
   StopAddress=address;
}

void StopZ80Mode2(UINT16 address, UINT8 data)
{
   print_debug("[StopZ80]\n");
   if (StopAddress)
     z80pc=StopAddress;
   mz80ReleaseTimeslice();
}

void SetStopZ80BMode2(UINT16 address)
{
   StopAddressB=address;
}

void StopZ80BMode2(UINT16 address, UINT8 data)
{
   print_debug("[StopZ80B]\n");
   if (StopAddressB)
     z80pc=StopAddressB;
   mz80ReleaseTimeslice();
}

void SetStopZ80CMode2(UINT16 address)
{
   StopAddressC=address;
}

void StopZ80CMode2(UINT16 address, UINT8 data)
{
  print_debug("[StopZ80C]\n");
  if (StopAddressC)
    z80pc=StopAddressC;
   mz80ReleaseTimeslice();
}

void SetStopZ80DMode2(UINT16 address)
{
   StopAddressD=address;
}

void StopZ80DMode2(UINT16 address, UINT8 data)
{
  print_debug("[StopZ80D]\n");
  if (StopAddressD)
    z80pc=StopAddressD;
   mz80ReleaseTimeslice();
}

UINT16 DefBadReadZ80(UINT16 offset)
{
  print_debug("Z80BadRead(%04x) [%04x] z80:%d\n",offset,z80pc,current_cpu_num[CPU_Z80_0>>4]);
   return(0xFF);
}

UINT16 DefBadReadPortZ80(UINT16 offset)
{
  print_debug("Z80BadReadPort(%04x) [%04x] z80:%d\n",offset,z80pc,current_cpu_num[CPU_Z80_0>>4]);
   return(0xFF);
}

void DefBadWriteZ80(UINT16 offset, UINT8 data)
{
  print_debug("Z80BadWrite(%04x,%02x) [%04x] z80:%d\n",offset,data,z80pc,current_cpu_num[CPU_Z80_0>>4]);
}

void DefBadWritePortZ80(UINT16 offset, UINT8 data)
{
  print_debug("Z80BadWritePort(%04x,%02x) [%04x] z80:%d\n",offset,data,z80pc,current_cpu_num[CPU_Z80_0>>4]);
}

// rom bankswitch code base on regions
// Taken from cps1.c

#define MAX_BANKS 80

UINT8 *ROM_BANK[MAX_Z80],*bank[3][MAX_BANKS];
static UINT16 nb_banks[MAX_Z80],current_bank[MAX_Z80],bank_offset[MAX_Z80],
  bank_len[MAX_Z80];

void reset_z80_banks() {
  int n;
  for (n=0; n<MAX_Z80; n++)
    bank_len[n] = bank_offset[n] = nb_banks[n] = 0;
}

void write_z80_bank(int cpu, int n, int address, int data) {
    WriteByte(bank[cpu][n]+address,data);
}

int read_z80_bank(int cpu, int n, int address) {
    return *(bank[cpu][n]+address);
}

static int allow_wb = 0; // always 0 except when writing region !

void allow_writebank(int allow) {
    allow_wb = allow;
}

static int check_z80_bank_write(int cpu, int index,UINT32 address,UINT8 data) {
  int ta,tb,n;
  /* The allow_wb check is for the hiscores ! They write to ram and usually the
   * ram is placed after the banks, so allowing to write to banks here messes
   * things up. So allowing writing to banks only when writing explicitely to
   * the rom (language dipswitch) */
  if (!allow_wb) return 0;

  // This function writes to a rom bank if needs to.
  // Clearly writing to a place in a bank must be to a prcise bank.
  // The problem is that for now there is no way to guess when bank we want
  // Region switches seem to use the last bank usually...

  // The only reasonable way to write to bank is this one : having the absolute
  // address into the ROM
  if (bank_len[cpu]) {
    int nb;
    if (address > bank_offset[cpu]) {
      address -= bank_offset[cpu];
      nb = ((address) / bank_len[cpu]);
      // new address is then...
      address = (nb*(bank_offset[cpu]+bank_len[cpu]))+(address&(bank_len[cpu]-1))+bank_offset[cpu];
    }
    WriteByte(ROM_BANK[cpu]+address,data);
    return 1;
  }

  // this one is the bad way for old drivers : some drivers have a z80 address
  // to write to a bank. Writing to every bank is stupid, but how am I supposed
  // to guess the right bank ???
   for(ta=0; ta<z80_data[cpu].read_bank.count; ta++){
      tb = z80_data[cpu].read_bank.list[ta];  // Get bank pos
      if (tb == index) {
	if (nb_banks[cpu]) { // I suppose there is only 1 bank (!)
	  // address -= bank_offset[cpu]; // For data banks
	  if (bank[cpu][0]) { // rom bank
	    // for (n=0; n<nb_banks[cpu]; n++) {
	    for (n=0; n<nb_banks[cpu]; n++)
		WriteByte(bank[cpu][n]+address,data);
	    // }
	    return 1;
	  } else  { // data bank
	    WriteByte(ROM_BANK[cpu]+address,data);
	    return 1;
	  }
	} else {
#ifdef RAINE_DEBUG
	  allegro_message("WARNING : you attempt to write in a banked area with a non-standard bankswitch code\n");
#endif
	}
	break;
      }
   }
   return 0;
}

static int check_z80_bank_read(int cpu, int index,UINT32 address) {
  int ta,tb,n;

  // Equivalent of the function just before, for read this time
  if (bank_len[cpu]) {
    int nb;
    if (address > bank_offset[cpu]) {
      address -= bank_offset[cpu];
      nb = ((address) / bank_len[cpu]);
      // new address is then...
      address = (nb*(bank_offset[cpu]+bank_len[cpu]))+(address&(bank_len[cpu]-1))+bank_offset[cpu];
    }
    return ReadByte(ROM_BANK[cpu]+address);
  }

   for(ta=0; ta<z80_data[cpu].read_bank.count; ta++){
      tb = z80_data[cpu].read_bank.list[ta];  // Get bank pos
      if (tb == index) {
	if (nb_banks[cpu]) { // I suppose there is only 1 bank (!)
	  // address -= bank_offset[cpu]; // For data banks
	  if (bank[cpu][0]) { // rom bank
	    // for (n=0; n<nb_banks[cpu]; n++) {
	    n = nb_banks[cpu] - 1;
	    // }
	    return ReadByte(bank[cpu][n]+address);
	  } else  { // data bank
	    return ReadByte(ROM_BANK[cpu]+address);
	  }
	} else {
#ifdef RAINE_DEBUG
	  allegro_message("WARNING : you attempt to write in a banked area with a non-standard bankswitch code\n");
#endif
	}
	break;
      }
   }
   return -1;
}

static void prepare_cpu_adr(int *cpu, UINT32 *address) {
  // Hack : to access the 1 cpu, pass address + 0x1000000
  // 2nd is address + 0x2000000, etc...
  *cpu = 0;
  while (*address >= 0x1000000) {
    *cpu = *cpu + 1;
    *address -= 0x1000000;
  }
  if (*cpu == 0) {
    // Antiriad programmed many games with a fake z80 #0...
    if (Z80_context[0].z80Base)
      *cpu = 0;
    else
     *cpu = 1;
  }

  if (*cpu > MZ80Engine-1) {
    *cpu = MZ80Engine -1;
  }
}

void write_z80_to_rom(UINT32 address, UINT8 data)
{
  int old = address;
  int cpu;
  prepare_cpu_adr(&cpu,&address);
  if (bank_len[cpu]) {
    check_z80_bank_write(cpu,0,address,data);
    return;
  }
  WriteMZ80Byte(old,data);
}

void WriteMZ80Byte(UINT32 address, UINT8 data)
{
  int ta, cpu;
  prepare_cpu_adr(&cpu,&address);

  // HACK : we are supposing that the RAM is read/write
  // and since there are cases where we cant write to ROM
  // we use Z80_memory_rb instead of z80_memory_wb.

  if (address > 0xffff) {
      check_z80_bank_write(cpu,0,address,data);
      return;
  }

   for(ta=0;ta<99;ta++){
      if((Z80_memory_rb[cpu][ta].lowAddr)==-1){
         ta=99;
            print_debug("Wb(%04x,%02x) [Via WriteMZ80Byte]\n",address,data);
      }
      else{
         if((address>=Z80_memory_rb[cpu][ta].lowAddr)&&(Z80_memory_rb[cpu][ta].highAddr>=address)){
            if(Z80_memory_rb[cpu][ta].memoryCall==NULL){
	      if (!check_z80_bank_write(cpu,ta,address,data)) {
		WriteByte( ((UINT8 *) Z80_memory_rb[cpu][ta].pUserArea) + address,data);
	      }
	      ta=99;
            }
            //else{
            //   *MC68000A_memoryall[ta].memorycall(address,data);
            //}
         }
      }
   }
}

UINT8 read_z80_from_rom(UINT32 address) {
  int old = address;
  int cpu;
  prepare_cpu_adr(&cpu,&address);
  if (bank_len[cpu]) {
    return check_z80_bank_read(cpu,0,address);
  }
  return ReadMZ80Byte(old);
}

UINT8 ReadMZ80Byte(UINT32 address)
{
  int ta,cpu;
  prepare_cpu_adr(&cpu,&address);
  if (address > 0xffff)
      return check_z80_bank_read(cpu,0,address);

  for(ta=0;ta<99;ta++){
    if((Z80_memory_rb[cpu][ta].lowAddr)==-1){
      print_debug("Rb(%04x) [Via ReadMZ80Byte]\n",address);
      return(0x00);
    }
    else{
      if((address>=Z80_memory_rb[cpu][ta].lowAddr)&&(Z80_memory_rb[cpu][ta].highAddr>=address)){
	if(Z80_memory_rb[cpu][ta].memoryCall==NULL){
	    UINT8 data = ReadByte( ((UINT8 *) Z80_memory_rb[cpu][ta].pUserArea) + address);
	  return data;
	}
      }
    }
  }

  return 0x00;
}

static void RestoreBankA(void)
{
  int old_bank = current_bank[0];
  current_bank[0] = -1;
  z80a_set_bank(0,old_bank);
}

static void RestoreBankB(void)
{
  int old_bank = current_bank[1];
  current_bank[1] = -1;
  z80_set_bank(1,old_bank);
}

static void RestoreBankC(void)
{
  int old_bank = current_bank[2];
  current_bank[2] = -1;
  z80_set_bank(2,old_bank);
}

static void RestoreBankD(void)
{
  int old_bank = current_bank[3];
  current_bank[3] = -1;
  z80_set_bank(3,old_bank);
}

void z80_set_data_bank(int cpu, UINT16 data) {
  if (data != current_bank[cpu] && data < nb_banks[cpu]) {
    current_bank[cpu] = data;
    print_debug("z80_set_data_bank %d,%d\n",cpu,data);
    Z80SetDataBank(0,ROM_BANK[cpu]+bank_offset[cpu]+bank_len[cpu]*data);
  }
#ifdef RAINE_DEBUG
  else if (data >= nb_banks[cpu]) print_debug("bad z80_set_data_bank %d,%d\n",cpu,data);
#endif
}

static void RestoreDataBankA()
{
  int old_bank = current_bank[0];
  current_bank[0] = -1;
  z80_set_data_bank(0,old_bank);
}

static void RestoreDataBankB()
{
  int old_bank = current_bank[1];
  current_bank[1] = -1;
  z80_set_data_bank(1,old_bank);
}

static void RestoreDataBankC()
{
  int old_bank = current_bank[2];
  current_bank[2] = -1;
  z80_set_data_bank(2,old_bank);
}

static void RestoreDataBankD()
{
  int old_bank = current_bank[3];
  current_bank[3] = -1;
  z80_set_data_bank(3,old_bank);
}

void z80_init_banks_area(int cpu,UINT8 *rombase, int rom_size, UINT32 offset,
			 UINT16 len)
{
  /* offset is the start of the bank in the region ie : */
  /* 0       -(offset-1)     ROM */
  /* (offset)-(offset+len-1) bank*/
  UINT32 size,n;
  // len2 is for stupid mcatadv which uses a bank of 0x8000 bytes by increments of 0x4000
  int len2 = (len > 0x4000 ? 0x4000 : len);

  nb_banks[cpu] = (rom_size - offset)/len2;
  size = nb_banks[cpu] * (offset + len); // must copy the rom for each bank
  bank_offset[cpu] = offset;
  bank_len[cpu] = len2;
  if (nb_banks[cpu] > MAX_BANKS) {
    allegro_message("cpu %d nb_banks (%d) > MAX_BANKS",cpu,nb_banks[cpu]);
    exit(1);
  }

  ROM_BANK[cpu] = AllocateMem(size);
  if (!ROM_BANK[cpu]) return;

  for (n=0; n<nb_banks[cpu]; n++) {
    UINT8 *dst = ROM_BANK[cpu] + n * (offset+len);
    bank[cpu][n] = dst;
    memcpy(dst, rombase, offset); // ROM
    if (len2 != len && n == nb_banks[cpu] - 1)
      memcpy(dst+offset, rombase+offset+(n*len2), len2); // bank
    else {
      memcpy(dst+offset, rombase+offset+(n*len2), len); // bank
    }
  }

  current_bank[cpu] = -1;
  print_debug("z80_init_banks cpu %d - nb_banks = %d\n",cpu,nb_banks[cpu]);
  AddSaveData(ASCII_ID('Z','B','K',cpu), (UINT8 *)&current_bank[cpu], sizeof(int));
  switch(cpu) {
  case 0: AddLoadCallback(RestoreBankA); break;
  case 1: AddLoadCallback(RestoreBankB); break;
  case 2: AddLoadCallback(RestoreBankC); break;
  case 3: AddLoadCallback(RestoreBankD); break;
  default: allegro_message("init_banks : cpu %d not supported\n",cpu);
  }
}

void z80_init_banks_area_gap(int cpu,UINT8 *rombase, int rom_size,
			     UINT32 offset,UINT32 bank_start,UINT16 len)
{
  /* This one has a gap between the rom and the bank */
  /* offset is the start of the bank in the region ie : */
  /* 0       -(offset-1)     ROM */
  /* ... (ram or others) */
  /* (bank_start)-(bank_start+len-1) bank*/
  UINT32 size,n;
  nb_banks[cpu] = (rom_size - offset)/len;
  size = nb_banks[cpu] * (bank_start + len); // must copy the rom for each bank
  bank_offset[cpu] = offset;
  if (nb_banks[cpu] > MAX_BANKS) {
    allegro_message("cpu %d nb_banks (%d) > MAX_BANKS",cpu,nb_banks[cpu]);
    exit(1);
  }

  ROM_BANK[cpu] = AllocateMem(size);
  if (!ROM_BANK[cpu]) return;

  for (n=0; n<nb_banks[cpu]; n++) {
    UINT8 *dst = ROM_BANK[cpu] + n * (bank_start+len);
    bank[cpu][n] = dst;
    memcpy(dst, rombase, offset); // ROM
    memcpy(dst+bank_start, rombase+offset+(n*len), len); // bank
  }

  current_bank[cpu] = -1;
  print_debug("z80_init_banks cpu %d - nb_banks = %d\n",cpu,nb_banks[cpu]);
  AddSaveData(ASCII_ID('Z','B','K',cpu), (UINT8 *)&current_bank[cpu], sizeof(int));
  switch(cpu) {
  case 0: AddLoadCallback(RestoreBankA); break;
  case 1: AddLoadCallback(RestoreBankB); break;
  case 2: AddLoadCallback(RestoreBankC); break;
  case 3: AddLoadCallback(RestoreBankD); break;
  default: allegro_message("init_banks : cpu %d not supported\n",cpu);
  }
}


void z80_init_banks_area_ofs(int cpu,UINT8 *rombase, int rom_size, UINT32 offset,
			 UINT16 len,UINT16 bank_offs)
{
  // bank_offs is the number of ram banks at begining.
  // bank 0-bank_offs-1 are ram, then real banks.
  /* offset is the start of the bank in the region ie : */
  /* 0       -(offset-1)     ROM */
  /* (offset)-(offset+len-1) bank*/
  UINT32 size,n;
  nb_banks[cpu] = (rom_size - offset)/len+bank_offs;
  size = nb_banks[cpu] * (offset + len); // must copy the rom for each bank
  bank_offset[cpu] = offset;
  if (nb_banks[cpu] > MAX_BANKS) {
    allegro_message("cpu %d nb_banks (%d) > MAX_BANKS",cpu,nb_banks[cpu]);
    exit(1);
  }

  ROM_BANK[cpu] = AllocateMem(size);
  if (!ROM_BANK[cpu]) return;

  for (n=0; n<nb_banks[cpu]; n++) {
    UINT8 *dst = ROM_BANK[cpu] + n * (offset+len);
    bank[cpu][n] = dst;
    memcpy(dst, rombase, offset); // ROM
    if (n<bank_offs) continue;
    memcpy(dst+offset, rombase+offset+((n-bank_offs)*len), len); // bank
  }

  current_bank[cpu] = -1;
  print_debug("z80_init_banks cpu %d - nb_banks = %d\n",cpu,nb_banks[cpu]);
  AddSaveData(ASCII_ID('Z','B','K',cpu), (UINT8 *)&current_bank[cpu], sizeof(int));
  switch(cpu) {
  case 0: AddLoadCallback(RestoreBankA); break;
  case 1: AddLoadCallback(RestoreBankB); break;
  case 2: AddLoadCallback(RestoreBankC); break;
  case 3: AddLoadCallback(RestoreBankD); break;
  default: allegro_message("init_banks : cpu %d not supported\n",cpu);
  }
}


void z80_init_data_banks_area(int cpu,UINT8 *rom,int rom_size,UINT32 offset,
			      UINT16 len)
{
  // Same thing as init_banks, but the bank contains data only, which makes
  // things MUCH easier !!!
  // And it saves memory too...

  nb_banks[cpu] = (rom_size - offset)/len;
  current_bank[cpu] = -1;
  bank_offset[cpu] = offset;
  bank_len[cpu] = len;
  ROM_BANK[cpu] = rom;

  print_debug("z80_init_data_banks - nb_banks = %d\n",nb_banks[cpu]);
  AddSaveData(ASCII_ID('Z','B','D',cpu), (UINT8 *)&current_bank[cpu], sizeof(int));
  switch(cpu) {
  case 0: AddLoadCallback(RestoreDataBankA); break;
  case 1: AddLoadCallback(RestoreDataBankB); break;
  case 2: AddLoadCallback(RestoreDataBankC); break;
  case 3: AddLoadCallback(RestoreDataBankD); break;
  default: allegro_message("init_data_banks : cpu %d not supported\n",cpu);
  }
}

void z80_init_banks_gap(int cpu,UINT32 region,UINT32 offset,
			UINT32 bank_start,UINT16 len) {
  z80_init_banks_area_gap(cpu,load_region[region],get_region_size(region),
			  offset,bank_start,len);
}

void z80_init_banks(int cpu,UINT32 region,UINT32 offset, UINT16 len)
{
  int size = get_region_size(region);
  if (size < offset || size < len) {
    print_debug("z80_init_banks: asked for offset %x len %x and region size %x\n",offset,len,size);
    return;
  }
  z80_init_banks_area(cpu,load_region[region],get_region_size(region),
		      offset,len);
}

void z80_init_data_banks(int cpu,UINT32 region,UINT32 offset, UINT16 len) {
  z80_init_data_banks_area(cpu,load_region[region],get_region_size(region),
			   offset,len);
}

void z80_set_bank(int cpu, UINT8 data)
{
  if (data != current_bank[cpu] && data < nb_banks[cpu]) {
    current_bank[cpu] = data;
    print_debug("z80_set_bank %x,%d\n",cpu,data);
    Z80SetBank(cpu,bank[cpu][data]);
  }
#ifdef RAINE_DEBUG
  else if (data >= nb_banks[cpu]) print_debug("bad z80_set_bank cpu %d %d\n",cpu,data);
#endif
}

int z80_get_current_bank(int cpu) {
  return current_bank[cpu];
}

void z80a_set_bank(UINT16 offset, UINT8 data) {
  z80_set_bank(0,data);
}

// Latch commands (for sound)

int latch; // global because it can be usefull in handlers (direct access)

UINT8 soundlatch_lo_r(UINT32 offset) {
  return latch & 0xff;
}

UINT8 soundlatch_hi_r(UINT32 offset) {
  return latch >> 8;
}

void soundcmd_w(UINT32 offset,UINT16 data)
{
  latch = data;
  cpu_int_nmi(CPU_Z80_0);
}

void soundcmd_wb(UINT32 offset, UINT8 data)
{
  if (offset & 1)
    latch = (latch & 0xff) | (data << 8);
  else
    latch = (latch & 0xff00) | data;
  cpu_int_nmi(CPU_Z80_0);
}

void soundcmd_wb_nonmi(UINT32 offset, UINT8 data)
{
  if (offset & 1)
    latch = (latch & 0xff) | (data << 8);
  else
    latch = (latch & 0xff00) | data;
}

void soundcmd_w_nonmi(UINT32 offset,UINT16 data)
{
  latch = data;
}

void z80_set_read_db(int cpu, int bank, UINT8 *src) {
    Z80_memory_rb[cpu][z80_data[cpu].read_bank.list[bank]].pUserArea =
	src - Z80_memory_rb[cpu][z80_data[cpu].read_bank.list[bank]].lowAddr;
}

UINT32 mz80GetPC() {
    return z80pc;
}

UINT8* mz80GetBase(int cpu) {
    return Z80_context[cpu & 0xf].z80Base;
}

void mz80ReleaseIRQ(int cpu) {
    z80intPending = 0;
}

void mz80ClearTimers() {
    dwElapsedTicks = 0;
}

UINT32 mz80GetCyclesDone() {
    return dwElapsedTicks;
}

void mz80AddCyclesDone(int cycles) {
    dwElapsedTicks += cycles;
}

int mz80GetCyclesRemaining() {
    return cyclesRemaining;
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

void finish_conf_z80_ports(int cpu) {
   add_mz80_port_region_rb(cpu, 0x00, 0xFF, DefBadReadPortZ80, NULL);
   add_mz80_port_region_wb(cpu, 0x00, 0xFF, DefBadWritePortZ80, NULL);
   finish_conf_z80(cpu);
}

