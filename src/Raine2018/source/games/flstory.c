/******************************************************************************/
/*                                                                            */
/*                 TAITO ?-SYSTEM (C) 1986 TAITO CORPORATION                  */
/*                                                                            */
/*                       Z80+Z80+tons of sound chips                          */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "ay8910.h"
#include "msm5232.h"
#include "sasound.h"		// sample support routines
#include "m68705.h"
#include "emumain.h"
#include "streams.h"
#include "dac.h"

/* This hardware is a nuisance :
 * a 68705 used only for protection, it doesn't even access any input, + its synchronization is weird, and it obliged me to patch a bug in the 68705 recompiler.
 * a split palette, the next byte of each color is $100 bytes away !
 * a way too complex bg layer, priorities with only 1 layer ??!!!
 * 3 sound chips for the sound z80 : ym2149 + msm5232 + dac. In raine we have only a primitive dac for now,
 * maybe it would work with a 2151, not much luck so far... !
 * A broken communication with the sound z80 : the main z80 expects to have time to read the sound command status
 * after posting a command and finding it "pending". If not, it creates an infinite loop ! I patched the rom to fix
 * that, it was that or making a "slow" soundlatch system, and really, no !!! */

static struct ROM_INFO rom_flstory[] =
{
  { "cpu-a45.15", 0x4000, 0xf03fc969, REGION_CPU1, 0x0000, LOAD_NORMAL },
  { "cpu-a45.16", 0x4000, 0x311aa82e, REGION_CPU1, 0x4000, LOAD_NORMAL },
  { "cpu-a45.17", 0x4000, 0xa2b5d17d, REGION_CPU1, 0x8000, LOAD_NORMAL },
  { "snd.22", 0x2000, 0xd58b201d, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "snd.23", 0x2000, 0x25e7fd9d, REGION_ROM2, 0x2000, LOAD_NORMAL },
  { "a45-20.mcu", 0x0800, 0x5378253c /*7d2cdd9b*/, REGION_ROM3, 0x0000, LOAD_NORMAL },
  { "vid-a45.18", 0x4000, 0x6f08f69e, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "vid-a45.06", 0x4000, 0xdc856a75, REGION_GFX1, 0x04000, LOAD_NORMAL },
  { "vid-a45.08", 0x4000, 0xd0b028ca, REGION_GFX1, 0x08000, LOAD_NORMAL },
  { "vid-a45.20", 0x4000, 0x1b0edf34, REGION_GFX1, 0x0c000, LOAD_NORMAL },
  { "vid-a45.19", 0x4000, 0x2b572dc9, REGION_GFX1, 0x10000, LOAD_NORMAL },
  { "vid-a45.07", 0x4000, 0xaa4b0762, REGION_GFX1, 0x14000, LOAD_NORMAL },
  { "vid-a45.09", 0x4000, 0x8336be58, REGION_GFX1, 0x18000, LOAD_NORMAL },
  { "vid-a45.21", 0x4000, 0xfc382bd1, REGION_GFX1, 0x1c000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_flstory[] =
{
  INP0( P1_START, 0x03, 0x01),
  INP0( P2_START, 0x03, 0x02),
  INP0( SERVICE, 0x03, 0x04),
  INP0( TILT, 0x03, 0x08),
  INP0( COIN1, 0x03, 0x10),
  INP0( COIN2, 0x03, 0x20),
  INP1( UNKNOWN, 0x03, 0x40), // bad io if INP0
  INP1( UNKNOWN, 0x03, 0x80), // bad io if INP0

  INP0( P1_B1, 0x04, 0x01),
  INP0( P1_B2, 0x04, 0x02),
  INP0( P1_LEFT, 0x04, 0x04),
  INP0( P1_RIGHT, 0x04, 0x08),

  // 5 is used by mcu_status_r
  INP0( P1_B1, 0x06, 0x01),
  INP0( P1_B2, 0x06, 0x02),
  INP0( P1_LEFT, 0x06, 0x04),
  INP0( P1_RIGHT, 0x06, 0x08),
  END_INPUT
};

static struct DSW_DATA dsw_data_flstory_0[] =
{
  { MSG_EXTRA_LIFE, 0x03, 4 },
  { "30000 100000", 0x00, 0x00 },
  { "30000 150000", 0x01, 0x00 },
  { "50000 150000", 0x02, 0x00 },
  { "70000 150000", 0x03, 0x00 },
  { MSG_FREE_PLAY, 0x04, 2 },
  { MSG_OFF, 0x04, 0x00 },
  { MSG_ON, 0x00, 0x00 },
  { MSG_LIVES, 0x18, 4 },
  { "3", 0x08, 0x00 },
  { "4", 0x10, 0x00 },
  { "5", 0x18, 0x00 },
  { "Infinite (Cheat)", 0x00, 0x00 },
  { "Debug Mode", 0x20, 2 },
  { MSG_OFF, 0x20, 0x00 },
  { MSG_ON, 0x00, 0x00 },
  { MSG_SCREEN, 0x40, 2 },
  { MSG_OFF, 0x40, 0x00 },
  { MSG_ON, 0x00, 0x00 },
  { MSG_CABINET, 0x80, 2 },
  { MSG_UPRIGHT, 0x80, 0x00 },
  { MSG_TABLE, 0x00, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_DATA dsw_data_flstory_1[] =
{
  { MSG_COIN1, 0x0f, 16 },
  { MSG_9COIN_1PLAY, 0x0f, 0x00 },
  { MSG_8COIN_1PLAY, 0x0e, 0x00 },
  { MSG_7COIN_1PLAY, 0x0d, 0x00 },
  { MSG_6COIN_1PLAY, 0x0c, 0x00 },
  { MSG_5COIN_1PLAY, 0x0b, 0x00 },
  { MSG_4COIN_1PLAY, 0x0a, 0x00 },
  { MSG_3COIN_1PLAY, 0x09, 0x00 },
  { MSG_2COIN_1PLAY, 0x08, 0x00 },
  { MSG_1COIN_1PLAY, 0x00, 0x00 },
  { MSG_1COIN_2PLAY, 0x01, 0x00 },
  { MSG_1COIN_3PLAY, 0x02, 0x00 },
  { MSG_1COIN_4PLAY, 0x03, 0x00 },
  { MSG_1COIN_5PLAY, 0x04, 0x00 },
  { MSG_1COIN_6PLAY, 0x05, 0x00 },
  { MSG_1COIN_7PLAY, 0x06, 0x00 },
  { MSG_1COIN_8PLAY, 0x07, 0x00 },
  { MSG_COIN2, 0xf0, 16 },
  { MSG_9COIN_1PLAY, 0xf0, 0x00 },
  { MSG_8COIN_1PLAY, 0xe0, 0x00 },
  { MSG_7COIN_1PLAY, 0xd0, 0x00 },
  { MSG_6COIN_1PLAY, 0xc0, 0x00 },
  { MSG_5COIN_1PLAY, 0xb0, 0x00 },
  { MSG_4COIN_1PLAY, 0xa0, 0x00 },
  { MSG_3COIN_1PLAY, 0x90, 0x00 },
  { MSG_2COIN_1PLAY, 0x80, 0x00 },
  { MSG_1COIN_1PLAY, 0x00, 0x00 },
  { MSG_1COIN_2PLAY, 0x10, 0x00 },
  { MSG_1COIN_3PLAY, 0x20, 0x00 },
  { MSG_1COIN_4PLAY, 0x30, 0x00 },
  { MSG_1COIN_5PLAY, 0x40, 0x00 },
  { MSG_1COIN_6PLAY, 0x50, 0x00 },
  { MSG_1COIN_7PLAY, 0x60, 0x00 },
  { MSG_1COIN_8PLAY, 0x70, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_DATA dsw_data_flstory_2[] =
{
    // 1st 3 bits unused
  { MSG_CONTINUE_PLAY, 0x08, 2 },
  { MSG_NO, 0x00, 0x00 },
  { MSG_YES, 0x08, 0x00 },
  { "Attract Animation", 0x10, 2 },
  { MSG_OFF, 0x00, 0x00 },
  { MSG_ON, 0x10, 0x00 },
  { "Leave Off", 0x20, 2 },
  { MSG_OFF, 0x20, 0x00 },	// (must be OFF or the game will
  { MSG_ON, 0x00, 0x00 },	// hang after the game is over !)
  { "Invulnerability (Cheat)", 0x40, 2 },
  { MSG_OFF, 0x40, 0x00 },
  { MSG_ON, 0x00, 0x00 },
  { "Coin Slots", 0x80, 2 },
  { "1", 0x00, 0x00 },
  { "2", 0x80, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_INFO dsw_flstory[] =
{
  { 0x0, 0xec, dsw_data_flstory_0 },
  { 0x1, 0x00, dsw_data_flstory_1 },
  { 0x2, 0xf8, dsw_data_flstory_2 },
  { 0, 0, NULL }
};

static int vol_ctrl[16];

static void mixer_init()
{
	int i;

	double db			= 0.0;
	double db_step		= 1.50;	/* 1.50 dB step (at least, maybe more) */
	double db_step_inc	= 0.125;
	for (i=0; i<16; i++)
	{
		double max = 255.0 / pow(10.0, db/20.0 );
		vol_ctrl[ 15-i ] = max;
		/*logerror("vol_ctrl[%x] = %i (%f dB)\n",15-i,vol_ctrl[ 15-i ],db);*/
		db += db_step;
		db_step += db_step_inc;
	}

	/* for (i=0; i<8; i++)
		logerror("SOUND Chan#%i name=%s\n", i, mixer_get_name(i) ); */
/*
  channels 0-2 AY#0
  channels 3,4 MSM5232 group1,group2
*/
}

static UINT8 snd_ctrl0=0;
static UINT8 snd_ctrl1=0;
static UINT8 snd_ctrl2=0;
static UINT8 snd_ctrl3=0;

static void sound_control_0_w(UINT32 offset,UINT8 data)
{
	snd_ctrl0 = data & 0xff;
//	usrintf_showmessage("SND0 0=%02x 1=%02x 2=%02x 3=%02x", snd_ctrl0, snd_ctrl1, snd_ctrl2, snd_ctrl3);

	/* this definitely controls main melody voice on 2'-1 and 4'-1 outputs */
	stream_set_volume (3, vol_ctrl[ (snd_ctrl0>>4) & 15 ]);	/* group1 from msm5232 */

}
static void sound_control_1_w(UINT32 offset,UINT8 data)
{
	snd_ctrl1 = data & 0xff;
//	usrintf_showmessage("SND1 0=%02x 1=%02x 2=%02x 3=%02x", snd_ctrl0, snd_ctrl1, snd_ctrl2, snd_ctrl3);
	stream_set_volume (4, vol_ctrl[ (snd_ctrl1>>4) & 15 ]);	/* group2 from msm5232 */
}

static void sound_control_2_w(UINT32 offset,UINT8 data)
{
	int i;

	snd_ctrl2 = data & 0xff;
//	usrintf_showmessage("SND2 0=%02x 1=%02x 2=%02x 3=%02x", snd_ctrl0, snd_ctrl1, snd_ctrl2, snd_ctrl3);

	for (i=0; i<3; i++)
		//stream_set_volume (i, vol_ctrl[ (snd_ctrl2>>4) & 15 ]);	/* ym2149f all */
	    // the ay8910 is too loud, I divide it by 2 (>>5)
		stream_set_volume (i, vol_ctrl[ (snd_ctrl2>>5) & 15 ]);	/* ym2149f all */
}

static void sound_control_3_w(UINT32 offset,UINT8 data) /* unknown */
{
	snd_ctrl3 = data & 0xff;
//	usrintf_showmessage("SND3 0=%02x 1=%02x 2=%02x 3=%02x", snd_ctrl0, snd_ctrl1, snd_ctrl2, snd_ctrl3);
}

static struct AY8910interface ay8910_interface =
{
	1,	/* 1 chip */
	8000000/4,	/* ??? */
	{ MIXER(10,OSD_PAN_CENTER) },
	{ 0 },
	{ 0 },
	{ sound_control_2_w },
	{ sound_control_3_w }
};

static struct MSM5232interface msm5232_interface =
{
	1, /* number of chips */
	2000000, /* 2 MHz ?*/
	{ { 1.0e-6, 1.0e-6, 1.0e-6, 1.0e-6, 1.0e-6, 1.0e-6, 1.0e-6, 1.0e-6 } },	/* 1.0 uF capacitors (verified on real PCB) */
	{ MIXER(100, OSD_PAN_CENTER) },
};

static struct DACinterface dac_interface =
{
	1,
	{ 22 }
};

static struct SOUND_INFO sound_flstory[] =
{
    { SOUND_AY8910,&ay8910_interface, }, // used for the sound effects during game (jump, shoot, etc...)
    { SOUND_MSM5232, &msm5232_interface, }, // music
    { SOUND_DAC, &dac_interface, }, // actually unknown, not even sure it works !
   { 0,             NULL,                 },
};


static int romset;

static UINT8 *RAM2;
static UINT8 *ROM2;
static UINT8 *RAM_COLOUR;
static int scrolly;
static UINT8 *nmi_enable;
UINT8 *fl_mcu_started,*ram_spr;

/*

0000-BFFF BASE ROM
C000-C7FF BG0 RAM
D400-D401 SOUND COMM
DC00-DCBF MCU?
DD00-DEFF ?
E000-E7FF WORK RAM

---

0000-3FFF BASE ROM
C000-C7FF WORK RAM
D800-D800 SOUND COMM

Supported romsets:

0 - A45 - Fairyland Story       - 1985 - ?-System

Todo:

- Many things.

*/


/******************************************************************************/

static int nmi_pending;
static void FLStorySoundWriteMain(UINT16 offset, UINT8 data)
{
    RAM[0xd403] = 1; // pending
    RAM[0xd402] = data;
    if (*nmi_enable) {
	cpu_int_nmi(CPU_Z80_1);
	cpu_execute_cycles(CPU_Z80_1,500);
	switch_cpu(CPU_Z80_0);
	// StopZ80(0,0);
    } else {
	nmi_pending = 1;
    }
}

static UINT8 FLStorySoundReadMain(UINT16 offset)
{
    if ((offset & 1) == 0) {
	RAM[0xd401] = 0; // not pending
	return RAM[0xd400]; // latch
    }
    return RAM[0xd403] | (RAM[0xd401] << 1); // status
}

static void FLStorySoundWriteSub(UINT16 offset, UINT8 data)
{
    RAM[0xd401] = 1; // pending
    RAM[0xd400] = data;
}

static UINT8 FLStorySoundReadSub(UINT16 offset)
{
    RAM[0xd403] = 0;
    return RAM[0xd402];
}


/******************************************************************************/

extern UINT8 flstory_mcu_r(UINT32 offset);
extern void flstory_mcu_w(UINT32 offset,UINT8 data);
extern UINT8 flstory_mcu_status_r(UINT32 offset);
extern void flstory_mcu_reset(UINT8 *ram);

static UINT8 main_mirror_r(UINT32 offset) {
    offset &= 0x7ff;
    return RAM[0xe000 + offset];
}

static void main_mirror_w(UINT32 offset, UINT8 data) {
    RAM[0xe000 + (offset & 0x7ff)] = data;
}

static void write_scrolly(UINT32 offset, UINT8 data) {
    scrolly = data;
    RAM[0xdca0 + (offset & 0x1f)] = data;
}

static UINT8 read_palette(UINT32 offset) {
    int pal_bank = (RAM[0xdf03] & 0x20) >> 5;
    if (offset >= 0xde00)
	return RAM[pal_bank*0x200+1+(offset & 0xff)*2];
    return RAM[pal_bank*0x200+(offset & 0xff)*2];
}

static void write_palette(UINT32 offset,UINT8 data) {
    int pal_bank = (RAM[0xdf03] & 0x20) >> 5;
    bank_status[pal_bank*0x10+((offset>>4)&0xf)] = 0;
    if (offset >= 0xde00)
	RAM[pal_bank*0x200+1+(offset & 0xff)*2] = data;
    else
	RAM[pal_bank*0x200+(offset & 0xff)*2] = data;
}

static void nmi_enable_w(UINT32 offset, UINT8 data) {
    *nmi_enable = 1;
    if (nmi_pending) {
	nmi_pending = 0;
	cpu_int_nmi(CPU_Z80_1);

    }
}
static void nmi_disable_w(UINT32 offset, UINT8 data) {
    *nmi_enable = 0;
}

static void dummy_write(UINT32 offset, UINT8 data) {
}

static UINT8 read_nop(UINT32 offset) {
    return 0;
}

static void myreset() {
   flstory_mcu_reset(load_region[REGION_ROM3]);
   *fl_mcu_started = *nmi_enable = 0;
   mixer_init();
}

static void load_flstory(void)
{
   ROM2 = Z80ROM;

   romset=0;
   RAMSize=0x10000+0x10000+0x200;

   if(!(RAM=AllocateMem(RAMSize))) return;
   nmi_enable = RAM + 0xd404;
   fl_mcu_started = nmi_enable + 1;
   ram_spr = RAM+0xdc00;

   RAM2       = RAM+0x10000;
   RAM_COLOUR = RAM+0x10000+0x10000;

   // BAD HW

   // ROM[0xBF59]=0xC9;

   // BAD ROM

   ROM[0xBFFA]=0xC9;

   // BAD SOUND PCB

   // ROM[0x021A]=0x00;
   // ROM[0x021B]=0x00;
   // ROM[0x021C]=0x00;

   // BAD IO

   // ROM[0x0225]=0x00;
   // ROM[0x0226]=0x00;
   // ROM[0x0227]=0x00;

   // Skip Idle Z80
   // -------------

   // unadviced : there are places where the number of irqs is counted
   /* ROM[0x485a]=0xC9;  // RET

   ROM[0x04FF]=0xC3;  // JP 005D
   ROM[0x0500]=0x5D;  //
   ROM[0x0501]=0x00;  //

   ROM[0x005D]=0x3A;  //
   ROM[0x005E]=0x90;  //
   ROM[0x005F]=0xDA;  //
   ROM[0x0060]=0xD3;  // OUTA (AAh)
   ROM[0x0061]=0xAA;  //

   SetStopZ80Mode2(0x0502); */

   // Fix stupid sync problem : the main z80 expects to have time to read the pending sound command bit at 1 when it posts a sound command
   // so if the sound z80 reacts too quickly (and here it does !), then it never reads its bit and hangs
   ROM[0x6e5] = 0xc9; // ret instead of infinite loop !

   memset(RAM+0x00000, 0x00, 0x10000);
   // memcpy(RAM,ROM,get_region_size(REGION_ROM1));

   AddZ80AROMBase(ROM, 0x38, 0x66);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,	ROM);	// Z80 ROM
   AddZ80ARW(0xC000, 0xC7FF, NULL,		RAM+0xc000);	// BG0 RAM
   AddZ80ARW(0xe000, 0xe7FF, NULL,		RAM+0xe000);	// main RAM
   AddZ80ARead(0xe800,0xffff, main_mirror_r, NULL);
   AddZ80AWrite(0xe800,0xffff, main_mirror_w, NULL);
   // AddZ80ARW(0xC800, 0xCfFF, NULL,		RAM+0xc000);	// BG0 RAM (mirror)
   AddZ80ARW(0xdc00, 0xdc9f, NULL, ram_spr); // sprites
   AddZ80ARead(0xdca0, 0xdcbf, NULL, RAM+0xdca0); // scrolly mirrored everywhere ?!!
   AddZ80AWrite(0xdca0, 0xdcbf, write_scrolly, NULL); // scrolly mirrored everywhere ?!!
   AddZ80ARW(0xdcc0, 0xdcff, NULL, RAM+0xdcc0);
   AddZ80ARead( 0xd000, 0xd000, flstory_mcu_r, NULL);
   AddZ80AWrite(0xd000, 0xd000, flstory_mcu_w, NULL);
   AddZ80AReadByte(0xd400, 0xd401, FLStorySoundReadMain,	NULL);	// SOUND COMM
   AddZ80ARead(0xd805, 0xd805, flstory_mcu_status_r, NULL);
   AddZ80ARead(0xd800, 0xd806, NULL, input_buffer);
   // Palette is split at $100 !!!
   AddZ80ARead(0xDD00, 0xDeff, read_palette,NULL);	// palette
   AddZ80AWrite(0xDD00, 0xDeff, write_palette, NULL);	// palette
   AddZ80ARW(0xdf00, 0xdf03, NULL, RAM + 0xdf00); // for df03, gfx_ctrl !

   AddZ80AWriteByte(0xD400, 0xD400, FLStorySoundWriteMain,	NULL);	// SOUND COMM

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,			NULL);	// Trap Idle Z80
   finish_conf_z80(0);

   // Skip Idle Z80
   // -------------

   // The speed hack seems to kill the dac handling when booting
   // but then for now it crashes the game on "bad sound pcb"
   ROM2[0x0167]=0xD3;  // OUTA (AAh)
   ROM2[0x0168]=0xAA;  //

   SetStopZ80BMode2(0x0160);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2,ROM2,get_region_size(REGION_ROM2));

   AddZ80BROMBase(ROM2, 0x0038, 0x0066);

   AddZ80BRead(0x0000, 0x3FFF, NULL,			ROM2);	// Z80 ROM
   // AddZ80BRW(0xC000, 0xC7FF, NULL,			RAM2);	// WORK RAM
   // AddZ80BRead(0xc300, 0xc300,
   // AddZ80BWrite(0xc300, 0xc300, write_c300, NULL);
   AddZ80BRW(0xc000, 0xc7ff, NULL,	RAM2+0xc000);	// WORK RAM
   AddZ80BReadByte(0xD800, 0xD800, FLStorySoundReadSub,		NULL);	// SOUND COMM
   AddZ80BRead(0xda00, 0xda00, read_nop, NULL);
   AddZ80BRead(0xde00, 0xde00, read_nop, NULL);

   AddZ80BWrite(0xc800,0xc800, AY8910_control_port_0_w, NULL);
   AddZ80BWrite(0xc801,0xc801, AY8910_write_port_0_w, NULL);
   AddZ80BWrite(0xca00,0xca0d, MSM5232_0_w, NULL);
   AddZ80BWrite(0xcc00,0xcc00, sound_control_0_w, NULL);
   AddZ80BWrite(0xce00,0xce00, sound_control_1_w, NULL);
   AddZ80BWrite(0xd800, 0xD800, FLStorySoundWriteSub,	NULL);	// SOUND COMM
   AddZ80BWrite(0xda00, 0xda00, nmi_enable_w, NULL);
   AddZ80BWrite(0xdc00, 0xdc00, nmi_disable_w, NULL);
   // AddZ80BWrite(0xde00, 0xde00, DAC_0_signed_data_w, NULL);
   AddZ80BWrite(0xde00, 0xde00, dummy_write, NULL); // a dac ?

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);	// Trap Idle Z80
   finish_conf_z80(1);

   /*-----------------------*/

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr_rev); // col_map_12bit_RRRRGGGGBBBBxxxx_Rev );
   InitPaletteMap(RAM, 0x20, 0x10, 0x1000);
   set_reset_function(myreset);
}

extern void flstory_mcu(int bih_count);

static void execute_flstory(void)
{
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(3,60));	// Main Z80 6MHz (60fps)  10533000/2/60

   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(3,60));	// Sub Z80 4MHz (60fps)
   cpu_interrupt(CPU_Z80_1, 0x38);

   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(3,60));	// Main Z80 6MHz (60fps)  10533000/2/60
   cpu_interrupt(CPU_Z80_0, 0x38);

   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(3,60));	// Sub Z80 4MHz (60fps)
   cpu_interrupt(CPU_Z80_1, 0x38);

   if (*fl_mcu_started) {
       /* There is a synchronization problem between the main z80 and the 68705
	* To avoid to loose the rom crc I must launch it only after receiving the
	* 1st commands from the z80 ! */
       flstory_mcu(1);
   }
}

