
/* The rules for driver definition :
 * the short name is used also for the game variable and the dir_info reference
 * if using gme, this is used also for inputs, dsw, load, video, exec and sound
 * When using clone, the parent is used instead for these 6 fields.
 * All this can be overriden by defining any of the 6 DRV_DEF_XXX macros, in
 * this case this file must be re-included to redefine all the game definition
 * macros (sorry, C is too stupid for macros !).
 *
 * WARNING : the DRV_DEF_xxx are inserted everywhere if defined, even in the
 * GAME and CLONE macros which are minimalistic usueally.
 * They are supposed to work like that, they define a default value for every
 * driver defined in a given file, that's all. */

#undef DLOAD
#ifndef DRV_DEF_LOAD
#define DLOAD(x) load_##x
#else
#define DLOAD(x) DRV_DEF_LOAD
#endif

#undef PCLEAR
#ifndef DRV_DEF_CLEAR
#define PCLEAR NULL
#else
#define PCLEAR DRV_DEF_CLEAR
#endif

#undef DINPUT
#undef PINPUT
#ifndef DRV_DEF_INPUT
#define DINPUT(x) input_##x
#define PINPUT NULL
#else
#define DINPUT(x) DRV_DEF_INPUT
#define PINPUT DRV_DEF_INPUT
#endif

#undef DDSW
#undef PDSW
#ifndef DRV_DEF_DSW
#define DDSW(x) dsw_##x
#define PDSW NULL
#else
#define DDSW(x) DRV_DEF_DSW
#define PDSW DRV_DEF_DSW
#endif

#undef DEXEC
#undef PEXEC
#ifndef DRV_DEF_EXEC
#define DEXEC(x) execute_##x
#define PEXEC NULL
#else
#define DEXEC(x) DRV_DEF_EXEC
#define PEXEC DRV_DEF_EXEC
#endif

#undef DSOUND
#undef PSOUND
#ifndef DRV_DEF_SOUND
#define DSOUND(x) sound_##x
#define PSOUND NULL
#else
#define DSOUND(x) DRV_DEF_SOUND
#define PSOUND DRV_DEF_SOUND
#endif

#undef DVIDEO
#undef PVIDEO
#ifndef DRV_DEF_VIDEO
#define DVIDEO(x) &video_##x
#define PVIDEO NULL
#else
#define DVIDEO(x) DRV_DEF_VIDEO
#define PVIDEO DRV_DEF_VIDEO
#endif

#define OLD_GAME(name,dir,rom,input,dsw,romsw,load,clear,video,exec,main_name, \
  long_name,long_name_jpn,company,board,year,sound,flags) \
\
const struct GAME_MAIN game_##name = \
{ \
  __FILE__, /* source_file */ \
  dir, rom, input,dsw,romsw,load,clear,video,exec,main_name,long_name, \
  long_name_jpn,company,board,year,sound,flags \
}

#define GAME(name,longn,company,yr,flg, ...) \
                                             \
struct GAME_MAIN game_##name =         \
{                                            \
  .source_file = __FILE__, /* source_file */ \
  .dir_list = dir_##name,                    \
  .rom_list = rom_##name,                    \
    .clear = PCLEAR,                         \
    .load_game = DLOAD(name),                \
    .main_name = #name,                      \
    .long_name = longn,                      \
    .company_id = COMPANY_ID_##company,      \
    .year = yr,                              \
    .flags = flg,                            \
    .input = PINPUT,                         \
    .dsw = PDSW,                             \
    .exec = PEXEC,                           \
    .sound = PSOUND,                         \
    .video = PVIDEO,                         \
##__VA_ARGS__ };


#define CREATE_DIR(name)               \
static struct DIR_INFO dir_##name[] = \
{                                      \
   { #name, },                         \
   { NULL, },                          \
};

#define CREATE_CLONE(name,parent)      \
static struct DIR_INFO dir_##name[] = \
{                                      \
   { #name, },                         \
   { ROMOF( #parent ), },              \
   { CLONEOF( #parent ), },            \
   { NULL, },                          \
};                                     \

// Ultra compact version
#define GME(name,long_name,company,year,flags,...) \
GAME( name, long_name,company,year,flags,          \
    .input = DINPUT(name),                         \
    .dsw = DDSW(name),                             \
    .load_game = DLOAD(name),                      \
    .video = DVIDEO(name),                         \
    .exec = DEXEC(name),                           \
    .sound = DSOUND(name),                         \
##__VA_ARGS__ );                                   \

// Same thing with dir_info creation
#define GMEI(name,long_name,company,year,flags,...) \
    CREATE_DIR(name);                               \
GME(name,long_name,company,year,flags,##__VA_ARGS__);

// Basic clone, just generate load based on the parent
#define CLONE(name, parent,longn,company,yr,flg,...) \
struct GAME_MAIN game_##name =                 \
{                                                    \
  .source_file = __FILE__, /* source_file */         \
  .dir_list = dir_##name,                            \
  .rom_list = rom_##name,                            \
    .clear = PCLEAR,                                 \
    .load_game = DLOAD(parent),                      \
    .main_name = #name,                              \
    .long_name = longn,                              \
    .company_id = COMPANY_ID_##company,              \
    .year = yr,                                      \
    .flags = flg,                                    \
    .input = PINPUT,                                 \
    .dsw = PDSW,                                     \
    .exec = PEXEC,                                   \
    .sound = PSOUND,                                 \
    .video = PVIDEO,                                 \
##__VA_ARGS__ };

#define CLONEI(name, parent,longn,company,yr,flg,...)  \
    CREATE_CLONE(name,parent);                         \
CLONE(name,parent,longn,company,yr,flg,##__VA_ARGS__); \

// Compact clones, try to re-use as many fields as possible...
#define CLNE(name, parent,longn,company,yr,flg,...) \
CLONE(name, parent,longn,company,yr,flg,	    \
    .input = DINPUT(parent),                        \
    .dsw = DDSW(parent),                            \
    .load_game = DLOAD(parent),                     \
    .video = DVIDEO(parent),                        \
    .exec = DEXEC(parent),                          \
    .sound = DSOUND(parent),                        \
##__VA_ARGS__ );

#define CLNEI(name, parent,longn,company,yr,flg,...)  \
    CREATE_CLONE(name,parent);                        \
CLNE(name,parent,longn,company,yr,flg,##__VA_ARGS__);

