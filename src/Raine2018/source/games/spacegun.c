#define DRV_DEF_SOUND taito_ym2610b_sound
/******************************************************************************/
/*                                                                            */
/*                     SPACE GUN (C) 1991 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "gun.h"
#ifdef SDL
#include "sdl/control_internal.h"
#endif


static struct ROM_INFO rom_spacegun[] =
{
   {       "c57-16.29", 0x00020000, 0xbfb5d1e7, 0, 0, 0, },
   {       "c57-07.76", 0x00080000, 0xad653dc1, 0, 0, 0, },
   {       "c57-06.52", 0x00080000, 0x4ebadd5b, 0, 0, 0, },
   {       "c57-05.36", 0x00080000, 0x6a70eb2e, 0, 0, 0, },
   {       "c57-03.12", 0x00100000, 0xfafca86f, 0, 0, 0, },
   {       "c57-02.24", 0x00100000, 0x21ee4633, 0, 0, 0, },
   {       "c57-01.25", 0x00100000, 0xf901b04e, 0, 0, 0, },
   {       "c57-15.27", 0x00020000, 0xb36eb8f1, 0, 0, 0, },
   {       "c57-08.75", 0x00080000, 0x22593550, 0, 0, 0, },
   {       "c57-17.59", 0x00020000, 0xe197edb8, 0, 0, 0, },
   {       "c57-18.62", 0x00020000, 0x19d7d52e, 0, 0, 0, },
   {       "c57-22.73", 0x00020000, 0x5855fde3, 0, 0, 0, },
   {       "c57-20.74", 0x00020000, 0x2e58253f, 0, 0, 0, },
   {       "c57-04.11", 0x00100000, 0xa9787090, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_spacegun[] =
{
   INP0( COIN1, 0x044004, 0x08 ),
   INP0( COIN2, 0x044004, 0x04 ),
   INP0( TILT, 0x044004, 0x20 ),
   INP0( SERVICE, 0x044004, 0x10 ),

   INP0( P1_START, 0x044004, 0x40 ),
   INP1( P1_UP, 0x044010, 0x01 ),
   INP1( P1_DOWN, 0x044010, 0x02 ),
   INP1( P1_LEFT, 0x044010, 0x04 ),
   INP1( P1_RIGHT, 0x044010, 0x08 ),
   { KB_DEF_P1_B1,        "P1 Trigger",            0x04400E, 0x01, BIT_ACTIVE_0 },
   { KB_DEF_P1_B2,        "P1 Bomb",               0x04400E, 0x04, BIT_ACTIVE_0 },
   { KB_DEF_P1_B3,        "P1 Pedal",              0x044004, 0x01, BIT_ACTIVE_0 },

   INP0( P2_START, 0x044004, 0x80 ),
   INP1( P2_UP, 0x044020, 0x01 ),
   INP1( P2_DOWN, 0x044020, 0x02 ),
   INP1( P2_LEFT, 0x044020, 0x04 ),
   INP1( P2_RIGHT, 0x044020, 0x08 ),
   { KB_DEF_P2_B1,        "P2 Trigger",            0x04400E, 0x02, BIT_ACTIVE_0 },
   { KB_DEF_P2_B2,        "P2 Bomb",               0x04400E, 0x08, BIT_ACTIVE_0 },
   { KB_DEF_P2_B3,        "P2 Pedal",              0x044004, 0x02, BIT_ACTIVE_0 },

   END_INPUT
};

static struct DSW_DATA dsw_data_space_gun_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};


static struct DSW_DATA dsw_fake_input_behaviour[] =
{

   { _("Mouse Speed"),           0x04, 0x02 },
   { _("Slow"),                  0x04},
   { _("Fast"),                  0x00},
   { _("Digital Input Speed"),   0x08, 0x02 },
   { _("Slow"),                  0x08},
   { _("Fast"),                  0x00},
   { _("P1 Input Control"),      0x30, 0x04 },
   { _("Mouse"),                 0x30},
   { _("Analog Joystick"),       0x20},
   { _("Digital"),               0x10},
   { MSG_UNUSED,                0x00},
   { _("Show Crosshair"),        0xC0, 0x04 },
   { _("All"),                   0xC0},
   { _("Player 1 Only"),         0x80},
   { _("Player 2 Only"),         0x40},
   { _("None"),                  0x00},


   { NULL,                    0,   },
};

static struct DSW_INFO dsw_spacegun[] =
{
   { 0x044000, 0xFF, dsw_data_space_gun_0 },
   { 0x044002, 0xFF, dsw_data_default_1 },
   { 0x044005, 0xF3, dsw_fake_input_behaviour },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_space_gun_0[] =
{
   { "Taito America",            0x01 },
   { "Taito America (FBI logo)", 0x02 },
   { "Taito Japan",              0x03 },
   { "Taito Japan (Romstar)",    0x05 },
   { NULL,                       0    },
};

static struct ROMSW_INFO romsw_spacegun[] =
{
   { 0x07FFFF, 0x03, romsw_data_space_gun_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static int BadReadByte(UINT32 address)
{
   #ifdef RAINE_DEBUG
      //print_debug("Rb%01d(%06x) [%06x]\n",tcpu,address,s68000context.pc);
   #endif
   return(0xFF);
}

static int BadReadWord(UINT32 address)
{
   #ifdef RAINE_DEBUG
       //print_debug("Rw%01d(%06x) [%06x]\n",tcpu,address,s68000context.pc);
   #endif
   return(0);
}

static void BadWriteByte(UINT32 address, UINT8 data)
{
   #ifdef RAINE_DEBUG
      //print_debug("Wb%01d(%06x,%02x) [%06x]\n",tcpu,address,data,s68000context.pc);
   #endif
}

static void BadWriteWord(UINT32 address, UINT16 data)
{
   #ifdef RAINE_DEBUG
      //print_debug("Ww%01d(%06x,%04x) [%06x]\n",tcpu,address,data,s68000context.pc);
   #endif
}

static int YM2610Read68k(UINT32 address)
{
   return YM2610ReadZ80( (UINT16) ((address&7)>>1) );
}

static void YM2610Write68k(UINT32 address, UINT16 data)
{
   YM2610WriteZ80( (UINT16) ((address&7)>>1) , (UINT8) data);
}

#if 0
static void BadWByte(UINT32 address, UINT8 data){
  print_ingame(120," Mem:%08x = %02x", address, data );
}
static void BadWWord(UINT32 address, UINT16 data){
  print_ingame(120," Mem:%08x=%04x", address, data );
}
#endif
static void PanWrite(UINT32 address, UINT8 data){
  Pan2610WriteZ80_OffsetVol( (UINT16) ((address&7)>>1) , data );
}

static void load_spacegun(void)
{
   int ta,tb,tc,td,te,tf;
   UINT8 *TMP;

   if(!(TMP=AllocateMem(0xF94B0+0x7CA580))) return;

   tb=0xF94B0;
   if(!load_rom("c57-04.11", TMP, 0xF94B0)) return;		// 16x8 SPRITES
   for(ta=0;ta<0xF94B0;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]=((tc&0x8000)>>(15-0));
      TMP[tb+1]=((tc&0x4000)>>(14-0));
      TMP[tb+2]=((tc&0x2000)>>(13-0));
      TMP[tb+3]=((tc&0x1000)>>(12-0));
      TMP[tb+4]=((tc&0x0800)>>(11-0));
      TMP[tb+5]=((tc&0x0400)>>(10-0));
      TMP[tb+6]=((tc&0x0200)>>(9-0));
      TMP[tb+7]=((tc&0x0100)>>(8-0));
      TMP[tb+8]=((tc&0x0080)>>(7-0));
      TMP[tb+9]=((tc&0x0040)>>(6-0));
      TMP[tb+10]=((tc&0x0020)>>(5-0));
      TMP[tb+11]=((tc&0x0010)>>(4-0));
      TMP[tb+12]=((tc&0x0008)>>(3-0));
      TMP[tb+13]=((tc&0x0004)>>(2-0));
      TMP[tb+14]=((tc&0x0002)>>(1-0));
      TMP[tb+15]=((tc&0x0001)>>(0-0));
      tb+=16;
   }
   tb=0xF94B0;
   if(!load_rom("c57-03.12", TMP, 0xF94B0)) return;		// 16x8 SPRITES
   for(ta=0;ta<0xF94B0;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]|=((tc&0x8000)>>(15-1));
      TMP[tb+1]|=((tc&0x4000)>>(14-1));
      TMP[tb+2]|=((tc&0x2000)>>(13-1));
      TMP[tb+3]|=((tc&0x1000)>>(12-1));
      TMP[tb+4]|=((tc&0x0800)>>(11-1));
      TMP[tb+5]|=((tc&0x0400)>>(10-1));
      TMP[tb+6]|=((tc&0x0200)>>(9-1));
      TMP[tb+7]|=((tc&0x0100)>>(8-1));
      TMP[tb+8]|=((tc&0x0080)>>(7-1));
      TMP[tb+9]|=((tc&0x0040)>>(6-1));
      TMP[tb+10]|=((tc&0x0020)>>(5-1));
      TMP[tb+11]|=((tc&0x0010)>>(4-1));
      TMP[tb+12]|=((tc&0x0008)>>(3-1));
      TMP[tb+13]|=((tc&0x0004)>>(2-1));
      TMP[tb+14]|=((tc&0x0002)>>(0));
      TMP[tb+15]|=((tc&0x0001)<<(1));
      tb+=16;
   }
   tb=0xF94B0;
   if(!load_rom("c57-02.24", TMP, 0xF94B0)) return;		// 16x8 SPRITES
   for(ta=0;ta<0xF94B0;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]|=((tc&0x8000)>>(15-2));
      TMP[tb+1]|=((tc&0x4000)>>(14-2));
      TMP[tb+2]|=((tc&0x2000)>>(13-2));
      TMP[tb+3]|=((tc&0x1000)>>(12-2));
      TMP[tb+4]|=((tc&0x0800)>>(11-2));
      TMP[tb+5]|=((tc&0x0400)>>(10-2));
      TMP[tb+6]|=((tc&0x0200)>>(9-2));
      TMP[tb+7]|=((tc&0x0100)>>(8-2));
      TMP[tb+8]|=((tc&0x0080)>>(7-2));
      TMP[tb+9]|=((tc&0x0040)>>(6-2));
      TMP[tb+10]|=((tc&0x0020)>>(5-2));
      TMP[tb+11]|=((tc&0x0010)>>(4-2));
      TMP[tb+12]|=((tc&0x0008)>>(3-2));
      TMP[tb+13]|=((tc&0x0004)>>(0));
      TMP[tb+14]|=((tc&0x0002)<<(1));
      TMP[tb+15]|=((tc&0x0001)<<(2));
      tb+=16;
   }
   tb=0xF94B0;
   if(!load_rom("c57-01.25", TMP, 0xF94B0)) return;		// 16x8 SPRITES
   for(ta=0;ta<0xF94B0;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]|=((tc&0x8000)>>(15-3));
      TMP[tb+1]|=((tc&0x4000)>>(14-3));
      TMP[tb+2]|=((tc&0x2000)>>(13-3));
      TMP[tb+3]|=((tc&0x1000)>>(12-3));
      TMP[tb+4]|=((tc&0x0800)>>(11-3));
      TMP[tb+5]|=((tc&0x0400)>>(10-3));
      TMP[tb+6]|=((tc&0x0200)>>(9-3));
      TMP[tb+7]|=((tc&0x0100)>>(8-3));
      TMP[tb+8]|=((tc&0x0080)>>(7-3));
      TMP[tb+9]|=((tc&0x0040)>>(6-3));
      TMP[tb+10]|=((tc&0x0020)>>(5-3));
      TMP[tb+11]|=((tc&0x0010)>>(4-3));
      TMP[tb+12]|=((tc&0x0008)>>(0));
      TMP[tb+13]|=((tc&0x0004)<<(1));
      TMP[tb+14]|=((tc&0x0002)<<(2));
      TMP[tb+15]|=((tc&0x0001)<<(3));
      tb+=16;
   }

   if(!(GFX=AllocateMem(0x100000+0xF61000+0x2000))) return;

   te=0;
   if(!load_rom("c57-05.36", TMP, 0x3D840)) return;		// 64x64 SPRITES
   for(ta=0x100000;ta<(0x100000+0xF61000);ta+=0x1000){
      for(tb=0;tb<8;tb++){
      for(tc=0;tc<4;tc++){
         td=ReadWord(&TMP[te])<<7;
         td+=0xF94B0;
         te+=2;
         for(tf=0;tf<8;tf++){
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+0],ReadLong(&TMP[td+0]));
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+4],ReadLong(&TMP[td+4]));
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+8],ReadLong(&TMP[td+8]));
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+12],ReadLong(&TMP[td+12]));
            td+=16;
         }
      }
      }
   }

   tb=0;
   if(!load_rom("c57-06.52", TMP, 0x80000)) return;		// 8x8 BG TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      tb+=4;
   }

   FreeMem(TMP);

   GFX_BG0=GFX+0x000000;
   GFX_SPR=GFX+0x100000;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x4000);
   GFX_SPR_SOLID = MakeSolidTileMap64x64(GFX_SPR, 0xF61);

   for(tb=0;tb<0xF61000;tb+=64){			// Flip Y Axis
   for(ta=0;ta<32;ta++){
      tc=GFX_SPR[tb+ta];
      GFX_SPR[tb+ta]=GFX_SPR[tb+63-ta];
      GFX_SPR[tb+63-ta]=tc;
   }
   }

   Init64x64_Table(&GFX[0x100000+0xF61000]);			// $1000x2

   RAMSize=0x50000+0x10000;

   if(!(ROM=AllocateMem(0xC0000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;

   if(!load_rom("c57-18.62", RAM, 0x20000)) return;	// MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c57-20.74", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("c57-17.59", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("c57-22.73", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   if(!load_rom("c57-15.27", RAM, 0x20000)) return;	// SUB 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom("c57-16.29", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("c57-08.75",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("c57-07.76",PCMROM+0x80000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   Pan2610_OffsetVol( 4 );	/* set volume shift size */

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x48000);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x24800;
   RAM_INPUT  = RAM+0x44000;
   GFX_FG0    = RAM+0x48000;

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
   InitPaletteMap(RAM+0x38000, 0x100, 0x10, 0x8000);

   tc0110pcr_init(RAM+0x38000, 1);

   ROM[0x23C0]=0x4E;		// V-PROG ROM ERROR
   ROM[0x23C1]=0x71;
   ROM[0x23C2]=0x4E;
   ROM[0x23C3]=0x71;

   ROM[0x80E74]=0x4E;		// M-PROG ROM ERROR
   ROM[0x80E75]=0x71;

   ROM[0x23D2]=0x4E;		// EE-ROM ERROR
   ROM[0x23D3]=0x71;
   ROM[0x23D4]=0x4E;
   ROM[0x23D5]=0x71;

   ROM[0x80076]=0x0B;		// INT#5
   ROM[0x80077]=0xF2;

   ROM[0x80BF2]=0x48;		// IMPROVE INT#5
   ROM[0x80BF3]=0xE7;
   ROM[0x80BF4]=0xC0;
   ROM[0x80BF5]=0xC0;

   ROM[0x809A6]=0x13;		// move.b #$00,$AA0000
   ROM[0x809A7]=0xFC;		// Speed Hack
   ROM[0x809A8]=0x00;
   ROM[0x809A9]=0x00;
   ROM[0x809AA]=0x00;
   ROM[0x809AB]=0xAA;
   ROM[0x809AC]=0x00;
   ROM[0x809AD]=0x00;

   ROM[0x809AE]=0x60;
   ROM[0x809AF]=0xF6;

   ROM[0x9AA]=0x13;		// move.b #$00,$AA0000
   ROM[0x9AB]=0xFC;		// Speed Hack
   ROM[0x9AC]=0x00;
   ROM[0x9AD]=0x00;
   ROM[0x9AE]=0x00;
   ROM[0x9AF]=0xAA;
   ROM[0x9B0]=0x00;
   ROM[0x9B1]=0x00;

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=64;
   tc0100scn[0].layer[0].bmp_y	=64;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=20;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=64;
   tc0100scn[0].layer[1].bmp_y	=64;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=20;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=64;
   tc0100scn[0].layer[2].bmp_y	=64;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=240;
   tc0100scn[0].layer[2].scr_x	=20;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xC0000);
   ByteSwap(RAM,0x48000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x310000, 0x31FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x30C000, 0x30FFFF, NULL, RAM+0x020000);			// V-WORK RAM
   AddReadByte(0x000000, 0xFFFFFF, BadReadByte, NULL);			// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x30C000, 0x30FFFF, NULL, RAM+0x020000);			// V-WORK RAM
   AddReadWord(0x310000, 0x31FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xB00000, 0xB00007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x500000, 0x5007FF, NULL, RAM+0x024000);			// OBJECT RAM
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x310000, 0x31FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x906000, 0x906FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, BadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x30C000, 0x30FFFF, NULL, RAM+0x020000);		// V-WORK RAM
   AddWriteWord(0x310000, 0x31FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0x500000, 0x5007FF, NULL, RAM+0x024000);		// OBJECT RAM
   AddWriteWord(0x906000, 0x906FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x920000, 0x92000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xB00000, 0xB00007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...


   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM+0x080000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x080000);			// 68000 ROM
   AddReadByteMC68000B(0x20C000, 0x20FFFF, NULL, RAM+0x040000);			// SUB LOCAL RAM
   AddReadByteMC68000B(0x210000, 0x21FFFF, NULL, RAM+0x000000);			// COMMON RAM
   AddReadByteMC68000B(0x800000, 0x80000F, NULL, RAM_INPUT);			// INPUT
   AddReadByteMC68000B(0x000000, 0xFFFFFF, BadReadByte, NULL);			// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x080000);			// 68000 ROM
   AddReadWordMC68000B(0x20C000, 0x20FFFF, NULL, RAM+0x040000);			// SUB LOCAL RAM
   AddReadWordMC68000B(0x210000, 0x21FFFF, NULL, RAM+0x000000);			// COMMON RAM
   AddReadWordMC68000B(0x800000, 0x80000F, NULL, RAM_INPUT);			// INPUT
   AddReadWordMC68000B(0xC00000, 0xC00007, YM2610Read68k, NULL);		// YM2610
   AddReadWordMC68000B(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x20C000, 0x20FFFF, NULL, RAM+0x040000);		// SUB LOCAL RAM
   AddWriteByteMC68000B(0x210000, 0x21FFFF, NULL, RAM+0x000000);		// COMMON RAM
   AddWriteByteMC68000B(0x800000, 0x80000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   //AddWriteByteMC68000B(0x000000, 0xFFFFFF, BadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x20C000, 0x20FFFF, NULL, RAM+0x040000);		// SUB LOCAL RAM
   AddWriteWordMC68000B(0x210000, 0x21FFFF, NULL, RAM+0x000000);		// COMMON RAM
   AddWriteWordMC68000B(0xC00000, 0xC00007, YM2610Write68k, NULL);		// YM2610
   AddWriteWordMC68000B(0xC20000, 0xC20007, PanWrite, NULL);                    // PANNING
   AddWriteWordMC68000B(0x800000, 0x80000F, tc0220ioc_ww, NULL);		// INPUT
   //AddWriteWordMC68000B(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...

   GameMouse=1;
}

