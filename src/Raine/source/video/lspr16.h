
#ifdef __cplusplus
extern "C" {
#endif
#ifndef LSPR16_H
#define LSPR16_H

void ldraw16x16_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw16x16_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

// 16x16 mapped transparent sprites

void ldraw16x16_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
void ldraw16x16_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw16x16_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

void pldraw16x16_Mask_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);

void pcdraw16x16_Mask_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);


void pldraw16x16_Mask_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);


void pcdraw16x16_Mask_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);

// 16bpp
void ldraw16x16_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw16x16_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

// 16x16 mapped transparent sprites

void ldraw16x16_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
void ldraw16x16_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw16x16_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

void pldraw16x16_Mask_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);

void pcdraw16x16_Mask_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);


void pldraw16x16_Mask_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);


void pcdraw16x16_Mask_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);

// 32bpp
void ldraw16x16_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw16x16_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

// 16x16 mapped transparent sprites

void ldraw16x16_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
void ldraw16x16_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);
void ldraw16x16_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy);

void cdraw16x16_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);
void cdraw16x16_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx);

void pldraw16x16_Mask_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);

void pcdraw16x16_Mask_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);
void pcdraw16x16_Mask_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dy, UINT8 pri);


void pldraw16x16_Mask_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);
void pldraw16x16_Mask_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);


void pcdraw16x16_Mask_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);
void pcdraw16x16_Mask_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, INT16 *dx, UINT8 pri);

// Rot

// line scroll functions. I need the address of the buffer containing the
// offsets. That means a new ldrawè_mapped_func, and another version of the
// macros to build the tables... big sigh !
typedef void ldraw_mapped_func(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy);
typedef void ldraw_mapped_func_pri(UINT8 *SPR, int x, int y, UINT8 *cmap,INT16 *dy, UINT8 pri);

extern ldraw_mapped_func *ldraw16x16_Mapped_Flip_Rot[4];

#define ldraw16x16_Mapped_flip_Rot(a, b, c, d, e,f) (*ldraw16x16_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define ldraw16x16_Mapped_Rot(a, b, c, d, e)        (*ldraw16x16_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define ldraw16x16_Mapped_FlipY_Rot(a, b, c, d, e)  (*ldraw16x16_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define ldraw16x16_Mapped_FlipX_Rot(a, b, c, d, e)  (*ldraw16x16_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define ldraw16x16_Mapped_FlipXY_Rot(a, b, c, d, e) (*ldraw16x16_Mapped_Flip_Rot[3])(a, b, c, d, e)

extern ldraw_mapped_func *ldraw16x16_Trans_Mapped_Flip_Rot[4];

#define ldraw16x16_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*ldraw16x16_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define ldraw16x16_Trans_Mapped_Rot(a, b, c, d, e)        (*ldraw16x16_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define ldraw16x16_Trans_Mapped_FlipY_Rot(a, b, c, d, e)  (*ldraw16x16_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define ldraw16x16_Trans_Mapped_FlipX_Rot(a, b, c, d, e)  (*ldraw16x16_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define ldraw16x16_Trans_Mapped_FlipXY_Rot(a, b, c, d, e) (*ldraw16x16_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e)

// column scroll

extern ldraw_mapped_func *cdraw16x16_Mapped_Flip_Rot[4];

#define cdraw16x16_Mapped_flip_Rot(a, b, c, d, e,f) (*cdraw16x16_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define cdraw16x16_Mapped_Rot(a, b, c, d, e)        (*cdraw16x16_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define cdraw16x16_Mapped_FlipY_Rot(a, b, c, d, e)  (*cdraw16x16_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define cdraw16x16_Mapped_FlipX_Rot(a, b, c, d, e)  (*cdraw16x16_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define cdraw16x16_Mapped_FlipXY_Rot(a, b, c, d, e) (*cdraw16x16_Mapped_Flip_Rot[3])(a, b, c, d, e)

