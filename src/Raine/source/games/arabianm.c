/******************************************************************************/
/*                                                                            */
/*                 ARABIAN MAGIC (C) 1992 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

// Particularity of this game : tiles/sprites are flipped in rom and it uses flipscreen to display them correctly.
// Now the problem is where flipscreen is... It seems to be in the sprite queue, when a special command bit is set !
// For now I test the detection and keep the old drawing code, but it should be possible to detect this and adapt

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"		// save/load game routines
#include "sasound.h"
extern char mybuff[0x10000];

static struct ROM_INFO rom_arabianm[] =
{
    { "d29-06.ic49", 0x080000, 0xeea07bf3, REGION_GFX2 , 0x000000, LOAD_16_64S },
  { "d29-07.ic50", 0x080000, 0xdb3c094d, REGION_GFX2 , 0x000004, LOAD_16_64S },
  { "d29-08.ic51", 0x080000, 0xd7562851, REGION_GFX2 , 0x000000, LOAD_MASK8 },
  { "d29-03.ic66", 0x100000, 0xaeaff456, REGION_GFX1 , 0x000000, LOAD_8_32S },
  { "d29-04.ic67", 0x100000, 0x01711cfe, REGION_GFX1 , 0x000002, LOAD_8_32S },
  { "d29-05.ic68", 0x100000, 0x9b5f7a17, REGION_GFX1 , 0x000000, LOAD_MASK4 },
  { "d29-23.ic40", 0x40000, 0x89a0c706, REGION_CPU1, 0x000000, LOAD_8_32 },
  { "d29-22.ic38", 0x40000, 0x4afc22a4, REGION_CPU1, 0x000001, LOAD_8_32 },
  { "d29-21.ic36", 0x40000, 0xac32eb38, REGION_CPU1, 0x000002, LOAD_8_32 },
  { "d29-25.ic34", 0x40000, 0xb9b652ed, REGION_CPU1, 0x000003, LOAD_8_32 },
  { "d29-01.ic17", 0x200000, 0x545ac4b3, REGION_SOUND1, 0x000000, LOAD_BE }, // C8 C9 CA CB
  { "d29-02.ic18", 0x100000, 0xed894fe1, REGION_SOUND1, 0x600000, LOAD_BE }, // -std-
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d29-18.rom",  0xd97780df,   "d29-19.rom",  0xb1ad365c),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_arabian_magic_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito Worldwide",       0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_arabianm[] =
{
   { 0x0FFFFF, 0x03, romsw_data_arabian_magic_0 },
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

static void load_arabianm(void)
{
   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_SPR = load_region[REGION_GFX1];
   GFX_BG0 = load_region[REGION_GFX2];
   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x1F75);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG3=RAM+0x33000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;

   SCR0_XOFS=0xF600;
   SCR1_XOFS=0xF700;
   SCR2_XOFS=0xF800;
   SCR3_XOFS=0xF900;

   SCR0_YOFS=0x0780-(16<<7);
   SCR1_YOFS=0x0780-(16<<7);
   SCR2_YOFS=0x0780-(16<<7);
   SCR3_YOFS=0x0780-(16<<7);

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(PCMROM+0x400000,0,0x1fffff);
   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM CHECKSUM
   // ----------------

   WriteWord68k(&ROM[0x00D66],0x4E75);		//	rts

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x0A496],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x0A498],0x4E75);		//	rts

   WriteWord68k(&ROM[0x0A512],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x0A514],0x4E75);		//	rts

   // SPEED HACK#1
   // ------------

   WriteLong68k(&ROM[0x00532],0x4E714E71);

   WriteLong68k(&ROM[0x0023E],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x00242],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x00246],0x60EC);

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_12bit_rgbxxxx);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   init_tc003vcu(0,16);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x20000;
   tc0200obj.RAM_B	= RAM+0x28000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= -16;	// -0x2E;
   tc0200obj.ofs_y	= -16;	// -0x18;

   tc0200obj.cols	= 64;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void clear_arabian_magic(void)
{
   save_eeprom();
}

static void draw_arabian_magic(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
   UINT8 *MAP;

   ClearPaletteMap();

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG0[zz])&0x1FF,
               32,        MAP
            );

      switch(RAM_BG0[zz]&0xC0){
      case 0xC0: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);        break;
      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0x00: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP); break;
      }

   END_SCROLL_512x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         32,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0xC0: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x00: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
      else{
         switch(RAM_BG1[zz]&0xC0){
         case 0xC0: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x00: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
   }

   END_SCROLL_512x512_4_16();
   }


/*
   if(check_layer_enabled(f3_bg6_id)){

   //zz=(ReadWord68k(&RAM_SCR0[8])>>7)+17;
   //zz&=0xFF;				// Y Offset (0-255)
   zz=0;

      MAP_PALETTE_MAPPED_NEW(
         16,
         16,
         MAP
      );

   if(zz<=48){

   zzzz=zz<<2;
   zzzz+=0x50000;
   for(x=64;x<(320+64);x+=8){
      Draw8xH_Trans_Packed_Mapped_Column_Rot(&RAM[zzzz],x,64+16,208,MAP);
      zzzz+=0x400;
   }

   }
   else{

   zzzz=zz<<2;
   zzzz+=0x50000;
   for(x=64;x<(320+64);x+=8){
      Draw8xH_Trans_Packed_Mapped_Column_Rot(&RAM[zzzz],x,64+16,256-zz,MAP);
      Draw8xH_Trans_Packed_Mapped_Column_Rot(&RAM[zzzz+((256-zz)<<2)-0x400],x,64+16+(256-zz),208-(256-zz),MAP);
      zzzz+=0x400;
   }

   }

   }
*/

   render_tc0200obj_mapped_f3system_r180();

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG2[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0xC0: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x00: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
      else{
         switch(RAM_BG2[zz]&0xC0){
         case 0xC0: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x00: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
   }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0xC0: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x00: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
      else{
         switch(RAM_BG3[zz]&0xC0){
         case 0xC0: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x00: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
   }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_r180();
   }
}
static struct VIDEO_INFO video_arabianm =
{
   draw_arabian_magic,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_arabianm[] =
{
   { "arabian_magic", },
   { "arabianm", },
   { NULL, },
};
GAME( arabianm, "Arabian Magic", TAITO, 1992, GAME_BEAT,
	.input = f3_system_inputs,
	.romsw = romsw_arabianm,
	.clear = clear_arabian_magic,
	.video = &video_arabianm,
	.exec = ExecuteF3SystemFrame_NoInt5B,
	.long_name_jpn = "アラビアンマジック",
	.board = "D29",
	.sound = f3_sound,
);

