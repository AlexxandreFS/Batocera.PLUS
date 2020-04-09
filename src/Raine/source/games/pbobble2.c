/******************************************************************************/
/*                                                                            */
/*               PUZZLE BOBBLE 2/2x (C) 1994 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"
#include "blit.h"


static struct ROM_INFO rom_pbobble2[] =
{
  { "e10-22.bin", 0x40000, 0x7b12105d, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "e10-23.bin", 0x40000, 0x56a66435, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "e10-24.bin", 0x40000, 0xf9d0794b, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "e10-25.bin", 0x40000, 0xff0407d3, REGION_CPU1, 0x000003, LOAD_8_32 },
  { "e10-02.rom", 0x100000, 0xc0564490, REGION_GFX1 , 0x000000, LOAD_8_32S },
  { "e10-01.rom", 0x100000, 0x8c26ff49, REGION_GFX1 , 0x000002, LOAD_8_32S },
  { "e10-07.rom", 0x100000, 0xdcb3c29b, REGION_GFX2 , 0x000000, LOAD_16_64S },
  { "e10-06.rom", 0x100000, 0x1b0f20e2, REGION_GFX2 , 0x000004, LOAD_16_64S },
  { "e10-05.rom", 0x100000, 0x81266151, REGION_GFX2 , 0x000000, LOAD_MASK8_45 },
  { "e10-03.rom", 0x200000, 0x46d68ac8, REGION_SOUND1 , 0x000000, LOAD_BE }, // CC CD CE CF
  { "e10-04.rom", 0x200000, 0x5c0862a6, REGION_SOUND1 , 0x400000, LOAD_BE }, // C8 C9 CA CB
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "e10-12.rom",  0xb92dc8ad,   "e10-13.rom",  0x87842c13),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pbobble2o[] = // clone of pbobble2
{
  { "e10-11.20", 0x40000, 0xb82f81da, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "e10-10.19", 0x40000, 0xf432267a, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "e10-09.18", 0x40000, 0xe0b1b599, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "e10-15.17", 0x40000, 0xa2c0a268, REGION_CPU1, 0x000003, LOAD_8_32 },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_puzzle_bobble_2_0[] =
{
   { "Taito Japan (Japanese)",            0x01 },
   { "Taito America (Bust-a-move again)", 0x02 },
   { "Taito Japan",                       0x03 },
   { NULL,                                0    },
};

static struct ROMSW_INFO romsw_pbobble2[] =
{
   { 0x0FFFFF, 0x03, romsw_data_puzzle_bobble_2_0 },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_pbobble2x[] = // clone of pbobble2
{
  { "e10-29.20", 0x40000, 0xf1e9ad3f, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "e10-28.19", 0x40000, 0x412a3602, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "e10-27.18", 0x40000, 0x88cc0b5c, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "e10-26.17", 0x40000, 0xa5c24047, REGION_CPU1, 0x000003, LOAD_8_32 },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "e10.30",  0xbb090c1e,       "e10.31",  0xf4b88d65),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_puzzle_bobble_2x_0[] =
{
   { "Taito Japan (Japanese)",               0x01 },
   { "Taito America (Bust-a-move again EX)", 0x02 },
   { "Taito Japan",                          0x03 },
   { NULL,                                   0    },
};

static struct ROMSW_INFO romsw_pbobble2x[] =
{
   { 0x0FFFFF, 0x03, romsw_data_puzzle_bobble_2x_0 },
   { 0,        0,    NULL },
};


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

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_pbobble2(void)
{
   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   GFX_SPR = load_region[REGION_GFX1];
   GFX_BG0 = load_region[REGION_GFX2];
   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x3EC7);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3F5D);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x33000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A006;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A000;

   SCR3_XOFS=0xF640;
   SCR2_XOFS=0xF740;
   SCR1_XOFS=0xF840;
   SCR0_XOFS=0xF940;

   SCR3_YOFS=0xF400;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xF400;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   if (is_current_game("pbobble2x")) {
       // EEPROM ACCESS
       // -------------

       WriteWord68k(&ROM[0x0044D2],0x7F00);		//	raine	#$00 <eeprom access>
       WriteWord68k(&ROM[0x0044D4],0x4ED6);		//	jmp	(a6)

       // SPEED HACK
       // ----------

       WriteWord68k(&ROM[0x031D4],0x4EF9);		//	jmp	$F8000
       WriteLong68k(&ROM[0x031D6],0x000F8000);

       WriteWord68k(&ROM[0xF8000],0x4EB9);		//	jsr	$0291C <random gen>
       WriteLong68k(&ROM[0xF8002],0x0000291C);
       WriteWord68k(&ROM[0xF8006],0x7F02);		//	raine	#$02 <stop cpu>
       WriteWord68k(&ROM[0xF8008],0x6100-10);	//	bra.s	<loop>
   } else if (is_current_game("pbobble2")) { // 2.30
       // EEPROM ACCESS
       // -------------

       WriteWord68k(&ROM[0x004516],0x7F00);		//	raine	#$00 <eeprom access>
       WriteWord68k(&ROM[0x004518],0x4ED6);		//	jmp	(a6)

       // SPEED HACK
       // ----------

       WriteWord68k(&ROM[0x03218],0x4EF9);		//	jmp	$F8000
       WriteLong68k(&ROM[0x0321a],0x000F8000);

       WriteWord68k(&ROM[0xF8000],0x4EB9);		//	jsr	$02960 <random gen>
       WriteLong68k(&ROM[0xF8002],0x00002960);
       WriteWord68k(&ROM[0xF8006],0x7F02);		//	raine	#$02 <stop cpu>
       WriteWord68k(&ROM[0xF8008],0x6100-10);	//	bra.s	<loop>

       // Wonder if it's a real update or just a hack ?
       WriteWord68k(&ROM[0x40092],0x4e71);	// weird crash (nops)
       WriteWord68k(&ROM[0x40094],0x4e71);	// nop
       WriteWord68k(&ROM[0x40096],0x4e71);	// nop
   } else { // 2.20
       // EEPROM ACCESS
       // -------------

       WriteWord68k(&ROM[0x0044B2],0x7F00);		//	raine	#$00 <eeprom access>
       WriteWord68k(&ROM[0x0044B4],0x4ED6);		//	jmp	(a6)

       // SPEED HACK
       // ----------

       WriteWord68k(&ROM[0x31B4],0x4EF9);		//	jmp	$F8000
       WriteLong68k(&ROM[0x31B6],0x000F8000);

       WriteWord68k(&ROM[0xF8000],0x4EB9);		//	jsr	$028FC <random gen>
       WriteLong68k(&ROM[0xF8002],0x000028FC);
       WriteWord68k(&ROM[0xF8006],0x7F02);		//	raine	#$02 <stop cpu>
       WriteWord68k(&ROM[0xF8008],0x6100-10);	//	bra.s	<loop>
   }

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   init_tc003vcu(0,0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x20000;
   tc0200obj.RAM_B	= RAM+0x28000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawPuzzleBobble2(void)
{
   int zz;
   int x,y,z;
   UINT8 *map;

   ClearPaletteMap();

   if(check_layer_enabled(f3_bg0_id))
       draw_f3_opaque_layer((ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7,RAM_BG0,GFX_BG0,3);
   else
       clear_game_screen(0);

   if (check_layer_enabled(f3_bg1_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,(ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7,RAM_BG1,GFX_BG0,GFX_BG0_SOLID);
   if (check_layer_enabled(f3_bg2_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,(ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7,RAM_BG2,GFX_BG0,GFX_BG0_SOLID);
   if (check_layer_enabled(f3_bg3_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,(ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7,RAM_BG3,GFX_BG0,GFX_BG0_SOLID);

   // object

   render_tc0200obj_mapped_f3system_b();

   if(check_layer_enabled(f3_bg5_id)){
   zz=0;
   for(y=64;y<232+64;y+=8){
   for(x=64;x<320+64;x+=8){
      z=RAM[0x3C001+zz];
      if((z!=0)&&(z!=0x10)){		// 0x10='brown' rectangle

         MAP_PALETTE_MULTI_MAPPED_NEW(
            (RAM[0x3C000+zz]>>1)&0x3F,
            16,
            map
         );

         if((RAM[0x3C000+zz]&0x01)!=0){
            Draw8x8_Trans_Packed_Mapped_Rot(&RAM[0x3E000+(z<<5)],x,y,map);
         }
         else{
	   Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&RAM[0x3E000+(z<<5)],x,y,map);
         }

      }
      zz+=2;
   }
   zz+=(128-80);
   }
   }
}


/******************************************************************************/
/* ENSONIQ ES-5505 [OTIS]                                                     */
/******************************************************************************/

