/******************************************************************************/
/*                                                                            */
/*                           CPU CALLING ROUTINES                             */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"
#include "cpumain.h"
#include "gameinc.h"
#ifdef HAVE_6502
#include "m6502.h"
#include "m6502hlp.h"
#endif
#include "games/default.h"
#include "sdl/gui.h" // goto_debuger

UINT32 current_cpu_num[0x10];

/*

switch to the requested cpu (context manager)

*/

void switch_cpu(UINT32 cpu_id)
{
   UINT32 new_type;
   UINT32 new_num;
   UINT32 old_id;

   new_type = cpu_id >> 4;
   new_num  = cpu_id & 0x0F;

   if( current_cpu_num[new_type] != new_num ){

      // first save the current cpu context

      old_id = (current_cpu_num[new_type]) | (new_type<<4);

      switch(old_id){
#ifdef HAVE_68000
         case CPU_68K_0:
            s68000GetContext(&M68000_context[0]);
         break;
         case CPU_68K_1:
            s68000GetContext(&M68000_context[1]);
         break;
#endif
#if HAVE_Z80
         case CPU_Z80_0:
            mz80GetContext(&Z80_context[0]);
         break;
         case CPU_Z80_1:
            mz80GetContext(&Z80_context[1]);
         break;
         case CPU_Z80_2:
            mz80GetContext(&Z80_context[2]);
         break;
         case CPU_Z80_3:
            mz80GetContext(&Z80_context[3]);
         break;
#endif
#ifndef NO020
         case CPU_M68020_0:
         break;
#endif
#ifdef HAVE_6502
         case CPU_M6502_0:
            m6502GetContext(&M6502_context[0]);
         break;
         case CPU_M6502_1:
            m6502GetContext(&M6502_context[1]);
         break;
         case CPU_M6502_2:
            m6502GetContext(&M6502_context[2]);
         break;
#endif
      }

      // now load the new cpu context

      switch(cpu_id){
#if HAVE_68000
         case CPU_68K_0:
            s68000SetContext(&M68000_context[0]);
         break;
         case CPU_68K_1:
            s68000SetContext(&M68000_context[1]);
         break;
#endif
#if HAVE_Z80
         case CPU_Z80_0:
            mz80SetContext(&Z80_context[0]);
         break;
         case CPU_Z80_1:
            mz80SetContext(&Z80_context[1]);
         break;
         case CPU_Z80_2:
            mz80SetContext(&Z80_context[2]);
         break;
         case CPU_Z80_3:
            mz80SetContext(&Z80_context[3]);
         break;
#endif
#ifndef NO020
         case CPU_M68020_0:
         break;
#endif

#ifdef HAVE_6502
         case CPU_M6502_0:
            m6502SetContext(&M6502_context[0]);
         break;
         case CPU_M6502_1:
            m6502SetContext(&M6502_context[1]);
         break;
         case CPU_M6502_2:
            m6502SetContext(&M6502_context[2]);
         break;
#endif
      }

      // update id

      current_cpu_num[new_type] = new_num;
   }
}

/*

initialize

*/

void start_cpu_main(void)
{
   UINT32 ta;

   for(ta=0; ta<0x10; ta++)
      current_cpu_num[ta] = 0x0F;
}

/*

uninitialize - need to do this before outside access to cpu contexts

*/

void stop_cpu_main(void)
{
  /* What's this code for ??? */
   UINT32 ta;

   for(ta=0; ta<0x10; ta++)
      switch_cpu((ta<<4) | 0x0F);
}

/*

request an interrupt on a cpu

*/

#ifdef SDL
extern int goto_debuger;
#endif

void cpu_interrupt(UINT32 cpu_id, UINT32 vector)
{
#ifdef SDL
    if (goto_debuger) return;
#endif

   switch_cpu(cpu_id);

   switch(cpu_id){
#if HAVE_68000
      case CPU_68K_0:
      case CPU_68K_1:
         s68000interrupt(vector, -1);
         s68000flushInterrupts();
      break;
#endif
#if HAVE_Z80
      case CPU_Z80_0:
      case CPU_Z80_1:
      case CPU_Z80_2:
      case CPU_Z80_3:
         mz80int(vector);
      break;
#endif
#ifndef NO020
      case CPU_M68020_0:
         Interrupt68020(vector);
      break;
#endif
#ifdef HAVE_6502
      case CPU_M6502_0:
      case CPU_M6502_1:
      case CPU_M6502_2:
	m6502int(1);
	break;
#endif
   }
}

/*

request an nmi on a cpu

*/

void cpu_int_nmi(UINT32 cpu_id)
{
   switch_cpu(cpu_id);

   switch(cpu_id){
      case CPU_68K_0:
      case CPU_68K_1:
         // not available on this cpu
      break;
      case CPU_Z80_0:
      case CPU_Z80_1:
      case CPU_Z80_2:
      case CPU_Z80_3:
         mz80nmi();
      break;
      case CPU_M68020_0:
         // not available on this cpu
      break;
#ifdef HAVE_6502
      case CPU_M6502_0:
      case CPU_M6502_1:
      case CPU_M6502_2:
	m6502nmi();
	break;
#endif
   }
}

/*

execute a cpu for some cycles

*/

