
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                         RAINE 32x32 TILE DRAWING                           */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

void init_spr32x32asm_8(void);

// 32x32 mapped sprites

void Draw32x32_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 32x32 mapped transparent sprites

void Draw32x32_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

void init_spr32x32asm_16(void);

// 32x32 mapped sprites

void Draw32x32_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 32x32 mapped transparent sprites

void Draw32x32_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

void init_spr32x32asm_32(void);

// 32x32 mapped sprites

void Draw32x32_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 32x32 mapped transparent sprites

void Draw32x32_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw32x32_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 32x32 sprites

void Draw32x32_8(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_16(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_16_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_16_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_32(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_32_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_32_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

// 32x32 transparent sprites

void Draw32x32_Trans_8(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_16(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_16_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_16_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_32(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_32_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_32_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

  // Transparent, alpha blending 50%

void Draw32x32_Trans_Alpha50_16(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha50_16_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha50_16_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha50_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

void Draw32x32_Trans_Alpha50_32(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha50_32_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha50_32_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha50_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

  // Generic mmx alpha blending

void Draw32x32_Trans_Alpha_16(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha_16_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha_16_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

void Draw32x32_Trans_Alpha_32(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha_32_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha_32_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw32x32_Trans_Alpha_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
#ifdef __cplusplus
}
#endif