/*

1E - Page Select

Page	Address	Function
00 - 1F	00 - 1D	Voice Specific Control
40	00 - ??

*/


/******************************************************************************/
/* ENSONIQ ES-5510 [Ensoniq Signal Processor / DSP]                           */
/******************************************************************************/

/*

Address	Register Name	Bits	Description / Function
---------------------------------------------------------------
00	GPR        	23-16	GPR / SPR Data MS-byte
01	GPR 		15-8	GPR / SPR  Data
02	GPR   		7-0	GPR / SPR  Data LS-byte
03	INSTR           47-40	Mult D Operand Address
04	INSTR   	39-32	Mult C Operand Address
05	INSTR 		31-24 	ALU B Operand Address
06	INSTR    	23-16	ALU A Operand Address
07	INSTR    	15-8	ALU Opcode / Operand Select
08	INSTR    	7-3	Skip Flag +  MAC + RAM Control
09	DIL 		23-16	DRAM Input Latch MS-byte
0A	DIL 		15-8	DRAM Input Latch
0B	DIL		7-0	DRAM Input Latch LS-byte	 (always read as 00 )
0C	DOL 		23-16	DRAM Ouput Latch MS-byte
0D	DOL 		15-8	DRAM Ouput Latch
0E	DOL		7-0	DRAM Ouput Latch LS-byte	 (always read as FF )
0F	DADR		23-16	DRAM Address MS-byte	 (write last to transfer data)
10	DADR		15-8	DRAM Address
11	DADR  		7-4	DRAM Address LS-byte
12	Host Control 	2-0	ESP State / Control Flags
14	RAM Access Control 	7-6	RAM,I/O, Read/Write Select
16	Program Counter            		For Test Purposes Only
17	Internal Refresh counter        		For Test Purposes Only
18	Host serial control	7-0	Serial I/O Format and Control
1F	Halt enable       (write only) Frame Counter (read only)		Stop ESP Execution For Test Purposes Only

80	Read  Select:  GPR + INSTR  	7-0	Read  Address	Address Ranges:
A0	Write Select:  GPR      	7-0	Write Address	GPR       $00 - $BF
C0	Write Select:  INSTR      	7-0	Write Address	SPR       $EA - $FF
E0	Write Select:  GPR+INSTR	7-0	Write Address	INSTR   $00 - $9F

*/


