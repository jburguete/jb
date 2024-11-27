/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
 *
 * Copyright 2005-2024, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file math_avx512.h
 * \brief Header file with useful mathematical functions for __m512.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2024, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_AVX512__H
#define JB_MATH_AVX512__H 1

/**
 * union to work with bits in 8 packed float numbers.
 */
typedef union
{
  __m512 x;                     ///< floating point.
  __m512i i;                    ///< bits.
} JBM16xF32;

/**
 * union to work with bits in 2 packed double numbers.
 */
typedef union
{
  __m512d x;                    ///< floating point.
  __m512i i;                    ///< bits.
} JBM8xF64;

/* Debug functions

static inline void
print_m512i32 (FILE *file, const char *label, __m512i x)
{
  int y[16] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi32 (y, x);
  for (i = 0; i < 16; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m512i64 (FILE *file, const char *label, __m512i x)
{
  long long int y[8] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi64 (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_m512 (FILE *file, const char *label, __m512 x)
{
  float y[16] JB_ALIGNED;
  unsigned int i;
  _mm512_store_ps (y, x);
  for (i = 0; i < 16; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m512d (FILE *file, const char *label, __m512d x)
{
  double y[8] JB_ALIGNED;
  unsigned int i;
  _mm512_store_pd (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

*/

/**
 * Function to calculate the additive inverse value of a __m512 vector.
 *
 * \return opposite value vector (__m512).
 */
static inline __m512
jbm_opposite_16xf32 (const __m512 x)    ///< __m512 vector.
{
  JBM16xF32 y;
  y.i = _mm512_set1_epi32 ((int) 0x80000000);
  return _mm512_xor_ps (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m512 vector.
 *
 * \return reciprocal value vector (__m512).
 */
static inline __m512
jbm_reciprocal_16xf32 (const __m512 x)  ///< __m512 vector.
{
  return _mm512_rcp14_ps (x);
}

/**
 * Function to calculate the absolute value of a __m512 vector.
 *
 * \return absolute value vector (__m512).
 */
static inline __m512
jbm_abs_16xf32 (const __m512 x) ///< __m512 vector.
{
  JBM16xF32 y;
  y.i = _mm512_set1_epi32 (0x7fffffffl);
  return _mm512_and_ps (x, y.x);
}

/**
 * Function to calculate the hypot function (__m512).
 *
 * \return function value vector (__m512).
 */
static inline __m512
jbm_hypot_16xf32 (const __m512 x,       ///< 1st __m512 vector.
                  const __m512 y)       ///< 2nd __m512 vector.
{
  return _mm512_sqrt_ps (_mm512_fmadd_ps (x, x, _mm512_mul_ps (y, y)));
}

/**
 * Function to calculate the rest of a division (__m512).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline __m512
jbm_rest_16xf32 (const __m512 x,        ///< dividend (__m512).
                 const __m512 d)        ///< divisor (__m512).
{
  return _mm512_fnmadd_ps (_mm512_floor_ps (_mm512_div_ps (x, d)), d, x);
}

/**
 * Function to implement the standard frexp function (__m512).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m512
jbm_frexp_16xf32 (const __m512 x,       ///< __m512 vector.
                  __m512i *e)   ///< pointer to the extracted exponents vector.
{
  JBM16xF32 a, y, y2, z;
  __m512i e16, b, zi;
  __mmask16 m1, m2, m3;
  a.x = x;
  b = _mm512_set1_epi32 (0x7f800000);
  y.i = _mm512_and_si512 (a.i, b);
  m1 = _mm512_cmpeq_epi32_mask (y.i, b);
  zi = _mm512_setzero_si512 ();
  m2 = _mm512_cmpeq_epi32_mask (y.i, zi);
  y2.x = x;
  y2.i = _mm512_and_si512 (y2.i, _mm512_set1_epi32 (0x007fffff));
  m3 = _mm512_cmpeq_epi32_mask (y2.i, zi);
  y2.i = _mm512_set1_epi32 (0x00400000);
  z.x = _mm512_div_ps (x, y2.x);
  z.i = _mm512_and_si512 (z.i, b);
  e16 = _mm512_mask_sub_epi32 (_mm512_sub_epi32 (_mm512_srli_epi32 (y.i, 23),
                                                 _mm512_set1_epi32 (126)), m2,
                               _mm512_srli_epi32 (z.i, 23),
                               _mm512_set1_epi32 (253));
  y.x = _mm512_mask_mul_ps (y.x, m2, y2.x, z.x);
  m1 |= m2 & m3;
  *e = _mm512_mask_blend_epi32 (m1, e16, zi);
  return
    _mm512_mask_mul_ps (x, ~m1, _mm512_set1_ps (0.5f), _mm512_div_ps (x, y.x));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m512i).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_exp2n_16xf32 (__m512i e)    ///< exponent vector (__m512i).
{
  __m512 x;
  x = _mm512_mask_blend_ps
    (_mm512_cmpgt_epi32_mask (e, _mm512_set1_epi32 (-127)),
     _mm512_castsi512_ps
     (_mm512_sllv_epi32 (_mm512_set1_epi32 (0x00400000),
                         _mm512_sub_epi32 (_mm512_set1_epi32 (-127), e))),
     _mm512_castsi512_ps
     (_mm512_slli_epi32 (_mm512_add_epi32 (e, _mm512_set1_epi32 (127)), 23)));
  x = _mm512_mask_blend_ps (_mm512_cmpgt_epi32_mask (_mm512_set1_epi32 (-150),
                                                     e),
                            x, _mm512_setzero_ps ());
  return
    _mm512_mask_blend_ps (_mm512_cmpgt_epi32_mask (e, _mm512_set1_epi32 (127)),
                          x, _mm512_set1_ps (INFINITY));
}


/**
 * Function to implement the standard ldexp function (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_ldexp_16xf32 (const __m512 x,       ///< __m512 vector.
                  __m512i e)    ///< exponent vector (__m512i).
{
  return _mm512_mul_ps (x, jbm_exp2n_16xf32 (e));
}

/**
 * Function to check small __m512 vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __mmask16
jbm_small_16xf32 (const __m512 x)       ///< __m512d vector.
{
  return _mm512_cmp_ps_mask (jbm_abs_16xf32 (x), _mm512_set1_ps (FLT_EPSILON),
                             _CMP_LT_OS);
}

/**
 * Function to calculate the __m512 vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m512 vector.
 */
static inline __m512
jbm_modmin_16xf32 (const __m512 a,      ///< 1st __m512d vector.
                   const __m512 b)      ///< 2nd __m512d vector.
{
  __m512 aa, ab, y, z;
  z = _mm512_setzero_ps ();
  ab = _mm512_mul_ps (a, b);
  y = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (ab, z, _CMP_GT_OS), z, a);
  aa = jbm_abs_16xf32 (y);
  ab = jbm_abs_16xf32 (b);
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (aa, ab, _CMP_GT_OS), y, b);
}

/**
 * Function to interchange 2 __m512 vectors.
 */
