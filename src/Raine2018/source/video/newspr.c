/******************************************************************************/
/*                                                                            */
/*                RAINE TILE FLIPPING AND ROTATION SUPPORT                    */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "games.h"
#include "newspr.h"
#include "spr64.h"
#include "tilemod.h"

#include "zoom/16x16.h"
#include "zoom/16x8.h"
#include "lspr16.h"
#include "lspr8.h"
#include "pdraw.h"
#include "str_opaque.h"

static int disp_x;
static int disp_y;
int disp_x_8;
int disp_y_8;
int disp_x_16,disp_x_32;
int disp_y_16,disp_y_32;
static int disp_x_64; // What is the precise goal of these variables ???
static int disp_y_64;
struct DISPLAY_CFG display_cfg, game_display_cfg, prev_display_cfg;

/*

rotation support, using jumptables and precomputing as much as we can
it's a real macro overload, but rotation overhead is now *very small*

*/

#define ldraw16x16_Mapped ldraw16x16_Mapped_8
#define ldraw8x8_Mapped ldraw8x8_Mapped_8
#define pldraw16x16_Mask_Mapped pldraw16x16_Mask_Mapped_8
#define pldraw8x8_Mask_Mapped pldraw8x8_Mask_Mapped_8
#define cdraw16x16_Mapped cdraw16x16_Mapped_8
#define cdraw8x8_Mapped cdraw8x8_Mapped_8
#define pcdraw16x16_Mask_Mapped pcdraw16x16_Mask_Mapped_8
#define pcdraw8x8_Mask_Mapped pcdraw8x8_Mask_Mapped_8
#define ldraw16x16_Mapped_FlipX ldraw16x16_Mapped_8_FlipX
#define ldraw8x8_Mapped_FlipX ldraw8x8_Mapped_8_FlipX
#define cdraw16x16_Mapped_FlipX cdraw16x16_Mapped_8_FlipX
#define cdraw8x8_Mapped_FlipX cdraw8x8_Mapped_8_FlipX
#define pldraw16x16_Mask_Mapped_FlipX pldraw16x16_Mask_Mapped_8_FlipX
#define pldraw8x8_Mask_Mapped_FlipX pldraw8x8_Mask_Mapped_8_FlipX
#define pcdraw16x16_Mask_Mapped_FlipX pcdraw16x16_Mask_Mapped_8_FlipX
#define pcdraw8x8_Mask_Mapped_FlipX pcdraw8x8_Mask_Mapped_8_FlipX
#define ldraw16x16_Mapped_FlipY ldraw16x16_Mapped_8_FlipY
#define ldraw8x8_Mapped_FlipY ldraw8x8_Mapped_8_FlipY
#define cdraw16x16_Mapped_FlipY cdraw16x16_Mapped_8_FlipY
#define cdraw8x8_Mapped_FlipY cdraw8x8_Mapped_8_FlipY
#define pldraw16x16_Mask_Mapped_FlipY pldraw16x16_Mask_Mapped_8_FlipY
#define pldraw8x8_Mask_Mapped_FlipY pldraw8x8_Mask_Mapped_8_FlipY
#define pcdraw16x16_Mask_Mapped_FlipY pcdraw16x16_Mask_Mapped_8_FlipY
#define pcdraw8x8_Mask_Mapped_FlipY pcdraw8x8_Mask_Mapped_8_FlipY
#define ldraw16x16_Mapped_FlipXY ldraw16x16_Mapped_8_FlipXY
#define ldraw8x8_Mapped_FlipXY ldraw8x8_Mapped_8_FlipXY
#define cdraw16x16_Mapped_FlipXY cdraw16x16_Mapped_8_FlipXY
#define cdraw8x8_Mapped_FlipXY cdraw8x8_Mapped_8_FlipXY
#define pldraw16x16_Mask_Mapped_FlipXY pldraw16x16_Mask_Mapped_8_FlipXY
#define pldraw8x8_Mask_Mapped_FlipXY pldraw8x8_Mask_Mapped_8_FlipXY
#define pcdraw16x16_Mask_Mapped_FlipXY pcdraw16x16_Mask_Mapped_8_FlipXY
#define pcdraw8x8_Mask_Mapped_FlipXY pcdraw8x8_Mask_Mapped_8_FlipXY
#define ldraw16x16_Trans_Mapped ldraw16x16_Trans_Mapped_8
#define ldraw8x8_Trans_Mapped ldraw8x8_Trans_Mapped_8
#define pldraw16x16_Mask_Trans_Mapped pldraw16x16_Mask_Trans_Mapped_8
#define pldraw8x8_Mask_Trans_Mapped pldraw8x8_Mask_Trans_Mapped_8
#define cdraw16x16_Trans_Mapped cdraw16x16_Trans_Mapped_8
#define cdraw8x8_Trans_Mapped cdraw8x8_Trans_Mapped_8
#define pcdraw16x16_Mask_Trans_Mapped pcdraw16x16_Mask_Trans_Mapped_8
#define pcdraw8x8_Mask_Trans_Mapped pcdraw8x8_Mask_Trans_Mapped_8
#define ldraw16x16_Trans_Mapped_FlipX ldraw16x16_Trans_Mapped_8_FlipX
#define ldraw8x8_Trans_Mapped_FlipX ldraw8x8_Trans_Mapped_8_FlipX
#define pldraw16x16_Mask_Trans_Mapped_FlipX pldraw16x16_Mask_Trans_Mapped_8_FlipX
#define pldraw8x8_Mask_Trans_Mapped_FlipX pldraw8x8_Mask_Trans_Mapped_8_FlipX
#define cdraw16x16_Trans_Mapped_FlipX cdraw16x16_Trans_Mapped_8_FlipX
#define cdraw8x8_Trans_Mapped_FlipX cdraw8x8_Trans_Mapped_8_FlipX
#define pcdraw16x16_Mask_Trans_Mapped_FlipX pcdraw16x16_Mask_Trans_Mapped_8_FlipX
#define pcdraw8x8_Mask_Trans_Mapped_FlipX pcdraw8x8_Mask_Trans_Mapped_8_FlipX
#define ldraw16x16_Trans_Mapped_FlipY ldraw16x16_Trans_Mapped_8_FlipY
#define ldraw8x8_Trans_Mapped_FlipY ldraw8x8_Trans_Mapped_8_FlipY
#define pldraw16x16_Mask_Trans_Mapped_FlipY pldraw16x16_Mask_Trans_Mapped_8_FlipY
#define pldraw8x8_Mask_Trans_Mapped_FlipY pldraw8x8_Mask_Trans_Mapped_8_FlipY
#define cdraw16x16_Trans_Mapped_FlipY cdraw16x16_Trans_Mapped_8_FlipY
#define cdraw8x8_Trans_Mapped_FlipY cdraw8x8_Trans_Mapped_8_FlipY
#define pcdraw16x16_Mask_Trans_Mapped_FlipY pcdraw16x16_Mask_Trans_Mapped_8_FlipY
#define pcdraw8x8_Mask_Trans_Mapped_FlipY pcdraw8x8_Mask_Trans_Mapped_8_FlipY
#define ldraw16x16_Trans_Mapped_FlipXY ldraw16x16_Trans_Mapped_8_FlipXY
#define ldraw8x8_Trans_Mapped_FlipXY ldraw8x8_Trans_Mapped_8_FlipXY
#define pldraw16x16_Mask_Trans_Mapped_FlipXY pldraw16x16_Mask_Trans_Mapped_8_FlipXY
#define pldraw8x8_Mask_Trans_Mapped_FlipXY pldraw8x8_Mask_Trans_Mapped_8_FlipXY
#define cdraw16x16_Trans_Mapped_FlipXY cdraw16x16_Trans_Mapped_8_FlipXY
#define cdraw8x8_Trans_Mapped_FlipXY cdraw8x8_Trans_Mapped_8_FlipXY
#define pcdraw16x16_Mask_Trans_Mapped_FlipXY pcdraw16x16_Mask_Trans_Mapped_8_FlipXY
#define pcdraw8x8_Mask_Trans_Mapped_FlipXY pcdraw8x8_Mask_Trans_Mapped_8_FlipXY

