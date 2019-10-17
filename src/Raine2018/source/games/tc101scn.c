/******************************************************************************/
/*                                                                            */
/*             tc0100scn: TAITO SCREEN LAYER CHIP (BG0/BG1/FG0)               */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "savegame.h"

#define GFX_FG0_COUNT	0x100

static UINT8 *RAM_FG[MAX_CHIP];
static UINT8 *GFX_FG[MAX_CHIP];

int layer_id_data[MAX_CHIP][3];

static UINT32 gfx_fg0_dirty_count[MAX_CHIP];
static UINT32 GFX_FG0_DIRTY[MAX_CHIP][GFX_FG0_COUNT];
static UINT8 GFX_FG0_SOLID[MAX_CHIP][GFX_FG0_COUNT];

static char *layer_id_name[MAX_CHIP][3] =
{
   { "BG0",   "BG1",   "FG0",   },
   { "BG0#2", "BG1#2", "FG0#2", },
   //{ "TC0100SCN:BG0",   "TC0100SCN:BG1",   "TC0100SCN:FG0",   },
   //{ "TC0100SCN#2:BG0", "TC0100SCN#2:BG1", "TC0100SCN#2:FG0", },
};

void tc0100scn_0_load_update(void);

void init_tc0100scn(int chip)
{
   GFX_FG[chip] = tc0100scn[chip].GFX_FG0;
   RAM_FG[chip] = tc0100scn[chip].RAM+0x6000;

   tc0100scn[chip].layer[2].MASK	= GFX_FG0_SOLID[chip];

   gfx_fg0_dirty_count[chip] = 0;
   memset(GFX_FG0_DIRTY[chip],0x00,GFX_FG0_COUNT*4);
   memset(GFX_FG0_SOLID[chip],0x00,GFX_FG0_COUNT);

   layer_id_data[chip][0] = add_layer_info(layer_id_name[chip][0]);
   layer_id_data[chip][1] = add_layer_info(layer_id_name[chip][1]);
   layer_id_data[chip][2] = add_layer_info(layer_id_name[chip][2]);

   if(GFX_FG[chip]){
      memset(GFX_FG[chip],0x00, 0x4000);
      memset(RAM_FG[chip],0x00, 0x1000);
   }

   AddLoadCallback(tc0100scn_0_load_update);
}

/******************************************************************************/

void tc0100scn_0_load_update(void)
{
   UINT32 i,j,chip;

   gfx_fg0_dirty_count[0] = 0;
   gfx_fg0_dirty_count[1] = 0;

   for (chip=0; chip<MAX_CHIP; chip++) {
     UINT8 *GFX_PTR = GFX_FG[chip];
     if (GFX_PTR) {
       UINT8 *RAM_PTR = RAM_FG[chip];
       for(i = 0; i < 0x1000; i += 2){
	 j = ReadWord(&RAM_PTR[i]);
	 WriteWord(&RAM_PTR[i], ~j);
	 tc0100scn_0_gfx_fg0_ww(i, j);
       }
     }
   }
}

void tc0100scn_update_gfx_fg0(int chip)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *source;

   UINT8 *GFX_PTR = GFX_FG[chip];
   if (GFX_PTR) {
     for(ta = 0; ta < gfx_fg0_dirty_count[0]; ta++){

       tb = GFX_FG0_DIRTY[chip][ta];
       source = GFX_PTR + (tb << 6);

       td=0;
       te=0;
       for(tc=0;tc<0x40;tc++){
         if(source[tc])
	   td=1;
         else
	   te=1;
       }
       if((td==0)&&(te==1)) GFX_FG0_SOLID[chip][tb]=0;	// All pixels are 0: Don't Draw
       if((td==1)&&(te==1)) GFX_FG0_SOLID[chip][tb]=1;	// Mixed: Draw Trans
       if((td==1)&&(te==0)) GFX_FG0_SOLID[chip][tb]=2;	// All pixels are !0: Draw Solid

     }
     gfx_fg0_dirty_count[chip] = 0;
   }
}

