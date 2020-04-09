
#ifdef __cplusplus
extern "C" {
#endif

#include "deftypes.h"

extern struct SOUND_INFO technos_ym2151_m6295_sound[];

UINT8 TechnosSoundReadZ80(UINT16 offset);

void TechnosSoundWrite68k(UINT32 address, UINT16 data);

void TechnosSound_Frame(void);

void AddTechnosSound(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, UINT8 *adpcmB, int volume);

void TechnosSoundOld_Frame(void);

void AddTechnosSoundOld(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, int volume);

#ifdef __cplusplus
}
#endif
