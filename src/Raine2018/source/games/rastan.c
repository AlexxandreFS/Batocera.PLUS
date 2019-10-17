/******************************************************************************/
/*                                                                            */
/*               RASTAN/RASTAN SAGA (C) 1987 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc002obj.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "msm5205.h"
#include "2151intf.h"
#include "timer.h"


static struct ROM_INFO rom_rastan[] =
{
  LOAD8_16(  REGION_GFX1,  0x000000,  0x00020000,
             "ic40_01.bin",  0xcd30de19,  "ic67_02.bin",  0x54040fec),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x00020000,
             "ic39_03.bin",  0xab67e064,  "ic66_04.bin",  0x94737e93),
  LOAD8_16(  REGION_GFX2,  0x000000,  0x00020000,
             "ic15_05.bin",  0xc22d94ac,  "ic28_06.bin",  0x002ccf39),
  LOAD8_16(  REGION_GFX2,  0x040000,  0x00020000,
             "ic14_07.bin",  0xb5632a51,  "ic27_08.bin",  0xfeafca05),
   {  "ic49_19.bin", 0x00010000, 0xee81fdd8, 0, 0, 0, },
   {  "ic76_20.bin", 0x00010000, 0xfd1a34cc, 0, 0, 0, },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00010000,
             "ic19_38.bin",  0x1c91dbb1,  "ic07_37.bin",  0xecf20bdd),
  LOAD8_16(  REGION_ROM1,  0x020000,  0x00010000,
             "ic20_40.bin",  0x0930d4b3,  "ic08_39.bin",  0xd95ade5e),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00010000,
             "ic21_42.bin",  0x1857a7cb,  "ic09_43.bin",  0xc34b9152),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_rastan[] =
{
   INP1( COIN1, 0x01A006, 0x20 ),
   INP1( COIN2, 0x01A006, 0x40 ),
   INP0( TILT, 0x01A006, 0x04 ),
   INP0( SERVICE, 0x01A006, 0x01 ),

   INP0( P1_START, 0x01A006, 0x08 ),
   INP0( P1_UP, 0x01A000, 0x01 ),
   INP0( P1_DOWN, 0x01A000, 0x02 ),
   INP0( P1_LEFT, 0x01A000, 0x04 ),
   INP0( P1_RIGHT, 0x01A000, 0x08 ),
   INP0( P1_B1, 0x01A000, 0x10 ),
   INP0( P1_B2, 0x01A000, 0x20 ),

   INP0( P2_START, 0x01A006, 0x10 ),
   INP0( P2_UP, 0x01A002, 0x01 ),
   INP0( P2_DOWN, 0x01A002, 0x02 ),
   INP0( P2_LEFT, 0x01A002, 0x04 ),
   INP0( P2_RIGHT, 0x01A002, 0x08 ),
   INP0( P2_B1, 0x01A002, 0x10 ),
   INP0( P2_B2, 0x01A002, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_rastan_0[] =
{
   DSW_CABINET( 0x01, 0x00),
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

static struct DSW_DATA dsw_data_rastan_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("100k"),                  0x0C},
   { _("150k"),                  0x08},
   { _("200k"),                  0x04},
   { _("250k"),                  0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "6",                     0x00},
   { _("Continue"),              0x40, 0x02 },
   { MSG_ON,                  0x40},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_rastan[] =
{
   { 0x01A008, 0xFF, dsw_data_rastan_0 },
   { 0x01A00A, 0xFF, dsw_data_rastan_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_rastan_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_rastan[] =
{
   { 0x05FFFF, 0x01, romsw_data_rastan_0 },
   { 0,        0,    NULL },
};

static gfx_layout rastan_gfx_tiles =
{
   8,8,
   RGN_FRAC(1,1),
   4,
   {0,1,2,3},
   {STEP8(0,4)},
   {STEP8(0,8*4)},
   8*8*4
};

static gfx_layout rastan_gfx_object =
{
   16,16,
   RGN_FRAC(1,1),
   4,
   {0,1,2,3},
   {STEP16(0,4)},
   {STEP16(0,16*4)},
   16*16*4
};

static struct GFX_LIST rastan_gfx[] =
{
   { REGION_GFX1, &rastan_gfx_tiles,  },
   { REGION_GFX2, &rastan_gfx_object, },
   { 0,           NULL,               },
};


static struct YM2151interface ym2151_interface =
{
  1,			// 1 chip
  4000000,		// 4 MHz
  { YM3012_VOL(160,OSD_PAN_LEFT,160,OSD_PAN_RIGHT) },
  { z80_irq_handler },
  { NULL }
};

static struct msm5205_adpcm_list rastan_adpcm[] =
{
  { 0x000000,0x0001C0-1 },
  { 0x000200,0x0006D4-1 },
  { 0x000700,0x002700-1 },
  { 0x002800,0x006280-1 },
  { 0x006300,0x00B040-1 },
  { 0x00B100,0x00C5F0-1 },
};

static struct MSM5205buffer_interface msm5205_interface =
{
   1,
   { 8000 },
   { 160 },
   { rastan_adpcm },
   { sizeof(rastan_adpcm) / sizeof(struct msm5205_adpcm_list) },
   { NULL },
   { 0 },
   { 0 },
   MSM5205_MONO,
};

static struct SOUND_INFO sound_rastan[] =
{
   { SOUND_YM2151J, &ym2151_interface,  },
   { SOUND_MSM5205_BUFF, &msm5205_interface, },
   { 0,             NULL,               },
};



static struct ROM_INFO rom_rastsaga[] =
{
  LOAD8_16(  REGION_GFX1,  0x000000,  0x00020000,
             "ic40_01.bin",  0xcd30de19,  "ic67_02.bin",  0x54040fec),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x00020000,
             "ic39_03.bin",  0xab67e064,  "ic66_04.bin",  0x94737e93),
  LOAD8_16(  REGION_GFX2,  0x000000,  0x00020000,
             "ic15_05.bin",  0xc22d94ac,  "ic28_06.bin",  0x002ccf39),
  LOAD8_16(  REGION_GFX2,  0x040000,  0x00020000,
             "ic14_07.bin",  0xb5632a51,  "ic27_08.bin",  0xfeafca05),
   {  "ic49_19.bin", 0x00010000, 0xee81fdd8, 0, 0, 0, },
   {  "ic76_20.bin", 0x00010000, 0xfd1a34cc, 0, 0, 0, },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00010000,
             "rs19_38.bin",  0xa38ac909,  "rs07_37.bin",  0xbad60872),
  LOAD8_16(  REGION_ROM1,  0x020000,  0x00010000,
             "rs20_40.bin",  0x6bcf70dc,  "rs08_39.bin",  0x8838ecc5),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00010000,
             "rs21_42.bin",  0xb626c439,  "rs09_43.bin",  0xc928a516),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_rastan_saga_0[] =
{
   DSW_CABINET( 0x01, 0x00),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},	// Alternate coinage in rastan saga
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_rastsaga[] =
{
   { 0x01A008, 0xFF, dsw_data_rastan_saga_0 },
   { 0x01A00A, 0xFF, dsw_data_rastan_1 },
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_rastanu[] =
{
  LOAD8_16(  REGION_GFX1,  0x000000,  0x00020000,
             "ic40_01.bin",  0xcd30de19,  "ic67_02.bin",  0x54040fec),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x00020000,
             "ic39_03.bin",  0xab67e064,  "ic66_04.bin",  0x94737e93),
  LOAD8_16(  REGION_GFX2,  0x000000,  0x00020000,
             "ic15_05.bin",  0xc22d94ac,  "ic28_06.bin",  0x002ccf39),
  LOAD8_16(  REGION_GFX2,  0x040000,  0x00020000,
             "ic14_07.bin",  0xb5632a51,  "ic27_08.bin",  0xfeafca05),
   {  "ic49_19.bin", 0x00010000, 0xee81fdd8, 0, 0, 0, },
   {  "ic76_20.bin", 0x00010000, 0xfd1a34cc, 0, 0, 0, },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00010000,
             "ic19_38.bin",  0x1c91dbb1,  "ic07_37.bin",  0xecf20bdd),
  LOAD8_16(  REGION_ROM1,  0x020000,  0x00010000,
               "b04-45.20",  0x362812dd,     "b04-44.8",  0x51cc5508),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00010000,
             "ic21_42.bin",  0x1857a7cb,   "b04-41-1.9",  0xbd403269),
   {           NULL,          0,          0, 0, 0, 0, },
};



static struct ROM_INFO rom_rastanu2[] =
{
  LOAD8_16(  REGION_GFX1,  0x000000,  0x00020000,
             "ic40_01.bin",  0xcd30de19,  "ic67_02.bin",  0x54040fec),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x00020000,
             "ic39_03.bin",  0xab67e064,  "ic66_04.bin",  0x94737e93),
  LOAD8_16(  REGION_GFX2,  0x000000,  0x00020000,
             "ic15_05.bin",  0xc22d94ac,  "ic28_06.bin",  0x002ccf39),
  LOAD8_16(  REGION_GFX2,  0x040000,  0x00020000,
             "ic14_07.bin",  0xb5632a51,  "ic27_08.bin",  0xfeafca05),
   {  "ic49_19.bin", 0x00010000, 0xee81fdd8, 0, 0, 0, },
   {  "ic76_20.bin", 0x00010000, 0xfd1a34cc, 0, 0, 0, },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00010000,
             "rs19_38.bin",  0xa38ac909,     "b04-21.7",  0x7c8dde9a),
  LOAD8_16(  REGION_ROM1,  0x020000,  0x00010000,
               "b04-23.20",  0x254b3dce,     "b04-22.8",  0x98e8edcf),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00010000,
               "b04-25.21",  0xd1e5adee,     "b04-24.9",  0xa3dcc106),
   {           NULL,          0,          0, 0, 0, 0, },
};


static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_OBJECT;

static void Rastan_M5205_W(UINT16 offset, UINT8 data);

static void load_rastan(void)
{
   RAMSize=0x20000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x20000;
   if(!(PCMROM=AllocateMem(0x10000))) return;

   if(!load_rom("ic49_19.bin", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM
   if(!load_rom("ic76_20.bin", PCMROM, 0x10000)) return;

   AddTaitoYM2151(0x01C0, 0x01AB, 0x10000, (UINT8 *) Rastan_M5205_W, NULL);

   msm5205_interface.rom[0] = PCMROM;
   msm5205_interface.romsize[0] = 0x10000;
   msm5205_interface.updatemode = MSM5205_MONO;

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x20000);

   RAM[0x1A007]=0x9F;			// !! Vital !!

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B080;
   RAM_OBJECT = RAM+0x18000;

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x8000);

   // 68000 Speed Hack
   // ----------------

   if(is_current_game("rastan"))
   {
      WriteLong68k(&ROM[0x00146],0x4E714E71);	//	nop
      WriteLong68k(&ROM[0x3B08C],0x13FC0000);	//	move.b	#$00,$AA0000
      WriteLong68k(&ROM[0x3B090],0x00AA0000);	//
      WriteWord68k(&ROM[0x3B094],0x4E71);	//	nop
   }
   if(is_current_game("rastsaga"))
   {
      WriteLong68k(&ROM[0x3B088],0x13FC0000);	//	move.b	#$00,$AA0000
      WriteLong68k(&ROM[0x3B08C],0x00AA0000);	//
      WriteWord68k(&ROM[0x3B090],0x4E71);	//	nop
   }

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM    =RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].SCR    =RAM_SCROLL+0;
   tc0100scn[0].layer[0].type   =0;
   tc0100scn[0].layer[0].bmp_x  =32;
   tc0100scn[0].layer[0].bmp_y  =32;
   tc0100scn[0].layer[0].bmp_w  =320;
   tc0100scn[0].layer[0].bmp_h  =240;
// Mapper disabled
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x  =16;
   tc0100scn[0].layer[0].scr_y  =8;

   tc0100scn[0].layer[1].RAM    =RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].SCR    =RAM_SCROLL+2;
   tc0100scn[0].layer[1].type   =0;
   tc0100scn[0].layer[1].bmp_x  =32;
   tc0100scn[0].layer[1].bmp_y  =32;
   tc0100scn[0].layer[1].bmp_w  =320;
   tc0100scn[0].layer[1].bmp_h  =240;
// Mapper disabled
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x  =16;
   tc0100scn[0].layer[1].scr_y  =8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   init_tc0100scn(0);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.RAM        = RAM_OBJECT;
   tc0002obj.GFX        = NULL;
   tc0002obj.bmp_x      = 32;
   tc0002obj.bmp_y      = 32;
   tc0002obj.bmp_w      = 320;
   tc0002obj.bmp_h      = 240;
// Mapper disabled
   tc0002obj.tile_mask  = 0x0FFF;
   tc0002obj.ofs_x      = 0;
   tc0002obj.ofs_y      = -8;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x1B100);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x10C000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);
   AddReadByte(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddReadByte(0x200000, 0x203FFF, NULL, RAM+0x004000);
   AddReadByte(0x390000, 0x390FFF, NULL, RAM+0x01A000);			// INPUT
   AddReadByte(0x350000, 0x35000F, NULL, RAM+0x01B010);
   AddReadByte(0x380000, 0x380001, NULL, RAM+0x01B00A);
   AddReadByte(0x3C0000, 0x3C0001, NULL, RAM+0x01B020);
   AddReadByte(0x3E0000, 0x3E0003, tc0140syt_read_main_68k, NULL);
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x10C000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);
   AddReadWord(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddReadWord(0x200000, 0x203FFF, NULL, RAM+0x004000);
   AddReadWord(0x390000, 0x390FFF, NULL, RAM+0x01A000);			// INPUT
   AddReadWord(0x350000, 0x35000F, NULL, RAM+0x01B010);
   AddReadWord(0x380000, 0x380001, NULL, RAM+0x01B00A);
   AddReadWord(0x3C0000, 0x3C0001, NULL, RAM+0x01B020);
   AddReadWord(0x3E0000, 0x3E0003, NULL, RAM+0x01B00C);
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x10C000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);
   AddWriteByte(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddWriteByte(0x200000, 0x203FFF, NULL, RAM+0x004000);
   AddWriteByte(0xC20000, 0xC20003, NULL, RAM_SCROLL+6);                // SCROLL Y
   AddWriteByte(0xC40000, 0xC40003, NULL, RAM_SCROLL+0);                // SCROLL X
   AddWriteByte(0xC50000, 0xC50001, NULL, RAM_SCROLL+14);               // CTRL
   AddWriteByte(0x350000, 0x35000F, NULL, RAM+0x01B010);
   AddWriteByte(0x380000, 0x380001, NULL, RAM+0x01B00A);
   AddWriteByte(0x390000, 0x390FFF, NULL, RAM+0x01A000);		// INPUT
   AddWriteByte(0x3C0000, 0x3C0001, NULL, RAM+0x01B020);
   AddWriteByte(0x3E0000, 0x3E0003, tc0140syt_write_main_68k, NULL);
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x10C000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);
   AddWriteWord(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddWriteWord(0x200000, 0x203FFF, NULL, RAM+0x004000);
   AddWriteWord(0xC20000, 0xC20003, NULL, RAM_SCROLL+6);                // SCROLL Y
   AddWriteWord(0xC40000, 0xC40003, NULL, RAM_SCROLL+0);                // SCROLL X
   AddWriteWord(0xC50000, 0xC50001, NULL, RAM_SCROLL+14);               // CTRL
   AddWriteWord(0x350000, 0x35000F, NULL, RAM+0x01B010);
   AddWriteWord(0x380000, 0x380001, NULL, RAM+0x01B00A);
   AddWriteWord(0x390000, 0x390FFF, NULL, RAM+0x01A000);		// INPUT
   AddWriteWord(0x3C0000, 0x3C0001, NULL, RAM+0x01B020);
   AddWriteWord(0x3E0000, 0x3E0003, NULL, RAM+0x01B00C);
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_rastan(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));    // M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);

   Taito2151_Frame();			// Z80 and YM2151 and MSM5205
}

static void draw_rastan(void)
{
   ClearPaletteMap();

   if (!tc0002obj.GFX) {
     tc0100scn[0].layer[0].GFX    =gfx[0];
     tc0100scn[0].layer[0].MASK   =gfx_solid[0];
     tc0100scn[0].layer[1].GFX    = gfx[0];
     tc0100scn[0].layer[1].MASK   =gfx_solid[0];
     tc0002obj.GFX        = gfx[1];
     tc0002obj.MASK       = gfx_solid[1];
   }

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.ctrl       = TC0002OBJ_CONV_CTRL(ReadWord(&RAM[0x1B00A]));
   tc0002obj.ctrl      &= ~0x2000;

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1+OBJECT
   // ----------

   if((tc0002obj.ctrl & 0x2000)==0){
      render_tc0100scn_layer_mapped(0,1,1);
      render_tc0002obj_mapped();
   }
   else{
      render_tc0002obj_mapped();
      render_tc0100scn_layer_mapped(0,1,1);
   }

}

/*-------[MSM5205 PORT A]-------*/

