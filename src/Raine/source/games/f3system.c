/******************************************************************************/
/*                                                                            */
/*                          TAITO F3-SYSTEM SUPPORT                           */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "savegame.h"
#include "mame/handlers.h"
#include "sasound.h" // Including this one in f3... !!!
#include "es5506.h"
#include "emumain.h"
#include "lspr16.h"

//#define DUMP 1

char f3_shared_ram[0x10000];
UINT8 *EEPROM;
int f3_bg0_id,f3_bg1_id,f3_bg2_id,f3_bg3_id,f3_bg5_id,f3_bg6_id;

struct INPUT_INFO f3_system_inputs[] =
{
   INP0( COIN1, 0x069001, 0x10 ),
   INP0( COIN2, 0x069001, 0x20 ),
   INP0( TILT, 0x069002, 0x01 ),
   INP0( SERVICE, 0x069002, 0x0E ),
   INP0( TEST, 0x069001, 0x02 ),

   INP0( P1_START, 0x069002, 0x10 ),
   INP0( P1_UP, 0x069007, 0x01 ),
   INP0( P1_DOWN, 0x069007, 0x02 ),
   INP0( P1_LEFT, 0x069007, 0x04 ),
   INP0( P1_RIGHT, 0x069007, 0x08 ),
   INP0( P1_B1, 0x069003, 0x01 ),
   INP0( P1_B2, 0x069003, 0x02 ),
   INP0( P1_B3, 0x069003, 0x04 ),

   INP0( P2_START, 0x069002, 0x20 ),
   INP0( P2_UP, 0x069007, 0x10 ),
   INP0( P2_DOWN, 0x069007, 0x20 ),
   INP0( P2_LEFT, 0x069007, 0x40 ),
   INP0( P2_RIGHT, 0x069007, 0x80 ),
   INP0( P2_B1, 0x069003, 0x10 ),
   INP0( P2_B2, 0x069003, 0x20 ),
   INP0( P2_B3, 0x069003, 0x40 ),

   END_INPUT
};

struct INPUT_INFO f3_system_inputs_6_button[] =
{
   INP0( COIN1, 0x069001, 0x10 ),
   INP0( COIN2, 0x069001, 0x20 ),
   INP0( TILT, 0x069002, 0x01 ),
   INP0( SERVICE, 0x069002, 0x0E ),
   INP0( TEST, 0x069001, 0x02 ),

   INP0( P1_START, 0x069002, 0x10 ),
   INP0( P1_UP, 0x069007, 0x01 ),
   INP0( P1_DOWN, 0x069007, 0x02 ),
   INP0( P1_LEFT, 0x069007, 0x04 ),
   INP0( P1_RIGHT, 0x069007, 0x08 ),
   INP0( P1_B1, 0x069003, 0x01 ),
   INP0( P1_B2, 0x069003, 0x02 ),
   INP0( P1_B3, 0x069003, 0x04 ),
   INP0( P1_B4, 0x069017, 0x01 ),
   INP0( P1_B5, 0x069017, 0x02 ),
   INP0( P1_B6, 0x069017, 0x04 ),

   INP0( P2_START, 0x069002, 0x20 ),
   INP0( P2_UP, 0x069007, 0x10 ),
   INP0( P2_DOWN, 0x069007, 0x20 ),
   INP0( P2_LEFT, 0x069007, 0x40 ),
   INP0( P2_RIGHT, 0x069007, 0x80 ),
   INP0( P2_B1, 0x069003, 0x10 ),
   INP0( P2_B2, 0x069003, 0x20 ),
   INP0( P2_B3, 0x069003, 0x40 ),
   INP0( P2_B4, 0x069012, 0x01 ),
   INP0( P2_B5, 0x069012, 0x02 ),
   INP0( P2_B6, 0x069012, 0x04 ),

   END_INPUT
};

struct INPUT_INFO f3_system_inputs_4_player[] =
{
   INP0( COIN1, 0x069001, 0x10 ),
   INP0( COIN2, 0x069001, 0x20 ),
   INP0( COIN3, 0x069001, 0x40 ),
   INP0( COIN4, 0x069001, 0x80 ),
   INP0( TILT, 0x069002, 0x01 ),
   INP0( SERVICE, 0x069002, 0x0E ),
   INP0( TEST, 0x069001, 0x02 ),

   INP0( P1_START, 0x069002, 0x10 ),
   INP0( P1_UP, 0x069007, 0x01 ),
   INP0( P1_DOWN, 0x069007, 0x02 ),
   INP0( P1_LEFT, 0x069007, 0x04 ),
   INP0( P1_RIGHT, 0x069007, 0x08 ),
   INP0( P1_B1, 0x069003, 0x01 ),
   INP0( P1_B2, 0x069003, 0x02 ),
   INP0( P1_B3, 0x069003, 0x04 ),

   INP0( P2_START, 0x069002, 0x20 ),
   INP0( P2_UP, 0x069007, 0x10 ),
   INP0( P2_DOWN, 0x069007, 0x20 ),
   INP0( P2_LEFT, 0x069007, 0x40 ),
   INP0( P2_RIGHT, 0x069007, 0x80 ),
   INP0( P2_B1, 0x069003, 0x10 ),
   INP0( P2_B2, 0x069003, 0x20 ),
   INP0( P2_B3, 0x069003, 0x40 ),

