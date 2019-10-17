/******************************************************************************/
/*									      */
/*	      TAITO SOUND SYSTEMS (C) 1986-1996 TAITO CORPORATION	      */
/*									      */
/******************************************************************************/

/*

answer of hiroshi
-----------------
YM30?? series is Serial DAC convertor. FM chip output is Serial DAC.
This DAC input to YM30??. It change to Analog data.

Antiriad: Thanks!!

Changes
-------

17-02-99:

- Reduce volume of YM2151 emulation.

11-02-99:

- z80 emulator and banking was changed some days ago...
- added tc0140syt_reset() calls.

18-01-99:

- tc0140syt emulation is moved to tc140syt.c/h.

14-01-99:

- Merge changes from Hiroshi source (M6295 bank, ym2151: reg -> reg2151).

09-01-99:

- Add debug message if 68000 sends data before z80 has read the current
  data.

27-12-98:

- Add Hiroshi changes (Volume and Panning).
- What is YM3016? Is this the chip for panning/volume control?

17-12-98:

- Added latest Hiro-Shi changes.
- Removed YM2610_Frame(), no longer needed.
- Removed Z80 debug as there is already Z80 bad read/write/io routines
  in mz80help.c.

16-12-98:

- Added YM2203 (Taito B-System). Used by Master of Weapons etc...

*/

#include "gameinc.h"
#include "taitosnd.h"
#include "fm.h"
#include "sasound.h"            // sample support routines
#include "2610intf.h"
#include "2151intf.h"
#include "2203intf.h"
#include "adpcm.h"
#include "timer.h"
#include "streams.h"

static UINT8 *ROMBANK=NULL;	// Pointer to start of z80 rom bank data
static UINT8 *BANKLIST[8];	// Pointers to start of each bank (0-7)

/************************************************************/

// YM2151 Handler
// --------------
static int reg2151;

UINT16 YM2151ReadZ80(UINT16 offset)
{
#if 0
  if( (offset&0x01) ){
    return YM2151_status_port_0_r(0);
  } else
    return 0;
#else

  static int ta=0;
  ta^=255;
  return(ta);

#endif
}

UINT16 YM2151ReadZ80_Timer(UINT16 offset)
{
#if 1
  if( (offset&0x01) ){
    return YM2151_status_port_0_r(0);
  } else
    return 0;
#else

  static int ta=0;
  ta^=255;
  return(ta);

#endif
}

void YM2151WriteZ80(UINT16 offset, UINT8 data)
{
   if((offset&1)==0){
      reg2151=data;
   }
   else{
     YM2151_register_port_0_w(offset,reg2151);	// It's faster to wait for the data like this!!
     YM2151_data_port_0_w(offset,data);
   }
}

// Banking via YM2151 - TAITO

void YM2151TaitoWriteZ80(UINT16 offset, UINT8 data)
{

   if((offset&1)==0){
      reg2151=data;
   }
   else{
      if(reg2151==0x1B){
	 TaitoSoundSetBank(offset, (UINT8) ((data>>6)&3) );
      }
      YM2151_register_port_0_w(offset,reg2151); // It's faster to wait for the data like this!!
      YM2151_data_port_0_w(offset,data);
   }
}

/************************************************************/

// YM2203A Handler
// ---------------

UINT16 YM2203AReadZ80(UINT16 offset)
{
   #if 0

   if((offset&1)==0){
      return YM2203_status_port_0_r(0);
   }
   else{
      return YM2203_read_port_0_r(0);
   }

   #else

   static int ta=0;
   ta^=255;
   return(ta);

#endif
}

void YM2203AWriteZ80(UINT16 offset, UINT8 data)
{
   static int reg;

   if((offset&1)==0){
      reg=data;
   }
   else{
      YM2203_control_port_0_w(offset,reg);
      YM2203_write_port_0_w(offset,data);
   }
}

// Banking via YM2203 - TAITO

void YM2203ATaitoWriteZ80(UINT16 offset, UINT8 data)
{
   static int reg;

   if((offset&1)==0){
      reg=data;
   }
   else{
      if(reg==0x0E){
	 TaitoSoundSetBank(offset, (UINT8) (data&3) );
      }
      YM2203_control_port_0_w(offset,reg);
      YM2203_write_port_0_w(offset,data);
   }
}

// YM2203A Handler
// ---------------

