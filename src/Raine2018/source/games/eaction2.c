/******************************************************************************/
/*                                                                            */
/*    ELEVATOR ACTION 2/ELEVATOR ACTION RETURNS (C) 1995 TAITO CORPORATION    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"
#include "emumain.h" // reset game hardware


/* -----------------------------------------------------------------------------
   The old ROM set used by RAINE matches the new set exactly (taken from MAME).
   We now use the MAME set for compatibility. Here are my notes (Logiqx):
   -----------------------------------------------------------------------------

CPU 1
-----
ea2.b62                 e02-10.18               IDENTICAL
ea2.b61                 e02-11.19               IDENTICAL
ea2.b60                 e02-12.20               IDENTICAL
ea2.b63                 ea2.b63                 IDENTICAL

CPU 2
-----
ea2.b66                 e02-13.32               IDENTICAL
ea2.b65                 e02-14.33               IDENTICAL

Sound
-----
ea2.b43                 e02-04.38    [1/4]      IDENTICAL
ea2.b44                 e02-04.38    [2/4]      IDENTICAL
ea2.b45                 e02-04.38    [3/4]      IDENTICAL
ea2.b46                 e02-04.38    [4/4]      IDENTICAL

ea2.b32                 e02-05.39    [1/4]      IDENTICAL
ea2.b33                 e02-05.39    [2/4]      IDENTICAL
ea2.b10                 e02-05.39    [3/4]      IDENTICAL
ea2.b11                 e02-05.39    [4/4]      IDENTICAL

GFX
---
ea2.a8                  e02-03.12    [1/4]      IDENTICAL
ea2.a7                  e02-03.12    [2/4]      IDENTICAL
ea2.a6                  e02-03.12    [3/4]      93.396%     0x75380 onwards is FF in old RAINE set

ea2.a20                 e02-02.8     [1/4]      IDENTICAL
ea2.a19                 e02-02.8     [2/4]      IDENTICAL
ea2.a18                 e02-02.8     [3/4]      91.819%     0x75380 onwards is FF in old RAINE set

ea2.a32                 e02-01.4     [1/4]      IDENTICAL
ea2.a31                 e02-01.4     [2/4]      IDENTICAL
ea2.a30                 e02-01.4     [3/4]      93.396%     0x75380 onwards is FF in old RAINE set

ea2.b7                  e02-08.47    [even 1/2] IDENTICAL
ea2.b6                  e02-08.47    [odd 1/2]  IDENTICAL
ea2.b16                 e02-08.47    [even 2/2] 53.557%     0x43320 onwards is FF in old RAINE set
ea2.b17                 e02-08.47    [odd 2/2]  53.261%     0x43320 onwards is FF in old RAINE set

ea2.b5                  e02-07.45    [even 1/2] IDENTICAL
ea2.b18                 e02-07.45    [even 2/2] 59.327%     0x43320 onwards is FF in old RAINE set
ea2.b4                  e02-07.45    [odd 1/2]  IDENTICAL
ea2.b19                 e02-07.45    [odd 2/2]  55.195%     0x43320 onwards is FF in old RAINE set

ea2.b3                  e02-06.43    [even 1/2] IDENTICAL
ea2.b15                 e02-06.43    [odd 1/2]  61.010%     0x43320 onwards is FF in old RAINE set

   ----------------------------------------------------------------------------- */