   INP0( P3_START, 0x069002, 0x40 ),
   INP0( P3_UP, 0x069017, 0x01 ),
   INP0( P3_DOWN, 0x069017, 0x02 ),
   INP0( P3_LEFT, 0x069017, 0x04 ),
   INP0( P3_RIGHT, 0x069017, 0x08 ),
   INP0( P3_B1, 0x069012, 0x01 ),
   INP0( P3_B2, 0x069012, 0x02 ),
   INP0( P3_B3, 0x069012, 0x04 ),

   INP0( P4_START, 0x069002, 0x80 ),
   INP0( P4_UP, 0x069017, 0x10 ),
   INP0( P4_DOWN, 0x069017, 0x20 ),
   INP0( P4_LEFT, 0x069017, 0x40 ),
   INP0( P4_RIGHT, 0x069017, 0x80 ),
   INP0( P4_B1, 0x069012, 0x10 ),
   INP0( P4_B2, 0x069012, 0x20 ),
   INP0( P4_B3, 0x069012, 0x40 ),

   END_INPUT
};

static int es_tmp=1,timer_mode;
static int counter,vector_reg,imr_status,m68681_imr;
static data16_t es5510_dsp_ram[0x200];
static data32_t	es5510_gpr[0xc0];
static data32_t	es5510_gpr_latch;
static void *timer_68681=NULL;
int int7_active = 0; // Must take this into account when executing the frame...
int f3_cycles_68000,f3_slices;

struct ES5505interface es5505_interface =
{
	1,					/* total number of chips */
	{ 16000000 },		/* freq */
	{ 0 },	/* Bank 0: Unused by F3 games? */
	{ 0 },	/* Bank 1: All games seem to use this */
	{ YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT) },		/* master volume */
	{ 0 }				/* irq callback */
};

struct SOUND_INFO f3_sound[] =
{
   { SOUND_ES5505,  &es5505_interface,  },
   { 0,             NULL,               },
};

int max_banks_this_game; //=memory_region_length(REGION_SOUND1)/0x200000;
UINT8 *M68000ROM, *M68000RAM; // sound 68000 memory...

// For the timer, might be usefull...
#define M68000_CLOCK	16000000
#define M68681_CLOCK	2000000 /* Actually X1, not the main clock */

READ16_HANDLER(f3_68000_share_rw)
{
  //fprintf(stderr,"_rw\n");
  //exit(1);
  return ReadWord68k(f3_shared_ram+(offset & 0xfff));
}

static int INLINE convert_offset(int offset) {
  offset >>=1;
  offset &= 0xfff;
  return offset;
}

READ_HANDLER( f3_68000_share_rb ) {
  int res = f3_shared_ram[convert_offset(offset)];
#ifdef DUMP
#endif
  return res;
}

WRITE_HANDLER( f3_68000_share_wb ) {
  f3_shared_ram[convert_offset(offset)]=data;
#ifdef DUMP
#endif

}

WRITE16_HANDLER(f3_68000_share_ww)
{
  //offset>>=1;
  offset &= 0xfff;
  WriteWord68k(f3_shared_ram+offset,data);
#ifdef DUMP
#endif
  //fprintf(stderr,"f3_68000_share_w %x,%x\n",offset,data);
  //exit(1);
}

void f3_68681_reset(void)
{
  int7_active = 0;
  timer_mode = 0;
  if (timer_68681) {
    //timer_remove(timer_68681);
    timer_68681=NULL;
  }
}

READ_HANDLER( ES5505_data_0_rb ) {
  int res = ES5505_data_0_r(offset);
  if (offset & 1)
    res &= 0xff;
  else
     res>>=8;
  //fprintf(stderr,"ES5505_data_0_r %x -> %x\n",offset,res);
  return res;
}

WRITE_HANDLER( ES5505_data_0_wdebug ) {
}

READ16_HANDLER(f3_68681_rdebug)
{
  return 0;
}

READ_HANDLER(f3_68681_rb)
{
  int ret;
  offset>>=1;
  offset &= 0x1f;
  if (offset==0x5) {
    ret=imr_status;
    imr_status=0;

    //		logerror("%06x: 68681 read offset %04x (%04x)\n",cpu_get_pc(),offset,ret);
  } else
    if (offset==0xe)
      ret= 1;

  /* IRQ ack */
    else if (offset==0xf) {
      //cpu_set_irq_line(1, 6, CLEAR_LINE);
      //cpu_interrupt(CPU_68K_0,6);
      ret= 0;
    } else
      ret= 0xff;
#ifdef DUMP
#endif
  return ret;
}

WRITE16_HANDLER(f3_68681_wdebug)
{
}

void f3_timer_callback() {
  //WriteLong(&M68000RAM[0x0060+4*7],vector_reg);
  //if (ReadLong68k(&M68000RAM[vector_reg]) != ReadLong68k(&M68000RAM[0x60+7*4])){
  int vec;
#ifdef DUMP
#endif
  vec = ReadLong68k(&M68000RAM[vector_reg*4]);
  /* Only cause IRQ if the mask is set to allow it */
  if (m68681_imr&8) {
    WriteLong68k(&M68000RAM[0x60+4*6],vec);
    cpu_interrupt(CPU_68K_0,6);
    imr_status |= 0x8;
    if (timer_mode){
      timer_mode = 0;
      int7_active = 0;
    }
  }
#if 0
  else {
    if (!vec) {
      exit(1);
    }
    mycpt=nb_frames=nb_int=0;
  }
#endif
}

