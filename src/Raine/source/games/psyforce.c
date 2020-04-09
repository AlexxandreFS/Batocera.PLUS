/******************************************************************************/
/*                                                                            */
/*                  PSYCHIC FORCE (C) 1991 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_psyforce[] =
{
   {       "e22-01", 0x00200000, 0x808b8340, REGION_SOUND1, 0, 0, },
   {       "e22-06", 0x00020000, 0x739af589, REGION_CPU2, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_psyforce[] =
{
   INP0( P1_UP, 0x000000, 0x01 ),
   INP0( P1_DOWN, 0x000000, 0x02 ),
   INP0( P1_LEFT, 0x000000, 0x04 ),
   INP0( P1_RIGHT, 0x000000, 0x08 ),
   INP0( P1_B1, 0x000000, 0x10 ),

   END_INPUT
};




static void load_psyforce(void)
{
   RAMSize=0x20000;
   RAM = load_region[REGION_CPU2];

   AddTaitoYM2610(0x0198, 0x0168, 0x20000);
}

static void clear_psychic_force(void)
{
   RemoveTaitoYM2610();
}

static UINT32 command;

static void execute_psyforce(void)
{
   static UINT32 flip_0;
   static UINT32 flip_1;
   static UINT32 flip_2;
   static UINT32 flip_3;
   static UINT32 flip_4;

   if(!(input_buffer[0] & 1)){

      if(!flip_0)

         command = (command + 0x10) & 0xFF;

      flip_0 = 1;
   }
   else

      flip_0 = 0;


   if(!(input_buffer[0] & 2)){

      if(!flip_1)

         command = (command - 0x10) & 0xFF;

      flip_1 = 1;
   }
   else

      flip_1 = 0;


   if(!(input_buffer[0] & 4)){

      if(!flip_2)

         command = (command - 0x01) & 0xFF;

      flip_2 = 1;
   }
   else

      flip_2 = 0;


   if(!(input_buffer[0] & 8)){

      if(!flip_3)

         command = (command + 0x01) & 0xFF;

      flip_3 = 1;
   }
   else

      flip_3 = 0;


   if(!(input_buffer[0] & 16)){

      if(!flip_4){

         tc0140syt_write_main_68k(0,0);
         tc0140syt_write_main_68k(2,(command >> 0) & 0x0F);
         tc0140syt_write_main_68k(2,(command >> 4) & 0x0F);

      }

      flip_4 = 1;
   }
   else

      flip_4 = 0;

   Taito2610_Frame();			// Z80 and YM2610
}

static void draw_psychic_force(void)
{
   clear_game_screen(0);

   clear_ingame_message_list();
   print_ingame(1,"PSYCHIC FORCE AUDIO BOARD");
   print_ingame(1,"-------------------------");
   print_ingame(1," ");
   print_ingame(1,"Sound Byte:%02x",command);
   print_ingame(1," ");
   print_ingame(1,"Joystick: Select Byte");
   print_ingame(1,"Button: Send Command");
}
static struct VIDEO_INFO video_psyforce =
{
   draw_psychic_force,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_psyforce[] =
{
   { "psychic_force", },
   { "psyforce", },
   { NULL, },
};
GAME( psyforce, "Psychic Force (audio board)", TAITO, 1990, GAME_MISC,
	.input = input_psyforce,
	.clear = clear_psychic_force,
	.video = &video_psyforce,
	.exec = execute_psyforce,
	.board = "E22",
	.sound = taito_ym2610_sound,
);

