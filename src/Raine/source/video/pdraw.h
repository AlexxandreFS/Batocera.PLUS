
#ifdef __cplusplus
extern "C" {
#endif

// 16x16 mapped sprites

#undef ARG_PRI
#define ARG_PRI UINT8 *SPR, int x, int y, UINT8 *cmap, UINT8 pri
#undef declare
#define declare(BPP)                                  \
void pdraw16x16_Mapped_##BPP(ARG_PRI);              \
void pdraw16x16_Mapped_##BPP##_FlipX(ARG_PRI);        \
void pdraw16x16_Mapped_##BPP##_FlipY(ARG_PRI);        \
void pdraw16x16_Mapped_##BPP##_FlipXY(ARG_PRI);       \
                                                      \
/* 16x16 mapped transparent sprites */                \
                                                      \
void pdraw16x16_Trans_Mapped_##BPP(ARG_PRI);        \
void pdraw16x16_Trans_Mapped_##BPP##_FlipX(ARG_PRI);  \
void pdraw16x16_Trans_Mapped_##BPP##_FlipY(ARG_PRI);  \
void pdraw16x16_Trans_Mapped_##BPP##_FlipXY(ARG_PRI); \

    declare(8);
    declare(16);
    declare(32);

  // back version : use background bitmap

// 16x16 mapped sprites

#undef declare
#define declare(BPP)                                                \
void pdraw16x16_Mapped_back_##BPP(ARG_PRI);                         \
void pdraw16x16_Mapped_back_##BPP##_FlipX(ARG_PRI);                 \
void pdraw16x16_Mapped_back_##BPP##_FlipY(ARG_PRI);                 \
void pdraw16x16_Mapped_back_##BPP##_FlipXY(ARG_PRI);                \
                                                                    \
/* 16x16 mapped transparent sprites */                              \
                                                                    \
void pdraw16x16_Trans_Mapped_back_##BPP(ARG_PRI);                   \
void pdraw16x16_Trans_Mapped_back_##BPP##_FlipX(ARG_PRI);           \
void pdraw16x16_Trans_Mapped_back_##BPP##_FlipY(ARG_PRI);           \
void pdraw16x16_Trans_Mapped_back_##BPP##_FlipXY(ARG_PRI);          \
                                                                    \
/* Alpha version */                                                 \
                                                                    \
void pdraw16x16_Mapped_back_Alpha_##BPP(ARG_PRI);                   \
void pdraw16x16_Mapped_back_Alpha_##BPP##_FlipX(ARG_PRI);           \
void pdraw16x16_Mapped_back_Alpha_##BPP##_FlipY(ARG_PRI);           \
void pdraw16x16_Mapped_back_Alpha_##BPP##_FlipXY(ARG_PRI);          \
                                                                    \
/* 16x16 mapped transparent sprites */                              \
                                                                    \
void pdraw16x16_Trans_Mapped_back_Alpha_##BPP(ARG_PRI);             \
void pdraw16x16_Trans_Mapped_back_Alpha_##BPP##_FlipX(ARG_PRI);     \
void pdraw16x16_Trans_Mapped_back_Alpha_##BPP##_FlipY(ARG_PRI);     \
void pdraw16x16_Trans_Mapped_back_Alpha_##BPP##_FlipXY(ARG_PRI);    \
                                                                    \
/* mask version : update pbitmap and GameBitmap at the same time */ \
                                                                    \
/* 16x16 mapped sprites */                                          \
                                                                    \
void pdraw16x16_Mask_Mapped_##BPP(ARG_PRI);                         \
void pdraw16x16_Mask_Mapped_##BPP##_FlipX(ARG_PRI);                 \
void pdraw16x16_Mask_Mapped_##BPP##_FlipY(ARG_PRI);                 \
void pdraw16x16_Mask_Mapped_##BPP##_FlipXY(ARG_PRI);                \
                                                                    \
/* 16x16 mapped transparent sprites */                              \
                                                                    \
void pdraw16x16_Mask_Trans_Mapped_##BPP(ARG_PRI);                   \
void pdraw16x16_Mask_Trans_Mapped_##BPP##_FlipX(ARG_PRI);           \
void pdraw16x16_Mask_Trans_Mapped_##BPP##_FlipY(ARG_PRI);           \
void pdraw16x16_Mask_Trans_Mapped_##BPP##_FlipXY(ARG_PRI);
    declare(8);
    declare(16);
    declare(32);

  /* Rot definitions */

typedef void draw_mapped_func_pri(UINT8 *SPR, int x, int y, UINT8 *cmap, UINT8 pri);

extern draw_mapped_func_pri *pdraw16x16_Mapped_Flip_Rot[4];

#define pdraw16x16_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Mapped_Rot(a, b, c, d, f)        (*pdraw16x16_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Mapped_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Trans_Mapped_Flip_Rot[4];

#define pdraw16x16_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Trans_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Trans_Mapped_Rot(a, b, c, d, f)        (*pdraw16x16_Trans_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Trans_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Trans_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Trans_Mapped_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Mapped_back_Flip_Rot[4];

#define pdraw16x16_Mapped_back_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Mapped_back_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Mapped_back_Rot(a, b, c, d, f)        (*pdraw16x16_Mapped_back_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Mapped_back_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Mapped_back_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Mapped_back_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Mapped_back_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Mapped_back_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Mapped_back_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Trans_Mapped_back_Flip_Rot[4];

#define pdraw16x16_Trans_Mapped_back_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Trans_Mapped_back_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Trans_Mapped_back_Rot(a, b, c, d, f)        (*pdraw16x16_Trans_Mapped_back_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_back_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Trans_Mapped_back_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_back_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Trans_Mapped_back_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_back_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Trans_Mapped_back_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Mapped_back_Alpha_Flip_Rot[4];

#define pdraw16x16_Mapped_back_Alpha_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Mapped_back_Alpha_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Mapped_back_Alpha_Rot(a, b, c, d, f)        (*pdraw16x16_Mapped_back_Alpha_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Mapped_back_Alpha_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Mapped_back_Alpha_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Mapped_back_Alpha_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Mapped_back_Alpha_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Mapped_back_Alpha_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Mapped_back_Alpha_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Trans_Mapped_back_Alpha_Flip_Rot[4];

#define pdraw16x16_Trans_Mapped_back_Alpha_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Trans_Mapped_back_Alpha_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Trans_Mapped_back_Alpha_Rot(a, b, c, d, f)        (*pdraw16x16_Trans_Mapped_back_Alpha_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_back_Alpha_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Trans_Mapped_back_Alpha_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_back_Alpha_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Trans_Mapped_back_Alpha_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Trans_Mapped_back_Alpha_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Trans_Mapped_back_Alpha_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Mask_Mapped_Flip_Rot[4];

#define pdraw16x16_Mask_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Mask_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Mask_Mapped_Rot(a, b, c, d, f)        (*pdraw16x16_Mask_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Mask_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Mask_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Mask_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Mask_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Mask_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Mask_Mapped_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw16x16_Mask_Trans_Mapped_Flip_Rot[4];

#define pdraw16x16_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw16x16_Mask_Trans_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw16x16_Mask_Trans_Mapped_Rot(a, b, c, d, f)        (*pdraw16x16_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw16x16_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw16x16_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw16x16_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw16x16_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw16x16_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw16x16_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, f)

  // 8x8 definitions : a copy & paste of the 16x16 declarations with replace...

  // mask version : update pbitmap and GameBitmap at the same time

/* 8x8 mapped sprites */

#undef declare
#define declare(BPP)                                       \
void pdraw8x8_Mask_Mapped_##BPP(ARG_PRI);                  \
void pdraw8x8_Mask_Mapped_##BPP##_FlipX(ARG_PRI);          \
void pdraw8x8_Mask_Mapped_##BPP##_FlipY(ARG_PRI);          \
void pdraw8x8_Mask_Mapped_##BPP##_FlipXY(ARG_PRI);         \
                                                           \
/* 8x8 mapped transparent sprites */                       \
                                                           \
void pdraw8x8_Mask_Trans_Mapped_##BPP(ARG_PRI);            \
void pdraw8x8_Mask_Trans_Mapped_##BPP##_FlipX(ARG_PRI);    \
void pdraw8x8_Mask_Trans_Mapped_##BPP##_FlipY(ARG_PRI);    \
void pdraw8x8_Mask_Trans_Mapped_##BPP##_FlipXY(ARG_PRI);   \
                                                           \
/* 32x32 mapped sprites */                                 \
                                                           \
void pdraw32x32_Mask_Mapped_##BPP(ARG_PRI);                \
void pdraw32x32_Mask_Mapped_##BPP##_FlipX(ARG_PRI);        \
void pdraw32x32_Mask_Mapped_##BPP##_FlipY(ARG_PRI);        \
void pdraw32x32_Mask_Mapped_##BPP##_FlipXY(ARG_PRI);       \
                                                           \
/* 32x32 mapped transparent sprites */                     \
                                                           \
void pdraw32x32_Mask_Trans_Mapped_##BPP(ARG_PRI);          \
void pdraw32x32_Mask_Trans_Mapped_##BPP##_FlipX(ARG_PRI);  \
void pdraw32x32_Mask_Trans_Mapped_##BPP##_FlipY(ARG_PRI);  \
void pdraw32x32_Mask_Trans_Mapped_##BPP##_FlipXY(ARG_PRI);
    declare(8);
    declare(16);
    declare(32);

  /* Rot definitions */

extern draw_mapped_func_pri *pdraw8x8_Mask_Mapped_Flip_Rot[4];

#define pdraw8x8_Mask_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw8x8_Mask_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw8x8_Mask_Mapped_Rot(a, b, c, d, f)        (*pdraw8x8_Mask_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw8x8_Mask_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw8x8_Mask_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw8x8_Mask_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw8x8_Mask_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw8x8_Mask_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw8x8_Mask_Mapped_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw8x8_Mask_Trans_Mapped_Flip_Rot[4];

#define pdraw8x8_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw8x8_Mask_Trans_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw8x8_Mask_Trans_Mapped_Rot(a, b, c, d, f)        (*pdraw8x8_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw8x8_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw8x8_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw8x8_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw8x8_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw8x8_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw8x8_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, f)

  /* 32x32 */

extern draw_mapped_func_pri *pdraw32x32_Mask_Mapped_Flip_Rot[4];

#define pdraw32x32_Mask_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw32x32_Mask_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw32x32_Mask_Mapped_Rot(a, b, c, d, f)        (*pdraw32x32_Mask_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw32x32_Mask_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw32x32_Mask_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw32x32_Mask_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw32x32_Mask_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw32x32_Mask_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw32x32_Mask_Mapped_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw32x32_Mask_Trans_Mapped_Flip_Rot[4];

#define pdraw32x32_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw32x32_Mask_Trans_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw32x32_Mask_Trans_Mapped_Rot(a, b, c, d, f)        (*pdraw32x32_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw32x32_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw32x32_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw32x32_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw32x32_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw32x32_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw32x32_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, f)

  /* 8x8 normal sprites */

#undef declare
#define declare(BPP)                               \
void pdraw8x8_Mapped_##BPP(ARG_PRI);               \
void pdraw8x8_Mapped_##BPP##_FlipX(ARG_PRI);       \
void pdraw8x8_Mapped_##BPP##_FlipY(ARG_PRI);       \
void pdraw8x8_Mapped_##BPP##_FlipXY(ARG_PRI);      \
                                                   \
/* 8x8 mapped transparent sprites */               \
                                                   \
void pdraw8x8_Trans_Mapped_##BPP(ARG_PRI);         \
void pdraw8x8_Trans_Mapped_##BPP##_FlipX(ARG_PRI); \
void pdraw8x8_Trans_Mapped_##BPP##_FlipY(ARG_PRI); \
void pdraw8x8_Trans_Mapped_##BPP##_FlipXY(ARG_PRI);
    declare(8);
    declare(16);
    declare(32);


  /* Rot definitions */

extern draw_mapped_func_pri *pdraw8x8_Mapped_Flip_Rot[4];

#define pdraw8x8_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw8x8_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw8x8_Mapped_Rot(a, b, c, d, f)        (*pdraw8x8_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw8x8_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw8x8_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw8x8_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw8x8_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw8x8_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw8x8_Mapped_Flip_Rot[3])(a, b, c, d, f)

extern draw_mapped_func_pri *pdraw8x8_Trans_Mapped_Flip_Rot[4];

#define pdraw8x8_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*pdraw8x8_Trans_Mapped_Flip_Rot[e])(a, b, c, d, f)

#define pdraw8x8_Trans_Mapped_Rot(a, b, c, d, f)        (*pdraw8x8_Trans_Mapped_Flip_Rot[0])(a, b, c, d, f)
#define pdraw8x8_Trans_Mapped_FlipY_Rot(a, b, c, d, f)  (*pdraw8x8_Trans_Mapped_Flip_Rot[1])(a, b, c, d, f)
#define pdraw8x8_Trans_Mapped_FlipX_Rot(a, b, c, d, f)  (*pdraw8x8_Trans_Mapped_Flip_Rot[2])(a, b, c, d, f)
#define pdraw8x8_Trans_Mapped_FlipXY_Rot(a, b, c, d, f) (*pdraw8x8_Trans_Mapped_Flip_Rot[3])(a, b, c, d, f)

#ifdef __cplusplus
}
#endif
