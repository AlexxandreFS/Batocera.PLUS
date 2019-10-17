/******************************************************************************/
/*                                                                            */
/*                GUN LOCK/RAY FORCE (C) 1995 TAITO CORPORATION               */
/*                                                                            */
/******************************************************************************/

#define DRV_DEF_INPUT f3_system_inputs
#define DRV_DEF_SOUND f3_sound
#define DRV_DEF_DSW NULL

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"

/******************
   GUN LOCK WORLD
 ******************/


static struct ROM_INFO rom_gunlock[] =
{
   {   "d66-01.rom", 0x00200000, 0x58c92efa, 0, 0, 0, },
   {   "d66-02.rom", 0x00200000, 0xdcdafaab, 0, 0, 0, },
   {   "d66-03.rom", 0x00100000, 0xe7a4a491, 0, 0, 0, },
   {   "d66-04.rom", 0x00100000, 0xc1c7aaa7, 0, 0, 0, },
   {   "d66-05.rom", 0x00100000, 0xa3cefe04, 0, 0, 0, },
   {   "d66-06.rom", 0x00100000, 0xb3d8126d, 0, 0, 0, },
   {   "d66-07.rom", 0x00100000, 0xa6da9be7, 0, 0, 0, },
   {   "d66-08.rom", 0x00100000, 0x9959f30b, 0, 0, 0, },
   {   "d66-18.rom", 0x00040000, 0x8418513e, 0, 0, 0, },
   {   "d66-19.rom", 0x00040000, 0x95731473, 0, 0, 0, },
   {   "d66-21.rom", 0x00040000, 0xbd0d60f2, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d66-23.rom",  0x57fb7c49,   "d66-22.rom",  0x83dd7f9b),
   {   "d66-24.rom", 0x00040000, 0x97816378, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

/*
static struct ROMSW_DATA romsw_data_gun_lock_0[] =
{
   { "Taito Japan (Ray Force)",  0x01 },
   { "Taito America (Ray Force)",0x02 },
   { "Taito Japan (Gun Lock)",   0x03 },
   { NULL,                       0    },
};

static struct ROMSW_INFO romsw_gun_lock[] =
{
   { 0x0FFFFF, 0x03, romsw_data_gun_lock_0 },
   { 0,        0,    NULL },
};
*/



/*****************
   RAY FORCE US
 *****************/


static struct ROM_INFO rom_rayforce[] =
{
   {   "d66-01.rom", 0x00200000, 0x58c92efa, 0, 0, 0, },
   {   "d66-02.rom", 0x00200000, 0xdcdafaab, 0, 0, 0, },
   {   "d66-03.rom", 0x00100000, 0xe7a4a491, 0, 0, 0, },
   {   "d66-04.rom", 0x00100000, 0xc1c7aaa7, 0, 0, 0, },
   {   "d66-05.rom", 0x00100000, 0xa3cefe04, 0, 0, 0, },
   {   "d66-06.rom", 0x00100000, 0xb3d8126d, 0, 0, 0, },
   {   "d66-07.rom", 0x00100000, 0xa6da9be7, 0, 0, 0, },
   {   "d66-08.rom", 0x00100000, 0x9959f30b, 0, 0, 0, },
   {   "d66-18.rom", 0x00040000, 0x8418513e, 0, 0, 0, },
   {   "d66-19.rom", 0x00040000, 0x95731473, 0, 0, 0, },
   {   "d66-21.rom", 0x00040000, 0xbd0d60f2, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d66-23.rom",  0x57fb7c49,   "d66-22.rom",  0x83dd7f9b),
   {  "gunlocku.35", 0x00040000, 0xe08653ee, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


/*******************
   RAY FORCE JAPAN
 *******************/


static struct ROM_INFO rom_rayforcj[] =
{
   {   "d66-01.rom", 0x00200000, 0x58c92efa, 0, 0, 0, },
   {   "d66-02.rom", 0x00200000, 0xdcdafaab, 0, 0, 0, },
   {   "d66-03.rom", 0x00100000, 0xe7a4a491, 0, 0, 0, },
   {   "d66-04.rom", 0x00100000, 0xc1c7aaa7, 0, 0, 0, },
   {   "d66-05.rom", 0x00100000, 0xa3cefe04, 0, 0, 0, },
   {   "d66-06.rom", 0x00100000, 0xb3d8126d, 0, 0, 0, },
   {   "d66-07.rom", 0x00100000, 0xa6da9be7, 0, 0, 0, },
   {   "d66-08.rom", 0x00100000, 0x9959f30b, 0, 0, 0, },
   {   "d66-18.rom", 0x00040000, 0x8418513e, 0, 0, 0, },
   {   "d66-19.rom", 0x00040000, 0x95731473, 0, 0, 0, },
   {   "d66-21.rom", 0x00040000, 0xbd0d60f2, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
              "d66-23.rom",  0x57fb7c49,   "d66-22.rom",  0x83dd7f9b),
   {    "d66-20.35", 0x00040000, 0x798f0254, 0, 0, 0, },
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

static void load_gunlock(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x3C8800+0x3DA100))) return;

   GFX_BG0 = GFX+0x3C8800;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("d66-03.rom", ROM, 0xF2200)) return;	// 16x16 SPRITES ($3C88)
   for(ta=0;ta<0xF2200;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d66-04.rom", ROM, 0xF2200)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xF2200;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d66-05.rom", ROM, 0xF2200)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xF2200;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d66-06.rom", ROM, 0xF6840)) return;	// 16x16 TILES ($3DA1)
   for(ta=0;ta<0xF6840;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d66-07.rom", ROM, 0xF6840)) return;	// 16x16 TILES
   for(ta=0;ta<0xF6840;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d66-08.rom", ROM, 0xF6840)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xF6840;ta+=2){
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

   Rotate16x16(GFX_SPR,0x3C88);
   Flip16x16_X(GFX_SPR,0x3C88);
   Rotate16x16(GFX_BG0,0x3DA1);
   Flip16x16_X(GFX_BG0,0x3DA1);

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x3DA1);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3C88);

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

   SCR0_XOFS=0xF640;
   SCR1_XOFS=0xF740;
   SCR2_XOFS=0xF840;
   SCR3_XOFS=0xF940;

   SCR0_YOFS=0xFF80;
   SCR1_YOFS=0xFF80;
   SCR2_YOFS=0xFF80;
   SCR3_YOFS=0xFF80;

   if(!load_rom("d66-18.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d66-19.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d66-21.rom", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom_index(13, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   Rotate8x8_4bpp(ROM+0xD857C,(0xDA69C-0xD857C)/0x20);
   Flip8x8_4bpp_X(ROM+0xD857C,(0xDA69C-0xD857C)/0x20);

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("d66-01.rom",PCMROM,0x200000);
   load_be("d66-02.rom",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM ERROR
   // -------------

   WriteWord68k(&ROM[0x0017B8],0x4E75);		//	rts

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x00417C],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x00417E],0x4E75);		//	rts

   WriteWord68k(&ROM[0x004200],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x004202],0x4E75);		//	rts

   // SPEED HACKS (100%)
   // ------------------

   WriteWord68k(&ROM[0x000B00],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x000BE4],0x7F02);		//	raine	#$02 <stop cpu>

   WriteWord68k(&ROM[0x000646],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x000648],0x6100-14);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x000C48],0x4E71);		//	nop
   WriteWord68k(&ROM[0x000C4A],0x4E71);		//	nop

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
   tc0200obj.bmp_w	= 224;
   tc0200obj.bmp_h	= 320;