void tc0100scn_gfx_fg0_wb(int chip,UINT32 addr, UINT8 data)
{
   int tb;
   UINT8 *RAM_PTR = RAM_FG[chip];
   UINT8 *GFX_PTR = GFX_FG[chip];

   addr=(addr^1)&0xFFF;

   if((RAM_PTR[addr])!=data){

   // Write to RAM
   // ------------

   RAM_PTR[addr]=data;

   // Write to 8x8 GFX
   // ----------------

   tb=(addr&0xFFE)<<2;

   if (current_game->video->flags & VIDEO_ROTATE_180) {
     if((addr&1)==0){
       GFX_PTR[tb+7] = (GFX_PTR[tb+0]&0x02)|((data&0x80)>>7);
       GFX_PTR[tb+6] = (GFX_PTR[tb+1]&0x02)|((data&0x40)>>6);
       GFX_PTR[tb+5] = (GFX_PTR[tb+2]&0x02)|((data&0x20)>>5);
       GFX_PTR[tb+4] = (GFX_PTR[tb+3]&0x02)|((data&0x10)>>4);
       GFX_PTR[tb+3] = (GFX_PTR[tb+4]&0x02)|((data&0x08)>>3);
       GFX_PTR[tb+2] = (GFX_PTR[tb+5]&0x02)|((data&0x04)>>2);
       GFX_PTR[tb+1] = (GFX_PTR[tb+6]&0x02)|((data&0x02)>>1);
       GFX_PTR[tb+0] = (GFX_PTR[tb+7]&0x02)|((data&0x01)>>0);
     }
     else{
       GFX_PTR[tb+7] = (GFX_PTR[tb+0]&0x01)|((data&0x80)>>6);
       GFX_PTR[tb+6] = (GFX_PTR[tb+1]&0x01)|((data&0x40)>>5);
       GFX_PTR[tb+5] = (GFX_PTR[tb+2]&0x01)|((data&0x20)>>4);
       GFX_PTR[tb+4] = (GFX_PTR[tb+3]&0x01)|((data&0x10)>>3);
       GFX_PTR[tb+3] = (GFX_PTR[tb+4]&0x01)|((data&0x08)>>2);
       GFX_PTR[tb+2] = (GFX_PTR[tb+5]&0x01)|((data&0x04)>>1);
       GFX_PTR[tb+1] = (GFX_PTR[tb+6]&0x01)|((data&0x02)>>0);
       GFX_PTR[tb+0] = (GFX_PTR[tb+7]&0x01)|((data&0x01)<<1);
     }
   } else {
     if((addr&1)==0){
       GFX_PTR[tb+0] = (GFX_PTR[tb+0]&0x02)|((data&0x80)>>7);
       GFX_PTR[tb+1] = (GFX_PTR[tb+1]&0x02)|((data&0x40)>>6);
       GFX_PTR[tb+2] = (GFX_PTR[tb+2]&0x02)|((data&0x20)>>5);
       GFX_PTR[tb+3] = (GFX_PTR[tb+3]&0x02)|((data&0x10)>>4);
       GFX_PTR[tb+4] = (GFX_PTR[tb+4]&0x02)|((data&0x08)>>3);
       GFX_PTR[tb+5] = (GFX_PTR[tb+5]&0x02)|((data&0x04)>>2);
       GFX_PTR[tb+6] = (GFX_PTR[tb+6]&0x02)|((data&0x02)>>1);
       GFX_PTR[tb+7] = (GFX_PTR[tb+7]&0x02)|((data&0x01)>>0);
     }
     else{
       GFX_PTR[tb+0] = (GFX_PTR[tb+0]&0x01)|((data&0x80)>>6);
       GFX_PTR[tb+1] = (GFX_PTR[tb+1]&0x01)|((data&0x40)>>5);
       GFX_PTR[tb+2] = (GFX_PTR[tb+2]&0x01)|((data&0x20)>>4);
       GFX_PTR[tb+3] = (GFX_PTR[tb+3]&0x01)|((data&0x10)>>3);
       GFX_PTR[tb+4] = (GFX_PTR[tb+4]&0x01)|((data&0x08)>>2);
       GFX_PTR[tb+5] = (GFX_PTR[tb+5]&0x01)|((data&0x04)>>1);
       GFX_PTR[tb+6] = (GFX_PTR[tb+6]&0x01)|((data&0x02)>>0);
       GFX_PTR[tb+7] = (GFX_PTR[tb+7]&0x01)|((data&0x01)<<1);
     }
   }
   // request mask update

   tb >>= 6;

   if(GFX_FG0_SOLID[chip][tb] != 3){
      GFX_FG0_SOLID[chip][tb] = 3;
      GFX_FG0_DIRTY[chip][gfx_fg0_dirty_count[0]++] = tb;
   }

   }
}

void tc0100scn_0_gfx_fg0_wb(UINT32 addr, UINT8 data)
{
   tc0100scn_gfx_fg0_wb(0, addr, data);
}

void tc0100scn_1_gfx_fg0_wb(UINT32 addr, UINT8 data)
{
   tc0100scn_gfx_fg0_wb(1, addr, data);
}

