#define DRV_DEF_SOUND taito_ym2610_sound
/* Current taito f2 driver - work in progress */

/* Most of this emulation is done by the external video chips :
   tc100scn for the background layers (and fg0)
   tc280grd/TC0430GRW for the tile with zoom/rotation

   In this file all I handle is the priorities, what mame calls the TC0360PRI.
   Congratulations to their team for their findings about this chip, no wonder
   Antiriad didn't guess it was a priority chip.

   Notice : the taito f2 is clearly not a standardized hardware, there are differences
   almost between every game, in the memory map, sometimes even in the video chips used.
   It's said on the web that dead connection and metal black use taito f2 hardware, but
   they don't use the tC100scn, they use a much more powerfull chip. So I will not emulate
   them here.

   Growl seems to have a bug, because I could reproduce it in mame : when you select your
   player, sometimes the background music does not start. It seems to depend on the time
   you spend before pressing the button. When you put 2 coins instead of 1, you have one
   more sound effect, and more chances that the music starts ! This bug made me quite
   crazy but it seems to be a game bug and not a raine bug.
   Also it tries to access what we call a tc220ioc for its inputs when it has none.
   Crappy code, really.
   There might be some sounds issues anyway, maybe the ym2610 does not start some
   samples sometimes but I am not totally sure...

   Here is the description of this chip from the info in mame.
   For the other 2 chips, look in tc100scn.c, tc005rot.c, and tc200obj.c for the sprites.

TC0360PRI
---------
Priority manager
A higher priority value means higher priority. 0 could mean disable but
I'm not sure. If two inputs have the same priority value, I think the first
one has priority, but I'm not sure of that either.
It seems the chip accepts three inputs from three different sources, and
each one of them can declare to have four different priority levels.

000 unknown. Could it be related to highlight/shadow effects in qcrayon2
    and gunfront?
001 in games with a roz layer, this is the roz palette bank (bottom 6 bits
    affect roz color, top 2 bits affect priority)
002 unknown
003 unknown

004 ----xxxx \       priority level 0 (unused? usually 0, pulirula sets it to F in some places)
    xxxx---- | Input priority level 1 (usually FG0)
005 ----xxxx |   #1  priority level 2 (usually BG0)
    xxxx---- /       priority level 3 (usually BG1)

006 ----xxxx \       priority level 0 (usually sprites with top color bits 00)
    xxxx---- | Input priority level 1 (usually sprites with top color bits 01)
007 ----xxxx |   #2  priority level 2 (usually sprites with top color bits 10)
    xxxx---- /       priority level 3 (usually sprites with top color bits 11)

008 ----xxxx \       priority level 0 (e.g. roz layer if top bits of register 001 are 00)
    xxxx---- | Input priority level 1 (e.g. roz layer if top bits of register 001 are 01)
009 ----xxxx |   #3  priority level 2 (e.g. roz layer if top bits of register 001 are 10)
    xxxx---- /       priority level 3 (e.g. roz layer if top bits of register 001 are 11)

00a unused
00b unused
00c unused
00d unused
00e unused
00f unused

Metalb uses in the PRI chip
---------------------------

+4	xxxx0000   BG1
	0000xxxx   BG0
+6	xxxx0000   BG3
	0000xxxx   BG2

About the clones :
I removed dinorexu and dinorexj, because they are just taito clones, which means only
1 region byte changes between the roms. The coinage changes too, but I really don't care
about the coinage.

Games known to use line scroll : don do kod, dino rex, thunder fox (every stage ?)
SSI can't use line scroll because it only uses sprites.
The others might use it at one place or another, but it's not easy to find !

*/

#include "gameinc.h"
#include "tc005rot.h"
#include "tc100scn.h"
#include "tc200obj.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "timer.h"
#include "blit.h"
#include "adpcm.h"
#include "tc110pcr.h"
#include "2203intf.h"

static UINT8 *TC0360PRI_regs;

/* Well this clone really looks like the original, but the roms are definetely different
   (see the hack in load_ssi : clearly different for the 2 roms. So well, let's keep it...
*/

