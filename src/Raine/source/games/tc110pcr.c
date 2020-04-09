/******************************************************************************/
/*                                                                            */
/*                    tc0110pcr: TAITO COLOUR RAM PORT                        */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc110pcr.h"

/*

'tc0110pcr' is only a guess at the chip name. pcr could stand for port colour
ram, but it could stand for something else (maybe priority control ram).

*/

static UINT16 F2_Colpos;
static UINT8 *F2_RAM_PAL;
static UINT8 F2_Colmode;
static UINT16 F2_Colpos_add;

void tc0110pcr_init(UINT8 *src, UINT8 colmode)
{
   F2_RAM_PAL = src;
   F2_Colpos  = 0;
   F2_Colmode = colmode;
   F2_Colpos_add = 2;		/* default size */
}

void tc0110pcr_init_typeb(UINT8 *src, UINT8 colmode, UINT16 add )
{
   F2_RAM_PAL = src;
   F2_Colpos  = 0;
   F2_Colmode = colmode;
   F2_Colpos_add = add;
}

void tc0110pcr_ww(UINT32 address, UINT16 data)
{
   address&=7;

   if(address==0){
      F2_Colpos = (data<<F2_Colmode)&0x1FFE;
      return;
   }
   if(address==2){
      WriteWord(&F2_RAM_PAL[F2_Colpos], data);
      F2_Colpos = (F2_Colpos+F2_Colpos_add)&0x1FFE;
      return;
   }
   if(address==4){
      F2_Colpos = 0;
      //print_debug( "in:%04x\n", data );
      return;
   }
}

UINT16 tc0110pcr_rw(UINT32 address)
{
   UINT16 ta;

   address&=7;

   if(address==0){
      return(F2_Colpos>>F2_Colmode);
   }
   if(address==2){
      ta = ReadWord(&F2_RAM_PAL[F2_Colpos]);
      F2_Colpos = (F2_Colpos+F2_Colpos_add)&0x1FFE;
      return(ta);
   }
   return 0;
}

// Second Copy (Dual Screen games)

static UINT16 F2_Colpos_2;
static UINT8 *F2_RAM_PAL_2;
static UINT8 F2_Colmode_2;
static UINT16 F2_Colpos_add_2;

void tc0110pcr_init_2(UINT8 *src, UINT8 colmode)
{
   F2_RAM_PAL_2 = src;
   F2_Colpos_2  = 0;
   F2_Colmode_2 = colmode;
   F2_Colpos_add_2 = 2;		/* default size */
}

void tc0110pcr_init_typeb_2(UINT8 *src, UINT8 colmode, UINT16 add)
{
   F2_RAM_PAL_2 = src;
   F2_Colpos_2  = 0;
   F2_Colmode_2 = colmode;
   F2_Colpos_add_2 = add;
}

void tc0110pcr_ww_2(UINT32 address, UINT16 data)
{
   address&=7;

   if(address==0){
      F2_Colpos_2 = (data<<F2_Colmode_2)&0x1FFE;
      return;
   }
   if(address==2){
      WriteWord(&F2_RAM_PAL_2[F2_Colpos_2], data);
      F2_Colpos_2 = (F2_Colpos_2+F2_Colpos_add_2)&0x1FFE;
      return;
   }
   if(address==4){
      F2_Colpos_2 = 0;
      return;
   }
}

UINT16 tc0110pcr_rw_2(UINT32 address)
{
   UINT16 ta;

   address&=7;

   if(address==0){
      return(F2_Colpos_2>>F2_Colmode_2);
   }
   if(address==2){
      ta = ReadWord(&F2_RAM_PAL_2[F2_Colpos_2]);
      F2_Colpos_2 = (F2_Colpos_2+F2_Colpos_add_2)&0x1FFE;
      return(ta);
   }
   return 0;
}

// Third Copy (Triple Screen games)

static UINT16 F2_Colpos_3;
static UINT8 *F2_RAM_PAL_3;
static UINT8 F2_Colmode_3;
static UINT16 F2_Colpos_add_3;

void tc0110pcr_init_3(UINT8 *src, UINT8 colmode)
{
   F2_RAM_PAL_3 = src;
   F2_Colpos_3  = 0;
   F2_Colmode_3 = colmode;
   F2_Colpos_add_3 = 2;		/* default size */
}

void tc0110pcr_init_typeb_3(UINT8 *src, UINT8 colmode, UINT16 add)
{
   F2_RAM_PAL_3 = src;
   F2_Colpos_3  = 0;
   F2_Colmode_3 = colmode;
   F2_Colpos_add_3 = add;
}

void tc0110pcr_ww_3(UINT32 address, UINT16 data)
{
   address&=7;

   if(address==0){
      F2_Colpos_3 = (data<<F2_Colmode_3)&0x1FFE;
      return;
   }
   if(address==2){
      WriteWord(&F2_RAM_PAL_3[F2_Colpos_3], data);
      F2_Colpos_3 = (F2_Colpos_3+F2_Colpos_add_3)&0x1FFE;
      return;
   }
   if(address==4){
      F2_Colpos_3 = 0;
      return;
   }
}

UINT16 tc0110pcr_rw_3(UINT32 address)
{
   UINT16 ta;

   address&=7;

   if(address==0){
      return(F2_Colpos_3>>F2_Colmode_3);
   }
   if(address==2){
      ta = ReadWord(&F2_RAM_PAL_3[F2_Colpos_3]);
      F2_Colpos_3 = (F2_Colpos_3+F2_Colpos_add_3)&0x1FFE;
      return(ta);
   }
   return 0;
}