UINT16 YM2203BReadZ80(UINT16 offset)
{
   #if 0

   if((offset&1)==0){
      return YM2203_status_port_1_r(0);
   }
   else{
      return YM2203_read_port_1_r(0);
   }

   #else	// Cadash and Rainbow Extra only work with this code>>>

   static int ta=0;
   ta^=255;
   return(ta);

#endif
}

void YM2203BWriteZ80(UINT16 offset, UINT8 data)
{
   static int reg;

   if((offset&1)==0){
      reg=data;
   }
   else{
      YM2203_control_port_1_w(offset,reg);
      YM2203_write_port_1_w(offset,data);
   }
}

/************************************************************
 Taito Z80+YM2610 Interface
 --------------------------
 For 99% of Taito sound Z80s using a YM2610
************************************************************/

// YM2610 Handler
// --------------

UINT16 YM2610ReadZ80(UINT16 offset)
{
#if 1
  switch(offset&3){
  case 0x00: return(YM2610_status_port_0_A_r(offset));
  case 0x01: return(YM2610_read_port_0_r(offset));
  case 0x02: return(YM2610_status_port_0_B_r(offset));
  default:   return(YM2610_read_port_0_r(offset));
  }
#else

  static int ta=0;
  ta^=255;
  return(ta);

#endif
}

UINT16 YM2610ReadZ80SP(UINT16 offset){
  // Speed patch
  static int ta = 0;
  switch(offset&3){
  case 0x00:
    ta ^= 0x03;
    return YM2610_status_port_0_A_r(offset) | ta;
    //return(YM2610_status_port_0_A_r(offset));

  case 0x02: return(YM2610_status_port_0_B_r(offset));	break;
  default:   return(YM2610_read_port_0_r(offset));    break;
  }
}

void YM2610WriteZ80(UINT16 offset, UINT8 data)
{
   switch(offset&3){
      case 0x00: YM2610_control_port_0_A_w(offset,data); break;
      case 0x01: YM2610_data_port_0_A_w(offset,data);	 break;
      case 0x02: YM2610_control_port_0_B_w(offset,data); break;
      default:	 YM2610_data_port_0_B_w(offset,data);	 break;
   }
}

static int taitoym2610pan[4];
void Pan2610WriteZ80(UINT16 offset, UINT8 data){
  int vol, pan, cen;
  taitoym2610pan[offset&0x03] = data&0x00ff;
  if( !(offset&0x02) ){
    /**** channel 0 (YM3016 Left channel) ****/
    if( taitoym2610pan[0] > taitoym2610pan[1] )  pan = taitoym2610pan[0];
    else					 pan = taitoym2610pan[1];
    if (pan == 0x1f) pan = 0xff;
    vol = (taitoym2610pan[0] + taitoym2610pan[1]) / 2;
    if( pan ){
      pan = 0x80 + (((0x7f00/pan) * (taitoym2610pan[0] - taitoym2610pan[1]))>>8);
      cen = pan < 0x80 ? 0x80 - pan : -(0x80 - pan);
      vol = vol - ((vol * cen)>>(8));
      // vol is sometimes 0x1f. It is a bad mapping
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0), vol );
      stream_set_pan( YM2610_get_stream_num(0), pan );
      //print_ingame(120,gettext("Make ch0 vol:%02x pan:%02x"), vol, pan );
    } else{
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0), vol>>1 );
      stream_set_pan( YM2610_get_stream_num(0), 0x80 ); /* center */
    }
  } else{
    /**** channel 1 (YM3016 Right channel) ****/
    if( taitoym2610pan[2] > taitoym2610pan[3] )  pan = taitoym2610pan[2];
    else					 pan = taitoym2610pan[3];
    if (pan == 0x1f) pan = 0xff;
    vol = (taitoym2610pan[2] + taitoym2610pan[3]) / 2;
    if( pan ){
      pan = 0x80 + (((0x7f00/pan) * (taitoym2610pan[2] - taitoym2610pan[3]))>>8);
      cen = pan < 0x80 ? 0x80 - pan : -(0x80 - pan);
      vol = vol - ((vol * cen)>>(8));
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0)+1, vol );
      stream_set_pan( YM2610_get_stream_num(0)+1, pan );
      //print_ingame(120,gettext("Make ch1 vol:%02x pan:%02x"), vol, pan );
    } else{
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0)+1, vol>>1 );
      stream_set_pan( YM2610_get_stream_num(0)+1, 0x80 ); /* center */
    }
  }
}

static int volume_offset;

void Pan2610_OffsetVol( int data ){
  volume_offset = data;
}

