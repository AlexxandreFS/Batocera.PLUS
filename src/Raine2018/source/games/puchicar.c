/******************************************************************************/
/*									      */
/*		     PUCHI CARAT (C) 1997 TAITO CORPORATION		      */
/*									      */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_puchicar[] =
{
  { "e46.16", 0x80000, 0xcf2accdf, REGION_ROM1, 0x000000, LOAD_8_32 },
  { "e46.15", 0x80000, 0xc32c6ed8, REGION_ROM1, 0x000001, LOAD_8_32 },
  { "e46.14", 0x80000, 0xa154c300, REGION_ROM1, 0x000002, LOAD_8_32 },
  { "e46.13", 0x80000, 0x59fbdf3a, REGION_ROM1, 0x000003, LOAD_8_32 },

  { "e46.06", 0x200000, 0xb74336f2, 0,0,0},
  { "e46.04", 0x200000, 0x463ecc4c, 0,0,0},
  { "e46.05", 0x200000, 0x83a32eee, 0,0,0},
  { "e46.03", 0x200000, 0xeb768193, 0,0,0},
  { "e46.02", 0x200000, 0xfb046018, 0,0,0},
  { "e46.01", 0x200000, 0x34fc2103, 0,0,0},
  { "e46.12", 0x100000, 0x1f3a9851, 0,0,0},
  { "e46.11", 0x100000, 0xe9f10bf1, 0,0,0},
  { "e46.10", 0x100000, 0x1999b76a, 0,0,0},

  LOAD8_16(  REGION_ROM2,  0x000000,  0x40000,
            "e46.19",  0x2624eba0, "e46.20",  0x065e934f),

  { "e46.07", 0x200000, 0xf20af91e, 0,0,0},
  { "e46.07", 0x200000, 0xf20af91e, 0,0,0},
  { "e46.08", 0x200000, 0xf7f96e1d, 0,0,0},
  { "e46.09", 0x200000, 0x824135f8, 0,0,0},
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROMSW_DATA romsw_data_puchicar_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Worldwide",        0x03 },
   { NULL,		       0    },
};

static struct ROMSW_INFO romsw_puchicar[] =
{
   { 0x0FFFFF, 0x03, romsw_data_puchicar_0 },
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

static void load_puchicar(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0xF17A00+0x3F0800))) return;

   GFX_BG0 = GFX+0xF17A00;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e46.06", ROM, 0x200000)) return;       // 16x16 SPRITES ($8000)
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=2;
   if(!load_rom("e46.04", ROM, 0x200000)) return;       // 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0;
   if(!load_rom("e46.02", ROM, 0x200000)) return;       // 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }
   tb=0x800000;
   if(!load_rom("e46.05", ROM, 0x1C5E80)) return;       // 16x16 SPRITES ($717A)
   for(ta=0;ta<0x1C5E80;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0x800002;
   if(!load_rom("e46.03", ROM, 0x1C5E80)) return;       // 16x16 SPRITES
   for(ta=0;ta<0x1C5E80;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=0x800000;
   if(!load_rom("e46.01", ROM, 0x1C5E80)) return;       // 16x16 SPRITES (MASK)
   for(ta=0;ta<0x1C5E80;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("e46.12", ROM, 0xFC200)) return;                // 16x16 TILES ($3F08)
   for(ta=0;ta<0xFC200;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=4;
   if(!load_rom("e46.11", ROM, 0xFC200)) return;                // 16x16 TILES
   for(ta=0;ta<0xFC200;ta+=2,tb+=8){
      WriteWord(&GFX_BG0[tb+0],((ROM[ta+0])|(ROM[ta+0]<<4))&0x0F0F);
      WriteWord(&GFX_BG0[tb+2],((ROM[ta+1])|(ROM[ta+1]<<4))&0x0F0F);
   }
   tb=0;
   if(!load_rom("e46.10", ROM, 0xFC200)) return;                // 16x16 TILES (MASK)
   for(ta=0;ta<0xFC200;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x3F08);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0xF17A);

   FreeMem(ROM);
   ROM = load_region[REGION_CPU1];

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

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xe00004))) return;
   load_be("e46.09",PCMROM,0x200000);
   load_be("e46.08",PCMROM+0x400000,0x200000);
   load_be("e46.07",PCMROM+0x800000,0x200000);
   max_banks_this_game=6; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(PCMROM+0xc00000,0x0,0x200003);
   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x0019C4],0x7F00); 	//	raine	#$00 <read/write eeprom>
   WriteWord68k(&ROM[0x0019C6],0x4ED6); 	//	jmp	(a6)

   // SPEED HACK#1
   // ------------

   // WriteWord68k(&ROM[0x009DC],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x009A4],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x009A6],0x4E71);		//	nop
   WriteWord68k(&ROM[0x009A8],0x4E71);		//	nop
   WriteWord68k(&ROM[0x009AA],0x4E71);		//	nop

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
   tc0200obj.tile_mask	= 0xFFFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON | F3_IOC_TRACKBALL);

   init_m68k();
   setup_sound_68000();
}

static void DrawPuchiCarat(void)
{
   int x16,y16;
   int x,y,ta,zz,zzz,zzzz;
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
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);	 break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP); break;
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

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
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

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
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

   render_tc0200obj_mapped_f3system_b();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_puchicar =
{
   DrawPuchiCarat,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_puchicar[] =
{
   { "puchi_carat", },
   { "puchicar", },
   { "puchicrj", },
   { NULL, },
};
GAME( puchicar, "Puchi Carat", TAITO, 1997, GAME_PUZZLE | GAME_BREAKOUT,
	.input = f3_system_inputs,
	.romsw = romsw_puchicar,
	.video = &video_puchicar,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "プチカラット",
	.board = "E46",
	.sound = f3_sound,
);

