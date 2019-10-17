/******************************************************************************/
/*                                                                            */
/*                 TAITO K-SYSTEM (C) 1986 TAITO CORPORATION                  */
/*                                                                            */
/*                           Z80+Z80+YM2203+M68705                            */
/*                  NOTE: K-SYSTEM is not the official name.                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "sasound.h"		// sample support routines
#include "emumain.h"
#include "blit.h" // clear_game_screen

/*

Z80 x 2

M68705 x 1

YM2203 x 1

TC0010VCU x 1

*/

/*

changes/kayamon:
15/2/00:
   - fixed Kick&Run at last, now it works properly =)
   - undid antiriad's amazing F018 bullshit ;-)
     now it works again, assuming MZ80 has been fixed.
     NOTE: it's what we in the trade technically call a 'WATCHDOG'... :P
   - renamed kickrun to kicknrun for general MAME compatibilty
30/8/99:
   - added Knight Boy, dunno if it was worth it though.

   - NOTE: MCU is tested for KKK, seems to be 100%, so any problems are
           most likely due to the rest of the hardware instead.
   - rewrote video h/w, based on Bubble Bobble.
   - *** KICK&RUN not tested at all!!!!!!!!!!!
         Not one bit. DIPs are wrong, etc
         (probably doesn't work at all) ***
   - MEXICO86 needs adding here too...
   - had a go at that SOLID_MASK type stuff, hope it's right.
   - added some more DIPs and stuff.
   - overclocked main CPU, to avoid MZ80 IFF1 bug.
     NOTE: I think the latest MZ80 fixes this itself.
   - renamed driver to K-SYSTEM.
   - added proper MCU emulation (hah, yeah right).
   - fiddled DIPs/inputs about to work.

changes/antiriad:

 - redid the speed hack, so they actually work ;). also hooked up F018 as
   an interrupt request. it's probably some kind of vsync/waitvbl request.
 - increased the cpu slices, because the main cpu was spending a lot of
   time waiting for the sub cpu. i also put the main cpu back to 8mhz, I
   can't see any problem yet, probably the use of F018 now prevents the
   bug showing up (mz80 3.0 will fix iff1 bugs anyway).
 - bank switching without memcpy :).
 - fiddle with the gfx but didn't fix anything (monster priority is wrong,
   if you render everything in reverse, the monsters are right, but not
   much else).

*/


