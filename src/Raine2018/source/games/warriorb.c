#define DRV_DEF_SOUND taito_ym2610b_sound
/*

 ******************************************************************************
 *									      *
 *		   WARRIOR BLADE (C) 1991 TAITO CORPORATION		      *
 *									      *
 ******************************************************************************

 Aug 04, 2000

  - Removed ROM d24-07.bin as it was 100% same as ROM d24-02.bin
  - Removed the loading of ROM d24-09.bin with the sound ROMs

*/



#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc220ioc.h"
#include "sasound.h"            // sample support routines
#include "taitosnd.h"
#include "timer.h"

cache_data bg0,bg1;


static struct ROM_INFO rom_warriorb[] =
{
   {   "d24-01.11", 0x00100000, 0x326dcca9, 0, 0, 0, },
   {   "d24-02.12", 0x00100000, 0x9f50c271, 0, 0, 0, },
   {   "d24-03.24", 0x00100000, 0x46db9fd7, 0, 0, 0, },
   {   "d24-04.25", 0x00100000, 0x148e0493, 0, 0, 0, },
   {   "d24-05.26", 0x00100000, 0x9f414317, 0, 0, 0, },
   {   "d24-06.27", 0x00100000, 0x918486fe, 0, 0, 0, },
   {   "d24-08.48", 0x00100000, 0x1e6d1528, 0, 0, 0, },
   {   "d24-09.75", 0x00100000, 0xece5cc59, 0, 0, 0, },
   {   "d24-10.95", 0x00100000, 0x0e0c716d, 0, 0, 0, },
   {   "d24-11.118", 0x00100000, 0x15362573, 0, 0, 0, },
   {   "d24-12.107", 0x00100000, 0x279203a1, 0, 0, 0, },
   {   "d24_17.69", 0x00020000, 0xe41e4aae, 0, 0, 0, },
   { "d24_18-1.71", 0x00040000, 0x4502db60, 0, 0, 0, },
   { "d24_19-1.73", 0x00040000, 0x15c16016, 0, 0, 0, },
   { "d24_20-1.74", 0x00040000, 0x4452dc25, 0, 0, 0, },
   { "d24_21-1.76", 0x00040000, 0x783ef8e1, 0, 0, 0, },
   {	       NULL,	      0,	  0, 0, 0, 0, },
};

static struct INPUT_INFO input_warriorb[] =
{
   INP0( COIN1, 0x040004, 0x04 ),
   INP0( COIN2, 0x040004, 0x08 ),
   INP0( TILT, 0x040004, 0x02 ),
   INP0( SERVICE, 0x040004, 0x01 ),

   INP0( P1_START, 0x040004, 0x10 ),
   INP0( P1_UP, 0x040006, 0x01 ),
   INP0( P1_DOWN, 0x040006, 0x02 ),
   INP0( P1_LEFT, 0x040006, 0x04 ),
   INP0( P1_RIGHT, 0x040006, 0x08 ),
   INP0( P1_B1, 0x04000E, 0x10 ),
   INP0( P1_B2, 0x04000E, 0x20 ),
   INP0( P1_B3, 0x040004, 0x40 ),