//c109e8: 68681 read offset 001c is end of init sequence
WRITE_HANDLER(f3_68681_wb)
{
  offset>>=1;
  offset &= 0x1f;
#ifdef DUMP
#endif
  switch (offset) {
  case 0x04: /* ACR */
    // the ACR has been entierly rewritten by Brian (who ?)
    switch ((data>>4)&7) {
#ifdef RAINE_DEBUG
    case 0:
      print_debug("Counter:  Unimplemented external IP2\n");
      break;
    case 1:
      print_debug("Counter:  Unimplemented TxCA - 1X clock of channel A\n");
      break;
    case 2:
      print_debug("Counter:  Unimplemented TxCB - 1X clock of channel B\n");
      break;
#endif
    case 3:
      print_debug("Counter:  X1/Clk - divided by 16, counter is %04x, so interrupt every %d cycles\n",counter,(M68000_CLOCK/M68681_CLOCK)*counter*16);
      //if (timer_68681) timer_remove(timer_68681);
      //timer_mode=TIMER_SINGLESHOT;
      //timer_68681=timer_set(TIME_IN_CYCLES((M68000_CLOCK/M68681_CLOCK)*counter*16,1), 0, timer_callback);
      f3_cycles_68000 = (M68000_CLOCK/M68681_CLOCK)*counter*16;
      f3_slices = 16000000/(60*f3_cycles_68000);
      timer_mode = 1; // single shot
      int7_active = 1;
      f3_timer_callback();
      // fprintf(stderr,"cycles %d slices %d counter %d\n",f3_cycles_68000,f3_slices,counter);
      if (!f3_slices)
	f3_slices = 2; // 2 is a minimum for games with half slices !!!
      break;
#ifdef RAINE_DEBUG
    case 4:
      print_debug("Timer:  Unimplemented external IP2\n");
      break;
    case 5:
      print_debug("Timer:  Unimplemented external IP2/16\n");
      break;
#endif
    case 6:
      print_debug("Timer:  X1/Clk, counter is %04x, so interrupt every %d cycles\n",counter,(M68000_CLOCK/M68681_CLOCK)*counter);
      //if (timer_68681) timer_remove(timer_68681);
      //timer_mode=TIMER_PULSE;
      //timer_68681=timer_pulse(TIME_IN_CYCLES((M68000_CLOCK/M68681_CLOCK)*counter,1), 0, timer_callback);
      f3_cycles_68000 = (M68000_CLOCK/M68681_CLOCK)*counter;
      f3_slices = 16000000/(60*f3_cycles_68000);
      int7_active = 1;
      // fprintf(stderr,"cycles2 %d slices %d counter %d\n",f3_cycles_68000,f3_slices,counter);
      // wait for the next one...
      break;
#ifdef RAINE_DEBUG
    case 7:
      print_debug("Timer:  Unimplemented X1/Clk - divided by 16\n");
      break;
#endif
    }
    break;

  case 0x05: /* IMR */
    m68681_imr=data&0xff;
    break;

  case 0x06: /* CTUR */
    counter=((data&0xff)<<8)|(counter&0xff);
    break;
  case 0x07: /* CTLR */
    counter=(counter&0xff00)|(data&0xff);
    break;
  case 0x08: break; /* MR1B (Mode register B) */
  case 0x09: break; /* CSRB (Clock select register B) */
  case 0x0a: break; /* CRB (Command register B) */
  case 0x0b: break; /* TBB (Transmit buffer B) */
  case 0x0c: /* IVR (Interrupt vector) */
    vector_reg=data&0xff;
    break;
  default:
    break;
  }
}

READ_HANDLER(es5510_dsp_rb)
{
  int res;
  offset &= 0x1ff;
#ifdef DUMP
#endif
  if (es_tmp) res =  ReadByte(((char*)es5510_dsp_ram)+offset);

  if (offset==0x24) res= 0;

  else if (offset==0x2c) res= 0x27;

  else res= ReadByte(((char*)es5510_dsp_ram)+offset);
#ifdef DUMP
#endif
  return res;
}

READ16_HANDLER(es5510_dsp_r)
{
  offset>>=1;
  offset &= 0x1ff;
  // Normally this code is NEVER called...
#ifdef DUMP
#endif
  if (es_tmp) return es5510_dsp_ram[offset];
  /*
    switch (offset) {
    case 0x00: return (es5510_gpr_latch>>16)&0xff;
    case 0x01: return (es5510_gpr_latch>> 8)&0xff;
    case 0x02: return (es5510_gpr_latch>> 0)&0xff;
    case 0x03: return 0;
    }
  */
  //	offset<<=1;

//if (offset<7 && es5510_dsp_ram[0]!=0xff) return rand()%0xffff;

  if (offset==0x12) return 0;

  //	if (offset>4)
  //	fprintf(stderr,"%06x: DSP read offset %04x (data is %04x)\n",cpu_get_pc(CPU_68K_0),offset,es5510_dsp_ram[offset]);
  if (offset==0x16) return 0x27;

  return es5510_dsp_ram[offset];
}