static struct ROM_INFO rom_kicknrun[] =
{
   {   "a87-02.bin", 0x00008000, 0x64f1a85f, 0, 0, 0, },
   {   "a87-03.bin", 0x00010000, 0xf42e8a88, 0, 0, 0, },
   {   "a87-04.bin", 0x00008000, 0x8b438d20, 0, 0, 0, },
   {   "a87-05.bin", 0x00010000, 0x4eee3a8a, 0, 0, 0, },
   {   "a87-06.bin", 0x00008000, 0x1625b587, 0, 0, 0, },
   {   "a87-07.bin", 0x00010000, 0x6cb6ebfe, 0, 0, 0, },
   {   "a87-08.bin", 0x00010000, 0x715e1b04, 0, 0, 0, },
   {   "a87-10.bin", 0x00000100, 0xbe6eb1f0, 0, 0, 0, },
   {   "a87-11.bin", 0x00000100, 0x14f6c28d, 0, 0, 0, },
   {   "a87-12.bin", 0x00000100, 0x3e953444, 0, 0, 0, },
//   {     "68_h.bin", 0x00000800, 0xff92f816, 0, 0, 0, },
   {     "68_h.bin", 0x00000800, 0x8e821fa0, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_kicknrun[] =
{
   INP0( COIN1, 0x020005, 0x01 ),
   INP0( COIN2, 0x020005, 0x02 ),
   INP0( TILT, 0x020000, 0x04 ),
   INP0( SERVICE, 0x020000, 0x01 ),

   INP0( P1_START, 0x020000, 0x08 ),
   INP0( P1_UP, 0x020001, 0x01 ),
   INP0( P1_DOWN, 0x020001, 0x02 ),
   INP0( P1_LEFT, 0x020001, 0x04 ),
   INP0( P1_RIGHT, 0x020001, 0x08 ),
   INP0( P1_B1, 0x020001, 0x10 ),
   INP0( P1_B2, 0x020001, 0x20 ),

   INP0( P2_START, 0x020000, 0x10 ),
   INP0( P2_UP, 0x020002, 0x01 ),
   INP0( P2_DOWN, 0x020002, 0x02 ),
   INP0( P2_LEFT, 0x020002, 0x04 ),
   INP0( P2_RIGHT, 0x020002, 0x08 ),
   INP0( P2_B1, 0x020002, 0x10 ),
   INP0( P2_B2, 0x020002, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_kick_and_run_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT2,           0x02, 0x02 },
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

static struct DSW_INFO dsw_kicknrun[] =
{
   { 0x020003, 0xFF, dsw_data_kick_and_run_0 },
   { 0x020004, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};



static struct YM2203interface ym2203_interface =
{
   1,
   4000000,
   { 0x00ff20c0 },
   {0},
   {0},
   {0},
   {0},
   {NULL}
};

static struct SOUND_INFO sound_kikikai[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { 0,             NULL,                 },
};



static struct ROM_INFO rom_kikikai[] =
{
   {   "a85-08.rom", 0x00000100, 0xd15f61a8, 0, 0, 0, },
   {   "a85-09.rom", 0x00000100, 0xb931c94d, 0, 0, 0, },
   {   "a85-10.rom", 0x00000100, 0x8fc3fa86, 0, 0, 0, },
   {   "a85-11.rom", 0x00008000, 0xcc3539db, 0, 0, 0, },
   {   "a85-12.rom", 0x00010000, 0x91e58067, 0, 0, 0, },
   {   "a85-13.rom", 0x00010000, 0x3eeaf878, 0, 0, 0, },
   {   "a85-14.rom", 0x00010000, 0xa9df0453, 0, 0, 0, },
   {   "a85-15.rom", 0x00010000, 0xaebc8c32, 0, 0, 0, },
   {   "a85-16.rom", 0x00010000, 0x4094d750, 0, 0, 0, },
   {   "a85-17.rom", 0x00010000, 0xc141d5ab, 0, 0, 0, },
   {   "knightb.uc", 0x00000800, 0x3cc2bbe4, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_kikikai[] =
{
   INP0( COIN1, 0x020005, 0x01 ),
   INP0( COIN2, 0x020005, 0x02 ),
   INP0( TILT, 0x020000, 0x04 ),
   INP0( SERVICE, 0x020000, 0x01 ),

   INP0( P1_START, 0x020000, 0x08 ),
   INP0( P1_UP, 0x020001, 0x01 ),
   INP0( P1_DOWN, 0x020001, 0x02 ),
   INP0( P1_LEFT, 0x020001, 0x04 ),
   INP0( P1_RIGHT, 0x020001, 0x08 ),
   INP0( P1_B1, 0x020001, 0x10 ),
   INP0( P1_B2, 0x020001, 0x20 ),

   INP0( P2_START, 0x020000, 0x10 ),
   INP0( P2_UP, 0x020002, 0x01 ),
   INP0( P2_DOWN, 0x020002, 0x02 ),
   INP0( P2_LEFT, 0x020002, 0x04 ),
   INP0( P2_RIGHT, 0x020002, 0x08 ),
   INP0( P2_B1, 0x020002, 0x10 ),
   INP0( P2_B2, 0x020002, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_kiki_kai_kai_0[] =
{
   DSW_CABINET( 0x01,0 ),
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_kiki_kai_kai_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("70k 150k"),              0x0C},
   { _("70k 200k"),              0x08},
   { _("100k 300k"),             0x04},
   { _("50k 100k"),              0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "2",                     0x00},
   { _("Unknown"),		      0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Number Match"),          0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_kikikai[] =
{
   { 0x020003, 0xFF, dsw_data_kiki_kai_kai_0 },
   { 0x020004, 0xFF, dsw_data_kiki_kai_kai_1 },
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_knightb[] =
{
   {  "a85-10.rom", 0x00000100, 0x8fc3fa86, 0, 0, 0, },
   {  "a85-09.rom", 0x00000100, 0xb931c94d, 0, 0, 0, },
   {  "a85-08.rom", 0x00000100, 0xd15f61a8, 0, 0, 0, },
   {  "a85-11.rom", 0x00008000, 0xcc3539db, 0, 0, 0, },
   {  "a85-12.rom", 0x00010000, 0x91e58067, 0, 0, 0, },
   {   "knightb.b", 0x00010000, 0x63ad7df3, 0, 0, 0, },
   {  "a85-14.rom", 0x00010000, 0xa9df0453, 0, 0, 0, },
   {   "knightb.d", 0x00010000, 0x53ecdb3f, 0, 0, 0, },
   {  "a85-16.rom", 0x00010000, 0x4094d750, 0, 0, 0, },
   {  "a85-17.rom", 0x00010000, 0xc141d5ab, 0, 0, 0, },
   {  "knightb.uc", 0x00000800, 0x3cc2bbe4, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static int romset;

static UINT8 *RAM2;
static UINT8 *ROM2;
static UINT8 *RAM_INPUT;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_MCU;

static UINT8 *GFX_BG0_SOLID;

/*

TAITO K-SYSTEM
--------------

0000-7FFF BASE ROM
8000-BFFF BANK ROM
D800-EFFF RAM
F000-F000 BANK SWITCH
F008-F008 MCU ENABLE?
F010-F010 INPUT READ
F018-F018 WATCHDOG
C000-FFFF <misc>

C500-CCFF SPRITE TILE RAM
CD00-D4FF BG0 RAM
D500-D501 BG0 SCROLL X
D502-D503 BG0 SCROLL Y

---

0000-7FFF BASE ROM
8000-9FFF COMMUNICATE RAM
C000-C001 YM2203

Supported romsets:

0 - B36 - Kiki Kai Kai          - 1986
1 - A87 - Kick and Run          - 1985

- Hardware info courtesy of Carl/DSC [Antiriad].

Todo:

- Graphics glitches: Shadows under monsters look like they might be in the
                     wrong priority... hmm..
- Player 2 inputs don't work in KKK?? (work in test mode, not in game).
  Could be do to with writes to 0xffff...
  Works in 'Table' mode, but using P1 inputs.
- I think this H/W has a system to connect 2 boards together...

*/

/******************************************************************************/
/* K-SYSTEM Z80 ROM BANKING                                                   */
/******************************************************************************/

static UINT8 gfx_bank;

static UINT8 bank_map[8] =
{
   4,5,6,7,2,3,0,1,
};

static void KSystemNewBankWrite(UINT16 offset, UINT8 data)
{
  UINT8 Z80Bank = bank_map[data&7];
  z80_set_bank(1,Z80Bank);
  gfx_bank = (data & 0x20) >> 5;
}

static void init_bank_rom(UINT8 *src, UINT8 *dst)
{
  z80_init_banks_area_ofs(1,src,0x20000,0x8000,0x4000,2);
}

/******************************************************************************/
/* K-SYSTEM COMMON RAM                                                        */
/******************************************************************************/

#if 0
// Unused functions !
static void KSystemCommonRAMWrite(UINT16 offset, UINT8 data)
{
   RAM[0xC000+(offset&0x1FFF)] = data;
}

static UINT8 KSystemCommonRAMRead(UINT16 offset)
{
   return RAM[0xC000+(offset&0x1FFF)];
}
#endif

/******************************************************************************/
/* K-SYSTEM MCU                                                               */
/******************************************************************************/

static int mcu_enable;
static UINT8 mcu_addr, mcu_latch, mcu_old_data;

static void KSystemMCUWrite(UINT16 offset, UINT8 data)
{
   offset&=0xFF;

#ifdef RAINE_DEBUG
   //print_debug("MCU Write: %02x:%02x [%04x]\n", offset, data, z80pc);
#endif

   RAM[offset+0xE800] = data;
}

static UINT8 KSystemMCURead(UINT16 offset)
{
   offset&=0xFF;

#ifdef RAINE_DEBUG
   //print_debug("MCU Read: %02x:?? [%04x]\n", offset, z80pc);
#endif

   return RAM[offset+0xE800];
}

void KikiKaiKai_mcu(int bih_count);
void KikiKaiKai_mcu_reset(void);
void KickRun_mcu(int bih_count);
void KickRun_mcu_reset(void);

UINT8 KSystem_MCU_RDMEM(int a)
{
   //print_debug("MCU RDMEM(0x%x)=%x\n", a, RAM_MCU[a]);
   if (a == 0x02) /* Port C - COIN,TILT,etc */
   {
      return RAM_INPUT[5];
   }
   return RAM_MCU[a];
}

void KSystem_MCU_WRMEM(int a, UINT8 v)
{
   UINT8 rising,falling;

   //print_debug("MCU WRMEM(0x%x,0x%x)\n", a, v);
   RAM_MCU[a] = v;

   if (a == 0x01) /* I/O control */
   {
      rising = (v ^ mcu_old_data) & v; /* only the rising-edge triggers these */
      falling = (v ^ mcu_old_data) & mcu_old_data; /* only the falling-edge triggers these */
      mcu_old_data = v;

      if (falling & 0x01) RAM_MCU[0x00] = mcu_latch;
      if (rising & 0x02) mcu_addr = RAM_MCU[0x00];
      if (falling & 0x08)
      {
         if (v & 0x10) /* read */
         {
            if (v & 4) /* System RAM */
            {
               mcu_latch = RAM[0xe800 + mcu_addr];
            } else {
               mcu_latch = RAM_INPUT[mcu_addr+1];
            }
         } else {    /* write */
            if (v & 4) /* System RAM */
            {
               RAM[0xe800 + mcu_addr] = RAM_MCU[0x00];
            } else {
               print_debug("INPUT WRITE!!?! (%x)\n", mcu_addr);
            }
         }
      }
      //if (falling & 0x20) mz80int(0xff);
   }
}


static void KSystemF008Write(UINT16 offset, UINT8 data)
{
   print_debug("MCU control: %04x:%02x [%04x]\n", offset, data, z80pc);

   // Just a hack for the MCU

   if(data == 0x1e)
      mcu_enable = 1;
   else
      mcu_enable = 0;
}

/******************************************************************************/
/* K-SYSTEM INPUT RAM                                                         */
/******************************************************************************/

static void KSystemInputWrite(UINT16 offset, UINT8 data)
{
   print_debug("Input Write: %04x:%02x [%04x]\n", offset, data, z80pc);
}

static UINT8 KSystemInputRead(UINT16 offset)
{
   return RAM_INPUT[0];
}

/******************************************************************************/
/* K-SYSTEM YM2203 AND DSW ACCESS                                             */
/******************************************************************************/

static UINT8 ksys_ym2203_reg;

static UINT8 KSystemYM2203Read(UINT16 offset)
{
   //print_debug("YM2203 RB:%04x/?? [%04x]\n", offset, z80pc);

   if((offset&1)==0){
      return 0; //YM2203_status_port_0_r(0);
   }
   else{
      switch(ksys_ym2203_reg){
         case 0x0e: return get_dsw(0);
         case 0x0f: return get_dsw(1);
         default:   return 0; //return YM2203_read_port_0_r(0);
      }
   }
}

static void KSystemYM2203Write(UINT16 offset, UINT8 data)
{
   //print_debug("YM2203 WB:%04x/%02x [%04x]\n", offset, data, z80pc);

   if((offset&1)==0){
      ksys_ym2203_reg = data;
   }
   else{
      YM2203_control_port_0_w(0,ksys_ym2203_reg);
      YM2203_write_port_0_w(1,data);
   }
}

/******************************************************************************/

static void DrawNibble0(UINT8 *out, UINT32 plane, UINT8 c)
{
   int count, t;

   count = 4;
      do {
         t = c & 1;
         *out = t << plane;
         out++;
         c >>= 1;
      } while(--count);
}

static void DrawNibble(UINT8 *out, UINT32 plane, UINT8 c)
{
   int count, t;

   count = 4;
      do {
         t = c & 1;
         *out |= t << plane;
         out++;
         c >>= 1;
      } while(--count);
}

static void load_kikikai(void)
{
   int ta,tb,tc,td;
   UINT8 *TMP;

   romset=0;
   mcu_enable=0;

   RAMSize=0x10000+0x10000+0x10+0x200+0x800;

   if(!(ROM2=AllocateMem(0x8000))) return;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_INPUT  = RAM+0x10000+0x10000;
   RAM_COLOUR = RAM+0x10000+0x10000+0x10;
   RAM_MCU    = RAM+0x10000+0x10000+0x10+0x200;

   if(!(TMP=AllocateMem(0x20000))) return;

   if(!load_rom("a85-17.rom",TMP+0x00000,0x10000)) return;	// Z80 MAIN ROM
   if(!load_rom("a85-16.rom",TMP+0x10000,0x10000)) return;	// Z80 MAIN ROM

   // Fix Checksum

   TMP[0x485a]=0xC9;  // RET

   // Skip Idle Z80

   TMP[0x0503]=0x28;  // JR Z,#0508
   TMP[0x0504]=0x03;  //

   TMP[0x0505]=0xD3;  // OUTA (AAh)
   TMP[0x0506]=0xAA;  //

   SetStopZ80BMode2(0x04FF);

   init_bank_rom(TMP,ROM);

   memset(RAM+0x00000, 0x00, RAMSize);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,                    NULL);         // Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC000, 0xE7FF, NULL,                    RAM+0xC000);   // RAM
   AddZ80BReadByte(0xE800, 0xE8FF, KSystemMCURead,          NULL);         // MCU COMM AREA
   AddZ80BReadByte(0xE900, 0xEFFF, NULL,                    RAM+0xE900);   // RAM
   AddZ80BReadByte(0xF010, 0xF010, KSystemInputRead,        NULL);         // INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,           NULL);         // <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC000, 0xE7FF, NULL,                   RAM+0xC000);   // RAM
   AddZ80BWriteByte(0xE800, 0xE8FF, KSystemMCUWrite,        NULL);         // MCU COMM AREA
   AddZ80BWriteByte(0xE900, 0xEFFF, NULL,                   RAM+0xE900);   // RAM
   AddZ80BWriteByte(0xF000, 0xF000, KSystemNewBankWrite,    NULL);         // ROM BANK
   AddZ80BWriteByte(0xF008, 0xF008, KSystemF008Write,       NULL);         // MCU??
   AddZ80BWriteByte(0xF010, 0xF010, KSystemInputWrite,      NULL);         // INPUT
   AddZ80BWriteByte(0xF018, 0xF018, NULL,                   RAM+0xF018);   // WATCHDOG
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);         // <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);	// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   if(!load_rom("a85-11.rom",ROM2,0x8000)) return;		// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x007F]=0x00;  // NOP
   ROM2[0x0080]=0x00;  // NOP

   ROM2[0x00BE]=0xC3;  // JP 00A4
   ROM2[0x00BF]=0xA4;  //
   ROM2[0x00C0]=0x00;  //

   ROM2[0x009C]=0x1A;  //
   ROM2[0x009D]=0x32;  //
   ROM2[0x009E]=0xFD;  //
   ROM2[0x009F]=0x9F;  //
   ROM2[0x00A0]=0x36;  //
   ROM2[0x00A1]=0x0F;  //
   ROM2[0x00A2]=0x18;  //
   ROM2[0x00A3]=0x10;  //

   ROM2[0x00A4]=0xD3;  // OUTA (AAh)
   ROM2[0x00A5]=0xAA;  //
   ROM2[0x00A6]=0x7E;  //
   ROM2[0x00A7]=0xFE;  //
   ROM2[0x00A8]=0xFF;  //
   ROM2[0x00A9]=0x28;  //
   ROM2[0x00AA]=0xF9;  //
   ROM2[0x00AB]=0xC3;  //
   ROM2[0x00AC]=0xC3;  //
   ROM2[0x00AD]=0x00;  //

   SetStopZ80CMode2(0x00A6);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0x7FFF, NULL,                    RAM2+0x0000);   // Z80 ROM
   AddZ80CReadByte(0x8000, 0x9FFF, NULL,                    RAM +0xC000);   // COMMON RAM
   AddZ80CReadByte(0xC000, 0xC001, KSystemYM2203Read,       NULL);          // YM2203; INPUT
   AddZ80CReadByte(0xA800, 0xC7FF, NULL,                    RAM2+0xA800);   // RAM?
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,           NULL);          // <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0x8000, 0x9FFF, NULL,                   RAM +0xC000);   // COMMON RAM
   AddZ80CWriteByte(0xC000, 0xC001, KSystemYM2203Write,     NULL);          // YM2203; INPUT
   AddZ80CWriteByte(0xA800, 0xC7FF, NULL,                   RAM2+0xA800);   // RAM?
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);          // <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);	// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   /* MCU ROM */
   if(!load_rom("knightb.uc",RAM_MCU,0x800)) return;

   if(!(GFX=AllocateMem(0x080000))) return;
   if(!(TMP=AllocateMem(0x040000))) return;

   tb=0;
   if(!load_rom("a85-15.rom", TMP+0x00000, 0x10000)) return;
   if(!load_rom("a85-14.rom", TMP+0x10000, 0x10000)) return;
   if(!load_rom("a85-13.rom", TMP+0x20000, 0x10000)) return;
   if(!load_rom("a85-12.rom", TMP+0x30000, 0x10000)) return;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(GFX+tb+0, 0, (UINT8) (TMP[ta+0x00000]&15) );
      DrawNibble (GFX+tb+0, 1, (UINT8) (TMP[ta+0x00000]>>4) );
      DrawNibble (GFX+tb+0, 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble (GFX+tb+0, 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble0(GFX+tb+4, 0, (UINT8) (TMP[ta+0x00001]&15) );
      DrawNibble (GFX+tb+4, 1, (UINT8) (TMP[ta+0x00001]>>4) );
      DrawNibble (GFX+tb+4, 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble (GFX+tb+4, 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }

   tb=0;
   if(!load_rom("a85-08.rom", TMP+0x00000, 0x80)) return;
   if(!load_rom("a85-10.rom", TMP+0x00080, 0x80)) return;
   if(!load_rom("a85-09.rom", TMP+0x00100, 0x80)) return;
   for(ta=0;ta<0x80;ta++,tb+=2){
      td  = (ta&0x70)|(0x0F-(ta&0x0F));
      tc  = (TMP[td+0x000]&0x0F)<<8;
      tc |= (TMP[td+0x080]&0x0F)<<4;
      tc |= (TMP[td+0x100]&0x0F)<<0;
      WriteWord(&RAM_COLOUR[tb+0x000],tc);
      WriteWord(&RAM_COLOUR[tb+0x100],tc);
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x2000);
}

static void load_knightb(void)
{
   int ta,tb,tc,td;
   UINT8 *TMP;

   romset=0;
   mcu_enable=0;

   RAMSize=0x10000+0x10000+0x10+0x200+0x800;

   if(!(ROM2=AllocateMem(0x8000))) return;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_INPUT  = RAM+0x10000+0x10000;
   RAM_COLOUR = RAM+0x10000+0x10000+0x10;
   RAM_MCU    = RAM+0x10000+0x10000+0x10+0x200;

   if(!(TMP=AllocateMem(0x20000))) return;

   if(!load_rom("a85-17.rom",TMP+0x00000,0x10000)) return;	// Z80 MAIN ROM
   if(!load_rom("a85-16.rom",TMP+0x10000,0x10000)) return;	// Z80 MAIN ROM

   // Fix Checksum

   TMP[0x485a]=0xC9;  // RET

   // Skip Idle Z80

   TMP[0x0503]=0x28;  // JR Z,#0508
   TMP[0x0504]=0x03;  //

   TMP[0x0505]=0xD3;  // OUTA (AAh)
   TMP[0x0506]=0xAA;  //

   SetStopZ80BMode2(0x04FF);

   init_bank_rom(TMP,ROM);

   memset(RAM+0x00000, 0x00, 0x10000);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,                    NULL);         // Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC000, 0xE7FF, NULL,                    RAM+0xC000);   // RAM
   AddZ80BReadByte(0xE800, 0xE8FF, KSystemMCURead,          NULL);         // MCU COMM AREA
   AddZ80BReadByte(0xE900, 0xEFFF, NULL,                    RAM+0xE900);   // RAM
   AddZ80BReadByte(0xF010, 0xF010, KSystemInputRead,        NULL);         // INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,           NULL);         // <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC000, 0xE7FF, NULL,                   RAM+0xC000);   // RAM
   AddZ80BWriteByte(0xE800, 0xE8FF, KSystemMCUWrite,        NULL);         // MCU COMM AREA
   AddZ80BWriteByte(0xE900, 0xEFFF, NULL,                   RAM+0xE900);   // RAM
   AddZ80BWriteByte(0xF000, 0xF000, KSystemNewBankWrite,    NULL);         // ROM BANK
   AddZ80BWriteByte(0xF008, 0xF008, KSystemF008Write,       NULL);         // MCU??
   AddZ80BWriteByte(0xF010, 0xF010, KSystemInputWrite,      NULL);         // INPUT
   AddZ80BWriteByte(0xF018, 0xF018, NULL,                   RAM+0xF018);   // WATCHDOG
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);         // <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);	// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   if(!load_rom("a85-11.rom",ROM2,0x8000)) return;		// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x007F]=0x00;  // NOP
   ROM2[0x0080]=0x00;  // NOP

   ROM2[0x00BE]=0xC3;  // JP 00A4
   ROM2[0x00BF]=0xA4;  //
   ROM2[0x00C0]=0x00;  //

   ROM2[0x009C]=0x1A;  //
   ROM2[0x009D]=0x32;  //
   ROM2[0x009E]=0xFD;  //
   ROM2[0x009F]=0x9F;  //
   ROM2[0x00A0]=0x36;  //
   ROM2[0x00A1]=0x0F;  //
   ROM2[0x00A2]=0x18;  //
   ROM2[0x00A3]=0x10;  //

   ROM2[0x00A4]=0xD3;  // OUTA (AAh)
   ROM2[0x00A5]=0xAA;  //
   ROM2[0x00A6]=0x7E;  //
   ROM2[0x00A7]=0xFE;  //
   ROM2[0x00A8]=0xFF;  //
   ROM2[0x00A9]=0x28;  //
   ROM2[0x00AA]=0xF9;  //
   ROM2[0x00AB]=0xC3;  //
   ROM2[0x00AC]=0xC3;  //
   ROM2[0x00AD]=0x00;  //

   SetStopZ80CMode2(0x00A6);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0x7FFF, NULL,                    RAM2+0x0000);   // Z80 ROM
   AddZ80CReadByte(0x8000, 0x9FFF, NULL,                    RAM +0xC000);   // COMMON RAM
   AddZ80CReadByte(0xC000, 0xC001, KSystemYM2203Read,       NULL);          // YM2203; INPUT
   AddZ80CReadByte(0xA000, 0xC7FF, NULL,                    RAM2+0xA000);   // RAM?
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,           NULL);          // <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0x8000, 0x9FFF, NULL,                   RAM +0xC000);   // COMMON RAM
   AddZ80CWriteByte(0xC000, 0xC001, KSystemYM2203Write,     NULL);          // YM2203; INPUT
   AddZ80CWriteByte(0xA000, 0xC7FF, NULL,                   RAM2+0xA000);   // RAM?
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);          // <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);	// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   /* MCU ROM */
   if(!load_rom("knightb.uc",RAM_MCU,0x800)) return;

   if(!(GFX=AllocateMem(0x080000))) return;
   if(!(TMP=AllocateMem(0x040000))) return;

   tb=0;
   if(!load_rom("knightb.d", TMP+0x00000, 0x10000)) return;
   if(!load_rom("a85-14.rom", TMP+0x10000, 0x10000)) return;
   if(!load_rom("knightb.b", TMP+0x20000, 0x10000)) return;
   if(!load_rom("a85-12.rom", TMP+0x30000, 0x10000)) return;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(GFX+tb+0, 0, (UINT8) (TMP[ta+0x00000]&15) );
      DrawNibble (GFX+tb+0, 1, (UINT8) (TMP[ta+0x00000]>>4) );
      DrawNibble (GFX+tb+0, 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble (GFX+tb+0, 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble0(GFX+tb+4, 0, (UINT8) (TMP[ta+0x00001]&15) );
      DrawNibble (GFX+tb+4, 1, (UINT8) (TMP[ta+0x00001]>>4) );
      DrawNibble (GFX+tb+4, 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble (GFX+tb+4, 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }

   tb=0;
   if(!load_rom("a85-08.rom", TMP+0x00000, 0x80)) return;
   if(!load_rom("a85-10.rom", TMP+0x00080, 0x80)) return;
   if(!load_rom("a85-09.rom", TMP+0x00100, 0x80)) return;
   for(ta=0;ta<0x80;ta++,tb+=2){
      td  = (ta&0x70)|(0x0F-(ta&0x0F));
      tc  = (TMP[td+0x000]&0x0F)<<8;
      tc |= (TMP[td+0x080]&0x0F)<<4;
      tc |= (TMP[td+0x100]&0x0F)<<0;
      WriteWord(&RAM_COLOUR[tb+0x000],tc);
      WriteWord(&RAM_COLOUR[tb+0x100],tc);
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x2000);
}

/* this is a patch for Kicn&Run.
 * it hacks it to accept an MCU from Mexico86.
 * If we ever got a proper K&R dump, we could probably remove this patch.
 */
static UINT8 PatchTable[] = {
   0x3E, 0x00, 0x32, 0x4A, 0xE8, 0x32, 0x4B, 0xE8,
   0x32, 0x77, 0xE8, 0x32, 0x54, 0xE8, 0x32, 0x60,
   0xE8, 0x3E, 0x37, 0x32, 0x4C, 0xE8, 0x3E, 0x12,
   0x32, 0x4F, 0xE8, 0x3E, 0x08, 0x32, 0x7B, 0xE8,
   0x3E, 0x80, 0x32, 0x7F, 0xE8, 0x3E, 0x92, 0x32,
   0x00, 0xE8, 0xC9
};

static void load_kicknrun(void)
{
   int ta,tb,tc,td;
   UINT8 *TMP;

   romset=1;
   mcu_enable=0;

   RAMSize=0x10000+0x10000+0x10+0x200+0x800;

   if(!(ROM2=AllocateMem(0x8000))) return;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_INPUT  = RAM+0x10000+0x10000;
   RAM_COLOUR = RAM+0x10000+0x10000+0x10;
   RAM_MCU    = RAM+0x10000+0x10000+0x10+0x200;

   if(!(TMP=AllocateMem(0x20000))) return;

   if(!load_rom("a87-08.bin",TMP+0x00000,0x10000)) return;  // Z80 MAIN ROM
   if(!load_rom("a87-07.bin",TMP+0x10000,0x10000)) return;  // Z80 MAIN ROM

   /* Mexico86 is a bootleg of Kick&Run. We don't have a MCU dump for K&R, so
    * we will use Mexico86's. However, the Mex86 dump is not quite an 100%
    * copy, so we need to patch Kick&Run to accept it.
    * If we ever got a proper K&R dump, we could probably remove this patch.
    */
   TMP[0x01C8] = 0x92;
   TMP[0x0207] = 0x3E;
   TMP[0x0208] = 0x92;
   TMP[0x0209] = 0x00;
   TMP[0x0223] = 0x18;
   TMP[0x07D1] = 0x18;
   for (ta=0;ta<sizeof(PatchTable);ta++)
   {
      TMP[0x084C+ta] = PatchTable[ta];
   }
   for (ta=0x0877;ta<=0x08b1;ta++) TMP[ta] = 0xff;

   init_bank_rom(TMP,ROM);

   memset(RAM, 0x00, RAMSize);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,              NULL);   // Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC000, 0xE7FF, NULL,              RAM+0xC000);   // RAM
   AddZ80BReadByte(0xE800, 0xE8FF, KSystemMCURead,    NULL);	// MCU
   AddZ80BReadByte(0xE900, 0xEFFF, NULL,              RAM+0xE900);   // RAM
   AddZ80BReadByte(0xF010, 0xF010, KSystemInputRead,  NULL);   // INPUT
   AddZ80BReadByte(0xF800, 0xFFFF, NULL,              RAM+0xF800);   // RAM?
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,     NULL);	// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC000, 0xE7FF, NULL,                RAM+0xC000);   // RAM
   AddZ80BWriteByte(0xE800, 0xE8FF, KSystemMCUWrite,     NULL);         // MCU
   AddZ80BWriteByte(0xE900, 0xEFFF, NULL,                RAM+0xE900);   // RAM
   AddZ80BWriteByte(0xF000, 0xF000, KSystemNewBankWrite, NULL);         // ROM BANK
   AddZ80BWriteByte(0xF008, 0xF008, KSystemF008Write,    NULL);         // ?
   AddZ80BWriteByte(0xF010, 0xF010, KSystemInputWrite,   NULL);         // INPUT
   AddZ80BWriteByte(0xF018, 0xF018, NULL,                RAM+0xF018);   // WATCHDOG
   AddZ80BWriteByte(0xF800, 0xFFFF, NULL,                RAM+0xF800);   // RAM?
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,      NULL);         // <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);	// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("a87-06.bin",ROM2,0x8000)) return;		// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x037d]=0xAF;  // XOR A (checksum always succeeds)
   ROM2[0x00d7]=0xD3;  // OUTA (AAh)
   ROM2[0x00d8]=0xAA;  //

   SetStopZ80CMode2(0x00d4);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0x7FFF, NULL,                    RAM2+0x0000);   // Z80 ROM
   AddZ80CReadByte(0x8000, 0xA7FF, NULL,                    RAM +0xC000);   // COMMON RAM
   AddZ80CReadByte(0xC000, 0xC001, KSystemYM2203Read,       NULL);          // YM2203; INPUT
   AddZ80CReadByte(0xA800, 0xC7FF, NULL,                    RAM2+0xA800);   // RAM?
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,           NULL);          // <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0x8000, 0xA7FF, NULL,                   RAM +0xC000);   // COMMON RAM
   AddZ80CWriteByte(0xC000, 0xC001, KSystemYM2203Write,     NULL);          // YM2203; INPUT
   AddZ80CWriteByte(0xA800, 0xC7FF, NULL,                   RAM2+0xA800);   // RAM?
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);          // <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,         NULL);   // <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);	// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   /* MCU ROM */
   if(!load_rom("68_h.bin",RAM_MCU,0x800)) return;

   if(!(GFX=AllocateMem(0x080000))) return;
   if(!(TMP=AllocateMem(0x040000))) return;

   if(!load_rom("a87-05.bin", TMP+0x00000, 0x10000)) return;
   if(!load_rom("a87-04.bin", TMP+0x10000, 0x08000)) return;
   if(!load_rom("a87-04.bin", TMP+0x18000, 0x08000)) return;
   if(!load_rom("a87-03.bin", TMP+0x20000, 0x10000)) return;
   if(!load_rom("a87-02.bin", TMP+0x30000, 0x08000)) return;
   if(!load_rom("a87-02.bin", TMP+0x38000, 0x08000)) return;

   // much annoyingness. we have to swap the upper/lower halves
   // of the 64K roms (the 32K ones just get repeated) :-(
   for(ta=0;ta<0x8000;ta++)
   {
      tb = TMP[0x00000+ta];
      TMP[0x00000+ta] = TMP[0x08000+ta];
      TMP[0x08000+ta] = tb;
      tb = TMP[0x20000+ta];
      TMP[0x20000+ta] = TMP[0x28000+ta];
      TMP[0x28000+ta] = tb;
   }

   tb=0;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(GFX+tb+0, 0, (UINT8) (TMP[ta+0x00000]&15) );
      DrawNibble (GFX+tb+0, 1, (UINT8) (TMP[ta+0x00000]>>4) );
      DrawNibble (GFX+tb+0, 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble (GFX+tb+0, 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble0(GFX+tb+4, 0, (UINT8) (TMP[ta+0x00001]&15) );
      DrawNibble (GFX+tb+4, 1, (UINT8) (TMP[ta+0x00001]>>4) );
      DrawNibble (GFX+tb+4, 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble (GFX+tb+4, 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }

   tb=0;
   if(!load_rom("a87-10.bin", TMP+0x00000, 0x100)) return;
   if(!load_rom("a87-12.bin", TMP+0x00100, 0x100)) return;
   if(!load_rom("a87-11.bin", TMP+0x00200, 0x100)) return;
   for(ta=0;ta<0x100;ta++,tb+=2){
      td  = ta ^ 0x0f;
      tc  = (TMP[td+0x000]&0x0F)<<8;
      tc |= (TMP[td+0x100]&0x0F)<<4;
      tc |= (TMP[td+0x200]&0x0F)<<0;
      WriteWord(&RAM_COLOUR[tb],tc);
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x2000);
}

static void execute_kikikai(void)
{
   int ta;

   if (cpu_get_pc(CPU_Z80_1) == 0x0000)
   {
      switch (romset) {
      case 0: KikiKaiKai_mcu_reset(); break;
      case 1: KickRun_mcu_reset(); break;
      }
   } else if (romset && cpu_get_pc(CPU_Z80_1) == 0x3ad3)
     // This is apparently caused by the protection : the z80 waits here
     // to be reseted, probably by the mcu. Since it does not happen in our
     // emulation, we force the reset.
     reset_game_hardware();

   // ---------------------

   if (romset==0)
   {
      for(ta=0;ta<16;ta++)
      {
         // probably actually only 6Mhz or so, but MZ80 bug means that...
         cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(16,60)/16);  // Main Z80 (60fps)

         if(cpu_get_pc(CPU_Z80_2) != 0x00A6)

            cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60)/16);  // Sub Z80 (60fps)

      }

      print_debug("Z80PC_MAIN:%04x\n",cpu_get_pc(CPU_Z80_1));

      cpu_interrupt(CPU_Z80_1, 0x38);

      cpu_interrupt(CPU_Z80_2, 0x38);


   }
   else {
      cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(8,60));   // Main Z80 6MHz (60fps)
      print_debug("Z80PC_MAIN:%04x\n",z80pc);
      cpu_interrupt(CPU_Z80_1, RAM[0xe800]);

      cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));   // Sub Z80 4MHz (60fps)
      print_debug("Z80PC_SUB:%04x\n",z80pc);
      cpu_interrupt(CPU_Z80_2, 0x38);
   }

   if (mcu_enable)
   {
      switch (romset) {
      case 0: KikiKaiKai_mcu(1); break;
      case 1: KickRun_mcu(1); break;
      }
   }
}