extern ldraw_mapped_func *cdraw16x16_Trans_Mapped_Flip_Rot[4];

#define cdraw16x16_Trans_Mapped_flip_Rot(a, b, c, d, e, f) (*cdraw16x16_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e)

#define cdraw16x16_Trans_Mapped_Rot(a, b, c, d, e)        (*cdraw16x16_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define cdraw16x16_Trans_Mapped_FlipY_Rot(a, b, c, d, e)  (*cdraw16x16_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define cdraw16x16_Trans_Mapped_FlipX_Rot(a, b, c, d, e)  (*cdraw16x16_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define cdraw16x16_Trans_Mapped_FlipXY_Rot(a, b, c, d, e) (*cdraw16x16_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e)

// Mask functions (Rot)

extern ldraw_mapped_func_pri *pldraw16x16_Mask_Mapped_Flip_Rot[4];

#define pldraw16x16_Mask_Mapped_flip_Rot(a, b, c, d, e,f,g) (*pldraw16x16_Mask_Mapped_Flip_Rot[f])(a, b, c, d, e, g)

#define pldraw16x16_Mask_Mapped_Rot(a, b, c, d, e, f)        (*pldraw16x16_Mask_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pldraw16x16_Mask_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pldraw16x16_Mask_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pldraw16x16_Mask_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pldraw16x16_Mask_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pldraw16x16_Mask_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pldraw16x16_Mask_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

extern ldraw_mapped_func_pri *pldraw16x16_Mask_Trans_Mapped_Flip_Rot[4];

#define pldraw16x16_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f,g) (*pldraw16x16_Mask_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e,g)

#define pldraw16x16_Mask_Trans_Mapped_Rot(a, b, c, d, e, f)        (*pldraw16x16_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pldraw16x16_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pldraw16x16_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pldraw16x16_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pldraw16x16_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pldraw16x16_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pldraw16x16_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

// column scroll

extern ldraw_mapped_func_pri *pcdraw16x16_Mask_Mapped_Flip_Rot[4];

#define pcdraw16x16_Mask_Mapped_flip_Rot(a, b, c, d, e,f,g) (*pcdraw16x16_Mask_Mapped_Flip_Rot[f])(a, b, c, d, e,g)

#define pcdraw16x16_Mask_Mapped_Rot(a, b, c, d, e, f)        (*pcdraw16x16_Mask_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pcdraw16x16_Mask_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pcdraw16x16_Mask_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pcdraw16x16_Mask_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pcdraw16x16_Mask_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pcdraw16x16_Mask_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pcdraw16x16_Mask_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

extern ldraw_mapped_func_pri *pcdraw16x16_Mask_Trans_Mapped_Flip_Rot[4];

#define pcdraw16x16_Mask_Trans_Mapped_flip_Rot(a, b, c, d, e, f, g) (*pcdraw16x16_Mask_Trans_Mapped_Flip_Rot[f])(a, b, c, d, e, g)

#define pcdraw16x16_Mask_Trans_Mapped_Rot(a, b, c, d, e, f)        (*pcdraw16x16_Mask_Trans_Mapped_Flip_Rot[0])(a, b, c, d, e, f)
#define pcdraw16x16_Mask_Trans_Mapped_FlipY_Rot(a, b, c, d, e, f)  (*pcdraw16x16_Mask_Trans_Mapped_Flip_Rot[1])(a, b, c, d, e, f)
#define pcdraw16x16_Mask_Trans_Mapped_FlipX_Rot(a, b, c, d, e, f)  (*pcdraw16x16_Mask_Trans_Mapped_Flip_Rot[2])(a, b, c, d, e, f)
#define pcdraw16x16_Mask_Trans_Mapped_FlipXY_Rot(a, b, c, d, e, f) (*pcdraw16x16_Mask_Trans_Mapped_Flip_Rot[3])(a, b, c, d, e, f)

#endif

#ifdef __cplusplus
}
#endif
