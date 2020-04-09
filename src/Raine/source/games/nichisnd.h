
#ifdef __cplusplus
extern "C" {
#endif

#include "deftypes.h"

extern struct SOUND_INFO nichi_ym3812_sound[];

// 68000->Z80 Communication Handlers
// ---------------------------------

UINT16 NichiSoundCommRead68k(UINT32 offset);
void NichiSoundCommWrite68k(UINT32 offset,UINT8 data);

void AddNichibutsuYM3526(UINT32 p1, UINT32 p2);
void RemoveNichibutsuYM3526(void);

void Nichibutsu3526_Frame(void);
void Nichibutsu3526_SlowFrame(void);

void AddNichiSample(UINT16 start, UINT16 end, int rate);

#ifdef __cplusplus
}
#endif
