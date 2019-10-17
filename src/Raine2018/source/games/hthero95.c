/******************************************************************************/
/*                                                                            */
/*              HAT TRICK HERO 95 (C) 1995 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"


static struct ROM_INFO rom_pwrgoal[] =
{
   { "d94-01.bin", 0x00200000, 0x410ffccd, 0, 0, 0, },
   { "d94-02.bin", 0x00200000, 0xf460b9ac, 0, 0, 0, },
   { "d94-03.bin", 0x00200000, 0x95e32072, 0, 0, 0, },
   { "d94-04.bin", 0x00200000, 0x24958b50, 0, 0, 0, },
   { "d94-05.bin", 0x00200000, 0x121c8542, 0, 0, 0, },
   { "d94-06.bin", 0x00200000, 0x0ed1df55, 0, 0, 0, },
   { "d94-07.bin", 0x00200000, 0xc8c95e49, 0, 0, 0, },
   { "d94-08.bin", 0x00200000, 0xbd909caf, 0, 0, 0, },
   { "d94-09.bin", 0x00200000, 0x425e6bec, 0, 0, 0, },
   { "d94-10.bin", 0x00200000, 0xa22563ae, 0, 0, 0, },
   { "d94-11.bin", 0x00200000, 0x61ed83fa, 0, 0, 0, },
   { "d94-12.bin", 0x00100000, 0x47064189, 0, 0, 0, },
   { "d94-13.bin", 0x00100000, 0xcafc68ce, 0, 0, 0, },
   { "d94-14.bin", 0x00100000, 0xb8ba5761, 0, 0, 0, },
   { "d94-16.bin", 0x00040000, 0xc6dbc9c8, 0, 0, 0, },
   { "d94-17.bin", 0x00040000, 0x6009333e, 0, 0, 0, },
   { "d94-18.bin", 0x00040000, 0xb92681c3, 0, 0, 0, },
   { "d94-19.bin", 0x00040000, 0xc93dbcf4, 0, 0, 0, },
   { "d94-20.bin", 0x00040000, 0xf232bf64, 0, 0, 0, },
   { "d94-22.rom", 0x00040000, 0xf672e487, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_hat_trick_hero_95_0[] =
{
   { "Taito Japan (notice)",    0x01 },
   { "Taito America (notice)",  0x02 },
   { "Taito Japan (Power Goal)",0x03 },
   { NULL,                      0    },
};

static struct ROMSW_INFO romsw_pwrgoal[] =
{
   { 0x0FFFFF, 0x02, romsw_data_hat_trick_hero_95_0 },
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

static void load_pwrgoal(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(GFX_SPR=AllocateMem(0x1600000))) return;
   if(!(GFX_BG0=AllocateMem(0x0400000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;

   tb=0;
   if(!load_rom("d94-09.bin", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d94-08.bin", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d94-07.bin", ROM, 0x180000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x180000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }

   tb=2;
   if(!load_rom("d94-06.bin", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d94-05.bin", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d94-04.bin", ROM, 0x180000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x180000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }

   tb=0;
   if(!load_rom("d94-03.bin", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x30)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }
   if(!load_rom("d94-02.bin", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x30)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }
   if(!load_rom("d94-01.bin", ROM, 0x180000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x180000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x30)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d94-14.bin", ROM, 0x100000)) return;	// 16x16 TILES
   for(ta=0;ta<0x100000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d94-13.bin", ROM, 0x100000)) return;	// 16x16 TILES
   for(ta=0;ta<0x100000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d94-12.bin", ROM, 0x100000)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x100000;ta+=2){
      tc=ROM[ta];
      GFX_BG0[tb+7] |= (((tc&0x80)>>7)<<4);
      GFX_BG0[tb+6] |= (((tc&0x40)>>6)<<4);
      GFX_BG0[tb+5] |= (((tc&0x20)>>5)<<4);
      GFX_BG0[tb+4] |= (((tc&0x10)>>4)<<4);
      GFX_BG0[tb+3] |= (((tc&0x08)>>3)<<4);
      GFX_BG0[tb+2] |= (((tc&0x04)>>2)<<4);
      GFX_BG0[tb+1] |= (((tc&0x02)>>1)<<4);
      GFX_BG0[tb+0] |= (((tc&0x01)>>0)<<4);
      tc=ROM[ta+1];
      GFX_BG0[tb+7] |= (((tc&0x80)>>7)<<5);
      GFX_BG0[tb+6] |= (((tc&0x40)>>6)<<5);
      GFX_BG0[tb+5] |= (((tc&0x20)>>5)<<5);
      GFX_BG0[tb+4] |= (((tc&0x10)>>4)<<5);
      GFX_BG0[tb+3] |= (((tc&0x08)>>3)<<5);
      GFX_BG0[tb+2] |= (((tc&0x04)>>2)<<5);
      GFX_BG0[tb+1] |= (((tc&0x02)>>1)<<5);
      GFX_BG0[tb+0] |= (((tc&0x01)>>0)<<5);
      tb+=8;
   }

   FreeMem(ROM);
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x04000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x16000);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG3=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG1=RAM+0x33000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR3=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR1=RAM+0x6A006;

   SCR0_XOFS=(0xF600)+(1<<6);
   SCR3_XOFS=(0xF700)+(1<<6);
   SCR2_XOFS=(0xF800)+(1<<6);
   SCR1_XOFS=(0xF900)+(1<<6);

   SCR0_YOFS=(0x0780-(16<<7));
   SCR3_YOFS=(0x0780-(16<<7));
   SCR2_YOFS=(0x0780-(16<<7));
   SCR1_YOFS=(0x0780-(16<<7));

   if(!load_rom("d94-18.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d94-17.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d94-16.bin", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d94-22.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM CHECKSUM

   WriteWord68k(&ROM[0x00DFC],0x4E75);		//	rts

   // EEPROM HACKS

   WriteWord68k(&ROM[0x0425C],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x0425E],0x4E75);		//	rts

   WriteWord68k(&ROM[0x042D8],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x042DA],0x4E75);		//	rts

   // SPEED HACK#1

//   WriteLong68k(&ROM[0x0562],0x4E714E71);

   WriteLong68k(&ROM[0x023A],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x023E],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x0242],0x60EC);

//   WriteWord68k(&ROM[0x0B3A],0x7F02);		// 	raine	#$02 <stop cpu>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x20, 0x1000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
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
// Mapper disabled
   tc0200obj.tile_mask	= 0x1FFFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= -16;	//-0x18;

   tc0200obj.cols	= 64;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
}

static void clear_hat_trick_hero_95(void)
{
   save_eeprom();
}

static void draw_hat_trick_hero_95(void)
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
               64,        MAP
            );

      (*Draw16x16_Mapped_Flip_Rot[3-((RAM_BG0[zz]&0xC0)>>6)])(&GFX_BG0[ReadWord68k(&RAM_BG0[zz+2])<<8],x,y,MAP);

   END_SCROLL_512x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

   ta=ReadWord68k(&RAM_BG1[zz+2]);
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG1[zz])&0x1FF,
               64,        MAP
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

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

   ta=ReadWord68k(&RAM_BG2[zz+2]);
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG2[zz])&0x1FF,
               64,        MAP
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

   render_tc0200obj_mapped_f3system_r180();

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_512x512_4_16(
      (0-320)-((ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6),
      (0-224)-((ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7)
   );

   START_SCROLL_512x512_4_16_R180(64,64,320,224);

   ta=ReadWord68k(&RAM_BG3[zz+2]);
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               64,        MAP
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
static struct VIDEO_INFO video_pwrgoal =
{
   draw_hat_trick_hero_95,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_pwrgoal[] =
{
   { "hat_trick_hero_95", },
   { "hthero95", },
   { "hath95", },
   { "pwrgoal", },
   { NULL, },
};
GAME( pwrgoal, "Power Goal", TAITO, 1995, GAME_SPORTS | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs_4_player,
	.romsw = romsw_pwrgoal,
	.clear = clear_hat_trick_hero_95,
	.video = &video_pwrgoal,
	.exec = ExecuteF3SystemFrame,
	.board = "D94",
);

