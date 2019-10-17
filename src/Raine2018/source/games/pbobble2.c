/******************************************************************************/
/*                                                                            */
/*               PUZZLE BOBBLE 2/2x (C) 1994 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_pbobble2[] =
{
   {   "e10-04.rom", 0x00200000, 0x5c0862a6, 0, 0, 0, },
   {   "e10-01.rom", 0x00100000, 0x8c26ff49, 0, 0, 0, },
   {   "e10-02.rom", 0x00100000, 0xc0564490, 0, 0, 0, },
   {   "e10-03.rom", 0x00200000, 0x46d68ac8, 0, 0, 0, },
   {   "e10-05.rom", 0x00100000, 0x81266151, 0, 0, 0, },
   {   "e10-06.rom", 0x00100000, 0x1b0f20e2, 0, 0, 0, },
   {   "e10-07.rom", 0x00100000, 0xdcb3c29b, 0, 0, 0, },
   {   "e10-09.rom", 0x00040000, 0xe0b1b599, 0, 0, 0, },
   {   "e10-10.rom", 0x00040000, 0xf432267a, 0, 0, 0, },
   {   "e10-11.rom", 0x00040000, 0xb82f81da, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "e10-12.rom",  0xb92dc8ad,   "e10-13.rom",  0x87842c13),
   {   "e10-15.rom", 0x00040000, 0xa2c0a268, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_puzzle_bobble_2_0[] =
{
   { "Taito Japan (Japanese)",            0x01 },
   { "Taito America (Bust-a-move again)", 0x02 },
   { "Taito Japan",                       0x03 },
   { NULL,                                0    },
};

static struct ROMSW_INFO romsw_pbobble2[] =
{
   { 0x0FFFFF, 0x03, romsw_data_puzzle_bobble_2_0 },
   { 0,        0,    NULL },
};




static struct ROM_INFO rom_pbobbl2x[] =
{
   {   "e10-01.rom", 0x00100000, 0x8c26ff49, 0, 0, 0, },
   {   "e10-02.rom", 0x00100000, 0xc0564490, 0, 0, 0, },
   {   "e10-03.rom", 0x00200000, 0x46d68ac8, 0, 0, 0, },
   {   "e10-04.rom", 0x00200000, 0x5c0862a6, 0, 0, 0, },
   {   "e10-05.rom", 0x00100000, 0x81266151, 0, 0, 0, },
   {   "e10-06.rom", 0x00100000, 0x1b0f20e2, 0, 0, 0, },
   {   "e10-07.rom", 0x00100000, 0xdcb3c29b, 0, 0, 0, },
   {       "e10.26", 0x00040000, 0xa5c24047, 0, 0, 0, },
   {       "e10.27", 0x00040000, 0x88cc0b5c, 0, 0, 0, },
   {       "e10.28", 0x00040000, 0x412a3602, 0, 0, 0, },
   {       "e10.29", 0x00040000, 0xf1e9ad3f, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
                  "e10.30",  0xbb090c1e,       "e10.31",  0xf4b88d65),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_puzzle_bobble_2x_0[] =
{
   { "Taito Japan (Japanese)",               0x01 },
   { "Taito America (Bust-a-move again EX)", 0x02 },
   { "Taito Japan",                          0x03 },
   { NULL,                                   0    },
};

static struct ROMSW_INFO romsw_pbobbl2x[] =
{
   { 0x0FFFFF, 0x03, romsw_data_puzzle_bobble_2x_0 },
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
static UINT8 *GFX_BG0_PENS;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_pbobble2(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x3F5D00+0x3EC700))) return;

   GFX_BG0 = GFX+0x3F5D00;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e10-02.rom", ROM, 0xFD740)) return;	// 16x16 SPRITES ($3F5D)
   for(ta=0;ta<0xFD740;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("e10-01.rom", ROM, 0xFD740)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xFD740;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("e10-07.rom", ROM, 0xFB1C0)) return;	// 16x16 TILES ($3EC7)
   for(ta=0;ta<0xFB1C0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("e10-06.rom", ROM, 0xFB1C0)) return;	// 16x16 TILES
   for(ta=0;ta<0xFB1C0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e10-05.rom", ROM, 0xFB1C0)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xFB1C0;ta+=2){
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

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x3EC7);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3F5D);

   GFX_BG0_PENS = make_colour_count_16x16(GFX_BG0, 0x3EC7);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x33000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A006;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A000;

   SCR3_XOFS=0xF640;
   SCR2_XOFS=0xF740;
   SCR1_XOFS=0xF840;
   SCR0_XOFS=0xF940;

   SCR3_YOFS=0xF400;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xF400;

   if(!load_rom("e10-11.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e10-10.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e10-09.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("e10-15.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("e10-03.rom",PCMROM,0x200000);
   load_be("e10-04.rom",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM ACCESS
   // -------------

   WriteWord68k(&ROM[0x0044B2],0x7F00);		//	raine	#$00 <eeprom access>
   WriteWord68k(&ROM[0x0044B4],0x4ED6);		//	jmp	(a6)

   // SPEED HACK
   // ----------

   WriteWord68k(&ROM[0x31B4],0x4EF9);		//	jmp	$F8000
   WriteLong68k(&ROM[0x31B6],0x000F8000);

   WriteWord68k(&ROM[0xF8000],0x4EB9);		//	jsr	$028FC <random gen>
   WriteLong68k(&ROM[0xF8002],0x000028FC);
   WriteWord68k(&ROM[0xF8006],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0xF8008],0x6100-10);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);


   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
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
   tc0200obj.mapper	= &Map_24bit_xRGB;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void load_pbobbl2x(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x3F5D00+0x3EC700))) return;

   GFX_BG0 = GFX+0x3F5D00;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e10-02.rom", ROM, 0xFD740)) return;	// 16x16 SPRITES ($3F5D)
   for(ta=0;ta<0xFD740;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("e10-01.rom", ROM, 0xFD740)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xFD740;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("e10-07.rom", ROM, 0xFB1C0)) return;	// 16x16 TILES ($3EC7)
   for(ta=0;ta<0xFB1C0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("e10-06.rom", ROM, 0xFB1C0)) return;	// 16x16 TILES
   for(ta=0;ta<0xFB1C0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e10-05.rom", ROM, 0xFB1C0)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xFB1C0;ta+=2){
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

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x3EC7);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3F5D);

   GFX_BG0_PENS = make_colour_count_16x16(GFX_BG0, 0x3EC7);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x33000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A006;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A000;

   SCR3_XOFS=0xF640;
   SCR2_XOFS=0xF740;
   SCR1_XOFS=0xF840;
   SCR0_XOFS=0xF940;

   SCR3_YOFS=0xF400;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xF400;

   if(!load_rom("e10.29", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e10.28", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e10.27", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("e10.26", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("e10-03.rom",PCMROM,0x200000);
   load_be("e10-04.rom",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM ACCESS
   // -------------

   WriteWord68k(&ROM[0x0044D2],0x7F00);		//	raine	#$00 <eeprom access>
   WriteWord68k(&ROM[0x0044D4],0x4ED6);		//	jmp	(a6)

   // SPEED HACK
   // ----------

   WriteWord68k(&ROM[0x031D4],0x4EF9);		//	jmp	$F8000
   WriteLong68k(&ROM[0x031D6],0x000F8000);

   WriteWord68k(&ROM[0xF8000],0x4EB9);		//	jsr	$0291C <random gen>
   WriteLong68k(&ROM[0xF8002],0x0000291C);
   WriteWord68k(&ROM[0xF8006],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0xF8008],0x6100-10);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);


   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
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
   tc0200obj.mapper	= &Map_24bit_xRGB;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawPuzzleBobble2(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y,z;
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

   START_SCROLL_512x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG0[zz+2])&0x3FFF;

      MAP_PALETTE_MULTI_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         GFX_BG0_PENS[ta],
         map
      );

      switch(RAM_BG0[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
      }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MULTI_MAPPED_NEW(
            ReadWord68k(&RAM_BG1[zz])&0x1FF,
            GFX_BG0_PENS[ta],
            map
         );

         if(GFX_BG0_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM_BG1[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG1[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
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

   START_SCROLL_512x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MULTI_MAPPED_NEW(
            ReadWord68k(&RAM_BG2[zz])&0x1FF,
            GFX_BG0_PENS[ta],
            map
         );

         if(GFX_BG0_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM_BG2[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG2[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
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

   START_SCROLL_512x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MULTI_MAPPED_NEW(
            ReadWord68k(&RAM_BG3[zz])&0x1FF,
            GFX_BG0_PENS[ta],
            map
         );

         if(GFX_BG0_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM_BG3[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG3[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
            }
         }

      }

   END_SCROLL_512x512_4_16();
   }

   // object

   render_tc0200obj_mapped_f3system_b();

   if(check_layer_enabled(f3_bg5_id)){
   zz=0;
   for(y=64;y<232+64;y+=8){
   for(x=64;x<320+64;x+=8){
      z=RAM[0x3C001+zz];
      if((z!=0)&&(z!=0x10)){		// 0x10='brown' rectangle

         MAP_PALETTE_MULTI_MAPPED_NEW(
            (RAM[0x3C000+zz]>>1)&0x3F,
            16,
            map
         );

         if((RAM[0x3C000+zz]&0x01)!=0){
            Draw8x8_Trans_Packed_Mapped_Rot(&RAM[0x3E000+(z<<5)],x,y,map);
         }
         else{
	   Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&RAM[0x3E000+(z<<5)],x,y,map);
         }

      }
      zz+=2;
   }
   zz+=(128-80);
   }
   }
}


/******************************************************************************/
/* ENSONIQ ES-5505 [OTIS]                                                     */
/******************************************************************************/

