/******************************************************************************/
/*                                                                            */
/*                            F3 DEMO / ANTIRIAD                              */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc003vcu.h"
#include "tc200obj.h"
#include "savegame.h"
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_f3demo[] =
{
   {     "code.bin", 0x0000194c, 0x08587aea, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};



static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_f3demo(void)
{
   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x100+0x100))) return;

   GFX_BG0 = GFX+0x000100;
   GFX_SPR = GFX+0x000000;
/*
   tb=0;
   if(!load_rom("D87-03.BIN", ROM, 0x1FBC00)) return;	// 16x16 SPRITES ($7EF0)
   for(ta=0;ta<0x1FBC00;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("D87-04.BIN", ROM, 0x1FBC00)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x1FBC00;ta++){
      GFX[tb++]=ROM[ta]&15;
      GFX[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("D87-05.BIN", ROM, 0x1FBC00)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x1FBC00;ta++){
      tc=ROM[ta];
      GFX[tb+3]|=((tc&0x40)>>6)<<4;
      GFX[tb+2]|=((tc&0x10)>>4)<<4;
      GFX[tb+1]|=((tc&0x04)>>2)<<4;
      GFX[tb+0]|=((tc&0x01)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("D87-06.BIN", ROM, 0x1FCD80)) return;	// 16x16 TILES ($7F36)
   for(ta=0;ta<0x1FCD80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("D87-17.BIN", ROM, 0x1FCD80)) return;	// 16x16 TILES
   for(ta=0;ta<0x1FCD80;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=0;
   if(!load_rom("D87-08.BIN", ROM, 0x1FCD80)) return;	// 16x16 TILES (MASK)
   for(ta=0;ta<0x1FCD80;ta+=2){
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
*/
   GFX_BG0_SOLID = MakeSolidTileMap16x16(GFX_BG0, 0x0001);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x0001);

   // Setup 68020 Memory Map
   // ----------------------

   AddF3MemoryMap(0x80000);

   RAM_BG0=RAM+0x33000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x31000;
   RAM_BG3=RAM+0x30000;

   RAM_SCR0=RAM+0x6A006;
   RAM_SCR1=RAM+0x6A004;
   RAM_SCR2=RAM+0x6A002;
   RAM_SCR3=RAM+0x6A000;

   SCR3_XOFS=0xF600;
   SCR2_XOFS=0xF700;
   SCR1_XOFS=0xF800;
   SCR0_XOFS=0xF900;

   SCR3_YOFS=0xFF80;
   SCR2_YOFS=0xF400;
   SCR1_YOFS=0xF400;
   SCR0_YOFS=0xFF80;

   memset(ROM,0xFF,0x80000);
   if(!load_rom("code.bin", ROM, 0x194c)) return;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x01000);

   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;


   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x40, 0x8000);


   init_f3_system_ioc(F3_IOC_2P_3BUTTON);

   init_m68k();
}

static void execute_f3demo(void)
{
   Execute68020(200000);

   Interrupt68020(3);
   //Execute68020(100000);
   //Interrupt68020(2);
   //Interrupt68020(5);

   IntF3System();
}

static void DrawF3Demo(void)
{
   ClearPaletteMap();

   clear_game_screen(0);		// Game has no solid BG0

   // Init tc0003vcu emulation
   // ------------------------

   tc0003vcu_layer_count = 0;

   if(RefreshBuffers){

   tc0003vcu.RAM	= RAM+0x20000;
// Mapper disabled
   tc0003vcu.bmp_x	= 64;
   tc0003vcu.bmp_y	= 64;
   tc0003vcu.bmp_w	= 320;
   tc0003vcu.bmp_h	= 224;
   tc0003vcu.scr_x	= 0;
   tc0003vcu.scr_y	= 0;

   }

   if(check_layer_enabled(f3_bg5_id)){
      f3video_render_fg0();
   }
}
static struct VIDEO_INFO video_f3demo =
{
   DrawF3Demo,
   320,
   224,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_f3demo[] =
{
   { "f3demo", },
   { NULL, },
};
GAME( f3demo, "F3 Demo by Antiriad", BOOTLEG, 1999, GAME_MISC,
	.input = f3_system_inputs,
	.video = &video_f3demo,
	.exec = execute_f3demo,
);