   INP0( P2_START, 0x040004, 0x20 ),
   INP0( P2_UP, 0x040006, 0x10 ),
   INP0( P2_DOWN, 0x040006, 0x20 ),
   INP0( P2_LEFT, 0x040006, 0x40 ),
   INP0( P2_RIGHT, 0x040006, 0x80 ),
   INP0( P2_B1, 0x04000E, 0x40 ),
   INP0( P2_B2, 0x04000E, 0x80 ),
   INP0( P2_B3, 0x040004, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_warrior_blade_0[] =
{
   { MSG_DSWA_BIT1,	      0x01, 0x02 },
   { MSG_OFF,		      0x01},
   { MSG_ON,		      0x00},
   { MSG_DSWA_BIT2,	      0x02, 0x02 },
   { MSG_OFF,		      0x02},
   { MSG_ON,		      0x00},
   { MSG_TEST_MODE,	      0x04, 0x02 },
   { MSG_OFF,		      0x04},
   { MSG_ON,		      0x00},
   { MSG_DEMO_SOUND,	      0x08, 0x02 },
   { MSG_ON,		      0x08},
   { MSG_OFF,		      0x00},
   { MSG_COIN1, 	      0x30, 0x04 },
   { MSG_1COIN_1PLAY,	      0x30},
   { MSG_1COIN_2PLAY,	      0x20},
   { MSG_2COIN_1PLAY,	      0x10},
   { MSG_3COIN_1PLAY,	      0x00},
   { MSG_COIN2, 	      0xC0, 0x04 },
   { MSG_1COIN_1PLAY,	      0xC0},
   { MSG_1COIN_2PLAY,	      0x80},
   { MSG_2COIN_1PLAY,	      0x40},
   { MSG_3COIN_1PLAY,	      0x00},
   { NULL,		      0,	 },
};

static struct DSW_DATA dsw_data_warrior_blade_1[] =
{
   { MSG_DIFFICULTY,	      0x03, 0x04 },
   { MSG_NORMAL,	      0x03},
   { MSG_EASY,		      0x02},
   { MSG_HARD,		      0x01},
   { MSG_HARDEST,	      0x00},
   { MSG_DSWB_BIT3,	      0x04, 0x02 },
   { MSG_OFF,		      0x04},
   { MSG_ON,		      0x00},
   { MSG_DSWB_BIT4,	      0x08, 0x02 },
   { MSG_OFF,		      0x08},
   { MSG_ON,		      0x00},
   { _("Power Ups"),             0x10, 0x02 },
   { MSG_OFF,		      0x10},
   { MSG_ON,		      0x00},
   { _("Magician"),              0x20, 0x02 },
   { MSG_OFF,		      0x20},
   { MSG_ON,		      0x00},
   { MSG_CONTINUE_PLAY,       0x40, 0x02 },
   { MSG_ON,		      0x40},
   { MSG_OFF,		      0x00},
   { MSG_DSWB_BIT8,	      0x80, 0x02 },
   { MSG_OFF,		      0x80},
   { MSG_ON,		      0x00},
   { NULL,		      0,	 },
};

static struct DSW_INFO dsw_warriorb[] =
{
   { 0x040000, 0xFF, dsw_data_warrior_blade_0 },
   { 0x040002, 0xFF, dsw_data_warrior_blade_1 },
   { 0,        0,    NULL,	},
};

static struct ROMSW_DATA romsw_data_warrior_blade_0[] =
{
   { "Taito Japan",           0x00 },
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { NULL,		      0    },
};

static struct ROMSW_INFO romsw_warriorb[] =
{
   { 0x0FFFFF, 0x01, romsw_data_warrior_blade_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG1;
static UINT8 *GFX_BG1_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_warriorb(void)
{
   int ta,tb;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(7,60));
   if(!(GFX=AllocateMem(0x1000000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG1 = GFX+0x400000;
   GFX_SPR = GFX+0x800000;

   tb=0;
   if(!load_rom("d24-02.12", RAM, 0x100000)) return;           // BG0 GFX (SCREEN 0)
   for(ta=0;ta<0x100000;ta+=2){
      GFX_BG0[tb++]=RAM[ta+1]>>4;
      GFX_BG0[tb++]=RAM[ta+1]&15;
      GFX_BG0[tb++]=RAM[ta+0]>>4;
      GFX_BG0[tb++]=RAM[ta+0]&15;
   }
   if(!load_rom("d24-01.11", RAM, 0x100000)) return;
   for(ta=0;ta<0x100000;ta+=2){
      GFX_BG0[tb++]=RAM[ta+1]>>4;
      GFX_BG0[tb++]=RAM[ta+1]&15;
      GFX_BG0[tb++]=RAM[ta+0]>>4;
      GFX_BG0[tb++]=RAM[ta+0]&15;
   }

   tb=0x200000;
   memcpy(GFX_BG1,GFX_BG0,tb);
   if(!load_rom("d24-08.48", RAM, 0x100000)) return;
   for(ta=0;ta<0x100000;ta+=2){
      GFX_BG1[tb++]=RAM[ta+1]>>4;
      GFX_BG1[tb++]=RAM[ta+1]&15;
      GFX_BG1[tb++]=RAM[ta+0]>>4;
      GFX_BG1[tb++]=RAM[ta+0]&15;
   }

   tb=0;
   if(!load_rom("d24-03.24", RAM, 0x100000)) return;           // SPRITES
   for(ta=0;ta<0x100000;ta+=2){
      GFX_SPR[tb+3]=RAM[ta+1]>>4;
      GFX_SPR[tb+2]=RAM[ta+1]&15;
      GFX_SPR[tb+1]=RAM[ta+0]>>4;
      GFX_SPR[tb+0]=RAM[ta+0]&15;
      tb+=16;
   }
   tb=0;
   if(!load_rom("d24-06.27", RAM, 0x100000)) return;
   for(ta=0;ta<0x100000;ta+=2){
      GFX_SPR[tb+7]=RAM[ta+1]>>4;
      GFX_SPR[tb+6]=RAM[ta+1]&15;
      GFX_SPR[tb+5]=RAM[ta+0]>>4;
      GFX_SPR[tb+4]=RAM[ta+0]&15;
      tb+=16;
   }
   tb=0;
   if(!load_rom("d24-05.26", RAM, 0x100000)) return;
   for(ta=0;ta<0x100000;ta+=2){
      GFX_SPR[tb+11]=RAM[ta+1]>>4;
      GFX_SPR[tb+10]=RAM[ta+1]&15;
      GFX_SPR[tb+9]=RAM[ta+0]>>4;
      GFX_SPR[tb+8]=RAM[ta+0]&15;
      tb+=16;
   }
   tb=0;
   if(!load_rom("d24-04.25", RAM, 0x100000)) return;
   for(ta=0;ta<0x100000;ta+=2){
      GFX_SPR[tb+15]=RAM[ta+1]>>4;
      GFX_SPR[tb+14]=RAM[ta+1]&15;
      GFX_SPR[tb+13]=RAM[ta+0]>>4;
      GFX_SPR[tb+12]=RAM[ta+0]&15;
      tb+=16;
   }

   FreeMem(RAM);

   GFX_BG0_SOLID = make_solid_mask_8x8	(GFX_BG0, 0x10000);
   GFX_BG1_SOLID = make_solid_mask_8x8	(GFX_BG1, 0x10000);
   init_tile_cachex4();
   clear_tile_cache();
   new_tile_cachex4(&bg0);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x08000);

   RAMSize=0x70000+0x20000;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x200000))) return;

   if(!load_rom("d24_20-1.74", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d24_19-1.73", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("d24_21-1.76", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom("d24_18-1.71", RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }
   if(!load_rom("d24-09.75",&ROM[0x100000],0x100000)) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x70000;
   if(!load_rom("d24_17.69", Z80ROM, 0x20000)) return; // Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x300000))) return;
   if(!load_rom("d24-12.107",PCMROM+0x000000,0x100000)) return; // ADPCM A rom
   if(!load_rom("d24-10.95",PCMROM+0x100000,0x100000)) return; // ADPCM B rom
   if(!load_rom("d24-11.118",PCMROM+0x200000,0x100000)) return; // ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x300000);

   AddTaitoYM2610B_OffsetVol(0x01FC, 0x0171, 0x20000, 4);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x70000);

   RAM_INPUT = RAM+0x40000;
   GFX_FG0   = RAM+0x3C000;

   tc0100scn[0].RAM	= RAM+0x21000-0x6000;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   tc0110pcr_init_typeb(RAM+0x3A000, 1, 0);
   tc0110pcr_init_typeb_2(RAM+0x3B000, 1, 0);

   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);
   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // 68000 Speed Hacks
   // -----------------

   WriteWord68k(&ROM[0x0376A],0x4EF9);		//	jmp	$400
   WriteLong68k(&ROM[0x0376C],0x00000400);	//

   WriteLong68k(&ROM[0x00400],0x4A2DA91E);	//	tst.b	-22242(a5)
   WriteWord68k(&ROM[0x00404],0x670A);		//	beq.S	LAB_0142
   WriteLong68k(&ROM[0x00406],0x206DA924);	//	movea.l -22236(a5),a0
   WriteWord68k(&ROM[0x0040A],0x4E90);		//	jsr	(a0)
   WriteLong68k(&ROM[0x0040C],0x422DA91E);	//	clr.b	-22242(a5)
   WriteLong68k(&ROM[0x00410],0x13FC0000);	//	move.b	#$00,$AA0000	; Speed Hack
   WriteLong68k(&ROM[0x00414],0x00AA0000);	//
   WriteWord68k(&ROM[0x00418],0x6100-0x1A);	//	bra.s	<loop>

   WriteLong68k(&ROM[0x03764],0x4EB80420);	//	jsr	($420).w

   WriteLong68k(&ROM[0x00420],0x4EB838AE);	//	jsr	(EXT_00CC).w	; Random Gen
   WriteLong68k(&ROM[0x00424],0x13FC0000);	//	move.b	#$00,$AA0000	; Speed Hack
   WriteLong68k(&ROM[0x00428],0x00AA0000);	//
   WriteWord68k(&ROM[0x0042C],0x4E75);		//	rts

   // Fix Freeze
   // ----------

   WriteWord68k(&ROM[0x033B6],0x4E71);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x70000);

   AddMemFetch(0x000000, 0x1FFFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x1FFFFF, NULL, ROM+0x000000); 		// 68000 ROM
   AddReadByte(0x200000, 0x20FFFF, NULL, RAM+0x000000); 		// 68000 RAM
   AddReadByte(0x300000, 0x313FFF, NULL, RAM+0x010000); 		// SCREEN RAM
   AddReadByte(0x340000, 0x353FFF, NULL, RAM+0x024000); 		// OBJECT RAM
   AddReadByte(0x800000, 0x80001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x1FFFFF, NULL, ROM+0x000000); 		// 68000 ROM
   AddReadWord(0x200000, 0x20FFFF, NULL, RAM+0x000000); 		// 68000 RAM
   AddReadWord(0x300000, 0x313FFF, NULL, RAM+0x010000); 		// SCREEN RAM
   AddReadWord(0x340000, 0x353FFF, NULL, RAM+0x024000); 		// OBJECT RAM
   AddReadWord(0x400000, 0x400007, tc0110pcr_rw, NULL); 		// COLOR RAM SCREEN A
   AddReadWord(0x420000, 0x420007, tc0110pcr_rw_2, NULL);		// COLOR RAM SCREEN B
   AddReadWord(0x600000, 0x601FFF, NULL, RAM+0x038000); 		// SPRITE RAM
   AddReadWord(0x800000, 0x80001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x830000, 0x830003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x300000, 0x310FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0x340000, 0x353FFF, NULL, RAM+0x024000);		// OBJECT RAM
   AddWriteByte(0x311000, 0x311FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x312000, 0x313FFF, NULL, RAM+0x022000);		// SCREEN RAM
   AddWriteWord(0x800000, 0x80001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x300000, 0x310FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0x340000, 0x353FFF, NULL, RAM+0x024000);		// OBJECT RAM
   AddWriteWord(0x311000, 0x311FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x312000, 0x313FFF, NULL, RAM+0x022000);		// SCREEN RAM
   AddWriteWord(0x400000, 0x400007, tc0110pcr_ww, NULL);		// COLOR RAM SCREEN A
   AddWriteWord(0x420000, 0x420007, tc0110pcr_ww_2, NULL);		// COLOR RAM SCREEN B
   AddWriteWord(0x600000, 0x601FFF, NULL, RAM+0x038000);		// SPRITE RAM
   AddWriteWord(0x320000, 0x32000F, NULL, RAM+0x040020);		// SCROLL A RAM
   AddWriteWord(0x360000, 0x36000F, NULL, RAM+0x040040);		// SCROLL B RAM
   AddWriteWord(0x830000, 0x830003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWord(0x800000, 0x80001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void ClearWarriorBlade(void)
{
   RemoveTaitoYM2610();

   #ifdef RAINE_DEBUG
      //save_debug("ROM.bin",ROM,0x100000,1);
      //save_debug("RAM.bin",RAM,0x070000,1);
   #endif
}

static void execute_warriorb(void)
{
   //print_ingame(600,gettext("%04x"),ReadWord(&RAM[0x4002C]));

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(20,60)); // M68000 20MHz (60fps)
   /*#ifdef RAINE_DEBUG
      print_debug("PC0:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
   #endif*/
   cpu_interrupt(CPU_68K_0, 4);

   execute_z80_audio_frame();
}

static void DrawWarriorBlade(void)
{
   int x,y,ta,tb;
   int zz,zzz,zzzz,x16,y16;
   UINT8 *map;
   UINT8 *RAM_BGA;
   UINT8 *RAM_BGB;
   UINT8 *SCR_BGA;
   UINT8 *SCR_BGB;

   ClearPaletteMap();

   if((ReadWord(&RAM[0x4002C])&0x08)==0){

   RAM_BGA = RAM+0x10000;
   RAM_BGB = RAM+0x18000;
   SCR_BGA = RAM+0x40020;
   SCR_BGB = RAM+0x40022;

   }
   else{

   RAM_BGA = RAM+0x18000;
   RAM_BGB = RAM+0x10000;
   SCR_BGA = RAM+0x40022;
   SCR_BGB = RAM+0x40020;

   }

   // BG0
   // ---

   clear_tile_cache(); // clear bg1

   MAKE_SCROLL_1024x512_4_8(
      20-(ReadWord(&SCR_BGA[0])),
       8-(ReadWord(&SCR_BGA[6]))
   );

   zz=zzzz;
   for(y=(32-y16);y<(240+32);y+=8){
   switch_cache(&bg1,&bg0);
   for(x=(32-x16);x<(320+32-x16);x+=8){

      MAP_PALETTE_MAPPED_NEW(
	 RAM_BGA[zz]&0x7F,
	 16,
	 map
      );

      ta = ReadWord(&RAM_BGA[2+zz]);
      tb = ta*4;

      switch(RAM_BGA[1+zz]&0xC0){
      case 0x00: 
	if (tile_cache[tb] && (cache_map[tb] == map)) {
	  Move8x8_Rot(tile_cache[tb],x,y,NULL);
	} else {
	  Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);	     
	  add_tile_cache_Rot(NULL,x,y,tb);
	  cache_map[tb] = map;
	}
	break;
      case 0x40: 
	if (tile_cache[tb+1] && (cache_map[tb+1] == map)) {
	  Move8x8_Rot(tile_cache[tb+1],x,y,NULL);
	} else {
	  Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);
	  add_tile_cache_Rot(NULL,x,y,tb+1);
	  cache_map[tb+1] = map;
	}
	break;
      case 0x80: 
	if (tile_cache[tb+2] && (cache_map[tb+2] == map)) {
	  Move8x8_Rot(tile_cache[tb+2],x,y,NULL);
	} else {
	  Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);
	  add_tile_cache_Rot(NULL,x,y,tb+2);
	  cache_map[tb+2] = map;
	}
	break;
      case 0xC0: 
	if (tile_cache[tb+3] && (cache_map[tb+3] == map)) {
	  Move8x8_Rot(tile_cache[tb+3],x,y,NULL);
	} else {
	  Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map);
	  add_tile_cache_Rot(NULL,x,y,tb+3);
	  cache_map[tb+3] = map;
	}
	break;
      }

      zz=(zz&0x7E00)|((zz+4)&0x1FF);
   }
   switch_cache(&bg0,&bg1);
   for(x=(320+32-x16);x<(640+32);x+=8){

      MAP_PALETTE_MAPPED_NEW(
	 RAM_BGA[zz]&0x7F,
	 16,
	 map
      );

      ta = ReadWord(&RAM_BGA[2+zz]);
      tb = ta*4;

      switch(RAM_BGA[1+zz]&0xC0){
      case 0x00:
	if (tile_cache[tb] && (cache_map[tb] == map)) {
	  Move8x8_Rot(tile_cache[tb],x,y,NULL);
	} else {
	  Draw8x8_Mapped_Rot(&GFX_BG1[ta<<6],x,y,map);
	  add_tile_cache_Rot(NULL,x,y,tb);
	  cache_map[tb] = map;
	}
	break;
      case 0x40: 
	if (tile_cache[tb+1] && (cache_map[tb+1] == map)) {
	  Move8x8_Rot(tile_cache[tb+1],x,y,NULL);
	} else {
	  Draw8x8_Mapped_FlipY_Rot(&GFX_BG1[ta<<6],x,y,map);
	  add_tile_cache_Rot(NULL,x,y,tb+1);
	  cache_map[tb+1] = map;
	}
	break;
      case 0x80: 
	if (tile_cache[tb+2] && (cache_map[tb+2] == map)) {
	  Move8x8_Rot(tile_cache[tb+2],x,y,NULL);
	} else {
	  Draw8x8_Mapped_FlipX_Rot(&GFX_BG1[ta<<6],x,y,map);
	  add_tile_cache_Rot(NULL,x,y,tb+2);
	  cache_map[tb+2] = map;
	}
	break;
      case 0xC0: 
	if (tile_cache[tb+3] && (cache_map[tb+3] == map)) {
	  Move8x8_Rot(tile_cache[tb+3],x,y,NULL);
	} else {
	  Draw8x8_Mapped_FlipXY_Rot(&GFX_BG1[ta<<6],x,y,map); 
	  add_tile_cache_Rot(NULL,x,y,tb+3);
	  cache_map[tb+3] = map;
	}
	break;
      }

      zz=(zz&0x7E00)|((zz+4)&0x1FF);
   }
   zzzz=(zzzz+0x200)&0x7FFF;
   zz=zzzz;
   }

   // BG1
   // ---

   clear_tile_cache(); // clear bg1

   switch_cache(&bg1,&bg0);

   clear_tile_cache(); // clear bg0

   MAKE_SCROLL_1024x512_4_8(
      20-(ReadWord(&SCR_BGB[0])),
       8-(ReadWord(&SCR_BGB[6]))
   );

   zz=zzzz;
   for(y=(32-y16);y<(240+32);y+=8){
   for(x=(32-x16);x<(320+32-x16);x+=8){

   ta=ReadWord(&RAM_BGB[2+zz]);
   if(GFX_BG0_SOLID[ta]){			// No pixels; skip

     tb = ta*4;
      MAP_PALETTE_MAPPED_NEW(
	 RAM_BGB[zz]&0x7F,
	 16,
	 map
      );

      if(GFX_BG0_SOLID[ta]==1){ 		// Some pixels; trans
	 switch(RAM_BGB[1+zz]&0xC0){
	    case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);	 break;
	    case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
	    case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
	    case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
	 }
      }
      else{					// all pixels; solid
	 switch(RAM_BGB[1+zz]&0xC0){
	    case 0x00:
	      if (tile_cache[tb] && (cache_map[tb] == map)) {
		Move8x8_Rot(tile_cache[tb],x,y,NULL);
	      } else {
		Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);
		add_tile_cache_Rot(NULL,x,y,tb);
		cache_map[tb] = map;
	      }
	      break;
	    case 0x40:
	      if (tile_cache[tb+1] && (cache_map[tb+1] == map)) {
		Move8x8_Rot(tile_cache[tb+1],x,y,NULL);
	      } else {
		Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  
		add_tile_cache_Rot(NULL,x,y,tb+1);
		cache_map[tb+1] = map;
	      }
	      break;
	    case 0x80: 
	      if (tile_cache[tb+2] && (cache_map[tb+2] == map)) {
		Move8x8_Rot(tile_cache[tb+2],x,y,NULL);
	      } else {
		Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);
		add_tile_cache_Rot(NULL,x,y,tb+2);
		cache_map[tb+2] = map;
	      }
	      break;
	    case 0xC0: 
	      if (tile_cache[tb+3] && (cache_map[tb+3] == map)) {
		Move8x8_Rot(tile_cache[tb+3],x,y,NULL);
	      } else {
		Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); 
		add_tile_cache_Rot(NULL,x,y,tb+3);
		cache_map[tb+3] = map;
	      }
	      break;
	 }
      }
   }
   zz=(zz&0x7E00)|((zz+4)&0x1FF);
   }

   switch_cache(&bg0,&bg1);

   for(x=(320+32-x16);x<(640+32);x+=8){

   ta=ReadWord(&RAM_BGB[2+zz]);
   if(GFX_BG1_SOLID[ta]){			// No pixels; skip
     tb = ta*4;
      MAP_PALETTE_MAPPED_NEW(
	 RAM_BGB[zz]&0x7F,
	 16,
	 map
      );

      if(GFX_BG1_SOLID[ta]==1){ 		// Some pixels; trans
	 switch(RAM_BGB[1+zz]&0xC0){
	    case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_BG1[ta<<6],x,y,map);	 break;
	    case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG1[ta<<6],x,y,map);  break;
	    case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG1[ta<<6],x,y,map);  break;
	    case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG1[ta<<6],x,y,map); break;
	 }
      }
      else{					// all pixels; solid
	 switch(RAM_BGB[1+zz]&0xC0){
	    case 0x00: 
	      if (tile_cache[tb] && (cache_map[tb] == map)) {
		Move8x8_Rot(tile_cache[tb],x,y,NULL);
	      } else {
		Draw8x8_Mapped_Rot(&GFX_BG1[ta<<6],x,y,map);	   
		add_tile_cache_Rot(NULL,x,y,tb);
		cache_map[tb] = map;
	      }
	      break;
	    case 0x40: 
	      if (tile_cache[tb+1] && (cache_map[tb+1] == map)) {
		Move8x8_Rot(tile_cache[tb+1],x,y,NULL);
	      } else {
		Draw8x8_Mapped_FlipY_Rot(&GFX_BG1[ta<<6],x,y,map);  
		add_tile_cache_Rot(NULL,x,y,tb+1);
		cache_map[tb+1] = map;
	      }
	      break;
	    case 0x80:
	      if (tile_cache[tb+2] && (cache_map[tb+2] == map)) {
		Move8x8_Rot(tile_cache[tb+2],x,y,NULL);
	      } else {
		Draw8x8_Mapped_FlipX_Rot(&GFX_BG1[ta<<6],x,y,map);  
		add_tile_cache_Rot(NULL,x,y,tb+2);
		cache_map[tb+2] = map;
	      }
	      break;
	    case 0xC0: 
	      if (tile_cache[tb+3] && (cache_map[tb+3] == map)) {
		Move8x8_Rot(tile_cache[tb+3],x,y,NULL);
	      } else {
		Draw8x8_Mapped_FlipXY_Rot(&GFX_BG1[ta<<6],x,y,map); 
		add_tile_cache_Rot(NULL,x,y,tb+3);
		cache_map[tb+3] = map;
	      }
	      break;
	 }
      }
   }
   zz=(zz&0x7E00)|((zz+4)&0x1FF);
   }
   switch_cache(&bg1,&bg0);

   zzzz=(zzzz+0x200)&0x7FFF;
   zz=zzzz;
   }

   clear_tile_cache(); // clear bg0
   switch_cache(&bg0,&bg1); // bg1 will be cleared at next frame...

   for(zz=0x393F8;zz>=0x38000;zz-=8){
   x=((32)+ReadWord(&RAM[zz+6]))&0x3FF;
   y=((32+224+256)-ReadWord(&RAM[zz]))&0x1FF;

   if((x>16)&&(y>16)&&(x<640+32)&&(y<240+32)){
   ta=ReadWord(&RAM[zz+2])&0x7FFF;
   if(GFX_SPR_SOLID[ta]){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
	 RAM[zz+4]&0x7F,
	 16,
	 map
      );

      if(GFX_SPR_SOLID[ta]==1){ 		// Some pixels; trans
	 switch(RAM[zz+7]&0x0C){
	 case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);	break;
	 case 0x04: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);	break;
	 case 0x08: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);	break;
	 case 0x0C: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
	 }
      }
      else{					// all pixels; solid
	 switch(RAM[zz+7]&0x0C){
	 case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);	  break;
	 case 0x04: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
	 case 0x08: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
	 case 0x0C: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
	 }
      }

   }

   }

   }

   // FG0
   // ---

   MAKE_SCROLL_1024x256_2_8(
      20-(ReadWord(&RAM[0x40024])),
       8-(ReadWord(&RAM[0x4002A]))
   );

   START_SCROLL_1024x256_2_8(32,32,640,240);

      ta = ReadWord(&RAM[0x22000+zz]);

      if(ta&0x00FF){

	 MAP_PALETTE_MAPPED_NEW(
	    (ta>>8)&0x3F,
	    16,
	    map
	 );

	 switch(ta&0xC000){
	    case 0x0000: Draw8x8_Trans_Mapped_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);	    break;
	    case 0x4000: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);  break;
	    case 0x8000: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);  break;
	    case 0xC000: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map); break;
	 }

      }

   END_SCROLL_1024x256_2_8();
}

static struct VIDEO_INFO video_warriorb =
{
   DrawWarriorBlade,
   640,
   240,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_warriorb[] =
{
   { "warrior_blade", },
   { "warriorb", },
   { NULL, },
};
GME( warriorb, "Warrior Blade", TAITO, 1991, GAME_BEAT,
	.romsw = romsw_warriorb,
	.clear = ClearWarriorBlade,
	.long_name_jpn = "âEâHâèâAü[âuâîü[âh",
	.board = "D24",
);