/*

1E - Page Select

Page	Address	Function
00 - 1F	00 - 1D	Voice Specific Control
40	00 - ??

*/


/******************************************************************************/
/* ENSONIQ ES-5510 [Ensoniq Signal Processor / DSP]                           */
/******************************************************************************/

/*

Address	Register Name	Bits	Description / Function
---------------------------------------------------------------
00	GPR        	23-16	GPR / SPR Data MS-byte
01	GPR 		15-8	GPR / SPR  Data
02	GPR   		7-0	GPR / SPR  Data LS-byte
03	INSTR           47-40	Mult D Operand Address
04	INSTR   	39-32	Mult C Operand Address
05	INSTR 		31-24 	ALU B Operand Address
06	INSTR    	23-16	ALU A Operand Address
07	INSTR    	15-8	ALU Opcode / Operand Select
08	INSTR    	7-3	Skip Flag +  MAC + RAM Control
09	DIL 		23-16	DRAM Input Latch MS-byte
0A	DIL 		15-8	DRAM Input Latch
0B	DIL		7-0	DRAM Input Latch LS-byte	 (always read as 00 )
0C	DOL 		23-16	DRAM Ouput Latch MS-byte
0D	DOL 		15-8	DRAM Ouput Latch
0E	DOL		7-0	DRAM Ouput Latch LS-byte	 (always read as FF )
0F	DADR		23-16	DRAM Address MS-byte	 (write last to transfer data)
10	DADR		15-8	DRAM Address
11	DADR  		7-4	DRAM Address LS-byte
12	Host Control 	2-0	ESP State / Control Flags
14	RAM Access Control 	7-6	RAM,I/O, Read/Write Select
16	Program Counter            		For Test Purposes Only
17	Internal Refresh counter        		For Test Purposes Only
18	Host serial control	7-0	Serial I/O Format and Control
1F	Halt enable       (write only) Frame Counter (read only)		Stop ESP Execution For Test Purposes Only

80	Read  Select:  GPR + INSTR  	7-0	Read  Address	Address Ranges:
A0	Write Select:  GPR      	7-0	Write Address	GPR       $00 - $BF
C0	Write Select:  INSTR      	7-0	Write Address	SPR       $EA - $FF
E0	Write Select:  GPR+INSTR	7-0	Write Address	INSTR   $00 - $9F

*/


