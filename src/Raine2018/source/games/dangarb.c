/******************************************************************************/
/*                                                                            */
/*                    Ufo Robo Dangar (C) 1986 NICHIBUTSU                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "nichisnd.h"
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_dangarb[] =
{
   { "dangar01.14f", 0x00008000, 0xd59ed1f1, 0, 0, 0, },
   { "dangar02.15f", 0x00008000, 0xdfdb931c, 0, 0, 0, },
   { "dangar03.17f", 0x00008000, 0x6954e8c3, 0, 0, 0, },
   { "dangar04.19f", 0x00008000, 0x4af6a8bf, 0, 0, 0, },
   { "dangar2.011", 0x00004000, 0xe804ffe1, 0, 0, 0, },
   { "dangar06.17d", 0x00004000, 0x6c899071, 0, 0, 0, },
   { "dangar07.19d", 0x00004000, 0x6dba32cf, 0, 0, 0, },
   { "8", 0x00008000, 0x8136fd10, 0, 0, 0, },
   { "9", 0x00004000, 0x3ce5ec11, 0, 0, 0, },
   { "dangar2.018", 0x00004000, 0xdb7f6613, 0, 0, 0, },
   { "dangarxx.f1", 0x00008000, 0x8cf11419, 0, 0, 0, },
   { "dangarxx.f4", 0x00008000, 0x55711884, 0, 0, 0, },
   { "dangar13.b14", 0x00004000, 0x3e041873, 0, 0, 0, },
   { "dangar14.b15", 0x00008000, 0x488e3463, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_dangarb[] =
{
   INP0( COIN1, 0x00C001, 0x04 ),
   INP0( COIN2, 0x00C001, 0x08 ),
   INP0( TILT, 0x00C003, 0x04 ),

   INP0( P1_START, 0x00C001, 0x01 ),
   INP0( P1_UP, 0x00C000, 0x01 ),
   INP0( P1_DOWN, 0x00C000, 0x02 ),
   INP0( P1_LEFT, 0x00C000, 0x04 ),
   INP0( P1_RIGHT, 0x00C000, 0x08 ),
   INP0( P1_B1, 0x00C000, 0x10 ),
   INP0( P1_B2, 0x00C000, 0x20 ),

   INP0( P2_START, 0x00C001, 0x02 ),
   INP0( P2_UP, 0x00C002, 0x01 ),
   INP0( P2_DOWN, 0x00C002, 0x02 ),
   INP0( P2_LEFT, 0x00C002, 0x04 ),
   INP0( P2_RIGHT, 0x00C002, 0x08 ),
   INP0( P2_B1, 0x00C002, 0x10 ),
   INP0( P2_B2, 0x00C002, 0x20 ),

   END_INPUT
};



static UINT8 *GFX_BG0;
static UINT8 *GFX_BG1;
static UINT8 *GFX_SPR;
static UINT8 *GFX_FG0;

static UINT8 *MSK_BG1;
static UINT8 *MSK_SPR;
static UINT8 *MSK_FG0;

static void load_dangarb(void)
{
   int ta,tb;

   RAMSize=0x40000+0x10000;

   if(!(ROM=AllocateMem(0x040000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x0A0000))) return;

   if(!load_rom("8", RAM+0x00000, 0x08000)) return;
   if(!load_rom("9", RAM+0x08000, 0x04000)) return;
   if(!load_rom("dangar2.018", RAM+0x10000, 0x04000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x040000;
   if(!load_rom("dangar13.b14", Z80ROM+0x00000, 0x04000)) return;
   if(!load_rom("dangar14.b15", Z80ROM+0x04000, 0x08000)) return;

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

   GFX_BG0 = GFX+0x000000;
   GFX_BG1 = GFX+0x008000;
   GFX_SPR = GFX+0x048000;
   GFX_FG0 = GFX+0x088000;

   tb=0;
   if(!load_rom("dangar2.011", RAM+0x00000, 0x04000)) return;
   for(ta=0;ta<0x04000;ta++,tb+=2){
      GFX_BG0[tb+0]=(RAM[ta]&15)^15;
      GFX_BG0[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("dangar01.14f", RAM+0x00000, 0x08000)) return;
   if(!load_rom("dangar02.15f", RAM+0x08000, 0x08000)) return;
   if(!load_rom("dangar03.17f", RAM+0x10000, 0x08000)) return;
   if(!load_rom("dangar04.19f", RAM+0x18000, 0x08000)) return;
   for(ta=0;ta<0x20000;ta++,tb+=2){
      GFX_BG1[tb+0]=(RAM[ta]&15)^15;
      GFX_BG1[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("dangarxx.f4", RAM+0x00000, 0x08000)) return;
   if(!load_rom("dangarxx.f1", RAM+0x08000, 0x08000)) return;
   for(ta=0;ta<0x10000;ta++,tb+=4){
      GFX_SPR[tb+0]=(RAM[ta+0x00000]&15)^15;
      GFX_SPR[tb+1]=(RAM[ta+0x00000]>>4)^15;
      GFX_SPR[tb+2]=(RAM[ta+0x08000]&15)^15;
      GFX_SPR[tb+3]=(RAM[ta+0x08000]>>4)^15;
   }

   tb=0;
   if(!load_rom("dangar07.19d", RAM+0x00000, 0x04000)) return;
   if(!load_rom("dangar06.17d", RAM+0x04000, 0x04000)) return;
   for(ta=0;ta<0x4000;ta++,tb+=2){
      GFX_FG0[tb+0]=(RAM[ta]&15)^15;
      GFX_FG0[tb+1]=(RAM[ta]>>4)^15;
   }

   Rotate16x16(GFX_BG0,0x0400);
   Flip16x16_X(GFX_BG0,0x0400);
   Rotate16x16(GFX_BG1,0x0400);
   Flip16x16_X(GFX_BG1,0x0400);
//   Rotate16x16(GFX_SPR,0x0800);
//   Flip16x16_X(GFX_SPR,0x0800);
   Rotate8x8  (GFX_FG0,0x0400);
   Flip8x8_X  (GFX_FG0,0x0400);


   MSK_BG1 = make_solid_mask_16x16(GFX_BG1, 0x0400);
//   MSK_SPR = make_solid_mask_16x16(GFX_SPR, 0x0800);
   MSK_FG0 = make_solid_mask_8x8  (GFX_FG0, 0x0400);

   memset(RAM+0x00000,0x00,0x40000);

   set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
   InitPaletteMap(RAM+0xA000, 0x100, 0x10, 0x1000);

}

static void ClearDangarB(void)
{
   RemoveNichibutsuYM3526();

   #ifdef RAINE_DEBUG
      //save_debug("RAM.bin",RAM,0x010000,1);
   #endif
}

static void execute_dangarb(void)
{
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(6,60));	// Z80 6MHz (60fps)
   cpu_interrupt(CPU_Z80_0, 1);

   Nichibutsu3526_Frame();		// Z80 and YM3526
}

static void DrawDangarB(void)
{
   UINT8 *map;
   int x,y,ta;
   int zz,zzz,zzzz,y16;

   ClearPaletteMap();

   // BG0
   // ---

   if(((zzz=ReadWord(&RAM[0xD000]))&0x0200)==0){
      clear_game_screen(0);
   }
   else{

   zzz=ReadWord(&RAM[0xD002])+96;
   zzzz=((zzz&0x3F0)>>4)<<6;			// Y Offset (16-1024)
   y16=(zzz&15);				// Y Offset (0-15)

   zzzz += 2;

   zzzz=zzzz&0x0FFF;

   for(y=(320+16+y16);y>=16;y-=16){
   zz=zzzz;
   for(x=32;x<(224+32);x+=16){

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x6001+zz]>>3)|0x60,
         16,
         map
      );

      Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord(&RAM[0x6000+zz])&0x3FF)<<8],x,y,map);

   zz+=2;
   }
   zzzz+=0x40;
   zzzz=zzzz&0x0FFF;
   }
   }

   // OBJECT LOW
   // ----------

   if(((zzz=ReadWord(&RAM[0xD000]))&0x0800)!=0){

   for(zz=0;zz<0x600;zz+=8){

      if((ReadWord(&RAM[zz+0])&0x2000)==0){

      ta=ReadWord(&RAM[zz+2])&0x7FF;
      if(MSK_SPR[ta]!=0){				// No pixels; skip

      x=((320+32+32) - ReadWord(&RAM[zz+0]))&0x1FF;
      y=((320+32+80) - ReadWord(&RAM[zz+6]))&0x1FF;

      if((x>16)&&(y>16)&&(x<224+32)&&(y<320+32)){

         MAP_PALETTE_MAPPED_NEW(
            (RAM[zz+5]&0x1F)|0x20,
            16,
            map
         );

         if(MSK_SPR[ta]==1){				// Some pixels; trans
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }


      }
      }
      }
   }
   }

   if(((zzz=ReadWord(&RAM[0xD000]))&0x0400)!=0){

   zzz=ReadWord(&RAM[0xD006])+96;
   zzzz=((zzz&0x3F0)>>4)<<6;			// Y Offset (16-1024)
   y16=(zzz&15);				// Y Offset (0-15)

   zzzz += 2;

   zzzz=zzzz&0x0FFF;

   for(y=(320+16+y16);y>=16;y-=16){
   zz=zzzz;
   for(x=32;x<(224+32);x+=16){

   ta=ReadWord(&RAM[0x7000+zz])&0x3FF;

      if(MSK_BG1[ta]!=0){				// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x7001+zz]>>3)|0x40,
         16,
         map
      );

      if(MSK_BG1[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG1[ta<<8],x,y,map);
      }
      else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG1[ta<<8],x,y,map);
      }


      }

   zz+=2;
   }
   zzzz+=0x40;
   zzzz=zzzz&0x0FFF;
   }

   }


   // OBJECT HIGH
   // -----------

   if(((zzz=ReadWord(&RAM[0xD000]))&0x0800)!=0){

   for(zz=0;zz<0x600;zz+=8){

      if((ReadWord(&RAM[zz+0])&0x2000)!=0){

      ta=ReadWord(&RAM[zz+2])&0x7FF;
      if(MSK_SPR[ta]!=0){				// No pixels; skip

      x=((320+32+32) - ReadWord(&RAM[zz+0]))&0x1FF;
      y=((320+32+80) - ReadWord(&RAM[zz+6]))&0x1FF;

      if((x>16)&&(y>16)&&(x<224+32)&&(y<320+32)){

         MAP_PALETTE_MAPPED_NEW(
            (RAM[zz+5]&0x1F)|0x20,
            16,
            map
         );

         if(MSK_SPR[ta]==1){				// Some pixels; trans
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }


      }
      }
      }
   }
   }

   // FG0
   // ---
   if(((zzz=ReadWord(&RAM[0xD000]))&0x0100)!=0){

   zz=4;
   for(y=(320+24);y>=32;y-=8){
   for(x=32;x<224+32;x+=8){

      ta = ((RAM[0x9300+zz]&3)<<8) | (RAM[0x8300+zz]);

      if(MSK_FG0[ta]!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM[0x9300+zz]>>4),
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
static struct VIDEO_INFO video_dangarb =
{
   DrawDangarB,
   224,
   320,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_dangarb[] =
{
   { "ufo_robo_dangar", },
   { "dangarb", },
   { "dangar", },
   { NULL, },
};
GAME( dangarb, "Dangar - Ufo Robo (bootleg)", NICHIBUTSU, 1986, GAME_SHOOT | GAME_NOT_WORKING,
	.input = input_dangarb,
	.clear = ClearDangarB,
	.video = &video_dangarb,
	.exec = execute_dangarb,
	.sound = nichi_ym3812_sound,
);

