/******************************************************************************/
/*                                                                            */
/*                     RING RAGE (C) 1994 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "files.h"
#include "savegame.h"
#include "sasound.h"


static struct ROM_INFO rom_ringrage[] =
{
  { "d21-23.40", 0x40000, 0x14e9ed65, REGION_ROM1, 0x000000, LOAD_8_32 },
  { "d21-22.38", 0x40000, 0x6f8b65b0, REGION_ROM1, 0x000001, LOAD_8_32 },
  { "d21-21.36", 0x40000, 0xbf7234bc, REGION_ROM1, 0x000002, LOAD_8_32 },
  { "ringr-25.rom", 0x40000, 0xaeff6e19, REGION_ROM1, 0x000003, LOAD_8_32 },
   { "d21-04.68", 0x00200000, 0x9dcdceca, 0, 0, 0, },
   { "d21-02.66", 0x00200000, 0xfacd3a02, 0, 0, 0, },
   { "d21-03.67", 0x00200000, 0x6f653e68, 0, 0, 0, },
   { "d21-01.17", 0x00200000, 0x1fb6f07d, 0, 0, 0, },
   { "d21-05.18", 0x00100000, 0xed894fe1, 0, 0, 0, },
   { "d21-06.49", 0x00080000, 0x92d4a720, 0, 0, 0, },
   { "d21-07.50", 0x00080000, 0x6da696e9, 0, 0, 0, },
   { "d21-08.51", 0x00080000, 0xa0d95be9, 0, 0, 0, },
  LOAD8_16(  REGION_ROM2,  0x000000,  0x00020000,
            "d21-18.5",  0x133b55d0, "d21-19.6",  0x1f98908f),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_DATA romsw_data_ring_rage_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito Worldwide",       0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_ringrage[] =
{
   { 0x07FFFF, 0x03, romsw_data_ring_rage_0 },
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

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_ringrage(void)
{
   int ta,tb,tc;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x1EF140))) return;
   if(!(GFX=AllocateMem(0x7BC500+0x1C7D00))) return;

   GFX_BG0 = GFX+0x7BC500;
   GFX_SPR = GFX+0x000000;

   tb=0;
   if(!load_rom("d21-02.66", ROM, 0x1EF140)) return;	// 16x16 SPRITES ($7BC5)
   for(ta=0;ta<0x1EF140;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("d21-03.67", ROM, 0x1EF140)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x1EF140;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("d21-04.68", ROM, 0x1EF140)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x1EF140;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("d21-06.49", ROM, 0x71F40)) return;	// 16x16 TILES ($1C7D)
   for(ta=0;ta<0x71F40;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("d21-07.50", ROM, 0x71F40)) return;	// 16x16 TILES
   for(ta=0;ta<0x71F40;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("d21-08.51", ROM, 0x71F40)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x71F40;ta+=2){
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

   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x1C7D);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x7BC5);

   ROM = load_region[REGION_CPU1];

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x100000);

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x31000;
   RAM_BG2=RAM+0x32000;
   RAM_BG3=RAM+0x33000;
   RAM_BG4=RAM+0x50000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR0_XOFS=0xF600+(1<<6);
   SCR1_XOFS=0xF700+(1<<6);
   SCR2_XOFS=0xF800+(1<<6);
   SCR3_XOFS=0xF900+(1<<6);
   SCR4_XOFS=0x0029-1;

   SCR0_YOFS=0xFF80+(1<<7);
   SCR1_YOFS=0xFF80+(1<<7);
   SCR2_YOFS=0xFF80+(1<<7);
   SCR3_YOFS=0xFF80+(1<<7);
   SCR4_YOFS=0x001F-1;

   // 68000 code
   M68000ROM = load_region[REGION_ROM2];
   if(!(PCMROM=AllocateMem(0x800000))) return;
   load_be("d21-01.17",PCMROM,0x200000);
   load_be("d21-05.18",PCMROM+0x400000,0x100000);
   max_banks_this_game=3; //=memory_region_length(REGION_SOUND1)/0x400000;
   memset(PCMROM+0x600000,0,0x1fffff);

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   // FIX ROM CHECKSUM
   // ----------------

   ROM[0x056AC]=0x00;

   // EEPROM HACKS
   // ------------

   WriteWord68k(&ROM[0x0B9BC],0x7F00);		//	raine	#$00	<eeprom read>
   WriteWord68k(&ROM[0x0B9BE],0x4E75);		//	rts

   WriteWord68k(&ROM[0x0BA38],0x7F01);		//	raine	#$01	<eeprom write>
   WriteWord68k(&ROM[0x0BA3A],0x4E75);		//	rts

   WriteWord68k(&ROM[0xa8c],0x4e71);		//	rts

/*    WriteWord68k(&ROM[0xa64],0x4e71);		//	nop */
/*    WriteWord68k(&ROM[0xa66],0x4e71);		//	nop */

   // SPEED HACKS
   // -----------

   WriteWord68k(&ROM[0x00706],0x7F02);		//	raine	#$02	<stop cpu>

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode1;

   set_colour_mapper(&col_map_12bit_rgbxxxx);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x2000);

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu.RAM	= RAM+0x20000;
   //tc0003vcu.mapper	= &Map_12bit_RGBxxxxx;
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
   //tc0200obj.mapper	= &Map_12bit_RGBxxxxx;
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0-0x2E;
   tc0200obj.ofs_y	= 0-0x1F;

   tc0200obj.cols	= 32;

   init_tc0200obj();

   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
   setup_sound_68000();
}

