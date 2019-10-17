#include "sasound.h"
#include "2151intf.h"
#include "2203intf.h"
#include "2610intf.h"
#include "adpcm.h"
#include "msm5205.h"
#include "msm5232.h"
#include "ay8910.h"
#include "3812intf.h"
#include "smp16bit.h"
#include "m6585.h"
#include "ymz280b.h"
#include "es5506.h"
#include "qsound.h"
#include "ymf278b.h"
#include "streams.h"
#include "namco.h"
#include "x1_010.h"
#include "dac.h"
#include "dxsmp.h"
#include "2413intf.h"
#include "debug.h"

int change_sample_rate;

struct SOUND_CHIP sound_chip_list[] = // Not static for dlg_about.c
{
#if HAS_YM2203
   { "ym2203",     YM2203_sh_stop,        },
#endif
#if HAS_YM2151
   { "ym2151",     YM2151_sh_stop,        },
#endif
#if HAS_YM2151_ALT
   { "ym2151",     YM2151_sh_stop,        },
#endif
#if HAS_YM2610
   { "ym2610",     YM2610_sh_stop,        },
#endif
#if HAS_YM2610B
   { "ym2610b",    YM2610_sh_stop,        },
#endif
#if HAS_MSM5205_BUFF
   { "msm5205_BUFF",    MSM5205buffer_sh_stop, },
#endif
#if HAS_MSM5232
   { "msm5232",    MSM5232_sh_stop, },
#endif
#if HAS_ADPCM
   { "m6295",      OKIM6295_sh_stop,   },
#endif
#if HAS_AY8910
   { "ay9810",     NULL,                  },
#endif
#if HAS_YM3812
   { "ym3812",     YM3812_sh_stop,        },
#endif
   { "sn76496",    NULL,                  },
#if HAS_YM2413
   { "ym2413",     YM2413_sh_stop,        },
#endif
#if HAS_SMP16
   { "smp16bit",   SMP16buffer_sh_stop,   },
#endif
#if HAS_M6585
   { "m6585",      M6585buffer_sh_stop,   },
#endif
#if HAS_YMZ280B
   { "ymz280b",    YMZ280B_sh_stop,       },
#endif
#if HAS_ES5505
   { "es5505",     ES5505_sh_stop,        },
   { "es5506",     ES5506_sh_stop,        },
#endif
#if HAS_QSOUND
   { "qsound",    qsound_sh_stop,       },
#endif
#if HAS_YMF278B
   { "ymf278b",   YMF278B_sh_stop,       },
#endif
#if HAS_NAMCO
   { "namco", namco_sh_stop },
#endif
#if HAS_X1_010
   { "seta x1 010", seta_sh_stop },
#endif
#if HAS_DAC
   { "dac", NULL },
#endif
#if HAS_DXSMP
   { "DX samples", dxsmp_sh_stop },
#endif
   { NULL,	   NULL,		  },
};

char *get_sound_chip_name(UINT32 id)
{
   return sound_chip_list[id].name;
}

static int emulators_active = 0;

int init_sound_emulators(void)
{
   int i,j;

   if(change_sample_rate)
      saStopSoundEmulators();
   if (emulators_active)
     return 0;

   change_sample_rate = 0;
   if( SndMachine ){
    if( !SndMachine->first ){
      saInitVolPan();		/* moved. (hiro-shi) */
      SndMachine->first = 1;	/* first flag clear */
      streams_sh_start();	/* streaming system initialize & start */
      for( j = 0; j < SndMachine->control_max; j++ ){
	switch( SndMachine->init[j] ){
#if HAS_YM2203
	case SOUND_YM2203:
	  i = YM2203_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YM2151
	case SOUND_YM2151S:
		  i = YM2151_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YM2413
	case SOUND_YM2413:
		  i = YM2413_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YM2151_ALT
	case SOUND_YM2151J:
	  i = YM2151_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YM2610
	case SOUND_YM2610:
	  i = YM2610_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YM2610B
	case SOUND_YM2610B:
	  i = YM2610B_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_MSM5205_BUFF
	case SOUND_MSM5205_BUFF:
	  i = MSM5205buffer_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_MSM5232
	case SOUND_MSM5232:
	  i = MSM5232_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_ADPCM
	case SOUND_M6295:
	  i = OKIM6295_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_AY8910
	case SOUND_AY8910:
	  i = AY8910_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YM3812
	case SOUND_YM3812:
	  i = YM3812_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_SMP16
	case SOUND_SMP16:
	  i = SMP16buffer_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_M6585
	case SOUND_M6585:
	  i = M6585buffer_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_YMZ280B
	case SOUND_YMZ280B:
	  i = YMZ280B_sh_start( SndMachine->intf[j] );
	break;
#endif
#if HAS_ES5505
	case SOUND_ES5505:
	  i = ES5505_sh_start( SndMachine->intf[j] );
	  break;
	case SOUND_ES5506:
	  i = ES5506_sh_start( SndMachine->intf[j] );
	  break;
#endif
#if HAS_QSOUND
	case SOUND_QSOUND:
	  i = qsound_sh_start( SndMachine->intf[j] );
	  break;
#endif
#if HAS_YMF278B
	case SOUND_YMF278B:
	  i = YMF278B_sh_start( SndMachine->intf[j] );
	  break;
#endif
#if HAS_NAMCO
	case SOUND_NAMCO:
	  i = namco_sh_start( SndMachine->intf[j] );
	  break;
#endif
#if HAS_X1_010
	case SOUND_X1_010:
	  i = seta_sh_start( SndMachine->intf[j] );
	  break;
#endif
#if HAS_DAC
	case SOUND_DAC:
	  i = DAC_sh_start( SndMachine->intf[j] );
	  break;
#endif
#if HAS_DXSMP
	case SOUND_DXSMP:
	  i = dxsmp_sh_start( SndMachine->intf[j] );
	  break;
#endif
	default:
	  i = 1;
	break;
	}
	if( i ){
	  audio_sample_rate = 0;
	  SndMachine = NULL;
	  printf("emulator init failed\n");
	  return 1;
	}
      }
    }
  }
   emulators_active = 1;
  return 0;
}

/*********************************************************************/
/* stop sound emulators: this is needed for when sample rate changes */
/*********************************************************************/
void saStopSoundEmulators(void)
{
   int i;
   print_debug("SaStopSoundEmulators()\n");

   emulators_active = 0;
   saResetPlayChannels();
   if( SndMachine == NULL ){
      SndMachine = &snd_entry;
   }
   else{
     if(SndMachine->first!=0){		// YM3812 fix crashes
       streams_sh_stop();
       for( i = 0; i < SndMachine->control_max; i++ ){

	 if( sound_chip_list[SndMachine->init[i]].shutdown )
	   sound_chip_list[SndMachine->init[i]].shutdown();
       }
       SndMachine->first	   = 0;
     }
   }
}