void cpu_execute_cycles(UINT32 cpu_id, UINT32 cycles)
{
   switch_cpu(cpu_id);

   switch(cpu_id){
#if HAVE_68000
      case CPU_68K_0:
      case CPU_68K_1:
         s68000exec(cycles);
	 print_debug("PC:%06x SR:%04x SP:%04x\n",s68000context.pc,s68000context.sr,s68000context.areg[7]);
#ifdef RAINE_DEBUG
	 if (s68000context.pc & 0xff000000) {
	   printf("pc out of bounds for 68k%d\n",cpu_id & 15);
	 }
#endif
      break;
#endif
#if HAVE_Z80
      case CPU_Z80_0:
      case CPU_Z80_1:
      case CPU_Z80_2:
      case CPU_Z80_3:
         mz80exec(cycles);
      break;
#endif
#ifndef NO020
      case CPU_M68020_0:
         Execute68020(cycles);
	 print_debug("PC0:%06x SR:%04x\n",regs.pc,regs.sr);
      break;
#endif
#ifdef HAVE_6502
      case CPU_M6502_0:
      case CPU_M6502_1:
      case CPU_M6502_2:
	m6502exec(cycles);
	break;
#endif
   }
}

/*

reset a cpu

*/

void cpu_reset(UINT32 cpu_id)
{
   switch_cpu(cpu_id);

   switch(cpu_id){
#if HAVE_68000
      case CPU_68K_0:
      case CPU_68K_1:
         s68000reset();
      break;
#endif
#if HAVE_Z80
      case CPU_Z80_0:
      case CPU_Z80_1:
      case CPU_Z80_2:
      case CPU_Z80_3:
         mz80reset();
      break;
#endif
#ifndef NO020
      case CPU_M68020_0:
         Reset68020();
      break;
#endif
#ifdef HAVE_6502
      case CPU_M6502_0:
      case CPU_M6502_1:
      case CPU_M6502_2:
	m6502reset();
	break;
#endif
   }
}

/*

get the pc of a cpu

*/

UINT32 cpu_get_pc(UINT32 cpu_id)
{
   UINT32 ret;

   switch_cpu(cpu_id);

   switch(cpu_id){
#if HAVE_68000
   case CPU_68K_0:
   case CPU_68K_1:
     ret = s68000context.pc;
     break;
#endif
#if HAVE_Z80
   case CPU_Z80_0:
   case CPU_Z80_1:
   case CPU_Z80_2:
   case CPU_Z80_3:
     ret = mz80GetPC();
     break;
#endif
#ifndef NO020
   case CPU_M68020_0:
     ret = regs.pc;
     break;
#endif
#ifdef HAVE_6502
   case CPU_M6502_0:
   case CPU_M6502_1:
   case CPU_M6502_2:
     ret = m6502pc;
     break;
#endif
   default:
     ret = 0;
     break;
   }

   return ret;
}

void cpu_get_ram(UINT32 cpu, UINT32 *range, UINT32 *count) {
    switch(cpu>>4) {
#if HAVE_68000
    case 1: s68000_get_ram(cpu & 0xf,range,count); break;
#endif
#if HAVE_Z80
    case 2: z80_get_ram(cpu & 0xf, range, count); break;
#endif
#ifndef NO020
    case 3:
	    {
		int n;
		*count = 0;
		for(n=0; n<0x100; n++) {
		    /* Check that this R24 is not already used.
		     * Otherwise it would be a very unefficient waste of ram ! */
		    int found = 0;
		    int m;
		    for (m=0; m<n; m++) {
			if (R24[n] == R24[m]) {
			    found = 1;
			    break;
			}
		    }
		    if (!found) {
			range[(*count)++] = n<<16;
			range[(*count)++] = ((n+1)<<16)-1;
		    }
		}
	    }
	    break;
#endif
    }
}

UINT8 *get_code_range(UINT32 cpu, UINT32 adr, UINT32 *start, UINT32 *end) {
    switch(cpu >> 4) {
#if HAVE_68000
    case 1:
	return s68k_get_code_range(cpu & 0xf, adr, start, end);
	break;
#endif
#if HAVE_Z80
    case 2:
	// For the z80 all the rombase is executable, so...
	*start = 0;
	*end = 0xffff;
	UINT8 *base = mz80GetBase(cpu & 0xf);
	int n;
	for (n=REGION_CPU1; n<=REGION_CPU4; n++)
	    if (base == load_region[n]) {
		*end = get_region_size(n)-1;
		break;
	    }
	return base;
#endif
#ifndef NO020
    case 3:
	// For the 020, the whole R24 array is executable, so...
	*start = (adr>>16)<<16;
	*end = *start + 0xffff;
	return R24[adr>>16]-*start;
#endif
    }
    return NULL;
}

UINT8 *get_userdata(UINT32 cpu, UINT32 adr) {
    switch(cpu >> 4) {
#if HAVE_68000
    case 1: return s68k_get_userdata(cpu & 0xf,adr);
#endif
#if HAVE_Z80
    case 2: return z80_get_userdata(cpu & 0xf,adr);
#endif
#ifndef NO020
    case 3: return R24[adr >> 16]-adr;
#endif
    }
    return NULL;
}

int bcd(int value) {
  return ((value/10)<<4) | (value % 10);
}

