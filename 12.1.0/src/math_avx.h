/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
 *
 * Copyright 2005-2026, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
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
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_AVX__H
#define JB_MATH_AVX__H 1

#include "math_f32.h"
#include "math_f64.h"

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

// float constants

#define JBM_BIAS_8xF32 _mm256_set1_epi32 (JBM_BIAS_F32)
///< bias for floats.
#define JBM_BITS_1_8xF32 _mm256_set1_epi32 (JBM_BITS_1_F32)
///< 1 bits for floats.
#define JBM_BITS_ABS_8xF32 _mm256_set1_epi32 (JBM_BITS_ABS_F32)
///< absolute value bits for floats.
#define JBM_BITS_EXPONENT_8xF32 _mm256_set1_epi32 (JBM_BITS_EXPONENT_F32)
///< exponent bits for floats.
#define JBM_BITS_MANTISSA_8xF32 _mm256_set1_epi32 (JBM_BITS_MANTISSA_F32)
///< mantissa bits for floats.
#define JBM_BITS_SIGN_8xF32 _mm256_set1_epi32 (JBM_BITS_SIGN_F32)
///< sign bits for floats.
#define JBM_CBRT2_8xF32 _mm256_set1_ps (JBM_CBRT2_F32)
///< cbrt(2) for floats.
#define JBM_CBRT4_8xF32 _mm256_set1_ps (JBM_CBRT4_F32)
///< cbrt(4) for floats.

// double constants

#define JBM_BIAS_4xF64 _mm256_set1_epi64x (JBM_BIAS_F64)
///< bias for doubles.
#define JBM_BITS_1_4xF64 _mm256_set1_epi64x (JBM_BITS_1_F64)
///< 1 bits for doubles.
#define JBM_BITS_ABS_4xF64 _mm256_set1_epi64x (JBM_BITS_ABS_F64)
///< absolute value bits for doubles.
#define JBM_BITS_EXPONENT_4xF64 _mm256_set1_epi64x (JBM_BITS_EXPONENT_F64)
///< exponent bits for doubles.
#define JBM_BITS_MANTISSA_4xF64 _mm256_set1_epi64x (JBM_BITS_MANTISSA_F64)
///< mantissa bits for doubles.
#define JBM_BITS_SIGN_4xF64 _mm256_set1_epi64x (JBM_BITS_SIGN_F64)
///< sign bits for doubles.
#define JBM_CBRT2_4xF64 _mm256_set1_pd (JBM_CBRT2_F64)
///< cbrt(2) for doubles.
#define JBM_CBRT4_4xF64 _mm256_set1_pd (JBM_CBRT4_F64)
///< cbrt(4) for doubles.

///> macro to define types for AVX
#define JBM_TYPE_256(type) JBM_SIMD_SELECT(type, __m256, __m256d)
///> macro to define loads for AVX
#define JBM_LOAD_256(type) JBM_SIMD_SELECT(type, _mm256_load_ps, _mm256_load_pd)

// Debug functions