static void draw_flstory(void)
{
   int x,y,ta;
   int zz,zzz,zzzz,x16,y16;
   UINT8 *map;
   int char_bank, flipscreen,attr,flip;

   flipscreen  = (~RAM[0xdf03] & 0x01);
   char_bank = (RAM[0xdf03] & 0x10) >> 4;

   // BG1/FG0
   // -------
   if (RefreshBuffers) {
       // RefreshBuffers in case of loading a savegame for example
       // since for once color banks are updated with the palette
       // they need to be cleared upon loading a save
       ClearPaletteMap();
   }

   MAKE_SCROLL_n_8(256,256,2,
      0,
      scrolly
   );

   START_SCROLL_256x256_2_8_R180(32,16,256,256);

      ta = RAM[0xC000+zz];
      attr = RAM[0xC000+zz+1];
      ta += ((attr & 0xc0) << 2) + 0x400 + 0x800 * char_bank;
      if ((attr & 0x20)==0) {
	  flip = ((attr >> 3) & 3) ^ 3;
	  MAP_PALETTE_MAPPED_NEW(
		  attr & 0xf,
		  16,
		  map
		  );

	  Draw8x8_Mapped_flip_Rot(&GFX[(ta<<6)], x, y, map,flip);
      }

   END_SCROLL_256x256_2_8();

   int i;

   for (i = 0; i < 0x20; i++)
   {
       int pr = ram_spr[0xa0-1 -i];
       int offs = (pr & 0x1f) * 4;

//       if ((pr & 0x80) == pri)
       {
	   int code,sx,sy,flipx,flipy;

	   code = ram_spr[offs+2] + ((ram_spr[offs+1] & 0x30) << 4);
	   sx = ram_spr[offs+3];
	   sy = ram_spr[offs+0];


	   flipx = ((ram_spr[offs+1]&0x40)>>6)^flipscreen;
	   flipy = ((ram_spr[offs+1]&0x80)>>7)^flipscreen;
	   sx = 256 - sx - 16;
	   flipx ^= 1;
	   flipy ^= 1;

	   if (gfx2_solid[code]) {
	       MAP_PAL((ram_spr[offs+1] & 0x0f)|0x10,
		       16,
		       map);
	       // printf("%d,%d,%x bank %x pr %x\n",sx,sy,code,ram_spr[offs+1] & 0x0f,pr);
	       if (gfx2_solid[code] == 1) {// some transp
		   Draw16x16_Trans_Mapped_flip_Rot(&gfx2[code << 8],
			   sx+32,sy+16,
			   map,
			   flipx+(flipy<<1));
		   if (sx < 16)
		       Draw16x16_Trans_Mapped_flip_Rot(&gfx2[code << 8],
			       256+32+sx,sy+16,
			       map,
			       flipx+(flipy<<1));
	       } else {
		   Draw16x16_Mapped_flip_Rot(&gfx2[code << 8],
			   sx+32,sy+16,
			   map,
			   flipx+(flipy<<1));
		   if (sx < 16)
		       Draw16x16_Mapped_flip_Rot(&gfx2[code << 8],
			       256+32+sx,sy+16,
			       map,
			       flipx+(flipy<<1));
	       }
	   }
       }
   }
   // printf("\n");
   // The layer seems super weird, there is some sort of priority field (attr & 0x20)
   // but the tiles with this bit set have a strange transparency
   // drawing everything opaque seems to work for now.
   // Notice these tiles have priority over sprites
   // This shows for example during intro : the dragon 1st appears on the left of the screen, but hidden by these priorities
   // it allows him to 1st appear smoothly from the right and disappear to the left
   // without priorities it's already on the left of the screen when the intro starts
   START_SCROLL_256x256_2_8_R180(32,16,256,256);

      ta = RAM[0xC000+zz];
      attr = RAM[0xC000+zz+1];
      ta += ((attr & 0xc0) << 2) + 0x400 + 0x800 * char_bank;
      if (attr & 0x20) {
	  flip = ((attr >> 3) & 3) ^ 3;
	  MAP_PALETTE_MAPPED_NEW(
		  attr & 0xf,
		  16,
		  map
		  );

	  /* This is a simplification of the crazy priority system for this game :
	   * it aims at working around the impossibility to draw sprites offscreen
	   * since x is on 1 byte and the screen is 256 pixels wide.
	   * But it's super weird, the transparent colors change for the "on top"
	   * sprites, and they really require a priority bitmap.
	   * The *much* easier way is to draw the top sprites opaque.
	   * It works almost everywhere, the only place I found where it doesn't work
	   * is when inserting a coin on the title screen, the character sprite which
	   * appears between the letters is half hidden.
	   * That's not too bad for such a simplification, and with that the dragon
	   * animation during attract mode is working fine !
	   * Notice : I also tried to draw sprites with high priority above this layer
	   * but it breaks the dragon animation in this case, so that's really the best
	   * solution without a priority bitmap ! */
	  Draw8x8_Mapped_flip_Rot(&GFX[(ta<<6)], x, y, map,flip);
      }

   END_SCROLL_256x256_2_8();
}

