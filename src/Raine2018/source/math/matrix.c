#include "matrix.h"
#include <string.h>

static void matrix_identity(math_matrix *mat)
{
    unsigned i;
   memset(mat, 0, sizeof(*mat));
   for (i = 0; i < 4; i++)
      MAT_ELEM(*mat, i, i) = 1.0f;
}

void matrix_ortho(math_matrix *mat,
      float left, float right,
      float bottom, float top,
      float znear, float zfar)
{
   matrix_identity(mat);

   float tx = -(right + left) / (right - left);
   float ty = -(top + bottom) / (top - bottom);
   float tz = -(zfar + znear) / (zfar - znear);

   MAT_ELEM(*mat, 0, 0) =  2.0f / (right - left);
   MAT_ELEM(*mat, 1, 1) =  2.0f / (top - bottom);
   MAT_ELEM(*mat, 2, 2) = -2.0f / (zfar - znear);
   MAT_ELEM(*mat, 0, 3) = tx;
   MAT_ELEM(*mat, 1, 3) = ty;
   MAT_ELEM(*mat, 2, 3) = tz;
}