WRITE_HANDLER(es5510_dsp_wb){
  UINT8 *snd_mem = PCMROM;
  offset &= 0xfff; // I want the whole offset...
#ifdef DUMP
#endif

  //	if (offset>4 && offset!=0x80  && offset!=0xa0  && offset!=0xc0  && offset!=0xe0)
//		fprintf(stderr,"%06x: DSP write offset %04x %04x\n",cpu_get_pc(CPU_68K_0),offset,data);
  WriteByte(((char*)es5510_dsp_ram)+offset,data);

  //fprintf(stderr,"dsp_w %x,%x\n",offset,data);
  switch (offset>>1) {
  case 0x00: es5510_gpr_latch=(es5510_gpr_latch&0x00ffff)|(data<<16);
  case 0x01: es5510_gpr_latch=(es5510_gpr_latch&0xff00ff)|(data<< 8);
  case 0x02: es5510_gpr_latch=(es5510_gpr_latch&0xffff00)|(data<< 0);
  case 0x03:
#ifdef DUMP
#endif
    break;

  case 0x80: /* Read select - GPR + INSTR */
    //		fprintf(stderr,"ES5510:  Read GPR/INSTR %06x (%06x)\n",data,es5510_gpr[data]);

    /* Check if a GPR is selected */
    if (data<0xc0) {
      es_tmp=0;
      //fprintf(stderr,"return gpr_latch %x\n",data);
      if (data < 0xc0)
	es5510_gpr_latch=es5510_gpr[data];
    } else es_tmp=1;
    break;

  case 0xa0: /* Write select - GPR */
    //fprintf(stderr,"snd_mem %x latch %x\n",snd_mem[es5510_gpr_latch>>8],es5510_gpr_latch>>8);
    if (data < 0xc0) es5510_gpr[data]=snd_mem[es5510_gpr_latch>>8];
    break;

  case 0xc0: /* Write select - INSTR */
    //fprintf(stderr,"ES5510:  Write INSTR %06x %06x\n",data,es5510_gpr_latch);
    break;

  case 0xe0: /* Write select - GPR + INSTR */
    //fprintf(stderr,"ES5510:  Write GPR/INSTR %06x %06x\n",data,es5510_gpr_latch);
    break;
  }
}

WRITE16_HANDLER(es5510_dsp_w)
{
  //fprintf(stderr,"%06x: DSP write offset %04x %04x\n",cpu_get_pc(CPU_68K_0),offset,data);
  es5510_dsp_wb(offset,data>>8);
  es5510_dsp_wb(offset+1,data & 0xff);
}

static WRITE16_HANDLER( es5505_bank_w )
{
  /* If game is using a out of range (empty) bank - just set it to the last empty bank */
  offset>>=1;
  offset &= 0x3f;
  data &= 7;
  /* if (data != 0 && data != 1)
    fprintf(stderr,"bank_w %x,%x (%x)\n",offset,data,max_banks_this_game); */
  if (data>max_banks_this_game)
    ES5506_voice_bank_0_w(offset,(max_banks_this_game)<<20);
  else
    ES5506_voice_bank_0_w(offset,data<<20);
}

#if 0
static WRITE16_HANDLER( volume_control ){
}
#endif

READ16_HANDLER( trap_rw ) {
  return ReadWord68k(&M68000RAM[0x40]);
}

READ_HANDLER( trap_rb ) {
  return M68000RAM[offset];
}

WRITE_HANDLER( trap_wb ) {
  M68000RAM[offset]=data;
}

WRITE16_HANDLER( trap_ww ) {
  WriteWord68k(&M68000RAM[0x40],data);
}

#define SIZE_68KRAM 0x48000
#define SAVE_SRAM ASCII_ID('S','R','A','M')

void f3_reset() {
  int7_active = 0;
  f3_slices = 15; // default frame... should be safe !
  RAM[0x69001] &= 0xfd; // clear test bit
  // Then execute 1 frame
  current_game->exec();
  RAM[0x69001] |= 2; // and then put back the bit to normal
  // It avoids the stupid message "press the test switch button" when changing
  // the region area of the rom
}

