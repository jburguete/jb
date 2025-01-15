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
 * \file math_avx.h
 * \brief Header file with useful mathematical functions for __m256.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2024, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_AVX__H
#define JB_MATH_AVX__H 1

/**
 * union to work with bits in 8 packed float numbers.
 */
typedef union
{
  __m256 x;                     ///< floating point.
  __m256i i;                    ///< bits.
} JBM8xF32;

/**
 * union to work with bits in 4 packed double numbers.
 */
typedef union
{
  __m256d x;                    ///< floating point.
  __m256i i;                    ///< bits.
} JBM4xF64;

/* Debug functions

static inline void
print_m256i32 (FILE *file, const char *label, __m256i x)
{
  int y[8] JB_ALIGNED;
  unsigned int i;
  _mm256_store_si256 ((__m128i *) y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m256i64 (FILE *file, const char *label, __m256i x)
{
  long long int y[4] JB_ALIGNED;
  unsigned int i;
  _mm256_store_si256 ((__m128i *) y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_m256 (FILE *file, const char *label, __m256 x)
{
  float y[8] JB_ALIGNED;
  unsigned int i;
  _mm256_store_ps (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m256d (FILE *file, const char *label, __m256d x)
{
  double y[4] JB_ALIGNED;
  unsigned int i;
  _mm256_store_pd (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

*/

/**
 * Function to calculate the additive inverse value of a __m256 vector.
 *
 * \return opposite value vector (__m256).
 */