static void Rastan_M5205_W(UINT16 offset, UINT8 data)
{
   int ta;

   if((offset&15)==0){

   switch(data){
      case 0x00: ta=0; break;
      case 0x02: ta=1; break;
      case 0x07: ta=2; break;
      case 0x28: ta=3; break;
      case 0x63: ta=4; break;
      case 0xB1: ta=5; break;
      default:  ta=-1; break;
   }

   if(ta>0){
      MSM5205buffer_request( 0, ta );
   }
   else{
      print_debug("Rastan_MSM5205[%02x]\n",data);
   }

   }
}

static struct VIDEO_INFO video_rastan =
{
   draw_rastan,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
   rastan_gfx,
};
GMEI( rastan, "Rastan", TAITO, 1987, GAME_BEAT | GAME_PLATFORM,
	.romsw = romsw_rastan,
	.long_name_jpn = "ラスタンサーガ",
	.board = "B04",
);
static struct DIR_INFO dir_rastanu[] =
{
   { "rastan_american", },
   { "rastan_usa", },
   { "rastanu", },
   { ROMOF("rastan"), },
   { CLONEOF("rastan"), },
   { NULL, },
};
CLNE( rastanu,rastan, "Rastan American", TAITO, 1987, GAME_BEAT | GAME_PLATFORM,
	.romsw = romsw_rastan,
	.long_name_jpn = "ラスタンサーガ American",
	.board = "B04",
);
static struct DIR_INFO dir_rastanu2[] =
{
   { "rastan_american_alt", },
   { "rastan_usa_2", },
   { "rastanu2", },
   { ROMOF("rastan"), },
   { CLONEOF("rastan"), },
   { NULL, },
};
CLNE( rastanu2, rastan,"Rastan American (alternate)", TAITO, 1987, GAME_BEAT | GAME_PLATFORM,
	.romsw = romsw_rastan,
	.long_name_jpn = "ラスタンサーガ American (alternate)",
	.board = "B04",
);
static struct DIR_INFO dir_rastsaga[] =
{
   { "rastan_saga", },
   { "rastsaga", },
   { ROMOF("rastan"), },
   { CLONEOF("rastan"), },
   { NULL, },
};
CLNE( rastsaga,rastan, "Rastan Saga", TAITO, 1987, GAME_BEAT | GAME_PLATFORM,
	.dsw = dsw_rastsaga,
	.romsw = NULL, // rastan_saga_romsw,
	.long_name_jpn = "ラスタンサーガ Saga",
	.board = "B04",
);

