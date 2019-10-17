
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                 RAINE 8x8 TILE DRAWING (4BPP PACKED DATA)                  */
/*                                                                            */
/******************************************************************************/

/*

Transparent Packed Mapped

*/

// 8x8 4bpp Packed Mapped Sprites

void init_spp8x8asm_8(void);
void init_spp8x8asm_16();
void init_spp8x8asm_32();

// 8x8 4bpp Packed Mapped Transparent Sprites
// [10325476]

void Draw8x8_Trans_Packed_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 8x8 4bpp Packed Mapped Transparent Sprites (word swapped)
// [54761032]

void Draw8x8_Trans_Packed_Mapped_SwapWord_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 16 & 32 bpp

// 8x8 4bpp Packed Mapped_16 Transparent Sprites
// [10325476]

void Draw8x8_Trans_Packed_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 8x8 4bpp Packed Mapped_16 Transparent Sprites (word swapped)
// [54761032]

void Draw8x8_Trans_Packed_Mapped_SwapWord_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 8x8 4bpp Packed Mapped_16 Transparent Sprites
// [10325476]

void Draw8x8_Trans_Packed_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// 8x8 4bpp Packed Mapped_32 Transparent Sprites (word swapped)
// [54761032]

void Draw8x8_Trans_Packed_Mapped_SwapWord_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw8x8_Trans_Packed_Mapped_SwapWord_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

#ifdef __cplusplus
}
#endif