static inline __m256
jbm_opposite_8xf32 (const __m256 x)     ///< __m256 vector.
{
  JBM8xF32 y;
  y.i = _mm256_set1_epi32 ((int) 0x80000000);
  return _mm256_xor_ps (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m256 vector.
 *
 * \return reciprocal value vector (__m256).
 */
static inline __m256
jbm_reciprocal_8xf32 (const __m256 x)   ///< __m256 vector.
{
  return _mm256_div_ps (_mm256_set1_ps (1.f), x);
}

/**
 * Function to calculate the absolute value of a __m256 vector.
 *
 * \return absolute value vector (__m256).
 */
static inline __m256
jbm_abs_8xf32 (const __m256 x)  ///< __m256 vector.
{
  JBM8xF32 y;
  y.i = _mm256_set1_epi32 (0x7fffffffl);
  return _mm256_and_ps (x, y.x);
}

/**
 * Function to calculate the hypot function (__m256).
 *
 * \return function value vector (__m256).
 */
static inline __m256
jbm_hypot_8xf32 (const __m256 x,        ///< 1st __m256 vector.
                 const __m256 y)        ///< 2nd __m256 vector.
{
  return _mm256_sqrt_ps (_mm256_fmadd_ps (x, x, _mm256_mul_ps (y, y)));
}

/**
 * Function to calculate the rest of a division (__m256).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline __m256
jbm_rest_8xf32 (const __m256 x, ///< dividend (__m256).
                const __m256 d) ///< divisor (__m256).
{
  return _mm256_fnmadd_ps (_mm256_floor_ps (_mm256_div_ps (x, d)), d, x);
}

/**
 * Function to implement the standard frexp function (__m256).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m256
jbm_frexp_8xf32 (const __m256 x,        ///< __m256 vector.
                 __m256i *e)    ///< pointer to the extracted exponents vector.
{
  JBM8xF32 a, y, y2, z;
  __m256i e8, b, m1, m2, m3, zi;
  a.x = x;
  b = _mm256_set1_epi32 (0x7f800000);
  y.i = _mm256_and_si256 (a.i, b);
  m1 = _mm256_cmpeq_epi32 (y.i, b);
  zi = _mm256_setzero_si256 ();
  m2 = _mm256_cmpeq_epi32 (y.i, zi);
  y2.x = x;
  y2.i = _mm256_and_si256 (y2.i, _mm256_set1_epi32 (0x007fffff));
  m3 = _mm256_cmpeq_epi32 (y2.i, zi);
  y2.i = _mm256_set1_epi32 (0x00400000);
  z.x = _mm256_div_ps (x, y2.x);
  z.i = _mm256_and_si256 (z.i, b);
  e8 = _mm256_blendv_epi8 (_mm256_sub_epi32 (_mm256_srli_epi32 (y.i, 23),
                                             _mm256_set1_epi32 (126)),
                           _mm256_sub_epi32 (_mm256_srli_epi32 (z.i, 23),
                                             _mm256_set1_epi32 (253)), m2);
  y.x = _mm256_blendv_ps (y.x, _mm256_mul_ps (y2.x, z.x),
                          _mm256_castsi256_ps (m2));
  m1 = _mm256_or_si256 (m1, _mm256_and_si256 (m2, m3));
  e8 = _mm256_blendv_epi8 (e8, zi, m1);
  *e = e8;
  return
    _mm256_blendv_ps (_mm256_mul_ps (_mm256_set1_ps (0.5f),
                                     _mm256_div_ps (x, y.x)), x,
                      _mm256_castsi256_ps (m1));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m256i).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_exp2n_8xf32 (__m256i e)     ///< exponent vector (__m256i).
{
  __m256 x;
  x = _mm256_blendv_ps
    (_mm256_castsi256_ps
     (_mm256_sllv_epi32 (_mm256_set1_epi32 (0x00400000),
                         _mm256_sub_epi32 (_mm256_set1_epi32 (-127), e))),
     _mm256_castsi256_ps
     (_mm256_slli_epi32 (_mm256_add_epi32 (e, _mm256_set1_epi32 (127)), 23)),
     _mm256_castsi256_ps (_mm256_cmpgt_epi32 (e, _mm256_set1_epi32 (-127))));
  x = _mm256_blendv_ps
    (x, _mm256_setzero_ps (),
     _mm256_castsi256_ps (_mm256_cmpgt_epi32 (_mm256_set1_epi32 (-150), e)));
  return
    _mm256_blendv_ps
    (x, _mm256_set1_ps (INFINITY),
     _mm256_castsi256_ps (_mm256_cmpgt_epi32 (e, _mm256_set1_epi32 (127))));
}


/**
 * Function to implement the standard ldexp function (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_ldexp_8xf32 (const __m256 x,        ///< __m256 vector.
                 __m256i e)     ///< exponent vector (__m256i).
{
  return _mm256_mul_ps (x, jbm_exp2n_8xf32 (e));
}

/**
 * Function to check small __m256 vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m256
jbm_small_8xf32 (const __m256 x)        ///< __m256d vector.
{
  return _mm256_cmp_ps (jbm_abs_8xf32 (x), _mm256_set1_ps (FLT_EPSILON),
                        _CMP_LT_OS);
}

/**
 * Function to calculate the __m256 vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m256 vector.
 */
static inline __m256
jbm_modmin_8xf32 (const __m256 a,       ///< 1st __m256d vector.
                  const __m256 b)       ///< 2nd __m256d vector.
{
  __m256 aa, ab, y, z;
  z = _mm256_setzero_ps ();
  ab = _mm256_mul_ps (a, b);
  y = _mm256_blendv_ps (z, a, _mm256_cmp_ps (ab, z, _CMP_GT_OS));
  aa = jbm_abs_8xf32 (y);
  ab = jbm_abs_8xf32 (b);
  return _mm256_blendv_ps (y, b, _mm256_cmp_ps (aa, ab, _CMP_GT_OS));
}

/**
 * Function to interchange 2 __m256 vectors.
 */
static inline void
jbm_change_8xf32 (__m256 *restrict a,   ///< 1st __m256 vector pointer.
                  __m256 *restrict b)   ///< 2nd __m256 vector pointer.
{
  __m256 c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m256 vector.
 *
 * \return __m256 double.
 */
static inline __m256
jbm_dbl_8xf32 (const __m256 x)  ///< __m256d vector.
{
  return _mm256_add_ps (x, x);
}

/**
 * Function to calculate the square of the components of a __m256 vector.
 *
 * \return __m256 vector square.
 */
static inline __m256
jbm_sqr_8xf32 (const __m256 x)  ///< __m256 vector.
{
  return _mm256_mul_ps (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m256 vectors of 2D points.
 *
 * \return __m256 vector of y-coordinates of the extrapolated points.
 */
static inline __m256
jbm_extrapolate_8xf32 (const __m256 x,
                       ///< __m256 vector of x-coordinates of the extrapolated
                       ///< points.
                       const __m256 x1,
                       ///< __m256 vector of x-coordinates of the 1st points.
                       const __m256 x2,
                       ///< __m256 vector of x-coordinates of the 2nd points.
                       const __m256 y1,
                       ///< __m256 vector of y-coordinates of the 1st points.
                       const __m256 y2)
                     ///< __m256 vector of y-coordinates of the 2nd points.
{
  __m256 d;
  d = _mm256_sub_ps (x, x1);
  return _mm256_fmadd_ps (d, _mm256_div_ps (_mm256_sub_ps (y2, y1),
                                            _mm256_sub_ps (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m256 vectors of 2D points.
 *
 * \return __m256 vector of y-coordinates of the interpolated points.
 */
static inline __m256
jbm_interpolate_8xf32 (const __m256 x,
                       ///< __m256 vector of x-coordinates of the interpolated
                       ///< points.
                       const __m256 x1,
                       ///< __m256 vector of x-coordinates of the 1st points.
                       const __m256 x2,
                       ///< __m256 vector of x-coordinates of the 2nd points.
                       const __m256 y1,
                       ///< __m256 vector of y-coordinates of the 1st points.
                       const __m256 y2)
                     ///< __m256 vector of y-coordinates of the 2nd points.
{
  __m256 k;
  k = jbm_extrapolate_8xf32 (x, x1, x2, y1, y2);
  k = _mm256_blendv_ps (y1, k, _mm256_cmp_ps (x, x1, _CMP_GT_OS));
  return _mm256_blendv_ps (y2, k, _mm256_cmp_ps (x, x2, _CMP_LT_OS));
}

/**
 * Function to calculate the length of a __m256 vector of 2D segments.
 *
 * \return __m256 vector of segment lengths.
 */
static inline __m256
jbm_v2_length_8xf32 (const __m256 x1,
///< __m256 vector of x-coordinates of the 1st points defining the segment.
                     const __m256 y1,
///< __m256 vector of y-coordinates of the 1st points defining the segment.
                     const __m256 x2,
///< __m256 vector of x-coordinates of the 2nd points defining the segment.
                     const __m256 y2)
///< __m256 vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_8xf32 (_mm256_sub_ps (x2, x1), _mm256_sub_ps (y2, y1));
}

/**
 * Function to calculate the length of a __m256 vector of 3D segments.
 *
 * \return __m256 vector of segment lengths.
 */
static inline __m256
jbm_v3_length_8xf32 (const __m256 x1,
///< __m256 vector of x-coordinates of the 1st points defining the segments.
                     const __m256 y1,
///< __m256 vector of y-coordinates of the 1st points defining the segments.
                     const __m256 z1,
///< __m256 vector of z-coordinates of the 1st points defining the segments.
                     const __m256 x2,
///< __m256 vector of x-coordinates of the 2nd points defining the segments.
                     const __m256 y2,
///< __m256 vector of y-coordinates of the 2nd points defining the segments.
                     const __m256 z2)
///< __m256 vector of z-coordinates of the 2nd points defining the segments.
{
  __m256 dx, dy, dz;
  dx = jbm_sqr_8xf32 (_mm256_sub_ps (x2, x1));
  dy = _mm256_sub_ps (y2, y1);
  dy = _mm256_fmadd_ps (dy, dy, dx);
  dz = _mm256_sub_ps (z2, z1);
  return _mm256_sqrt_ps (_mm256_fmadd_ps (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, _mm256_set1_ps (p[1]), _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_4_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_5_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_6_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_7_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_8_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_9_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_10_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_11_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_12_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_13_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_14_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_15_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_16_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_17_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_18_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_19_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_20_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_21_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_22_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_23_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_24_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_25_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_24_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_26_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_25_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_27_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_26_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_28_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_27_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_polynomial_29_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_polynomial_28_8xf32 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_1_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[1]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_2_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+1st order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_2_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[2]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_3_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_3_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_3_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[3]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_4_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_4_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_4_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_4_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[4]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_5_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_5_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_5_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_5_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_5_4_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[5]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_6_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_6_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_6_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_6_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_6_4_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_6_5_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[6]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_4_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_5_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_7_6_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[7]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_4_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_5_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_6_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_8_7_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[8]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_0_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_1_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_2_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_3_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_4_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_5_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_6_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_7_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_9_8_8xf32 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[9]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_10_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[10]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_11_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[11]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_12_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[12]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_13_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[13]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_14_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[14]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_15_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[15]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_16_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[16]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_17_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[17]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_18_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[18]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_19_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[19]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_20_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[20]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_21_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[21]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_22_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[22]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_23_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[23]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_24_23_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_23_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[24]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_24_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_23_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_23_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_25_24_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_24_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[25]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_25_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_24_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_23_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_23_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_24_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_24_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_26_25_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_25_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[26]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_26_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_25_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_24_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_23_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_23_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_24_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_24_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_25_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_25_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 26),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_27_26_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_26_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[27]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+28th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_27_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_26_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_25_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_24_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_23_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_23_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_24_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_24_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_25_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_25_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 26),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_26_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_26_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 27),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_28_27_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_27_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[28]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+29th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_0_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_polynomial_28_8xf32 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_1_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_1_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_27_8xf32 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_2_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_2_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_26_8xf32 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_3_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_3_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_25_8xf32 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_4_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_4_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_24_8xf32 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_5_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_5_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_23_8xf32 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_6_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_6_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_22_8xf32 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_7_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_7_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_21_8xf32 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_8_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_8_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_20_8xf32 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_9_8xf32 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_9_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_19_8xf32 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_10_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_10_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_18_8xf32 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_11_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_11_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_17_8xf32 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_12_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_12_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_16_8xf32 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_13_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_13_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_15_8xf32 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_14_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_14_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_14_8xf32 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_15_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_15_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_13_8xf32 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_16_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_16_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_12_8xf32 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_17_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_17_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_11_8xf32 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_18_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_18_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_10_8xf32 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_19_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_19_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_9_8xf32 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_20_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_20_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_8_8xf32 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_21_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_21_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_7_8xf32 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_22_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_22_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_6_8xf32 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_23_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_23_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_5_8xf32 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_24_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_24_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_4_8xf32 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_25_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_25_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_3_8xf32 (x, p + 26),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_26_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_26_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_2_8xf32 (x, p + 27),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_27_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_27_8xf32 (x, p),
                        _mm256_fmadd_ps (x, jbm_polynomial_1_8xf32 (x, p + 28),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_rational_29_28_8xf32 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_polynomial_28_8xf32 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[29]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_expm1wc_8xf32 (const __m256 x)
///< __m256 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = 9.9999999917826835759154742878523887e-01f;
  const float a2 = -4.9999999958913417879577371439261924e-01f;
  const float a3 = 8.3333136366700581865508474051734715e-02f;
  const float a5 = -1.3833464660905326042591440964123531e-03f;
  __m256 x2;
  x2 = jbm_sqr_8xf32 (x);
  x2 = _mm256_fmadd_ps (x2, _mm256_set1_ps (a5), _mm256_set1_ps (a3));
  x2 = _mm256_fmadd_ps (x2, x, _mm256_set1_ps (a2));
  x2 = _mm256_fmadd_ps (x2, x, _mm256_set1_ps (1.f));
  return _mm256_mul_ps (x, _mm256_div_ps (_mm256_set1_ps (a1), x2));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m256).
 *
 * \return function value.
 */
static inline __m256
jbm_exp2wc_8xf32 (const __m256 x)
                  ///< __m256 vector \f$\in\left[\frac12,1\right]\f$.
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
  return jbm_polynomial_6_8xf32 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_8xf32 and
 * jbm_exp2n_8xf32 functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_exp2_8xf32 (const __m256 x) ///< __m256 vector.
{
  __m256 y, f;
  y = _mm256_floor_ps (x);
  f = _mm256_sub_ps (x, y);
  y = jbm_exp2n_8xf32 (_mm256_cvtps_epi32 (y));
  return _mm256_mul_ps (y, jbm_exp2wc_8xf32 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_8xf32 function
 * (__m256).
 *
 * \return function value.
 */
static inline __m256
jbm_exp_8xf32 (const __m256 x)  ///< __m256 vector.
{
  return jbm_exp2_8xf32 (_mm256_mul_ps (x, _mm256_set1_ps (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_8xf32
 * function (__m256).
 *
 * \return function value.
 */
static inline __m256
jbm_exp10_8xf32 (const __m256 x)        ///< __m256 vector.
{
  return jbm_exp2_8xf32 (_mm256_mul_ps (x, _mm256_set1_ps (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_8xf32 and
 * jbm_exp_8xf32 functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_expm1_8xf32 (const __m256 x)        ///< __m256 vector.
{
  return
    _mm256_blendv_ps (_mm256_sub_ps (jbm_exp_8xf32 (x), _mm256_set1_ps (1.f)),
                      jbm_expm1wc_8xf32 (x),
                      _mm256_cmp_ps (jbm_abs_8xf32 (x),
                                     _mm256_set1_ps (M_LN2f / 2.f),
                                     _CMP_LT_OS));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_log2wc_8xf32 (const __m256 x)       ///< __m256 vector.
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
  return jbm_rational_6_3_8xf32 (x, a);
}

/**
 * Function to calculate the function log2(x) using jbm_log2wc_8xf32 and
 * jbm_frexp_8xf32 (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_log2_8xf32 (const __m256 x) ///< __m256 vector.
{
  __m256 y, z;
  __m256i e;
  y = jbm_frexp_8xf32 (x, &e);
  y = _mm256_add_ps (jbm_log2wc_8xf32 (y), _mm256_cvtepi32_ps (e));
  z = _mm256_setzero_ps ();
  y = _mm256_blendv_ps (_mm256_set1_ps (-INFINITY), y,
                        _mm256_cmp_ps (x, z, _CMP_GT_OS));
  return _mm256_blendv_ps (y, _mm256_set1_ps (NAN),
                           _mm256_cmp_ps (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the function log(x) using jbm_log2_8xf32 (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_log_8xf32 (const __m256 x)  ///< __m256 vector.
{
  return _mm256_mul_ps (jbm_log2_8xf32 (x), _mm256_set1_ps (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_8xf32.
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_log10_8xf32 (const __m256 x)        ///< __m256 vector.
{
  return _mm256_mul_ps (jbm_log2_8xf32 (x), _mm256_set1_ps (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (__m256).
 *
 * \return function value (__m256) (__m256).
 */
static inline __m256
jbm_pown_8xf32 (const __m256 x, ///< __m256 vector.
                const int e)    ///< exponent (int).
{
  __m256 f, xn;
  unsigned int i;
  f = _mm256_set1_ps (1.f);
  if (e < 0)
    xn = _mm256_div_ps (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_8xf32 (xn))
    if (i & 1)
      f = _mm256_mul_ps (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_exp2_8xf32 and
 * jbm_log2_8xf32 functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_pow_8xf32 (const __m256 x,  ///< __m256 vector.
               const float e)   ///< exponent (float).
{
  float f;
  f = floorf (e);
  if (f == e)
    return jbm_pown_8xf32 (x, (int) e);
  return
    jbm_exp2_8xf32 (_mm256_mul_ps (_mm256_set1_ps (e), jbm_log2_8xf32 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_8xf32 and
 * jbm_pow_8xf32 functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_cbrt_8xf32 (const __m256 x) ///< __m256 vector.
{
  __m256 f, z;
  f = jbm_pow_8xf32 (jbm_abs_8xf32 (x), 1.f / 3.f);
  z = _mm256_setzero_ps ();
  return _mm256_blendv_ps (_mm256_sub_ps (z, f), f,
                           _mm256_cmp_ps (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m256)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_sinwc_8xf32 (const __m256 x)
                 ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const float a[4] JB_ALIGNED = {
    9.9999999652998170520234859388240338e-01f,
    -1.6666653850132705938945722106817969e-01f,
    8.3322256622392457162205759786691734e-03f,
    -1.9524867674489682553254582414001857e-04f
  };
  return _mm256_mul_ps (x, jbm_polynomial_3_8xf32 (jbm_sqr_8xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m256):
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_coswc_8xf32 (const __m256 x)
                 ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const float a[5] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00f,
    -4.9999999965238906843549904534867220e-01f,
    4.1666653828165636463917247496043632e-02f,
    -1.3887779469291056608109602187665577e-03f,
    2.4484799013341679093941386831846651e-05f
  };
  return jbm_polynomial_4_8xf32 (jbm_sqr_8xf32 (x), a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_8xf32 approximation (__m256).
 */
static inline void
jbm_sincoswc_8xf32 (const __m256 x,
                    ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m256 *s,  ///< pointer to the sin function value (__m256).
                    __m256 *c)  ///< pointer to the cos function value (__m256).
{
  __m256 s0;
  *s = s0 = jbm_sinwc_8xf32 (x);
  *c = _mm256_sqrt_ps (_mm256_fnmadd_ps (s0, s0, _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_8xf32 and
 * jbm_coswc_8xf32 approximations (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_sin_8xf32 (const __m256 x)  ///< __m256 vector.
{
  __m256 y, s, pi2;
  pi2 = _mm256_set1_ps (2.f * M_PIf);
  y = jbm_rest_8xf32 (x, pi2);
  s = jbm_sinwc_8xf32 (_mm256_sub_ps (y, pi2));
  s = _mm256_blendv_ps (s,
                        jbm_opposite_8xf32
                        (jbm_coswc_8xf32
                         (_mm256_sub_ps (_mm256_set1_ps (3.f * M_PI_2f), y))),
                        _mm256_cmp_ps (y, _mm256_set1_ps (7.f * M_PI_4f),
                                       _CMP_LT_OS));
  s =
    _mm256_blendv_ps (s,
                      jbm_sinwc_8xf32 (_mm256_sub_ps
                                       (_mm256_set1_ps (M_PIf), y)),
                      _mm256_cmp_ps (y, _mm256_set1_ps (5.f * M_PI_4f),
                                     _CMP_LT_OS));
  s =
    _mm256_blendv_ps (s,
                      jbm_coswc_8xf32 (_mm256_sub_ps
                                       (_mm256_set1_ps (M_PI_2f), y)),
                      _mm256_cmp_ps (y, _mm256_set1_ps (3.f * M_PI_4f),
                                     _CMP_LT_OS));
  return _mm256_blendv_ps (s, jbm_sinwc_8xf32 (y),
                           _mm256_cmp_ps (y, _mm256_set1_ps (M_PI_4f),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_8xf32 and
 * jbm_coswc_8xf32 approximations (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_cos_8xf32 (const __m256 x)  ///< __m256 vector.
{
  __m256 y, c, pi2;
  pi2 = _mm256_set1_ps (2.f * M_PIf);
  y = jbm_rest_8xf32 (x, pi2);
  c = jbm_coswc_8xf32 (_mm256_sub_ps (y, pi2));
  c = _mm256_blendv_ps (c,
                        jbm_sinwc_8xf32
                        (_mm256_sub_ps (y, _mm256_set1_ps (3.f * M_PI_2f))),
                        _mm256_cmp_ps (y, _mm256_set1_ps (7.f * M_PI_4f),
                                       _CMP_LT_OS));
  c = _mm256_blendv_ps (c,
                        jbm_opposite_8xf32
                        (jbm_coswc_8xf32
                         (_mm256_sub_ps (_mm256_set1_ps (M_PIf), y))),
                        _mm256_cmp_ps (y, _mm256_set1_ps (5.f * M_PI_4f),
                                       _CMP_LT_OS));
  c =
    _mm256_blendv_ps (c,
                      jbm_sinwc_8xf32 (_mm256_sub_ps
                                       (_mm256_set1_ps (M_PI_2f), y)),
                      _mm256_cmp_ps (y, _mm256_set1_ps (3.f * M_PI_4f),
                                     _CMP_LT_OS));
  return _mm256_blendv_ps (c, jbm_coswc_8xf32 (y),
                           _mm256_cmp_ps (y, _mm256_set1_ps (M_PI_4f),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_sinwc_8xf32 and jbm_coswc_8xf32 approximations (__m256).
 */
static inline void
jbm_sincos_8xf32 (const __m256 x,
                  ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m256 *s,    ///< pointer to the sin function value (__m256).
                  __m256 *c)    ///< pointer to the cos function value (__m256).
{
  __m256 y, pi2, z, m, s1, c1, s2, c2;
  pi2 = _mm256_set1_ps (2.f * M_PIf);
  y = jbm_rest_8xf32 (x, pi2);
  jbm_sincoswc_8xf32 (_mm256_sub_ps (y, pi2), &s1, &c1);
  jbm_sincoswc_8xf32 (_mm256_sub_ps (y, _mm256_set1_ps (3.f * M_PI_2f)), &c2,
                      &s2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (7.f * M_PI_4f), _CMP_LT_OS);
  z = _mm256_setzero_ps ();
  s1 = _mm256_blendv_ps (s1, _mm256_sub_ps (z, s2), m);
  c1 = _mm256_blendv_ps (c1, c2, m);
  jbm_sincoswc_8xf32 (_mm256_sub_ps (_mm256_set1_ps (M_PIf), y), &s2, &c2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (5.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm256_blendv_ps (s1, s2, m);
  c1 = _mm256_blendv_ps (c1, _mm256_sub_ps (z, c2), m);
  jbm_sincoswc_8xf32 (_mm256_sub_ps (_mm256_set1_ps (M_PI_2f), y), &c2, &s2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (3.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm256_blendv_ps (s1, s2, m);
  c1 = _mm256_blendv_ps (c1, c2, m);
  jbm_sincoswc_8xf32 (y, &s2, &c2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (M_PI_4f), _CMP_LT_OS);
  *s = _mm256_blendv_ps (s1, s2, m);
  *c = _mm256_blendv_ps (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_8xf32 function
 * (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_tan_8xf32 (const __m256 x)  ///< __m256 vector.
{
  __m256 s, c;
  jbm_sincos_8xf32 (x, &s, &c);
  return _mm256_div_ps (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_atanwc0_8xf32 (const __m256 x)
                   ///< __m256 vector \f$\in\left[0,\frac12\right]\f$.
{
  const float a[4] JB_ALIGNED = {
    9.9999984048730143841335295268244848e-01f,
    4.9566847198521400589504493089955823e-01f,
    8.2898705878810240458099950004542931e-01f,
    7.6658333542753920209846592962853791e-02f
  };
  return _mm256_mul_ps (x, jbm_rational_3_1_8xf32 (jbm_sqr_8xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_atanwc1_8xf32 (const __m256 x)
                   ///< __m256 vector \f$\in\left[\frac12,1\right]\f$.
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
  return jbm_rational_7_3_8xf32 (_mm256_sub_ps (x, _mm256_set1_ps (1.f)), a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_8xf32 and
 * jbm_atanwc1_8xf32 functions (__m256).
 *
 * \return function value (in [-pi/2,pi/2]) (__m256).
 */
static inline __m256
jbm_atan_8xf32 (const __m256 x) ///< __m256 vector.
{
  __m256 f, ax, m, z;
  ax = jbm_abs_8xf32 (x);
  m = _mm256_cmp_ps (ax, _mm256_set1_ps (1.5f), _CMP_GT_OS);
  ax = _mm256_blendv_ps (ax, jbm_reciprocal_8xf32 (ax), m);
  f = _mm256_blendv_ps (jbm_atanwc0_8xf32 (ax), jbm_atanwc1_8xf32 (ax),
                        _mm256_cmp_ps (ax, _mm256_set1_ps (0.5f), _CMP_GT_OS));
  f = _mm256_blendv_ps (f, _mm256_sub_ps (_mm256_set1_ps (M_PI_2f), f), m);
  z = _mm256_setzero_ps ();
  return _mm256_blendv_ps (f, _mm256_sub_ps (z, f),
                           _mm256_cmp_ps (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_8xf32
 * function (__m256).
 *
 * \return function value (in [-pi,pi]) (__m256).
 */
static inline __m256
jbm_atan2_8xf32 (const __m256 y,        ///< __m256 y component.
                 const __m256 x)        ///< __m256 x component.
{
  __m256 f, mx, my, z, pi;
  z = _mm256_setzero_ps ();
  pi = _mm256_set1_ps (M_PIf);
  f = jbm_atan_8xf32 (_mm256_div_ps (y, x));
  mx = _mm256_cmp_ps (x, z, _CMP_LT_OS);
  my = _mm256_cmp_ps (y, z, _CMP_LT_OS);
  f = _mm256_blendv_ps (f, _mm256_sub_ps (f, pi), _mm256_and_ps (my, mx));
  return _mm256_blendv_ps (f, _mm256_add_ps (f, pi), _mm256_andnot_ps (my, mx));
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_8xf32 function
 * (__m256).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline __m256
jbm_asin_8xf32 (const __m256 x) ///< __m256 vector.
{
  return
    jbm_atan_8xf32 (_mm256_div_ps
                    (x,
                     _mm256_sqrt_ps (_mm256_fnmadd_ps
                                     (x, x, _mm256_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_8xf32 function
 * (__m256).
 *
 * \return function value (in [0,pi]) (__m256).
 */
static inline __m256
jbm_acos_8xf32 (const __m256 x) ///< __m256 vector.
{
  __m256 f;
  f =
    jbm_atan_8xf32 (_mm256_div_ps
                    (_mm256_sqrt_ps
                     (_mm256_fnmadd_ps (x, x, _mm256_set1_ps (1.f))), x));
  return _mm256_blendv_ps (f, _mm256_add_ps (f, _mm256_set1_ps (M_PIf)),
                           _mm256_cmp_ps (x, _mm256_setzero_ps (), _CMP_LT_OS));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_sinh_8xf32 (const __m256 x) ///< __m256 number.
{
  __m256 f;
  f = jbm_exp_8xf32 (x);
  return _mm256_mul_ps (_mm256_set1_ps (0.5f),
                        _mm256_sub_ps (f, jbm_reciprocal_8xf32 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_cosh_8xf32 (const __m256 x) ///< __m256 number.
{
  __m256 f;
  f = jbm_exp_8xf32 (x);
  return _mm256_mul_ps (_mm256_set1_ps (0.5f),
                        _mm256_add_ps (f, jbm_reciprocal_8xf32 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_tanh_8xf32 (const __m256 x) ///< __m256 number.
{
  __m256 f, fi;
  f = jbm_exp_8xf32 (x);
  fi = jbm_reciprocal_8xf32 (f);
  f = _mm256_div_ps (_mm256_sub_ps (f, fi), _mm256_add_ps (f, fi));
  f = _mm256_blendv_ps (f, _mm256_set1_ps (1.f),
                        _mm256_cmp_ps (x, _mm256_set1_ps (JBM_FLT_MAX_E_EXP),
                                       _CMP_GT_OS));
  return
    _mm256_blendv_ps (f, _mm256_set1_ps (-1.f),
                      _mm256_cmp_ps (x, _mm256_set1_ps (-JBM_FLT_MAX_E_EXP),
                                     _CMP_LT_OS));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_asinh_8xf32 (const __m256 x)        ///< __m256 number.
{
  return
    jbm_log_8xf32 (_mm256_add_ps
                   (x,
                    _mm256_sqrt_ps (_mm256_fmadd_ps
                                    (x, x, _mm256_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_acosh_8xf32 (const __m256 x)        ///< __m256 number.
{
  return
    jbm_log_8xf32 (_mm256_add_ps
                   (x,
                    _mm256_sqrt_ps (_mm256_fmsub_ps
                                    (x, x, _mm256_set1_ps (1.f)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_atanh_8xf32 (const __m256 x)        ///< __m256 number.
{
  __m256 u;
  u = _mm256_set1_ps (1.f);
  return _mm256_mul_ps (_mm256_set1_ps (0.5f),
                        jbm_log_8xf32 (_mm256_div_ps (_mm256_add_ps (u, x),
                                                      _mm256_sub_ps (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m256)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_erfwc_8xf32 (const __m256 x)
                 ///< __m256 vector \f$\in\left[-1,1\right]\f$.
{
  const float a[6] JB_ALIGNED = {
    1.1283791671633124547603970137089329e+00f,
    1.1356247077387072221530473806173895e-01f,
    3.3606359392673594485175487779855494e-02f,
    4.3397545597876753616401102540952801e-01f,
    7.4441296041206635020857929305718177e-02f,
    5.2260592856163505486272407800095742e-03f
  };
  return _mm256_mul_ps (x, jbm_rational_5_2_8xf32 (jbm_sqr_8xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m256)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_erfcwc_8xf32 (const __m256 x)
                  ///< __m256 vector \f$\in\left[1,\infty\right]\f$.
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
  __m256 f, x2;
  x2 = jbm_sqr_8xf32 (x);
  f = _mm256_div_ps (jbm_rational_6_3_8xf32 (jbm_reciprocal_8xf32 (x2), a),
                     _mm256_mul_ps (x, jbm_exp_8xf32 (x2)));
  return _mm256_blendv_ps (f, _mm256_setzero_ps (),
                           _mm256_cmp_ps (x, _mm256_set1_ps (m), _CMP_GT_OS));
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_8xf32 and
 * jbm_erfcwc_8xf32
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_erf_8xf32 (const __m256 x)  ///< __m256 vector.
{
  __m256 ax, u, f;
  ax = jbm_abs_8xf32 (x);
  u = _mm256_set1_ps (1.f);
  f =
    _mm256_mul_ps (_mm256_div_ps (x, ax),
                   _mm256_sub_ps (u, jbm_erfcwc_8xf32 (ax)));
  return _mm256_blendv_ps (f, jbm_erfwc_8xf32 (x),
                           _mm256_cmp_ps (ax, u, _CMP_LT_OS));

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_8xf32 and
 * jbm_erfcwc_8xf32
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_erfc_8xf32 (const __m256 x) ///< __m256 vector.
{
  __m256 ax, u, f;
  ax = jbm_abs_8xf32 (x);
  u = _mm256_set1_ps (1.f);
  f = _mm256_sub_ps (u, _mm256_mul_ps (_mm256_div_ps (x, ax),
                                       _mm256_sub_ps (u,
                                                      jbm_erfcwc_8xf32 (ax))));
  return _mm256_blendv_ps (f, _mm256_sub_ps (u, jbm_erfwc_8xf32 (x)),
                           _mm256_cmp_ps (ax, u, _CMP_LT_OS));
}

/**
 * Function to calculate the solution of a __m256 vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m256 vector of solution values.
 */
static inline __m256
jbm_solve_quadratic_reduced_8xf32 (__m256 a,
///< __m256 vector of 1st order coefficient of the equations.
                                   __m256 b,
///< __m256 vector of 0th order coefficient of the equations.
                                   const __m256 x1,
///< __m256 vector of left limits of the solution intervals.
                                   const __m256 x2)
///< __m256 vector of right limits of the solution intervals.
{
  __m256 k1, k2;
  k1 = _mm256_set1_ps (-0.5f);
  a = _mm256_mul_ps (a, k1);
  b = _mm256_sqrt_ps (_mm256_sub_ps (jbm_sqr_8xf32 (a), b));
  k1 = _mm256_add_ps (a, b);
  k2 = _mm256_sub_ps (a, b);
  k1 = _mm256_blendv_ps (k1, k2, _mm256_cmp_ps (k1, x1, _CMP_LT_OS));
  return _mm256_blendv_ps (k1, k2, _mm256_cmp_ps (k1, x2, _CMP_GT_OS));
}

/**
 * Function to calculate the solution of a __m256 vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m256 vector of solution values.
 */
static inline __m256
jbm_solve_quadratic_8xf32 (const __m256 a,
///< __m256 vector of 2nd order coefficient of the equations.
                           const __m256 b,
///< __m256 vector of 1st order coefficient of the equations.
                           const __m256 c,
///< __m256 vector of 0th order coefficient of the equations.
                           const __m256 x1,
///< __m256 vector of left limits of the solution intervals.
                           const __m256 x2)
///< __m256 vector of right limits of the solution intervals.
{
  __m256 k1, k2;
  k1 =
    jbm_solve_quadratic_reduced_8xf32 (_mm256_div_ps (b, a),
                                       _mm256_div_ps (c, a), x1, x2);
  k2 = _mm256_div_ps (jbm_opposite_8xf32 (c), b);
  return _mm256_blendv_ps (k1, k2, jbm_small_8xf32 (a));
}

/**
 * Function to calculate the solution of a __m256 vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m256 vector of solution values.
 */
static inline __m256
jbm_solve_cubic_reduced_8xf32 (const __m256 a,
                               ///< 2nd order coefficient of the equation.
                               const __m256 b,
                               ///< 1st order coefficient of the equation.
                               const __m256 c,
                               ///< 0th order coefficient of the equation.
                               const __m256 x1,
                               ///< left limit of the solution interval.
                               const __m256 x2)
                               ///< right limit of the solution interval.
{
  __m256 a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm256_set1_ps (2.f * M_PIf / 3.f);
  c_2 = _mm256_set1_ps (0.5f);
  c_3 = _mm256_set1_ps (1.f / 3.f);
  a3 = _mm256_mul_ps (a, c_3);
  k0 = _mm256_mul_ps (a3, a3);
  k1 = _mm256_fmsub_ps (b, c_3, k0);
  k0 =
    _mm256_fmsub_ps (_mm256_fmsub_ps (b, a3, c), c_2, _mm256_mul_ps (a3, k0));
  k3 = _mm256_mul_ps (k1, _mm256_mul_ps (k1, k1));
  k2 = _mm256_fmadd_ps (k0, k0, k3);
  l1 = _mm256_sqrt_ps (jbm_opposite_8xf32 (k1));
  l0 = _mm256_mul_ps (jbm_acos_8xf32 (_mm256_div_ps (k0, k3)), c_3);
  l1 = _mm256_add_ps (l1, l1);
  l2 = _mm256_fmsub_ps (l1, jbm_cos_8xf32 (k0), a3);
  l3 = _mm256_fmsub_ps (l1, jbm_cos_8xf32 (_mm256_add_ps (l0, c2p_3)), a3);
  l3 = _mm256_blendv_ps (l3, l2,
                         _mm256_or_ps (_mm256_cmp_ps (l2, x1, _CMP_LT_OS),
                                       _mm256_cmp_ps (l2, x2, _CMP_GT_OS)));
  l4 = _mm256_fmsub_ps (l1, jbm_cos_8xf32 (_mm256_sub_ps (l0, c2p_3)), a);
  l4 = _mm256_blendv_ps (l4, l3,
                         _mm256_or_ps (_mm256_cmp_ps (l3, x1, _CMP_LT_OS),
                                       _mm256_cmp_ps (l3, x2, _CMP_GT_OS)));
  k1 = _mm256_sqrt_ps (k2);
  l5 = _mm256_add_ps (k0, k1);
  l5 = jbm_cbrt_8xf32 (k2);
  k0 = _mm256_sub_ps (k0, k1);
  l5 = _mm256_add_ps (l5, _mm256_sub_ps (jbm_cbrt_8xf32 (k0), a3));
  return _mm256_blendv_ps (l4, l5,
                           _mm256_cmp_ps (k2, _mm256_setzero_ps (),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the solution of a __m256 vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m256 vector of solution values.
 */
static inline __m256
jbm_solve_cubic_8xf32 (__m256 a,
///< __m256 vector of 3rd order coefficient of the equations.
                       __m256 b,
///< __m256 vector of 2nd order coefficient of the equations.
                       __m256 c,
///< __m256 vector of 1st order coefficient of the equations.
                       __m256 d,
///< __m256 vector of 0th order coefficient of the equations.
                       __m256 x1,
///< __m256 vector of left limits of the solution intervals.
                       __m256 x2)
///< __m256 vector of right limits of the solution intervals.
{
  return
    _mm256_blendv_ps (jbm_solve_cubic_reduced_8xf32 (_mm256_div_ps (b, a),
                                                     _mm256_div_ps (c, a),
                                                     _mm256_div_ps (d, a), x1,
                                                     x2),
                      jbm_solve_quadratic_8xf32 (b, c, d, x1, x2),
                      jbm_small_8xf32 (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_total_8xf32 (const __m256 d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m256 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm256_setzero_ps ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_null_8xf32 (const __m256 d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const __m256 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm256_set1_ps (1.f);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_centred_8xf32 (const __m256 d1,
                                ///< 1st flux limiter function parameter.
                                const __m256 d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm256_blendv_ps (_mm256_div_ps (d1, d2), _mm256_setzero_ps (),
                           jbm_small_8xf32 (d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_superbee_8xf32 (const __m256 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_div_ps (d1, d2);
  r = _mm256_max_ps (_mm256_min_ps (jbm_dbl_8xf32 (r), _mm256_set1_ps (1.f)),
                     _mm256_min_ps (r, _mm256_set1_ps (2.f)));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_minmod_8xf32 (const __m256 d1,
                               ///< 1st flux limiter function parameter.
                               const __m256 d2)
                             ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_min_ps (_mm256_div_ps (d1, d2), _mm256_set1_ps (1.f));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_VanLeer_8xf32 (const __m256 d1,
                                ///< 1st flux limiter function parameter.
                                const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r, k;
  r = _mm256_div_ps (d1, d2);
  k = jbm_abs_8xf32 (r);
  r =
    _mm256_div_ps (_mm256_add_ps (r, k),
                   _mm256_add_ps (_mm256_set1_ps (1.f), k));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_VanAlbada_8xf32 (const __m256 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r, k;
  r = _mm256_div_ps (d1, d2);
  k = jbm_sqr_8xf32 (r);
  r =
    _mm256_div_ps (_mm256_add_ps (r, k),
                   _mm256_add_ps (_mm256_set1_ps (1.f), k));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_minsuper_8xf32 (const __m256 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_min_ps (_mm256_div_ps (d1, d2), _mm256_set1_ps (2.f));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_supermin_8xf32 (const __m256 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_div_ps (d1, d2);
  r = _mm256_min_ps (jbm_dbl_8xf32 (r), _mm256_set1_ps (1.f));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_monotonized_central_8xf32 (const __m256 d1,
///< 1st flux limiter function parameter.
                                            const __m256 d2)
///< 2nd flux limiter function parameter.
{
  __m256 r, rm;
  r = _mm256_div_ps (d1, d2);
  rm =
    _mm256_mul_ps (_mm256_set1_ps (0.5f),
                   _mm256_add_ps (r, _mm256_set1_ps (1.f)));
  rm =
    _mm256_blendv_ps (_mm256_set1_ps (2.f), rm,
                      _mm256_cmp_ps (r, _mm256_set1_ps (3.f), _CMP_LT_OS));
  rm =
    _mm256_blendv_ps (rm, jbm_dbl_8xf32 (r),
                      _mm256_cmp_ps (r, _mm256_set1_ps (1.f / 3.f),
                                     _CMP_GT_OS));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_mean_8xf32 (const __m256 d1,
                             ///< 1st flux limiter function parameter.
                             const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_mul_ps (_mm256_set1_ps (0.5f),
                     _mm256_add_ps (_mm256_set1_ps (1.f),
                                    _mm256_div_ps (d1, d2)));
  return _mm256_blendv_ps (_mm256_setzero_ps (), r,
                           _mm256_cmp_ps (_mm256_mul_ps (d1, d2),
                                          _mm256_set1_ps (FLT_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to do a flux limiter function (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_flux_limiter_8xf32 (const __m256 d1,
                        ///< 1st flux limiter function parameter.
                        const __m256 d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_8xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_8xf32 (d1, d2);
    }
  return jbm_flux_limiter_mean_8xf32 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m256).
 *
 * \return __m256 vector of integral values.
 */
static inline __m256
jbm_integral_8xf32 (__m256 (*f) (__m256),
                    ///< pointer to the function to integrate.
                    const __m256 x1,    ///< left limit of the interval.
                    const __m256 x2)    ///< right limit of the interval.
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
  __m256 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m256 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm256_set1_ps (0.5f);
  dx = _mm256_mul_ps (h, _mm256_sub_ps (x2, x1));
  x = _mm256_mul_ps (h, _mm256_add_ps (x2, x1));
  k = _mm256_set1_ps (a[0]);
  k = _mm256_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm256_set1_ps (b[i]);
      k2 = _mm256_mul_ps (k2, dx);
      f1 = f (_mm256_sub_ps (x, k2));
      f2 = f (_mm256_add_ps (x, k2));
      h = _mm256_set1_ps (a[i]);
      k = _mm256_fmadd_ps (h, _mm256_add_ps (f1, f2), k);
    }
#endif
  k = _mm256_mul_ps (k, dx);
  return k;
}

/**
 * Function to calculate the additive inverse value of a __m256d vector.
 *
 * \return negative value vector (__m256d).
 */
static inline __m256d
jbm_opposite_4xf64 (const __m256d x)    ///< __m256d vector.
{
  JBM4xF64 y;
  y.i = _mm256_set1_epi64x (0x8000000000000000L);
  return _mm256_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m256d vector.
 *
 * \return reciprocal value vector (__m256d).
 */
static inline __m256d
jbm_reciprocal_4xf64 (const __m256d x)  ///< __m256 vector.
{
  return _mm256_div_pd (_mm256_set1_pd (1.), x);
}

/**
 * Function to calculate the absolute value of a __m256d vector.
 *
 * \return absolute value vector.
 */
static inline __m256d
jbm_abs_4xf64 (const __m256d x)
{
  JBM4xF64 y;
  y.i = _mm256_set1_epi64x (0x7fffffffffffffffL);
  return _mm256_and_pd (x, y.x);
}

/**
 * Function to calculate the hypot function (__m256d).
 *
 * \return function value vector (__m256d).
 */
static inline __m256d
jbm_hypot_4xf64 (const __m256d x,       ///< 1st __m256d vector.
                 const __m256d y)       ///< 2nd __m256d vector.
{
  return _mm256_sqrt_pd (_mm256_fmadd_pd (x, x, _mm256_mul_pd (y, y)));
}

/**
 * Function to calculate the rest of a division (__m256d).
 *
 * \return rest value (in [0,|divisor|) interval) (__m256d).
 */
static inline __m256d
jbm_rest_4xf64 (const __m256d x,        ///< dividend (__m256d).
                const __m256d d)        ///< divisor (__m256d).
{
  return _mm256_fnmadd_pd (_mm256_floor_pd (_mm256_div_pd (x, d)), d, x);
}

/**
 * Function to implement the standard frexp function (__m256d).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m256d
jbm_frexp_4xf64 (const __m256d x,       ///< __m256d vector.
                 __m256i *e)    ///< pointer to the extracted exponents vector.
{
  JBM4xF64 a, y, y2, z;
  __m256i e2, b, m1, m2, m3, zi;
  a.x = x;
  b = _mm256_set1_epi64x (0x7ff0000000000000L);
  y.i = _mm256_and_si256 (a.i, b);
  m1 = _mm256_cmpeq_epi64 (y.i, b);
  zi = _mm256_setzero_si256 ();
  m2 = _mm256_cmpeq_epi64 (y.i, zi);
  y2.x = x;
  y2.i = _mm256_and_si256 (y2.i, _mm256_set1_epi64x (0x000fffffffffffffL));
  m3 = _mm256_cmpeq_epi64 (y2.i, zi);
  y2.i = _mm256_set1_epi64x (0x0010000000000000L);
  z.x = _mm256_div_pd (x, y2.x);
  z.i = _mm256_and_si256 (z.i, b);
  e2 = _mm256_blendv_epi8 (_mm256_sub_epi64 (_mm256_srli_epi64 (y.i, 52),
                                             _mm256_set1_epi64x (1022L)),
                           _mm256_sub_epi64 (_mm256_srli_epi64 (z.i, 52),
                                             _mm256_set1_epi64x (2044L)), m2);
  y.x = _mm256_blendv_pd (y.x, _mm256_mul_pd (y2.x, z.x),
                          _mm256_castsi256_pd (m2));
  m1 = _mm256_or_si256 (m1, _mm256_and_si256 (m2, m3));
  e2 = _mm256_blendv_epi8 (e2, zi, m1);
  *e = e2;
  return _mm256_blendv_pd (_mm256_mul_pd (_mm256_set1_pd (0.5),
                                          _mm256_div_pd (x, y.x)), x,
                           _mm256_castsi256_pd (m1));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m256i)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_exp2n_4xf64 (__m256i e)     ///< exponent vector (__m256i).
{
  __m256d x;
  x = _mm256_blendv_pd
    (_mm256_castsi256_pd
     (_mm256_sllv_epi64
      (_mm256_set1_epi64x (0x0008000000000000L),
       _mm256_sub_epi64 (_mm256_set1_epi64x (-1023L), e))),
     _mm256_castsi256_pd
     (_mm256_slli_epi64 (_mm256_add_epi64 (e, _mm256_set1_epi64x (1023L)),
                         52)),
     _mm256_castsi256_pd (_mm256_cmpgt_epi64 (e, _mm256_set1_epi64x (-1023L))));
  x =
    _mm256_blendv_pd
    (x, _mm256_setzero_pd (),
     _mm256_castsi256_pd (_mm256_cmpgt_epi64 (_mm256_set1_epi64x (-1074L), e)));
  return
    _mm256_blendv_pd
    (x, _mm256_set1_pd (INFINITY),
     _mm256_castsi256_pd (_mm256_cmpgt_epi64 (e, _mm256_set1_epi64x (1023L))));
}

/**
 * Function to implement the standard ldexp function (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_ldexp_4xf64 (const __m256d x,       ///< __m256d vector.
                 __m256i e)     ///< exponent vector (__m256i).
{
  return _mm256_mul_pd (x, jbm_exp2n_4xf64 (e));
}

/**
 * Function to check small __m256d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m256d
jbm_small_4xf64 (const __m256d x)       ///< __m256d vector.
{
  return _mm256_cmp_pd (jbm_abs_4xf64 (x), _mm256_set1_pd (DBL_EPSILON),
                        _CMP_LT_OS);
}

/**
 * Function to calculate the __m256d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m256d vector.
 */
static inline __m256d
jbm_modmin_4xf64 (const __m256d a,      ///< 1st __m256d vector.
                  const __m256d b)      ///< 2nd __m256d vector.
{
  __m256d aa, ab, y, z;
  z = _mm256_setzero_pd ();
  ab = _mm256_mul_pd (a, b);
  y = _mm256_blendv_pd (a, z, _mm256_cmp_pd (z, ab, _CMP_GT_OS));
  aa = jbm_abs_4xf64 (y);
  ab = jbm_abs_4xf64 (b);
  return _mm256_blendv_pd (y, b, _mm256_cmp_pd (aa, ab, _CMP_GT_OS));
}

/**
 * Function to interchange 2 __m256d numbers.
 */
static inline void
jbm_change_4xf64 (__m256d *restrict a,  ///< 1st __m256d vector pointer.
                  __m256d *restrict b)  ///< 2nd __m256d vector pointer.
{
  __m256d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m256d vector.
 *
 * \return __m256d double.
 */
static inline __m256d
jbm_dbl_4xf64 (const __m256d x) ///< __m256d vector.
{
  return _mm256_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m256d vector.
 *
 * \return __m256d vector square.
 */
static inline __m256d
jbm_sqr_4xf64 (const __m256d x) ///< __m256d vector.
{
  return _mm256_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m256d vectors of 2D points.
 *
 * \return __m256d vector of y-coordinates of the extrapolated points.
 */
static inline __m256d
jbm_extrapolate_4xf64 (const __m256d x,
                       ///< __m256d vector of x-coordinates of the extrapolated
                       ///< points.
                       const __m256d x1,
                       ///< __m256d vector of x-coordinates of the 1st points.
                       const __m256d x2,
                       ///< __m256d vector of x-coordinates of the 2nd points.
                       const __m256d y1,
                       ///< __m256d vector of y-coordinates of the 1st points.
                       const __m256d y2)
    ///< __m256d vector of y-coordinates of the 2nd points.
{
  __m256d d;
  d = _mm256_sub_pd (x, x1);
  return _mm256_fmadd_pd (d, _mm256_div_pd (_mm256_sub_pd (y2, y1),
                                            _mm256_sub_pd (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m256d vectors of 2D points.
 *
 * \return __m256d vector of y-coordinates of the interpolated points.
 */
static inline __m256d
jbm_interpolate_4xf64 (const __m256d x,
                       ///< __m256d vector of x-coordinates of the interpolated
                       ///< points.
                       const __m256d x1,
                       ///< __m256d vector of x-coordinates of the 1st points.
                       const __m256d x2,
                       ///< __m256d vector of x-coordinates of the 2nd points.
                       const __m256d y1,
                       ///< __m256d vector of y-coordinates of the 1st points.
                       const __m256d y2)
    ///< __m256d vector of y-coordinates of the 2nd points.
{
  __m256d k;
  k = jbm_extrapolate_4xf64 (x, x1, x2, y1, y2);
  k = _mm256_blendv_pd (y1, k, _mm256_cmp_pd (x, x1, _CMP_GT_OS));
  return _mm256_blendv_pd (y2, k, _mm256_cmp_pd (x, x2, _CMP_LT_OS));
}

/**
 * Function to calculate the length of a __m256d vector of 2D segments.
 *
 * \return __m256d vector of segment lengths.
 */
static inline __m256d
jbm_v2_length_4xf64 (const __m256d x1,
///< __m256d vector of x-coordinates of the 1st points defining the segment.
                     const __m256d y1,
///< __m256d vector of y-coordinates of the 1st points defining the segment.
                     const __m256d x2,
///< __m256d vector of x-coordinates of the 2nd points defining the segment.
                     const __m256d y2)
///< __m256d vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_4xf64 (_mm256_sub_pd (x2, x1), _mm256_sub_pd (y2, y1));
}

/**
 * Function to calculate the length of a __m256d vector of 3D segments.
 *
 * \return __m256d vector of segment lengths.
 */
static inline __m256d
jbm_v3_length_4xf64 (const __m256d x1,
///< __m256d vector of x-coordinates of the 1st points defining the segments.
                     const __m256d y1,
///< __m256d vector of y-coordinates of the 1st points defining the segments.
                     const __m256d z1,
///< __m256d vector of z-coordinates of the 1st points defining the segments.
                     const __m256d x2,
///< __m256d vector of x-coordinates of the 2nd points defining the segments.
                     const __m256d y2,
///< __m256d vector of y-coordinates of the 2nd points defining the segments.
                     const __m256d z2)
///< __m256d vector of z-coordinates of the 2nd points defining the segments.
{
  __m256d dx, dy, dz;
  dx = jbm_sqr_4xf64 (_mm256_sub_pd (x2, x1));
  dy = _mm256_sub_pd (y2, y1);
  dy = _mm256_fmadd_pd (dy, dy, dx);
  dz = _mm256_sub_pd (z2, z1);
  return _mm256_sqrt_pd (_mm256_fmadd_pd (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, _mm256_set1_pd (p[1]), _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_4_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_5_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_6_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_7_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_8_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_9_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_10_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_11_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_12_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_13_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_14_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_15_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_16_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_17_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_18_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_19_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_20_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_21_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_22_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_23_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_24_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_25_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_24_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_26_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_25_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_27_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_26_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_28_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_27_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_29_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_28_4xf64 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_1_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[1]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_2_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+1st order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_2_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[2]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_3_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_3_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_3_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[3]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_4_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_4_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_4_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_4_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[4]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_5_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_5_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_5_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_5_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_5_4_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[5]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_6_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_6_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_6_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_6_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_6_4_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_6_5_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[6]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_4_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_5_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_7_6_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[7]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_4_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_5_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_6_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_8_7_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[8]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_0_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_1_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_2_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_3_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_4_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_5_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_6_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_7_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_9_8_4xf64 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[9]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_10_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[10]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_11_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[11]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_12_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[12]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_13_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[13]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_14_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[14]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_15_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[15]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_16_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[16]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_17_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[17]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_18_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[18]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_19_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[19]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_20_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[20]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_21_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[21]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_22_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[22]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_23_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[23]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_24_23_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_23_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[24]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_24_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_23_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_23_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_25_24_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_24_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[25]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_25_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_24_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_23_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_23_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_24_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_24_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_26_25_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_25_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[26]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_26_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_25_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_24_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_23_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_23_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_24_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_24_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_25_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_25_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 26),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_27_26_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_26_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[27]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+28th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_27_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_26_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_25_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_24_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_23_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_23_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_24_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_24_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_25_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_25_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 26),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_26_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_26_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 27),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_28_27_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_27_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[28]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+29th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_0_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_polynomial_28_4xf64 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_1_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_1_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_27_4xf64 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_2_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_2_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_26_4xf64 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_3_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_3_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_25_4xf64 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_4_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_4_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_24_4xf64 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_5_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_5_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_23_4xf64 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_6_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_6_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_22_4xf64 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_7_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_7_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_21_4xf64 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_8_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_8_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_20_4xf64 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_9_4xf64 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_9_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_19_4xf64 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_10_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_10_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_18_4xf64 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_11_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_11_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_17_4xf64 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_12_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_12_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_16_4xf64 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_13_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_13_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_15_4xf64 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_14_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_14_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_14_4xf64 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_15_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_15_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_13_4xf64 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_16_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_16_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_12_4xf64 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_17_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_17_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_11_4xf64 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_18_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_18_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_10_4xf64 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_19_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_19_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_9_4xf64 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_20_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_20_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_8_4xf64 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_21_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_21_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_7_4xf64 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_22_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_22_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_6_4xf64 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_23_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_23_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_5_4xf64 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_24_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_24_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_4_4xf64 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_25_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_25_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_3_4xf64 (x, p + 26),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_26_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_26_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_2_4xf64 (x, p + 27),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_27_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_27_4xf64 (x, p),
                        _mm256_fmadd_pd (x, jbm_polynomial_1_4xf64 (x, p + 28),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_rational_29_28_4xf64 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_polynomial_28_4xf64 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[29]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_expm1wc_4xf64 (const __m256d x)
///< __m256d vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const double a1 = 9.9999999999999999866523626874215789e-01;
  const double a3 = 2.4998453858981619674396608301250598e-02;
  const double a4 = -4.9999999999999999933261730198779978e-01;
  const double a5 = 1.0833178719231388723914535942973379e-01;
  const double a6 = -1.2499226929490809837198234785821115e-02;
  const double a7 = 6.9431559947707471609539363612700440e-04;
  const double a9 = -1.6512957626515476078093301716091145e-06;
  __m256d x2;
  x2 = jbm_sqr_4xf64 (x);
  return
    _mm256_div_pd (_mm256_mul_pd (x, _mm256_fmadd_pd (x2, _mm256_set1_pd (a3),
                                                      _mm256_set1_pd (a1))),
                   _mm256_fmadd_pd
                   (x,
                    _mm256_fmadd_pd
                    (x,
                     _mm256_fmadd_pd
                     (x,
                      _mm256_fmadd_pd
                      (x,
                       _mm256_fmadd_pd
                       (x2,
                        _mm256_set1_pd (a9), _mm256_set1_pd (a7)),
                       _mm256_set1_pd (a6)),
                      _mm256_set1_pd (a5)), _mm256_set1_pd (a4)),
                    _mm256_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m256d).
 *
 * \return function value.
 */
static inline __m256d
jbm_exp2wc_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in[\frac12,1]\f$.
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
  return jbm_rational_10_5_4xf64 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_4xf64 and
 * jbm_exp2n_4xf64 functions.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_exp2_4xf64 (const __m256d x)        ///< __m256d vector.
{
  __m256d y, f, z;
  __m256i i;
  y = _mm256_floor_pd (x);
  f = _mm256_sub_pd (x, y);
#ifdef __AVX512F__
  i = _mm256_cvtpd_epi64 (y);
  z = jbm_exp2n_4xf64 (i);
#else
  z = _mm256_set1_pd (0x0018000000000000);
  y = _mm256_add_pd (y, z);
  i = _mm256_sub_epi64 (_mm256_castpd_si256 (y), _mm256_castpd_si256 (z));
  z = _mm256_blendv_pd (jbm_exp2n_4xf64 (i), _mm256_setzero_pd (),
                        _mm256_cmp_pd (y, _mm256_set1_pd (-1074.), _CMP_LT_OS));
#endif
  return _mm256_mul_pd (z, jbm_exp2wc_4xf64 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_4xf64 function.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_exp_4xf64 (const __m256d x) ///< __m256d vector.
{
  return jbm_exp2_4xf64 (_mm256_mul_pd (x, _mm256_set1_pd (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_4xf64
 * function (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_exp10_4xf64 (const __m256d x)       ///< __m256d vector.
{
  return jbm_exp2_4xf64 (_mm256_mul_pd (x, _mm256_set1_pd (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_4xf64 and
 * jbm_exp_4xf64 functions (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_expm1_4xf64 (const __m256d x)       ///< __m256d vector.
{
  return
    _mm256_blendv_pd (_mm256_sub_pd (jbm_exp_4xf64 (x), _mm256_set1_pd (1.)),
                      jbm_expm1wc_4xf64 (x),
                      _mm256_cmp_pd (jbm_abs_4xf64 (x),
                                     _mm256_set1_pd (M_LN2 / 2.), _CMP_LT_OS));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_log2wc_4xf64 (const __m256d x)      ///< __m256d vector \f$\in[0.5,1]\f$.
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
  return jbm_rational_14_7_4xf64 (x, a);
}

/**
 * Function to calculate the function log_2(x) using jbm_logwc_4xf64 and
 * jbm_frexp_4xf64
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_log2_4xf64 (const __m256d x)        ///< __m256d vector.
{
  __m256d y, z;
  __m256i e;
  y = jbm_log2wc_4xf64 (jbm_frexp_4xf64 (x, &e));
#ifdef __AVX512F__
  z = _mm256_cvtepi64_pd (e);
#else
  z = _mm256_set1_pd (0x0018000000000000);
  e = _mm256_add_epi64 (e, _mm256_castpd_si256 (z));
  z = _mm256_sub_pd (_mm256_castsi256_pd (e), z);
#endif
  y = _mm256_add_pd (y, z);
  z = _mm256_setzero_pd ();
  y = _mm256_blendv_pd (y, _mm256_set1_pd (-INFINITY),
                        _mm256_cmp_pd (x, z, _CMP_GT_OS));
  return _mm256_blendv_pd (_mm256_set1_pd (NAN), y,
                           _mm256_cmp_pd (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the function log(x) using jbm_log2_4xf64 (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_log_4xf64 (const __m256d x) ///< __m256d vector.
{
  return _mm256_mul_pd (jbm_log2_4xf64 (x), _mm256_set1_pd (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_4xf64 (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_log10_4xf64 (const __m256d x)       ///< __m256d vector.
{
  return _mm256_mul_pd (jbm_log2_4xf64 (x), _mm256_set1_pd (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (__m256d).
 *
 * \return function value (__m256d) (__m256d).
 */
static inline __m256d
jbm_pown_4xf64 (const __m256d x,        ///< __m256d vector.
                const int e)    ///< exponent (int).
{
  __m256d f, xn;
  unsigned int i;
  f = _mm256_set1_pd (1.);
  if (e < 0)
    xn = _mm256_div_pd (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_4xf64 (xn))
    if (i & 1)
      f = _mm256_mul_pd (f, xn);
  return f;
}

/**
 * Function to calculate the function f32 using the jbm_exp2_4xf64 and
 * jbm_log2_4xf64 functions.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_pow_4xf64 (const __m256d x, ///< __m256d vector.
               const double e)  ///< exponent (__m256d).
{
  double f;
  f = floor (e);
  if (f == e)
    return jbm_pown_4xf64 (x, (int) e);
  return
    jbm_exp2_4xf64 (_mm256_mul_pd (_mm256_set1_pd (e), jbm_log2_4xf64 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_4xf64 and
 * jbm_pow_4xf64 functions (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_cbrt_4xf64 (const __m256d x)        ///< __m256d vector.
{
  __m256d f, z;
  f = jbm_pow_4xf64 (jbm_abs_4xf64 (x), 1. / 3.);
  z = _mm256_setzero_pd ();
  return _mm256_blendv_pd (f, _mm256_sub_pd (z, f),
                           _mm256_cmp_pd (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m256d)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_sinwc_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
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
  return _mm256_mul_pd (x, jbm_polynomial_6_4xf64 (jbm_sqr_4xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_coswc_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
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
  return jbm_polynomial_7_4xf64 (jbm_sqr_4xf64 (x), a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_4xf64 approximation (__m256d).
 */
static inline void
jbm_sincoswc_4xf64 (const __m256d x,
                    ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m256d *s,
                    ///< pointer to the f32 function value (__m256d).
                    __m256d *c)
    ///< pointer to the f32 function value (__m256d).
{
  __m256d s0;
  *s = s0 = jbm_sinwc_4xf64 (x);
  *c = _mm256_sqrt_pd (_mm256_fnmadd_pd (x, x, _mm256_set1_pd (1.)));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_4xf64 and
 * jbm_coswc_4xf64 approximations.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_sin_4xf64 (const __m256d x) ///< __m256d vector.
{
  __m256d y, s, pi2;
  pi2 = _mm256_set1_pd (2. * M_PI);
  y = jbm_rest_4xf64 (x, pi2);
  s = jbm_sinwc_4xf64 (_mm256_sub_pd (y, pi2));
  s = _mm256_blendv_pd (s,
                        jbm_opposite_4xf64
                        (jbm_coswc_4xf64
                         (_mm256_sub_pd (_mm256_set1_pd (3. * M_PI_2), y))),
                        _mm256_cmp_pd (y, _mm256_set1_pd (7. * M_PI_4),
                                       _CMP_LT_OS));
  s =
    _mm256_blendv_pd (s,
                      jbm_sinwc_4xf64 (_mm256_sub_pd
                                       (_mm256_set1_pd (M_PI), y)),
                      _mm256_cmp_pd (y, _mm256_set1_pd (5. * M_PI_4),
                                     _CMP_LT_OS));
  s =
    _mm256_blendv_pd (s,
                      jbm_coswc_4xf64 (_mm256_sub_pd
                                       (_mm256_set1_pd (M_PI_2), y)),
                      _mm256_cmp_pd (y, _mm256_set1_pd (3. * M_PI_4),
                                     _CMP_LT_OS));
  return _mm256_blendv_pd (s, jbm_sinwc_4xf64 (y),
                           _mm256_cmp_pd (y, _mm256_set1_pd (M_PI_4),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_4xf64 and
 * jbm_coswc_4xf64 approximations (__m256).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_cos_4xf64 (const __m256d x) ///< __m256d vector.
{
  __m256d y, c, pi2;
  pi2 = _mm256_set1_pd (2. * M_PI);
  y = jbm_rest_4xf64 (x, pi2);
  c = jbm_coswc_4xf64 (_mm256_sub_pd (y, pi2));
  c = _mm256_blendv_pd (c,
                        jbm_sinwc_4xf64
                        (_mm256_sub_pd (y, _mm256_set1_pd (3. * M_PI_2))),
                        _mm256_cmp_pd (y, _mm256_set1_pd (7. * M_PI_4),
                                       _CMP_LT_OS));
  c = _mm256_blendv_pd (c,
                        jbm_opposite_4xf64
                        (jbm_coswc_4xf64
                         (_mm256_sub_pd (_mm256_set1_pd (M_PI), y))),
                        _mm256_cmp_pd (y, _mm256_set1_pd (5. * M_PI_4),
                                       _CMP_LT_OS));
  c =
    _mm256_blendv_pd (c,
                      jbm_sinwc_4xf64 (_mm256_sub_pd
                                       (_mm256_set1_pd (M_PI_2), y)),
                      _mm256_cmp_pd (y, _mm256_set1_pd (3. * M_PI_4),
                                     _CMP_LT_OS));
  return _mm256_blendv_pd (c, jbm_coswc_4xf64 (y),
                           _mm256_cmp_pd (y, _mm256_set1_pd (M_PI_4),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sinwc_4xf64
 * and jbm_coswc_4xf64 approximations (__m256d).
 */
static inline void
jbm_sincos_4xf64 (const __m256d x,
                  ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m256d *s,   ///< pointer to the f32 function value (__m256d).
                  __m256d *c)   ///< pointer to the f32 function value (__m256d).
{
  __m256d y, pi2, z, m, s1, c1, s2, c2;
  pi2 = _mm256_set1_pd (2. * M_PI);
  y = jbm_rest_4xf64 (x, pi2);
  jbm_sincoswc_4xf64 (_mm256_sub_pd (y, pi2), &s1, &c1);
  jbm_sincoswc_4xf64 (_mm256_sub_pd (y, _mm256_set1_pd (3. * M_PI_2)), &c2,
                      &s2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (7. * M_PI_4), _CMP_LT_OS);
  z = _mm256_setzero_pd ();
  s1 = _mm256_blendv_pd (s1, _mm256_sub_pd (z, s2), m);
  c1 = _mm256_blendv_pd (c1, c2, m);
  jbm_sincoswc_4xf64 (_mm256_sub_pd (_mm256_set1_pd (M_PI), y), &s2, &c2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (5. * M_PI_4), _CMP_LT_OS);
  s1 = _mm256_blendv_pd (s1, s2, m);
  c1 = _mm256_blendv_pd (c1, _mm256_sub_pd (z, c2), m);
  jbm_sincoswc_4xf64 (_mm256_sub_pd (_mm256_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (3. * M_PI_4), _CMP_LT_OS);
  s1 = _mm256_blendv_pd (s1, s2, m);
  c1 = _mm256_blendv_pd (c1, c2, m);
  jbm_sincoswc_4xf64 (y, &s2, &c2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (M_PI_4), _CMP_LT_OS);
  *s = _mm256_blendv_pd (s1, s2, m);
  *c = _mm256_blendv_pd (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_sinwc_4xf64 and
 * jbm_coswc_4xf64 approximations.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_tan_4xf64 (const __m256d x) ///< __m256d vector.
{
  __m256d s, c;
  jbm_sincos_4xf64 (x, &s, &c);
  return _mm256_div_pd (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_atanwc0_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in\left[0,\frac12\right]\f$.
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
  return _mm256_mul_pd (x, jbm_rational_9_4_4xf64 (jbm_sqr_4xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_atanwc1_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in\left[\frac12,1\right]\f$.
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
  return jbm_rational_16_8_4xf64 (_mm256_sub_pd (x, _mm256_set1_pd (1.)), a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_4xf64 and
 * jbm_atanwc1_4xf64 functions (__m256d).
 *
 * \return function value (__m256d in [-pi/2,pi/2]).
 */
static inline __m256d
jbm_atan_4xf64 (const __m256d x)        ///< double number.
{
  __m256d f, ax, m, z;
  ax = jbm_abs_4xf64 (x);
  m = _mm256_cmp_pd (ax, _mm256_set1_pd (1.5), _CMP_GT_OS);
  ax = _mm256_blendv_pd (ax, jbm_reciprocal_4xf64 (ax), m);
  f = _mm256_blendv_pd (jbm_atanwc0_4xf64 (ax), jbm_atanwc1_4xf64 (ax),
                        _mm256_cmp_pd (ax, _mm256_set1_pd (0.5), _CMP_GT_OS));
  f = _mm256_blendv_pd (f, _mm256_sub_pd (_mm256_set1_pd (M_PI_2), f), m);
  z = _mm256_setzero_pd ();
  return _mm256_blendv_pd (f, _mm256_sub_pd (z, f),
                           _mm256_cmp_pd (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_4xf64
 * function (__m256d).
 *
 * \return function value (__m256d in [-pi,pi]).
 */
static inline __m256d
jbm_atan2_4xf64 (const __m256d y,       ///< __m256d y component.
                 const __m256d x)       ///< __m256d x component.
{
  __m256d f, mx, my, z, pi;
  z = _mm256_setzero_pd ();
  pi = _mm256_set1_pd (M_PI);
  f = jbm_atan_4xf64 (_mm256_div_pd (y, x));
  mx = _mm256_cmp_pd (x, z, _CMP_LT_OS);
  my = _mm256_cmp_pd (y, z, _CMP_LT_OS);
  f = _mm256_blendv_pd (f, _mm256_sub_pd (f, pi), _mm256_and_pd (my, mx));
  return _mm256_blendv_pd (f, _mm256_add_pd (f, pi), _mm256_andnot_pd (my, mx));
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_4xf64 function
 * (__m256d).
 *
 * \return function value (__m256d in [-pi/2,pi/2]).
 */
static inline __m256d
jbm_asin_4xf64 (const __m256d x)        ///< __m256d number.
{
  return
    jbm_atan_4xf64 (_mm256_div_pd
                    (x,
                     _mm256_sqrt_pd (_mm256_fnmadd_pd
                                     (x, x, _mm256_set1_pd (1.)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_4xf64 function
 * (__m256d).
 *
 * \return function value (__m256d in [0,pi]).
 */
static inline __m256d
jbm_acos_4xf64 (const __m256d x)        ///< __m256d number.
{
  __m256d f;
  f =
    jbm_atan_4xf64 (_mm256_div_pd
                    (_mm256_sqrt_pd
                     (_mm256_fnmadd_pd (x, x, _mm256_set1_pd (1.))), x));
  return _mm256_blendv_pd (f, _mm256_add_pd (f, _mm256_set1_pd (M_PI)),
                           _mm256_cmp_pd (x, _mm256_setzero_pd (), _CMP_LT_OS));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_sinh_4xf64 (const __m256d x)        ///< __m256d number.
{
  __m256d f;
  f = jbm_exp_4xf64 (x);
  return _mm256_mul_pd (_mm256_set1_pd (0.5),
                        _mm256_sub_pd (f, jbm_reciprocal_4xf64 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_cosh_4xf64 (const __m256d x)        ///< __m256d number.
{
  __m256d f;
  f = jbm_exp_4xf64 (x);
  return _mm256_mul_pd (_mm256_set1_pd (0.5),
                        _mm256_add_pd (f, jbm_reciprocal_4xf64 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_tanh_4xf64 (const __m256d x)        ///< __m256d number.
{
  __m256d f, fi;
  f = jbm_exp_4xf64 (x);
  fi = jbm_reciprocal_4xf64 (f);
  f = _mm256_div_pd (_mm256_sub_pd (f, fi), _mm256_add_pd (f, fi));
  f = _mm256_blendv_pd (f, _mm256_set1_pd (1.),
                        _mm256_cmp_pd (x, _mm256_set1_pd (JBM_DBL_MAX_E_EXP),
                                       _CMP_GT_OS));
  return _mm256_blendv_pd (f, _mm256_set1_pd (-1.),
                           _mm256_cmp_pd (x,
                                          _mm256_set1_pd (-JBM_DBL_MAX_E_EXP),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_asinh_4xf64 (const __m256d x)       ///< __m256d number.
{
  return
    jbm_log_4xf64 (_mm256_add_pd
                   (x,
                    _mm256_sqrt_pd (_mm256_fmadd_pd
                                    (x, x, _mm256_set1_pd (1.)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_acosh_4xf64 (const __m256d x)       ///< __m256d number.
{
  return
    jbm_log_4xf64 (_mm256_add_pd
                   (x,
                    _mm256_sqrt_pd (_mm256_fmsub_pd
                                    (x, x, _mm256_set1_pd (1.)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_atanh_4xf64 (const __m256d x)       ///< __m256d number.
{
  __m256d u;
  u = _mm256_set1_pd (1.);
  return _mm256_mul_pd (_mm256_set1_pd (0.5),
                        jbm_log_4xf64 (_mm256_div_pd (_mm256_add_pd (u, x),
                                                      _mm256_sub_pd (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m256d)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_erfwc_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in\left[-1,1\right]\f$.
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
  return _mm256_mul_pd (x, jbm_rational_9_4_4xf64 (jbm_sqr_4xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m256d)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_erfcwc_4xf64 (const __m256d x)
    ///< __m256d vector \f$\in\left[1,\infty\right]\f$.
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
  __m256d f, x2;
  x2 = jbm_sqr_4xf64 (x);
  f = _mm256_div_pd (jbm_rational_19_9_4xf64 (jbm_reciprocal_4xf64 (x2), a),
                     _mm256_mul_pd (x, jbm_exp_4xf64 (x2)));
  return _mm256_blendv_pd (f, _mm256_setzero_pd (),
                           _mm256_cmp_pd (x, _mm256_set1_pd (m), _CMP_GT_OS));
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_4xf64 and
 * jbm_erfcwc_4xf64
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_erf_4xf64 (const __m256d x) ///< __m256d vector.
{
  __m256d ax, u, f;
  ax = jbm_abs_4xf64 (x);
  u = _mm256_set1_pd (1.);
  f =
    _mm256_mul_pd (_mm256_div_pd (x, ax),
                   _mm256_sub_pd (u, jbm_erfcwc_4xf64 (ax)));
  return _mm256_blendv_pd (f, jbm_erfwc_4xf64 (x),
                           _mm256_cmp_pd (ax, u, _CMP_LT_OS));

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_4xf64 and
 * jbm_erfcwc_4xf64
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_erfc_4xf64 (const __m256d x)        ///< __m256d vector.
{
  __m256d ax, u, f;
  ax = jbm_abs_4xf64 (x);
  u = _mm256_set1_pd (1.);
  f = _mm256_sub_pd (u, _mm256_mul_pd (_mm256_div_pd (x, ax),
                                       _mm256_sub_pd (u,
                                                      jbm_erfcwc_4xf64 (ax))));
  return _mm256_blendv_pd (f, _mm256_sub_pd (u, jbm_erfwc_4xf64 (x)),
                           _mm256_cmp_pd (ax, u, _CMP_LT_OS));
}

/**
 * Function to calculate the solution of a __m256d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_quadratic_reduced_4xf64 (__m256d a,
///< __m256d vector of 1st order coefficient of the equations.
                                   __m256d b,
///< __m256d vector of 0th order coefficient of the equations.
                                   const __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                                   const __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  __m256d k1, k2;
  k1 = _mm256_set1_pd (-0.5);
  a = _mm256_mul_pd (a, k1);
  b = _mm256_sqrt_pd (_mm256_sub_pd (jbm_sqr_4xf64 (a), b));
  k1 = _mm256_add_pd (a, b);
  k2 = _mm256_sub_pd (a, b);
  k1 = _mm256_blendv_pd (k1, k2, _mm256_cmp_pd (k1, x1, _CMP_LT_OS));
  return _mm256_blendv_pd (k1, k2, _mm256_cmp_pd (k1, x2, _CMP_GT_OS));
}

/**
 * Function to calculate the solution of a __m256d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_quadratic_4xf64 (const __m256d a,
///< __m256d vector of 2nd order coefficient of the equations.
                           const __m256d b,
///< __m256d vector of 1st order coefficient of the equations.
                           const __m256d c,
///< __m256d vector of 0th order coefficient of the equations.
                           const __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                           const __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  __m256d k1, k2;
  k1 = jbm_solve_quadratic_reduced_4xf64 (_mm256_div_pd (b, a),
                                          _mm256_div_pd (c, a), x1, x2);
  k2 = _mm256_div_pd (jbm_opposite_4xf64 (c), b);
  return _mm256_blendv_pd (k1, k2, jbm_small_4xf64 (a));
}

/**
 * Function to calculate the solution of a __m256d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_cubic_reduced_4xf64 (const __m256d a,
                               ///< 2nd order coefficient of the equation.
                               const __m256d b,
                               ///< 1st order coefficient of the equation.
                               const __m256d c,
                               ///< 0th order coefficient of the equation.
                               const __m256d x1,
                               ///< left limit of the solution interval.
                               const __m256d x2)
    ///< right limit of the solution interval.
{
  __m256d a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm256_set1_pd (2. * M_PI / 3.);
  c_2 = _mm256_set1_pd (0.5);
  c_3 = _mm256_set1_pd (1. / 3.);
  a3 = _mm256_mul_pd (a, c_3);
  k0 = _mm256_mul_pd (a3, a3);
  k1 = _mm256_fmsub_pd (b, c_3, k0);
  k0 =
    _mm256_fmsub_pd (_mm256_fmsub_pd (b, a3, c), c_2, _mm256_mul_pd (a3, k0));
  k3 = _mm256_mul_pd (k1, _mm256_mul_pd (k1, k1));
  k2 = _mm256_fmadd_pd (k0, k0, k3);
  l1 = _mm256_sqrt_pd (jbm_opposite_4xf64 (k1));
  l0 = _mm256_mul_pd (jbm_acos_4xf64 (_mm256_div_pd (k0, k3)), c_3);
  l1 = _mm256_add_pd (l1, l1);
  l2 = _mm256_fmsub_pd (l1, jbm_cos_4xf64 (k0), a3);
  l3 = _mm256_fmsub_pd (l1, jbm_cos_4xf64 (_mm256_add_pd (l0, c2p_3)), a3);
  l3 = _mm256_blendv_pd (l3, l2,
                         _mm256_or_pd (_mm256_cmp_pd (l2, x1, _CMP_LT_OS),
                                       _mm256_cmp_pd (l2, x2, _CMP_GT_OS)));
  l4 = _mm256_fmsub_pd (l1, jbm_cos_4xf64 (_mm256_sub_pd (l0, c2p_3)), a);
  l4 = _mm256_blendv_pd (l4, l3,
                         _mm256_or_pd (_mm256_cmp_pd (l3, x1, _CMP_LT_OS),
                                       _mm256_cmp_pd (l3, x2, _CMP_GT_OS)));
  k1 = _mm256_sqrt_pd (k2);
  l5 = _mm256_add_pd (k0, k1);
  l5 = jbm_cbrt_4xf64 (k2);
  k0 = _mm256_sub_pd (k0, k1);
  l5 = _mm256_add_pd (l5, _mm256_sub_pd (jbm_cbrt_4xf64 (k0), a3));
  return _mm256_blendv_pd (l4, l5,
                           _mm256_cmp_pd (k2, _mm256_setzero_pd (),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the solution of a __m256d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_cubic_4xf64 (__m256d a,
///< __m256d vector of 3rd order coefficient of the equations.
                       __m256d b,
///< __m256d vector of 2nd order coefficient of the equations.
                       __m256d c,
///< __m256d vector of 1st order coefficient of the equations.
                       __m256d d,
///< __m256d vector of 0th order coefficient of the equations.
                       __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                       __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  return
    _mm256_blendv_pd (jbm_solve_cubic_reduced_4xf64 (_mm256_div_pd (b, a),
                                                     _mm256_div_pd (c, a),
                                                     _mm256_div_pd (d, a), x1,
                                                     x2),
                      jbm_solve_quadratic_4xf64 (b, c, d, x1, x2),
                      jbm_small_4xf64 (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_total_4xf64 (const __m256d d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m256d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm256_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_null_4xf64 (const __m256d d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const __m256d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm256_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_centred_4xf64 (const __m256d d1,
                                ///< 1st flux limiter function parameter.
                                const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  return _mm256_blendv_pd (_mm256_div_pd (d1, d2), _mm256_setzero_pd (),
                           jbm_small_4xf64 (d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_superbee_4xf64 (const __m256d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_div_pd (d1, d2);
  r = _mm256_max_pd (_mm256_min_pd (jbm_dbl_4xf64 (r), _mm256_set1_pd (1.)),
                     _mm256_min_pd (r, _mm256_set1_pd (2.)));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_minmod_4xf64 (const __m256d d1,
                               ///< 1st flux limiter function parameter.
                               const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_min_pd (_mm256_div_pd (d1, d2), _mm256_set1_pd (1.));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_VanLeer_4xf64 (const __m256d d1,
                                ///< 1st flux limiter function parameter.
                                const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r, k;
  r = _mm256_div_pd (d1, d2);
  k = jbm_abs_4xf64 (r);
  r = _mm256_div_pd (_mm256_add_pd (r, k),
                     _mm256_add_pd (_mm256_set1_pd (1.), k));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_VanAlbada_4xf64 (const __m256d d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r, k;
  r = _mm256_div_pd (d1, d2);
  k = jbm_sqr_4xf64 (r);
  r = _mm256_div_pd (_mm256_add_pd (r, k),
                     _mm256_add_pd (_mm256_set1_pd (1.), k));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_minsuper_4xf64 (const __m256d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_min_pd (_mm256_div_pd (d1, d2), _mm256_set1_pd (2.));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_supermin_4xf64 (const __m256d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_div_pd (d1, d2);
  r = _mm256_min_pd (jbm_dbl_4xf64 (r), _mm256_set1_pd (1.));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_monotonized_central_4xf64 (const __m256d d1,
///< 1st flux limiter function parameter.
                                            const __m256d d2)
///< 2nd flux limiter function parameter.
{
  __m256d r, rm;
  r = _mm256_div_pd (d1, d2);
  rm =
    _mm256_mul_pd (_mm256_set1_pd (0.5),
                   _mm256_add_pd (r, _mm256_set1_pd (1.)));
  rm =
    _mm256_blendv_pd (_mm256_set1_pd (2.), rm,
                      _mm256_cmp_pd (r, _mm256_set1_pd (3.), _CMP_LT_OS));
  rm =
    _mm256_blendv_pd (rm, jbm_dbl_4xf64 (r),
                      _mm256_cmp_pd (r, _mm256_set1_pd (1. / 3.), _CMP_GT_OS));
  return _mm256_blendv_pd (_mm256_setzero_pd (), rm,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_mean_4xf64 (const __m256d d1,
                             ///< 1st flux limiter function parameter.
                             const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_mul_pd (_mm256_set1_pd (0.5),
                     _mm256_add_pd (_mm256_set1_pd (1.),
                                    _mm256_div_pd (d1, d2)));
  return _mm256_blendv_pd (_mm256_setzero_pd (), r,
                           _mm256_cmp_pd (_mm256_mul_pd (d1, d2),
                                          _mm256_set1_pd (DBL_EPSILON),
                                          _CMP_GT_OS));
}

/**
 * Function to do a flux limiter function (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_4xf64 (const __m256d d1,
                        ///< 1st flux limiter function parameter.
                        const __m256d d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_4xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_4xf64 (d1, d2);
    }
  return jbm_flux_limiter_mean_4xf64 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m256d).
 *
 * \return __m256d vector of integral values.
 */
static inline __m256d
jbm_integral_4xf64 (__m256d (*f) (__m256d),
                    ///< pointer to the function to integrate.
                    const __m256d x1,   ///< left limit of the interval.
                    const __m256d x2)   ///< right limit of the interval.
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
  __m256d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m256d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm256_set1_pd (0.5);
  dx = _mm256_mul_pd (h, _mm256_sub_pd (x2, x1));
  x = _mm256_mul_pd (h, _mm256_add_pd (x2, x1));
  k = _mm256_set1_pd (a[0]);
  k = _mm256_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm256_set1_pd (b[i]);
      k2 = _mm256_mul_pd (k2, dx);
      f1 = f (_mm256_sub_pd (x, k2));
      f2 = f (_mm256_add_pd (x, k2));
      h = _mm256_set1_pd (a[i]);
      k = _mm256_fmadd_pd (h, _mm256_add_pd (f1, f2), k);
    }
#endif
  k = _mm256_mul_pd (k, dx);
  return k;
}

#endif
