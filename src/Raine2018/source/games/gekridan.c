/******************************************************************************/
/*                                                                            */
/*                    GEKIRINDAN (C) 1995 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_gekirido[] =
{
   {   "e11-01.bin", 0x00200000, 0xc2cd1069, 0, 0, 0, },
   {   "e11-02.bin", 0x00200000, 0x5722a83b, 0, 0, 0, },
   {   "e11-03.bin", 0x00200000, 0xf73877c5, 0, 0, 0, },
   {   "e11-04.bin", 0x00200000, 0xe0ff4fb1, 0, 0, 0, },
   {   "e11-05.bin", 0x00200000, 0xa4d08cf1, 0, 0, 0, },
   {   "e11-06.bin", 0x00200000, 0x200ce305, 0, 0, 0, },
   {   "e11-07.bin", 0x00200000, 0xef018607, 0, 0, 0, },
   {   "e11-08.bin", 0x00200000, 0x907f69d3, 0, 0, 0, },
   {   "e11-09.bin", 0x00040000, 0xb4e17ef4, 0, 0, 0, },
   {   "e11-10.bin", 0x00040000, 0x8795e6ba, 0, 0, 0, },
   {   "e11-11.bin", 0x00040000, 0x2284a08e, 0, 0, 0, },
   {   "e11-12.bin", 0x00040000, 0x6a7aaacf, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "e11-13.bin",  0x51a11ff7,   "e11-14.bin",  0xdce2ba91),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_gekirindan_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",         0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_gekirido[] =
{
   { 0x0FFFFF, 0x01, romsw_data_gekirindan_0 },
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

static void load_gekirido(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(GFX=AllocateMem(0x698900+0x544800))) return;
   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x1A6240))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x698900;

   if(!load_rom("E11-03.bin", ROM, 0x151200)) return;	// 16x16 SPRITES ($5448)
   tb=0;
   for(ta=0;ta<0x151200;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   if(!load_rom("E11-02.bin", ROM, 0x151200)) return;	// 16x16 SPRITES
   tb=2;
   for(ta=0;ta<0x151200;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0;
   if(!load_rom("E11-01.bin", ROM, 0x151200)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x151200;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0x40)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x10)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x04)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("E11-08.bin", ROM, 0x1A6240)) return;	// 16x16 TILES ($6989)
   for(ta=0;ta<0x1A6240;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=4;
   if(!load_rom("E11-07.bin", ROM, 0x1A6240)) return;	// 16x16 TILES
   for(ta=0;ta<0x1A6240;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=0;
   if(!load_rom("E11-06.bin", ROM, 0x1A6240)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x1A6240;ta+=2){
      tc=ROM[ta];
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

   FreeMem(ROM);
   if(!(ROM=AllocateMem(0x100000))) return;

   Rotate16x16(GFX_BG0,0x6989);
   Flip16x16_X(GFX_BG0,0x6989);
   Rotate16x16(GFX_SPR,0x5448);
   Flip16x16_X(GFX_SPR,0x5448);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x6989);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x5448);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG3=RAM+0x30000;
   RAM_BG2=RAM+0x31000;
   RAM_BG1=RAM+0x32000;
   RAM_BG0=RAM+0x33000;

   RAM_SCR3=RAM+0x6A000;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR0=RAM+0x6A006;

   SCR3_XOFS=0xF900;
   SCR2_XOFS=0xF800;
   SCR1_XOFS=0xF700;
   SCR0_XOFS=0xF600;

   SCR3_YOFS=0xFF80;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xFF80;

   if(!load_rom("E11-12.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("E11-11.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("E11-10.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("E11-09.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   for(ta=0x104F4;ta<0x124F4;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   Rotate8x8_4bpp(ROM+0x104F4,0x2000>>5);
   Flip8x8_4bpp_X(ROM+0x104F4,0x2000>>5);

   for(ta=0x104F4;ta<0x124F4;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   for(ta=0x8EBD8;ta<0x8EC78;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   Rotate8x8_4bpp(ROM+0x8EBD8,0x00A0>>5);
   Flip8x8_4bpp_X(ROM+0x8EBD8,0x00A0>>5);

   for(ta=0x8EBD8;ta<0x8EC78;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   for(ta=0xF6820;ta<0xF6D60;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   Rotate8x8_4bpp(ROM+0xF6820,0x0540>>5);
   Flip8x8_4bpp_X(ROM+0xF6820,0x0540>>5);

   for(ta=0xF6820;ta<0xF6D60;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("e11-04.bin",PCMROM,0x200000);
   load_be("e11-05.bin",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACK
   // -----------

   WriteWord68k(&ROM[0x0044F8],0x7F00);		//	raine	#$00	<eeprom read/write>
   WriteWord68k(&ROM[0x0044FA],0x4ED6);		//	jmp	(a6)

   // SPEED HACKS
   // -----------

   WriteWord68k(&ROM[0x002340],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x002342],0x6100-10);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 232;
   tc0003vcu.bmp_h	= 320;
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
   tc0200obj.bmp_w	= 232;
   tc0200obj.bmp_h	= 320;
// Mapper disabled
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;	//-16;		//(0-0x0C)-16;		// 0x0C 0x1F
   tc0200obj.ofs_y	= 0;		//0-0x2E;	//(0-0x1F)+15;	// 0x1F 0x2E

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearGekirindan(void)
{
   save_eeprom();
}

static void DrawGekirindan(void)
{
   UINT8 *MAP;
   int x16,y16;
   int x,y,zz,zzz,zzzz;
   int ta;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG0[zz])&0x1FF,
               32,        MAP
            );

      ta=ReadWord68k(&RAM_BG0[zz+2])&0x7FFF;

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
      }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x7FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG1[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
         }
      }
      else{
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
         }
      }
   }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x7FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG2[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
         }
      }
      else{
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
         }
      }
   }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x7FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
         }
      }
      else{
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],y,(320+128-16)-x,MAP); break;
         }
      }
   }

   END_SCROLL_512x512_4_16();
   }

   render_tc0200obj_mapped_f3system_r270_b();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_r270();
   }
}
static struct VIDEO_INFO video_gekirido =
{
   DrawGekirindan,
   232,
   320,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_gekirido[] =
{
   { "gekirindan", },
   { "gekridan", },
   { "gekirido", },
   { NULL, },
};
GAME( gekirido, "Gekirindan", TAITO, 1995, GAME_SHOOT,
	.input = f3_system_inputs,
	.romsw = romsw_gekirido,
	.clear = ClearGekirindan,
	.video = &video_gekirido,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "‹t—Ø’e",
	.board = "E11",
	.sound = f3_sound,
);