void setup_sound_68000() {
  set_reset_function(&f3_reset);
  if(!(M68000RAM=AllocateMem(SIZE_68KRAM))) return;

  ByteSwap(M68000ROM,get_region_size(REGION_ROM2));

  ByteSwap(M68000RAM,SIZE_68KRAM);
  memset(M68000RAM,0x00,SIZE_68KRAM);
  memcpy(M68000RAM,M68000ROM,0x8);

  memset(f3_shared_ram,0,0x800);
  AddMemFetch(0xc00000, 0xcfffff, M68000ROM+0x000000-0xc00000);      // 68000 ROM
  AddMemFetch(0x000000, 0x000007, M68000RAM+0x000000-0x000000);      // 68000 ROM
  AddMemFetch(-1, -1, NULL);

  AddReadBW(0xc00000, 0xcfffff, NULL, M68000ROM+0x000000);   // 68000 ROM
  AddRWBW(  0x000000, 0x03FFFF, NULL, M68000RAM+0x000000);   // 68000 RAM

  AddReadWord(0x140000, 0x140fff, f3_68000_share_rw, NULL);
  AddReadByte(0x140000, 0x140fff, f3_68000_share_rb, NULL);

  AddReadByte(0x200000, 0x20001f, ES5505_data_0_rb,NULL);
  AddReadWord(0x200000, 0x20001f, ES5505_data_0_r,NULL);
  AddReadWord(0x260000, 0x2601ff, es5510_dsp_r, NULL);
  AddReadByte(0x260000, 0x2601ff, es5510_dsp_rb, NULL);
  AddReadByte(0x280000, 0x28001f, f3_68681_rb,   NULL);
  AddReadWord(0x280000, 0x28001f, f3_68681_rdebug,   NULL);
  AddRWBW(0xff8000, 0xffffff, NULL, M68000RAM+0x40000);

  // Write...

  AddWriteWord(0x140000, 0x140fff, f3_68000_share_ww, NULL);
  AddWriteByte(0x140000, 0x140fff, f3_68000_share_wb, NULL);
  AddWriteWord(0x200000, 0x20001f, ES5505_data_0_ww,NULL);
  AddWriteByte(0x200000, 0x20001f, ES5505_data_0_wb,NULL);
  AddWriteWord(0x260000, 0x2601ff, es5510_dsp_w, NULL);
  AddWriteByte(0x260000, 0x2601ff, es5510_dsp_wb, NULL);
  AddWriteByte(0x280000, 0x28001f, f3_68681_wb,   NULL);
  AddWriteWord(0x280000, 0x28001f, f3_68681_wb,   NULL);
  AddWriteByte(0x300000, 0x30003f, es5505_bank_w,  NULL); // BANK1 ???!

  //AddWriteBW(0x340000, 0x34003f, volume_control, NULL);
  AddWriteBW(0xc00000, 0xcfffff, DefBadWriteByte, NULL); // ROM

  AddRWBW(-1, -1, NULL, NULL);
  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);      // <Bad Reads>
  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);      // <Bad Reads>
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);    // <Bad Writes>
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);    // <Bad Writes>

  AddInitMemory();   // Set Starscream mem pointers...
  AddSaveData(SAVE_SRAM,M68000RAM,SIZE_68KRAM);
}


void AddF3MemoryMap(UINT32 romsize)
{
   UINT32 ta;

   for(ta=0;ta<0x100;ta++){
      R24[ta]=RAM+0x70000;	// SCRATCH RAM
   }

   R24[0x40]=RAM+0x00000;	// MAIN RAM
   R24[0x41]=RAM+0x10000;	// MAIN RAM

   R24[0x44]=RAM+0x60000;	// COLOR RAM	($440000-$447FFF)

   R24[0x4A]=RAM+0x69000;	// INPUT	($4A0000-$4A00FF)

   R24[0x60]=RAM+0x20000;	// OBJECT RAM
   R24[0x61]=RAM+0x30000;	// SCREEN RAM
   R24[0x62]=RAM+0x40000;	// LINE RAM
   R24[0x63]=RAM+0x50000;	// PIXEL RAM

   R24[0x66]=RAM+0x6A000;	// SCROLL RAM	($660000-$66001F)

   R24[0xC0]=(UINT8*)f3_shared_ram; //RAM+0x68000;	// SOUND RAM	($C00000-$C007FF)

   for(ta=0;ta<0x100;ta++){
      W24[ta]=R24[ta];		// COPY READ>WRITE
   }

   for(ta=0;ta<(romsize>>16);ta++){
      R24[ta]=ROM+(ta<<16);	// 68020 ROM
   }

   W24[0x4A]=RAM+0x69100;	// OUTPUT	($4A0000-$4A00FF)

   EEPROM=RAM+0x6B000;		// EEPROM
}

static const INT16 planes[] = { 16, 32, 0, 64 };

void draw_f3_opaque_layer(int sx, int sy, UINT8 *RAM_BG,UINT8 *GFX_BG,int index) {
    SCROLL_REGS;
    int w;
    if (ReadWord68k(RAM+0x6A000+0xf*2) == 0x80)
	w = 1024;
    else
	w = 512;
    int bit_select = 1<<index;
    UINT8 *lbase = RAM+0x4a000+0x200*index;
    INT16 xoff[256];
    INT16 l = 0;
    char has_lscroll[256/16];
    memset(has_lscroll,0,256/16);
    int warned = 0;
    for (y=0; y<256; y++) {
	if (ReadWord68k(RAM+0x40000+(0x600+y)*2) & bit_select) {
	    l = ReadWord68k(lbase + y*2)>>15;
	}
	xoff[y] = l;
	if (l) {
	    has_lscroll[y/16] = 1;
#ifdef RAINE_DEBUG
	    if (!warned) {
		warned = 1;
		print_ingame(1,"lscroll bg%d",index);
	    }
#endif
	}
    }
    MAKE_SCROLL_n_16(w,512,4,sx,sy);

    START_SCROLL_16(current_game->video->border_size,current_game->video->border_size,current_game->video->screen_x,current_game->video->screen_y);

    INT16 color = ReadWord68k(&RAM_BG[zz]);
    INT16 extra_planes = (color & 0xc00) >> 10; // 0 = 4bpp, 1 = 5bpp, 3 = 6bpp !
    UINT8 *map;
    MAP_PALETTE_MAPPED_NEW(
	    color&0x1FF & (~extra_planes),
	    planes[extra_planes],        map
	    );
    if (has_lscroll[(y-64+24)/16])
	ldraw16x16_Mapped_flip_Rot(&GFX_BG[(ReadWord68k(&RAM_BG[zz+2]))<<8],x,y,map,&xoff[y-64+24],(color & 0xc000)>>14);
    else
	Draw16x16_Mapped_flip_Rot(&GFX_BG[(ReadWord68k(&RAM_BG[zz+2]))<<8],x,y,map,(color & 0xc000)>>14);

    END_SCROLL_n_16(w,512,4);
}

