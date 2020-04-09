/******************************************************************************/
/*                                                                            */
/*                  CHACK'N POP (C) 1983 TAITO CORPORATION                    */
/*                                                                            */
/******************************************************************************/

/*

Todo:

- Sound Chips should be AY-8910 (is YM2203 100% compatible?)
- Colours (proms? ram?)
- BG0 Tile banking & pixel layers
- MCU!!

*/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "blit.h"


static struct ROM_INFO rom_chaknpop[] =
{
   {    "a04-01.28", 0x00002000, 0x386fe1c8, 0, 0, 0, },
   {    "a04-02.27", 0x00002000, 0x5562a6a7, 0, 0, 0, },
   {    "a04-03.26", 0x00002000, 0x3e2f0a9c, 0, 0, 0, },
   {    "a04-04.25", 0x00002000, 0x5209c7d4, 0, 0, 0, },
   {     "a04-05.3", 0x00002000, 0x8720e024, 0, 0, 0, },
   {    "a04-07.15", 0x00002000, 0xae687c18, 0, 0, 0, },
   {    "a04-08.14", 0x00002000, 0x5575a021, 0, 0, 0, },
   {    "a04-09.98", 0x00002000, 0x757a723a, 0, 0, 0, },
   {    "a04-10.97", 0x00002000, 0x3e3fd608, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_chaknpop[] =
{
   INP0( COIN1, 0x010000, 0x40 ),
   INP0( TILT, 0x010000, 0x80 ),

   INP0( P1_START, 0x010000, 0x10 ),
   INP0( P1_UP, 0x010001, 0x08 ),
   INP0( P1_DOWN, 0x010001, 0x04 ),
   INP0( P1_LEFT, 0x010001, 0x01 ),
   INP0( P1_RIGHT, 0x010001, 0x02 ),
   INP0( P1_B1, 0x010001, 0x10 ),
   INP0( P1_B2, 0x010001, 0x20 ),

   INP0( P2_START, 0x010000, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_chack_n_pop_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
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

static struct DSW_INFO dsw_chaknpop[] =
{
   { 0x010002, 0xFF, dsw_data_chack_n_pop_0 },
   { 0,        0,    NULL,      },
};


static struct YM2203interface ym2203_interface =
{
  2,
  4000000,
  { 0x00ff2040, 0x00ff2040 },
  { 0, 0 },
  { 0, 0 },
  { NULL, NULL },
  { NULL, NULL },
  { NULL, NULL }
};

static struct SOUND_INFO sound_chaknpop[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { 0,             NULL,                 },
};


static UINT16 ReadIO(UINT16 offset)
{
   switch(offset&15){
   case 0x04:
   case 0x05:
      return(YM2203AReadZ80(offset));
   case 0x06:
   case 0x07:
      return(YM2203BReadZ80(offset));
   case 0x08:
      return(get_dsw(0));
   break;
   case 0x09:
      return(RAM[0x10001]);
   break;
   case 0x0A:
      return(RAM[0x10000]);
   break;
   default:
      print_debug("RB: %04x\n",offset);
      return(0xFF);
   break;
   }
}

static void WriteIO(UINT16 offset, UINT8 data)
{
   switch(offset&15){
   case 0x04:
   case 0x05:
      YM2203AWriteZ80(offset,data);
   case 0x06:
   case 0x07:
      YM2203BWriteZ80(offset,data);
   break;
   default:
      print_debug("WB: %04x,%02x\n",offset,data);
   break;
   }
}

static void load_chaknpop(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

//컴컴 Set up ROM/RAM 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴//

   RAMSize=0x10000+4;

   if(!(ROM=AllocateMem(0x10000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return; /* +4 to allocate DSW/Inputs storage space */

   if(!load_rom("a04-01.28",ROM+0x0000,0x2000)) return;      // Z80 CODE ROM
   if(!load_rom("a04-02.27",ROM+0x2000,0x2000)) return;      // Z80 CODE ROM
   if(!load_rom("a04-03.26",ROM+0x4000,0x2000)) return;      // Z80 CODE ROM
   if(!load_rom("a04-04.25",ROM+0x6000,0x2000)) return;      // Z80 CODE ROM
   memset(ROM+0x8000,0x00,0x2000);
   if(!load_rom("a04-05.3", ROM+0xA000,0x2000)) return;      // Z80 CODE ROM
   memset(ROM+0xC000,0x00,0x2000);
   memset(ROM+0xE000,0x00,0x2000);

/*
   // Skip Idle Z80
   // -------------

   ROM[0x00B3]=0xD3;  // OUTA (AAh)
   ROM[0x00B4]=0xAA;  //

   // Fix ROM Checksum
   // ----------------

   ROM[0x0396]=0x00;  // NOP
   ROM[0x0397]=0x00;  // NOP
   ROM[0x0398]=0x00;  // NOP
*/
   // Fix Some Hardware Test
   // ----------------------

   ROM[0x06C8]=0x00;
   ROM[0x06C9]=0x00;

   ROM[0x06DB]=0x18;

   memcpy(RAM, ROM, 0x10000);
   WriteLong(RAM+0x10000,0xFFFFFFFF);

   AddZ80AROMBase(RAM, 0x38, 0x66);

   AddZ80AReadByte(0x0000, 0x87FF, NULL,                  NULL);        // Z80 ROM; Z80 RAM
   AddZ80AReadByte(0x8800, 0x880F, ReadIO,                NULL);        // I/O
   AddZ80AReadByte(0x9000, 0x93FF, NULL,                  NULL);        // BG0 RAM
   AddZ80AReadByte(0x9800, 0x98FF, NULL,                  NULL);        // OBJ RAM
   AddZ80AReadByte(0xA000, 0xFFFF, NULL,                  NULL);        // Z80 ROM; PIXEL RAM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,         NULL);        // <bad writes>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x87FF, NULL,                 NULL);        // Z80 RAM
   AddZ80AWriteByte(0x8800, 0x880F, WriteIO,              NULL);        // I/O
   AddZ80AWriteByte(0x9000, 0x93FF, NULL,                 NULL);        // BG0 RAM
   AddZ80AWriteByte(0x9800, 0x98FF, NULL,                 NULL);        // OBJ RAM
   AddZ80AWriteByte(0xC000, 0xFFFF, NULL,                 NULL);        // PIXEL RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,       NULL);        // <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80,                NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

//컴컴 Set up graphics 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�//

   if(!(GFX=AllocateMem(0x20000))) return;
   if(!(TMP=AllocateMem(0x2000))) return;

   if(!load_rom("a04-09.98", TMP, 0x2000)) return;            // BG0 TILES
   tb=0;
   for(ta=0;ta<0x2000;ta++,tb+=8){
      tc=TMP[ta];
      GFX[tb+0] = (((tc&0x80)>>7)<<0);
      GFX[tb+1] = (((tc&0x40)>>6)<<0);
      GFX[tb+2] = (((tc&0x20)>>5)<<0);
      GFX[tb+3] = (((tc&0x10)>>4)<<0);
      GFX[tb+4] = (((tc&0x08)>>3)<<0);
      GFX[tb+5] = (((tc&0x04)>>2)<<0);
      GFX[tb+6] = (((tc&0x02)>>1)<<0);
      GFX[tb+7] = (((tc&0x01)>>0)<<0);
   }

   if(!load_rom("a04-10.97", TMP, 0x2000)) return;            // BG0 TILES
   tb=0;
   for(ta=0;ta<0x2000;ta++,tb+=8){
      tc=TMP[ta];
      GFX[tb+0] |= (((tc&0x80)>>7)<<1);
      GFX[tb+1] |= (((tc&0x40)>>6)<<1);
      GFX[tb+2] |= (((tc&0x20)>>5)<<1);
      GFX[tb+3] |= (((tc&0x10)>>4)<<1);
      GFX[tb+4] |= (((tc&0x08)>>3)<<1);
      GFX[tb+5] |= (((tc&0x04)>>2)<<1);
      GFX[tb+6] |= (((tc&0x02)>>1)<<1);
      GFX[tb+7] |= (((tc&0x01)>>0)<<1);
   }

   if(!load_rom("a04-07.15", TMP, 0x2000)) return;            // SPR TILES
   tb=0x10000;
   for(ta=0;ta<0x2000;ta++){
      tc=TMP[ta];
      GFX[tb+0] = (((tc&0x80)>>7)<<0);
      GFX[tb+1] = (((tc&0x40)>>6)<<0);
      GFX[tb+2] = (((tc&0x20)>>5)<<0);
      GFX[tb+3] = (((tc&0x10)>>4)<<0);
      GFX[tb+4] = (((tc&0x08)>>3)<<0);
      GFX[tb+5] = (((tc&0x04)>>2)<<0);
      GFX[tb+6] = (((tc&0x02)>>1)<<0);
      GFX[tb+7] = (((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x8;}}
   }

   if(!load_rom("a04-08.14", TMP, 0x2000)) return;            // SPR TILES
   tb=0x10000;
   for(ta=0;ta<0x2000;ta++){
      tc=TMP[ta];
      GFX[tb+0] |= (((tc&0x80)>>7)<<1);
      GFX[tb+1] |= (((tc&0x40)>>6)<<1);
      GFX[tb+2] |= (((tc&0x20)>>5)<<1);
      GFX[tb+3] |= (((tc&0x10)>>4)<<1);
      GFX[tb+4] |= (((tc&0x08)>>3)<<1);
      GFX[tb+5] |= (((tc&0x04)>>2)<<1);
      GFX[tb+6] |= (((tc&0x02)>>1)<<1);
      GFX[tb+7] |= (((tc&0x01)>>0)<<1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x8;}}
   }

   FreeMem(TMP);

}

static void execute_chaknpop(void)
{
   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Main Z80
      print_debug("Z80PC0:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_0, 0x38);
}

static void DrawChacknpop(void)
{
   int x,y,zz,z,z2;
   UINT8 *BIT;

   zz=0;
   for(y=32;y<256+32;y+=8){
       for(x=32;x<256+32;x+=8,zz++){
	   z=RAM[zz+0x9000];
	   Draw8x8_8(&GFX[z<<6],x,y,0);
       }
   }

   zz=(32*240)-1;
   for(y=0;y<224;y++){
   BIT=GameViewBitmap->line[y];
   for(x=0;x<256;x+=8,zz--){
      z=RAM[zz+0xC000];
      z2=RAM[zz+0xE000];
      if((z&0x80)!=(z2&0x80))BIT[x+0]=3;
      if((z&0x40)!=(z2&0x40))BIT[x+1]=3;
      if((z&0x20)!=(z2&0x20))BIT[x+2]=3;
      if((z&0x10)!=(z2&0x10))BIT[x+3]=3;
      if((z&0x08)!=(z2&0x08))BIT[x+4]=3;
      if((z&0x04)!=(z2&0x04))BIT[x+5]=3;
      if((z&0x02)!=(z2&0x02))BIT[x+6]=3;
      if((z&0x01)!=(z2&0x01))BIT[x+7]=3;
   }
   }

   for(zz=0;zz<0x100;zz+=4){
      x=RAM[zz+0x9803]+32;
      y=(256+17)-RAM[zz+0x9800];
      z=RAM[zz+0x9801]&0x3F;
      z |= (((RAM[zz+0x9802]>>3)&3)<<6);
      switch(RAM[zz+0x9801]&0xC0){
      case 0x00: Draw16x16_Trans_8(&GFX[(z<<8)+0x10000],x,y,4);        break;
      case 0x40: Draw16x16_Trans_8_FlipY(&GFX[(z<<8)+0x10000],x,y,4);  break;
      case 0x80: Draw16x16_Trans_8_FlipX(&GFX[(z<<8)+0x10000],x,y,4);  break;
      case 0xC0: Draw16x16_Trans_8_FlipXY(&GFX[(z<<8)+0x10000],x,y,4); break;
      }
   }
#ifdef SDL
   int max = 255;
#else
   int max = 63;
#endif

   pal[0].r=0;
   pal[0].g=0;
   pal[0].b=0;

   pal[1].r=max;
   pal[1].g=0;
   pal[1].b=0;

   pal[2].r=max;
   pal[2].g=max;
   pal[2].b=0;

   pal[3].r=max;
   pal[3].g=max;
   pal[3].b=max;

   pal[4].r=0;
   pal[4].g=0;
   pal[4].b=0;

   pal[5].r=0;
   pal[5].g=0;
   pal[5].b=max;

   pal[6].r=47;
   pal[6].g=31;
   pal[6].b=23;

   pal[7].r=max;
   pal[7].g=0;
   pal[7].b=max;
}
static struct VIDEO_INFO video_chaknpop =
{
   DrawChacknpop,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_NEEDS_8BPP,
};
static struct DIR_INFO dir_chaknpop[] =
{
   { "chack_n_pop", },
   { "chaknpop", },
   { NULL, },
};
GME( chaknpop, "Chack'n Pop", TAITO, 1983, GAME_PLATFORM | GAME_NOT_WORKING,
	.board = "A04",
);

