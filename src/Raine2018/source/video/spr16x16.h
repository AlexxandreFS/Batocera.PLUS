
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                         RAINE 16x16 TILE DRAWING                           */
/*                                                                            */
/******************************************************************************/

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

void init_spr16x16asm_8(void);
void init_spr16x16asm_mask(BITMAP *bitmap);

// 16x16 mapped sprites

void Draw16x16_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x16 mapped transparent sprites

void Draw16x16_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

void init_spr16x16asm_16(void);

// 16x16 mapped sprites

void Draw16x16_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x16 mapped transparent sprites

void Draw16x16_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

void init_spr16x16asm_32(void);

// 16x16 mapped sprites

void Draw16x16_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x16 mapped transparent sprites

void Draw16x16_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw16x16_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16x16 sprites

void Draw16x16_8(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_16(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_16_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_16_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_32(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_32_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_32_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

// 16x16 masks

void Draw16x16_Mask(UINT8 *SPR, int x, int y, UINT8 cmap);
#define Draw16x16_Mask_FlipX Draw16x16_Mask
#define Draw16x16_Mask_FlipY Draw16x16_Mask
#define Draw16x16_Mask_FlipXY Draw16x16_Mask

// 16x16 transparent sprites

void Draw16x16_Trans_8(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_16(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_16_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_16_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_32(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_32_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_32_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Trans_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

// 16x16 transparant masks

void Draw16x16_Mask_Trans(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Mask_Trans_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Mask_Trans_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap);
void Draw16x16_Mask_Trans_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap);

#ifdef __cplusplus
}
#endif
