/******************************************************************************/
/*                                                                            */
/*                   GRID SEEKER (C) 1995 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_gseeker[] =
{
   {   "d40_04.rom", 0x00100000, 0xcd2ac666, 0, 0, 0, },
   {   "d40_02.rom", 0x00100000, 0xed894fe1, 0, 0, 0, },
   {   "d40_03.rom", 0x00100000, 0xbcd70efc, 0, 0, 0, },
   {   "d40_01.rom", 0x00200000, 0xee312e95, 0, 0, 0, },
   {   "d40_05.rom", 0x00100000, 0xbe6eec8f, 0, 0, 0, },
   {   "d40_06.rom", 0x00100000, 0xa822abe4, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d40_07.rom",  0x7e9b26c2,   "d40_08.rom",  0x9c926a28),
   {   "d40_10.rom", 0x00040000, 0x1e659ac5, 0, 0, 0, },
   {   "d40_11.rom", 0x00040000, 0x85e701d2, 0, 0, 0, },
   {   "d40_12.rom", 0x00040000, 0x884055fb, 0, 0, 0, },
   {   "d40_14.rom", 0x00040000, 0xd9a76bd9, 0, 0, 0, },
   {   "d40_15.rom", 0x00080000, 0x50555125, 0, 0, 0, },
   {   "d40_16.rom", 0x00080000, 0x3f9bbe1e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_grid_seeker_0[] =
{
   { "Taito 1",               0x01 },
   { "Taito 2",               0x02 },
   { "Taito 3",               0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_gseeker[] =
{
   { 0x0FFFFF, 0x03, romsw_data_grid_seeker_0 },
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

static void load_gseeker(void)
{
   int ta,tb;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x3E2200+0x400000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x3E2200;

   if(!load_rom("d40_03.rom", ROM, 0x100000)) return;	// 16x16 SPRITES ($4000)
   tb=2;
   for(ta=0;ta<0x80000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0x200000;
   for(ta=0x80000;ta<0x100000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   if(!load_rom("d40_04.rom", ROM, 0x100000)) return;	// 16x16 SPRITES
   tb=0;
   for(ta=0x80000;ta<0x100000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0x200002;
   for(ta=0;ta<0x80000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   tb=0;
   if(!load_rom("d40_05.rom", ROM, 0xF8880)) return;	// 16x16 TILES ($3E22)
   for(ta=0;ta<0xF8880;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=4;
   if(!load_rom("d40_06.rom", ROM, 0xF8880)) return;	// 16x16 TILES
   for(ta=0;ta<0xF8880;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }

   Rotate16x16(GFX_BG0,0x3E22);
   Flip16x16_X(GFX_BG0,0x3E22);
   Rotate16x16(GFX_SPR,0x4000);
   Flip16x16_X(GFX_SPR,0x4000);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x3E22);
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

   SCR0_XOFS=0xFFD8 <<6;
   SCR1_XOFS=0xFFDC <<6;
   SCR2_XOFS=0xFFE0 <<6;
   SCR3_XOFS=0xFFE4 <<6;

   SCR0_YOFS=0x0000 <<7;
   SCR1_YOFS=0x0000 <<7;
   SCR2_YOFS=0x0000 <<7;
   SCR3_YOFS=0x0000 <<7;

   if(!load_rom("d40_12.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d40_11.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d40_10.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d40_14.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   for(ta=0x0C76;ta<0x3876;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   Rotate8x8_4bpp(ROM+0x00C76,0x2C00>>5);
   Flip8x8_4bpp_X(ROM+0x00C76,0x2C00>>5);

   for(ta=0x0C76;ta<0x3876;ta+=4){			// swap words
       tb=ReadWord(&ROM[ta]);
       WriteWord(&ROM[ta],ReadWord(&ROM[ta+2]));
       WriteWord(&ROM[ta+2],tb);
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xa00000))) return;
   load_be("d40_01.rom",PCMROM,0x200000);
   load_be("d40_02.rom",PCMROM+0x600000,0x100000);
   max_banks_this_game=4; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(PCMROM+0x400000,0,0x1fffff);
   memset(PCMROM+0x800000,0,0x1fffff);
   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM ERROR
   // -------------

   WriteWord68k(&ROM[0x000AEC],0x4E75);		//	nop

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x003BF6],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x003BF8],0x4E75);		//	rts

   WriteWord68k(&ROM[0x003C72],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x003C74],0x4E75);		//	rts

   // COLOUR RAM IS TRASHING INPUTS
   // -----------------------------

   WriteLong68k(&ROM[0x005042],0x4EF80300);	//	jmp	$0300.w

   WriteLong68k(&ROM[0x000300],0x48E770E0);	//
   WriteLong68k(&ROM[0x000304],0x41F90044);	//
   WriteLong68k(&ROM[0x000308],0x000045F9);	//
   WriteLong68k(&ROM[0x00030C],0x00444000);	//
   WriteLong68k(&ROM[0x000310],0x26025341);	//
   WriteLong68k(&ROM[0x000314],0x02820000);	//
   WriteLong68k(&ROM[0x000318],0x7FFF0283);	//
   WriteLong68k(&ROM[0x00031C],0x00003FFF);	//
   WriteLong68k(&ROM[0x000320],0x21912800);	//
   WriteLong68k(&ROM[0x000324],0x25993800);	//
   WriteLong68k(&ROM[0x000328],0x58825883);	//
   WriteLong68k(&ROM[0x00032C],0x51C9FFE6);	//
   WriteLong68k(&ROM[0x000330],0x4CDF070E);	//
   WriteLong68k(&ROM[0x000334],0x4E750000);	//

   // SPEED HACKS
   // -----------

   WriteLong68k(&ROM[0x0043A4],0x4EF80380);	//	jmp	$0380.w

   WriteLong68k(&ROM[0x000380],0x4EB83DB2);	//	jsr	$3DB2.w
   WriteLong68k(&ROM[0x000384],0x526DAD94);	//	addq	#1,(-21100,a5)
   WriteWord68k(&ROM[0x000388],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x00038A],0x6100-12);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 224;
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
   tc0200obj.bmp_w	= 224;
   tc0200obj.bmp_h	= 320;
// Mapper disabled
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-1;			//-0x2E;
   tc0200obj.ofs_y	= 0-(0x2D+0x40+37);	//-0x1F;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearGridSeeker(void)
{
   save_eeprom();
}

static void DrawGridSeeker(void)
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
   MAKE_SCROLL_512x512_4_16_R(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         16,
         MAP
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP); break;
      }

      zz=(zz&0x0F80)|((zz-4)&0x7F);
   }
   zzzz=(zzzz-0x080)&0xFFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16_R(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         16,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
      else{
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
   }

      zz=(zz&0x0F80)|((zz-4)&0x7F);
   }
   zzzz=(zzzz-0x080)&0xFFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_512x512_4_16_R(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG2[zz])&0x1FF,
         16,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
      else{
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
   }

      zz=(zz&0x0F80)|((zz-4)&0x7F);
   }
   zzzz=(zzzz-0x080)&0xFFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_512x512_4_16_R(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG3[zz])&0x1FF,
         16,
         MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
      else{
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
   }

      zz=(zz&0x0F80)|((zz-4)&0x7F);
   }
   zzzz=(zzzz-0x080)&0xFFF;
   zz=zzzz;
   }
   }

   render_tc0200obj_mapped_f3system_r270_b();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_r270();
   }
}
static struct VIDEO_INFO video_gseeker =
{
   DrawGridSeeker,
   224,
   320,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_gseeker[] =
{
   { "grid_seeker", },
   { "gridseek", },
   { "gseeker", },
   { NULL, },
};
GAME( gseeker, "Grid Seeker", TAITO, 1992, GAME_SHOOT,
	.input = f3_system_inputs,
	.romsw = romsw_gseeker,
	.clear = ClearGridSeeker,
	.video = &video_gseeker,
	.exec = ExecuteF3SystemFrame_NoInt5B,
	.long_name_jpn = "グリッドシーカー",
	.board = "D40",
	.sound = f3_sound,
);

