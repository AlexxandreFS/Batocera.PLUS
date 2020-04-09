/******************************************************************************/
/*                                                                            */
/*                           KONAMI GX M68020 SYSTEM                          */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"

static struct ROM_INFO rom_salmndr2[] =
{
   { "300-a01.34k", 0x00008000, 0xaeeb5148, 0, 0, 0, },
   { "521-a02.31b", 0x00080000, 0xf6c3a95b, 0, 0, 0, },
   { "521-a03.30b", 0x00080000, 0xc3be5e0a, 0, 0, 0, },
   {  "521-a04.9c", 0x00010000, 0xefddca7a, 0, 0, 0, },
   {  "521-a05.7c", 0x00010000, 0x51a3af2c, 0, 0, 0, },
   { "521-a06.30g", 0x00200000, 0xcba5db2c, 0, 0, 0, },
   { "521-a07.28g", 0x00200000, 0x50ef9b7a, 0, 0, 0, },
   { "521-a08.25g", 0x00200000, 0xf24f76bd, 0, 0, 0, },
   { "521-a09.17h", 0x00200000, 0xfb9e2f5e, 0, 0, 0, },
   { "521-a11.15h", 0x00100000, 0x25e0a6e5, 0, 0, 0, },
   {  "521-a12.9g", 0x00200000, 0x66614d3b, 0, 0, 0, },
   { "521-a13.13c", 0x00200000, 0x3ed7441b, 0, 0, 0, },
   {  "521-a13.7g", 0x00100000, 0xc3322475, 0, 0, 0, },
   {          NULL,          0,          0, 0, 0, 0, },
};

static void load_salmndr2(void)
{
   int ta;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x300000))) return;

   // Setup 68020 Memory Map
   // ----------------------

   for(ta=0;ta<0x100;ta++){
      R24[ta]=RAM+0x70000;	// SCRATCH RAM
   }

   R24[0xC0]=RAM+0x00000;	// MAIN RAM
   R24[0xC1]=RAM+0x10000;	// MAIN RAM

   for(ta=0;ta<0x100;ta++){
      W24[ta]=R24[ta];		// COPY READ>WRITE
   }

   for(ta=0;ta<(0x300000>>16);ta++){
      R24[ta]=ROM+(ta<<16);	// 68020 ROM
   }

   memset(ROM,0xFF,0x200000);

   if(!load_rom("300-a01.34k", ROM, 0x08000)) return;

   if(!load_rom("521-a03.30b", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=2){
      WriteWord68k(&ROM[ta+ta+0x200000],ReadWord(&RAM[ta]));
   }
   if(!load_rom("521-a02.31b", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=2){
      WriteWord68k(&ROM[ta+ta+0x200002],ReadWord(&RAM[ta]));
   }

   memset(RAM+0x00000,0x00,0x80000);

   //F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;

   //InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x1000);

   //SetScreenBitmap(320+128,232+128,64,64,320,232);

   init_m68k();
}

static void execute_salmndr2(void)
{
   Execute68020(CPU_FRAME_MHz(12,60));	// M68020 48MHz (60fps)
/*
   Interrupt68020(3);
   Interrupt68020(2);
   Interrupt68020(5);
*/
}

static struct VIDEO_INFO video_salmndr2 =
{
   NULL,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_salmndr2[] =
{
   { "salamander_2", },
   { "salmndr2", },
   { NULL, },
};
GAME( salmndr2, "Salamander 2", KONAMI, 1995, GAME_MISC | GAME_NOT_WORKING,
	.video = &video_salmndr2,
	.exec = execute_salmndr2,
);