/*

Elevator Action 2
-----------------

Ensoniq
OTISR2
609-0381303
FP05164
K9442

Ensoniq
5701000101
9416MVA82

Ensoniq
609-0390750
FP03457 K9420
ES5510000106
ESPR6

Motorola
MC68681P

Twin Qix
--------

Ensoniq
OTISR2
609-0381303
FP05164
K9442

Ensoniq
5701000101
9416MVA82

Ensoniq
609-0390750
FP03457 K9420
ES5510000106
ESPR6

Motorola
MC68681P

Super Chase
-----------

68000
68681
MB8421 (x2)
MB87078
Ensoniq 5510
Ensoniq 5505

*/
static struct VIDEO_INFO video_pbobble2 =
{
   DrawPuzzleBobble2,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_pbobble2[] =
{
   { "puzzle_bobble_2", },
   { "pbobble2", },
   { NULL, },
};
GAME( pbobble2, "Puzzle Bobble 2", TAITO, 1995, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_pbobble2,
	.video = &video_pbobble2,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "パズルボブル２",
	.board = "E10",
	.sound = f3_sound,
);
static struct DIR_INFO dir_pbobbl2x[] =
{
   { "puzzle_bobble_2x", },
   { "puzbob2x", },
   { "pbobbl2x", },
   { ROMOF("pbobble2"), },
   { CLONEOF("pbobble2"), },
   { NULL, },
};
GAME( pbobbl2x, "Puzzle Bobble 2 (extra)", TAITO, 1995, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_pbobbl2x,
	.video = &video_pbobble2,
	.exec = ExecuteF3SystemFrameB,
	.long_name_jpn = "パズルボブル２Ｘ",
	.board = "E10",
	.sound = f3_sound,
);

