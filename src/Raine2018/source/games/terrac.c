#define DRV_DEF_SOUND nichi_ym3812_sound
/******************************************************************************/
/*                                                                            */
/*                    TERRA CRESTA (C) 1985 NICHIBUTSU                        */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "nichisnd.h"
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_terracre[] =
{
   {    "1a_4b.rom", 0x00004000, 0x76f17479, 0, 0, 0, },
   {    "1a_6b.rom", 0x00004000, 0xba4b5822, 0, 0, 0, },
   {    "1a_7b.rom", 0x00004000, 0xd0771bba, 0, 0, 0, },
   {    "1a_9b.rom", 0x00004000, 0x69227b56, 0, 0, 0, },
   {    "1a_4d.rom", 0x00004000, 0x8119f06e, 0, 0, 0, },
   {    "1a_6d.rom", 0x00004000, 0xca4852f6, 0, 0, 0, },
   {    "1a_7d.rom", 0x00004000, 0x029d59d9, 0, 0, 0, },
   {    "1a_9d.rom", 0x00004000, 0x5a672942, 0, 0, 0, },
   {   "1a_15f.rom", 0x00008000, 0x984a597f, 0, 0, 0, },
   {   "1a_17f.rom", 0x00008000, 0x30e297ff, 0, 0, 0, },
   {   "2a_16b.rom", 0x00002000, 0x591a3804, 0, 0, 0, },
   {   "2a_15b.rom", 0x00004000, 0x604c3b11, 0, 0, 0, },
   {   "2a_17b.rom", 0x00004000, 0xaffc898d, 0, 0, 0, },
   {   "2a_18b.rom", 0x00004000, 0x302dc0ab, 0, 0, 0, },
   {    "2a_6g.rom", 0x00004000, 0x4a9ec3e6, 0, 0, 0, },
   {    "2a_7g.rom", 0x00004000, 0x450749fc, 0, 0, 0, },
   {    "2a_6e.rom", 0x00004000, 0xbcf7740b, 0, 0, 0, },
   {    "2a_7e.rom", 0x00004000, 0xa70b565c, 0, 0, 0, },
   {  "tc2a_4e.bin", 0x00000100, 0x2c43991f, 0, 0, 0, },
   {  "tc2a_2g.bin", 0x00000100, 0x08609bad, 0, 0, 0, },
   { "tc1a_12f.bin", 0x00000100, 0x7ea63946, 0, 0, 0, },
   { "tc1a_11f.bin", 0x00000100, 0x566d323a, 0, 0, 0, },
   { "tc1a_10f.bin", 0x00000100, 0xce07c544, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_terracre[] =
{
   INP0( COIN1, 0x004005, 0x04 ),
   INP0( COIN2, 0x004005, 0x08 ),
   INP0( SERVICE, 0x004005, 0x20 ),

   INP0( P1_START, 0x004005, 0x01 ),
   INP0( P1_UP, 0x004000, 0x01 ),
   INP0( P1_DOWN, 0x004000, 0x02 ),
   INP0( P1_LEFT, 0x004000, 0x04 ),
   INP0( P1_RIGHT, 0x004000, 0x08 ),
   INP0( P1_B1, 0x004000, 0x10 ),
   INP0( P1_B2, 0x004000, 0x20 ),

   INP0( P2_START, 0x004005, 0x02 ),
   INP0( P2_UP, 0x004002, 0x01 ),
   INP0( P2_DOWN, 0x004002, 0x02 ),
   INP0( P2_LEFT, 0x004002, 0x04 ),
   INP0( P2_RIGHT, 0x004002, 0x08 ),
   INP0( P2_B1, 0x004002, 0x10 ),
   INP0( P2_B2, 0x004002, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_terra_cresta_0[] =
{
   { _("Lives"),                 0x03, 0x04 },
   { "3",                     0x03},
   { "4",                     0x02},
   { "5",                     0x01},
   { "6",                     0x00},
   { _("Extra Life at"),         0x04, 0x02 },
   { "20,000",                0x04, 0x00 },
   { "50,000"},
   { _("Second Life at"),        0x08, 0x02 },
   { "60,000",                0x08, 0x00 },
   { "90,000"},
   DSW_DEMO_SOUND( 0x10, 0x00),
   DSW_CABINET( 0x00,0x20 ),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_terra_cresta_1[] =
{
   { MSG_COIN1,               0x03, 0x04 },
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_1COIN_2PLAY,         0x02},
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_FREE_PLAY,             0x00},
   { MSG_COIN2,               0x0C, 0x04 },
   { MSG_1COIN_3PLAY,         0x0C},
   { MSG_1COIN_6PLAY,         0x08},
   { MSG_2COIN_3PLAY,         0x04},
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_DIFFICULTY,          0x10, 0x02 },
   { MSG_NORMAL,              0x10},
   { MSG_HARD,                0x00},
   DSW_SCREEN( 0x20, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_terracre[] =
{
   { 0x004006, 0xFF, dsw_data_terra_cresta_0 },
   { 0x004007, 0xFF, dsw_data_terra_cresta_1 },
   { 0,        0,    NULL,      },
};



static UINT8 *RAM_COLOUR;
static UINT8 *COLTAB;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *GFX_FG0;
static UINT8 *GFX_FG0_SOLID;

static void load_terracre(void)
{
   int ta,tb,tc,td;
   int red,green,blue;

   RAMSize=0x10000+0x10000;

   if(!(ROM=AllocateMem(0x20000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x40000+0x8000+0x100+0x8000))) return;

   GFX_BG0	=GFX+0x00000;
   GFX_SPR	=GFX+0x20000;
   GFX_FG0	=GFX+0x40000;

   COLTAB	=GFX+0x40000+0x8000;
   RAM_COLOUR	=GFX+0x40000+0x8000+0x100;

   if(!load_rom("1a_4d.rom", RAM+0x0000, 0x4000)) return;	// 68000 ROM
   if(!load_rom("1a_6d.rom", RAM+0x4000, 0x4000)) return;
   if(!load_rom("1a_7d.rom", RAM+0x8000, 0x4000)) return;
   if(!load_rom("1a_9d.rom", RAM+0xC000, 0x4000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("1a_4b.rom", RAM+0x0000, 0x4000)) return;	// 68000 ROM
   if(!load_rom("1a_6b.rom", RAM+0x4000, 0x4000)) return;
   if(!load_rom("1a_7b.rom", RAM+0x8000, 0x4000)) return;
   if(!load_rom("1a_9b.rom", RAM+0xC000, 0x4000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("2a_6e.rom", RAM+0x0000, 0x4000)) return;
   if(!load_rom("2a_7e.rom", RAM+0x4000, 0x4000)) return;
   if(!load_rom("2a_6g.rom", RAM+0x8000, 0x4000)) return;
   if(!load_rom("2a_7g.rom", RAM+0xC000, 0x4000)) return;
   tb=0;
   for(ta=0;ta<0x8000;ta++,tb+=4){
      GFX_SPR[tb+0]=(RAM[ta+0x0000]&15);
      GFX_SPR[tb+1]=(RAM[ta+0x0000]>>4);
      GFX_SPR[tb+2]=(RAM[ta+0x8000]&15);
      GFX_SPR[tb+3]=(RAM[ta+0x8000]>>4);
   }

   if(!load_rom("1a_15f.rom", RAM+0x0000, 0x8000)) return;
   if(!load_rom("1a_17f.rom", RAM+0x8000, 0x8000)) return;
   tb=0;
   for(ta=0;ta<0x10000;ta++,tb+=2){
      GFX_BG0[tb+0]=(RAM[ta]&15);
      GFX_BG0[tb+1]=(RAM[ta]>>4);
   }

   if(!load_rom("2a_16b.rom", RAM, 0x2000)) return;
   tb=0;
   for(ta=0;ta<0x2000;ta++,tb+=2){
      GFX_FG0[tb+0]=(RAM[ta]&15)^15;
      GFX_FG0[tb+1]=(RAM[ta]>>4)^15;
   }

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x0200);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x0200);
   GFX_FG0_SOLID = make_solid_mask_8x8  (GFX_FG0, 0x0100);

   if(!load_rom("tc1a_10f.bin", RAM+0x000, 0x100)) return;	// Red
   if(!load_rom("tc1a_11f.bin", RAM+0x100, 0x100)) return;	// Green
   if(!load_rom("tc1a_12f.bin", RAM+0x200, 0x100)) return;	// Blue
   if(!load_rom("tc2a_2g.bin",  RAM+0x300, 0x100)) return;	// Sprite Colour orders
   if(!load_rom("tc2a_4e.bin",  COLTAB, 0x100)) return;		// Sprite Colour banks

   tb=0x44000;

   // Palette BG0 (16x16 colours)
   // ---------------------------

   for(tc=0;tc<4;tc++){
   for(td=0;td<4;td++){
   for(ta=0;ta<8;ta++){
      GFX[tb++]=RAM[ta+0x0C0+(td<<4)]<<2;
      GFX[tb++]=RAM[ta+0x1C0+(td<<4)]<<2;
      GFX[tb++]=RAM[ta+0x2C0+(td<<4)]<<2;
   }
   for(ta=8;ta<16;ta++){
      GFX[tb++]=RAM[ta+0x0C0+(tc<<4)]<<2;
      GFX[tb++]=RAM[ta+0x1C0+(tc<<4)]<<2;
      GFX[tb++]=RAM[ta+0x2C0+(tc<<4)]<<2;
   }
   }
   }

   // Palette SPR (64x16 colours)
   // ---------------------------

   td=0x300;
   for(ta=0;ta<256;ta++){
   for(tc=0;tc<4;tc++){
       GFX[tb+0+((ta + tc *(256))*3)]=RAM[0x080+(tc<<4)+(RAM[td]&15)]<<2;
       GFX[tb+1+((ta + tc *(256))*3)]=RAM[0x180+(tc<<4)+(RAM[td]&15)]<<2;
       GFX[tb+2+((ta + tc *(256))*3)]=RAM[0x280+(tc<<4)+(RAM[td]&15)]<<2;
   }
   td++;
   }
   tb+=(64*48);

   // Palette FG0 (1x16 colours)
   // --------------------------

   for(ta=15;ta>=0;ta--){
      GFX[tb++]=RAM[ta+0x000]<<2;
      GFX[tb++]=RAM[ta+0x100]<<2;
      GFX[tb++]=RAM[ta+0x200]<<2;
   }

   tb=0;
   for(ta=0x44000;ta<0x48000;ta+=3,tb+=2){
   red   = (GFX[ta+0]>>2)&15;
   green = (GFX[ta+1]>>2)&15;
   blue  = (GFX[ta+2]>>2)&15;
   WriteWord(&RAM_COLOUR[tb],(red<<8)|(green<<4)|(blue));
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x10000;
   if(!load_rom("2a_15b.rom", Z80ROM+0x0000, 0x4000)) return;	// Z80 SOUND ROM
   if(!load_rom("2a_17b.rom", Z80ROM+0x4000, 0x4000)) return;	// Z80 SOUND ROM
   if(!load_rom("2a_18b.rom", Z80ROM+0x8000, 0x4000)) return;	// Z80 SOUND ROM

   AddNichibutsuYM3526(0x0077, 0x006F);

   AddNichiSample(0x014F, 0x0151, 1);
   AddNichiSample(0x0152, 0x0154, 1);

   AddNichiSample(0x1016, 0x2A72, 3);
   AddNichiSample(0x8040, 0x80FF, 2);
   AddNichiSample(0x8100, 0x9C00, 3);
   AddNichiSample(0x9C01, 0xADE1, 2);
   AddNichiSample(0xADE2, 0xBEA2, 2);

   /*-----------------------*/

   // 68000 Checksum Fix
   // ------------------

   WriteWord68k(&ROM[0x2064],0x4E71);		// 	nop

   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x002A2],0x4EF9);		// 	jmp	$1C000
   WriteLong68k(&ROM[0x002A4],0x0001C000);	//

   WriteLong68k(&ROM[0x1C000],0x46FC2000);	//	move.w	#$2000,SR

   WriteLong68k(&ROM[0x1C004],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x1C008],0x00AA0000);	//	(Speed Hack)

   WriteWord68k(&ROM[0x1C00C],0x6100-10);	//	bra.s	<loop>

   // Change Sound Comm Address (for speed)
   // -------------------------------------

   WriteLong68k(&ROM[0x002EA],0x00BB0000);

   // Clear RAM
   // ---------

   memset(RAM+0x00000,0x00,0x10000);

   // Clear INPUT/DSW
   // ---------------

   WriteLong(&RAM[0x4000],0xFFFFFFFF);
   WriteLong(&RAM[0x4004],0xFFFFFFFF);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_xxxx_rrrr_gggg_bbbb);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x20000);
   ByteSwap(RAM,0x10000);

   AddMemFetch(0x000000, 0x01FFFF, ROM+0x000000-0x000000);
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x01FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x020000, 0x02FFFF, NULL, RAM+0x000000);			// ALL RAM
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x01FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x020000, 0x02FFFF, NULL, RAM+0x000000);			// ALL RAM
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x020000, 0x02FFFF, NULL, RAM+0x000000);		// ALL RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x020000, 0x02FFFF, NULL, RAM+0x000000);		// ALL RAM
   AddWriteWord(0xBB0000, 0xBB0001, NichiSoundCommWrite68k, NULL);	// SOUND COMM
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_terracre(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);

   Nichibutsu3526_Frame();		// Z80 and YM3526
}