void draw_f3_layer(int sx,int sy, UINT8 *RAM_BG,UINT8 *GFX_BG,UINT8 *GFX_BG_SOLID) {
    SCROLL_REGS;
    int w;
    if (ReadWord68k(RAM+0x6A000+0xf*2) == 0x80)
	w = 1024;
    else
	w = 512;
    MAKE_SCROLL_n_16(w,512,4,sx,sy);

    START_SCROLL_16(current_game->video->border_size,current_game->video->border_size,current_game->video->screen_x,current_game->video->screen_y);
    INT16 color = ReadWord68k(&RAM_BG[zz]);
    INT16 extra_planes = (color & 0xc00) >> 10; // 0 = 4bpp, 1 = 5bpp, 3 = 6bpp !
    UINT8 *map;

    UINT16 ta=ReadWord68k(&RAM_BG[zz+2]);
    if(GFX_BG_SOLID[ta]){

	MAP_PALETTE_MAPPED_NEW(
		color&0x1FF & (~extra_planes),
		planes[extra_planes],        map
		);

	if(GFX_BG_SOLID[ta]==2){
	    Draw16x16_Mapped_flip_Rot(&GFX_BG[ta<<8],x,y,map,(color & 0xc000)>>14);
	}
	else if (GFX_BG_SOLID[ta]){
	    Draw16x16_Trans_Mapped_flip_Rot(&GFX_BG[ta<<8],x,y,map,(color & 0xc000)>>14);
	}
    }

    END_SCROLL_n_16(w,512,4);
}

void draw_f3_pixel(int dx,int dy,UINT8 *src) {
    /* One of the craziest layers I ever saw !
     * So the idea is to draw a pixel bitmap, but each 8x8 area on its surface has an attribute in videoram
     * to make things even worse : the attributes area is not oriented the same way as the bitmap itself !
     * Mostly used in bubblem and bubsymph clones (levels walls + some backgrounds for the prototype), and twinqix
     */
    int x,x16,zzzz,zzz,zz;
    UINT8 *map;
   zzz=1-dx; // x scrolling used in bublbob2 !
   zzzz=((zzz&0x1F8)>>3)<<10;			// X Offset (16-1024)
   int tile_index = (zzz & 0x1f8)>>3;
   x16=7-(zzz&7);				// X Offset (0-15)
   zz=1-dy;
   zz&=0xFf;					// Y Offset (0-255)
   // The fix to be able to do the vertical scrolling with constant colors :
   // change zzzz on 8 pixels boundaries, and then change y loop to draw
   // the offscreen part of the sprite so that we always draw the same 8x8 sprite
   zzzz+=(zz&0xf8)<<2;					// Y Offset (0-255)
   tile_index += (((1-dy)&0x1ff)>>3)<<6;
   if (tile_index > 0x800 || tile_index < 0)
       tile_index = 0x800+(tile_index & 0x7FF);

   zzzz&=0xFFFF;
   int orig = tile_index;

   for(x=56+x16;x<(320+64);x+=8){
       if (orig < 0x40 && tile_index >= 0x40 && tile_index < 0x80)
	   /* This is really a super ugly hack :
	    * in bublbob2, beginning of stage 3 when coming from the middle gate
	    * when the level scrolls towards the left, the right side of the level has wrong colors
	    * it seems to happen when tile_index becomes >= 0x40
	    * There is probably an offset to fix this, but I doubt &= 0x3f is the right solution
	    * since it takes the index back... ! But here, it works, so it will do the trick until
	    * I find somewhere where it doesn't work !!! */
	   tile_index = (tile_index & 0x3f);
       int tile0 = tile_index;
       int z0 = zzzz;
       for (int y=0-(zz&7); y<224; y+=8) {
	   INT16 vram_tile = ReadWord68k(&RAM[0x3c000+tile_index*2]);

	   MAP_PALETTE_MAPPED_NEW(
		   (vram_tile>>9)&0x3f,
		   16,     map
		   );
	   // if (vram_tile&0x8000) printf("flipy\n"); // flags|=TILE_FLIPY;

	   if (vram_tile&0x0100)
	       // The only game I know which uses this is twinqix
	       Draw8x8_Trans_Packed_Mapped_Rot(&src[zzzz],x,64+1+y,map);
	   else
	       Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&src[zzzz],x,64+1+y,map);
	   tile_index+=0x40;
	   tile_index &= 0xFff;
	   zzzz+=8*4;
	   if ((tile_index >= 0x800 && tile_index < 0x840) || (tile_index >= 0 && tile_index < 0x40)) {
	       /* There is again something weird with this layer, when reaching a limit, a sign limit apparently, instead of cycling smoothly
		* it needs to be corrected of 1 char on the left. Tested here on tile_index. The fix is not perfect, while a level is scrolling
		* in bubblem for example you might see the walls moving left and right very fast before stabilizing at the end of the scrolling.
		* No idea to make it better for now... */
	       zzzz -= 0x400;
	   }
       }
       zzzz=(z0+0x400)&0xFFFF;
       tile_index = tile0 + 1;
   }
}

