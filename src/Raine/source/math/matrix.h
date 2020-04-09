#ifndef MATH_MATRIX_H__
#define MATH_MATRIX_H__

// Subset from math.h from retroarch

#define MAT_ELEM(mat, r, c) ((mat).data[4 * (c) + (r)])

// Colunm-major matrix (OpenGL-style).
// Reimplements functionality from FF OpenGL pipeline to be able to work on GLES 2.0 and modern GL variants.
typedef struct math_matrix
{
   float data[16];
} math_matrix;

void matrix_ortho(math_matrix *mat,
      float left, float right,
      float bottom, float top,
      float znear, float zfar);

#endif