/*

Elevator Action 2
-----------------

Ensoniq
OTISR2
609-0381303
FP05164
K9442

Ensoniq
5701000101
9416MVA82

Ensoniq
609-0390750
FP03457 K9420
ES5510000106
ESPR6

Motorola
MC68681P

Twin Qix
--------

Ensoniq
OTISR2
609-0381303
FP05164
K9442

Ensoniq
5701000101
9416MVA82

Ensoniq
609-0390750
FP03457 K9420
ES5510000106
ESPR6

Motorola
MC68681P

Super Chase
-----------

68000
68681
MB8421 (x2)
MB87078
Ensoniq 5510
Ensoniq 5505

*/
static struct VIDEO_INFO video_pbobble2 =
{
   DrawPuzzleBobble2,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_pbobble2[] =
{
   { "puzzle_bobble_2", },
   { "pbobble2", },
   { NULL, },
};
#define input_pbobble2 f3_system_inputs
#define dsw_pbobble2 NULL
#define execute_pbobble2 ExecuteF3SystemFrameB
#define sound_pbobble2 f3_sound

GME( pbobble2, "Puzzle Bobble 2 (Ver 2.3O 1995/07/31)", TAITO, 1995, GAME_PUZZLE,
	.romsw = romsw_pbobble2,
	.long_name_jpn = "パズルボブル２",
	.board = "E10",
);
CLNEI(pbobble2o, pbobble2,"Puzzle Bobble 2 (Ver 2.2O 1995/07/20)",TAITO,1995,GAME_PUZZLE);
CLNEI(pbobble2x, pbobble2,"Puzzle Bobble 2X (Ver 2.20 1995/11/11)",TAITO,1995,GAME_PUZZLE,
	.romsw = romsw_pbobble2x,
	);

