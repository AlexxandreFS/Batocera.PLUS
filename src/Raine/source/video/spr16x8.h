
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                         RAINE 16x8 TILE DRAWING                            */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped

*/

void init_spr16x8asm(void);

// 16x8 mapped sprites

void Draw16x8_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x8 mapped transparent sprites

void Draw16x8_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16 bpp
void init_spr16x8asm_16(void);

// 16x8 mapped sprites

void Draw16x8_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x8 mapped transparent sprites

void Draw16x8_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 32 bpp
void init_spr16x8asm_32(void);

// 16x8 mapped sprites

void Draw16x8_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x8 mapped transparent sprites

void Draw16x8_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x8_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

#ifdef __cplusplus
}
#endif