#define MAKE_ROT_JUMP( FUNC, XOFS, YOFS )                                      \
                                                                               \
                                                                               \
static void FUNC##_R090(UINT8 *SPR, int x, int y, ARGS)                        \
{                                                                              \
   FUNC(SPR, YOFS - y, x,          ARGS_2);                                \
}                                                                              \
                                                                               \
static void FUNC##_R180(UINT8 *SPR, int x, int y, ARGS)                        \
{                                                                              \
   FUNC(SPR, XOFS - x, YOFS - y, ARGS_1);                                \
}                                                                              \
                                                                               \
static void FUNC##_R270(UINT8 *SPR, int x, int y, ARGS)                        \
{                                                                              \
   FUNC(SPR, y,          XOFS - x, ARGS_2);                                \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R090_X(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_FlipY(SPR, YOFS - y, x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_R180_X(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_FlipX(SPR, XOFS - x, YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_R270_X(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_FlipY(SPR, y,          XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R090_Y(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_FlipX(SPR, YOFS - y, x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_R180_Y(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_FlipY(SPR, XOFS - x, YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_R270_Y(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_FlipX(SPR, y,          XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R090_XY(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_FlipXY(SPR, YOFS - y, x,          ARGS_2);                         \
}                                                                              \
                                                                               \
static void FUNC##_R180_XY(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_FlipXY(SPR, XOFS - x, YOFS - y, ARGS_1);                         \
}                                                                              \
                                                                               \
static void FUNC##_R270_XY(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_FlipXY(SPR, y,          XOFS - x, ARGS_2);                         \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R000_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC(SPR, XOFS - x, y,          ARGS_1);                                \
}                                                                              \
                                                                               \
static void FUNC##_R090_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC(SPR, y,          x,          ARGS_2);                                \
}                                                                              \
                                                                               \
static void FUNC##_R180_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC(SPR, x,          YOFS - y, ARGS_1);                                \
}                                                                              \
                                                                               \
static void FUNC##_R270_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC(SPR, YOFS - y, XOFS - x, ARGS_2);                                \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R000_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipX(SPR, XOFS - x, y,          ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_R090_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipY(SPR, y,          x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_R180_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipX(SPR, x,          YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_R270_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipY(SPR, YOFS - y, XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R000_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipY(SPR, XOFS - x, y,          ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_R090_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipX(SPR, y,          x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_R180_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipY(SPR, x,          YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_R270_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_FlipX(SPR, YOFS - y, XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_R000_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_FlipXY(SPR, XOFS - x, y,          ARGS_1);                         \
}                                                                              \
                                                                               \
static void FUNC##_R090_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_FlipXY(SPR, y,          x,          ARGS_2);                         \
}                                                                              \
                                                                               \
static void FUNC##_R180_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_FlipXY(SPR, x,          YOFS - y, ARGS_1);                         \
}                                                                              \
                                                                               \
static void FUNC##_R270_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_FlipXY(SPR, YOFS - y, XOFS - x, ARGS_2);                         \
}                                                                              \
                                                                               \
                                                                               \
CMAP_FUNC *FUNC##_Flip_Rot[4];                                                 \
                                                                               \
static void FUNC##_init_jump_table(void)                                       \
{                                                                              \
   UINT32 i;                                                                    \
                                                                               \
   i  = display_cfg.rotate;                                                    \
   i ^= display_cfg.flip & 2;                                                  \
                                                                               \
   if((display_cfg.flip == 0) || (display_cfg.flip == 3)){                     \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC;                                            \
      FUNC##_Flip_Rot[1] = &FUNC##_FlipY;                                      \
      FUNC##_Flip_Rot[2] = &FUNC##_FlipX;                                      \
      FUNC##_Flip_Rot[3] = &FUNC##_FlipXY;                                     \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R090;                                       \
      FUNC##_Flip_Rot[1] = &FUNC##_R090_Y;                                     \
      FUNC##_Flip_Rot[2] = &FUNC##_R090_X;                                     \
      FUNC##_Flip_Rot[3] = &FUNC##_R090_XY;                                    \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R180;                                       \
      FUNC##_Flip_Rot[1] = &FUNC##_R180_Y;                                     \
      FUNC##_Flip_Rot[2] = &FUNC##_R180_X;                                     \
      FUNC##_Flip_Rot[3] = &FUNC##_R180_XY;                                    \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R270;                                       \
      FUNC##_Flip_Rot[1] = &FUNC##_R270_Y;                                     \
      FUNC##_Flip_Rot[2] = &FUNC##_R270_X;                                     \
      FUNC##_Flip_Rot[3] = &FUNC##_R270_XY;                                    \
   break;                                                                      \
   };                                                                          \
                                                                               \
   }                                                                           \
   else{                                                                       \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R000_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_R000_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_R000_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_R000_XY_FX;                                 \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R090_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_R090_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_R090_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_R090_XY_FX;                                 \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R180_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_R180_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_R180_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_R180_XY_FX;                                 \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_R270_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_R270_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_R270_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_R270_XY_FX;                                 \
   break;                                                                      \
   };                                                                          \
                                                                               \
   };                                                                          \
};                                                                             \
                                                                               \



/*

rotation support, using jumptables and precomputing as much as we can
it's a real macro overload, but rotation overhead is now *very small*

*/

#define MAKE_ROT_JUMP_16( FUNC, XOFS, YOFS )                                   \
                                                                               \
                                                                               \
static void FUNC##_8_R090(UINT8 *SPR, int x, int y, ARGS)                        \
{                                                                              \
   FUNC##_8(SPR, YOFS - y, x,          ARGS_2);                                \
}                                                                              \
                                                                               \
static void FUNC##_8_R180(UINT8 *SPR, int x, int y, ARGS)                        \
{                                                                              \
   FUNC##_8(SPR, XOFS - x, YOFS - y, ARGS_1);                                \
}                                                                              \
                                                                               \
static void FUNC##_8_R270(UINT8 *SPR, int x, int y, ARGS)                        \
{                                                                              \
   FUNC##_8(SPR, y,          XOFS - x, ARGS_2);                                \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R090_X(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_8_FlipY(SPR, YOFS - y, x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_X(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_8_FlipX(SPR, XOFS - x, YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_X(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_8_FlipY(SPR, y,          XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R090_Y(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_8_FlipX(SPR, YOFS - y, x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_Y(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_8_FlipY(SPR, XOFS - x, YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_Y(UINT8 *SPR, int x, int y, ARGS)                      \
{                                                                              \
   FUNC##_8_FlipX(SPR, y,          XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R090_XY(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8_FlipXY(SPR, YOFS - y, x,          ARGS_2);                         \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_XY(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8_FlipXY(SPR, XOFS - x, YOFS - y, ARGS_1);                         \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_XY(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8_FlipXY(SPR, y,          XOFS - x, ARGS_2);                         \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R000_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8(SPR, XOFS - x, y,          ARGS_1);                                \
}                                                                              \
                                                                               \
static void FUNC##_8_R090_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8(SPR, y,          x,          ARGS_2);                                \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8(SPR, x,          YOFS - y, ARGS_1);                                \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_FX(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_8(SPR, YOFS - y, XOFS - x, ARGS_2);                                \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R000_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipX(SPR, XOFS - x, y,          ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R090_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipY(SPR, y,          x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipX(SPR, x,          YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_X_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipY(SPR, YOFS - y, XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R000_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipY(SPR, XOFS - x, y,          ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R090_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipX(SPR, y,          x,          ARGS_2);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipY(SPR, x,          YOFS - y, ARGS_1);                          \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_Y_FX(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_8_FlipX(SPR, YOFS - y, XOFS - x, ARGS_2);                          \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_8_R000_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_8_FlipXY(SPR, XOFS - x, y,          ARGS_1);                         \
}                                                                              \
                                                                               \
static void FUNC##_8_R090_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_8_FlipXY(SPR, y,          x,          ARGS_2);                         \
}                                                                              \
                                                                               \
static void FUNC##_8_R180_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_8_FlipXY(SPR, x,          YOFS - y, ARGS_1);                         \
}                                                                              \
                                                                               \
static void FUNC##_8_R270_XY_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_8_FlipXY(SPR, YOFS - y, XOFS - x, ARGS_2);                         \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R090(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_16(SPR, YOFS - y, x,          ARGS_2);                             \
}                                                                              \
                                                                               \
