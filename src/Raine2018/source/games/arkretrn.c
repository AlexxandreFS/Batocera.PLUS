/******************************************************************************/
/*									      */
/*		 ARKANOID RETURNS (C) 1997 TAITO CORPORATION		      */
/*									      */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"           // save/load game routines
#include "sasound.h"


static struct ROM_INFO rom_arkretrn[] =
{
   {	   "e36.01", 0x00040000, 0x54b9b2cd, 0, 0, 0, },
   {	   "e36.02", 0x00040000, 0x694eda31, 0, 0, 0, },
   {	   "e36.03", 0x00040000, 0x1ea8558b, 0, 0, 0, },
   {	   "e36.04", 0x00200000, 0x2250959b, 0, 0, 0, },
   {	   "e36.05", 0x00080000, 0xdb18bce2, 0, 0, 0, },
   {	   "e36.06", 0x00080000, 0x110ab729, 0, 0, 0, },
   {	   "e36.07", 0x00080000, 0x266bf1c1, 0, 0, 0, },
   {	   "e36.08", 0x00040000, 0xaa699e1b, 0, 0, 0, },
   {	   "e36.09", 0x00040000, 0xf16985e0, 0, 0, 0, },
   {	   "e36.10", 0x00040000, 0xc940dba1, 0, 0, 0, },
   {	   "e36.11", 0x00040000, 0xb50cfb92, 0, 0, 0, },
   {	   "e36.12", 0x00040000, 0x3bae39be, REGION_ROM2, 0x000000, LOAD_8_16, },
   {	   "e36.13", 0x00040000, 0x94448e82, REGION_ROM2, 0x000001, LOAD_8_16, },
   {	       NULL,	      0,	  0, 0, 0, 0, },
};


static struct ROMSW_DATA romsw_data_arkanoid_returns_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito Worldwide",       0x03 },
   { NULL,		      0    },
};

static struct ROMSW_INFO romsw_arkretrn[] =
{
   { 0x0FFFFF, 0x03, romsw_data_arkanoid_returns_0 },
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

static void load_arkretrn(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x0BAF00+0x19A500))) return;

   GFX_BG0 = GFX+0x0BAF00;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e36.03", ROM, 0x2EBC0)) return;                // 16x16 SPRITES ($BAF)
   for(ta=0;ta<0x2EBC0;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("e36.02", ROM, 0x2EBC0)) return;                // 16x16 SPRITES
   for(ta=0;ta<0x2EBC0;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("e36.01", ROM, 0x2EBC0)) return;                // 16x16 SPRITES (MASK)
   for(ta=0;ta<0x2EBC0;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("e36.07", ROM, 0x66940)) return;                // 16x16 TILES ($19A5)
   for(ta=0;ta<0x66940;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("e36.06", ROM, 0x66940)) return;                // 16x16 TILES
   for(ta=0;ta<0x66940;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e36.05", ROM, 0x66940)) return;                // 16x16 TILES (MASK)
   for(ta=0;ta<0x66940;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x19A5);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x0BAF);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x34000;
   RAM_BG3=RAM+0x36000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;

   SCR0_XOFS=0xF600;
   SCR1_XOFS=0xF700;
   SCR2_XOFS=0xF800;
   SCR3_XOFS=0xF900;

   SCR0_YOFS=0xFF80;
   SCR1_YOFS=0xFF80;
   SCR2_YOFS=0xFF80;
   SCR3_YOFS=0xFF80;

   if(!load_rom("e36.11", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e36.10", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e36.09", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("e36.08", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x400000))) return;
   load_be("e36.04",PCMROM+0x000000,0x200000);
   max_banks_this_game=1;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x001814],0x7F00); 	//	raine	#$00 <read/write eeprom>
   WriteWord68k(&ROM[0x001816],0x4ED6); 	//	jmp	(a6)

   // SPEED HACK#1
   // ------------

// WriteWord68k(&ROM[0x00960],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x00928],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x0092A],0x4E71);		//	nop
   WriteWord68k(&ROM[0x0092C],0x4E71);		//	nop
   WriteWord68k(&ROM[0x0092E],0x4E71);		//	nop

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
   tc0200obj.tile_mask	= 0x0FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON | F3_IOC_TRACKBALL);

   init_m68k();
   setup_sound_68000();
}

static void ClearArkRetrn(void)
{
   save_eeprom();
}

static void DrawArkRetrn(void)
{
   int x,y,ta,zz,zzz,zzzz,x16,y16;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_1024x512_4_16(
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
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);	 break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP); break;
      }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
	 ReadWord68k(&RAM_BG1[zz])&0x1FF,
	 64,
	 MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
	 switch(RAM_BG1[zz]&0xC0){
	 case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
	 }
      }
      else{
	 switch(RAM_BG1[zz]&0xC0){
	 case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);	  break;
	 case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
	 case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
	 case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
	 }
      }
   }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
	 ReadWord68k(&RAM_BG2[zz])&0x1FF,
	 64,
	 MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
	 switch(RAM_BG2[zz]&0xC0){
	 case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
	 }
      }
      else{
	 switch(RAM_BG2[zz]&0xC0){
	 case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);	  break;
	 case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
	 case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
	 case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
	 }
      }
   }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }
/*
   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
	 ReadWord68k(&RAM_BG3[zz])&0x1FF,
	 64,
	 MAP
      );

      if(GFX_BG0_SOLID[ta]==0){
	 switch(RAM_BG3[zz]&0xC0){
	 case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);	break;
	 case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
	 }
      }
      else{
	 switch(RAM_BG3[zz]&0xC0){
	 case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,MAP);	  break;
	 case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
	 case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,MAP);  break;
	 case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,MAP); break;
	 }
      }
   }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }
*/
   render_tc0200obj_mapped_f3system_b();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_arkretrn =
{
   DrawArkRetrn,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_arkretrn[] =
{
   { "arkanoid_returns", },
   { "arkretrn", },
   { NULL, },
};
GAME( arkretrn, "Arkanoid Returns", TAITO, 1997, GAME_BREAKOUT,
	.input = f3_system_inputs,
	.romsw = romsw_arkretrn,
	.clear = ClearArkRetrn,
	.video = &video_arkretrn,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "アルカノイド　リターンズ",
	.board = "E36",
	.sound = f3_sound,
);