static UINT32 lastled;
static UINT32 ioc_type;

static UINT32 p2_trackball_x;
static UINT32 p2_trackball_y;

void init_f3_system_ioc(UINT32 type)
{
   lastled  = 0xFFFFFFFF;
   ioc_type = type;

   add_eeprom(EEPROM, 0x80, EPR_INVALIDATE_ON_ROM_CHANGE);
   load_eeprom();

   if(ioc_type & F3_IOC_TRACKBALL){
      GameMouse = 1;
      p1_trackball_x = 0;
      p1_trackball_y = 0;
      p2_trackball_x = 0;
      p2_trackball_y = 0;
   }

   f3_bg0_id = add_layer_info(gettext("BG0"));
   f3_bg1_id = add_layer_info(gettext("BG1"));
   f3_bg2_id = add_layer_info(gettext("BG2"));
   f3_bg3_id = add_layer_info(gettext("BG3"));

   f3_bg5_id = add_layer_info(gettext("FG0"));
   f3_bg6_id = add_layer_info(gettext("Pixel"));
}

//static int scrsav[16];

void IntF3System(void)
{
/*
   int ta,tc,td;
   char tb[256];
*/
  int mx,my;

   //print_ingame(600,gettext("%04x"),ReadWord68k(&RAM[0x4623E]));

   // update ioc leds

   if(RAM[0x69104]!=lastled){
      lastled = RAM[0x69104];
      RAM[0x69004] = lastled;			// Write to input (where it should be...)
      switch_led(0,(lastled>>2)&1);		// Coin A [Coin Inserted]
      switch_led(1,(lastled>>3)&1);		// Coin B [Coin Inserted]
      switch_led(2,(lastled>>0)&1);		// Coin A [Ready for coins]
      //switch_led(3,(lastled>>1)&1);		// Coin B [Ready for coins]
   }

   // update trackballs

   if(ioc_type & F3_IOC_TRACKBALL){

   // map mouse as trackball

   GetMouseMickeys(&mx,&my);

   p1_trackball_x += mx;
   p1_trackball_y += my;

   // map joy/key movement as trackball

   if(!(RAM[0x069007]&0x04)) p1_trackball_x -= 12;
   if(!(RAM[0x069007]&0x08)) p1_trackball_x += 12;
   if(!(RAM[0x069007]&0x01)) p1_trackball_y -= 12;
   if(!(RAM[0x069007]&0x02)) p1_trackball_y += 12;

   if(!(RAM[0x069007]&0x40)) p2_trackball_x -= 12;
   if(!(RAM[0x069007]&0x80)) p2_trackball_x += 12;
   if(!(RAM[0x069007]&0x10)) p2_trackball_y -= 12;
   if(!(RAM[0x069007]&0x20)) p2_trackball_y += 12;

   // write new trackball positions

   WriteWord(&RAM[0x06900A],p1_trackball_x);
   WriteWord(&RAM[0x06900C],p1_trackball_y);	// could be 0x08
   WriteWord(&RAM[0x06900E],p2_trackball_x);
   WriteWord(&RAM[0x069010],p2_trackball_y);	// could be 0x0C

   // map mouse buttons too

   if(*MouseB&1) RAM[0x069003] &= ~0x01;
   if(*MouseB&2) RAM[0x069003] &= ~0x02;

   }
}

// EEP-ROM Access Hack Type 1
// --------------------------
//
// EEPROM is 64 words (ie. 128 bytes)

void F3SysEEPROMAccessMode1(UINT8 data)
{
   // READ: d0=EEPROM[d0]

   if(data==0){
      m68k_dreg(regs,0)=ReadWord(&EEPROM[(m68k_dreg(regs,0)&0x3F)<<1]);
      return;
   }

   // WRITE: EEPROM[d0]=d1

   if(data==1){
      WriteWord(&EEPROM[(m68k_dreg(regs,0)&0x3F)<<1],m68k_dreg(regs,1)&0xFFFF);
      return;
   }

   // SPEED HACK

   if(data==2){
      Stop68020();
      return;
   }
}

// EEP-ROM Access Hack Type 1B
// --------------------------
//
// EEPROM is 64 words (ie. 128 bytes)

void F3SysEEPROMAccessMode1B(UINT8 data)
{
   // READ: d1=EEPROM[d0]

   if(data==0){
      m68k_dreg(regs,1)=ReadWord(&EEPROM[(m68k_dreg(regs,0)&0x3F)<<1]);
      return;
   }

   // WRITE: EEPROM[d0]=d1

   if(data==1){
      WriteWord(&EEPROM[(m68k_dreg(regs,0)&0x3F)<<1],m68k_dreg(regs,1)&0xFFFF);
      return;
   }

   // SPEED HACK

   if(data==2){
      Stop68020();
      return;
   }
}