static struct ROM_INFO rom_cameltry[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "c38-11",  0xbe172da0, "c38-14",  0xffa430de),
	/* empty! */
  { "c38-01.bin", 0x80000, 0xc170ff36, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "c38-02.bin", 0x20000, 0x1a11714b, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "c38-08.bin", 0x10000, 0x7ff78873, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
  { "c38-03.bin", 0x020000, 0x59fa59a7, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_camltrua[] =
{
	/* empty! */
  { "c38-us.15", 0x10000, 0x0e60faac, REGION_ROM2, 0x00000, LOAD_NORMAL },
	/* no Delta-T samples */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gunfront[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "c71-09.42",  0x10a544a2, "c71-08.41",  0xc17dc0a0),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x20000,
            "c71-10.40",  0xf39c0a06, "c71-14.39",  0x312da036),
  LOAD8_16(  REGION_ROM1,  0x80000,  0x20000,
            "c71-16.38",  0x1bbcc2d4, "c71-15.37",  0xdf3e00bb),
  { "c71-02.59", 0x100000, 0x2a600c92, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c71-03.19", 0x100000, 0x9133c605, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "c71-12.49", 0x10000, 0x0038c7f8, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
/* Pals c71-16.28  c71-07.27 */
  { "c71-01.29", 0x100000, 0x0e73105a, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_growl[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x40000,
            "c74-10.59",  0xca81a20b, "c74-08.61",  0xaa35dd9e),
  LOAD8_16(  REGION_ROM1,  0x80000,  0x40000,
            "c74-11.58",  0xee3bd6d5, "c74-14.60",  0xb6c24ec7),
  { "c74-01.34", 0x100000, 0x3434ce80, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c74-03.12", 0x100000, 0x1a0d8951, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "c74-02.11", 0x100000, 0x15a21506, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "c74-12.62", 0x10000, 0xbb6ed668, REGION_ROM2, 0, LOAD_NORMAL },
  { "c74-04.28", 0x100000, 0x2d97edf2, REGION_SMP1, 0x000000, LOAD_NORMAL },
/*Pals c74-06.48  c74-07.47 */
  { "c74-05.29", 0x080000, 0xe29c0828, REGION_SMP2, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_finalb[] =
{
  { "b82_09.10", 0x20000, 0x632f1ecd, REGION_ROM1, 0x00000, LOAD_8_16 },
  { "b82_17.11", 0x20000, 0xe91b2ec9, REGION_ROM1, 0x00001, LOAD_8_16 },
  { "b82-06.19", 0x20000, 0xfc450a25, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "b82-07.18", 0x20000, 0xec3df577, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "b82-04.4", 0x80000, 0x6346f98e, REGION_GFX2, 0x000000, LOAD_8_16 },
	/* Note: this is intentional to load at 0x180000, not at 0x100000
	   because finalb_driver_init will move some bits around before data
	   will be 'gfxdecoded'. The whole thing is because this data is 2bits-
	   while above is 4bits-packed format, for a total of 6 bits per pixel. */
  { "b82-03.5", 0x80000, 0xdaa11561, REGION_GFX2, 0x000001, LOAD_8_16 },
  { "b82-05.3", 0x80000, 0xaa90b93a, REGION_GFX2, 0x180000, LOAD_NORMAL },
  { "b82_10.16", 0x10000, 0xa38aaaed, REGION_ROM2, 0, LOAD_NORMAL },
  { "b82-02.1", 0x80000, 0x5dd06bdd, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "b82-01.2", 0x80000, 0xf0eb6846, REGION_SMP2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_solfigtr[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x40000,
            "c91-05.59",  0xc1260e7c, "c91-09.61",  0xd82b5266),
  { "c91-03.34", 0x100000, 0x8965da12, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c91-01.12", 0x100000, 0x0f3f4e00, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "c91-02.11", 0x100000, 0xe14ab98e, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "c91-07.62", 0x10000, 0xe471a05a, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
/*Pals c74-06.48 */
  { "c91-04.28", 0x80000, 0x390b1065, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mjnquest[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "c77-09",  0x0a005d01, "c77-08",  0x4244f775),
  { "c77-04", 0x080000, 0xc2e7e038, REGION_ROM1, 0x080000, LOAD_SWAP_16 },
  { "c77-01", 0x100000, 0x5ba51205, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c77-02", 0x100000, 0x6a6f3040, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "c77-05", 0x80000, 0xc5a54678, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "c77-10", 0x10000, 0xf16b2c1e, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
  { "c77-03", 0x080000, 0x312f17b1, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_f2demo[] =
{
   {  "lk_obj0.bin", 0x00080000, 0x1bb8aa37, REGION_GFX2, 0, LOAD_NORMAL },
   {  "lk_obj1.bin", 0x00080000, 0x75660aac, REGION_GFX2, 0x80000, LOAD_NORMAL },
   {   "lk_scr.bin", 0x00080000, 0xb178fb05, REGION_GFX1, 0, LOAD_NORMAL },
  LOAD8_16(  REGION_ROM1,  0,  0x00020000,
                "lq09.bin",  0x809a968b,     "lq11.bin",  0x7ba3a5cb),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x00020000,
                "lq10.bin",  0x7ee8cdcd,     "lq12.bin",  0x7ee8cdcd),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_dinorex[] =
{
  LOAD8_16(  REGION_ROM1,  	0x000000,  0x080000,
            "d39_14.9",  0xe6aafdac, "d39_16.8",  0xcedc8537),
  { "d39-04.6", 0x100000, 0x3800506d, REGION_ROM1, 	0x100000, LOAD_SWAP_16 },
  { "d39-05.7", 0x100000, 0xe2ec3b5d, REGION_ROM1, 	0x200000, LOAD_SWAP_16 },
  { "d39-06.2", 0x100000, 0x52f62835, REGION_GFX1, 	0x000000, LOAD_NORMAL },
  { "d39-01.29", 0x200000, 0xd10e9c7d, REGION_GFX2, 	0x000000, LOAD_NORMAL },
  { "d39-02.28", 0x200000, 0x6c304403, REGION_GFX2, 	0x200000, LOAD_NORMAL },
  { "d39-03.27", 0x200000, 0xfc9cdab4, REGION_GFX2, 	0x400000, LOAD_NORMAL },
  { "d39_12.5", 0x10000, 0x8292c7c1, REGION_ROM2, 0, LOAD_NORMAL },
  { "d39-07.10", 0x100000, 0x28262816, REGION_SMP1, 	0x000000, LOAD_NORMAL },
  { "d39-08.4", 0x080000, 0x377b8b7b, REGION_SMP2, 	0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_thundfox[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "c28-13-1.51",  0xacb07013, "c28-16-1.40",  0x1e43d55b),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x20000,
            "c28-08.50",  0x38e038f1, "c28-07.39",  0x24419abb),
  { "c28-02.61", 0x80000, 0x6230a09d, REGION_GFX1, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  0x00000,  0x80000,
            "c28-03.29",  0x51bdc7af, "c28-04.28",  0xba7ed535),
  { "c28-01.63", 0x80000, 0x44552b25, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "c28-14.3", 0x10000, 0x45ef3616, REGION_ROM2, 0, LOAD_NORMAL },
  { "c28-06.41", 0x80000, 0xdb6983db, REGION_SMP1, 0x00000, LOAD_NORMAL },
/* Pals: c28-09.25  c28-10.26  c28-11.35  b89-01.19  b89-03.37  b89-04.33 */
  { "c28-05.42", 0x80000, 0xd3b238fa, REGION_SMP2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_driveout[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "driveout.003",  0xdc431e4e, "driveout.002",  0x6f9063f4),
	/* empty */
  LOAD8_16(  REGION_GFX2,  0x00000,  0x40000,
            "driveout.084",  0x530ac420, "driveout.081",  0x0e9a3e9e),
  { "driveout.020", 0x8000, 0x99aaeb2e, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "driveout.028", 0x80000, 0xcbde0b66, REGION_SMP1, 0, LOAD_NORMAL },
  { "driveout.029", 0x20000, 0x0aba2026, REGION_SMP1, 0x20000, LOAD_NORMAL },
  { "driveout.029", 0x20000, 0x0aba2026, REGION_SMP1, 0x60000, LOAD_NORMAL },
  { "driveout.029", 0x20000, 0x0aba2026, REGION_SMP1, 0xa0000, LOAD_NORMAL },
  { "driveout.029", 0x20000, 0x0aba2026, REGION_SMP1, 0xe0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_driftout[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "do_46.rom",  0xf960363e, "do_45.rom",  0xe3fe66b9),
	/* empty */
  { "do_obj.rom", 0x80000, 0x5491f1c4, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "do_piv.rom", 0x80000, 0xc4f012f7, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "do_50.rom", 0x10000, 0xffe10124, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
  { "do_snd.rom", 0x80000, 0xf2deb82b, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ssi[] =
{
   {  "c64-01.1", 0x00100000, 0xa1b4f486, REGION_GFX2, 0x000000, LOAD_NORMAL, },
   {  "c64-02.2", 0x00020000, 0x3cb0b907, REGION_SMP1, 0x000000, LOAD_NORMAL, },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00040000,
            "c64_15-1.bin",  0xce9308a6, "c64_16-1.bin",  0x470a483a),
   {   "c64_09.13", 0x00010000, 0x88d7f65c, REGION_ROM2, 0x000000, LOAD_NORMAL, },
   {           NULL,          0,          0, 0,           0,        0,           },
};

static struct ROM_INFO rom_majest12[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
              "c64_07.10",  0xf29ed5c9,   "c64_08.11",  0xddfd33d5),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
              "c64_06.4",  0x18dc71ac,   "c64_05.5",  0xb61866c0),
   {           NULL,          0,          0, 0,           0,        0,           },
};

static struct ROM_INFO rom_dondokdj[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "b95-12.bin",  0xd0fce87a, "b95-11-1.bin",  0xdad40cd3),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x20000,
            "b95-10.bin",  0xa46e1f0b, "b95-wrld.7",  0x6e4e1351),
  { "b95-02.bin", 0x80000, 0x67b4e979, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "b95-01.bin", 0x80000, 0x51c176ce, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "b95-03.bin", 0x80000, 0x543aa0d1, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "b95-08.bin", 0x10000, 0xb5aa49e1, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
  { "b95-04.bin", 0x80000, 0xac4c1716, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_megab[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "c11-07.55",  0x11d228b6, "c11-08.39",  0xa79d4dca),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x20000,
            "c11-06.54",  0x7c249894, "c11-11.38",  0x263ecbf9),
  { "c11-05.58", 0x80000, 0x733e6d8e, REGION_GFX1, 0x00000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  0x00000,  0x80000,
            "c11-03.32",  0x46718c7a, "c11-04.31",  0x663f33cc),
  { "c11-12.3", 0x10000, 0xb11094f1, REGION_ROM2, 0, LOAD_NORMAL },
  { "c11-01.29", 0x80000, 0xfd1ea532, REGION_SMP1, 0x00000, LOAD_NORMAL },
/*Pals  b89-01.8  b89-02.28  b89-04.27  c11-13.13  c11-14.23 */
  { "c11-02.30", 0x80000, 0x451cc187, REGION_SMP2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_liquidk[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "c49_09.12",  0x6ae09eb9, "c49_11.14",  0x42d2be6e),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x20000,
            "c49_10.13",  0x50bef2e0, "c49_12.15",  0xcb16bad5),
  { "lk_scr.bin", 0x80000, 0xc3364f9b, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "lk_obj0.bin", 0x80000, 0x67cc3163, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "lk_obj1.bin", 0x80000, 0xd2400710, REGION_GFX2, 0x80000, LOAD_NORMAL },
  { "c49_08.9", 0x10000, 0x413c310c, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
  { "lk_snd.bin", 0x80000, 0x474d45a4, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_pulirula[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x40000,
            "c98-12.rom",  0x816d6cde, "c98-16.rom",  0x59df5c77),
  LOAD8_16(  REGION_ROM1,  0x80000,  0x20000,
            "c98-06.rom",  0x64a71b45, "c98-07.rom",  0x90195bc0),
  { "c98-04.rom", 0x100000, 0x0e1fe3b2, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c98-02.rom", 0x100000, 0x4a2ad2b3, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "c98-03.rom", 0x100000, 0x589a678f, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "c98-05.rom", 0x080000, 0x9ddd9c39, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "c98-14.rom", 0x20000, 0xa858e17c, REGION_ROM2, 0, LOAD_NORMAL },
	/* no Delta-T samples */
  { "c98-01.rom", 0x100000, 0x197f66f5, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/*
static struct ROM_INFO koshien_roms[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "c81-11.bin",  0xb44ea8c9, "c81-10.bin",  0x8f98c40a),
  { "c81-04.bin", 0x080000, 0x1592b460, REGION_ROM1, 0x080000, LOAD_SWAP_16 },
  { "c81-03.bin", 0x100000, 0x29bbf492, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c81-01.bin", 0x100000, 0x64b15d2a, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "c81-02.bin", 0x100000, 0x962461e8, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "c81-12.bin", 0x10000, 0x6e8625b6, REGION_ROM2, 0, LOAD_NORMAL },
  { "c81-05.bin", 0x80000, 0x9c3d71be, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "c81-06.bin", 0x80000, 0x927833b4, REGION_SMP2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};
*/

static struct INPUT_INFO input_f2b1[] =
{
   INP0( COIN1, 0xe, 0x04 ),
   INP0( COIN2, 0xe, 0x08 ),
   INP0( TILT, 0xe, 0x01 ),
   INP0( SERVICE, 0xe, 0x02 ),

   INP0( P1_START, 0x4, 0x80 ),
   INP0( P1_UP, 0x4, 0x01 ),
   INP0( P1_DOWN, 0x4, 0x02 ),
   INP0( P1_LEFT, 0x4, 0x04 ),
   INP0( P1_RIGHT, 0x4, 0x08 ),
   INP0( P1_B1, 0x4, 0x10 ),

   INP0( P2_START, 0x6, 0x80 ),
   INP0( P2_UP, 0x6, 0x01 ),
   INP0( P2_DOWN, 0x6, 0x02 ),
   INP0( P2_LEFT, 0x6, 0x04 ),
   INP0( P2_RIGHT, 0x6, 0x08 ),
   INP0( P2_B1, 0x6, 0x10 ),

   END_INPUT
};

static struct INPUT_INFO input_f2b2[] =
{
    INCL_INP( f2b1 ),
    INP0( P1_B2, 0x4, 0x20 ),
    INP0( P2_B2, 0x6, 0x20 ),
    END_INPUT
};

// 3 buttons
static struct INPUT_INFO input_f2b3[] =
{
   INCL_INP( f2b2 ),

   INP0( P1_B3, 0x4, 0x40 ),
   INP0( P2_B3, 0x6, 0x40 ),

   END_INPUT
};

// 4 players
static struct INPUT_INFO input_growl[] =
{
   INP0( COIN1, 0x032384, 0x04 ),
   INP0( COIN2, 0x032384, 0x08 ),
   INP0( TILT, 0x032384, 0x01 ),
   INP0( SERVICE, 0x032384, 0x02 ),

   INP0( P1_START, 0x032380, 0x80 ),
   INP0( P1_UP, 0x032380, 0x01 ),
   INP0( P1_DOWN, 0x032380, 0x02 ),
   INP0( P1_LEFT, 0x032380, 0x04 ),
   INP0( P1_RIGHT, 0x032380, 0x08 ),
   INP0( P1_B1, 0x032380, 0x10 ),
   INP0( P1_B2, 0x032380, 0x20 ),
   INP0( P1_B3, 0x032380, 0x40 ),

   INP0( P2_START, 0x032382, 0x80 ),
   INP0( P2_UP, 0x032382, 0x01 ),
   INP0( P2_DOWN, 0x032382, 0x02 ),
   INP0( P2_LEFT, 0x032382, 0x04 ),
   INP0( P2_RIGHT, 0x032382, 0x08 ),
   INP0( P2_B1, 0x032382, 0x10 ),
   INP0( P2_B2, 0x032382, 0x20 ),
   INP0( P2_B3, 0x032382, 0x40 ),

  INP0( P3_UP, 0x04, 0x01 ),
  INP0( P3_DOWN, 0x04, 0x02 ),
  INP0( P3_LEFT, 0x04, 0x04 ),
  INP0( P3_RIGHT, 0x04, 0x08 ),
  INP0( P3_B1, 0x04, 0x10 ),
  INP0( P3_B2, 0x04, 0x20 ),
  INP0( P3_B3, 0x04, 0x40 ),
  INP0( P3_START, 0x04, 0x80 ),
  INP0( P4_UP, 0x05, 0x01 ),
  INP0( P4_DOWN, 0x05, 0x02 ),
  INP0( P4_LEFT, 0x05, 0x04 ),
  INP0( P4_RIGHT, 0x05, 0x08 ),
  INP0( P4_B1, 0x05, 0x10 ),
  INP0( P4_B2, 0x05, 0x20 ),
  INP0( P4_B3, 0x05, 0x40 ),
  INP0( P4_START, 0x05, 0x80 ),

  INP0( COIN3, 0x06, 0x01 ),
  INP0( COIN4, 0x06, 0x02 ),
  INP0( SERVICE, 6, 0x04 ),
   END_INPUT
};

// mahjong quest inputs (generated by conv_inputs.pl from the mame source...)
static struct INPUT_INFO input_mjnquest[] =
{
  INP0( P1_A, 0x00, 0x01 ),
  INP0( P1_E, 0x00, 0x02 ),
  INP0( P1_I, 0x00, 0x04 ),
  INP0( P1_M, 0x00, 0x08 ),
  INP0( P1_KAN, 0x00, 0x10 ),
  INP0( P1_START, 0x00, 0x20 ),

  INP0( P1_B, 0x02, 0x01 ),
  INP0( P1_F, 0x02, 0x02 ),
  INP0( P1_J, 0x02, 0x04 ),
  INP0( P1_N, 0x02, 0x08 ),
  INP0( P1_REACH, 0x02, 0x10 ),

  INP0( P1_C, 0x04, 0x01 ),
  INP0( P1_G, 0x04, 0x02 ),
  INP0( P1_K, 0x04, 0x04 ),
  INP0( P1_CHI, 0x04, 0x08 ),
  INP0( P1_RON, 0x04, 0x10 ),

  INP0( P1_D, 0x06, 0x01 ),
  INP0( P1_H, 0x06, 0x02 ),
  INP0( P1_L, 0x06, 0x04 ),
  INP0( P1_PON, 0x06, 0x08 ),

  INP0( TILT, 0x0a, 0x01 ),
  INP0( COIN2, 0x0a, 0x02 ),

  INP0( SERVICE, 0x0c, 0x01 ),
  INP0( COIN1, 0x0c, 0x02 ),
   END_INPUT
};

#define TAITO_COINAGE_WORLD_8 \
  { MSG_COIN1, 0x30, 4 },\
  { MSG_4COIN_1PLAY, 0x00, 0x00 },\
  { MSG_3COIN_1PLAY, 0x10, 0x00 },\
  { MSG_2COIN_1PLAY, 0x20, 0x00 },\
  { MSG_1COIN_1PLAY, 0x30, 0x00 },\
  { MSG_COIN2, 0xc0, 4 },\
  { MSG_1COIN_1PLAY, 0xc0, 0x00 },\
  { MSG_1COIN_3PLAY, 0x80, 0x00 },\
  { MSG_1COIN_4PLAY, 0x40, 0x00 },\
  { MSG_1COIN_6PLAY, 0x00, 0x00 },\

#define TAITO_DIFFICULTY_8 \
  { MSG_DIFFICULTY, 0x03, 4 },\
  { "Easy" , 0x02, 0x00 },\
  { "Medium" , 0x03, 0x00 },\
  { "Hard" , 0x01, 0x00 },\
  { "Hardest" , 0x00, 0x00 },\

static struct DSW_DATA dsw_data_camel_try_0[] =
{
   { _("Game Style"),            0x01, 0x02 },
   { _("Table"),                 0x01},
   { _("Upright"),               0x00},
   DSW_SCREEN( 0x02, 0x00),
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

static struct DSW_DATA dsw_data_camel_try_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Start Time"),            0x0C, 0x04 },
   { _("50 sec"),                0x0C},
   { _("60 sec"),                0x08},
   { _("40 sec"),                0x04},
   { _("35 sec"),                0x00},
   { _("Continue Time Add"),     0x30, 0x04 },
   { _("30 sec"),                0x30},
   { _("40 sec"),                0x20},
   { _("25 sec"),                0x10},
   { _("20 sec"),                0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { _("2 Player Mode"),         0x80, 0x02 },
   { _("Single"),                0x80},
   { _("Together"),              0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_cameltry[] =
{
   { 0x00, 0xFF, dsw_data_camel_try_0 },
   { 0x02, 0xFF, dsw_data_camel_try_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_final_blow_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
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

static struct DSW_DATA dsw_data_final_blow_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_finalb[] =
{
   { 0x0, 0xFF, dsw_data_final_blow_0 },
   { 0x2, 0xFF, dsw_data_final_blow_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_dondokod_0[] =
{
  { MSG_UNKNOWN, 0x01, 2 },
  { MSG_OFF, 0x01},
  { MSG_ON, 0x00},
  DSW_SCREEN( 0x02, 0x00),
  DSW_SERVICE( 0, 0x04),
	TAITO_COINAGE_WORLD_8
  DSW_DEMO_SOUND( 0x08, 0x00),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_dondokod_1[] =
{
	TAITO_DIFFICULTY_8
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("10k and 100k") , 0x0c},
  { _("10k and 150k") , 0x08},
  { _("10k and 250k") , 0x04},
  { _("10k and 350k") , 0x00},
  { MSG_LIVES, 0x30, 4 },
  { "2" , 0x20},
  { "3" , 0x30},
  { "4" , 0x00},
  { "5" , 0x10},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_dondokdj[] =
{
   { 0x00, 0xFF, dsw_data_dondokod_0 },
   { 0x02, 0xFF, dsw_data_dondokod_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_gunfront_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_DSWB_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT4,           0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "1",                     0x20},
   { "2",                     0x10},
   { "5",                     0x00},
   { _("Continue Mode"),         0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Simultaneous Play"),     0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_gunfront[] =
{
  { 0x0, 0xff, dsw_data_dondokod_0 },
  { 0x2, 0xff, dsw_data_gunfront_1 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_megab_0[] =
{
   DSW_CABINET( 0x00,1 ),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_mega_blast_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Bonus / K=10,000"),      0x0c, 0x04 },
   { _("10k, 110K, 210K, 310K"), 0x0c, 0x00 },
   { _("20k, 220K, 420K, 620K"), 0x08, 0x00 },
   { _("15K, 145K, 365K, 515K"), 0x04, 0x00 },
   { _("No Bonus Lives"),        0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "1",                     0x10},
   { "2",                     0x00},
   { _("Control Panel"),         0x40, 0x02 },
   { _("Double"),                0x40},
   { _("Single"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_megab[] =
{
   { 0x00, 0xFF, dsw_data_megab_0 },
   { 0x02, 0xFF, dsw_data_mega_blast_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_liquidk_1[] =
{
	TAITO_DIFFICULTY_8
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("30k and 100k") , 0x0c},
  { _("30k and 150k") , 0x08},
  { _("50k and 250k") , 0x04},
  { _("50k and 350k") , 0x00},
  { MSG_LIVES, 0x30, 4 },
  { "2" , 0x20},
  { "3" , 0x30},
  { "4" , 0x00},
  { "5" , 0x10},
  { _("Allow Continue"), 0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  { _("Upright Controls"), 0x80, 2 },
  { _("Single") , 0x80},
  { _("Dual") , 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_liquidk[] =
{
   { 0x00, 0xFF, dsw_data_megab_0 },
   { 0x02, 0xFF, dsw_data_liquidk_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_ssi_1[] =
{
	TAITO_DIFFICULTY_8
  { _("Shields"), 0x0c, 4 },
  { _("None"), 0x00},
  { "1", 0x0c},
  { "2", 0x04},
  { "3", 0x08},
  { MSG_LIVES, 0x10, 2 },
  { "2", 0x00},
  { "3", 0x10},
  { _("2 Players Mode"), 0xa0, 4 },
  { _("Simultaneous"), 0xa0},
  { _("AlternateSingle"), 0x80},
  { _("AlternateDual"), 0x00},
  { _("Not Allowed"), 0x20},
  { _("Allow Continue"), 0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  { NULL, 0}
};

static struct DSW_INFO dsw_ssi[] =
{
  { 0x00, 0xfe, dsw_data_megab_0 },
  { 0x02, 0xff, dsw_data_ssi_1 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_drift_out_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_drift_out_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Control"),               0x0C, 0x04 },
   { _("Lever"),                 0x0C},
   { _("Paddle A"),              0x08},
   { _("Lever"),                 0x04},
   { _("Paddle B"),              0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_driftout[] =
{
   { 0x00, 0xFF, dsw_data_drift_out_0 },
   { 0x02, 0xFF, dsw_data_drift_out_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_thunder_fox_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_thunder_fox_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Time Limit"),            0x04, 0x02 },
   { MSG_ON,                  0x04},
   { MSG_OFF,                 0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "4",                     0x10},
   { "5",                     0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { _("Controls"),              0x80, 0x02 },
   { _("Dual"),                  0x80},
   { _("Single"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_thundfox[] =
{
   { 0x00, 0xFF, dsw_data_thunder_fox_0 },
   { 0x02, 0xFF, dsw_data_thunder_fox_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_growl_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Game Type"),             0x30, 0x04 },
   { _("1 Credit/2P"),           0x30},
   { _("4 Credits/4P"),          0x20},
   { _("1 Credit/4P"),           0x10},
   { _("2 Credits/4P"),          0x00},
   { _("Final Stage Cont"),      0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_growl[] =
{
  { 0x32100, 0xff, dsw_data_thunder_fox_0 },
  { 0x32102, 0xff, dsw_data_growl_1 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_dino_rex_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Damage"),                0x0C, 0x04 },
   { MSG_NORMAL,              0x0C},
   { _("Small"),                 0x08},
   { _("Big"),                   0x04},
   { _("Biggest"),               0x00},
   { _("Timer"),                 0x10, 0x02 },
   { MSG_NORMAL,              0x10},
   { _("Fast"),                  0x00},
   { _("Match Type"),            0x20, 0x02 },
   { _("Best of 3"),             0x20},
   { _("Single"),                0x00},
   { _("2 Player Mode"),         0x40, 0x02 },
   { _("Upright"),               0x40},
   { _("Cocktail"),              0x00},
   { _("Upright Controls"),      0x80, 0x02 },
   { _("Dual"),                  0x80},
   { _("Single"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_dinorex[] =
{
   { 0x0, 0xFF, dsw_data_thunder_fox_0 },
   { 0x2, 0xFF, dsw_data_dino_rex_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_solfigtr_1[] =
{
	TAITO_DIFFICULTY_8
  { MSG_UNKNOWN, 0x04, 2 },
  { MSG_OFF, 0x04},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x08, 2 },
  { MSG_OFF, 0x08},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_solfigtr[] =
{
  { 0x0, 0xff, dsw_data_dondokod_0 },
  { 0x2, 0xff, dsw_data_solfigtr_1 },
  { 0, 0, NULL }
};

#define TAITO_COINAGE_JAPAN_NEW_8 \
  { MSG_COIN1, 0x30, 4 },\
  { MSG_3COIN_1PLAY, 0x00, 0x00 },\
  { MSG_2COIN_1PLAY, 0x10, 0x00 },\
  { MSG_1COIN_1PLAY, 0x30, 0x00 },\
  { MSG_1COIN_1PLAY, 0x20, 0x00 },\
  { MSG_COIN2, 0xc0, 4 },\
  { MSG_3COIN_1PLAY, 0x00, 0x00 },\
  { MSG_2COIN_1PLAY, 0x40, 0x00 },\
  { MSG_1COIN_1PLAY, 0xc0, 0x00 },\
  { MSG_1COIN_1PLAY, 0x80, 0x00 },\

static struct DSW_DATA dsw_data_pulirulj_0[] =
{
  { MSG_UNKNOWN, 0x01, 2 },
  { MSG_OFF, 0x01},
  { MSG_ON, 0x00},
  DSW_SCREEN( 0x02, 0x00),
  DSW_SERVICE( 0, 0x04),
	TAITO_COINAGE_JAPAN_NEW_8
  DSW_DEMO_SOUND( 0x08, 0x00),
  { NULL, 0}
};

// mjnquest has some kind of protection to filter inputs/dsw. I use input_buffer for that
static struct DSW_INFO dsw_mjnquest[] =
{
  { 0xe, 0xff, dsw_data_pulirulj_0 },
  { 0x10, 0xff, dsw_data_solfigtr_1 },
  { 0, 0, NULL }
};

static struct ROMSW_DATA romsw_data_taito_jap_us[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "World",                 0x03 },
   { NULL,                    0    },
};

static struct ROMSW_DATA romsw_data_majestic_twelve_0[] =
{
   { "Taito Japan (MJ12)",    0x01 },
   { "Taito America (MJ12)",  0x02 },
   { "Taito Japan (SSI)",     0x03 },
   { NULL,                    0    },
};

static struct ROMSW_DATA romsw_data_thunder_fox_0[] =
{
   { "Taito Japan",           0x00 },
   { "Taito America",         0x01 },
   { "Taito",                 0x02 },
   { NULL,                    0    },
};

static struct ROMSW_DATA romsw_data_growl_0[] =
{
   { "Taito Japan (Runark)",    0x01 },
   { "Taito America (Growl)",   0x02 },
   { "Taito Worldwide (Growl)", 0x03 },
   { NULL,                      0    },
};

static struct ROMSW_DATA romsw_data_camel_try_alt_0[] =
{
   { "Taito Japan (Japanese)", 0x00 },
   { "Taito America",          0x01 },
   { "Taito Japan",            0x02 },
/*   { "Taito America (Romstar)",0x03 },
   { "Taito (Phoenix)",        0x04 }, */
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_cameltry[] =
{
   { 0x03FFFF, 0x01, romsw_data_camel_try_alt_0 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_growl[] =
{
   { 0x0FFFFF, 0x03, romsw_data_growl_0 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_thundfox[] =
{
   { 0x03FFFF, 0x02, romsw_data_thunder_fox_0 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_dondokdj[] =
{
   { 0x077FFF, 0x03, romsw_data_taito_jap_us },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_solfigtr[] =
{
   { 0x03ffff, 0x03, romsw_data_taito_jap_us },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_f2demo[] =
{
   { 0x07FFFF, 0x02, romsw_data_thunder_fox_0 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_ssi[] =
{
   { 0x07FFFF, 0x03, romsw_data_majestic_twelve_0 },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_liquidk[] =
{
   { 0x07FFFF, 0x03, romsw_data_taito_jap_us },
   { 0,        0,    NULL },
};

static GfxLayout tilelayout =
{
	16,16,	/* 16*16 sprites */
	RGN_FRAC(1,1),
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },
	{ 1*4, 0*4, 3*4, 2*4, 5*4, 4*4, 7*4, 6*4, 9*4, 8*4, 11*4, 10*4, 13*4, 12*4, 15*4, 14*4 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64, 8*64, 9*64, 10*64, 11*64, 12*64, 13*64, 14*64, 15*64 },
	128*8	/* every sprite takes 128 consecutive bytes */
};

static GfxLayout charlayout =
{
	8,8,	/* 8*8 characters */
	RGN_FRAC(1,1),
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },
	{ 2*4, 3*4, 0*4, 1*4, 6*4, 7*4, 4*4, 5*4 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8	/* every sprite takes 32 consecutive bytes */
};

static GfxLayout pivotlayout =
{
	8,8,	/* 8*8 characters */
	RGN_FRAC(1,1),
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },
	{ 0*4, 1*4, 2*4, 3*4, 4*4, 5*4, 6*4, 7*4 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8	/* every sprite takes 32 consecutive bytes */
};

static GfxLayout finalb_tilelayout =
{
	16,16,	/* 16*16 sprites */
	RGN_FRAC(1,2),
	6,	/* 6 bits per pixel */
	{ RGN_FRAC(1,2)+0, RGN_FRAC(1,2)+1, 0, 1, 2, 3 },
	{ 3*4, 2*4, 1*4, 0*4, 7*4, 6*4, 5*4, 4*4,
			11*4, 10*4, 9*4, 8*4, 15*4, 14*4, 13*4, 12*4 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64,
			8*64, 9*64, 10*64, 11*64, 12*64, 13*64, 14*64, 15*64 },
	128*8	/* every sprite takes 128 consecutive bytes */
};

static struct GFX_LIST pivot_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &charlayout }, // 256 color banks
	{ REGION_GFX2, &tilelayout }, // 256 color banks
	{ REGION_GFX3, &pivotlayout }, // 256 color banks
	{ 0, NULL } /* end of array */
};

static struct GFX_LIST thundfox_decodeinfo[] =
{
	{ REGION_GFX1, &charlayout }, // tc100scn #0
	{ REGION_GFX2, &tilelayout }, // 256 color banks
	{ REGION_GFX3, &charlayout }, // tc100scn #1
	{ 0, NULL } /* end of array */
};

// REGION_GFX3 is empty
static struct GFX_LIST finalb_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &charlayout }, // 256 color banks
	{ REGION_GFX2, &finalb_tilelayout },
	{ 0, NULL } /* end of array */
};

static struct GFX_LIST mjnquest_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &charlayout }, // 256 color banks
	{ REGION_GFX2, &tilelayout },
	{ 0, NULL } /* end of array */
};

static UINT8 *RAM_VIDEO,*RAM_VIDEO2,*GFX_BANK;
static UINT8 *RAM_SCROLL,*RAM_SCROLL2;
static UINT8 *RAM_OBJECT;
static UINT8 *RAM_INPUT;
static UINT8 *RAM_ROTATE;

static struct layer {
  UINT32 pri,num;
} layer[16];

static int layer_cmp(const void *a, const void *b) {
  return ((struct layer *)a)->pri - ((struct layer *)b)->pri;
}

static void load_common() {
  UINT32 size = get_region_size(REGION_CPU1);
   RAMSize=0x50000;

   if(!(RAM=AllocateMem(0x40000+0x14000))) return;

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   // make_solid_mask not called for GFX3.

   ByteSwap(ROM,size);
   AddMemFetch(0x000000, size-1, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadBW(0x000000, size-1, NULL, ROM+0x000000);			// 68000 ROM
}

static int init_gfx;

static void setup_gfx() {
   // Init tc0200obj emulation
   // ------------------------

  init_gfx = 0;
   tc0200obj.RAM	= RAM_OBJECT+0x0000;
   tc0200obj.RAM_B	= NULL;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.ofs_x	= -3;
   tc0200obj.ofs_y	= 0; // sprite type now

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   tc0100scn[0].layer[0].scr_x	=16-3;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].scr_x	=13; // -80 for f2demo !
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].scr_x	=13;
   tc0100scn[0].layer[2].scr_y	=8;

   if (load_region[REGION_GFX3] && tc0005rot.RAM) {
     // to init pixel_bitmap in tc005rot (will be called in finish_setup_gfx again)
     tc0005rot.GFX_ROT = load_region[REGION_GFX3]; // init this to tell loadroms that we
     //  don't want to call make_solid_region on it
     init_tc0005rot();
   }
}

static void finish_setup_gfx() {
  // called when the layouts have been applied
  init_gfx = 1;
   tc0200obj.GFX	= gfx2;
   tc0200obj.MASK	= gfx2_solid;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=gfx_solid[0];
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=gfx_solid[0];
   tc0200obj.tile_mask	= max_sprites[1]-1;
   tc0100scn[0].layer[0].tile_mask=max_sprites[0]-1;
   tc0100scn[0].layer[1].tile_mask=max_sprites[0]-1;
   init_tc0200obj();
   if (gfx3 && tc0005rot.RAM) {
     tc0005rot.GFX_ROT = gfx3;
     if (is_current_game("pulirula") || is_current_game("driftout") ||
       is_current_game("driveout"))
       init_tc430grw();
     else
       init_tc0005rot();
     {
       int max = 0;
       int size = get_region_size(REGION_GFX3);
       int n;
       for (n=0; n<size; n++) {
	 if (gfx3[n] > max)
	   max = n;
       }
     }
   }
}

static void load_common_cameltry() {
  UINT8 *RAM_COLOUR;
   // 68000 Speed Hack

   WriteLong68k(&ROM[0x00BA2],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00BA6],0x00AA0000);
   WriteWord68k(&ROM[0x00BAA],0x6100-16);	// bra.s <loop>

   // Set vcu type

   WriteWord68k(&ROM[0x3FF8C],0x0000);

   load_common();

   RAM_OBJECT     = RAM+0x10000;
   RAM_ROTATE     = RAM+0x34000;
   RAM_COLOUR     = RAM+0x36000;
   RAM_VIDEO      = RAM+0x20000;
   RAM_SCROLL     = RAM+0x38200;
   TC0360PRI_regs = RAM+0x38300;
   GFX_FG0        = RAM+0x40000;
   RAMSize = 0x38320;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0005rot emulation
   // ------------------------

   tc0005rot.RAM     = RAM_ROTATE;
   tc0005rot.RAM_SCR = RAM+0x30100;
   setup_gfx();

   tc0100scn[0].layer[2].scr_x	=19;

   tc0200obj.ofs_x	= 8;
   init_tc0100scn(0);


   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddRWBW(0x900000, 0x90fFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x813FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xA00000, 0xA01FFF, tc0005rot_bg0_ww, NULL);		// SCREEN RAM (ROTATE)
   AddRWBW(0xA00000, 0xA01FFF, NULL, RAM_ROTATE);			// SCREEN RAM (ROTATION)
   AddReadByte(0x320000, 0x320003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadBW(0x300000, 0x30001F, NULL, input_buffer);			// INPUT RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x320000, 0x320003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x300000, 0x30001F, tc0220ioc_wb, NULL);		// INPUT RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xA02000, 0xA0200F, NULL, RAM+0x030100);		// SCROLL RAM (ROTATION)
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xD00000, 0xD0001F, NULL, TC0360PRI_regs);		// Priorities
   AddWriteWord(0x300000, 0x30001F, tc0220ioc_ww, NULL);		// INPUT RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   GameMouse=1;
}

static void load_cameltry() {
  load_common_cameltry();
  AddTaitoYM2610(0x01E6, 0x0185, 0x10000);
}

static struct YM2203interface ym2203_interface =
{
	1,		/* 1 chip ??? */
	3000000,	/* 3 MHz ??? (tempo much too fast @4) */
	{ YM2203_VOL(60,20) },
	{ 0 },	/* portA read */
	{ 0 },
	{ NULL }, // camltrua_porta_w },	/* portA write - not implemented */
	{ 0 },	/* portB write */
	{ z80_irq_handler }
};

static struct SOUND_INFO sound_camltrua[] =
{
   { SOUND_YM2203,   &ym2203_interface,	},
   { 0, 	    NULL,		},
};

static void load_camltrua() {
  /* Alt version with YM2203 sound missing ADPCM chip? Also sound tempo
     may be fractionally too slow. */
  /* This alternate version seems quite experimental, I take its specificities from mame */
  UINT8 *z80_ram;
  load_common_cameltry();

  z80_ram = RAM + RAMSize;
  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

  AddZ80ARead(0x0000, 0x7FFF, NULL,	Z80ROM);   // No bank control found
  AddZ80ARead(0x8000, 0x8fff, NULL, z80_ram);
  AddZ80ARead(0x9000, 0x9000, YM2203_status_port_0_r, NULL);
  AddZ80ARead(0xa001, 0xa001, tc0140syt_read_sub_z80, NULL);

  AddZ80AWrite(0x8000,0x8fff, NULL, z80_ram);
  AddZ80AWrite(0x9000,0x9000, YM2203_control_port_0_w, NULL);
  AddZ80AWrite(0x9001,0x9001, YM2203_write_port_0_w, NULL);
  AddZ80AWrite(0xa000,0xa001, tc0140syt_write_sub_z80, NULL);

  AddZ80ARead(0, 0xffff, DefBadReadZ80, NULL);
  AddZ80ARead (    -1,     -1, NULL,			NULL);

  AddZ80AWrite    (0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
  AddZ80AWrite(    -1,     -1, NULL,			NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
  AddZ80AReadPort(  -1,   -1, NULL,			NULL);

  // AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
  AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);
  AddZ80AWritePort(  -1,   -1, NULL,			NULL);

  AddZ80AInit();
}

static void load_gunfront() {
   // speed hack

   WriteWord68k(&ROM[0x151DE],0x4EF9);			//	jmp	$0000C0
   WriteLong68k(&ROM[0x151E0],0x000000C0);

   WriteLong68k(&ROM[0x000C0],0x13FC0000);		//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x000C4],0x00AA0000);

   WriteWord68k(&ROM[0x000C8],0x082D);			//	btst	#2,-32762(a5)
   WriteLong68k(&ROM[0x000CA],0x00028006);

   WriteWord68k(&ROM[0x000CE],0x6700+(0x100-0x10)); 	//	beq.s	<loop>

   WriteWord68k(&ROM[0x000D0],0x082D);			//	btst	#5,-1223(a5)
   WriteLong68k(&ROM[0x000D2],0x0005FB39);

   WriteWord68k(&ROM[0x000D6],0x6600+(0x100-0x18)); 	//	bne.s	<loop>

   WriteWord68k(&ROM[0x000D8],0x4EF9);			//	jmp	$0151EE
   WriteLong68k(&ROM[0x000DA],0x000151EE);

   // scroll hack

   WriteLong68k(&ROM[0x10DFC],0x4EB80100);		//	jsr	$100.w

   WriteWord68k(&ROM[0x00100],0x4EB9);			//	jsr	$1101C
   WriteLong68k(&ROM[0x00102],0x0001101C);

   WriteLong68k(&ROM[0x00106],0x13FC0000);		//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0010A],0x00AA0000);

   WriteWord68k(&ROM[0x0010E],0x4E75);			//	rts

   load_common();

   AddTaitoYM2610(0x01A4, 0x0150, 0x10000);

   RAM_VIDEO      = RAM+0x10000;
   RAM_SCROLL     = RAM+0x32000;
   RAM_OBJECT     = RAM+0x20000;
   TC0360PRI_regs = RAM+0x32200;
   GFX_FG0        = RAM+0x35000;
   RAMSize = 0x33000;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x1000);

   setup_gfx();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------
   tc0100scn[0].layer[0].scr_x	=19;
   tc0100scn[0].layer[1].scr_x	=19; // -80 for f2demo !
   tc0100scn[0].layer[2].scr_x	=19;

   tc0200obj.ofs_x	= 8+1;
   init_tc0100scn(0);

   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x300000, 0x30000F, tc0220ioc_rb_bswap, NULL);		// INPUT
   AddReadByte(0x320000, 0x320003, tc0140syt_read_main_68k, NULL);	// SOUND COMM

   AddReadWord(0x200000, 0x201FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadWord(0x300000, 0x30000F, tc0220ioc_rw_bswap, NULL);		// INPUT

   AddWriteByte(0x320000, 0x320003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x300000, 0x30000F, tc0220ioc_wb_bswap, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

   AddWriteWord(0x200000, 0x201FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xB00000, 0xB0001F, NULL, TC0360PRI_regs);		// ??? RAM
   AddWriteWord(0x300000, 0x30000F, tc0220ioc_ww_bswap, NULL);		// INPUT
   finish_conf_68000(0);

}

static void load_growl() {
  UINT8 *RAM_COLOUR;

  // Addresses in rom :
  // 1124 : sound mode
  // called from 7542 from f34 (int 5)
   ROM[0x01010]=0x4E;		// SKIP OLD CODE (NO ROOM FOR HACK)
   ROM[0x01011]=0xF9;		// (JMP $72900)
   ROM[0x01012]=0x00;
   ROM[0x01013]=0x07;
   ROM[0x01014]=0x29;
   ROM[0x01015]=0x00;

   ROM[0x72900]=0x4E;		// jsr $BB4
   ROM[0x72901]=0xB9;		// (random number)
   ROM[0x72902]=0x00;
   ROM[0x72903]=0x00;
   ROM[0x72904]=0x0B;
   ROM[0x72905]=0xB4;

   ROM[0x72906]=0x13;		// move.b #$00,$AA0000
   ROM[0x72907]=0xFC;		// (Speed Hack)
   ROM[0x72908]=0x00;
   ROM[0x72909]=0x00;
   ROM[0x7290A]=0x00;
   ROM[0x7290B]=0xAA;
   ROM[0x7290C]=0x00;
   ROM[0x7290D]=0x00;

   ROM[0x7290E]=0x60;		// Loop
   ROM[0x7290F]=0x100-16;

   // Frame Sync Hack
   // ---------------

   WriteLong68k(&ROM[0x75B0],0x13FC0000);
   WriteLong68k(&ROM[0x75B4],0x00AA0000);
   WriteLong68k(&ROM[0x75B8],0x4E714E71);

   // Fix Sprite/Int6 Wait
   // --------------------

   WriteLong68k(&ROM[0x4CEE],0x4E714E71);

   load_common();

   RAM_VIDEO       = RAM+0x10000;
   RAM_OBJECT      = RAM+0x20000;
   RAM_SCROLL      = RAM+0x30000;
   GFX_BANK        = RAM+0x30010;
   TC0360PRI_regs  = RAM+0x30020;
   RAM_INPUT       = RAM+0x32100;
   GFX_FG0         = RAM+0x32200;
   RAM_COLOUR      = RAM+0x36100;

   RAMSize = 0x38100;

   AddTaitoYM2610(0x01A9, 0x0155, 0x10000);
   // AddTaitoYM2610(0, 0, 0x10000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   setup_gfx();

   tc0100scn[0].layer[0].scr_x	= 0x3+16;
   tc0100scn[0].layer[1].scr_x	= 0x3+16;
   tc0100scn[0].layer[2].scr_x	= 0x3+16;

   init_tc0100scn(0);
   tc0200obj.ofs_x	= 0; // - 0x13;
   tc0200obj.ofs_y	= 0; // - 0x60;


   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadBW(0x300000, 0x30000F, NULL, RAM_INPUT);			// input (dsw)
   AddReadBW(0x320000, 0x32000F, NULL, RAM+0x32380);			// INPUT
   AddReadBW(0x508000, 0x508001, NULL, &input_buffer[4]); // input player 3
   AddReadBW(0x50c000, 0x50c001, NULL, &input_buffer[6]); // input player 3
   AddReadByte(0x400000, 0x400003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddRWBW(0x820000, 0x82000F, NULL, RAM_SCROLL);		// SCROLL RAM
   AddRWBW(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddRWBW(0x500000, 0x50000F, NULL, GFX_BANK);		// OBJECT BANK?
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   // AddWriteByte(0x300000, 0x30000F, tc0220ioc_wb, NULL);		// tc0220ioc
   AddWriteByte(0x400000, 0x400003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   // AddWriteWord(0x340000, 0x34000F, NULL, RAM+0x032380);		// watchdog
   // AddWriteWord(0x380000, 0x38000F, NULL, RAM+0x032180);		// ???
   // AddWriteWord(0x600000, 0x60000F, NULL, RAM+0x032280);		// ???
   AddWriteWord(0xB00000, 0xB0001F, NULL, TC0360PRI_regs);		// priorities
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_dondokdj(void)
{
   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x005EC4],0x4E71);

   // Fix ROM Checksum
   // ----------------

   WriteWord68k(&ROM[0x00D1A],0x4E75);

   // Fix Long Sound Wait
   // -------------------

   WriteWord68k(&ROM[0x001A6],0x4E71);

  load_common();

   /*-----[Sound Setup]-----*/

   AddTaitoYM2610(0x01E6, 0x0185, 0x10000);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x32000;
   RAM_ROTATE = RAM+0x34000;
   RAM_OBJECT = RAM+0x20000;
   GFX_FG0    = RAM+0x3C000;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x1000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0005rot emulation
   // ------------------------

   tc0005rot.RAM     = RAM_ROTATE;
   tc0005rot.RAM_SCR = RAM+0x36000;
   setup_gfx();
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   // tc0200obj.ofs_x	= -3+7; // ???

   init_tc0100scn(0);


/*
 *  StarScream Stuff follows
 */

   AddRWBW(  0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadBW(0x300000, 0x30001F, NULL, input_buffer);			// INPUT
   AddReadByte(0x320000, 0x320003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x200000, 0x201FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x300000, 0x30000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0x320000, 0x320003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteBW(0xB00000, 0xB000FF, NULL, RAM+0x032300);		// priority register
   TC0360PRI_regs = RAM+0x032300;
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x201FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteWord(0xA00000, 0xA01FFF, tc0005rot_bg0_ww, NULL);		// SCREEN RAM (ROTATE)
   AddWriteWord(0x300000, 0x30000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xA02000, 0xA0200F, NULL, RAM+0x036000);		// SCROLL RAM (ROTATE)
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

void load_finalb() {
  int i;
  unsigned char data;
  unsigned int offset;
  UINT8 *gfx = load_region[REGION_GFX2];

  offset = 0x100000;
  for (i = 0x180000; i<0x200000; i++)
    {
      int d1,d2,d3,d4;

      /* convert from 2bits into 4bits format */
      data = gfx[i];
      d1 = (data>>0) & 3;
      d2 = (data>>2) & 3;
      d3 = (data>>4) & 3;
      d4 = (data>>6) & 3;

      gfx[offset] = (d3<<2) | (d4<<6);
      offset++;

      gfx[offset] = (d1<<2) | (d2<<6);
      offset++;
    }

   // Fix Int#6
   // ---------

   //WriteLong68k(&ROM[0x00610],0x4E714E71);	//	nop

   // Speed Hack
   // ----------

   WriteLong68k(&ROM[0x00744],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x00748],0x00AA0000);
   WriteWord68k(&ROM[0x0074C],0x6100-16);

   //WriteLong68k(&ROM[0x00618],0x13FC0000);	//	move.b	#$00,$AA0000
   //WriteLong68k(&ROM[0x0061C],0x00AA0000);

   // Fix Colour ram error
   // --------------------

   WriteWord68k(&ROM[0x022E6],0x4E71);
   load_common();

   AddTaitoYM2610(0x033A, 0x02A7, 0x10000);

   RAM_VIDEO  = RAM+0x20000;
   RAM_SCROLL = RAM+0x30000;
   RAM_OBJECT = RAM+0x10000;
   RAM_INPUT  = RAM+0x3c000;
   GFX_FG0    = RAM+0x31000;
   RAMSize = 0x3c010;

   tc0110pcr_init(RAM+0x35000, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x35000, 0x100, 0x10, 0x8000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   setup_gfx();

   init_tc0100scn(0);
   f2_sprites_colors = 64;

   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadBW(0x300000, 0x30000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x320000, 0x320003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x900000, 0x90fFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x200000, 0x200007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x320000, 0x320003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x300000, 0x30000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x200007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   // AddWriteWord(0x360000, 0x36000F, NULL, RAM+0x03C300);		// ??? RAM
   AddWriteWord(0x300000, 0x30000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static UINT16 mjnquest_input;

static UINT16  dsw_mjnquest_r (UINT32 offset) {
  switch (offset&0xf)
    {
    case 0x00:
      return (input_buffer[0xa] << 0) + (input_buffer[0xe]<<8); /* DSW A + coin */
    case 0x02:
      return (input_buffer[0xc] << 0) + (input_buffer[0x10]<<8); /* DSW B + coin */
    }
  return 0xff;
}

static UINT16  mjnquest_input_r (UINT32 offset) {
  switch (mjnquest_input)
    {
    case 0x01:
      return input_buffer[0]; /* IN0 */
    case 0x02:
      return input_buffer[2]; /* IN1 */
    case 0x04:
      return input_buffer[4]; /* IN2 */
    case 0x08:
      return input_buffer[6]; /* IN3 */
    case 0x10:
      return input_buffer[8]; /* IN4 */
    }

  return 0xff;
}

static void  input_mjnquestelect_w (UINT32 offset, UINT16 data) {
  mjnquest_input = (data >> 6);
}

static void load_mjnquest() {
  UINT8 *RAM_COLOUR;
  int i,size = get_region_size(REGION_GFX2);
  UINT8 *gfx = load_region[REGION_GFX2];

  /* the bytes in each longword are in reversed order, put them in the
     order used by the other games. */

  for (i = 0;i < size;i += 2) {
    int t;

    t = gfx[i];
    gfx[i] = (gfx[i+1] >> 4) | (gfx[i+1] << 4);
    gfx[i+1] = (t >> 4) | (t << 4);
  }

   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x004A4],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x004A8],0x00AA0000);

   load_common();

   AddTaitoYM2610(0x0338, 0x02A5, 0x10000);

   RAM_OBJECT = RAM+0x20000;
   RAM_VIDEO  = RAM+0x30000;
   RAM_SCROLL = RAM+0x4A000;
   RAM_COLOUR = RAM+0x40000;
   RAM_INPUT  = RAM+0x4A100;
   GFX_BANK   = RAM+0x4A200;
   GFX_FG0    = RAM+0x50000;
   RAMSize = 0x54000;

   setup_gfx();

   tc0110pcr_init(RAM_COLOUR, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x8000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   tc0100scn[0].layer[0].scr_x	=16+1;

   tc0100scn[0].layer[1].scr_x	=16+1;

   tc0100scn[0].layer[2].scr_x	=16+1;
   init_tc0100scn(0);

   tc0200obj.ofs_x	= 0+6;

   AddRWBW(0x110000, 0x12FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x200000, 0x200007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadBW(0x300000, 0x30000f, dsw_mjnquest_r, NULL);
   AddReadBW(0x310000, 0x310001, mjnquest_input_r, NULL);
   AddReadByte(0x360000, 0x360003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x406000, 0x406FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x406000, 0x406FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x400000, 0x40FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x420000, 0x42000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddRWBW(0x500000, 0x50FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteWord(0x200000, 0x200007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x320000, 0x320001, input_mjnquestelect_w, NULL);
   AddWriteByte(0x360000, 0x360003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWord(0x380000, 0x380001, NULL, GFX_BANK);			// BANK SWITCH
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_dinorex() {
   WriteWord68k(&ROM[0x01084],0x4EF9);		// JMP $7FF00
   WriteLong68k(&ROM[0x01086],0x0007FF00);

   WriteWord68k(&ROM[0x7FF00],0x4EB9);
   WriteLong68k(&ROM[0x7FF02],0x000032FC);
   WriteLong68k(&ROM[0x7FF06],0x13FC0000);	// Stop 68000
   WriteLong68k(&ROM[0x7FF0A],0x00AA0000);
   WriteWord68k(&ROM[0x7FF0E],0x6100-16);	// Loop

  load_common();

   /*-----[Sound Setup]-----*/
   AddTaitoYM2610(0x0211, 0x017A, 0x10000);

   RAM_OBJECT = RAM+0x10000;
   f2_sprite_extension = (UINT16*)(RAM+0x20000);
   RAM_SCROLL = RAM+0x33100;
   TC0360PRI_regs = RAM+0x34000;
   RAM_VIDEO  = RAM+0x40000;
   GFX_FG0    = RAM+0x50000;
   memset(GFX_FG0,0,0x4000);
   RAMSize = 0x54000;

   // don't know if this color mapper is correct or not... anyway...
   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x8000);

   setup_gfx();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   tc0200obj.ofs_x	= 9;
   tc0200obj.ofs_y	= 3; // sprite type now

   tc0100scn[0].layer[0].scr_x	=19;
   tc0100scn[0].layer[1].scr_x	=19;
   tc0100scn[0].layer[2].scr_x	=19;

   init_tc0100scn(0);

   AddRWBW(0x600000, 0x60FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_OBJECT);
   AddRWBW(0x400000, 0x400FFF, NULL, (UINT8*)f2_sprite_extension);
   // Notice : you can't position GFX_FG0 = RAM_VIDEO + 0x6000
   // because these 2 functions create a 0x4000 bytes long buffer from the
   // 0x1000 bytes of data (4x the size)
   AddWriteByte(0x906000, 0x906FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x906000, 0x906FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x900000, 0x90fFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x500000, 0x501FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadBW(0x300000, 0x30001F, NULL, input_buffer);			// INPUT
   AddReadByte(0xA00000, 0xA00003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddRWBW(0x700000, 0x7000FF, NULL, TC0360PRI_regs);

   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xA00000, 0xA00003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x300000, 0x30001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x920000, 0x92000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x300000, 0x30001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void solitary_fighter_ioc_0_wb(UINT32 offset, UINT8 data)
{
   switch(offset & 6){
      case 0:
         tc0220ioc_wb(0, data);
      break;
      case 2:
         tc0220ioc_wb(2, data);
      break;
      case 4:
         tc0220ioc_wb(8, data);
      break;
      default:
      break;
   }
}

static void solitary_fighter_ioc_0_ww(UINT32 offset, UINT16 data)
{
   solitary_fighter_ioc_0_wb(offset, (UINT8) (data & 0xFF));
}

static UINT8 solitary_fighter_ioc_0_rb(UINT32 offset)
{
   switch(offset & 6){
      case 0:
         return tc0220ioc_rb(0);
      break;
      case 2:
         return tc0220ioc_rb(2);
      break;
      case 4:
         return tc0220ioc_rb(8);
      break;
      default:
         return 0xFF;
      break;
   }
}

static UINT16 solitary_fighter_ioc_0_rw(UINT32 offset)
{
   return solitary_fighter_ioc_0_rb(offset);
}

static void solitary_fighter_ioc_1_wb(UINT32 offset, UINT8 data)
{
   switch(offset & 6){
      case 0:
         tc0220ioc_wb(4, data);
      break;
      case 2:
         tc0220ioc_wb(6, data);
      break;
      case 4:
         tc0220ioc_wb(14, data);
      break;
      default:
      break;
   }
}

static void solitary_fighter_ioc_1_ww(UINT32 offset, UINT16 data)
{
   solitary_fighter_ioc_1_wb(offset, (UINT8) (data & 0xFF));
}

static UINT8 solitary_fighter_ioc_1_rb(UINT32 offset)
{
   switch(offset & 6){
      case 0:
         return tc0220ioc_rb(4);
      break;
      case 2:
         return tc0220ioc_rb(6);
      break;
      case 4:
         return tc0220ioc_rb(14);
      break;
      default:
         return 0xFF;
      break;
   }
}

static UINT16 solitary_fighter_ioc_1_rw(UINT32 offset)
{
   return solitary_fighter_ioc_1_rb(offset);

}

static void load_solfigtr() {
  UINT8 *RAM_COLOUR;
   // SBCD flag bug - game relies on undefined flags (not supported in starscream)
  // Effect : big slow down when one of the player is loosing
  WriteWord68k(&ROM[0x09B9A],0x4E71);

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x0058E],0x4EF800C0);

   WriteLong68k(&ROM[0x000C0],0x46FC2000);

   WriteLong68k(&ROM[0x000C4],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x000C8],0x00AA0000);
   WriteWord68k(&ROM[0x000CC],0x6100-10);

   load_common();

   AddTaitoYM2610(0x01A9, 0x0155, 0x10000);

   RAM_OBJECT = RAM+0x10000;
   RAM_COLOUR = RAM+0x20000;
   RAM_SCROLL = RAM+0x22000;
   GFX_BANK   = RAM+0x22200;
   GFX_FG0    = RAM+0x23000;
   RAM_VIDEO  = RAM+0x30000;

   setup_gfx();

   RAMSize=0x40000;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   init_tc0100scn(0);

   AddRWBW(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddRWBW(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x300000, 0x300007, solitary_fighter_ioc_0_rb, NULL);	// INPUT
   AddReadByte(0x320000, 0x320007, solitary_fighter_ioc_1_rb, NULL);	// INPUT
   AddReadByte(0x400000, 0x400003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x300000, 0x300007, solitary_fighter_ioc_0_rw, NULL);	// INPUT
   AddReadWord(0x320000, 0x320007, solitary_fighter_ioc_1_rw, NULL);	// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteBW(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteByte(0x400000, 0x400003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x300000, 0x300007, solitary_fighter_ioc_0_wb, NULL);	// INPUT
   AddWriteByte(0x320000, 0x320007, solitary_fighter_ioc_1_wb, NULL);	// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x500000, 0x50001F, NULL, GFX_BANK);			// BANK
   AddWriteWord(0xB00000, 0xB0001F, NULL, GFX_BANK+0x20);		// priorities
   TC0360PRI_regs = GFX_BANK + 0x20;
   AddWriteWord(0x300000, 0x300007, solitary_fighter_ioc_0_ww, NULL);	// INPUT
   AddWriteWord(0x320000, 0x320007, solitary_fighter_ioc_1_ww, NULL);	// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static int init_gfx3;

static void load_thundfox(void)
{
   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x0A0C],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0A10],0x00AA0000);
   WriteWord68k(&ROM[0x0A14],0x6100-16);	// bra.s <loop>

   WriteLong68k(&ROM[0x07B0],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x07B4],0x00AA0000);

  load_common();

   /*-----[Sound Setup]-----*/
   AddTaitoYM2610(0x023A, 0x01BA, 0x10000);

   RAM_VIDEO  = RAM+0x04000;
   RAM_SCROLL = RAM+0x2E000;

   RAM_VIDEO2 = RAM+0x14000;
   RAM_SCROLL2= RAM+0x2E100;
   TC0360PRI_regs = RAM+0x2e200;

   RAM_OBJECT = RAM+0x24000;

   GFX_FG0    = RAM+0x30000;
   GFX_FG1    = RAM+0x34000;
   RAMSize=0x38000;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x2C000, 0x100, 0x10, 0x1000);

   setup_gfx();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x2C000, 0x100, 0x10, 0x1000);

   init_tc0100scn(0);
   memcpy(&tc0100scn[1],&tc0100scn[0],sizeof(struct TC0100SCN));

   init_gfx3 = 0;

   tc0100scn[1].layer[0].RAM	=RAM_VIDEO2 +0x0000;
   tc0100scn[1].layer[0].SCR	=RAM_SCROLL2 +0;
   tc0100scn[1].layer[0].scr_x	=15; // to be checked
   tc0100scn[1].layer[0].scr_y	=15;

   tc0100scn[1].layer[1].RAM	=RAM_VIDEO2 +0x8000;
   tc0100scn[1].layer[1].SCR	=RAM_SCROLL2 +2;
   tc0100scn[1].layer[1].scr_x	=15;
   tc0100scn[1].layer[1].scr_y	=15;

   tc0100scn[1].layer[2].RAM	=RAM_VIDEO2 +0x4000;
   tc0100scn[1].layer[2].GFX	=GFX_FG1;
   tc0100scn[1].layer[2].SCR	=RAM_SCROLL2 +4;

   tc0100scn[1].RAM     = RAM_VIDEO2;
   tc0100scn[1].GFX_FG0 = GFX_FG1;

   init_tc0100scn(1);

   AddRWBW(0x300000, 0x303FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddWriteByte(0x406000, 0x406FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x406000, 0x406FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x400000, 0x40FFFF, NULL, RAM_VIDEO);			// SCREEN0 RAM
   AddWriteByte(0x506000, 0x506FFF, tc0100scn_1_gfx_fg0_wb, NULL);	// FG1 GFX RAM
   AddWriteWord(0x506000, 0x506FFF, tc0100scn_1_gfx_fg0_ww, NULL);	// FG1 GFX RAM
   AddRWBW(0x500000, 0x50FFFF, NULL, RAM_VIDEO2);			// SCREEN1 RAM
   AddRWBW(0x600000, 0x607FFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadBW(0x200000, 0x20000F, NULL, input_buffer);			// INPUT
   AddReadByte(0x220000, 0x220003, tc0140syt_read_main_68k, NULL);	// SOUND COMM

   AddRWBW(0x800000,0x80001f,NULL,TC0360PRI_regs);

   AddReadWord(0x100000, 0x101FFF, NULL, RAM+0x02C000);			// COLOR RAM

   AddWriteByte(0x220000, 0x220003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x200000, 0x20000F, tc0220ioc_wb, NULL);		// INPUT RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

   AddWriteWord(0x100000, 0x101FFF, NULL, RAM+0x02C000);		// COLOR RAM
   AddWriteWord(0x420000, 0x42000F, NULL, RAM_SCROLL);			// SCROLL0 RAM
   AddWriteWord(0x520000, 0x52000F, NULL, RAM_SCROLL2);			// SCROLL1 RAM
   AddWriteWord(0x200000, 0x20000F, tc0220ioc_ww, NULL);		// INPUT RAM
   finish_conf_68000(0);
}

static struct DSW_DATA dsw_data_pulirula_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_pulirula_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Magic"),                 0x0C, 0x03 },
   { "3",                     0x0C},
   { "4",                     0x08},
   { "5",                     0x04},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "4",                     0x10},
   { "5",                     0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Upright Controls"),      0x80, 0x02 },
   { _("Dual"),                  0x80},
   { _("Single"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_pulirula[] =
{
   { 0x0, 0xFF, dsw_data_pulirula_0 },
   { 0x2, 0xFF, dsw_data_pulirula_1 },
   { 0,        0,    NULL,      },
};

static void pri_swap_bytes(UINT32 offset, UINT16 data) {
  offset &= 0x1f;

  if (TC0360PRI_regs[offset] != data) {
    TC0360PRI_regs[(offset)] = data;
  }
}

static void pri_swap_word(UINT32 offset, UINT16 data) {
  offset &= 0x1f;
  if (ReadWord68k(&TC0360PRI_regs[offset]) != data) {
    WriteWord68k(&TC0360PRI_regs[(offset )], data);
  }
}

static void load_pulirula(void)
{
  UINT8 *RAM_COLOUR;
   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x084C],0x4EF9);		// jmp $300
   WriteLong68k(&ROM[0x084E],0x00000300);
   WriteLong68k(&ROM[0x00300],0x526DABF2);	// jsr <random gen>
   WriteLong68k(&ROM[0x00304],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00308],0x00AA0000);
   WriteWord68k(&ROM[0x0030C],0x6100-14);	// bra.s <loop>

  load_common();

   /*-----[Sound Setup]-----*/
   AddTaitoYM2610(0x01A4, 0x0150, 0x20000);

   RAM_OBJECT = RAM+0x10000;
   RAM_VIDEO  = RAM+0x20000;
   RAM_COLOUR = RAM+0x30000;
   RAM_SCROLL = RAM+0x32000;
   TC0360PRI_regs = RAM_SCROLL+0x10;
   RAM_ROTATE = RAM+0x34000;
   f2_sprite_extension = (UINT16*)(RAM+0x37000);
   GFX_FG0    = RAM+0x40000;
   RAMSize = 0x40000;

   // set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x8000);

   tc0005rot.RAM     = RAM_ROTATE;
   tc0005rot.RAM_SCR = RAM_ROTATE+0x2000;
   setup_gfx();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   init_gfx3 = 0;
   tc0100scn[0].layer[0].scr_x	=16+1;

   tc0100scn[0].layer[1].scr_x	=16+1;

   tc0100scn[0].layer[2].scr_x	=16+1;
   f2_sprites_colors = 64;

   init_tc0100scn(0);
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.ofs_x	= 6;
   tc0200obj.ofs_y	= 2; // sprite type : pulirula

   AddRWBW(0x300000, 0x30FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddRWBW(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN0 RAM
   AddRWBW(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x600000, 0x603FFF, NULL, (UINT8*)f2_sprite_extension);		// OBJECT EXTRA RAM
   AddWriteWord(0x400000, 0x401fff, tc0005rot_bg0_ww, NULL);		// SCREEN RAM (ROTATE)
   AddRWBW(0x400000, 0x40200F, NULL, RAM_ROTATE);			// SCREEN RAM (ROTATION) + scroll registers
   AddReadBW(0xB00000, 0xB0000F, NULL, input_buffer);			// INPUT
   AddRWBW(0x700000, 0x701FFF, NULL, RAM_COLOUR);
   AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM

   AddWriteByte(0xa00000,0xa0001f,pri_swap_bytes, NULL);
   // AddWriteByte(0xa00000,0xa0001f,NULL, TC0360PRI_regs);
   AddWriteWord(0xa00000,0xa0001f,pri_swap_word, NULL);
   // AddWriteWord(0xa00000,0xa0001f,NULL, TC0360PRI_regs);

   AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xB00000, 0xB0000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL0 RAM
   AddWriteWord(0xB00000, 0xB0000F, tc0220ioc_ww, NULL);		// INPUT
   finish_conf_68000(0);
}

/* specific sound roms for driveout... */

static struct OKIM6295interface okim6295_interface =
{
  1,
  { 8000 },			/* Hz ?? */
  { REGION_SOUND1 },	/* memory region */
  { 255 }			/* volume ?? */
};

static SOUND_INFO sound_driveout[] =
{
   { SOUND_M6295,   &okim6295_interface,	},
   { 0, 	    NULL,		},
};

static int driveout_sound_latch = 0;

static UINT8 sound_driveout_command_r(UINT32 offset)
{
  //cpu_set_irq_line(1,0,CLEAR_LINE);
  /*	logerror("sound IRQ OFF (sound command=%02x)\n",driveout_sound_latch); */
  return driveout_sound_latch;
}

static int oki_bank = 0;

static void reset_sound_driveout_region(void)
{
  OKIM6295_set_bank_base(0, ALL_VOICES, oki_bank*0x40000);
}

static void oki_bank_w(UINT32 offset, UINT8 data)
{
  if ((data&4) && (oki_bank!=(data&3)) )
    {
      oki_bank = (data&3);
    }
  reset_sound_driveout_region();
}

static void sound_driveout_command_wb(UINT32 offset, UINT16 data)
{
  static int nibble = 0;
  offset &=3;

  if (offset==0)
    {
      nibble = data & 1;
    }
  else
    {
      if (nibble==0)
	{
	  driveout_sound_latch = (data & 0x0f) | (driveout_sound_latch & 0xf0);
	}
      else
	{
	  driveout_sound_latch = ((data<<4) & 0xf0) | (driveout_sound_latch & 0x0f);
	  cpu_interrupt(CPU_Z80_0, 0x38);
	}
    }
}

static void load_common_driftout() {
  load_common();

  /*-----[Sound Setup]-----*/

  RAM_OBJECT = RAM+0x33000;
  RAM_VIDEO  = RAM+0x16000-0x4000;
  RAM_SCROLL = RAM+0x20020;
  RAM_ROTATE = RAM+0x10000;
  GFX_FG0    = RAM+0x21000;

  RAM_INPUT  = input_buffer;

  set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
  InitPaletteMap(RAM+0x14000, 0x100, 0x10, 0x8000);
  // Init tc0005rot emulation
  // ------------------------

  tc0005rot.RAM     = RAM_ROTATE;
  tc0005rot.RAM_SCR = RAM_ROTATE+0x2000;
  setup_gfx();

  // tc0200obj.ofs_x	= 8;

  tc0220ioc.RAM  = input_buffer;
  tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
  reset_tc0220ioc();

  tc0200obj.ofs_x	= -3+6; // ???
  tc0100scn[0].layer[0].scr_x	=19;
  tc0100scn[0].layer[1].scr_x	=19; // -80 for f2demo !
  tc0100scn[0].layer[2].scr_x	=19;
  init_tc0100scn(0);


  /*
   *  StarScream Stuff follows
   */

  AddRWBW(0x300000, 0x30FFFF, NULL, RAM+0x000000);			// 68000 RAM
  AddReadByte(0xB00000, 0xB0001F, NULL, input_buffer);			// INPUT RAM
  AddRWBW(0x900000, 0x90fFFF, NULL, RAM_OBJECT);			// OBJECT RAM
  AddRWBW(0x700000, 0x701FFF, NULL, RAM+0x014000);		// COLOR RAM

  AddReadWord(0x400000, 0x40200F, NULL, RAM_ROTATE);			// SCREEN/SCROLL (ROT)
  AddReadWord(0xB00000, 0xB0001F, NULL, RAM_INPUT);			// INPUT RAM

  AddWriteByte(0xB00000, 0xB0001F, tc0220ioc_wb, NULL);		// INPUT RAM
  AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

  AddWriteWord(0x400000, 0x401FFF, tc0005rot_bg0_ww, NULL);		// SCREEN RAM (ROTATE)
  AddWriteWord(0x402000, 0x40200F, NULL, RAM+0x012000);		// SCROLL RAM (ROTATE)
  AddWriteWord(0x804000, 0x805FFF, NULL, RAM+0x016000);		// SCREEN RAM
  AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
  AddWriteWord(0x820000, 0x82000F, NULL, RAM+0x020020);		// SCROLL RAM
  AddWriteBW(0xA00000, 0xA0001F, NULL, RAM+0x020030);		// Priorities
  TC0360PRI_regs = RAM+0x020030;
  AddWriteWord(0xB00000, 0xB0001F, tc0220ioc_ww, NULL);		// INPUT RAM
}

static void load_driftout() {
  // 68000 Speed Hack
  // ----------------
  WriteWord68k(&ROM[0x0724],0x13FC);	//	move.b	#$00,$AA0000
  WriteWord68k(&ROM[0x0726],0x0000);	//	move.b	#$00,$AA0000
  WriteWord68k(&ROM[0x0728],0x00AA);	//
  WriteWord68k(&ROM[0x072a],0x0000);	//	move.b	#$00,$AA0000
  WriteWord68k(&ROM[0x072C],0x6100-14);	//	bra.s	<loop>

  load_common_driftout();

  AddTaitoYM2610(0x023A, 0x01BA, 0x10000);

  AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
  AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM

  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
  AddReadByte(-1, -1, NULL, NULL);
  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
  AddReadWord(-1, -1,NULL, NULL);
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
  AddWriteByte(-1, -1, NULL, NULL);
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
  AddWriteWord(-1, -1, NULL, NULL);

  AddInitMemory();	// Set Starscream mem pointers...
}

static void load_driveout() {
  UINT8 *z80_ram;
  WriteWord68k(&ROM[0x0700],0x13FC);	//	move.b	#$00,$AA0000
  WriteWord68k(&ROM[0x0702],0x0000);	//	move.b	#$00,$AA0000
  WriteWord68k(&ROM[0x0704],0x00AA);	//
  WriteWord68k(&ROM[0x0706],0x0000);	//	move.b	#$00,$AA0000
  WriteWord68k(&ROM[0x0708],0x6100-14);	//	bra.s	<loop>

  load_common_driftout();

  z80_ram = RAM + 0x32120;

  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

  AddZ80AReadByte(0x0000, 0x7FFF, NULL,	Z80ROM);			// BANK ROM
  AddZ80AReadByte(0x8000, 0x87FF, NULL, z80_ram);	// Z80 RAM
  AddZ80AReadByte(0x9800, 0x9801, OKIM6295_status_0_r, NULL);
  AddZ80AReadByte(0xa000, 0xa000, sound_driveout_command_r, NULL);
  AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
  AddZ80AReadByte(    -1,     -1, NULL, 			NULL);

  AddZ80AWriteByte(0x8000, 0x87ff, NULL, z80_ram);	// Z80 RAM
  AddZ80AWrite(0x9000,0x9000,oki_bank_w, NULL);
  AddZ80AWrite(0x9800,0x9800,OKIM6295_data_0_w,NULL);
  AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
  AddZ80AWriteByte(    -1,     -1, NULL,			NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
  AddZ80AReadPort(  -1,   -1, NULL,			NULL);

  // AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
  AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);
  AddZ80AWritePort(  -1,   -1, NULL,			NULL);

  AddZ80AInit();

  // AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
  AddWriteByte(0x200000, 0x200003, sound_driveout_command_wb, NULL);	// SOUND COMM

  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
  AddReadByte(-1, -1, NULL, NULL);
  // AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
  AddReadWord(-1, -1,NULL, NULL);
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
  AddWriteByte(-1, -1, NULL, NULL);
  // AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
  AddWriteWord(-1, -1, NULL, NULL);

  AddInitMemory();	// Set Starscream mem pointers...
}

static void load_ssi() {
  WriteWord68k(&ROM[0x01FB4],0x4EF9);
  WriteLong68k(&ROM[0x01FB6],0x000000C0);

  WriteWord68k(&ROM[0x000C0],0x4EB9);		//	jsr	<???>
  if(is_current_game("ssi"))
    WriteLong68k(&ROM[0x000C2],0x0000932A);
  else
    WriteLong68k(&ROM[0x000C2],0x0000929A);

  WriteWord68k(&ROM[0x000C6],0x4EB9);		//	jsr	<random gen>
  WriteLong68k(&ROM[0x000C8],0x00001BE6);

  WriteLong68k(&ROM[0x000CC],0x13FC0000);	//	move.b	#$00,$AA0000
  WriteLong68k(&ROM[0x000D0],0x00AA0000);

  WriteWord68k(&ROM[0x000D4],0x6100-0x16);	//	bra.s	<loop>

  if(is_current_game("ssi"))
    {
      WriteLong68k(&ROM[0x09CFC],0x00000100);

      WriteWord68k(&ROM[0x00100],0x4EB9);
      WriteLong68k(&ROM[0x00102],0x0000B3E6);
      WriteLong68k(&ROM[0x00106],0x13FC0000);	//	move.b	#$00,$AA0000
      WriteLong68k(&ROM[0x0010A],0x00AA0000);
      WriteWord68k(&ROM[0x0010E],0x4E75);
    }
  else
    {
      WriteLong68k(&ROM[0x09C6C],0x00000100);

      WriteWord68k(&ROM[0x00100],0x4EB9);
      WriteLong68k(&ROM[0x00102],0x0000B41C);
      WriteLong68k(&ROM[0x00106],0x13FC0000);	//	move.b	#$00,$AA0000
      WriteLong68k(&ROM[0x0010A],0x00AA0000);
      WriteWord68k(&ROM[0x0010E],0x4E75);
    }

  load_common();

  /*-----[Sound Setup]-----*/

  AddTaitoYM2610(0x0217, 0x018F, 0x10000);

  RAM_OBJECT = RAM+0x10000;
  GFX_FG0    = RAM+0x3C000;

  set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
  InitPaletteMap(RAM+0x20000, 0x100, 0x10, 0x1000);

  setup_gfx();
  tc0220ioc.RAM  = input_buffer;
  tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
  reset_tc0220ioc();

  tc0200obj.ofs_x	= 10;

  /*
   *  StarScream Stuff follows
   */

  AddRWBW  (0x200000, 0x20FFFF, NULL, RAM+0x000000);			// 68000 RAM
  AddReadBW(0x100000, 0x10000F, NULL, input_buffer);			// INPUT
  AddReadByte(0x400000, 0x400003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
  AddRWBW  (0x800000, 0x80FFFF, NULL, RAM_OBJECT);			// SPRITE

  AddReadWord(0x300000, 0x301FFF, NULL, RAM+0x020000);			// COLOR RAM

  AddWriteByte(0x400000, 0x400003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
  AddWriteByte(0x500000, 0x5000FF, NULL, RAM+0x022200);		// ???
  AddWriteByte(0x100000, 0x10000F, tc0220ioc_wb, NULL);		// INPUT
  AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

  AddWriteWord(0x300000, 0x301FFF, NULL, RAM+0x020000);		// COLOR RAM
  AddWriteWord(0x500000, 0x5000FF, NULL, RAM+0x022200);		// ???
  AddWriteWord(0x100000, 0x10000F, tc0220ioc_ww, NULL);		// INPUT
  finish_conf_68000(0);
}

static void load_megab(void)
{
  ROM[0x00628]=0x4E;
  ROM[0x00629]=0x71;
  ROM[0x0062A]=0x4E;
  ROM[0x0062B]=0x71;

  ROM[0x0770]=0x13;		// move.b #$00,$AA0000
  ROM[0x0771]=0xFC;		// Speed Hack
  ROM[0x0772]=0x00;
  ROM[0x0773]=0x00;
  ROM[0x0774]=0x00;
  ROM[0x0775]=0xAA;
  ROM[0x0776]=0x00;
  ROM[0x0777]=0x00;

  ROM[0x0778]=0x60;
  ROM[0x0779]=0x100-(6+10);

  load_common();

  AddTaitoYM2610(0x023A, 0x01BA, 0x10000);

  /*-----------------------*/

  RAM_VIDEO  = RAM+0x18000;
  RAM_SCROLL = RAM+0x3C100;
  RAM_OBJECT = RAM+0x10000;
  GFX_FG0    = RAM+0x3c200;

  set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
  InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x1000);

  setup_gfx();

  // Init tc0220ioc emulation
  // ------------------------

  tc0100scn[0].layer[0].scr_x	=19;
  tc0100scn[0].layer[1].scr_x	=19; // -80 for f2demo !
  tc0100scn[0].layer[2].scr_x	=19;
  tc0200obj.ofs_x	= -3+6; // ???

  tc0220ioc.RAM  = RAM_INPUT;
  tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
  reset_tc0220ioc();

  // Init tc0100scn emulation
  // ------------------------

  init_tc0100scn(0);
  tc0100scn_0_copy_gfx_fg0(ROM+0x10FC2, 0x1000);

  /*
   *  StarScream Stuff follows
   */

  AddRWBW(0x200000, 0x20FFFF, NULL, RAM+0x000000);			// 68000 RAM
  AddRWBW(0x600000, 0x61FFFF, NULL, RAM_VIDEO);			// SCREEN RAM

  AddReadBW(0x120000, 0x12000F, NULL, RAM_INPUT);			// INPUT
  AddReadByte(0x100000, 0x100003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
  AddRWBW(0x180000, 0x180FFF, NULL, RAM+0x038000);			// C-CHIP (HACKED?)
  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
  AddReadByte(-1, -1, NULL, NULL);

  AddReadWord(0x800000, 0x807FFF, NULL, RAM_OBJECT);			// SPRITE RAM
  AddReadWord(0x300000, 0x301FFF, NULL, RAM+0x03A000);			// COLOR RAM
  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
  AddReadWord(-1, -1,NULL, NULL);

  AddWriteByte(0x800000, 0x807FFF, NULL, RAM_OBJECT);			// SPRITE RAM
  AddWriteByte(0x400000, 0x4000FF, NULL, RAM+0x039000);		// ???
  AddWriteByte(0x100000, 0x100003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
  AddWriteByte(0x120000, 0x12000F, tc0220ioc_wb, NULL);		// INPUT
  AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
  AddWriteByte(-1, -1, NULL, NULL);

  AddWriteWord(0x200000, 0x20FFFF, NULL, RAM+0x000000);		// 68000 RAM
  AddWriteWord(0x800000, 0x807FFF, NULL, RAM_OBJECT);			// SPRITE RAM
  AddWriteWord(0x300000, 0x301FFF, NULL, RAM+0x03A000);		// COLOR RAM
  AddWriteWord(0x620000, 0x6200FF, NULL, RAM+0x03C100);		// SCROLL RAM
  AddWriteWord(0x400000, 0x4000FF, NULL, RAM+0x039000);		// ???
  AddWriteWord(0x120000, 0x12000F, tc0220ioc_ww, NULL);		// INPUT
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
  AddWriteWord(-1, -1, NULL, NULL);

  AddInitMemory();	// Set Starscream mem pointers...
  TC0360PRI_regs = RAM+0x039000;
}

static void load_liquidk(void)
{
   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x89F6],0x4E714E71);
   WriteLong68k(&ROM[0x89FA],0x4E714E71);

   // Fix ROM Checksum
   // ----------------

   WriteWord68k(&ROM[0x1DAE],0x4E75);

   // Fix Long Sound Wait
   // -------------------

   WriteWord68k(&ROM[0x017A],0x4E71);

   load_common();

   if (load_region[REGION_CPU2]) {
     setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(4.2,60));
     AddTaitoYM2610(0x01DD, 0x0189, 0x10000);
   }

   /*-----------------------*/

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x32000;
   RAM_OBJECT = RAM+0x20000;
   GFX_FG0    = RAM+0x34000;

   setup_gfx();
   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x1000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   // tc0100scn[0].layer[0].scr_x	=20;

   // tc0100scn[0].layer[1].scr_x	=20; // -80 for f2demo !

   // tc0100scn[0].layer[2].scr_x	=20;
   // tc0100scn[0].layer[2].scr_y	=24;
   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.ofs_x	= -3+7; // ???

/*
 *  StarScream Stuff follows
 */

   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadBW(0x300000, 0x30001F, NULL, input_buffer);			// INPUT
   AddReadByte(0x320000, 0x320003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x400000, 0x40000F, NULL, RAM+0x032200);			// ???

   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0x200000, 0x201FFF, NULL, RAM+0x030000);			// COLOR RAM

   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0x300000, 0x30001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0x400000, 0x40000F, NULL, RAM+0x032200);		// ???
   AddWriteByte(0x320000, 0x320003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteBW(0xB00000, 0xB000FF, NULL, RAM+0x032300);		// ???

   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x200000, 0x201FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteWord(0x300000, 0x30001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x380000, 0x38000F, NULL, RAM+0x032180);		// ???
   AddWriteWord(0x600000, 0x60000F, NULL, RAM+0x032280);		// ???

   finish_conf_68000(0);
   TC0360PRI_regs = RAM+0x032300;
}

static int last_scr,last_scr2;

static void execute_dondokdj(void)
{
   tc0005rot_set_bitmap();

   last_scr=ReadLong(&RAM_OBJECT[0x24]); // Keep Sprites and Scrolling in sync (sprites are 1 frame behind)

   //print_ingame(60,gettext("%04x"),ReadWord(&RAM_OBJECT[0x0A]));

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610

   tc0005rot_unset_bitmap();
}

static void execute_driftout(void)
{
   tc0005rot_set_bitmap();

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);
   cpu_execute_cycles(CPU_68K_0,500);
   cpu_interrupt(CPU_68K_0, 5);

   Taito2610_Frame();			// Z80 and YM2610

   tc0005rot_unset_bitmap();
}

static void execute_driveout(void)
{
  // rotation frame, no sprites delay
   tc0005rot_set_bitmap();

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, 500);	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   cpu_execute_cycles(CPU_Z80_0, (4000000/60));			// Sound Z80
   tc0005rot_unset_bitmap();
}

static void execute_liquidk(void)
{
   last_scr=ReadLong(&RAM_OBJECT[0x24]); // Keep Sprites and Scrolling in sync (sprites are 1 frame behind)

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   Taito2610_Frame();			// Z80 and YM2610
}

static void execute_f2demo(void)
{
  // the demo appears too much on the right, but it's based on mame source...
  // It's funny there is such a difference, because we are very similar for the games.
  UINT16 *scroll = (UINT16*)RAM_SCROLL+1;
   last_scr=ReadLong(&RAM_OBJECT[0x24]); // Keep Sprites and Scrolling in sync (sprites are 1 frame behind)

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   if ((RAM[0x32104] & 8) == 0)
     scroll[1]--;
   else if ((RAM[0x32104] & 4) == 0)
     scroll[1]++;
   else if ((RAM[0x32104] & 1) == 0) // up
     scroll[4]++;
   else if ((RAM[0x32104] & 2) == 0) // up
     scroll[4]--;
}

static void execute_megab(void)
{
  RAM[0x38802]=0x01; // c chip for megab

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, 500);	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610
}

static void execute_ssi(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(6,60));	// Overflow for sprite sync

   Taito2610_Frame();			// Z80 and YM2610
}

static void execute_mjnquest(void)
{
  // no delay, no c chip, no rotating tile !
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, 500);	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610
}

static void execute_solfigtr(void)
{
  // no delay, no c chip, no rotating tile, but sprite banks...
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, 500);	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610
   make_object_bank(GFX_BANK);
}

static void execute_growl(void)
{
  // no delay, no c chip, no rotating tile, but sprite banks...
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610
   make_object_bank(GFX_BANK);
}

static void execute_gunfront(void)
{
  // 68k overclocked because of speed hacks, 2 execute_cycles / frame for sprite sync
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(20,60) - s68000context.odometer);
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 5);
   s68000context.odometer = 0;
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(20,60));

   Taito2610_Frame();			// Z80 and YM2610
}

static void execute_cameltry(void)
{
   static int p1_paddle_x,p1_paddle_y;
   static int p2x,p2y;
   int px,py;

   p1_paddle_x=p1_paddle_x/2;
   p1_paddle_y=p1_paddle_y/2;
   p2x=p2x/2;
   p2y=p2y/2;

   /*------[Mouse Hack]-------*/

   GetMouseMickeys(&px,&py);

   p1_paddle_x+=px/4;
   p1_paddle_y+=py/4;

   if(*MouseB&1){input_buffer[0x04]&=0x10^255;}

   if((!(input_buffer[0x4]&4))&&(p1_paddle_x> -0x40)) p1_paddle_x-=0x08;
   if((!(input_buffer[0x4]&8))&&(p1_paddle_x<  0x3F)) p1_paddle_x+=0x08;

   if((!(input_buffer[0x6]&4))&&(p2x> -0x40)) p2x-=0x08;
   if((!(input_buffer[0x6]&8))&&(p2x<  0x3F)) p2x+=0x08;

   WriteWord(&input_buffer[0x18],p1_paddle_x);
   WriteWord(&input_buffer[0x1C],p2x);

   tc0005rot_set_bitmap();

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 5);

   execute_z80_audio_frame();

   tc0005rot_unset_bitmap();
}

#define TC0360PRI_regs_lsb(x) TC0360PRI_regs[(x)*2]
#define TC0360PRI_regs_msb(x) TC0360PRI_regs[(x)*2+1]

static void draw_f2_pri_rot_delay(void)
{
  int ta, num,pri_mask=0;
  UINT8 rozpri;
   ClearPaletteMap();

   if (!init_gfx)
     finish_setup_gfx();

   for (ta=0; ta<8; ta++)
     layer[ta].num = ta;

   layer[0].pri = TC0360PRI_regs_lsb(5) & 0x0f; // tc100scn BG0 (or flipped)
   layer[1].pri = TC0360PRI_regs_lsb(5) >> 4; // tc100scn BG1 (or flipped)
   layer[2].pri = TC0360PRI_regs_lsb(4) >> 4; // tc100scn FG0
   rozpri = (TC0360PRI_regs_lsb(1) & 0xc0) >> 6;
   rozpri = (TC0360PRI_regs_lsb(8 + rozpri/2) >> 4*(rozpri & 1)) & 0x0f;
   layer[3].pri = rozpri;
   layer[4].pri = TC0360PRI_regs_lsb(6) & 0x0f; // sprites colors 00
   layer[5].pri = TC0360PRI_regs_lsb(6) >> 4;   // sprites colors 01
   layer[6].pri = TC0360PRI_regs_lsb(7) & 0x0f; // sprites colors 10
   layer[7].pri = TC0360PRI_regs_lsb(7) >> 4;   // sprites colors 11
   qsort(&layer,8,sizeof(struct layer),layer_cmp);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   /* Notice : below there is a hack to try to do without a priority bitmap
    * but it doesn't work well for pulirula.
    * But adding a priority bitmap would require to use it for all the games
    * using tc005rot, tc200obj or tc100scn, which is a really big mess.
    * So for now I prefer to leave it as it is... ! */

   if(RefreshBuffers){
      tc0005rot_refresh_buffer();
   }

   last_scr2=ReadLong(&RAM_OBJECT[0x24]);	// [Store]
   WriteLong(&RAM_OBJECT[0x24],last_scr);	// Delay Scrolling 1 frame
   for (ta=0; ta<8; ta++) {
     num = layer[ta].num;
     if (ta == 0 && num > 3)
       clear_game_screen(0);
     switch(num) {
     case 0:
     case 1:
     case 2:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       render_tc0100scn_layer_mapped(0,num,ta>0);
       break;
     case 3:
       tc0005rot_draw_rot((ReadWord(&TC0360PRI_regs[2])&0x3F)<<2,ta>0);
       break;
     default:
       pri_mask |= (1<<(num & 3));
     }
   }
   if (pri_mask) {
     render_tc0200obj_mapped(pri_mask);
   }
   WriteLong(&RAM_OBJECT[0x24],last_scr2);	// [Restore]
}

// Compared to dondokod it does not have the 1 frame delay for the sprites
// and it does not have bg0/bg1.
static void draw_cameltry(void)
{
  int ta, num,pri_mask=0;
  UINT8 rozpri;
   ClearPaletteMap();

   if (!init_gfx)
     finish_setup_gfx();

   for (ta=0; ta<6; ta++)
     layer[ta].num = ta;

   rozpri = (TC0360PRI_regs_lsb(1) & 0xc0) >> 6;
   rozpri = (TC0360PRI_regs_lsb(8 + rozpri/2) >> 4*(rozpri & 1)) & 0x0f;
   layer[0].pri = TC0360PRI_regs_lsb(6) & 0x0f; // sprites colors 00
   layer[1].pri = TC0360PRI_regs_lsb(6) >> 4;   // sprites colors 01
   layer[2].pri = TC0360PRI_regs_lsb(7) & 0x0f; // sprites colors 10
   layer[3].pri = TC0360PRI_regs_lsb(7) >> 4;   // sprites colors 11
   layer[4].pri = rozpri;
   layer[5].pri = TC0360PRI_regs_lsb(4) >> 4; // tc100scn FG0
   qsort(&layer,6,sizeof(struct layer),layer_cmp);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   if(RefreshBuffers){
      tc0005rot_refresh_buffer();
   }
   if (layer[0].num != 4) {
     UINT8 *map;
     MAP_PALETTE_MAPPED_NEW(
            0,
              16,
              map
            );
     clear_game_screen(ReadLong(&map[0]));
   }

   for (ta=0; ta<6; ta++) {
     num = layer[ta].num;
     switch(num) {
     case 5:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       render_tc0100scn_layer_mapped(0,2,ta>0);
       break;
     case 4:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       tc0005rot_draw_rot((ReadWord(&TC0360PRI_regs[2])&0x3F)<<2,ta>0);
       break;
     default:
       pri_mask |= (1<<(num & 3));
     }
   }
   if (pri_mask) {
     render_tc0200obj_mapped(pri_mask);
   }
}

static void draw_f2_pri_rot(void)
{
  int ta, num,pri_mask=0;
  UINT8 rozpri,*map;
   ClearPaletteMap();

   if (!init_gfx)
     finish_setup_gfx();

   for (ta=0; ta<6; ta++)
     layer[ta].num = ta;

   layer[5].pri = TC0360PRI_regs_msb(4) >> 4; // tc100scn FG0
   rozpri = (TC0360PRI_regs_msb(1) & 0xc0) >> 6;
   rozpri = (TC0360PRI_regs_msb(8 + rozpri/2) >> 4*(rozpri & 1)) & 0x0f;
   layer[4].pri = rozpri;
   layer[0].pri = TC0360PRI_regs_msb(6) & 0x0f; // sprites colors 00
   layer[1].pri = TC0360PRI_regs_msb(6) >> 4;   // sprites colors 01
   layer[2].pri = TC0360PRI_regs_msb(7) & 0x0f; // sprites colors 10
   layer[3].pri = TC0360PRI_regs_msb(7) >> 4;   // sprites colors 11
   qsort(&layer,6,sizeof(struct layer),layer_cmp);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   if(RefreshBuffers){
      tc0005rot_refresh_buffer();
   }

   // in fact the priorities in drift out never place the rotating layer as the first
   // layer (at least nowhere in the attract mode nor in the 1st race). So no need to
   // bother : just clear the screen then draw a transparant rotating layer.
   if (layer[0].num < 4) {
     MAP_PALETTE_MAPPED_NEW(
            0,
              16,
              map
            );
     clear_game_screen(ReadLong(&map[0]));
   }
   for (ta=0; ta<6; ta++) {
     num = layer[ta].num;
     switch(num) {
     case 0:
     case 1:
     case 2:
     case 3:
       pri_mask |= (1<<(num));
       break;
     case 4:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       tc0005rot_draw_rot_r270((ReadWord(&TC0360PRI_regs[2])&0x3F)<<2,ta>0);
       break;
     case 5:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       render_tc0100scn_layer_mapped(0,2,ta>0);
       break;
     }
   }
   if (pri_mask) {
     render_tc0200obj_mapped(pri_mask);
   }
}

// same thing without the rotated layer (TC280GRD)
static void draw_f2_pri(void)
{
  int ta, num,pri_mask=0;
  UINT8 *map;
   ClearPaletteMap();

   if (!init_gfx)
     finish_setup_gfx();

   for (ta=0; ta<8; ta++)
     layer[ta].num = ta;

   layer[0].pri = TC0360PRI_regs_lsb(5) & 0x0f; // tc100scn BG0 (or flipped)
   layer[1].pri = TC0360PRI_regs_lsb(5) >> 4; // tc100scn BG1 (or flipped)
   layer[2].pri = TC0360PRI_regs_lsb(4) >> 4; // tc100scn FG0
   // sprites must start at 4, so layer 3 is empty
   layer[4].pri = TC0360PRI_regs_lsb(6) & 0x0f; // sprites colors 00
   layer[5].pri = TC0360PRI_regs_lsb(6) >> 4;   // sprites colors 01
   layer[6].pri = TC0360PRI_regs_lsb(7) & 0x0f; // sprites colors 10
   layer[7].pri = TC0360PRI_regs_lsb(7) >> 4;   // sprites colors 11
   qsort(&layer,8,sizeof(struct layer),layer_cmp);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   if (layer[0].num >= 4) {
     MAP_PALETTE_MAPPED_NEW(
            0,
              16,
              map
            );
     clear_game_screen(ReadLong(&map[0]));
   }
   for (ta=0; ta<8; ta++) {
     num = layer[ta].num;
     switch(num) {
     case 0:
     case 1:
     case 2:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       render_tc0100scn_layer_mapped(0,num,ta>0);
       break;
     case 3:
       // tc0005rot_draw_rot((ReadWord(&RAM[0x32302])&0x3F)<<2);
       break;
     default:
       pri_mask |= (1<<(num & 3));
     }
   }
   if (pri_mask) {
     render_tc0200obj_mapped(pri_mask);
   }
}

// And a mix between the 2
static void draw_f2_pri_delay(void)
{
  int ta, num,pri_mask=0;
  UINT8 *map;
   ClearPaletteMap();

   if (!init_gfx)
     finish_setup_gfx();

   for (ta=0; ta<8; ta++)
     layer[ta].num = ta;

   layer[0].pri = TC0360PRI_regs_lsb(5) & 0x0f; // tc100scn BG0 (or flipped)
   layer[1].pri = TC0360PRI_regs_lsb(5) >> 4; // tc100scn BG1 (or flipped)
   layer[2].pri = TC0360PRI_regs_lsb(4) >> 4; // tc100scn FG0
   // no layer 3
   layer[4].pri = TC0360PRI_regs_lsb(6) & 0x0f; // sprites colors 00
   layer[5].pri = TC0360PRI_regs_lsb(6) >> 4;   // sprites colors 01
   layer[6].pri = TC0360PRI_regs_lsb(7) & 0x0f; // sprites colors 10
   layer[7].pri = TC0360PRI_regs_lsb(7) >> 4;   // sprites colors 11
   qsort(&layer,8,sizeof(struct layer),layer_cmp);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   last_scr2=ReadLong(&RAM_OBJECT[0x24]);	// [Store]
   WriteLong(&RAM_OBJECT[0x24],last_scr);	// Delay Scrolling 1 frame
   if (layer[0].num > 1) {
     MAP_PALETTE_MAPPED_NEW(
            0,
              16,
              map
            );
     clear_game_screen(ReadLong(&map[0]));
   }
   for (ta=0; ta<8; ta++) {
     num = layer[ta].num;
     // printf("%d:%d ",num,layer[ta].pri);
     switch(num) {
     case 0:
     case 1:
     case 2:
       if (pri_mask) {
	 render_tc0200obj_mapped(pri_mask);
	 pri_mask = 0;
       }
       render_tc0100scn_layer_mapped(0,num,ta>0);
       break;
     case 3:
       break;
     default:
       pri_mask |= (1<<(num & 3));
       break;
     }
   }
   if (pri_mask) {
     render_tc0200obj_mapped(pri_mask);
   }
   WriteLong(&RAM_OBJECT[0x24],last_scr2);	// [Restore]
}

static void draw_thundfox(void)
{
  UINT8 *map;
  /* Clearly the priorities chip is not used for this game :
      - if you believe theory, a bg layer should go on top of sprites, which creates
     a big black thunder bolt during attract mode
      - Also fg priority often becomes bad, and text disappears behind sprites
    The priorities found by hand by Antiriad seem to work much better ! :-) */

   ClearPaletteMap();
   if (!init_gfx3) {
     tc0100scn[1].layer[0].GFX	=gfx3;
     tc0100scn[1].layer[0].MASK	=gfx3_solid;
     tc0100scn[1].layer[1].GFX	=gfx3;
     tc0100scn[1].layer[1].MASK	=gfx3_solid;
     tc0100scn[1].layer[0].tile_mask=
     tc0100scn[1].layer[1].tile_mask=
       max_sprites[2]-1;
     init_gfx3 = 1;

     finish_setup_gfx();
   }
   // it would be draw_no_pri if bg0 was really solid, but in attract mode
   // you get a black area if you draw bg0 as solid.
   // And you have the init of the 2 tc100scn also.
   MAP_PALETTE_MAPPED_NEW(
            0,
              16,
              map
            );
   clear_game_screen(ReadLong(&map[0]));

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL + 12);
   tc0100scn[1].ctrl = ReadWord(RAM_SCROLL2 + 12);

   // BG0 A
   // -----

   render_tc0100scn_layer_mapped(1,0,1);

   // BG0 B
   // -----

   render_tc0100scn_layer_mapped(0,0,1);

   // BG1 A
   // -----

   render_tc0100scn_layer_mapped(1,1,1);

   // BG1 B
   // -----

   render_tc0100scn_layer_mapped(0,1,1);

   // OBJECT
   // ------

   render_tc0200obj_mapped(255);

   // FG0 A
   // -----

   render_tc0100scn_layer_mapped(1,2,1);

   // FG0 B
   // -----

   render_tc0100scn_layer_mapped(0,2,1);
}

static void draw_ssi(void)
{
  UINT8 *map;
   ClearPaletteMap();

   if (!init_gfx)
     finish_setup_gfx();

     MAP_PALETTE_MAPPED_NEW(
            0,
              16,
              map
            );
     clear_game_screen(ReadLong(&map[0]));

   // only sprites, and apparently there are no priorities to handle
   // (because the sprites are probably grouped since there are big sprites)
   render_tc0200obj_mapped(255);
}

static void draw_no_pri() {
  ClearPaletteMap();
   if (!init_gfx)
     finish_setup_gfx();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // OBJECT
   // ------

   render_tc0200obj_mapped(255);

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);
}

// and mahjong quest : no priorities at all ?!!
static void draw_mjnquest(void)
{
   if(ReadWord(&GFX_BANK[0])==0){
      tc0100scn[0].layer[0].GFX  = GFX;
      tc0100scn[0].layer[0].MASK = gfx_solid[0];
      tc0100scn[0].layer[1].GFX  = GFX;
      tc0100scn[0].layer[1].MASK = gfx_solid[0];
   }
   else{
      tc0100scn[0].layer[0].GFX  = GFX + (0x8000 * 0x40);
      tc0100scn[0].layer[0].MASK = gfx_solid[0] + (0x8000);
      tc0100scn[0].layer[1].GFX  = GFX + (0x8000 * 0x40);
      tc0100scn[0].layer[1].MASK = gfx_solid[0] + (0x8000);
   }

   draw_no_pri();
}













// The inputs do not have the same adreses as dondokod. Maybe we should use input_buffer
// instead of a direct mapping...
static struct INPUT_INFO input_megab[] =
{
   INP0( COIN1, 0x03C00E, 0x04 ),
   INP0( COIN2, 0x03C00E, 0x08 ),
   INP0( TILT, 0x03C00E, 0x01 ),
   INP0( SERVICE, 0x03C00E, 0x02 ),

   INP0( P1_START, 0x03C00E, 0x10 ),
   INP0( P1_UP, 0x03C004, 0x01 ),
   INP0( P1_DOWN, 0x03C004, 0x02 ),
   INP0( P1_LEFT, 0x03C004, 0x04 ),
   INP0( P1_RIGHT, 0x03C004, 0x08 ),
   INP0( P1_B1, 0x03C004, 0x10 ),
   INP0( P1_B2, 0x03C004, 0x20 ),

   INP0( P2_START, 0x03C00E, 0x20 ),
   INP0( P2_UP, 0x03C006, 0x01 ),
   INP0( P2_DOWN, 0x03C006, 0x02 ),
   INP0( P2_LEFT, 0x03C006, 0x04 ),
   INP0( P2_RIGHT, 0x03C006, 0x08 ),
   INP0( P2_B1, 0x03C006, 0x10 ),
   INP0( P2_B2, 0x03C006, 0x20 ),

   END_INPUT
};


















static struct VIDEO_INFO video_cameltry =
{
   draw_cameltry,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_dondokdj =
{
   draw_f2_pri_rot_delay,
   320,
   224,
   32,
   VIDEO_ROTATE_180 | VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_driftout =
{
   draw_f2_pri_rot,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_finalb =
{
   draw_no_pri,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
   finalb_gfxdecodeinfo
};
static struct VIDEO_INFO video_gunfront =
{
   draw_f2_pri,
   320,
   224,
   32,
   VIDEO_ROTATE_270 | VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_liquidk =
{
   draw_f2_pri_delay,
   320,
   224,
   32,
   VIDEO_ROTATE_180 | VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_mjnquest =
{
   draw_mjnquest,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
   mjnquest_gfxdecodeinfo
};
static struct VIDEO_INFO video_pulirula =
{
   draw_f2_pri_rot_delay,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_solfigtr =
{
   draw_f2_pri,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_ssi =
{
  // this one is particular : only sprites !
  draw_ssi,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   pivot_gfxdecodeinfo
};
static struct VIDEO_INFO video_thundfox =
{
   draw_thundfox,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
   thundfox_decodeinfo
};
#define input_cameltry input_f2b1
GMEI( cameltry, "Camel Try", TAITO, 1989, GAME_PUZZLE,
	.romsw = romsw_cameltry,
	.long_name_jpn = "キャメルトライ",
	.board = "C38",
);
CLNEI(camltrua,cameltry, "Camel Try (Alternate)", TAITO, 1989, GAME_PUZZLE,
	.load_game = load_camltrua,
	.long_name_jpn = "キャメルトライ",
	.board = "C38",
	.sound = sound_camltrua,
);
static struct DIR_INFO dir_dinorex[] =
{
   { "dino_rex", },
   { "dinorex", },
   { NULL, },
};
GAME( dinorex, "Dino Rex", TAITO, 1992, GAME_BEAT,
	.input = input_f2b2,
	.dsw = dsw_dinorex,
	.romsw = romsw_dondokdj,
	.video = &video_solfigtr,
	.exec = execute_mjnquest,
	.long_name_jpn = "ダイノレックス",
	.board = "D39",
);
static struct DIR_INFO dir_dondokdj[] =
{
   { "don_doko_don", },
   { "dondokod", },
   { "dondokdj", },
   { NULL, },
};
GAME( dondokdj, "Don Doko Don", TAITO, 1989, GAME_PLATFORM,
	.input = input_f2b2,
	.dsw = dsw_dondokdj,
	.romsw = romsw_dondokdj,
	.video = &video_dondokdj,
	.exec = execute_dondokdj,
	.long_name_jpn = "ドンドコドン",
	.board = "B95",
);
static struct DIR_INFO dir_driftout[] =
{
   { "drift_out", },
   { "driftout", },
   { NULL, },
};
GAME( driftout, "Drift Out", VISCO, 1991, GAME_RACE,
	.input = input_f2b2,
	.dsw = dsw_driftout,
	.video = &video_driftout,
	.exec = execute_driftout,
	.long_name_jpn = "ドリフトアウト",
);
static struct DIR_INFO dir_driveout[] =
{
   { "drive_out", },
   { "driveout", },
   { ROMOF("driftout"), },
   { CLONEOF("driftout"), },
   { NULL, },
};
GAME(driveout, "Drive Out", BOOTLEG, 1991, GAME_RACE,
	.input = input_f2b2,
	.dsw = dsw_driftout,
	.video = &video_driftout,
	.exec = execute_driveout,
	.sound = sound_driveout,
);
static struct DIR_INFO dir_f2demo[] =
{
   { "f2demo", },
   { NULL, },
};
#define input_liquidk input_f2b2
CLNE( f2demo, liquidk, "Demo Taito F2", BOOTLEG, 2000, GAME_MISC,
	.input = input_f2b2,
	.romsw = romsw_f2demo,
	.exec = execute_f2demo,
	.board = "C49",
);
static struct DIR_INFO dir_finalb[] =
{
   { "final_blow", },
   { "finalb", },
   { "finalbl", },
   { NULL, },
};
#define input_finalb input_f2b3
GAME( finalb, "Final Blow", TAITO, 1988, GAME_BEAT,
	.dsw = dsw_finalb,
	.romsw = romsw_thundfox,
	.video = &video_finalb,
	.exec = execute_mjnquest,
	.long_name_jpn = "ファイナルブロー",
	.board = "B82",
);
static struct DIR_INFO dir_growl[] =
{
  { "growl" },
  { NULL }
};
GAME( growl, "Growl", TAITO, 1990, GAME_BEAT,
	.input = input_growl,
	.dsw = dsw_growl,
	.romsw = romsw_growl,
	.video = &video_solfigtr,
	.exec = execute_growl,
	.long_name_jpn = "ルナーク",
	.board = "C74",
);
static struct DIR_INFO dir_gunfront[] =
{
   { "gun_frontier", },
   { "gunfront", },
   { NULL, },
};
GAME( gunfront, "Gun Frontier", TAITO, 1990, GAME_SHOOT,
	.input = input_f2b2,
	.dsw = dsw_gunfront,
	.romsw = romsw_liquidk,
	.video = &video_gunfront,
	.exec = execute_gunfront,
	.long_name_jpn = "ガンフロンティア",
	.board = "C71",
);
static struct DIR_INFO dir_liquidk[] =
{
   { "liquid_kids", },
   { "liquidk", },
   { NULL, },
};
GAME( liquidk, "Liquid Kids", TAITO, 1990, GAME_PLATFORM,
	.input = input_f2b2,
	.dsw = dsw_liquidk,
	.romsw = romsw_liquidk,
	.video = &video_liquidk,
	.exec = execute_liquidk,
	.long_name_jpn = "ミズバクｵ蝟`険",
	.board = "C49",
);
static struct DIR_INFO dir_mjnquest[] =
{
   { "mahjong_quest", },
   { "mjnquest", },
   { NULL, },
};
GAME( mjnquest, "Mahjong Quest", TAITO, 1990, GAME_PUZZLE,
	.input = input_mjnquest,
	.dsw = dsw_mjnquest,
	.video = &video_mjnquest,
	.exec = execute_mjnquest,
	.board = "C77",
);
static struct DIR_INFO dir_majest12[] =
{
   { "majestic_twelve", },
   { "mj12", },
   { "majest12", },
   { ROMOF("ssi"), },
   { CLONEOF("ssi"), },
   { NULL, },
};
#define input_ssi input_f2b2
CLNE(majest12, ssi, "Majestic Twelve", TAITO, 1990, GAME_SHOOT,
	.long_name_jpn = "マジェスティックトウェルブ",
	.board = "C64",
);
static struct DIR_INFO dir_megab[] =
{
   { "mega_blast", },
   { "megab", },
   { "megabl", },
   { NULL, },
};
GAME( megab, "Mega Blast", TAITO, 1989, GAME_SHOOT,
	.input = input_megab,
	.dsw = dsw_megab,
	.romsw = romsw_f2demo,
	.video = &video_solfigtr,
	.exec = execute_megab,
	.long_name_jpn = "メガブラスト",
	.board = "C11",
);
static struct DIR_INFO dir_pulirula[] =
{
   { "pulirula", },
   { NULL, },
};
GAME( pulirula, "Pulirula", TAITO, 1991, GAME_BEAT,
	.input = input_f2b3,
	.dsw = dsw_pulirula,
	.romsw = romsw_liquidk,
	.video = &video_pulirula,
	.exec = execute_driftout,
	.long_name_jpn = "プリルラ",
	.board = "C98",
);
static struct DIR_INFO dir_solfigtr[] =
{
   { "solitary_fighter", },
   { "solfigtr", },
   { NULL, },
};
#define input_solfigtr input_f2b3
GME( solfigtr, "Solitary Fighter", TAITO, 1990, GAME_BEAT,
	.romsw = romsw_solfigtr,
	.long_name_jpn = "ダイノレックス",
	.board = "C91",
);
static struct DIR_INFO dir_ssi[] =
{
   { "super_space_invaders_91", },
   { "ssi", },
   { "space_invaders_91", },
   { NULL, },
};
GME( ssi, "Super Space Invaders 91", TAITO, 1990, GAME_SHOOT,
	.romsw = romsw_ssi,
	.long_name_jpn = "スーパースペースインベーダー’９１",
	.board = "C64",
);
static struct DIR_INFO dir_thundfox[] =
{
   { "thunder_fox", },
   { "thundfox", },
   { "thndfoxj", },
   { NULL, },
};
GAME( thundfox, "Thunder Fox", TAITO, 1990, GAME_SHOOT,
	.input = input_f2b3,
	.dsw = dsw_thundfox,
	.romsw = romsw_thundfox,
	.video = &video_thundfox,
	.exec = execute_liquidk,
	.long_name_jpn = "サンダーフォックス",
	.board = "C28",
);

