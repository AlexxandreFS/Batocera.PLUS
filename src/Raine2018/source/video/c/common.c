// Here go all the functions which are also used by the i386 video core

#include "raine.h"
#include "blit.h"
#include "unmapped.h"
#include "emudx.h"

unmapped(32,32);
unmapped_trans(32,32,ReadLong);
unmapped_trans(32,8,ReadByte);
