/**************************************************************/
/* M68705 static-recompiler, support functions.               */
/**************************************************************/

#include "raine.h"         // General defines and stuff
#include "savegame.h"      // Savegame support
#include "m68705.h"        // M68705 stuff

M68705 m68705;
void *m68705_jump_table[0x800];

#define MAX_MCU         1

typedef struct SAVE_BUFFER
{
   UINT32 id;
   UINT32 r_x;
   UINT32 r_a;
   UINT32 r_flag_n;
   UINT32 r_flag_h;
   UINT32 r_flag_z;
   UINT32 r_flag_c;
   UINT32 r_flag_i;
   UINT32 r_sp;
   UINT32 r_pc;
} SAVE_BUFFER;

static struct SAVE_BUFFER save_buffer[MAX_MCU];

static void do_save_packing(int cpu)
{
   save_buffer[cpu].id = ASCII_ID('V','0','.','2');

   save_buffer[cpu].r_x         = m68705.x;
   save_buffer[cpu].r_a         = m68705.a;
   save_buffer[cpu].r_flag_n    = m68705.flag_n;
   save_buffer[cpu].r_flag_h    = m68705.flag_h;
   save_buffer[cpu].r_flag_z    = m68705.flag_z;
   save_buffer[cpu].r_flag_c    = m68705.flag_c;
   save_buffer[cpu].r_flag_i    = m68705.flag_i;
   save_buffer[cpu].r_sp        = m68705.sp;
   save_buffer[cpu].r_pc        = m68705.pc;
}

void MCU_A_save_update(void)
{
   do_save_packing(0);
}

static void do_load_unpacking(int cpu)
{
   if( save_buffer[cpu].id == ASCII_ID('V','0','.','2') ){

   m68705.x         = save_buffer[cpu].r_x;
   m68705.a         = save_buffer[cpu].r_a;
   m68705.flag_n    = save_buffer[cpu].r_flag_n;
   m68705.flag_h    = save_buffer[cpu].r_flag_h;
   m68705.flag_z    = save_buffer[cpu].r_flag_z;
   m68705.flag_c    = save_buffer[cpu].r_flag_c;
   m68705.flag_i    = save_buffer[cpu].r_flag_i;
   m68705.sp        = save_buffer[cpu].r_sp;
   m68705.pc        = save_buffer[cpu].r_pc;

   }
}

void MCU_A_load_update(void)
{
   do_load_unpacking(0);
}

// M68705_Unpack();
// Unpack the jump table.

void M68705_Unpack(const M68705_JumpTable *table, void *invalid)
{
   int pc;
   for (pc=0;pc<0x800;pc++)
   {
      m68705_jump_table[pc] = invalid;
   }

   while(table->code)
   {
      m68705_jump_table[table->addr] = table->code;
      table++;
   }

   AddSaveCallback_Internal(MCU_A_save_update);
   AddLoadCallback_Internal(MCU_A_load_update);
   AddSaveData(SAVE_MCU_0, (UINT8 *) &save_buffer[0], sizeof(SAVE_BUFFER));
}

