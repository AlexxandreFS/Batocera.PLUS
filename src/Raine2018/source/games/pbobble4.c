/******************************************************************************/
/*                                                                            */
/*                 PUZZLE BOBBLE 4 (C) 1997 TAITO CORPORATION                 */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_pbobble4[] =
{
   {       "e49.01", 0x00100000, 0xa3dd5f85, 0, 0, 0, },
   {       "e49.02", 0x00100000, 0xc7d2f40b, 0, 0, 0, },
   {       "e49.03", 0x00200000, 0xf64303e0, 0, 0, 0, },
   {       "e49.04", 0x00200000, 0x09be229c, 0, 0, 0, },
   {       "e49.05", 0x00200000, 0x5ce90ee2, 0, 0, 0, },
   {       "e49.06", 0x00100000, 0xec85f7ce, 0, 0, 0, },
   {       "e49.07", 0x00100000, 0x1e1e8e1c, 0, 0, 0, },
   {       "e49.08", 0x00100000, 0x87408106, 0, 0, 0, },
   {       "e49.10", 0x00080000, 0x0307460b, 0, 0, 0, },
   {       "e49.11", 0x00080000, 0xbf69a087, 0, 0, 0, },
   {       "e49.12", 0x00080000, 0xfffea203, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "e49.13",  0x83536f7f,       "e49.14",  0x19815bdb),
   {       "e49.16", 0x00080000, 0x0a021624, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_puzzle_bobble_4_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Worldwide",        0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_pbobble4[] =
{
   { 0x1FFFFF, 0x03, romsw_data_puzzle_bobble_4_0 },
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

static void load_pbobble4(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0x3FA100+0x3FA100))) return;

   GFX_BG0 = GFX+0x3FA100;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("E49.02", ROM, 0xFE840)) return;		// 16x16 SPRITES ($3FA1)
   for(ta=0;ta<0xFE840;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("E49.01", ROM, 0xFE840)) return;		// 16x16 SPRITES
   for(ta=0;ta<0xFE840;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }

   tb=0;
   if(!load_rom("E49.08", ROM, 0xFE840)) return;		// 16x16 TILES ($3FA1)
   for(ta=0;ta<0xFE840;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("E49.07", ROM, 0xFE840)) return;		// 16x16 TILES
   for(ta=0;ta<0xFE840;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("E49.06", ROM, 0xFE840)) return;		// 16x16 TILES (MASK)
   for(ta=0;ta<0xFE840;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x3FA1);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3FA1);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

   RAM_BG0=RAM+0x30000;
   RAM_BG3=RAM+0x31000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x33000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR3=RAM+0x6A002;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A006;

   SCR0_XOFS=0xF640;
   SCR3_XOFS=0xF740;
   SCR1_XOFS=0xF840;
   SCR2_XOFS=0xF940;

   SCR0_YOFS=0xF400;
   SCR3_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR2_YOFS=0xF400;

   if(!load_rom("E49.12", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("E49.11", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("E49.10", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("E49.16", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x1000000))) return;
   load_be("e49.05",PCMROM,0x200000);
   load_be("e49.04",PCMROM+0x400000,0x200000);
   load_be("e49.03",PCMROM+0x800000,0x200000);
   max_banks_this_game=6; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(PCMROM+0xc00000,0x0,0x3fffff);
   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // PROTECTION HACK
   // ---------------

   WriteLong68k(&ROM[0x00BA96],0x001E8000);
   W24[0x1E] = ROM+0x1E0000;

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x0047AE],0x7F00);		//	raine	#$00 <read/write eeprom>
   WriteWord68k(&ROM[0x0047B0],0x4ED6);		//	jmp	(a6)


   // SPEED HACK#1
   // ------------

   WriteWord68k(&ROM[0x001500],0x4EF9);		//	jmp	$1E8100
   WriteLong68k(&ROM[0x001502],0x001E8100);	//

   WriteWord68k(&ROM[0x1E8100],0x4EB9);		//	jsr	$15EA
   WriteLong68k(&ROM[0x1E8102],0x000015EA);	//

   WriteWord68k(&ROM[0x1E8106],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x1E8108],0x6100-10);	//	bra.s	<loop>

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
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();


   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearPuzzleBobble4(void)
{
   save_eeprom();
}

static int BGPRI[4];

