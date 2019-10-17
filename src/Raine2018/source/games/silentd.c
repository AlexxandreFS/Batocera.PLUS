#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                 SILENT DRAGON (C) 1992 TAITO CORPORATION                   */
/*                                                                            */
/*                    SEL FEENA (C) 1991 EAST TECHNOLOGY                      */
/*                                                                            */
/*                    RYU JIN (C) 1993 TAITO CORPORATION                      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"


static struct ROM_INFO rom_silentd[] =
{
   {   "sd_m05.rom", 0x00100000, 0xe02472c5, 0, 0, 0, },
   {   "sd_m02.rom", 0x00080000, 0xe0de5c39, 0, 0, 0, },
   {   "sd_m03.rom", 0x00100000, 0x1b9b2846, 0, 0, 0, },
   {   "sd_m04.rom", 0x00100000, 0x53237217, 0, 0, 0, },
   {   "sd_m01.rom", 0x00080000, 0xb41fff1a, 0, 0, 0, },
   {   "sd_m06.rom", 0x00100000, 0xe6e6dfa7, 0, 0, 0, },
   {    "sr_09.rom", 0x00020000, 0x2f05b14a, 0, 0, 0, },
   {    "sr_11.rom", 0x00020000, 0x35da4428, 0, 0, 0, },
   {  "sr_12-1.rom", 0x00020000, 0x5883d362, 0, 0, 0, },
   {  "sr_15-1.rom", 0x00020000, 0x8c0a72ae, 0, 0, 0, },
   {    "sr_13.rom", 0x00010000, 0x651861ab, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_silentd[] =
{
   INP0( COIN1, 0x025006, 0x10 ),
   INP0( COIN2, 0x025006, 0x20 ),
   INP0( COIN3, 0x025060, 0x01 ),
   INP0( COIN4, 0x025060, 0x04 ),
   INP0( TILT, 0x025006, 0x01 ),
   INP0( SERVICE, 0x025006, 0x02 ),

   INP0( P1_START, 0x025006, 0x04 ),
   INP0( P1_UP, 0x02500E, 0x01 ),
   INP0( P1_DOWN, 0x02500E, 0x02 ),
   INP0( P1_LEFT, 0x02500E, 0x04 ),
   INP0( P1_RIGHT, 0x02500E, 0x08 ),
   INP0( P1_B1, 0x025004, 0x01 ),
   INP0( P1_B2, 0x025004, 0x02 ),
   INP0( P1_B3, 0x025004, 0x04 ),

   INP0( P2_START, 0x025006, 0x08 ),
   INP0( P2_UP, 0x02500E, 0x10 ),
   INP0( P2_DOWN, 0x02500E, 0x20 ),
   INP0( P2_LEFT, 0x02500E, 0x40 ),
   INP0( P2_RIGHT, 0x02500E, 0x80 ),
   INP0( P2_B1, 0x025004, 0x08 ),
   INP0( P2_B2, 0x025004, 0x10 ),
   INP0( P2_B3, 0x025004, 0x20 ),

   INP0( P3_START, 0x025020, 0x01 ),
   INP0( P3_UP, 0x025020, 0x08 ),
   INP0( P3_DOWN, 0x025020, 0x10 ),
   INP0( P3_LEFT, 0x025020, 0x02 ),
   INP0( P3_RIGHT, 0x025020, 0x04 ),
   INP0( P3_B1, 0x025020, 0x20 ),
   INP0( P3_B2, 0x025020, 0x40 ),
   INP0( P3_B3, 0x025020, 0x80 ),

   INP0( P4_START, 0x025040, 0x01 ),
   INP0( P4_UP, 0x025040, 0x08 ),
   INP0( P4_DOWN, 0x025040, 0x10 ),
   INP0( P4_LEFT, 0x025040, 0x02 ),
   INP0( P4_RIGHT, 0x025040, 0x04 ),
   INP0( P4_B1, 0x025040, 0x20 ),
   INP0( P4_B2, 0x025040, 0x40 ),
   INP0( P4_B3, 0x025040, 0x80 ),

   END_INPUT
};

#define DSW_A_SILENTD \
   { MSG_UNUSED,              0x01, 0x02 },\
   { MSG_OFF,                 0x01, 0x00 },\
   { MSG_ON,                  0x00, 0x00 },\
   { MSG_SCREEN,              0x02, 0x02 },\
   { MSG_NORMAL,              0x02, 0x00 },\
   { MSG_INVERT,              0x00, 0x00 },\
   { MSG_SERVICE,             0x04, 0x02 },\
   { MSG_OFF,                 0x04, 0x00 },\
   { MSG_ON,                  0x00, 0x00 },\
   { MSG_DEMO_SOUND,          0x08, 0x02 },\
   { MSG_OFF,                 0x00, 0x00 },\
   { MSG_ON,                  0x08, 0x00 },

static struct DSW_DATA dsw_data_silent_dragon_0[] =
{
   DSW_A_SILENTD
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_UNKNOWN,             0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_silent_dragon_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Player Hurt Player"),    0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { _("Coin Slots"),            0x20, 0x02 },
   { _("Combined"),              0x20},
   { _("Seperate"),              0x00},
   { MSG_CABINET,             0xC0, 0x04 },
   { _("2 Players"),             0x80},
   { _("3 Players"),             0xC0},
   { _("4 Players / 1 Cab"),     0x40},
   { _("4 Players / 2 Cabs"),    0x00},
   { NULL,                    0,   },
};


static struct DSW_INFO dsw_silentd[] =
{
   { 0x025000, 0xFF, dsw_data_silent_dragon_0 },
   { 0x025002, 0x7F, dsw_data_silent_dragon_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_selfeena[] =
{
   {     "se-02.27", 0x00020000, 0x08f0c8e3, 0, 0, 0, },
   {     "se-01.26", 0x00020000, 0xa06ca64b, 0, 0, 0, },
   {     "se-03.39", 0x00010000, 0x675998be, 0, 0, 0, },
   {      "se-04.2", 0x00080000, 0x920ad100, 0, 0, 0, },
   {      "se-05.1", 0x00080000, 0xd297c995, 0, 0, 0, },
   {     "se-06.11", 0x00080000, 0x80d5e772, 0, 0, 0, },
   {	       NULL,	      0,	  0, 0, 0, 0, },
};

static struct INPUT_INFO input_ryujin[] =
{
   INP0( COIN1, 0x025006, 0x10 ),
   INP0( COIN2, 0x025006, 0x20 ),
   INP0( TILT, 0x025006, 0x01 ),
   INP0( SERVICE, 0x025006, 0x02 ),

   INP0( P1_START, 0x025006, 0x04 ),
   INP0( P1_UP, 0x02500E, 0x01 ),
   INP0( P1_DOWN, 0x02500E, 0x02 ),
   INP0( P1_LEFT, 0x02500E, 0x04 ),
   INP0( P1_RIGHT, 0x02500E, 0x08 ),
   INP0( P1_B1, 0x025004, 0x01 ),
   INP0( P1_B2, 0x025004, 0x02 ),
   INP0( P1_B3, 0x025004, 0x04 ),

   INP0( P2_START, 0x025006, 0x08 ),
   INP0( P2_UP, 0x02500E, 0x10 ),
   INP0( P2_DOWN, 0x02500E, 0x20 ),
   INP0( P2_LEFT, 0x02500E, 0x40 ),
   INP0( P2_RIGHT, 0x02500E, 0x80 ),
   INP0( P2_B1, 0x025004, 0x08 ),
   INP0( P2_B2, 0x025004, 0x10 ),
   INP0( P2_B3, 0x025004, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_sel_feena_0[] =
{
   DSW_A_SILENTD
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_sel_feena_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("100k only"),             0x0C},
   { _("200k only"),             0x08},
   { _("300k only"),             0x04},
   { _("400k only"),             0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "1",                     0x00},
   { "2",                     0x10},
   { "3",                     0x30},
   { "4",                     0x20},
   DSW_UNUSED( 0x00, 0x40),
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_selfeena[] =
{
   { 0x025000, 0xFF, dsw_data_sel_feena_0 },
   { 0x025002, 0xFF, dsw_data_sel_feena_1 },
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_ryujin[] =
{
   {     "ruj02.27", 0x00020000, 0x0d223aee, 0, 0, 0, },
   {     "ruj01.26", 0x00020000, 0xc6bcdd1e, 0, 0, 0, },
   {     "ruj04.29", 0x00020000, 0x0c153cab, 0, 0, 0, },
   {     "ruj03.28", 0x00020000, 0x7695f89c, 0, 0, 0, },
   {     "ruj05.39", 0x00010000, 0x95270b16, 0, 0, 0, },
   {   "ryujin07.2", 0x00100000, 0x34f50980, 0, 0, 0, },
   {   "ryujin06.1", 0x00100000, 0x1b85ff34, 0, 0, 0, },
   {  "ryujin08.11", 0x00080000, 0x480d040d, 0, 0, 0, },
   {	       NULL,	      0,	  0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_ryu_jin_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Energy"),                0x0C, 0x04 },
   { "1",                     0x00},
   { "2",                     0x04},
   { "3",                     0x0C},
   { "4",                     0x08},
   DSW_UNUSED( 0x00, 0x10),
   DSW_UNUSED( 0x00, 0x20),
   DSW_UNUSED( 0x00, 0x40),
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ryujin[] =
{
   { 0x025000, 0xFF, dsw_data_sel_feena_0 },
   { 0x025002, 0xFF, dsw_data_ryu_jin_1 },
   { 0,        0,    NULL,      },
};



static void DecodeBSystemGfx(int tb, int tc, int n, int rev)
{
  if ((!rev && n==0) || (rev && n==3)) {
    GFX[tb+0] = (((tc&0x80)>>7)<<n);
    GFX[tb+1] = (((tc&0x40)>>6)<<n);
    GFX[tb+2] = (((tc&0x20)>>5)<<n);
    GFX[tb+3] = (((tc&0x10)>>4)<<n);
    GFX[tb+4] = (((tc&0x08)>>3)<<n);
    GFX[tb+5] = (((tc&0x04)>>2)<<n);
    GFX[tb+6] = (((tc&0x02)>>1)<<n);
    GFX[tb+7] = (((tc&0x01)>>0)<<n);
  }
  else {
    GFX[tb+0] |= (((tc&0x80)>>7)<<n);
    GFX[tb+1] |= (((tc&0x40)>>6)<<n);
    GFX[tb+2] |= (((tc&0x20)>>5)<<n);
    GFX[tb+3] |= (((tc&0x10)>>4)<<n);
    GFX[tb+4] |= (((tc&0x08)>>3)<<n);
    GFX[tb+5] |= (((tc&0x04)>>2)<<n);
    GFX[tb+6] |= (((tc&0x02)>>1)<<n);
    GFX[tb+7] |= (((tc&0x01)>>0)<<n);
  }
}

static UINT8 *RAM_INPUT;
static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG2;
static UINT8 *GFX_BG2_SOLID;

static void load_silentd(void)
{
   int ta,tb,tc;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x840000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x800000;

   if(!load_rom("sd_m03.rom", RAM, 0x100000)) return;	// GFX
   tb=0;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   tb=0x800000;
   for(ta=0;ta<0x8000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=8;
   }

   if(!load_rom("sd_m04.rom", RAM, 0x100000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   tb=0x800000;
   for(ta=0;ta<0x8000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=8;
   }

   if(!load_rom("sd_m05.rom", RAM, 0x100000)) return;	// GFX
   tb=0x400000;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   tb=0x820000;
   for(ta=0xF8000;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=8;
   }

   if(!load_rom("sd_m06.rom", RAM, 0x100000)) return;
   tb=0x400000;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   tb=0x820000;
   for(ta=0xF8000;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=8;
   }

   RAMSize=0x28000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   if(!load_rom("sr_13.rom", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("sd_m02.rom",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("sd_m01.rom",PCMROM+0x80000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM+0x00000, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x0025, 0x001F, 0x10000);

   /*-----------------------*/

   if(!load_rom("sr_12-1.rom", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("sr_15-1.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("sr_11.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("sr_09.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   memset(RAM+0x00000,0x00,0x28000);
   memset(RAM+0x25020,0xFF,0x00080);

   RAM_INPUT  = RAM+0x25000;
   RAM_VIDEO  = RAM+0x04000;
   RAM_COLOUR = RAM+0x24000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x8000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   // 68000 Speed Hack/Int Fix

   WriteWord68k(&ROM[0x00810],0x4EF9);
   WriteLong68k(&ROM[0x00812],0x00000038);

   WriteWord68k(&ROM[0x00038],0x082D);
   WriteLong68k(&ROM[0x0003A],0x0000005C);

   WriteWord68k(&ROM[0x0003E],0x6700+10);

   WriteLong68k(&ROM[0x00040],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00044],0x00AA0000);	// Speed Hack

   WriteWord68k(&ROM[0x00048],0x6100-18);

   WriteWord68k(&ROM[0x0004A],0x4EF9);
   WriteLong68k(&ROM[0x0004C],0x00000818);

   // 68000 Speed Hack/Int Fix

   WriteWord68k(&ROM[0x00828],0x4EF9);
   WriteLong68k(&ROM[0x0082A],0x0007FF80);

   WriteWord68k(&ROM[0x7FF80],0x082D);
   WriteLong68k(&ROM[0x7FF82],0x0001005C);

   WriteWord68k(&ROM[0x7FF86],0x6600+10);

   WriteLong68k(&ROM[0x7FF88],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x7FF8C],0x00AA0000);	// Speed Hack

   WriteWord68k(&ROM[0x7FF90],0x6100-18);

   WriteWord68k(&ROM[0x7FF92],0x4E75);

   WriteLong68k(&ROM[0x7FF80],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x7FF84],0x00AA0000);	// Speed Hack

   WriteLong68k(&ROM[0x7FF88],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x7FF8C],0x00AA0000);	// Speed Hack

   WriteWord68k(&ROM[0x7FF90],0x4E75);

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO+0x18000;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x7FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x10,0x30,0x20,0x10,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x28000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x400000, 0x403FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x500000, 0x51FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x200000, 0x20000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x210000, 0x21000F, NULL, RAM+0x025020);			// P3 INPUT
   AddReadByte(0x220000, 0x22000F, NULL, RAM+0x025040);			// P3 INPUT
   AddReadByte(0x230000, 0x23000F, NULL, RAM+0x025060);			// P4 INPUT
   AddReadByte(0x240000, 0x24000F, NULL, RAM+0x025080);			// P4 INPUT
   AddReadByte(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x100000, 0x100003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x400000, 0x403FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x500000, 0x51FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x200000, 0x20000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x210000, 0x21000F, NULL, RAM+0x025020);			// P3 INPUT
   AddReadWord(0x220000, 0x22000F, NULL, RAM+0x025040);			// P3 INPUT
   AddReadWord(0x230000, 0x23000F, NULL, RAM+0x025060);			// P4 INPUT
   AddReadWord(0x240000, 0x24000F, NULL, RAM+0x025080);			// P4 INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x400000, 0x403FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x500000, 0x51FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x100000, 0x100003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x200000, 0x20000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x400000, 0x403FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0x500000, 0x51FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x200000, 0x20000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void MemoryMap_SelFeena(void)
{
   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x103FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x200000, 0x21FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x400000, 0x40000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x500000, 0x500003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x103FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x200000, 0x21FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x400000, 0x40000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x103FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x200000, 0x21FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x500000, 0x500003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x400000, 0x40000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x103FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0x200000, 0x21FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x300000, 0x300FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x400000, 0x40000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);
}

