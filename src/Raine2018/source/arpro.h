
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                             PRO ACTION REPLAY                              */
/*                                                                            */
/******************************************************************************/

#ifndef _ARPRO_H_
#define _ARPRO_H_

#include "deftypes.h"

enum {
   SEARCH_MODE_ABSOLUTE = 0,
   SEARCH_MODE_RELATIVE,
   SEARCH_MODE_SINGLE_BIT,
   SEARCH_MODE_SLOW,

   SEARCH_MODE_COUNT,
};

extern UINT32 search_mode;

#define CHEAT_MAX	(256)

typedef struct CHEAT
{
   char name[256];		// cheat name/description
   char info[256];		// extra info (used to keep comments in cheats.cfg)
   UINT32 address;		// 32-bit address in cpu memory map
   UINT32 data;			// data to patch
   UINT32 mask;			// data mask
   UINT32 type;			// patch mode
   UINT32 edit_value;           // value given by user for editable cheats
   UINT32 old_value;             // for editable cheats on change
   UINT16 active;		// active status
} CHEAT;

extern int CheatCount;			// Number of Cheats in List
extern struct CHEAT CheatList[CHEAT_MAX]; // List of Current Game cheats

// Cheat data size

#define CHEAT_8BIT		(0x00)
#define CHEAT_16BIT		(0x01)
#define CHEAT_24BIT		(0x02)
#define CHEAT_32BIT		(0x03)

// Cheat bitmask enabled

#define CHEAT_MASKED		(0x04)

// Cheat only lasts one frame

#define CHEAT_1_TIME		(0x08)

#define CHEAT_WATCH             (0x10)
#define CHEAT_EDITABLE          (0x20)
// The following 3 bits are relevant only for editable cheats
// Base for the edited cheat 0 or 1
#define CHEAT_EDIT_BASE         (0x40)
#define CHEAT_EDIT_BCD          (0x80)
#define CHEAT_EDIT_ONCHANGE     (0x100)

#define CHEAT_EVERY_5S          (0x200)

char *get_search_mode_name(UINT32 mode);

void update_arpro_cheats(void);

void start_arpro_search(UINT8 data);

void continue_arpro_search(UINT8 data);

UINT32 get_search_range_start(UINT32 addr);
UINT32 get_search_range_end(UINT32 addr);
UINT8 get_address_status(UINT32 addr);

void reset_arpro(void);

void load_arpro_cheats(const char *section);
void save_arpro_cheats(const char *section);

UINT32 *get_arpro_results(int num);

UINT8 gen_cpu_read_byte(UINT32 address);
void gen_cpu_write_byte(UINT32 address, UINT8 data);

void get_cheat_hex_value(int ta, char *text);

extern int match_all_count;		// total of all match_count

#endif

#ifdef __cplusplus
}
#endif
