#define DRV_DEF_SOUND f3_sound
/******************************************************************************/
/*                                                                            */
/*                 SUPER CHASE (C) 1992 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_superchs[] =
{
   {    "d46-01.64", 0x00200000, 0x5c2ae92d, 0, 0, 0, },
   {    "d46-02.65", 0x00200000, 0xa83ca82e, 0, 0, 0, },
   {    "d46-03.66", 0x00200000, 0xe0e9cbfd, 0, 0, 0, },
   {    "d46-04.67", 0x00200000, 0x832769a9, 0, 0, 0, },
   {    "d46-05.87", 0x00100000, 0x150d0e4c, 0, 0, 0, },
   {    "d46-06.88", 0x00100000, 0x321308be, 0, 0, 0, },
   {    "d46-07.34", 0x00080000, 0xc3b8b093, 0, 0, 0, },
   {     "d46-10.2", 0x00200000, 0x306256be, 0, 0, 0, },
   {     "d46-11.5", 0x00200000, 0xd4ea0f56, 0, 0, 0, },
   {     "d46-12.4", 0x00200000, 0xa24a53a8, 0, 0, 0, },
  LOAD8_16(  REGION_ROM3,  0x000000,  0x00020000,
              "d46-24.127",  0xa006baa1,   "d46-23.112",  0x9a69dbd0),
   {    "d46-31.21", 0x00040000, 0x38b983a3, 0, 0, 0, },
   {    "d46-33.23", 0x00040000, 0x3094bcd0, 0, 0, 0, },
   {    "d46-34.25", 0x00040000, 0xc72a4d2b, 0, 0, 0, },
   {    "d46-35.27", 0x00040000, 0x1575c9a7, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d46-37.8up",  0x60b51b91,   "d46-36.7lo",  0x8f7aa276),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_superchs[] =
{

   INP0( COIN1, 0x069001, 0x80 ),
   INP0( COIN2, 0x069001, 0x40 ),

   INP0( SERVICE, 0x069001, 0x07 ),
   INP0( TEST, 0x069001, 0x10 ),

   INP0( P1_START, 0x069002, 0x80 ),

   INP0( P1_B1, 0x069002, 0x10 ),
   INP0( P1_B2, 0x069002, 0x20 ),

   END_INPUT
};

static struct ROMSW_DATA romsw_data_super_chase_0[] =
{
   { "Taito 1",                0x01 },
   { "Taito 2",                0x02 },
   { "Taito 3",                0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_superchs[] =
{
   { 0x0FFFFF, 0x02, romsw_data_super_chase_0 },
   { 0,        0,    NULL },
};



#define OBJ_A_COUNT	(0xF1D0)

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
//static UINT8 *GFX_OBJ_A_SOLID;

//static UINT8 *zoom16_ofs;
static UINT8 *ROM3;

static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

//static UINT8 *GFX_SPR;
//static UINT8 *GFX_SPR_SOLID;

static void AddSCMemoryMap(UINT32 romsize)
{
   UINT32 ta;

   for(ta=0;ta<0x100;ta++){
      R24[ta]=RAM+0x70000;	// SCRATCH RAM
   }

   R24[0x10]=RAM+0x00000;	// MAIN RAM
   R24[0x11]=RAM+0x10000;	// MAIN RAM

   R24[0x18]=RAM+0x30000;	// SCREEN RAM - F3 system

   R24[0x1B]=RAM+0x6A000;	// SCROLL RAM - F3 system

   R24[0x20]=RAM+0x40000;	// COMM RAM?

   R24[0x28]=RAM+0x60000;	// COLOR?
   R24[0x2c]=(UINT8*)f3_shared_ram;

   R24[0x30]=RAM+0x69000;	// INPUT	($300000-$300007)


/*
   R24[0x30]=RAM+0x40000;	// OBJECT?

   //R24[0xC0]=RAM+0x68000;	// SOUND RAM	($C00000-$C007FF)
*/
   for(ta=0;ta<0x100;ta++){
      W24[ta]=R24[ta];		// COPY READ>WRITE
   }

   for(ta=0;ta<(romsize>>16);ta++){
      R24[ta]=ROM+(ta<<16);	// 68020 ROM
   }

   W24[0x30]=RAM+0x69100;	// OUTPUT	($300000-$300007)

   EEPROM=RAM+0x6B000;		// EEPROM
}

static UINT8 ram_comm_rb(UINT32 addr)
{
   addr &= 0xFFFF;
   return RAM[0x40000+addr];
}

static UINT16 ram_comm_rw(UINT32 addr)
{
   addr &= 0xFFFF;
   return ReadWord68k(&RAM[0x40000+addr]);
}