void Pan2610WriteZ80_OffsetVol(UINT16 offset, UINT8 data){
  int vol, pan, cen;
  taitoym2610pan[offset&0x03] = data&0x00ff;
  if( !(offset&0x02) ){
    /**** channel 0 (YM3016 Left channel) ****/
    if( taitoym2610pan[0] > taitoym2610pan[1] )  pan = taitoym2610pan[0];
    else					 pan = taitoym2610pan[1];
    if (pan == 0x1f) pan = 0xff;
    vol = ((taitoym2610pan[0] + taitoym2610pan[1]) / 2)<<volume_offset;
    if( pan ){
      pan = 0x80 + (((0x7f00/pan) * (taitoym2610pan[0] - taitoym2610pan[1]))>>8);
      cen = pan < 0x80 ? 0x80 - pan : -(0x80 - pan);
      vol = vol - ((vol * cen)>>(8));
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0), vol );
      stream_set_pan( YM2610_get_stream_num(0), pan );
      //print_ingame(120,gettext("Make ch0 vol:%02x pan:%02x"), vol, pan );
    } else{
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0), vol>>1 );
      stream_set_pan( YM2610_get_stream_num(0), 0x80 ); /* center */
    }
  } else{
    /**** channel 1 (YM3016 Right channel) ****/
    if( taitoym2610pan[2] > taitoym2610pan[3] )  pan = taitoym2610pan[2];
    else					 pan = taitoym2610pan[3];
    if (pan == 0x1f) pan = 0xff;
    vol = ((taitoym2610pan[2] + taitoym2610pan[3]) / 2)<<volume_offset;
    if( pan ){
      pan = 0x80 + (((0x7f00/pan) * (taitoym2610pan[2] - taitoym2610pan[3]))>>8);
      cen = pan < 0x80 ? 0x80 - pan : -(0x80 - pan);
      vol = vol - ((vol * cen)>>(8));
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0)+1, vol );
      stream_set_pan( YM2610_get_stream_num(0)+1, pan );
      //print_ingame(120,gettext("Make ch1 vol:%02x pan:%02x"), vol, pan );
    } else{
      if (vol == 0x1f) vol = 0xff;
      stream_set_volume( YM2610_get_stream_num(0)+1, vol>>1 );
      stream_set_pan( YM2610_get_stream_num(0)+1, 0x80 ); /* center */
    }
  }
}

static UINT8 TYM = 0x07;
UINT16 TaitoYM2610Test(UINT16 offset){
  return TYM;
}

static struct YM2610interface ym2610_interface =
{
  1,
  8000000,
  { (100 | (OSD_PAN_CENTER<<8) ) },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { z80_irq_handler },
  { REGION_SOUND2 },	/* Delta-T */
  { REGION_SOUND1 },	/* ADPCM */
  { YM3012_VOL(255,OSD_PAN_LEFT,255,OSD_PAN_RIGHT) },
};

struct SOUND_INFO taito_ym2610_sound[] =
{
   { SOUND_YM2610,  &ym2610_interface,	},
   { 0, 	    NULL,		},
};

// the ay8910 emits an annoying sound as soon as the race starts
// no idea why, but the easiest solution is to mute it !
static struct YM2610interface ym2610_interface_mute_ay8910 =
{
  1,
  8000000,
  { YM2203_VOL(0,0) },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { z80_irq_handler },
  { REGION_SOUND2 },	/* Delta-T */
  { REGION_SOUND1 },	/* ADPCM */
  { YM3012_VOL(255,OSD_PAN_LEFT,255,OSD_PAN_RIGHT) },
};

struct SOUND_INFO contcirc_ym2610_sound[] =
{
   { SOUND_YM2610,  &ym2610_interface_mute_ay8910,	},
   { 0, 	    NULL,		},
};

struct SOUND_INFO taito_ym2610b_sound[] =
{
   { SOUND_YM2610B, &ym2610_interface,	},
   { 0, 	    NULL,		},
};

/**** not pan control (lock volume) ****/
void Taito2610_Frame(void){
  //cpu_execute_cycles(CPU_Z80_0, (4000000/60)*2);			// Sound Z80
  execute_z80_audio_frame(); // How short !
}

