#define DRV_DEF_SOUND f3_sound
/******************************************************************************/
/*                                                                            */
/*               TOP RANKING STARS (C) 1994 TAITO CORPORATION                 */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_trstar[] =
{
   { "d53-01.2", 0x00200000, 0x28fd2d9b, 0, 0, 0, },
   { "d53-02.3", 0x00200000, 0x8bd4367a, 0, 0, 0, },
   { "d53-03.45", 0x00200000, 0x91b66145, 0, 0, 0, },
   { "d53-04.46", 0x00200000, 0xac3a5e80, 0, 0, 0, },
   { "d53-05.47", 0x00200000, 0xb9b68b15, 0, 0, 0, },
   { "d53-06.64", 0x00100000, 0xf4bac410, 0, 0, 0, },
   { "d53-07.65", 0x00100000, 0x2f4773c3, 0, 0, 0, },
   { "d53-08.66", 0x00100000, 0xad13a1ee, 0, 0, 0, },
   { "d53-09.48", 0x00100000, 0x690554d3, 0, 0, 0, },
   { "d53-10.49", 0x00100000, 0x0ec05dc5, 0, 0, 0, },
   { "d53-11.50", 0x00100000, 0x39c0a546, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
            "d53-13.10",  0x877f0361, "d53-14.23",  0xa8664867),
   { "d53-15-1.24", 0x00040000, 0x098bba94, 0, 0, 0, },
   { "d53-16-1.26", 0x00040000, 0x4fa8b15c, 0, 0, 0, },
   { "d53-18-1.37", 0x00040000, 0xaa71cfcc, 0, 0, 0, },
   { "d53-20-1.rom", 0x00040000, 0x4de1e287, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_top_ranking_stars_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_trstar[] =
{
   { 0x0FFFFF, 0x03, romsw_data_top_ranking_stars_0 },
   { 0,        0,    NULL },
};




static struct ROM_INFO rom_prmtmfgo[] =
{
   { "d53-01.2", 0x00200000, 0x28fd2d9b, 0, 0, 0, },
   { "d53-02.3", 0x00200000, 0x8bd4367a, 0, 0, 0, },
   { "d53-03.45", 0x00200000, 0x91b66145, 0, 0, 0, },
   { "d53-04.46", 0x00200000, 0xac3a5e80, 0, 0, 0, },
   { "d53-05.47", 0x00200000, 0xb9b68b15, 0, 0, 0, },
   { "d53-06.64", 0x00100000, 0xf4bac410, 0, 0, 0, },
   { "d53-07.65", 0x00100000, 0x2f4773c3, 0, 0, 0, },
   { "d53-08.66", 0x00100000, 0xad13a1ee, 0, 0, 0, },
   { "d53-09.48", 0x00100000, 0x690554d3, 0, 0, 0, },
   { "d53-10.49", 0x00100000, 0x0ec05dc5, 0, 0, 0, },
   { "d53-11.50", 0x00100000, 0x39c0a546, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
            "d53-13.10",  0x877f0361, "d53-14.23",  0xa8664867),
   {    "d53-15.24", 0x00040000, 0xf24de51b, 0, 0, 0, },
   {    "d53-16.26", 0x00040000, 0xffc84429, 0, 0, 0, },
   {    "d53-18.37", 0x00040000, 0xea2d6e13, 0, 0, 0, },
   {    "d53-19.35", 0x00040000, 0x00e6c2f1, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_INFO romsw_prmtmfgo[] =
{
   { 0x0FFFFF, 0x02, romsw_data_top_ranking_stars_0 },
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

static void load_actual(int romset)
{
   int ta,tb,tc;

   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(GFX=AllocateMem(0xBC0A00+0x366B00))) return;

   GFX_BG0 = GFX+0xBC0A00;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("d53-03.45", ROM, 0x200000)) return;	// 16x16 SPRITES ($BC0A)
   for(ta=0;ta<0x200000;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d53-06.64", ROM, 0xF0280)) return;	// 16x16 SPRITES
   for(ta=0;ta<0xF0280;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d53-04.46", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   if(!load_rom("d53-07.65", ROM, 0xF0280)) return;		// 16x16 SPRITES
   for(ta=0;ta<0xF0280;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d53-05.47", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }
   if(!load_rom("d53-08.66", ROM, 0xF0280)) return;		// 16x16 SPRITES (MASK)
   for(ta=0;ta<0xF0280;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   tb=0;
   if(!load_rom("d53-09.48", ROM, 0xD9AC0)) return;	// 16x16 TILES ($366B)
   for(ta=0;ta<0xD9AC0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d53-10.49", ROM, 0xD9AC0)) return;	// 16x16 TILES
   for(ta=0;ta<0xD9AC0;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d53-11.50", ROM, 0xD9AC0)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0xD9AC0;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x366B);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0xBC0A);

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

   if(!load_rom_index(13, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+0]=RAM[ta];
   }
   if(!load_rom_index(14, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+1]=RAM[ta];
   }
   if(!load_rom_index(15, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+2]=RAM[ta];
   }
   if(!load_rom_index(16, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[(ta<<2)+3]=RAM[ta];
   }

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x1000000))) return;
   load_be("d53-01.2",PCMROM,0x200000);
   load_be("d53-02.3",PCMROM+0xc00000,0x200000);
   max_banks_this_game=7; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0x400000,0,0x7fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   if(romset==0){

   // eeprom hacks

   WriteWord68k(&ROM[0x1D10A],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x1D10C],0x4E75);		//	rts

   WriteWord68k(&ROM[0x1D186],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x1D188],0x4E75);		//	rts

   // speed hacks

   WriteLong68k(&ROM[0x13C8],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x13CC],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x13D0],0x4A2DA612);
   WriteWord68k(&ROM[0x13D4],0x67E6);
   WriteLong68k(&ROM[0x13D6],0x4E714E71);

   }
   else{

   // eeprom hacks

   WriteWord68k(&ROM[0x1D00E],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x1D010],0x4E75);		//	rts

   WriteWord68k(&ROM[0x1D08A],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x1D08C],0x4E75);		//	rts

   // speed hacks

   WriteLong68k(&ROM[0x13BA],0x7F024E71);	// 	raine	#$02 <stop cpu>
   WriteLong68k(&ROM[0x13BE],0x4E714E71);	//	nop

   WriteLong68k(&ROM[0x13C2],0x4A2DA612);
   WriteWord68k(&ROM[0x13C6],0x67E6);
   WriteLong68k(&ROM[0x13C8],0x4E714E71);

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
   tc0200obj.tile_mask	= 0xFFFF;
   tc0200obj.ofs_x	= 0-64;
   tc0200obj.ofs_y	= 0-32;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

static void load_trstar(void)
{
   load_actual(0);
}

static void load_prmtmfgo(void)
{
   load_actual(1);
}

static void execute_trstar(void)
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

  Interrupt68020(3);

  IntF3System();
}

static void DrawTRStars(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   zzz=(ReadWord68k(&RAM_SCR0[0])>>6)+40;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR0[8])>>7)+32;
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;

   for(y=(48+y16);y<(224+64);y+=16){
   zz=zzzz;
   for(x=(48+x16);x<(320+64);x+=16){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         32,
         MAP
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ReadWord68k(&RAM_BG0[zz+2])<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ReadWord68k(&RAM_BG0[zz+2])<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ReadWord68k(&RAM_BG0[zz+2])<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ReadWord68k(&RAM_BG0[zz+2])<<8],x,y,MAP); break;
      }

   zz+=4;
   if((zz&0xFF)==0){zz-=0x100;}
   }
   zzzz+=0x100;
   zzzz&=0x1FFF;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   zzz=(ReadWord68k(&RAM_SCR1[0])>>6)+36;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR1[8])>>7)+32;
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;

   for(y=(48+y16);y<(224+64);y+=16){
   zz=zzzz;
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2]);
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         32,
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

   zz+=4;
   if((zz&0xFF)==0){zz-=0x100;}
   }
   zzzz+=0x100;
   zzzz&=0x1FFF;
   }
   }

   if(check_layer_enabled(f3_bg2_id)){
   zzz=(ReadWord68k(&RAM_SCR2[0])>>6)+32;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR2[8])>>7)+32;
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;

   for(y=(48+y16);y<(224+64);y+=16){
   zz=zzzz;
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2]);
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG2[zz])&0x1FF,
         32,
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

   zz+=4;
   if((zz&0xFF)==0){zz-=0x100;}
   }
   zzzz+=0x100;
   zzzz&=0x1FFF;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   zzz=(ReadWord68k(&RAM_SCR3[0])>>6)+28;
   zzzz=((zzz&0x3F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR3[8])>>7)+32;
   zzzz+=((zzz&0x1F0)>>4)<<8;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0x1FFF;

   for(y=(48+y16);y<(224+64);y+=16){
   zz=zzzz;
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2]);
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG3[zz])&0x1FF,
         32,
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

   zz+=4;
   if((zz&0xFF)==0){zz-=0x100;}
   }
   zzzz+=0x100;
   zzzz&=0x1FFF;
   }
   }

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_trstar =
{
   DrawTRStars,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_prmtmfgo[] =
{
   { "prime_time_fighter", },
   { "prmtmfgt", },
   { "prmtmfgo", },
   { "trstars", },
   { ROMOF("trstar"), },
   { CLONEOF("trstar"), },
   { NULL, },
};
GAME(prmtmfgo, "Prime Time Fighter (Old Version)", TAITO, 1994, GAME_BEAT | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs,
	.romsw = romsw_prmtmfgo,
	.video = &video_trstar,
	.exec = execute_trstar,
	.board = "D53",
);
static struct DIR_INFO dir_trstar[] =
{
   { "top_ranking_stars", },
   { "trstars", },
   { "trstar", },
   { NULL, },
};
GAME( trstar, "Top Ranking Stars", TAITO, 1994, GAME_BEAT | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs,
	.romsw = romsw_trstar,
	.video = &video_trstar,
	.exec = execute_trstar,
	.board = "D53",
);