static void DrawKikiKaiKai(void)
{
   int x,y,ta;
   int sx,sy,offs,goffs,gfx_offs,gfx_num,gfx_attr,height,xc,yc;
   UINT8 map;

   // PALETTE

   if (RefreshBuffers)
   {
      for(x=0;x<0x200;x+=2)
      {
         ta = ReadWord(&RAM_COLOUR[x]);
#ifdef SDL
         pal[x >> 1].r = (ta & 0x0F00) >> 4;
         pal[x >> 1].g = (ta & 0x00F0);
         pal[x >> 1].b = (ta & 0x000F) << 4;
#else
         pal[x >> 1].r = (ta & 0x0F00) >> 6;
         pal[x >> 1].g = (ta & 0x00F0) >> 2;
         pal[x >> 1].b = (ta & 0x000F) << 2;
#endif
      }
   }

   // No Solid BG0

   clear_game_screen(0);

   // OBJECT

   sx = 0;
   for (offs=0;offs<0x300;offs+=4)
   {
      /* skip empty sprites */
      if (*(UINT32 *)(&RAM[offs+0xd500]) == 0) continue;

      gfx_num = RAM[0xd500 + offs + 1];
      gfx_attr = RAM[0xd500 + offs + 3];

      if ((gfx_num & 0x80) == 0)      /* 16x16 sprites */
      {
         gfx_offs = ((gfx_num & 0x1f) * 0x80) + ((gfx_num & 0x60) >> 1) + 12;
         height = 2;
      }
      else    /* tilemaps (each sprite is a 16x256 column) */
      {
         gfx_offs = ((gfx_num & 0x3f) * 0x80);
         height = 32;
      }

      if ((gfx_num & 0xc0) == 0xc0)
         sx += 16;
      else
      {
         sx = RAM[0xd500 + offs + 2];
         if (gfx_attr & 0x40) sx -= 256;
      }
      sy = 256 - height*8 - (RAM[0xd500 + offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++,goffs+=2)
         {
            /* this is different to Bubble Bobble */
            ta = ReadWord(&RAM[0xc000+goffs]) & 0x1FFF;
            if (!GFX_BG0_SOLID[ta]) continue;       // No pixels; skip

            map = (RAM[0xc001 + goffs] >> 1) & 0x70;

            x = (sx + xc * 8) & 0xff;
            y = ((sy + yc * 8) & 0xff) -16;

            /* Kiki Kai Kai appears not to have a X/Y flip (eh?) */
            if ((x > -8) && (y > -8) && (x < 256) && (y < 224))
            {
               if (GFX_BG0_SOLID[ta] == 1)       // Some pixels; trans
               {
                  Draw8x8_Trans_8_Rot(&GFX[ta<<6], x+8, y+8, map);
               } else {                          // all pixels; solid
                  Draw8x8_8_Rot(&GFX[ta<<6], x+8, y+8, map);
               }
            }
         }

         gfx_offs += 64;
      }
   }
}

