/******************************************************************************/
/*                                                                            */
/*                BUBBLE MEMORIES (C) 1995 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"		// save/load game routines
#include "sasound.h"
#include "blit.h"

/********************
   BUBBLE MEMORIES
 ********************/

static struct ROM_INFO rom_bubblem[] =
{
  { "e21-21.20", 0x080000, 0xcac4169c, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "e21-20.19", 0x080000, 0x7727c673, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "e21-19.18", 0x080000, 0xbe0b907d, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "e21-18.17", 0x080000, 0xd14e313a, REGION_CPU1, 0x000003, LOAD_8_32 },
  { "e21-02.rom", 0x200000, 0xb7cb9232, REGION_GFX1 , 0x000000, LOAD_8_32S },
  { "e21-01.rom", 0x200000, 0xa11f2f99, REGION_GFX1 , 0x000002, LOAD_8_32S },
  { "e21-07.rom", 0x100000, 0x7789bf7c, REGION_GFX2 , 0x000000, LOAD_16_64S },
  { "e21-06.rom", 0x100000, 0x997fc0d7, REGION_GFX2 , 0x000004, LOAD_16_64S },
  { "e21-05.rom", 0x100000, 0x07eab58f, REGION_GFX2 , 0x000000, LOAD_MASK8 },
  { "e21-03.rom", 0x200000, 0x54c5f83d, REGION_SOUND1, 0x000000, LOAD_BE }, // C8 C9 CA CB
  { "e21-04.rom", 0x200000, 0xe5af2a2d, REGION_SOUND1, 0x400000, LOAD_BE }, // CC CD -std-
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "e21-12.rom",  0x34093de1,   "e21-13.rom",  0x9e9ec437),
   {           NULL,          0,          0, 0, 0, 0, },
};


static struct ROMSW_DATA romsw_data_bubble_memories_0[] =
{
   { "Taito Worldwide (Japanese)", 0x01 },
   { "Taito America",              0x02 },
   { "Taito Japan",                0x03 },
   { NULL,                         0    },
};

static struct ROMSW_INFO bubblem_romsw[] =
{
   { 0x0FFFFF, 0x03, romsw_data_bubble_memories_0 },
   { 0,        0,    NULL },
};

/**************************
   BUBBLEM MEMORIES JAPAN
 **************************/

static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;
static UINT8 *RAM_BG4;		// PIXEL

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;
static UINT8 *RAM_SCR4;		// PIXEL

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;
static UINT32 SCR4_XOFS;		// PIXEL

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;
static UINT32 SCR4_YOFS;		// PIXEL

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 default_eeprom_world[] = {
  0x41,0x54,0x54,0x49,0x03,0x4f,0x31,0x30,0x30,0x31,0x01,0xe0,0x12,0x11,0x00,
  0x30,0x00,0x00,0x04,0x02,0xf7,0xff,0x12,0x22,0x00,0x00,0x00,0x00,0x00,0x00,
  0xe7,0x6c };

static UINT8 default_eeprom_jp[] = {
  0x41,0x54,0x54,0x49,0x01,0x4f,0x31,0x30,0x30,0x31,0x01,0xe0,0x11,0x11,0x00,
  0x30,0x00,0x00,0x03,0x02,0xf7,0xff,0x12,0x22,0x00,0x00,0x00,0x00,0x00,0x00,
  0xeb,0x6c };

static void LoadBubbleMemories(int version)
{
   RAMSize=0x80000;

   if (version == 0) {
     default_eeprom = default_eeprom_world;
     default_eeprom_size = sizeof(default_eeprom_world);
   } else {
     default_eeprom = default_eeprom_jp;
     default_eeprom_size = sizeof(default_eeprom_jp);
   }
   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_SPR = load_region[REGION_GFX1];
   GFX_BG0 = load_region[REGION_GFX2];
   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x3C23);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x64AB);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x32000;
   RAM_BG3=RAM+0x34000;
   RAM_BG2=RAM+0x36000;
   RAM_BG4=RAM+0x50000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR0_XOFS=(0xFFD8)<<6;
   SCR1_XOFS=(0xFFDC)<<6;
   SCR3_XOFS=(0xFFE0)<<6;
   SCR2_XOFS=(0xFFE4)<<6;
   SCR4_XOFS=(0x0029-1)<<0;

   SCR0_YOFS=(0xFFFF)<<7;
   SCR1_YOFS=(0xFFFF)<<7;
   SCR3_YOFS=(0xFFFF)<<7;
   SCR2_YOFS=(0xFFFF)<<7;
   SCR4_YOFS=(0x001F-1)<<0;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   //WriteWord68k(&ROM[0x199b4],0x4e71); // Hack from mame ??!
   //save_file("rom.dat",M68000ROM,0x40000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x103DBC],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x103DBE],0x4E75);		//	rts

   WriteWord68k(&ROM[0x103E38],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x103E3A],0x4E75);		//	rts

   // SPEED HACKS
   // -----------

   WriteWord68k(&ROM[0x100A5E],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x100A60],0x4E71);		//	nop
   WriteWord68k(&ROM[0x100A62],0x4E71);		//	nop

   WriteWord68k(&ROM[0x100906],0x4EF9);		//	jmp	$FF000
   WriteLong68k(&ROM[0x100908],0x000FF000);	//

   WriteLong68k(&ROM[0x0FF000],0x526D8124);	//	addq	#1,(-32476,a5)
   WriteWord68k(&ROM[0x0FF004],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x0FF006],0x4EF9);		//	jmp	$E98F8
   WriteLong68k(&ROM[0x0FF008],0x001008FC);	//

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   init_tc003vcu(0,0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x20000;
   tc0200obj.RAM_B	= RAM+0x28000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x1F;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void load_bubblem(void) {
  LoadBubbleMemories(0);
}

static void DrawBubbleMemories(void)
{
   ClearPaletteMap();

   if(check_layer_enabled(f3_bg0_id))
       draw_f3_opaque_layer((ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7,RAM_BG0,GFX_BG0,0);
   else
       clear_game_screen(0);
   if (check_layer_enabled(f3_bg1_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,(ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7,RAM_BG1,GFX_BG0,GFX_BG0_SOLID);
   if (check_layer_enabled(f3_bg2_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,(ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7,RAM_BG2,GFX_BG0,GFX_BG0_SOLID);
   if (check_layer_enabled(f3_bg3_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,(ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7,RAM_BG3,GFX_BG0,GFX_BG0_SOLID);

   if(check_layer_enabled(f3_bg6_id))
       draw_f3_pixel(((ReadWord68k(&RAM_SCR4[0])-SCR4_XOFS)>>0),((ReadWord68k(&RAM_SCR4[2])-SCR4_YOFS)>>0),RAM_BG4);

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}



static struct VIDEO_INFO video_bubblem =
{
   DrawBubbleMemories,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_bubblem[] =
{
   { "bubble_memories", },
   { "bubblem", },
   { NULL, },
};
GAME( bubblem, "Bubble Memories", TAITO, 1995, GAME_PLATFORM,
	.input = f3_system_inputs,
	.romsw = bubblem_romsw,
	.video = &video_bubblem,
	.exec = ExecuteF3SystemFrame_NoInt5,
	.long_name_jpn = "バブルメモリーズ",
	.board = "E21",
	.sound = f3_sound,
);

