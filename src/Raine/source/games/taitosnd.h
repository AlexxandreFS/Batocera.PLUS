
#ifdef __cplusplus
extern "C" {
#endif

#include "deftypes.h"
#include "tc140syt.h"

extern struct SOUND_INFO taito_ym2203_sound[];
extern struct SOUND_INFO taito_ym2203_m6295_sound[];

extern struct SOUND_INFO taito_ym2151_sound[];
extern struct SOUND_INFO taito_ym2151_msm5205_sound[];

extern struct SOUND_INFO taito_ym2610_sound[];
extern struct SOUND_INFO taito_ym2610b_sound[];
extern struct SOUND_INFO contcirc_ym2610_sound[];

// Z80->YM2203A Communication Handlers
// -----------------------------------

UINT16 YM2203AReadZ80(UINT16 offset);
void YM2203AWriteZ80(UINT16 offset, UINT8 data);
void YM2203ATaitoWriteZ80(UINT16 offset, UINT8 data);

// Z80->YM2203B Communication Handlers
// -----------------------------------

UINT16 YM2203BReadZ80(UINT16 offset);
void YM2203BWriteZ80(UINT16 offset, UINT8 data);

// Z80->YM2151 Communication Handlers
// ----------------------------------

UINT16 YM2151ReadZ80(UINT16 offset);
UINT16 YM2151ReadZ80_Timer(UINT16 offset);
void YM2151WriteZ80(UINT16 offset, UINT8 data);
void YM2151TaitoWriteZ80(UINT16 offset, UINT8 data);

// Z80->YM2610 Communication Handlers
// ----------------------------------

UINT16 YM2610ReadZ80(UINT16 offset);
void YM2610WriteZ80(UINT16 offset, UINT8 data);

// Z80->YM2610 Volume Panning Handlers (TAITO)
// -------------------------------------------
void Pan2610WriteZ80(UINT16 offset, UINT8 data);
void Pan2610_OffsetVol( int data );
void Pan2610WriteZ80_OffsetVol(UINT16 offset, UINT8 data);

void YM2610SetBuffers(UINT8 *bufa, UINT8 *bufb, UINT32 sizea, UINT32 sizeb);

// TAITO Generic YM2610+Z80 Handler
// --------------------------------

void AddTaitoYM2610(UINT32 p1, UINT32 p2, UINT32 romsize);
void AddTaitoYM2610B(UINT32 p1, UINT32 p2, UINT32 romsize);
void AddTaitoYM2610B_OffsetVol(UINT32 p1, UINT32 p2, UINT32 romsize, int vol);

void Taito2610_Frame(void);
void RemoveTaitoYM2610(void);

void YM2610_Init(void);
void YM2610B_Init(void);

// TAITO Generic YM2151+ADPCM+Z80 Handler
// --------------------------------------

void AddTaitoYM2151(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, UINT8 *adpcmB);
void AddTaitoYM2151_Timer(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, UINT8 *adpcmB);
void AddTaitoYM2151_xsystem(UINT32 p1, UINT32 p2, UINT32 romsize);

void Taito2151_Frame(void);
void Taito2151_FrameFast(void);
void Taito2151_FrameRI(void);
void Taito2151_Frame_xsystem(void);

void RemoveTaitoYM2151(void);

// TAITO Generic YM2203+M6295+Z80 Handler
// --------------------------------------

void AddTaitoYM2203(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcm, UINT32 adpcmsize);
void AddTaitoYM2203_B(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcm, UINT32 adpcmsize);
void Taito2203_Frame(void);
void RemoveTaitoYM2203(void);

// Z80 rom banking system (TAITO)
// ------------------------------

void AddTaitoSoundBanking(UINT8 *romsrc, UINT32 romsize);
void RemoveTaitoSoundBanking(void);

UINT16 TaitoSoundReadBankData(UINT16 offset);
void TaitoSoundSetBank(UINT16 offset, UINT8 data);

// First OKI 6295

void M6295_A_Write_68k( UINT32 address, UINT16 data );
UINT16 M6295_A_Read_68k( UINT32 address );
void M6295_A_WriteBank_68k( UINT32 address, UINT16 data );

void M6295_A_Write_Z80(UINT16 offset, UINT8 data);
UINT16 M6295_A_Read_Z80(UINT16 offset);
UINT16 M6295_A_ReadFree_Z80(UINT16 offset);
void M6295_A_WriteBank_Z80(UINT16 offset, UINT8 data);

// Second OKI 6295

void M6295_B_Write_68k( UINT32 address, UINT16 data );
UINT16 M6295_B_Read_68k( UINT32 address );
void M6295_B_WriteBank_68k( UINT32 address, UINT16 data );

/**************** end of file ****************/

#ifdef __cplusplus
}
#endif