static struct ROM_INFO rom_elvact2u[] =
{
   {    "e02-12.20", 0x00080000, 0xea5f5a32, 0, 0, 0, },
   {    "e02-11.19", 0x00080000, 0xbcced8ff, 0, 0, 0, },
   {    "e02-10.18", 0x00080000, 0x72f1b952, 0, 0, 0, },
   {      "ea2.b63", 0x00080000, 0xba9028bd, 0, 0, 0, },
   {    "e02-03.12", 0x00200000, 0xc884ebb5, 0, 0, 0, },
   {     "e02-02.8", 0x00200000, 0xc8e06cfb, 0, 0, 0, },
   {     "e02-01.4", 0x00200000, 0x2ba94726, 0, 0, 0, },
   {    "e02-08.47", 0x00200000, 0x29c9bd02, 0, 0, 0, },
   {    "e02-07.45", 0x00200000, 0x5eeee925, 0, 0, 0, },
   {    "e02-06.43", 0x00200000, 0x4c8726e9, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
               "e02-13.32",  0x80932702,    "e02-14.33",  0x706671a5),
   {    "e02-04.38", 0x00200000, 0xb74307af, 0, 0, 0, },
   {    "e02-05.39", 0x00200000, 0xeb729855, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_elevator_action_2_0[] =
{
   { "Elevator Action Returns (Japan)", 0x01 },
   { "Elevator Action 2 (America)",     0x02 },
   { "Elevator Action Returns",         0x03 },
   { NULL,                              0    },
};

static struct ROMSW_INFO romsw_elvact2u[] =
{
   { 0x1FFFFF, 0x03, romsw_data_elevator_action_2_0 },
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

static void load_elvact2u(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   //if(!(GFX=AllocateMem(0x5D4E00+0x619900))) return;
   if(!(GFX=AllocateMem(0x5D4E00+0x800000))) return;

   GFX_BG0 = GFX+0x5D4E00;		// 16x16 Tiles $8000x$100 ($800000)
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e02-03.12", ROM, 0x80000+0x80000+0x75380)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x80000+0x80000+0x75380;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("e02-02.8", ROM, 0x80000+0x80000+0x75380)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x80000+0x80000+0x75380;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("e02-01.4", ROM, 0x80000+0x80000+0x75380)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x80000+0x80000+0x75380;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e02-08.47", ROM, 0x80000+0x80000+0x43320+0x43320)) return;	// 16x16 TILES
   for(ta=0;ta<0x80000+0x80000+0x43320+0x43320;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("e02-07.45", ROM, 0x80000+0x80000+0x43320+0x43320)) return;	// 16x16 TILES
   for(ta=0;ta<0x80000+0x80000+0x43320+0x43320;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e02-06.43", ROM, 0x80000+0x43320)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x80000;ta+=2){
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
   for(ta=1;ta<0x43320;ta+=2){
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

   memset(GFX+0x296100,0x00,0x00300);			// Remove 'Green' things

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x6199);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x5D4E);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

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
   SCR1_YOFS=0xF400;
   SCR2_YOFS=0xF400;
   SCR3_YOFS=0xFF80;

   if(!load_rom("e02-12.20", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e02-11.19", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e02-10.18", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("ea2.b63", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("e02-04.38",PCMROM+0x000000,0x200000);
   load_be("e02-05.39",PCMROM+0x400000,0x200000);

   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACK
   // -----------

   WriteWord68k(&ROM[0x005DC4],0x7F00);		//	raine	#$00	<eeprom read/write>
   WriteWord68k(&ROM[0x005DC6],0x4ED6);		//	jmp	(a6)
   WriteWord68k(&ROM[0x0102C2],0x4ED6); // jmp (a6) (to disable hardware check)
   WriteWord68k(&ROM[0x010290],0x4ED6); // jmp (a6) (the same... too slow)

   ROM[0x18C8]=0x4E;		// Skip Old
   ROM[0x18C9]=0xF9;		// (JMP $00A000)
   ROM[0x18CA]=0x00;
   ROM[0x18CB]=0x00;
   ROM[0x18CC]=0xA0;
   ROM[0x18CD]=0x00;

   ROM[0xA000]=0x4E;		// Random
   ROM[0xA001]=0xB9;		// (JSR $001044)
   ROM[0xA002]=0x00;
   ROM[0xA003]=0x00;
   ROM[0xA004]=0x10;
   ROM[0xA005]=0x44;

   WriteWord68k(&ROM[0xA006],0x7F02);		//	raine	#$02	<stop cpu>
   WriteWord68k(&ROM[0xA008],0x6100-10);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
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
// Mapper disabled
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearEAction2(void)
{
   save_eeprom();
}

static void DrawEAction2(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
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
         32,
         MAP
      );

      (*Draw16x16_Mapped_Flip_Rot[(RAM_BG0[zz]&0xC0)>>6])(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,MAP);

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

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x7FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         32,
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

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x7FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG2[zz])&0x1FF,
         32,
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

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(232+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x7FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG3[zz])&0x1FF,
         32,
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

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   // object

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_elvact2u =
{
   DrawEAction2,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_elvact2u[] =
{
   { "elevator_action_2", },
   { "eaction2", },
   { "elvact2u", },
   { "elvactr", },
   { "elevator_action_returns", },
   { NULL, },
};
GAME( elvact2u, "Elevator Action 2", TAITO, 1994, GAME_PLATFORM,
	.input = f3_system_inputs,
	.romsw = romsw_elvact2u,
	.clear = ClearEAction2,
	.video = &video_elvact2u,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "エレベーターアクションリターンズ",
	.board = NULL,		// "D??",
	.sound = f3_sound,
);

