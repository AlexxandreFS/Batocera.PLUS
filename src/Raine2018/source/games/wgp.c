#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*               WORLD GRAND PRIX (C) 1988 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines

/*

* This board uses following custom chips:
    TC0100SCN - OK
    TC0140SYT - OK
    TC0170ABT
    TC0220IOC - OK
    TC0240PBJ
    TC0250SCR
    TC0260DAR
    TC0330CHL

* This game has LAN interface board, it uses uPD72105C.

*/


static struct ROM_INFO rom_wgp[] =
{
   {       "c32-01.12", 0x00080000, 0xd27d7d93, 0, 0, 0, },
   {       "c32-02.11", 0x00080000, 0xc5721f3a, 0, 0, 0, },
   {       "c32-03.10", 0x00080000, 0x9ec3e134, 0, 0, 0, },
   {       "c32-04.9", 0x00080000, 0x473a19c9, 0, 0, 0, },
   {       "c32-05.71", 0x00080000, 0x3698d47a, 0, 0, 0, },
   {       "c32-06.70", 0x00080000, 0xf0267203, 0, 0, 0, },
   {       "c32-07.69", 0x00080000, 0x743d46bd, 0, 0, 0, },
   {       "c32-08.68", 0x00080000, 0xfaab63b0, 0, 0, 0, },
   {       "c32-09.16", 0x00080000, 0x96495f35, 0, 0, 0, },
   {       "c32-10.9", 0x00080000, 0xa44c66e9, 0, 0, 0, },
   {       "c32-11.8", 0x00080000, 0x2b326ff0, 0, 0, 0, },
   {       "c32-12.7", 0x00080000, 0xdf48a37b, 0, 0, 0, },
   {       "c32-24.34", 0x00010000, 0xe9adb447, 0, 0, 0, },
   {       "c32-25.12", 0x00020000, 0x0cc81e77, 0, 0, 0, },
   {       "c32-27.63", 0x00020000, 0xbe2397fb, 0, 0, 0, },
   {       "c32-28.64", 0x00020000, 0x38f3c7bf, 0, 0, 0, },
   {       "c32-29.13", 0x00020000, 0xfab47cf0, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_wgp[] =
{
   INP0( COIN1, 0x06220E, 0x04 ),
   INP0( COIN2, 0x06220E, 0x08 ),
   INP0( TILT, 0x06220E, 0x01 ),
   INP0( SERVICE, 0x06220E, 0x02 ),

   INP0( P1_START, 0x062204, 0x08 ),
   { KB_DEF_P1_B1,        "Shift Up",              0x062204, 0x02, BIT_ACTIVE_0 },
   { KB_DEF_P1_B2,        "Shift Down",            0x062204, 0x04, BIT_ACTIVE_0 },

   { KB_DEF_P1_B3,        "Start Lump (Lamp?)",    0x062206, 0x01, BIT_ACTIVE_1 },
   { KB_DEF_P1_B4,        "Brake Lump (Lamp?)",    0x062206, 0x02, BIT_ACTIVE_1 },

   END_INPUT
};

static struct DSW_DATA dsw_data_world_grand_prix_0[] =
{
   { _("Motor"),                 0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { MSG_DSWA_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};


static struct DSW_INFO dsw_wgp[] =
{
   { 0x062200, 0xFF, dsw_data_world_grand_prix_0 },
   { 0x062202, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_wgpj[] =
{
   {       "c32-01.12", 0x00080000, 0xd27d7d93, 0, 0, 0, },
   {       "c32-02.11", 0x00080000, 0xc5721f3a, 0, 0, 0, },
   {       "c32-03.10", 0x00080000, 0x9ec3e134, 0, 0, 0, },
   {       "c32-04.9", 0x00080000, 0x473a19c9, 0, 0, 0, },
   {       "c32-05.71", 0x00080000, 0x3698d47a, 0, 0, 0, },
   {       "c32-06.70", 0x00080000, 0xf0267203, 0, 0, 0, },
   {       "c32-07.69", 0x00080000, 0x743d46bd, 0, 0, 0, },
   {       "c32-08.68", 0x00080000, 0xfaab63b0, 0, 0, 0, },
   {       "c32-09.16", 0x00080000, 0x96495f35, 0, 0, 0, },
   {       "c32-10.9", 0x00080000, 0xa44c66e9, 0, 0, 0, },
   {       "c32-11.8", 0x00080000, 0x2b326ff0, 0, 0, 0, },
   {       "c32-12.7", 0x00080000, 0xdf48a37b, 0, 0, 0, },
   {       "c32-24.34", 0x00010000, 0xe9adb447, 0, 0, 0, },
   {   "c32-48.12", 0x00020000, 0x819cc134, 0, 0, 0, },
   {       "c32-27.63", 0x00020000, 0xbe2397fb, 0, 0, 0, },
   {       "c32-28.64", 0x00020000, 0x38f3c7bf, 0, 0, 0, },
   {   "c32-49.13", 0x00020000, 0x4a515f02, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


#define PIV_COUNT	(0x4000)
#define OBJ_B_COUNT	(0x4000)

static int obj_id,rod_id;
//static int romset;

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

//static UINT8 *GFX_OBJ_A;
//static UINT8 *GFX_OBJ_A_SOLID;

// 16x16 OBJECT TILES BANK B

static UINT8 *GFX_OBJ_B;
static UINT8 *GFX_OBJ_B_SOLID;

// 16x16 PIVOT TILES

static UINT8 *GFX_PIV;
static UINT8 *GFX_PIV_SOLID;

static UINT8 *zoom16_ofs;

static UINT8 *RAM_MAIN;
static UINT8 *RAM_MAIN_2;
static UINT8 *RAM_COMMON;
static UINT8 *RAM_VIDEO;
static UINT8 *RAM_VIDEO_2;
static UINT8 *RAM_OBJECT;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_SCROLL_2;
static UINT8 *RAM_INPUT;
static UINT8 *RAM_INPUT_2;
static UINT8 *RAM_INPUT_3;

static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_LINES;

/******************************************************************************/
/* WGP colour banking                                                         */
/******************************************************************************/

static void set_col_bank(UINT32 bank)
{
   bank &= 3;
   silly_wgp_colour_ram(RAM_COLOUR + (bank * 0x800));
   memset(bank_status, 0x00, 0x100 * 2);
}

static void load_actual(int romset)
{
   int ta,tb,tc;
   UINT8 *TMP;

   romset=0;

   if(!(GFX=AllocateMem(0x100000))) return;

   if(!(GFX_LINES=AllocateMem(0x200000))) return;

   if(!(GFX_PIV=AllocateMem(PIV_COUNT*0x100))) return;
   if(!(GFX_OBJ_B=AllocateMem(OBJ_B_COUNT*0x100))) return;

   if(!(OBJECT_MAP=AllocateMem(0x80000))) return;

   if(!(TMP=AllocateMem(0x80000))) return;

   if(!load_rom_index(4, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] = ((tc&0x000F)>> 0);
      GFX_OBJ_B[tb+1] = ((tc&0x00F0)>> 4);
      GFX_OBJ_B[tb+2] = ((tc&0x0F00)>> 8);
      GFX_OBJ_B[tb+3] = ((tc&0xF000)>>12);
      tb+=8;
   }
   if(!load_rom_index(5, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=4;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] = ((tc&0x000F)>> 0);
      GFX_OBJ_B[tb+1] = ((tc&0x00F0)>> 4);
      GFX_OBJ_B[tb+2] = ((tc&0x0F00)>> 8);
      GFX_OBJ_B[tb+3] = ((tc&0xF000)>>12);
      tb+=8;
   }
   if(!load_rom_index(6, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0x200000;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] = ((tc&0x000F)>> 0);
      GFX_OBJ_B[tb+1] = ((tc&0x00F0)>> 4);
      GFX_OBJ_B[tb+2] = ((tc&0x0F00)>> 8);
      GFX_OBJ_B[tb+3] = ((tc&0xF000)>>12);
      tb+=8;
   }
   if(!load_rom_index(7, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0x200004;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] = ((tc&0x000F)>> 0);
      GFX_OBJ_B[tb+1] = ((tc&0x00F0)>> 4);
      GFX_OBJ_B[tb+2] = ((tc&0x0F00)>> 8);
      GFX_OBJ_B[tb+3] = ((tc&0xF000)>>12);
      tb+=8;
   }

   if(!load_rom_index(0, TMP, PIV_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<PIV_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_PIV[tb+0] = ((tc&0x000F)>> 0);
      GFX_PIV[tb+1] = ((tc&0x00F0)>> 4);
      GFX_PIV[tb+2] = ((tc&0x0F00)>> 8);
      GFX_PIV[tb+3] = ((tc&0xF000)>>12);
      tb+=16;
   }
   if(!load_rom_index(1, TMP, PIV_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=4;
   for(ta=0;ta<PIV_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_PIV[tb+0] = ((tc&0x000F)>> 0);
      GFX_PIV[tb+1] = ((tc&0x00F0)>> 4);
      GFX_PIV[tb+2] = ((tc&0x0F00)>> 8);
      GFX_PIV[tb+3] = ((tc&0xF000)>>12);
      tb+=16;
   }
   if(!load_rom_index(2, TMP, PIV_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=8;
   for(ta=0;ta<PIV_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_PIV[tb+0] = ((tc&0x000F)>> 0);
      GFX_PIV[tb+1] = ((tc&0x00F0)>> 4);
      GFX_PIV[tb+2] = ((tc&0x0F00)>> 8);
      GFX_PIV[tb+3] = ((tc&0xF000)>>12);
      tb+=16;
   }
   if(!load_rom_index(3, TMP, PIV_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=12;
   for(ta=0;ta<PIV_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_PIV[tb+0] = ((tc&0x000F)>> 0);
      GFX_PIV[tb+1] = ((tc&0x00F0)>> 4);
      GFX_PIV[tb+2] = ((tc&0x0F00)>> 8);
      GFX_PIV[tb+3] = ((tc&0xF000)>>12);
      tb+=16;
   }

   if(!load_rom_index(8, TMP, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX[tb+0] = ((tc&0xF000)>>12);
      GFX[tb+1] = ((tc&0x0F00)>> 8);
      GFX[tb+2] = ((tc&0x00F0)>> 4);
      GFX[tb+3] = ((tc&0x000F)>> 0);
      tb+=4;
   }

   FreeMem(TMP);

   GFX_PIV_SOLID   = make_solid_mask_16x16(GFX_PIV,   PIV_COUNT);
   GFX_OBJ_B_SOLID = make_solid_mask_16x16(GFX_OBJ_B, OBJ_B_COUNT);
   GFX_BG0_SOLID   = make_solid_mask_8x8  (GFX,       0x4000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   if(!load_rom_index(13, RAM, 0x20000)) return;	// 68000 MAIN ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(16, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom_index(15, RAM, 0x20000)) return;	// 68000 SUB ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom_index(14, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   if(!load_rom_index(9, ROM+0x80000, 0x80000)) return; // 68000 MAIN DATA ROM

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x70000;
   if(!load_rom_index(12, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom_index(10, PCMROM+0x000000, 0x80000)) return;	// Delta-T
   if(!load_rom_index(11, PCMROM+0x080000, 0x80000)) return;	// Main
   YM2610SetBuffers(PCMROM+0x80000, PCMROM+0x00000, 0x80000, 0x80000);

   AddTaitoYM2610(0x020B, 0x01BA, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x70000);
   //memset(RAM+0x62200,0xFF,0x00200);

   RAM_MAIN    = RAM+0x00000;
   RAM_VIDEO   = RAM+0x10000;
   RAM_VIDEO_2 = RAM+0x20000;
   RAM_OBJECT  = RAM+0x40000;
   GFX_FG0     = RAM+0x50000;
   RAM_MAIN_2  = RAM+0x54000;
   RAM_COMMON  = RAM+0x5C000;
   RAM_COLOUR  = RAM+0x60000;
   RAM_SCROLL  = RAM+0x62000;
   RAM_SCROLL_2= RAM+0x62100;
   RAM_INPUT   = RAM+0x62200;
   RAM_INPUT_2 = RAM+0x62300;
   RAM_INPUT_3 = RAM+0x62400;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   // Fix COMMON RAM sync problems

   WriteWord68k(&ROM[0x02E0E],0x600C);

   // Speed Hack M68000A

   WriteLong68k(&ROM[0x0159A],0x067915F3);
   WriteLong68k(&ROM[0x0159E],0x00108DA0);
   WriteLong68k(&ROM[0x015A2],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x015A6],0x00AA0000);	//
   WriteWord68k(&ROM[0x015AA],0x6100-18);

   // Speed Hack M68000B

   WriteWord68k(&ROM[0x40942],0x5279);		//	inc random number
   WriteLong68k(&ROM[0x40944],0x00101682);
   WriteLong68k(&ROM[0x40948],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x4094C],0x00AA0000);	//
   WriteWord68k(&ROM[0x40950],0x6100-16);

   WriteLong68k(&ROM[0x4820C],0x4E714E71);	//	don't kill random number
   WriteWord68k(&ROM[0x48210],0x4E71);

   // ?

   WriteWord68k(&ROM[0x482D2],0x4E71);

   // LAN HEAD ERROR

   WriteWord68k(&ROM[0x504D8],0x6010);

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
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=240;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   init_16x16_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1z();

   obj_id = add_layer_info(gettext("Zooming Object") );
   rod_id = add_layer_info(gettext("Roadscroll")     );

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x70000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM *
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM_MAIN);			// 68000 RAM *
   AddReadByte(0x300000, 0x30FFFF, NULL, RAM_VIDEO);			// SCREEN RAM *
   AddReadByte(0x500000, 0x51FFFF, NULL, RAM_VIDEO_2);			// ?
   AddReadByte(0x140000, 0x143FFF, NULL, RAM_COMMON);			// COMMON RAM *
   AddReadByte(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// ?
   AddReadByte(0x180000, 0x18001F, tc0220ioc_rb, NULL);			// INPUT *
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM *
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM_MAIN);			// 68000 RAM *
   AddReadWord(0x300000, 0x30FFFF, NULL, RAM_VIDEO);			// SCREEN RAM *
   AddReadWord(0x500000, 0x51FFFF, NULL, RAM_VIDEO_2);			// ?
   AddReadWord(0x140000, 0x143FFF, NULL, RAM_COMMON);			// COMMON RAM *
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// ?
   AddReadWord(0x700000, 0x701FFF, NULL, RAM_COLOUR);			// COLOR RAM *
   AddReadWord(0x200000, 0x20000F, NULL, RAM_INPUT_2);			// ?
   AddReadWord(0x180000, 0x18001F, tc0220ioc_rw, NULL);			// INPUT *
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM_MAIN);			// 68000 RAM *
   AddWriteByte(0x306000, 0x306FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM *
   AddWriteByte(0x300000, 0x30FFFF, NULL, RAM_VIDEO);			// SCREEN RAM *
   AddWriteByte(0x500000, 0x51FFFF, NULL, RAM_VIDEO_2);			// ?
   AddWriteByte(0x140000, 0x143FFF, NULL, RAM_COMMON);			// COMMON RAM *
   AddWriteByte(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// ?
   AddWriteByte(0x180000, 0x18001F, tc0220ioc_wb, NULL);		// INPUT *
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM_MAIN);			// 68000 RAM *
   AddWriteWord(0x306000, 0x306FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM *
   AddWriteWord(0x300000, 0x30FFFF, NULL, RAM_VIDEO);			// SCREEN RAM *
   AddWriteWord(0x500000, 0x51FFFF, NULL, RAM_VIDEO_2);			// ?
   AddWriteWord(0x140000, 0x143FFF, NULL, RAM_COMMON);			// COMMON RAM *
   AddWriteWord(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// ?
   AddWriteWord(0x700000, 0x701FFF, NULL, RAM_COLOUR);			// COLOR RAM *
   AddWriteWord(0x320000, 0x32000F, NULL, RAM_SCROLL);			// SCROLL RAM *
   AddWriteWord(0x520000, 0x52001F, NULL, RAM_SCROLL_2);		// ?
   AddWriteWord(0x180000, 0x18001F, tc0220ioc_ww, NULL);		// INPUT *
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM+0x040000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x040000);		// 68000 ROM
   AddReadByteMC68000B(0x100000, 0x107FFF, NULL, RAM_MAIN_2);		// MAIN RAM
   AddReadByteMC68000B(0x140000, 0x143FFF, NULL, RAM_COMMON);		// COMMON RAM *
   AddReadByteMC68000B(0x200000, 0x200003, tc0140syt_read_main_68k, NULL); // SOUND COMM *
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);	// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x040000);		// 68000 ROM
   AddReadWordMC68000B(0x100000, 0x107FFF, NULL, RAM_MAIN_2);		// MAIN RAM
   AddReadWordMC68000B(0x140000, 0x143FFF, NULL, RAM_COMMON);		// COMMON RAM *
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);	// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x100000, 0x107FFF, NULL, RAM_MAIN_2);		// MAIN RAM
   AddWriteByteMC68000B(0x140000, 0x143FFF, NULL, RAM_COMMON);		// COMMON RAM *
   AddWriteByteMC68000B(0x200000, 0x200003, tc0140syt_write_main_68k, NULL); // SOUND COMM *
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);	// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x100000, 0x107FFF, NULL, RAM_MAIN_2);		// MAIN RAM
   AddWriteWordMC68000B(0x140000, 0x143FFF, NULL, RAM_COMMON);		// COMMON RAM *
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);	// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void load_wgp(void)
{
   load_actual(0);
}

static void load_wgpj(void)
{
   load_actual(1);
}

static void ClearWorldGrandPrix(void)
{
   RemoveTaitoYM2610();
}

static void execute_wgp(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));		// M68000 12MHz (60fps)
      print_debug("PC0:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 4);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 6);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(12,60));		// M68000 12MHz (60fps)
      print_debug("PC1:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 4);
   cpu_interrupt(CPU_68K_1, 6);

   Taito2610_Frame();				// Z80 and YM2610
}


static void render_z_system_sprites(void)
{
   int x,y,ta,tb,zz;
   int zx,zy,rx,ry,xx,zzx,zzy;
   UINT8 *map,*SPR_MAP;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;

   // OBJECT Z-SYSTEM
   // ---------------

   for(zz=0x4C000;zz<0x4DC00;zz+=16){

      zx=0x7F;
      zy=0x7F;
      if((zx!=0)&&(zy!=0)){

         ta = (ReadWord(&RAM[zz+4]))&0x3FF;
         if(ta!=0){

            x=(32+ReadWord(&RAM[zz+0]))&0x1FF;

            y=(32+ReadWord(&RAM[zz+2]))&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+6])>>7)&0x3F,
               16,
               map
            );

            if((zx&0x40)!=0){					// [128x128]

            zoom_dat_x = zoom16_ofs+(zx<<3);
            zoom_dat_y = zoom16_ofs+(zy<<3);

            SPR_MAP = RAM + 0x40000 + (ta<<8);

            switch(RAM[zz+5]&0x00){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=4;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=32;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=16;
            x=xx;
            }

            break;
            }


            }
            else{

            if((zy&0x20)!=0){					// [64x128]

            zoom_dat_x = zoom16_ofs+(((zx<<1)|1)<<3);
            zoom_dat_y = zoom16_ofs+(zy<<3);

            SPR_MAP = RAM + 0x20000 + (ta<<7);

            switch(RAM[zz+5]&0xC0){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=8;
            x=xx;
            }

            break;
            }


            }
            else{						// [32x128]

            zoom_dat_x = zoom16_ofs+(((zx<<2)|3)<<3);
            zoom_dat_y = zoom16_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + 0x60000 + (ta<<5);

            switch(RAM[zz+5]&0xC0){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=4;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=4;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=4;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=4;
            x=xx;
            }

            break;
            }


            }


            }

         }
      }
   }
}

static void DrawWorldGrandPrix(void)
{
   int x,y,ta,zz,zzz,zzzz,x16,y16;
   //int zy,tb,tb2;
   UINT8 *map;
   //UINT32 mask_count;
   //UINT32 mask_pos[32];
   //UINT32 mask_pos_y[32];

   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   set_col_bank(2);
   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   set_col_bank(3);
   render_tc0100scn_layer_mapped(0,1,1);

   // OBJECT
   // ------

   set_col_bank(1);
   if(check_layer_enabled(obj_id))
      render_z_system_sprites();

   // PIV
   // ---

   //if(check_layer_enabled(f3_bg1_id)){
   set_col_bank(2);
   MAKE_SCROLL_1024x1024_2_16(
      ReadWord(&RAM_SCROLL_2[0x06]),
      ReadWord(&RAM_SCROLL_2[0x00])
   );

   START_SCROLL_1024x1024_2_16(32,32,320,240);

      ta=ReadWord(&RAM[zz+0x22000])&0x3FFF;
      if(GFX_PIV_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord(&RAM[zz+0x32000])&0x3F,
            16,
            map
         );

         if(GFX_PIV_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM[zz+0x32001]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_PIV[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_PIV[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM[zz+0x32001]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_PIV[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_PIV[ta<<8],x,y,map); break;
            }
         }

      }

   END_SCROLL_1024x1024_2_16();

   //}

   // PIV
   // ---

   //if(check_layer_enabled(f3_bg1_id)){
   set_col_bank(2);
   MAKE_SCROLL_1024x1024_2_16(
      ReadWord(&RAM_SCROLL_2[0x08]),
      ReadWord(&RAM_SCROLL_2[0x02])
   );

   START_SCROLL_1024x1024_2_16(32,32,320,240);

      ta=ReadWord(&RAM[zz+0x24000])&0x3FFF;
      if(GFX_PIV_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord(&RAM[zz+0x34000])&0x3F,
            16,
            map
         );

         if(GFX_PIV_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM[zz+0x34001]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_PIV[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_PIV[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM[zz+0x34001]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_PIV[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_PIV[ta<<8],x,y,map); break;
            }
         }

      }

   END_SCROLL_1024x1024_2_16();

   //}

   // PIV
   // ---

   //if(check_layer_enabled(f3_bg1_id)){
   set_col_bank(2);
   MAKE_SCROLL_1024x1024_2_16(
      ReadWord(&RAM_SCROLL_2[0x0A]),
      ReadWord(&RAM_SCROLL_2[0x04])
   );

   START_SCROLL_1024x1024_2_16(32,32,320,240);

      ta=ReadWord(&RAM[zz+0x26000])&0x3FFF;
      if(GFX_PIV_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord(&RAM[zz+0x36000])&0x3F,
            16,
            map
         );

         if(GFX_PIV_SOLID[ta]==1){		// Some pixels; trans
            switch(RAM[zz+0x36001]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_PIV[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_PIV[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM[zz+0x36001]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&GFX_PIV[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_PIV[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_PIV[ta<<8],x,y,map); break;
            }
         }

      }

   END_SCROLL_1024x1024_2_16();

   //}

   // FG0
   // ---

   set_col_bank(1);
   render_tc0100scn_layer_mapped(0,2,1);

   set_col_bank(0);
}


static struct VIDEO_INFO video_wgp =
{
   DrawWorldGrandPrix,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_wgp[] =
{
   { "world_grand_prix", },
   { "wgp", },
   { NULL, },
};
GME( wgp, "World Grand Prix", TAITO, 1989, GAME_RACE | GAME_NOT_WORKING,
	.clear = ClearWorldGrandPrix,
	.board = "C32",
);
static struct DIR_INFO dir_wgpj[] =
{
   { "world_grand_prix_japanese", },
   { "wgpj", },
   { ROMOF("wgp"), },
   { CLONEOF("wgp"), },
   { NULL, },
};
GAME(wgpj, "World Grand Prix (Japan)", TAITO, 1989, GAME_RACE | GAME_NOT_WORKING,
	.input = input_wgp,
	.dsw = dsw_wgp,
	.clear = ClearWorldGrandPrix,
	.video = &video_wgp,
	.exec = execute_wgp,
	.board = "C32",
);