static void DrawKickRun(void)
{
   int x,y,ta;
   int sx,sy,offs,goffs,gfx_offs,gfx_num,gfx_attr,height,xc,yc;
   UINT8 map;

   // PALETTE

   if (RefreshBuffers)
   {
      for(x=0;x<0x200;x+=2)
      {
         ta = ReadWord(&RAM_COLOUR[x]);
#ifdef SDL
         pal[x >> 1].r = (ta & 0x0F00) >> 4;
         pal[x >> 1].g = (ta & 0x00F0);
         pal[x >> 1].b = (ta & 0x000F) << 4;
#else
         pal[x >> 1].r = (ta & 0x0F00) >> 6;
         pal[x >> 1].g = (ta & 0x00F0) >> 2;
         pal[x >> 1].b = (ta & 0x000F) << 2;
#endif
      }
   }

   // No Solid BG0

   clear_game_screen(0);

   // OBJECT

   sx = 0;
   for (offs=0;offs<0x4c0;offs+=4)
   {
      // I really give up on this bollocks, I really do.
      // MAME says do this. <sigh>
      if (offs >= 0x300 && offs < 0x480) continue;

      /* skip empty sprites */
      if (*(UINT32 *)(&RAM[offs+0xd500]) == 0) continue;

      gfx_num = RAM[0xd500 + offs + 1];
      gfx_attr = RAM[0xd500 + offs + 3];

      if ((gfx_num & 0x80) == 0)      /* 16x16 sprites */
      {
         gfx_offs = ((gfx_num & 0x1f) * 0x80) + ((gfx_num & 0x60) >> 1) + 12;
         height = 2;
      }
      else    /* tilemaps (each sprite is a 16x256 column) */
      {
         gfx_offs = ((gfx_num & 0x3f) * 0x80);
         height = 32;
      }

      if ((gfx_num & 0xc0) == 0xc0)
         sx += 16;
      else
      {
         sx = RAM[0xd500 + offs + 2];
         // not this either (accoring to MAME at least)?
         //if (gfx_attr & 0x40) sx -= 256;
      }
      sy = 256 - height*8 - (RAM[0xd500 + offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++,goffs+=2)
         {
            /* this is different to both Bubble Bobble and KKK */

            ta = ReadWord(&RAM[0xc000+goffs]) & 0x07FF;
            ta |= (RAM[0xc001+goffs] & 0x80) << 4;
            ta |= gfx_bank << 12;

            if (!GFX_BG0_SOLID[ta]) continue;       // No pixels; skip

            map = (RAM[0xc001 + goffs] << 1) & 0x70;
            map |= (gfx_attr & 0x02) << 6;

            x = (sx + xc * 8) & 0xff;
            y = ((sy + yc * 8) & 0xff) -16;

            if ((x > -8) && (y > -8) && (x < 256) && (y < 224))
            {
               if (GFX_BG0_SOLID[ta] == 1)       // Some pixels; trans
               {
                  if (RAM[0xc000+goffs+1] & 0x40)
                     Draw8x8_Trans_8_FlipY_Rot(&GFX[ta<<6], x+8, y+8, map);
                  else
                     Draw8x8_Trans_8_Rot(&GFX[ta<<6], x+8, y+8, map);
               } else {                          // all pixels; solid
                  if (RAM[0xc000+goffs+1] & 0x40)
                     Draw8x8_8_FlipY_Rot(&GFX[ta<<6], x+8, y+8, map);
                  else
                     Draw8x8_8_Rot(&GFX[ta<<6], x+8, y+8, map);
               }
            }
         }

         gfx_offs += 64;
      }
   }
}

