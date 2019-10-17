/******************************************************************************/
/*                                                                            */
/*                   POP'N POP (C) 1997 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_popnpopj[] =
{
   {    "e51-12.20", 0x00080000, 0x86a237d5, REGION_ROM1, 0x000000, LOAD_8_32, },
   {    "e51-11.19", 0x00080000, 0x8a49f34f, REGION_ROM1, 0x000001, LOAD_8_32, },
   {    "e51-10.18", 0x00080000, 0x4bce68f8, REGION_ROM1, 0x000002, LOAD_8_32, },
   {    "e51-09.17", 0x00080000, 0x4a086017, REGION_ROM1, 0x000003, LOAD_8_32, },
   {     "e51-01.4", 0x00100000, 0x70347e24, 0, 0, 0, },
   {     "e51-02.8", 0x00100000, 0x6aa8b96c, 0, 0, 0, },
   {    "e51-03.12", 0x00100000, 0xa24c4607, 0, 0, 0, },
   {    "e51-04.38", 0x00200000, 0x66790f55, 0, 0, 0, },
   {    "e51-05.41", 0x00200000, 0x4d08b26d, 0, 0, 0, },
   {    "e51-06.43", 0x00200000, 0xc240d6c8, 0, 0, 0, },
   {    "e51-07.45", 0x00200000, 0x95873e46, 0, 0, 0, },
   {    "e51-08.47", 0x00200000, 0x3ad41f02, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00040000,
               "e51-13.32",  0x3b9e3986,    "e51-14.33",  0x1f9a5015),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_pop_n_pop_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Worldwide",        0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_popnpopj[] =
{
   { 0x0FFFFF, 0x01, romsw_data_pop_n_pop_0 },
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

static void load_popnpopj(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(TMP=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0x5B3A00+0x3EC400))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x5B3A00;

   tb=0;
   if(!load_rom("E51-03.12", TMP, 0xFB100)) return;	// 16x16 SPRITES ($3EC4)
   for(ta=0;ta<0xFB100;ta++){
      GFX_SPR[tb++]=TMP[ta]&15;
      GFX_SPR[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("E51-02.8", TMP, 0xFB100)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xFB100;ta++){
      GFX_SPR[tb++]=TMP[ta]&15;
      GFX_SPR[tb++]=TMP[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("E51-01.4", TMP, 0xFB100)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xFB100;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x30)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("E51-08.47", TMP, 0x16CE80)) return;	// 16x16 TILES ($5B3A)
   for(ta=0;ta<0x16CE80;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("E51-07.45", TMP, 0x16CE80)) return;	// 16x16 TILES
   for(ta=0;ta<0x16CE80;ta+=2){
      GFX_BG0[tb++]=TMP[ta]&15;
      GFX_BG0[tb++]=TMP[ta]>>4;
      GFX_BG0[tb++]=TMP[ta+1]&15;
      GFX_BG0[tb++]=TMP[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("E51-06.43", TMP, 0x16CE80)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x16CE80;ta+=2){
      tc=TMP[ta];
      GFX_BG0[tb+7]|=((tc&0x80)>>7)<<4;
      GFX_BG0[tb+6]|=((tc&0x40)>>6)<<4;
      GFX_BG0[tb+5]|=((tc&0x20)>>5)<<4;
      GFX_BG0[tb+4]|=((tc&0x10)>>4)<<4;
      GFX_BG0[tb+3]|=((tc&0x08)>>3)<<4;
      GFX_BG0[tb+2]|=((tc&0x04)>>2)<<4;
      GFX_BG0[tb+1]|=((tc&0x02)>>1)<<4;
      GFX_BG0[tb+0]|=((tc&0x01)>>0)<<4;
      tc=TMP[ta+1];
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

   FreeMem(TMP);

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("e51-04.38",PCMROM,0x200000);
   load_be("e51-05.41",PCMROM+0x400000,0x200000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(GFX_BG0+0x243E00,0x00,0x100);			// BG3 Transparency Mask Tile?

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x5B3A);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x3EC4);

   GFX_BG0_PENS = make_colour_count_16x16(GFX_BG0, 0x5B3A);
   GFX_SPR_PENS = make_colour_count_16x16(GFX_SPR, 0x3EC4);

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

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x001C6E],0x7F00);		//	raine	#$00	<eeprom read/write>
   WriteWord68k(&ROM[0x001C70],0x4ED6);		//	jmp	(a6)

   // SPEED HACKS
   // -----------

   WriteWord68k(&ROM[0x000984],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x000986],0x4E71);		//	nop
   WriteWord68k(&ROM[0x000988],0x4E71);		//	nop
   WriteWord68k(&ROM[0x00098A],0x4E71);		//	nop

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;

   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
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
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x18;

   tc0200obj.cols	= 64;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void clear_pop_n_pop(void)
{
   save_eeprom();
}

static void execute_popnpopj(void)
{
  int ta;
  Interrupt68020(3);		// Interrupt#3 [Video Start]
  cycles = 1;
  for (ta=0; ta<f3_slices; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(1600000/f3_slices);
      print_debug("PC0:%06x SR:%04x\n",regs.pc,regs.sr);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
  }

  IntF3System();
}

static void draw_pop_n_pop(void)
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
static struct VIDEO_INFO video_popnpopj =
{
   draw_pop_n_pop,
   320,
   232,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_popnpopj[] =
{
   { "pop_n_pop", },
   { "popnpop", },
   { "popnpopj", },
   { NULL, },
};
GAME( popnpopj, "Pop'n Pop", TAITO, 1997, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_popnpopj,
	.clear = clear_pop_n_pop,
	.video = &video_popnpopj,
	.exec = execute_popnpopj,
	.long_name_jpn = "‚Û‚Á‚Õ‚¤‚Û‚Á‚Õ",
	.board = "E51",
	.sound = f3_sound,
);

