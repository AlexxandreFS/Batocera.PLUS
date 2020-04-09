/******************************************************************************/
/*                                                                            */
/*                 DARIUS GAIDEN (C) 1994 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"
#include "blit.h" // clear_game_screen

static struct ROM_INFO rom_dariusg[] =
{
  { "d87-12.bin", 0x80000, 0xde78f328, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "d87-11.bin", 0x80000, 0xf7bed18e, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "d87-10.bin", 0x80000, 0x4149f66f, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "d87-16.bin", 0x80000, 0x8f7e5901, REGION_CPU1, 0x000003, LOAD_8_32 },
  { "d87-03.bin", 0x200000, 0x4be1666e, REGION_GFX1 , 0x000000, LOAD_8_32S },
  { "d87-04.bin", 0x200000, 0x2616002c, REGION_GFX1 , 0x000002, LOAD_8_32S },
  { "d87-05.bin", 0x200000, 0x4e5891a9, REGION_GFX1 , 0x000000, LOAD_MASK4 },
  { "d87-06.bin", 0x200000, 0x3b97a07c, REGION_GFX2 , 0x000000, LOAD_16_64S },
  { "d87-17.bin", 0x200000, 0xe601d63e, REGION_GFX2 , 0x000004, LOAD_16_64S },
  { "d87-08.bin", 0x200000, 0x76d23602, REGION_GFX2 , 0x000000, LOAD_MASK8 },
  { "d87-13.bin", 0x40000, 0x15b1fff4, REGION_CPU2, 0x000000, LOAD_8_16 },
  { "d87-14.bin", 0x40000, 0xeecda29a, REGION_CPU2, 0x000001, LOAD_8_16 },
  { "d87-01.bin", 0x200000, 0x3848a110, REGION_SMP1 , 0x000000, LOAD_BE }, // C9 CA CB CC
  { "d87-02.bin", 0x200000, 0x9250abae, REGION_SMP1 , 0x400000, LOAD_BE }, // CD CE CF D0
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROMSW_DATA romsw_data_darius_gaiden_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito",         0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_dariusg[] =
{
   { 0x1FFFFF, 0x03, romsw_data_darius_gaiden_0 },
   { 0,        0,    NULL },
};


static struct ROM_INFO rom_dariusgx[] =
{
  { "dge_mpr3.bin", 0x80000, 0x1c1e24a7, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "dge_mpr2.bin", 0x80000, 0x7be23e23, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "dge_mpr1.bin", 0x80000, 0xbc030f6f, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "dge_mpr0.bin", 0x80000, 0xc5bd135c, REGION_CPU1, 0x000003, LOAD_8_32 },
  { NULL, 0, 0, 0, 0, 0 }
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

static void load_dariusg()
{
   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_SPR = load_region[REGION_GFX1];
   GFX_BG0 = load_region[REGION_GFX2];
   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x8000);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

   RAM_BG0=RAM+0x33000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A006;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A000;

   SCR3_XOFS=0xF600;
   SCR2_XOFS=0xF700;
   SCR1_XOFS=0xF800;
   SCR0_XOFS=0xF900;

   SCR3_YOFS=0xFF80;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xFF80;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;
   // memset(PCMROM+0x800000,0,0x1fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   if(is_current_game("dariusg")){

   // EEPROM HACKS

   WriteWord68k(&ROM[0x047C0],0x7F00);		//	raine	#$00 <eeprom access>
   WriteWord68k(&ROM[0x047C2],0x4ED6);		//	jmp	(a6)

   }
   else{

   // EEPROM HACKS

   WriteWord68k(&ROM[0x047E6],0x7F00);		//	raine	#$00 <eeprom access>
   WriteWord68k(&ROM[0x047E8],0x4ED6);		//	jmp	(a6)

   }

   WriteWord68k(&ROM[0x0554],0x4ED6);		// disable slow hardware check
   WriteWord68k(&ROM[0x0522],0x4ED6);		// 2nd part

   // SPEED HACK#1

   WriteWord68k(&ROM[0x02320],0x4EF9);
   WriteLong68k(&ROM[0x02322],0x0000FF00);

   WriteWord68k(&ROM[0x0FF00],0x4EB9);
   WriteLong68k(&ROM[0x0FF02],0x00001A72);
   WriteWord68k(&ROM[0x0FF06],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x0FF08],0x6100-10);	//	bra.s	<loop>

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
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= 0;	//-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void draw_darius_gaiden(void)
{
   ClearPaletteMap();

   if(check_layer_enabled(f3_bg0_id))
       draw_f3_opaque_layer((ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7,RAM_BG0,GFX_BG0,0);
   else
       clear_game_screen(0);

   if(check_layer_enabled(f3_bg1_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,(ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7,RAM_BG1,GFX_BG0,GFX_BG0_SOLID);

   if(check_layer_enabled(f3_bg2_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,(ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7,RAM_BG2,GFX_BG0,GFX_BG0_SOLID);

   if(check_layer_enabled(f3_bg3_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,(ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7,RAM_BG3,GFX_BG0,GFX_BG0_SOLID);

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}



static struct VIDEO_INFO video_dariusg =
{
   draw_darius_gaiden,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_dariusg[] =
{
   { "darius_gaiden", },
   { "dariusg", },
   { "dariusgj", },
   { NULL, },
};
#define input_dariusg f3_system_inputs
#define dsw_dariusg NULL
#define execute_dariusg ExecuteF3SystemFrame
#define sound_dariusg f3_sound
GME( dariusg, "Darius Gaiden", TAITO, 1994, GAME_SHOOT,
	.romsw = romsw_dariusg,
	.long_name_jpn = "ダライアス外伝",
	.board = "D87",
);
static struct DIR_INFO dir_dariusgx[] =
{
   { "darius_gaiden_extra", },
   { "dariusgx", },
   { ROMOF("dariusg"), },
   { CLONEOF("dariusg"), },
   { NULL, },
};
CLNE( dariusgx, dariusg, "Darius Gaiden Extra", TAITO, 1994, GAME_SHOOT,
	.romsw = romsw_dariusg,
	.video = &video_dariusg,
	.long_name_jpn = "ダライアス外伝 Extra",
	.board = "D87",
);

