/******************************************************************************/
/*                                                                            */
/*         BUBBLE BOBBLE 2/BUBBLE SYMPHONY (C) 1994 TAITO CORPORATION         */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"
#include "blit.h"

/*******************
   BUBBLE BOBBLE 2
 *******************/


static struct ROM_INFO rom_bublbob2[] =
{
  { "d90-21.ic20", 0x40000, 0x2a2b771a, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "d90-20.ic19", 0x40000, 0xf01f63b6, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "d90-19.ic18", 0x40000, 0x86eef19a, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "d90-18.ic17", 0x40000, 0xf5b8cdce, REGION_CPU1, 0x000003, LOAD_8_32 },
  { "d90-03", 0x100000, 0x6fa894a1, REGION_GFX1 , 0x000000, LOAD_8_32S },
  { "d90-02", 0x100000, 0x5ab04ca2, REGION_GFX1 , 0x000002, LOAD_8_32S },
  { "d90-01", 0x100000, 0x8aedb9e5, REGION_GFX1 , 0x000000, LOAD_MASK4 },
  { "d90-08", 0x100000, 0x25a4fb2c, REGION_GFX2 , 0x000000, LOAD_16_64S },
  { "d90-07", 0x100000, 0xb436b42d, REGION_GFX2 , 0x000004, LOAD_16_64S },
  { "d90-06", 0x100000, 0x166a72b8, REGION_GFX2 , 0x000000, LOAD_MASK8 },
  { "d90-04", 0x200000, 0xfeee5fda, REGION_SMP1, 0x000000, LOAD_BE }, // C8 C9 CA CB
  { "d90-05", 0x200000, 0xc192331f, REGION_SMP1, 0x400000, LOAD_BE }, // CC CD -std-
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "d90.13",  0x6762bd90,       "d90.14",  0x8e33357e),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_bublbob2o[] =
{
   {       "d90.12", 0x00040000, 0x9e523996, REGION_ROM1, 0x000000, LOAD_8_32, },
   {       "d90.11", 0x00040000, 0xedfdbb7f, REGION_ROM1, 0x000001, LOAD_8_32, },
   {       "d90.10", 0x00040000, 0x8e957d3d, REGION_ROM1, 0x000002, LOAD_8_32, },
   {       "d90.17", 0x00040000, 0x711f1894, REGION_ROM1, 0x000003, LOAD_8_32, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_bublbob2p[] =
{
  { "soft-3-8c9b.ic60", 0x40000, 0x15d0594e, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "soft-2-0587.ic61", 0x40000, 0xd1a5231f, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "soft-1-9a9c.ic62", 0x40000, 0xc11a4d26, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "soft-0-a523.ic63", 0x40000, 0x58131f9e, REGION_CPU1, 0x000003, LOAD_8_32 },
  { "cq80-obj-0l-c166.ic8", 0x80000, 0x9bff223b, REGION_GFX1 , 0x000000, LOAD_8_32S },
  { "cq80-obj-0m-24f4.ic30", 0x80000, 0xee71f643, REGION_GFX1 , 0x000002, LOAD_8_32S },
  { "cq80-obj-0h-990d.ic32", 0x80000, 0x4d3a78e0, REGION_GFX1 , 0x000000, LOAD_MASK4 },
  { "cq80-scr0-5ba4.ic7", 0x080000, 0x044dc38b, REGION_GFX3 , 0x000000, LOAD_8_32 },
  { "cq80-scr1-a5f3.ic6", 0x080000, 0x3cf3a3ba, REGION_GFX3 , 0x000001, LOAD_8_32 },
  { "cq80-scr2-cc11.ic5", 0x080000, 0xb81aa2c7, REGION_GFX3 , 0x000002, LOAD_8_32 },
  { "cq80-scr3-4266.ic4", 0x080000, 0xc114583f, REGION_GFX3 , 0x000003, LOAD_8_32 },
  { "cq80-scr4-7fe1.ic3", 0x080000, 0x2bba1728, REGION_GFX4 , 0x000000, LOAD_NORMAL },
  { "snd-h-348f.ic66",    0x020000, 0xf66e60f2, REGION_ROM2,  0x000000, LOAD_8_16 },
  { "snd-l-4ec1.ic65",    0x020000, 0xd302d8bc, REGION_ROM2,  0x000001, LOAD_8_16 },
  { "cq80-snd-data0-7b5f.ic43", 0x080000, 0xbf8f26d3, REGION_SMP1 , 0x000000, LOAD_BE }, // C8
  { "cq80-snd-data1-933b.ic44", 0x080000, 0x62b00475, REGION_SMP1 , 0x100000, LOAD_BE }, // C9
  { "cq80-snd3-std5-3a9c.ic10", 0x080000, 0x26312451, REGION_SMP1 , 0x600000, LOAD_BE }, // -std-
  { "cq80-snd2-std6-a148.ic11", 0x080000, 0x2edaa9dc, REGION_SMP1 , 0x700000, LOAD_BE }, // -std-
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_bubble_bobble_2[] =
{
   { "Taito Japan (Japanese - Symphony)",        0x01 },
   { "Taito America (Symphony)",                 0x02 },
   { "Taito World (Bubble Bobble 2)", 0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO bubsymph_romsw[] =
{
   { 0x0FFFFF, 0x01, romsw_data_bubble_bobble_2 },
   { 0,        0,    NULL },
};

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

static void load_bublbob2(void)
{
   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_SPR = load_region[REGION_GFX1];
   memset(GFX_SPR+0x1C8900,0x00,0x100); // ??!
   if (is_current_game("bublbob2p")) {
       GFX_BG0 = AllocateMem(0x400000);
       int ta;
       int tb=0;
       UINT8 *src = load_region[REGION_GFX3];
       for (ta=0; ta<0x200000; ta++) {
	   GFX_BG0[tb++]=src[ta]&15;
	   GFX_BG0[tb++]=src[ta]>>4;
       }
       src = load_region[REGION_GFX4];
       tb=0;
       for (ta=0; ta<0x80000; ta++) {
	   UINT8 tc=src[ta];
	   GFX_BG0[tb+7]|=((tc&0x80)>>7)<<4;
	   GFX_BG0[tb+6]|=((tc&0x40)>>6)<<4;
	   GFX_BG0[tb+5]|=((tc&0x20)>>5)<<4;
	   GFX_BG0[tb+4]|=((tc&0x10)>>4)<<4;
	   GFX_BG0[tb+3]|=((tc&0x08)>>3)<<4;
	   GFX_BG0[tb+2]|=((tc&0x04)>>2)<<4;
	   GFX_BG0[tb+1]|=((tc&0x02)>>1)<<4;
	   GFX_BG0[tb+0]|=((tc&0x01)>>0)<<4;
	   tb+=8;
       }
   } else
       GFX_BG0 = load_region[REGION_GFX2];

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG3=RAM+0x30000;
   RAM_BG2=RAM+0x32000;
   RAM_BG0=RAM+0x34000;
   RAM_BG1=RAM+0x36000;
   RAM_BG4=RAM+0x50000;

   RAM_SCR3=RAM+0x6A000;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR0=RAM+0x6A004;
   RAM_SCR1=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR3_XOFS=(0xFFD8)<<6;
   SCR2_XOFS=(0xFFDC)<<6;
   SCR0_XOFS=(0xFFE0)<<6;
   SCR1_XOFS=(0xFFE4)<<6;
   SCR4_XOFS=(0x0029-1)<<0;

   SCR3_YOFS=(0xFFFF)<<7;
   SCR2_YOFS=(0xFFFF)<<7;
   SCR0_YOFS=(0xFFFF)<<7;
   SCR1_YOFS=(0xFFFF)<<7;
   SCR4_YOFS=(0x001F-1)<<0;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   if (is_current_game("bublbob2p")) {
       WriteWord68k(&ROM[0x0Eb92c],0x7F00);		//	raine	#$00 <read eeprom>
       WriteWord68k(&ROM[0x0Eb92e],0x4E75);		//	rts

       WriteWord68k(&ROM[0x0Eb9a8],0x7F01);		//	raine	#$01 <write eeprom>
       WriteWord68k(&ROM[0x0Eb9aa],0x4E75);		//	rts
   } else {
       WriteWord68k(&ROM[0x0ECD6A],0x7F00);		//	raine	#$00 <read eeprom>
       WriteWord68k(&ROM[0x0ECD6C],0x4E75);		//	rts

       WriteWord68k(&ROM[0x0ECDE6],0x7F01);		//	raine	#$01 <write eeprom>
       WriteWord68k(&ROM[0x0ECDE8],0x4E75);		//	rts
   }

   // SPEED HACKS
   // -----------

   if (is_current_game("bublbob2p")) {
       WriteWord68k(&ROM[0x0E8a16],0x7F02);		//	raine	#$02 <stop cpu>
       WriteWord68k(&ROM[0x0E8a18],0x4E71);		//	nop
       WriteWord68k(&ROM[0x0E8a1a],0x4E71);		//	nop

       WriteWord68k(&ROM[0x0E8902],0x4EF9);		//	jmp	$FFA00
       WriteLong68k(&ROM[0x0E8904],0x000FFA00);	//

       WriteLong68k(&ROM[0x0FFA00],0x526D8120);	//	addq	#1,(-32480,a5)
       WriteWord68k(&ROM[0x0FFA04],0x7F02);		//	raine	#$02 <stop cpu>

       WriteWord68k(&ROM[0x0FFA06],0x4EF9);		//	jmp	$E88F8
       WriteLong68k(&ROM[0x0FFA08],0x000E88F8);	//
   } else {
       WriteWord68k(&ROM[0x0E9A3A],0x7F02);		//	raine	#$02 <stop cpu>
       WriteWord68k(&ROM[0x0E9A3C],0x4E71);		//	nop
       WriteWord68k(&ROM[0x0E9A3E],0x4E71);		//	nop

       WriteWord68k(&ROM[0x0E9902],0x4EF9);		//	jmp	$FFA00
       WriteLong68k(&ROM[0x0E9904],0x000FFA00);	//

       WriteLong68k(&ROM[0x0FFA00],0x526D8124);	//	addq	#1,(-32476,a5)
       WriteWord68k(&ROM[0x0FFA04],0x7F02);		//	raine	#$02 <stop cpu>

       WriteWord68k(&ROM[0x0FFA06],0x4EF9);		//	jmp	$E98F8
       WriteLong68k(&ROM[0x0FFA08],0x000E98F8);	//
   }

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
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x1F;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawBubbleSymphony(void)
{
   ClearPaletteMap();

   if(check_layer_enabled(f3_bg0_id))
       draw_f3_opaque_layer((ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7,RAM_BG0,GFX_BG0,2);
   else
       clear_game_screen(0);
   if(check_layer_enabled(f3_bg1_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,(ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7,RAM_BG1,GFX_BG0,GFX_BG0_SOLID);

   if(check_layer_enabled(f3_bg2_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,(ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7,RAM_BG2,GFX_BG0,GFX_BG0_SOLID);

   if(check_layer_enabled(f3_bg3_id))
       draw_f3_layer((ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,(ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7,RAM_BG3,GFX_BG0,GFX_BG0_SOLID);

   if(check_layer_enabled(f3_bg6_id))
	draw_f3_pixel(((ReadWord68k(&RAM_SCR4[0])-SCR4_XOFS)>>0),((ReadWord68k(&RAM_SCR4[2])-SCR4_YOFS)>>0),RAM_BG4);

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_bublbob2 =
{
   DrawBubbleSymphony,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_bublbob2[] =
{
   { "bubble_bobble_2", },
   { "bublbob2", },
   { NULL, },
};
#define input_bublbob2 f3_system_inputs
#define sound_bublbob2 f3_sound
#define execute_bublbob2 ExecuteF3SystemFrame_NoInt5
#define dsw_bublbob2 NULL
GAME( bublbob2, "Bubble Bobble II (Ver 2.6O 1994/12/16)", TAITO, 1994, GAME_PLATFORM,
	.input = f3_system_inputs,
	.romsw = bubsymph_romsw,
	.video = &video_bublbob2,
	.exec = ExecuteF3SystemFrame_NoInt5,
	.long_name_jpn = "バブルシンフォニー",
	.board = "D90",
	.sound = f3_sound,
);
CLNEI(bublbob2o,bublbob2,"Bubble Bobble II (Ver 2.5O 1994/10/05)",TAITO,1994,GAME_PLATFORM,
	.romsw = bubsymph_romsw,
	);
CLNEI(bublbob2p,bublbob2,"Bubble Bobble II (Ver 0.0J 1993/12/13, prototype)",TAITO,1994,GAME_PLATFORM);
