#define DRV_DEF_SOUND taito_ym2610b_sound
/******************************************************************************/
/*                                                                            */
/*                  BATTLE SHARK (C) 1989 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc150rod.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "zoom/16x8.h"		// 16x8 zoomed sprite routines
#include "zoom/16x16.h"		// 16x8 zoomed sprite routines

#include "taito_z.h"
#include "gun.h"


static struct ROM_INFO rom_bshark[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "c34_71.98",  0xdf1fa629, "c34_69.75",  0xa54c137a),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x20000,
            "c34_70.97",  0xd77d81e2, "bshark67.bin",  0x39307c74),
  LOAD8_16(  REGION_ROM2,  0x00000,  0x20000,
            "c34_74.128",  0x6869fa99, "c34_72.112",  0xc09c0f91),
  LOAD8_16(  REGION_ROM2,  0x40000,  0x20000,
            "c34_75.129",  0x6ba65542, "c34_73.113",  0xf2fe62b5),
  { "c34_05.3", 0x80000, 0x596b83da, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "c34_04.17", 0x080000, 0x2446b0da, REGION_GFX2, 0x000000, LOAD_8_32 },
  { "c34_03.16", 0x080000, 0xa18eab78, REGION_GFX2, 0x000001, LOAD_8_32 },
  { "c34_02.15", 0x080000, 0x8488ba10, REGION_GFX2, 0x000002, LOAD_8_32 },
  { "c34_01.14", 0x080000, 0x3ebe8c63, REGION_GFX2, 0x000003, LOAD_8_32 },
  { "c34_07.42", 0x80000, 0xedb07808, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "c34_06.12", 0x80000, 0xd200b6eb, REGION_USER1, 0x00000, LOAD_NORMAL },
  { "c34_08.127", 0x80000, 0x89a30450, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "c34_09.126", 0x80000, 0x39d12b50, REGION_SMP2, 0x00000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_bshark[] =
{
   INP0( COIN1, 0x027014, 0x02 ),
   INP0( COIN2, 0x027014, 0x01 ),
   INP0( TILT, 0x027014, 0x08 ),
   INP0( SERVICE, 0x027014, 0x04 ),

   INP0( P1_START, 0x02701E, 0x01 ),
   INP0( P1_B1, 0x02701E, 0x40 ),

   INP0( P2_START, 0x02701E, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_battle_shark_0[] =
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

static struct DSW_INFO dsw_bshark[] =
{
   { 0x027010, 0xFF, dsw_data_battle_shark_0 },
   { 0x027012, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_battle_shark_0[] =
{
   { "Taito 0",               0x00 },
   { "Taito 1",               0x01 },
   { "Taito 2",               0x02 },
   { "Taito 3",               0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_bshark[] =
{
   { 0x07FFFF, 0x02, romsw_data_battle_shark_0 },
   { 0,        0,    NULL },
};



#define OBJ_A_COUNT	(0x75C8)

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
static UINT8 *GFX_OBJ_A_SOLID;

static UINT8 *zoom16_ofs;
static UINT8 *zoom8_ofs;

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_LINES;

static UINT16 YM2610Read68k(UINT32 address)
{
   return YM2610ReadZ80( (UINT16) ((address&7)>>1) );
}

static void YM2610Write68k(UINT32 address, UINT16 data)
{
   YM2610WriteZ80( (UINT16) ((address&7)>>1), (UINT8) data);
}

static void load_bshark(void)
{
   UINT8 *ROM2 = load_region[REGION_CPU2];

   GFX_BG0_SOLID = NULL;

   OBJECT_MAP = load_region[REGION_USER1];

   if (!(GFX_LINES = process_lines(REGION_GFX3))) return;

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x14000;
   RAM_SCROLL = RAM+0x27000;
   RAM_INPUT  = RAM+0x27010;
   GFX_FG0    = RAM+0x3C000;

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x25000, 0x100, 0x10, 0x8000);

   // CPU Communication
   // -----------------

   ROM[0x0BD52]=0x60;
   WriteLong68k(&ROM[0x0BD6A],0x4E714E71);	//	nop
   WriteLong68k(&ROM[0x0BD72],0x4E714E71);	//	nop
   ROM[0x0BEB6]=0x60;
   ROM[0x0BEE6]=0x60;
   ROM[0x0BF0E]=0x60;
   WriteLong68k(&ROM[0x0BF24],0x4E714E71);	//	nop
   WriteWord68k(&ROM[0x0BF3A],0x4E71);		//	nop

   // Control Hack
   // ------------

   WriteWord68k(&ROM[0x07FDE],0x1B79);		//	X
   WriteLong68k(&ROM[0x07FE0],0x00800001);	//
   WriteWord68k(&ROM[0x07FE4],0xB902);		//

   WriteWord68k(&ROM[0x07FE6],0x1B79);		//	Y
   WriteLong68k(&ROM[0x07FE8],0x00800003);	//
   WriteWord68k(&ROM[0x07FEC],0xB903);		//

   WriteWord68k(&ROM[0x07FEE],0x3E1F);		//	move	(a7)+,D7
   WriteWord68k(&ROM[0x07FF0],0x4E73);		//	rte

   // Main 68000 Speed Hack
   // ---------------------

   WriteWord68k(&ROM[0x0304C],0x4EF9);		//	jmp	$2F00
   WriteLong68k(&ROM[0x0304E],0x00002F00);	//

   WriteLong68k(&ROM[0x02F00],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x02F04],0x00AA0000);	//
   WriteWord68k(&ROM[0x02F08],0x4EB9);		//	jsr	<random_gen>
   WriteLong68k(&ROM[0x02F0A],0x000004C6);	//
   WriteWord68k(&ROM[0x02F0E],0x4EF9);		//	jmp	$3052
   WriteLong68k(&ROM[0x02F10],0x00003052);	//

   // Sub 68000 Speed Hack
   // ---------------------

   WriteLong68k(&ROM2[0x0093C],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM2[0x00940],0x00AA0000);	//
   WriteWord68k(&ROM2[0x00944],0x6100-10);	//	bra.s	loop

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0150rod emulation
   // ------------------------

   tc0150rod.RAM  	= RAM + 0x34000;
   tc0150rod.GFX  	= GFX_LINES;
   tc0150rod.PAL  	= NULL;
   // tc0150rod.mapper	= &Map_15bit_xBGR;
   tc0150rod.bmp_x	= 32;
   tc0150rod.bmp_y	= 32;
   tc0150rod.bmp_w	= 320;
   tc0150rod.bmp_h	= 240;
   tc0150rod.scr_x	= 0;
   tc0150rod.scr_y	= -14;

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   // tc0100scn[0].layer[0].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   // tc0100scn[0].layer[1].mapper	=&Map_15bit_xBGR;
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
   // tc0100scn[0].layer[2].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;


   init_16x8_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1zz();
   zoom8_ofs  = make_16x8_zoom_ofs_type1zz();

   GameMouse = 1;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_CPU1));
   ByteSwap(ROM2,get_region_size(REGION_CPU2));

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x113FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0xC00000, 0xC00FFF, NULL, RAM+0x024000);			// OBJECT RAM
   AddReadByte(0xA00000, 0xA01FFF, NULL, RAM+0x025000);			// COLOR RAM
   AddReadByte(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x800000, 0x80000F, NULL, RAM+0x027020);			// CURSOR
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x113FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xC00000, 0xC00FFF, NULL, RAM+0x024000);			// OBJECT RAM
   AddReadWord(0xA00000, 0xA01FFF, NULL, RAM+0x025000);			// COLOR RAM
   AddReadWord(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x113FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xD06000, 0xD06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xC00000, 0xC00FFF, NULL, RAM+0x024000);		// OBJECT RAM
   AddWriteByte(0xA00000, 0xA01FFF, NULL, RAM+0x025000);		// COLOR RAM
   AddWriteByte(0x400000, 0x40000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x113FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xD06000, 0xD06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xC00000, 0xC00FFF, NULL, RAM+0x024000);		// OBJECT RAM
   AddWriteWord(0xA00000, 0xA01FFF, NULL, RAM+0x025000);		// COLOR RAM
   AddWriteWord(0xD20000, 0xD2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x400000, 0x40000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x07FFFF, ROM2);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x07FFFF, NULL, ROM2);		// 68000 ROM
   AddReadByteMC68000B(0x108000, 0x10BFFF, NULL, RAM+0x030000);		// MAIN RAM
   AddReadByteMC68000B(0x110000, 0x113FFF, NULL, RAM+0x010000);		// COMMON RAM
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);	// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x07FFFF, NULL, ROM2);		// 68000 ROM
   AddReadWordMC68000B(0x108000, 0x10BFFF, NULL, RAM+0x030000);		// MAIN RAM
   AddReadWordMC68000B(0x110000, 0x113FFF, NULL, RAM+0x010000);		// COMMON RAM
   AddReadWordMC68000B(0x600000, 0x600007, YM2610Read68k, NULL);	// YM2610
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);	// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x108000, 0x10BFFF, NULL, RAM+0x030000);	// MAIN RAM
   AddWriteByteMC68000B(0x110000, 0x113FFF, NULL, RAM+0x010000);	// COMMON RAM
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);	// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x108000, 0x10BFFF, NULL, RAM+0x030000);	// MAIN RAM
   AddWriteWordMC68000B(0x110000, 0x113FFF, NULL, RAM+0x010000);	// COMMON RAM
   AddWriteWordMC68000B(0x800000, 0x801FFF, NULL, RAM+0x034000);	// ROADSCROLL RAM
   AddWriteWordMC68000B(0x600000, 0x600007, YM2610Write68k, NULL);	// YM2610
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);	// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static int x1,myy1,x11,myy11;

static void execute_bshark(void)
{
   /*------[Mouse Hack]-------*/

   set_mouse_range(0,0,319,239);

   x11=319-mouse_x;
   myy11=mouse_y;

   x1=(x11*106)/320;
   myy1=(myy11*98)/240;

   if(x1<0){x1=0;}
   if(x1>127){x1=127;}
   if(myy1<0){myy1=0;}
   if(myy1>127){myy1=127;}

   RAM[0x27020]=x1-0x40+12;
   RAM[0x27022]=myy1-0x40+18;

   if(mouse_b&1) RAM[0x2701E] &= ~0x40;

   /*------[CPU Execution]------*/

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(10,60));	// M68000 12MHz (60fps)
      print_debug("PC0:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 4);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(10,60));	// M68000 12MHz (60fps)
      print_debug("PC1:%06x SR1:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 4);
}

static void render_z_system_sprites(int pri)
{
   int x,y,ta,tb,zz;
   int zx,zy,rx,ry,xx,zzx,zzy;
   UINT8 *map,*SPR_MAP;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
/*
   if(pri!=0)
      pri=0x00;
   else
      pri=0x80;
*/
   // OBJECT Z-SYSTEM
   // ---------------

   for(zz=0x24000;zz<0x25000;zz+=8){

      //if((RAM[zz+2]&0x80)==pri){

      zx=(RAM[zz+2]>>0)&0x3F;
      zy=(RAM[zz+1]>>1)&0x3F;
      if((zx!=0)&&(zy!=0)){

         ta = ReadWord(&RAM[zz+6])&0xFFF;
         if(ta!=0){

            x=((320+32)-(ReadWord(&RAM[zz+4])+zx))&0x1FF;

            //y=(32+ReadWord(&RAM[zz+0])+(0x3F-(zy>>1)))&0x1FF;

            y=(((64-16)+32+7)+(ReadWord(&RAM[zz+0])-zy))&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+2])>>7)&0xFF,
               16,
               map
            );

            zoom_dat_x = zoom16_ofs+(zx<<2);
            zoom_dat_y = zoom8_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + (ta<<6);

            switch(RAM[zz+5]&0xC0){
            case 0x40:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
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
            case 0x00:

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
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
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
            case 0xC0:

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
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
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
            case 0x80:

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
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
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
      }
   //}
   }
}

