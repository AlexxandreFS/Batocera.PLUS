/******************************************************************************/
/*                                                                            */
/*         DARIUS 2 - DUAL SCREEN VERSION (C) 1989 TAITO CORPORATION          */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"


static struct ROM_INFO rom_drius2do[] =
{
   {       "c07-03.12", 0x00080000, 0x189bafce, 0, 0, 0, },
   {       "c07-04.11", 0x00080000, 0x50421e81, 0, 0, 0, },
   {   "c07-05.24", 0x00080000, 0xfb6d0550, 0, 0, 0, },
   {   "c07-06.27", 0x00080000, 0x5eebbcd6, 0, 0, 0, },
   {   "c07-07.26", 0x00080000, 0xfd9f9e74, 0, 0, 0, },
   {   "c07-08.25", 0x00080000, 0xa07dc846, 0, 0, 0, },
   {   "c07-09.75", 0x00080000, 0xcc69c2ce, 0, 0, 0, },
   {       "c07-10.95", 0x00080000, 0x4bbe0ed9, 0, 0, 0, },
   {       "c07-11.96", 0x00080000, 0x3c815699, 0, 0, 0, },
   {       "c07-12.107", 0x00080000, 0xe0b71258, 0, 0, 0, },
   {   "c07-17.69", 0x00020000, 0xae16c905, 0, 0, 0, },
   { "c07_18-1.71", 0x00020000, 0xc552e42f, 0, 0, 0, },
   { "c07_19-1.73", 0x00020000, 0x1f9a4f83, 0, 0, 0, },
   { "c07_20-1.74", 0x00020000, 0x48b0804a, 0, 0, 0, },
   { "c07_21-1.76", 0x00020000, 0xb491b0ca, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_drius2do[] =
{
   INP0( COIN1, 0x03B004, 0x04 ),
   INP0( COIN2, 0x03B004, 0x08 ),
   INP0( TILT, 0x03B004, 0x02 ),
   INP0( SERVICE, 0x03B004, 0x01 ),

   INP0( P1_START, 0x03B004, 0x10 ),
   INP0( P1_UP, 0x03B006, 0x01 ),
   INP0( P1_DOWN, 0x03B006, 0x02 ),
   INP0( P1_LEFT, 0x03B006, 0x04 ),
   INP0( P1_RIGHT, 0x03B006, 0x08 ),
   INP0( P1_B1, 0x03B00E, 0x10 ),
   INP0( P1_B2, 0x03B00E, 0x20 ),

   INP0( P2_START, 0x03B004, 0x20 ),
   INP0( P2_UP, 0x03B006, 0x10 ),
   INP0( P2_DOWN, 0x03B006, 0x20 ),
   INP0( P2_LEFT, 0x03B006, 0x40 ),
   INP0( P2_RIGHT, 0x03B006, 0x80 ),
   INP0( P2_B1, 0x03B00E, 0x40 ),
   INP0( P2_B2, 0x03B00E, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_darius_2_dual_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { _("Continuous Fire"),       0x02, 0x02 },
   { MSG_NORMAL,              0x02},
   { _("Fast"),                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_3COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_darius_2_dual_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("Every 700k"),            0x0C},
   { _("Every 800k"),            0x08},
   { _("Every 900k"),            0x04},
   { _("Every 500k"),            0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "6",                     0x00},
   { MSG_CONTINUE_PLAY,       0x80, 0x02 },
   { MSG_ON,                  0x80},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_drius2do[] =
{
   { 0x03B000, 0xFF, dsw_data_darius_2_dual_0 },
   { 0x03B002, 0xFF, dsw_data_darius_2_dual_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_darius_2_dual_0[] =
{
   { "Taito Japan (notice)",           0x01 },
   { "Taito Romstar licence (Sagaia)", 0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_drius2do[] =
{
   { 0x07FFFF, 0x01, romsw_data_darius_2_dual_0 },
   { 0,        0,    NULL },
};



static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *RAM_INPUT;

static void load_drius2do(void)
{
   int ta,tb;
   UINT8 *TMP;

   if(!(GFX=AllocateMem(0x400000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x200000;

   tb=0;
   if(!load_rom("c07-03.12", TMP, 0x80000)) return;		// 8x8 BG0
   for(ta=0;ta<0x80000;ta+=2){
      GFX_BG0[tb+1]=TMP[ta+1]&15;
      GFX_BG0[tb+0]=TMP[ta+1]>>4;
      GFX_BG0[tb+3]=TMP[ta+0]&15;
      GFX_BG0[tb+2]=TMP[ta+0]>>4;
      tb+=4;
   }
   if(!load_rom("c07-04.11", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=2){
      GFX_BG0[tb+1]=TMP[ta+1]&15;
      GFX_BG0[tb+0]=TMP[ta+1]>>4;
      GFX_BG0[tb+3]=TMP[ta+0]&15;
      GFX_BG0[tb+2]=TMP[ta+0]>>4;
      tb+=4;
   }

   if(!load_rom("c07-05.24", TMP, 0x40000)) return;		// 16x16 OBJ
   tb=0;
   for(ta=0;ta<0x40000;ta+=2){
      GFX_SPR[tb+0]=TMP[ta+0]&15;
      GFX_SPR[tb+1]=TMP[ta+0]>>4;
      GFX_SPR[tb+2]=TMP[ta+1]&15;
      GFX_SPR[tb+3]=TMP[ta+1]>>4;
      tb+=16;
   }

   if(!load_rom("c07-06.27", TMP, 0x40000)) return;		// 16x16 OBJ
   tb=4;
   for(ta=0;ta<0x40000;ta+=2){
      GFX_SPR[tb+0]=TMP[ta+0]&15;
      GFX_SPR[tb+1]=TMP[ta+0]>>4;
      GFX_SPR[tb+2]=TMP[ta+1]&15;
      GFX_SPR[tb+3]=TMP[ta+1]>>4;
      tb+=16;
   }

   if(!load_rom("c07-07.26", TMP, 0x40000)) return;		// 16x16 OBJ
   tb=8;
   for(ta=0;ta<0x40000;ta+=2){
      GFX_SPR[tb+0]=TMP[ta+0]&15;
      GFX_SPR[tb+1]=TMP[ta+0]>>4;
      GFX_SPR[tb+2]=TMP[ta+1]&15;
      GFX_SPR[tb+3]=TMP[ta+1]>>4;
      tb+=16;
   }

   if(!load_rom("c07-08.25", TMP, 0x40000)) return;		// 16x16 OBJ
   tb=12;
   for(ta=0;ta<0x40000;ta+=2){
      GFX_SPR[tb+0]=TMP[ta+0]&15;
      GFX_SPR[tb+1]=TMP[ta+0]>>4;
      GFX_SPR[tb+2]=TMP[ta+1]&15;
      GFX_SPR[tb+3]=TMP[ta+1]>>4;
      tb+=16;
   }

   FreeMem(TMP);

   RAMSize=0xA0000+0x20000;

   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;

   if(!load_rom("c07_20-1.74", RAM+0x00000, 0x20000)) return;
   if(!load_rom("c07_21-1.76", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c07_19-1.73", RAM+0x00000, 0x20000)) return;
   if(!load_rom("c07_18-1.71", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("c07-09.75", ROM+0x80000, 0x80000)) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0xA0000;
   if(!load_rom("c07-17.69", Z80ROM, 0x20000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x180000))) return;
   if(!load_rom("c07-12.107",PCMROM+0x000000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("c07-10.95",PCMROM+0x080000,0x80000)) return;	// ADPCM B rom 1/2
   if(!load_rom("c07-11.96",PCMROM+0x100000,0x80000)) return;	// ADPCM B rom 2/2
   YM2610SetBuffers(PCMROM, PCMROM+0x080000, 0x080000, 0x100000);

   AddTaitoYM2610(0x0247, 0x01C7, 0x20000);

   /*-----------------------*/

   /// Checksum Fix

   WriteWord68k(&ROM[0x012BE],0x4E71);		//	nop

   /// Allow Rom Versions

   WriteLong68k(&ROM[0x01280],0x4E714E71);	//	nop

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x012A4],0x13FC0000);	// 	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x012A8],0x00AA0000);
   WriteWord68k(&ROM[0x012AC],0x6100-16);	//	bra.s	<loop>

   memset(RAM+0x00000,0x00,0xA0000);

   GFX_FG0    = RAM+0x64000;
   RAM_INPUT  = RAM+0x3B000;

   tc0100scn[0].RAM     = RAM+0x21000-0x6000;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);

   tc0110pcr_init_typeb(RAM+0x38000, 1, 0);
   tc0110pcr_init_typeb_2(RAM+0x39000, 1, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x38000, 0x80, 0x10, 0x8000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   memset(RAM_INPUT,0x00,0x20);
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x60000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x600000, 0x603FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadByte(0x200000, 0x213FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByte(0x800000, 0x80001F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x600000, 0x603FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadWord(0x200000, 0x213FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWord(0x240000, 0x253FFF, NULL, RAM+0x050000);			// SCREEN B
   AddReadWord(0x400000, 0x400007, tc0110pcr_rw, NULL);			// COLOR RAM SCREEN A
   AddReadWord(0x420000, 0x420007, tc0110pcr_rw_2, NULL);		// COLOR RAM SCREEN B
   AddReadWord(0x800000, 0x80001F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x830000, 0x830003, tc0140syt_read_main_68k, NULL);	// SOUND
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x600000, 0x603FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteByte(0x200000, 0x210FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0x211000, 0x211FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x212000, 0x213FFF, NULL, RAM+0x022000);		// FG0 RAM
   AddWriteByte(0x800000, 0x80001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0x600000, 0x603FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteWord(0x200000, 0x210FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0x211000, 0x211FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x212000, 0x213FFF, NULL, RAM+0x022000);		// FG0 RAM
   AddWriteWord(0x240000, 0x253FFF, NULL, RAM+0x050000);		// SCREEN B
   AddWriteWord(0x400000, 0x400007, tc0110pcr_ww, NULL);		// COLOR RAM SCREEN A
   AddWriteWord(0x420000, 0x420007, tc0110pcr_ww_2, NULL);		// COLOR RAM SCREEN B
   AddWriteWord(0x800000, 0x80001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x220000, 0x22000F, NULL, RAM+0x03B100);		// SCROLL A
   AddWriteWord(0x260000, 0x26000F, NULL, RAM+0x03B200);		// SCROLL B
   AddWriteWord(0x830000, 0x830003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void clear_darius_2_dual(void)
{
   RemoveTaitoYM2610();

#ifdef RAINE_DEBUG
      //save_debug("ROM.bin",ROM,0x080000,1);
      //save_debug("RAM.bin",RAM,0x060000,1);
      //save_debug("GFX.bin",GFX,0x400000,0);
#endif
}

static void execute_drius2do(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 4);

   Taito2610_Frame();			// Z80 and YM2610
}

static void draw_darius_2_dual(void)
{
   int x,y,ta,zz,zzz,zzzz,x16,y16;
   UINT8 *map;

   ClearPaletteMap();

   // BG0
   // ---

   MAKE_SCROLL_1024x512_4_8(
      20-(ReadWord(&RAM[0x3B100])+ReadWord(&RAM[0x20100])),  // Add one of the line-line offsets
      24-(ReadWord(&RAM[0x3B106]))
   );

   START_SCROLL_1024x512_4_8(32,32,640,224);

      ta = ReadWord(&RAM[0x10002+zz])&0x7FFF;

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x10000+zz]&0x7F,
         16,
         map
      );

      switch(RAM[0x10001+zz]&0xC0){
         case 0x00: Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
         case 0x40: Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
         case 0x80: Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
      }

   END_SCROLL_1024x512_4_8();

   // BG1
   // ---

   MAKE_SCROLL_1024x512_4_8(
      20-(ReadWord(&RAM[0x3B102])),
      24-(ReadWord(&RAM[0x3B108]))
   );

   START_SCROLL_1024x512_4_8(32,32,640,224);

   ta=ReadWord(&RAM[0x18002+zz])&0x7FFF;
   if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x18000+zz]&0x7F,
         16,
         map
      );

      if(GFX_BG0_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM[0x18001+zz]&0xC0){
            case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
            case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM[0x18001+zz]&0xC0){
            case 0x00: Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
            case 0x40: Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0x80: Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
         }
      }

   }

   END_SCROLL_1024x512_4_8();

   // OBJECT
   // ------

   for(zz=0x353F8;zz>=0x34000;zz-=8){

   x=((32)+ReadWord(&RAM[zz+6]))&0x3FF;
   y=((32+224+240)-ReadWord(&RAM[zz]))&0x1FF;

   if((x>16)&&(y>16)&&(x<640+32)&&(y<224+32)){
   ta=ReadWord(&RAM[zz+2])&0x1FFF;
   if(GFX_SPR_SOLID[ta]){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[zz+4]&0x7F,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM[zz+7]&0x0C){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
         case 0x04: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         case 0x08: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         case 0x0C: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM[zz+7]&0x0C){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
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
      20-(ReadWord(&RAM[0x3B104])),
      24-(ReadWord(&RAM[0x3B10A]))
   );

   START_SCROLL_1024x256_2_8(32,32,640,224);

      ta = ReadWord(&RAM[0x22000+zz]);

      if(ta&0x00FF){

         MAP_PALETTE_MAPPED_NEW(
            (ta>>8)&0x3F,
            4,
            map
         );

         switch(ta&0xC000){
            case 0x0000: Draw8x8_Trans_Mapped_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);        break;
            case 0x4000: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);  break;
            case 0x8000: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);  break;
            case 0xC000: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map); break;
         }

      }

   END_SCROLL_1024x256_2_8();

}

/*

280000 - 287FFF | BG0 (1024x512 - 4 bytes/tile)
288000 - 28FFFF | BG1 (1024x512 - 4 bytes/tile)
290000 - 2903FF | BG0 LINE
290400 - 2907FF | BG1 LINE
291000 - 291FFF | FG0 GFX (8x8x4 - 16 bytes/tile)
292000 - 293FFF | FG0 (1024x256 - 2 bytes/tile)

*/
static struct VIDEO_INFO video_drius2do =
{
   draw_darius_2_dual,
   640,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_drius2do[] =
{
   { "darius_2_dual_screen", },
   { "darius2d", },
   { "drius2do", },
   { ROMOF("darius2"), },
   { CLONEOF("darius2"), },
   { NULL, },
};
GAME( drius2do, "Darius 2 (dual screen)", TAITO, 1989, GAME_SHOOT,
	.input = input_drius2do,
	.dsw = dsw_drius2do,
	.romsw = romsw_drius2do,
	.clear = clear_darius_2_dual,
	.video = &video_drius2do,
	.exec = execute_drius2do,
	.long_name_jpn = "ダライアス２（２苑面）",
	.board = "C07",
	.sound = contcirc_ym2610_sound,
);

