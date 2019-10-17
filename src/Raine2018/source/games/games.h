
#ifdef __cplusplus
 extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                               RAINE GAME LISTS                             */
/*                                                                            */
/******************************************************************************/

#ifndef __raine_games_h_
#define __raine_games_h_

#include "deftypes.h"
#include "loadroms.h"
#include "dsw.h"

enum company_num
{
   COMPANY_ID_UNKNOWN = 0,
   COMPANY_ID_BOOTLEG,
   COMPANY_ID_CAPCOM,
   COMPANY_ID_DECO,
   COMPANY_ID_IREM,
   COMPANY_ID_JALECO,
   COMPANY_ID_KONAMI,
   COMPANY_ID_NICHIBUTSU,
   COMPANY_ID_SEGA,
   COMPANY_ID_SNK,
   COMPANY_ID_TAITO,
   COMPANY_ID_TECMO,
   COMPANY_ID_TOAPLAN,
   COMPANY_ID_BANPREST,
   COMPANY_ID_UPL,
   COMPANY_ID_NAMCO,
   COMPANY_ID_NTC,
   COMPANY_ID_VISCO,
   COMPANY_ID_FACE,
   COMPANY_ID_SEIBU,
   COMPANY_ID_SAMMY,
   COMPANY_ID_VIDEOSYSTEM,
   COMPANY_ID_ALPHA,
   COMPANY_ID_NAZCA,
   COMPANY_ID_TECHNOS,
   COMPANY_ID_NMK,
   COMPANY_ID_SUNSOFT,
   COMPANY_ID_AICOM,
   COMPANY_ID_YUMEKOBO,
   COMPANY_ID_HUDSON,
   COMPANY_ID_TAD,
   COMPANY_ID_COMAD,
   COMPANY_ID_SETA,
   COMPANY_ID_EX_SYSTEM,
   COMPANY_ID_KANEKO,
   COMPANY_ID_RAIZING,
   COMPANY_ID_CAVE,
   COMPANY_ID_ZEUS,
   COMPANY_ID_GAELCO,
   COMPANY_ID_PSIKYO,
   COMPANY_ID_EAST_TECHNOLOGY,
   COMPANY_ID_WILLIAMS,
   COMPANY_ID_HOT_B,
   COMPANY_ID_MARBLE,
   COMPANY_ID_WINTECHNO,
   COMPANY_ID_ALLUMER,
   COMPANY_ID_ATHENA,
   COMPANY_ID_YANG_CHENG,
   COMPANY_ID_MIDWAY,
   COMPANY_ID_NINTENDO,
   COMPANY_ID_MITCHELL,
   COMPANY_ID_SEMICOM,
   COMPANY_ID_ESD,
   COMPANY_ID_SPACY,
   COMPANY_ID_ELECTRONIC_DEVICES,
   COMPANY_ID_NIX,
   COMPANY_ID_ADK,
   COMPANY_ID_HACK,
   COMPANY_ID_TAKUMI,
   COMPANY_ID_VICCOM,
   COMPANY_ID_EIGHTING,
   COMPANY_ID_SAURUS,
   COMPANY_ID_ELEVEN,
   COMPANY_ID_NOISE,
   COMPANY_ID_EOLITH_S,
   COMPANY_ID_MEGA_P,
   COMPANY_ID_EVOGA_P,
   COMPANY_ID_EOLITH_P,
   COMPANY_ID_NOISE_ATLUS,
   COMPANY_ID_AIKY,
   COMPANY_ID_SNK_PLAYMORE,
   COMPANY_ID_KYLE_HODGETTS,
   COMPANY_ID_F2,
};

extern const int nb_companies;

#define ROMOF(game) "#" game

#define CLONEOF(game) "$" game

#define IS_ROMOF(string) (string[0] == '#')

#define IS_CLONEOF(string) (string[0] == '$')

typedef struct INPUT_INFO
{
   UINT16  default_key;          // default input mapping
   char *name;                 // input name
   UINT32  offset;               // offset in (input) ram
   UINT8  bit_mask;             // bit mask
   UINT8  flags;                // type flags
} INPUT_INFO;

typedef struct ROMSW_DATA
{
   char *name;                 // romsw setting name
   UINT8  data;                 // romsw setting byte
} ROMSW_DATA;