static struct VIDEO_INFO video_kicknrun =
{
   DrawKickRun,
   256,
   224,
   8,
   VIDEO_ROTATABLE | VIDEO_NEEDS_8BPP,
};
static struct VIDEO_INFO video_kikikai =
{
   DrawKikiKaiKai,
   256,
   224,
   8,
   VIDEO_ROTATE_90 | VIDEO_NEEDS_8BPP |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_kicknrun[] =
{
   { "kick_and_run", },
   { "kicknrun", },
   { NULL, },
};
GAME( kicknrun, "Kick and Run", TAITO, 1986, GAME_SPORTS,
	.input = input_kicknrun,
	.dsw = dsw_kicknrun,
	.video = &video_kicknrun,
	.exec = execute_kikikai,
	.board = "A87",
	.sound = sound_kikikai,
);
static struct DIR_INFO dir_kikikai[] =
{
   { "kiki_kai_kai", },
   { "kikikai", },
   { "kikikaik", },
   { "knightb", },
   { NULL, },
};
GME( kikikai, "Kiki Kai Kai", TAITO, 1986, GAME_PLATFORM,
	.board = "A85",
);
static struct DIR_INFO dir_knightb[] =
{
   { "knight_boy", },
   { "knightb", },
   { ROMOF("kikikai"), },
   { CLONEOF("kikikai"), },
   { NULL, },
};
CLNE( knightb,kikikai, "Knight Boy", BOOTLEG, 1986, GAME_PLATFORM,
	.load_game = load_knightb);

