#define DRV_DEF_SOUND f3_sound
/******************************************************************************/
/*                                                                            */
/*                SPACE INVADERS 95 (C) 1995 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_akkanvdr[] =
{
   {       "e06.05", 0x00200000, 0xf370ff15, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "e06.09",  0x9bcafc87,       "e06.10",  0xb752b61f),
   {       "e06.11", 0x00020000, 0x3fe550b9, 0, 0, 0, },
   {       "e06.12", 0x00020000, 0x06cbd72b, 0, 0, 0, },
   {       "e06.13", 0x00020000, 0xf506ba4b, 0, 0, 0, },
   {       "e06.14", 0x00020000, 0x71ba7f00, 0, 0, 0, },
   {       "e06.01", 0x00100000, 0x51721b15, 0, 0, 0, },
   {       "e06.02", 0x00100000, 0x8f646dea, 0, 0, 0, },
   {       "e06.03", 0x00100000, 0xa24070ef, 0, 0, 0, },
   {       "e06.06", 0x00100000, 0x9380db3c, 0, 0, 0, },
   {       "e06.07", 0x00100000, 0x4b02e8f5, 0, 0, 0, },
   {       "e06.08", 0x00100000, 0x72ae2fbf, 0, 0, 0, },
   {       "e06.04", 0x00200000, 0x1dac29df, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_space_invaders_95_0[] =
{
   { "Taito Japan (Akkanbeder)",          0x01 },
   { "Taito America (Space Inv 95)",      0x02 },
   { "Taito Japan (Space Inv 95)",        0x03 },
   { "Taito Kumagaya R&D (Space Inv 95)", 0x04 },
   { NULL,                                0    },
};

static struct ROMSW_INFO romsw_akkanvdr[] =
{
   { 0x07FFFF, 0x02, romsw_data_space_invaders_95_0 },
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

static void load_akkanvdr(void)
{
   int ta,tb,tc;

   if(!(GFX=AllocateMem(0x2B5C00+0x3FF600))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x2B5C00;

   tb=0;
   if(!load_rom("E06.03", ROM, 0xFFD80)) return;	// 16x16 SPRITES ($3FF6)
   for(ta=0;ta<0xFFD80;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("E06.02", ROM, 0xFFD80)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xFFD80;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("E06.01", ROM, 0xFFD80)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xFFD80;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0x40)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x10)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x04)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("E06.08", ROM, 0xAD700)) return;	// 16x16 TILES ($2B5C)
   for(ta=0;ta<0xAD700;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("E06.07", ROM, 0xAD700)) return;	// 16x16 TILES
   for(ta=0;ta<0xAD700;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("E06.06", ROM, 0xAD700)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xAD700;ta+=2){
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

   FreeMem(ROM);

   Rotate16x16(GFX_SPR,0x3FF6);
   Flip16x16_X(GFX_SPR,0x3FF6);
   Rotate16x16(GFX_BG0,0x2B5C);
   Flip16x16_X(GFX_BG0,0x2B5C);

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2B5C);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3FF6);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x80000);

   RAM_BG3=RAM+0x30000;
   RAM_BG1=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG0=RAM+0x33000;

   RAM_SCR3=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR0=RAM+0x6A006;

   SCR3_XOFS=0xF600;
   SCR1_XOFS=0xF700;
   SCR2_XOFS=0xF800;
   SCR0_XOFS=0xF900;

   SCR3_YOFS=0x0780-(16<<7);
   SCR1_YOFS=0x0780-(16<<7);
   SCR2_YOFS=0x0780-(16<<7);
   SCR0_YOFS=0x0780-(16<<7);

   if(!load_rom("E06.14", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("E06.13", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("E06.12", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("E06.11", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   Rotate8x8_4bpp(ROM+0x63470,(0x5A8*4)/0x20);
   Flip8x8_4bpp_X(ROM+0x63470,(0x5A8*4)/0x20);

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xa00000))) return;
   load_be("e06.04",PCMROM,0x200000);
   load_be("e06.05",PCMROM+0x400000,0x200000);
   max_banks_this_game=4; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0x800000,0,0x1fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM ERROR
   // -------------

   WriteWord68k(&ROM[0x000FD8],0x4E75);		//	rts

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x004A70],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x004A72],0x4E75);		//	rts

   WriteWord68k(&ROM[0x004AEE],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x004AF0],0x4E75);		//	rts

   // SPEED HACKS
   // -----------

   WriteWord68k(&ROM[0x000260],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x000262],0x6100-14);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x000552],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x000554],0x4E71);		//	nop

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;


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
   tc0003vcu.scr_x	= 16;
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
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= -16;
   tc0200obj.ofs_y	= 0;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearSpcInv95(void)
{
   save_eeprom();
}

static void DrawSpcInv95(void)
{
   int x16,y16;
   int x,y,zz,zzz,zzzz;
   int ta;
   UINT8 *map;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
      MAKE_SCROLL_512x512_4_16(
         (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
         (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
      );

      START_SCROLL_512x512_4_16_R270(64,64,224,320);

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG0[zz])&0x1FF,
            32,
            map
         );

      switch(RAM_BG0[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map);        break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map);  break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,map); break;
      }

      END_SCROLL_512x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){
      MAKE_SCROLL_512x512_4_16(
         (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
         (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
      );

      START_SCROLL_512x512_4_16_R270(64,64,224,320);

      ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG1[zz])&0x1FF,
            32,
            map
         );

         if(GFX_BG0_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM_BG1[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG1[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
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

      START_SCROLL_512x512_4_16_R270(64,64,224,320);

      ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG2[zz])&0x1FF,
            32,
            map
         );

         if(GFX_BG0_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM_BG2[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG2[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
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

      START_SCROLL_512x512_4_16_R270(64,64,224,320);

      ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG3[zz])&0x1FF,
            32,
            map
         );

         if(GFX_BG0_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM_BG3[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG3[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
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
static struct VIDEO_INFO video_akkanvdr =
{
   DrawSpcInv95,
   224,
   320,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_akkanvdr[] =
{
   { "space_invaders_95", },
   { "spcinv95", },
   { "akkanvdr", },
   { NULL, },
};
GAME( akkanvdr, "Akkanvader", TAITO, 1995, GAME_SHOOT,
	.input = f3_system_inputs,
	.romsw = romsw_akkanvdr,
	.clear = ClearSpcInv95,
	.video = &video_akkanvdr,
	.exec = ExecuteF3SystemFrame,
	.long_name_jpn = "‚ß‚Á‚©‚¤‚×[‚¾[",
	.board = "E06",
);

