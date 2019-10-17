/******************************************************************************/
/*                                                                            */
/*                  UNDER FIRE (C) 1995 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "savegame.h"


static struct ROM_INFO rom_undrfire[] =
{
   {   "d67-06", 0x00200000, 0xa2a63488, 0, 0, 0, },
   {   "d67-02", 0x00200000, 0xfceb715e, 0, 0, 0, },
   {   "d67-03", 0x00200000, 0x3b6e99a9, 0, 0, 0, },
   {   "d67-04", 0x00200000, 0x8f2934c9, 0, 0, 0, },
   {   "d67-05", 0x00200000, 0xe2e7dcf3, 0, 0, 0, },
   {   "d67-01", 0x00200000, 0xa2f18122, 0, 0, 0, },
   {   "d67-07", 0x00200000, 0x189c0ee5, 0, 0, 0, },
   {   "d67-08", 0x00200000, 0x56730d44, 0, 0, 0, },
   {   "d67-09", 0x00200000, 0x3c19f9e3, 0, 0, 0, },
   {   "d67-10", 0x00100000, 0xd79e6ce9, 0, 0, 0, },
   {   "d67-11", 0x00100000, 0x7a401bb3, 0, 0, 0, },
   {   "d67-12", 0x00100000, 0x67b16fec, 0, 0, 0, },
   {   "d67-13", 0x00080000, 0x42e7690d, 0, 0, 0, },
   {   "d67-17", 0x00080000, 0x34e030b7, 0, 0, 0, },
   {   "d67-18", 0x00080000, 0xf41ae7fd, 0, 0, 0, },
   {   "d67-19", 0x00080000, 0x1d88fa5a, 0, 0, 0, },
   {   "d67-20", 0x00020000, 0x974ebf69, 0, 0, 0, },
   {   "d67-21", 0x00020000, 0x8fc6046f, 0, 0, 0, },
   {   "d67-23", 0x00080000, 0x28e84e0a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_undrfire[] =
{
   INP0( COIN1, 0x069007, 0x04 ),
   INP0( COIN2, 0x069007, 0x08 ),
   INP0( SERVICE, 0x069007, 0x02 ),
   INP0( TEST, 0x069007, 0x01 ),
   INP0( P1_START, 0x069002, 0x10 ),
   INP0( P1_B1, 0x069001, 0x10 ),
   INP0( P1_B2, 0x069001, 0x20 ),
   INP0( P2_START, 0x069002, 0x20 ),
   INP0( P2_B1, 0x069001, 0x40 ),
   INP0( P2_B2, 0x069001, 0x80 ),
   END_INPUT
};

static struct ROMSW_DATA romsw_data_under_fire_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Japan",            0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_undrfire[] =
{
   { 0x1FFFFF, 0x03, romsw_data_under_fire_0 },
   { 0,        0,    NULL },
};



#define OBJ_A_COUNT	(0xF685)

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
/* static UINT8 *GFX_OBJ_A_SOLID; */

/* static UINT8 *zoom16_ofs; */

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

static UINT8 *GFX_BG1;
static UINT8 *GFX_BG1_SOLID;

/* static UINT8 *GFX_SPR; */
/* static UINT8 *GFX_SPR_SOLID; */

