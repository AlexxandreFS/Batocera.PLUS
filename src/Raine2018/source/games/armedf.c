#define DRV_DEF_SOUND nichi_ym3812_sound
/******************************************************************************/
/*                                                                            */
/*                    ARMED FORMATION (C) 1987 NICHIBUTSU                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "nichisnd.h"
#include "blit.h" // clear_game_screen
#include "profile.h" // fps


static struct ROM_INFO rom_armedf[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x10000,
            "af_06.rom",  0xc5326603, "af_01.rom",  0x458e9542),
  LOAD8_16(  REGION_ROM1,  0x20000,  0x10000,
            "af_07.rom",  0xcc8517f5, "af_02.rom",  0x214ef220),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x10000,
            "af_08.rom",  0xd1d43600, "af_03.rom",  0xbbe1fe2d),
  { "af_10.rom", 0x10000, 0xc5eacb87, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "af_09.rom", 0x08000, 0x7025e92d, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "af_04.rom", 0x10000, 0x44d3af4f, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "af_05.rom", 0x10000, 0x92076cab, REGION_GFX2, 0x10000, LOAD_NORMAL },
  { "af_14.rom", 0x10000, 0x8c5dc5a7, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "af_13.rom", 0x10000, 0x136a58a3, REGION_GFX3, 0x10000, LOAD_NORMAL },
  { "af_11.rom", 0x20000, 0xb46c473c, REGION_GFX4, 0x00000, LOAD_NORMAL },
  { "af_12.rom", 0x20000, 0x23cb6bfe, REGION_GFX4, 0x20000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_cclimbr2[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x10000,
            "4.bin",  0x7922ea14, "1.bin",  0x2ac7ed67),
  LOAD8_16(  REGION_ROM1,  0x20000,  0x10000,
            "6.bin",  0x7905c992, "5.bin",  0x47be6c1e),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x10000,
            "3.bin",  0x1fb110d6, "2.bin",  0x0024c15b),
  { "11.bin", 0x04000, 0xfe0175be, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "12.bin", 0x08000, 0x5ddf18f2, REGION_ROM2, 0x04000, LOAD_NORMAL },
  { "10.bin", 0x08000, 0x7f475266, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "7.bin", 0x10000, 0xcbdd3906, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "8.bin", 0x10000, 0xb2a613c0, REGION_GFX2, 0x10000, LOAD_NORMAL },
  { "17.bin", 0x10000, 0xe24bb2d7, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "18.bin", 0x10000, 0x56834554, REGION_GFX3, 0x10000, LOAD_NORMAL },
  { "15.bin", 0x10000, 0x4bf838be, REGION_GFX4, 0x00000, LOAD_NORMAL },
  { "16.bin", 0x10000, 0x21a265c5, REGION_GFX4, 0x10000, LOAD_NORMAL },
  { "13.bin", 0x10000, 0x6b6ec999, REGION_GFX4, 0x20000, LOAD_NORMAL },
  { "14.bin", 0x10000, 0xf426a4ad, REGION_GFX4, 0x30000, LOAD_NORMAL },
  { "9.bin", 0x4000, 0x740d260f, REGION_GFX5, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static GFX_LAYOUT char_layout =
{
	8,8,
	RGN_FRAC(1,1),
	4,
	{ 0, 1, 2, 3 },
	{ 4, 0, 12, 8, 20, 16, 28, 24},
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8
};

static GFX_LAYOUT tile_layout =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0, 1, 2, 3 },
	{ 4, 0, 12, 8, 20, 16, 28, 24,
			32+4, 32+0, 32+12, 32+8, 32+20, 32+16, 32+28, 32+24 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64,
			8*64, 9*64, 10*64, 11*64, 12*64, 13*64, 14*64, 15*64 },
	128*8
};

static GFX_LAYOUT sprite_layout =
{
	16,16,
	RGN_FRAC(1,2),
	4,
	{ 0, 1, 2, 3 },
	{ 4, 0, RGN_FRAC(1,2)+4, RGN_FRAC(1,2)+0, 12, 8, RGN_FRAC(1,2)+12, RGN_FRAC(1,2)+8,
			20, 16, RGN_FRAC(1,2)+20, RGN_FRAC(1,2)+16, 28, 24, RGN_FRAC(1,2)+28, RGN_FRAC(1,2)+24 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32,
			8*32, 9*32, 10*32, 11*32, 12*32, 13*32, 14*32, 15*32 },
	64*8
};

static GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &char_layout,}, //	 0*16,	32 },
	{ REGION_GFX2,  &tile_layout,	}, //	64*16,	32 },
	{ REGION_GFX3,  &tile_layout,	}, //	96*16,	32 },
	{ REGION_GFX4,  &sprite_layout,}, //	32*16,	32 },
	{ -1 } /* end of array */
};