static void DrawPuzzleBobble4(void)
{
   UINT8 *MAP;
   int x,y,z,ta,zz,zzz,zzzz,x16,y16;
   UINT16 d0;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   d0=0;

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

      if(d0==0) d0=ReadWord68k(&RAM_BG0[zz])&0x3E00;

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG0[zz])&0x1FF,
               64,        MAP
            );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],x,y,MAP); break;
      }

   END_SCROLL_512x512_4_16();
   }

   BGPRI[0]=d0;
   d0=0;

   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
   if(ta!=0){

      if(d0==0) d0=ReadWord68k(&RAM_BG1[zz])&0x3E00;

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG1[zz])&0x1FF,
               64,        MAP
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

   END_SCROLL_512x512_4_16();
   }

   BGPRI[1]=d0;
   d0=0;

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
   if(ta!=0){

      if(d0==0) d0=ReadWord68k(&RAM_BG2[zz])&0x3E00;

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG2[zz])&0x1FF,
               64,        MAP
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

   END_SCROLL_512x512_4_16();
   }

   BGPRI[2]=d0;
   d0=0;

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
   if(ta!=0){

      if(d0==0) d0=ReadWord68k(&RAM_BG3[zz])&0x3E00;

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               64,        MAP
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

   END_SCROLL_512x512_4_16();
   }

   BGPRI[3]=d0;

   render_tc0200obj_mapped_f3system_b();

   if(check_layer_enabled(f3_bg5_id)){
      //memset(RAM+0x3E000+(5<<5),0x20,0x00);
      //f3video_render_fg0();

   zz=0;
   for(y=64;y<232+64;y+=8){
   for(x=64;x<320+64;x+=8){
      z=RAM[0x3C001+zz];
      if((z!=0)&&(z!=5)){		// 5='black' transparent shade

      MAP_PALETTE_MAPPED_NEW(
               (RAM[0x3C000+zz]>>1)&0x3F,
               16,        MAP
            );

         if((RAM[0x3C000+zz]&0x01)!=0){
            Draw8x8_Trans_Packed_Mapped_Rot(&RAM[0x3E000+(z<<5)],x,y,MAP);
         }
         else{
            Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&RAM[0x3E000+(z<<5)],x,y,MAP);
         }

      }
      zz+=2;
   }
   zz+=(128-80);
   }
   }

//     print_ingame(1,gettext("$$$: %04x %04x %04x %04x"),BGPRI[0],BGPRI[1],BGPRI[2],BGPRI[3]);

     if((BGPRI[0]!=0)||(BGPRI[1]!=0)||(BGPRI[2]!=0)||(BGPRI[3]!=0))
     {
       RAM_BG0=RAM+0x33000;
       RAM_BG2=RAM+0x31000;
       RAM_BG3=RAM+0x30000;

       RAM_SCR0=RAM+0x6A006;
       RAM_SCR2=RAM+0x6A002;
       RAM_SCR3=RAM+0x6A000;

       SCR3_XOFS=0xF640;
       SCR2_XOFS=0xF740;
       SCR0_XOFS=0xF940;

     }
     else
     {
       RAM_BG0=RAM+0x30000;
       RAM_BG3=RAM+0x31000;
       RAM_BG2=RAM+0x33000;

       RAM_SCR0=RAM+0x6A000;
       RAM_SCR3=RAM+0x6A002;
       RAM_SCR2=RAM+0x6A006;

       SCR0_XOFS=0xF640;
       SCR3_XOFS=0xF740;
       SCR2_XOFS=0xF940;

     }

}

/*

'Raven' Romlist
---------------

File   | Contents
-------+----------------------------------
pb4.17 | 68020 3
pb4.18 | 68020 2
pb4.19 | 68020 1
pb4.20 | 68020 0
pb4.32 | 68000 1
pb4.33 | 68000 0
pb4.45 | Tiles odd
pb4.47 | Tiles even
pb4.38 | Samples 0 (missing odd bytes)
pb4.39 | Samples 1 (missing odd bytes)
pb4.40 | Samples 2 (missing odd bytes)
pb4.8  | Sprites odd  (missing odd bytes)
pb4.12 | Sprites even (missing odd bytes)

What's missing:

- Odd bytes on 5 of the roms
- 1 Mask rom for tiles

*/
static struct VIDEO_INFO video_pbobble4 =
{
   DrawPuzzleBobble4,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_pbobble4[] =
{
   { "puzzle_bobble_4", },
   { "puzbob4", },
   { "pbobble4", },
   { NULL, },
};
GAME( pbobble4, "Puzzle Bobble 4", TAITO, 1997, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_pbobble4,
	.clear = ClearPuzzleBobble4,
	.video = &video_pbobble4,
	.exec = ExecuteF3SystemFrameB,
	.board = "E49",
	.sound = f3_sound,
);