static inline void
jbm_change_16xf32 (__m512 *restrict a,  ///< 1st __m512 vector pointer.
                   __m512 *restrict b)  ///< 2nd __m512 vector pointer.
{
  __m512 c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m512 vector.
 *
 * \return __m512 double.
 */
static inline __m512
jbm_dbl_16xf32 (const __m512 x) ///< __m512d vector.
{
  return _mm512_add_ps (x, x);
}

/**
 * Function to calculate the square of the components of a __m512 vector.
 *
 * \return __m512 vector square.
 */
static inline __m512
jbm_sqr_16xf32 (const __m512 x) ///< __m512 vector.
{
  return _mm512_mul_ps (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m512 vectors of 2D points.
 *
 * \return __m512 vector of y-coordinates of the extrapolated points.
 */
static inline __m512
jbm_extrapolate_16xf32 (const __m512 x,
                        ///< __m512 vector of x-coordinates of the extrapolated
                        ///< points.
                        const __m512 x1,
                        ///< __m512 vector of x-coordinates of the 1st points.
                        const __m512 x2,
                        ///< __m512 vector of x-coordinates of the 2nd points.
                        const __m512 y1,
                        ///< __m512 vector of y-coordinates of the 1st points.
                        const __m512 y2)
                     ///< __m512 vector of y-coordinates of the 2nd points.
{
  __m512 d;
  d = _mm512_sub_ps (x, x1);
  return _mm512_fmadd_ps (d, _mm512_div_ps (_mm512_sub_ps (y2, y1),
                                            _mm512_sub_ps (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m512 vectors of 2D points.
 *
 * \return __m512 vector of y-coordinates of the interpolated points.
 */
static inline __m512
jbm_interpolate_16xf32 (const __m512 x,
                        ///< __m512 vector of x-coordinates of the interpolated
                        ///< points.
                        const __m512 x1,
                        ///< __m512 vector of x-coordinates of the 1st points.
                        const __m512 x2,
                        ///< __m512 vector of x-coordinates of the 2nd points.
                        const __m512 y1,
                        ///< __m512 vector of y-coordinates of the 1st points.
                        const __m512 y2)
                     ///< __m512 vector of y-coordinates of the 2nd points.
{
  __m512 k;
  k = jbm_extrapolate_16xf32 (x, x1, x2, y1, y2);
  k = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, x1, _CMP_GT_OS), y1, k);
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, x2, _CMP_LT_OS), y2, k);
}

/**
 * Function to calculate the length of a __m512 vector of 2D segments.
 *
 * \return __m512 vector of segment lengths.
 */
static inline __m512
jbm_v2_length_16xf32 (const __m512 x1,
///< __m512 vector of x-coordinates of the 1st points defining the segment.
                      const __m512 y1,
///< __m512 vector of y-coordinates of the 1st points defining the segment.
                      const __m512 x2,
///< __m512 vector of x-coordinates of the 2nd points defining the segment.
                      const __m512 y2)
///< __m512 vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_16xf32 (_mm512_sub_ps (x2, x1), _mm512_sub_ps (y2, y1));
}

/**
 * Function to calculate the length of a __m512 vector of 3D segments.
 *
 * \return __m512 vector of segment lengths.
 */
static inline __m512
jbm_v3_length_16xf32 (const __m512 x1,
///< __m512 vector of x-coordinates of the 1st points defining the segments.
                      const __m512 y1,
///< __m512 vector of y-coordinates of the 1st points defining the segments.
                      const __m512 z1,
///< __m512 vector of z-coordinates of the 1st points defining the segments.
                      const __m512 x2,
///< __m512 vector of x-coordinates of the 2nd points defining the segments.
                      const __m512 y2,
///< __m512 vector of y-coordinates of the 2nd points defining the segments.
                      const __m512 z2)
///< __m512 vector of z-coordinates of the 2nd points defining the segments.
{
  __m512 dx, dy, dz;
  dx = _mm512_sqrt_ps (_mm512_sub_ps (x2, x1));
  dy = _mm512_sub_ps (y2, y1);
  dy = _mm512_fmadd_ps (dy, dy, dx);
  dz = _mm512_sub_ps (z2, z1);
  return _mm512_sqrt_ps (_mm512_fmadd_ps (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]), _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_4_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_5_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_6_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_7_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_8_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_9_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_10_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_11_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_12_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_13_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_14_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_15_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_16_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_17_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_18_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_19_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_20_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_21_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_22_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_23_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_24_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_25_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_24_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_26_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_25_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_27_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_26_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_28_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_27_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m512).
 *
 * \return __m512 vector of polynomial values.
 */
static inline __m512
jbm_polynomial_29_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_fmadd_ps (x, jbm_polynomial_28_16xf32 (x, p + 1),
                          _mm512_set1_ps (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_1_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[1]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_2_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+1st order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_2_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[2]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_3_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_3_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_3_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[3]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_4_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_4_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_4_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_4_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[4]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_5_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_5_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_5_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_5_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_5_4_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[5]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_6_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_6_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_6_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_6_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_6_4_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_6_5_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[6]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_4_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_5_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_7_6_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[7]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_4_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_5_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_6_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_8_7_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[8]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_0_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_1_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_2_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_3_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_4_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_5_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_6_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_7_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_9_8_16xf32 (const __m512 x,        ///< __m512 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[9]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_10_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[10]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_11_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[11]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_12_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[12]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_13_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[13]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_14_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[14]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_15_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[15]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_16_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[16]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_17_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[17]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_18_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[18]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_10_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_19_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[19]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_11_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_20_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[20]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_12_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_21_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[21]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_13_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_22_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[22]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_14_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_23_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[23]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_15_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_14_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_24_23_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_23_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[24]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_24_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_16_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_15_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_14_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_23_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_23_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_25_24_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_24_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[25]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_25_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_24_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_17_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_16_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_15_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_14_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_23_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_23_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_24_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_24_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_26_25_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_25_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[26]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_26_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_25_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_24_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_18_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_17_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_16_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_15_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_14_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_23_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_23_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_24_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_24_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_25_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_25_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 26),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_27_26_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_26_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[27]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+28th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_27_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_26_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_25_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_24_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_19_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_18_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_17_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_16_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_15_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_14_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_23_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_23_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_24_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_24_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_25_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_25_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 26),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_26_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_26_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 27),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_28_27_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_27_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[28]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+29th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_0_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (_mm512_set1_ps (p[0]),
                        _mm512_fmadd_ps (x, jbm_polynomial_28_16xf32 (x, p + 1),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_1_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_1_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_27_16xf32 (x, p + 2),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_2_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_2_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_26_16xf32 (x, p + 3),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_3_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_3_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_25_16xf32 (x, p + 4),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+25th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_4_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_4_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_24_16xf32 (x, p + 5),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+24th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_5_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_5_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_23_16xf32 (x, p + 6),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+23th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_6_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_6_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_22_16xf32 (x, p + 7),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+22th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_7_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_7_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_21_16xf32 (x, p + 8),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+21th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_8_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_8_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_20_16xf32 (x, p + 9),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+20th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_9_16xf32 (const __m512 x,       ///< __m512 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_9_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_19_16xf32 (x, p + 10),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+19th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_10_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_10_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_18_16xf32 (x, p + 11),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+18th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_11_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_11_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_17_16xf32 (x, p + 12),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+17th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_12_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_12_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_16_16xf32 (x, p + 13),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+16th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_13_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_13_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_15_16xf32 (x, p + 14),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+15th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_14_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_14_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_14_16xf32 (x, p + 15),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+14th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_15_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_15_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_13_16xf32 (x, p + 16),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+13th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_16_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_16_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_12_16xf32 (x, p + 17),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+12th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_17_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_17_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_11_16xf32 (x, p + 18),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+11th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_18_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_18_16xf32 (x, p),
                        _mm512_fmadd_ps (x,
                                         jbm_polynomial_10_16xf32 (x, p + 19),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+10th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_19_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_19_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_9_16xf32 (x, p + 20),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+9th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_20_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_20_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_8_16xf32 (x, p + 21),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+8th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_21_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_21_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_7_16xf32 (x, p + 22),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+7th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_22_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_22_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_6_16xf32 (x, p + 23),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+6th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_23_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_23_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_5_16xf32 (x, p + 24),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+5th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_24_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_24_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_4_16xf32 (x, p + 25),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+4th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_25_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_25_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_3_16xf32 (x, p + 26),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_26_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_26_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_2_16xf32 (x, p + 27),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_27_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_27_16xf32 (x, p),
                        _mm512_fmadd_ps (x, jbm_polynomial_1_16xf32 (x, p + 28),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512).
 *
 * \return __m512 vector of rational values.
 */
static inline __m512
jbm_rational_29_28_16xf32 (const __m512 x,      ///< __m512 vector.
                           const float *p)      ///< array of coefficients.
{
  return _mm512_div_ps (jbm_polynomial_28_16xf32 (x, p),
                        _mm512_fmadd_ps (x, _mm512_set1_ps (p[29]),
                                         _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_expm1wc_16xf32 (const __m512 x)
///< __m512 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = 9.9999999917826835759154742878523887e-01f;
  const float a2 = -4.9999999958913417879577371439261924e-01f;
  const float a3 = 8.3333136366700581865508474051734715e-02f;
  const float a5 = -1.3833464660905326042591440964123531e-03f;
  __m512 x2;
  x2 = jbm_sqr_16xf32 (x);
  x2 = _mm512_fmadd_ps (x2, _mm512_set1_ps (a5), _mm512_set1_ps (a3));
  x2 = _mm512_fmadd_ps (x2, x, _mm512_set1_ps (a2));
  x2 = _mm512_fmadd_ps (x2, x, _mm512_set1_ps (1.f));
  return _mm512_mul_ps (x, _mm512_div_ps (_mm512_set1_ps (a1), x2));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512).
 *
 * \return function value.
 */
static inline __m512
jbm_exp2wc_16xf32 (const __m512 x)
                  ///< __m512 vector \f$\in\left[\frac12,1\right]\f$.
{
  const float a[7] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00f,
    6.9314686072833467549614190619455902e-01f,
    2.4023118169610183345256217102144910e-01f,
    5.5478530109176099769719280450854577e-02f,
    9.6865061954622047550464877418812215e-03f,
    1.2383545075613684860722656859898531e-03f,
    2.1856676336381804045788890526617381e-04f
  };
  return jbm_polynomial_6_16xf32 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_16xf32 and
 * jbm_exp2n_16xf32 functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_exp2_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 y, f;
  y = _mm512_floor_ps (x);
  f = _mm512_sub_ps (x, y);
  y = jbm_exp2n_16xf32 (_mm512_cvtps_epi32 (y));
  return _mm512_mul_ps (y, jbm_exp2wc_16xf32 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_16xf32 function
 * (__m512).
 *
 * \return function value.
 */
static inline __m512
jbm_exp_16xf32 (const __m512 x) ///< __m512 vector.
{
  return jbm_exp2_16xf32 (_mm512_mul_ps (x, _mm512_set1_ps (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_16xf32
 * function (__m512).
 *
 * \return function value.
 */
static inline __m512
jbm_exp10_16xf32 (const __m512 x)       ///< __m512 vector.
{
  return jbm_exp2_16xf32 (_mm512_mul_ps (x, _mm512_set1_ps (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_16xf32 and
 * jbm_exp_16xf32 functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_expm1_16xf32 (const __m512 x)       ///< __m512 vector.
{
  return
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (jbm_abs_16xf32 (x),
                                              _mm512_set1_ps (M_LN2f / 2.f),
                                              _CMP_LT_OS),
                          _mm512_sub_ps (jbm_exp_16xf32 (x),
                                         _mm512_set1_ps (1.f)),
                          jbm_expm1wc_16xf32 (x));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_log2wc_16xf32 (const __m512 x)      ///< __m512 vector.
{
  const float a[7] JB_ALIGNED = {
    -5.7614734502501607747654602917594776e+00,
    -2.3619900574486177423704274945198131e+01,
    1.6942914690062891037195707459711629e+01,
    1.2438459334673447161274027777245978e+01,
    1.2423302678466295723498856823510141e+01,
    1.6996336524406058588262995830668668e+01,
    2.5612174224694665867539204628212066e+00
  };
  return jbm_rational_6_3_16xf32 (x, a);
}

/**
 * Function to calculate the function log2(x) using jbm_log2wc_16xf32 and
 * jbm_frexp_16xf32 (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_log2_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 y, z;
  __m512i e;
  y = jbm_frexp_16xf32 (x, &e);
  y = _mm512_add_ps (jbm_log2wc_16xf32 (y), _mm512_cvtepi32_ps (e));
  z = _mm512_setzero_ps ();
  y = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, z, _CMP_GT_OS),
                            _mm512_set1_ps (-INFINITY), y);
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, z, _CMP_LT_OS),
                               y, _mm512_set1_ps (NAN));

}

/**
 * Function to calculate the function log(x) using jbm_log2_16xf32 (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_log_16xf32 (const __m512 x) ///< __m512 vector.
{
  return _mm512_mul_ps (jbm_log2_16xf32 (x), _mm512_set1_ps (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_16xf32.
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_log10_16xf32 (const __m512 x)       ///< __m512 vector.
{
  return _mm512_mul_ps (jbm_log2_16xf32 (x), _mm512_set1_ps (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (__m512).
 *
 * \return function value (__m512) (__m512).
 */
static inline __m512
jbm_pown_16xf32 (const __m512 x,        ///< __m512 vector.
                 int e)         ///< exponent (int).
{
  __m512 f, xn;
  unsigned int i;
  f = _mm512_set1_ps (1.f);
  if (e < 0)
    xn = _mm512_div_ps (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_16xf32 (xn))
    if (i & 1)
      f = _mm512_mul_ps (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_exp2_16xf32 and
 * jbm_log2_16xf32 functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_pow_16xf32 (const __m512 x, ///< __m512 vector.
                const float e)  ///< exponent (float).
{
  float f;
  f = floorf (e);
  if (f == e)
    return jbm_pown_16xf32 (x, (int) e);
  return
    jbm_exp2_16xf32 (_mm512_mul_ps (_mm512_set1_ps (e), jbm_log2_16xf32 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_16xf32 and
 * jbm_pow_16xf32 functions (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_cbrt_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 f, z;
  f = jbm_abs_16xf32 (x);
  f = jbm_pow_16xf32 (x, 1.f / 3.f);
  z = _mm512_setzero_ps ();
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, z, _CMP_LT_OS),
                               _mm512_sub_ps (z, f), f);

}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m512)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_sinwc_16xf32 (const __m512 x)
                 ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const float a[4] JB_ALIGNED = {
    9.9999999652998170520234859388240338e-01f,
    -1.6666653850132705938945722106817969e-01f,
    8.3322256622392457162205759786691734e-03f,
    -1.9524867674489682553254582414001857e-04f
  };
  return _mm512_mul_ps (x, jbm_polynomial_3_16xf32 (jbm_sqr_16xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m512):
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_coswc_16xf32 (const __m512 x)
                 ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const float a[5] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00f,
    -4.9999999965238906843549904534867220e-01f,
    4.1666653828165636463917247496043632e-02f,
    -1.3887779469291056608109602187665577e-03f,
    2.4484799013341679093941386831846651e-05f
  };
  return jbm_polynomial_4_16xf32 (jbm_sqr_16xf32 (x), a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_16xf32 approximation (__m512).
 */
static inline void
jbm_sincoswc_16xf32 (const __m512 x,
                     ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                     __m512 *s, ///< pointer to the sin function value (__m512).
                     __m512 *c) ///< pointer to the cos function value (__m512).
{
  __m512 s0;
  *s = s0 = jbm_sinwc_16xf32 (x);
  *c = _mm512_sqrt_ps (_mm512_fnmadd_ps (s0, s0, _mm512_set1_ps (1.f)));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_16xf32 and
 * jbm_coswc_16xf32 approximations (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_sin_16xf32 (const __m512 x) ///< __m512 vector.
{
  __m512 y, s, pi2;
  pi2 = _mm512_set1_ps (2.f * M_PIf);
  y = jbm_rest_16xf32 (x, pi2);
  s = jbm_sinwc_16xf32 (_mm512_sub_ps (y, pi2));
  s = _mm512_mask_blend_ps
    (_mm512_cmp_ps_mask (y, _mm512_set1_ps (7.f * M_PI_4f), _CMP_LT_OS),
     s,
     jbm_opposite_16xf32
     (jbm_coswc_16xf32 (_mm512_sub_ps (_mm512_set1_ps (3.f * M_PI_2f), y))));
  s =
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y, _mm512_set1_ps (5.f * M_PI_4f),
                                              _CMP_LT_OS),
                          s,
                          jbm_sinwc_16xf32 (_mm512_sub_ps
                                            (_mm512_set1_ps (M_PIf), y)));
  s =
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y, _mm512_set1_ps (3.f * M_PI_4f),
                                              _CMP_LT_OS),
                          s,
                          jbm_coswc_16xf32 (_mm512_sub_ps
                                            (_mm512_set1_ps (M_PI_2f), y)));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y, _mm512_set1_ps (M_PI_4f),
                                                   _CMP_LT_OS),
                               s, jbm_sinwc_16xf32 (y));
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_16xf32 and
 * jbm_coswc_16xf32 approximations (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_cos_16xf32 (const __m512 x) ///< __m512 vector.
{
  __m512 y, c, pi2;
  pi2 = _mm512_set1_ps (2.f * M_PIf);
  y = jbm_rest_16xf32 (x, pi2);
  c = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y,
                                                _mm512_set1_ps (7.f * M_PI_4f),
                                                _CMP_LT_OS),
                            jbm_coswc_16xf32 (_mm512_sub_ps (y, pi2)),
                            jbm_sinwc_16xf32
                            (_mm512_sub_ps (y,
                                            _mm512_set1_ps (3.f * M_PI_2f))));
  c = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y,
                                                _mm512_set1_ps (5.f * M_PI_4f),
                                                _CMP_LT_OS),
                            c,
                            jbm_opposite_16xf32
                            (jbm_coswc_16xf32
                             (_mm512_sub_ps (_mm512_set1_ps (M_PIf), y))));
  c = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y,
                                                _mm512_set1_ps (3.f * M_PI_4f),
                                                _CMP_LT_OS),
                            c,
                            jbm_sinwc_16xf32 (_mm512_sub_ps
                                              (_mm512_set1_ps (M_PI_2f), y)));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y, _mm512_set1_ps (M_PI_4f),
                                                   _CMP_LT_OS),
                               c, jbm_coswc_16xf32 (y));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_sinwc_16xf32 and jbm_coswc_16xf32 approximations (__m512).
 */
static inline void
jbm_sincos_16xf32 (const __m512 x,
                   ///< __m512 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                   __m512 *s,   ///< pointer to the sin function value (__m512).
                   __m512 *c)   ///< pointer to the cos function value (__m512).
{
  __m512 y, pi2, z, s1, c1, s2, c2;
  __mmask16 m;
  pi2 = _mm512_set1_ps (2.f * M_PIf);
  y = jbm_rest_16xf32 (x, pi2);
  jbm_sincoswc_16xf32 (_mm512_sub_ps (y, pi2), &s1, &c1);
  jbm_sincoswc_16xf32 (_mm512_sub_ps (y, _mm512_set1_ps (3.f * M_PI_2f)), &c2,
                       &s2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (7.f * M_PI_4f), _CMP_LT_OS);
  z = _mm512_setzero_ps ();
  s1 = _mm512_mask_blend_ps (m, s1, _mm512_sub_ps (z, s2));
  c1 = _mm512_mask_blend_ps (m, c1, c2);
  jbm_sincoswc_16xf32 (_mm512_sub_ps (_mm512_set1_ps (M_PIf), y), &s2, &c2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (5.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm512_mask_blend_ps (m, s1, s2);
  c1 = _mm512_mask_blend_ps (m, c1, _mm512_sub_ps (z, c2));
  jbm_sincoswc_16xf32 (_mm512_sub_ps (_mm512_set1_ps (M_PI_2f), y), &c2, &s2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (3.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm512_mask_blend_ps (m, s1, s2);
  c1 = _mm512_mask_blend_ps (m, c1, c2);
  jbm_sincoswc_16xf32 (y, &s2, &c2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (M_PI_4f), _CMP_LT_OS);
  *s = _mm512_mask_blend_ps (m, s1, s2);
  *c = _mm512_mask_blend_ps (m, c1, c2);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_16xf32 function
 * (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_tan_16xf32 (const __m512 x) ///< __m512 vector.
{
  __m512 s, c;
  jbm_sincos_16xf32 (x, &s, &c);
  return _mm512_div_ps (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_atanwc0_16xf32 (const __m512 x)
                   ///< __m512 vector \f$\in\left[0,\frac12\right]\f$.
{
  const float a[4] JB_ALIGNED = {
    9.9999984048730143841335295268244848e-01f,
    4.9566847198521400589504493089955823e-01f,
    8.2898705878810240458099950004542931e-01f,
    7.6658333542753920209846592962853791e-02f
  };
  return _mm512_mul_ps (x, jbm_rational_3_1_16xf32 (jbm_sqr_16xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_atanwc1_16xf32 (const __m512 x)
                   ///< __m512 vector \f$\in\left[\frac12,1\right]\f$.
{
  const float a[8] JB_ALIGNED = {
    7.8539816255139945753131801776549671e-01f,
    1.5745201941534749424905726297312445e+00f,
    1.0480101799785619330373271236286859e+00f,
    2.5928000609503906398597815174946580e-01f,
    1.3681216008010664678472144108090419e+00f,
    7.8170438323723224777454800430939851e-01f,
    1.6186088663013176341397431580496626e-01f,
    6.2512302543463204942783713123096548e-04f
  };
  return jbm_rational_7_3_16xf32 (_mm512_sub_ps (x, _mm512_set1_ps (1.f)), a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_16xf32 and
 * jbm_atanwc1_16xf32 functions (__m512).
 *
 * \return function value (in [-pi/2,pi/2]) (__m512).
 */
static inline __m512
jbm_atan_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 f, ax, z;
  __mmask16 m;
  ax = jbm_abs_16xf32 (x);
  m = _mm512_cmp_ps_mask (ax, _mm512_set1_ps (1.5f), _CMP_GT_OS);
  ax = _mm512_mask_blend_ps (m, ax, jbm_reciprocal_16xf32 (ax));
  f = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (ax, _mm512_set1_ps (0.5f),
                                                _CMP_GT_OS),
                            jbm_atanwc0_16xf32 (ax), jbm_atanwc1_16xf32 (ax));
  f = _mm512_mask_blend_ps (m, f, _mm512_sub_ps (_mm512_set1_ps (M_PI_2f), f));
  z = _mm512_setzero_ps ();
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, z, _CMP_LT_OS),
                               f, _mm512_sub_ps (z, f));
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_16xf32
 * function (__m512).
 *
 * \return function value (in [-pi,pi]) (__m512).
 */
static inline __m512
jbm_atan2_16xf32 (const __m512 y,       ///< __m512 y component.
                  const __m512 x)       ///< __m512 x component.
{
  __m512 f, z, pi;
  __mmask16 mx, my;
  z = _mm512_setzero_ps ();
  pi = _mm512_set1_ps (M_PIf);
  f = jbm_atan_16xf32 (_mm512_div_ps (y, x));
  mx = _mm512_cmp_ps_mask (x, z, _CMP_LT_OS);
  my = _mm512_cmp_ps_mask (y, z, _CMP_LT_OS);
  f = _mm512_mask_blend_ps (my & mx, f, _mm512_sub_ps (f, pi));
  return _mm512_mask_blend_ps ((~my) & mx, f, _mm512_add_ps (f, pi));
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_16xf32 function
 * (__m512).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline __m512
jbm_asin_16xf32 (const __m512 x)        ///< __m512 vector.
{
  return
    jbm_atan_16xf32 (_mm512_div_ps
                     (x,
                      _mm512_sqrt_ps (_mm512_fnmadd_ps
                                      (x, x, _mm512_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_16xf32 function
 * (__m512).
 *
 * \return function value (in [0,pi]) (__m512).
 */
static inline __m512
jbm_acos_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 f;
  f =
    jbm_atan_16xf32 (_mm512_div_ps
                     (_mm512_sqrt_ps
                      (_mm512_fnmadd_ps (x, x, _mm512_set1_ps (1.f))), x));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, _mm512_setzero_ps (),
                                                   _CMP_LT_OS),
                               f, _mm512_add_ps (f, _mm512_set1_ps (M_PIf)));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_sinh_16xf32 (const __m512 x)        ///< __m512 number.
{
  __m512 f;
  f = jbm_exp_16xf32 (x);
  return _mm512_mul_ps (_mm512_set1_ps (0.5f),
                        _mm512_sub_ps (f, jbm_reciprocal_16xf32 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_cosh_16xf32 (const __m512 x)        ///< __m512 number.
{
  __m512 f;
  f = jbm_exp_16xf32 (x);
  return _mm512_mul_ps (_mm512_set1_ps (0.5f),
                        _mm512_add_ps (f, jbm_reciprocal_16xf32 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_tanh_16xf32 (const __m512 x)        ///< __m512 number.
{
  __m512 f, fi;
  f = jbm_exp_16xf32 (x);
  fi = jbm_reciprocal_16xf32 (f);
  f = _mm512_div_ps (_mm512_sub_ps (f, fi), _mm512_add_ps (f, fi));
  f = _mm512_mask_blend_ps
    (_mm512_cmp_ps_mask (x, _mm512_set1_ps (JBM_FLT_MAX_E_EXP), _CMP_GT_OS),
     f, _mm512_set1_ps (1.f));
  return
    _mm512_mask_blend_ps
    (_mm512_cmp_ps_mask (x, _mm512_set1_ps (-JBM_FLT_MAX_E_EXP), _CMP_LT_OS),
     f, _mm512_set1_ps (-1.f));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_asinh_16xf32 (const __m512 x)       ///< __m512 number.
{
  return
    jbm_log_16xf32 (_mm512_add_ps
                    (x,
                     _mm512_sqrt_ps (_mm512_fmadd_ps
                                     (x, x, _mm512_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_acosh_16xf32 (const __m512 x)       ///< __m512 number.
{
  return
    jbm_log_16xf32 (_mm512_add_ps
                    (x,
                     _mm512_sqrt_ps (_mm512_fmsub_ps
                                     (x, x, _mm512_set1_ps (1.f)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_atanh_16xf32 (const __m512 x)       ///< __m512 number.
{
  __m512 u;
  u = _mm512_set1_ps (1.f);
  return _mm512_mul_ps (_mm512_set1_ps (0.5f),
                        jbm_log_16xf32 (_mm512_div_ps (_mm512_add_ps (u, x),
                                                       _mm512_sub_ps (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m512)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_erfwc_16xf32 (const __m512 x)
                 ///< __m512 vector \f$\in\left[-1,1\right]\f$.
{
  const float a[6] JB_ALIGNED = {
    1.1283791671633124547603970137089329e+00f,
    1.1356247077387072221530473806173895e-01f,
    3.3606359392673594485175487779855494e-02f,
    4.3397545597876753616401102540952801e-01f,
    7.4441296041206635020857929305718177e-02f,
    5.2260592856163505486272407800095742e-03f
  };
  return _mm512_mul_ps (x, jbm_rational_5_2_16xf32 (jbm_sqr_16xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m512)
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_erfcwc_16xf32 (const __m512 x)
                  ///< __m512 vector \f$\in\left[1,\infty\right]\f$.
{
  const float a[7] JB_ALIGNED = {
    5.6418091764636642421399952962410440e-01,
    2.3259215523506370130840763503668292e+00,
    1.7480917193581656978658253659192661e+00,
    1.2835716481660171242272557816263124e-01,
    4.6220051294746234636042153676346028e+00,
    4.6697994386130441831194770859452481e+00,
    8.5584393582117540916415181581091126e-01
  };
  const float m = 1.0019834265884623367967105586324901e+01;
  __m512 f, x2;
  x2 = jbm_sqr_16xf32 (x);
  f = _mm512_div_ps (jbm_rational_6_3_16xf32 (jbm_reciprocal_16xf32 (x2), a),
                     _mm512_mul_ps (x, jbm_exp_16xf32 (x2)));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (x, _mm512_set1_ps (m),
                                                   _CMP_GT_OS),
                               f, _mm512_setzero_ps ());
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_16xf32 and
 * jbm_erfcwc_16xf32
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_erf_16xf32 (const __m512 x) ///< __m512 vector.
{
  __m512 ax, u, f;
  ax = jbm_abs_16xf32 (x);
  u = _mm512_set1_ps (1.f);
  f =
    _mm512_mul_ps (_mm512_div_ps (x, ax),
                   _mm512_sub_ps (u, jbm_erfcwc_16xf32 (ax)));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (ax, u, _CMP_LT_OS),
                               f, jbm_erfwc_16xf32 (x));

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_16xf32 and
 * jbm_erfcwc_16xf32
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_erfc_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 ax, u, f;
  ax = jbm_abs_16xf32 (x);
  u = _mm512_set1_ps (1.f);
  f = _mm512_sub_ps (u, _mm512_mul_ps (_mm512_div_ps (x, ax),
                                       _mm512_sub_ps (u,
                                                      jbm_erfcwc_16xf32 (ax))));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (ax, u, _CMP_LT_OS),
                               f, _mm512_sub_ps (u, jbm_erfwc_16xf32 (x)));
}

/**
 * Function to calculate the solution of a __m512 vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_quadratic_reduced_16xf32 (__m512 a,
///< __m512 vector of 1st order coefficient of the equations.
                                    __m512 b,
///< __m512 vector of 0th order coefficient of the equations.
                                    const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                                    const __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  __m512 k1, k2;
  k1 = _mm512_set1_ps (-0.5f);
  a = _mm512_mul_ps (a, k1);
  b = _mm512_sqrt_ps (_mm512_sub_ps (jbm_sqr_16xf32 (a), b));
  k1 = _mm512_add_ps (a, b);
  k2 = _mm512_sub_ps (a, b);
  k1 = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (k1, x1, _CMP_LT_OS), k1, k2);
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (k1, x2, _CMP_GT_OS), k1, k2);
}

/**
 * Function to calculate the solution of a __m512 vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_quadratic_16xf32 (const __m512 a,
///< __m512 vector of 2nd order coefficient of the equations.
                            const __m512 b,
///< __m512 vector of 1st order coefficient of the equations.
                            const __m512 c,
///< __m512 vector of 0th order coefficient of the equations.
                            const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                            const __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  __m512 k1, k2;
  k1 =
    jbm_solve_quadratic_reduced_16xf32 (_mm512_div_ps (b, a),
                                        _mm512_div_ps (c, a), x1, x2);
  k2 = _mm512_div_ps (jbm_opposite_16xf32 (c), b);
  return _mm512_mask_blend_ps (jbm_small_16xf32 (a), k1, k2);
}

/**
 * Function to calculate the solution of a __m512 vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_cubic_reduced_16xf32 (const __m512 a,
                                ///< 2nd order coefficient of the equation.
                                const __m512 b,
                                ///< 1st order coefficient of the equation.
                                const __m512 c,
                                ///< 0th order coefficient of the equation.
                                const __m512 x1,
                                ///< left limit of the solution interval.
                                const __m512 x2)
                               ///< right limit of the solution interval.
{
  __m512 a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm512_set1_ps (2.f * M_PIf / 3.f);
  c_2 = _mm512_set1_ps (0.5f);
  c_3 = _mm512_set1_ps (1.f / 3.f);
  a3 = _mm512_mul_ps (a, c_3);
  k0 = _mm512_mul_ps (a3, a3);
  k1 = _mm512_fmsub_ps (b, c_3, k0);
  k0 =
    _mm512_fmsub_ps (_mm512_fmsub_ps (b, a3, c), c_2, _mm512_mul_ps (a3, k0));
  k3 = _mm512_mul_ps (k1, _mm512_mul_ps (k1, k1));
  k2 = _mm512_fmadd_ps (k0, k0, k3);
  l1 = _mm512_sqrt_ps (jbm_opposite_16xf32 (k1));
  l0 = _mm512_mul_ps (jbm_acos_16xf32 (_mm512_div_ps (k0, k3)), c_3);
  l1 = _mm512_add_ps (l1, l1);
  l2 = _mm512_fmsub_ps (l1, jbm_cos_16xf32 (k0), a3);
  l3 = _mm512_fmsub_ps (l1, jbm_cos_16xf32 (_mm512_add_ps (l0, c2p_3)), a3);
  l3 = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (l2, x1, _CMP_LT_OS)
                             | _mm512_cmp_ps_mask (l2, x2, _CMP_GT_OS), l3, l2);
  l4 = _mm512_fmsub_ps (l1, jbm_cos_16xf32 (_mm512_sub_ps (l0, c2p_3)), a);
  l4 = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (l3, x1, _CMP_LT_OS)
                             | _mm512_cmp_ps_mask (l3, x2, _CMP_GT_OS), l4, l3);
  k1 = _mm512_sqrt_ps (k2);
  l5 = _mm512_add_ps (k0, k1);
  l5 = jbm_cbrt_16xf32 (k2);
  k0 = _mm512_sub_ps (k0, k1);
  l5 = _mm512_add_ps (l5, _mm512_sub_ps (jbm_cbrt_16xf32 (k0), a3));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (k2, _mm512_setzero_ps (),
                                                   _CMP_LT_OS), l4, l5);
}

/**
 * Function to calculate the solution of a __m512 vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_cubic_16xf32 (__m512 a,
///< __m512 vector of 3rd order coefficient of the equations.
                        __m512 b,
///< __m512 vector of 2nd order coefficient of the equations.
                        __m512 c,
///< __m512 vector of 1st order coefficient of the equations.
                        __m512 d,
///< __m512 vector of 0th order coefficient of the equations.
                        __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                        __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  return
    _mm512_mask_blend_ps (jbm_small_16xf32 (a),
                          jbm_solve_cubic_reduced_16xf32 (_mm512_div_ps (b, a),
                                                          _mm512_div_ps (c, a),
                                                          _mm512_div_ps (d, a),
                                                          x1, x2),
                          jbm_solve_quadratic_16xf32 (b, c, d, x1, x2));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_total_16xf32 (const __m512 d1 __attribute__((unused)),
                               ///< 1st flux limiter function parameter.
                               const __m512 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_setzero_ps ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_null_16xf32 (const __m512 d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m512 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_set1_ps (1.f);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_centred_16xf32 (const __m512 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512 d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm512_mask_blend_ps (jbm_small_16xf32 (d2),
                               _mm512_div_ps (d1, d2), _mm512_setzero_ps ());

}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_superbee_16xf32 (const __m512 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_div_ps (d1, d2);
  r = _mm512_max_ps (_mm512_min_ps (jbm_dbl_16xf32 (r), _mm512_set1_ps (1.f)),
                     _mm512_min_ps (r, _mm512_set1_ps (2.f)));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_minmod_16xf32 (const __m512 d1,
                                ///< 1st flux limiter function parameter.
                                const __m512 d2)
                             ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_min_ps (_mm512_div_ps (d1, d2), _mm512_set1_ps (1.f));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_VanLeer_16xf32 (const __m512 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r, k;
  r = _mm512_div_ps (d1, d2);
  k = jbm_abs_16xf32 (r);
  r =
    _mm512_div_ps (_mm512_add_ps (r, k),
                   _mm512_add_ps (_mm512_set1_ps (1.f), k));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_VanAlbada_16xf32 (const __m512 d1,
                                   ///< 1st flux limiter function parameter.
                                   const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r, k;
  r = _mm512_div_ps (d1, d2);
  k = jbm_sqr_16xf32 (r);
  r =
    _mm512_div_ps (_mm512_add_ps (r, k),
                   _mm512_add_ps (_mm512_set1_ps (1.f), k));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_minsuper_16xf32 (const __m512 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_min_ps (_mm512_div_ps (d1, d2), _mm512_set1_ps (2.f));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_supermin_16xf32 (const __m512 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_div_ps (d1, d2);
  r = _mm512_min_ps (jbm_dbl_16xf32 (r), _mm512_set1_ps (1.f));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_monotonized_central_16xf32 (const __m512 d1,
///< 1st flux limiter function parameter.
                                             const __m512 d2)
///< 2nd flux limiter function parameter.
{
  __m512 r, rm;
  r = _mm512_div_ps (d1, d2);
  rm =
    _mm512_mul_ps (_mm512_set1_ps (0.5f),
                   _mm512_add_ps (r, _mm512_set1_ps (1.f)));
  rm =
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (r, _mm512_set1_ps (3.f),
                                              _CMP_LT_OS),
                          _mm512_set1_ps (2.f), rm);

  rm =
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (r, _mm512_set1_ps (1.f / 3.f),
                                              _CMP_GT_OS),
                          rm, jbm_dbl_16xf32 (r));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_mean_16xf32 (const __m512 d1,
                              ///< 1st flux limiter function parameter.
                              const __m512 d2)
    ///< 2nd flux limiter function parameter.
{
  __m512 r;
  r = _mm512_mul_ps (_mm512_set1_ps (0.5f),
                     _mm512_add_ps (_mm512_set1_ps (1.f),
                                    _mm512_div_ps (d1, d2)));
  return _mm512_mask_blend_ps (_mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                   _mm512_set1_ps (FLT_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_ps (), r);
}

/**
 * Function to do a flux limiter function (__m512).
 *
 * \return flux limiter function value.
 */
static inline __m512
jbm_flux_limiter_16xf32 (const __m512 d1,
                         ///< 1st flux limiter function parameter.
                         const __m512 d2,
                         ///< 2nd flux limiter function parameter.
                         unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_16xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_16xf32 (d1, d2);
    }
  return jbm_flux_limiter_mean_16xf32 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m512).
 *
 * \return __m512 vector of integral values.
 */
static inline __m512
jbm_integral_16xf32 (__m512 (*f) (__m512),
                     ///< pointer to the function to integrate.
                     const __m512 x1,   ///< left limit of the interval.
                     const __m512 x2)   ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] JB_ALIGNED = { 2.f };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] JB_ALIGNED = { 8.f / 9.f, 5.f / 9.f },
    b[2] JB_ALIGNED = { 0.f, 7.745966692414834e-1f };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] JB_ALIGNED = {
    128.f / 225.f,
    4.786286704993665e-1f,
    2.369268850561891e-1f
  }, b[3] JB_ALIGNED = {
    0.f,
    5.384693101056831e-1f,
    9.061798459386640e-1f
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] JB_ALIGNED = {
    4.179591836734694e-1f,
    3.818300505051189e-1f,
    2.797053914892767e-1f,
    1.294849661688697e-1f
  }, b[4] JB_ALIGNED = {
    0.f,
    4.058451513773972e-1f,
    7.415311855993944e-1f,
    9.491079123427585e-1f
  };
#endif
  __m512 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_ps (0.5f);
  dx = _mm512_mul_ps (h, _mm512_sub_ps (x2, x1));
  x = _mm512_mul_ps (h, _mm512_add_ps (x2, x1));
  k = _mm512_set1_ps (a[0]);
  k = _mm512_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_ps (b[i]);
      k2 = _mm512_mul_ps (k2, dx);
      f1 = f (_mm512_sub_ps (x, k2));
      f2 = f (_mm512_add_ps (x, k2));
      h = _mm512_set1_ps (a[i]);
      k = _mm512_fmadd_ps (h, _mm512_add_ps (f1, f2), k);
    }
#endif
  k = _mm512_mul_ps (k, dx);
  return k;
}

/**
 * Function to calculate the additive inverse value of a __m512d vector.
 *
 * \return negative value vector (__m512d).
 */
static inline __m512d
jbm_opposite_8xf64 (const __m512d x)    ///< __m512d vector.
{
  JBM8xF64 y;
  y.i = _mm512_set1_epi64 (0x8000000000000000L);
  return _mm512_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m512d vector.
 *
 * \return reciprocal value vector (__m512d).
 */
static inline __m512d
jbm_reciprocal_8xf64 (const __m512d x)  ///< __m512 vector.
{
  return _mm512_div_pd (_mm512_set1_pd (1.), x);
}

/**
 * Function to calculate the absolute value of a __m512d vector.
 *
 * \return absolute value vector.
 */
static inline __m512d
jbm_abs_8xf64 (const __m512d x)
{
  JBM8xF64 y;
  y.i = _mm512_set1_epi64 (0x7fffffffffffffffL);
  return _mm512_and_pd (x, y.x);
}

/**
 * Function to calculate the hypot function (__m512d).
 *
 * \return function value vector (__m512d).
 */
static inline __m512d
jbm_hypot_8xf64 (const __m512d x,       ///< 1st __m512d vector.
                 const __m512d y)       ///< 2nd __m512d vector.
{
  return _mm512_sqrt_pd (_mm512_fmadd_pd (x, x, _mm512_mul_pd (y, y)));
}

/**
 * Function to calculate the rest of a division (__m512d).
 *
 * \return rest value (in [0,|divisor|) interval) (__m512d).
 */
static inline __m512d
jbm_rest_8xf64 (const __m512d x,        ///< dividend (__m512d).
                const __m512d d)        ///< divisor (__m512d).
{
  return _mm512_fnmadd_pd (_mm512_floor_pd (_mm512_div_pd (x, d)), d, x);
}

/**
 * Function to implement the standard frexp function (__m512d).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m512d
jbm_frexp_8xf64 (const __m512d x,       ///< __m512d vector.
                 __m512i *e)    ///< pointer to the extracted exponents vector.
{
  JBM8xF64 a, y, y2, z;
  __m512i e2, b, zi;
  __mmask16 m1, m2, m3;
  a.x = x;
  b = _mm512_set1_epi64 (0x7ff0000000000000L);
  y.i = _mm512_and_si512 (a.i, b);
  m1 = _mm512_cmpeq_epi64_mask (y.i, b);
  zi = _mm512_setzero_si512 ();
  m2 = _mm512_cmpeq_epi64_mask (y.i, zi);
  y2.x = x;
  y2.i = _mm512_and_si512 (y2.i, _mm512_set1_epi64 (0x000fffffffffffffL));
  m3 = _mm512_cmpeq_epi64_mask (y2.i, zi);
  y2.i = _mm512_set1_epi64 (0x0010000000000000L);
  z.x = _mm512_div_pd (x, y2.x);
  z.i = _mm512_and_si512 (z.i, b);
  e2 = _mm512_mask_sub_epi64 (_mm512_sub_epi64 (_mm512_srli_epi64 (y.i, 52),
                                                _mm512_set1_epi64 (1022L)), m2,
                              _mm512_srli_epi64 (z.i, 52),
                              _mm512_set1_epi64 (2044L));
  y.x = _mm512_mask_mul_pd (y.x, m2, y2.x, z.x);
  m1 |= m2 & m3;
  *e = _mm512_mask_blend_epi64 (m1, e2, zi);
  return _mm512_mask_blend_pd (m1, _mm512_mul_pd (_mm512_set1_pd (0.5),
                                                  _mm512_div_pd (x, y.x)), x);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m512i)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_exp2n_8xf64 (__m512i e)     ///< exponent vector (__m512i).
{
  __m512d x;
  x = _mm512_mask_blend_pd
    (_mm512_cmpgt_epi64_mask (e, _mm512_set1_epi64 (-1023L)),
     _mm512_castsi512_pd
     (_mm512_sllv_epi64
      (_mm512_set1_epi64 (0x0008000000000000L),
       _mm512_sub_epi64 (_mm512_set1_epi64 (-1023L), e))),
     _mm512_castsi512_pd
     (_mm512_slli_epi64 (_mm512_add_epi64 (e, _mm512_set1_epi64 (1023L)), 52)));
  x =
    _mm512_mask_blend_pd (_mm512_cmpgt_epi64_mask (_mm512_set1_epi64 (-1074L),
                                                   e), x, _mm512_setzero_pd ());
  return
    _mm512_mask_blend_pd (_mm512_cmpgt_epi64_mask (e,
                                                   _mm512_set1_epi64 (1023L)),
                          x, _mm512_set1_pd (INFINITY));
}

/**
 * Function to implement the standard ldexp function (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_ldexp_8xf64 (const __m512d x,       ///< __m512d vector.
                 __m512i e)     ///< exponent vector (__m512i).
{
  return _mm512_mul_pd (x, jbm_exp2n_8xf64 (e));
}

/**
 * Function to check small __m512d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __mmask16
jbm_small_8xf64 (const __m512d x)       ///< __m512d vector.
{
  return _mm512_cmp_pd_mask (jbm_abs_8xf64 (x), _mm512_set1_pd (DBL_EPSILON),
                             _CMP_LT_OS);
}

/**
 * Function to calculate the __m512d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m512d vector.
 */
static inline __m512d
jbm_modmin_8xf64 (const __m512d a,      ///< 1st __m512d vector.
                  const __m512d b)      ///< 2nd __m512d vector.
{
  __m512d aa, ab, y, z;
  z = _mm512_setzero_pd ();
  ab = _mm512_mul_pd (a, b);
  y = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (z, ab, _CMP_GT_OS), a, z);
  aa = jbm_abs_8xf64 (y);
  ab = jbm_abs_8xf64 (b);
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (aa, ab, _CMP_GT_OS), y, b);
}

/**
 * Function to interchange 2 __m512d numbers.
 */
static inline void
jbm_change_8xf64 (__m512d *restrict a,  ///< 1st __m512d vector pointer.
                  __m512d *restrict b)  ///< 2nd __m512d vector pointer.
{
  __m512d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m512d vector.
 *
 * \return __m512d double.
 */
static inline __m512d
jbm_dbl_8xf64 (const __m512d x) ///< __m512d vector.
{
  return _mm512_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m512d vector.
 *
 * \return __m512d vector square.
 */
static inline __m512d
jbm_sqr_8xf64 (const __m512d x) ///< __m512d vector.
{
  return _mm512_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m512d vectors of 2D points.
 *
 * \return __m512d vector of y-coordinates of the extrapolated points.
 */
static inline __m512d
jbm_extrapolate_8xf64 (const __m512d x,
                       ///< __m512d vector of x-coordinates of the extrapolated
                       ///< points.
                       const __m512d x1,
                       ///< __m512d vector of x-coordinates of the 1st points.
                       const __m512d x2,
                       ///< __m512d vector of x-coordinates of the 2nd points.
                       const __m512d y1,
                       ///< __m512d vector of y-coordinates of the 1st points.
                       const __m512d y2)
    ///< __m512d vector of y-coordinates of the 2nd points.
{
  __m512d d;
  d = _mm512_sub_pd (x, x1);
  return _mm512_fmadd_pd (d, _mm512_div_pd (_mm512_sub_pd (y2, y1),
                                            _mm512_sub_pd (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m512d vectors of 2D points.
 *
 * \return __m512d vector of y-coordinates of the interpolated points.
 */
static inline __m512d
jbm_interpolate_8xf64 (const __m512d x,
                       ///< __m512d vector of x-coordinates of the interpolated
                       ///< points.
                       const __m512d x1,
                       ///< __m512d vector of x-coordinates of the 1st points.
                       const __m512d x2,
                       ///< __m512d vector of x-coordinates of the 2nd points.
                       const __m512d y1,
                       ///< __m512d vector of y-coordinates of the 1st points.
                       const __m512d y2)
    ///< __m512d vector of y-coordinates of the 2nd points.
{
  __m512d k;
  k = jbm_extrapolate_8xf64 (x, x1, x2, y1, y2);
  k = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, x1, _CMP_GT_OS), y1, k);
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, x2, _CMP_LT_OS), y2, k);
}

/**
 * Function to calculate the length of a __m512d vector of 2D segments.
 *
 * \return __m512d vector of segment lengths.
 */
static inline __m512d
jbm_v2_length_8xf64 (const __m512d x1,
///< __m512d vector of x-coordinates of the 1st points defining the segment.
                     const __m512d y1,
///< __m512d vector of y-coordinates of the 1st points defining the segment.
                     const __m512d x2,
///< __m512d vector of x-coordinates of the 2nd points defining the segment.
                     const __m512d y2)
///< __m512d vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_8xf64 (_mm512_sub_pd (x2, x1), _mm512_sub_pd (y2, y1));
}

/**
 * Function to calculate the length of a __m512d vector of 3D segments.
 *
 * \return __m512d vector of segment lengths.
 */
static inline __m512d
jbm_v3_length_8xf64 (const __m512d x1,
///< __m512d vector of x-coordinates of the 1st points defining the segments.
                     const __m512d y1,
///< __m512d vector of y-coordinates of the 1st points defining the segments.
                     const __m512d z1,
///< __m512d vector of z-coordinates of the 1st points defining the segments.
                     const __m512d x2,
///< __m512d vector of x-coordinates of the 2nd points defining the segments.
                     const __m512d y2,
///< __m512d vector of y-coordinates of the 2nd points defining the segments.
                     const __m512d z2)
///< __m512d vector of z-coordinates of the 2nd points defining the segments.
{
  __m512d dx, dy, dz;
  dx = jbm_sqr_8xf64 (_mm512_sub_pd (x2, x1));
  dy = _mm512_sub_pd (y2, y1);
  dy = _mm512_fmadd_pd (dy, dy, dx);
  dz = _mm512_sub_pd (z2, z1);
  return _mm512_sqrt_pd (_mm512_fmadd_pd (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_4_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_5_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_6_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_7_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_8_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_9_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_10_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_11_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_12_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_13_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_14_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_15_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_16_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_17_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_18_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_19_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_20_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_21_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_22_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_23_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_24_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_25_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_24_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_26_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_25_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_27_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_26_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_28_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_27_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m512d).
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_29_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_28_8xf64 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_1_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_2_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+1st order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_2_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[2]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_3_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_3_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_3_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[3]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_4_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_4_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_4_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_4_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[4]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_5_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_5_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_5_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_5_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_5_4_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[5]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_6_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_6_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_6_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_6_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_6_4_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_6_5_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[6]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_4_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_5_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_7_6_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[7]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_4_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_5_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_6_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_8_7_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[8]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_0_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_1_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_2_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_3_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_4_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_5_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_6_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_7_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_9_8_8xf64 (const __m512d x,        ///< __m512d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[9]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_10_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[10]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_11_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[11]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_12_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[12]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_13_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[13]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_14_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[14]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_15_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[15]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_16_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[16]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_17_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[17]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_18_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[18]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_19_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[19]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_20_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[20]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_21_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[21]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_22_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[22]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_23_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[23]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_24_23_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_23_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[24]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_24_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_23_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_23_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_25_24_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_24_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[25]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_25_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_24_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_23_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_23_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_24_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_24_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_26_25_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_25_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[26]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_26_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_25_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_24_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_23_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_23_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_24_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_24_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_25_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_25_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 26),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_27_26_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_26_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[27]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+28th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_27_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_26_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_25_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_24_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_23_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_23_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_24_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_24_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_25_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_25_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 26),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_26_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_26_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 27),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_28_27_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_27_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[28]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+29th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_0_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (_mm512_set1_pd (p[0]),
                        _mm512_fmadd_pd (x, jbm_polynomial_28_8xf64 (x, p + 1),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_1_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_1_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_27_8xf64 (x, p + 2),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_2_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_2_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_26_8xf64 (x, p + 3),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_3_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_3_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_25_8xf64 (x, p + 4),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+25th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_4_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_4_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_24_8xf64 (x, p + 5),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+24th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_5_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_5_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_23_8xf64 (x, p + 6),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+23th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_6_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_6_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_22_8xf64 (x, p + 7),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+22th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_7_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_7_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_21_8xf64 (x, p + 8),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+21th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_8_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_8_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_20_8xf64 (x, p + 9),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+20th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_9_8xf64 (const __m512d x,       ///< __m512d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_9_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_19_8xf64 (x, p + 10),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+19th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_10_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_10_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_18_8xf64 (x, p + 11),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+18th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_11_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_11_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_17_8xf64 (x, p + 12),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+17th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_12_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_12_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_16_8xf64 (x, p + 13),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+16th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_13_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_13_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_15_8xf64 (x, p + 14),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+15th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_14_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_14_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_14_8xf64 (x, p + 15),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+14th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_15_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_15_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_13_8xf64 (x, p + 16),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+13th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_16_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_16_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_12_8xf64 (x, p + 17),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+12th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_17_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_17_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_11_8xf64 (x, p + 18),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+11th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_18_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_18_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_10_8xf64 (x, p + 19),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+10th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_19_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_19_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_9_8xf64 (x, p + 20),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+9th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_20_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_20_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_8_8xf64 (x, p + 21),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+8th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_21_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_21_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_7_8xf64 (x, p + 22),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+7th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_22_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_22_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_6_8xf64 (x, p + 23),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+6th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_23_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_23_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_5_8xf64 (x, p + 24),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+5th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_24_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_24_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_4_8xf64 (x, p + 25),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+4th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_25_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_25_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_3_8xf64 (x, p + 26),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_26_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_26_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_2_8xf64 (x, p + 27),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_27_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_27_8xf64 (x, p),
                        _mm512_fmadd_pd (x, jbm_polynomial_1_8xf64 (x, p + 28),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m512d).
 *
 * \return __m512d vector of rational values.
 */
static inline __m512d
jbm_rational_29_28_8xf64 (const __m512d x,      ///< __m512d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm512_div_pd (jbm_polynomial_28_8xf64 (x, p),
                        _mm512_fmadd_pd (x, _mm512_set1_pd (p[29]),
                                         _mm512_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_expm1wc_8xf64 (const __m512d x)
///< __m512d vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const double a1 = 9.9999999999999999866523626874215789e-01;
  const double a3 = 2.4998453858981619674396608301250598e-02;
  const double a4 = -4.9999999999999999933261730198779978e-01;
  const double a5 = 1.0833178719231388723914535942973379e-01;
  const double a6 = -1.2499226929490809837198234785821115e-02;
  const double a7 = 6.9431559947707471609539363612700440e-04;
  const double a9 = -1.6512957626515476078093301716091145e-06;
  __m512d x2;
  x2 = jbm_sqr_8xf64 (x);
  return
    _mm512_div_pd (_mm512_mul_pd (x, _mm512_fmadd_pd (x2, _mm512_set1_pd (a3),
                                                      _mm512_set1_pd (a1))),
                   _mm512_fmadd_pd
                   (x,
                    _mm512_fmadd_pd
                    (x,
                     _mm512_fmadd_pd
                     (x,
                      _mm512_fmadd_pd
                      (x,
                       _mm512_fmadd_pd
                       (x2,
                        _mm512_set1_pd (a9), _mm512_set1_pd (a7)),
                       _mm512_set1_pd (a6)),
                      _mm512_set1_pd (a5)), _mm512_set1_pd (a4)),
                    _mm512_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512d).
 *
 * \return function value.
 */
static inline __m512d
jbm_exp2wc_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in[\frac12,1]\f$.
{
  const double a[11] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00,
    3.5324464160776157561870873030858037e-01,
    5.5726188114087417626793519052430392e-02,
    4.9794664779672329730006391328596054e-03,
    2.5696766500385563533145513033700273e-04,
    6.2985082749669456733647499053841285e-06,
    -3.3990253895218437504130399181004685e-01,
    5.1102167694878854560231687504362842e-02,
    -4.2923660062672093556805841384253418e-03,
    2.0397216803284294746970787132187830e-04,
    -4.4537179125887109629652401561427060e-06
  };
  return jbm_rational_10_5_8xf64 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_8xf64 and
 * jbm_exp2n_8xf64 functions.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_exp2_8xf64 (const __m512d x)        ///< __m512d vector.
{
  __m512d y, f;
  y = _mm512_floor_pd (x);
  f = _mm512_sub_pd (x, y);
  y = jbm_exp2n_8xf64 (_mm512_cvtpd_epi64 (y));
  return _mm512_mul_pd (y, jbm_exp2wc_8xf64 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_8xf64 function.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_exp_8xf64 (const __m512d x) ///< __m512d vector.
{
  return jbm_exp2_8xf64 (_mm512_mul_pd (x, _mm512_set1_pd (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_8xf64
 * function (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_exp10_8xf64 (const __m512d x)       ///< __m512d vector.
{
  return jbm_exp2_8xf64 (_mm512_mul_pd (x, _mm512_set1_pd (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_8xf64 and
 * jbm_exp_8xf64 functions (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_expm1_8xf64 (const __m512d x)       ///< __m512d vector.
{
  return
    _mm512_mask_blend_pd (_mm512_cmp_pd_mask (jbm_abs_8xf64 (x),
                                              _mm512_set1_pd (M_LN2 / 2.),
                                              _CMP_LT_OS),
                          _mm512_sub_pd (jbm_exp_8xf64 (x),
                                         _mm512_set1_pd (1.)),
                          jbm_expm1wc_8xf64 (x));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_log2wc_8xf64 (const __m512d x)      ///< __m512d vector \f$\in[0.5,1]\f$.
{
  const double a[15] JB_ALIGNED = {
    -7.9445725043339633009093277936943052e+00,
    -3.1306546076105827158342766214592963e+02,
    -2.2596302912826161601573681743578623e+03,
    -3.7011744743004340940774417180404135e+03,
    1.1936685118668431116423053473379377e+03,
    3.8374682673222485827998102112182728e+03,
    1.1890592032684574259156121240957413e+03,
    6.1618816390893368761419199685947705e+01,
    6.7438513228370798777306221258955200e+01,
    8.3260419313804486427720362029685246e+02,
    3.1623624595055189214992652784402685e+03,
    4.3100873037825815385272111966054767e+03,
    2.1080135755402681113985588091844912e+03,
    3.1720338140658189902127224771013209e+02,
    8.7394176052337947394585614577964751e+00,
  };
  return jbm_rational_14_7_8xf64 (x, a);
}

/**
 * Function to calculate the function log_2(x) using jbm_logwc_8xf64 and
 * jbm_frexp_8xf64
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_log2_8xf64 (const __m512d x)        ///< __m512d vector.
{
  __m512d y, z;
  __m512i e;
  y = jbm_frexp_8xf64 (x, &e);
  y = _mm512_add_pd (jbm_log2wc_8xf64 (y), _mm512_cvtepi64_pd (e));
  z = _mm512_setzero_pd ();
  y = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, z, _CMP_GT_OS),
                            y, _mm512_set1_pd (-INFINITY));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, z, _CMP_LT_OS),
                               _mm512_set1_pd (NAN), y);
}

/**
 * Function to calculate the function log(x) using jbm_log2_8xf64 (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_log_8xf64 (const __m512d x) ///< __m512d vector.
{
  return _mm512_mul_pd (jbm_log2_8xf64 (x), _mm512_set1_pd (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_8xf64 (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_log10_8xf64 (const __m512d x)       ///< __m512d vector.
{
  return _mm512_mul_pd (jbm_log2_8xf64 (x), _mm512_set1_pd (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (__m512d).
 *
 * \return function value (__m512d) (__m512d).
 */
static inline __m512d
jbm_pown_8xf64 (const __m512d x,        ///< __m512d vector.
                int e)          ///< exponent (int).
{
  __m512d f, xn;
  unsigned int i;
  f = _mm512_set1_pd (1.);
  if (e < 0)
    xn = _mm512_div_pd (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_8xf64 (xn))
    if (i & 1)
      f = _mm512_mul_pd (f, xn);
  return f;
}

/**
 * Function to calculate the function f32 using the jbm_exp2_8xf64 and
 * jbm_log2_8xf64 functions.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_pow_8xf64 (const __m512d x, ///< __m512d vector.
               const double e)  ///< exponent (__m512d).
{
  double f;
  f = floor (e);
  if (f == e)
    return jbm_pown_8xf64 (x, (int) e);
  return
    jbm_exp2_8xf64 (_mm512_mul_pd (_mm512_set1_pd (e), jbm_log2_8xf64 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_8xf64 and
 * jbm_pow_8xf64 functions (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_cbrt_8xf64 (const __m512d x)        ///< __m512d vector.
{
  __m512d f, z;
  f = jbm_abs_8xf64 (x);
  f = jbm_pow_8xf64 (x, 1. / 3.);
  z = _mm512_setzero_pd ();
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, z, _CMP_LT_OS),
                               f, _mm512_sub_pd (z, f));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m512d)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_sinwc_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const double a[7] JB_ALIGNED = {
    9.9999999999999999903298528022992608e-01,
    -1.6666666666666655053351577460983916e-01,
    8.3333333333296595862456464924174883e-03,
    -1.9841269836544823130841945764534327e-04,
    2.7557316317701496371521577585751979e-06,
    -2.5051208834780181372040633623490924e-08,
    1.5924807404448211967660639660668199e-10
  };
  return _mm512_mul_pd (x, jbm_polynomial_6_8xf64 (jbm_sqr_8xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_coswc_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const double a[8] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00,
    -4.9999999999999999993951803557338505e-01,
    4.1666666666666659403140067984185230e-02,
    -1.3888888888886591172439404142742802e-03,
    2.4801587298632131731562671126858188e-05,
    -2.7557317406370546117628828935636779e-07,
    2.0876194438132647163852946046090933e-09,
    -1.1386810444187770618168073556226784e-11
  };
  return jbm_polynomial_7_8xf64 (jbm_sqr_8xf64 (x), a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_8xf64 approximation (__m512d).
 */
static inline void
jbm_sincoswc_8xf64 (const __m512d x,
                    ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m512d *s,
                    ///< pointer to the f32 function value (__m512d).
                    __m512d *c)
    ///< pointer to the f32 function value (__m512d).
{
  __m512d s0;
  *s = s0 = jbm_sinwc_8xf64 (x);
  *c = _mm512_sqrt_pd (_mm512_fnmadd_pd (x, x, _mm512_set1_pd (1.)));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_8xf64 and
 * jbm_coswc_8xf64 approximations.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_sin_8xf64 (const __m512d x) ///< __m512d vector.
{
  __m512d y, s, pi2;
  pi2 = _mm512_set1_pd (2. * M_PI);
  y = jbm_rest_8xf64 (x, pi2);
  s = jbm_sinwc_8xf64 (_mm512_sub_pd (y, pi2));
  s = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4),
                                                _CMP_LT_OS), s,
                            jbm_opposite_8xf64
                            (jbm_coswc_8xf64
                             (_mm512_sub_pd (_mm512_set1_pd (3. * M_PI_2),
                                             y))));
  s =
    _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4),
                                              _CMP_LT_OS), s,
                          jbm_sinwc_8xf64 (_mm512_sub_pd
                                           (_mm512_set1_pd (M_PI), y)));
  s =
    _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4),
                                              _CMP_LT_OS), s,
                          jbm_coswc_8xf64 (_mm512_sub_pd
                                           (_mm512_set1_pd (M_PI_2), y)));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4),
                                                   _CMP_LT_OS),
                               s, jbm_sinwc_8xf64 (y));
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_8xf64 and
 * jbm_coswc_8xf64 approximations (__m512).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_cos_8xf64 (const __m512d x) ///< __m512d vector.
{
  __m512d y, c, pi2;
  pi2 = _mm512_set1_pd (2. * M_PI);
  y = jbm_rest_8xf64 (x, pi2);
  c = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4),
                                                _CMP_LT_OS),
                            jbm_coswc_8xf64 (_mm512_sub_pd (y, pi2)),
                            jbm_sinwc_8xf64
                            (_mm512_sub_pd (y, _mm512_set1_pd (3. * M_PI_2))));
  c = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4),
                                                _CMP_LT_OS), c,
                            jbm_opposite_8xf64
                            (jbm_coswc_8xf64
                             (_mm512_sub_pd (_mm512_set1_pd (M_PI), y))));
  c = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4),
                                                _CMP_LT_OS), c,
                            jbm_sinwc_8xf64 (_mm512_sub_pd
                                             (_mm512_set1_pd (M_PI_2), y)));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4),
                                                   _CMP_LT_OS), c,
                               jbm_coswc_8xf64 (y));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sinwc_8xf64
 * and jbm_coswc_8xf64 approximations (__m512d).
 */
static inline void
jbm_sincos_8xf64 (const __m512d x,
                  ///< __m512d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m512d *s,   ///< pointer to the f32 function value (__m512d).
                  __m512d *c)   ///< pointer to the f32 function value (__m512d).
{
  __m512d y, pi2, z, s1, c1, s2, c2;
  __mmask16 m;
  pi2 = _mm512_set1_pd (2. * M_PI);
  y = jbm_rest_8xf64 (x, pi2);
  jbm_sincoswc_8xf64 (_mm512_sub_pd (y, pi2), &s1, &c1);
  jbm_sincoswc_8xf64 (_mm512_sub_pd (y, _mm512_set1_pd (3. * M_PI_2)), &c2,
                      &s2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4), _CMP_LT_OS);
  z = _mm512_setzero_pd ();
  s1 = _mm512_mask_blend_pd (m, s1, _mm512_sub_pd (z, s2));
  c1 = _mm512_mask_blend_pd (m, c1, c2);
  jbm_sincoswc_8xf64 (_mm512_sub_pd (_mm512_set1_pd (M_PI), y), &s2, &c2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_blend_pd (m, s1, s2);
  c1 = _mm512_mask_blend_pd (m, c1, _mm512_sub_pd (z, c2));
  jbm_sincoswc_8xf64 (_mm512_sub_pd (_mm512_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_blend_pd (m, s1, s2);
  c1 = _mm512_mask_blend_pd (m, c1, c2);
  jbm_sincoswc_8xf64 (y, &s2, &c2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4), _CMP_LT_OS);
  *s = _mm512_mask_blend_pd (m, s1, s2);
  *c = _mm512_mask_blend_pd (m, c1, c2);
}

/**
 * Function to calculate the function tan(x) from jbm_sinwc_8xf64 and
 * jbm_coswc_8xf64 approximations.
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_tan_8xf64 (const __m512d x) ///< __m512d vector.
{
  __m512d s, c;
  jbm_sincos_8xf64 (x, &s, &c);
  return _mm512_div_pd (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_atanwc0_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in\left[0,\frac12\right]\f$.
{
  const double a[10] JB_ALIGNED = {
    9.9999999999999999988350098880131410e-01,
    1.9790364737826274474033003211225036e+00,
    1.2763597145212189564865953502384577e+00,
    2.9546746828946397414064200278471676e-01,
    1.7639277573399157020779462118021500e-02,
    2.3123698071159607081902867468765628e+00,
    1.8471496502265516962365125891076585e+00,
    5.9156719979799457278683486027185371e-01,
    6.4625846927010323822388899418597147e-02,
    1.0861419677837522058022889198563474e-03
  };
  return _mm512_mul_pd (x, jbm_rational_9_4_8xf64 (jbm_sqr_8xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_atanwc1_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in\left[\frac12,1\right]\f$.
{
  const double a[17] JB_ALIGNED = {
    7.8539816339744830961566084581987599e-01,
    3.6019848928935528884465960340137432e+00,
    7.4487375237845230623458887689330376e+00,
    9.1082434414060510898995115666908167e+00,
    7.2046633212753672361640031613773788e+00,
    3.7740519627035511804411052221784210e+00,
    1.2781285312701001711685987092639674e+00,
    2.5581681984824742938379345858671711e-01,
    2.3169583706129032297801621164494009e-02,
    3.9495698328031396665071422411902205e+00,
    7.2879628119099187769306724069562724e+00,
    8.1083983348912850287664247511095260e+00,
    5.9120637834458533736606676341532886e+00,
    2.8810729714331433161564092281460773e+00,
    9.1394922488193546008617533053450878e-01,
    1.7224818123175960988680742148655125e-01,
    1.4750226980146190425631669160362206e-02
  };
  return jbm_rational_16_8_8xf64 (_mm512_sub_pd (x, _mm512_set1_pd (1.)), a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_8xf64 and
 * jbm_atanwc1_8xf64 functions (__m512d).
 *
 * \return function value (__m512d in [-pi/2,pi/2]).
 */
static inline __m512d
jbm_atan_8xf64 (const __m512d x)        ///< double number.
{
  __m512d f, ax, z;
  __mmask16 m;
  ax = jbm_abs_8xf64 (x);
  m = _mm512_cmp_pd_mask (ax, _mm512_set1_pd (1.5), _CMP_GT_OS);
  ax = _mm512_mask_blend_pd (m, ax, jbm_reciprocal_8xf64 (ax));
  f = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (ax, _mm512_set1_pd (0.5),
                                                _CMP_GT_OS),
                            jbm_atanwc0_8xf64 (ax), jbm_atanwc1_8xf64 (ax));
  f = _mm512_mask_blend_pd (m, f, _mm512_sub_pd (_mm512_set1_pd (M_PI_2), f));
  z = _mm512_setzero_pd ();
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, z, _CMP_LT_OS),
                               f, _mm512_sub_pd (z, f));

}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_8xf64
 * function (__m512d).
 *
 * \return function value (__m512d in [-pi,pi]).
 */
static inline __m512d
jbm_atan2_8xf64 (const __m512d y,       ///< __m512d y component.
                 const __m512d x)       ///< __m512d x component.
{
  __m512d f, z, pi;
  __mmask16 mx, my;
  z = _mm512_setzero_pd ();
  pi = _mm512_set1_pd (M_PI);
  f = jbm_atan_8xf64 (_mm512_div_pd (y, x));
  mx = _mm512_cmp_pd_mask (x, z, _CMP_LT_OS);
  my = _mm512_cmp_pd_mask (y, z, _CMP_LT_OS);
  f = _mm512_mask_blend_pd (my & mx, f, _mm512_sub_pd (f, pi));
  return _mm512_mask_blend_pd ((~my) & mx, f, _mm512_add_pd (f, pi));
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_8xf64 function
 * (__m512d).
 *
 * \return function value (__m512d in [-pi/2,pi/2]).
 */
static inline __m512d
jbm_asin_8xf64 (const __m512d x)        ///< __m512d number.
{
  return
    jbm_atan_8xf64 (_mm512_div_pd
                    (x,
                     _mm512_sqrt_pd (_mm512_fnmadd_pd
                                     (x, x, _mm512_set1_pd (1.)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_8xf64 function
 * (__m512d).
 *
 * \return function value (__m512d in [0,pi]).
 */
static inline __m512d
jbm_acos_8xf64 (const __m512d x)        ///< __m512d number.
{
  __m512d f;
  f =
    jbm_atan_8xf64 (_mm512_div_pd
                    (_mm512_sqrt_pd
                     (_mm512_fnmadd_pd (x, x, _mm512_set1_pd (1.))), x));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, _mm512_setzero_pd (),
                                                   _CMP_LT_OS),
                               f, _mm512_add_pd (f, _mm512_set1_pd (M_PI)));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_sinh_8xf64 (const __m512d x)        ///< __m512d number.
{
  __m512d f;
  f = jbm_exp_8xf64 (x);
  return _mm512_mul_pd (_mm512_set1_pd (0.5),
                        _mm512_sub_pd (f, jbm_reciprocal_8xf64 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_cosh_8xf64 (const __m512d x)        ///< __m512d number.
{
  __m512d f;
  f = jbm_exp_8xf64 (x);
  return _mm512_mul_pd (_mm512_set1_pd (0.5),
                        _mm512_add_pd (f, jbm_reciprocal_8xf64 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_tanh_8xf64 (const __m512d x)        ///< __m512d number.
{
  __m512d f, fi;
  f = jbm_exp_8xf64 (x);
  fi = jbm_reciprocal_8xf64 (f);
  f = _mm512_div_pd (_mm512_sub_pd (f, fi), _mm512_add_pd (f, fi));
  f = _mm512_mask_blend_pd
    (_mm512_cmp_pd_mask (x, _mm512_set1_pd (JBM_DBL_MAX_E_EXP), _CMP_GT_OS),
     f, _mm512_set1_pd (1.));
  return _mm512_mask_blend_pd
    (_mm512_cmp_pd_mask (x, _mm512_set1_pd (-JBM_DBL_MAX_E_EXP),
                         _CMP_LT_OS), f, _mm512_set1_pd (-1.));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_asinh_8xf64 (const __m512d x)       ///< __m512d number.
{
  return
    jbm_log_8xf64 (_mm512_add_pd
                   (x,
                    _mm512_sqrt_pd (_mm512_fmadd_pd
                                    (x, x, _mm512_set1_pd (1.)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_acosh_8xf64 (const __m512d x)       ///< __m512d number.
{
  return
    jbm_log_8xf64 (_mm512_add_pd
                   (x,
                    _mm512_sqrt_pd (_mm512_fmsub_pd
                                    (x, x, _mm512_set1_pd (1.)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_atanh_8xf64 (const __m512d x)       ///< __m512d number.
{
  __m512d u;
  u = _mm512_set1_pd (1.);
  return _mm512_mul_pd (_mm512_set1_pd (0.5),
                        jbm_log_8xf64 (_mm512_div_pd (_mm512_add_pd (u, x),
                                                      _mm512_sub_pd (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m512d)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_erfwc_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in\left[-1,1\right]\f$.
{
  const double a[10] JB_ALIGNED = {
    1.1283791670955125741568625140595924e+00,
    1.4214718479810524638132403970020488e-01,
    4.5306179971396543690857253459349899e-02,
    1.8274816817509842382145455741517242e-03,
    1.9503007205367896132091567678475243e-04,
    4.5930799587872320487565036900734355e-01,
    9.3254221872966235149934861274412522e-02,
    1.0583028318143433311933480099172922e-02,
    6.8136985371491773172998872537320205e-04,
    2.0308921409930923470822806343114398e-05
  };
  return _mm512_mul_pd (x, jbm_rational_9_4_8xf64 (jbm_sqr_8xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m512d)
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_erfcwc_8xf64 (const __m512d x)
    ///< __m512d vector \f$\in\left[1,\infty\right]\f$.
{
  const double a[20] JB_ALIGNED = {
    5.6418958354769171053431905176049333e-01,
    1.8068961711087721035668047582636303e+01,
    2.2022510757253783364808659279988124e+02,
    1.3175735323486293364416299596436524e+03,
    4.1723505653931692236493611641369690e+03,
    7.0505362896886770244509888328078530e+03,
    6.1198125907832643324578344059336028e+03,
    2.4898887087886410784589345555029580e+03,
    3.9404031476510540966278418298734249e+02,
    1.5468025835275747101796618568222419e+01,
    3.2526400766649515543445105783083186e+01,
    4.0585204037055623922900027619809544e+02,
    2.5157445005494375226611017002497585e+03,
    8.4032065652011294040345483852481811e+03,
    1.5388593778112773752099006975806151e+04,
    1.5090737465088611791618559746791879e+04,
    7.4211295423849975956162400081056901e+03,
    1.6051571793324163368261447072990388e+03,
    1.1562663263971111608658677334644857e+02,
    1.1686136200874353881730567222417832e+00,
  };
  const double m = 2.7213293210812948815313823864674587e+01;
  __m512d f, x2;
  x2 = jbm_sqr_8xf64 (x);
  f = _mm512_div_pd (jbm_rational_19_9_8xf64 (jbm_reciprocal_8xf64 (x2), a),
                     _mm512_mul_pd (x, jbm_exp_8xf64 (x2)));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, _mm512_set1_pd (m),
                                                   _CMP_GT_OS),
                               f, _mm512_setzero_pd ());
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_8xf64 and
 * jbm_erfcwc_8xf64
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_erf_8xf64 (const __m512d x) ///< __m512d vector.
{
  __m512d ax, u, f;
  ax = jbm_abs_8xf64 (x);
  u = _mm512_set1_pd (1.);
  f =
    _mm512_mul_pd (_mm512_div_pd (x, ax),
                   _mm512_sub_pd (u, jbm_erfcwc_8xf64 (ax)));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (ax, u, _CMP_LT_OS),
                               f, jbm_erfwc_8xf64 (x));

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_8xf64 and
 * jbm_erfcwc_8xf64
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_erfc_8xf64 (const __m512d x)        ///< __m512d vector.
{
  __m512d ax, u, f;
  ax = jbm_abs_8xf64 (x);
  u = _mm512_set1_pd (1.);
  f = _mm512_sub_pd (u, _mm512_mul_pd (_mm512_div_pd (x, ax),
                                       _mm512_sub_pd (u,
                                                      jbm_erfcwc_8xf64 (ax))));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (ax, u, _CMP_LT_OS),
                               f, _mm512_sub_pd (u, jbm_erfwc_8xf64 (x)));
}

/**
 * Function to calculate the solution of a __m512d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_quadratic_reduced_8xf64 (__m512d a,
///< __m512d vector of 1st order coefficient of the equations.
                                   __m512d b,
///< __m512d vector of 0th order coefficient of the equations.
                                   const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                                   const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d k1, k2;
  k1 = _mm512_set1_pd (-0.5);
  a = _mm512_mul_pd (a, k1);
  b = _mm512_sqrt_pd (_mm512_sub_pd (jbm_sqr_8xf64 (a), b));
  k1 = _mm512_add_pd (a, b);
  k2 = _mm512_sub_pd (a, b);
  k1 = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (k1, x1, _CMP_LT_OS), k1, k2);
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (k1, x2, _CMP_GT_OS), k1, k2);
}

/**
 * Function to calculate the solution of a __m512d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_quadratic_8xf64 (const __m512d a,
///< __m512d vector of 2nd order coefficient of the equations.
                           const __m512d b,
///< __m512d vector of 1st order coefficient of the equations.
                           const __m512d c,
///< __m512d vector of 0th order coefficient of the equations.
                           const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                           const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d k1, k2;
  k1 = jbm_solve_quadratic_reduced_8xf64 (_mm512_div_pd (b, a),
                                          _mm512_div_pd (c, a), x1, x2);
  k2 = _mm512_div_pd (jbm_opposite_8xf64 (c), b);
  return _mm512_mask_blend_pd (jbm_small_8xf64 (a), k1, k2);
}

/**
 * Function to calculate the solution of a __m512d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_cubic_reduced_8xf64 (const __m512d a,
                               ///< 2nd order coefficient of the equation.
                               const __m512d b,
                               ///< 1st order coefficient of the equation.
                               const __m512d c,
                               ///< 0th order coefficient of the equation.
                               const __m512d x1,
                               ///< left limit of the solution interval.
                               const __m512d x2)
    ///< right limit of the solution interval.
{
  __m512d a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm512_set1_pd (2. * M_PI / 3.);
  c_2 = _mm512_set1_pd (0.5);
  c_3 = _mm512_set1_pd (1. / 3.);
  a3 = _mm512_mul_pd (a, c_3);
  k0 = _mm512_mul_pd (a3, a3);
  k1 = _mm512_fmsub_pd (b, c_3, k0);
  k0 =
    _mm512_fmsub_pd (_mm512_fmsub_pd (b, a3, c), c_2, _mm512_mul_pd (a3, k0));
  k3 = _mm512_mul_pd (k1, _mm512_mul_pd (k1, k1));
  k2 = _mm512_fmadd_pd (k0, k0, k3);
  l1 = _mm512_sqrt_pd (jbm_opposite_8xf64 (k1));
  l0 = _mm512_mul_pd (jbm_acos_8xf64 (_mm512_div_pd (k0, k3)), c_3);
  l1 = _mm512_add_pd (l1, l1);
  l2 = _mm512_fmsub_pd (l1, jbm_cos_8xf64 (k0), a3);
  l3 = _mm512_fmsub_pd (l1, jbm_cos_8xf64 (_mm512_add_pd (l0, c2p_3)), a3);
  l3 = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (l2, x1, _CMP_LT_OS)
                             | _mm512_cmp_pd_mask (l2, x2, _CMP_GT_OS), l3, l2);
  l4 = _mm512_fmsub_pd (l1, jbm_cos_8xf64 (_mm512_sub_pd (l0, c2p_3)), a);
  l4 = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (l3, x1, _CMP_LT_OS)
                             | _mm512_cmp_pd_mask (l3, x2, _CMP_GT_OS), l4, l3);
  k1 = _mm512_sqrt_pd (k2);
  l5 = _mm512_add_pd (k0, k1);
  l5 = jbm_cbrt_8xf64 (k2);
  k0 = _mm512_sub_pd (k0, k1);
  l5 = _mm512_add_pd (l5, _mm512_sub_pd (jbm_cbrt_8xf64 (k0), a3));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (k2, _mm512_setzero_pd (),
                                                   _CMP_LT_OS), l4, l5);

}

/**
 * Function to calculate the solution of a __m512d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_cubic_8xf64 (__m512d a,
///< __m512d vector of 3rd order coefficient of the equations.
                       __m512d b,
///< __m512d vector of 2nd order coefficient of the equations.
                       __m512d c,
///< __m512d vector of 1st order coefficient of the equations.
                       __m512d d,
///< __m512d vector of 0th order coefficient of the equations.
                       __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                       __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  return
    _mm512_mask_blend_pd (jbm_small_8xf64 (a),
                          jbm_solve_cubic_reduced_8xf64 (_mm512_div_pd (b, a),
                                                         _mm512_div_pd (c, a),
                                                         _mm512_div_pd (d, a),
                                                         x1, x2),
                          jbm_solve_quadratic_8xf64 (b, c, d, x1, x2));

}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_total_8xf64 (const __m512d d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m512d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_null_8xf64 (const __m512d d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const __m512d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_centred_8xf64 (const __m512d d1,
                                ///< 1st flux limiter function parameter.
                                const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  return _mm512_mask_blend_pd (jbm_small_8xf64 (d2),
                               _mm512_div_pd (d1, d2), _mm512_setzero_pd ());

}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_superbee_8xf64 (const __m512d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_div_pd (d1, d2);
  r = _mm512_max_pd (_mm512_min_pd (jbm_dbl_8xf64 (r), _mm512_set1_pd (1.)),
                     _mm512_min_pd (r, _mm512_set1_pd (2.)));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_minmod_8xf64 (const __m512d d1,
                               ///< 1st flux limiter function parameter.
                               const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_min_pd (_mm512_div_pd (d1, d2), _mm512_set1_pd (1.));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_VanLeer_8xf64 (const __m512d d1,
                                ///< 1st flux limiter function parameter.
                                const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r, k;
  r = _mm512_div_pd (d1, d2);
  k = jbm_abs_8xf64 (r);
  r = _mm512_div_pd (_mm512_add_pd (r, k),
                     _mm512_add_pd (_mm512_set1_pd (1.), k));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_VanAlbada_8xf64 (const __m512d d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r, k;
  r = _mm512_div_pd (d1, d2);
  k = jbm_sqr_8xf64 (r);
  r = _mm512_div_pd (_mm512_add_pd (r, k),
                     _mm512_add_pd (_mm512_set1_pd (1.), k));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_minsuper_8xf64 (const __m512d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_min_pd (_mm512_div_pd (d1, d2), _mm512_set1_pd (2.));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_supermin_8xf64 (const __m512d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_div_pd (d1, d2);
  r = _mm512_min_pd (jbm_dbl_8xf64 (r), _mm512_set1_pd (1.));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_monotonized_central_8xf64 (const __m512d d1,
///< 1st flux limiter function parameter.
                                            const __m512d d2)
///< 2nd flux limiter function parameter.
{
  __m512d r, rm;
  r = _mm512_div_pd (d1, d2);
  rm = _mm512_mul_pd (_mm512_set1_pd (0.5),
                      _mm512_add_pd (r, _mm512_set1_pd (1.)));
  rm = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (r, _mm512_set1_pd (3.),
                                                 _CMP_LT_OS),
                             _mm512_set1_pd (2.), rm);
  rm = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (r, _mm512_set1_pd (1. / 3.),
                                                 _CMP_GT_OS),
                             rm, jbm_dbl_8xf64 (r));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_mean_8xf64 (const __m512d d1,
                             ///< 1st flux limiter function parameter.
                             const __m512d d2)
    ///< 2nd flux limiter function parameter.
{
  __m512d r;
  r = _mm512_mul_pd (_mm512_set1_pd (0.5),
                     _mm512_add_pd (_mm512_set1_pd (1.),
                                    _mm512_div_pd (d1, d2)));
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                   _mm512_set1_pd (DBL_EPSILON),
                                                   _CMP_GT_OS),
                               _mm512_setzero_pd (), r);
}

/**
 * Function to do a flux limiter function (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_8xf64 (const __m512d d1,
                        ///< 1st flux limiter function parameter.
                        const __m512d d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_8xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_8xf64 (d1, d2);
    }
  return jbm_flux_limiter_mean_8xf64 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m512d).
 *
 * \return __m512d vector of integral values.
 */
static inline __m512d
jbm_integral_8xf64 (__m512d (*f) (__m512d),
                    ///< pointer to the function to integrate.
                    const __m512d x1,   ///< left limit of the interval.
                    const __m512d x2)   ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] JB_ALIGNED = { 2. };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] JB_ALIGNED = { 8. / 9., 5. / 9. },
    b[2] JB_ALIGNED = { 0., 7.745966692414834e-1 };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] JB_ALIGNED = {
    128. / 225.,
    4.786286704993665e-1,
    2.369268850561891e-1
  }, b[3] JB_ALIGNED = {
    0.,
    5.384693101056831e-1,
    9.061798459386640e-1
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] JB_ALIGNED = {
    4.179591836734694e-1,
    3.818300505051189e-1,
    2.797053914892767e-1,
    1.294849661688697e-1
  }, b[4] JB_ALIGNED = {
    0.,
    4.058451513773972e-1,
    7.415311855993944e-1,
    9.491079123427585e-1
  };
#endif
  __m512d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_pd (0.5);
  dx = _mm512_mul_pd (h, _mm512_sub_pd (x2, x1));
  x = _mm512_mul_pd (h, _mm512_add_pd (x2, x1));
  k = _mm512_set1_pd (a[0]);
  k = _mm512_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_pd (b[i]);
      k2 = _mm512_mul_pd (k2, dx);
      f1 = f (_mm512_sub_pd (x, k2));
      f2 = f (_mm512_add_pd (x, k2));
      h = _mm512_set1_pd (a[i]);
      k = _mm512_fmadd_pd (h, _mm512_add_pd (f1, f2), k);
    }
#endif
  k = _mm512_mul_pd (k, dx);
  return k;
}

#endif
