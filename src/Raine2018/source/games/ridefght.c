/******************************************************************************/
/*                                                                            */
/*                   RIDING FIGHT (C) 1992 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "files.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_ridingf[] =
{
   {   "d34-01.66", 0x00200000, 0x7974e6aa, 0, 0, 0, },
   {   "d34-02.67", 0x00200000, 0xf4422370, 0, 0, 0, },
   {   "d34-03.17", 0x00200000, 0xe534ef74, 0, 0, 0, },
   {   "d34-04.18", 0x00100000, 0xed894fe1, 0, 0, 0, },
   {   "d34-05.49", 0x00080000, 0x72e3ee4b, 0, 0, 0, },
   {   "d34-06.50", 0x00080000, 0xedc9b9f3, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
              "d34-07.5",  0x67239e2b,   "d34-08.6",  0x2cf20323),
   {   "d34-10.36", 0x00040000, 0x8aa3f4ac, 0, 0, 0, },
   {   "d34-11.38", 0x00040000, 0x7d240a88, 0, 0, 0, },
   {   "d34-12.40", 0x00040000, 0xe67e69d4, 0, 0, 0, },
   {   "d34_14.34", 0x00040000, 0xe000198e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_riding_fight_0[] =
{
   { "Taito 1",               0x01 },
   { "Taito 2",               0x02 },
   { "Taito 3",               0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_ridingf[] =
{
   { 0x0FFFFF, 0x03, romsw_data_riding_fight_0 },
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

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_ridingf(void)
{
   int ta,tb;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x180000))) return;
   if(!(GFX=AllocateMem(0x5FB800+0x1F7000))) return;

   GFX_BG0 = GFX+0x5FB800;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("d34-01.66", ROM, 0x17EE00)) return;	// 16x16 SPRITES ($5FB8)
   for(ta=0;ta<0x17EE00;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d34-02.67", ROM, 0x17EE00)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x17EE00;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }

   tb=0;
   if(!load_rom("d34-05.49", ROM, 0x7DC00)) return;	// 16x16 TILES ($1F70)
   for(ta=0;ta<0x7DC00;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d34-06.50", ROM, 0x7DC00)) return;	// 16x16 TILES
   for(ta=0;ta<0x7DC00;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }

   FreeMem(ROM);
   if(!(ROM=AllocateMem(0x100000))) return;

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x1F70);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x5FB8);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x36000;
   RAM_BG3=RAM+0x34000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A006;
   RAM_SCR3=RAM+0x6A004;

   if(!load_rom("d34-12.40", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom("d34-11.38", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom("d34-10.36", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom("d34_14.34", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("d34-03.17",PCMROM,0x200000);
   load_be("d34-04.18",PCMROM+0x400000,0x100000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;

   memset(PCMROM+0x600000,0,0x1fffff);
   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;

   set_colour_mapper(&col_map_12bit_rgbxxxx);
   InitPaletteMap(RAM+0x60000, 0x200, 0x10, 0x4000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 224;
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
   tc0200obj.bmp_h	= 224;
// Mapper disabled
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;	//-0x2E;
   tc0200obj.ofs_y	= 0;	//-0x18;

   tc0200obj.cols	= 16;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void execute_ridingf(void)
{
  int ta;

  cycles = 1;
  for (ta=0; ta<f3_slices/2; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(214000/f3_slices);
      print_debug("[BEFORE INT2] PC:%06x SR:%04x\n",regs.pc,regs.sr);
    }
#if 0
    // For some reason sound does seem to hang the whole thing...
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
#endif
  }

  Interrupt68020(2);
  cycles = 1;
  for (ta=0; ta<f3_slices/2; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(214000/f3_slices);
      print_debug("[BEFORE INT3] PC:%06x SR:%04x\n",regs.pc,regs.sr);
    }
#if 0
    if (RaineSoundCard) {
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps)
      if (int7_active)
	f3_timer_callback();
    }
#endif
  }
  Interrupt68020(3);

  IntF3System();
}

static void DrawRideFght(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   zzz=(ReadWord68k(&RAM_SCR0[0])>>6)-0xFFD8;	//+40;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR0[8])>>7);
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         16,
         MAP
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP); break;
      }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   zzz=(ReadWord68k(&RAM_SCR1[0])>>6)-0xFFDC;	//+32;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR1[8])>>7);
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         16,
         MAP
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

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg2_id)){
   zzz=(ReadWord68k(&RAM_SCR2[0])>>6)-0xFFE4;	//+27;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR2[8])>>7);
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG2[zz])&0x1FF,
         16,
         MAP
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

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   zzz=(ReadWord68k(&RAM_SCR3[0])>>6)-0xFFE0;	//+22;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR3[8])>>7);
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG3[zz])&0x1FF,
         16,
         MAP
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

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zzzz=(zzzz+0x100)&0x1FFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg6_id)){

   zz=(ReadWord68k(&RAM_SCR0[8])>>7)+17;
   zz&=0xFF;				// Y Offset (0-255)

      MAP_PALETTE_MAPPED_NEW(
         16,
         16,
         MAP
      );

   if(zz<=48){

   zzzz=zz<<2;
   zzzz+=0x50000;
   for(x=64;x<(320+64);x+=8){
      Draw8xH_Trans_Packed_Mapped_FlipY_Rot(&RAM[zzzz],x,64+16,208,MAP);
      zzzz+=0x400;
   }

   }
   else{

   zzzz=zz<<2;
   zzzz+=0x50000;
   for(x=64;x<(320+64);x+=8){
      Draw8xH_Trans_Packed_Mapped_FlipY_Rot(&RAM[zzzz],x,64+16,256-zz,MAP);
      Draw8xH_Trans_Packed_Mapped_FlipY_Rot(&RAM[zzzz+((256-zz)<<2)-0x400],x,64+16+(256-zz),208-(256-zz),MAP);
      zzzz+=0x400;
   }

   }

   }

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_ridingf =
{
   DrawRideFght,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ridingf[] =
{
   { "riding_fight", },
   { "ridefght", },
   { "ridingf", },
   { NULL, },
};
GAME( ridingf, "Riding Fight", TAITO, 1992, GAME_BEAT | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs,
	.romsw = romsw_ridingf,
	.video = &video_ridingf,
	.exec = execute_ridingf,
	.board = "D34",
	.sound = f3_sound,
);