static struct INPUT_INFO input_armedf[] =
{
   INP0( COIN1, 0x00C001, 0x04 ),
   INP0( COIN2, 0x00C001, 0x08 ),
   INP0( SERVICE, 0x00C003, 0x01 ),
   INP0( TEST, 0x00C003, 0x02 ),
   INP0( TILT, 0x00C003, 0x04 ),

   INP0( P1_START, 0x00C001, 0x01 ),
   INP0( P1_UP, 0x00C000, 0x01 ),
   INP0( P1_DOWN, 0x00C000, 0x02 ),
   INP0( P1_LEFT, 0x00C000, 0x04 ),
   INP0( P1_RIGHT, 0x00C000, 0x08 ),
   INP0( P1_B1, 0x00C000, 0x10 ),
   INP0( P1_B2, 0x00C000, 0x20 ),
   INP0( P1_B3, 0x00C000, 0x40 ),

   INP0( P2_START, 0x00C001, 0x02 ),
   INP0( P2_UP, 0x00C002, 0x01 ),
   INP0( P2_DOWN, 0x00C002, 0x02 ),
   INP0( P2_LEFT, 0x00C002, 0x04 ),
   INP0( P2_RIGHT, 0x00C002, 0x08 ),
   INP0( P2_B1, 0x00C002, 0x10 ),
   INP0( P2_B2, 0x00C002, 0x20 ),
   INP0( P2_B3, 0x00C002, 0x40 ),

   END_INPUT
};

static struct INPUT_INFO input_cclimbr2[] =
{
   INP0( COIN1, 0x018001, 0x04 ),
   INP0( COIN2, 0x018001, 0x08 ),
   INP0( SERVICE, 0x018003, 0x01 ),
   INP0( TEST, 0x018003, 0x02 ),
   INP0( TILT, 0x018003, 0x04 ),

   INP0( P1_START, 0x018001, 0x01 ),
   INP0( P1_UP, 0x018000, 0x01 ),
   INP0( P1_DOWN, 0x018000, 0x02 ),
   INP0( P1_LEFT, 0x018000, 0x04 ),
   INP0( P1_RIGHT, 0x018000, 0x08 ),
   INP0( P1_B5, 0x018000, 0x10 ),
   INP0( P1_B2, 0x018000, 0x20 ),
   INP0( P1_B1, 0x018000, 0x40 ),
   INP0( P1_B3, 0x018000, 0x80 ),

   INP0( P2_START, 0x018001, 0x02 ),
   INP0( P2_UP, 0x018002, 0x01 ),
   INP0( P2_DOWN, 0x018002, 0x02 ),
   INP0( P2_LEFT, 0x018002, 0x04 ),
   INP0( P2_RIGHT, 0x018002, 0x08 ),
   INP0( P2_B5, 0x018002, 0x10 ),
   INP0( P2_B2, 0x018002, 0x20 ),
   INP0( P2_B1, 0x018002, 0x40 ),
   INP0( P2_B3, 0x018002, 0x80 ),

   END_INPUT
};

#define COINAGE_ARMEDFORMATION \
   { MSG_COIN1,               0x03, 0x04 },\
   { MSG_2COIN_1PLAY,         0x01, 0x00 },\
   { MSG_1COIN_1PLAY,         0x03, 0x00 },\
   { MSG_1COIN_2PLAY,         0x02, 0x00 },\
   { MSG_FREE_PLAY,           0x00, 0x00 },\
   { MSG_COIN2,               0x0C, 0x04 },\
   { MSG_2COIN_1PLAY,         0x04, 0x00 },\
   { MSG_1COIN_1PLAY,         0x0C, 0x00 },\
   { MSG_2COIN_3PLAY,         0x00, 0x00 },\
   { MSG_1COIN_2PLAY,         0x08, 0x00 },

