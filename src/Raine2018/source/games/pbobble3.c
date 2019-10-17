/******************************************************************************/
/*                                                                            */
/*                 PUZZLE BOBBLE 3 (C) 1995 TAITO CORPORATION                 */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_pbobble3[] =
{
   {   "pb3_02.rom", 0x00100000, 0x437391d3, 0, 0, 0, },
  { "e29-03.rom", 0x200000, 0xa4371658, REGION_SOUND1 , 0x000000, LOAD_BE },
  { "e29-05.rom", 0x200000, 0xe33c1234, REGION_SOUND1 , 0x400000, LOAD_BE },
  /* Every sound bank is correctly detected by the f3 system, except for the
   * last one of e24-04.rom, which must be placed at the end (default location)
   * Maybe there is something broken in the f3system implementation (related to
   * the lsb & msb probably). Anyway having the roms in this order fixes the
   * problem */
  { "e29-04.rom", 0x200000, 0xd1f42457, REGION_SOUND1 , 0x800000, LOAD_BE },
   {   "pb3_01.rom", 0x00100000, 0x52547c77, 0, 0, 0, },
   {   "pb3_06.rom", 0x00100000, 0xc16184f8, 0, 0, 0, },
   {   "pb3_07.rom", 0x00100000, 0xfca2ea9b, 0, 0, 0, },
   {   "pb3_08.rom", 0x00100000, 0x7040a3d5, 0, 0, 0, },
  { "e29-12.rom", 0x80000, 0x9eb19a00, REGION_ROM1, 0x000000, LOAD_8_32 },
  { "e29-11.rom", 0x80000, 0xe54ada97, REGION_ROM1, 0x000001, LOAD_8_32 },
  { "e29-10.rom", 0x80000, 0x1502a122, REGION_ROM1, 0x000002, LOAD_8_32 },
  { "e29-16.rom", 0x80000, 0xaac293da, REGION_ROM1, 0x000003, LOAD_8_32 },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "pb3_13.rom",  0x1ef551ef,   "pb3_14.rom",  0x7ee7e688),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_puzzle_bobble_3_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Worldwide",        0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_pbobble3[] =
{
   { 0x1FFFFF, 0x03, romsw_data_puzzle_bobble_3_0 },
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

static void load_pbobble3(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0x3CD600+0x3B0400))) return;

   GFX_BG0 = GFX+0x3CD600;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("pb3_02.rom", ROM, 0xF3580)) return;	// 16x16 SPRITES ($3CD6)
   for(ta=0;ta<0xF3580;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("pb3_01.rom", ROM, 0xF3580)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xF3580;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }

   tb=0;
   if(!load_rom("pb3_08.rom", ROM, 0xEC100)) return;	// 16x16 TILES ($3B04)
   for(ta=0;ta<0xEC100;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("pb3_07.rom", ROM, 0xEC100)) return;	// 16x16 TILES
   for(ta=0;ta<0xEC100;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("pb3_06.rom", ROM, 0xEC100)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xEC100;ta+=2){
      tc=ROM[ta];
      GFX_BG0[tb+7]|=((tc&0x80)>>7)<<4;
      GFX_BG0[tb+6]|=((tc&0x40)>>6)<<4;
      GFX_BG0[tb+5]|=((tc&0x20)>>5)<<4;
      GFX_BG0[tb+4]|=((tc&0x10)>>4)<<4;
      GFX_BG0[tb+3]|=((tc&0x08)>>3)<<4;
      GFX_BG0[tb+2]|=((tc&0x04)>>2)<<4;
      GFX_BG0[tb+1]|=((tc&0x02)>>1)<<4;
      GFX_BG0[tb+0]|=((tc&0x01)>>0)<<4;
      tc=ROM[ta+1];
      GFX_BG0[tb+7]|=((tc&0x80)>>7)<<5;
      GFX_BG0[tb+6]|=((tc&0x40)>>6)<<5;
      GFX_BG0[tb+5]|=((tc&0x20)>>5)<<5;
      GFX_BG0[tb+4]|=((tc&0x10)>>4)<<5;
      GFX_BG0[tb+3]|=((tc&0x08)>>3)<<5;
      GFX_BG0[tb+2]|=((tc&0x04)>>2)<<5;
      GFX_BG0[tb+1]|=((tc&0x02)>>1)<<5;
      GFX_BG0[tb+0]|=((tc&0x01)>>0)<<5;
      tb+=8;
   }

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x3B04);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3CD6);

   // Setup 68020 Memory Map
   // ----------------------


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
   FreeMem(ROM);
   ROM = load_region[REGION_ROM1];
   AddF3MemoryMap(0x200000);

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   max_banks_this_game=5; // get_region_size(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // PROTECTION HACK
   // ---------------

   WriteLong68k(&ROM[0x00B98E],0x001E8000);
   W24[0x1E] = ROM+0x1E0000;

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x00466A],0x7F00);		//	raine	#$00 <read/write eeprom>
   WriteWord68k(&ROM[0x00466C],0x4ED6);		//	jmp	(a6)

   WriteWord68k(&ROM[0x065F14],0x7F00);		//	raine	#$00 <read/write eeprom>
   WriteWord68k(&ROM[0x065F16],0x4ED6);		//	jmp	(a6)

   // SPEED HACK#1
   // ------------

   WriteWord68k(&ROM[0x0014AA],0x4EF9);		//	jmp	$1E8100
   WriteLong68k(&ROM[0x0014AC],0x001E8100);	//

   WriteWord68k(&ROM[0x1E8100],0x4EB9);		//	jsr	$159A
   WriteLong68k(&ROM[0x1E8102],0x0000159A);	//

   WriteWord68k(&ROM[0x1E8106],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x1E8108],0x6100-10);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 232;
   tc0003vcu.scr_x	= 0;
   tc0003vcu.scr_y	= 0;

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x20000;
   tc0200obj.RAM_B	= RAM+0x28000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 64;
   tc0200obj.bmp_y	= 64;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 232;
   tc0200obj.mapper	= &Map_24bit_xRGB;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawPuzzleBobble3(void)
{
   int x,y,z,ta,zz,zzz,zzzz,x16,y16;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         64,
         MAP
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP); break;
      }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         64,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
      else{
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
   }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG2[zz])&0x1FF,
         64,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
      else{
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
   }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG3[zz])&0x1FF,
         64,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
      else{
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
         }
      }
   }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

   // object

   render_tc0200obj_mapped_f3system_b();

   if(check_layer_enabled(f3_bg5_id)){
   zz=0;
   for(y=64;y<232+64;y+=8){
   for(x=64;x<320+64;x+=8){
      z=RAM[0x3C001+zz];
      if((z!=0)&&(z!=0x05)){		// 0x05='black' rectangle

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x3C000+zz]>>1)&0x3F,
         16,
         MAP
      );

         if((RAM[0x3C000+zz]&0x01)!=0){
            Draw8x8_Trans_Packed_Mapped_Rot(&RAM[0x3E000+(z<<5)],x,y,MAP);
         }
         else{
            Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&RAM[0x3E000+(z<<5)],x,y,MAP);
         }

      }
      zz+=2;
   }
   zz+=(128-80);
   }
   }
}
static struct VIDEO_INFO video_pbobble3 =
{
   DrawPuzzleBobble3,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_pbobble3[] =
{
   { "puzzle_bobble_3", },
   { "pbobble3", },
   { NULL, },
};
GAME( pbobble3, "Puzzle Bobble 3", TAITO, 1996, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_pbobble3,
	.video = &video_pbobble3,
	.exec = ExecuteF3SystemFrame_int2,
	.long_name_jpn = "パズルボブル３",
	.board = "E29",
	.sound = f3_sound,
);