static void DrawTerraC(void)
{
   int x,y,ta;
   int zz,zzz,zzzz,x16,y16;
   UINT8 *map;

   ClearPaletteMap();

   // Clear/Draw BG0
   // --------------

   if((zzz=ReadWord(&RAM[0x228]))&0x2000){
      clear_game_screen(0);			// Game has no solid BG0
   }
   else{

   zzzz=2;					// X Offset (16-512)
   x16=15-15;					// X Offset (0-15)
   zzzz|=((zzz&0x3F0)>>4)<<6;			// Y Offset (16-1024)
   y16=(zzz&15);				// Y Offset (0-15)

   zzzz&=0x0FFF;

   for(x=(32-y16);x<(256+32);x+=16){
   zz=zzzz;
   for(y=(32-x16);y<(224+32);y+=16){

   ta=ReadWord(&RAM[0x2000+zz])&0x1FF;

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x2001+zz]&0x78)>>3,
         16,
         map
      );

      Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8],x,y,map);

   zz+=2;
   }
   zzzz+=0x40;
   zzzz=zzzz&0x0FFF;
   }

   }

   // OBJECT

   for(zz=0;zz<0x200;zz+=8){

   y = (224+32)-(ReadWord(&RAM[zz])&0xFF);

   x = (ReadWord(&RAM[zz+6])&0xFF)-0x80+((RAM[zz+4]&1)<<8);
   x = x + 32;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   ta=(((RAM[zz+4]&2)<<7)|((RAM[zz+2])));

      MAP_PALETTE_MAPPED_NEW(
         (RAM[zz+4]>>4)+((COLTAB[ta>>1]&3)<<4)+16,
         16,
         map
      );

      switch(RAM[zz+4]&0x0C){
      case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
      case 0x04: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
      case 0x08: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
      case 0x0C: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
      }

   }
   }

   // FG0

   zz=0x8000+4;

   MAP_PALETTE_MAPPED_NEW(
      80,
      16,
      map
   );

   for(x=32;x<256+32;x+=8,zz+=8){
   for(y=32;y<224+32;y+=8,zz+=2){
      if((ta=RAM[zz])!=0){
      Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
      }
   }
   }
}



/*

Sprite Table (8 bytes/sprite)
=============================

- Even bytes are unused

Byte | Bit(s) | Usage
-----+76543210+----------------------
  1  |xxxxxxxx| SpriteX (low)
  3  |xxxxxxxx| Sprite Number (low)
  5  |.......x| SpriteY (high)
  5  |......x.| Sprite Number (high)
  5  |.....x..| Sprite Flip Y
  5  |....x...| Sprite Flip X
  5  |xxxx....| Sprite Colour Bank
  7  |xxxxxxxx| SpriteY (low)

*/
static struct VIDEO_INFO video_terracre =
{
   DrawTerraC,
   256,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_terracre[] =
{
   { "terra_cresta", },
   { "terracre", },
   { NULL, },
};
GME( terracre, "Terra Cresta", NICHIBUTSU, 1985, GAME_SHOOT,
	.long_name_jpn = "テラクレスタ",
);