static void load_selfeena(void)
{
   int ta,tb,tc;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x200000;

   if(!load_rom("se-04.2", RAM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,1);
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   for(ta=0;ta<0x8000;ta+=2){
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,1);
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,1);
      tb+=8;
   }
   for(ta=0x78000;ta<0x80000;ta+=2){
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,3,1);
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,1);
      tb+=8;
   }
   if(!load_rom("se-05.1", RAM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,1);
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   for(ta=0;ta<0x8000;ta+=2){
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,1);
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,1);
      tb+=8;
   }
   for(ta=0x78000;ta<0x80000;ta+=2){
      tc=RAM[ta+0];
      DecodeBSystemGfx(tb,tc,1,1);
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,1);
      tb+=8;
   }

   RAMSize=0x28000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   if(!load_rom("se-02.27", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("se-01.26", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   if(!load_rom("se-03.39", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("se-06.11",PCMROM,0x80000)) return;            // ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x017F, 0x0152, 0x10000);		// 100% not sure

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);
   memset(RAM+0x25020,0xFF,0x00080);

   RAM_INPUT  = RAM+0x25000;
   RAM_VIDEO  = RAM+0x04000;
   RAM_COLOUR = RAM+0x24000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x0028a],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0028e],0x00AA0000);	// Speed Hack

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO+0x18000;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x1FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x10,0x30,0x20,0x10,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x28000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   MemoryMap_SelFeena();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_ryujin(void)
{
   int ta,tb,tc;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x440000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x400000;

   if(!load_rom("ryujin06.1", RAM+0x00000, 0x100000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   for(ta=0;ta<0x8000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=8;
   }
   for(ta=0xF0000;ta<0xF8000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,0,0);
      tc=RAM[ta];
      DecodeBSystemGfx(tb,tc,1,0);
      tb+=8;
   }

   if(!load_rom("ryujin07.2", RAM+0x00000, 0x100000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   for(ta=0;ta<0x8000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=8;
   }
   for(ta=0xF0000;ta<0xF8000;ta+=2){
      tc=RAM[ta+1];
      DecodeBSystemGfx(tb,tc,2,0);
      tc=RAM[ta];
      DecodeBSystemGfx(tb,tc,3,0);
      tb+=8;
   }

   RAMSize=0x28000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   if(!load_rom("ruj02.27", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("ruj01.26", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("ruj04.29", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("ruj03.28", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   if(!load_rom("ruj05.39", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("ryujin08.11",PCMROM,0x80000)) return;            // ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x023A, 0x01BA, 0x10000);		// 100% not sure

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);
   memset(RAM+0x25020,0xFF,0x00080);

   RAM_INPUT  = RAM+0x25000;
   RAM_VIDEO  = RAM+0x04000;
   RAM_COLOUR = RAM+0x24000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x00908],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0090c],0x00AA0000);	// Speed Hack

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO+0x18000;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x3FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x10,0x30,0x20,0x10,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x28000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   MemoryMap_SelFeena();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_silentd(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   //if((s68000context.pc<0x80)||(s68000context.pc>0x7FF80))
   cpu_interrupt(CPU_68K_0, 6);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   //if((s68000context.pc<0x80)||(s68000context.pc>0x7FF80))
   cpu_interrupt(CPU_68K_0, 4);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(2,60));	// Sync Scroll

   Taito2610_Frame();			// Z80 and YM2610
}

static void execute_ryujin(void)
{
   #ifdef RAINE_DEBUG
     vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60)); // M68000 16MHz (60fps)

   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 4);

   Taito2610_Frame();			// Z80 and YM2610
}

static void DrawSilentD(void)
{
   ClearPaletteMap();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu_layer_count = 0;

   // BG0
   // ---

   vcu_render_bg0();

   // BG1
   // ---

   vcu_render_bg1();

   // OBJ
   // ---

   vcu_render_obj(0x1A0);

   // BG2
   // ---

   vcu_render_bg2();
}

static void DrawRyuJin(void)
{
   int pri;

   ClearPaletteMap();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu_layer_count = 0;

   // BG
   // --

   pri = ReadWord(&tc0180vcu.RAM_2[0]);

   if (pri==0x3200) {
     vcu_render_ryujin_bg(1,pri);
     vcu_render_ryujin_bg(0,pri);
   }
   else {
     vcu_render_ryujin_bg(0,pri);
     vcu_render_ryujin_bg(1,pri);
   }

   // OBJ
   // ---

   vcu_render_obj(0x200);

   // TXT
   // ----

   vcu_render_bg2();
}
static struct VIDEO_INFO video_ryujin =
{
   DrawRyuJin,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
};
static struct VIDEO_INFO video_silentd =
{
   DrawSilentD,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
GMEI( ryujin, "Ryu Jin", TAITO, 1993, GAME_SHOOT);
static struct DIR_INFO dir_selfeena[] =
{
   { "selfeena", },
   { NULL, },
};
GAME( selfeena, "Sel Feena", EAST_TECHNOLOGY, 1991, GAME_PUZZLE,
	.input = input_ryujin,
	.dsw = dsw_selfeena,
	.video = &b_system_video,
	.exec = execute_ryujin,
);
static struct DIR_INFO dir_silentd[] =
{
   { "silent_dragon", },
   { "silentd", },
   { NULL, },
};
GME( silentd, "Silent Dragon", TAITO, 1992, GAME_BEAT,
	.long_name_jpn = "サイレントドラゴン",
);

