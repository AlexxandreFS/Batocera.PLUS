/******************************************************************************/
/*                                                                            */
/*                   LAND MAKER (C) 1998 TAITO CORPORATION                    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"
#include "emumain.h"


static struct ROM_INFO rom_landmakr[] =
{
   {    "e61-01.04", 0x00200000, 0x6cdd8311, 0, 0, 0, },
   {    "e61-02.08", 0x00200000, 0x1dc4a164, 0, 0, 0, },
   {    "e61-03.12", 0x00200000, 0xe8abfc46, 0, 0, 0, },
   {    "e61-04.38", 0x00200000, 0xc27aec0c, 0, 0, 0, },
   {    "e61-05.39", 0x00200000, 0x83920d9d, 0, 0, 0, },
   {    "e61-06.40", 0x00200000, 0x2e717bfe, 0, 0, 0, },
   {    "e61-07.43", 0x00200000, 0x4a57965d, 0, 0, 0, },
   {    "e61-08.45", 0x00200000, 0x76c98e14, 0, 0, 0, },
   {    "e61-09.47", 0x00200000, 0x6ba29987, 0, 0, 0, },
   {    "e61-10.17", 0x00080000, 0xdaabf2b2, 0, 0, 0, },
   {    "e61-11.18", 0x00080000, 0x279a0ee4, 0, 0, 0, },
   {    "e61-12.19", 0x00080000, 0x636b3df9, 0, 0, 0, },
   {    "e61-13.20", 0x00080000, 0x0af756a2, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
               "e61-14.32",  0xb905f4a7,    "e61-15.33",  0x87909869),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_land_maker_0[] =
{
   { "Land Maker v2.01 (Japanese)", 0x01 },
   { "Land Maker v2.01 (American)", 0x02 },
   { "Land Maker v2.01 (Overseas)", 0x03 },
   { NULL,                          0    },
};

static struct ROMSW_INFO romsw_landmakr[] =
{
   { 0x1FFFFF, 0x01, romsw_data_land_maker_0 },
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

static void load_landmakr(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0x800000+0x800000))) return;

   GFX_BG0 = GFX+0x800000;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("e61-03.12", ROM, 0x200000)) return;	// 16x16 SPRITES ($7EF0)
   for(ta=0;ta<0x200000;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("e61-02.08", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("e61-01.04", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("e61-09.47", ROM, 0x200000)) return;	// 16x16 TILES ($7F36)
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("e61-08.45", ROM, 0x200000)) return;	// 16x16 TILES
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e61-07.43", ROM, 0x200000)) return;	// 16x16 TILES (MASK)
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

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x8000);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

   RAM_BG0=RAM+0x33000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A006;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A000;

   SCR3_XOFS=0xF600;
   SCR2_XOFS=0xF700;
   SCR1_XOFS=0xF800;
   SCR0_XOFS=0xF900;

   SCR3_YOFS=0xFF80;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xFF80;

   if(!load_rom("e61-13.20", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e61-12.19", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e61-11.18", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("e61-10.17", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0xe00000))) return;
   load_be("e61-04.38",PCMROM,0x200000);
   load_be("e61-06.40",PCMROM+0x400000,0x200000);
   load_be("e61-05.39",PCMROM+0x800000,0x200000);
   max_banks_this_game=5; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0xc00000,0,0x1fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // eeprom hack

   WriteWord68k(&ROM[0x04BD0],0x7F00);		//	raine	#$00 <eeprom access>
   WriteWord68k(&ROM[0x04BD2],0x4ED6);		//	jmp	(a6)

   // speed hack

   WriteWord68k(&ROM[0x019FE],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x01A00],0x6100-10);	//	bra.s	<loop>

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
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= 0;	//-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void execute_landmakr(void)
{
  int ta;
  cycles = 1;
  for (ta=0; ta<f3_slices*2/3; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices)); //1600000/f3_slices);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
  }


  if (ReadWord68k(&ROM[regs.pc]) == 0x60fe)
    reset_game_hardware();
  else {
    Interrupt68020(3);
    cycles = 1;
    for (ta=0; ta<f3_slices/3; ta++) {
      if (cycles) {// cycles = 0 if we reached the speed hack
	cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(16,60*f3_slices)); //1600000/f3_slices);
      }
      if (RaineSoundCard) {
	cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
	if (int7_active)
	  f3_timer_callback();
      }
    }
    Interrupt68020(2);
    Interrupt68020(5);

    IntF3System();
  }
}

static void draw_land_maker(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
   UINT8 *map;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6,
      (ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,232);

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         64,
         map
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x7FFF)<<8],x,y,map); break;
      }

   END_SCROLL_1024x512_4_16();
   }


   if(check_layer_enabled(f3_bg1_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR1[0])-SCR1_XOFS)>>6,
      (ReadWord68k(&RAM_SCR1[8])-SCR1_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG1[zz+2])&0x7FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG1[zz])&0x1FF,
            64,
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

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg2_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR2[0])-SCR2_XOFS)>>6,
      (ReadWord68k(&RAM_SCR2[8])-SCR2_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG2[zz+2])&0x7FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG2[zz])&0x1FF,
            64,
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

   END_SCROLL_1024x512_4_16();
   }

   if(check_layer_enabled(f3_bg3_id)){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG3[zz+2])&0x7FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord68k(&RAM_BG3[zz])&0x1FF,
            64,
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

   END_SCROLL_1024x512_4_16();
   }

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_landmakr =
{
   draw_land_maker,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_landmakr[] =
{
   { "land_maker", },
   { "landmakr", },
   { NULL, },
};
GAME( landmakr, "Land Maker", TAITO, 1998, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_landmakr,
	.video = &video_landmakr,
	.exec = execute_landmakr,
	.board = "E61",
	.sound = f3_sound,
);