static struct DSW_DATA dsw_data_armed_formation_0[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "3",                     0x03},
   { "4",                     0x02},
   { "5",                     0x01},
   { "6",                     0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("20000, every 60000"),    0x0C, 0x00 },
   { _("20000, every 80000"),    0x04, 0x00 },
   { _("40000, every 60000"),    0x08, 0x00 },
   { _("40000, every 80000")},
   DSW_DEMO_SOUND( 0x10, 0x00),
   DSW_CABINET( 0x00, 0x20),
   { MSG_DIFFICULTY,          0xC0, 0x04 },
   { MSG_EASY,                0xC0},
   { MSG_NORMAL,              0x80},
   { MSG_HARD,                0x40},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_armed_formation_1[] =
{
   COINAGE_ARMEDFORMATION
   { MSG_CONTINUE_PLAY,       0x30, 0x04 },
   { MSG_NO,                  0x30},
   { _("3 Times"),               0x20},
   { _("5 Times"),               0x10},
   { MSG_YES,                 0x00},
   DSW_SCREEN( 0x40, 0x00),
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_armedf[] =
{
   { 0x00C004, 0xBF, dsw_data_armed_formation_0 },
   { 0x00C006, 0xCF, dsw_data_armed_formation_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_crazy_climber2_0[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "3",                     0x03},
   { "4",                     0x02},
   { "5",                     0x01},
   { "6",                     0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("30000 and 100000"),      0x0C},
   { _("60000 and 130000"),      0x04},
   { _("30000 only"),            0x08},
   { _("60000 only"),            0x00},
   DSW_DEMO_SOUND( 0x10, 0x00),
   DSW_CABINET( 0x00, 0x20),
   { MSG_DIFFICULTY,          0x40, 0x02 },
   { MSG_NORMAL,              0x40},
   { MSG_HARD,                0x00},
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_crazy_climber2_1[] =
{
   COINAGE_ARMEDFORMATION
   { MSG_CONTINUE_PLAY, 0x10, 2 },
   { _("3 Times"), 0x10 },
   { MSG_NO, 0x00 },
   DSW_SCREEN( 0x20, 0x00),
   { _("Invulnerability"),       0x40, 0x02 },
   { MSG_NO,                  0x40},
   { MSG_YES,                 0x00},
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_cclimbr2[] =
{
   { 0x018004, 0xFF, dsw_data_crazy_climber2_0 },
   { 0x018006, 0xFF, dsw_data_crazy_climber2_1 },
   { 0,        0,    NULL,      },
};

static void load_armedf(void);
static void DrawArmedF(void);
static void execute_armedf(void);



static void execute_cclimbr2(void);



static void load_cclimbr2(void);


static UINT8 *GFX_BG0;
static UINT8 *GFX_BG1;
static UINT8 *GFX_SPR;
static UINT8 *GFX_FG0;

static UINT8 *MSK_BG0;
static UINT8 *MSK_BG1;
static UINT8 *MSK_SPR;
static UINT8 *MSK_FG0;

static UINT32 io_w; // Address of io_w
static UINT32 bg_videoram,fg_videoram,tx_info;
static UINT8 scroll_type,sprite_offy,fg_method;
int x_res, sp_off;

static int layer_id_data[4];
static char *layer_id_name[4] =
{
   "BG0", "OBJ", "BG1","FG0",
};

static int border,resx,resy;

static void finish_conf() {
  int i,j;
  UINT32 *GFX;
  for (i=0; i<4; i++) {
    layer_id_data[i] = add_layer_info(layer_id_name[i]);
     GFX = (UINT32*)load_region[REGION_GFX1+i];
     for (j=0; j<get_region_size(REGION_GFX1+i)/4; j++)
       GFX[j] ^= 0xffffffff;
   }
   AddInitMemory();	// Set Starscream mem pointers...
   border = current_game->video->border_size;
   resx = current_game->video->screen_x;
   resy = current_game->video->screen_y;
}

static void load_armedf(void)
{
   x_res = 320; sp_off = 16;

   RAMSize=0x40000+0x10000;
   io_w = 0xd000;
   bg_videoram = 0x6000;
   fg_videoram = 0x7000;
   scroll_type = 0;
   sprite_offy = 96;
   tx_info = 0x9300;
   fg_method = 0;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM[0x57]=0x00;
   Z80ROM[0x58]=0x00;

   Z80ROM[0x70]=0x00;
   Z80ROM[0x71]=0x00;

   AddNichibutsuYM3526(0x0082, 0x0077);

   AddNichiSample(0x015F, 0x0161, 1);
   AddNichiSample(0x0162, 0x0164, 1);

   AddNichiSample(0x5040, 0x559A, 1);
   AddNichiSample(0x559B, 0x57BC, 1);
   AddNichiSample(0x57BD, 0x5E1D, 1);
   AddNichiSample(0x5E1E, 0x6EBE, 1);
   AddNichiSample(0x6EBF, 0x754F, 1);
   AddNichiSample(0x7550, 0x7EC1, 1);

   AddNichiSample(0x8040, 0x9040, 1);
   AddNichiSample(0x9041, 0x9FD1, 1);
   AddNichiSample(0x9FD2, 0xB6C2, 3);
   AddNichiSample(0xB6C3, 0xCB13, 1);
   AddNichiSample(0xCB14, 0xE5E4, 1);
   AddNichiSample(0xE5E5, 0xF5E4, 2);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
   InitPaletteMap(RAM+0xA000, 0x100, 0x10, 0x1000);

   // 68000 Checksum Fix
   // ------------------

   WriteLong68k(&ROM[0x0DF98],0x4E714E71);	// 	nop

   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x0E81C],0x4EF9);		// 	jmp	$5D000
   WriteLong68k(&ROM[0x0E81E],0x0005D000);	//

   WriteLong68k(&ROM[0x5D000],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x5D004],0x00AA0000);	//	(Speed Hack)

   WriteWord68k(&ROM[0x5D008],0x6100-10);	//	bra.s	<loop>

   // Change Sound Comm Address (for speed)
   // -------------------------------------

   WriteLong68k(&ROM[0x0E5EC],0x00BB0000);
   WriteLong68k(&ROM[0x0E736],0x00BB0000);
   WriteLong68k(&ROM[0x0E7B2],0x00BB0000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x10000);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);
   AddReadByte(0x060000, 0x06FFFF, NULL, RAM+0x000000);
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);
   AddReadWord(0x060000, 0x06FFFF, NULL, RAM+0x000000);
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x060000, 0x06FFFF, NULL, RAM+0x000000);
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x060000, 0x06FFFF, NULL, RAM+0x000000);
   AddWriteWord(0xBB0000, 0xBB0001, NichiSoundCommWrite68k, NULL);
   AddWriteWord(-1, -1, NULL, NULL);

   finish_conf();
}