static void ram_comm_wb(UINT32 addr, UINT8 data)
{
   addr &= 0xFFFF;
   RAM[0x40000+addr] = data;
}

static void ram_comm_ww(UINT32 addr, UINT16 data)
{
   addr &= 0xFFFF;
   WriteWord68k(&RAM[0x40000+addr], data);
}

static void load_superchs(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   if(!(GFX_BG0=AllocateMem(0x3F6C00))) return;

   if(!(GFX_OBJ_A=AllocateMem(OBJ_A_COUNT*0x100))) return;
   if(!(OBJECT_MAP=AllocateMem(0x80000))) return;

   if(!(TMP=AllocateMem(0x200000))) return;

   if(!load_rom("d46-01.64", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_A[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_A[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_A[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_A[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_A[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_A[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_A[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_A[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom("d46-02.65", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom("d46-03.66", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom("d46-04.67", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }

   if(!load_rom("d46-07.34", OBJECT_MAP, 0x80000)) return; // TILE MAPPING

   tb=0;
   if(!load_rom("d46-05.87", TMP, 0xFDB00)) return;	// 16x16 TILES ($3F6C)
   for(ta=0;ta<0xFDB00;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d46-06.88", TMP, 0xFDB00)) return;	// 16x16 TILES
   for(ta=0;ta<0xFDB00;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x03F6C);

   RAMSize=0xB0000;

   if(!(RAM=AllocateMem(0xB0000))) return;
   if(!(ROM=AllocateMem(0x140000))) return;

   // Setup 68020 Memory Map
   // ----------------------

   AddSCMemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG3=RAM+0x33000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;

   SCR0_XOFS=0x0020;
   SCR1_XOFS=0x001C;
   SCR2_XOFS=0x0018;
   SCR3_XOFS=0x0014;

   SCR0_YOFS=0xFFF8;
   SCR1_YOFS=0xFFF8;
   SCR2_YOFS=0xFFF8;
   SCR3_YOFS=0xFFF8;

   if(!load_rom("d46-35.27", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d46-34.25", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d46-33.23", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d46-31.21", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // Load 68000 PROGRAM ROMS

   ROM3 = load_region[REGION_ROM3];
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xe00000))) return;
   load_be("d46-10.2",PCMROM+0x000000,0x200000);
   load_be("d46-12.4",PCMROM+0x400000,0x200000);
   load_be("d46-11.5",PCMROM+0x800000,0x200000);
   max_banks_this_game=6;

   memset(PCMROM+0xc00000,0,0x1fffff);
   memset(RAM+0x00000,0x00,0xB0000);
   memset(RAM+0x69000,0xFF,0x01000);

   RAM[0x69001] &= ~8;

   add_eeprom(EEPROM, 0x80, EPR_INVALIDATE_ON_ROM_CHANGE);
   load_eeprom();

   // eeprom hacks

   WriteWord68k(&ROM[0x007292],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x007294],0x4E75);		//	rts

   WriteWord68k(&ROM[0x007316],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x007318],0x4E75);		//	rts

   // main cpu speed hack

   WriteWord68k(&ROM[0x0006FA],0x7F02);		//	raine	#$02	<stop cpu>
   WriteWord68k(&ROM[0x0006FC],0x6100-8);	//	bra.s	<loop>

   // main rom checksum

   WriteWord68k(&ROM[0x0036AA],0x4E75);

   // communication lockup

   WriteWord68k(&ROM[0x0005D0],0x4E71);

   // sub cpu speed hack

   WriteLong68k(&ROM[0x10044E],0x4EF80300);

   WriteWord68k(&ROM[0x100300],0x52B9);
   WriteLong68k(&ROM[0x100302],0x0080000A);

   WriteLong68k(&ROM[0x100306],0x13FC0000);
   WriteLong68k(&ROM[0x10030A],0x00AA0000);
   WriteWord68k(&ROM[0x10030E],0x6100-16);

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);


   init_m68k();
   setup_sound_68000();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM3,0x40000);

   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM3-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM3);		      // 68000 ROM
   AddReadByteMC68000B(0x200000, 0x20FFFF, NULL, RAM+0x080000);	      // WORK RAM
   AddReadByteMC68000B(0x800000, 0x80FFFF, ram_comm_rb, NULL);	      // COMMON RAM
   AddReadByteMC68000B(0x600000, 0x60FFFF, NULL, RAM+0x090000);	      // ?
   AddReadByteMC68000B(0xA00000, 0xA001FF, NULL, RAM+0x0A0000);			// ?
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM3);			// 68000 ROM
   AddReadWordMC68000B(0x200000, 0x20FFFF, NULL, RAM+0x080000);			// WORK RAM
   AddReadWordMC68000B(0x800000, 0x80FFFF, ram_comm_rw, NULL);			// COMMON RAM
   AddReadWordMC68000B(0x600000, 0x60FFFF, NULL, RAM+0x090000);			// ?
   AddReadWordMC68000B(0xA00000, 0xA001FF, NULL, RAM+0x0A0000);			// ?
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1,NULL, NULL);

   AddWriteByteMC68000B(0x200000, 0x20FFFF, NULL, RAM+0x080000);		// WORK RAM
   AddWriteByteMC68000B(0x800000, 0x80FFFF, ram_comm_wb, NULL);			// COMMON RAM
   AddWriteByteMC68000B(0x600000, 0x60FFFF, NULL, RAM+0x090000);		// ?
   AddWriteByteMC68000B(0xA00000, 0xA001FF, NULL, RAM+0x0A0000);		// ?
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x200000, 0x20FFFF, NULL, RAM+0x080000);		// WORK RAM
   AddWriteWordMC68000B(0x800000, 0x80FFFF, ram_comm_ww, NULL);			// COMMON RAM
   AddWriteWordMC68000B(0x600000, 0x60FFFF, NULL, RAM+0x090000);		// ?
   AddWriteWordMC68000B(0xA00000, 0xA001FF, NULL, RAM+0x0A0000);		// ?
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...

   Reset68020();
}

static void ClearSuperChase(void)
{
   save_eeprom();
}

static void execute_superchs(void)
{
  int ta;
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
      print_debug("PC020:%06x SR:%04x\n",regs.pc,regs.sr);
   Interrupt68020(2);
   Interrupt68020(3);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(8,60));	// M68000 8MHz (60fps)
#ifdef RAINE_DEBUG
   // Not sure wether these are actually about the 2nd 68k...
   print_debug("PC000:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
#endif
   if(((regs.sr & 0x0700)!=0x0700)&&(s68000context.pc==0x030e))
      cpu_interrupt(CPU_68K_1, 4);

   IntF3System();
}

static void DrawSuperChase(void)
{
   int x,y,ta,zz,zzz,zzzz,x16,y16;
   UINT8 *map;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(RefreshBuffers){

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 240;
   tc0003vcu.scr_x	= 0;
   tc0003vcu.scr_y	= 0;

   }

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>0,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>0
   );

   START_SCROLL_1024x512_4_16(64,64,320,240);

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG0[zz])&0x1FF,
            16,
            map
         );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map); break;
      }

   END_SCROLL_1024x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>0,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>0
   );

   START_SCROLL_1024x512_4_16(64,64,320,240);

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
   if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG1[zz])&0x1FF,
            16,
            map
         );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
      else{
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
   }

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>0,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>0
   );

   START_SCROLL_1024x512_4_16(64,64,320,240);

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
   if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG2[zz])&0x1FF,
            16,
            map
         );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
      else{
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
   }

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>0,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>0
   );

   START_SCROLL_1024x512_4_16(64,64,320,240);

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
   if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG3[zz])&0x1FF,
            16,
            map
         );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
      else{
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
   }

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_gfx2();
   }
}


