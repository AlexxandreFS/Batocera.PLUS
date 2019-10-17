#ifndef __DSW__
#define __DSW__

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                              DIPSWITCH SUPPORT                             */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

#define MAX_DIPSWITCHES		10

// Fill DSW bytes from stat list

void make_dipswitch_bytes(void);
void make_dipswitch_statlist(void);
void init_dsw(void);

typedef struct DSW_DATA
{
   char *name;                 // dsw name          / dsw setting name
   UINT8  bit_mask;             // dsw bit mask      / dsw setting bit pattern
   UINT8  count;                // dsw setting count / zero
} DSW_DATA;

typedef struct DSW_INFO
{
   UINT32     offset;            // offset in (dsw) ram
   UINT8     factory_setting;   // dsw default data
   DSW_DATA *data;              // dsw data list
} DSW_INFO;

extern void (*write_region_byte)(int data);
extern int (*read_region_byte)();
extern  struct DSW_DATA  dsw_data_default_0[];
extern  struct DSW_DATA  dsw_data_default_1[];
extern  struct DSW_DATA  dsw_data_default_2[];
extern int override_region;

void RestoreDSWDefault(void);

UINT8 get_dsw(int i);
void write_dsw(int index);

void load_dipswitches(char *section);

void save_dipswitches(char *section);

/******************************************************************************/
/*                                                                            */
/*         ROM SWITCH SUPPORT (consider them unofficial dip switches)         */
/*                                                                            */
/******************************************************************************/

typedef struct ROMSW
{
   char *Name;			// ROMSwitch Name
   UINT32 Address;		// Address of Switch
   int Count;			// Number of Settings(modes) for this switch
   char *Mode[16];		// Mode Name x16
   UINT8 Data[16];		// Mode Byte x16
   UINT8 def;
} ROMSW;

extern struct ROMSW LanguageSw;	// ROMSwitch for Language Selection (Taito roms)

void init_romsw(void);

void SetLanguageSwitch(int number);

int GetLanguageSwitch(void);

void load_romswitches(char *section);

void save_romswitches(char *section);

/******************************************************************************/
/*                                                                            */
/*                ROM PATCHING SUPPORT (something like an .ips)               */
/*                                                                            */
/******************************************************************************/

typedef struct ROM_PATCH
{
   UINT32 offset;		// offset to patch
   UINT32 data_0;		// first longword
   UINT32 data_1;		// second longword
} ROM_PATCH;

void patch_rom(UINT8 *src, ROM_PATCH *patch);

/******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
