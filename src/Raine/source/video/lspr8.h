
#ifdef __cplusplus
extern "C" {
#endif
#ifndef LSPR8_H
#define LSPR8_H

#include "lspr16.h" // ldraw_mapped_func typedef definition

void ldraw8x8_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw8x8_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

// 8x8 mapped transparent sprites

void ldraw8x8_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
void ldraw8x8_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw8x8_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

void pldraw8x8_Mask_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);

void pcdraw8x8_Mask_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);


void pldraw8x8_Mask_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);


void pcdraw8x8_Mask_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);

// 16bpp
void ldraw8x8_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw8x8_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

// 8x8 mapped transparent sprites

void ldraw8x8_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
void ldraw8x8_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw8x8_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

void pldraw8x8_Mask_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);

void pcdraw8x8_Mask_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);


void pldraw8x8_Mask_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);


void pcdraw8x8_Mask_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);

// 32bpp
void ldraw8x8_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw8x8_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

// 8x8 mapped transparent sprites

void ldraw8x8_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
void ldraw8x8_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw8x8_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw8x8_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw8x8_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

void pldraw8x8_Mask_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);

void pcdraw8x8_Mask_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw8x8_Mask_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);


void pldraw8x8_Mask_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw8x8_Mask_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);


void pcdraw8x8_Mask_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw8x8_Mask_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);

// Rot

// line scroll functions. I need the address of the buffer containing the
// offsets. That means a new ldrawè_mapped_func, and another version of the
// macros to build the tables... big sigh !

extern ldraw_mapped_func *ldraw8x8_Mapped_Flip_Rot[4];

#define ldraw8x8_Mapped_flip_Rot(a, b, c, d, e,f) (*ldraw8x8_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define ldraw8x8_Mapped_Rot(a, b, c, d, e)        (*ldraw8x8_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define ldraw8x8_Mapped_FlipY_Rot(a, b, c, d, e)  (*ldraw8x8_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define ldraw8x8_Mapped_FlipX_Rot(a, b, c, d, e)  (*ldraw8x8_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define ldraw8x8_Mapped_FlipXY_Rot(a, b, c, d, e) (*ldraw8x8_Mapped_Flip_Rot[3])(a, b, c, d, e)

extern ldraw_mapped_func *ldraw8x8_Trans_Mapped_Flip_Rot[4];

#define ldraw8x8_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*ldraw8x8_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define ldraw8x8_Trans_Mapped_Rot(a, b, c, d, e)        (*ldraw8x8_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define ldraw8x8_Trans_Mapped_FlipY_Rot(a, b, c, d, e)  (*ldraw8x8_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define ldraw8x8_Trans_Mapped_FlipX_Rot(a, b, c, d, e)  (*ldraw8x8_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define ldraw8x8_Trans_Mapped_FlipXY_Rot(a, b, c, d, e) (*ldraw8x8_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e)

// column scroll

extern ldraw_mapped_func *cdraw8x8_Mapped_Flip_Rot[4];

#define cdraw8x8_Mapped_flip_Rot(a, b, c, d, e,f) (*cdraw8x8_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define cdraw8x8_Mapped_Rot(a, b, c, d, e)        (*cdraw8x8_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define cdraw8x8_Mapped_FlipY_Rot(a, b, c, d, e)  (*cdraw8x8_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define cdraw8x8_Mapped_FlipX_Rot(a, b, c, d, e)  (*cdraw8x8_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define cdraw8x8_Mapped_FlipXY_Rot(a, b, c, d, e) (*cdraw8x8_Mapped_Flip_Rot[3])(a, b, c, d, e)

extern ldraw_mapped_func *cdraw8x8_Trans_Mapped_Flip_Rot[4];

#define cdraw8x8_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*cdraw8x8_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define cdraw8x8_Trans_Mapped_Rot(a, b, c, d, e)        (*cdraw8x8_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define cdraw8x8_Trans_Mapped_FlipY_Rot(a, b, c, d, e)  (*cdraw8x8_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define cdraw8x8_Trans_Mapped_FlipX_Rot(a, b, c, d, e)  (*cdraw8x8_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define cdraw8x8_Trans_Mapped_FlipXY_Rot(a, b, c, d, e) (*cdraw8x8_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e)

// Mask functions (Rot)

extern ldraw_mapped_func_pri *pldraw8x8_Mask_Mapped_Flip_Rot[4];

#define pldraw8x8_Mask_Mapped_flip_Rot(a, b, c, d, e,f,g) (*pldraw8x8_Mask_Mapped_Flip_Rot[f])(a, b, c, d, e, g)

#define pldraw8x8_Mask_Mapped_Rot(a, b, c, d, e, f)        (*pldraw8x8_Mask_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pldraw8x8_Mask_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pldraw8x8_Mask_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pldraw8x8_Mask_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pldraw8x8_Mask_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pldraw8x8_Mask_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pldraw8x8_Mask_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

extern ldraw_mapped_func_pri *pldraw8x8_Mask_Trans_Mapped_Flip_Rot[4];

#define pldraw8x8_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f,g) (*pldraw8x8_Mask_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e,g)

#define pldraw8x8_Mask_Trans_Mapped_Rot(a, b, c, d, e, f)        (*pldraw8x8_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pldraw8x8_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pldraw8x8_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pldraw8x8_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pldraw8x8_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pldraw8x8_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pldraw8x8_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

// column scroll

extern ldraw_mapped_func_pri *pcdraw8x8_Mask_Mapped_Flip_Rot[4];

#define pcdraw8x8_Mask_Mapped_flip_Rot(a, b, c, d, e,f,g) (*pcdraw8x8_Mask_Mapped_Flip_Rot[f])(a, b, c, d, e,g)

#define pcdraw8x8_Mask_Mapped_Rot(a, b, c, d, e, f)        (*pcdraw8x8_Mask_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pcdraw8x8_Mask_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pcdraw8x8_Mask_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pcdraw8x8_Mask_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pcdraw8x8_Mask_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pcdraw8x8_Mask_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pcdraw8x8_Mask_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

extern ldraw_mapped_func_pri *pcdraw8x8_Mask_Trans_Mapped_Flip_Rot[4];

#define pcdraw8x8_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f, g) (*pcdraw8x8_Mask_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e, g)

#define pcdraw8x8_Mask_Trans_Mapped_Rot(a, b, c, d, e, f)        (*pcdraw8x8_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pcdraw8x8_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pcdraw8x8_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pcdraw8x8_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pcdraw8x8_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pcdraw8x8_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pcdraw8x8_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e, f)


#endif

#ifdef __cplusplus
}
#endif
