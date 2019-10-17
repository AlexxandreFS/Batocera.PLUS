/******************************************************************************/
/*                                                                            */
/*               TAITO CUP FINAL (C) 1992 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_cupfinal[] =
{
   {   "d49-01", 0x00200000, 0x1dc89f1c, 0, 0, 0, },
   {   "d49-02", 0x00200000, 0x1e4c374f, 0, 0, 0, },
   {   "d49-03", 0x00200000, 0xcf9a8727, 0, 0, 0, },
   {   "d49-04", 0x00200000, 0x44b365a9, 0, 0, 0, },
   {   "d49-05", 0x00100000, 0xed894fe1, 0, 0, 0, },
   {   "d49-06", 0x00100000, 0x71ef4ee1, 0, 0, 0, },
   {   "d49-07", 0x00100000, 0xe5655b8f, 0, 0, 0, },
   {   "d49-08", 0x00100000, 0x7d3c6536, 0, 0, 0, },
   {   "d49-09", 0x00080000, 0x257ede01, 0, 0, 0, },
   {   "d49-10", 0x00080000, 0xf587b787, 0, 0, 0, },
   {   "d49-11", 0x00080000, 0x11318b26, 0, 0, 0, },
   {   "d49-13.bin", 0x00020000, 0xccee5e73, 0, 0, 0, },
   {   "d49-14.bin", 0x00020000, 0x2323bf2e, 0, 0, 0, },
   {   "d49-16.bin", 0x00020000, 0x8e73f739, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d49-17",  0x49942466,   "d49-18",  0x9d75b7d4),
   {   "d49-20.bin", 0x00020000, 0x1e9c392c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_taito_cup_final_0[] =
{
   { "Taito Japan (Hat Trick Hero 93)",   0x01 },
   { "Taito America (Hat Trick Hero 93)", 0x02 },
   { "Taito Japan (Taito Cup Finals)",    0x03 },
   { NULL,                                0    },
};

static struct ROMSW_INFO romsw_cupfinal[] =
{
   { 0x07FFFF, 0x03, romsw_data_taito_cup_final_0 },
   { 0,        0,    NULL },
};




static struct ROM_INFO rom_scfinals[] =
{
   {   "d49-01", 0x00200000, 0x1dc89f1c, 0, 0, 0, },
   {   "d49-02", 0x00200000, 0x1e4c374f, 0, 0, 0, },
   {   "d49-03", 0x00200000, 0xcf9a8727, 0, 0, 0, },
   {   "d49-04", 0x00200000, 0x44b365a9, 0, 0, 0, },
   {   "d49-05", 0x00100000, 0xed894fe1, 0, 0, 0, },
   {   "d49-06", 0x00100000, 0x71ef4ee1, 0, 0, 0, },
   {   "d49-07", 0x00100000, 0xe5655b8f, 0, 0, 0, },
   {   "d49-08", 0x00100000, 0x7d3c6536, 0, 0, 0, },
   {   "d49-09", 0x00080000, 0x257ede01, 0, 0, 0, },
   {   "d49-10", 0x00080000, 0xf587b787, 0, 0, 0, },
   {   "d49-11", 0x00080000, 0x11318b26, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d49-17",  0x49942466,   "d49-18",  0x9d75b7d4),
   {       "d68-01", 0x00040000, 0xcb951856, 0, 0, 0, },
   {       "d68-02", 0x00040000, 0x4f94413a, 0, 0, 0, },
   {       "d68-03", 0x00040000, 0xa40be699, 0, 0, 0, },
   {       "d68-04", 0x00040000, 0x4a4e4972, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_super_cup_final_0[] =
{
   { "Taito Japan? (\?\?\?)",    0x01 },
   { "Taito America (\?\?\?)",   0x02 },
   { "Taito Japan (\?\?\?)",     0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_scfinals[] =
{
   { 0x07FFFF, 0x03, romsw_data_super_cup_final_0 },
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

static void load_actual(int romset)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(GFX=AllocateMem(0x1FB300+0xBC7100))) return;
   if(!(ROM=AllocateMem(0x200000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x1FB300;

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
      GFX_SPR[tb+3]|=((tc&0x40)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x10)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x04)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }
   if(!load_rom("d49-08", ROM, 0xF1C40)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xF1C40;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0x40)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x10)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x04)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d49-09", ROM, 0x7ECC0)) return;	// 16x16 TILES ($1FB3)
   for(ta=0;ta<0x7ECC0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d49-10", ROM, 0x7ECC0)) return;	// 16x16 TILES
   for(ta=0;ta<0x7ECC0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d49-11", ROM, 0x7ECC0)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x7ECC0;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x1FB3);
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

   if(romset==0){

   if(!load_rom("d49-13.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d49-14.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d49-16.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d49-20.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   }
   else{

   if(!load_rom("d68-01", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d68-02", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d68-04", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d68-03", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

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

   if(romset==0){

   // FIX ROM CHECKSUM

   WriteWord68k(&ROM[0x0D96],0x4E75);		//	rts

   // EEPROM HACKS

   WriteWord68k(&ROM[0x5CF6],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x5CF8],0x4E75);		//	rts

   WriteWord68k(&ROM[0x5D72],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x5D74],0x4E75);		//	rts

   // SPEED HACK#1

   WriteLong68k(&ROM[0x0562],0x4E714E71);

   WriteLong68k(&ROM[0x025A],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x025E],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x0262],0x60EC);

   WriteWord68k(&ROM[0x0B3A],0x7F02);		// 	raine	#$02 <stop cpu>

   }
   else{

   // FIX ROM CHECKSUM

   WriteWord68k(&ROM[0x00DD0],0x4E75);		//	rts

   // EEPROM HACKS

   WriteWord68k(&ROM[0x05F9C],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x05F9E],0x4E75);		//	rts

   WriteWord68k(&ROM[0x06018],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x0601A],0x4E75);		//	rts

   // SPEED HACK#1

   WriteLong68k(&ROM[0x0056E],0x4E714E71);

   WriteLong68k(&ROM[0x00260],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x00264],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x00268],0x60EC);

   WriteWord68k(&ROM[0x00B6A],0x7F02);		// 	raine	#$02 <stop cpu>

   // INPUT PROBLEM?!?!

   WriteWord68k(&ROM[0x05AF0],0x4E75);		//	rts

   }

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

static void load_cupfinal(void)
{
   load_actual(0);
}

static void load_scfinals(void)
{
   load_actual(1);
}

static void clear_taito_cup_final(void)
{
   save_eeprom();
}

static void draw_taito_cup_final(void)
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
static struct VIDEO_INFO video_scfinals =
{
   draw_taito_cup_final,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_scfinals[] =
{
   { "super_cup_final", },
   { "scupfinl", },
   { "scfinals", },
   { NULL, },
};
GAME( scfinals, "Super Cup Final", TAITO, 1993, GAME_SPORTS | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs_4_player,
	.romsw = romsw_scfinals,
	.clear = clear_taito_cup_final,
	.video = &video_scfinals,
	.exec = ExecuteF3SystemFrame,
	.board = "D68",
	.sound = f3_sound,
);
static struct DIR_INFO dir_cupfinal[] =
{
   { "taito_cup_final", },
   { "cupfinal", },
   { "cup_final", },
   { ROMOF("scfinals"), },
   { CLONEOF("scfinals"), },
   { NULL, },
};
GAME( cupfinal, "Taito Cup Final", TAITO, 1992, GAME_SPORTS | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs_4_player,
	.romsw = romsw_cupfinal,
	.clear = clear_taito_cup_final,
	.video = &video_scfinals,
	.exec = ExecuteF3SystemFrameB,
	.board = "D49",
	.sound = f3_sound,
);