static int x1,x2,myy1,y2,x11,myy11;

static void execute_spacegun(void)
{


/*----------[Start of Player 1 Gun Input Emulation]------------*/



/* User selects mouse control on fake dipswitch - Default */
if ((RAM[0x44005] &0x20) && (RAM[0x44005] &0x10)){

 if (RAM[0x44005] &0x4)                //Slow
    {set_mouse_range(0,0,319,239);
    x11=319-mouse_x;
    myy11=mouse_y;}

 else                                  //Fast
    {set_mouse_range(0,0,159,119);
    x11=319-(mouse_x*2);
    myy11=(mouse_y*2);}

    x1=(x11<<7)/320;
    myy1=(myy11<<7)/240;

    if(x1<0){x1=0;}
    if(x1>127){x1=127;}
    if(myy1<0){myy1=0;}
    if(myy1>127){myy1=127;}

    if(mouse_b&1) RAM[0x4400E] &= ~0x01;
    if(mouse_b&2) RAM[0x4400E] &= ~0x04;

    RAM[0xE2B4]=x1+128-64;
    RAM[0xE2B6]=myy1+128-64;}


else{

 /* User selects analog joystick control on fake dipswitch */
 if (RAM[0x44005] &0x20){

   /*------[Analog Joystick Hack]-------*/
#ifdef SDL
   RAM[0xE2B4]=((-analog_normx)>>8)+128;
   RAM[0xE2B6]=(analog_normy>>8)+128;
#else
   RAM[0xE2B4]=(-joy[0].stick[0].axis[0].pos)/2+128;
   RAM[0xE2B6]=joy[0].stick[0].axis[1].pos/2+128;
#endif

  }

 /* User selects digital control on fake dipswitch */
 if (RAM[0x44005] &0x10){

   /*-----[Player 1 Keyboard Hack - Slow]-----*/
   if  (RAM[0x44005]&0x08){
   if(((RAM[0x44010]&0x01)!=0)&&(myy1>0)){myy1-=1;}
   if(((RAM[0x44010]&0x02)!=0)&&(myy1<127)){myy1+=1;}
   if(((RAM[0x44010]&0x08)!=0)&&(x1>0)){x1-=1;}
   if(((RAM[0x44010]&0x04)!=0)&&(x1<127)){x1+=1;}
   }

   else{

   /*-----[Player 1 Keyboard Hack - Fast]-----*/
   if(((RAM[0x44010]&0x01)!=0)&&(myy1>0)){myy1-=2;}
   if(((RAM[0x44010]&0x02)!=0)&&(myy1<127)){myy1+=2;}
   if(((RAM[0x44010]&0x08)!=0)&&(x1>0)){x1-=2;}
   if(((RAM[0x44010]&0x04)!=0)&&(x1<127)){x1+=2;}
   }


   RAM[0xE2B4]=x1+128-64;
   RAM[0xE2B6]=myy1+128-64;

  }
 }



/*----------[End of Player 1 Gun Input Emulation]------------*/



   /*-----[Player 2 Keyboard Hack - Slow]-----*/
   if  (RAM[0x44005]&0x08){
   if(((RAM[0x44020]&0x01)!=0)&&(y2>0)){y2-=1;}
   if(((RAM[0x44020]&0x02)!=0)&&(y2<127)){y2+=1;}
   if(((RAM[0x44020]&0x08)!=0)&&(x2>0)){x2-=1;}
   if(((RAM[0x44020]&0x04)!=0)&&(x2<127)){x2+=1;}
   }

   else{

   /*-----[Player 2 Keyboard Hack - Fast]-----*/
   if(((RAM[0x44020]&0x01)!=0)&&(y2>0)){y2-=2;}
   if(((RAM[0x44020]&0x02)!=0)&&(y2<127)){y2+=2;}
   if(((RAM[0x44020]&0x08)!=0)&&(x2>0)){x2-=2;}
   if(((RAM[0x44020]&0x04)!=0)&&(x2<127)){x2+=2;}
   }

   /*----[Player 2 Write Positions]----*/

   RAM[0xE2B8]=x2+128-64;
   RAM[0xE2BA]=y2+128-64;


   /*------[EE-ROM Hack]------*/

   WriteLong(&RAM[0x0006+0x00], 0x00C00040);
   WriteLong(&RAM[0x0006+0x04], 0x80000002);
   WriteLong(&RAM[0x0006+0x08], 0x00C00040);
   WriteLong(&RAM[0x0006+0x0C], 0xE0000001);

   WriteLong(&RAM[0x0006+0x10], 0x00C00040);
   WriteLong(&RAM[0x0006+0x14], 0x80000002);
   WriteLong(&RAM[0x0006+0x18], 0x00C00040);
   WriteLong(&RAM[0x0006+0x1C], 0xE0000001);

   WriteLong(&RAM[0x0006+0x20], 0x00800080);
   WriteLong(&RAM[0x0006+0x24], 0x00800080);
   WriteLong(&RAM[0x0006+0x28], 0x80000002);
   WriteLong(&RAM[0x0006+0x2C], 0xE0000001);

   WriteLong(&RAM[0x0006+0x30], 0x80000002);
   WriteLong(&RAM[0x0006+0x34], 0xE0000001);

   WriteLong(&RAM[0x0006+0x38], 0x80000002);
   WriteLong(&RAM[0x0006+0x3C], 0xE0000001);

   WriteLong(&RAM[0x0006+0x40], 0x80000002);
   WriteLong(&RAM[0x0006+0x44], 0xE0000001);

   WriteLong(&RAM[0x0006+0x24], 0x00800080);

   /*----[Run the 68000's]----*/

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));
   cpu_interrupt(CPU_68K_0, 4);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(16,60));
   cpu_interrupt(CPU_68K_1, 4);
   cpu_interrupt(CPU_68K_1, 5);
}