extern UINT32 cpu_frame_count;
static void execute_ringrage(void)
{
  int ta;
  cycles = 1;
  for (ta=0; ta<f3_slices; ta++) {
    if (cycles) {// cycles = 0 if we reached the speed hack
      Execute68020(400000/f3_slices);
    }
/*     if (RaineSoundCard) { */
/*       cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60*f3_slices)); // M68000 16MHz (60fps) */
/*       print_debug("PC68k:%06x SR:%04x\n",s68000context.pc,s68000context.sr); */
/*       if (int7_active) { */
/* 	if (f3_slices == 16) */
/* 	  f3_slices = 1; */
/* 	f3_timer_callback(); */
/*       } */
/*     } */
  }

  Interrupt68020(3);
  Interrupt68020(2);

  IntF3System();
}

static void DrawRingRage(void)
{
   int x16,y16,zz,zzz,zzzz;
   int ta,x,y;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(check_layer_enabled(f3_bg0_id)){
   zzz=(ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6;
   zzzz=((zzz&0x1F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7;
   zzzz+=((zzz&0x1F0)>>4)<<7;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0xFFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG0[zz])&0x1FF,
         64,
         MAP
      );

      switch(RAM_BG0[zz]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[(ReadWord68k(&RAM_BG0[zz+2])&0x1FFF)<<8],x,y,MAP); break;
      }

   zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }


   if(check_layer_enabled(f3_bg1_id)){
   zzz=(ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6;
   zzzz=((zzz&0x1F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7;
   zzzz+=((zzz&0x1F0)>>4)<<7;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0xFFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG1[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG1[zz])&0x1FF,
         64,
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

   zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

   render_tc0200obj_mapped_f3system();

   if(check_layer_enabled(f3_bg2_id)){
   zzz=(ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6;
   zzzz=((zzz&0x1F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7;
   zzzz+=((zzz&0x1F0)>>4)<<7;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0xFFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG2[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG2[zz])&0x1FF,
         64,
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

   zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg3_id)){
   zzz=(ReadWord68k(&RAM_SCR0[0])-SCR0_XOFS)>>6;
   zzzz=((zzz&0x1F0)>>4)<<2;			// X Offset (16-1024)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=(ReadWord68k(&RAM_SCR0[8])-SCR0_YOFS)>>7;
   zzzz+=((zzz&0x1F0)>>4)<<7;			// Y Offset (16-511)
   y16=15-(zzz&15);				// Y Offset (0-15)

   zzzz&=0xFFF;
   zz=zzzz;

   for(y=(48+y16);y<(224+64);y+=16){
   for(x=(48+x16);x<(320+64);x+=16){

   ta=ReadWord68k(&RAM_BG3[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         ReadWord68k(&RAM_BG3[zz])&0x1FF,
         64,
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

   zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }
   }

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}

static struct VIDEO_INFO video_ringrage =
{
   DrawRingRage,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ringrage[] =
{
   { "ring_rage", },
   { "ringrage", },
   { NULL, },
};
GAME( ringrage, "Ring Rage", TAITO, 1992, GAME_BEAT | GAME_PARTIALLY_WORKING,
	.input = f3_system_inputs,
	.romsw = romsw_ringrage,
	.video = &video_ringrage,
	.exec = execute_ringrage,
	.board = "D21",
	.sound = f3_sound,
);