static void load_cclimbr2(void)
{
   x_res = 288; sp_off = 0;

   RAMSize=0x40000+0x10000;

   io_w = 0x1c000;
   bg_videoram = 0x14000;
   fg_videoram = 0x10000;
   sprite_offy = -32;
   tx_info = 0x8b00;
   fg_method = 1;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----------------------*/


   memset(RAM+0x00000,0x00,0x40000);

   set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
   InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x1000);

   if (is_current_game("cclimbr2")) {
     scroll_type = 1;
     // 68000 Checksum Fix
     // ------------------

     WriteLong68k(&ROM[0x12f98],0x4E714E71);	// 	nop

#if 0
     // 68000 Speed Hack
     // ----------------
     WriteWord68k(&ROM[0x0E81C],0x4EF9);		// 	jmp	$5D000
     WriteLong68k(&ROM[0x0E81E],0x0005D000);	//

     WriteLong68k(&ROM[0x5D000],0x13FC0000);	//	move.b	#$00,$AA0000
     WriteLong68k(&ROM[0x5D004],0x00AA0000);	//	(Speed Hack)

     WriteWord68k(&ROM[0x5D008],0x6100-10);	//	bra.s	<loop>
#endif

     // Change Sound Comm Address (for speed)
     // -------------------------------------

     WriteLong68k(&ROM[0x13532],0x00BB0000);
     WriteLong68k(&ROM[0x1369A],0x00BB0000);
     WriteLong68k(&ROM[0x13726],0x00BB0000);
     /*-----[Sound Setup]-----*/

     AddNichibutsuYM3526(0x0077, 0x006F);
     /*
	AddNichiSample(0x015F, 0x0161, 1);
	AddNichiSample(0x0162, 0x0164, 1);

	AddNichiSample(0x5040, 0x559A, 1);
	AddNichiSample(0x559B, 0x57BC, 1);
	AddNichiSample(0x57BD, 0x5E1D, 1);
	AddNichiSample(0x5E1E, 0x6EBE, 1);
	AddNichiSample(0x6EBF, 0x754F, 1);
	AddNichiSample(0x7550, 0x7EC1, 1);

	AddNichiSample(0x8040, 0x9040, 1);
	AddNichiSample(0x9041, 0x9FD1, 1);
	AddNichiSample(0x9FD2, 0xB6C2, 3);
	AddNichiSample(0xB6C3, 0xCB13, 1);
	AddNichiSample(0xCB14, 0xE5E4, 1);
	AddNichiSample(0xE5E5, 0xF5E4, 2);
	*/
   }
   /*
    *  StarScream Stuff follows
    */

   ByteSwap(ROM,get_region_size(REGION_ROM1));

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);
   AddRWBW(0x060000, 0x07FFFF, NULL, RAM+0x000000);
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xBB0000, 0xBB0001, NichiSoundCommWrite68k, NULL);
   AddWriteWord(-1, -1, NULL, NULL);

   finish_conf();
}

