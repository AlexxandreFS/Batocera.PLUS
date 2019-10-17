#define DRV_DEF_SOUND f3_sound
/******************************************************************************/
/*                                                                            */
/*                    TWIN QIX (C) 1995 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_twinqix[] =
{
   {   "mpr0-0.b63", 0x00040000, 0xa4c44c11, 0, 0, 0, },
   {   "mpr0-1.b62", 0x00040000, 0x531f9447, 0, 0, 0, },
   {   "mpr0-2.b61", 0x00040000, 0x45a70987, 0, 0, 0, },
   {   "mpr0-3.b60", 0x00040000, 0x1a63d0de, 0, 0, 0, },
   {   "obj0-0.a08", 0x00080000, 0xc6ea845c, 0, 0, 0, },
   {   "obj0-1.a20", 0x00080000, 0x8c12b7fb, 0, 0, 0, },
   {   "scr0-0.b07", 0x00080000, 0x9a1b9b34, 0, 0, 0, },
   {   "scr0-1.b06", 0x00080000, 0xe9bef879, 0, 0, 0, },
   {   "scr0-2.b05", 0x00080000, 0xcac6854b, 0, 0, 0, },
   {   "scr0-3.b04", 0x00080000, 0xce063034, 0, 0, 0, },
   {   "scr0-4.b03", 0x00080000, 0xd32280fe, 0, 0, 0, },
   {   "scr0-5.b02", 0x00080000, 0xfdd1a85b, 0, 0, 0, },
   {    "snd-0.b43", 0x00080000, 0xad5405a9, 0, 0, 0, },
   {    "snd-1.b44", 0x00080000, 0x274864af, 0, 0, 0, },
   {   "snd-14.b10", 0x00080000, 0x26312451, 0, 0, 0, },
   {   "snd-15.b11", 0x00080000, 0x2edaa9dc, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "spr0-1.b66",  0x4b20e99d,   "spr0-0.b65",  0x2569eb30),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_twin_qix_0[] =
{
   { "Taito Japan (Japanese gfx)", 0x01 },
   { "Taito America",              0x02 },
   { "Taito Japan",                0x03 },
   { NULL,                         0    },
};

static struct ROMSW_INFO romsw_twinqix[] =
{
   { 0x0FFFFF, 0x03, romsw_data_twin_qix_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;
static UINT8 *RAM_BG4;		// PIXEL

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;
static UINT8 *RAM_SCR4;		// PIXEL

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;
static UINT32 SCR4_XOFS;		// PIXEL

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;
static UINT32 SCR4_YOFS;		// PIXEL

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_twinqix(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x2BE800+0x134D00))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x2BE800;

   tb=0;
   if(!load_rom("obj0-0.a08", ROM, 0x4D340)) return;	// 16x16 SPRITES ($134D)
   for(ta=0;ta<0x4D340;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   tb=2;
   if(!load_rom("obj0-1.a20", ROM, 0x4D340)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x4D340;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   tb=0;
   if(!load_rom("scr0-0.b07", ROM, 0x57D00)) return;	// 16x16 TILES
   for(ta=0;ta<0x57D00;ta++){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      tb+=6;
   }
   tb=2;
   if(!load_rom("scr0-1.b06", ROM, 0x57D00)) return;	// 16x16 TILES
   for(ta=0;ta<0x57D00;ta++){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      tb+=6;
   }
   tb=4;
   if(!load_rom("scr0-2.b05", ROM, 0x57D00)) return;	// 16x16 TILES
   for(ta=0;ta<0x57D00;ta++){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      tb+=6;
   }
   tb=6;
   if(!load_rom("scr0-3.b04", ROM, 0x57D00)) return;	// 16x16 TILES
   for(ta=0;ta<0x57D00;ta++){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      tb+=6;
   }
   tb=0;
   if(!load_rom("scr0-4.b03", ROM, 0x57D00)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x57D00;ta++){
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
   tb=0;
   if(!load_rom("scr0-5.b02", ROM, 0x57D00)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x57D00;ta++){
      tc=ROM[ta];
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x2BE8);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x134D);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x34000;
   RAM_BG3=RAM+0x36000;
   RAM_BG4=RAM+0x50000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR0_XOFS=0xF600;
   SCR1_XOFS=0xF700;
   SCR2_XOFS=0xF800;
   SCR3_XOFS=0xF900;
   SCR4_XOFS=0x0029-1;

   SCR0_YOFS=0xFF80;
   SCR1_YOFS=0xFF80;
   SCR2_YOFS=0xFF80;
   SCR3_YOFS=0xFF80;
   SCR4_YOFS=0x001F-1;

   if(!load_rom("mpr0-3.b60", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("mpr0-2.b61", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("mpr0-1.b62", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("mpr0-0.b63", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x600000))) return;
   load_be("snd-0.b43",PCMROM,0x80000);
   load_be("snd-14.b10",PCMROM+0x100000,0x80000);
   load_be("snd-1.b44",PCMROM+0x200000,0x80000);
   load_be("snd-15.b11",PCMROM+0x300000,0x80000);
   max_banks_this_game=2; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0x400000,0,0x1fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   ROM[0xECF46]=0x7F;		// move.b #$00,$BB0000
   ROM[0xECF47]=0x00;		// (EEP-ROM READ HACK)

   ROM[0xECF48]=0x4E;		// rts
   ROM[0xECF49]=0x75;

   ROM[0xECFC2]=0x7F;		// move.b #$01,$BB0000
   ROM[0xECFC3]=0x01;		// (EEP-ROM WRITE HACK)

   ROM[0xECFC4]=0x4E;		// rts
   ROM[0xECFC5]=0x75;

   ROM[0xE9A4C]=0x7F;		// move.b #$02,$BB0000
   ROM[0xE9A4D]=0x02;		// (SPEED HACK)
   ROM[0xE9A4E]=0x4E;
   ROM[0xE9A4F]=0x71;
   ROM[0xE9A50]=0x4E;
   ROM[0xE9A51]=0x71;
   ROM[0xE9A52]=0x4E;
   ROM[0xE9A53]=0x71;

   ROM[0xE9916]=0x4E;		// Skip Old
   ROM[0xE9917]=0xF9;		// (JMP $F8000)
   ROM[0xE9918]=0x00;
   ROM[0xE9919]=0x0F;
   ROM[0xE991A]=0x80;
   ROM[0xE991B]=0x00;

   ROM[0xF8000]=0x52;		// addq	#1,(-32476,a5)
   ROM[0xF8001]=0x6D;
   ROM[0xF8002]=0x81;
   ROM[0xF8003]=0x24;

   ROM[0xF8004]=0x7F;		// move.b #$02,$BB0000
   ROM[0xF8005]=0x02;		// (SPEED HACK)
   ROM[0xF8006]=0x4E;
   ROM[0xF8007]=0x71;
   ROM[0xF8008]=0x4E;
   ROM[0xF8009]=0x71;
   ROM[0xF800A]=0x4E;
   ROM[0xF800B]=0x71;

   ROM[0xF800C]=0x4E;		// Go back
   ROM[0xF800D]=0xF9;		// (JMP $E990C)
   ROM[0xF800E]=0x00;
   ROM[0xF800F]=0x0E;
   ROM[0xF8010]=0x99;
   ROM[0xF8011]=0x0C;

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 224;
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
   tc0200obj.bmp_h	= 224;
// Mapper disabled
   tc0200obj.tile_mask	= 0x1FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x1F;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawTwinQix(void)
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

   START_SCROLL_1024x512_4_16(64,64,320,224);

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

   END_SCROLL_1024x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){

   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,224);

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

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg2_id)){

   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,224);

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

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg3_id)){
   if(ReadWord68k(&RAM[0x4623E])==0x0F07){

   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,224);

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

   END_SCROLL_1024x512_4_16();
   }
   }

   if(check_layer_enabled(f3_bg6_id)){

      MAP_PALETTE_MAPPED_NEW(
         16,
         16,
         MAP
      );

   zzzz=0x50000;
   for(x=64;x<(320+64);x+=8){
      Draw8xH_Trans_Packed_Mapped_Rot(&RAM[zzzz],x,64,224,MAP);
      zzzz+=0x400;
   }
   }

   // object

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_twinqix =
{
   DrawTwinQix,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_twinqix[] =
{
   { "twin_qix", },
   { "twinqix", },
   { NULL, },
};
GAME( twinqix, "Twin Qix", TAITO, 1995, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_twinqix,
	.video = &video_twinqix,
	.exec = ExecuteF3SystemFrame_NoInt5,
	.long_name_jpn = "ツインクイックス",
	.board = NULL /* "E??" */,
);

