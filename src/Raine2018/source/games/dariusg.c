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


static struct ROM_INFO rom_dariusg[] =
{
   {   "d87-01.bin", 0x00200000, 0x3848a110, 0, 0, 0, },
   {   "d87-02.bin", 0x00200000, 0x9250abae, 0, 0, 0, },
   {   "d87-03.bin", 0x00200000, 0x4be1666e, 0, 0, 0, },
   {   "d87-04.bin", 0x00200000, 0x2616002c, 0, 0, 0, },
   {   "d87-05.bin", 0x00200000, 0x4e5891a9, 0, 0, 0, },
   {   "d87-06.bin", 0x00200000, 0x3b97a07c, 0, 0, 0, },
   {   "d87-08.bin", 0x00200000, 0x76d23602, 0, 0, 0, },
   {   "d87-09.bin", 0x00080000, 0x6170382d, 0, 0, 0, },
   {   "d87-10.bin", 0x00080000, 0x4149f66f, 0, 0, 0, },
   {   "d87-11.bin", 0x00080000, 0xf7bed18e, 0, 0, 0, },
   {   "d87-12.bin", 0x00080000, 0xde78f328, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d87-13.bin",  0x15b1fff4,   "d87-14.bin",  0xeecda29a),
   {   "d87-17.bin", 0x00200000, 0xe601d63e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
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
   {   "d87-01.bin", 0x00200000, 0x3848a110, 0, 0, 0, },
   {   "d87-02.bin", 0x00200000, 0x9250abae, 0, 0, 0, },
   {   "d87-03.bin", 0x00200000, 0x4be1666e, 0, 0, 0, },
   {   "d87-04.bin", 0x00200000, 0x2616002c, 0, 0, 0, },
   {   "d87-05.bin", 0x00200000, 0x4e5891a9, 0, 0, 0, },
   {   "d87-06.bin", 0x00200000, 0x3b97a07c, 0, 0, 0, },
   {   "d87-08.bin", 0x00200000, 0x76d23602, 0, 0, 0, },
   { "dge_mpr0.bin", 0x00080000, 0xc5bd135c, 0, 0, 0, },
   { "dge_mpr1.bin", 0x00080000, 0xbc030f6f, 0, 0, 0, },
   { "dge_mpr2.bin", 0x00080000, 0x7be23e23, 0, 0, 0, },
   { "dge_mpr3.bin", 0x00080000, 0x1c1e24a7, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d87-13.bin",  0x15b1fff4,   "d87-14.bin",  0xeecda29a),
   {   "d87-17.bin", 0x00200000, 0xe601d63e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
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

static void load_darius_gaiden(int version)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0x7EF000+0x7F3600))) return;

   GFX_BG0 = GFX+0x7EF000;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("d87-03.bin", ROM, 0x1FBC00)) return;	// 16x16 SPRITES ($7EF0)
   for(ta=0;ta<0x1FBC00;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d87-04.bin", ROM, 0x1FBC00)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x1FBC00;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d87-05.bin", ROM, 0x1FBC00)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x1FBC00;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d87-06.bin", ROM, 0x1FCD80)) return;	// 16x16 TILES ($7F36)
   for(ta=0;ta<0x1FCD80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d87-17.bin", ROM, 0x1FCD80)) return;	// 16x16 TILES
   for(ta=0;ta<0x1FCD80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d87-08.bin", ROM, 0x1FCD80)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x1FCD80;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x7F36);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x7EF0);

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

   if(!load_rom_index(10, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom_index(9, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom_index(8, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom_index(7, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xa00000))) return;
   load_be("d87-01.bin",PCMROM,0x200000);
   load_be("d87-02.bin",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0x800000,0,0x1fffff);

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
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= 0;	//-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void load_dariusg() {
  load_darius_gaiden(0);
}

static void load_dariusgx() {
  load_darius_gaiden(1);
}

static void draw_darius_gaiden(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
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
         32,
         MAP
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,MAP); break;
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

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

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
GAME( dariusg, "Darius Gaiden", TAITO, 1994, GAME_SHOOT,
	.input = f3_system_inputs,
	.romsw = romsw_dariusg,
	.video = &video_dariusg,
	.exec = ExecuteF3SystemFrame,
	.long_name_jpn = "ダライアス外伝",
	.board = "D87",
	.sound = f3_sound,
);
static struct DIR_INFO dir_dariusgx[] =
{
   { "darius_gaiden_extra", },
   { "dariusgx", },
   { ROMOF("dariusg"), },
   { CLONEOF("dariusg"), },
   { NULL, },
};
GAME( dariusgx, "Darius Gaiden Extra", TAITO, 1994, GAME_SHOOT,
	.input = f3_system_inputs,
	.romsw = romsw_dariusg,
	.video = &video_dariusg,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "ダライアス外伝 Extra",
	.board = "D87",
	.sound = f3_sound,
);