void tc0100scn_gfx_fg0_ww(int chip, UINT32 addr, UINT16 data)
{
  int rotation = (current_game->video->flags & 3);
  UINT8 *RAM_PTR = RAM_FG[chip];
  UINT8 *GFX_PTR = GFX_FG[chip];
   addr&=0xFFE;

   if(ReadWord(&RAM_PTR[addr])!=data){

   // Write to RAM
   // ------------

   WriteWord(&RAM_PTR[addr],data);

   // Write to 8x8 GFX
   // ----------------

   addr=addr<<2;

   if (rotation == VIDEO_ROTATE_180) {
     // fprintf(stderr,"ww 180\n");
     addr ^= 0x38;
     GFX_PTR[addr+7] = ((data&0x8000)>>14)|((data&0x0080)>>7);
     GFX_PTR[addr+6] = ((data&0x4000)>>13)|((data&0x0040)>>6);
     GFX_PTR[addr+5] = ((data&0x2000)>>12)|((data&0x0020)>>5);
     GFX_PTR[addr+4] = ((data&0x1000)>>11)|((data&0x0010)>>4);
     GFX_PTR[addr+3] = ((data&0x0800)>>10)|((data&0x0008)>>3);
     GFX_PTR[addr+2] = ((data&0x0400)>> 9)|((data&0x0004)>>2);
     GFX_PTR[addr+1] = ((data&0x0200)>> 8)|((data&0x0002)>>1);
     GFX_PTR[addr+0] = ((data&0x0100)>> 7)|((data&0x0001)>>0);
   } else if (rotation == VIDEO_ROTATE_270) {
     int y = (addr & 0x38)>>3;
     addr = (addr & 0xffc0);
     addr = addr + y;
     GFX_PTR[addr+56] = ((data&0x8000)>>14)|((data&0x0080)>>7);
     GFX_PTR[addr+48] = ((data&0x4000)>>13)|((data&0x0040)>>6);
     GFX_PTR[addr+40] = ((data&0x2000)>>12)|((data&0x0020)>>5);
     GFX_PTR[addr+32] = ((data&0x1000)>>11)|((data&0x0010)>>4);
     GFX_PTR[addr+24] = ((data&0x0800)>>10)|((data&0x0008)>>3);
     GFX_PTR[addr+16] = ((data&0x0400)>> 9)|((data&0x0004)>>2);
     GFX_PTR[addr+8] = ((data&0x0200)>> 8)|((data&0x0002)>>1);
     GFX_PTR[addr+0] = ((data&0x0100)>> 7)|((data&0x0001)>>0);
   } else {
     GFX_PTR[addr+0] = ((data&0x8000)>>14)|((data&0x0080)>>7);
     GFX_PTR[addr+1] = ((data&0x4000)>>13)|((data&0x0040)>>6);
     GFX_PTR[addr+2] = ((data&0x2000)>>12)|((data&0x0020)>>5);
     GFX_PTR[addr+3] = ((data&0x1000)>>11)|((data&0x0010)>>4);
     GFX_PTR[addr+4] = ((data&0x0800)>>10)|((data&0x0008)>>3);
     GFX_PTR[addr+5] = ((data&0x0400)>> 9)|((data&0x0004)>>2);
     GFX_PTR[addr+6] = ((data&0x0200)>> 8)|((data&0x0002)>>1);
     GFX_PTR[addr+7] = ((data&0x0100)>> 7)|((data&0x0001)>>0);
   }
   // request mask update

   addr >>= 6;

   if(GFX_FG0_SOLID[chip][addr] != 3){
      GFX_FG0_SOLID[chip][addr] = 3;
      GFX_FG0_DIRTY[chip][gfx_fg0_dirty_count[chip]++] = addr;
   }

   }
}

void tc0100scn_0_gfx_fg0_ww(UINT32 addr, UINT16 data) {
   tc0100scn_gfx_fg0_ww(0, addr, data);
}

void tc0100scn_1_gfx_fg0_ww(UINT32 addr, UINT16 data) {
   tc0100scn_gfx_fg0_ww(1, addr, data);
}

void tc0100scn_0_copy_gfx_fg0(UINT8 *src, UINT32 size)
{
   UINT32 i;

   for(i=0; i<size; i+=2){
      tc0100scn_0_gfx_fg0_ww(i, (UINT16) (ReadWord68k(&src[i])) );
   }
}


void tc0100scn_1_copy_gfx_fg0(UINT8 *src, UINT32 size)
{
   UINT32 i;

   for(i=0; i<size; i+=2){
      tc0100scn_1_gfx_fg0_ww(i, (UINT16) (ReadWord68k(&src[i])) );
   }
}

