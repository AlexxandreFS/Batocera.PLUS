/******************************************************************************/
/*                                                                            */
/*   tc0140syt: TAITO MAIN TO SOUND CPU COMMUNICATION (68000-Z80; Z80-Z80)    */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "tc140syt.h"
#include "cpumain.h"

#if 0

#define SYT_PORT01_FULL         (0x01)
#define SYT_PORT23_FULL         (0x02)
#define SYT_SET_OK              (0x04)
#define SYT_PORT01_FULL_S       SYT_PORT01_FULL
#define SYT_PORT23_FULL_S       SYT_PORT23_FULL

#else

#define SYT_PORT01_FULL         (0x01)
#define SYT_PORT23_FULL         (0x02)
#define SYT_SET_OK              (0x00)
#define SYT_PORT01_FULL_S       (0x04)
#define SYT_PORT23_FULL_S       (0x08)

#endif

typedef struct TC0140SYT                        // Information about 1 chip
{
   UINT8 port_data[4];                          // Data on port (4 nibbles)
   UINT8 main_mode;                             // Access mode on main cpu side
   UINT8 sub_mode;                              // Access mode on sub cpu side
   UINT8 status;                                // Status read data
   UINT8 sub_nmi;                               // 1 if sub cpu has nmi's enabled
   UINT8 sub_want_nmi;                          // 1 if sub cpu has a pending nmi
} TC0140SYT;

struct TC0140SYT tc0140syt;                     // Support just one chip for now

/******************************************************************************/

void tc0140syt_reset(void)
{
   memset(&tc0140syt,0x00,sizeof(TC0140SYT));
   tc0140syt.main_mode = 0xFF;
   tc0140syt.sub_mode = 0xFF;
}

UINT8 tc0140syt_get_port01(void)
{
   return ((tc0140syt.port_data[1]&0x0F)<<4)|(tc0140syt.port_data[0]&0x0F);
}

UINT8 tc0140syt_get_port23(void)
{
   return ((tc0140syt.port_data[2]&0x0F)<<4)|(tc0140syt.port_data[3]&0x0F);
}

UINT8 tc0140syt_want_nmi(void)
{
   int ret;

   ret = tc0140syt.sub_want_nmi;
   tc0140syt.sub_want_nmi = 0;
   return ret;
}

/******************************************************************************/

void tc0140syt_write_main_68k(UINT32 offset, UINT8 data)
{
   data &= 15;
   if((offset&2)==0){
      tc0140syt.main_mode=data;
/* #ifdef RAINE_DEBUG */
/*       if(tc0140syt.main_mode>4) print_debug("tc0140syt error: 68000 Entering Unknown Mode[%02x]\n",tc0140syt.main_mode); */
/* #endif */
   }
   else{
      switch(tc0140syt.main_mode){

         // [Nibble#0]

         case 0x00:
            tc0140syt.port_data[tc0140syt.main_mode++]=data;
         break;

         // [Nibble#1]

         case 0x01:
            tc0140syt.port_data[tc0140syt.main_mode++]=data;
            if(tc0140syt.status & SYT_PORT01_FULL){
/* #ifdef RAINE_DEBUG */
/*                //print_ingame(120,"68000 Sends 0/1 before port is clear!"); */
/*                print_debug("tc0140syt error: 68000 Sends 0/1 before port is clear!\n"); */
/* #endif */
            }
            tc0140syt.status |= SYT_PORT01_FULL;
            if(tc0140syt.sub_nmi!=0) tc0140syt.sub_want_nmi = 1;
            print_debug("Main CPU sends 0/1:%01x%01x\n",tc0140syt.port_data[1],tc0140syt.port_data[0]);
         break;

         // [Nibble#2]

         case 0x02:
            tc0140syt.port_data[tc0140syt.main_mode++]=data;
         break;

         // [Nibble#3]

         case 0x03:
            tc0140syt.port_data[tc0140syt.main_mode++]=data;
            if(tc0140syt.status & SYT_PORT23_FULL){
/* #ifdef RAINE_DEBUG */
/*                //print_ingame(120,"68000 Sends 2/3 before port is clear!"); */
/*                print_debug("tc0140syt error: 68000 Sends 2/3 before port is clear!\n"); */
/* #endif */
            }
            tc0140syt.status |= SYT_PORT23_FULL;
            if(tc0140syt.sub_nmi!=0) tc0140syt.sub_want_nmi = 1;
            print_debug("Main CPU sends 2/3:%01x%01x\n",tc0140syt.port_data[3],tc0140syt.port_data[2]);
         break;

         // [Port Status]

         case 0x04:
            tc0140syt.status = SYT_SET_OK;
         break;

         // [Data Error]

         default:
/*             print_debug("tc0140syt error: 68000 Write Data in Mode[%02x] Data[%02x]\n",tc0140syt.main_mode,data); */
         break;
      }
   }
}

