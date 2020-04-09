#ifndef DRV_RECURSIVE

#define DRV_RECURSIVE
#define DRV(NAME) extern struct GAME_MAIN game_##NAME;
#include "driver.c"

// 2nd part, make the array
#undef DRV
#define DRV(NAME) &game_##NAME,

struct GAME_MAIN *game_list[] =
{
#include "driver.c"
};

#else

#include "drivers.h"

#endif


