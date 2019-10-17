/******************************************************************************/
/*                                                                            */
/*      tc0220ioc: TAITO INPUT/OUTPUT CONTROL CHIP (F2 SYSTEM, B SYSTEM)      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc220ioc.h"

/*

tc0220ioc conversions:

Ashura Blaster     - OK
Asuka & Asuka      - OK [Reads LED status bits 2&3]
Battle Shark       - OK
Cadash             - OK
Camel Try          - OK
Champion Wrestler  - ?
Chase HQ           - OK
Chase HQ 2         - OK
Continental Circus - OK
Crime City         - OK
Dinorex            - ?
Don Doko Don       - OK
Drift Out          - OK
Dynamite League    - ?
Earth Joker        - OK [Writes to 0x0A and 0x0C]
Final Blow         - OK
Gun Frontier       - OK ['Byte' swapped]
Hit the Ice        - OK
Liquid Kids        - OK
Master of Weapons  - OK [Port access]
Maze of Flott      - OK [Writes to 0x0A and 0x0C]
Mega Blast         - OK
Metal Black        - OK ['Byte' swapped]
Night Striker      - OK
Operation Thunder  - ?
Pulirula           - OK
Raimais            - OK
Rambo 3            - OK
Rastan 2           - OK
Record Breaker     - OK [Port access]
Silent Dragon      - OK [Coin B never alight]
Space Gun          - ?
Super Space Inv    - OK
Taito Tetris       - OK
Thunder Fox        - OK
Top Speed          - OK
Violence Fight     - OK
Warrior Blade      - ?

Air Inferno        - NO
American Horseshoe - NO [Input on ym2203]
Aqua Jack          - OK [Not mapped]
Arkanoid 2         - NO [Input on m-chip]
Bonze Adventure    - OK [Input on c-chip]
Darius             - NO
Darius 2           - OK
Dead Connection    - NO [4 Player IO chip]
Euro Champ         - NO [4 Player IO chip]
Football Champ     - NO [4 Player IO chip]
Growl              - NO [4 Player IO chip]
Insector X         - NO [Input on m-chip]
Ninja Kids         - NO [4 Player IO chip]
Ninja Warriors     - OK
Operation Wolf     - NO [Input on c-chip]
Operation Wolf 3   - NO
Plotting           - NO [Input on ym2203]
Rainbow Islands    - OK [Input on c-chip]
Rastan             - NO
Space Invaders DX  - NO [F3-System IO chip]
Superman           - OK [Input on c-chip; seems not 100% right]
Syvalion           - OK
Top Landing        - NO
New Zealand Story  - NO [Input on m-chip]
Volfied            - NO [Input on c-chip]

- All F3-System games have leds on a generic chip

*/

/*

Ashura Blaster
Crime City
Master of Weapons
Rambo 3
Rastan Saga 2

*/

struct INPUT_INFO b_system_inputs[] =
{
   INP0( COIN1, 0x00000E, 0x04 ),
   INP0( COIN2, 0x00000E, 0x08 ),
   INP0( TILT, 0x00000E, 0x01 ),
   INP0( SERVICE, 0x00000E, 0x02 ),

   INP0( P1_START, 0x00000E, 0x40 ),
   INP0( P1_UP, 0x000004, 0x01 ),
   INP0( P1_DOWN, 0x000004, 0x02 ),
   INP0( P1_LEFT, 0x000004, 0x04 ),
   INP0( P1_RIGHT, 0x000004, 0x08 ),
   INP0( P1_B1, 0x000004, 0x20 ),
   INP0( P1_B2, 0x000004, 0x10 ),

   INP0( P2_START, 0x00000E, 0x80 ),
   INP0( P2_UP, 0x000006, 0x01 ),
   INP0( P2_DOWN, 0x000006, 0x02 ),
   INP0( P2_LEFT, 0x000006, 0x04 ),
   INP0( P2_RIGHT, 0x000006, 0x08 ),
   INP0( P2_B1, 0x000006, 0x20 ),
   INP0( P2_B2, 0x000006, 0x10 ),

   END_INPUT
};

/*

Violence Fight

*/

struct INPUT_INFO b_system_inputs_3_button[] =
{
   INP0( COIN1, 0x00000E, 0x04 ),
   INP0( COIN2, 0x00000E, 0x08 ),
   INP0( TILT, 0x00000E, 0x01 ),
   INP0( SERVICE, 0x00000E, 0x02 ),

   INP0( P1_START, 0x00000E, 0x40 ),
   INP0( P1_UP, 0x000004, 0x01 ),
   INP0( P1_DOWN, 0x000004, 0x02 ),
   INP0( P1_LEFT, 0x000004, 0x04 ),
   INP0( P1_RIGHT, 0x000004, 0x08 ),
   INP0( P1_B1, 0x000004, 0x40 ),
   INP0( P1_B2, 0x000004, 0x20 ),
   INP0( P1_B3, 0x000004, 0x10 ),

   INP0( P2_START, 0x00000E, 0x80 ),
   INP0( P2_UP, 0x000006, 0x01 ),
   INP0( P2_DOWN, 0x000006, 0x02 ),
   INP0( P2_LEFT, 0x000006, 0x04 ),
   INP0( P2_RIGHT, 0x000006, 0x08 ),
   INP0( P2_B1, 0x000006, 0x40 ),
   INP0( P2_B2, 0x000006, 0x20 ),
   INP0( P2_B3, 0x000006, 0x10 ),