UINT8 tc0140syt_read_main_68k(UINT32 offset)
{
   static int tog=0;

   if((offset&2)==0){
/*       print_debug("tc0140syt error: Main CPU read control port\n"); */
      // tog^=0xFF;
      return 0; // (tog);
   }
   else{
      switch(tc0140syt.main_mode){

         // [Nibble#0]

         case 0x00:
	   print_debug("main cpu reads (0) data at %d (%d)\n",tc0140syt.main_mode,tc0140syt.port_data[tc0140syt.main_mode+1]);
            return tc0140syt.port_data[tc0140syt.main_mode++];
         break;

         // [Nibble#1]

         case 0x01:
/*             print_debug("Main CPU receives 0/1:%01x%01x\n",tc0140syt.port_data[1],tc0140syt.port_data[0]); */
            tc0140syt.status &= ~SYT_PORT01_FULL_S;
            return tc0140syt.port_data[tc0140syt.main_mode++];
         break;

         // [Nibble#2]

         case 0x02:
/* 	   print_debug("main cpu reads data at %d (%d)\n",tc0140syt.main_mode,tc0140syt.port_data[tc0140syt.main_mode++]); */
            return tc0140syt.port_data[tc0140syt.main_mode++];
         break;

         // [Nibble#3]

         case 0x03:
/*             print_debug("Main CPU receives 2/3:%01x%01x\n",tc0140syt.port_data[3],tc0140syt.port_data[2]); */
            tc0140syt.status &= ~SYT_PORT23_FULL_S;
            return tc0140syt.port_data[tc0140syt.main_mode++];
         break;

         // [Port Status]

         case 0x04:
/*             print_debug("Main CPU read status:%02x\n",tc0140syt.status); */
            return tc0140syt.status;
         break;

         // [Data Error]

         default:
/*             print_debug("tc0140syt error: 68000 Read Data in Mode[%02x]\n",tc0140syt.main_mode); */
            tog^=0xFF;
            return(tog);
         break;
      }
   }
}

/******************************************************************************/

void tc0140syt_write_main_z80(UINT16 offset, UINT8 data)
{
   tc0140syt_write_main_68k( (offset&1)<<1, data );
}

UINT8 tc0140syt_read_main_z80(UINT16 offset)
{
   return tc0140syt_read_main_68k( (offset&1)<<1 );
}

/******************************************************************************/

void tc0140syt_write_sub_z80(UINT16 offset, UINT8 data)
{
   if((offset&1)==0){
      tc0140syt.sub_mode=data;
/* #ifdef RAINE_DEBUG */
/*       if(tc0140syt.sub_mode>6) print_debug("tc0140syt error: Sub CPU unknown mode[%02x]\n",tc0140syt.sub_mode); */
/* #endif */
   }
   else{
      switch(tc0140syt.sub_mode){

         // [Nibble#0]

         case 0x00:
            tc0140syt.port_data[tc0140syt.sub_mode++]=data&15;
         break;

         // [Nibble#1]

         case 0x01:
            tc0140syt.port_data[tc0140syt.sub_mode++]=data&15;
            tc0140syt.status |= SYT_PORT01_FULL_S;
/*             print_debug("Sub CPU sends 0/1:%01x%01x\n",tc0140syt.port_data[1],tc0140syt.port_data[0]); */
         break;

         // [Nibble#2]

         case 0x02:
            tc0140syt.port_data[tc0140syt.sub_mode++]=data&15;
         break;

         // [Nibble#3]

         case 0x03:
            tc0140syt.port_data[tc0140syt.sub_mode++]=data&15;
            tc0140syt.status |= SYT_PORT23_FULL_S;
/*             print_debug("Sub CPU sends 2/3:%01x%01x\n",tc0140syt.port_data[3],tc0140syt.port_data[2]); */
         break;

         // [Port Status]

         case 0x04:
            tc0140syt.status = SYT_SET_OK;
         break;

         // [NMI Disable]

         case 0x05:
            tc0140syt.sub_nmi = 0;
         break;

         // [NMI Enable]

         case 0x06:
            tc0140syt.sub_nmi = 1;
         break;

         // [Data Error]

         default:
/*             print_debug("tc0140syt error: Sub CPU write in mode[%02x] data[%02x]\n",tc0140syt.sub_mode,data); */
         break;
      }
   }
}

UINT8 tc0140syt_read_sub_z80(UINT16 offset)
{
   static int tog=0;
   UINT8 res;

   if((offset&1)==0){
/*       print_debug("tc0140syt error: Sub CPU read control port\n"); */
      // tog^=0xFF;
      return 0; //tog;
   }
   else{
      switch(tc0140syt.sub_mode){

         // [Nibble#0]

         case 0x00:
            res=tc0140syt.port_data[tc0140syt.sub_mode++];
         break;

         // [Nibble#1]

         case 0x01:
/*             print_debug("Sub CPU receives 0/1:%01x%01x\n",tc0140syt.port_data[1],tc0140syt.port_data[0]); */
            tc0140syt.status &= ~SYT_PORT01_FULL;
            //tc0140syt.sub_want_nmi = 0;
            res=tc0140syt.port_data[tc0140syt.sub_mode++];
         break;

         // [Nibble#2]

         case 0x02:
            res=tc0140syt.port_data[tc0140syt.sub_mode++];
         break;

         // [Nibble#3]

         case 0x03:
/*             print_debug("Sub CPU receives 2/3:%01x%01x\n",tc0140syt.port_data[3],tc0140syt.port_data[2]); */
            tc0140syt.status &= ~SYT_PORT23_FULL;
            //tc0140syt.sub_want_nmi = 0;
            res=tc0140syt.port_data[tc0140syt.sub_mode++];
         break;

         // [Port Status]

         case 0x04:
            /*#ifdef RAINE_DEBUG
            print_debug("Sub CPU read status:%02x\n",tc0140syt.status);
#endif*/
            res=tc0140syt.status;
         break;

         // [Data Error]

         default:
/*             print_debug("tc0140syt error: Sub CPU read in mode[%02x]\n",tc0140syt.sub_mode); */
            tog^=0xFF;
            return tog;
         break;
      }
   }
   return res;
}

/******************************************************************************/