static void FUNC##_16_R180(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_16(SPR, XOFS - x, YOFS - y, ARGS_1);                             \
}                                                                              \
                                                                               \
static void FUNC##_16_R270(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_16(SPR, y,          XOFS - x, ARGS_2);                             \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R090_X(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_16_FlipY(SPR, YOFS - y, x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_X(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_16_FlipX(SPR, XOFS - x, YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_X(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_16_FlipY(SPR, y,          XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R090_Y(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_16_FlipX(SPR, YOFS - y, x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_Y(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_16_FlipY(SPR, XOFS - x, YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_Y(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_16_FlipX(SPR, y,          XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R090_XY(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16_FlipXY(SPR, YOFS - y, x,          ARGS_2);                      \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_XY(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16_FlipXY(SPR, XOFS - x, YOFS - y, ARGS_1);                      \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_XY(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16_FlipXY(SPR, y,          XOFS - x, ARGS_2);                      \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R000_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16(SPR, XOFS - x, y,          ARGS_1);                             \
}                                                                              \
                                                                               \
static void FUNC##_16_R090_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16(SPR, y,          x,          ARGS_2);                             \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16(SPR, x,          YOFS - y, ARGS_1);                             \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_16(SPR, YOFS - y, XOFS - x, ARGS_2);                             \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R000_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipX(SPR, XOFS - x, y,          ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R090_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipY(SPR, y,          x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipX(SPR, x,          YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipY(SPR, YOFS - y, XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R000_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipY(SPR, XOFS - x, y,          ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R090_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipX(SPR, y,          x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipY(SPR, x,          YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_16_FlipX(SPR, YOFS - y, XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_16_R000_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_16_FlipXY(SPR, XOFS - x, y,          ARGS_1);                      \
}                                                                              \
                                                                               \
