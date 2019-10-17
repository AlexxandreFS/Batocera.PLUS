#define DRV_DEF_INPUT f3_system_inputs_6_button
#define DRV_DEF_DSW NULL
#define DRV_DEF_EXEC ExecuteF3SystemFrameB
#define DRV_DEF_SOUND f3_sound
/******************************************************************************/
/*                                                                            */
/*                   KAISER KNUCKLE (C) 1994 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"

static struct ROM_INFO rom_kaiserkn[] =
{
   {   "d84-01.rom", 0x00200000, 0x9ad22149, 0, 0, 0, },
   {   "d84-02.rom", 0x00200000, 0x9e1827e4, 0, 0, 0, },
   {   "d84-03.rom", 0x00200000, 0xd786f552, 0, 0, 0, },
   {   "d84-04.rom", 0x00200000, 0xd1f32b5d, 0, 0, 0, },
   {   "d84-05.rom", 0x00200000, 0x31a3c75d, 0, 0, 0, },
   {   "d84-06.rom", 0x00200000, 0xfa924dab, 0, 0, 0, },
   {   "d84-07.rom", 0x00200000, 0x54517a6b, 0, 0, 0, },
   {   "d84-08.rom", 0x00200000, 0x07347bf1, 0, 0, 0, },
   {   "d84-09.rom", 0x00200000, 0xfaa78d98, 0, 0, 0, },
   {   "d84-10.rom", 0x00200000, 0xb84b7320, 0, 0, 0, },
   {   "d84-11.rom", 0x00200000, 0xa062c1d4, 0, 0, 0, },
   {   "d84-12.rom", 0x00200000, 0x66a7a9aa, 0, 0, 0, },
   {   "d84-13.rom", 0x00200000, 0xae125516, 0, 0, 0, },
   {   "d84-14.rom", 0x00200000, 0x2b2e693e, 0, 0, 0, },
   {   "d84-15.rom", 0x00100000, 0x31ceb152, 0, 0, 0, },
   {   "d84-16.rom", 0x00100000, 0xbcff9b2d, 0, 0, 0, },
   {   "d84-17.rom", 0x00100000, 0x0be37cc3, 0, 0, 0, },
   {   "d84-18.rom", 0x00100000, 0xe812bcc5, 0, 0, 0, },
   {   "d84-19.rom", 0x00080000, 0x6ddf77e5, 0, 0, 0, },
   {   "d84-20.rom", 0x00080000, 0xf85041e5, 0, 0, 0, },
   {   "d84-21.rom", 0x00080000, 0x89f68b66, 0, 0, 0, },
   {   "d84-29.rom", 0x00080000, 0x9821f17a, 0, 0, 0, },
   {   "d84-23.rom", 0x00080000, 0x39f12a9b, 0, 0, 0, },
   {   "d84-24.rom", 0x00080000, 0xbf20c755, 0, 0, 0, },
   {   "d84-25.rom", 0x00080000, 0x2840893f, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d84-26.rom",  0x4f5b8563,   "d84-27.rom",  0xfb0cb1ba),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_kaiser_knuckle_0[] =
{
   { "Taito Japan",                     0x01 },
   { "Taito America (Global Champion)", 0x02 },
   { "Taito",                           0x03 },
   { NULL,                              0    },
};

static struct ROMSW_INFO romsw_kaiserkn[] =
{
   { 0x1FFFFF, 0x03, romsw_data_kaiser_knuckle_0 },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_dankuga[] =
{
   {   "d84-01.rom", 0x00200000, 0x9ad22149, 0, 0, 0, },
   {   "d84-02.rom", 0x00200000, 0x9e1827e4, 0, 0, 0, },
   {   "d84-03.rom", 0x00200000, 0xd786f552, 0, 0, 0, },
   {   "d84-04.rom", 0x00200000, 0xd1f32b5d, 0, 0, 0, },
   {   "d84-05.rom", 0x00200000, 0x31a3c75d, 0, 0, 0, },
   {   "d84-06.rom", 0x00200000, 0xfa924dab, 0, 0, 0, },
   {   "d84-07.rom", 0x00200000, 0x54517a6b, 0, 0, 0, },
   {   "d84-08.rom", 0x00200000, 0x07347bf1, 0, 0, 0, },
   {   "d84-09.rom", 0x00200000, 0xfaa78d98, 0, 0, 0, },
   {   "d84-10.rom", 0x00200000, 0xb84b7320, 0, 0, 0, },
   {   "d84-11.rom", 0x00200000, 0xa062c1d4, 0, 0, 0, },
   {   "d84-12.rom", 0x00200000, 0x66a7a9aa, 0, 0, 0, },
   {   "d84-13.rom", 0x00200000, 0xae125516, 0, 0, 0, },
   {   "d84-14.rom", 0x00200000, 0x2b2e693e, 0, 0, 0, },
   {   "d84-15.rom", 0x00100000, 0x31ceb152, 0, 0, 0, },
   {   "d84-16.rom", 0x00100000, 0xbcff9b2d, 0, 0, 0, },
   {   "d84-17.rom", 0x00100000, 0x0be37cc3, 0, 0, 0, },
   {   "d84-18.rom", 0x00100000, 0xe812bcc5, 0, 0, 0, },
   {   "d84-19.rom", 0x00080000, 0x6ddf77e5, 0, 0, 0, },
   {   "d84-20.rom", 0x00080000, 0xf85041e5, 0, 0, 0, },
   {   "d84-21.rom", 0x00080000, 0x89f68b66, 0, 0, 0, },
   { "dkg_mpr0.bin", 0x00080000, 0xad6ada07, 0, 0, 0, },
   { "dkg_mpr1.bin", 0x00080000, 0x97566f69, 0, 0, 0, },
   { "dkg_mpr2.bin", 0x00080000, 0x18a4748b, 0, 0, 0, },
   { "dkg_mpr3.bin", 0x00080000, 0xee1531ca, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d84-26.rom",  0x4f5b8563,   "d84-27.rom",  0xfb0cb1ba),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_kaiser_knuckle_alt_0[] =
{
   { "Taito Japan",                     0x01 },
   { "Taito America (Global Champion)", 0x02 },
   { "Taito",                           0x03 },
   { NULL,                              0    },
};

static struct ROMSW_INFO romsw_dankuga[] =
{
   { 0x1FFFFF, 0x01, romsw_data_kaiser_knuckle_alt_0 },
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

static UINT8 *GFX2;
static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_kaiserkn(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX2=AllocateMem(0x9BAE00))) return;
   if(!(GFX=AllocateMem(0x1900400))) return;	// ouch!!

   GFX_BG0=GFX2;
   GFX_SPR=GFX;

   if(!load_rom("d84-03.rom", ROM, 0x200000)) return;	// 16x16 SPRITES ($8000)
   tb=0;
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   if(!load_rom("d84-04.rom", ROM, 0x200000)) return;	// 16x16 SPRITES
   tb=2;
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   tb=0;
   if(!load_rom("d84-05.rom", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   if(!load_rom("d84-06.rom", ROM, 0x200000)) return;	// 16x16 SPRITES ($8000)
   tb=0x800000;
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   if(!load_rom("d84-07.rom", ROM, 0x200000)) return;	// 16x16 SPRITES
   tb=0x800002;
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   tb=0x800000;
   if(!load_rom("d84-08.rom", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   if(!load_rom("d84-09.rom", ROM, 0x200000)) return;	// 16x16 SPRITES ($8000)
   tb=0x1000000;
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   if(!load_rom("d84-10.rom", ROM, 0x200000)) return;	// 16x16 SPRITES
   tb=0x1000002;
   for(ta=0;ta<0x200000;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   tb=0x1000000;
   if(!load_rom("d84-11.rom", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   if(!load_rom("d84-19.rom", ROM, 0x40100)) return;	// 16x16 SPRITES ($1004)
   tb=0x1800000;
   for(ta=0;ta<0x40100;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }
   if(!load_rom("d84-20.rom", ROM, 0x40100)) return;	// 16x16 SPRITES
   tb=0x1800002;
   for(ta=0;ta<0x40100;ta++,tb+=4){
      WriteWord(&GFX_SPR[tb],((ROM[ta])|(ROM[ta]<<4))&0x0F0F);
   }

   tb=0x1800000;
   if(!load_rom("d84-21.rom", ROM, 0x40100)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x40100;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d84-12.rom", ROM, 0x200000)) return;	// 16x16 TILES ($8000)
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d84-13.rom", ROM, 0x200000)) return;	// 16x16 TILES
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d84-14.rom", ROM, 0x200000)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x200000;ta+=2){
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
   tb=0x800000;
   if(!load_rom("d84-16.rom", ROM, 0x6EB80)) return;	// 16x16 TILES ($1BAE)
   for(ta=0;ta<0x6EB80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0x800004;
   if(!load_rom("d84-17.rom", ROM, 0x6EB80)) return;	// 16x16 TILES
   for(ta=0;ta<0x6EB80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0x800000;
   if(!load_rom("d84-18.rom", ROM, 0x6EB80)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x6EB80;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x09BAE);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x19004);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

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

   if(!load_rom_index(24, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom_index(23, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom_index(22, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom_index(21, RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xc00000))) return;
   load_be("d84-01.rom",PCMROM,0x200000);
   load_be("d84-02.rom",PCMROM+0x400000,0x200000);
   max_banks_this_game=4;
   memset(PCMROM+0x800000,0,0x3fffff);
   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   if(is_current_game("kaiserkn")){

   // FIX ROM CHECKSUM

   WriteWord68k(&ROM[0x11CE],0x4E75);		//	rts

   // EEPROM HACKS

   WriteWord68k(&ROM[0xC30C],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0xC30E],0x4E75);		//	rts

   WriteWord68k(&ROM[0xC388],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0xC38A],0x4E75);		//	rts

   // SPEED HACK#1

   WriteLong68k(&ROM[0x0534],0x4E714E71);

   WriteLong68k(&ROM[0x025C],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x0260],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x0264],0x60EC);

   }
   else{

   // FIX ROM CHECKSUM

   WriteWord68k(&ROM[0x11F4],0x4E75);		//	rts

   // EEPROM HACKS

   WriteWord68k(&ROM[0xD93A],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0xD93C],0x4E75);		//	rts

   WriteWord68k(&ROM[0xD9B6],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0xD9B8],0x4E75);		//	rts

   // SPEED HACK#1

   WriteLong68k(&ROM[0x052E],0x4E714E71);

   WriteLong68k(&ROM[0x025C],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x0260],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x0264],0x60EC);

   }

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

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_6BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void DrawKaiserKnuckle(void)
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
static struct VIDEO_INFO video_kaiserkn =
{
   DrawKaiserKnuckle,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_kaiserkn[] =
{
   { "kaiser_knuckle", },
   { "kaiserkn", },
   { NULL, },
};
GAME( kaiserkn, "Kaiser Knuckle", TAITO, 1994, GAME_BEAT,
	.romsw = romsw_kaiserkn,
	.video = &video_kaiserkn,
	.long_name_jpn = "カイザーナックル",
	.board = "D84",
);
static struct DIR_INFO dir_dankuga[] =
{
   { "dankuga", },
   { ROMOF("kaiserkn"), },
   { CLONEOF("kaiserkn"), },
   { NULL, },
};
CLNE( dankuga,kaiserkn, "Dankuga", TAITO, 1994, GAME_BEAT,
	.romsw = romsw_dankuga,
	.video = &video_kaiserkn,
	.long_name_jpn = "カイザーナックル (alternate)",
	.board = "D84",
);

