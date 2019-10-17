/******************************************************************************/
/*                                                                            */
/*         BUBBLE BOBBLE 2/BUBBLE SYMPHONY (C) 1994 TAITO CORPORATION         */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"

/*******************
   BUBBLE BOBBLE 2
 *******************/


static struct ROM_INFO rom_bublbob2[] =
{
   {       "d90.12", 0x00040000, 0x9e523996, REGION_ROM1, 0x000000, LOAD_8_32, },
   {       "d90.11", 0x00040000, 0xedfdbb7f, REGION_ROM1, 0x000001, LOAD_8_32, },
   {       "d90.10", 0x00040000, 0x8e957d3d, REGION_ROM1, 0x000002, LOAD_8_32, },
   {       "d90.17", 0x00040000, 0x711f1894, REGION_ROM1, 0x000003, LOAD_8_32, },
   {       "d90.01", 0x00100000, 0x8aedb9e5, 0, 0, 0, },
   {       "d90.02", 0x00100000, 0x5ab04ca2, 0, 0, 0, },
   {       "d90.03", 0x00100000, 0x6fa894a1, 0, 0, 0, },
   {       "d90.04", 0x00200000, 0xfeee5fda, 0, 0, 0, },
   {       "d90.05", 0x00200000, 0xc192331f, 0, 0, 0, },
   {       "d90.06", 0x00100000, 0x166a72b8, 0, 0, 0, },
   {       "d90.07", 0x00100000, 0xb436b42d, 0, 0, 0, },
   {       "d90.08", 0x00100000, 0x25a4fb2c, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "d90.13",  0x6762bd90,       "d90.14",  0x8e33357e),
   {           NULL,          0,          0, 0, 0, 0, },
};

/*
static struct ROMSW_DATA romsw_data_bubble_bobble_2[] =
{
   { "Taito Japan (Japanese)",        0x01 },
   { "Taito America",                 0x02 },
   { "Taito World (Bubble Bobble 2)", 0x03 },
   { NULL,                     0    },
};
*/



/*******************
   BUBBLE SYMPHONY
 *******************/


static struct ROM_INFO rom_bubsymph[] =
{
   {       "d90.12", 0x00040000, 0x9e523996, REGION_ROM1, 0x000000, LOAD_8_32, },
   {       "d90.11", 0x00040000, 0xedfdbb7f, REGION_ROM1, 0x000001, LOAD_8_32, },
   {       "d90.10", 0x00040000, 0x8e957d3d, REGION_ROM1, 0x000002, LOAD_8_32, },
   {       "d90.09", 0x00040000, 0x3f2090b7, REGION_ROM1, 0x000003, LOAD_8_32, },
   {       "d90.01", 0x00100000, 0x8aedb9e5, 0, 0, 0, },
   {       "d90.02", 0x00100000, 0x5ab04ca2, 0, 0, 0, },
   {       "d90.03", 0x00100000, 0x6fa894a1, 0, 0, 0, },
   {       "d90.04", 0x00200000, 0xfeee5fda, 0, 0, 0, },
   {       "d90.05", 0x00200000, 0xc192331f, 0, 0, 0, },
   {       "d90.06", 0x00100000, 0x166a72b8, 0, 0, 0, },
   {       "d90.07", 0x00100000, 0xb436b42d, 0, 0, 0, },
   {       "d90.08", 0x00100000, 0x25a4fb2c, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "d90.13",  0x6762bd90,       "d90.14",  0x8e33357e),
   {           NULL,          0,          0, 0, 0, 0, },
};


/**********************
   BUBBLE SYMPHONY US
 **********************/