/*

C000-C7FF - BG0
---------------

- 64 bytes/line
- 256x256 size

-----+--------+---------------
Byte | Bit(s) | Use
-----+76543210+---------------
  0  |xx......| Tile (8-9)?
  0  |....x...| Flip Y Axis
  1  |xxxxxxxx| Tile (0-7)
-----+--------+---------------


D500-D7FF - CTRL DATA
---------------------

- 4 bytes/sprite
- D500 BG0 scroll (sprite?)

-----+--------+---------------
Byte | Bit(s) | Use
-----+76543210+---------------
  0  |xxxxxxxx| Sprite X (low)
  1  |xxx.....| Offset (low)
  1  |...xxxxx| Offset (high)
  2  |xxxxxxxx| Sprite Y (low)
-----+--------+---------------


*/

static gfx_layout charlayout =
{
	8,8,
	RGN_FRAC(1,2),
	4,
	{ RGN_FRAC(1,2)+0, RGN_FRAC(1,2)+4, 0, 4 },
	{ 3, 2, 1, 0, 8+3, 8+2, 8+1, 8+0 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
	16*8
};

static gfx_layout spritelayout =
{
	16,16,
	RGN_FRAC(1,2),
	4,
	{ RGN_FRAC(1,2)+0, RGN_FRAC(1,2)+4, 0, 4 },
	{ 3, 2, 1, 0, 8+3, 8+2, 8+1, 8+0,
			16*8+3, 16*8+2, 16*8+1, 16*8+0, 16*8+8+3, 16*8+8+2, 16*8+8+1, 16*8+8+0 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16,
			16*16, 17*16, 18*16, 19*16, 20*16, 21*16, 22*16, 23*16 },
	64*8
};

static struct GFX_LIST flstory_gfx[] =
{
   { REGION_GFX1, &charlayout, },
   { REGION_GFX1, &spritelayout, },
   { 0,           NULL,        },
};

static struct VIDEO_INFO video_flstory =
{
   draw_flstory,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
   flstory_gfx,
   59.871277
};
static struct DIR_INFO dir_flstory[] =
{
   { "fairy_land_story", },
   { "flstory", },
   { NULL, },
};
GME( flstory, "The FairyLand Story", TAITO, 1985, GAME_PLATFORM,
	.board = "A45",
);