static void FUNC##_16_R090_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_16_FlipXY(SPR, y,          x,          ARGS_2);                      \
}                                                                              \
                                                                               \
static void FUNC##_16_R180_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_16_FlipXY(SPR, x,          YOFS - y, ARGS_1);                      \
}                                                                              \
                                                                               \
static void FUNC##_16_R270_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_16_FlipXY(SPR, YOFS - y, XOFS - x, ARGS_2);                      \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R090(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_32(SPR, YOFS - y, x,          ARGS_2);                             \
}                                                                              \
                                                                               \
static void FUNC##_32_R180(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_32(SPR, XOFS - x, YOFS - y, ARGS_1);                             \
}                                                                              \
                                                                               \
static void FUNC##_32_R270(UINT8 *SPR, int x, int y, ARGS)                     \
{                                                                              \
   FUNC##_32(SPR, y,          XOFS - x, ARGS_2);                             \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R090_X(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_32_FlipY(SPR, YOFS - y, x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_X(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_32_FlipX(SPR, XOFS - x, YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_X(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_32_FlipY(SPR, y,          XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R090_Y(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_32_FlipX(SPR, YOFS - y, x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_Y(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_32_FlipY(SPR, XOFS - x, YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_Y(UINT8 *SPR, int x, int y, ARGS)                   \
{                                                                              \
   FUNC##_32_FlipX(SPR, y,          XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R090_XY(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32_FlipXY(SPR, YOFS - y, x,          ARGS_2);                      \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_XY(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32_FlipXY(SPR, XOFS - x, YOFS - y, ARGS_1);                      \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_XY(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32_FlipXY(SPR, y,          XOFS - x, ARGS_2);                      \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R000_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32(SPR, XOFS - x, y,          ARGS_1);                             \
}                                                                              \
                                                                               \
static void FUNC##_32_R090_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32(SPR, y,          x,          ARGS_2);                             \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32(SPR, x,          YOFS - y, ARGS_1);                             \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_FX(UINT8 *SPR, int x, int y, ARGS)                  \
{                                                                              \
   FUNC##_32(SPR, YOFS - y, XOFS - x, ARGS_2);                             \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R000_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipX(SPR, XOFS - x, y,          ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R090_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipY(SPR, y,          x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipX(SPR, x,          YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_X_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipY(SPR, YOFS - y, XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R000_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipY(SPR, XOFS - x, y,          ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R090_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipX(SPR, y,          x,          ARGS_2);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipY(SPR, x,          YOFS - y, ARGS_1);                       \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_Y_FX(UINT8 *SPR, int x, int y, ARGS)                \
{                                                                              \
   FUNC##_32_FlipX(SPR, YOFS - y, XOFS - x, ARGS_2);                       \
}                                                                              \
                                                                               \
                                                                               \
static void FUNC##_32_R000_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_32_FlipXY(SPR, XOFS - x, y,          ARGS_1);                      \
}                                                                              \
                                                                               \
static void FUNC##_32_R090_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_32_FlipXY(SPR, y,          x,          ARGS_2);                      \
}                                                                              \
                                                                               \
static void FUNC##_32_R180_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_32_FlipXY(SPR, x,          YOFS - y, ARGS_1);                      \
}                                                                              \
                                                                               \
static void FUNC##_32_R270_XY_FX(UINT8 *SPR, int x, int y, ARGS)               \
{                                                                              \
   FUNC##_32_FlipXY(SPR, YOFS - y, XOFS - x, ARGS_2);                      \
}                                                                              \
                                                                               \
                                                                               \
CMAP_FUNC *FUNC##_Flip_Rot[4];                                                 \
                                                                               \