static void DrawBattleShark(void)
{
   int x,y;

   ClearPaletteMap();

   if (!GFX_BG0_SOLID) {
     GFX_OBJ_A = gfx[0];
     GFX_OBJ_A_SOLID = gfx_solid[0]; // make_solid_mask_16x8(GFX_OBJ_A, OBJ_A_COUNT);
     GFX_BG0_SOLID   = gfx_solid[1]; // make_solid_mask_8x8 (GFX,       0x4000);
     tc0100scn[0].layer[0].GFX	=GFX;
     tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
     tc0100scn[0].layer[1].GFX	=GFX;
     tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
     init_tc0100scn(0);
   }

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped_flipy(0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped_flipy(0,1);

   // 3D-ROAD Z-SYSTEM
   // ----------------

   tc0150rod_init_palette();
   tc0150rod_render_flipy(0x000,0x800);

   // OBJECT
   // ------

   render_z_system_sprites(1);

   // FG0
   // ---

   render_tc0100scn_layer_mapped_flipy(0,2);

   // CURSOR
   // ------

   x=(32+(319-x11))-7;
   y=(32+myy11)-7;
   if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){
     disp_gun(0,x,y);
   }

}

/*

BATTLE SHARK
------------

- Taito; 1989; Z-System
- 68000; 68000; YM2610

-------------+--------------------------------
File         | Contents
-------------+--------------------------------
BSHARK01.BIN | Sprite Tiles (plane0)
BSHARK02.BIN | Sprite Tiles (plane1)
BSHARK03.BIN | Sprite Tiles (plane2)
BSHARK04.BIN | Sprite Tiles (plane3)
BSHARK05.BIN | 8x8 BG0 Tiles
BSHARK06.BIN | Sprite Table
BSHARK07.BIN | tc0150rod gfx
BSHARK08.BIN | YM2610 ADPCM
BSHARK09.BIN | YM2610 ADPCM
BSHARK18.BIN | ? (Zoom table data/Roadscroll)
BSHARK19.BIN | ? (256 bytes)
BSHARK67.BIN | Main 68000 block#1 (odd)
BSHARK69.BIN | Main 68000 block#0 (odd)
BSHARK70.BIN | Main 68000 block#1 (even)
BSHARK71.BIN | Main 68000 block#0 (even)
BSHARK72.BIN | Sub 68000 block#0 (odd)
BSHARK73.BIN | Sub 68000 block#1 (odd)
BSHARK74.BIN | Sub 68000 block#0 (even)
BSHARK75.BIN | Sub 68000 block#1 (even)
-------------+--------------------------------

OBJECT RAM
----------

-----+--------+-------------------------------
Byte | Bit(s) | Description
-----+76543210+-------------------------------
  0  |.xxxxxx.| Zoom Y Axis (0-63)
  0  |.......x| Y Position (High)
  1  |xxxxxxxx| Y Position (Low)
  2  |.xxxxxxx| Colour Bank (High)
  3  |x.......| Colour Bank (Low)
  3  |..xxxxxx| Zoom X Axis (0-63)
  4  |x.......| Flip X Axis
  4  |.x......| Flip Y Axis
  4  |.......x| X Position (High)
  5  |xxxxxxxx| X Position (Low)
  6  |....xxxx| Sprite Tile (High)
  7  |xxxxxxxx| Sprite Tile (Low)
-----+--------+-------------------------------

- Colour ram looks like it can switch access mode:

A00004 == 0000: Normal access (A00000-A01FFF)
A00004 == 0001: Port access   (A00000-A00003)

- Maybe other taito games can switch like this.
- Maybe they just left some old code in the rom.

*/

static struct VIDEO_INFO video_bshark =
{
   DrawBattleShark,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
   taitoz_gfxdecodeinfo
};
static struct DIR_INFO dir_bshark[] =
{
   { "battle_shark", },
   { "bshark", },
   { NULL, },
};
GME( bshark, "Battle Shark", TAITO, 1989, GAME_SHOOT,
	.romsw = romsw_bshark,
	.board = "C34",
);

