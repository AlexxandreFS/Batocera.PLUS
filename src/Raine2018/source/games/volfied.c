#define DRV_DEF_SOUND taito_ym2203_sound
/******************************************************************************/
/*                                                                            */
/*                    VOLFIED (C) 1988 TAITO CORPORATION                      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "2203intf.h"
#include "taitosnd.h"
#include "blit.h"


static struct ROM_INFO rom_volfiedj[] =
{
   {   "c04-06.bin", 0x00008000, 0xb70106b2, 0, 0, 0, },
   { "c04-07-1.bin", 0x00010000, 0x5d9065d5, 0, 0, 0, },
   { "c04-08-1.bin", 0x00010000, 0x19f7e66b, 0, 0, 0, },
   {   "c04-09.bin", 0x00010000, 0xc78cf057, 0, 0, 0, },
   {   "c04-10.bin", 0x00010000, 0x429b6b49, 0, 0, 0, },
   { "c04-11-1.bin", 0x00010000, 0x1aaf6e9b, 0, 0, 0, },
   { "c04-12-1.bin", 0x00010000, 0xafb6a058, 0, 0, 0, },
   {   "c04-15.bin", 0x00020000, 0x7c50b978, 0, 0, 0, },
   {   "c04-16.bin", 0x00020000, 0x8c2476ef, 0, 0, 0, },
   {   "c04-17.bin", 0x00020000, 0xc62fdeb8, 0, 0, 0, },
   {   "c04-18.bin", 0x00020000, 0x7665212c, 0, 0, 0, },
   {   "c04-19.bin", 0x00020000, 0x231493ae, 0, 0, 0, },
   {   "c04-20.bin", 0x00020000, 0x0aea651f, 0, 0, 0, },
   {   "c04-21.bin", 0x00020000, 0x8598d38e, 0, 0, 0, },
   {   "c04-22.bin", 0x00020000, 0xf405d465, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_volfiedj[] =
{
   INP1( COIN1, 0x0B0009, 0x01 ),
   INP1( COIN2, 0x0B0009, 0x02 ),
   INP0( TILT, 0x0B000B, 0x01 ),
   INP0( SERVICE, 0x0B0007, 0x80 ),

   INP0( P1_START, 0x0B0007, 0x40 ),
   INP0( P1_UP, 0x0B000B, 0x04 ),
   INP0( P1_DOWN, 0x0B000B, 0x08 ),
   INP0( P1_LEFT, 0x0B000B, 0x10 ),
   INP0( P1_RIGHT, 0x0B000B, 0x20 ),
   INP0( P1_B1, 0x0B000B, 0x40 ),

   INP0( P2_START, 0x0B0007, 0x20 ),
   INP0( P2_UP, 0x0B000D, 0x02 ),
   INP0( P2_DOWN, 0x0B000D, 0x04 ),
   INP0( P2_LEFT, 0x0B000D, 0x08 ),
   INP0( P2_RIGHT, 0x0B000D, 0x10 ),
   INP0( P2_B1, 0x0B000D, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_volfied_0[] =
{
   { _("Game Style"),            0x01, 0x02 },
   { MSG_NORMAL,              0x01},
   { _("Upright"),               0x00},
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

static struct DSW_DATA dsw_data_volfied_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("20k 40k"),               0x0C},
   { _("50k 150k"),              0x08},
   { _("70k 280k"),              0x04},
   { _("100k 500k"),             0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "6",                     0x00},
   { _("Language"),              0x80, 0x02 },
   { _("Japanese"),              0x80},
   { _("English"),               0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_volfiedj[] =
{
   { 0x08A001, 0xFF, dsw_data_volfied_0 },
   { 0x08A000, 0x7F, dsw_data_volfied_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_volfied_0[] =
{
   { "Taito 0",               0x00 },
   { "Taito 1",               0x01 },
   { "Taito 2",               0x02 },
   { "Taito 3",               0x03 },
   { "Taito 4",               0x04 },
   { "Taito 5",               0x05 },
   { "Taito 6",               0x06 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_volfiedj[] =
{
   { 0x03FFFF, 0x01, romsw_data_volfied_0 },
   { 0,        0,    NULL },
};



static UINT8 *GFX_SPR_SOLID;

static void BadWriteByte(UINT32 addr, UINT8 data)
{
#ifdef RAINE_DEBUG
      if(addr!=0x700001) print_debug("Wb(%06x,%02x) [%06x]\n",addr,data,s68000context.pc);
#endif
}

//static UINT8 *GFX_BG0_SOLID;

static UINT8 *CBANK[8];
static int CChip_Bank=0;

static int CChip_ID=0x01;

static int CChipReadB(UINT32 address)
{
   int i;

   i=address&0x0FFF;

   switch(i){
      case 0x803:
         return(CChip_ID);
      break;
      case 0xC01:
         return(CChip_Bank);
      break;
      default:
#ifdef RAINE_DEBUG
            if((i<0x07)||(i>0x0D)){
            print_debug("CCRB[%02x][%03x](%02x)\n",CChip_Bank,i,CBANK[CChip_Bank][i]);
            print_ingame(60,"CCRB[%02x][%03x](%02x)\n",CChip_Bank,i,CBANK[CChip_Bank][i]);
            }
#endif
         return(CBANK[CChip_Bank][i]);
      break;
   }
}

static int CChipReadW(UINT32 address)
{
   return(CChipReadB(address+1));
}

static void CChipWriteB(UINT32 address, int data)
{
   int i;

   i=address&0x0FFF;
   data&=0xFF;

   switch(i){
      case 0x803:       // C-CHIP ID
      break;
      case 0xC01:       // C-CHIP BANK SELECT
         CChip_Bank=data&7;
      break;
      default:
         //CBANK[CChip_Bank][i]=data;
      break;
   }
}

static void CChipWriteW(UINT32 address, int data)
{
   CChipWriteB(address+1,data&0xFF);
}


static UINT16 pal_test[16]=
{
   0x0101,
   0x6210,
   0x5AD6,
   0x5294,
   0x4A52,
   0x4210,
   0x39CE,
   0x318C,
   0x2948,
   0x69CC,
   0x71C6,
   0x3000,
   0x4000,
   0x5000,
   0x6000,
   0x7800,
};

static void load_volfiedj(void)
{
   int ta,tb;

   RAMSize=0xA0000+0x10000+0x4000;

   if(!(ROM=AllocateMem(0xC0000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x180000))) return;

   CBANK[0]=RAM+0xA0000+0x10000+0x0000; // C-CHIP BANKS ($F00000-$F00FFF)
   CBANK[1]=RAM+0xA0000+0x10000+0x0800;
   CBANK[2]=RAM+0xA0000+0x10000+0x1000;
   CBANK[3]=RAM+0xA0000+0x10000+0x1800;
   CBANK[4]=RAM+0xA0000+0x10000+0x2000;
   CBANK[5]=RAM+0xA0000+0x10000+0x2800;
   CBANK[6]=RAM+0xA0000+0x10000+0x3000;
   CBANK[7]=RAM+0xA0000+0x10000+0x3800;

   for(ta=0;ta<0x4000;ta+=2){
      WriteWord(&RAM[0xA0000+0x10000+ta],pal_test[(ta>>1)&0x0F]);
   }

   if(!load_rom("c04-16.bin",&ROM[0x00000],0x20000)) return;   // 16x16 SPRITES
   if(!load_rom("c04-15.bin",&ROM[0x20000],0x20000)) return;
   if(!load_rom("c04-10.bin",&ROM[0x40000],0x10000)) return;   // 16x16 SPRITES
   if(!load_rom("c04-10.bin",&ROM[0x50000],0x10000)) return;   // 16x16 SPRITES
   tb=0;
   for(ta=0;ta<0x60000;ta++,tb+=4){
      GFX[tb+0]=ROM[ta]>>4;
      GFX[tb+1]=ROM[ta]&15;
   }
   if(!load_rom("c04-18.bin",&ROM[0x00000],0x20000)) return;   // 16x16 SPRITES
   if(!load_rom("c04-17.bin",&ROM[0x20000],0x20000)) return;
   if(!load_rom("c04-09.bin",&ROM[0x40000],0x10000)) return;   // 16x16 SPRITES
   if(!load_rom("c04-09.bin",&ROM[0x50000],0x10000)) return;   // 16x16 SPRITES
   tb=2;
   for(ta=0;ta<0x60000;ta++,tb+=4){
      GFX[tb+0]=ROM[ta]>>4;
      GFX[tb+1]=ROM[ta]&15;
   }
   GFX_SPR_SOLID = make_solid_mask_16x16( GFX, 0x180000/0x100  );

   if(!load_rom("c04-12-1.bin",&RAM[0x00000],0x10000)) return; // 68000 ROM
   if(!load_rom("c04-11-1.bin",&RAM[0x10000],0x10000)) return;
   if(!load_rom("c04-20.bin",  &RAM[0x20000],0x20000)) return; // 8x8 TILES
   if(!load_rom("c04-19.bin",  &RAM[0x40000],0x20000)) return;
   for(ta=0;ta<0x60000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c04-08-1.bin",&RAM[0x00000],0x10000)) return;
   if(!load_rom("c04-07-1.bin",&RAM[0x10000],0x10000)) return;
   if(!load_rom("c04-22.bin",  &RAM[0x20000],0x20000)) return; // 8x8 TILES
   if(!load_rom("c04-21.bin",  &RAM[0x40000],0x20000)) return;
   for(ta=0;ta<0x60000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0xA0000;
   if(!load_rom("c04-06.bin",Z80ROM,0x8000)) return;           // Z80 SOUND ROM
   memset(Z80ROM+0x8000,0xFF,0x8000);

   Z80ROM[0x0253]=0xD3; // OUTA (AAh)
   Z80ROM[0x0254]=0xAA; //

   SetStopZ80Mode2(0x020E);

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x8800, 0x8801, tc0140syt_read_sub_z80,      NULL);
   AddZ80AReadByte(0x9000, 0x9001, YM2203AReadZ80,              NULL);
   AddZ80AReadByte(0x0000, 0xFFFF, NULL,                        Z80ROM+0x0000); // <test>
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);          // <bad reads>
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0x8800, 0x8801, tc0140syt_write_sub_z80,    NULL);
   AddZ80AWriteByte(0x9000, 0x9001, YM2203AWriteZ80,            NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, NULL,                       Z80ROM+0x0000); // <test>
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);          // <bad writes>
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   tc0140syt_reset();			// Add [J3d!]

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0xA0000);
   memset(RAM+0x8A000,0xFF,0x00100);

   // C-Chip
   // ------

   WriteWord68k(&ROM[0x13FB2],0x4E71);

   WriteWord68k(&ROM[0x08262],0x4E71);          // Use unprotected code
   WriteWord68k(&ROM[0x08228],0x4E71);          // better than nothing i guess

   // Sound Wait
   // ----------

   WriteWord68k(&ROM[0x004F0],0x4E71);

   // Speed Hack
   // ----------

   WriteWord68k(&ROM[0x0161C],0x4EF9);
   WriteLong68k(&ROM[0x0161E],0x00000300);

   WriteWord68k(&ROM[0x00300],0x4EB9);
   WriteLong68k(&ROM[0x00302],0x00005CD6);
   WriteLong68k(&ROM[0x00306],0x13FC0000);
   WriteLong68k(&ROM[0x0030A],0x00AA0000);
   WriteWord68k(&ROM[0x0030E],0x6100-16);

   WriteLong68k(&ROM[0x1438E],0x13FC0000);
   WriteLong68k(&ROM[0x14392],0x00AA0000);
   WriteWord68k(&ROM[0x14396],0x4E75);

   // DSW Hack
   // --------

   WriteWord68k(&ROM[0x073A6],0x1039);                  //      move.b  $110000,d0
   WriteLong68k(&ROM[0x073A8],0x00110000);
   WriteWord68k(&ROM[0x073AC],0x4EF9);                  //      jmp     $73E2
   WriteLong68k(&ROM[0x073AE],0x000073E2);

   WriteWord68k(&ROM[0x073F4],0x1039);                  //      move.b  $110001,d0
   WriteLong68k(&ROM[0x073F6],0x00110001);
   WriteWord68k(&ROM[0x073FA],0x4EF9);                  //      jmp     $7430
   WriteLong68k(&ROM[0x073FC],0x00007430);

   InitPaletteMap(RAM+0x86000, 0x200, 0x10, 0x8000);
   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xC0000);
   ByteSwap(RAM,0xA0000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x103FFF, NULL, RAM+0x000000);                 // MAIN RAM
   AddReadByte(0x080000, 0x0FFFFF, NULL, ROM+0x040000);                 // 68000 GFX ROM
   AddReadByte(0x200000, 0x201FFF, NULL, RAM+0x084000);                 // OBJECT RAM
   AddReadByte(0x400000, 0x47FFFF, NULL, RAM+0x004000);                 // PIXEL RAM
   AddReadByte(0xE00000, 0xE00003, tc0140syt_read_main_68k, NULL);      // SOUND
   AddReadByte(0xF00000, 0xF00FFF, CChipReadB, NULL);                   // C-CHIP
   AddReadByte(0x110000, 0x110001, NULL, RAM+0x08A000);                 // DSW (HACKED)
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x103FFF, NULL, RAM+0x000000);                 // MAIN RAM
   AddReadWord(0x080000, 0x0FFFFF, NULL, ROM+0x040000);                 // 68000 GFX ROM
   AddReadWord(0x200000, 0x201FFF, NULL, RAM+0x084000);                 // OBJECT RAM
   AddReadWord(0x400000, 0x47FFFF, NULL, RAM+0x004000);                 // PIXEL RAM
   AddReadWord(0x500000, 0x503FFF, NULL, RAM+0x086000);                 // COLOR RAM
   AddReadWord(0xE00000, 0xE00003, tc0140syt_read_main_68k, NULL);      // SOUND
   AddReadWord(0xF00000, 0xF00FFF, CChipReadW, NULL);                   // C-CHIP
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x100000, 0x103FFF, NULL, RAM+0x000000);                // MAIN RAM
   AddWriteByte(0x200000, 0x201FFF, NULL, RAM+0x084000);                // OBJECT RAM
   AddWriteByte(0x400000, 0x47FFFF, NULL, RAM+0x004000);                // PIXEL RAM
   AddWriteByte(0xE00000, 0xE00003, tc0140syt_write_main_68k, NULL);    // SOUND
   AddWriteByte(0xF00000, 0xF00FFF, CChipWriteB, NULL);                 // C-CHIP
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, BadWriteByte, NULL);                // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x103FFF, NULL, RAM+0x000000);                // MAIN RAM
   AddWriteWord(0x200000, 0x201FFF, NULL, RAM+0x084000);                // OBJECT RAM
   AddWriteWord(0x400000, 0x47FFFF, NULL, RAM+0x004000);                // PIXEL RAM
   AddWriteWord(0x500000, 0x503FFF, NULL, RAM+0x086000);                // COLOR RAM
   AddWriteWord(0xE00000, 0xE00003, tc0140syt_write_main_68k, NULL);    // SOUND
   AddWriteWord(0xF00000, 0xF00FFF, CChipWriteW, NULL);                 // C-CHIP
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void execute_volfiedj(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));    // M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 4);

   if(tc0140syt_want_nmi()!=0) cpu_int_nmi(CPU_Z80_0);

   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Sound Z80
   cpu_interrupt(CPU_Z80_0, 0x0038);
}

static void DrawVolfied(void)
{
   int x,y,zz;
   UINT8 *BIT;
   UINT8 *MAP;
   static int tm=1;
   static int tm2=8;
   UINT16 ta;

   ClearPaletteMap();

      MAP_PALETTE_MAPPED_NEW(
         tm2*16,
         0x10,
         MAP
      );

#if 0
   if(key[KEY_J]){
   if(flip1==0){
      tm--;
      tm&=0x1F;
      flip1=1;
   }
   }
   else{
#endif
      // flip1=0;
#if 0
   }
   if(key[KEY_K]){
   if(flip2==0){
      tm++;
      tm&=0x1F;
      flip2=1;
   }
   }
   else{
#endif
      // flip2=0;
#if 0
     }

   if(key[KEY_I]){
   if(flip3==0){
      tm2--;
      tm2&=0x1F;
      flip3=1;
   }
   }
   else{
#endif
      // flip3=0;
#if 0
   }
   if(key[KEY_O]){
   if(flip4==0){
      tm2++;
      tm2&=0x1F;
      flip4=1;
   }
   }
   else{
#endif
      // flip4=0;
   // }

   print_ingame(60,"%04x.%04x",tm,tm2);

   zz=0x04001+(8*1024);

   // Now that the screen is rotated, this code should rotate too !
   // to do later.
   for(y=0;y<240;y++){
   BIT=GameViewBitmap->line[y];
   for(x=0;x<320;x++){
      BIT[x]=MAP[((ReadWord(&RAM[zz])>>tm)&0x0F)];
      //if(RAM[zz+1]!=0)BIT[x]=MAP[RAM[zz+1]];
      zz+=2;
   }
   zz+=(1024-(320*2));
   }

   for(zz=0x847F8;zz>=0x84000;zz-=8){
   x=(32+ReadWord(&RAM[zz+6]))&0x1FF;
   y=(24+ReadWord(&RAM[zz+2]))&0x1FF;

   if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){

     ta = ReadWord(&RAM[zz+4])&0x1FFF;
     if (GFX_SPR_SOLID[ta]) {
       MAP_PALETTE_MAPPED_NEW(
         (RAM[zz]&0x0F)|0x100,
         16,
         MAP
        );

       if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
	 switch(RAM[zz+1]&0xC0){
	 case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[((ta)<<8)],x,y,MAP);        break;
	 case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[((ta)<<8)],x,y,MAP);  break;
	 case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[((ta)<<8)],x,y,MAP);  break;
	 case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[((ta)<<8)],x,y,MAP); break;
	 }
       } else { // solid
	 switch(RAM[zz+1]&0xC0){
	 case 0x00: Draw16x16_Mapped_Rot(&GFX[((ta)<<8)],x,y,MAP);        break;
	 case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX[((ta)<<8)],x,y,MAP);  break;
	 case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX[((ta)<<8)],x,y,MAP);  break;
	 case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[((ta)<<8)],x,y,MAP); break;
	 }
       }
     }

   }

   }
}


/*

COLOUR RAM
----------

- $4000 bytes
- $2000 colours
- $200 banks of 16 colours

*/
static struct VIDEO_INFO video_volfiedj =
{
   DrawVolfied,
   320,
   240,
   32,
   VIDEO_ROTATE_270 | VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_volfiedj[] =
{
   { "volfied", },
   { "volfiedj", },
   { NULL, },
};
GME( volfiedj, "Volfied", TAITO, 1989, GAME_SHOOT | GAME_NOT_WORKING,
	.romsw = romsw_volfiedj,
	.board = "C04",
);