static void execute_armedf(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);

   Nichibutsu3526_Frame();		// Z80 and YM3526

   if (s68000readPC()==0xE090)
     make_dipswitch_bytes();		// fix dsw
}

static void execute_cclimbr2(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);

   Nichibutsu3526_Frame();		// Z80 and YM3526
}

static void draw_sprites(int priority) {
   int zz,x,y,ta;
   UINT8 *map;
   if (check_layer_enabled(layer_id_data[1])) {
   if(ReadWord(&RAM[io_w]) & 0x0800){

   for(zz=0;zz<0x600;zz+=8){

      if(((ReadWord(&RAM[zz+0])&0x3000)>>12) == priority){

      ta=ReadWord(&RAM[zz+2])&0x7FF;
      if(MSK_SPR[ta]!=0){				// No pixels; skip

	if (fg_method) {
	  y=((224+16) - ReadWord(&RAM[zz+0]))&0x1FF;
	  x=((128 - (sprite_offy)) + ReadWord(&RAM[zz+6]))&0x1FF;
	} else {
	  y=((320+32+32) - ReadWord(&RAM[zz+0]))&0x1FF;
	  x=((32 - (sprite_offy)) + ReadWord(&RAM[zz+6]))&0x1FF;
	}

      if((x>sp_off)&&(y>sp_off)&&(x<x_res+16+sp_off)&&(y<224+16+sp_off)){

         MAP_PALETTE_MAPPED_NEW(
            (RAM[zz+5]&0x1F)|0x20,
            16,
            map
         );

         if(MSK_SPR[ta]==1){				// Some pixels; trans
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }


      }
      }
      }
   }
   }
   }
}

