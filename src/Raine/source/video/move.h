
#ifdef __cplusplus
extern "C" {
#endif
// Moving sprite blocks...

void init_moveasm(void);

void Move8x8_16(UINT8 *SPR, int x, int y,UINT8 *map);
void Move8x8_16_FlipX(UINT8 *SPR, int x, int y,UINT8 *map);
void Move8x8_16_FlipY(UINT8 *SPR, int x, int y,UINT8 *map);
void Move8x8_16_FlipXY(UINT8 *SPR, int x, int y,UINT8 *map);

void Move8x8_32(UINT8 *SPR, int x, int y, UINT8 *map);
void Move8x8_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *map);
void Move8x8_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *map);
void Move8x8_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *map);

void Move8x8_8(UINT8 *SPR, int x, int y, UINT8 *map);
void Move8x8_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *map);
void Move8x8_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *map);
void Move8x8_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *map);

#ifdef __cplusplus
}
#endif