static void AddUFMemoryMap(UINT32 romsize)
{
   UINT32 ta;

   for(ta=0;ta<0x100;ta++){
      R24[ta]=RAM+0x70000;	// SCRATCH RAM
   }

   R24[0x20]=RAM+0x00000;	// MAIN RAM
   R24[0x21]=RAM+0x10000;	// MAIN RAM

   R24[0x30]=RAM+0x40000;	// OBJECT?

   R24[0xA0]=RAM+0x60000;	// COLOR?

   R24[0x50]=RAM+0x69000;	// INPUT	($500000-$500007)

   //R24[0x80]=RAM+0x20000;	// OBJECT RAM
   R24[0x80]=RAM+0x30000;	// SCREEN RAM - F3 system
   //R24[0x82]=RAM+0x40000;	// LINE RAM
   //R24[0x83]=RAM+0x50000;	// PIXEL RAM

   R24[0x83]=RAM+0x6A000;	// SCROLL RAM - F3 system

   //R24[0xC0]=RAM+0x68000;	// SOUND RAM	($C00000-$C007FF)

   R24[0x90]=RAM+0x20000;	// SCREEN RAM - tc0100scn (?)

   R24[0x92]=RAM+0x6A100;	// SCROLL RAM - tc0100scn (?)

   for(ta=0;ta<0x100;ta++){
      W24[ta]=R24[ta];		// COPY READ>WRITE
   }

   for(ta=0;ta<(romsize>>16);ta++){
      R24[ta]=ROM+(ta<<16);	// 68020 ROM
   }

   W24[0x50]=RAM+0x69100;	// OUTPUT	($500000-$50000F)

   EEPROM=RAM+0x6B000;		// EEPROM
}

static void load_undrfire(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   if(!(GFX_BG0=AllocateMem(0x569000))) return;
   if(!(GFX_BG1=AllocateMem(0x400000))) return;

   if(!(GFX_OBJ_A=AllocateMem(OBJ_A_COUNT*0x100))) return;
   if(!(OBJECT_MAP=AllocateMem(0x80000))) return;

   if(!(TMP=AllocateMem(0x200000))) return;

   if(!load_rom("d67-03", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_A[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_A[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_A[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_A[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_A[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_A[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_A[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_A[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom("d67-04", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom("d67-05", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom("d67-06", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }
   if(!load_rom("d67-07", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(11));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(10));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>( 9));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 8));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 7));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 6));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 5));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 4));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 3));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 2));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 1));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 0));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)<<( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 2));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 3));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 4));
      tb+=16;
   }

   if(!load_rom("d67-13", OBJECT_MAP, 0x80000)) return; // TILE MAPPING

   tb=0;
   if(!load_rom("d67-08", TMP, 0x15A400)) return;	// 16x16 TILES ($5690)
   for(ta=0;ta<0x15A400;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d67-09", TMP, 0x15A400)) return;	// 16x16 TILES
   for(ta=0;ta<0x15A400;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d67-10", TMP, 0x100000)) return;	// 8x8 TILES ($10000)
   for(ta=0;ta<0x100000;ta+=4,tb+=16){
      GFX_BG1[tb+0]=TMP[ta+0]&15;
      GFX_BG1[tb+8]=TMP[ta+0]>>4;
      GFX_BG1[tb+1]=TMP[ta+1]&15;
      GFX_BG1[tb+9]=TMP[ta+1]>>4;
      GFX_BG1[tb+2]=TMP[ta+2]&15;
      GFX_BG1[tb+10]=TMP[ta+2]>>4;
      GFX_BG1[tb+3] =TMP[ta+3]&15;
      GFX_BG1[tb+11]=TMP[ta+3]>>4;
   }
   tb=4;
   if(!load_rom("d67-11", TMP, 0x100000)) return;	// 8x8 TILES
   for(ta=0;ta<0x100000;ta+=4,tb+=16){
      GFX_BG1[tb+0]=TMP[ta+0]&15;
      GFX_BG1[tb+8]=TMP[ta+0]>>4;
      GFX_BG1[tb+1]=TMP[ta+1]&15;
      GFX_BG1[tb+9]=TMP[ta+1]>>4;
      GFX_BG1[tb+2]=TMP[ta+2]&15;
      GFX_BG1[tb+10]=TMP[ta+2]>>4;
      GFX_BG1[tb+3] =TMP[ta+3]&15;
      GFX_BG1[tb+11]=TMP[ta+3]>>4;
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x05690);
   GFX_BG1_SOLID = make_solid_mask_8x8  (GFX_BG1, 0x10000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;

   // Setup 68020 Memory Map
   // ----------------------

   AddUFMemoryMap(0x200000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG3=RAM+0x33000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;

   SCR0_XOFS=0xF640;
   SCR1_XOFS=0xF740;
   SCR2_XOFS=0xF840;
   SCR3_XOFS=0xF940;

   SCR0_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR2_YOFS=0xF400;
   SCR3_YOFS=0xF400;

   if(!load_rom("d67-19", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d67-18", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d67-17", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d67-23", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   add_eeprom(EEPROM, 0x80, EPR_INVALIDATE_ON_ROM_CHANGE);
   load_eeprom();

   // EEPROM HACK
   // -----------

   WriteWord68k(&ROM[0x19FD6E],0x7F00);		//	raine	#$00	<eeprom read/write>
   WriteWord68k(&ROM[0x19FD70],0x4ED6);		//	jmp	(a6)

   // SPEED HACK
   // ----------

   WriteWord68k(&ROM[0x000BEA],0x7F02);		//	raine	#$02	<stop cpu>
   WriteWord68k(&ROM[0x000BEC],0x6100-10);	//	bra.s	<loop>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x4000);


   init_m68k();
}

static void execute_undrfire(void)
{
   Execute68020(800000);
      print_debug("PC:%06x SR:%04x\n",regs.pc,regs.sr);
   Interrupt68020(4);
   Interrupt68020(5);

   //IntF3System();
}

static void DrawUndrFire(void)
{
   int x,y,ta,zz,zzz,zzzz,x16,y16;
   UINT8 *map;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(RefreshBuffers){

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 232;
   tc0003vcu.scr_x	= 0;
   tc0003vcu.scr_y	= 8;

   }

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG0[zz])&0x1FF,
            16,
            map
         );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map); break;
      }

   END_SCROLL_512x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_512x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   START_SCROLL_512x512_4_16(64,64,320,232);

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x7FFF;
   if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG1[zz])&0x1FF,
            16,
            map
         );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
      else{
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

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x7FFF;
   if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG2[zz])&0x1FF,
            16,
            map
         );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
      else{
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

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x7FFF;
   if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG3[zz])&0x1FF,
            16,
            map
         );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],x,y,map); break;
         }
      }
      else{
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

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_gfx2();
   }
}


