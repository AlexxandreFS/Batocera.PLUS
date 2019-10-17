#include "raine.h"
#include "ingame.h"

int speed_hack = 0; // speed hack detection (see execute_xxx_frame)

#define NB_ADR 32
static UINT8* adr[NB_ADR];
static UINT16 wordval[NB_ADR];
static int hack_length;

void undo_hack() {
  // Undo the speed hack when a game is reseted, or the rom check will fail
  // Sigh ! This is to avoid to have to find 80 rom check functions or so.
  if (speed_hack) {
    int n;
    for (n=0; n<hack_length; n++)
      WriteWord(adr[n],wordval[n]);
    hack_length = 0;
    speed_hack = 0; // Not found yet...
  }
}

void pWriteWord(UINT8* myadr, UINT16 val) {
  adr[hack_length] = myadr;
  wordval[hack_length] = ReadWord(myadr);
  hack_length++;
  if (hack_length == NB_ADR) {
    printf("speed hack overloads NB_ADR\n");
    hack_length--;
  }
  WriteWord(myadr,val);
}

void apply_rom_hack(UINT8 *ROM, UINT32 pc, int kind) {
  print_ingame(180,gettext("Applied speed hack %d at %x"),kind,pc);
  print_debug("Applied speed hack %d at %x\n",kind,pc);
  speed_hack = 1;

  pWriteWord(&ROM[pc],0x4239);
  pWriteWord(&ROM[pc+2],0xaa);
  pWriteWord(&ROM[pc+4],0);
  if (kind == 1) {
    pWriteWord(&ROM[pc+6],0x4e71);
  } else if (kind == 2) {
    // qsound (punisher)
    pWriteWord(&ROM[pc+6],0x6000);
  } else if (kind == 3) {
    // qsound (slammast)
    pWriteWord(&ROM[pc+6],0x6008);
  } else if (kind == 10) {
    // cps2 beq long
    pWriteWord(&ROM[pc+6],0x4e71);
    pWriteWord(&ROM[pc+8],0x4e71);
  } else if (kind == 11) {
    // cps2 most stupid (19xx)
    pWriteWord(&ROM[pc+6],0x4e71);
    pWriteWord(&ROM[pc+8],0x4e71);
    pWriteWord(&ROM[pc+10],0x4e71);
  }
}

void apply_hack(UINT32 pc, int kind) {
  apply_rom_hack(ROM, pc, kind);
}

UINT8 *get_speed_hack_adr(int n) {
  return adr[n];
}