   END_INPUT
};

static UINT8 reset_data[0x10] =
{
   0xFF,		// 0x00: DSW A
   0xFF,		// 0x02: DSW B
   0xFF,		// 0x04: Player 1
   0xFF,		// 0x06: Player 2
   0x00,		// 0x08: LED; Paddle Acknowledge
   0xFF,		// 0x0A: ?
   0xFF,		// 0x0C: ?
   0xFF,		// 0x0E: Coins, Tilt, Service
   0x00,
   0x00,
   0x00,
   0x00,
   0x00,		// 0x18: Player 1 Analogue (Camel Try, Drift Out)
   0x00,		// 0x1A: Player 1 Analogue (Drift Out)
   0x00,		// 0x1C: Player 2 Analogue (Camel Try)
   0x00,		// 0x1E: Player 2 Analogue
};

void reset_tc0220ioc(void)
{
   int ta;

   for(ta=0;ta<0x10;ta++){
      tc0220ioc.RAM[(ta<<1)+0]=reset_data[ta];
      tc0220ioc.RAM[(ta<<1)+1]=reset_data[ta];
   }
}

void tc0220ioc_wb(UINT32 address, UINT8 data)
{
   switch(address&0x1E){
      case 0x00:			    	// [Frame Sync]
         if(tc0220ioc.ctrl & TC0220_STOPCPU){
            Stop68000(address,data);
         }
      break;
      case 0x08:				// [Lights and Paddle Acknowledge]
	print_debug("tc220ioc: ram_input 8 = %x [%x]\n",data,s68000context.pc);
         tc0220ioc.RAM[0x08] = data;
         switch_led(0,(data>>2)&1);		// Coin A [Coin Inserted]
         switch_led(1,(data>>3)&1);		// Coin B [Coin Inserted]
         switch_led(2,(data>>0)&1);		// Coin A [Ready for coins]
         //switch_led(3,(data>>1)&1);		// Coin B [Ready for coins]
      break;
      default:
#ifdef RAINE_DEBUG
         if(!(tc0220ioc.ctrl & TC0220_QUIET)){
            print_debug("tc0220ioc_wb(%02x,%02x) [%06x]\n",address&0x1E,data,s68000context.pc);
         }
#endif
      break;
   }
}

void tc0220ioc_ww(UINT32 address, UINT16 data)
{
   tc0220ioc_wb(address, (UINT8) (data&0xFF) );
}

UINT8 tc0220ioc_rb(UINT32 address)
{
   return tc0220ioc.RAM[address&0x1E];
}

UINT16 tc0220ioc_rw(UINT32 address)
{
   return ((tc0220ioc.RAM[address&0x1E]<<8) | (tc0220ioc.RAM[address&0x1E]));
}

/******************************************************************************/

void tc0220ioc_wb_bswap(UINT32 address, UINT8 data)
{
   tc0220ioc_wb(address^2, (UINT8) (data&0xFF) );
}

void tc0220ioc_ww_bswap(UINT32 address, UINT16 data)
{
   tc0220ioc_wb(address^2, (UINT8) (data&0xFF) );
}

UINT8 tc0220ioc_rb_bswap(UINT32 address)
{
   return tc0220ioc.RAM[(address&0x1E)^2];
}

UINT16 tc0220ioc_rw_bswap(UINT32 address)
{
   return ((tc0220ioc.RAM[(address&0x1E)^2]<<8) | (tc0220ioc.RAM[(address&0x1E)^2]));
}

/******************************************************************************/

static UINT8 port_offset;

void tc0220ioc_wb_port(UINT32 address, UINT8 data)
{
   if(!(address&2)){
      tc0220ioc_wb(port_offset<<1, data);
   }
   else{
      port_offset = data&0x0F;
   }
}

void tc0220ioc_ww_port(UINT32 address, UINT16 data)
{
   tc0220ioc_wb_port(address, (UINT8) (data&0xFF) );
}

UINT8 tc0220ioc_rb_port(UINT32 address)
{
   if(!(address&2)){
      return tc0220ioc_rb(port_offset<<1);
   }
   else{
      return port_offset;
   }
}

UINT16 tc0220ioc_rw_port(UINT32 address)
{
   return ((tc0220ioc_rb_port(address)<<8) | (tc0220ioc_rb_port(address)));
}

/******************************************************************************/

//static UINT8 port_offset_z80;

void tc0220ioc_wb_z80_port(UINT16 address, UINT8 data)
{
   if(!(address&1)){
      tc0220ioc_wb(port_offset<<1, data);
   }
   else{
      port_offset = data&0x0F;
   }
}

UINT8 tc0220ioc_rb_z80_port(UINT16 address)
{
   if(!(address&1)){
      return tc0220ioc_rb(port_offset<<1);
   }
   else{
      return port_offset;
   }
}

/******************************************************************************/

void tc0220ioc_wb_z80(UINT16 address, UINT8 data)
{
   tc0220ioc_wb(address<<1, data);
}

UINT8 tc0220ioc_rb_z80(UINT16 address)
{
   return tc0220ioc_rb(address<<1);
}

/******************************************************************************/
