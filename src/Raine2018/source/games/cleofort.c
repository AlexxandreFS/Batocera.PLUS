/******************************************************************************/
/*                                                                            */
/*              CLEOPATRA'S FORTUNE (C) 1996 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_cleopatr[] =
{
   {   "e28-01.bin", 0x00080000, 0x4440e659, 0, 0, 0, },
   {   "e28-02.bin", 0x00080000, 0xb20d47cb, 0, 0, 0, },
   {   "e28-03.bin", 0x00200000, 0x15c7989d, 0, 0, 0, },
   {   "e28-04.bin", 0x00100000, 0x57aef029, 0, 0, 0, },
   {   "e28-05.bin", 0x00100000, 0x2870dbbc, 0, 0, 0, },
   {   "e28-06.bin", 0x00100000, 0x21d0c454, 0, 0, 0, },
   {   "e28-07.bin", 0x00080000, 0xa507797b, 0, 0, 0, },
   {   "e28-08.bin", 0x00080000, 0x7564f199, 0, 0, 0, },
   {   "e28-09.bin", 0x00080000, 0x1c48a1f9, 0, 0, 0, },
   {   "e28-10.bin", 0x00080000, 0x013fbc39, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "e28-11.bin",  0x01a06950,   "e28-12.bin",  0xdc19260f),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_cleopatras_fortune_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito Worldwide",       0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_cleopatr[] =
{
   { 0x07FFFF, 0x01, romsw_data_cleopatras_fortune_0 },
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

static void load_cleopatr(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(GFX=AllocateMem(0x2DBA00+0x0FC000))) return;
   if(!(ROM=AllocateMem(0xB6E80))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x2DBA00;

   tb=0;
   if(!load_rom("e28-02.bin", ROM, 0x3F000)) return;	// 16x16 SPRITES ($0FC0)
   for(ta=0;ta<0x3F000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("e28-01.bin", ROM, 0x3F000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x3F000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }

   memset(GFX_SPR+0x25200,0x00,0x100);			// Transparent Green Layer

   tb=0;
   if(!load_rom("e28-06.bin", ROM, 0xB6E80)) return;	// 16x16 TILES ($2DBA)
   for(ta=0;ta<0xB6E80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("e28-05.bin", ROM, 0xB6E80)) return;	// 16x16 TILES
   for(ta=0;ta<0xB6E80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("e28-04.bin", ROM, 0xB6E80)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xB6E80;ta+=2){
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

   FreeMem(ROM);
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x80000))) return;

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x2DBA);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x0FC0);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x80000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG3=RAM+0x33000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;

   SCR0_XOFS=0xF600;
   SCR1_XOFS=0xF700;
   SCR2_XOFS=0xF800;
   SCR3_XOFS=0xF900;

   SCR0_YOFS=0x0780-(16<<7);
   SCR1_YOFS=0x0780-(16<<7);
   SCR2_YOFS=0x0780-(16<<7);
   SCR3_YOFS=0x0780-(16<<7);

   if(!load_rom("e28-10.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("e28-09.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("e28-08.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("e28-07.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x400000))) return;
   load_be("e28-03.bin",PCMROM,0x200000);
   max_banks_this_game=1; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM ERROR
   // -------------

   WriteWord68k(&ROM[0x000D7E],0x4E71);		//	nop

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x00425E],0x7F00);		//	raine	#$00 <read eeprom>
   WriteWord68k(&ROM[0x004260],0x4E75);		//	rts

   WriteWord68k(&ROM[0x0042DC],0x7F01);		//	raine	#$01 <write eeprom>
   WriteWord68k(&ROM[0x0042DE],0x4E75);		//	rts

   // SPEED HACK#1
   // ------------

   WriteLong68k(&ROM[0x0053A],0x4E714E71);

   WriteWord68k(&ROM[0x0025A],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x0025C],0x60EC+6);

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;

   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   tc0003vcu.mapper	= &Map_24bit_xRGB;
   // &Map_21bit_xRGB;
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
   tc0200obj.mapper	= &Map_24bit_xRGB;
   // Map_21bit_xRGB;
   tc0200obj.tile_mask	= 0x0FFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= -16;	//-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void ClearCleoFortune(void)
{
   save_eeprom();
}

static void execute_cleopatr(void)
{
  int ta;
  cycles = 1;
  for (ta=0; ta<f3_slices; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(300000/f3_slices);
    }
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
  }
  Interrupt68020(2);

  IntF3System();
}

static void DrawCleoFortune(void)
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
               64,        MAP
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
               64,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         (*Draw16x16_Trans_Mapped_Flip_Rot[3-((RAM_BG1[zz]&0xC0)>>6)])(&GFX_BG0[ta<<8],x,y,MAP);
      }
      else{
         (*Draw16x16_Mapped_Flip_Rot[3-((RAM_BG1[zz]&0xC0)>>6)])(&GFX_BG0[ta<<8],x,y,MAP);
      }
   }

   END_SCROLL_512x512_4_16();
   }

   set_colour_mapper(&col_map_21bit_xRGB);
   render_tc0200obj_mapped_f3system_r180();
   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);

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
               64,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         (*Draw16x16_Trans_Mapped_Flip_Rot[3-((RAM_BG2[zz]&0xC0)>>6)])(&GFX_BG0[ta<<8],x,y,MAP);
      }
      else{
         (*Draw16x16_Mapped_Flip_Rot[3-((RAM_BG2[zz]&0xC0)>>6)])(&GFX_BG0[ta<<8],x,y,MAP);
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
               64,        MAP
            );

      if(GFX_BG0_SOLID[ta]==0){
         (*Draw16x16_Trans_Mapped_Flip_Rot[3-((RAM_BG3[zz]&0xC0)>>6)])(&GFX_BG0[ta<<8],x,y,MAP);
      }
      else{
         (*Draw16x16_Mapped_Flip_Rot[3-((RAM_BG3[zz]&0xC0)>>6)])(&GFX_BG0[ta<<8],x,y,MAP);
      }
   }

   END_SCROLL_512x512_4_16();
   }

   if(check_layer_enabled(f3_bg5_id)){
     set_colour_mapper(&col_map_21bit_xRGB);
     f3video_render_fg0_r180();
     set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   }
}
static struct VIDEO_INFO video_cleopatr =
{
   DrawCleoFortune,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_cleopatr[] =
{
   { "cleopatras_fortune", },
   { "cleofort", },
   { "cleopatr", },
   { NULL, },
};
GAME( cleopatr, "Cleopatra's Fortune", TAITO, 1996, GAME_PUZZLE,
	.input = f3_system_inputs,
	.romsw = romsw_cleopatr,
	.clear = ClearCleoFortune,
	.video = &video_cleopatr,
	.exec = execute_cleopatr,
	.long_name_jpn = "クレオパトラ・フォーチュン",
	.board = "E28",
	.sound = f3_sound,
);