// EEP-ROM Access Hack Type 2
// --------------------------
// d0=Read/Write data
// d1=Address Bitcount
// Read expects a word in d0

void F3SysEEPROMAccessMode2(UINT8 data)
{
   UINT32 ta,tb,tc;

   // SPEED HACK

   if(data==2){
      Stop68020();
      return;
   }

   // READ/WRITE

   ta=m68k_dreg(regs,0);
   tb=m68k_dreg(regs,1);

   if(((ta&0x80000000)!=0)&&(tb==9)){
      tc=ReadWord(&EEPROM[(ta&0x3F)<<1]);
      m68k_dreg(regs,0)=tc;
      return;
   }
   if(((ta&0x40000000)!=0)&&(tb==25)){
      tc=ta&0xFFFF;
      WriteWord(&EEPROM[(ta&0x3F0000)>>15],tc);
      return;
   }
}

/*

Generic Frame

*/

void ExecuteF3SystemFrame(void)
{
  int ta;
  IntF3System();
  cpu_interrupt(CPU_M68020_0, 3);	// Interrupt#3 [Video Start]
  cycles = 1;
  for (ta=0; ta<f3_slices; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices)); //1600000/f3_slices);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0,CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active) {
	f3_timer_callback();
      }
    }
  }
   switch_cpu(CPU_M68020_0);
  if (ReadWord68k(&ROM[REG_PC]) == 0x60fe)
    reset_game_hardware();
  else {
    cpu_interrupt(CPU_M68020_0, 5);	// Interrupt#5 [Occasionally used, for timing I think]
    cpu_interrupt(CPU_M68020_0, 2);	// Interrupt#2 [Video End]
    cpu_execute_cycles(CPU_M68020_0, 20000);
  }
}

void ExecuteF3SystemFrameB(void)
{
  // The same, but without the execute_cycles at the end
  int ta;
  IntF3System();
  cycles = 1;
  for (ta=0; ta<f3_slices; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices)); //1600000/f3_slices)
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0,CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active) {
	f3_timer_callback();
      }
    }
  }
   switch_cpu(CPU_M68020_0);
  if (ReadWord68k(&ROM[REG_PC]) == 0x60fe)
  {
    reset_game_hardware();
  }
  else {
      cpu_interrupt(CPU_M68020_0, 3);	// Interrupt#3 [Video Start]
      cpu_execute_cycles(CPU_M68020_0, 100); //1600000/f3_slices)
      cpu_interrupt(CPU_M68020_0, 5);	// Interrupt#5 [Occasionally used, for timing I think]
      cpu_execute_cycles(CPU_M68020_0, 100); //1600000/f3_slices)
      cpu_interrupt(CPU_M68020_0, 2);	// Interrupt#2 [Video End]
      cpu_execute_cycles(CPU_M68020_0, 100); //1600000/f3_slices)
  }
}

void ExecuteF3SystemFrame_NoInt5(void)
{
  int ta;
  IntF3System();

   cpu_interrupt(CPU_M68020_0, 3);	// Interrupt#3 [Video Start]
   cycles = 1;
   for (ta=0; ta<f3_slices; ta++) {
     if (cycles) {// cycles = 0 if we reached the speed hack
       cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices));
     }

     if (RaineSoundCard) {
       cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
       if (int7_active) {
	 f3_timer_callback();
       }
     }
   }
   switch_cpu(CPU_M68020_0);
  if (ReadWord68k(&ROM[REG_PC]) == 0x60fe)
    reset_game_hardware();
  else {
    cpu_interrupt(CPU_M68020_0, 2);	// Interrupt#2 [Video End]
    cpu_execute_cycles(CPU_M68020_0, 200000);
  }
}

void ExecuteF3SystemFrame_NoInt5B(void)
{
  // The same without the execute_cycles at the end
  int ta;
  IntF3System();

   cpu_interrupt(CPU_M68020_0, 3);	// Interrupt#3 [Video Start]
   cycles = 1;
   for (ta=0; ta<f3_slices; ta++) {
     if (cycles) {// cycles = 0 if we reached the speed hack
       cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices));
     }

     if (RaineSoundCard) {
       cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
       if (int7_active) {
	 f3_timer_callback();
       }
     }
   }
   switch_cpu(CPU_M68020_0);
  if (ReadWord68k(&ROM[REG_PC]) == 0x60fe)
     reset_game_hardware();
   else {
     cpu_interrupt(CPU_M68020_0, 2);	// Interrupt#2 [Video End]
   }
}

void ExecuteF3SystemFrame_int2(void)
{
  int ta;
  IntF3System();

   cpu_interrupt(CPU_M68020_0, 2);	// Interrupt#3 [Video Start]
   cycles = 1;
   for (ta=0; ta<f3_slices; ta++) {
     if (cycles) {// cycles = 0 if we reached the speed hack
       cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices));
     }

     if (RaineSoundCard) {
       cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
       if (int7_active) {
	 f3_timer_callback();
       }
     }
   }
   switch_cpu(CPU_M68020_0);
  if (ReadWord68k(&ROM[REG_PC]) == 0x60fe)
     reset_game_hardware();
}
