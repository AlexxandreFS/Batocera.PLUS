/******************************************************************************/
/*                                                                            */
/*                 ARABIAN MAGIC (C) 1992 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"		// save/load game routines
#include "sasound.h"
extern char mybuff[0x10000];


static struct ROM_INFO rom_arabianm[] =
{
   {   "d29-06.rom", 0x00080000, 0xeea07bf3, 0, 0, 0, },
   {   "d29-02.rom", 0x00100000, 0xed894fe1, 0, 0, 0, },
   {   "d29-03.rom", 0x00100000, 0xaeaff456, 0, 0, 0, },
   {   "d29-04.rom", 0x00100000, 0x01711cfe, 0, 0, 0, },
   {   "d29-05.rom", 0x00100000, 0x9b5f7a17, 0, 0, 0, },
   {   "d29-01.rom", 0x00200000, 0x545ac4b3, 0, 0, 0, },
   {   "d29-07.rom", 0x00080000, 0xdb3c094d, 0, 0, 0, },
   {   "d29-08.rom", 0x00080000, 0xd7562851, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d29-18.rom",  0xd97780df,   "d29-19.rom",  0xb1ad365c),
   {   "d29-21.rom", 0x00040000, 0xac32eb38, 0, 0, 0, },
   {   "d29-22.rom", 0x00040000, 0x4afc22a4, 0, 0, 0, },
   {   "d29-23.rom", 0x00040000, 0x89a0c706, 0, 0, 0, },
   {   "d29-25.rom", 0x00040000, 0xb9b652ed, 0, 0, 0, },
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
   int ta,tb,tc;
   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   if(!(GFX=AllocateMem(0x1F7500+0x400000))) return;

   GFX_BG0=GFX+0x000000;
   GFX_SPR=GFX+0x1F7500;

   tb=0;
   if(!load_rom("d29-03.rom", ROM, 0x100000)) return;	// 16x16 SPRITES ($4000)
   for(ta=0;ta<0x100000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d29-04.rom", ROM, 0x100000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d29-05.rom", ROM, 0x100000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x100000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x30)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d29-06.rom", ROM, 0x7DD40)) return;	// 16x16 TILES ($1F75)
   for(ta=0;ta<0x7DD40;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d29-07.rom", ROM, 0x7DD40)) return;	// 16x16 TILES
   for(ta=0;ta<0x7DD40;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d29-08.rom", ROM, 0x7DD40)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x7DD40;ta+=2){
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

   if(!load_rom("d29-23.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d29-22.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d29-21.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d29-25.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("d29-01.rom",PCMROM,0x200000);
   load_be("d29-02.rom",PCMROM+0x600000,0x100000);
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

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   //tc0003vcu.mapper	= &Map_12bit_RGBxxxxx;
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 224;
   tc0003vcu.scr_x	= 0;
   tc0003vcu.scr_y	= 16;

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x20000;
   tc0200obj.RAM_B	= RAM+0x28000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 64;
   tc0200obj.bmp_y	= 64;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   //tc0200obj.mapper	= &Map_12bit_RGBxxxxx;
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

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

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

