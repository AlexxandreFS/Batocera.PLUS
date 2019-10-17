/******************************************************************************/
/*                                                                            */
/*               INTERNATIONAL CUP '94 (C) 1994 TAITO CORPORATION             */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"

static struct ROM_INFO rom_intcup94[] =
{
   {   "d49-07", 0x00100000, 0xe5655b8f, 0, 0, 0, },
   {   "d49-02", 0x00200000, 0x1e4c374f, 0, 0, 0, },
   {   "d49-03", 0x00200000, 0xcf9a8727, 0, 0, 0, },
   {   "d49-04", 0x00200000, 0x44b365a9, 0, 0, 0, },
   {   "d49-05", 0x00100000, 0xed894fe1, 0, 0, 0, },
   {   "d49-06", 0x00100000, 0x71ef4ee1, 0, 0, 0, },
   {   "d49-01", 0x00200000, 0x1dc89f1c, 0, 0, 0, },
   {   "d49-08", 0x00100000, 0x7d3c6536, 0, 0, 0, },
   {   "d78-01", 0x00080000, 0x543f8967, 0, 0, 0, },
   {   "d78-02", 0x00080000, 0xe8289394, 0, 0, 0, },
   {   "d78-03", 0x00080000, 0xa8bc36e5, 0, 0, 0, },
   {   "d78-05", 0x00020000, 0x5f7fbbbc, 0, 0, 0, },
   {   "d78-06", 0x00020000, 0x42db1d41, 0, 0, 0, },
   {   "d78-07", 0x00020000, 0x8525d990, 0, 0, 0, },
   {   "d78-11", 0x00020000, 0xbb9d2987, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d78-08",  0xa629d07c,   "d78-09",  0x1f0efe01),
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

static void load_intcup94(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(GFX=AllocateMem(0x1F7500+0xBC7100))) return;
   if(!(ROM=AllocateMem(0x200000))) return;

   GFX_BG0=GFX+0x000000;
   GFX_SPR=GFX+0x1F7500;

   tb=0;
   if(!load_rom("d49-01", ROM, 0x200000)) return;	// 16x16 SPRITES ($BC71)
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d49-06", ROM, 0xF1C40)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xF1C40;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d49-02", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d49-07", ROM, 0xF1C40)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xF1C40;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d49-03", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3] |= (((tc&0x40)>>6)<<4);
      GFX_SPR[tb+2] |= (((tc&0x10)>>4)<<4);
      GFX_SPR[tb+1] |= (((tc&0x04)>>2)<<4);
      GFX_SPR[tb+0] |= (((tc&0x01)>>0)<<4);
      tb+=4;
   }
   if(!load_rom("d49-08", ROM, 0xF1C40)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xF1C40;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3] |= (((tc&0x40)>>6)<<4);
      GFX_SPR[tb+2] |= (((tc&0x10)>>4)<<4);
      GFX_SPR[tb+1] |= (((tc&0x04)>>2)<<4);
      GFX_SPR[tb+0] |= (((tc&0x01)>>0)<<4);
      tb+=4;
   }

   tb=0;
   if(!load_rom("d78-01", ROM, 0x77B00)) return;	// 16x16 TILES ($1F75)
   for(ta=0;ta<0x77B00;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d78-02", ROM, 0x77B00)) return;	// 16x16 TILES
   for(ta=0;ta<0x77B00;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d78-03", ROM, 0x77B00)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x77B00;ta+=2){
      tc=ROM[ta];
      GFX_BG0[tb+7] |= (((tc&0x80)>>7)<<4);
      GFX_BG0[tb+6] |= (((tc&0x40)>>6)<<4);
      GFX_BG0[tb+5] |= (((tc&0x20)>>5)<<4);
      GFX_BG0[tb+4] |= (((tc&0x10)>>4)<<4);
      GFX_BG0[tb+3] |= (((tc&0x08)>>3)<<4);
      GFX_BG0[tb+2] |= (((tc&0x04)>>2)<<4);
      GFX_BG0[tb+1] |= (((tc&0x02)>>1)<<4);
      GFX_BG0[tb+0] |= (((tc&0x01)>>0)<<4);
      tb+=8;
   }

   FreeMem(ROM);
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x1F75);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0xBC71);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x80000);

   RAM_BG1=RAM+0x30000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x32000;
   RAM_BG0=RAM+0x33000;

   RAM_SCR1=RAM+0x6A000;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A004;
   RAM_SCR0=RAM+0x6A006;

   SCR1_XOFS=(0xF600)+(1<<6);
   SCR2_XOFS=(0xF700)+(1<<6);
   SCR3_XOFS=(0xF800)+(1<<6);
   SCR0_XOFS=(0xF900)+(1<<6);

   SCR1_YOFS=(0x0780-(16<<7));
   SCR2_YOFS=(0x0780-(16<<7));
   SCR3_YOFS=(0x0780-(16<<7));
   SCR0_YOFS=(0x0780-(16<<7));

   if(!load_rom("d78-07", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d78-06", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d78-05", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d78-11", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xa00000))) return;
   load_be("d49-04",PCMROM,0x200000);
   load_be("d49-05",PCMROM+0x600000,0x100000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0x400000,0,0x1fffff);
   memset(PCMROM+0x800000,0,0x1fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM CHECKSUM
   // ----------------

   WriteWord68k(&ROM[0x0DD4],0x4E75);		//	rts

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x646C],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x646E],0x4E75);		//	rts

   WriteWord68k(&ROM[0x64E8],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x64EA],0x4E75);		//	rts

   // SPEED HACK#1
   // ------------

   //WriteLong68k(&ROM[0x0562],0x4E714E71);

   WriteLong68k(&ROM[0x0262],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x0266],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x026A],0x60EC);

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
   tc0200obj.tile_mask	= 0xFFFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= -16;	//-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawIntCup94(void)
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
               32,        MAP
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

   ta=ReadWord68k(&RAM_BG3[zz+2]);
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

   render_tc0200obj_mapped_f3system_r180();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_r180();
   }
}
static struct VIDEO_INFO video_intcup94 =
{
   DrawIntCup94,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_intcup94[] =
{
   { "international_cup_94", },
   { "intcup94", },
   { ROMOF("scfinals"), },
   { CLONEOF("scfinals"), },
   { NULL, },
};
GAME( intcup94, "International Cup 94", TAITO, 1994, GAME_SPORTS | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs,
	.video = &video_intcup94,
	.exec = ExecuteF3SystemFrameB,
	.board = "D49",
	.sound = f3_sound,
);