static void DrawSpaceGun(void)
{
   int x,y,ta,zz;
   int zx,zy;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped_flipy(0,0);

   // OBJECT LOW
   // ----------

   for(zz=0x24600-8;zz>=0x24000;zz-=8){

      if((RAM[zz+3]&0x80)!=0){

      zx=RAM[zz+4]&63;
      zy=(RAM[zz+1]>>1)&63;
      if((zx!=0)&&(zy!=0)){
         y=RAM[zz];
         if((RAM[zz+1]&1)!=0){y=0-((y^255)+1);}
         y=32+20+y;
         x=ReadWord(&RAM[zz+2])&0x1FF;
         if(x>400){x=0-((x^511)+1);}
         x=(320+(63-zx))-x;

         if((x>0)&&(y>0)&&(x<320+64)&&(y<240+64)){
            ta=ReadWord(&RAM[zz+6])&0xFFF;

            if(ta!=0){

            MAP_PALETTE_MAPPED_NEW(
               RAM[zz+5],
               16,
               MAP
            );

               if(GFX_SPR_SOLID[ta]==0){
                  if((RAM[zz+7]&0x80)==0){
                     if((RAM[zz+3]&0x40)==0){
			 Draw64x64_Trans_Mapped_Zoom2_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);
		     }
                     else{
 			 Draw64x64_Trans_Mapped_Zoom2_FlipY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);
		     }
                  }else{
                     if((RAM[zz+3]&0x40)==0){	Draw64x64_Trans_Mapped_Zoom2_FlipX_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                     else{			Draw64x64_Trans_Mapped_Zoom2_FlipXY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                  }
               }
               else{
                  if((RAM[zz+7]&0x80)==0){
                     if((RAM[zz+3]&0x40)==0){
		 	 Draw64x64_Mapped_Zoom2_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);
		     }
                     else{
 			 Draw64x64_Mapped_Zoom2_FlipY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);
		     }
                  }else{
                     if((RAM[zz+3]&0x40)==0){	Draw64x64_Mapped_Zoom2_FlipX_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                     else{			Draw64x64_Mapped_Zoom2_FlipXY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                  }
               }

            }
         }
      }
      }
   }

   // BG1
   // ---

   render_tc0100scn_layer_mapped_flipy(0,1);

   // OBJECT HIGH
   // -----------

   for(zz=0x24600-8;zz>=0x24000;zz-=8){

      if((RAM[zz+3]&0x80)==0){

      zx=RAM[zz+4]&63;
      zy=(RAM[zz+1]>>1)&63;
      if((zx!=0)&&(zy!=0)){
         y=RAM[zz];
         if((RAM[zz+1]&1)!=0){y=0-((y^255)+1);}
         y=32+20+y;
         x=ReadWord(&RAM[zz+2])&0x1FF;
         if(x>400){x=0-((x^511)+1);}
         x=(320+(63-zx))-x;

         if((x>0)&&(y>0)&&(x<320+64)&&(y<240+64)){
            ta=ReadWord(&RAM[zz+6])&0xFFF;

            if(ta!=0){

            MAP_PALETTE_MAPPED_NEW(
               RAM[zz+5],
               16,
               MAP
            );

               if(GFX_SPR_SOLID[ta]==0){
                  if((RAM[zz+7]&0x80)==0){
                     if((RAM[zz+3]&0x40)==0){	Draw64x64_Trans_Mapped_Zoom2_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                     else{			Draw64x64_Trans_Mapped_Zoom2_FlipY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                  }else{
                     if((RAM[zz+3]&0x40)==0){	Draw64x64_Trans_Mapped_Zoom2_FlipX_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                     else{			Draw64x64_Trans_Mapped_Zoom2_FlipXY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                  }
               }
               else{
                  if((RAM[zz+7]&0x80)==0){
                     if((RAM[zz+3]&0x40)==0){	Draw64x64_Mapped_Zoom2_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                     else{			Draw64x64_Mapped_Zoom2_FlipY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                  }else{
                     if((RAM[zz+3]&0x40)==0){	Draw64x64_Mapped_Zoom2_FlipX_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                     else{			Draw64x64_Mapped_Zoom2_FlipXY_Rot(&GFX_SPR[ta<<12],x,y,MAP,zx,zy);}
                  }
               }

            }
         }
      }
      }
   }

   // FG0
   // ---

   render_tc0100scn_layer_mapped_flipy(0,2);

   // GUNS
   // ----

/*----------[Start of Gun Targetting]------------*/

if (RAM[0x44005] &0x40){
   // Player 2 Targetting
   x=(64+(((127-x2)*320)>>7))-7;
   y=(64+((y2*240)>>7))-7;
   if((x>48)&&(y>48)&&(x<320+64)&&(y<240+64)){
      disp_gun(1,x,y);
   }
 }


if (RAM[0x44005] &0x80){
   // Player 1 Targetting
   x=(64+(((127-(RAM[0xE2B4]-64))*320)>>7))-7;
   y=(64+(((RAM[0xE2B6]-64)*240)>>7))-7;
   if((x>48)&&(y>48)&&(x<320+64)&&(y<240+64)){
      disp_gun(0,x,y);
   }
 }


/*----------[End of Gun Targetting]------------*/

}

/*

Sprite List Format (8 bytes/sprite)
===================================

Byte | Bit(s) | Description
-----+76543210+--------------------
  0  |.xxxxxx.| ZoomY (0-63)
  0  |.......x| Y Position (High)
  1  |xxxxxxxx| Y Position (Low)
  2  |.x......| Flip Y Axis
  2  |x.......| Sprite:BG1 Priority
  2  |..?????x| X Position (High)
  3  |xxxxxxxx| X Position (Low)
  4  |xxxxxxxx| Palette Bank
  5  |..xxxxxx| ZoomX (0-63)
  6  |x.......| Flip X Axis?
  6  |.....xxx| Sprite Number (High)
  7  |xxxxxxxx| Sprite Number (Low)

*/
static struct VIDEO_INFO video_spacegun =
{
   DrawSpaceGun,
   320,
   240,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_spacegun[] =
{
   { "space_gun", },
   { "spacegun", },
   { NULL, },
};
GME( spacegun, "Space Gun", TAITO, 1990, GAME_SHOOT,
	.romsw = romsw_spacegun,
	.long_name_jpn = "âXâyü[âXâKâô",
	.board = "C57",
);

