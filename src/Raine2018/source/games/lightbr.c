/******************************************************************************/
/*                                                                            */
/*                 LIGHT BRINGER (C) 1997 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_lightbr[] =
{
   {   "d69-20.bin", 0x00080000, 0x33650fe4, REGION_ROM1, 0x000000, LOAD_8_32, },
   {   "d69-13.bin", 0x00080000, 0xdec2ec17, REGION_ROM1, 0x000001, LOAD_8_32, },
   {   "d69-15.bin", 0x00080000, 0x323e1955, REGION_ROM1, 0x000002, LOAD_8_32, },
   {   "d69-14.bin", 0x00080000, 0x990bf945, REGION_ROM1, 0x000003, LOAD_8_32, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d69-18.bin",  0x04600d7b,   "d69-19.bin",  0x1484e853),
   {   "d69-01.bin", 0x00200000, 0x9ac93ac2, 0, 0, 0, },
   {   "d69-02.bin", 0x00200000, 0xdce28dd7, 0, 0, 0, },
   {   "d69-03.bin", 0x00200000, 0x6999c86f, 0, 0, 0, },
   {   "d69-04.bin", 0x00200000, 0xcc91dcb7, 0, 0, 0, },
   {   "d69-05.bin", 0x00200000, 0xf9f5433c, 0, 0, 0, },
   {   "d69-06.bin", 0x00200000, 0xcb4aac81, 0, 0, 0, },
   {   "d69-07.bin", 0x00200000, 0xb749f984, 0, 0, 0, },
   {   "d69-08.bin", 0x00200000, 0x5b68d7d8, 0, 0, 0, },
   {   "d69-09.bin", 0x00100000, 0xa96c19b8, 0, 0, 0, },
   {   "d69-10.bin", 0x00100000, 0x36aa80c6, 0, 0, 0, },
   {   "d69-11.bin", 0x00100000, 0xc11adf92, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_light_bringer_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Worldwide",        0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_lightbr[] =
{
   { 0x0FFFFF, 0x01, romsw_data_light_bringer_0 },
   { 0,        0,    NULL },
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
static UINT8 *GFX_BG0_PENS;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;
static UINT8 *GFX_SPR_PENS;

static void load_lightbr(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x587B00+0x9C4D00))) return;
   if(!(TMP=AllocateMem(0x200000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x587B00;

   tb=0;
   if(!load_rom("d69-06.bin", TMP, 0x200000)) return;	// 16x16 SPRITES ($8000)
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=TMP[ta]&15;
      GFX_SPR[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d69-09.bin", TMP, 0x071340)) return;	// 16x16 SPRITES ($1C4D)
   for(ta=0;ta<0x071340;ta++){
      GFX_SPR[tb++]=TMP[ta]&15;
      GFX_SPR[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d69-07.bin", TMP, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=TMP[ta]&15;
      GFX_SPR[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d69-10.bin", TMP, 0x071340)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x071340;ta++){
      GFX_SPR[tb++]=TMP[ta]&15;
      GFX_SPR[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d69-08.bin", TMP, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+3]|=((tc&0x40)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x10)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x04)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }
   if(!load_rom("d69-11.bin", TMP, 0x071340)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x071340;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+3]|=((tc&0x40)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x10)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x04)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d69-03.bin", TMP, 0x161EC0)) return;	// 16x16 TILES ($587B)
   for(ta=0;ta<0x161EC0;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d69-04.bin", TMP, 0x161EC0)) return;	// 16x16 TILES
   for(ta=0;ta<0x161EC0;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d69-05.bin", TMP, 0x161EC0)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x161EC0;ta+=2){
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

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x587B);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x9C4D);

   GFX_BG0_PENS = make_colour_count_16x16(GFX_BG0, 0x587B);
   GFX_SPR_PENS = make_colour_count_16x16(GFX_SPR, 0x9C4D);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x200000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x34000;
   RAM_BG3=RAM+0x36000;
   RAM_BG4=RAM+0x50000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR0_XOFS=0xF600;
   SCR1_XOFS=0xF700;
   SCR2_XOFS=0xF800;
   SCR3_XOFS=0xF900;
   SCR4_XOFS=0x0029-1;

   SCR0_YOFS=0xFF80;
   SCR1_YOFS=0xFF80;
   SCR2_YOFS=0xFF80;
   SCR3_YOFS=0xFF80;
   SCR4_YOFS=0x0018-1;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("d69-01.bin",PCMROM,0x200000);
   load_be("d69-02.bin",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS

   WriteWord68k(&ROM[0x0E3A3C],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x0E3A3E],0x4E75);		//	rts

   WriteWord68k(&ROM[0x0E3AB8],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x0E3ABA],0x4E75);		//	rts

   // SPEED HACK

   WriteWord68k(&ROM[0x0E0AFE],0x4EB9);		//	jsr	$123456
   WriteWord68k(&ROM[0x0E0B00],0x000D);		//
   WriteWord68k(&ROM[0x0E0B02],0xFFF0);		//

   WriteWord68k(&ROM[0x0DFFF0],0x4A2D);		//	tst.b	-32461(a5)
   WriteWord68k(&ROM[0x0DFFF2],0x8133);		//
   WriteWord68k(&ROM[0x0DFFF4],0x6704);		//	beq.s	+4
   WriteWord68k(&ROM[0x0DFFF6],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x0DFFF8],0x60F6);		//	bra.s	-10
   WriteWord68k(&ROM[0x0DFFFA],0x4E75);		//	rts

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;

   InitPaletteMap(RAM+0x60000, 0x200, 0x10, 0x8000);

   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);

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
   tc0200obj.tile_mask	= 0xFFFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void execute_lightbr(void)
{
  int ta;
  IntF3System();

  cpu_interrupt(CPU_M68020_0, 3); // Interrupt#3 [Video Start]
  cpu_execute_cycles(CPU_M68020_0, 600000);
  cpu_interrupt(CPU_M68020_0, 2); // Interrupt#2 [Video End]
  cycles = 1;
  for (ta=0; ta<f3_slices; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      cpu_execute_cycles(CPU_M68020_0, 1600000/f3_slices);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16, 60 * f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
  }
}

static void draw_light_bringer(void)
{
   UINT8 *map;
   int x,y,ta,zz,zzz,zzzz,x16,y16;

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

      ta=ReadWord68k(&RAM_BG0[zz+2])&0x7FFF;

      MAP_PALETTE_MULTI_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         GFX_BG0_PENS[ta],
         map
      );

      Draw16x16_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG0[zz]>>6);

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

         MAP_PALETTE_MULTI_MAPPED_NEW(
            ReadWord68k(&RAM_BG1[zz])&0x1FF,
            GFX_BG0_PENS[ta],
            map
         );

         if(GFX_BG0_SOLID[ta]==1)		// Some pixels; trans
            Draw16x16_Trans_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG1[zz]>>6);
         else					// all pixels; solid
            Draw16x16_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG1[zz]>>6);
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

         MAP_PALETTE_MULTI_MAPPED_NEW(
            ReadWord68k(&RAM_BG2[zz])&0x1FF,
            GFX_BG0_PENS[ta],
            map
         );

         if(GFX_BG0_SOLID[ta]==1)		// Some pixels; trans
            Draw16x16_Trans_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG2[zz]>>6);
         else					// all pixels; solid
            Draw16x16_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG2[zz]>>6);
      }

   END_SCROLL_1024x512_4_16();
   }

   render_tc0200obj_mapped_f3system_b_multi(GFX_SPR_PENS);

   if(check_layer_enabled(f3_bg3_id)){
   //if((RAM[0x46101]&0x80)!=0){
   MAKE_SCROLL_1024x512_4_16(
      (ReadWord68k(&RAM_SCR3[0])-SCR3_XOFS)>>6,
      (ReadWord68k(&RAM_SCR3[8])-SCR3_YOFS)>>7
   );

   START_SCROLL_1024x512_4_16(64,64,320,232);

      ta=ReadWord68k(&RAM_BG3[zz+2])&0x7FFF;
      if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MULTI_MAPPED_NEW(
            ReadWord68k(&RAM_BG3[zz])&0x1FF,
            GFX_BG0_PENS[ta],
            map
         );

         if(GFX_BG0_SOLID[ta]==1)		// Some pixels; trans
            Draw16x16_Trans_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG3[zz]>>6);
         else					// all pixels; solid
            Draw16x16_Mapped_flip_Rot(&GFX_BG0[ta<<8],x,y,map,RAM_BG3[zz]>>6);
      }

   END_SCROLL_1024x512_4_16();
   //}
   }

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0_new();
   }
}
static struct VIDEO_INFO video_lightbr =
{
   draw_light_bringer,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_lightbr[] =
{
   { "light_bringer", },
   { "lightbr", },
   { "lightb", },
   { "dungeonm", },
   { NULL, },
};
GAME( lightbr, "Light Bringer", TAITO, 1996, GAME_BEAT,
	.input = f3_system_inputs,
	.romsw = romsw_lightbr,
	.video = &video_lightbr,
	.exec = execute_lightbr,
	.board = "D69",
	.sound = f3_sound,
);