static void FUNC##_init_jump_table(void)                                       \
{                                                                              \
   UINT32 i;                                                                   \
                                                                               \
   i  = display_cfg.rotate;                                                    \
   i ^= display_cfg.flip & 2;                                                  \
                                                                               \
   switch(internal_bpp(display_cfg.bpp)){                                      \
   case 8:                                                                     \
                                                                               \
   if((display_cfg.flip == 0) || (display_cfg.flip == 3)){                     \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8;                                            \
      FUNC##_Flip_Rot[1] = &FUNC##_8_FlipY;                                      \
      FUNC##_Flip_Rot[2] = &FUNC##_8_FlipX;                                      \
      FUNC##_Flip_Rot[3] = &FUNC##_8_FlipXY;                                     \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R090;                                       \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R090_Y;                                     \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R090_X;                                     \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R090_XY;                                    \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R180;                                       \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R180_Y;                                     \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R180_X;                                     \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R180_XY;                                    \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R270;                                       \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R270_Y;                                     \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R270_X;                                     \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R270_XY;                                    \
   break;                                                                      \
   };                                                                          \
                                                                               \
   }                                                                           \
   else{                                                                       \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R000_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R000_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R000_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R000_XY_FX;                                 \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R090_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R090_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R090_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R090_XY_FX;                                 \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R180_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R180_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R180_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R180_XY_FX;                                 \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_8_R270_FX;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_8_R270_Y_FX;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_8_R270_X_FX;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_8_R270_XY_FX;                                 \
   break;                                                                      \
   };                                                                          \
                                                                               \
   };                                                                          \
                                                                               \
   break;                                                                      \
   case 16:                                                                    \
                                                                               \
   if((display_cfg.flip == 0) || (display_cfg.flip == 3)){                     \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16;                                         \
      FUNC##_Flip_Rot[1] = &FUNC##_16_FlipY;                                   \
      FUNC##_Flip_Rot[2] = &FUNC##_16_FlipX;                                   \
      FUNC##_Flip_Rot[3] = &FUNC##_16_FlipXY;                                  \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R090;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R090_Y;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R090_X;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R090_XY;                                 \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R180;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R180_Y;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R180_X;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R180_XY;                                 \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R270;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R270_Y;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R270_X;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R270_XY;                                 \
   break;                                                                      \
   };                                                                          \
                                                                               \
   }                                                                           \
   else{                                                                       \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R000_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R000_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R000_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R000_XY_FX;                              \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R090_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R090_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R090_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R090_XY_FX;                              \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R180_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R180_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R180_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R180_XY_FX;                              \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_16_R270_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_16_R270_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_16_R270_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_16_R270_XY_FX;                              \
   break;                                                                      \
   };                                                                          \
                                                                               \
   };                                                                          \
                                                                               \
   break;                                                                      \
   case 32:                                                                    \
                                                                               \
   if((display_cfg.flip == 0) || (display_cfg.flip == 3)){                     \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32;                                         \
      FUNC##_Flip_Rot[1] = &FUNC##_32_FlipY;                                   \
      FUNC##_Flip_Rot[2] = &FUNC##_32_FlipX;                                   \
      FUNC##_Flip_Rot[3] = &FUNC##_32_FlipXY;                                  \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R090;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R090_Y;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R090_X;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R090_XY;                                 \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R180;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R180_Y;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R180_X;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R180_XY;                                 \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R270;                                    \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R270_Y;                                  \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R270_X;                                  \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R270_XY;                                 \
   break;                                                                      \
   };                                                                          \
                                                                               \
   }                                                                           \
   else{                                                                       \
                                                                               \
   switch(i){                                                                  \
   case 0:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R000_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R000_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R000_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R000_XY_FX;                              \
   break;                                                                      \
   case 1:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R090_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R090_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R090_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R090_XY_FX;                              \
   break;                                                                      \
   case 2:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R180_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R180_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R180_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R180_XY_FX;                              \
   break;                                                                      \
   case 3:                                                                     \
      FUNC##_Flip_Rot[0] = &FUNC##_32_R270_FX;                                 \
      FUNC##_Flip_Rot[1] = &FUNC##_32_R270_Y_FX;                               \
      FUNC##_Flip_Rot[2] = &FUNC##_32_R270_X_FX;                               \
      FUNC##_Flip_Rot[3] = &FUNC##_32_R270_XY_FX;                              \
   break;                                                                      \
   };                                                                          \
                                                                               \
   };                                                                          \
                                                                               \
   break;                                                                      \
   };                                                                          \
};                                                                             \
                                                                               \
/*

prepare for mapper direct routines

*/

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 cmap
#define ARGS_1    cmap
#define ARGS_2    cmap
#define CMAP_FUNC draw_func

/*

generate direct mapped routines

*/

MAKE_ROT_JUMP( Draw8x8_8,       disp_x_8, disp_y_8 )

MAKE_ROT_JUMP( Draw8x8_Trans_8, disp_x_8, disp_y_8 )

  /* Notice : the cmap parameter is not used at all by the Draw16x16_16 functions, but
     removing it would force to create new versions of the macros, a few hundreds lines!*/