/*

d67-01.rom | Ensoniq Sample Data
d67-02.rom | Ensoniq Sample Data
d67-03.rom | Zoom Tiles (plane#0)
d67-04.rom | Zoom Tiles (plane#1)
d67-05.rom | Zoom Tiles (plane#2)
d67-06.rom | Zoom Tiles (plane#3)
d67-07.rom | Zoom Tiles (plane#4)
d67-08.rom | 16x16 F3 Tiles (even)
d67-09.rom | 16x16 F3 Tiles (odd)
d67-10.rom | 8x8 F2 Tiles (even)
d67-11.rom | 8x8 F2 Tiles (odd)
d67-12.rom | Mask data (???)
d67-13.rom | Zoom Object Maps
d67-17.rom | 68020 rom (byte#2)
d67-18.rom | 68020 rom (byte#1)
d67-19.rom | 68020 rom (byte#0)
d67-20.rom | 68000 rom (even)
d67-21.rom | 68000 rom (odd)
d67-23.rom | 68020 rom (byte#3)
readme.txt | dumped by aracorn

*/
static struct VIDEO_INFO video_undrfire =
{
   DrawUndrFire,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_undrfire[] =
{
   { "under_fire", },
   { "undrfire", },
   { NULL, },
};
GAME( undrfire, "Under Fire", TAITO, 1993, GAME_SHOOT | GAME_NOT_WORKING,
	.input = input_undrfire,
	.romsw = romsw_undrfire,
	.video = &video_undrfire,
	.exec = execute_undrfire,
	.board = "D67",
);

