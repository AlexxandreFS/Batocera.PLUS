/******************************************************************************/
/*                                                                            */
/*                 KYUKYOKU TIGER 2 (C) 1995 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_ktiger2[] =
{
   {   "e15-03.bin", 0x00100000, 0xbe45a52f, 0, 0, 0, },
   {   "e15-02.bin", 0x00200000, 0x2ea7f2bd, 0, 0, 0, },
   {   "e15-07.bin", 0x00100000, 0x8164f7ee, 0, 0, 0, },
   {   "e15-04.bin", 0x00200000, 0x6ea8d9bd, 0, 0, 0, },
   {   "e15-05.bin", 0x00200000, 0x3e5da5f6, 0, 0, 0, },
   {   "e15-06.bin", 0x00200000, 0xb182a3e1, 0, 0, 0, },
   {   "e15-09.bin", 0x00100000, 0x07c29f60, 0, 0, 0, },
   {   "e15-08.bin", 0x00200000, 0x4bdb2bf3, 0, 0, 0, },
   {   "e15-10.bin", 0x00200000, 0xd8c96b00, 0, 0, 0, },
   {   "e15-11.bin", 0x00040000, 0xa706a286, 0, 0, 0, },
   {   "e15-12.bin", 0x00040000, 0x59d832f2, 0, 0, 0, },
   {   "e15-13.bin", 0x00040000, 0x0f03daf7, 0, 0, 0, },
   {   "e15-14.bin", 0x00040000, 0xb527b733, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "e15-15.bin",  0x22126dfb,   "e15-16.bin",  0xf8b58ea0),
   {   "e15-01.bin", 0x00100000, 0x85421aac, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_kyukyoku_tiger_2_0[] =
{
   { "Kyukyoku Tiger 2 (Japan)",               0x01 },
   { "Twin Cobra 2 (USA)",               0x02 },
   { "Twin Cobra 2 (World)",               0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_ktiger2[] =
{
   { 0x0FFFFF, 0x01, romsw_data_kyukyoku_tiger_2_0 },
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

static void load_ktiger2(void)
{
   int ta,tb;

   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0x800000+0x400000))) return;

   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e15-04.bin", ROM, 0x200000)) return;	// 16x16 SPRITES ($8000)
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=2;
   if(!load_rom("e15-02.bin", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0x800000;
   if(!load_rom("e15-03.bin", ROM, 0x100000)) return;	// 16x16 SPRITES ($2000)
   for(ta=0;ta<0x100000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0x800002;
   if(!load_rom("e15-01.bin", ROM, 0x100000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   if(!(GFX_BG0=AllocateMem(0x800000+0x400000))) return;

   tb=0;
   if(!load_rom("e15-10.bin", ROM, 0x200000)) return;	// 16x16 TILES ($8000)
   for(ta=0;ta<0x200000;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=4;
   if(!load_rom("e15-08.bin", ROM, 0x200000)) return;	// 16x16 TILES
   for(ta=0;ta<0x200000;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=0x800000;
   if(!load_rom("e15-09.bin", ROM, 0x100000)) return;	// 16x16 TILES ($2000)
   for(ta=0;ta<0x100000;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=0x800004;
   if(!load_rom("e15-07.bin", ROM, 0x100000)) return;	// 16x16 TILES
   for(ta=0;ta<0x100000;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }

   FreeMem(ROM);

   Rotate16x16(GFX_SPR,0xC000);
   Flip16x16_X(GFX_SPR,0xC000);
   Rotate16x16(GFX_BG0,0xC000);
   Flip16x16_X(GFX_BG0,0xC000);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0xC000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0xC000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x31000;
   RAM_BG1=RAM+0x33000;
   RAM_BG2=RAM+0x32000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A002;
   RAM_SCR1=RAM+0x6A006;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A000;

   SCR0_XOFS=0xF740;
   SCR1_XOFS=0xF940;
   SCR2_XOFS=0xF840;
   SCR3_XOFS=0xF640;

   SCR0_YOFS=0xFD80;
   SCR1_YOFS=0xFD80;
   SCR2_YOFS=0xFD80;
   SCR3_YOFS=0xFD80;

   if(!load_rom("e15-14.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e15-13.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e15-12.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("e15-11.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   Rotate8x8_4bpp(ROM+0x48000,0x2000>>5);
   Flip8x8_4bpp_X(ROM+0x48000,0x2000>>5);

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("e15-05.bin",PCMROM,0x200000);
   load_be("e15-06.bin",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x001180],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x001182],0x4E75);		//	rts

   WriteWord68k(&ROM[0x0011F4],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x0011F6],0x4E75);		//	rts

   // SPEED HACKS
   // -----------

   WriteLong68k(&ROM[0x0005AC],0x7F024E71);	//	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x0005B0],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x0005E6],0x7F024E71);	//	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x0005EA],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x00065A],0x7F024E71);	//	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x00065E],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x000684],0x7F024E71);	//	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x000688],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x001BE6],0x7F024E71);	//	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x001BEA],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x001C0E],0x7F024E71);	//	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x001C12],0x4E714E71);	//	nop

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1B;


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
   tc0200obj.tile_mask	= 0xFFFF;

   // [kayamon] - apparently this layer needs a strange offset.
   // god knows why. never mind.
   //tc0200obj.ofs_x   = -16;      //(0-0x0C)-16;    // 0x0C 0x1F
   //tc0200obj.ofs_y   = 0;     //0-0x2E;   //(0-0x1F)+15; // 0x1F 0x2E
   tc0200obj.ofs_x   = -40;    // 0x0C 0x1F
   tc0200obj.ofs_y   = -77;   //(0-0x1F)+15; // 0x1F 0x2E

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearKyukyokuTiger2(void)
{
   save_eeprom();
}

static void DrawKyukyokuTiger2(void)
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

   START_SCROLL_512x512_4_16(64,64,320,224);

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG0[zz])&0x1FF,
               16,        MAP
            );

      ta=ReadWord68k(&RAM_BG0[zz+2]);
      if(ta>=0xC000) ta=0;

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

   START_SCROLL_512x512_4_16(64,64,320,224);

   ta=ReadWord68k(&RAM_BG1[zz+2]);
   if((ta!=0)&&(ta<0xC000)){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG1[zz])&0x1FF,
               16,        MAP
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

   START_SCROLL_512x512_4_16(64,64,320,224);

   ta=ReadWord68k(&RAM_BG2[zz+2]);
   if((ta!=0)&&(ta<0xC000)){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG2[zz])&0x1FF,
               16,        MAP
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

   START_SCROLL_512x512_4_16(64,64,320,224);

   ta=ReadWord68k(&RAM_BG3[zz+2]);
   if((ta!=0)&&(ta<0xC000)){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               16,        MAP
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

/*

E15-01.BIN  | 16x16 Tiles block#1 odd     | 1MB - Half OK, not sure if the rest is ok or unused
E15-02.BIN  | 16x16 Sprites block#0 odd   | 2MB - All OK
E15-03.BIN  | 16x16 Tiles block#1 even    | 1MB - Half OK, not sure if the rest is ok or unused
E15-04.BIN  | 16x16 Sprites block#0 even  | 2MB - All OK
E15-05.BIN  | 16-bit sample data
E15-06.BIN  | 16-bit sample data
E15-07.BIN  | 16x16 Tiles block#1 odd     | 1MB - Half OK, not sure if the rest is ok or unused
E15-08.BIN  | 16x16 Tiles block#0 odd     | 2MB - All OK
E15-09.BIN  | 16x16 Tiles block#1 even    | 1MB - Half OK, not sure if the rest is ok or unused
E15-10.BIN  | 16x16 Tiles block#0 even    | 2MB - All OK
E15-11.BIN  | Main 68020 byte#3
E15-12.BIN  | Main 68020 byte#2
E15-13.BIN  | Main 68020 byte#1
E15-14.BIN  | Main 68020 byte#0
E15-15.BIN  | Sound 68000 even
E15-16.BIN  | Sound 68000 odd
FILE_ID.DIZ | Message of J-Rom

*/
static struct VIDEO_INFO video_ktiger2 =
{
   DrawKyukyokuTiger2,
   224,
   320,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ktiger2[] =
{
   { "kyukyoku_tiger_2", },
   { "ktiger2", },
   { "tcobra2", },
   { NULL, },
};
GAME( ktiger2, "Kyukyoku Tiger 2", TAITO, 1995, GAME_SHOOT,
	.input = f3_system_inputs,
	.romsw = romsw_ktiger2,
	.clear = ClearKyukyokuTiger2,
	.video = &video_ktiger2,
	.exec = ExecuteF3SystemFrameB,
	.board = "E15",
	.sound = f3_sound,
);