static inline void
print_m256b32 (FILE *file, const char *label, __m256i x)
{
  int y[8] JB_ALIGNED;
  unsigned int i;
  _mm256_store_si256 ((__m256i *) y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m256b64 (FILE *file, const char *label, __m256i x)
{
  long long int y[4] JB_ALIGNED;
  unsigned int i;
  _mm256_store_si256 ((__m256i *) y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_m256i32 (FILE *file, const char *label, __m256i x)
{
  int y[8] JB_ALIGNED;
  unsigned int i;
  _mm256_store_si256 ((__m256i *) y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m256i64 (FILE *file, const char *label, __m256i x)
{
  long long int y[4] JB_ALIGNED;
  unsigned int i;
  _mm256_store_si256 ((__m256i *) y, x);
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

/**
 * Function to calculate the additive reduction value of a __m256 vector.
 *
 * \return additive reduction (float).
 */
static inline float
jbm_8xf32_reduce_add (const __m256 x)   ///< __m256 vector.
{
  __m128 h, l;
  h = _mm256_extractf128_ps (x, 1);
  l = _mm256_castps256_ps128 (x);
  return jbm_4xf32_reduce_add (_mm_add_ps (h, l));
}

/**
 * Function to calculate the maximum reduction value of a __m256 vector.
 *
 * \return maximum reduction (float).
 */
static inline float
jbm_8xf32_reduce_max (const __m256 x)  ///< __m256 vector.
{
  __m128 h, l;
  h = _mm256_extractf128_ps (x, 1);
  l = _mm256_castps256_ps128 (x);
  return jbm_4xf32_reduce_max (_mm_max_ps (h, l));
}

/**
 * Function to calculate the minimum reduction value of a __m256 vector.
 *
 * \return minimum reduction (float).
 */
static inline float
jbm_8xf32_reduce_min (const __m256 x)  ///< __m256 vector.
{
  __m128 h, l;
  h = _mm256_extractf128_ps (x, 1);
  l = _mm256_castps256_ps128 (x);
  return jbm_4xf32_reduce_min (_mm_min_ps (h, l));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m256
 * vector.
 */
static inline void
jbm_8xf32_reduce_maxmin (const __m256 x,       ///< __m256 vector.
                         float *max,   ///< pointer to the maximum value
                         float *min)   ///< pointer to the minimum value
{
  __m128 h, l;
  h = _mm256_extractf128_ps (x, 1);
  l = _mm256_castps256_ps128 (x);
  *max = jbm_4xf32_reduce_max (_mm_max_ps (h, l));
  *min = jbm_4xf32_reduce_min (_mm_min_ps (h, l));
}


/**
 * Function to calculate the additive inverse value of a __m256 vector.
 *
 * \return opposite value vector (__m256).
 */
static inline __m256
jbm_8xf32_opposite (const __m256 x)     ///< __m256 vector.
{
  JBM8xF32 y;
  y.i = JBM_BITS_SIGN_8xF32;
  return _mm256_xor_ps (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m256 vector.
 *
 * \return reciprocal value vector (__m256).
 */
static inline __m256
jbm_8xf32_reciprocal (const __m256 x)   ///< __m256 vector.
{
  return _mm256_div_ps (_mm256_set1_ps (1.f), x);
}

/**
 * Function to calculate the sign of a __m256 vector.
 *
 * \return sign vector (__m256).
 */
static inline __m256
jbm_8xf32_sign (const __m256 x) ///< __m256 vector.
{
  JBM8xF32 y;
  y.x = x;
  y.i = _mm256_and_si256 (y.i, JBM_BITS_SIGN_8xF32);
  y.i = _mm256_or_si256 (y.i, JBM_BITS_1_8xF32);
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m256 vector.
 *
 * \return absolute value vector (__m256).
 */
static inline __m256
jbm_8xf32_abs (const __m256 x)  ///< __m256 vector.
{
  JBM8xF32 y;
  y.i = JBM_BITS_SIGN_8xF32;
  return _mm256_andnot_ps (y.x, x);
}

/**
 * Function to copy the sign of a __m256 vector to another __m256 vector.
 *
 * \return __m256 vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m256
jbm_copy8xf32_sign (const __m256 x,
///< __m256 vector to preserve magnitude.
                    const __m256 y)     ///< __m256 vector to preserve sign.
{
  JBM8xF32 m;
  m.i = JBM_BITS_SIGN_8xF32;
  return _mm256_or_ps (jbm_8xf32_abs (x), _mm256_and_ps (y, m.x));
}

/**
 * Function to calculate the hypot function (__m256).
 *
 * \return function value vector (__m256).
 */
static inline __m256
jbm_8xf32_hypot (const __m256 x,        ///< 1st __m256 vector.
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
jbm_8xf32_mod (const __m256 x,  ///< dividend (__m256).
               const __m256 d)  ///< divisor (__m256).
{
  __m256 r;
  r = _mm256_floor_ps (_mm256_div_ps (x, d));
  return _mm256_blendv_ps (_mm256_fnmadd_ps (r, d, x),
                        _mm256_mul_ps (d, _mm256_set1_ps (0.5f)),
                        _mm256_cmp_ps (jbm_8xf32_abs (r),
                                       _mm256_set1_ps (1.f / FLT_EPSILON),
				       _CMP_GT_OQ));
}

/**
 * Function to implement the standard frexp function (__m256).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m256
jbm_8xf32_frexp (const __m256 x,        ///< __m256 vector.
                 __m256i *e)    ///< pointer to the extracted exponents vector.
{
  const __m256i zi = _mm256_setzero_si256 ();
  const __m256i bias = JBM_BIAS_8xF32;
  const __m256i abs_mask = JBM_BITS_ABS_8xF32;
  const __m256i sign_mask = JBM_BITS_SIGN_8xF32;
  const __m256i mant_mask = JBM_BITS_MANTISSA_8xF32;
  JBM8xF32 y, z;
  __m256i exp, is_z, is_sub, is_nan, is_finite;
  // y(x)=abs(x)
  y.x = x;
  y.i = _mm256_and_si256 (y.i, abs_mask);
  // masks
  is_z = _mm256_cmpeq_epi32 (y.i, zi);
  is_nan
    = _mm256_cmpgt_epi32 (y.i, _mm256_set1_epi32 (JBM_BITS_EXPONENT_F32 - 1));
  is_finite = _mm256_andnot_si256 (_mm256_or_si256 (is_z , is_nan),
                                   _mm256_set1_epi32 (-1));
  // extract exponent
  exp = _mm256_srli_epi32 (y.i, 23);
  // subnormals
  is_sub = _mm256_and_si256 (is_finite, _mm256_cmpeq_epi32 (exp, zi));
  y.x
    = _mm256_blendv_ps (y.x,
                        _mm256_mul_ps (y.x, _mm256_set1_ps (0x1p23f)),
                        _mm256_castsi256_ps (is_sub));
  exp
    = _mm256_blendv_epi8 (exp, _mm256_sub_epi32 (_mm256_srli_epi32 (y.i, 23),
                                                  _mm256_set1_epi32 (23)),
                          is_sub);
  // exponent
  *e = _mm256_blendv_epi8 (zi, _mm256_sub_epi32 (exp, bias), is_finite);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm256_or_si256 (_mm256_and_si256 (z.i, sign_mask),
                         _mm256_or_si256 (_mm256_set1_epi32 (JBM_BIAS_F32
                                                             << 23),
                                          _mm256_and_si256 (y.i, mant_mask)));
  return _mm256_blendv_ps (x, y.x, _mm256_castsi256_ps (is_finite));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m256i).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_exp2n (__m256i e)     ///< exponent vector (__m256i).
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
jbm_8xf32_ldexp (const __m256 x,        ///< __m256 vector.
                 const __m256i e)       ///< exponent vector (__m256i).
{
  return _mm256_mul_ps (x, jbm_8xf32_exp2n (e));
}

/**
 * Function to check small __m256 vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m256
jbm_small_8xf32 (const __m256 x)        ///< __m256d vector.
{
  return _mm256_cmp_ps (jbm_8xf32_abs (x), _mm256_set1_ps (FLT_EPSILON),
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
  const __m256 z = _mm256_setzero_ps ();
  __m256 aa, ab, y;
  ab = _mm256_mul_ps (a, b);
  y = _mm256_blendv_ps (z, a, _mm256_cmp_ps (ab, z, _CMP_GT_OS));
  aa = jbm_8xf32_abs (y);
  ab = jbm_8xf32_abs (b);
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
jbm_8xf32_dbl (const __m256 x)  ///< __m256d vector.
{
  return _mm256_add_ps (x, x);
}

/**
 * Function to calculate the square of the components of a __m256 vector.
 *
 * \return __m256 vector square.
 */
static inline __m256
jbm_8xf32_sqr (const __m256 x)  ///< __m256 vector.
{
  return _mm256_mul_ps (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m256 vectors of 2D points.
 *
 * \return __m256 vector of y-coordinates of the extrapolated points.
 */
static inline __m256
jbm_8xf32_extrapolate (const __m256 x,
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
  return _mm256_fmadd_ps (_mm256_sub_ps (x, x1),
                          _mm256_div_ps (_mm256_sub_ps (y2, y1),
                                         _mm256_sub_ps (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m256 vectors of 2D points.
 *
 * \return __m256 vector of y-coordinates of the interpolated points.
 */
static inline __m256
jbm_8xf32_interpolate (const __m256 x,
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
  k = jbm_8xf32_extrapolate (x, x1, x2, y1, y2);
  k = _mm256_blendv_ps (y1, k, _mm256_cmp_ps (x, x1, _CMP_GT_OS));
  return _mm256_blendv_ps (y2, k, _mm256_cmp_ps (x, x2, _CMP_LT_OS));
}

/**
 * Function to calculate the length of a __m256 vector of 2D segments.
 *
 * \return __m256 vector of segment lengths.
 */
static inline __m256
jbm_8xf32_v2_length (const __m256 x1,
///< __m256 vector of x-coordinates of the 1st points defining the segment.
                     const __m256 y1,
///< __m256 vector of y-coordinates of the 1st points defining the segment.
                     const __m256 x2,
///< __m256 vector of x-coordinates of the 2nd points defining the segment.
                     const __m256 y2)
///< __m256 vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_8xf32_hypot (_mm256_sub_ps (x2, x1), _mm256_sub_ps (y2, y1));
}

/**
 * Function to calculate the length of a __m256 vector of 3D segments.
 *
 * \return __m256 vector of segment lengths.
 */
static inline __m256
jbm_8xf32_v3_length (const __m256 x1,
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
  dx = jbm_8xf32_sqr (_mm256_sub_ps (x2, x1));
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
jbm_8xf32_polynomial_1 (const __m256 x, ///< __m256 vector.
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
jbm_8xf32_polynomial_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_4 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_5 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_6 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_7 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_8 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_9 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_10 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_11 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_12 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_13 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_14 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_15 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_16 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_17 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_18 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_19 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_20 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_21 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_22 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_23 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_24 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_25 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_24 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_26 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_25 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_27 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_26 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_28 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_27 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m256).
 *
 * \return __m256 vector of polynomial values.
 */
static inline __m256
jbm_8xf32_polynomial_29 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_fmadd_ps (x, jbm_8xf32_polynomial_28 (x, p + 1),
                          _mm256_set1_ps (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_1_0 (const __m256 x, ///< __m256 vector.
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
jbm_8xf32_rational_2_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+1st order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_2_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[2]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_3_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_3_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_3_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[3]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_4_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_4_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_4_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_4_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[4]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_5_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_5_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_5_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_5_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_5_4 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[5]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_6_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_6_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_6_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_6_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_6_4 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_6_5 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[6]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_4 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_5 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_7_6 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[7]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_4 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_5 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_6 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_8_7 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[8]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_0 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_1 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_2 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_3 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_4 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_5 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_6 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_7 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_9_8 (const __m256 x, ///< __m256 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[9]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_10_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[10]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_11_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[11]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_12_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[12]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_13_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[13]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_14_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[14]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_15_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[15]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_16_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[16]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_17_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[17]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_18_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[18]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_19_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[19]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_20_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[20]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_21_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[21]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_22_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[22]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_23_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[23]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_24_23 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_23 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[24]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_24 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_23 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_23 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_25_24 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_24 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[25]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_25 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_24 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_23 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_23 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_24 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_24 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_26_25 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_25 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[26]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_26 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_25 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_24 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_23 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_23 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_24 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_24 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_25 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_25 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 26),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_27_26 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_26 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[27]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+28th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_27 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_26 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_25 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_24 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_23 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_23 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_24 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_24 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_25 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_25 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 26),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_26 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_26 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 27),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_28_27 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_27 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[28]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+29th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_0 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (_mm256_set1_ps (p[0]),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_28 (x, p + 1),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_1 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_1 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_27 (x, p + 2),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_2 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_2 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_26 (x, p + 3),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_3 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_3 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_25 (x, p + 4),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+25th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_4 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_4 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_24 (x, p + 5),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+24th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_5 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_5 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_23 (x, p + 6),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+23th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_6 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_6 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_22 (x, p + 7),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+22th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_7 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_7 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_21 (x, p + 8),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+21th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_8 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_8 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_20 (x, p + 9),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+20th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_9 (const __m256 x,        ///< __m256 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_9 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_19 (x, p + 10),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+19th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_10 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_10 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_18 (x, p + 11),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+18th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_11 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_11 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_17 (x, p + 12),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+17th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_12 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_12 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_16 (x, p + 13),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+16th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_13 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_13 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_15 (x, p + 14),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+15th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_14 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_14 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_14 (x, p + 15),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+14th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_15 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_15 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_13 (x, p + 16),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+13th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_16 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_16 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_12 (x, p + 17),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+12th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_17 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_17 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_11 (x, p + 18),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+11th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_18 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_18 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_10 (x, p + 19),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+10th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_19 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_19 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_9 (x, p + 20),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+9th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_20 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_20 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_8 (x, p + 21),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+8th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_21 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_21 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_7 (x, p + 22),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+7th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_22 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_22 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_6 (x, p + 23),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+6th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_23 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_23 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_5 (x, p + 24),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+5th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_24 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_24 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_4 (x, p + 25),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+4th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_25 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_25 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_3 (x, p + 26),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_26 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_26 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_2 (x, p + 27),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_27 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_27 (x, p),
                        _mm256_fmadd_ps (x, jbm_8xf32_polynomial_1 (x, p + 28),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256).
 *
 * \return __m256 vector of rational values.
 */
static inline __m256
jbm_8xf32_rational_29_28 (const __m256 x,       ///< __m256 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm256_div_ps (jbm_8xf32_polynomial_28 (x, p),
                        _mm256_fmadd_ps (x, _mm256_set1_ps (p[29]),
                                         _mm256_set1_ps (1.f)));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_cbrtwc (const __m256 x)
                   ///< __m256 vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_8xf32_rational_5_3 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_8xf32_cbrtwc
 * function (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_cbrt (const __m256 x) ///< __m256 vector.
{
  const __m256 cbrt2 = JBM_CBRT2_8xF32;
  const __m256 cbrt4 = JBM_CBRT4_8xF32;
  const __m256i v3 = _mm256_set1_epi32 (3);
  const __m256i v2 = _mm256_set1_epi32 (2);
  const __m256i v1 = _mm256_set1_epi32 (1);
  __m256 y;
  __m256i e, e3, r, n;
  __m128i e16;
  y = jbm_8xf32_frexp (jbm_8xf32_abs (x), &e);
  e16 = _mm256_cvtepi32_epi16 (e);
  e16 = _mm_mulhi_epi16 (e16, _mm_set1_epi16 (0x5556));
  e3 = _mm256_cvtepi16_epi32 (e16);
  r = _mm256_sub_epi32 (e, _mm256_mullo_epi32 (e3, v3));
  n = _mm256_srai_epi32 (r, 31);
  r = _mm256_add_epi32 (r, _mm256_and_si256 (n, v3));
  e3 = _mm256_sub_epi32 (e3, _mm256_and_si256 (n, v1));
  y = jbm_8xf32_ldexp (jbm_8xf32_cbrtwc (y), e3);
  y = _mm256_blendv_ps (y, _mm256_mul_ps (y, cbrt2),
                        _mm256_castsi256_ps (_mm256_cmpeq_epi32 (r, v1)));
  y = _mm256_blendv_ps (y, _mm256_mul_ps (y, cbrt4),
                        _mm256_castsi256_ps (_mm256_cmpeq_epi32 (r, v2)));
  return jbm_copy8xf32_sign (y, x);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m256).
 *
 * \return function value.
 */
static inline __m256
jbm_8xf32_exp2wc (const __m256 x)
                  ///< __m256 vector \f$\in\left[\frac12,1\right]\f$.
{
  return jbm_8xf32_polynomial_5 (x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_8xf32 and
 * jbm_8xf32_exp2n functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_exp2 (const __m256 x) ///< __m256 vector.
{
  __m256 y, f;
  y = _mm256_floor_ps (x);
  f = _mm256_sub_ps (x, y);
  y = jbm_8xf32_exp2n (_mm256_cvtps_epi32 (y));
  return _mm256_mul_ps (y, jbm_8xf32_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_8xf32_exp2 function
 * (__m256).
 *
 * \return function value.
 */
static inline __m256
jbm_8xf32_exp (const __m256 x)  ///< __m256 vector.
{
  return jbm_8xf32_exp2 (_mm256_mul_ps (x, _mm256_set1_ps (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_8xf32_exp2
 * function (__m256).
 *
 * \return function value.
 */
static inline __m256
jbm_8xf32_exp10 (const __m256 x)        ///< __m256 vector.
{
  return jbm_8xf32_exp2 (_mm256_mul_ps (x, _mm256_set1_ps (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_expm1wc (const __m256 x)
///< __m256 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  __m256 x2;
  x2 = jbm_8xf32_sqr (x);
  x2 = _mm256_fmadd_ps (x2, _mm256_set1_ps (b4), _mm256_set1_ps (b2));
  x2 = _mm256_fmadd_ps (x2, x, _mm256_set1_ps (b1));
  x2 = _mm256_fmadd_ps (x2, x, _mm256_set1_ps (1.f));
  return _mm256_mul_ps (x, _mm256_div_ps (_mm256_set1_ps (a1), x2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_8xf32_expm1wc and
 * jbm_8xf32_exp functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_expm1 (const __m256 x)        ///< __m128 vector.
{
  return
    _mm256_blendv_ps (_mm256_sub_ps (jbm_8xf32_exp (x), _mm256_set1_ps (1.f)),
                      jbm_8xf32_expm1wc (x),
                      _mm256_cmp_ps (jbm_8xf32_abs (x),
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
jbm_8xf32_log2wc (const __m256 x)       ///< __m256 vector.
{
  return _mm256_mul_ps (x, jbm_8xf32_rational_5_2 (x, K_LOG2WC_F32));
}

/**
 * Function to calculate the function log2(x) using jbm_8xf32_log2wc and
 * jbm_8xf32_frexp (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_log2 (const __m256 x) ///< __m256 vector.
{
  const __m256 z = _mm256_setzero_ps ();
  __m256 y, m;
  __m256i e;
  y = jbm_8xf32_frexp (x, &e);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (M_SQRT1_2f), _CMP_LT_OQ);
  y = _mm256_add_ps (y, _mm256_and_ps (m, y));
  e = _mm256_sub_epi32 (e, _mm256_and_si256 (_mm256_castps_si256 (m),
                                             _mm256_set1_epi32 (1)));
  y = _mm256_add_ps (jbm_8xf32_log2wc (_mm256_sub_ps (y,
                                        _mm256_set1_ps (1.f))),
                     _mm256_cvtepi32_ps (e));
  y = _mm256_blendv_ps (y, _mm256_set1_ps (-INFINITY),
                        _mm256_cmp_ps (x, z, _CMP_EQ_OQ));
  y = _mm256_blendv_ps (y, _mm256_set1_ps (NAN),
                        _mm256_cmp_ps (x, z, _CMP_LT_OQ));
  y = _mm256_blendv_ps (y, x,
                        _mm256_cmp_ps (x, _mm256_set1_ps (INFINITY),
                                       _CMP_EQ_OQ));
  return _mm256_blendv_ps (y, x, _mm256_cmp_ps (x, x, _CMP_UNORD_Q));
}

/**
 * Function to calculate the function log(x) using jbm_8xf32_log2 (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_log (const __m256 x)  ///< __m256 vector.
{
  return _mm256_mul_ps (jbm_8xf32_log2 (x), _mm256_set1_ps (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_8xf32_log2.
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_log10 (const __m256 x)        ///< __m256 vector.
{
  return _mm256_mul_ps (jbm_8xf32_log2 (x), _mm256_set1_ps (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (__m256).
 *
 * \return function value (__m256) (__m256).
 */
static inline __m256
jbm_8xf32_pown (const __m256 x, ///< __m256 vector.
                const int e)    ///< exponent (int).
{
  __m256 f, xn;
  unsigned int i;
  f = _mm256_set1_ps (1.f);
  if (e < 0)
    xn = _mm256_div_ps (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_8xf32_sqr (xn))
    if (i & 1)
      f = _mm256_mul_ps (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_8xf32_exp2 and
 * jbm_8xf32_log2 functions (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_pow (const __m256 x,  ///< __m256 vector.
               const float e)   ///< exponent (float).
{
  return
    jbm_8xf32_exp2 (_mm256_mul_ps (_mm256_set1_ps (e), jbm_8xf32_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m256)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_sinwc (const __m256 x)
                 ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm256_mul_ps (x, jbm_8xf32_polynomial_3 (jbm_8xf32_sqr (x), K_SINWC_F32));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m256):
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_coswc (const __m256 x)
                 ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_8xf32_polynomial_3 (jbm_8xf32_sqr (x), K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_8xf32_sinwc approximation (__m256).
 */
static inline void
jbm_sin8xf32_coswc (const __m256 x,
                    ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m256 *s,  ///< pointer to the sin function value (__m256).
                    __m256 *c)  ///< pointer to the cos function value (__m256).
{
  *s = jbm_8xf32_sinwc (x);
  *c = jbm_8xf32_coswc (x);
}

/**
 * Function to calculate the function sin(x) from jbm_8xf32_sinwc and
 * jbm_8xf32_coswc approximations (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_sin (const __m256 x)  ///< __m256 vector.
{
  const __m256 pi3_2 = _mm256_set1_ps (3.f * M_PI_2f);
  const __m256 pi = _mm256_set1_ps (M_PIf);
  const __m256 pi_2 = _mm256_set1_ps (M_PI_2f);
  const __m256 pi_4 = _mm256_set1_ps (M_PI_4f);
  __m256 y, q, s;
  q = jbm_8xf32_mod (_mm256_add_ps (x, pi_4), _mm256_set1_ps (2.f * M_PIf));
  y = _mm256_sub_ps (q, pi_4);
  s = jbm_8xf32_opposite (jbm_8xf32_coswc (_mm256_sub_ps (pi3_2, y)));
  s = _mm256_blendv_ps (s, jbm_8xf32_sinwc (_mm256_sub_ps (pi, y)),
                        _mm256_cmp_ps (q, pi3_2, _CMP_LT_OS));
  s = _mm256_blendv_ps (s, jbm_8xf32_coswc (_mm256_sub_ps (pi_2, y)),
                        _mm256_cmp_ps (q, pi, _CMP_LT_OS));
  return _mm256_blendv_ps (s, jbm_8xf32_sinwc (y),
                           _mm256_cmp_ps (q, pi_2, _CMP_LT_OS));
}

/**
 * Function to calculate the function cos(x) from jbm_8xf32_sinwc and
 * jbm_8xf32_coswc approximations (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_cos (const __m256 x)  ///< __m256 vector.
{
  const __m256 pi2 = _mm256_set1_ps (2.f * M_PIf);
  __m256 y, c;
  y = jbm_8xf32_mod (x, pi2);
  c = _mm256_blendv_ps (jbm_8xf32_coswc (_mm256_sub_ps (y, pi2)),
                        jbm_8xf32_sinwc
                        (_mm256_sub_ps (y, _mm256_set1_ps (3.f * M_PI_2f))),
                        _mm256_cmp_ps (y, _mm256_set1_ps (7.f * M_PI_4f),
                                       _CMP_LT_OS));
  c = _mm256_blendv_ps (c,
                        jbm_8xf32_opposite
                        (jbm_8xf32_coswc
                         (_mm256_sub_ps (_mm256_set1_ps (M_PIf), y))),
                        _mm256_cmp_ps (y, _mm256_set1_ps (5.f * M_PI_4f),
                                       _CMP_LT_OS));
  c =
    _mm256_blendv_ps (c,
                      jbm_8xf32_sinwc (_mm256_sub_ps
                                       (_mm256_set1_ps (M_PI_2f), y)),
                      _mm256_cmp_ps (y, _mm256_set1_ps (3.f * M_PI_4f),
                                     _CMP_LT_OS));
  return _mm256_blendv_ps (c, jbm_8xf32_coswc (y),
                           _mm256_cmp_ps (y, _mm256_set1_ps (M_PI_4f),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_8xf32_sinwc and jbm_8xf32_coswc approximations (__m256).
 */
static inline void
jbm_sin8xf32_cos (const __m256 x,
                  ///< __m256 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m256 *s,    ///< pointer to the sin function value (__m256).
                  __m256 *c)    ///< pointer to the cos function value (__m256).
{
  const __m256 pi2 = _mm256_set1_ps (2.f * M_PIf);
  const __m256 z = _mm256_setzero_ps ();
  __m256 y, m, s1, c1, s2, c2;
  y = jbm_8xf32_mod (x, pi2);
  jbm_sin8xf32_coswc (_mm256_sub_ps (y, pi2), &s1, &c1);
  jbm_sin8xf32_coswc (_mm256_sub_ps (y, _mm256_set1_ps (3.f * M_PI_2f)), &c2,
                      &s2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (7.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm256_blendv_ps (s1, _mm256_sub_ps (z, s2), m);
  c1 = _mm256_blendv_ps (c1, c2, m);
  jbm_sin8xf32_coswc (_mm256_sub_ps (_mm256_set1_ps (M_PIf), y), &s2, &c2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (5.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm256_blendv_ps (s1, s2, m);
  c1 = _mm256_blendv_ps (c1, _mm256_sub_ps (z, c2), m);
  jbm_sin8xf32_coswc (_mm256_sub_ps (_mm256_set1_ps (M_PI_2f), y), &c2, &s2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (3.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm256_blendv_ps (s1, s2, m);
  c1 = _mm256_blendv_ps (c1, c2, m);
  jbm_sin8xf32_coswc (y, &s2, &c2);
  m = _mm256_cmp_ps (y, _mm256_set1_ps (M_PI_4f), _CMP_LT_OS);
  *s = _mm256_blendv_ps (s1, s2, m);
  *c = _mm256_blendv_ps (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_sin8xf32_cos function
 * (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_tan (const __m256 x)  ///< __m256 vector.
{
  __m256 s, c;
  jbm_sin8xf32_cos (x, &s, &c);
  return _mm256_div_ps (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m256).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_atanwc (const __m256 x)
                  ///< __m256 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm256_mul_ps (x, jbm_8xf32_rational_5_2 (jbm_8xf32_sqr (x), K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_8xf32
 * function (__m256).
 *
 * \return function value (in [-pi/2,pi/2]) (__m256).
 */
static inline __m256
jbm_8xf32_atan (const __m256 x) ///< __m256 vector.
{
  __m256 f, ax, m;
  ax = jbm_8xf32_abs (x);
  m = _mm256_cmp_ps (ax, _mm256_set1_ps (1.f), _CMP_GT_OS);
  ax = _mm256_blendv_ps (ax, jbm_8xf32_reciprocal (ax), m);
  f = jbm_8xf32_atanwc (ax);
  f = _mm256_blendv_ps (f, _mm256_sub_ps (_mm256_set1_ps (M_PI_2f), f), m);
  return jbm_copy8xf32_sign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_8xf32_atan
 * function (__m256).
 *
 * \return function value (in [-pi,pi]) (__m256).
 */
static inline __m256
jbm_8xf32_atan2 (const __m256 y,        ///< __m256 y component.
                 const __m256 x)        ///< __m256 x component.
{
  __m256 f, g;
  f = jbm_8xf32_atan (_mm256_div_ps (y, x));
  g = _mm256_add_ps (f, jbm_copy8xf32_sign (_mm256_set1_ps (M_PIf), y));
  return
    _mm256_blendv_ps (f, g,
                      _mm256_cmp_ps (x, _mm256_setzero_ps (), _CMP_LT_OS));
}

/**
 * Function to calculate the function asin(x) using the jbm_8xf32_atan function
 * (__m256).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline __m256
jbm_8xf32_asin (const __m256 x) ///< __m256 vector.
{
  return
    jbm_8xf32_atan (_mm256_div_ps
                    (x,
                     _mm256_sqrt_ps (_mm256_fnmadd_ps
                                     (x, x, _mm256_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_8xf32_atan function
 * (__m256).
 *
 * \return function value (in [0,pi]) (__m256).
 */
static inline __m256
jbm_8xf32_acos (const __m256 x) ///< __m256 vector.
{
  __m256 f;
  f =
    jbm_8xf32_atan (_mm256_div_ps
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
jbm_8xf32_sinh (const __m256 x) ///< __m256 number.
{
  __m256 f;
  f = jbm_8xf32_exp (x);
  return _mm256_mul_ps (_mm256_set1_ps (0.5f),
                        _mm256_sub_ps (f, jbm_8xf32_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_cosh (const __m256 x) ///< __m256 number.
{
  __m256 f;
  f = jbm_8xf32_exp (x);
  return _mm256_mul_ps (_mm256_set1_ps (0.5f),
                        _mm256_add_ps (f, jbm_8xf32_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_tanh (const __m256 x) ///< __m256 number.
{
  __m256 f, fi;
  f = jbm_8xf32_exp (x);
  fi = jbm_8xf32_reciprocal (f);
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
jbm_8xf32_asinh (const __m256 x)        ///< __m256 number.
{
  return
    jbm_8xf32_log (_mm256_add_ps
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
jbm_8xf32_acosh (const __m256 x)        ///< __m256 number.
{
  return
    jbm_8xf32_log (_mm256_add_ps
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
jbm_8xf32_atanh (const __m256 x)        ///< __m256 number.
{
  const __m256 u = _mm256_set1_ps (1.f);
  return _mm256_mul_ps (_mm256_set1_ps (0.5f),
                        jbm_8xf32_log (_mm256_div_ps (_mm256_add_ps (u, x),
                                                      _mm256_sub_ps (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m256)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_erfwc (const __m256 x)
                 ///< __m256 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm256_mul_ps (x, jbm_8xf32_polynomial_5 (jbm_8xf32_sqr (x), K_ERFWC_F32));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m256)
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_erfcwc (const __m256 x)
                  ///< __m256 vector \f$\in\left[1,\infty\right]\f$.
{
  __m256 f, x2;
  x2 = jbm_8xf32_sqr (x);
  f = _mm256_mul_ps (jbm_8xf32_rational_8_4 (jbm_8xf32_reciprocal (x),
                                             K_ERFCWC_F32),
                     _mm256_div_ps (x, jbm_8xf32_exp (x2)));
  return
    _mm256_blendv_ps (f, _mm256_setzero_ps (),
                      _mm256_cmp_ps (x, _mm256_set1_ps (K_ERFC_MAX_F32),
                                     _CMP_GT_OS));
}

/**
 * Function to calculate the function erf(x) using jbm_8xf32_erfwc and
 * jbm_8xf32_erfcwc.
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_erf (const __m256 x)  ///< __m256 vector.
{
  const __m256 u = _mm256_set1_ps (1.f);
  __m256 ax, f;
  ax = jbm_8xf32_abs (x);
  f = jbm_copy8xf32_sign (_mm256_sub_ps (u, jbm_8xf32_erfcwc (ax)), x);
  return _mm256_blendv_ps (f, jbm_8xf32_erfwc (x),
                           _mm256_cmp_ps (ax, u, _CMP_LT_OS));

}

/**
 * Function to calculate the function erfc(x) using jbm_8xf32_erfwc and
 * jbm_8xf32_erfcwc.
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_erfc (const __m256 x) ///< __m256 vector.
{
  const __m256 u2 = _mm256_set1_ps (2.f);
  const __m256 u = _mm256_set1_ps (1.f);
  __m256 ax, cwc, wc;
  ax = jbm_8xf32_abs (x);
  cwc = jbm_8xf32_erfcwc (ax);
  wc = _mm256_sub_ps (u, jbm_8xf32_erfwc (x));
  return
    _mm256_blendv_ps
    (_mm256_blendv_ps
     (wc, _mm256_sub_ps (u2, cwc), _mm256_cmp_ps (ax, u, _CMP_GT_OS)), cwc,
     _mm256_cmp_ps (x, u, _CMP_GT_OS));
}

/**
 * Function to calculate the solution of a __m256 vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m256 vector of solution values.
 */
static inline __m256
jbm_solve_quadratic_reduced_8xf32 (const __m256 a,
///< __m256 vector of 1st order coefficient of the equations.
                                   const __m256 b,
///< __m256 vector of 0th order coefficient of the equations.
                                   const __m256 x1,
///< __m256 vector of left limits of the solution intervals.
                                   const __m256 x2)
///< __m256 vector of right limits of the solution intervals.
{
  __m256 ka, kb, k1, k2;
  k1 = _mm256_set1_ps (-0.5f);
  ka = _mm256_mul_ps (a, k1);
  kb = _mm256_sqrt_ps (_mm256_sub_ps (jbm_8xf32_sqr (ka), b));
  k1 = _mm256_add_ps (ka, kb);
  k2 = _mm256_sub_ps (ka, kb);
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
jbm_8xf32_solve_quadratic (const __m256 a,
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
  k2 = _mm256_div_ps (jbm_8xf32_opposite (c), b);
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
  l1 = _mm256_sqrt_ps (jbm_8xf32_opposite (k1));
  l0 = _mm256_mul_ps (jbm_8xf32_acos (_mm256_div_ps (k0, k3)), c_3);
  l1 = _mm256_add_ps (l1, l1);
  l2 = _mm256_fmsub_ps (l1, jbm_8xf32_cos (k0), a3);
  l3 = _mm256_fmsub_ps (l1, jbm_8xf32_cos (_mm256_add_ps (l0, c2p_3)), a3);
  l3 = _mm256_blendv_ps (l3, l2,
                         _mm256_or_ps (_mm256_cmp_ps (l2, x1, _CMP_LT_OS),
                                       _mm256_cmp_ps (l2, x2, _CMP_GT_OS)));
  l4 = _mm256_fmsub_ps (l1, jbm_8xf32_cos (_mm256_sub_ps (l0, c2p_3)), a);
  l4 = _mm256_blendv_ps (l4, l3,
                         _mm256_or_ps (_mm256_cmp_ps (l3, x1, _CMP_LT_OS),
                                       _mm256_cmp_ps (l3, x2, _CMP_GT_OS)));
  k1 = _mm256_sqrt_ps (k2);
  l5 = _mm256_add_ps (k0, k1);
  l5 = jbm_8xf32_cbrt (k2);
  k0 = _mm256_sub_ps (k0, k1);
  l5 = _mm256_add_ps (l5, _mm256_sub_ps (jbm_8xf32_cbrt (k0), a3));
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
jbm_8xf32_solve_cubic (const __m256 a,
///< __m256 vector of 3rd order coefficient of the equations.
                       const __m256 b,
///< __m256 vector of 2nd order coefficient of the equations.
                       const __m256 c,
///< __m256 vector of 1st order coefficient of the equations.
                       const __m256 d,
///< __m256 vector of 0th order coefficient of the equations.
                       const __m256 x1,
///< __m256 vector of left limits of the solution intervals.
                       const __m256 x2)
///< __m256 vector of right limits of the solution intervals.
{
  return
    _mm256_blendv_ps (jbm_solve_cubic_reduced_8xf32 (_mm256_div_ps (b, a),
                                                     _mm256_div_ps (c, a),
                                                     _mm256_div_ps (d, a), x1,
                                                     x2),
                      jbm_8xf32_solve_quadratic (b, c, d, x1, x2),
                      jbm_small_8xf32 (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m256).
 *
 * \return flux limiter function value.
 */
static inline __m256
jbm_8xf32_flux_limiter_total (const __m256 d1 __attribute__((unused)),
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
jbm_8xf32_flux_limiter_null (const __m256 d1 __attribute__((unused)),
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
jbm_8xf32_flux_limiter_centred (const __m256 d1,
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
jbm_8xf32_flux_limiter_superbee (const __m256 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_div_ps (d1, d2);
  r = _mm256_max_ps (_mm256_min_ps (jbm_8xf32_dbl (r), _mm256_set1_ps (1.f)),
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
jbm_8xf32_flux_limiter_minmod (const __m256 d1,
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
jbm_8xf32_flux_limiter_VanLeer (const __m256 d1,
                                ///< 1st flux limiter function parameter.
                                const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r, k;
  r = _mm256_div_ps (d1, d2);
  k = jbm_8xf32_abs (r);
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
jbm_8xf32_flux_limiter_VanAlbada (const __m256 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r, k;
  r = _mm256_div_ps (d1, d2);
  k = jbm_8xf32_sqr (r);
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
jbm_8xf32_flux_limiter_minsuper (const __m256 d1,
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
jbm_8xf32_flux_limiter_supermin (const __m256 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256 d2)
    ///< 2nd flux limiter function parameter.
{
  __m256 r;
  r = _mm256_div_ps (d1, d2);
  r = _mm256_min_ps (jbm_8xf32_dbl (r), _mm256_set1_ps (1.f));
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
jbm_8xf32_flux_limiter_monotonized_central (const __m256 d1,
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
    _mm256_blendv_ps (rm, jbm_8xf32_dbl (r),
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
jbm_8xf32_flux_limiter_mean (const __m256 d1,
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
jbm_8xf32_flux_limiter (const __m256 d1,
                        ///< 1st flux limiter function parameter.
                        const __m256 d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_8xf32_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_8xf32_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_8xf32_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_8xf32_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_8xf32_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_8xf32_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_8xf32_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_8xf32_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_8xf32_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_8xf32_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_8xf32_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m256).
 *
 * \return __m256 vector of integral values.
 */
static inline __m256
jbm_8xf32_integral (__m256 (*f) (__m256),
                    ///< pointer to the function to integrate.
                    const __m256 x1,    ///< left limit of the interval.
                    const __m256 x2)    ///< right limit of the interval.
{
  __m256 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m256 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm256_set1_ps (0.5f);
  dx = _mm256_mul_ps (h, _mm256_sub_ps (x2, x1));
  x = _mm256_mul_ps (h, _mm256_add_ps (x2, x1));
  k = _mm256_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[0]);
  k = _mm256_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm256_set1_ps (JBM_INTEGRAL_GAUSS_B_F32[i]);
      k2 = _mm256_mul_ps (k2, dx);
      f1 = f (_mm256_sub_ps (x, k2));
      f2 = f (_mm256_add_ps (x, k2));
      h = _mm256_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[i]);
      k = _mm256_fmadd_ps (h, _mm256_add_ps (f1, f2), k);
    }
#endif
  return _mm256_mul_ps (k, dx);
}

/**
 * Function to calculate the additive reduction value of a __m256d vector.
 *
 * \return additive reduction (double).
 */
static inline double
jbm_4xf64_reduce_add (const __m256d x)  ///< __m256d vector.
{
  __m128d h, l;
  h = _mm256_extractf128_pd (x, 1);
  l = _mm256_castpd256_pd128 (x);
  return jbm_2xf64_reduce_add (_mm_add_pd (h, l));
}

/**
 * Function to calculate the maximum reduction value of a __m256d vector.
 *
 * \return maximum reduction (double).
 */
static inline double
jbm_4xf64_reduce_max (const __m256d x)  ///< __m256d vector.
{
  __m128d h, l;
  h = _mm256_extractf128_pd (x, 1);
  l = _mm256_castpd256_pd128 (x);
  return jbm_2xf64_reduce_max (_mm_max_pd (h, l));
}

/**
 * Function to calculate the minimum reduction value of a __m256d vector.
 *
 * \return minimum reduction (double).
 */
static inline double
jbm_4xf64_reduce_min (const __m256d x)  ///< __m256d vector.
{
  __m128d h, l;
  h = _mm256_extractf128_pd (x, 1);
  l = _mm256_castpd256_pd128 (x);
  return jbm_2xf64_reduce_min (_mm_min_pd (h, l));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m256d
 * vector.
 */
static inline void
jbm_4xf64_reduce_maxmin (const __m256d x,       ///< __m256d vector.
                         double *max,   ///< pointer to the maximum value
                         double *min)   ///< pointer to the minimum value
{
  __m128d h, l;
  h = _mm256_extractf128_pd (x, 1);
  l = _mm256_castpd256_pd128 (x);
  *max = jbm_2xf64_reduce_max (_mm_max_pd (h, l));
  *min = jbm_2xf64_reduce_min (_mm_min_pd (h, l));
}

/**
 * Function to calculate the additive inverse value of a __m256d vector.
 *
 * \return negative value vector (__m256d).
 */
static inline __m256d
jbm_4xf64_opposite (const __m256d x)    ///< __m256d vector.
{
  JBM4xF64 y;
  y.i = JBM_BITS_SIGN_4xF64;
  return _mm256_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m256d vector.
 *
 * \return reciprocal value vector (__m256d).
 */
static inline __m256d
jbm_4xf64_reciprocal (const __m256d x)  ///< __m256d vector.
{
  return _mm256_div_pd (_mm256_set1_pd (1.), x);
}

/**
 * Function to calculate the sign of a __m256d vector.
 *
 * \return sign vector (__m256d).
 */
static inline __m256d
jbm_4xf64_sign (const __m256d x)        ///< __m256d vector.
{
  JBM4xF64 y;
  y.x = x;
  y.i = _mm256_and_si256 (y.i, JBM_BITS_SIGN_4xF64);
  y.i = _mm256_and_si256 (y.i, JBM_BITS_1_4xF64);
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m256d vector.
 *
 * \return absolute value vector.
 */
static inline __m256d
jbm_4xf64_abs (const __m256d x)
{
  JBM4xF64 y;
  y.i = JBM_BITS_SIGN_4xF64;
  return _mm256_andnot_pd (y.x, x);
}

/**
 * Function to copy the sign of a __m256d vector to another __m256d vector.
 *
 * \return __m256d vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m256d
jbm_copy4xf64_sign (const __m256d x,
///< __m256d vector to preserve magnitude.
                    const __m256d y)    ///< __m256d vector to preserve sign.
{
  JBM4xF64 m;
  m.i = JBM_BITS_SIGN_4xF64;
  return _mm256_or_pd (jbm_4xf64_abs (x), _mm256_and_pd (y, m.x));
}

/**
 * Function to calculate the hypot function (__m256d).
 *
 * \return function value vector (__m256d).
 */
static inline __m256d
jbm_4xf64_hypot (const __m256d x,       ///< 1st __m256d vector.
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
jbm_4xf64_mod (const __m256d x, ///< dividend (__m256d).
               const __m256d d) ///< divisor (__m256d).
{
  __m256d r;
  r = _mm256_floor_pd (_mm256_div_pd (x, d));
  return _mm256_blendv_pd (_mm256_fnmadd_pd (r, d, x),
                           _mm256_mul_pd (d, _mm256_set1_pd (0.5)),
                           _mm256_cmp_pd (jbm_4xf64_abs (r),
                                          _mm256_set1_pd (1. / DBL_EPSILON),
					  _CMP_GT_OQ));
}

/**
 * Function to implement the standard frexp function (__m256d).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m256d
jbm_4xf64_frexp (const __m256d x,       ///< __m256d vector.
                 __m256i *e)    ///< pointer to the extracted exponents vector.
{
  const __m256i zi = _mm256_setzero_si256 ();
  const __m256i bias = JBM_BIAS_4xF64;
  const __m256i abs_mask = JBM_BITS_ABS_4xF64;
  const __m256i sign_mask = JBM_BITS_SIGN_4xF64;
  const __m256i mant_mask = JBM_BITS_MANTISSA_4xF64;
  JBM4xF64 y, z;
  __m256i exp, is_z, is_sub, is_nan, is_finite;
  // y(x)=abs(x)
  y.x = x;
  y.i = _mm256_and_si256 (y.i, abs_mask);
  // masks
  is_z = _mm256_cmpeq_epi64 (y.i, zi);
  is_nan =_mm256_cmpgt_epi64 (y.i,
                              _mm256_set1_epi64x (JBM_BITS_EXPONENT_F64 - 1ll));
  is_finite = _mm256_andnot_si256 (_mm256_or_si256 (is_z , is_nan),
                                   _mm256_set1_epi64x (-1ll));
  // extract exponent
  exp = _mm256_srli_epi64 (y.i, 52);
  // subnormals
  is_sub = _mm256_and_si256 (is_finite,
                             _mm256_cmpeq_epi64 (exp, zi));
  y.x
    = _mm256_blendv_pd (y.x, _mm256_mul_pd (y.x, _mm256_set1_pd (0x1p52)),
                        _mm256_castsi256_pd (is_sub));
  exp
    = _mm256_blendv_epi8 (exp, _mm256_sub_epi64 (_mm256_srli_epi64 (y.i, 52),
                                                  _mm256_set1_epi64x (52ll)),
                          is_sub);
  // exponent
  *e = _mm256_blendv_epi8 (zi, _mm256_sub_epi64 (exp, bias), is_finite);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm256_or_si256 (_mm256_and_si256 (z.i, sign_mask),
                         _mm256_or_si256 (_mm256_set1_epi64x (JBM_BIAS_F64
                                                              << 52),
                                          _mm256_and_si256 (y.i, mant_mask)));
  return _mm256_blendv_pd (x, y.x, _mm256_castsi256_pd (is_finite));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m256i)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_exp2n (const __m256i e)     ///< exponent vector (__m256i).
{
  const __m256i v1023 = _mm256_set1_epi64x (1023ll);
  __m256d x;
  // normal and subnormal
  x = _mm256_blendv_pd
      (_mm256_castsi256_pd
       (_mm256_slli_epi64 (_mm256_add_epi64 (e, v1023), 52)),
       _mm256_castsi256_pd
       (_mm256_sllv_epi64 (_mm256_set1_epi64x (1),
                           _mm256_add_epi64 (e, _mm256_set1_epi64x (1074ll)))),
       _mm256_castsi256_pd (_mm256_cmpgt_epi64 (_mm256_set1_epi64x (-1022ll),
                            e)));
  // zero
  x = _mm256_blendv_pd
      (x, _mm256_setzero_pd (),
       _mm256_castsi256_pd (_mm256_cmpgt_epi64 (_mm256_set1_epi64x (-1074ll),
                            e)));
  // infinity
  return
    _mm256_blendv_pd (x, _mm256_set1_pd (INFINITY),
                      _mm256_castsi256_pd (_mm256_cmpgt_epi64 (e, v1023)));
}

/**
 * Function to implement the standard ldexp function (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_ldexp (const __m256d x,       ///< __m256d vector.
                 __m256i e)     ///< exponent vector (__m256i).
{
  return _mm256_mul_pd (x, jbm_4xf64_exp2n (e));
}

/**
 * Function to check small __m256d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m256d
jbm_small_4xf64 (const __m256d x)       ///< __m256d vector.
{
  return _mm256_cmp_pd (jbm_4xf64_abs (x), _mm256_set1_pd (DBL_EPSILON),
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
  const __m256d z = _mm256_setzero_pd ();
  __m256d aa, ab, y;
  ab = _mm256_mul_pd (a, b);
  y = _mm256_blendv_pd (a, z, _mm256_cmp_pd (z, ab, _CMP_GT_OS));
  aa = jbm_4xf64_abs (y);
  ab = jbm_4xf64_abs (b);
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
jbm_4xf64_dbl (const __m256d x) ///< __m256d vector.
{
  return _mm256_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m256d vector.
 *
 * \return __m256d vector square.
 */
static inline __m256d
jbm_4xf64_sqr (const __m256d x) ///< __m256d vector.
{
  return _mm256_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m256d vectors of 2D points.
 *
 * \return __m256d vector of y-coordinates of the extrapolated points.
 */
static inline __m256d
jbm_4xf64_extrapolate (const __m256d x,
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
jbm_4xf64_interpolate (const __m256d x,
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
  k = jbm_4xf64_extrapolate (x, x1, x2, y1, y2);
  k = _mm256_blendv_pd (y1, k, _mm256_cmp_pd (x, x1, _CMP_GT_OS));
  return _mm256_blendv_pd (y2, k, _mm256_cmp_pd (x, x2, _CMP_LT_OS));
}

/**
 * Function to calculate the length of a __m256d vector of 2D segments.
 *
 * \return __m256d vector of segment lengths.
 */
static inline __m256d
jbm_4xf64_v2_length (const __m256d x1,
///< __m256d vector of x-coordinates of the 1st points defining the segment.
                     const __m256d y1,
///< __m256d vector of y-coordinates of the 1st points defining the segment.
                     const __m256d x2,
///< __m256d vector of x-coordinates of the 2nd points defining the segment.
                     const __m256d y2)
///< __m256d vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_4xf64_hypot (_mm256_sub_pd (x2, x1), _mm256_sub_pd (y2, y1));
}

/**
 * Function to calculate the length of a __m256d vector of 3D segments.
 *
 * \return __m256d vector of segment lengths.
 */
static inline __m256d
jbm_4xf64_v3_length (const __m256d x1,
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
  dx = jbm_4xf64_sqr (_mm256_sub_pd (x2, x1));
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
jbm_4xf64_polynomial_1 (const __m256d x,        ///< __m256d vector.
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
jbm_4xf64_polynomial_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_4 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_5 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_6 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_7 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_8 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_9 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_10 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_11 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_12 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_13 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_14 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_15 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_16 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_17 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_18 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_19 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_20 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_21 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_22 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_23 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_24 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_25 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_24 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_26 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_25 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_27 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_26 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_28 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_27 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m256d).
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_4xf64_polynomial_29 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_4xf64_polynomial_28 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_1_0 (const __m256d x,        ///< __m256d vector.
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
jbm_4xf64_rational_2_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+1st order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_2_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[2]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_3_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_3_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_3_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[3]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_4_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_4_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_4_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_4_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[4]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_5_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_5_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_5_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_5_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_5_4 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[5]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_6_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_6_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_6_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_6_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_6_4 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_6_5 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[6]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_4 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_5 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_7_6 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[7]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_4 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_5 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_6 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_8_7 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[8]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_0 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_1 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_2 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_3 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_4 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_5 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_6 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_7 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_9_8 (const __m256d x,        ///< __m256d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[9]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_10_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[10]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_11_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[11]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_12_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[12]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_13_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[13]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_14_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[14]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_15_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[15]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_16_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[16]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_17_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[17]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_18_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[18]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_19_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[19]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_20_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[20]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_21_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[21]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_22_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[22]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_23_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[23]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_24_23 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_23 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[24]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_24 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_23 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_23 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_25_24 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_24 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[25]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_25 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_24 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_23 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_23 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_24 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_24 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_26_25 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_25 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[26]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_26 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_25 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_24 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_23 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_23 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_24 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_24 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_25 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_25 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 26),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_27_26 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_26 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[27]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+28th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_27 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_26 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_25 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_24 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_23 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_23 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_24 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_24 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_25 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_25 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 26),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_26 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_26 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 27),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_28_27 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_27 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[28]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+29th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_0 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (_mm256_set1_pd (p[0]),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_28 (x, p + 1),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_1 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_1 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_27 (x, p + 2),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_2 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_2 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_26 (x, p + 3),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_3 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_3 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_25 (x, p + 4),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+25th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_4 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_4 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_24 (x, p + 5),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+24th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_5 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_5 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_23 (x, p + 6),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+23th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_6 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_6 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_22 (x, p + 7),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+22th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_7 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_7 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_21 (x, p + 8),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+21th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_8 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_8 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_20 (x, p + 9),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+20th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_9 (const __m256d x,       ///< __m256d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_9 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_19 (x, p + 10),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+19th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_10 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_10 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_18 (x, p + 11),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+18th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_11 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_11 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_17 (x, p + 12),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+17th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_12 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_12 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_16 (x, p + 13),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+16th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_13 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_13 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_15 (x, p + 14),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+15th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_14 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_14 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_14 (x, p + 15),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+14th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_15 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_15 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_13 (x, p + 16),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+13th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_16 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_16 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_12 (x, p + 17),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+12th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_17 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_17 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_11 (x, p + 18),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+11th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_18 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_18 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_10 (x, p + 19),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+10th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_19 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_19 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_9 (x, p + 20),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+9th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_20 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_20 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_8 (x, p + 21),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+8th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_21 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_21 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_7 (x, p + 22),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+7th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_22 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_22 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_6 (x, p + 23),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+6th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_23 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_23 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_5 (x, p + 24),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+5th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_24 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_24 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_4 (x, p + 25),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+4th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_25 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_25 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_3 (x, p + 26),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_26 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_26 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_2 (x, p + 27),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_27 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_27 (x, p),
                        _mm256_fmadd_pd (x, jbm_4xf64_polynomial_1 (x, p + 28),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m256d).
 *
 * \return __m256d vector of rational values.
 */
static inline __m256d
jbm_4xf64_rational_29_28 (const __m256d x,      ///< __m256d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm256_div_pd (jbm_4xf64_polynomial_28 (x, p),
                        _mm256_fmadd_pd (x, _mm256_set1_pd (p[29]),
                                         _mm256_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_cbrtwc (const __m256d x)
                  ///< __m256d vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_4xf64_rational_11_6 (x, K_CBRTWC_F64);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_4xf64_abs and
 * jbm_4xf64_pow functions (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_cbrt (const __m256d x)        ///< __m256d vector.
{
  const __m256d cbrt2 = JBM_CBRT2_4xF64;
  const __m256d cbrt4 = JBM_CBRT4_4xF64;
  const __m256i v3 = _mm256_set1_epi32 (3);
  const __m256i v2 = _mm256_set1_epi64x (2);
  const __m256i v1 = _mm256_set1_epi64x (1);
  __m256d y;
  __m256i e, e3, r, n;
  y = jbm_4xf64_frexp (jbm_4xf64_abs (x), &e);
  e3 = _mm256_mul_epu32 (e, _mm256_set1_epi32 (0x55555556));
  e3 = _mm256_srli_epi64 (e3, 32);
  r = _mm256_sub_epi32 (e, _mm256_mullo_epi32 (e3, v3));
  n = _mm256_srai_epi32 (r, 31);
  r = _mm256_add_epi32 (r, _mm256_and_si256 (n, v3));
  e3 = _mm256_sub_epi32 (e3, _mm256_and_si256 (n, _mm256_set1_epi32 (1)));
  y = jbm_4xf64_ldexp (jbm_4xf64_cbrtwc (y), e3);
  y = _mm256_blendv_pd (y, _mm256_mul_pd (y, cbrt2),
                        _mm256_castsi256_pd (_mm256_cmpeq_epi64 (r, v1)));
  y = _mm256_blendv_pd (y, _mm256_mul_pd (y, cbrt4),
                        _mm256_castsi256_pd (_mm256_cmpeq_epi64 (r, v2)));
  return jbm_copy4xf64_sign (y, x);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_expm1wc (const __m256d x)
///< __m256d vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return _mm256_mul_pd (x, jbm_4xf64_rational_8_2 (x, K_EXPM1WC_F64));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m256d).
 *
 * \return function value.
 */
static inline __m256d
jbm_4xf64_exp2wc (const __m256d x)
    ///< __m256d vector \f$\in[\frac12,1]\f$.
{
  return jbm_4xf64_rational_9_4 (x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_4xf64 and
 * jbm_4xf64_exp2n functions.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_exp2 (const __m256d x)        ///< __m256d vector.
{
  __m256d y, f;
  __m256i i;
  y = _mm256_floor_pd (x);
  f = _mm256_sub_pd (x, y);
#ifdef __AVX512F__
  i = _mm256_cvttpd_epi64 (y);
#else
  i = _mm256_cvtepi32_epi64 (_mm256_cvttpd_epi32 (y));
#endif
  return _mm256_mul_pd (jbm_4xf64_exp2n (i), jbm_4xf64_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_4xf64_exp2 function.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_exp (const __m256d x) ///< __m256d vector.
{
  return jbm_4xf64_exp2 (_mm256_mul_pd (x, _mm256_set1_pd (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_4xf64_exp2
 * function (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_exp10 (const __m256d x)       ///< __m256d vector.
{
  return jbm_4xf64_exp2 (_mm256_mul_pd (x, _mm256_set1_pd (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_4xf64_expm1wc and
 * jbm_4xf64_exp functions (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_expm1 (const __m256d x)       ///< __m256d vector.
{
  return
    _mm256_blendv_pd (_mm256_sub_pd (jbm_4xf64_exp (x), _mm256_set1_pd (1.)),
                      jbm_4xf64_expm1wc (x),
                      _mm256_cmp_pd (jbm_4xf64_abs (x),
                                     _mm256_set1_pd (M_LN2 / 2.), _CMP_LT_OS));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_log2wc (const __m256d x)      ///< __m256d vector \f$\in[0.5,1]\f$.
{
  return _mm256_mul_pd (x, jbm_4xf64_rational_12_6 (x, K_LOG2WC_F64));
}

/**
 * Function to calculate the function log_2(x) using jbm_logwc_4xf64 and
 * jbm_4xf64_frexp.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_log2 (const __m256d x)        ///< __m256d vector.
{
  const __m256d z = _mm256_setzero_pd ();
  __m256d y, m;
  __m256i e;
  y = jbm_4xf64_frexp (x, &e);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (M_SQRT1_2), _CMP_LT_OQ);
  y = _mm256_add_pd (y, _mm256_and_pd (m, y));
  e = _mm256_sub_epi64 (e, _mm256_and_si256 (_mm256_castpd_si256 (m),
                                             _mm256_set1_epi64x (1ll)));
  y = _mm256_add_pd (jbm_4xf64_log2wc (_mm256_sub_pd (y, _mm256_set1_pd (1.))),
                     _mm256_cvtepi64_pd (e));
  y = _mm256_blendv_pd (y, _mm256_set1_pd (-INFINITY),
                        _mm256_cmp_pd (x, z, _CMP_EQ_OQ));
  y = _mm256_blendv_pd (y, _mm256_set1_pd (NAN),
                        _mm256_cmp_pd (x, z, _CMP_LT_OQ));
  y = _mm256_blendv_pd (y, x,
                        _mm256_cmp_pd (x, _mm256_set1_pd (INFINITY),
                                       _CMP_EQ_OQ));
  return _mm256_blendv_pd (y, x, _mm256_cmp_pd (x, x, _CMP_UNORD_Q));
}

/**
 * Function to calculate the function log(x) using jbm_4xf64_log2 (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_log (const __m256d x) ///< __m256d vector.
{
  return _mm256_mul_pd (jbm_4xf64_log2 (x), _mm256_set1_pd (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_4xf64_log2 (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_log10 (const __m256d x)       ///< __m256d vector.
{
  return _mm256_mul_pd (jbm_4xf64_log2 (x), _mm256_set1_pd (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (__m256d).
 *
 * \return function value (__m256d) (__m256d).
 */
static inline __m256d
jbm_4xf64_pown (const __m256d x,        ///< __m256d vector.
                const int e)    ///< exponent (int).
{
  __m256d f, xn;
  unsigned int i;
  f = _mm256_set1_pd (1.);
  if (e < 0)
    xn = _mm256_div_pd (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_4xf64_sqr (xn))
    if (i & 1)
      f = _mm256_mul_pd (f, xn);
  return f;
}

/**
 * Function to calculate the function f32 using the jbm_4xf64_exp2 and
 * jbm_4xf64_log2 functions.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_pow (const __m256d x, ///< __m256d vector.
               const double e)  ///< exponent (__m256d).
{
  return
    jbm_4xf64_exp2 (_mm256_mul_pd (_mm256_set1_pd (e), jbm_4xf64_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m256d)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_sinwc (const __m256d x)
    ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm256_mul_pd (x, jbm_4xf64_polynomial_6 (jbm_4xf64_sqr (x), K_SINWC_F64));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_coswc (const __m256d x)
    ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_4xf64_polynomial_6 (jbm_4xf64_sqr (x), K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_4xf64_sinwc approximation (__m256d).
 */
static inline void
jbm_sin4xf64_coswc (const __m256d x,
                    ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m256d *s,
                    ///< pointer to the f32 function value (__m256d).
                    __m256d *c)
    ///< pointer to the f32 function value (__m256d).
{
  *s = jbm_4xf64_sinwc (x);
  *c = jbm_4xf64_coswc (x);
}

/**
 * Function to calculate the function sin(x) from jbm_4xf64_sinwc and
 * jbm_4xf64_coswc approximations.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_sin (const __m256d x) ///< __m256d vector.
{
  const __m256d pi2 = _mm256_set1_pd (2. * M_PI);
  __m256d y, s;
  y = jbm_4xf64_mod (x, pi2);
  s = jbm_4xf64_sinwc (_mm256_sub_pd (y, pi2));
  s = _mm256_blendv_pd (s,
                        jbm_4xf64_opposite
                        (jbm_4xf64_coswc
                         (_mm256_sub_pd (_mm256_set1_pd (3. * M_PI_2), y))),
                        _mm256_cmp_pd (y, _mm256_set1_pd (7. * M_PI_4),
                                       _CMP_LT_OS));
  s =
    _mm256_blendv_pd (s,
                      jbm_4xf64_sinwc (_mm256_sub_pd
                                       (_mm256_set1_pd (M_PI), y)),
                      _mm256_cmp_pd (y, _mm256_set1_pd (5. * M_PI_4),
                                     _CMP_LT_OS));
  s =
    _mm256_blendv_pd (s,
                      jbm_4xf64_coswc (_mm256_sub_pd
                                       (_mm256_set1_pd (M_PI_2), y)),
                      _mm256_cmp_pd (y, _mm256_set1_pd (3. * M_PI_4),
                                     _CMP_LT_OS));
  return _mm256_blendv_pd (s, jbm_4xf64_sinwc (y),
                           _mm256_cmp_pd (y, _mm256_set1_pd (M_PI_4),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the function cos(x) from jbm_4xf64_sinwc and
 * jbm_4xf64_coswc approximations (__m256).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_cos (const __m256d x) ///< __m256d vector.
{
  const __m256d pi2 = _mm256_set1_pd (2. * M_PI);
  __m256d y, c;
  y = jbm_4xf64_mod (x, pi2);
  c = jbm_4xf64_coswc (_mm256_sub_pd (y, pi2));
  c = _mm256_blendv_pd (c,
                        jbm_4xf64_sinwc
                        (_mm256_sub_pd (y, _mm256_set1_pd (3. * M_PI_2))),
                        _mm256_cmp_pd (y, _mm256_set1_pd (7. * M_PI_4),
                                       _CMP_LT_OS));
  c = _mm256_blendv_pd (c,
                        jbm_4xf64_opposite
                        (jbm_4xf64_coswc
                         (_mm256_sub_pd (_mm256_set1_pd (M_PI), y))),
                        _mm256_cmp_pd (y, _mm256_set1_pd (5. * M_PI_4),
                                       _CMP_LT_OS));
  c =
    _mm256_blendv_pd (c,
                      jbm_4xf64_sinwc (_mm256_sub_pd
                                       (_mm256_set1_pd (M_PI_2), y)),
                      _mm256_cmp_pd (y, _mm256_set1_pd (3. * M_PI_4),
                                     _CMP_LT_OS));
  return _mm256_blendv_pd (c, jbm_4xf64_coswc (y),
                           _mm256_cmp_pd (y, _mm256_set1_pd (M_PI_4),
                                          _CMP_LT_OS));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_4xf64_sinwc
 * and jbm_4xf64_coswc approximations (__m256d).
 */
static inline void
jbm_sin4xf64_cos (const __m256d x,
                  ///< __m256d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m256d *s,   ///< pointer to the f32 function value (__m256d).
                  __m256d *c)   ///< pointer to the f32 function value (__m256d).
{
  const __m256d pi2 = _mm256_set1_pd (2. * M_PI);
  const __m256d z = _mm256_setzero_pd ();
  __m256d y, m, s1, c1, s2, c2;
  y = jbm_4xf64_mod (x, pi2);
  jbm_sin4xf64_coswc (_mm256_sub_pd (y, pi2), &s1, &c1);
  jbm_sin4xf64_coswc (_mm256_sub_pd (y, _mm256_set1_pd (3. * M_PI_2)), &c2,
                      &s2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (7. * M_PI_4), _CMP_LT_OS);
  s1 = _mm256_blendv_pd (s1, _mm256_sub_pd (z, s2), m);
  c1 = _mm256_blendv_pd (c1, c2, m);
  jbm_sin4xf64_coswc (_mm256_sub_pd (_mm256_set1_pd (M_PI), y), &s2, &c2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (5. * M_PI_4), _CMP_LT_OS);
  s1 = _mm256_blendv_pd (s1, s2, m);
  c1 = _mm256_blendv_pd (c1, _mm256_sub_pd (z, c2), m);
  jbm_sin4xf64_coswc (_mm256_sub_pd (_mm256_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (3. * M_PI_4), _CMP_LT_OS);
  s1 = _mm256_blendv_pd (s1, s2, m);
  c1 = _mm256_blendv_pd (c1, c2, m);
  jbm_sin4xf64_coswc (y, &s2, &c2);
  m = _mm256_cmp_pd (y, _mm256_set1_pd (M_PI_4), _CMP_LT_OS);
  *s = _mm256_blendv_pd (s1, s2, m);
  *c = _mm256_blendv_pd (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_4xf64_sinwc and
 * jbm_4xf64_coswc approximations.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_tan (const __m256d x) ///< __m256d vector.
{
  __m256d s, c;
  jbm_sin4xf64_cos (x, &s, &c);
  return _mm256_div_pd (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m256d).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_atanwc (const __m256d x)
                  ///< __m256d vector \f$\in\left[0,\frac12\right]\f$.
{
  return
    _mm256_mul_pd (x,
                   jbm_4xf64_rational_11_5 (jbm_4xf64_sqr (x), K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_4xf64_atanwc and
 * function (__m256d).
 *
 * \return function value (__m256d in [-pi/2,pi/2]).
 */
static inline __m256d
jbm_4xf64_atan (const __m256d x)        ///< __m256d vector.
{
  __m256d f, ax, m;
  ax = jbm_4xf64_abs (x);
  m = _mm256_cmp_pd (ax, _mm256_set1_pd (1.), _CMP_GT_OS);
  ax = _mm256_blendv_pd (ax, jbm_4xf64_reciprocal (ax), m);
  f = jbm_4xf64_atanwc (ax);
  f = _mm256_blendv_pd (f, _mm256_sub_pd (_mm256_set1_pd (M_PI_2), f), m);
  return jbm_copy4xf64_sign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_4xf64_atan
 * function (__m256d).
 *
 * \return function value (__m256d in [-pi,pi]).
 */
static inline __m256d
jbm_4xf64_atan2 (const __m256d y,       ///< __m256d y component.
                 const __m256d x)       ///< __m256d x component.
{
  const __m256d pi = _mm256_set1_pd (M_PI);
  const __m256d z = _mm256_setzero_pd ();
  __m256d f, g;
  f = jbm_4xf64_atan (_mm256_div_pd (y, x));
  g = _mm256_add_pd (f, jbm_copy4xf64_sign (pi, y));
  return _mm256_blendv_pd (f, g, _mm256_cmp_pd (x, z, _CMP_LT_OS));
}

/**
 * Function to calculate the function asin(x) using the jbm_4xf64_atan function
 * (__m256d).
 *
 * \return function value (__m256d in [-pi/2,pi/2]).
 */
static inline __m256d
jbm_4xf64_asin (const __m256d x)        ///< __m256d number.
{
  return
    jbm_4xf64_atan (_mm256_div_pd
                    (x,
                     _mm256_sqrt_pd (_mm256_fnmadd_pd
                                     (x, x, _mm256_set1_pd (1.)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_4xf64_atan function
 * (__m256d).
 *
 * \return function value (__m256d in [0,pi]).
 */
static inline __m256d
jbm_4xf64_acos (const __m256d x)        ///< __m256d number.
{
  __m256d f;
  f =
    jbm_4xf64_atan (_mm256_div_pd
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
jbm_4xf64_sinh (const __m256d x)        ///< __m256d number.
{
  __m256d f;
  f = jbm_4xf64_exp (x);
  return _mm256_mul_pd (_mm256_set1_pd (0.5),
                        _mm256_sub_pd (f, jbm_4xf64_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_cosh (const __m256d x)        ///< __m256d number.
{
  __m256d f;
  f = jbm_4xf64_exp (x);
  return _mm256_mul_pd (_mm256_set1_pd (0.5),
                        _mm256_add_pd (f, jbm_4xf64_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_tanh (const __m256d x)        ///< __m256d number.
{
  __m256d f, fi;
  f = jbm_4xf64_exp (x);
  fi = jbm_4xf64_reciprocal (f);
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
jbm_4xf64_asinh (const __m256d x)       ///< __m256d number.
{
  return
    jbm_4xf64_log (_mm256_add_pd
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
jbm_4xf64_acosh (const __m256d x)       ///< __m256d number.
{
  return
    jbm_4xf64_log (_mm256_add_pd
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
jbm_4xf64_atanh (const __m256d x)       ///< __m256d number.
{
  __m256d u;
  u = _mm256_set1_pd (1.);
  return _mm256_mul_pd (_mm256_set1_pd (0.5),
                        jbm_4xf64_log (_mm256_div_pd (_mm256_add_pd (u, x),
                                                      _mm256_sub_pd (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m256d)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_erfwc (const __m256d x)
    ///< __m256d vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm256_mul_pd (x, jbm_4xf64_rational_9_4 (jbm_4xf64_sqr (x), K_ERFWC_F64));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m256d)
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_erfcwc (const __m256d x)
    ///< __m256d vector \f$\in\left[1,\infty\right]\f$.
{
  __m256d f, x2;
  x2 = jbm_4xf64_sqr (x);
  f = _mm256_mul_pd (jbm_4xf64_rational_18_10 (jbm_4xf64_reciprocal (x),
                                               K_ERFCWC_F64),
                     _mm256_div_pd (x, jbm_4xf64_exp (x2)));
  return
    _mm256_blendv_pd (f, _mm256_setzero_pd (),
                      _mm256_cmp_pd (x, _mm256_set1_pd (K_ERFC_MAX_F64),
                                     _CMP_GT_OS));
}

/**
 * Function to calculate the function erf(x) using jbm_4xf64_erfwc and
 * jbm_4xf64_erfcwc.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_erf (const __m256d x) ///< __m256d vector.
{
  const __m256d u = _mm256_set1_pd (1.);
  __m256d ax, f;
  ax = jbm_4xf64_abs (x);
  f = jbm_copy4xf64_sign (_mm256_sub_pd (u, jbm_4xf64_erfcwc (ax)), x);
  return _mm256_blendv_pd (f, jbm_4xf64_erfwc (x),
                           _mm256_cmp_pd (ax, u, _CMP_LT_OS));

}

/**
 * Function to calculate the function erfc(x) using jbm_4xf64_erfwc and
 * jbm_4xf64_erfcwc.
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_erfc (const __m256d x)        ///< __m256d vector.
{
  const __m256d u2 = _mm256_set1_pd (2.);
  const __m256d u = _mm256_set1_pd (1.);
  __m256d ax, cwc, wc;
  ax = jbm_4xf64_abs (x);
  cwc = jbm_4xf64_erfcwc (ax);
  wc = _mm256_sub_pd (u, jbm_4xf64_erfwc (x));
  return
    _mm256_blendv_pd
    (_mm256_blendv_pd
     (wc, _mm256_sub_pd (u2, cwc), _mm256_cmp_pd (ax, u, _CMP_GT_OS)), cwc,
     _mm256_cmp_pd (x, u, _CMP_GT_OS));
}

/**
 * Function to calculate the solution of a __m256d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_quadratic_reduced_4xf64 (const __m256d a,
///< __m256d vector of 1st order coefficient of the equations.
                                   const __m256d b,
///< __m256d vector of 0th order coefficient of the equations.
                                   const __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                                   const __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  __m256d ka, kb, k1, k2;
  k1 = _mm256_set1_pd (-0.5);
  ka = _mm256_mul_pd (a, k1);
  kb = _mm256_sqrt_pd (_mm256_sub_pd (jbm_4xf64_sqr (ka), b));
  k1 = _mm256_add_pd (ka, kb);
  k2 = _mm256_sub_pd (ka, kb);
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
jbm_4xf64_solve_quadratic (const __m256d a,
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
  k2 = _mm256_div_pd (jbm_4xf64_opposite (c), b);
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
  l1 = _mm256_sqrt_pd (jbm_4xf64_opposite (k1));
  l0 = _mm256_mul_pd (jbm_4xf64_acos (_mm256_div_pd (k0, k3)), c_3);
  l1 = _mm256_add_pd (l1, l1);
  l2 = _mm256_fmsub_pd (l1, jbm_4xf64_cos (k0), a3);
  l3 = _mm256_fmsub_pd (l1, jbm_4xf64_cos (_mm256_add_pd (l0, c2p_3)), a3);
  l3 = _mm256_blendv_pd (l3, l2,
                         _mm256_or_pd (_mm256_cmp_pd (l2, x1, _CMP_LT_OS),
                                       _mm256_cmp_pd (l2, x2, _CMP_GT_OS)));
  l4 = _mm256_fmsub_pd (l1, jbm_4xf64_cos (_mm256_sub_pd (l0, c2p_3)), a);
  l4 = _mm256_blendv_pd (l4, l3,
                         _mm256_or_pd (_mm256_cmp_pd (l3, x1, _CMP_LT_OS),
                                       _mm256_cmp_pd (l3, x2, _CMP_GT_OS)));
  k1 = _mm256_sqrt_pd (k2);
  l5 = _mm256_add_pd (k0, k1);
  l5 = jbm_4xf64_cbrt (k2);
  k0 = _mm256_sub_pd (k0, k1);
  l5 = _mm256_add_pd (l5, _mm256_sub_pd (jbm_4xf64_cbrt (k0), a3));
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
jbm_4xf64_solve_cubic (const __m256d a,
///< __m256d vector of 3rd order coefficient of the equations.
                       const __m256d b,
///< __m256d vector of 2nd order coefficient of the equations.
                       const __m256d c,
///< __m256d vector of 1st order coefficient of the equations.
                       const __m256d d,
///< __m256d vector of 0th order coefficient of the equations.
                       const __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                       const __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  return
    _mm256_blendv_pd (jbm_solve_cubic_reduced_4xf64 (_mm256_div_pd (b, a),
                                                     _mm256_div_pd (c, a),
                                                     _mm256_div_pd (d, a), x1,
                                                     x2),
                      jbm_4xf64_solve_quadratic (b, c, d, x1, x2),
                      jbm_small_4xf64 (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_4xf64_flux_limiter_total (const __m256d d1 __attribute__((unused)),
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
jbm_4xf64_flux_limiter_null (const __m256d d1 __attribute__((unused)),
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
jbm_4xf64_flux_limiter_centred (const __m256d d1,
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
jbm_4xf64_flux_limiter_superbee (const __m256d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_div_pd (d1, d2);
  r = _mm256_max_pd (_mm256_min_pd (jbm_4xf64_dbl (r), _mm256_set1_pd (1.)),
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
jbm_4xf64_flux_limiter_minmod (const __m256d d1,
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
jbm_4xf64_flux_limiter_VanLeer (const __m256d d1,
                                ///< 1st flux limiter function parameter.
                                const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r, k;
  r = _mm256_div_pd (d1, d2);
  k = jbm_4xf64_abs (r);
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
jbm_4xf64_flux_limiter_VanAlbada (const __m256d d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r, k;
  r = _mm256_div_pd (d1, d2);
  k = jbm_4xf64_sqr (r);
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
jbm_4xf64_flux_limiter_minsuper (const __m256d d1,
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
jbm_4xf64_flux_limiter_supermin (const __m256d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m256d d2)
    ///< 2nd flux limiter function parameter.
{
  __m256d r;
  r = _mm256_div_pd (d1, d2);
  r = _mm256_min_pd (jbm_4xf64_dbl (r), _mm256_set1_pd (1.));
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
jbm_4xf64_flux_limiter_monotonized_central (const __m256d d1,
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
    _mm256_blendv_pd (rm, jbm_4xf64_dbl (r),
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
jbm_4xf64_flux_limiter_mean (const __m256d d1,
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
jbm_4xf64_flux_limiter (const __m256d d1,
                        ///< 1st flux limiter function parameter.
                        const __m256d d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
    ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_4xf64_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_4xf64_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_4xf64_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_4xf64_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_4xf64_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_4xf64_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_4xf64_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_4xf64_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_4xf64_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_4xf64_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_4xf64_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m256d).
 *
 * \return __m256d vector of integral values.
 */
static inline __m256d
jbm_4xf64_integral (__m256d (*f) (__m256d),
                    ///< pointer to the function to integrate.
                    const __m256d x1,   ///< left limit of the interval.
                    const __m256d x2)   ///< right limit of the interval.
{
  __m256d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m256d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm256_set1_pd (0.5);
  dx = _mm256_mul_pd (h, _mm256_sub_pd (x2, x1));
  x = _mm256_mul_pd (h, _mm256_add_pd (x2, x1));
  k = _mm256_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[0]);
  k = _mm256_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm256_set1_pd (JBM_INTEGRAL_GAUSS_B_F64[i]);
      k2 = _mm256_mul_pd (k2, dx);
      f1 = f (_mm256_sub_pd (x, k2));
      f2 = f (_mm256_add_pd (x, k2));
      h = _mm256_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[i]);
      k = _mm256_fmadd_pd (h, _mm256_add_pd (f1, f2), k);
    }
#endif
  return _mm256_mul_pd (k, dx);
}

#ifndef __AVX512F__

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_f32_add (float *xr,   ///< result float array.
                   const float *x1,     ///< 1st addend float array.
                   const float *x2,     ///< 1st addend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, _mm256_add_ps (_mm256_load_ps (x1 + i),
                                            _mm256_load_ps (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_add_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] + x2[i];
}

/**
 * Function to subtract 2 float arrays.
 */
static inline void
jbm_array_f32_sub (float *xr,   ///< result float array.
                   const float *x1,     ///< minuend float array.
                   const float *x2,     ///< subtrahend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, _mm256_sub_ps (_mm256_load_ps (x1 + i),
                                            _mm256_load_ps (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_sub_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] - x2[i];
}

/**
 * Function to multiply a float array by a float number.
 */
static inline void
jbm_array_f32_mul1 (float *xr,  ///< result float array.
                    const float *x1,    ///< multiplier float array.
                    const float x2,     ///< multiplicand float number.
                    const unsigned int n)       ///< number of array elements.
{
  __m256 a8;
  __m128 s4;
  unsigned int i, j;
  i = 0;
  j = n >> 3;
  if (j)
    {
      a8 = _mm256_set1_ps (x2);
      for (; j > 0; --j, i += 8)
        _mm256_store_ps (xr + i, _mm256_mul_ps (_mm256_load_ps (x1 + i), a8));
    }
  j = (n - i) >> 2;
  if (j)
    {
      s4 = _mm_set1_ps (x2);
      for (; j > 0; --j, i += 4)
        _mm_store_ps (xr + i, _mm_mul_ps (_mm_load_ps (x1 + i), s4));
    }
  for (; i < n; ++i)
    xr[i] = x1[i] * x2;
}

/**
 * Function to divide a float array by a float number.
 */
static inline void
jbm_array_f32_div1 (float *xr,  ///< result float array.
                    const float *x1,    ///< dividend float array.
                    const float x2,     ///< divisor float number.
                    const unsigned int n)       ///< number of array elements.
{
  __m256 a8;
  __m128 s4;
  unsigned int i, j;
  i = 0;
  j = n >> 3;
  if (j)
    {
      a8 = _mm256_set1_ps (x2);
      for (; j > 0; --j, i += 8)
        _mm256_store_ps (xr + i, _mm256_div_ps (_mm256_load_ps (x1 + i), a8));
    }
  j = (n - i) >> 1;
  if (j)
    {
      s4 = _mm_set1_ps (x2);
      for (; j > 0; --j, i += 4)
        _mm_store_ps (xr + i, _mm_div_ps (_mm_load_ps (x1 + i), s4));
    }
  for (; i < n; ++i)
    xr[i] = x1[i] / x2;
}

/**
 * Function to multiply 2 float arrays.
 */
static inline void
jbm_array_f32_mul (float *xr,   ///< result float array.
                   const float *x1,     ///< multiplier float array.
                   const float *x2,     ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, _mm256_mul_ps (_mm256_load_ps (x1 + i),
                                            _mm256_load_ps (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_mul_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] * x2[i];
}

/**
 * Function to divide 2 float arrays.
 */
static inline void
jbm_array_f32_div (float *xr,   ///< result float array.
                   const float *x1,     ///< dividend float array.
                   const float *x2,     ///< divisor float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, _mm256_div_ps (_mm256_load_ps (x1 + i),
                                            _mm256_load_ps (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_div_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to calculate the double of a float array.
 */
static inline void
jbm_array_f32_dbl (float *xr,   ///< result float array.
                   const float *xd,     ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, jbm_8xf32_dbl (_mm256_load_ps (xd + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i, jbm_4xf32_dbl (_mm_load_ps (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_f32_dbl (xd[i]);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_sqr (float *xr,   ///< result float array.
                   const float *xd,     ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, jbm_8xf32_sqr (_mm256_load_ps (xd + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i, jbm_4xf32_sqr (_mm_load_ps (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_f32_sqr (xd[i]);
}

/**
 * Function to find the highest element of a float array.
 *
 * \return the highest value.
 */
static inline float
jbm_array_f32_max (const float *xx,     ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  float ax[8] JB_ALIGNED;
  __m256 a8;
  float k;
  unsigned int i, j;
  j = n >> 2;
  if (j)
    {
      a8 = _mm256_load_ps (xx);
      i = 8;
      while (--j > 0)
        {
          a8 = _mm256_max_ps (a8, _mm256_load_ps (xx + i));
          i += 8;
        }
      _mm256_store_ps (ax, a8);
      k = fmaxf (ax[0], ax[1]);
      k = fmaxf (k, ax[2]);
      k = fmaxf (k, ax[3]);
      k = fmaxf (k, ax[4]);
      k = fmaxf (k, ax[5]);
      k = fmaxf (k, ax[6]);
      k = fmaxf (k, ax[7]);
    }
  else
    {
      k = xx[0];
      i = 1;
    }
  while (i < n)
    k = fmaxf (k, xx[i++]);
  return k;
}

/**
 * Function to find the lowest element of a float array.
 *
 * \return the lowest value.
 */
static inline float
jbm_array_f32_min (const float *xx,     ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  float ax[8] JB_ALIGNED;
  __m256 a8;
  float k;
  unsigned int i, j;
  j = n >> 3;
  if (j)
    {
      a8 = _mm256_load_ps (xx);
      i = 8;
      while (--j > 0)
        {
          a8 = _mm256_min_ps (a8, _mm256_load_ps (xx + i));
          i += 8;
        }
      _mm256_store_ps (ax, a8);
      k = fminf (ax[0], ax[1]);
      k = fminf (k, ax[2]);
      k = fminf (k, ax[3]);
      k = fminf (k, ax[4]);
      k = fminf (k, ax[5]);
      k = fminf (k, ax[6]);
      k = fminf (k, ax[7]);
    }
  else
    {
      k = xx[0];
      i = 1;
    }
  while (i < n)
    k = fminf (k, xx[i++]);
  return k;
}

/**
 * Function to find the highest and the lowest elements of a float array.
 */
static inline void
jbm_array_f32_maxmin (const float *xx,  ///< float array.
                      float *max,       ///< the highest value.
                      float *min,       ///< the lowest value.
                      const unsigned int n)     ///< number of array elements.
{
  float ax[8] JB_ALIGNED;
  __m256 a8, amax8, amin8;
  float kmax, kmin;
  unsigned int i, j;
  j = n >> 3;
  if (j)
    {
      amax8 = amin8 = _mm256_load_ps (xx);
      i = 8;
      while (--j > 0)
        {
          a8 = _mm256_load_ps (xx + i);
          amax8 = _mm256_max_ps (amax8, a8);
          amin8 = _mm256_min_ps (amin8, a8);
          i += 8;
        }
      _mm256_store_ps (ax, amax8);
      kmax = fmaxf (ax[0], ax[1]);
      kmax = fmaxf (kmax, ax[2]);
      kmax = fmaxf (kmax, ax[3]);
      kmax = fmaxf (kmax, ax[4]);
      kmax = fmaxf (kmax, ax[5]);
      kmax = fmaxf (kmax, ax[6]);
      kmax = fmaxf (kmax, ax[7]);
      _mm256_store_ps (ax, amin8);
      kmin = fminf (ax[0], ax[1]);
      kmin = fminf (kmin, ax[2]);
      kmin = fminf (kmin, ax[3]);
      kmin = fminf (kmin, ax[4]);
      kmin = fminf (kmin, ax[5]);
      kmin = fminf (kmin, ax[6]);
      kmin = fminf (kmin, ax[7]);
    }
  else
    {
      kmax = kmin = xx[0];
      i = 1;
    }
  while (i < n)
    kmax = fmaxf (kmax, xx[i]), kmin = fminf (kmin, xx[i++]);
  *max = kmax, *min = kmin;
}

/**
 * Function to add 2 double arrays.
 */
static inline void
jbm_array_f64_add (double *xr,  ///< result double array.
                   const double *x1,    ///< 1st addend double array.
                   const double *x2,    ///< 1st addend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, _mm256_add_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_add_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] + x2[i];
}

/**
 * Function to subtract 2 double arrays.
 */
static inline void
jbm_array_f64_sub (double *xr,  ///< result double array.
                   const double *x1,    ///< minuend double array.
                   const double *x2,    ///< subtrahend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, _mm256_sub_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_sub_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] - x2[i];
}

/**
 * Function to multiply a double array by a double number.
 */
static inline void
jbm_array_f64_mul1 (double *xr, ///< result double array.
                    const double *x1,   ///< multiplier double array.
                    const double x2,    ///< multiplicand double number.
                    const unsigned int n)       ///< number of array elements.
{
  __m256d a4;
  __m128d s2;
  unsigned int i, j;
  i = 0;
  j = n >> 2;
  if (j)
    {
      a4 = _mm256_set1_pd (x2);
      for (; j > 0; --j, i += 4)
        _mm256_store_pd (xr + i, _mm256_mul_pd (_mm256_load_pd (x1 + i), a4));
    }
  j = (n - i) >> 1;
  if (j)
    {
      s2 = _mm_set1_pd (x2);
      for (; j > 0; --j, i += 2)
        _mm_store_pd (xr + i, _mm_mul_pd (_mm_load_pd (x1 + i), s2));
    }
  for (; i < n; ++i)
    xr[i] = x1[i] * x2;
}

/**
 * Function to divide a double array by a double number.
 */
static inline void
jbm_array_f64_div1 (double *xr, ///< result double array.
                    const double *x1,   ///< dividend double array.
                    const double x2,    ///< divisor double number.
                    const unsigned int n)       ///< number of array elements.
{
  __m256d a4;
  __m128d s2;
  unsigned int i, j;
  i = 0;
  j = n >> 2;
  if (j)
    {
      a4 = _mm256_set1_pd (x2);
      for (; j > 0; --j, i += 4)
        _mm256_store_pd (xr + i, _mm256_div_pd (_mm256_load_pd (x1 + i), a4));
    }
  j = (n - i) >> 1;
  if (j)
    {
      s2 = _mm_set1_pd (x2);
      for (; j > 0; --j, i += 2)
        _mm_store_pd (xr + i, _mm_div_pd (_mm_load_pd (x1 + i), s2));
    }
  for (; i < n; ++i)
    xr[i] = x1[i] / x2;
}

/**
 * Function to multiply 2 double arrays.
 */
static inline void
jbm_array_f64_mul (double *xr,  ///< result double array.
                   const double *x1,    ///< multiplier double array.
                   const double *x2,    ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, _mm256_mul_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_mul_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] * x2[i];
}

/**
 * Function to divide 2 double arrays.
 */
static inline void
jbm_array_f64_div (double *xr,  ///< result double array.
                   const double *x1,    ///< dividend double array.
                   const double *x2,    ///< divisor double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, _mm256_div_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_div_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to calculate the double of a double array.
 */
static inline void
jbm_array_f64_dbl (double *xr,  ///< result double array.
                   const double *xd,    ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, jbm_4xf64_dbl (_mm256_load_pd (xd + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i, jbm_2xf64_dbl (_mm_load_pd (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_f64_dbl (xd[i]);
}

/**
 * Function to calculate the square of a double array.
 */
static inline void
jbm_array_f64_sqr (double *xr,  ///< result double array.
                   const double *xd,    ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, jbm_4xf64_sqr (_mm256_load_pd (xd + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i, jbm_2xf64_sqr (_mm_load_pd (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_f64_sqr (xd[i]);
}

/**
 * Function to find the highest element of a double array.
 *
 * \return the highest value.
 */
static inline double
jbm_array_f64_max (const double *xx,    ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  double ax[4] JB_ALIGNED;
  __m256d a4;
  double k;
  unsigned int i, j;
  j = n >> 2;
  if (j)
    {
      a4 = _mm256_load_pd (xx);
      i = 4;
      while (--j > 0)
        {
          a4 = _mm256_max_pd (a4, _mm256_load_pd (xx + i));
          i += 4;
        }
      _mm256_store_pd (ax, a4);
      k = fmax (fmax (ax[0], ax[1]), fmax (ax[2], ax[3]));
    }
  else
    {
      k = xx[0];
      i = 1;
    }
  while (i < n)
    k = fmax (k, xx[i++]);
  return k;
}

/**
 * Function to find the lowest element of a double array.
 *
 * \return the lowest value.
 */
static inline double
jbm_array_f64_min (const double *xx,    ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  double ax[4] JB_ALIGNED;
  __m256d a4;
  double k;
  unsigned int i, j;
  j = n >> 2;
  if (j)
    {
      a4 = _mm256_load_pd (xx);
      i = 4;
      while (--j > 0)
        {
          a4 = _mm256_min_pd (a4, _mm256_load_pd (xx + i));
          i += 4;
        }
      _mm256_store_pd (ax, a4);
      k = fmin (fmin (ax[0], ax[1]), fmin (ax[2], ax[3]));
    }
  else
    {
      k = xx[0];
      i = 1;
    }
  while (i < n)
    k = fmin (k, xx[i++]);
  return k;
}

/**
 * Function to find the highest and the lowest elements of a double array.
 */
static inline void
jbm_array_f64_maxmin (const double *xx, ///< double array.
                      double *max,      ///< the highest value.
                      double *min,      ///< the lowest value.
                      const unsigned int n)     ///< number of array elements.
{
  double ax[4] JB_ALIGNED;
  __m256d a4, amax4, amin4;
  double kmax, kmin;
  unsigned int i, j;
  j = n >> 2;
  if (j)
    {
      amax4 = amin4 = _mm256_load_pd (xx);
      i = 4;
      while (--j > 0)
        {
          a4 = _mm256_load_pd (xx + i);
          amax4 = _mm256_max_pd (amax4, a4);
          amin4 = _mm256_min_pd (amin4, a4);
          i += 4;
        }
      _mm256_store_pd (ax, amax4);
      kmax = fmax (fmax (ax[0], ax[1]), fmax (ax[2], ax[3]));
      _mm256_store_pd (ax, amin4);
      kmin = fmin (fmin (ax[0], ax[1]), fmin (ax[2], ax[3]));
    }
  else
    {
      kmax = kmin = xx[0];
      i = 1;
    }
  while (i < n)
    kmax = fmax (kmax, xx[i]), kmin = fmin (kmin, xx[i++]);
  *max = kmax, *min = kmin;
}

#endif

#endif
