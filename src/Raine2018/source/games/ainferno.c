#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                   AIR INFERNO (C) 1990 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc004vcu.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines


static struct ROM_INFO rom_ainferno[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
                  "c45-22",  0x50300926,       "c45-20",  0x39b189d9),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
                  "c45-21",  0x1b687241,       "c45-28",  0xc7cd2567),
   {       "c45-01", 0x00020000, 0x6c59a808, 0, 0, 0, },
   {       "c45-02", 0x00020000, 0x6d081044, 0, 0, 0, },
   {       "c45-03", 0x00020000, 0x0e1e5b5f, 0, 0, 0, },
   {       "c45-04", 0x00020000, 0x2fc0a88e, 0, 0, 0, },
   {       "c45-05", 0x00020000, 0x052997b2, 0, 0, 0, },
   {       "c45-06", 0x00020000, 0x6a7976d4, 0, 0, 0, },
   {       "c45-25", 0x00002000, 0xc0d39f95, 0, 0, 0, },
   {       "c45-24", 0x00002000, 0x1013d937, 0, 0, 0, },
   {       "c45-23", 0x00010000, 0xd0750c78, 0, 0, 0, },
   {       "c45-18", 0x00020000, 0xba7ecf3b, 0, 0, 0, },
   {       "c45-16", 0x00020000, 0xc6eb93b0, 0, 0, 0, },
   {       "c45-15", 0x00020000, 0xd4610698, 0, 0, 0, },
   {       "c45-14", 0x00020000, 0x481b6f29, 0, 0, 0, },
   {       "c45-13", 0x00020000, 0x69b82af6, 0, 0, 0, },
   {       "c45-12", 0x00020000, 0x4ae305b8, 0, 0, 0, },
   {       "c45-11", 0x00020000, 0xd9b4b77c, 0, 0, 0, },
   {       "c45-17", 0x00020000, 0x0dbee000, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ainferno[] =
{
   INP1( COIN1, 0x055204, 0x04 ),
   INP1( COIN2, 0x055204, 0x08 ),
   INP0( TILT, 0x055204, 0x20 ),
   INP0( SERVICE, 0x055204, 0x10 ),

   INP0( P1_START, 0x055204, 0x40 ),
   INP0( P1_B1, 0x055206, 0x08 ),
   { KB_DEF_P1_B2,        "Lever",                 0x055206, 0x01, BIT_ACTIVE_0 },
   { KB_DEF_P1_B3,        "Handle X",              0x055206, 0x02, BIT_ACTIVE_0 },
   { KB_DEF_P1_B4,        "Handle Y",              0x055206, 0x04, BIT_ACTIVE_0 },
   { KB_DEF_P1_B5,        "Pedal L",               0x055206, 0x20, BIT_ACTIVE_0 },
   { KB_DEF_P1_B6,        "Pedal R",               0x055206, 0x10, BIT_ACTIVE_0 },

   END_INPUT
};

static struct DSW_DATA dsw_data_air_inferno_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
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

static struct DSW_INFO dsw_ainferno[] =
{
   { 0x055200, 0xFF, dsw_data_air_inferno_0 },
   { 0x055202, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_air_inferno_0[] =
{
   { "Taito Japan (Notice)",  0x00 },
   { "Taito America",         0x01 },
   { "Taito Japan",           0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_ainferno[] =
{
   { 0x03FFFF, 0x00, romsw_data_air_inferno_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_FG0;

static int BadReadWord(UINT32 address)
{
       print_debug("Rw(%06x) [%06x]\n",address,s68000context.pc);
   return(0xFFFF);
}

static void BadWriteByte(UINT32 address, UINT8 data)
{
#ifdef RAINE_DEBUG
      if(address!=0xA00200) print_debug("Wb(%06x,%02x) [%06x]\n",address,data,s68000context.pc);
#endif
}

static void BadWriteWord(UINT32 address, UINT16 data)
{
      print_debug("Ww(%06x,%04x) [%06x]\n",address,data,s68000context.pc);
}

static void load_ainferno(void)
{
   int ta,tb,tc;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x200000))) return;

   GFX_BG0 = GFX+0x000000;

   if(!load_rom("c45-11", RAM, 0x20000)) return;	// GFX
   tb=0;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-15", RAM, 0x20000)) return;	// GFX
   tb=2;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-12", RAM, 0x20000)) return;	// GFX
   tb=4;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-16", RAM, 0x20000)) return;	// GFX
   tb=6;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-13", RAM, 0x20000)) return;	// GFX
   tb=8;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-17", RAM, 0x20000)) return;	// GFX
   tb=10;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-14", RAM, 0x20000)) return;	// GFX
   tb=12;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("c45-18", RAM, 0x20000)) return;	// GFX
   tb=14;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }

   RAMSize=0x60000+0x10000;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   if(!load_rom("c45-23", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0xC0000))) return;
   memset(PCMROM,0x80,0xC0000);
   if(!load_rom("c45-01",PCMROM+0x00000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("c45-02",PCMROM+0x20000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("c45-03",PCMROM+0x40000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("c45-04",PCMROM+0x60000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("c45-05",PCMROM+0x80000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("c45-06",PCMROM+0xA0000,0x20000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x0C0000, 0x0C0000);

   AddTaitoYM2610(0x023A, 0x01BA, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x60000);
   memset(RAM+0x55000,0xFF,0x00400);

   GFX_FG0   = RAM+0x56000;
   RAM_VIDEO = RAM+0x10000;
   RAM_COLOUR= RAM+0x39000;
   RAM_INPUT = RAM+0x55200;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x8000);

   set_colour_mapper(&col_map_xxbb_bbxg_gggx_rrrr);

   // Fix Freeze
   // ----------

   WriteByte68k(&ROM[0x07D6],0x60);
   WriteWord68k(&ROM[0x56D8],0x4E71);

   // Fix SOUND CPU ERROR
   // -------------------

   WriteByte68k(&ROM[0x206E],0x60);
   WriteByte68k(&ROM[0x20EE],0x60);

   // Fix TMS320C25 ERROR
   // -------------------

   WriteByte68k(&ROM[0x56A0],0x60);
/*
   // Fix DMA ERROR
   // -------------

   WriteByte68k(&ROM[0x09C4],0x60);

   // Fix SOUND CPU ERROR
   // -------------------

   WriteByte68k(&ROM[0x0B22],0x60);
   WriteByte68k(&ROM[0xE8A6],0x60);
   WriteByte68k(&ROM[0xE93E],0x60);

   // 68000 Speed hack
   // ----------------

   //WriteLong68k(&ROM[0x072E],0x13FC0000);	// move.b #$00,$AA0000
   //WriteLong68k(&ROM[0x0732],0x00AA0000);	//

   // Fix ROM Checksum
   // ----------------

   WriteLong68k(&ROM[0x04A0],0x4E714E71);		// nop; nop
   WriteLong68k(&ROM[0x04C2],0x4E714E71);		// nop; nop
*/

   // Init tc0004vcu emulation
   // ------------------------

   tc0004vcu.RAM	= RAM_VIDEO;
   tc0004vcu.GFX_BG0	= GFX_BG0;
   tc0004vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0004vcu.GFX_FG0	= GFX_FG0;
   tc0004vcu.tile_mask	= 0x1FFF;
   tc0004vcu.bmp_x	= 64;
   tc0004vcu.bmp_y	= 64;
   tc0004vcu.bmp_w	= 512;
   tc0004vcu.bmp_h	= 400;
   tc0004vcu.scr_x	= 0;
   tc0004vcu.scr_y	= 48;

   tc0004vcu_init();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x60000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x820FFF, NULL, RAM_VIDEO);			// VIDEO RAM
   AddReadByte(0x180000, 0x18BFFF, NULL, RAM+0x031000);			// ??? RAM/COLOUR RAM
   AddReadByte(0x908000, 0x91FFFF, NULL, RAM+0x03D000);			// ??? RAM
   AddReadByte(0xA00000, 0xA003FF, NULL, RAM+0x055000);			// I/O RAM
   AddReadByte(0xA80000, 0xA80003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x800000, 0x820FFF, NULL, RAM_VIDEO);			// VIDEO RAM
   AddReadWord(0x180000, 0x18BFFF, NULL, RAM+0x031000);			// ??? RAM/COLOUR RAM
   AddReadWord(0x908000, 0x91FFFF, NULL, RAM+0x03D000);			// ??? RAM
   AddReadWord(0xA00000, 0xA003FF, NULL, RAM+0x055000);			// I/O RAM
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x800000, 0x820FFF, NULL, RAM_VIDEO);			// VIDEO RAM
   AddWriteByte(0x180000, 0x18BFFF, NULL, RAM+0x031000);		// ??? RAM/COLOUR RAM
   AddWriteByte(0x908000, 0x91FFFF, NULL, RAM+0x03D000);		// ??? RAM
   AddWriteByte(0xA80000, 0xA80003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, BadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x800000, 0x820FFF, NULL, RAM_VIDEO);			// VIDEO RAM
   AddWriteWord(0x180000, 0x18BFFF, NULL, RAM+0x031000);		// ??? RAM/COLOUR RAM
   AddWriteWord(0x908000, 0x91FFFF, NULL, RAM+0x03D000);		// ??? RAM
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_ainferno(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);

   Taito2610_Frame();			// Z80 and YM2610
}

static void draw_air_inferno(void)
{
   ClearPaletteMap();

   // Init tc0180vcu emulation
   // ------------------------

   tc0004vcu_layer_count = 0;

   // BG0
   // ---

   tc0004vcu_render_bg0();

   // BG1
   // ---

   tc0004vcu_render_bg1();

   // OBJECT
   // ------

   tc0004vcu_render_obj();

   // FG0
   // ---

   //tc0004vcu_render_fg0();
}

static struct VIDEO_INFO video_ainferno =
{
   draw_air_inferno,
   512,
   400,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_ainferno[] =
{
   { "air_inferno", },
   { "ainferno", },
   { NULL, },
};
GME( ainferno, "Air Inferno", TAITO, 1990, GAME_MISC | GAME_NOT_WORKING,
	.romsw = romsw_ainferno,
	.board = "C45",
);