/*

d67-01.rom | Ensoniq Sample Data
d67-02.rom | Ensoniq Sample Data
d67-03.rom | Zoom Tiles (plane#0)
d67-04.rom | Zoom Tiles (plane#1)
d67-05.rom | Zoom Tiles (plane#2)
d67-06.rom | Zoom Tiles (plane#3)
d67-07.rom | Zoom Tiles (plane#4)
d67-08.rom | 16x16 F3 Tiles (even)
d67-09.rom | 16x16 F3 Tiles (odd)
d67-10.rom | 8x8 F2 Tiles (even)
d67-11.rom | 8x8 F2 Tiles (odd)
d67-12.rom | Mask data (???)
d67-13.rom | Zoom Object Maps
d67-17.rom | 68020 rom (byte#2)
d67-18.rom | 68020 rom (byte#1)
d67-19.rom | 68020 rom (byte#0)
d67-20.rom | 68000 rom (even)
d67-21.rom | 68000 rom (odd)
d67-23.rom | 68020 rom (byte#3)
readme.txt | dumped by aracorn

*/
static struct VIDEO_INFO video_superchs =
{
   DrawSuperChase,
   320,
   240,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_superchs[] =
{
   { "super_chase", },
   { "superchs", },
   { NULL, },
};
GAME( superchs, "Super Chase", TAITO, 1992, GAME_RACE | GAME_NOT_WORKING,
	.input = input_superchs,
	.romsw = romsw_superchs,
	.clear = ClearSuperChase,
	.video = &video_superchs,
	.exec = execute_superchs,
	.board = "D46",
);