MAKE_ROT_JUMP_16( Draw16x16,       disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( Draw16x16_Trans, disp_x_16, disp_y_16 )

// MAKE_ROT_JUMP( Draw32x32_16,       disp_x_32, disp_y_32 )
// MAKE_ROT_JUMP( Draw32x32_Trans_16, disp_x_32, disp_y_32 )
MAKE_ROT_JUMP_16( Draw32x32,       disp_x_32, disp_y_32 )
MAKE_ROT_JUMP_16( Draw32x32_Trans, disp_x_32, disp_y_32 )

MAKE_ROT_JUMP( Draw32x32_Trans_Alpha50_16, disp_x_32, disp_y_32 )
MAKE_ROT_JUMP( Draw32x32_Trans_Alpha50_32, disp_x_32, disp_y_32 )
MAKE_ROT_JUMP( Draw32x32_Trans_Alpha_16, disp_x_32, disp_y_32 )
MAKE_ROT_JUMP( Draw32x32_Trans_Alpha_32, disp_x_32, disp_y_32 )

MAKE_ROT_JUMP( Draw16x16_Mask_Trans, disp_x_16, disp_y_16 )
MAKE_ROT_JUMP( Draw16x16_Mask, disp_x_16, disp_y_16 )

/*

prepare for colour mapped routines

*/

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap
#define ARGS_1    cmap
#define ARGS_2    cmap
#define CMAP_FUNC draw_mapped_func

/*

generate mapped routines

*/

MAKE_ROT_JUMP_16( Draw8x8_Mapped,         disp_x_8,  disp_y_8  )

MAKE_ROT_JUMP_16( Draw8x8_Trans_Mapped,   disp_x_8,  disp_y_8  )

MAKE_ROT_JUMP_16( Draw8x8_Trans_Packed_Mapped, disp_x_8, disp_y_8 )

MAKE_ROT_JUMP_16( Draw8x8_Trans_Packed_Mapped_SwapWord, disp_x_8, disp_y_8 )

MAKE_ROT_JUMP_16( Draw16x16_Mapped,       disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( Draw16x16_Trans_Mapped, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( Draw16x16_Trans_Mapped_Alpha, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( Draw16x16_Mapped_Alpha, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( Draw16x8_Mapped,       disp_x_16, disp_y_8 )

MAKE_ROT_JUMP_16( Draw16x8_Trans_Mapped, disp_x_16, disp_y_8 )

MAKE_ROT_JUMP_16( Draw32x32_Mapped,       disp_x_32, disp_y_32 )

MAKE_ROT_JUMP_16( Draw32x32_Trans_Mapped, disp_x_32, disp_y_32 )

MAKE_ROT_JUMP_16( Draw64x64_Mapped,       disp_x_64, disp_y_64 )

/*

Generate move routines

*/

MAKE_ROT_JUMP_16( Move8x8,       disp_x_8, disp_y_8 )

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap, UINT8 pri
#define ARGS_1    cmap, pri
#define ARGS_2    cmap, pri
#define CMAP_FUNC draw_mapped_func_pri

MAKE_ROT_JUMP_16( pdraw16x16_Mapped,       disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pdraw16x16_Trans_Mapped, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( pdraw16x16_Mapped_back,       disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pdraw16x16_Trans_Mapped_back, disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pdraw16x16_Mapped_back_Alpha,       disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pdraw16x16_Trans_Mapped_back_Alpha, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( pdraw16x16_Mask_Mapped,       disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pdraw16x16_Mask_Trans_Mapped, disp_x_16, disp_y_16 )


MAKE_ROT_JUMP_16( pdraw8x8_Mapped,       disp_x_8, disp_y_8 )
MAKE_ROT_JUMP_16( pdraw8x8_Trans_Mapped, disp_x_8, disp_y_8 )

MAKE_ROT_JUMP_16( pdraw8x8_Mask_Mapped,       disp_x_8, disp_y_8 )
MAKE_ROT_JUMP_16( pdraw8x8_Mask_Trans_Mapped, disp_x_8, disp_y_8 )

MAKE_ROT_JUMP_16( pdraw32x32_Mask_Mapped,       disp_x_32, disp_y_32 )
MAKE_ROT_JUMP_16( pdraw32x32_Mask_Trans_Mapped, disp_x_32, disp_y_32 )

  // add_tile_cache

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      int ta
#define ARGS_1    ta
#define ARGS_2    ta
#define CMAP_FUNC add_move_func

  // The line below produces tons of warnings, and I have no idea why !!!
MAKE_ROT_JUMP_16( add_tile_cache,       disp_x_8, disp_y_8 )

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      int height, UINT8 *cmap
#define ARGS_1    height, cmap
#define ARGS_2    height, cmap
#define CMAP_FUNC drawh_mapped_func

MAKE_ROT_JUMP_16( Draw8xH_Trans_Packed_Mapped,       disp_x_64, disp_y_64 )

/*

prepare for linescroll routines

*/

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap, INT16 *dy
#define ARGS_1    cmap, dy
#define ARGS_2    cmap, dy
#define CMAP_FUNC ldraw_mapped_func


MAKE_ROT_JUMP_16( ldraw16x16_Mapped,       disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( ldraw16x16_Trans_Mapped, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( cdraw16x16_Mapped,       disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( cdraw16x16_Trans_Mapped, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( ldraw8x8_Mapped,       disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( ldraw8x8_Trans_Mapped, disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( cdraw8x8_Mapped,       disp_x_16, disp_y_16 )

MAKE_ROT_JUMP_16( cdraw8x8_Trans_Mapped, disp_x_16, disp_y_16 )

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap, INT16 *dy, UINT8 pri
#define ARGS_1    cmap, dy, pri
#define ARGS_2    cmap, dy, pri
#define CMAP_FUNC ldraw_mapped_func_pri

MAKE_ROT_JUMP_16( pldraw16x16_Mask_Trans_Mapped, disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pldraw16x16_Mask_Mapped, disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pcdraw16x16_Mask_Trans_Mapped, disp_x_16, disp_y_16 )
MAKE_ROT_JUMP_16( pcdraw16x16_Mask_Mapped, disp_x_16, disp_y_16 )

/*

prepare for colour mapped zoom xy routines

*/

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap, int zoom_x, int zoom_y
#define ARGS_1    cmap, zoom_x, zoom_y
#define ARGS_2    cmap, zoom_y, zoom_x
#define CMAP_FUNC draw_mapped_zoom_xy_func

  /* Note : I still don't know why we have _32 zoom functions and 64
     since 64 are zooming from 0 to 63 and 32 from 0 to 31 ???
     It is probably because of speed (or quality ?)... */

MAKE_ROT_JUMP_16( Draw16x16_Trans_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x16_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x16_Trans_Mapped_ZoomXY_Alpha,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x16_Mapped_ZoomXY_Alpha,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x8_Trans_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x8_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x16_32_Trans_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw16x16_32_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )

MAKE_ROT_JUMP_16( Draw16x16_64_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )

MAKE_ROT_JUMP_16( Draw16x16_64_Trans_Mapped_ZoomXY, (disp_x - zoom_x), (disp_y - zoom_y) )

MAKE_ROT_JUMP_16( Draw64x64_Trans_Mapped_Zoom2,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( Draw64x64_Mapped_Zoom2,       (disp_x - zoom_x), (disp_y - zoom_y) )

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap, int zoom
#define ARGS_1    cmap, zoom
#define ARGS_2    cmap, zoom
#define CMAP_FUNC draw_mapped_zoom_func

MAKE_ROT_JUMP_16( Draw64x64_Trans_Mapped_Zoom,       (disp_x - zoom), (disp_y - zoom) )

#undef ARGS
#undef ARGS_1
#undef ARGS_2
#undef CMAP_FUNC

#define ARGS      UINT8 *cmap, int zoom_x, int zoom_y, int pri
#define ARGS_1    cmap, zoom_x, zoom_y, pri
#define ARGS_2    cmap, zoom_y, zoom_x, pri
#define CMAP_FUNC draw_mapped_zoom_xy_func_pri

MAKE_ROT_JUMP_16( pdraw16x16_Trans_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( pdraw16x16_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( pdraw16x16_64_Trans_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( pdraw16x16_64_Mapped_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( pdraw16x16_64_Trans_Mapped_back_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )
MAKE_ROT_JUMP_16( pdraw16x16_64_Mapped_back_ZoomXY,       (disp_x - zoom_x), (disp_y - zoom_y) )

text_func *textout_fast;
draw_pixel_func *raine_put_pixel;

// Pixel functions : can draw a pixel to the game bitmap in any depth
// does not support rotation for now... oh well...

void raine_put_pixel_8(UINT8 *line, int xoff, UINT32 *pal, int color) {
  line[xoff] = pal[color];
}

void raine_put_pixel_16(UINT8 *line, int xoff, UINT32 *pal, int color) {
  ((UINT16*)line)[xoff] = pal[color];
}

void raine_put_pixel_32(UINT8 *line, int xoff, UINT32 *pal, int color) {
  ((UINT32*)line)[xoff] = pal[color];
}

void init_video_core(void)
{
   const VIDEO_INFO *vid_info;
   ldraw_mapped_func *temp_ldraw[4];
   ldraw_mapped_func_pri *temp_ldraw_mask[4];

   // convenient screen data

   vid_info = current_game->video;

   disp_x = vid_info->border_size + vid_info->screen_x + vid_info->border_size;
   disp_y = vid_info->border_size + vid_info->screen_y + vid_info->border_size;

   disp_x_8 = disp_x - 8;
   disp_y_8 = disp_y - 8;

   disp_x_16 = disp_x - 16;
   disp_y_16 = disp_y - 16;

   disp_x_32 = disp_x - 32;
   disp_y_32 = disp_y - 32;

   disp_x_64 = disp_x - 64;
   disp_y_64 = disp_y - 64;

   // rotation jumptables

   Draw8x8_8_init_jump_table();
   Draw8x8_Trans_8_init_jump_table();
   Draw16x16_init_jump_table();
   Draw16x16_Trans_init_jump_table();
   Draw32x32_init_jump_table();
   Draw32x32_Trans_init_jump_table();

   Draw32x32_Trans_Alpha50_16_init_jump_table();
   Draw32x32_Trans_Alpha50_32_init_jump_table();
   Draw32x32_Trans_Alpha_16_init_jump_table();
   Draw32x32_Trans_Alpha_32_init_jump_table();

   Draw16x16_Mask_Trans_init_jump_table();
   Draw16x16_Mask_init_jump_table();

   Draw8x8_Mapped_init_jump_table();
   Draw8x8_Trans_Mapped_init_jump_table();

   Draw8x8_Trans_Packed_Mapped_init_jump_table();
   Draw8x8_Trans_Packed_Mapped_SwapWord_init_jump_table();

   Draw16x16_Mapped_init_jump_table();
   Draw16x16_Trans_Mapped_init_jump_table();
   Draw16x16_Trans_Mapped_Alpha_init_jump_table();
   Draw16x16_Mapped_Alpha_init_jump_table();
   Draw16x8_Mapped_init_jump_table();
   Draw16x8_Trans_Mapped_init_jump_table();

   pdraw16x16_Mapped_init_jump_table();
   pdraw16x16_Trans_Mapped_init_jump_table();
   pdraw16x16_Mapped_back_init_jump_table();
   pdraw16x16_Trans_Mapped_back_init_jump_table();
   pdraw16x16_Mapped_back_Alpha_init_jump_table();
   pdraw16x16_Trans_Mapped_back_Alpha_init_jump_table();
   pdraw16x16_Mask_Mapped_init_jump_table();
   pdraw16x16_Mask_Trans_Mapped_init_jump_table();

   pdraw8x8_Mapped_init_jump_table();
   pdraw8x8_Trans_Mapped_init_jump_table();

   pdraw8x8_Mask_Mapped_init_jump_table();
   pdraw8x8_Mask_Trans_Mapped_init_jump_table();

   pdraw32x32_Mask_Mapped_init_jump_table();
   pdraw32x32_Mask_Trans_Mapped_init_jump_table();

   Draw32x32_Mapped_init_jump_table();
   Draw32x32_Trans_Mapped_init_jump_table();

   Draw16x16_Mapped_ZoomXY_init_jump_table();
   Draw16x16_Trans_Mapped_ZoomXY_init_jump_table();
   Draw16x16_Mapped_ZoomXY_Alpha_init_jump_table();
   Draw16x16_Trans_Mapped_ZoomXY_Alpha_init_jump_table();
   Draw64x64_Mapped_Zoom2_init_jump_table();
   Draw64x64_Trans_Mapped_Zoom2_init_jump_table();
   Draw16x8_Mapped_ZoomXY_init_jump_table();
   Draw16x8_Trans_Mapped_ZoomXY_init_jump_table();

   pdraw16x16_Mapped_ZoomXY_init_jump_table();
   pdraw16x16_Trans_Mapped_ZoomXY_init_jump_table();

   pdraw16x16_64_Mapped_ZoomXY_init_jump_table();
   pdraw16x16_64_Trans_Mapped_ZoomXY_init_jump_table();
   pdraw16x16_64_Mapped_back_ZoomXY_init_jump_table();
   pdraw16x16_64_Trans_Mapped_back_ZoomXY_init_jump_table();

   Draw16x16_32_Mapped_ZoomXY_init_jump_table();
   Draw16x16_32_Trans_Mapped_ZoomXY_init_jump_table();
   Draw16x16_64_Mapped_ZoomXY_init_jump_table();
   Draw16x16_64_Trans_Mapped_ZoomXY_init_jump_table();

   Draw64x64_Trans_Mapped_Zoom_init_jump_table();

   Draw64x64_Mapped_init_jump_table();

   Draw8xH_Trans_Packed_Mapped_init_jump_table();

   // Move

   Move8x8_init_jump_table();
   add_tile_cache_init_jump_table();
   init_moveasm();

   // Line scroll

   ldraw16x16_Mapped_init_jump_table();
   ldraw16x16_Trans_Mapped_init_jump_table();

   cdraw16x16_Mapped_init_jump_table();
   cdraw16x16_Trans_Mapped_init_jump_table();

   ldraw8x8_Mapped_init_jump_table();
   ldraw8x8_Trans_Mapped_init_jump_table();

   cdraw8x8_Mapped_init_jump_table();
   cdraw8x8_Trans_Mapped_init_jump_table();

   pldraw16x16_Mask_Trans_Mapped_init_jump_table();
   pldraw16x16_Mask_Mapped_init_jump_table();
   pcdraw16x16_Mask_Trans_Mapped_init_jump_table();
   pcdraw16x16_Mask_Mapped_init_jump_table();

   switch(VIDEO_ROTATE( vid_info->flags ^ display_cfg.user_rotate)){
   case VIDEO_ROTATE_90:
     // Not supported for line scroll...
     // but I'll convert it as 270 to avoid the crash
   case VIDEO_ROTATE_270:
     memcpy(temp_ldraw,cdraw16x16_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(cdraw16x16_Mapped_Flip_Rot,ldraw16x16_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(ldraw16x16_Mapped_Flip_Rot,temp_ldraw,
	    sizeof(ldraw_mapped_func *)*4);

     memcpy(temp_ldraw_mask,pcdraw16x16_Mask_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func_pri *)*4);
     memcpy(pcdraw16x16_Mask_Mapped_Flip_Rot,pldraw16x16_Mask_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func_pri *)*4);
     memcpy(pldraw16x16_Mask_Mapped_Flip_Rot,temp_ldraw_mask,
	    sizeof(ldraw_mapped_func_pri *)*4);

     memcpy(temp_ldraw,cdraw16x16_Trans_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(cdraw16x16_Trans_Mapped_Flip_Rot,ldraw16x16_Trans_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(ldraw16x16_Trans_Mapped_Flip_Rot,temp_ldraw,
	    sizeof(ldraw_mapped_func *)*4);

     memcpy(temp_ldraw_mask,pcdraw16x16_Mask_Trans_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func_pri *)*4);
     memcpy(pcdraw16x16_Mask_Trans_Mapped_Flip_Rot,pldraw16x16_Mask_Trans_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func_pri *)*4);
     memcpy(pldraw16x16_Mask_Trans_Mapped_Flip_Rot,temp_ldraw_mask,
	    sizeof(ldraw_mapped_func_pri *)*4);

     memcpy(temp_ldraw,cdraw8x8_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(cdraw8x8_Mapped_Flip_Rot,ldraw8x8_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(ldraw8x8_Mapped_Flip_Rot,temp_ldraw,
	    sizeof(ldraw_mapped_func *)*4);

     memcpy(temp_ldraw,cdraw8x8_Trans_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(cdraw8x8_Trans_Mapped_Flip_Rot,ldraw8x8_Trans_Mapped_Flip_Rot,
	    sizeof(ldraw_mapped_func *)*4);
     memcpy(ldraw8x8_Trans_Mapped_Flip_Rot,temp_ldraw,
	    sizeof(ldraw_mapped_func *)*4);

     break;
   }

   // 8bpp sprites

   init_spr8x8asm_8();
   init_spr8x8asm_16();
   init_spr8x8asm_32();

   init_spr16x8asm();
   init_spr16x8asm_16();
   init_spr16x8asm_32();

   init_spr16x16asm_8();
   init_spr16x16asm_16();
   init_spr16x16asm_32();

   init_spr32x32asm_8();
   init_spr32x32asm_16();
   init_spr32x32asm_32();

   // 4bpp sprites

   init_spp8x8asm_8();
   init_spp8x8asm_16();
   init_spp8x8asm_32();

   // 1bpp text

   init_str6x8asm();
   init_str6x8asm_16();
   init_str6x8asm_32();

   // 64x64 and 8xH
   init_newspr2asm();
   init_newspr2asm_16();
   init_newspr2asm_32();

   switch(internal_bpp(display_cfg.bpp)){
      case 8:
	  if (opaque_hud)
	      textout_fast = &draw_string_6x8_opaque;
	  else
	      textout_fast = &draw_string_6x8;
	 raine_put_pixel = &raine_put_pixel_8;
      break;
      case 16:
	  if (opaque_hud)
	      textout_fast = &draw_string_6x8_opaque_16;
	  else
	      textout_fast = &draw_string_6x8_16;
	 raine_put_pixel = &raine_put_pixel_16;
      break;
      case 32:
	  if (opaque_hud)
	      textout_fast = &draw_string_6x8_opaque_32;
	  else
	      textout_fast = &draw_string_6x8_32;
	 raine_put_pixel = &raine_put_pixel_32;
      break;
   }
}

/******************************************************************************/