/******************************************************************************/

#undef  RAM_PTR
#undef  GFX_PTR
#define RAM_PTR		RAM_FG[0]
#define GFX_PTR		GFX_FG[0]

void tc0100scn_0_gfx_fg0_wb_r270(UINT32 addr, UINT8 data)
{
   int tb;

   addr=(addr^1)&0xFFF;

   if((RAM_PTR[addr])!=data){

   // Write to RAM
   // ------------

   RAM_PTR[addr]=data;

   // Write to 8x8 GFX
   // ----------------

   tb=((addr&0xFF0)<<2)|((addr&0x0E)>>1);

   if((addr&1)==0){
      GFX_PTR[tb+0x00] = (GFX_PTR[tb+0x00]&0x02)|((data&0x01)>>0);
      GFX_PTR[tb+0x08] = (GFX_PTR[tb+0x08]&0x02)|((data&0x02)>>1);
      GFX_PTR[tb+0x10] = (GFX_PTR[tb+0x10]&0x02)|((data&0x04)>>2);
      GFX_PTR[tb+0x18] = (GFX_PTR[tb+0x18]&0x02)|((data&0x08)>>3);
      GFX_PTR[tb+0x20] = (GFX_PTR[tb+0x20]&0x02)|((data&0x10)>>4);
      GFX_PTR[tb+0x28] = (GFX_PTR[tb+0x28]&0x02)|((data&0x20)>>5);
      GFX_PTR[tb+0x30] = (GFX_PTR[tb+0x30]&0x02)|((data&0x40)>>6);
      GFX_PTR[tb+0x38] = (GFX_PTR[tb+0x38]&0x02)|((data&0x80)>>7);
   }
   else{
      GFX_PTR[tb+0x00] = (GFX_PTR[tb+0x00]&0x01)|((data&0x01)<<1);
      GFX_PTR[tb+0x08] = (GFX_PTR[tb+0x08]&0x01)|((data&0x02)>>0);
      GFX_PTR[tb+0x10] = (GFX_PTR[tb+0x10]&0x01)|((data&0x04)>>1);
      GFX_PTR[tb+0x18] = (GFX_PTR[tb+0x18]&0x01)|((data&0x08)>>2);
      GFX_PTR[tb+0x20] = (GFX_PTR[tb+0x20]&0x01)|((data&0x10)>>3);
      GFX_PTR[tb+0x28] = (GFX_PTR[tb+0x28]&0x01)|((data&0x20)>>4);
      GFX_PTR[tb+0x30] = (GFX_PTR[tb+0x30]&0x01)|((data&0x40)>>5);
      GFX_PTR[tb+0x38] = (GFX_PTR[tb+0x38]&0x01)|((data&0x80)>>6);
   }

   }
}

void tc0100scn_0_gfx_fg0_ww_r270(UINT32 addr, UINT16 data)
{
   int tb;

   addr&=0xFFE;

   if(ReadWord(&RAM_PTR[addr])!=data){

   // Write to RAM
   // ------------

   WriteWord(&RAM_PTR[addr],data);

   // Write to 8x8 GFX
   // ----------------

   tb=((addr&0xFF0)<<2)|((addr&0x0E)>>1);

   GFX_PTR[tb+0x00] = ((data&0x0100)>> 7)|((data&0x0001)>>0);
   GFX_PTR[tb+0x08] = ((data&0x0200)>> 8)|((data&0x0002)>>1);
   GFX_PTR[tb+0x10] = ((data&0x0400)>> 9)|((data&0x0004)>>2);
   GFX_PTR[tb+0x18] = ((data&0x0800)>>10)|((data&0x0008)>>3);
   GFX_PTR[tb+0x20] = ((data&0x1000)>>11)|((data&0x0010)>>4);
   GFX_PTR[tb+0x28] = ((data&0x2000)>>12)|((data&0x0020)>>5);
   GFX_PTR[tb+0x30] = ((data&0x4000)>>13)|((data&0x0040)>>6);
   GFX_PTR[tb+0x38] = ((data&0x8000)>>14)|((data&0x0080)>>7);

   }
}

void tc0100scn_0_copy_gfx_fg0_r270(UINT8 *src, UINT32 size)
{
   UINT32 i;

   for(i=0; i<size; i+=2){
      tc0100scn_0_gfx_fg0_ww_r270(i, (UINT16) (ReadWord68k(&src[i])) );
   }
}

/******************************************************************************/


