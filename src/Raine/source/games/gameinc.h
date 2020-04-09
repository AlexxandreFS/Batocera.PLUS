
#ifdef __cplusplus
extern "C" {
#endif
// Includes for game drivers
// -------------------------

#include "raine.h"		// General Raine Stuff
#include "starhelp.h"		// M68000 support interface
#include "mz80help.h"		// Z80 support interface
#include "newspr.h"		// sprite drawing routines
#include "spr64.h"		// 64x64 sprite routines
#include "tilemod.h"		// sprite flipping/rotating/masking
#include "newmem.h"		// memory handling routines
#include "../control.h"		// control/input handling routines (../ is due to conflict with another control.h in direct-x)
#include "dsw.h"		// dipswitch handling routines
#include "ingame.h"		// screen handling routines
#include "palette.h"		// colour mapping routines
#include "scroll.h"		// scroll routines
#include "cpumain.h"		// generic cpu routines
#include "loadroms.h"		// sprite flipping/rotating/masking
#include "u020help.h"		// M68020 support interface
#include "games.h"		// game struct info


#ifdef __cplusplus
}
#endif