// Mapper disabled
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0x71 - 1;
   tc0200obj.ofs_y	= 180+48-64;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void execute_gunlock(void)
{
  int ta;
  cycles = 1;
  for (ta=0; ta<f3_slices/2; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(800000/f3_slices);
      print_debug("PC1:%06x SR:%04x\n",regs.pc,regs.sr);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
  }

  Interrupt68020(2);

  cycles = 1;
  for (ta=0; ta<f3_slices/2; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(800000/f3_slices);
      print_debug("PC2:%06x SR:%04x\n",regs.pc,regs.sr);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
  }
  IntF3System();
}


static void DrawGunLock(void)
{
   UINT8 *MAP;
   int x16,y16;
   int x,y,zz,zzz,zzzz;
   int ta;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_1024x512_4_16_R(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG0[zz])&0x1FF,
               32,        MAP
            );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x3FFF)<<8],(224+128-16)-y,x,MAP); break;
      }

      zz=(zz&0x1F00)|((zz-4)&0xFF);
   }
   zzzz=(zzzz-0x100)&0x1FFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_1024x512_4_16_R(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG1[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
      else{
         switch(RAM_BG1[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
   }

      zz=(zz&0x1F00)|((zz-4)&0xFF);
   }
   zzzz=(zzzz-0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_1024x512_4_16_R(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG2[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
      else{
         switch(RAM_BG2[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
   }

      zz=(zz&0x1F00)|((zz-4)&0xFF);
   }
   zzzz=(zzzz-0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_1024x512_4_16_R(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   zz=zzzz;

   for(y=(64-y16);y<(224+64);y+=16){
   for(x=(64-x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x3FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               ReadWord68k(&RAM_BG3[zz])&0x1FF,
               32,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
      else{
         switch(RAM_BG3[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8],(224+128-16)-y,x,MAP); break;
         }
      }
   }

      zz=(zz&0x1F00)|((zz-4)&0xFF);
   }
   zzzz=(zzzz-0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   render_tc0200obj_mapped_f3system_r270_b();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_r270();
   }
}
static struct VIDEO_INFO video_gunlock =
{
   DrawGunLock,
   224,
   320,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_gunlock[] =
{
   { "gun_lock", },
   { "gunlock", },
   { NULL, },
};
GAME( gunlock, "Gun Lock", TAITO, 1993, GAME_SHOOT,
	.video = &video_gunlock,
	.exec = execute_gunlock,
	.long_name_jpn = "レイフォース",
	.board = "D66",
);
static struct DIR_INFO dir_rayforcj[] =
{
   { "ray_force_jp", },
   { "rayforcj", },
   { ROMOF("gunlock"), },
   { CLONEOF("gunlock"), },
   { NULL, },
};
CLNE( rayforcj, gunlock,"Ray Force (Japan)", TAITO, 1993, GAME_SHOOT,
	.long_name_jpn = "レイフォース (Japan)",
	.board = "D66",
);
static struct DIR_INFO dir_rayforce[] =
{
   { "ray_force", },
   { "rayforce", },
   { ROMOF("gunlock"), },
   { CLONEOF("gunlock"), },
   { NULL, },
};
CLNE( rayforce, gunlock,"Ray Force (US)", TAITO, 1993, GAME_SHOOT,
	.long_name_jpn = "レイフォース (US)",
	.board = "D66",
);