/*******************************************************/
/*    YM2610 mem map control (normal type)	       */
/*******************************************************/
void TaitoYM2610Memmap( void )
{
  /* The z80 ram is in the middle of the rom banks !
     This has been done by Antiriad, which means that the z80 ram is not saved in the savegames
     Since the ym2610 is not saved neither yet, it does not seem to make any harm.
     It does not overwrite any code because the rom has been copyed to banks before that */
/*   UINT8 *z80ram = RAM + RAMSize; */
/*   RAMSize += 0x2000; */

  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

  AddZ80AReadByte(0x0000, 0x7FFF, NULL, 			NULL);			// BANK ROM
  AddZ80AReadByte(0xC000, 0xDFFF, NULL, 			Z80ROM+0x00C000);	// Z80 RAM
  AddZ80AReadByte(0xE000, 0xE003, YM2610ReadZ80,		NULL);			// YM2610
  AddZ80AReadByte(0xE200, 0xE201, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
  AddZ80AReadByte(0xEA00, 0xEA00, TaitoYM2610Test,		NULL);
  AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
  AddZ80AReadByte(    -1,     -1, NULL, 			NULL);

  AddZ80AWriteByte(0xC000, 0xDFFF, NULL,			Z80ROM+0x00C000);	// Z80 RAM
  AddZ80AWriteByte(0xE000, 0xE003, YM2610WriteZ80,		NULL);			// YM2610
  AddZ80AWriteByte(0xE200, 0xE201, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
  if (!is_current_game("psyforce"))
      AddZ80AWriteByte(0xE400, 0xE403, Pan2610WriteZ80,		NULL);			// PANNING
  AddZ80AWriteByte(0xF200, 0xF200, TaitoSoundSetBank,		NULL);			// BANK SELECT
  AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
  AddZ80AWriteByte(    -1,     -1, NULL,			NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
  AddZ80AReadPort(  -1,   -1, NULL,			NULL);

  AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
  AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);
  AddZ80AWritePort(  -1,   -1, NULL,			NULL);

  AddZ80AInit();

  TaitoSoundSetBank(0,1);

  taitoym2610pan[0] = 0x00;
  taitoym2610pan[1] = 0x00;
  taitoym2610pan[2] = 0x00;
  taitoym2610pan[3] = 0x00;

  tc0140syt_reset();
}

/*******************************************************/
/*    YM2610 mem map control (normal type)	       */
/*******************************************************/
void TaitoYM2610MemmapOffsetVol( void )
{
  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

  AddZ80AReadByte(0x0000, 0x7FFF, NULL, 			NULL);			// BANK ROM
  AddZ80AReadByte(0xC000, 0xDFFF, NULL, 			Z80ROM+0x00C000);	// Z80 RAM
  AddZ80AReadByte(0xE000, 0xE003, YM2610ReadZ80,		NULL);			// YM2610
  AddZ80AReadByte(0xE200, 0xE201, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
  AddZ80AReadByte(0xEA00, 0xEA00, TaitoYM2610Test,		NULL);
  AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
  AddZ80AReadByte(    -1,     -1, NULL, 			NULL);

  AddZ80AWriteByte(0xC000, 0xDFFF, NULL,			Z80ROM+0x00C000);	// Z80 RAM
  AddZ80AWriteByte(0xE000, 0xE003, YM2610WriteZ80,		NULL);			// YM2610
  AddZ80AWriteByte(0xE200, 0xE201, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
  AddZ80AWriteByte(0xE400, 0xE403, Pan2610WriteZ80_OffsetVol,	NULL);			// PANNING
  AddZ80AWriteByte(0xF200, 0xF200, TaitoSoundSetBank,		NULL);			// BANK SELECT
  AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
  AddZ80AWriteByte(    -1,     -1, NULL,			NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
  AddZ80AReadPort(  -1,   -1, NULL,			NULL);

  AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
  AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);
  AddZ80AWritePort(  -1,   -1, NULL,			NULL);

  AddZ80AInit();

  TaitoSoundSetBank(0,1);

  taitoym2610pan[0] = 0x00;
  taitoym2610pan[1] = 0x00;
  taitoym2610pan[2] = 0x00;
  taitoym2610pan[3] = 0x00;

  tc0140syt_reset();
}

/*******************************************************/
/*    YM2610 sound system init			       */
/*******************************************************/
void AddTaitoYM2610(UINT32 p1, UINT32 p2, UINT32 romsize){
  // Apply Speed Patch
  // -----------------
  print_debug( "AddYM2610System\n" );

  if (p1) {
    Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
    Z80ROM[p1+1]=0xAA;	//

    SetStopZ80Mode2( (UINT16) p2);
  }

   // Setup rom banking system
   // ------------------------

   AddTaitoSoundBanking( Z80ROM, romsize );

   // Setup Z80 memory map
   // --------------------

   TaitoYM2610Memmap();

  print_debug( "AddYM2610System end\n" );
}

/*******************************************************/
/*    YM2610B sound system init 		       */
/*******************************************************/
void AddTaitoYM2610B(UINT32 p1, UINT32 p2, UINT32 romsize){
  // Apply Speed Patch
  // -----------------
  print_debug( "AddYM2610System\n" );

  Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
  Z80ROM[p1+1]=0xAA;	//

  SetStopZ80Mode2( (UINT16) p2);

  // Setup rom banking system
  // ------------------------

  AddTaitoSoundBanking( Z80ROM, romsize );

  // Setup Z80 memory map
  // --------------------

  TaitoYM2610Memmap();

  print_debug( "AddYM2610System end\n" );
}

/*******************************************************/
/*    YM2610B sound system init 		       */
/*******************************************************/
void AddTaitoYM2610B_OffsetVol(UINT32 p1, UINT32 p2, UINT32 romsize, int vol){
  // Apply Speed Patch
  // -----------------
  print_debug( "AddYM2610System\n" );

  Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
  Z80ROM[p1+1]=0xAA;	//

  SetStopZ80Mode2( (UINT16) p2);

  // Setup rom banking system
  // ------------------------

  AddTaitoSoundBanking( Z80ROM, romsize );

  // Setup Z80 memory map
  // --------------------

  TaitoYM2610MemmapOffsetVol();

  Pan2610_OffsetVol( vol );	/* set volume shift size */

  print_debug( "AddYM2610System end\n" );
}

/************************************************************/
/************************************************************/
void RemoveTaitoYM2610(void)
{
   RemoveTaitoSoundBanking();
}


#if 0
static void TaitoYM2151WriteBank( int ctw ){
  //print_ingame(120,gettext("NowBank = %02x"), ctw );
  TaitoSoundSetBank( 0, (UINT8) (ctw&0x03) ); /* bank change */
}

static void TaitoYM2151_irq_handler(void){
  //print_ingame(120,gettext("IRQ") );
  //cpu_interrupt(CPU_Z80_0, 0x0038);
}
#endif

static struct YM2151interface ym2151_interface =
{
  1,			// 1 chip
  4000000,		// 4 MHz
  { YM3012_VOL(160,OSD_PAN_LEFT,160,OSD_PAN_RIGHT) },
  { z80_irq_handler },
  { NULL }
};

struct SOUND_INFO taito_ym2151_sound[] =
{
   { SOUND_YM2151J, &ym2151_interface,	},
   { 0, 	    NULL,		},
};

void Taito2151_Frame(void)
{
   if(tc0140syt_want_nmi()) cpu_int_nmi(CPU_Z80_0);
   execute_z80_audio_frame();
}

void Taito2151_FrameFast(void)
{
   if(tc0140syt_want_nmi()!=0) cpu_int_nmi(CPU_Z80_0);

   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(6,60));	// Z80 6MHz (60fps)
   /*#ifdef RAINE_DEBUG
     print_debug("Z80PC0:%04x\n",z80pc);
#endif*/
   cpu_interrupt(CPU_Z80_0, 0x38);
}

void Taito2151_FrameRI(void)
{
   if(tc0140syt_want_nmi()!=0){
      if(tc0140syt_get_port01()!=0x00){ 	// Temp fix for Rainbow Islands
	 cpu_int_nmi(CPU_Z80_0);
      }
   }

   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(6,60));	// Z80 6MHz (60fps)
   /*#ifdef RAINE_DEBUG
     print_debug("Z80PC0:%04x\n",z80pc);
#endif*/
   cpu_interrupt(CPU_Z80_0, 0x38);
}

void Taito2151_Frame_xsystem(void)
{
/*     cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(8,60));	// Z80 8MHz (60fps) */
/*     cpu_interrupt(CPU_Z80_0, 0x38); */
      execute_z80_audio_frame();
}

void AddTaitoYM2151(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, UINT8 *adpcmB)
{
   // Apply Speed Patch
   // -----------------

   Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
   Z80ROM[p1+1]=0xAA;	//

   SetStopZ80Mode2( (UINT16) p2);

   // Setup rom banking system
   // ------------------------

   AddTaitoSoundBanking(Z80ROM, romsize);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x38, 0x66);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,			NULL);			// BANK ROM
   AddZ80AReadByte(0x8000, 0x8FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AReadByte(0x9000, 0x9001, YM2151ReadZ80,		NULL);			// YM2151
   AddZ80AReadByte(0xA000, 0xA001, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x8FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AWriteByte(0x9000, 0x9001, YM2151TaitoWriteZ80,	NULL);			// YM2151+BANKING
   AddZ80AWriteByte(0xA000, 0xA001, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
   if(adpcmA!=NULL){
   AddZ80AWriteByte(0xB000, 0xB006, adpcmA,			NULL);			// ADPCM CHANNEL A
   }
   if(adpcmB!=NULL){
   AddZ80AWriteByte(0xC000, 0xC006, adpcmB,			NULL);			// ADPCM CHANNEL B
   }
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   TaitoSoundSetBank(0,1);

   tc0140syt_reset();
}

void AddTaitoYM2151_Timer(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, UINT8 *adpcmB)
{
   // Apply Speed Patch
   // -----------------

   Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
   Z80ROM[p1+1]=0xAA;	//

   SetStopZ80Mode2( (UINT16) p2);

   // Setup rom banking system
   // ------------------------

   AddTaitoSoundBanking(Z80ROM, romsize);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x38, 0x66);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,			NULL);			// BANK ROM
   AddZ80AReadByte(0x8000, 0x8FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AReadByte(0x9000, 0x9001, YM2151ReadZ80_Timer, 	NULL);			// YM2151
   AddZ80AReadByte(0xA000, 0xA001, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x8FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AWriteByte(0x9000, 0x9001, YM2151TaitoWriteZ80,	NULL);			// YM2151+BANKING
   AddZ80AWriteByte(0xA000, 0xA001, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
   if(adpcmA!=NULL){
   AddZ80AWriteByte(0xB000, 0xB006, adpcmA,			NULL);			// ADPCM CHANNEL A
   }
   if(adpcmB!=NULL){
   AddZ80AWriteByte(0xC000, 0xC006, adpcmB,			NULL);			// ADPCM CHANNEL B
   }
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   TaitoSoundSetBank(0,1);

   tc0140syt_reset();
}

/*

more recent memory map:

 - it resembles the ym2610 one
 - banking is not via ym2151
 - no nmi (nmi will reset the cpu)
 - ym30xx volume and panning support?

*/

void AddTaitoYM2151_xsystem(UINT32 p1, UINT32 p2, UINT32 romsize)
{
   // Apply Speed Patch
   // -----------------

   Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
   Z80ROM[p1+1]=0xAA;	//

   SetStopZ80Mode2( (UINT16) p2);

   // Setup rom banking system
   // ------------------------

   AddTaitoSoundBanking(Z80ROM, romsize);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x38, 0x66);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,			NULL);			// BANK ROM
   AddZ80AReadByte(0xC000, 0xDFFF, NULL,			Z80ROM+0x00C000);	// Z80 RAM
   AddZ80AReadByte(0xE000, 0xE001, YM2151ReadZ80_Timer, 	NULL);			// YM2610
   AddZ80AReadByte(0xE200, 0xE201, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
   //AddZ80AReadByte(0xEA00, 0xEA00, TaitoYM2610Test,		NULL);
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadByte(    -1,     -1, NULL,			NULL);

   AddZ80AWriteByte(0xC000, 0xDFFF, NULL,			Z80ROM+0x00C000);	// Z80 RAM
   AddZ80AWriteByte(0xE000, 0xE001, YM2151WriteZ80,		NULL);			// YM2610
   AddZ80AWriteByte(0xE200, 0xE201, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
   //AddZ80AWriteByte(0xE400, 0xE403, Pan2610WriteZ80_OffsetVol,NULL);			// PANNING
   AddZ80AWriteByte(0xF200, 0xF200, TaitoSoundSetBank,		NULL);			// BANK SELECT
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
   AddZ80AWriteByte(	-1,	-1, NULL,			NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   TaitoSoundSetBank(0,1);

   tc0140syt_reset();
}

void RemoveTaitoYM2151(void)
{
   RemoveTaitoSoundBanking();
}

/******************************************************************************/
/*									      */
/*			 YM2203; M6295 / Taito B-System 		      */
/*			 ------------------------------ 		      */
/*									      */
/* - Master of Weapons, Hit the Ice, Violence Fight			      */
/*									      */
/******************************************************************************/


static struct YM2203interface ym2203_interface =
{
  1,			// 1 x YM2203
  3000000,		// Rate - Guessed
  { YM2203_VOL(200,50) },	// Volume Control
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { z80_irq_handler }
};

struct SOUND_INFO taito_ym2203_sound[] =
{
   { SOUND_YM2203,  &ym2203_interface,	},
   { 0, 	    NULL,		},
};

static struct OKIM6295interface m6295_interface =
{
   1,					// 1 chip
   { 8500 },				// rate
   { 0 },		// rom list
   { 250 },
};

struct SOUND_INFO taito_ym2203_m6295_sound[] =
{
   { SOUND_YM2203,  &ym2203_interface,	},
   { SOUND_M6295,   &m6295_interface,	},
   { 0, 	    NULL,		},
};

void M6295_Init(UINT8 *src, UINT32 size)
{
  ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),src,0x40000);
}

void Taito2203_Frame(void)
{
  execute_z80_audio_frame();

/*    cpu_execute_cycles(CPU_Z80_0, (4000000/60)*2); */
/*    /\*#ifdef RAINE_DEBUG */
/*      print_debug("Z80PC0:%04x\n",z80pc); */
/*    #endif*\/ */
/*    cpu_interrupt(CPU_Z80_0, 0x0038); */
}

void AddTaitoYM2203(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcm, UINT32 adpcmsize)
{
   // Apply Speed Patch
   // -----------------

   Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
   Z80ROM[p1+1]=0xAA;	//

   SetStopZ80Mode2( (UINT16) p2);

   // Setup rom banking system
   // ------------------------

   AddTaitoSoundBanking(Z80ROM, romsize);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,			NULL);			// BANK ROM
   AddZ80AReadByte(0x8000, 0x8FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AReadByte(0x9000, 0x9001, YM2203AReadZ80,		NULL);			// YM2203
   AddZ80AReadByte(0xA000, 0xA001, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
   if(adpcm!=NULL){
   AddZ80AReadByte(0xB000, 0xB000, M6295_A_Read_Z80,		NULL);			// ADPCM CHANNEL A
   }
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x8FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AWriteByte(0x9000, 0x9001, YM2203ATaitoWriteZ80,	NULL);			// YM2203+BANK SELECT
   AddZ80AWriteByte(0xA000, 0xA001, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
   if(adpcm!=NULL){
   AddZ80AWriteByte(0xB000, 0xB000, M6295_A_Write_Z80,	    NULL);			// ADPCM CHANNEL A
   }
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,	    NULL);
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   TaitoSoundSetBank(0,1);

   tc0140syt_reset();

   // Setup M6295
   // -----------
   if(adpcm) M6295_Init(adpcm, adpcmsize);

   // ExecuteSoundFrame=&Taito2203_Frame;
}

// Diff Memory Map [L-System Fighting Hawk]

void AddTaitoYM2203_B(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcm, UINT32 adpcmsize)
{
   // Apply Speed Patch
   // -----------------

   Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
   Z80ROM[p1+1]=0xAA;	//

   SetStopZ80Mode2( (UINT16) p2);

   // Setup rom banking system
   // ------------------------

   AddTaitoSoundBanking(Z80ROM, romsize);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,			NULL);			// BANK ROM
   AddZ80AReadByte(0x8000, 0x9FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AReadByte(0xF000, 0xF001, YM2203AReadZ80,		NULL);			// YM2203
   AddZ80AReadByte(0xE000, 0xE001, tc0140syt_read_sub_z80,	NULL);			// 68000 COMM
   if(adpcm!=NULL){
   AddZ80AReadByte(0xB000, 0xB000, M6295_A_Read_Z80,		NULL);			// ADPCM CHANNEL A
   }
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x9FFF, NULL,			Z80ROM+0x008000);	// Z80 RAM
   AddZ80AWriteByte(0xF000, 0xF001, YM2203ATaitoWriteZ80,	NULL);			// YM2203+BANK SELECT
   AddZ80AWriteByte(0xE000, 0xE001, tc0140syt_write_sub_z80,	NULL);			// 68000 COMM
   if(adpcm!=NULL){
   AddZ80AWriteByte(0xB000, 0xB000, M6295_A_Write_Z80,	    NULL);			// ADPCM CHANNEL A
   }
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,	    NULL);
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   TaitoSoundSetBank(0,1);

   tc0140syt_reset();

   // Setup M6295
   // -----------

   if(adpcm) M6295_Init(adpcm, adpcmsize);

   // ExecuteSoundFrame=&Taito2203_Frame;
}

void RemoveTaitoYM2203(void)
{
   RemoveTaitoSoundBanking();
}

/************************************************************/
/* Taito Z80 Banking interface				    */
/* ---------------------------				    */
/* For 99% of Taito sound Z80s				    */
/************************************************************/

// AddTaitoSoundBanking():
// Setup bank buffer

void AddTaitoSoundBanking(UINT8 *romsrc, UINT32 romsize)
{
  if (load_region[REGION_CPU2]) {
    z80_init_banks(0,REGION_CPU2,0x4000,0x4000);
  } else {
    int ta;

    // Make a copy of the rom banks

    ROMBANK = AllocateMem(romsize*2);

    if(romsize==0x08000){

      for(ta=0;ta<2;ta++){
	BANKLIST[ta+0] = ROMBANK+(ta*0x8000);
	BANKLIST[ta+2] = ROMBANK+(ta*0x8000);
	BANKLIST[ta+4] = ROMBANK+(ta*0x8000);
	BANKLIST[ta+6] = ROMBANK+(ta*0x8000);
	memcpy(BANKLIST[ta]+0x0000,romsrc,	    0x4000);
	memcpy(BANKLIST[ta]+0x4000,romsrc+(ta*0x4000),0x4000);
      }

    }

    if(romsize==0x10000){

      for(ta=0;ta<4;ta++){
	BANKLIST[ta+0] = ROMBANK+(ta*0x8000);
	BANKLIST[ta+4] = ROMBANK+(ta*0x8000);
	memcpy(BANKLIST[ta]+0x0000,romsrc,	    0x4000);
	memcpy(BANKLIST[ta]+0x4000,romsrc+(ta*0x4000),0x4000);
      }

    }

    if(romsize==0x20000){

      for(ta=0;ta<8;ta++){
	BANKLIST[ta] = ROMBANK+(ta*0x8000);
	memcpy(BANKLIST[ta]+0x0000,romsrc,	    0x4000);
	memcpy(BANKLIST[ta]+0x4000,romsrc+(ta*0x4000),0x4000);
      }

    }
  }
}

// RemoveTaitoSoundBanking():
// Remove bank buffer

void RemoveTaitoSoundBanking(void)
{
    if (ROMBANK) {
	FreeMem(ROMBANK);
	ROMBANK=NULL;
    }
}

// TaitoSoundSetBank():
// switch the current rom bank (0-7)

void TaitoSoundSetBank(UINT16 offset, UINT8 data)
{
   if (load_region[REGION_CPU2]) {
     z80_set_bank(0,(data-1) & 7);
   } else {
     Z80ASetBank( BANKLIST[data&7] );
   }
}

void YM2610SetBuffers(UINT8 *bufa, UINT8 *bufb, UINT32 sizea, UINT32 sizeb)
{
   YM2610_Rompointers[0] = bufa;
   YM2610_Rompointers[1] = bufb;
   YM2610_Romsizes[0]	 = sizea;
   YM2610_Romsizes[1]	 = sizeb;
}

/**********************************************************/

// First OKI 6295

void M6295_A_Write_68k( UINT32 address, UINT16 data )
{
  OKIM6295_data_0_w( 0, data&0xFF );
}

UINT16 M6295_A_Read_68k( UINT32 address )
{
  return 0; //OKIM6295_status_0_r( 0 );
}

void M6295_A_WriteBank_68k(UINT32 address,UINT16 data) { // bankswitch
  OKIM6295_bankswitch(0,data);
}

// Second OKI 6295

void M6295_B_Write_68k( UINT32 address, UINT16 data )
{
  OKIM6295_data_1_w( 1, data&0xFF );
}

UINT16 M6295_B_Read_68k( UINT32 address )
{
  return 0; //OKIM6295_status_1_r( 1 );
}

void M6295_B_WriteBank_68k( UINT32 address, UINT16 data ){
  OKIM6295_bankswitch(1,data);
}

/**********************************************************/

// First OKI 6295

void M6295_A_Write_Z80(UINT16 offset, UINT8 data)
{
  OKIM6295_data_0_w( 0, data );
}

UINT16 M6295_A_Read_Z80(UINT16 offset)
{
  return OKIM6295_status_0_r( 0 );
}

UINT16 M6295_A_ReadFree_Z80(UINT16 offset)
{
   return(0x00);
}

void M6295_A_WriteBank_Z80(UINT16 offset, UINT8 data){
  OKIM6295_bankswitch(0,data);
}

