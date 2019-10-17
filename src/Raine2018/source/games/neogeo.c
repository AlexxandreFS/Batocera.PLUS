#define DRV_DEF_LOAD load_neocd
#define DRV_DEF_EXEC execute_neocd
#define DRV_DEF_VIDEO &neocd_video
#define DRV_DEF_SOUND sound_neocd
#define DRV_DEF_CLEAR clear_neocd
#define DRV_DEF_INPUT input_neogeo
#define DRV_DEF_DSW dsw_neogeo

#include "raine.h"
#include "games.h"
#include "68000/starhelp.h"
#include "cpumain.h"
#include "control.h"
#include "neocd/neocd.h"
#include "neogeo.h"
#include "emumain.h" // reset_game_hardware

extern struct SOUND_INFO sound_neocd[];

// Bios names are in neocd_options.c in sdl/dialogs, not really convenient
// but this is not updated often...
static struct ROM_INFO rom_bios[] = // struct used to select bios
{
  { "sp-s2.sp1", 0x020000, 0x9036d879, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp-s.sp1", 0x020000, 0xc7f2fa45, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp-u2.sp1", 0x020000, 0xe72943de, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp-e.sp1", 0x020000, 0x2723a5b5, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "asia-s3.rom", 0x020000, 0x91b64be3, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "vs-bios.rom", 0x020000, 0xf0e8f27d, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp-j2.sp1", 0x020000, 0xacede59c, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp1.jipan.1024", 0x020000, 0x9fb0abe4, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp-45.sp1", 0x080000, 0x03cc9f6a, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "japan-j3.bin", 0x020000, 0xdff6d41f, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sp-1v1_3db8c.bin", 0x020000, 0x162f0ebe, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_3_1.rom", 0x020000, 0x0c58093f, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_3_0.rom", 0x020000, 0xa97c89a9, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_2_3.rom", 0x020000, 0x27664eb5, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_2_2.rom", 0x020000, 0x2d50996a, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_2_1.rom", 0x020000, 0x8dabf76b, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_2_0.rom", 0x020000, 0x0c12c2ad, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_1_3.rom", 0x020000, 0xb24b44a0, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_1_2.rom", 0x020000, 0x4fa698e9, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_1_1.rom", 0x020000, 0x5dda0d84, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "uni-bios_1_0.rom", 0x020000, 0x0ce453a0, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "neodebug.rom", 0x020000, 0x698ebb7d, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "neo-epo.sp1", 0x020000, 0xd27a71f1, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "neo-po.sp1", 0x020000, 0x16d0c132, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "236-bios.sp1", 0x020000, 0x853e6b96, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

struct ROM_INFO rom_neogeo[] =
{
  { "sp-s2.sp1", 0x020000, 0x9036d879, REGION_MAINBIOS, 0x00000, LOAD_SWAP_16 },
  { "sm1.sm1", 0x20000, 0x94416d67, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "000-lo.lo", 0x20000, 0x5a86cff2, REGION_ZOOMY, 0x00000, LOAD_NORMAL },
  { "sfix.sfix", 0x20000, 0xc2ea0cfd, REGION_FIXEDBIOS, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

void set_neogeo_bios(int sel) {
    if (!strcmp(rom_neogeo[0].name,rom_bios[sel].name))
	return;
    rom_neogeo[0] = rom_bios[sel];
    if (current_game && !is_neocd() && current_game->load_game == &load_neocd){
	extern int loaded_roms; // from loadroms.c
	loaded_roms--;
	load_rom(rom_bios[sel].name,load_region[REGION_MAINBIOS],get_region_size(REGION_MAINBIOS));
    }
}

static struct DSW_DATA dsw_data_neogeo_0[] =
{
// _("SW:1")
  DSW_TEST_MODE( 0x0000, 0x0001 ),
// _("SW:2")
  { _("Coin Chutes?"), 0x0002, 2 },
  { "1?", 0x0000, 0x00 },
  { "2?", 0x0002, 0x00 },
// _("SW:3")
  { _("Autofire (in some games)"), 0x0004, 2 },
  { MSG_OFF, 0x0004, 0x00 },
  { MSG_ON, 0x0000, 0x00 },
// _("SW:4,5")
  { _("COMM Setting (Cabinet No.)"), 0x0018, 4 },
  { "1", 0x0018, 0x00 },
  { "2", 0x0010, 0x00 },
  { "3", 0x0008, 0x00 },
  { "4", 0x0000, 0x00 },
// _("SW:6")
  { _("COMM Setting (Link Enable)"), 0x0020, 2 },
  { MSG_OFF, 0x0020, 0x00 },
  { MSG_ON, 0x0000, 0x00 },
// _("SW:7")
  { MSG_FREE_PLAY, 0x0040, 2 },
  { MSG_OFF, 0x0040, 0x00 },
  { MSG_ON, 0x0000, 0x00 },
// _("SW:8")
  { _("Freeze"), 0x0080, 2 },
  { MSG_OFF, 0x0080, 0x00 },
  { MSG_ON, 0x0000, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_INFO dsw_neogeo[] =
{
  { 0x0, 0xff, dsw_data_neogeo_0 },
  { 0, 0, NULL }
};

/* Inputs : the start is exactly like neocd, then next game/prev game replaces
 * SELECT, and then input_buffer[6] is used for coins ! */
static struct INPUT_INFO input_neogeo[] = // 2 players, 4 buttons
{
    INP0( P1_UP, 1, 1 ),
    INP0( P1_DOWN, 1, 2 ),
    INP0( P1_LEFT, 1, 4 ),
    INP0( P1_RIGHT, 1, 8 ),
  { KB_DEF_P1_B1, "Player1 A", 0x01, 0x10, BIT_ACTIVE_0 },
  { KB_DEF_P1_B2, "Player1 B", 0x01, 0x20, BIT_ACTIVE_0 },
  { KB_DEF_P1_B3, "Player1 C", 0x01, 0x40, BIT_ACTIVE_0 },
  { KB_DEF_P1_B4, "Player1 D", 0x01, 0x80, BIT_ACTIVE_0 },
#ifndef RAINE_DOS
  { KB_DEF_P1_B1B2,"Player1 A+B", 1, 0x30, BIT_ACTIVE_0 },
  { KB_DEF_P1_B3B4,"Player1 C+D", 1, 0xc0, BIT_ACTIVE_0 },
  { KB_DEF_P1_B2B3,"Player1 B+C", 1, 0x60, BIT_ACTIVE_0 },
  { KB_DEF_P1_B1B2B3,"Player1 A+B+C", 1, 0x70, BIT_ACTIVE_0 },
  { KB_DEF_P1_B2B3B4,"Player1 B+C+D", 1, 0xe0, BIT_ACTIVE_0 },
#endif

  { KB_DEF_P2_UP, MSG_P2_UP, 0x03, 0x01, BIT_ACTIVE_0 },
  { KB_DEF_P2_DOWN, MSG_P2_DOWN, 0x03, 0x02, BIT_ACTIVE_0 },
  { KB_DEF_P2_LEFT, MSG_P2_LEFT, 0x03, 0x04, BIT_ACTIVE_0 },
  { KB_DEF_P2_RIGHT, MSG_P2_RIGHT, 0x03, 0x08, BIT_ACTIVE_0 },
  { KB_DEF_P2_B1, "Player2 A", 0x03, 0x10, BIT_ACTIVE_0 },
  { KB_DEF_P2_B2, "Player2 B", 0x03, 0x20, BIT_ACTIVE_0 },
  { KB_DEF_P2_B3, "Player2 C", 0x03, 0x40, BIT_ACTIVE_0 },
  { KB_DEF_P2_B4, "Player2 D", 0x03, 0x80, BIT_ACTIVE_0 },
#ifndef RAINE_DOS
  { KB_DEF_P2_B1B2,"Player2 A+B", 3, 0x30, BIT_ACTIVE_0 },
  { KB_DEF_P2_B3B4,"Player2 C+D", 3, 0xc0, BIT_ACTIVE_0 },
  { KB_DEF_P2_B2B3,"Player2 B+C", 3, 0x60, BIT_ACTIVE_0 },
  { KB_DEF_P2_B1B2B3,"Player2 A+B+C", 3, 0x70, BIT_ACTIVE_0 },
  { KB_DEF_P2_B2B3B4,"Player2 B+C+D", 3, 0xe0, BIT_ACTIVE_0 },
#endif

  INP0( P1_START, 5, 1 ),
  { KB_DEF_NEXT_GAME, "Select 1", 0x05, 0x02, BIT_ACTIVE_0 },
  INP0( P2_START, 5, 4 ),
  { KB_DEF_PREV_GAME, "Select 2", 0x05, 0x08, BIT_ACTIVE_0 },
  INP1( UNKNOWN, 5, 0x70), // memcard status
  INP0( UNKNOWN, 5, 0x80), // mvs/aes ?
  // Bit 4 (0x10) is 0 if the memory card is present !!!
  // neogeo doc :
  // bit 5 = mc 2 insertion status (0 = inserted)
  // bit 6 write protect 0 = write enable
  // bit 7 = neogeo mode : 0 = neogeo / 1 = mvs !!!

  INP0( COIN1, 6, 1 ),
  INP0( COIN2, 6, 2 ),
  INP0( SERVICE, 6, 4 ),
  /* having this ACTIVE_HIGH causes you to start with 2 credits using USA bios roms; if ACTIVE_HIGH + IN4 bit 6 ACTIVE_HIGH = AES 'mode' */
  INP0( UNKNOWN, 6, 8 ),
  INP0( UNKNOWN, 6, 0x10 ), // same as previous
  /* what is this? When ACTIVE_HIGH + IN4 bit 6 ACTIVE_LOW MVS-4 slot is detected */
  { KB_DEF_SPECIAL, MSG_UNKNOWN, 6, 0x20, BIT_ACTIVE_0 },
  { KB_DEF_SPECIAL, MSG_UNKNOWN, 6, 0xc0, BIT_ACTIVE_1 }, // calendar

  INP1( UNKNOWN, 8, 0x3f ),
  /* what is this? If ACTIVE_LOW, MVS-6 slot detected, when ACTIVE_HIGH MVS-1 slot (AES) detected */
  { KB_DEF_SPECIAL, MSG_UNKNOWN, 8, 0x40, BIT_ACTIVE_1 },
  INP0( TEST, 8, 0x80 ), // enter bios

  END_INPUT
};

static struct INPUT_INFO input_irrmaze[] = // trackball
{
    INCL_INP( neogeo ),
    INP0( UNKNOWN, 1, 0xff ), // trackball

    INP0( P1_UP, 2, 1 ),
    INP0( P1_DOWN, 2, 2 ),
    INP0( P1_LEFT, 2, 4 ),
    INP0( P1_RIGHT, 2, 8 ),
  { KB_DEF_P2_UP, MSG_P2_UP, 0x03, 0x01, BIT_ACTIVE_0 },
  { KB_DEF_P2_DOWN, MSG_P2_DOWN, 0x03, 0x02, BIT_ACTIVE_0 },
  { KB_DEF_P2_LEFT, MSG_P2_LEFT, 0x03, 0x04, BIT_ACTIVE_0 },
  { KB_DEF_P2_RIGHT, MSG_P2_RIGHT, 0x03, 0x08, BIT_ACTIVE_0 },
    INP0( UNKNOWN, 3, 0xf), // unused
  { KB_DEF_P1_B1, "Player1 A", 0x03, 0x10, BIT_ACTIVE_0 },
  { KB_DEF_P1_B2, "Player1 B", 0x03, 0x20, BIT_ACTIVE_0 },
  { KB_DEF_P2_B1, "Player2 A", 0x03, 0x40, BIT_ACTIVE_0 },
  { KB_DEF_P2_B2, "Player2 B", 0x03, 0x80, BIT_ACTIVE_0 },

  END_INPUT
};

static struct INPUT_INFO input_popbounc[] = // trackball
{
    INCL_INP( irrmaze ),

    INP0( P1_B1, 2, 0x90 ), // Actually bit7 is when control = paddle
    // and bit4 is normal button1 when control = joystick
    INP0( P1_B2, 2, 0x20 ), // I don't think b2 and b3 are used anyway... !
    INP0( P1_B3, 2, 0x40 ),
    INP0( UNUSED, 3, 0xff ), // trackball p2 / inputs

    INP0( P2_UP, 4, 1 ),
    INP0( P2_DOWN, 4, 2 ),
    INP0( P2_LEFT, 4, 4 ),
    INP0( P2_RIGHT, 4, 8 ),
    INP0( P2_B1, 4, 0x90 ),
    INP0( P2_B2, 4, 0x20 ),
    INP0( P2_B3, 4, 0x40 ),

    END_INPUT
};

GMEI( neogeo, "Neo-Geo bios", SNK, 1990, GAME_MISC);

int check_bios_presence(int sel) {
    return load_rom_dir(dir_neogeo,rom_bios[sel].name,NULL, rom_bios[sel].size,
		rom_bios[sel].crc32,0);
}

static struct ROM_INFO rom_nam1975[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "001-p1.p1", 0x080000, 0xcc9fc951, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "001-s1.s1", 0x20000, 0x7988ba51, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "001-m1.m1", 0x40000, 0xba874463, REGION_ROM2, 0x00000, LOAD_NORMAL },
	// AES has different label, data is the same: 001-v1.v1
  { "001-v11.v11", 0x080000, 0xa7c3d5e5, REGION_SMP1, 0x000000, LOAD_NORMAL },
	// AES has different label, data is the same: 001-v2.v21
  { "001-v21.v21", 0x080000, 0x55e670b3, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "001-v22.v22", 0x080000, 0xab0d8368, REGION_YMSND_DELTAT, 0x080000, LOAD_NORMAL },
  { "001-v23.v23", 0x080000, 0xdf468e28, REGION_YMSND_DELTAT, 0x100000, LOAD_NORMAL },
  { "001-c1.c1", 0x80000, 0x32ea98e1, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "001-c2.c2", 0x80000, 0xcbc4064c, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "001-c3.c3", 0x80000, 0x0151054c, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "001-c4.c4", 0x80000, 0x0a32570d, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { "001-c5.c5", 0x80000, 0x90b74cc2, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "001-c6.c6", 0x80000, 0xe62bed58, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( nam1975, neogeo, "NAM-1975 (NGM-001)(NGH-001)", SNK, 1990, GAME_SHOOT);

static struct ROM_INFO rom_bstars[] = /* MVS VERSION clone of neogeo */
{
  { "002-pg.p1", 0x080000, 0xc100b5f5, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "002-s1.s1", 0x20000, 0x1a7fd0c6, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "002-m1.m1", 0x40000, 0x4ecaa4ee, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "002-v11.v11", 0x080000, 0xb7b925bd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "002-v12.v12", 0x080000, 0x329f26fc, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "002-v13.v13", 0x080000, 0x0c39f3c8, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "002-v14.v14", 0x080000, 0xc7e11c38, REGION_SMP1, 0x180000, LOAD_NORMAL },
  { "002-v21.v21", 0x080000, 0x04a733d1, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "002-c1.c1", 0x080000, 0xaaff2a45, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "002-c2.c2", 0x080000, 0x3ba0f7e4, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "002-c3.c3", 0x080000, 0x96f0fdfa, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "002-c4.c4", 0x080000, 0x5fd87f2f, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { "002-c5.c5", 0x080000, 0x807ed83b, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "002-c6.c6", 0x080000, 0x5a3cad41, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI(bstars, neogeo, "Baseball Stars Professional (NGM-002)", SNK, 1990, GAME_SPORTS);

static struct ROM_INFO rom_bstarsh[] = /* AES VERSION clone of bstars */
{
  { "002-p1.p1", 0x080000, 0x3bc7790e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( bstarsh, bstars, "Baseball Stars Professional (NGH-002)", SNK, 1990, GAME_SPORTS);

static struct ROM_INFO rom_tpgolf[] = /* MVS AND AES VERSION */
{
  { "003-p1.p1", 0x080000, 0xf75549ba, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "003-p2.p2", 0x080000, 0xb7809a8f, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "003-s1.s1", 0x20000, 0x7b3eb9b1, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "003-m1.m1", 0x20000, 0x4cc545e6, REGION_ROM2, 0x00000, LOAD_NORMAL },
	// AES has different label, data is the same (also found on MVS): 003-v1.v11
  { "003-v11.v11", 0x080000, 0xff97f1cb, REGION_SMP1, 0x000000, LOAD_NORMAL },
	// AES has different label, data is the same (also found on MVS): 003-v2.v21
  { "003-v21.v21", 0x080000, 0xd34960c6, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "003-v22.v22", 0x080000, 0x9a5f58d4, REGION_YMSND_DELTAT, 0x080000, LOAD_NORMAL },
  { "003-v23.v23", 0x080000, 0x30f53e54, REGION_YMSND_DELTAT, 0x100000, LOAD_NORMAL },
  { "003-v24.v24", 0x080000, 0x5ba0f501, REGION_YMSND_DELTAT, 0x180000, LOAD_NORMAL },
  { "003-c1.c1", 0x80000, 0x0315fbaf, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "003-c2.c2", 0x80000, 0xb4c15d59, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "003-c3.c3", 0x80000, 0x8ce3e8da, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "003-c4.c4", 0x80000, 0x29725969, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { "003-c5.c5", 0x80000, 0x9a7146da, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "003-c6.c6", 0x80000, 0x1e63411a, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "003-c7.c7", 0x80000, 0x2886710c, REGION_SPRITES, 0x300000, LOAD_8_16 },
  { "003-c8.c8", 0x80000, 0x422af22d, REGION_SPRITES, 0x300001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( tpgolf, neogeo, "Top Player's Golf (NGM-003)(NGH-003)", SNK, 1990, GAME_SPORTS);

static struct ROM_INFO rom_maglord[] = /* MVS VERSION clone of neogeo */
{
  { "005-pg1.p1", 0x080000, 0xbd0a492d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "005-s1.s1", 0x20000, 0x1c5369a2, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "005-m1.m1", 0x40000, 0x26259f0f, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "005-v11.v11", 0x080000, 0xcc0455fd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "005-v21.v21", 0x080000, 0xf94ab5b7, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "005-v22.v22", 0x080000, 0x232cfd04, REGION_YMSND_DELTAT, 0x080000, LOAD_NORMAL },
  { "005-c1.c1", 0x80000, 0x806aee34, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "005-c2.c2", 0x80000, 0x34aa9a86, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "005-c3.c3", 0x80000, 0xc4c2b926, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "005-c4.c4", 0x80000, 0x9c46dcf4, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { "005-c5.c5", 0x80000, 0x69086dec, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "005-c6.c6", 0x80000, 0xab7ac142, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_maglordh[] = /* AES VERSION clone of maglord */
{
  { "005-p1.p1", 0x080000, 0x599043c5, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( maglord, neogeo, "Magician Lord (NGM-005)", ALPHA, 1990, GAME_PLATFORM);

CLNEI( maglordh, maglord, "Magician Lord (NGH-005)", ALPHA, 1990, GAME_PLATFORM);

static struct ROM_INFO rom_ridhero[] = /* MVS AND AES VERSION */
{
  { "006-p1.p1", 0x080000, 0xd4aaf597, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "006-s1.s1", 0x20000, 0xeb5189f0, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "006-m1.m1", 0x40000, 0x92e7b4fe, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "006-v11.v11", 0x080000, 0xcdf74a42, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "006-v12.v12", 0x080000, 0xe2fd2371, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "006-v21.v21", 0x080000, 0x94092bce, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "006-v22.v22", 0x080000, 0x4e2cd7c3, REGION_YMSND_DELTAT, 0x080000, LOAD_NORMAL },
  { "006-v23.v23", 0x080000, 0x069c71ed, REGION_YMSND_DELTAT, 0x100000, LOAD_NORMAL },
  { "006-v24.v24", 0x080000, 0x89fbb825, REGION_YMSND_DELTAT, 0x180000, LOAD_NORMAL },
  { "006-c1.c1", 0x080000, 0x4a5c7f78, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "006-c2.c2", 0x080000, 0xe0b70ece, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "006-c3.c3", 0x080000, 0x8acff765, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "006-c4.c4", 0x080000, 0x205e3208, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ridheroh[] = // clone of ridhero
{
	/* Chip label p1h does not exist, renamed temporarly to pg1, marked BAD_DUMP. This needs to be verified. */
  { "006-pg1.p1", 0x080000, 0x52445646, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ridhero, neogeo, "Riding Hero (NGM-006)(NGH-006)", SNK, 1990, GAME_RACE);
CLNEI( ridheroh, ridhero, "Riding Hero (set 2)", SNK, 1990, GAME_RACE);

static struct ROM_INFO rom_alpham2[] = /* MVS AND AES VERSION */
{
  { "007-p1.p1", 0x080000, 0x5b266f47, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "007-p2.p2", 0x020000, 0xeb9c1044, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "007-s1.s1", 0x20000, 0x85ec9acf, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "007-m1.m1", 0x20000, 0x28dfe2cd, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "007-v1.v1", 0x100000, 0xcd5db931, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "007-v2.v2", 0x100000, 0x63e9b574, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "007-c1.c1", 0x100000, 0x8fba8ff3, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "007-c2.c2", 0x100000, 0x4dad2945, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "007-c3.c3", 0x080000, 0x68c2994e, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "007-c4.c4", 0x080000, 0x7d588349, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_alpham2p[] = /* early prototype - all roms were hand labeled with CRCs, dumps verified against them clone of alpham2 */
{
  { "proto_007-p1.p1", 0x080000, 0xc763e52a, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "proto_007-p2.p2", 0x080000, 0x7a0b435c, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "proto_007-s1.s1", 0x20000, 0xefc9ae2e, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "proto_007-m1.m1", 0x20000, 0x5976b464, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "proto_007-v11.v11", 0x080000, 0x18eaa9e1, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "proto_007-v12.v12", 0x080000, 0x2487d495, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "proto_007-v13.v13", 0x080000, 0x25e60f25, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "proto_007-v21.v21", 0x080000, 0xac44b75a, REGION_SMP1, 0x180000, LOAD_NORMAL },
/* Ignored : 	ROM_COPY( "ymsnd", 0x180000, 0x00000, 0x80000 ) */
  { "proto_007-c1.c1", 0x80000, 0x24841639, REGION_SPRITES, 0x000000, LOAD_8_32 },
  { "proto_007-c2.c2", 0x80000, 0x912763ab, REGION_SPRITES, 0x000002, LOAD_8_32 },
  { "proto_007-c3.c3", 0x80000, 0x0743bde2, REGION_SPRITES, 0x000001, LOAD_8_32 },
  { "proto_007-c4.c4", 0x80000, 0x61240212, REGION_SPRITES, 0x000003, LOAD_8_32 },
  { "proto_007-c5.c5", 0x80000, 0xcf9f4c53, REGION_SPRITES, 0x200000, LOAD_8_32 },
  { "proto_007-c6.c6", 0x80000, 0x3d903b19, REGION_SPRITES, 0x200002, LOAD_8_32 },
  { "proto_007-c7.c7", 0x80000, 0xe41e3875, REGION_SPRITES, 0x200001, LOAD_8_32 },
  { "proto_007-c8.c8", 0x80000, 0x4483e2cf, REGION_SPRITES, 0x200003, LOAD_8_32 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( alpham2, neogeo, "Alpha Mission II / ASO II - Last Guardian (NGM-007)(NGH-007)", SNK, 1991, GAME_SHOOT);
CLNEI( alpham2p, alpham2, "Alpha Mission II / ASO II - Last Guardian (prototype)", SNK, 1991, GAME_SHOOT);

static struct ROM_INFO rom_ncombat[] = /* MVS VERSION clone of neogeo */
{
  { "009-p1.p1", 0x080000, 0xb45fcfbf, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "009-s1.s1", 0x20000, 0xd49afee8, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "009-m1.m1", 0x20000, 0xb5819863, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "009-v11.v11", 0x080000, 0xcf32a59c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "009-v12.v12", 0x080000, 0x7b3588b7, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "009-v13.v13", 0x080000, 0x505a01b5, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "009-v21.v21", 0x080000, 0x365f9011, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "009-c1.c1", 0x80000, 0x33cc838e, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "009-c2.c2", 0x80000, 0x26877feb, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "009-c3.c3", 0x80000, 0x3b60a05d, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "009-c4.c4", 0x80000, 0x39c2d039, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { "009-c5.c5", 0x80000, 0x67a4344e, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "009-c6.c6", 0x80000, 0x2eca8b19, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ncombat, neogeo, "Ninja Combat (NGM-009)", ALPHA, 1990, GAME_BEAT);

static struct ROM_INFO rom_ncombath[] = /* AES VERSION clone of ncombat */
{
  { "009-pg1.p1", 0x080000, 0x8e9f0add, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ncombath, ncombat, "Ninja Combat (NGH-009)", ALPHA, 1990, GAME_BEAT);

static struct ROM_INFO rom_cyberlip[] = // clone of neogeo
{
  { "010-p1.p1", 0x080000, 0x69a6b42d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "010-s1.s1", 0x20000, 0x79a35264, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "010-m1.m1", 0x20000, 0x8be3a078, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "010-v11.v11", 0x080000, 0x90224d22, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "010-v12.v12", 0x080000, 0xa0cf1834, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "010-v13.v13", 0x080000, 0xae38bc84, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "010-v14.v14", 0x080000, 0x70899bd2, REGION_SMP1, 0x180000, LOAD_NORMAL },
  { "010-v21.v21", 0x080000, 0x586f4cb2, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "010-c1.c1", 0x80000, 0x8bba5113, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "010-c2.c2", 0x80000, 0xcbf66432, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "010-c3.c3", 0x80000, 0xe4f86efc, REGION_SPRITES, 0x100000, LOAD_8_16 },
  { "010-c4.c4", 0x80000, 0xf7be4674, REGION_SPRITES, 0x100001, LOAD_8_16 },
  { "010-c5.c5", 0x80000, 0xe8076da0, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "010-c6.c6", 0x80000, 0xc495c567, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( cyberlip, neogeo, "Cyber-Lip (NGM-010)", SNK, 1990, GAME_PLATFORM);

static struct ROM_INFO rom_superspy[] = /* MVS AND AES VERSION */
{
  { "011-p1.p1", 0x080000, 0xc7f944b5, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "sp2.p2", 0x020000, 0x811a4faf, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "011-s1.s1", 0x20000, 0xec5fdb96, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "011-m1.m1", 0x40000, 0xca661f1b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "011-v11.v11", 0x100000, 0x5c674d5c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "011-v12.v12", 0x080000, 0x9f513d5a, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "011-v21.v21", 0x080000, 0x426cd040, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "011-c1.c1", 0x100000, 0xcae7be57, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "011-c2.c2", 0x100000, 0x9e29d986, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "011-c3.c3", 0x100000, 0x14832ff2, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "011-c4.c4", 0x100000, 0xb7f63162, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( superspy, neogeo, "The Super Spy (NGM-011)(NGH-011)", SNK, 1990, GAME_FIGHT);

static struct ROM_INFO rom_mutnat[] = /* MVS AND AES VERSION */
{
  { "014-p1.p1", 0x080000, 0x6f1699c8, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "014-s1.s1", 0x20000, 0x99419733, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "014-m1.m1", 0x20000, 0xb6683092, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "014-v1.v1", 0x100000, 0x25419296, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "014-v2.v2", 0x100000, 0x0de53d5e, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "014-c1.c1", 0x100000, 0x5e4381bf, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "014-c2.c2", 0x100000, 0x69ba4e18, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "014-c3.c3", 0x100000, 0x890327d5, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "014-c4.c4", 0x100000, 0xe4002651, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mutnat, neogeo, "Mutation Nation (NGM-014)(NGH-014)", SNK, 1992, GAME_BEAT);

static struct ROM_INFO rom_kotm[] = /* MVS VERSION */
{
  { "016-p1.p1", 0x080000, 0x1b818731, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "016-p2.p2", 0x020000, 0x12afdc2b, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "016-s1.s1", 0x20000, 0x1a2eeeb3, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "016-m1.m1", 0x20000, 0x9da9ca10, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "016-v1.v1", 0x100000, 0x86c0a502, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "016-v2.v2", 0x100000, 0x5bc23ec5, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "016-c1.c1", 0x100000, 0x71471c25, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "016-c2.c2", 0x100000, 0x320db048, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "016-c3.c3", 0x100000, 0x98de7995, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "016-c4.c4", 0x100000, 0x070506e2, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_kotmh[] = /* AES VERSION clone of kotm */
{
  { "016-hp1.p1", 0x080000, 0xb774621e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "016-p2.p2", 0x020000, 0x12afdc2b, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kotm, neogeo, "King of the Monsters (set 1)", SNK, 1991, GAME_BEAT);
CLNEI( kotmh, kotm, "King of the Monsters (set 2)", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_sengoku[] = /* MVS AND AES VERSION */
{
  { "017-p1.p1", 0x080000, 0xf8a63983, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "017-p2.p2", 0x020000, 0x3024bbb3, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "017-s1.s1", 0x20000, 0xb246204d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "017-m1.m1", 0x20000, 0x9b4f34c6, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "017-v1.v1", 0x100000, 0x23663295, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "017-v2.v2", 0x100000, 0xf61e6765, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "017-c1.c1", 0x100000, 0xb4eb82a1, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "017-c2.c2", 0x100000, 0xd55c550d, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "017-c3.c3", 0x100000, 0xed51ef65, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "017-c4.c4", 0x100000, 0xf4f3c9cb, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sengokuh[] = /* AES VERSION (US) clone of sengoku */
{
  { "017-hp1.p1", 0x080000, 0x33eccae0, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "017-p2.p2", 0x020000, 0x3024bbb3, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( sengoku, neogeo, "Sengoku / Sengoku Denshou (NGM-017)(NGH-017)", SNK, 1991, GAME_BEAT);
CLNEI( sengokuh, sengoku, "Sengoku / Sengoku Denshou (NGH-017)(US)", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_burningf[] = /* MVS AND AES VERSION */
{
  { "018-p1.p1", 0x080000, 0x4092c8db, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "018-s1.s1", 0x20000, 0x6799ea0d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "018-m1.m1", 0x20000, 0x0c939ee2, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "018-v1.v1", 0x100000, 0x508c9ffc, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "018-v2.v2", 0x100000, 0x854ef277, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "018-c1.c1", 0x100000, 0x25a25e9b, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "018-c2.c2", 0x100000, 0xd4378876, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "018-c3.c3", 0x100000, 0x862b60da, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "018-c4.c4", 0x100000, 0xe2e0aff7, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_burningfh[] = /* AES VERSION (US) clone of burningf */
{
  { "018-hp1.p1", 0x080000, 0xddffcbf4, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( burningf, neogeo, "Burning Fight (NGM-018)(NGH-018)", SNK, 1991, GAME_BEAT);
CLNEI( burningfh, burningf, "Burning Fight (NGH-018)(US)", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_lbowling[] = /* MVS AND AES VERSION */
{
  { "019-p1.p1", 0x080000, 0xa2de8445, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "019-s1.s1", 0x20000, 0x5fcdc0ed, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "019-m1.m1", 0x20000, 0xd568c17d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "019-v11.v11", 0x080000, 0x0fb74872, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "019-v12.v12", 0x080000, 0x029faa57, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "019-v21.v21", 0x080000, 0x2efd5ada, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "019-c1.c1", 0x080000, 0x4ccdef18, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "019-c2.c2", 0x080000, 0xd4dd0802, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( lbowling, neogeo, "League Bowling (NGM-019)(NGH-019)", SNK, 1990, GAME_SPORTS);

static struct ROM_INFO rom_gpilots[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "020-p1.p1", 0x080000, 0xe6f2fe64, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "020-p2.p2", 0x020000, 0xedcb22ac, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "020-s1.s1", 0x20000, 0xa6d83d53, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "020-m1.m1", 0x20000, 0x48409377, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "020-v11.v11", 0x100000, 0x1b526c8b, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "020-v12.v12", 0x080000, 0x4a9e6f03, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "020-v21.v21", 0x080000, 0x7abf113d, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "020-c1.c1", 0x100000, 0xbd6fe78e, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "020-c2.c2", 0x100000, 0x5f4a925c, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "020-c3.c3", 0x100000, 0xd1e42fd0, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "020-c4.c4", 0x100000, 0xedde439b, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gpilotsh[] = /* AES VERSION (US) clone of gpilots */
{
  { "020-hp1.p1", 0x080000, 0x7cdb01ce, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "020-p2.p2", 0x020000, 0xedcb22ac, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( gpilots, neogeo, "Ghost Pilots (NGM-020)(NGH-020)", SNK, 1991, GAME_SHOOT);
CLNEI( gpilotsh, gpilots, "Ghost Pilots (NGH-020)(US)", SNK, 1991, GAME_SHOOT);

static struct ROM_INFO rom_joyjoy[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "021-p1.p1", 0x080000, 0x39c3478f, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "021-s1.s1", 0x20000, 0x6956d778, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "021-m1.m1", 0x40000, 0x5a4be5e8, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "021-v11.v11", 0x080000, 0x66c1e5c4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "021-v21.v21", 0x080000, 0x8ed20a86, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "021-c1.c1", 0x080000, 0x509250ec, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "021-c2.c2", 0x080000, 0x09ed5258, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( joyjoy, neogeo, "Puzzled / Joy Joy Kid (NGM-021)(NGH-021)", SNK, 1990, GAME_PUZZLE);

static struct ROM_INFO rom_bjourney[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "022-p1.p1", 0x100000, 0x6a2f6d4a, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "022-s1.s1", 0x20000, 0x843c3624, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "022-m1.m1", 0x20000, 0x8e1d4ab6, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "022-v11.v11", 0x100000, 0x2cb4ad91, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "022-v22.v22", 0x100000, 0x65a54d13, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "022-c1.c1", 0x100000, 0x4d47a48c, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "022-c2.c2", 0x100000, 0xe8c1491a, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "022-c3.c3", 0x080000, 0x66e69753, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "022-c4.c4", 0x080000, 0x71bfd48a, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( bjourney, neogeo, "Blue's Journey / Raguy (ALM-001)(ALH-001)", ALPHA, 1990, GAME_PLATFORM);

static struct ROM_INFO rom_lresort[] = // clone of neogeo
{
  { "024-p1.p1", 0x080000, 0x89c4ab97, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "024-s1.s1", 0x20000, 0x5cef5cc6, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "024-m1.m1", 0x20000, 0xcec19742, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "024-v1.v1", 0x100000, 0xefdfa063, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "024-v2.v2", 0x100000, 0x3c7997c0, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "024-c1.c1", 0x100000, 0x3617c2dc, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "024-c2.c2", 0x100000, 0x3f0a7fd8, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "024-c3.c3", 0x080000, 0xe9f745f8, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "024-c4.c4", 0x080000, 0x7382fefb, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( lresort, neogeo, "Last Resort", SNK, 1992, GAME_SHOOT);

static struct ROM_INFO rom_eightman[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "025-p1.p1", 0x080000, 0x43344cb0, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "025-s1.s1", 0x20000, 0xa402202b, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "025-m1.m1", 0x20000, 0x9927034c, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "025-v1.v1", 0x100000, 0x4558558a, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "025-v2.v2", 0x100000, 0xc5e052e9, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "025-c1.c1", 0x100000, 0x555e16a4, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "025-c2.c2", 0x100000, 0xe1ee51c3, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "025-c3.c3", 0x080000, 0x0923d5b0, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "025-c4.c4", 0x080000, 0xe3eca67b, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( eightman, neogeo, "Eight Man (NGM-025)(NGH-025)", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_legendos[] = // clone of neogeo
{
  { "029-p1.p1", 0x080000, 0x9d563f19, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "029-s1.s1", 0x20000, 0xbcd502f0, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "029-m1.m1", 0x20000, 0x6f2843f0, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "029-v1.v1", 0x100000, 0x85065452, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "029-c1.c1", 0x100000, 0x2f5ab875, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "029-c2.c2", 0x100000, 0x318b2711, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "029-c3.c3", 0x100000, 0x6bc52cb2, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "029-c4.c4", 0x100000, 0x37ef298c, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( legendos, neogeo, "Legend of Success Joe / Ashita no Joe Densetsu", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_2020bb[] = // clone of neogeo
{
  { "030-p1.p1", 0x080000, 0xd396c9cb, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "030-s1.s1", 0x20000, 0x7015b8fc, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "030-m1.m1", 0x20000, 0x4cf466ec, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "030-v1.v1", 0x100000, 0xd4ca364e, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "030-v2.v2", 0x100000, 0x54994455, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "030-c1.c1", 0x100000, 0x4f5e19bd, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "030-c2.c2", 0x100000, 0xd6314bf0, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "030-c3.c3", 0x100000, 0x47fddfee, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "030-c4.c4", 0x100000, 0x780d1c4e, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( 2020bb, neogeo, "2020 Super Baseball (set 1)", SNK, 1991, GAME_SPORTS);

static struct ROM_INFO rom_socbrawl[] = /* MVS VERSION clone of neogeo */
{
  { "031-pg1.p1", 0x080000, 0x17f034a7, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "031-s1.s1", 0x20000, 0x4c117174, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "031-m1.m1", 0x20000, 0xcb37427c, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "031-v1.v1", 0x100000, 0xcc78497e, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "031-v2.v2", 0x100000, 0xdda043c6, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "031-c1.c1", 0x100000, 0xbd0a4eb8, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "031-c2.c2", 0x100000, 0xefde5382, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "031-c3.c3", 0x080000, 0x580f7f33, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "031-c4.c4", 0x080000, 0xed297de8, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( socbrawl, neogeo, "Soccer Brawl (NGM-031)", SNK, 1991, GAME_SPORTS);

static struct ROM_INFO rom_socbrawlh[] = /* AES VERSION clone of socbrawl */
{
  { "031-p1.p1", 0x080000, 0xa2801c24, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( socbrawlh, socbrawl, "Soccer Brawl (NGH-031)", SNK, 1991, GAME_SPORTS);

static struct ROM_INFO rom_fatfury1[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "033-p1.p1", 0x080000, 0x47ebdc2f, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "033-p2.p2", 0x020000, 0xc473af1c, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "033-s1.s1", 0x20000, 0x3c3bdf8c, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "033-m1.m1", 0x20000, 0x5be10ffd, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "033-v1.v1", 0x100000, 0x212fd20d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "033-v2.v2", 0x100000, 0xfa2ae47f, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "033-c1.c1", 0x100000, 0x74317e54, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "033-c2.c2", 0x100000, 0x5bb952f3, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "033-c3.c3", 0x100000, 0x9b714a7c, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "033-c4.c4", 0x100000, 0x9397476a, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fatfury1, neogeo, "Fatal Fury - King of Fighters / Garou Densetsu - shukumei no tatakai (NGM-033)(NGH-033)", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_roboarmy[] = // clone of neogeo
{
  { "032-p1.p1", 0x080000, 0xcd11cbd4, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "032-s1.s1", 0x20000, 0xac0daa1b, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "032-m1.m1", 0x20000, 0x35ec952d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "032-v1.v1", 0x100000, 0x63791533, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "032-v2.v2", 0x100000, 0xeb95de70, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "032-c1.c1", 0x100000, 0x97984c6c, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "032-c2.c2", 0x100000, 0x65773122, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "032-c3.c3", 0x080000, 0x40adfccd, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "032-c4.c4", 0x080000, 0x462571de, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( roboarmy, neogeo, "Robo Army", SNK, 1991, GAME_BEAT);

static struct ROM_INFO rom_fbfrenzy[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "034-p1.p1", 0x080000, 0xcdef6b19, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "034-s1.s1", 0x20000, 0x8472ed44, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "034-m1.m1", 0x20000, 0xf41b16b8, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "034-v1.v1", 0x100000, 0x50c9d0dd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "034-v2.v2", 0x100000, 0x5aa15686, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "034-c1.c1", 0x100000, 0x91c56e78, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "034-c2.c2", 0x100000, 0x9743ea2f, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "034-c3.c3", 0x080000, 0xe5aa65f5, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "034-c4.c4", 0x080000, 0x0eb138cc, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fbfrenzy, neogeo, "Football Frenzy (NGM-034)(NGH-034)", SNK, 1992, GAME_SPORTS);

static struct ROM_INFO rom_crsword[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "037-p1.p1", 0x080000, 0xe7f2553c, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "037-s1.s1", 0x20000, 0x74651f27, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "037-m1.m1", 0x20000, 0x9504b2c6, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "037-v1.v1", 0x100000, 0x61fedf65, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "037-c1.c1", 0x100000, 0x09df6892, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "037-c2.c2", 0x100000, 0xac122a78, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "037-c3.c3", 0x100000, 0x9d7ed1ca, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "037-c4.c4", 0x100000, 0x4a24395d, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( crsword, neogeo, "Crossed Swords (ALM-002)(ALH-002)", ALPHA, 1991, GAME_FIGHT);

static struct ROM_INFO rom_trally[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "038-p1.p1", 0x080000, 0x1e52a576, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "038-p2.p2", 0x080000, 0xa5193e2f, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "038-s1.s1", 0x20000, 0xfff62ae3, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "038-m1.m1", 0x20000, 0x0908707e, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "038-v1.v1", 0x100000, 0x5ccd9fd5, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "038-v2.v2", 0x080000, 0xddd8d1e6, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "038-c1.c1", 0x100000, 0xc58323d4, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "038-c2.c2", 0x100000, 0xbba9c29e, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "038-c3.c3", 0x080000, 0x3bb7b9d6, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "038-c4.c4", 0x080000, 0xa4513ecf, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( trally, neogeo, "Thrash Rally (ALM-003)(ALH-003)", ALPHA, 1991, GAME_MISC);

static struct ROM_INFO rom_kotm2[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "039-p1.p1", 0x080000, 0xb372d54c, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "039-p2.p2", 0x080000, 0x28661afe, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "039-s1.s1", 0x20000, 0x63ee053a, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "039-m1.m1", 0x20000, 0x0c5b2ad5, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "039-v2.v2", 0x200000, 0x86d34b25, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "039-v4.v4", 0x100000, 0x8fa62a0b, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "039-c1.c1", 0x100000, 0x6d1c4aa9, REGION_SPRITES, 0, LOAD_8_16 },
  { "039-c1.c1", 0x100000, 0x6d1c4aa9, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "039-c2.c2", 0x100000, 0xf7b75337, REGION_SPRITES, 1, LOAD_8_16 },
  { "039-c2.c2", 0x100000, 0xf7b75337, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { "039-c3.c3", 0x080000, 0xbfc4f0b2, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "039-c4.c4", 0x080000, 0x81c9c250, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kotm2, neogeo, "King of the Monsters 2 - The Next Thing (NGM-039)(NGH-039)", SNK, 1992, GAME_BEAT);

static struct ROM_INFO rom_sengoku2[] = // clone of neogeo
{
  { "040-p1.p1", 0x100000, 0x6dde02c2, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "040-s1.s1", 0x20000, 0xcd9802a3, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "040-m1.m1", 0x20000, 0xd4de4bca, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "040-v1.v1", 0x200000, 0x71cb4b5d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "040-v2.v2", 0x100000, 0xc5cece01, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "040-c1.c1", 0x100000, 0xfaa8ea99, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "040-c1.c1", 0x100000 , 0xfaa8ea99, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "040-c2.c2", 0x100000, 0x87d0ec65, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "040-c2.c2", 0x100000 , 0x87d0ec65, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { "040-c3.c3", 0x080000, 0x24b5ba80, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "040-c4.c4", 0x080000, 0x1c9e9930, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( sengoku2, neogeo, "Sengoku 2 / Sengoku Denshou 2", SNK, 1993, GAME_BEAT);

static struct ROM_INFO rom_bstars2[] = // clone of neogeo
{
  { "041-p1.p1", 0x080000, 0x523567fd, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "041-s1.s1", 0x20000, 0x015c5c94, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "041-m1.m1", 0x20000, 0x15c177a6, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "041-v1.v1", 0x100000, 0xcb1da093, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "041-v2.v2", 0x100000, 0x1c954a9d, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "041-v3.v3", 0x080000, 0xafaa0180, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "041-c1.c1", 0x100000, 0xb39a12e1, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "041-c2.c2", 0x100000, 0x766cfc2f, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "041-c3.c3", 0x100000, 0xfb31339d, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "041-c4.c4", 0x100000, 0x70457a0c, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( bstars2, neogeo, "Baseball Stars 2", SNK, 1992, GAME_SPORTS);

static struct ROM_INFO rom_3countb[] = // clone of neogeo
{
	/* The original p1 is 8mbit; also found sets with p1 / p2 4mbit on eprom. */
  { "043-p1.p1", 0x100000, 0xffbdd928, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "043-s1.s1", 0x20000, 0xc362d484, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "043-m1.m1", 0x20000, 0x7eab59cb, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "043-v1.v1", 0x200000, 0x63688ce8, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "043-v2.v2", 0x200000, 0xc69a827b, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "043-c1.c1", 0x100000, 0xbad2d67f, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "043-c1.c1", 0x100000 , 0xbad2d67f, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "043-c2.c2", 0x100000, 0xa7fbda95, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "043-c2.c2", 0x100000 , 0xa7fbda95, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { "043-c3.c3", 0x100000, 0xf00be011, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "043-c3.c3", 0x100000 , 0xf00be011, REGION_SPRITES, 0x600000, LOAD_CONTINUE },
  { "043-c4.c4", 0x100000, 0x1887e5c0, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "043-c4.c4", 0x100000 , 0x1887e5c0, REGION_SPRITES, 0x600001, LOAD_CONTINUE },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( 3countb, neogeo, "3 Count Bout / Fire Suplex (NGM-043)(NGH-043)", SNK, 1993, GAME_FIGHT);

static struct ROM_INFO rom_aof[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "044-p1.p1", 0x080000, 0xca9f7a6d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "044-s1.s1", 0x20000, 0x89903f39, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "044-m1.m1", 0x20000, 0x0987e4bb, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "044-v2.v2", 0x200000, 0x3ec632ea, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "044-v4.v4", 0x200000, 0x4b0f8e23, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "044-c1.c1", 0x100000, 0xddab98a7, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "044-c1.c1", 0x100000 , 0xddab98a7, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "044-c2.c2", 0x100000, 0xd8ccd575, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "044-c2.c2", 0x100000 , 0xd8ccd575, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { "044-c3.c3", 0x100000, 0x403e898a, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "044-c3.c3", 0x100000 , 0x403e898a, REGION_SPRITES, 0x600000, LOAD_CONTINUE },
  { "044-c4.c4", 0x100000, 0x6235fbaa, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "044-c4.c4", 0x100000 , 0x6235fbaa, REGION_SPRITES, 0x600001, LOAD_CONTINUE },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( aof, neogeo, "Art of Fighting / Ryuuko no Ken (NGM-044)(NGH-044)", SNK, 1992, GAME_BEAT);

static struct ROM_INFO rom_samsho[] = /* MVS VERSION clone of neogeo */
{
  { "045-p1.p1", 0x100000, 0xdfe51bf0, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "045-pg2.sp2", 0x100000, 0x46745b94, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "045-s1.s1", 0x20000, 0x9142a4d3, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "045-m1.m1", 0x20000, 0x95170640, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "045-v1.v1", 0x200000, 0x37f78a9b, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "045-v2.v2", 0x200000, 0x568b20cf, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "045-c1.c1", 0x200000, 0x2e5873a4, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "045-c2.c2", 0x200000, 0x04febb10, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "045-c3.c3", 0x200000, 0xf3dabd1e, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "045-c4.c4", 0x200000, 0x935c62f0, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "045-c51.c5", 0x100000, 0x81932894, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "045-c61.c6", 0x100000, 0xbe30612e, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho, neogeo, "Samurai Shodown / Samurai Spirits (NGM-045)", SNK, 1993, GAME_BEAT);

static struct ROM_INFO rom_samshoh[] = /* AES VERSION clone of samsho */
{
  { "045-p1.p1", 0x100000, 0xdfe51bf0, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "045-p2.sp2", 0x080000, 0x38ee9ba9, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "045-c1.c1", 0x200000, 0x2e5873a4, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "045-c2.c2", 0x200000, 0x04febb10, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "045-c3.c3", 0x200000, 0xf3dabd1e, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "045-c4.c4", 0x200000, 0x935c62f0, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "045-c5.c5", 0x080000, 0xa2bb8284, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "045-c6.c6", 0x080000, 0x4fa71252, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samshoh, samsho, "Samurai Shodown / Samurai Spirits (NGH-045)", SNK, 1993, GAME_BEAT);

static struct ROM_INFO rom_tophuntr[] = /* MVS VERSION clone of neogeo */
{
  { "046-p1.p1", 0x100000, 0x69fa9e29, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "046-p2.sp2", 0x100000, 0xf182cb3e, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "046-s1.s1", 0x20000, 0x14b01d7b, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "046-m1.m1", 0x20000, 0x3f84bb9f, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "046-v1.v1", 0x100000, 0xc1f9c2db, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "046-v2.v2", 0x100000, 0x56254a64, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "046-v3.v3", 0x100000, 0x58113fb1, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "046-v4.v4", 0x100000, 0x4f54c187, REGION_SMP1, 0x300000, LOAD_NORMAL },
  { "046-c1.c1", 0x100000, 0xfa720a4a, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "046-c2.c2", 0x100000, 0xc900c205, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "046-c3.c3", 0x100000, 0x880e3c25, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "046-c4.c4", 0x100000, 0x7a2248aa, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "046-c5.c5", 0x100000, 0x4b735e45, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "046-c6.c6", 0x100000, 0x273171df, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "046-c7.c7", 0x100000, 0x12829c4c, REGION_SPRITES, 0x600000, LOAD_8_16 },
  { "046-c8.c8", 0x100000, 0xc944e03d, REGION_SPRITES, 0x600001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( tophuntr, neogeo, "Top Hunter - Roddy & Cathy (NGM-046)", SNK, 1994, GAME_PLATFORM);

static struct ROM_INFO rom_fatfury2[] = /* MVS AND AES VERSION clone of neogeo */
{
	/* The original p1 is 8mbit; also found sets with p1 / p2 4mbit on eprom. */
  { "047-p1.p1", 0x100000, 0xecfdbb69, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "047-s1.s1", 0x20000, 0xd7dbbf39, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "047-m1.m1", 0x20000, 0x820b0ba7, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "047-v1.v1", 0x200000, 0xd9d00784, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "047-v2.v2", 0x200000, 0x2c9a4b33, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "047-c1.c1", 0x100000, 0xf72a939e, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "047-c1.c1", 0x100000 , 0xf72a939e, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "047-c2.c2", 0x100000, 0x05119a0d, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "047-c2.c2", 0x100000 , 0x05119a0d, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { "047-c3.c3", 0x100000, 0x01e00738, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "047-c3.c3", 0x100000 , 0x01e00738, REGION_SPRITES, 0x600000, LOAD_CONTINUE },
  { "047-c4.c4", 0x100000, 0x9fe27432, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "047-c4.c4", 0x100000 , 0x9fe27432, REGION_SPRITES, 0x600001, LOAD_CONTINUE },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fatfury2, neogeo, "Fatal Fury 2 / Garou Densetsu 2 - arata-naru tatakai (NGM-047)(NGH-047)", SNK, 1992, GAME_BEAT);

static struct ROM_INFO rom_androdun[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "049-p1.p1", 0x080000, 0x3b857da2, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "049-p2.p2", 0x080000, 0x2f062209, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "049-s1.s1", 0x20000, 0x6349de5d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "049-m1.m1", 0x20000, 0xedd2acf4, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "049-v1.v1", 0x100000, 0xce43cb89, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "049-c1.c1", 0x100000, 0x7ace6db3, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "049-c2.c2", 0x100000, 0xb17024f7, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( androdun, neogeo, "Andro Dunos (NGM-049)(NGH-049)", VISCO, 1992, GAME_SHOOT);

static struct ROM_INFO rom_ncommand[] = // clone of neogeo
{
  { "050-p1.p1", 0x100000, 0x4e097c40, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "050-s1.s1", 0x20000, 0xdb8f9c8e, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "050-m1.m1", 0x20000, 0x6fcf07d3, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "050-v1.v1", 0x100000, 0x23c3ab42, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "050-v2.v2", 0x080000, 0x80b8a984, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "050-c1.c1", 0x100000, 0x87421a0a, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "050-c2.c2", 0x100000, 0xc4cf5548, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "050-c3.c3", 0x100000, 0x03422c1e, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "050-c4.c4", 0x100000, 0x0845eadb, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ncommand, neogeo, "Ninja Commando", ALPHA, 1992, GAME_SHOOT);

static struct ROM_INFO rom_viewpoin[] = // clone of neogeo
{
  { "051-p1.p1", 0x100000, 0x17aa899d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "051-s1.s1", 0x20000, 0x9fea5758, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "051-m1.m1", 0x20000, 0x8e69f29a, REGION_ROM2, 0x00000, LOAD_NORMAL },
	/* What board was originally used (labels 051-V2 and 051-V4)? MVS is twice confirmed on NEO-MVS PROG-G2 */
  { "051-v2.v1", 0x200000, 0x019978b6, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "051-v4.v2", 0x200000, 0x5758f38c, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "051-c1.c1", 0x100000, 0xd624c132, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "051-c1.c1", 0x100000 , 0xd624c132, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "051-c2.c2", 0x100000, 0x40d69f1e, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "051-c2.c2", 0x100000 , 0x40d69f1e, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( viewpoin, neogeo, "Viewpoint", SAMMY, 1992, GAME_SHOOT);

static struct ROM_INFO rom_ssideki[] = // clone of neogeo
{
  { "052-p1.p1", 0x080000, 0x9cd97256, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "052-s1.s1", 0x20000, 0x97689804, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "052-m1.m1", 0x20000, 0x49f17d2d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "052-v1.v1", 0x200000, 0x22c097a5, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "052-c1.c1", 0x100000, 0x53e1c002, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "052-c1.c1", 0x100000 , 0x53e1c002, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "052-c2.c2", 0x100000, 0x776a2d1f, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "052-c2.c2", 0x100000 , 0x776a2d1f, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ssideki, neogeo, "Super Sidekicks / Tokuten Ou", SNK, 1992, GAME_SPORTS);

static struct ROM_INFO rom_wh1[] = /* MVS VERSION clone of neogeo */
{
  { "053-epr.p1", 0x080000, 0xd42e1e9a, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* P's on eprom, correct chip label unknown */
  { "053-epr.p2", 0x080000, 0x0e33e8a3, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "053-s1.s1", 0x20000, 0x8c2c2d6b, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "053-m1.m1", 0x20000, 0x1bd9d04b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "053-v2.v2", 0x200000, 0xa68df485, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "053-v4.v4", 0x100000, 0x7bea8f66, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "053-c1.c1", 0x100000, 0x85eb5bce, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "053-c1.c1", 0x100000 , 0x85eb5bce, REGION_SPRITES, 0x400000, LOAD_CONTINUE },
  { "053-c2.c2", 0x100000, 0xec93b048, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "053-c2.c2", 0x100000 , 0xec93b048, REGION_SPRITES, 0x400001, LOAD_CONTINUE },
  { "053-c3.c3", 0x100000, 0x0dd64965, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "053-c4.c4", 0x100000, 0x9270d954, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( wh1, neogeo, "World Heroes (ALM-005)", ALPHA, 1992, GAME_BEAT);

static struct ROM_INFO rom_kof94[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "055-p1.p1", 0x100000, 0xf10a2042, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "055-p1.p1", 0x100000 , 0xf10a2042, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "055-s1.s1", 0x20000, 0x825976c1, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "055-m1.m1", 0x20000, 0xf6e77cf5, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "055-v1.v1", 0x200000, 0x8889596d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "055-v2.v2", 0x200000, 0x25022b27, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "055-v3.v3", 0x200000, 0x83cf32c0, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "055-c1.c1", 0x200000, 0xb96ef460, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "055-c2.c2", 0x200000, 0x15e096a7, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "055-c3.c3", 0x200000, 0x54f66254, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "055-c4.c4", 0x200000, 0x0b01765f, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "055-c5.c5", 0x200000, 0xee759363, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "055-c6.c6", 0x200000, 0x498da52c, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "055-c7.c7", 0x200000, 0x62f66888, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "055-c8.c8", 0x200000, 0xfe0a235d, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof94, neogeo, "The King of Fighters '94 (NGM-055)(NGH-055)", SNK, 1994, GAME_BEAT);

static struct ROM_INFO rom_aof2[] = /* MVS VERSION clone of neogeo */
{
  { "056-p1.p1", 0x100000, 0xa3b1d021, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "056-s1.s1", 0x20000, 0x8b02638e, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "056-m1.m1", 0x20000, 0xf27e9d52, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "056-v1.v1", 0x200000, 0x4628fde0, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "056-v2.v2", 0x200000, 0xb710e2f2, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "056-v3.v3", 0x100000, 0xd168c301, REGION_SMP1, 0x400000, LOAD_NORMAL },
	/* Different layout with 4xC (32mbit) also exists; chip labels are 056-C13, 056-C24, 056-C57 and 056-C68 */
  { "056-c1.c1", 0x200000, 0x17b9cbd2, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "056-c2.c2", 0x200000, 0x5fd76b67, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "056-c3.c3", 0x200000, 0xd2c88768, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "056-c4.c4", 0x200000, 0xdb39b883, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "056-c5.c5", 0x200000, 0xc3074137, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "056-c6.c6", 0x200000, 0x31de68d3, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "056-c7.c7", 0x200000, 0x3f36df57, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "056-c8.c8", 0x200000, 0xe546d7a8, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( aof2, neogeo, "Art of Fighting 2 / Ryuuko no Ken 2 (NGM-056)", SNK, 1994, GAME_BEAT);

static struct ROM_INFO rom_aof2a[] = /* AES VERSION clone of aof2 */
{
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
  { "056-p1.p1", 0x100000, 0xa3b1d021, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* P is on eprom, correct chip label unknown */
  { "056-epr.ep1", 0x80000, 0x75d6301c, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "056-c1.c1", 0x200000, 0x17b9cbd2, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "056-c2.c2", 0x200000, 0x5fd76b67, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "056-c3.c3", 0x200000, 0xd2c88768, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "056-c4.c4", 0x200000, 0xdb39b883, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "056-c5.c5", 0x200000, 0xc3074137, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "056-c6.c6", 0x200000, 0x31de68d3, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "056-c7.c7", 0x200000, 0x3f36df57, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "056-c8.c8", 0x200000, 0xe546d7a8, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( aof2a, aof2, "Art of Fighting 2 / Ryuuko no Ken 2 (NGH-056)", SNK, 1994, GAME_BEAT);

static struct ROM_INFO rom_wh2[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "057-p1.p1", 0x100000, 0x65a891d9, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "057-p1.p1", 0x100000 , 0x65a891d9, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "057-s1.s1", 0x20000, 0xfcaeb3a4, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "057-m1.m1", 0x20000, 0x8fa3bc77, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "057-v1.v1", 0x200000, 0x8877e301, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "057-v2.v2", 0x200000, 0xc1317ff4, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "057-c1.c1", 0x200000, 0x21c6bb91, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "057-c2.c2", 0x200000, 0xa3999925, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "057-c3.c3", 0x200000, 0xb725a219, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "057-c4.c4", 0x200000, 0x8d96425e, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "057-c5.c5", 0x200000, 0xb20354af, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "057-c6.c6", 0x200000, 0xb13d1de3, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( wh2, neogeo,              "World Heroes 2 (ALM-006)(ALH-006)", ADK, 1993, GAME_BEAT);

static struct ROM_INFO rom_fatfursp[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "058-p1.p1", 0x100000, 0x2f585ba2, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "058-p2.sp2", 0x080000, 0xd7c71a6b, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "058-s1.s1", 0x20000, 0x2df03197, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "058-m1.m1", 0x20000, 0xccc5186e, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "058-v1.v1", 0x200000, 0x55d7ce84, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "058-v2.v2", 0x200000, 0xee080b10, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "058-v3.v3", 0x100000, 0xf9eb3d4a, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "058-c1.c1", 0x200000, 0x044ab13c, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "058-c2.c2", 0x200000, 0x11e6bf96, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "058-c3.c3", 0x200000, 0x6f7938d5, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "058-c4.c4", 0x200000, 0x4ad066ff, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "058-c5.c5", 0x200000, 0x49c5e0bf, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "058-c6.c6", 0x200000, 0x8ff1f43d, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fatfursp, neogeo, "Fatal Fury Special / Garou Densetsu Special (set 1)(NGM-058)(NGH-058)", SNK, 1993, GAME_BEAT);

static struct ROM_INFO rom_fatfurspa[] = /* MVS AND AES VERSION clone of fatfursp */
{
  { "058-p1.p1", 0x100000, 0x2f585ba2, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* the rom below acts as a patch to the program rom in the cart, replacing the first 512kb */
  { "058-p2.sp2", 0x080000, 0xd7c71a6b, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* P is on eprom, correct chip label unknown */
  { "058-epr.ep1", 0x080000, 0x9f0c1e1a, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fatfurspa, fatfursp, "Fatal Fury Special / Garou Densetsu Special (set 2)(NGM-058)(NGH-058)", SNK, 1993, GAME_BEAT);

static struct ROM_INFO rom_savagere[] = // clone of neogeo
{
  { "059-p1.p1", 0x100000, 0x01d4e9c0, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "059-p1.p1", 0x100000 , 0x01d4e9c0, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "059-s1.s1", 0x20000, 0xe08978ca, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "059-m1.m1", 0x20000, 0x29992eba, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "059-v1.v1", 0x200000, 0x530c50fd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "059-v2.v2", 0x200000, 0xeb6f1cdb, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "059-v3.v3", 0x200000, 0x7038c2f9, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "059-c1.c1", 0x200000, 0x763ba611, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "059-c2.c2", 0x200000, 0xe05e8ca6, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "059-c3.c3", 0x200000, 0x3e4eba4b, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "059-c4.c4", 0x200000, 0x3c2a3808, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "059-c5.c5", 0x200000, 0x59013f9e, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "059-c6.c6", 0x200000, 0x1c8d5def, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "059-c7.c7", 0x200000, 0xc88f7035, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "059-c8.c8", 0x200000, 0x484ce3ba, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( savagere, neogeo, "Savage Reign / Fu'un Mokushiroku - kakutou sousei", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_fightfev[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "060-p1.p1", 0x100000, 0x2a104b50, REGION_CPU1, 0x0000000, LOAD_SWAP_16 },
  { "060-s1.s1", 0x20000, 0x7f012104, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "060-m1.m1", 0x20000, 0x0b7c4e65, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "060-v1.v1", 0x200000, 0xf417c215, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "060-v2.v2", 0x100000, 0xefcff7cf, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "060-c1.c1", 0x200000, 0x8908fff9, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "060-c2.c2", 0x200000, 0xc6649492, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "060-c3.c3", 0x200000, 0x0956b437, REGION_SPRITES, 0x0400000, LOAD_8_16 },
  { "060-c4.c4", 0x200000, 0x026f3b62, REGION_SPRITES, 0x0400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fightfev, neogeo, "Fight Fever (set 1)", VICCOM, 1994, GAME_BEAT);

static struct ROM_INFO rom_ssideki2[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "061-p1.p1", 0x100000, 0x5969e0dc, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "061-s1.s1", 0x20000, 0x226d1b68, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "061-m1.m1", 0x20000, 0x156f6951, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "061-v1.v1", 0x200000, 0xf081c8d3, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "061-v2.v2", 0x200000, 0x7cd63302, REGION_SMP1, 0x200000, LOAD_NORMAL },
	/* Different layout with 8xC (8 mbit) also exists; naming sheme 061-Cx */
  { "061-c1-16.c1", 0x200000, 0xa626474f, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "061-c2-16.c2", 0x200000, 0xc3be42ae, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "061-c3-16.c3", 0x200000, 0x2a7b98b9, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "061-c4-16.c4", 0x200000, 0xc0be9a1f, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ssideki2, neogeo, "Super Sidekicks 2 - The World Championship / Tokuten Ou 2 - real fight football (NGM-061)(NGH-061)", SNK, 1994, GAME_SPORTS);

static struct ROM_INFO rom_spinmast[] =
{
  { "062-p1.p1", 0x100000, 0x37aba1aa, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "062-p2.sp2", 0x100000, 0xf025ab77, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "062-s1.s1", 0x20000, 0x289e2bbe, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "062-m1.m1", 0x20000, 0x76108b2f, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "062-v1.v1", 0x100000, 0xcc281aef, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "062-c1.c1", 0x100000, 0xa9375aa2, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "062-c2.c2", 0x100000, 0x0e73b758, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "062-c3.c3", 0x100000, 0xdf51e465, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "062-c4.c4", 0x100000, 0x38517e90, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "062-c5.c5", 0x100000, 0x7babd692, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "062-c6.c6", 0x100000, 0xcde5ade5, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "062-c7.c7", 0x100000, 0xbb2fd7c0, REGION_SPRITES, 0x600000, LOAD_8_16 },
  { "062-c8.c8", 0x100000, 0x8d7be933, REGION_SPRITES, 0x600001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( spinmast, neogeo, "Spin Master / Miracle Adventure", DECO, 1993, GAME_BEAT);

static struct ROM_INFO rom_samsho2[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "063-p1.p1", 0x100000, 0x22368892, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "063-p1.p1", 0x100000 , 0x22368892, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "063-s1.s1", 0x20000, 0x64a5cd66, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "063-m1.m1", 0x20000, 0x56675098, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "063-v1.v1", 0x200000, 0x37703f91, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "063-v2.v2", 0x200000, 0x0142bde8, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "063-v3.v3", 0x200000, 0xd07fa5ca, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "063-v4.v4", 0x100000, 0x24aab4bb, REGION_SMP1, 0x600000, LOAD_NORMAL },
  { "063-c1.c1", 0x200000, 0x86cd307c, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "063-c2.c2", 0x200000, 0xcdfcc4ca, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "063-c3.c3", 0x200000, 0x7a63ccc7, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "063-c4.c4", 0x200000, 0x751025ce, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "063-c5.c5", 0x200000, 0x20d3a475, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "063-c6.c6", 0x200000, 0xae4c0a88, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "063-c7.c7", 0x200000, 0x2df3cbcf, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "063-c8.c8", 0x200000, 0x1ffc6dfa, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho2, neogeo, "Samurai Shodown II / Shin Samurai Spirits - Haohmaru jigokuhen (NGM-063)(NGH-063)", SNK, 1994, GAME_BEAT);

static struct ROM_INFO rom_samsho2k[] = /* KOREAN VERSION clone of samsho2 */
{
  { "063-p1-kan.p1", 0x100000, 0x147cc6d7, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	// the roms below apply as patch over the main program (I haven't checked what they change, the game boots as the Korean version even with just the above program)
  { "063-p1-kan.p1", 0x100000 , 0x147cc6d7, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "063-ep1-kan.ep1", 0x080000, 0xfa32e2d8, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "063-ep2-kan.ep2", 0x080000, 0x70b1a4d9, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "063-s1-kan.s1", 0x20000, 0xff08f80b, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho2k, samsho2, "Saulabi Spirits / Jin Saulabi Tu Hon (Korean release of Samurai Shodown II)", SNK, 1994, GAME_BEAT);

static struct ROM_INFO rom_wjammers[] =
{
  { "065-p1.p1", 0x100000, 0x6692c140, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "065-s1.s1", 0x20000, 0x074b5723, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "065-m1.m1", 0x20000, 0x52c23cfc, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "065-v1.v1", 0x100000, 0xce8b3698, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "065-v2.v2", 0x100000, 0x659f9b96, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "065-v3.v3", 0x100000, 0x39f73061, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "065-v4.v4", 0x100000, 0x5dee7963, REGION_SMP1, 0x300000, LOAD_NORMAL },
  { "065-c1.c1", 0x100000, 0xc7650204, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "065-c2.c2", 0x100000, 0xd9f3e71d, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "065-c3.c3", 0x100000, 0x40986386, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "065-c4.c4", 0x100000, 0x715e15ff, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_karnovr[] =
{
  { "066-p1.p1", 0x100000, 0x8c86fd22, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "066-s1.s1", 0x20000, 0xbae5d5e5, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "066-m1.m1", 0x20000, 0x030beae4, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "066-v1.v1", 0x200000, 0x0b7ea37a, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "066-c1.c1", 0x200000, 0x09dfe061, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "066-c2.c2", 0x200000, 0xe0f6682a, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "066-c3.c3", 0x200000, 0xa673b4f7, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "066-c4.c4", 0x200000, 0xcb3dc5f4, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "066-c5.c5", 0x200000, 0x9a28785d, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "066-c6.c6", 0x200000, 0xc15c01ed, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( wjammers, neogeo, "Windjammers / Flying Power Disc", DECO, 1994, GAME_SPORTS);

CLNEI( karnovr, neogeo, "Karnov's Revenge / Fighter's History Dynamite", DECO, 1994, GAME_BEAT);

static struct ROM_INFO rom_gururin[] = /* MVS ONLY RELEASE */
{
  { "067-p1.p1", 0x80000, 0x4cea8a49, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "067-s1.s1", 0x20000, 0xb119e1eb, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "067-m1.m1", 0x20000, 0x9e3c6328, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "067-v1.v1", 0x80000, 0xcf23afd0, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "067-c1.c1", 0x200000, 0x35866126, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "067-c2.c2", 0x200000, 0x9db64084, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( gururin, neogeo, "Gururin", FACE, 1994, GAME_PUZZLE);

static struct ROM_INFO rom_pspikes2[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "068-pg1.p1", 0x100000, 0x105a408f, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "068-sg1.s1", 0x20000, 0x18082299, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "068-mg1.m1", 0x20000, 0xb1c7911e, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "068-v1.v1", 0x100000, 0x2ced86df, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "068-v2.v2", 0x100000, 0x970851ab, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "068-v3.v3", 0x100000, 0x81ff05aa, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "068-c1.c1", 0x100000, 0x7f250f76, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "068-c2.c2", 0x100000, 0x20912873, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "068-c3.c3", 0x100000, 0x4b641ba1, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "068-c4.c4", 0x100000, 0x35072596, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "068-c5.c5", 0x100000, 0x151dd624, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "068-c6.c6", 0x100000, 0xa6722604, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( pspikes2, neogeo, "Power Spikes II (NGM-068)", VIDEOSYSTEM, 1994, GAME_SPORTS);

static struct ROM_INFO rom_fatfury3[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "069-p1.p1", 0x100000, 0xa8bcfbbc, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "069-sp2.sp2", 0x200000, 0xdbe963ed, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "069-s1.s1", 0x20000, 0x0b33a800, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "069-m1.m1", 0x20000, 0xfce72926, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "069-v1.v1", 0x400000, 0x2bdbd4db, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "069-v2.v2", 0x400000, 0xa698a487, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "069-v3.v3", 0x200000, 0x581c5304, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "069-c1.c1", 0x400000, 0xe302f93c, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "069-c2.c2", 0x400000, 0x1053a455, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "069-c3.c3", 0x400000, 0x1c0fde2f, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "069-c4.c4", 0x400000, 0xa25fc3d0, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "069-c5.c5", 0x200000, 0xb3ec6fa6, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "069-c6.c6", 0x200000, 0x69210441, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( fatfury3, neogeo, "Fatal Fury 3 - Road to the Final Victory / Garou Densetsu 3 - haruka-naru tatakai (NGM-069)(NGH-069)", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_zupapa[] = /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
{
  { "070-p1.p1", 0x100000, 0x5a96203e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* The Encrypted Boards do _not_ have an s1 rom, data for it comes from the Cx ROMs */
  // Dummy region_fixed, overwritten by the decrypt functions but the size is
  // important
  { "sfix.sfix", 0x20000, 0xc2ea0cfd, REGION_FIXED, 0x000000, LOAD_NORMAL },
/* Ignored : 	ROM_FILL( 0x000000, 0x20000, 0 ) */
  { "070-epr.m1", 0x20000, 0x5a3b3191, REGION_ROM2, 0x00000, LOAD_NORMAL },
	/* M1 on eprom, correct chip label unknown */
  { "070-v1.v1", 0x200000, 0xd3a7e1ff, REGION_SMP1, 0x000000, LOAD_NORMAL },
	/* Encrypted */
  { "070-c1.c1", 0x800000, 0xf8ad02d8, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "070-c2.c2", 0x800000, 0x70156dde, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( zupapa, neogeo, "Zupapa!" , SNK, 2001, GAME_PLATFORM);

static struct ROM_INFO rom_panicbom[] = /* MVS ONLY RELEASE */
{
  { "073-p1.p1", 0x080000, 0xadc356ad, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "073-s1.s1", 0x20000, 0xb876de7e, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "073-m1.m1", 0x20000, 0x3cdf5d88, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "073-v1.v1", 0x200000, 0x7fc86d2f, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "073-v2.v2", 0x100000, 0x082adfc7, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "073-c1.c1", 0x100000, 0x8582e1b5, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "073-c2.c2", 0x100000, 0xe15a093b, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( panicbom, neogeo, "Panic Bomber", EIGHTING, 1994, GAME_PUZZLE);

static struct ROM_INFO rom_aodk[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "074-p1.p1", 0x100000, 0x62369553, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "074-p1.p1", 0x100000 , 0x62369553, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "074-s1.s1", 0x20000, 0x96148d2b, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "074-m1.m1", 0x20000, 0x5a52a9d1, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "074-v1.v1", 0x200000, 0x7675b8fa, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "074-v2.v2", 0x200000, 0xa9da86e9, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "074-c1.c1", 0x200000, 0xa0b39344, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "074-c2.c2", 0x200000, 0x203f6074, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "074-c3.c3", 0x200000, 0x7fff4d41, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "074-c4.c4", 0x200000, 0x48db3e0a, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "074-c5.c5", 0x200000, 0xc74c5e51, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "074-c6.c6", 0x200000, 0x73e8e7e0, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "074-c7.c7", 0x200000, 0xac7daa01, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "074-c8.c8", 0x200000, 0x14e7ad71, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( aodk, neogeo,        "Aggressors of Dark Kombat / Tsuukai GANGAN Koushinkyoku (ADM-008)(ADH-008)", ADK, 1994, GAME_BEAT);

static struct ROM_INFO rom_sonicwi2[] =
{
  { "075-p1.p1", 0x100000, 0x92871738, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "075-p1.p1", 0x100000 , 0x92871738, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "075-s1.s1", 0x20000, 0xc9eec367, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "075-m1.m1", 0x20000, 0xbb828df1, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "075-v1.v1", 0x200000, 0x7577e949, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "075-v2.v2", 0x100000, 0x021760cd, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "075-c1.c1", 0x200000, 0x3278e73e, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "075-c2.c2", 0x200000, 0xfe6355d6, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "075-c3.c3", 0x200000, 0xc1b438f1, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "075-c4.c4", 0x200000, 0x1f777206, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( sonicwi2, neogeo, "Aero Fighters 2 / Sonic Wings 2", VIDEOSYSTEM, 1994, GAME_SHOOT);

static struct ROM_INFO rom_zedblade[] = /* MVS ONLY RELEASE */
{
  { "076-p1.p1", 0x080000, 0xd7c1effd, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "076-s1.s1", 0x20000, 0xf4c25dd5, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "076-m1.m1", 0x20000, 0x7b5f3d0a, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "076-v1.v1", 0x200000, 0x1a21d90c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "076-v2.v2", 0x200000, 0xb61686c3, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "076-v3.v3", 0x100000, 0xb90658fa, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "076-c1.c1", 0x200000, 0x4d9cb038, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "076-c2.c2", 0x200000, 0x09233884, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "076-c3.c3", 0x200000, 0xd06431e3, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "076-c4.c4", 0x200000, 0x4b1c089b, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( zedblade, neogeo, "Zed Blade / Operation Ragnarok", NMK, 1994, GAME_SHOOT);

static struct ROM_INFO rom_galaxyfg[] =
{
  { "078-p1.p1", 0x100000, 0x45906309, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "078-p1.p1", 0x100000 , 0x45906309, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "078-s1.s1", 0x20000, 0x72f8923e, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "078-m1.m1", 0x20000, 0x8e9e3b10, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "078-v1.v1", 0x200000, 0xe3b735ac, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "078-v2.v2", 0x200000, 0x6a8e78c2, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "078-v3.v3", 0x100000, 0x70bca656, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "078-c1.c1", 0x200000, 0xc890c7c0, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "078-c2.c2", 0x200000, 0xb6d25419, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "078-c3.c3", 0x200000, 0x9d87e761, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "078-c4.c4", 0x200000, 0x765d7cb8, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "078-c5.c5", 0x200000, 0xe6b77e6a, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "078-c6.c6", 0x200000, 0xd779a181, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "078-c7.c7", 0x100000, 0x4f27d580, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "078-c8.c8", 0x100000, 0x0a7cc0d8, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( galaxyfg, neogeo, "Galaxy Fight - Universal Warriors", SUNSOFT, 1995, GAME_BEAT);

static struct ROM_INFO rom_strhoop[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "079-p1.p1", 0x100000, 0x5e78328e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "079-s1.s1", 0x20000, 0x3ac06665, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "079-m1.m1", 0x20000, 0xbee3455a, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "079-v1.v1", 0x200000, 0x718a2400, REGION_SMP1, 0x000000, LOAD_NORMAL },
	/* AES 079-v2 is only 4 mbit (TC534200), data is the same */
  { "079-v2.v2", 0x100000, 0x720774eb, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "079-c1.c1", 0x200000, 0x0581c72a, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "079-c2.c2", 0x200000, 0x5b9b8fb6, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "079-c3.c3", 0x200000, 0xcd65bb62, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "079-c4.c4", 0x200000, 0xa4c90213, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( strhoop, neogeo, "Street Hoop / Street Slam / Dunk Dream (DEM-004) (DEH-004)", DECO, 1994, GAME_SPORTS);

static struct ROM_INFO rom_ssideki3[] = // clone of neogeo
{
  { "081-p1.p1", 0x100000, 0x6bc27a3d, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "081-p1.p1", 0x100000 , 0x6bc27a3d, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "081-s1.s1", 0x20000, 0x7626da34, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "081-m1.m1", 0x20000, 0x82fcd863, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "081-v1.v1", 0x200000, 0x201fa1e1, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "081-v2.v2", 0x200000, 0xacf29d96, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "081-v3.v3", 0x200000, 0xe524e415, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "081-c1.c1", 0x200000, 0x1fb68ebe, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "081-c2.c2", 0x200000, 0xb28d928f, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "081-c3.c3", 0x200000, 0x3b2572e8, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "081-c4.c4", 0x200000, 0x47d26a7c, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "081-c5.c5", 0x200000, 0x17d42f0d, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "081-c6.c6", 0x200000, 0x6b53fb75, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ssideki3, neogeo, "Super Sidekicks 3 - The Next Glory / Tokuten Ou 3 - eikou e no michi", SNK, 1995, GAME_SPORTS);

static struct ROM_INFO rom_doubledr[] = // clone of neogeo
{
  { "082-p1.p1", 0x100000, 0x34ab832a, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "082-p1.p1", 0x100000 , 0x34ab832a, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "082-s1.s1", 0x20000, 0xbef995c5, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "082-m1.m1", 0x20000, 0x10b144de, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "082-v1.v1", 0x200000, 0xcc1128e4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "082-v2.v2", 0x200000, 0xc3ff5554, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "082-c1.c1", 0x200000, 0xb478c725, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "082-c2.c2", 0x200000, 0x2857da32, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "082-c3.c3", 0x200000, 0x8b0d378e, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "082-c4.c4", 0x200000, 0xc7d2f596, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "082-c5.c5", 0x200000, 0xec87bff6, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "082-c6.c6", 0x200000, 0x844a8a11, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "082-c7.c7", 0x100000, 0x727c4d02, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "082-c8.c8", 0x100000, 0x69a5fa37, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( doubledr, neogeo, "Double Dragon (Neo-Geo)", TECHNOS, 1995, GAME_BEAT);

static struct ROM_INFO rom_pbobblen[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "d96-07.ep1", 0x080000, 0x6102ca14, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "d96-04.s1", 0x20000, 0x9caae538, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "d96-06.m1", 0x20000, 0xf424368a, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "068-v1.v1", 0x100000, 0x2ced86df, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "068-v2.v2", 0x100000, 0x970851ab, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "d96-01.v3", 0x100000, 0x0840cbc4, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "d96-05.v4", 0x080000, 0x0a548948, REGION_SMP1, 0x300000, LOAD_NORMAL },
  { "068-c1.c1", 0x100000, 0x7f250f76, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "068-c2.c2", 0x100000, 0x20912873, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "068-c3.c3", 0x100000, 0x4b641ba1, REGION_SPRITES, 0x200000, LOAD_8_16 },
  { "068-c4.c4", 0x100000, 0x35072596, REGION_SPRITES, 0x200001, LOAD_8_16 },
  { "d96-02.c5", 0x80000, 0xe89ad494, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "d96-03.c6", 0x80000, 0x4b42d7eb, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( pbobblen, neogeo, "Puzzle Bobble / Bust-A-Move (Neo-Geo) (NGM-083)", TAITO, 1994, GAME_PUZZLE);

static struct ROM_INFO rom_kof95[] = /* MVS VERSION clone of neogeo */
{
  { "084-p1.p1", 0x100000, 0x2cba2716, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "084-p1.p1", 0x100000 , 0x2cba2716, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "084-s1.s1", 0x20000, 0xde716f8a, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "084-m1.m1", 0x20000, 0x6f2d7429, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "084-v1.v1", 0x400000, 0x84861b56, REGION_SMP1, 0x000000, LOAD_NORMAL },
	/* 600000-7fffff empty */
  { "084-v2.v2", 0x200000, 0xb38a2803, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "084-v3.v3", 0x100000, 0xd683a338, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "084-c1.c1", 0x400000, 0xfe087e32, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "084-c2.c2", 0x400000, 0x07864e09, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "084-c3.c3", 0x400000, 0xa4e65d1b, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "084-c4.c4", 0x400000, 0xc1ace468, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "084-c5.c5", 0x200000, 0x8a2c1edc, REGION_SPRITES, 0x1000000, LOAD_8_16 },
	/* 1400000-17fffff empty */
  { "084-c6.c6", 0x200000, 0xf593ac35, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "084-c7.c7", 0x100000, 0x9904025f, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "084-c8.c8", 0x100000, 0x78eb0f9b, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof95, neogeo, "The King of Fighters '95 (NGM-084)", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_kof95h[] = /* MVS AND AES VERSION clone of kof95 */
{
  { "084-pg1.p1", 0x100000, 0x5e54cf95, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "084-pg1.p1", 0x100000 , 0x5e54cf95, REGION_CPU1, 0x000000, LOAD_CONTINUE },
	/* 600000-7fffff empty */
	/* 1400000-17fffff empty */
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof95h, kof95, "The King of Fighters '95 (NGH-084)", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_tws96[] = /* MVS ONLY RELEASE */
{
  { "086-p1.p1", 0x100000, 0x03e20ab6, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "086-s1.s1", 0x20000, 0x6f5e2b3a, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "086-m1.m1", 0x20000, 0xcb82bc5d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "086-v1.v1", 0x200000, 0x97bf1986, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "086-v2.v2", 0x200000, 0xb7eb05df, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "086-c1.c1", 0x400000, 0x2611bc2a, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "086-c2.c2", 0x400000, 0x6b0d6827, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "086-c3.c3", 0x100000, 0x750ddc0c, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "086-c4.c4", 0x100000, 0x7a6e7d82, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( tws96, neogeo, "Tecmo World Soccer '96", TECMO, 1996, GAME_SPORTS);

static struct ROM_INFO rom_samsho3[] = /* MVS VERSION clone of neogeo */
{
  { "087-epr.ep1", 0x080000, 0x23e09bb8, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "087-epr.ep2", 0x080000, 0x256f5302, REGION_CPU1, 0x080000, LOAD_SWAP_16 },
  { "087-epr.ep3", 0x080000, 0xbf2db5dd, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* P's on eprom, correct chip label unknown */
  { "087-epr.ep4", 0x080000, 0x53e60c58, REGION_CPU1, 0x180000, LOAD_SWAP_16 },
  { "087-p5.p5", 0x100000, 0xe86ca4af, REGION_CPU1, 0x200000, LOAD_SWAP_16 },
  { "087-s1.s1", 0x20000, 0x74ec7d9f, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "087-m1.m1", 0x20000, 0x8e6440eb, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "087-v1.v1", 0x400000, 0x84bdd9a0, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "087-v2.v2", 0x200000, 0xac0f261a, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "087-c1.c1", 0x400000, 0x07a233bc, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "087-c2.c2", 0x400000, 0x7a413592, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "087-c3.c3", 0x400000, 0x8b793796, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "087-c4.c4", 0x400000, 0x728fbf11, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "087-c5.c5", 0x400000, 0x172ab180, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "087-c6.c6", 0x400000, 0x002ff8f3, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "087-c7.c7", 0x100000, 0xae450e3d, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "087-c8.c8", 0x100000, 0xa9e82717, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho3, neogeo, "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (NGM-087)", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_samsho3h[] = /* AES VERSION clone of samsho3 */
{
  { "087-pg1.p1", 0x100000, 0x282a336e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "087-p2.sp2", 0x200000, 0x9bbe27e0, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_fswords[] = /* KOREAN VERSION clone of samsho3 */
{
  { "187-p1k.p1", 0x100000, 0xc8e7c075, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "087-p2.sp2", 0x200000, 0x9bbe27e0, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho3h, samsho3, "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (NGH-087)", SNK, 1995, GAME_BEAT);
CLNEI( fswords, samsho3, "Fighters Swords (Korean release of Samurai Shodown III)", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_stakwin[] =
{
  { "088-p1.p1", 0x100000, 0xbd5814f6, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "088-p1.p1", 0x100000, 0xbd5814f6, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "088-s1.s1", 0x20000, 0x073cb208, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "088-m1.m1", 0x20000, 0x2fe1f499, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "088-v1.v1", 0x200000, 0xb7785023, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "088-c1.c1", 0x200000, 0x6e733421, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "088-c2.c2", 0x200000, 0x4d865347, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "088-c3.c3", 0x200000, 0x8fa5a9eb, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "088-c4.c4", 0x200000, 0x4604f0dc, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( stakwin, neogeo, "Stakes Winner / Stakes Winner - GI kinzen seiha e no michi", SAURUS, 1995, GAME_SPORTS);

static struct ROM_INFO rom_pulstar[] = // clone of neogeo
{
  { "089-p1.p1", 0x100000, 0x5e5847a2, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "089-p2.sp2", 0x200000, 0x028b774c, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "089-s1.s1", 0x20000, 0xc79fc2c8, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "089-m1.m1", 0x20000, 0xff3df7c7, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "089-v1.v1", 0x400000, 0x6f726ecb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "089-v2.v2", 0x400000, 0x9d2db551, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "089-c1.c1", 0x400000, 0xf4e97332, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "089-c2.c2", 0x400000, 0x836d14da, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "089-c3.c3", 0x400000, 0x913611c4, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "089-c4.c4", 0x400000, 0x44cef0e3, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "089-c5.c5", 0x400000, 0x89baa1d7, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "089-c6.c6", 0x400000, 0xb2594d56, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "089-c7.c7", 0x200000, 0x6a5618ca, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "089-c8.c8", 0x200000, 0xa223572d, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( pulstar, neogeo, "Pulstar", AICOM, 1995, GAME_SHOOT);

static struct ROM_INFO rom_whp[] = // clone of neogeo
{
  { "090-p1.p1", 0x100000, 0xafaa4702, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "090-p1.p1", 0x100000 , 0xafaa4702, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "090-s1.s1", 0x20000, 0x174a880f, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "090-m1.m1", 0x20000, 0x28065668, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "090-v1.v1", 0x200000, 0x30cf2709, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "064-v2.v2", 0x200000, 0xb6527edd, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "090-v3.v3", 0x200000, 0x1908a7ce, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "090-c1.c1", 0x400000, 0xcd30ed9b, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "090-c2.c2", 0x400000, 0x10eed5ee, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "064-c3.c3", 0x200000, 0x436d1b31, REGION_SPRITES, 0x0800000, LOAD_8_16 },
	/* 0c00000-0ffffff empty */
  { "064-c4.c4", 0x200000, 0xf9c8dd26, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "064-c5.c5", 0x200000, 0x8e34a9f4, REGION_SPRITES, 0x1000000, LOAD_8_16 },
	/* 1400000-17fffff empty */
  { "064-c6.c6", 0x200000, 0xa43e4766, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "064-c7.c7", 0x200000, 0x59d97215, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "064-c8.c8", 0x200000, 0xfc092367, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( whp, neogeo,        "World Heroes Perfect", ADK, 1995, GAME_BEAT);

static struct ROM_INFO rom_kabukikl[] =
{
  { "092-p1.p1", 0x100000, 0x28ec9b77, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "092-p1.p1", 0x100000 , 0x28ec9b77, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "092-s1.s1", 0x20000, 0xa3d68ee2, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "092-m1.m1", 0x20000, 0x91957ef6, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "092-v1.v1", 0x200000, 0x69e90596, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "092-v2.v2", 0x200000, 0x7abdb75d, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "092-v3.v3", 0x200000, 0xeccc98d3, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "092-v4.v4", 0x100000, 0xa7c9c949, REGION_SMP1, 0x600000, LOAD_NORMAL },
  { "092-c1.c1", 0x400000, 0x2a9fab01, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "092-c2.c2", 0x400000, 0x6d2bac02, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "092-c3.c3", 0x400000, 0x5da735d6, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "092-c4.c4", 0x400000, 0xde07f997, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kabukikl, neogeo, "Kabuki Klash - Far East of Eden / Tengai Makyou - Shin Den", HUDSON, 1995, GAME_BEAT);

static struct ROM_INFO rom_neobombe[] = /* MVS ONLY RELEASE */
{
  { "093-p1.p1", 0x100000, 0xa1a71d0d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "093-s1.s1", 0x20000, 0x4b3fa119, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "093-m1.m1", 0x20000, 0xe81e780b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "093-v1.v1", 0x400000, 0x02abd4b0, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "093-v2.v2", 0x200000, 0xa92b8b3d, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "093-c1.c1", 0x400000, 0xd1f328f8, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "093-c2.c2", 0x400000, 0x82c49540, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "093-c3.c3", 0x080000, 0xe37578c5, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "093-c4.c4", 0x080000, 0x59826783, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( neobombe, neogeo, "Neo Bomberman", HUDSON, 1997, GAME_MAZE);

static struct ROM_INFO rom_gowcaizr[] =
{
  { "094-p1.p1", 0x100000, 0x33019545, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "094-p1.p1", 0x100000 , 0x33019545, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "094-s1.s1", 0x20000, 0x2f8748a2, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "094-m1.m1", 0x20000, 0x78c851cb, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "094-v1.v1", 0x200000, 0x6c31223c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "094-v2.v2", 0x200000, 0x8edb776c, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "094-v3.v3", 0x100000, 0xc63b9285, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "094-c1.c1", 0x200000, 0x042f6af5, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "094-c2.c2", 0x200000, 0x0fbcd046, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "094-c3.c3", 0x200000, 0x58bfbaa1, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "094-c4.c4", 0x200000, 0x9451ee73, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "094-c5.c5", 0x200000, 0xff9cf48c, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "094-c6.c6", 0x200000, 0x31bbd918, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "094-c7.c7", 0x200000, 0x2091ec04, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "094-c8.c8", 0x200000, 0xd80dd241, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( gowcaizr, neogeo, "Voltage Fighter - Gowcaizer / Choujin Gakuen Gowcaizer", TECHNOS, 1995, GAME_BEAT);

static struct ROM_INFO rom_rbff1[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "095-p1.p1", 0x100000, 0x63b4d8ae, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "095-p2.sp2", 0x200000, 0xcc15826e, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "095-s1.s1", 0x20000, 0xb6bf5e08, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "095-m1.m1", 0x20000, 0x653492a7, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "069-v1.v1", 0x400000, 0x2bdbd4db, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "069-v2.v2", 0x400000, 0xa698a487, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "095-v3.v3", 0x400000, 0x189d1c6c, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "069-c1.c1", 0x400000, 0xe302f93c, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "069-c2.c2", 0x400000, 0x1053a455, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "069-c3.c3", 0x400000, 0x1c0fde2f, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "069-c4.c4", 0x400000, 0xa25fc3d0, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "095-c5.c5", 0x400000, 0x8b9b65df, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "095-c6.c6", 0x400000, 0x3e164718, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "095-c7.c7", 0x200000, 0xca605e12, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "095-c8.c8", 0x200000, 0x4e6beb6c, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( rbff1, neogeo, "Real Bout Fatal Fury / Real Bout Garou Densetsu (NGM-095)(NGH-095)", SNK, 1995, GAME_BEAT);

static struct ROM_INFO rom_aof3[] = // clone of neogeo
{
  { "096-p1.p1", 0x100000, 0x9edb420d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "096-p2.sp2", 0x200000, 0x4d5a2602, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "096-s1.s1", 0x20000, 0xcc7fd344, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "096-m1.m1", 0x20000, 0xcb07b659, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "096-v1.v1", 0x200000, 0xe2c32074, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "096-v2.v2", 0x200000, 0xa290eee7, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "096-v3.v3", 0x200000, 0x199d12ea, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "096-c1.c1", 0x400000, 0xf17b8d89, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "096-c2.c2", 0x400000, 0x3840c508, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "096-c3.c3", 0x400000, 0x55f9ee1e, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "096-c4.c4", 0x400000, 0x585b7e47, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "096-c5.c5", 0x400000, 0xc75a753c, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "096-c6.c6", 0x400000, 0x9a9d2f7a, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "096-c7.c7", 0x200000, 0x51bd8ab2, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "096-c8.c8", 0x200000, 0x9a34f99c, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( aof3, neogeo, "Art of Fighting 3 - The Path of the Warrior / Art of Fighting - Ryuuko no Ken Gaiden", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_aof3k[] = /* KOREAN VERSION */
{
  { "196-p1k.p1", 0x100000, 0xa0780789, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "096-p2.sp2", 0x200000, 0x4d5a2602, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "096-s1.s1", 0x20000, 0xcc7fd344, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "096-m1.m1", 0x20000, 0xcb07b659, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "096-v1.v1", 0x200000, 0xe2c32074, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "096-v2.v2", 0x200000, 0xa290eee7, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "096-v3.v3", 0x200000, 0x199d12ea, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "096-c1.c1", 0x400000, 0xf17b8d89, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "096-c2.c2", 0x400000, 0x3840c508, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "096-c3.c3", 0x400000, 0x55f9ee1e, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "096-c4.c4", 0x400000, 0x585b7e47, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "096-c5.c5", 0x400000, 0xc75a753c, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "096-c6.c6", 0x400000, 0x9a9d2f7a, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "096-c7.c7", 0x200000, 0x51bd8ab2, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "096-c8.c8", 0x200000, 0x9a34f99c, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( aof3k, aof3, "Art of Fighting 3 - The Path of the Warrior (Korean release)", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_sonicwi3[] =
{
  { "097-p1.p1", 0x100000, 0x0547121d, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "097-p1.p1", 0x100000 , 0x0547121d, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "097-s1.s1", 0x20000, 0x8dd66743, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "097-m1.m1", 0x20000, 0xb20e4291, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "097-v1.v1", 0x400000, 0x6f885152, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "097-v2.v2", 0x200000, 0x3359e868, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "097-c1.c1", 0x400000, 0x33d0d589, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "097-c2.c2", 0x400000, 0x186f8b43, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "097-c3.c3", 0x200000, 0xc339fff5, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "097-c4.c4", 0x200000, 0x84a40c6e, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( sonicwi3, neogeo, "Aero Fighters 3 / Sonic Wings 3", VIDEOSYSTEM, 1995, GAME_SHOOT);

static struct ROM_INFO rom_turfmast[] =
{
  { "200-p1.p1", 0x100000, 0x28c83048, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "200-p1.p1", 0x100000, 0x28c83048, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "200-s1.s1", 0x20000, 0x9a5402b2, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "200-m1.m1", 0x20000, 0x9994ac00, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "200-v1.v1", 0x200000, 0x00fd48d2, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "200-v2.v2", 0x200000, 0x082acb31, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "200-v3.v3", 0x200000, 0x7abca053, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "200-v4.v4", 0x200000, 0x6c7b4902, REGION_SMP1, 0x600000, LOAD_NORMAL },
  { "200-c1.c1", 0x400000, 0x8e7bf41a, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "200-c2.c2", 0x400000, 0x5a65a8ce, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( turfmast, neogeo, "Neo Turf Masters / Big Tournament Golf", NAZCA, 1996, GAME_SPORTS);

static struct ROM_INFO rom_mslug[] =
{
  { "201-p1.p1", 0x100000, 0x08d8daa5, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "201-p1.p1", 0x100000 , 0x08d8daa5, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "201-s1.s1", 0x20000, 0x2f55958d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "201-m1.m1", 0x20000, 0xc28b3253, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "201-v1.v1", 0x400000, 0x23d22ed1, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "201-v2.v2", 0x400000, 0x472cf9db, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "201-c1.c1", 0x400000, 0x72813676, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "201-c2.c2", 0x400000, 0x96f62574, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "201-c3.c3", 0x400000, 0x5121456a, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "201-c4.c4", 0x400000, 0xf4ad59a3, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug, neogeo, "Metal Slug - Super Vehicle-001", NAZCA, 1996, GAME_SHOOT);

static struct ROM_INFO rom_puzzledp[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "202-p1.p1", 0x080000, 0x2b61415b, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "202-s1.s1", 0x20000, 0xcd19264f, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "202-m1.m1", 0x20000, 0x9c0291ea, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "202-v1.v1", 0x080000, 0xdebeb8fb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "202-c1.c1", 0x100000, 0xcc0095ef, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "202-c2.c2", 0x100000, 0x42371307, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( puzzledp, neogeo, "Puzzle De Pon!", TAITO, 1995, GAME_PUZZLE);

static struct ROM_INFO rom_neomrdo[] = /* MVS ONLY RELEASE */
{
  { "207-p1.p1", 0x100000, 0x334ea51e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "207-s1.s1", 0x20000, 0x6aebafce, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "207-m1.m1", 0x20000, 0xb5b74a95, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "207-v1.v1", 0x200000, 0x4143c052, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "207-c1.c1", 0x200000, 0xc7541b9d, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "207-c2.c2", 0x200000, 0xf57166d2, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( neomrdo, neogeo, "Neo Mr. Do!", VISCO, 1996, GAME_MAZE);

static struct ROM_INFO rom_sdodgeb[] = /* MVS ONLY RELEASE */
{
  { "208-p1.p1", 0x100000, 0x127f3d32, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "208-p1.p1", 0x100000 , 0x127f3d32, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "208-s1.s1", 0x20000, 0x64abd6b3, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "208-m1.m1", 0x20000, 0x0a5f3325, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "208-v1.v1", 0x400000, 0xe7899a24, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "208-c1.c1", 0x400000, 0x93d8619b, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "208-c2.c2", 0x400000, 0x1c737bb6, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "208-c3.c3", 0x200000, 0x14cb1703, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "208-c4.c4", 0x200000, 0xc7165f19, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( sdodgeb, neogeo, "Super Dodge Ball / Kunio no Nekketsu Toukyuu Densetsu", TECHNOS, 1996, GAME_SPORTS);

static struct ROM_INFO rom_goalx3[] = /* MVS ONLY RELEASE */
{
  { "209-p1.p1", 0x100000, 0x2a019a79, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "209-p1.p1", 0x100000 , 0x2a019a79, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "209-s1.s1", 0x20000, 0xc0eaad86, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "209-m1.m1", 0x20000, 0xcd758325, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "209-v1.v1", 0x200000, 0xef214212, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "209-c1.c1", 0x400000, 0xb49d980e, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "209-c2.c2", 0x400000, 0x5649b015, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "209-c3.c3", 0x100000, 0x5f91bace, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "209-c4.c4", 0x100000, 0x1e9f76f2, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( goalx3, neogeo, "Goal! Goal! Goal!", VISCO, 1995, GAME_SPORTS);

static struct ROM_INFO rom_overtop[] = // clone of neogeo
{
  { "212-p1.p1", 0x100000, 0x16c063a9, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "212-p1.p1", 0x100000 , 0x16c063a9, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "212-s1.s1", 0x20000, 0x481d3ddc, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "212-m1.m1", 0x20000, 0xfcab6191, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "212-v1.v1", 0x400000, 0x013d4ef9, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "212-c1.c1", 0x400000, 0x50f43087, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "212-c2.c2", 0x400000, 0xa5b39807, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "212-c3.c3", 0x400000, 0x9252ea02, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "212-c4.c4", 0x400000, 0x5f41a699, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "212-c5.c5", 0x200000, 0xfc858bef, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "212-c6.c6", 0x200000, 0x0589c15e, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( overtop, neogeo,"Over Top", ADK, 1996, GAME_MISC);

static struct ROM_INFO rom_neodrift[] = /* MVS ONLY RELEASE */
{
  { "213-p1.p1", 0x100000, 0xe397d798, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "213-p1.p1", 0x100000, 0xe397d798, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "213-s1.s1", 0x20000, 0xb76b61bc, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "213-m1.m1", 0x20000, 0x200045f1, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "213-v1.v1", 0x200000, 0xa421c076, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "213-v2.v2", 0x200000, 0x233c7dd9, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "213-c1.c1", 0x400000, 0x3edc8bd3, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "213-c2.c2", 0x400000, 0x46ae5f16, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( neodrift, neogeo, "Neo Drift Out - New Technology", VISCO, 1996, GAME_RACE);

static struct ROM_INFO rom_kof96[] = /* MVS VERSION clone of neogeo */
{
  { "214-p1.p1", 0x100000, 0x52755d74, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "214-p2.sp2", 0x200000, 0x002ccb73, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "214-s1.s1", 0x20000, 0x1254cbdb, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "214-m1.m1", 0x20000, 0xdabc427c, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "214-v1.v1", 0x400000, 0x63f7b045, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "214-v2.v2", 0x400000, 0x25929059, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "214-v3.v3", 0x200000, 0x92a2257d, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "214-c1.c1", 0x400000, 0x7ecf4aa2, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "214-c2.c2", 0x400000, 0x05b54f37, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "214-c3.c3", 0x400000, 0x64989a65, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "214-c4.c4", 0x400000, 0xafbea515, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "214-c5.c5", 0x400000, 0x2a3bbd26, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "214-c6.c6", 0x400000, 0x44d30dc7, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "214-c7.c7", 0x400000, 0x3687331b, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "214-c8.c8", 0x400000, 0xfa1461ad, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof96, neogeo, "The King of Fighters '96 (NGM-214)", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_kof96h[] = // clone of kof96
{
  { "214-pg1.p1", 0x100000, 0xbd3757c9, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "214-p2.sp2", 0x200000, 0x002ccb73, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof96h, kof96, "The King of Fighters '96 (NGH-214)", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_ssideki4[] = // clone of neogeo
{
  { "215-p1.p1", 0x100000, 0x519b4ba3, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "215-p1.p1", 0x100000 , 0x519b4ba3, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "215-s1.s1", 0x20000, 0xf0fe5c36, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "215-m1.m1", 0x20000, 0xa932081d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "215-v1.v1", 0x400000, 0x877d1409, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "215-v2.v2", 0x200000, 0x1bfa218b, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "215-c1.c1", 0x400000, 0x8ff444f5, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "215-c2.c2", 0x400000, 0x5b155037, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "215-c3.c3", 0x400000, 0x456a073a, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "215-c4.c4", 0x400000, 0x43c182e1, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "215-c5.c5", 0x200000, 0x0c6f97ec, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "215-c6.c6", 0x200000, 0x329c5e1b, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ssideki4, neogeo, "The Ultimate 11 - The SNK Football Championship / Tokuten Ou - Honoo no Libero", SNK, 1996, GAME_SPORTS);

static struct ROM_INFO rom_kizuna[] = // clone of neogeo
{
  { "216-p1.p1", 0x100000, 0x75d2b3de, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "216-p1.p1", 0x100000, 0x75d2b3de, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "216-s1.s1", 0x20000, 0xefdc72d7, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "216-m1.m1", 0x20000, 0x1b096820, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "059-v1.v1", 0x200000, 0x530c50fd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "216-v2.v2", 0x200000, 0x03667a8d, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "059-v3.v3", 0x200000, 0x7038c2f9, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "216-v4.v4", 0x200000, 0x31b99bd6, REGION_SMP1, 0x600000, LOAD_NORMAL },
  { "059-c1.c1", 0x200000, 0x763ba611, REGION_SPRITES, 0x0000000, LOAD_8_16 },
	/* 400000-7fffff empty */
  { "059-c2.c2", 0x200000, 0xe05e8ca6, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "216-c3.c3", 0x400000, 0x665c9f16, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "216-c4.c4", 0x400000, 0x7f5d03db, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "059-c5.c5", 0x200000, 0x59013f9e, REGION_SPRITES, 0x1000000, LOAD_8_16 },
	/* 1400000-17fffff empty */
  { "059-c6.c6", 0x200000, 0x1c8d5def, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "059-c7.c7", 0x200000, 0xc88f7035, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "059-c8.c8", 0x200000, 0x484ce3ba, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kizuna, neogeo, "Kizuna Encounter - Super Tag Battle / Fu'un Super Tag Battle", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_ninjamas[] =
{
  { "217-p1.p1", 0x100000, 0x3e97ed69, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "217-p2.sp2", 0x200000, 0x191fca88, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "217-s1.s1", 0x20000, 0x8ff782f0, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "217-m1.m1", 0x20000, 0xd00fb2af, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "217-v1.v1", 0x400000, 0x1c34e013, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "217-v2.v2", 0x200000, 0x22f1c681, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "217-c1.c1", 0x400000, 0x5fe97bc4, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "217-c2.c2", 0x400000, 0x886e0d66, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "217-c3.c3", 0x400000, 0x59e8525f, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "217-c4.c4", 0x400000, 0x8521add2, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "217-c5.c5", 0x400000, 0xfb1896e5, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "217-c6.c6", 0x400000, 0x1c98c54b, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "217-c7.c7", 0x400000, 0x8b0ede2e, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "217-c8.c8", 0x400000, 0xa085bb61, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ninjamas, neogeo, "Ninja Master's - haoh-ninpo-cho", ADK, 1996, GAME_BEAT);

static struct ROM_INFO rom_ragnagrd[] =
{
  { "218-p1.p1", 0x100000, 0xca372303, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "218-p1.p1", 0x100000 , 0xca372303, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "218-s1.s1", 0x20000, 0x7d402f9a, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "218-m1.m1", 0x20000, 0x17028bcf, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "218-v1.v1", 0x400000, 0x61eee7f4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "218-v2.v2", 0x400000, 0x6104e20b, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "218-c1.c1", 0x400000, 0xc31500a4, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "218-c2.c2", 0x400000, 0x98aba1f9, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "218-c3.c3", 0x400000, 0x833c163a, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "218-c4.c4", 0x400000, 0xc1a30f69, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "218-c5.c5", 0x400000, 0x6b6de0ff, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "218-c6.c6", 0x400000, 0x94beefcf, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "218-c7.c7", 0x400000, 0xde6f9b28, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "218-c8.c8", 0x400000, 0xd9b311f6, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ragnagrd, neogeo, "Ragnagard / Shin-Oh-Ken", SAURUS, 1996, GAME_BEAT);

static struct ROM_INFO rom_pgoal[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "219-p1.p1", 0x100000, 0x6af0e574, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "219-p1.p1", 0x100000 , 0x6af0e574, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "219-s1.s1", 0x20000, 0x002f3c88, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "219-m1.m1", 0x20000, 0x958efdc8, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "219-v1.v1", 0x400000, 0xd0ae33d9, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "219-c1.c1", 0x400000, 0x67fec4dc, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "219-c2.c2", 0x400000, 0x86ed01f2, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "219-c3.c3", 0x200000, 0x5fdad0a5, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "219-c4.c4", 0x200000, 0xf57b4a1c, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( pgoal, neogeo, "Pleasure Goal / Futsal - 5 on 5 Mini Soccer (NGM-219)", SAURUS, 1996, GAME_SPORTS);

static struct ROM_INFO rom_ironclad[] = /* Prototype - crcs should match the ones of the unreleased dump. clone of neogeo */
{
  { "proto_220-p1.p1", 0x100000, 0x62a942c6, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "proto_220-p1.p1", 0x100000 , 0x62a942c6, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "proto_220-s1.s1", 0x20000, 0x372fe217, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "proto_220-m1.m1", 0x20000, 0x3a08bb63, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "proto_220-v1.v1", 0x400000, 0x8f30a215, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "proto_220-c1.c1", 0x400000, 0x9aa2b7dc, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "proto_220-c2.c2", 0x400000, 0x8a2ad708, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "proto_220-c3.c3", 0x400000, 0xd67fb15a, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "proto_220-c4.c4", 0x400000, 0xe73ea38b, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ironclad, neogeo, "Iron clad - Choutetsu Brikin'ger (Prototype)", SAURUS, 1996, GAME_SHOOT);

static struct ROM_INFO rom_ironclado[] = /* Prototype - bootleg/hack based on later release. clone of ironclad */
{
  { "proto_220-p1o.p1", 0x100000, 0xce37e3a0, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "proto_220-p1o.p1", 0x100000 , 0xce37e3a0, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ironclado, ironclad, "Iron clad - Choutetsu Brikin'ger (Prototype, bootleg)", BOOTLEG, 1996, GAME_SHOOT);

static struct ROM_INFO rom_magdrop2[] =
{
  { "221-p1.p1", 0x80000, 0x7be82353, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "221-s1.s1", 0x20000, 0x2a4063a3, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "221-m1.m1", 0x20000, 0xbddae628, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "221-v1.v1", 0x200000, 0x7e5e53e4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "221-c1.c1", 0x400000, 0x1f862a14, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "221-c2.c2", 0x400000, 0x14b90536, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( magdrop2, neogeo, "Magical Drop II", DECO, 1996, GAME_PUZZLE);

static struct ROM_INFO rom_samsho4[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "222-p1.p1", 0x100000, 0x1a5cb56d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "222-p2.sp2", 0x400000, 0xb023cd8b, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "222-s1.s1", 0x20000, 0x8d3d3bf9, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "222-m1.m1", 0x20000, 0x7615bc1b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "222-v1.v1", 0x400000, 0x7d6ba95f, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "222-v2.v2", 0x400000, 0x6c33bb5d, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "222-v3.v3", 0x200000, 0x831ea8c0, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "222-c1.c1", 0x400000, 0x68f2ed95, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "222-c2.c2", 0x400000, 0xa6e9aff0, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "222-c3.c3", 0x400000, 0xc91b40f4, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "222-c4.c4", 0x400000, 0x359510a4, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "222-c5.c5", 0x400000, 0x9cfbb22d, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "222-c6.c6", 0x400000, 0x685efc32, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "222-c7.c7", 0x400000, 0xd0f86f0d, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "222-c8.c8", 0x400000, 0xadfc50e3, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho4, neogeo, "Samurai Shodown IV - Amakusa's Revenge / Samurai Spirits - Amakusa Kourin (NGM-222)(NGH-222)", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_samsho4k[] = /* KOREAN VERSION clone of samsho4 */
{
  { "222-p1k.p1", 0x100000, 0x06e0a25d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "222-p2.sp2", 0x400000, 0xb023cd8b, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "222-s1k.s1", 0x20000, 0xd313687d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho4k, samsho4, "Pae Wang Jeon Seol / Legend of a Warrior (Korean censored Samurai Shodown IV)", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_rbffspec[] = // clone of neogeo
{
  { "223-p1.p1", 0x100000, 0xf84a2d1d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "223-p2.sp2", 0x400000, 0xaddd8f08, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "223-s1.s1", 0x20000, 0x7ecd6e8c, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "223-m1.m1", 0x20000, 0x3fee46bf, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "223-v1.v1", 0x400000, 0x76673869, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "223-v2.v2", 0x400000, 0x7a275acd, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "223-v3.v3", 0x400000, 0x5a797fd2, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "223-c1.c1", 0x400000, 0xebab05e2, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "223-c2.c2", 0x400000, 0x641868c3, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "223-c3.c3", 0x400000, 0xca00191f, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "223-c4.c4", 0x400000, 0x1f23d860, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "223-c5.c5", 0x400000, 0x321e362c, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "223-c6.c6", 0x400000, 0xd8fcef90, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "223-c7.c7", 0x400000, 0xbc80dd2d, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "223-c8.c8", 0x400000, 0x5ad62102, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( rbffspec, neogeo, "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special", SNK, 1996, GAME_BEAT);

static struct ROM_INFO rom_twinspri[] = // clone of neogeo
{
  { "224-p1.p1", 0x100000, 0x7697e445, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "224-p1.p1", 0x100000 , 0x7697e445, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "224-s1.s1", 0x20000, 0xeeed5758, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "224-m1.m1", 0x20000, 0x364d6f96, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "224-v1.v1", 0x400000, 0xff57f088, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "224-v2.v2", 0x200000, 0x7ad26599, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "224-c1.c1", 0x400000, 0xf7da64ab, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "224-c2.c2", 0x400000, 0x4c09bbfb, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "224-c3.c3", 0x100000, 0xc59e4129, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "224-c4.c4", 0x100000, 0xb5532e53, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( twinspri, neogeo,        "Twinkle Star Sprites", ADK, 1996, GAME_SHOOT);

static struct ROM_INFO rom_wakuwak7[] =
{
  { "225-p1.p1", 0x100000, 0xb14da766, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "225-p2.sp2", 0x200000, 0xfe190665, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "225-s1.s1", 0x20000, 0x71c4b4b5, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "225-m1.m1", 0x20000, 0x0634bba6, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "225-v1.v1", 0x400000, 0x6195c6b4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "225-v2.v2", 0x400000, 0x6159c5fe, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "225-c1.c1", 0x400000, 0xee4fea54, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "225-c2.c2", 0x400000, 0x0c549e2d, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "225-c3.c3", 0x400000, 0xaf0897c0, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "225-c4.c4", 0x400000, 0x4c66527a, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "225-c5.c5", 0x400000, 0x8ecea2b5, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "225-c6.c6", 0x400000, 0x0eb11a6d, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( wakuwak7, neogeo, "Waku Waku 7", SUNSOFT, 1996, GAME_BEAT);

static struct ROM_INFO rom_stakwin2[] =
{
  { "227-p1.p1", 0x100000, 0xdaf101d2, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "227-p1.p1", 0x100000 , 0xdaf101d2, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "227-s1.s1", 0x20000, 0x2a8c4462, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "227-m1.m1", 0x20000, 0xc8e5e0f9, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "227-v1.v1", 0x400000, 0xb8f24181, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "227-v2.v2", 0x400000, 0xee39e260, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "227-c1.c1", 0x400000, 0x7d6c2af4, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "227-c2.c2", 0x400000, 0x7e402d39, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "227-c3.c3", 0x200000, 0x93dfd660, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "227-c4.c4", 0x200000, 0x7efea43a, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( stakwin2, neogeo, "Stakes Winner 2", SAURUS, 1996, GAME_SPORTS);

static struct ROM_INFO rom_ghostlop[] = /* Prototype clone of neogeo */
{
  { "proto_228-p1.p1", 0x100000, 0x6033172e, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "proto_228-s1.s1", 0x20000, 0x83c24e81, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "proto_228-m1.m1", 0x20000, 0xfd833b33, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "proto_228-v1.v1", 0x200000, 0xc603fce6, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "proto_228-c1.c1", 0x400000, 0xbfc99efe, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "proto_228-c2.c2", 0x400000, 0x69788082, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ghostlop, neogeo, "Ghostlop (prototype)", DECO, 1996, GAME_PUZZLE);

static struct ROM_INFO rom_breakers[] = // clone of neogeo
{
  { "230-p1.p1", 0x100000, 0xed24a6e6, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "230-p1.p1", 0x100000 , 0xed24a6e6, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "230-s1.s1", 0x20000, 0x076fb64c, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "230-m1.m1", 0x20000, 0x3951a1c1, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "230-v1.v1", 0x400000, 0x7f9ed279, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "230-v2.v2", 0x400000, 0x1d43e420, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "230-c1.c1", 0x400000, 0x68d4ae76, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "230-c2.c2", 0x400000, 0xfdee05cd, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "230-c3.c3", 0x400000, 0x645077f3, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "230-c4.c4", 0x400000, 0x63aeb74c, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( breakers, neogeo, "Breakers", VISCO, 1996, GAME_BEAT);

static struct ROM_INFO rom_miexchng[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "231-p1.p1", 0x80000, 0x61be1810, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "231-s1.s1", 0x20000, 0xfe0c0c53, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "231-m1.m1", 0x20000, 0xde41301b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "231-v1.v1", 0x400000, 0x113fb898, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "231-c1.c1", 0x200000, 0x6c403ba3, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "231-c2.c2", 0x200000, 0x554bcd9b, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "231-c3.c3", 0x100000, 0x4f6f7a63, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "231-c4.c4", 0x100000, 0x2e35e71b, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( miexchng, neogeo, "Money Puzzle Exchanger / Money Idol Exchanger", FACE, 1997, GAME_PUZZLE);

static struct ROM_INFO rom_kof97[] = /* MVS VERSION clone of neogeo */
{
  { "232-p1.p1", 0x100000, 0x7db81ad9, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "232-p2.sp2", 0x400000, 0x158b23f6, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "232-s1.s1", 0x20000, 0x8514ecf5, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "232-m1.m1", 0x20000, 0x45348747, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "232-v1.v1", 0x400000, 0x22a2b5b5, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "232-v2.v2", 0x400000, 0x2304e744, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "232-v3.v3", 0x400000, 0x759eb954, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "232-c1.c1", 0x800000, 0x5f8bf0a1, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "232-c2.c2", 0x800000, 0xe4d45c81, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "232-c3.c3", 0x800000, 0x581d6618, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "232-c4.c4", 0x800000, 0x49bb1e68, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "232-c5.c5", 0x400000, 0x34fc4e51, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "232-c6.c6", 0x400000, 0x4ff4d47b, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof97, neogeo, "The King of Fighters '97 (NGM-2320)", SNK, 1997, GAME_BEAT);

static struct ROM_INFO rom_kof97h[] = /* AES VERSION clone of kof97 */
{
  { "232-pg1.p1", 0x100000, 0x5c2400b7, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "232-p2.sp2", 0x400000, 0x158b23f6, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof97h, kof97, "The King of Fighters '97 (NGH-2320)", SNK, 1997, GAME_BEAT);

static struct ROM_INFO rom_magdrop3[] = // clone of neogeo
{
  { "233-p1.p1", 0x100000, 0x931e17fa, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "233-s1.s1", 0x20000, 0x7399e68a, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "233-m1.m1", 0x20000, 0x5beaf34e, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "233-v1.v1", 0x400000, 0x58839298, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "233-v2.v2", 0x080000, 0xd5e30df4, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "233-c1.c1", 0x400000, 0x65e3f4c4, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "233-c2.c2", 0x400000, 0x35dea6c9, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "233-c3.c3", 0x400000, 0x0ba2c502, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "233-c4.c4", 0x400000, 0x70dbbd6d, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( magdrop3, neogeo, "Magical Drop III", DECO, 1997, GAME_PUZZLE);

static struct ROM_INFO rom_lastblad[] = /* MVS VERSION clone of neogeo */
{
  { "234-p1.p1", 0x100000, 0xe123a5a3, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "234-p2.sp2", 0x400000, 0x0fdc289e, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "234-s1.s1", 0x20000, 0x95561412, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "234-m1.m1", 0x20000, 0x087628ea, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "234-v1.v1", 0x400000, 0xed66b76f, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "234-v2.v2", 0x400000, 0xa0e7f6e2, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "234-v3.v3", 0x400000, 0xa506e1e2, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "234-v4.v4", 0x400000, 0x0e34157f, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "234-c1.c1", 0x800000, 0x9f7e2bd3, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "234-c2.c2", 0x800000, 0x80623d3c, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "234-c3.c3", 0x800000, 0x91ab1a30, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "234-c4.c4", 0x800000, 0x3d60b037, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "234-c5.c5", 0x400000, 0x1ba80cee, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "234-c6.c6", 0x400000, 0xbeafd091, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_lastbladh[] = /* AES VERSION clone of lastblad */
{
  { "234-pg1.p1", 0x100000, 0xcd01c06d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "234-p2.sp2", 0x400000, 0x0fdc289e, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( lastblad, neogeo, "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (NGM-2340)", SNK, 1997, GAME_BEAT);
CLNEI( lastbladh, lastblad, "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (NGH-2340)", SNK, 1997, GAME_BEAT);

static struct ROM_INFO rom_puzzldpr[] = /* MVS ONLY RELEASE clone of puzzledp */
{
  { "235-p1.p1", 0x080000, 0xafed5de2, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "235-s1.s1", 0x10000, 0x5a68d91e, REGION_FIXED, 0x000000, LOAD_NORMAL },
  FILL(          0x10000, 0x10000, 0, FIXED),
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( puzzldpr, puzzledp, "Puzzle De Pon! R!", TAITO, 1997, GAME_PUZZLE);

static struct ROM_INFO rom_irrmaze[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "236-p1.p1", 0x100000, 0x4c2ff660, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "236-p1.p1", 0x100000 , 0x4c2ff660, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "236-s1.s1", 0x20000, 0x5d1ca640, REGION_FIXED, 0x000000, LOAD_NORMAL },
	/* special BIOS with trackball support, we only have one Irritating Maze bios and thats asia */
  { "236-m1.m1", 0x20000, 0x880a1abd, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "236-v1.v1", 0x200000, 0x5f89c3b4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "236-v2.v2", 0x100000, 0x1e843567, REGION_YMSND_DELTAT, 0x000000, LOAD_NORMAL },
  { "236-c1.c1", 0x400000, 0xc1d47902, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "236-c2.c2", 0x400000, 0xe15f972e, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( irrmaze, neogeo, "The Irritating Maze / Ultra Denryu Iraira Bou", SNK, 1997, GAME_PUZZLE,
	.input = input_irrmaze);

static struct ROM_INFO rom_popbounc[] = /* MVS ONLY RELEASE */
{
  { "237-p1.p1", 0x100000, 0xbe96e44f, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "237-s1.s1", 0x20000, 0xb61cf595, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "237-m1.m1", 0x20000, 0xd4c946dd, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "237-v1.v1", 0x200000, 0xedcb1beb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "237-c1.c1", 0x200000, 0xeda42d66, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "237-c2.c2", 0x200000, 0x5e633c65, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( popbounc, neogeo, "Pop 'n Bounce / Gapporin", VIDEOSYSTEM, 1997, GAME_BREAKOUT,
	.input = input_popbounc);

static struct ROM_INFO rom_shocktro[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "238-p1.p1", 0x100000, 0x5677456f, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "238-p2.sp2", 0x400000, 0x5b4a09c5, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "238-s1.s1", 0x20000, 0x1f95cedb, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "238-m1.m1", 0x20000, 0x075b9518, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "238-v1.v1", 0x400000, 0x260c0bef, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "238-v2.v2", 0x200000, 0x4ad7d59e, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "238-c1.c1", 0x400000, 0x90c6a181, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "238-c2.c2", 0x400000, 0x888720f0, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "238-c3.c3", 0x400000, 0x2c393aa3, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "238-c4.c4", 0x400000, 0xb9e909eb, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "238-c5.c5", 0x400000, 0xc22c68eb, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "238-c6.c6", 0x400000, 0x119323cd, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "238-c7.c7", 0x400000, 0xa72ce7ed, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "238-c8.c8", 0x400000, 0x1c7c2efb, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( shocktro, neogeo, "Shock Troopers (set 1)", SAURUS, 1997, GAME_SHOOT);

static struct ROM_INFO rom_blazstar[] = // clone of neogeo
{
  { "239-p1.p1", 0x100000, 0x183682f8, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "239-p2.sp2", 0x200000, 0x9a9f4154, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "239-s1.s1", 0x20000, 0xd56cb498, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "239-m1.m1", 0x20000, 0xd31a3aea, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "239-v1.v1", 0x400000, 0x1b8d5bf7, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "239-v2.v2", 0x400000, 0x74cf0a70, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "239-c1.c1", 0x400000, 0x84f6d584, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "239-c2.c2", 0x400000, 0x05a0cb22, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "239-c3.c3", 0x400000, 0x5fb69c9e, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "239-c4.c4", 0x400000, 0x0be028c4, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "239-c5.c5", 0x400000, 0x74bae5f8, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "239-c6.c6", 0x400000, 0x4e0700d2, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "239-c7.c7", 0x400000, 0x010ff4fd, REGION_SPRITES, 0x1800000, LOAD_8_16 },
  { "239-c8.c8", 0x400000, 0xdb60460e, REGION_SPRITES, 0x1800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( blazstar, neogeo, "Blazing Star", YUMEKOBO, 1998, GAME_SHOOT);

static struct ROM_INFO rom_rbff2[] = /* MVS VERSION clone of neogeo */
{
  { "240-p1.p1", 0x100000, 0x80e41205, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "240-p2.sp2", 0x400000, 0x960aa88d, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "240-s1.s1", 0x20000, 0xda3b40de, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "240-m1.m1", 0x40000, 0xed482791, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "240-v1.v1", 0x400000, 0xf796265a, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "240-v2.v2", 0x400000, 0x2cb3f3bb, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "240-v3.v3", 0x400000, 0x8fe1367a, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "240-v4.v4", 0x200000, 0x996704d8, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "240-c1.c1", 0x800000, 0xeffac504, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "240-c2.c2", 0x800000, 0xed182d44, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "240-c3.c3", 0x800000, 0x22e0330a, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "240-c4.c4", 0x800000, 0xc19a07eb, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "240-c5.c5", 0x800000, 0x244dff5a, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "240-c6.c6", 0x800000, 0x4609e507, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_rbff2h[] = /* AES VERSION clone of rbff2 */
{
  { "240-pg1.p1", 0x100000, 0xb6969780, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "240-p2.sp2", 0x400000, 0x960aa88d, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( rbff2, neogeo, "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - the newcomers (NGM-2400)", SNK, 1998, GAME_BEAT);
CLNEI( rbff2h, rbff2, "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - the newcomers (NGH-2400)", SNK, 1998, GAME_BEAT);

static struct ROM_INFO rom_mslug2[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "241-p1.p1", 0x100000, 0x2a53c5da, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "241-p2.sp2", 0x200000, 0x38883f44, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "241-s1.s1", 0x20000, 0xf3d32f0f, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "241-m1.m1", 0x20000, 0x94520ebd, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "241-v1.v1", 0x400000, 0x99ec20e8, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "241-v2.v2", 0x400000, 0xecb16799, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "241-c1.c1", 0x800000, 0x394b5e0d, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "241-c2.c2", 0x800000, 0xe5806221, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "241-c3.c3", 0x800000, 0x9f6bfa6f, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "241-c4.c4", 0x800000, 0x7d3e306f, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug2, neogeo, "Metal Slug 2 - Super Vehicle-001/II (NGM-2410)(NGH-2410)", SNK, 1998, GAME_SHOOT);

static struct ROM_INFO rom_kof98[] = /* encrypted code + protection clone of neogeo */
 /* MVS VERSION */{
  { "242-p1.p1", 0x200000, 0x8893df89, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "242-p2.sp2", 0x400000, 0x980aba4c, REGION_CPU1, 0x200000, LOAD_SWAP_16 },
  { "242-s1.s1", 0x20000, 0x7f7b4805, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "242-m1.m1", 0x40000, 0x4ef7016b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "242-v1.v1", 0x400000, 0xb9ea8051, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "242-v2.v2", 0x400000, 0xcc11106e, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "242-v3.v3", 0x400000, 0x044ea4e1, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "242-v4.v4", 0x400000, 0x7985ea30, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "242-c1.c1", 0x800000, 0xe564ecd6, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "242-c2.c2", 0x800000, 0xbd959b60, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "242-c3.c3", 0x800000, 0x22127b4f, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "242-c4.c4", 0x800000, 0x0b4fa044, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "242-c5.c5", 0x800000, 0x9d10bed3, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "242-c6.c6", 0x800000, 0xda07b6a2, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "242-c7.c7", 0x800000, 0xf6d7a38a, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "242-c8.c8", 0x800000, 0xc823e045, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof98, neogeo, "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGM-2420)", SNK, 1998, GAME_BEAT);

static struct ROM_INFO rom_kof98h[] = /* AES VERSION clone of kof98 */
{
  { "242-pn1.p1", 0x100000, 0x61ac868a, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "242-p2.sp2", 0x400000, 0x980aba4c, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "242-mg1.m1", 0x40000, 0x4e7a6b1b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof98h, kof98, "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGH-2420)", SNK, 1998, GAME_BEAT);

static struct ROM_INFO rom_lastbld2[] = /* MVS AND AES VERSION clone of neogeo */
 /* later revision */{
  { "243-pg1.p1", 0x100000, 0xaf1e6554, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "243-pg2.sp2", 0x400000, 0xadd4a30b, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "243-s1.s1", 0x20000, 0xc9cd2298, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "243-m1.m1", 0x20000, 0xacf12d10, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "243-v1.v1", 0x400000, 0xf7ee6fbb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "243-v2.v2", 0x400000, 0xaa9e4df6, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "243-v3.v3", 0x400000, 0x4ac750b2, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "243-v4.v4", 0x400000, 0xf5c64ba6, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "243-c1.c1", 0x800000, 0x5839444d, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "243-c2.c2", 0x800000, 0xdd087428, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "243-c3.c3", 0x800000, 0x6054cbe0, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "243-c4.c4", 0x800000, 0x8bd2a9d2, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "243-c5.c5", 0x800000, 0x6a503dcf, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "243-c6.c6", 0x800000, 0xec9c36d0, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( lastbld2, neogeo, "The Last Blade 2 / Bakumatsu Roman - Dai Ni Maku Gekka no Kenshi (NGM-2430)(NGH-2430)", SNK, 1998, GAME_BEAT);

static struct ROM_INFO rom_neocup98[] = // clone of neogeo
{
  { "244-p1.p1", 0x100000, 0xf8fdb7a5, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "244-p1.p1", 0x100000 , 0xf8fdb7a5, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "244-s1.s1", 0x20000, 0x9bddb697, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "244-m1.m1", 0x20000, 0xa701b276, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "244-v1.v1", 0x400000, 0x79def46d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "244-v2.v2", 0x200000, 0xb231902f, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "244-c1.c1", 0x800000, 0xc7a62b23, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "244-c2.c2", 0x800000, 0x33aa0f35, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( neocup98, neogeo, "Neo-Geo Cup '98 - The Road to the Victory", SNK, 1998, GAME_SPORTS);

static struct ROM_INFO rom_breakrev[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "245-p1.p1", 0x100000, 0xc828876d, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "245-p1.p1", 0x100000 , 0xc828876d, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "245-s1.s1", 0x20000, 0xe7660a5d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "245-m1.m1", 0x20000, 0x00f31c66, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "245-v1.v1", 0x400000, 0xe255446c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "245-v2.v2", 0x400000, 0x9068198a, REGION_SMP1, 0x400000, LOAD_NORMAL },
	/* The chip labels and sizes are correct */
  { "245-c1.c1", 0x400000, 0x68d4ae76, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "245-c2.c2", 0x400000, 0xfdee05cd, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "245-c3.c3", 0x400000, 0x645077f3, REGION_SPRITES, 0x0800000, LOAD_8_16 },
  { "245-c4.c4", 0x400000, 0x63aeb74c, REGION_SPRITES, 0x0800001, LOAD_8_16 },
  { "245-c5.c5", 0x400000, 0xb5f40e7f, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "245-c6.c6", 0x400000, 0xd0337328, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( breakrev, neogeo, "Breakers Revenge", VISCO, 1998, GAME_BEAT);

static struct ROM_INFO rom_shocktr2[] = // clone of neogeo
{
  { "246-p1.p1", 0x100000, 0x6d4b7781, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "246-p2.sp2", 0x400000, 0x72ea04c3, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "246-s1.s1", 0x20000, 0x2a360637, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "246-m1.m1", 0x20000, 0xd0604ad1, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "246-v1.v1", 0x400000, 0x16986fc6, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "246-v2.v2", 0x400000, 0xada41e83, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "246-v3.v3", 0x200000, 0xa05ba5db, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "246-c1.c1", 0x800000, 0x47ac9ec5, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "246-c2.c2", 0x800000, 0x7bcab64f, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "246-c3.c3", 0x800000, 0xdb2f73e8, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "246-c4.c4", 0x800000, 0x5503854e, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "246-c5.c5", 0x800000, 0x055b3701, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "246-c6.c6", 0x800000, 0x7e2caae1, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( shocktr2, neogeo, "Shock Troopers - 2nd Squad", SAURUS, 1998, GAME_SHOOT);

static struct ROM_INFO rom_flipshot[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "247-p1.p1", 0x100000, 0x95779094, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "247-s1.s1", 0x20000, 0x6300185c, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "247-m1.m1", 0x20000, 0xa9fe0144, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "247-v1.v1", 0x200000, 0x42ec743d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "247-c1.c1", 0x200000, 0xc9eedcb2, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "247-c2.c2", 0x200000, 0x7d6d6e87, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( flipshot, neogeo, "Battle Flip Shot", VISCO, 1998, GAME_MISC);

static struct ROM_INFO rom_pbobbl2n[] = /* MVS ONLY RELEASE clone of neogeo */
{
  { "248-p1.p1", 0x100000, 0x9d6c0754, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "248-s1.s1", 0x20000, 0x0a3fee41, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "248-m1.m1", 0x20000, 0x883097a9, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "248-v1.v1", 0x400000, 0x57fde1fa, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "248-v2.v2", 0x400000, 0x4b966ef3, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "248-c1.c1", 0x400000, 0xd9115327, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "248-c2.c2", 0x400000, 0x77f9fdac, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "248-c3.c3", 0x100000, 0x8890bf7c, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "248-c4.c4", 0x100000, 0x8efead3f, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( pbobbl2n, neogeo, "Puzzle Bobble 2 / Bust-A-Move Again (Neo-Geo)", TAITO, 1999, GAME_PUZZLE);

static struct ROM_INFO rom_ctomaday[] = /* MVS ONLY RELEASE */
{
  { "249-p1.p1", 0x100000, 0xc9386118, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "249-p1.p1", 0x100000 , 0xc9386118, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "249-s1.s1", 0x20000, 0xdc9eb372, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "249-m1.m1", 0x20000, 0x80328a47, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "249-v1.v1", 0x400000, 0xde7c8f27, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "249-v2.v2", 0x100000, 0xc8e40119, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "249-c1.c1", 0x400000, 0x041fb8ee, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "249-c2.c2", 0x400000, 0x74f3cdf4, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ctomaday, neogeo, "Captain Tomaday", VISCO, 1999, GAME_SHOOT);

static struct ROM_INFO rom_mslugx[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "250-p1.p1", 0x100000, 0x81f1f60b, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "250-p2.ep1", 0x400000, 0x1fda2e12, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "250-s1.s1", 0x20000, 0xfb6f441d, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "250-m1.m1", 0x20000, 0xfd42a842, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "250-v1.v1", 0x400000, 0xc79ede73, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "250-v2.v2", 0x400000, 0xea9aabe1, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "250-v3.v3", 0x200000, 0x2ca65102, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "250-c1.c1", 0x800000, 0x09a52c6f, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "250-c2.c2", 0x800000, 0x31679821, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "250-c3.c3", 0x800000, 0xfd602019, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "250-c4.c4", 0x800000, 0x31354513, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "250-c5.c5", 0x800000, 0xa4b56124, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "250-c6.c6", 0x800000, 0x83e3e69d, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslugx, neogeo, "Metal Slug X - Super Vehicle-001 (NGM-2500)(NGH-2500)", SNK, 1999, GAME_SHOOT);

static struct ROM_INFO rom_kof99[] = /* Original Version - Encrypted Code & GFX clone of neogeo */
 /* MVS VERSION */{
  { "ka.neo-sma", 0x040000, 0x7766d09e, REGION_CPU1, 0x0c0000, LOAD_SWAP_16 },
  { "251-p1.p1", 0x400000, 0x006e4532, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "251-p2.p2", 0x400000, 0x90175f15, REGION_CPU1, 0x500000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
 FILL( 0x000000, 0x20000, 0, FIXED ),
  { "251-m1.m1", 0x20000, 0x5e74539c, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "251-v1.v1", 0x400000, 0xef2eecc8, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "251-v2.v2", 0x400000, 0x73e211ca, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "251-v3.v3", 0x400000, 0x821901da, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "251-v4.v4", 0x200000, 0xb49e6178, REGION_SMP1, 0xc00000, LOAD_NORMAL },
	/* Encrypted */
  { "251-c1.c1", 0x800000, 0x0f9e93fe, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "251-c2.c2", 0x800000, 0xe71e2ea3, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "251-c3.c3", 0x800000, 0x238755d2, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "251-c4.c4", 0x800000, 0x438c8b22, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "251-c5.c5", 0x800000, 0x0b0abd0a, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "251-c6.c6", 0x800000, 0x65bbf281, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "251-c7.c7", 0x800000, 0xff65f62e, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "251-c8.c8", 0x800000, 0x8d921c68, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof99, neogeo, "The King of Fighters '99 - Millennium Battle (NGM-2510)" , SNK, 1999, GAME_BEAT);

static struct ROM_INFO rom_kof99h[] = /* Original Version - Encrypted Code & GFX clone of kof99 */
 /* AES VERSION */{
  { "kc.neo-sma", 0x040000, 0x6c9d0647, REGION_CPU1, 0x0c0000, LOAD_SWAP_16 },
  { "251-p1.p1", 0x400000, 0x006e4532, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "251-pg2.p2", 0x400000, 0xd9057f51, REGION_CPU1, 0x500000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
/* Ignored : 	ROM_FILL( 0x000000, 0x20000, 0 ) */
	/* Encrypted */
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof99h, kof99, "The King of Fighters '99 - Millennium Battle (NGH-2510)" , SNK, 1999, GAME_BEAT);

static struct ROM_INFO rom_ganryu[] = /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
{
  { "252-p1.p1", 0x100000, 0x4b8ac4fb, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "252-p1.p1", 0x100000 , 0x4b8ac4fb, REGION_CPU1, 0x000000, LOAD_CONTINUE },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED),
  { "252-m1.m1", 0x20000, 0x30cc4099, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "252-v1.v1", 0x400000, 0xe5946733, REGION_SMP1, 0x000000, LOAD_NORMAL },
	/* Encrypted */
  { "252-c1.c1", 0x800000, 0x50ee7882, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "252-c2.c2", 0x800000, 0x62585474, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( ganryu, neogeo, "Ganryu / Musashi Ganryuki" , VISCO, 1999, GAME_BEAT);

static struct ROM_INFO rom_garou[] = /* Original Version - Encrypted GFX clone of neogeo */
 /* MVS VERSION - later revision */{
  { "kf.neo-sma", 0x040000, 0x98bc93dc, REGION_CPU1, 0x0c0000, LOAD_SWAP_16 },
  { "253-ep1.p1", 0x200000, 0xea3171a4, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "253-ep2.p2", 0x200000, 0x382f704b, REGION_CPU1, 0x300000, LOAD_SWAP_16 },
  { "253-ep3.p3", 0x200000, 0xe395bfdd, REGION_CPU1, 0x500000, LOAD_SWAP_16 },
  { "253-ep4.p4", 0x200000, 0xda92c08e, REGION_CPU1, 0x700000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED),
  { "253-m1.m1", 0x40000, 0x36a806be, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "253-v1.v1", 0x400000, 0x263e388c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "253-v2.v2", 0x400000, 0x2c6bc7be, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "253-v3.v3", 0x400000, 0x0425b27d, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "253-v4.v4", 0x400000, 0xa54be8a9, REGION_SMP1, 0xc00000, LOAD_NORMAL },
	/* Encrypted */
  { "253-c1.c1", 0x800000, 0x0603e046, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "253-c2.c2", 0x800000, 0x0917d2a4, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "253-c3.c3", 0x800000, 0x6737c92d, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "253-c4.c4", 0x800000, 0x5ba92ec6, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "253-c5.c5", 0x800000, 0x3eab5557, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "253-c6.c6", 0x800000, 0x308d098b, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "253-c7.c7", 0x800000, 0xc0e995ae, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "253-c8.c8", 0x800000, 0x21a11303, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( garou, neogeo, "Garou - Mark of the Wolves (NGM-2530)" , SNK, 1999, GAME_BEAT);

static struct ROM_INFO rom_garouh[] = /* Original Version - Encrypted GFX clone of garou */
 /* MVS AND AES VERSION - earlier revision */{
  { "ke.neo-sma", 0x040000, 0x96c72233, REGION_CPU1, 0x0c0000, LOAD_SWAP_16 },
  { "253-p1.p1", 0x400000, 0x18ae5d7e, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "253-p2.p2", 0x400000, 0xafffa779, REGION_CPU1, 0x500000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
/* Ignored : 	ROM_FILL( 0x000000, 0x20000, 0 ) */
	/* Encrypted */
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( garouh, garou, "Garou - Mark of the Wolves (NGM-2530)(NGH-2530)" , SNK, 1999, GAME_BEAT);

static struct ROM_INFO rom_s1945p[] = /* Original Version, Encrypted GFX Roms */ /* MVS ONLY RELEASE */
{
  { "254-p1.p1", 0x100000, 0xff8efcff, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "254-p2.sp2", 0x400000, 0xefdfd4dd, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED),
  { "254-m1.m1", 0x20000, 0x994b4487, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "254-v1.v1", 0x400000, 0x844f58fb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "254-v2.v2", 0x400000, 0xd9a248f0, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "254-v3.v3", 0x400000, 0x0b0d2d33, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "254-v4.v4", 0x400000, 0x6d13dc91, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "254-c1.c1", 0x800000, 0xae6fc8ef, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "254-c2.c2", 0x800000, 0x436fa176, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "254-c3.c3", 0x800000, 0xe53ff2dc, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "254-c4.c4", 0x800000, 0x818672f0, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "254-c5.c5", 0x800000, 0x4580eacd, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "254-c6.c6", 0x800000, 0xe34970fc, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "254-c7.c7", 0x800000, 0xf2323239, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "254-c8.c8", 0x800000, 0x66848c7d, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( s1945p, neogeo, "Strikers 1945 Plus" , PSIKYO, 1999, GAME_SHOOT);

static struct ROM_INFO rom_preisle2[] = /* Original Version, Encrypted GFX */ /* MVS ONLY RELEASE */
{
  { "255-p1.p1", 0x100000, 0xdfa3c0f3, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "255-p2.sp2", 0x400000, 0x42050b80, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0,FIXED ),
  { "255-m1.m1", 0x20000, 0x8efd4014, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "255-v1.v1", 0x400000, 0x5a14543d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "255-v2.v2", 0x200000, 0x6610d91a, REGION_SMP1, 0x400000, LOAD_NORMAL },
	/* Encrypted */
  { "255-c1.c1", 0x800000, 0xea06000b, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "255-c2.c2", 0x800000, 0x04e67d79, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "255-c3.c3", 0x800000, 0x60e31e08, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "255-c4.c4", 0x800000, 0x40371d69, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "255-c5.c5", 0x800000, 0x0b2e6adf, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "255-c6.c6", 0x800000, 0xb001bdd3, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( preisle2, neogeo, "Prehistoric Isle 2" , YUMEKOBO, 1999, GAME_SHOOT);

static struct ROM_INFO rom_mslug3[] = /* Original Version - Encrypted Code & GFX clone of neogeo */
 /* revision 2000.4.1 */ /* MVS VERSION */{
	/* The SMA for this release has a green colour marking; the older revision has a white colour marking */
  { "neo-sma", 0x040000, 0x9cd55736, REGION_CPU1, 0x0c0000, LOAD_SWAP_16 },
  { "256-pg1.p1", 0x400000, 0xb07edfd5, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "256-pg2.p2", 0x400000, 0x6097c26b, REGION_CPU1, 0x500000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
  { "256-m1.m1", 0x80000, 0xeaeec116, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "256-v1.v1", 0x400000, 0xf2690241, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "256-v2.v2", 0x400000, 0x7e2a10bd, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "256-v3.v3", 0x400000, 0x0eaec17c, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "256-v4.v4", 0x400000, 0x9b4b22d4, REGION_SMP1, 0xc00000, LOAD_NORMAL },
	/* Encrypted */
  { "256-c1.c1", 0x800000, 0x5a79c34e, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "256-c2.c2", 0x800000, 0x944c362c, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "256-c3.c3", 0x800000, 0x6e69d36f, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "256-c4.c4", 0x800000, 0xb755b4eb, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "256-c5.c5", 0x800000, 0x7aacab47, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "256-c6.c6", 0x800000, 0xc698fd5d, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "256-c7.c7", 0x800000, 0xcfceddd2, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "256-c8.c8", 0x800000, 0x4d9be34c, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug3, neogeo, "Metal Slug 3 (NGM-2560)" , SNK, 2000, GAME_SHOOT);

static struct ROM_INFO rom_mslug3h[] = /* Original Version - Encrypted GFX clone of mslug3 */
 /* revision 2000.3.17 */ /* AES VERSION */{
  { "256-ph1.p1", 0x100000, 0x9c42ca85, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "256-ph2.sp2", 0x400000, 0x1f3d8ce8, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug3h, mslug3, "Metal Slug 3 (NGH-2560)" , SNK, 2000, GAME_SHOOT);

static struct ROM_INFO rom_kof2000[] = /* Original Version, Encrypted Code + Sound + GFX Roms clone of neogeo */
 /* MVS AND AES VERSION */{
  { "neo-sma", 0x040000, 0x71c6e6bb, REGION_CPU1, 0x0c0000, LOAD_SWAP_16 },
  { "257-p1.p1", 0x400000, 0x60947b4c, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "257-p2.p2", 0x400000, 0x1b7ec415, REGION_CPU1, 0x500000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
	/* Encrypted */
  { "257-m1.m1", 0x40000, 0x4b749113, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
  FILL(0x40000,0x40000, 0, AUDIOCRYPT),

  { "257-v1.v1", 0x400000, 0x17cde847, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "257-v2.v2", 0x400000, 0x1afb20ff, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "257-v3.v3", 0x400000, 0x4605036a, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "257-v4.v4", 0x400000, 0x764bbd6b, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "257-c1.c1", 0x800000, 0xcef1cdfa, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "257-c2.c2", 0x800000, 0xf7bf0003, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "257-c3.c3", 0x800000, 0x101e6560, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "257-c4.c4", 0x800000, 0xbd2fc1b1, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "257-c5.c5", 0x800000, 0x89775412, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "257-c6.c6", 0x800000, 0xfa7200d5, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "257-c7.c7", 0x800000, 0x7da11fe4, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "257-c8.c8", 0x800000, 0xb1afa60b, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof2000, neogeo, "The King of Fighters 2000 (NGM-2570) (NGH-2570)" , SNK, 2000, GAME_BEAT);

static struct ROM_INFO rom_bangbead[] = /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
{
  { "259-p1.p1", 0x100000, 0x88a37f8b, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "259-p1.p1", 0x100000 , 0x88a37f8b, REGION_CPU1, 0x000000, LOAD_CONTINUE },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
  { "259-m1.m1", 0x20000, 0x85668ee9, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "259-v1.v1", 0x400000, 0x088eb8ab, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "259-v2.v2", 0x100000, 0x97528fe9, REGION_SMP1, 0x400000, LOAD_NORMAL },
	/* Encrypted */
  { "259-c1.c1", 0x800000, 0x1f537f74, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "259-c2.c2", 0x800000, 0x0efd98ff, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( bangbead, neogeo, "Bang Bead", VISCO, 2000, GAME_SPORTS);

static struct ROM_INFO rom_nitd[] = /* Original Version - Encrypted GFX */ /* MVS ONLY RELEASE */
{
  { "260-p1.p1", 0x080000, 0x61361082, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
  { "260-m1.m1", 0x80000, 0x6407c5e5, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "260-v1.v1", 0x400000, 0x24b0480c, REGION_SMP1, 0x000000, LOAD_NORMAL },
	/* Encrypted */
  { "260-c1.c1", 0x800000, 0x147b0c7f, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "260-c2.c2", 0x800000, 0xd2b04b0d, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( nitd, neogeo, "Nightmare in the Dark" , ELEVEN, 2000, GAME_PLATFORM);

static struct ROM_INFO rom_sengoku3[] = /* Original Version - Encrypted GFX */
{
  { "261-ph1.p1", 0x100000, 0xe0d4bc0a, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "261-ph1.p1", 0x100000 , 0xe0d4bc0a, REGION_CPU1, 0x000000, LOAD_CONTINUE },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0,FIXED ),
  { "261-m1.m1", 0x80000, 0x7d501c39, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "261-v1.v1", 0x400000, 0x64c30081, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "261-v2.v2", 0x400000, 0x392a9c47, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "261-v3.v3", 0x400000, 0xc1a7ebe3, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "261-v4.v4", 0x200000, 0x9000d085, REGION_SMP1, 0xc00000, LOAD_NORMAL },
  { "261-c1.c1", 0x800000, 0xded84d9c, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "261-c2.c2", 0x800000, 0xb8eb4348, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "261-c3.c3", 0x800000, 0x84e2034a, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "261-c4.c4", 0x800000, 0x0b45ae53, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( sengoku3, neogeo, "Sengoku 3 / Sengoku Densho 2001" , NOISE, 2001, GAME_BEAT);

static struct ROM_INFO rom_kof2001[] = /* MVS VERSION clone of neogeo */
{
  { "262-p1-08-e0.p1", 0x100000, 0x9381750d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* The first/early production run sets have proms with above labels. Some later? sets found have eproms instead of proms */
  { "262-p2-08-e0.sp2", 0x400000, 0x8e0d8329, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "265-262-m1.m1", 0x40000, 0xa7f8119f, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
  FILL(0x40000, 0x40000, 0, AUDIOCRYPT),
  { "262-v1-08-e0.v1", 0x400000, 0x83d49ecf, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "262-v2-08-e0.v2", 0x400000, 0x003f1843, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "262-v3-08-e0.v3", 0x400000, 0x2ae38dbe, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "262-v4-08-e0.v4", 0x400000, 0x26ec4dd9, REGION_SMP1, 0xc00000, LOAD_NORMAL },
	/* Encrypted */
  { "262-c1-08-e0.c1", 0x800000, 0x99cc785a, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "262-c2-08-e0.c2", 0x800000, 0x50368cbf, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "262-c3-08-e0.c3", 0x800000, 0xfb14ff87, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "262-c4-08-e0.c4", 0x800000, 0x4397faf8, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "262-c5-08-e0.c5", 0x800000, 0x91f24be4, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "262-c6-08-e0.c6", 0x800000, 0xa31e4403, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "262-c7-08-e0.c7", 0x800000, 0x54d9d1ec, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "262-c8-08-e0.c8", 0x800000, 0x59289a6b, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof2001, neogeo, "The King of Fighters 2001 (NGM-262?)" , EOLITH_S, 2001, GAME_BEAT);

static struct ROM_INFO rom_kof2001h[] = /* AES VERSION clone of kof2001 */
{
  { "262-pg1.p1", 0x100000, 0x2af7e741, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "262-pg2.sp2", 0x400000, 0x91eea062, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof2001h, kof2001, "The King of Fighters 2001 (NGH-2621)" , EOLITH_S, 2001, GAME_BEAT);

static struct ROM_INFO rom_mslug4[] = /* Original Version - Encrypted GFX clone of neogeo */
 /* MVS VERSION */{
  { "263-p1.p1", 0x100000, 0x27e4def3, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "263-p2.sp2", 0x400000, 0xfdb7aed8, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
	/* Encrypted */
  { "263-m1.m1", 0x20000, 0x46ac8228, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
  FILL(0x20000,0x60000,0,AUDIOCRYPT),
	/* Encrypted */
  { "263-v1.v1", 0x800000, 0x01e9b9cd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "263-v2.v2", 0x800000, 0x4ab2bf81, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "263-c1.c1", 0x800000, 0x84865f8a, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "263-c2.c2", 0x800000, 0x81df97f2, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "263-c3.c3", 0x800000, 0x1a343323, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "263-c4.c4", 0x800000, 0x942cfb44, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "263-c5.c5", 0x800000, 0xa748854f, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "263-c6.c6", 0x800000, 0x5c8ba116, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug4, neogeo, "Metal Slug 4 (NGM-2630)", MEGA_P, 2002, GAME_SHOOT);

static struct ROM_INFO rom_mslug4h[] = /* Original Version - Encrypted GFX clone of mslug4 */
 /* AES VERSION */{
  { "263-ph1.p1", 0x100000, 0xc67f5c8d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "263-ph2.sp2", 0x400000, 0xbc3ec89e, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug4h, mslug4, "Metal Slug 4 (NGH-2630)", MEGA_P, 2002, GAME_SHOOT);

static struct ROM_INFO rom_rotd[] = /* Encrypted Set clone of neogeo */
 /* MVS VERSION */{
  { "264-p1.p1", 0x800000, 0xb8cc969d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "264-m1.m1", 0x20000, 0x4dbd7b43, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
  FILL(0x20000,0x60000,0,AUDIOCRYPT),
	/* Encrypted */
  { "264-v1.v1", 0x800000, 0xfa005812, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "264-v2.v2", 0x800000, 0xc3dc8bf0, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "264-c1.c1", 0x800000, 0x4f148fee, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "264-c2.c2", 0x800000, 0x7cf5ff72, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "264-c3.c3", 0x800000, 0x64d84c98, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "264-c4.c4", 0x800000, 0x2f394a95, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "264-c5.c5", 0x800000, 0x6b99b978, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "264-c6.c6", 0x800000, 0x847d5c7d, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "264-c7.c7", 0x800000, 0x231d681e, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "264-c8.c8", 0x800000, 0xc5edb5c4, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( rotd, neogeo, "Rage of the Dragons (NGM-264?)", EVOGA_P, 2002, GAME_BEAT);

static struct ROM_INFO rom_kof2002[] = /* Encrypted Set clone of neogeo */
 /* MVS AND AES VERSION */{
  { "265-p1.p1", 0x100000, 0x9ede7323, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "265-p2.sp2", 0x400000, 0x327266b8, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "265-m1.m1", 0x20000, 0x85aaa632, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
  FILL( 0x20000, 0x60000, 0, AUDIOCRYPT ),
	/* Encrypted */
  { "265-v1.v1", 0x800000, 0x15e8f3f5, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "265-v2.v2", 0x800000, 0xda41d6f9, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "265-c1.c1", 0x800000, 0x2b65a656, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "265-c2.c2", 0x800000, 0xadf18983, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "265-c3.c3", 0x800000, 0x875e9fd7, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "265-c4.c4", 0x800000, 0x2da13947, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "265-c5.c5", 0x800000, 0x61bd165d, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "265-c6.c6", 0x800000, 0x03fdd1eb, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "265-c7.c7", 0x800000, 0x1a2749d8, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "265-c8.c8", 0x800000, 0xab0bb549, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof2002, neogeo, "The King of Fighters 2002 (NGM-2650)(NGH-2650)" , EOLITH_P, 2002, GAME_BEAT);

static struct ROM_INFO rom_matrim[] = /* Encrypted Set clone of neogeo */
 /* MVS AND AES VERSION */{
  { "266-p1.p1", 0x100000, 0x5d4c2dc7, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "266-p2.sp2", 0x400000, 0xa14b1906, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
	/* Encrypted */
  { "266-m1.m1", 0x20000, 0x456c3e6c, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
  FILL( 0x020000, 0x60000, 0, AUDIOCRYPT ),
	/* Encrypted */
  { "266-v1.v1", 0x800000, 0xa4f83690, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "266-v2.v2", 0x800000, 0xd0f69eda, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "266-c1.c1", 0x800000, 0x505f4e30, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "266-c2.c2", 0x800000, 0x3cb57482, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "266-c3.c3", 0x800000, 0xf1cc6ad0, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "266-c4.c4", 0x800000, 0x45b806b7, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "266-c5.c5", 0x800000, 0x9a15dd6b, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "266-c6.c6", 0x800000, 0x281cb939, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "266-c7.c7", 0x800000, 0x4b71f780, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "266-c8.c8", 0x800000, 0x29873d33, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( matrim, neogeo, "Matrimelee / Shin Gouketsuji Ichizoku Toukon (NGM-2660) (NGH-2660)", NOISE, 2002, GAME_BEAT);

static struct ROM_INFO rom_pnyaa[] = /* Encrypted Set */ /* MVS ONLY RELEASE */
{
  { "267-p1.p1", 0x100000, 0x112fe2c0, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "267-m1.m1", 0x80000, 0xc7853ccd, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "267-v1.v1", 0x400000, 0xe2e8e917, REGION_SMP1, 0x000000, LOAD_NORMAL },
	/* Encrypted */
  { "267-c1.c1", 0x800000, 0x5eebee65, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "267-c2.c2", 0x800000, 0x2b67187b, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( pnyaa, neogeo, "Pochi and Nyaa", AIKY, 2003, GAME_PUZZLE);

static struct ROM_INFO rom_mslug5[] = /* Encrypted Set clone of neogeo */
 /* MVS VERSION */{
  { "268-p1cr.p1", 0x400000, 0xd0466792, REGION_CPU1, 0x000000, LOAD32_SWAP_16 },
  { "268-p2cr.p2", 0x400000, 0xfbf6b61e, REGION_CPU1, 0x000002, LOAD32_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "268-m1.m1", 0x80000, 0x4a5a6e0e, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "268-v1c.v1", 0x800000, 0xae31d60c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "268-v2c.v2", 0x800000, 0xc40613ed, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "268-c1c.c1", 0x800000, 0xab7c389a, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "268-c2c.c2", 0x800000, 0x3560881b, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "268-c3c.c3", 0x800000, 0x3af955ea, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "268-c4c.c4", 0x800000, 0xc329c373, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "268-c5c.c5", 0x800000, 0x959c8177, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "268-c6c.c6", 0x800000, 0x010a831b, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "268-c7c.c7", 0x800000, 0x6d72a969, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "268-c8c.c8", 0x800000, 0x551d720e, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug5, neogeo, "Metal Slug 5 (NGM-2680)", SNK_PLAYMORE, 2003, GAME_SHOOT);

static struct ROM_INFO rom_mslug5h[] = /* Encrypted Set clone of mslug5 */
 /* AES release of the game but is also found in later MVS carts */{
  { "268-p1c.p1", 0x400000, 0x3636690a, REGION_CPU1, 0x000000, LOAD32_SWAP_16 },
  { "268-p2c.p2", 0x400000, 0x8dfc47a2, REGION_CPU1, 0x000002, LOAD32_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mslug5h, mslug5, "Metal Slug 5 (NGH-2680)", SNK_PLAYMORE, 2003, GAME_SHOOT);

static struct ROM_INFO rom_svc[] = /* Encrypted Set clone of neogeo */
 /* MVS AND AES VERSION */{
  { "269-p1.p1", 0x400000, 0x38e2005e, REGION_CPU1, 0x000000, LOAD32_SWAP_16 },
  { "269-p2.p2", 0x400000, 0x6d13797c, REGION_CPU1, 0x000002, LOAD32_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
	/* Encrypted */
  { "269-m1.m1", 0x80000, 0xf6819d00, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "269-v1.v1", 0x800000, 0xc659b34c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "269-v2.v2", 0x800000, 0xdd903835, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "269-c1r.c1", 0x800000, 0x887b4068, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "269-c2r.c2", 0x800000, 0x4e8903e4, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "269-c3r.c3", 0x800000, 0x7d9c55b0, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "269-c4r.c4", 0x800000, 0x8acb5bb6, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "269-c5r.c5", 0x800000, 0x097a4157, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "269-c6r.c6", 0x800000, 0xe19df344, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "269-c7r.c7", 0x800000, 0xd8f0340b, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "269-c8r.c8", 0x800000, 0x2570b71b, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( svc, neogeo, "SNK vs. Capcom - SVC Chaos (NGM-2690)(NGH-2690)", SNK_PLAYMORE, 2003, GAME_BEAT);

static struct ROM_INFO rom_samsho5[] = /* Encrypted Set clone of neogeo */
 /* MVS VERSION */{
  { "270-p1.p1", 0x400000, 0x4a2a09e6, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "270-p2.sp2", 0x400000, 0xe0c74c85, REGION_CPU1, 0x400000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "270-m1.m1", 0x80000, 0x49c9901a, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "270-v1.v1", 0x800000, 0x62e434eb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "270-v2.v2", 0x800000, 0x180f3c9a, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "270-c1.c1", 0x800000, 0x14ffffac, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "270-c2.c2", 0x800000, 0x401f7299, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "270-c3.c3", 0x800000, 0x838f0260, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "270-c4.c4", 0x800000, 0x041560a5, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "270-c5.c5", 0x800000, 0xbd30b52d, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "270-c6.c6", 0x800000, 0x86a69c70, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "270-c7.c7", 0x800000, 0xd28fbc3c, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "270-c8.c8", 0x800000, 0x02c530a6, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho5, neogeo, "Samurai Shodown V / Samurai Spirits Zero (NGM-2700)", SNK_PLAYMORE, 2003, GAME_BEAT);

static struct ROM_INFO rom_samsho5h[] = /* Encrypted Set, Alternate Set clone of samsho5 */
 /* AES VERSION */{
  { "270-p1c.p1", 0x400000, 0xbf956089, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "270-p2c.sp2", 0x400000, 0x943a6b1d, REGION_CPU1, 0x400000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsho5h, samsho5, "Samurai Shodown V / Samurai Spirits Zero (NGH-2700)", SNK_PLAYMORE, 2003, GAME_BEAT);

static struct ROM_INFO rom_kof2003[] = /* Encrypted Code + Sound + GFX Roms clone of neogeo */
 /* MVS VERSION */{
  { "271-p1c.p1", 0x400000, 0x530ecc14, REGION_CPU1, 0x000000, LOAD32_SWAP_16 },
  { "271-p2c.p2", 0x400000, 0xfd568da9, REGION_CPU1, 0x000002, LOAD32_SWAP_16 },
  { "271-p3c.p3", 0x100000, 0xaec5b4a9, REGION_CPU1, 0x800000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
	/* Encrypted */
  { "271-m1c.m1", 0x80000, 0xf5515629, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "271-v1c.v1", 0x800000, 0xffa3f8c7, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "271-v2c.v2", 0x800000, 0x5382c7d1, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "271-c1c.c1", 0x800000, 0xb1dc25d0, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "271-c2c.c2", 0x800000, 0xd5362437, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "271-c3c.c3", 0x800000, 0x0a1fbeab, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "271-c4c.c4", 0x800000, 0x87b19a0c, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "271-c5c.c5", 0x800000, 0x704ea371, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "271-c6c.c6", 0x800000, 0x20a1164c, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "271-c7c.c7", 0x800000, 0x189aba7f, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "271-c8c.c8", 0x800000, 0x20ec4fdc, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof2003, neogeo, "The King of Fighters 2003 (NGM-2710)", SNK_PLAYMORE, 2003, GAME_BEAT);

static struct ROM_INFO rom_kof2003h[] = /* Encrypted Code + Sound + GFX Roms clone of kof2003 */
 /* AES VERSION */{
  { "271-p1k.p1", 0x400000, 0xd0d0ae3e, REGION_CPU1, 0x000000, LOAD32_SWAP_16 },
  { "271-p2k.p2", 0x400000, 0xfb3f79d9, REGION_CPU1, 0x000002, LOAD32_SWAP_16 },
  { "271-p3k.p3", 0x100000, 0x232702ad, REGION_CPU1, 0x800000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x80000, 0, FIXED ),
	/* Encrypted */
  { "271-m1k.m1", 0x80000, 0x48d9affe, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "271-c1k.c1", 0x800000, 0xefb9dd24, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "271-c2k.c2", 0x800000, 0x3fb90447, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "271-c3k.c3", 0x800000, 0x27950f28, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "271-c4k.c4", 0x800000, 0x735177f8, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "271-c5k.c5", 0x800000, 0xa51b7c0f, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "271-c6k.c6", 0x800000, 0xd5cae4e0, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "271-c7k.c7", 0x800000, 0xe65ae2d0, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "271-c8k.c8", 0x800000, 0x312f528c, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof2003h, kof2003, "The King of Fighters 2003 (NGH-2710)", SNK_PLAYMORE, 2003, GAME_BEAT);

static struct ROM_INFO rom_samsh5sp[] = /* Encrypted Set clone of neogeo */
 /* MVS VERSION */{
  { "272-p1.p1", 0x400000, 0xfb7a6bba, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "272-p2.sp2", 0x400000, 0x63492ea6, REGION_CPU1, 0x400000, LOAD_SWAP_16 },
	/* The Encrypted Boards do not have an s1 rom, data for it comes from the Cx ROMs */
  FILL( 0x000000, 0x20000, 0, FIXED ),
	/* Encrypted */
  { "272-m1.m1", 0x80000, 0xadeebf40, REGION_AUDIOCRYPT, 0x00000, LOAD_NORMAL },
	/* Encrypted */
  { "272-v1.v1", 0x800000, 0x76a94127, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "272-v2.v2", 0x800000, 0x4ba507f1, REGION_SMP1, 0x800000, LOAD_NORMAL },
	/* Encrypted */
  { "272-c1.c1", 0x800000, 0x4f97661a, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "272-c2.c2", 0x800000, 0xa3afda4f, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "272-c3.c3", 0x800000, 0x8c3c7502, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "272-c4.c4", 0x800000, 0x32d5e2e2, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "272-c5.c5", 0x800000, 0x6ce085bc, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "272-c6.c6", 0x800000, 0x05c8dc8e, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "272-c7.c7", 0x800000, 0x1417b742, REGION_SPRITES, 0x3000000, LOAD_8_16 },
  { "272-c8.c8", 0x800000, 0xd49773cd, REGION_SPRITES, 0x3000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsh5sp, neogeo, "Samurai Shodown V Special / Samurai Spirits Zero Special (NGM-2720)", SNK_PLAYMORE, 2004, GAME_BEAT);

static struct ROM_INFO rom_samsh5sph[] = /* Encrypted Set clone of samsh5sp */
 /* AES VERSION, 2nd bugfix release */{
  { "272-p1ca.p1", 0x400000, 0xc30a08dd, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
	/* Correct chip labels unknown */
  { "272-p2ca.sp2", 0x400000, 0xbd64a518, REGION_CPU1, 0x400000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( samsh5sph, samsh5sp, "Samurai Shodown V Special / Samurai Spirits Zero Special (NGH-2720) (2nd release, less censored)", SNK_PLAYMORE, 2004, GAME_BEAT);

static struct ROM_INFO rom_lans2004[] = // clone of shocktr2
{
  { "lnsq-p1.bin", 0x200000, 0xb40a879a, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "lnsq-p21.bin", 0x200000, 0xecdb2d42, REGION_CPU1, 0x200000, LOAD_SWAP_16 },
  { "lnsq-p22.bin", 0x200000, 0xfac5e2e7, REGION_CPU1, 0x400000, LOAD_SWAP_16 },
  { "lnsq-s1.bin", 0x20000, 0x39e82897, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "lnsq-v1.bin", 0x400000, 0x4408ebc3, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "lnsq-v2.bin", 0x400000, 0x3d953975, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "lnsq-v3.bin", 0x200000, 0x437d1d8e, REGION_SMP1, 0x800000, LOAD_NORMAL },
  { "lnsq-c1.bin", 0x800000, 0xb83de59f, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "lnsq-c2.bin", 0x800000, 0xe08969fd, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "lnsq-c3.bin", 0x800000, 0x013f2cda, REGION_SPRITES, 0x1000000, LOAD_8_16 },
  { "lnsq-c4.bin", 0x800000, 0xd8c3a758, REGION_SPRITES, 0x1000001, LOAD_8_16 },
  { "lnsq-c5.bin", 0x800000, 0x75500b82, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "lnsq-c6.bin", 0x800000, 0x670ac13b, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( lans2004, shocktr2, "Lansquenet 2004 (Shock Troopers - 2nd Squad bootleg)", BOOTLEG, 1998, GAME_SHOOT);

static struct ROM_INFO rom_diggerma[] = /* Unlicensed Prototype, no official game ID # clone of neogeo */
{
  { "dig-p1.bin", 0x080000, 0xeda433d7, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "dig-s1.bin", 0x10000, 0x75a88c1f, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "dig-m1.bin", 0x10000, 0x833cdf1b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "dig-m1.bin", 0x10000, 0x833cdf1b, REGION_ROM2, 0x10000, LOAD_NORMAL },
  { "dig-v1.bin", 0x080000, 0xee15bda4, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "dig-c1.bin", 0x080000, 0x3db0a4ed, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "dig-c2.bin", 0x080000, 0x3e632161, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( diggerma, neogeo, "Digger Man (prototype)", KYLE_HODGETTS, 2000, GAME_MAZE);

static struct ROM_INFO rom_kof97pls[] = // clone of kof97
{
  { "kf97-p1p.bin", 0x100000, 0xc01fda46, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "kf97-p2p.bin", 0x400000, 0x5502b020, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "kf97-s1p.bin", 0x20000, 0x73254270, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof97pls, kof97, "The King of Fighters '97 Plus (bootleg)", BOOTLEG, 1997, GAME_BEAT);

static struct ROM_INFO rom_kof97oro[] = // clone of kof97
{
  { "orochi-p1.bin", 0x100000, 0x6dcb2946, REGION_CPU1, 0x0000000, LOAD_SWAP_16 },
  { "orochi-p21.bin", 0x100000, 0x6e1c4d8c, REGION_CPU1, 0x0200000, LOAD_SWAP_16 },
  { "orochi-p21.bin", 0x100000 , 0x6e1c4d8c, REGION_CPU1, 0x100000, LOAD_CONTINUE },
  { "orochi-p29.bin", 0x100000, 0x4c7c0221, REGION_CPU1, 0x0400000, LOAD_SWAP_16 },
  { "orochi-p29.bin", 0x100000 , 0x4c7c0221, REGION_CPU1, 0x300000, LOAD_CONTINUE },
  { "orochi-s1.bin", 0x20000, 0x4ee2149a, REGION_FIXED, 0x000000, LOAD_NORMAL },
	// The C1 and C2 here are reconstructed but very likely to be correct.
  { "orochi-c1.bin", 0x1000000, 0xf13e841c, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "orochi-c2.bin", 0x1000000, 0x2db1f6d3, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { "orochi-c51.bin", 0x0200000, 0xa90340cb, REGION_SPRITES, 0x2000000, LOAD_8_16 },
  { "orochi-c61.bin", 0x0200000, 0x188e351a, REGION_SPRITES, 0x2000001, LOAD_8_16 },
  { "orochi-c52.bin", 0x0200000, 0xd4eec50a, REGION_SPRITES, 0x2400000, LOAD_8_16 },
  { "orochi-c62.bin", 0x0200000, 0x031b1ad5, REGION_SPRITES, 0x2400001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( kof97oro, kof97, "The King of Fighters '97 Oroshi Plus 2003 (bootleg)", BOOTLEG, 1997, GAME_BEAT);

// Other companies

static struct ROM_INFO rom_wh2j[] = /* MVS AND AES VERSION clone of neogeo */
{
  { "064-p1.p1", 0x100000, 0x385a2e86, REGION_CPU1, 0x100000, LOAD_SWAP_16 },
  { "064-p1.p1", 0x100000 , 0x385a2e86, REGION_CPU1, 0x000000, LOAD_CONTINUE },
  { "064-s1.s1", 0x20000, 0x2a03998a, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "064-m1.m1", 0x20000, 0xd2eec9d3, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "064-v1.v1", 0x200000, 0xaa277109, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "064-v2.v2", 0x200000, 0xb6527edd, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "064-c1.c1", 0x200000, 0x2ec87cea, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "064-c2.c2", 0x200000, 0x526b81ab, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { "064-c3.c3", 0x200000, 0x436d1b31, REGION_SPRITES, 0x400000, LOAD_8_16 },
  { "064-c4.c4", 0x200000, 0xf9c8dd26, REGION_SPRITES, 0x400001, LOAD_8_16 },
  { "064-c5.c5", 0x200000, 0x8e34a9f4, REGION_SPRITES, 0x800000, LOAD_8_16 },
  { "064-c6.c6", 0x200000, 0xa43e4766, REGION_SPRITES, 0x800001, LOAD_8_16 },
  { "064-c7.c7", 0x200000, 0x59d97215, REGION_SPRITES, 0xc00000, LOAD_8_16 },
  { "064-c8.c8", 0x200000, 0xfc092367, REGION_SPRITES, 0xc00001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( wh2j, neogeo,        "World Heroes 2 Jet (ADM-007)(ADH-007)", ADK, 1994, GAME_BEAT);

static struct ROM_INFO rom_mosyougi[] = // clone of neogeo
{
  { "203-p1.p1", 0x100000, 0x7ba70e2d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "203-s1.s1", 0x20000, 0xbfdc8309, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "203-m1.m1", 0x20000, 0xa602c2c2, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "203-v1.v1", 0x200000, 0xbaa2b9a5, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "203-c1.c1", 0x200000, 0xbba9e8c0, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "203-c2.c2", 0x200000, 0x2574be03, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( mosyougi, neogeo,        "Syougi No Tatsujin - Master of Syougi", ADK, 1995, GAME_PUZZLE);

static struct ROM_INFO rom_zintrckb[] = // clone of neogeo
{
  { "zin-p1.bin", 0x100000, 0x06c8fca7, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "zin-s1.bin", 0x20000, 0xa7ab0e81, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "zin-m1.bin", 0x20000, 0xfd9627ca, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "zin-v1.bin", 0x200000, 0xc09f74f1, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "zin-c1.bin", 0x200000, 0x76aee189, REGION_SPRITES, 0x000000, LOAD_8_16 },
  { "zin-c2.bin", 0x200000, 0x844ed4b3, REGION_SPRITES, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( zintrckb, neogeo,             "Zintrick / Oshidashi Zentrix (hack)", HACK, 1996, GAME_MISC);

static struct ROM_INFO rom_b2b[] = /* testing bang bang buster... */
{
  { "071-p1.bin", 0x80000, 0x7687197d, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "071-s1.bin", 0x20000, 0x44e5f154, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "071-m1.bin", 0x20000, 0x6da739ad, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "071-v1.bin", 0x100000, 0x50feffb0, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "071-c1.bin", 0x200000, 0x23d84a7a, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "071-c2.bin", 0x200000, 0xce7b6248, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( b2b, neogeo, "Bang Bang busters", VISCO, 2000, GAME_PLATFORM); // The rom shows 2000 on title screen, but released in 2010 ?

static struct ROM_INFO rom_totcarib[] = /* testing treasure of the caribeans... */
{
  { "totc-p1.bin", 0x100000, 0x99604539, REGION_CPU1, 0x000000, LOAD_SWAP_16 },
  { "totc-s1.bin", 0x20000, 0x0a3fee41, REGION_FIXED, 0x000000, LOAD_NORMAL },
  { "totc-m1.bin", 0x20000, 0x18b23ace, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "totc-v1.bin", 0x200000, 0x15c7f9e6, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "totc-v2.bin", 0x200000, 0x1b264559, REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "totc-v3.bin", 0x100000, 0x84b62c5d, REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "totc-c1.bin", 0x200000, 0xcdd6600f, REGION_SPRITES, 0x0000000, LOAD_8_16 },
  { "totc-c2.bin", 0x200000, 0xf362c271, REGION_SPRITES, 0x0000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

CLNEI( totcarib, neogeo, "Treasure of the Caribeans", FACE, 2011, GAME_MISC); // 2011, really ???