typedef struct ROMSW_INFO
{
   UINT32       offset;          // offset in rom
   UINT8       factory_setting; // romsw default data
   ROMSW_DATA *data;            // romsw data list
} ROMSW_INFO;

/*

flags for VIDEO_INFO

*/

#define VIDEO_ROTATE_NORMAL	(0x00000000)
#define VIDEO_ROTATE_90		(0x00000001)
#define VIDEO_ROTATE_180	(0x00000002)
#define VIDEO_ROTATE_270	(0x00000003)

#define VIDEO_ROTATE(flags)	((flags >> 0) & 3)

#define VIDEO_ROTATABLE		(0x00000004)

#define VIDEO_FLIP_NORMAL	(0x00000000)
#define VIDEO_FLIP_X		(0x00000008)
#define VIDEO_FLIP_Y		(0x00000010)
#define VIDEO_FLIP_XY		(0x00000018)

#define VIDEO_FLIP(flags)	((flags >> 3) & 3)

#define VIDEO_NEEDS_16BPP       (0x00000020)
#define VIDEO_NEEDS_8BPP        (0x00000040)

typedef struct VIDEO_INFO
{
   void       (*draw_game)();   // pointer to screen update function
   int        screen_x;         // screen width
   int        screen_y;         // screen height
   int        border_size;      // clipping border size
   UINT32      flags;		// extra info
   GFX_LIST  *gfx_list;
   float fps; // default 60 fps if uninitialized
} VIDEO_INFO;

#ifdef interface
// stupid windows api...
#undef interface
#endif

typedef struct SOUND_INFO
{
   UINT32      type;             // chip type
   void      *interface;        // chip specific inteface
} SOUND_INFO;

/*

main game structure

*/

/* For the game type definitions : it might not be necessary to define one
   bit for each type, since the games should not require to have more than
   one type... Anyway, since I have 32 bits available, I will keep the bits
   definition for now */

// All is 0
#define GAME_BREAKOUT 1
#define GAME_SHOOT    2
#define GAME_BEAT     4
#define GAME_PUZZLE   8
#define GAME_PLATFORM 0x10
#define GAME_MISC     0x20
#define GAME_SPORTS   0x40
#define GAME_ADULT    0X80
#define GAME_RACE     0x100
#define GAME_QUIZZ    0x200
#define GAME_MAZE    0x400
#define GAME_FIGHT    0x800

#define NB_GAME_TYPE 13
extern char *game_type[NB_GAME_TYPE];

// Status
#define GAME_NOT_WORKING       0x10000
#define GAME_PARTIALLY_WORKING 0x20000

typedef struct GAME_MAIN
{
  const char *source_file; // can be initialised with __FILE__
  const DIR_INFO    *dir_list;       // dir list
  const ROM_INFO    *rom_list;       // rom list
  const INPUT_INFO  *input;     // input list
  const DSW_INFO    *dsw;       // dsw list
  const ROMSW_INFO  *romsw;     // romsw list

  void       (*load_game)();   // Pointer to load/init game function
  void       (*clear)();  // Pointer to clear game function
  VIDEO_INFO  *video;     // video hardware information
  void       (*exec)();  // Pointer to exec game function

  /*

  game 'database' information

  */

  char       *main_name;      // id game name (8 char, lower case)
  char       *long_name;      // full game name
  const char       *long_name_jpn;  // full game name
  const UINT8        company_id;     // company who produced the game
  const char       *board;          // board number (company specific)
  const UINT32        year;           // year of release

  /*

  sound cpu information

  */

  const SOUND_INFO  *sound;     // sound list
  const UINT32 flags;
} GAME_MAIN;

#include "game_def.h"

/*

the list of all games

*/

extern struct GAME_MAIN *game_list[];

/*

the number of games in game_list

*/

extern int game_count;

/*

the currently loaded game (or NULL)

*/

extern struct GAME_MAIN *current_game;

/*

initialize game_list (and other things)

*/

void init_game_list(void);

/*

return string for company_id

*/

char *game_company_name(UINT8 company_id);

/*

check the current game

*/

int is_current_game(char *main_name);
int is_neocd();

/*

Return the name of the parent if current game is a clone
else return current game name

*/

const char *parent_name();
int is_clone(struct GAME_MAIN *current_game);

GAME_MAIN *find_game(char *main_name); // in loadroms.c

int game_exists(GAME_MAIN **my_game_list,int num);

#endif // __raine_games_h_

#ifdef __cplusplus
}
#endif