static void DrawArmedF(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta,scrollx,scrolly;
   UINT8 *map;

   ClearPaletteMap();
   if (RefreshBuffers) {
     GFX_BG0 = gfx3;
     GFX_BG1 = gfx2;
     GFX_SPR = load_region[REGION_GFX4];
     GFX_FG0 = gfx1;

     MSK_BG0 = gfx3_solid;
     MSK_BG1 = gfx2_solid;
     MSK_SPR = gfx_solid[3];
     MSK_FG0 = gfx1_solid;
   }

   // BG0

   if (check_layer_enabled(layer_id_data[0])) {
     if(ReadWord(&RAM[io_w]) & 0x0200){

     scrolly = ReadWord(&RAM[io_w+2])+112-16;
     scrollx = ReadWord(&RAM[io_w+4])+16;

     MAKE_SCROLL_512x1024_2_16(scrollx,scrolly);

     START_SCROLL_512x1024_2_16(border,border,resy,resx);
     MAP_PALETTE_MAPPED_NEW(
			  (RAM[bg_videoram+1+zz]>>3)|0x60,
			  16,
			  map
			  );

     Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord(&RAM[bg_videoram+zz])&0x03FF)<<8],y,x,map);
     END_SCROLL_512x1024_2_16();
   }
   else{
      clear_game_screen(0);
   }
   } else
     clear_game_screen(0);


   // OBJECT
   draw_sprites(2);

   // BG1
   if (check_layer_enabled(layer_id_data[2])) {
   if(ReadWord(&RAM[io_w]) & 0x0400){

     if (scroll_type) {
       /* scrolling is handled by the protection mcu */
       scrolly = (RAM[0x8000+13*2] | (RAM[0x8000+14*2]<<8))+112;
       scrollx = (RAM[0x8000+11*2] | (RAM[0x8000+12*2]<<8))+16;
     } else {
       scrollx = ReadWord(&RAM[io_w+8])+16;
       scrolly = ReadWord(&RAM[io_w+6])+96;
     }
     //fprintf(stderr,"%d & %d (%d)\n",scrollx,scrolly,scroll_type);
     MAKE_SCROLL_512x1024_2_16(
			     scrollx,
			     scrolly
   );

     START_SCROLL_512x1024_2_16(border,border,resy,resx);

     ta = ReadWord(&RAM[fg_videoram+zz]) & 0x03FF;

     if(MSK_BG1[ta]!=0){				// No pixels; skip

       MAP_PALETTE_MAPPED_NEW(
			    (RAM[fg_videoram+1+zz]>>3)|0x40,
			    16,
			    map
			    );

       if(MSK_BG1[ta]==1)				// Some pixels; trans
	 Draw16x16_Trans_Mapped_Rot(&GFX_BG1[ta<<8],y,x,map);
       else						// all pixels; solid
	 Draw16x16_Mapped_Rot(&GFX_BG1[ta<<8],y,x,map);

     }

     END_SCROLL_512x1024_2_16();
     }
   }

   draw_sprites(1);

   // FG0
   if (check_layer_enabled(layer_id_data[3])) {
   if(ReadWord(&RAM[io_w]) & 0x0100){
     if (fg_method) {
       zz=-0x280;
       for(y=232;y>0;y-=8){
	 for(x=32;x<256+32;x+=8){
	   ta = ((RAM[tx_info+zz]&3)<<8) | (RAM[0x8300+zz]);
	   if(MSK_FG0[ta]!=0){				// No pixels; skip

	     MAP_PALETTE_MAPPED_NEW(
				(RAM[tx_info+zz]>>4),
				16,
				map
				);

	     if(MSK_FG0[ta]==1){				// Some pixels; trans
	       Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
	     }
	     else{						// all pixels; solid
	       Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
	     }
	   }

	   zz+=2;
	 }
	 //zz+=2;
       }
       zz=-0x280;
       for(y=232;y>0;y-=8){
	 for(x=0;x<32;x+=8){
	   ta = ((RAM[tx_info+0x1000+zz+56]&3)<<8) | (RAM[0x8300+0x1000+zz+56]);
	   if(MSK_FG0[ta]!=0){				// No pixels; skip

	     MAP_PALETTE_MAPPED_NEW( (RAM[tx_info+0x1000+zz+56]>>4), 16, map);

	     Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
	   }
	   ta = ((RAM[tx_info+0x1000+zz]&3)<<8) | (RAM[0x8300+0x1000+zz]);
	   if(MSK_FG0[ta]!=0){				// No pixels; skip

	     MAP_PALETTE_MAPPED_NEW( (RAM[tx_info+0x1000+zz]>>4), 16, map);

	     Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x+256+32,y,map);
	   }
	   zz+=2;
	 }
	 zz+=56;
       }

     } else { // Armed formation
       zz=4;
       for(x=32;x<320+32;x+=8){
	 for(y=32;y<224+32;y+=8){

	   ta = ((RAM[tx_info+zz]&3)<<8) | (RAM[0x8300+zz]);

	   if(MSK_FG0[ta]!=0){				// No pixels; skip

	     MAP_PALETTE_MAPPED_NEW(
				(RAM[tx_info+zz]>>4),
				16,
				map
				);

	     if(MSK_FG0[ta]==1){				// Some pixels; trans
	       Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
	     }
	     else{						// all pixels; solid
	       Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
	     }
	   }

	   zz+=2;
	 }
	 zz+=8;
       }

     }
   }
   }

   draw_sprites(0);
}
static struct VIDEO_INFO video_armedf =
{
   DrawArmedF,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   gfxdecodeinfo,
   57
};
static struct VIDEO_INFO video_cclimbr2 =
{
   DrawArmedF,
   288,
   224,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   gfxdecodeinfo
};
static struct DIR_INFO dir_armedf[] =
{
   { "armed_formation", },
   { "armedf", },
   { NULL, },
};
GME( armedf, "Armed Formation", NICHIBUTSU, 1988, GAME_SHOOT,
	.long_name_jpn = "アームド・フォーメーション",
);
static struct DIR_INFO dir_cclimbr2[] =
{
   { "crazy_climber_2", },
   { "cclimbr2", },
   { NULL, },
};
GME( cclimbr2, "Crazy Climber 2", NICHIBUTSU, 1988, GAME_MISC);