static struct ROM_INFO rom_bubsympu[] =
{
   {       "d90.12", 0x00040000, 0x9e523996, REGION_ROM1, 0x000000, LOAD_8_32, },
   {       "d90.11", 0x00040000, 0xedfdbb7f, REGION_ROM1, 0x000001, LOAD_8_32, },
   {       "d90.10", 0x00040000, 0x8e957d3d, REGION_ROM1, 0x000002, LOAD_8_32, },
   {      "d90.usa", 0x00040000, 0x06182802, REGION_ROM1, 0x000003, LOAD_8_32, },
   {       "d90.01", 0x00100000, 0x8aedb9e5, 0, 0, 0, },
   {       "d90.02", 0x00100000, 0x5ab04ca2, 0, 0, 0, },
   {       "d90.03", 0x00100000, 0x6fa894a1, 0, 0, 0, },
   {       "d90.04", 0x00200000, 0xfeee5fda, 0, 0, 0, },
   {       "d90.05", 0x00200000, 0xc192331f, 0, 0, 0, },
   {       "d90.06", 0x00100000, 0x166a72b8, 0, 0, 0, },
   {       "d90.07", 0x00100000, 0xb436b42d, 0, 0, 0, },
   {       "d90.08", 0x00100000, 0x25a4fb2c, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "d90.13",  0x6762bd90,       "d90.14",  0x8e33357e),
   {           NULL,          0,          0, 0, 0, 0, },
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

static void load_bublbob2(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x3E8D00+0x336E00))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   GFX_BG0 = GFX+0x3E8D00;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("d90.03", TMP, 0xFA340)) return;	// 16x16 SPRITES ($3E8D)
   for(ta=0;ta<0xFA340;ta++){
      GFX[tb++]=TMP[ta]&15;
      GFX[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d90.02", TMP, 0xFA340)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xFA340;ta++){
      GFX[tb++]=TMP[ta]&15;
      GFX[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d90.01", TMP, 0xFA340)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xFA340;ta++){
      tc=TMP[ta];
      GFX[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX[tb+2]|=((tc&0x30)>>4)<<4;
      GFX[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }

   memset(GFX+0x1C8900,0x00,0x100);

   tb=0;
   if(!load_rom("d90.08", TMP, 0xCDB80)) return;	// 16x16 TILES ($336E)
   for(ta=0;ta<0xCDB80;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d90.07", TMP, 0xCDB80)) return;	// 16x16 TILES
   for(ta=0;ta<0xCDB80;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d90.06", TMP, 0xCDB80)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xCDB80;ta+=2){
      tc=TMP[ta];
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

   FreeMem(TMP);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x336E);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3E8D);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG3=RAM+0x30000;
   RAM_BG2=RAM+0x32000;
   RAM_BG0=RAM+0x34000;
   RAM_BG1=RAM+0x36000;
   RAM_BG4=RAM+0x50000;

   RAM_SCR3=RAM+0x6A000;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR0=RAM+0x6A004;
   RAM_SCR1=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR3_XOFS=(0xFFD8)<<6;
   SCR2_XOFS=(0xFFDC)<<6;
   SCR0_XOFS=(0xFFE0)<<6;
   SCR1_XOFS=(0xFFE4)<<6;
   SCR4_XOFS=(0x0029-1)<<0;

   SCR3_YOFS=(0xFFFF)<<7;
   SCR2_YOFS=(0xFFFF)<<7;
   SCR0_YOFS=(0xFFFF)<<7;
   SCR1_YOFS=(0xFFFF)<<7;
   SCR4_YOFS=(0x001F-1)<<0;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("d90.04",PCMROM,0x200000);
   load_be("d90.05",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x0ECD6A],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x0ECD6C],0x4E75);		//	rts

   WriteWord68k(&ROM[0x0ECDE6],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x0ECDE8],0x4E75);		//	rts

   // SPEED HACKS
   // -----------

   WriteWord68k(&ROM[0x0E9A3A],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x0E9A3C],0x4E71);		//	nop
   WriteWord68k(&ROM[0x0E9A3E],0x4E71);		//	nop

   WriteWord68k(&ROM[0x0E9902],0x4EF9);		//	jmp	$FFA00
   WriteLong68k(&ROM[0x0E9904],0x000FFA00);	//

   WriteLong68k(&ROM[0x0FFA00],0x526D8124);	//	addq	#1,(-32476,a5)
   WriteWord68k(&ROM[0x0FFA04],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x0FFA06],0x4EF9);		//	jmp	$E98F8
   WriteLong68k(&ROM[0x0FFA08],0x000E98F8);	//

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
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
   tc0200obj.mapper	= &Map_24bit_xRGB;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x1F;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawBubbleSymphony(void)
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
               32,        MAP
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
               32,        MAP
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
               32,        MAP
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
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,224);

      ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
      if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               32,        MAP
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

   if(check_layer_enabled(f3_bg6_id)){
   zzz=0-((ReadWord68k(&RAM_SCR4[0])-SCR4_XOFS)>>0);
   zzzz=((zzz&0x1F8)>>3)<<10;			// X Offset (16-1024)
   x16=7-(zzz&7);				// X Offset (0-15)
   zz=17-((ReadWord68k(&RAM_SCR4[2])-SCR4_YOFS)>>0);
   zz&=0xFF;					// Y Offset (0-255)
   zzzz+=zz<<2;					// Y Offset (0-255)

   zzzz&=0xFFFF;
   MAP_PALETTE_MAPPED_NEW(
			  16, // ???
            16,     MAP
         );

   if(zz<=48){

   for(x=56+x16;x<(320+64);x+=8){
     Draw8xH_Trans_Packed_Mapped_FlipY_Rot(&RAM_BG4[zzzz],x,64+16,208,MAP);
      zzzz=(zzzz+0x400)&0xFFFF;
   }

   }
   else{

   for(x=56+x16;x<(320+64);x+=8){
     Draw8xH_Trans_Packed_Mapped_FlipY_Rot(&RAM_BG4[zzzz],x,64+16,256-zz,MAP);
     Draw8xH_Trans_Packed_Mapped_FlipY_Rot(&RAM_BG4[zzzz+((256-zz)<<2)-0x400],x,64+16+(256-zz),208-(256-zz),MAP);
     zzzz=(zzzz+0x400)&0xFFFF;
   }

   }

   }
   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_bublbob2 =
{
   DrawBubbleSymphony,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_bublbob2[] =
{
   { "bubble_bobble_2", },
   { "bublbob2", },
   { NULL, },
};
#define load_bubsymph load_bublbob2
#define load_bubsympu load_bublbob2
GAME( bublbob2, "Bubble Bobble 2", TAITO, 1994, GAME_PLATFORM,
	.input = f3_system_inputs,
	.video = &video_bublbob2,
	.exec = ExecuteF3SystemFrame_NoInt5,
	.long_name_jpn = "バブルシンフォニー",
	.board = "D90",
	.sound = f3_sound,
);
static struct DIR_INFO dir_bubsymph[] =
{
   { "bubble_symphony", },
   { "bubsymph", },
   { ROMOF("bublbob2"), },
   { CLONEOF("bublbob2"), },
   { NULL, },
};
GAME( bubsymph, "Bubble Symphony", TAITO, 1994, GAME_PLATFORM,
	.input = f3_system_inputs,
	.video = &video_bublbob2,
	.exec = ExecuteF3SystemFrame_NoInt5,
	.long_name_jpn = "バブルシンフォニー",
	.board = "D90",
	.sound = f3_sound,
);
static struct DIR_INFO dir_bubsympu[] =
{
   { "bubble_symphony_us", },
   { "bubsympu", },
   { ROMOF("bublbob2"), },
   { CLONEOF("bublbob2"), },
   { NULL, },
};
GAME( bubsympu, "Bubble Symphony (US)", TAITO, 1994, GAME_PLATFORM,
	.input = f3_system_inputs,
	.video = &video_bublbob2,
	.exec = ExecuteF3SystemFrame_NoInt5,
	.long_name_jpn = "バブルシンフォニー (US)",
	.board = "D90",
	.sound = f3_sound,
);

