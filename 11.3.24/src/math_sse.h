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
 * \file math_sse.h
 * \brief Header file with useful mathematical functions for __m128.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_SSE4__H
#define JB_MATH_SSE4__H 1

#include "math_f32.h"
#include "math_f64.h"

/**
 * union to work with bits in 4 packed float numbers.
 */
typedef union
{
  __m128 x;                     ///< floating point.
  __m128i i;                    ///< bits.
} JBM4xF32;

/**
 * union to work with bits in 2 packed double numbers.
 */
typedef union
{
  __m128d x;                    ///< floating point.
  __m128i i;                    ///< bits.
} JBM2xF64;

// Debug functions

static inline void
print_m128b32 (FILE *file, const char *label, __m128i x)
{
  int y[4] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m128b64 (FILE *file, const char *label, __m128i x)
{
  long long int y[2] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_m128i32 (FILE *file, const char *label, __m128i x)
{
  int y[4] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m128i64 (FILE *file, const char *label, __m128i x)
{
  long long int y[2] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%lld\n", label, i, y[i]);
}

static inline void
print_m128 (FILE *file, const char *label, __m128 x)
{
  float y[4] JB_ALIGNED;
  unsigned int i;
  _mm_store_ps (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m128d (FILE *file, const char *label, __m128d x)
{
  double y[2] JB_ALIGNED;
  unsigned int i;
  _mm_store_pd (y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

#ifndef __FMA__

static inline __m128
_mm_fmadd_ps (const __m128 x, const __m128 y, const __m128 z)
{
  return _mm_add_ps (_mm_mul_ps (x, y), z);
}

static inline __m128
_mm_fmsub_ps (const __m128 x, const __m128 y, const __m128 z)
{
  return _mm_sub_ps (_mm_mul_ps (x, y), z);
}

static inline __m128
_mm_fnmadd_ps (const __m128 x, const __m128 y, const __m128 z)
{
  return _mm_sub_ps (z, _mm_mul_ps (x, y));
}

static inline __m128
_mm_fnmsub_ps (const __m128 x, const __m128 y, const __m128 z)
{
  return _mm_sub_ps (_mm_setzero_ps (), _mm_fmadd_ps (x, y, z));
}

static inline __m128d
_mm_fmadd_pd (const __m128d x, const __m128d y, const __m128d z)
{
  return _mm_add_pd (_mm_mul_pd (x, y), z);
}

static inline __m128d
_mm_fmsub_pd (const __m128d x, const __m128d y, const __m128d z)
{
  return _mm_sub_pd (_mm_mul_pd (x, y), z);
}

static inline __m128d
_mm_fnmadd_pd (const __m128d x, const __m128d y, const __m128d z)
{
  return _mm_sub_pd (z, _mm_mul_pd (x, y));
}

static inline __m128d
_mm_fnmsub_pd (const __m128d x, const __m128d y, const __m128d z)
{
  return _mm_sub_pd (_mm_setzero_pd (), _mm_fmadd_pd (x, y, z));
}

#endif

#ifndef __AVX__

static inline __m128i
_mm_sllv_epi32 (__m128i x, __m128i i)
{
  int xx[4] JB_ALIGNED, ii[4] JB_ALIGNED;
  _mm_store_si128 ((__m128i *) xx, x);
  _mm_store_si128 ((__m128i *) ii, i);
  xx[0] <<= ii[0];
  xx[1] <<= ii[1];
  xx[2] <<= ii[2];
  xx[3] <<= ii[3];
  return _mm_load_si128 ((__m128i *) xx);
}

static inline __m128i
_mm_sllv_epi64 (__m128i x, __m128i i)
{
  long long int xx[2] JB_ALIGNED, ii[2] JB_ALIGNED;
  _mm_store_si128 ((__m128i *) xx, x);
  _mm_store_si128 ((__m128i *) ii, i);
  xx[0] <<= ii[0];
  xx[1] <<= ii[1];
  return _mm_load_si128 ((__m128i *) xx);
}

#endif

/**
 * Function to calculate the additive inverse value of a __m128 vector.
 *
 * \return opposite value vector (__m128).
 */
static inline __m128
jbm_opposite_4xf32 (const __m128 x)     ///< __m128 vector.
{
  JBM4xF32 y;
  y.i = _mm_set1_epi32 ((int) JBM_SIGN_BITS_F32);
  return _mm_xor_ps (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m128 vector.
 *
 * \return reciprocal value vector (__m128).
 */
static inline __m128
jbm_reciprocal_4xf32 (const __m128 x)   ///< __m128 vector.
{
  return _mm_div_ps (_mm_set1_ps (1.f), x);
}

/**
 * Function to calculate the sign of a __m128 vector.
 *
 * \return sign vector (__m128).
 */
static inline __m128
jbm_sign_4xf32 (const __m128 x) ///< __m128 vector.
{
  JBM4xF32 y;
  y.x = x;
  y.i = _mm_and_si128 (y.i, _mm_set1_epi32 ((int) JBM_SIGN_BITS_F32));
  y.i = _mm_or_si128 (y.i, _mm_set1_epi32 ((int) JBM_1_BITS_F32));
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m128 vector.
 *
 * \return absolute value vector (__m128).
 */
static inline __m128
jbm_abs_4xf32 (const __m128 x)  ///< __m128 vector.
{
  JBM4xF32 y;
  y.i = _mm_set1_epi32 ((int) JBM_SIGN_BITS_F32);
  return _mm_andnot_ps (y.x, x);
}

/**
 * Function to copy the sign of a __m128 vector to another __m128 vector.
 *
 * \return __m128 vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m128
jbm_copysign_4xf32 (const __m128 x,
///< __m128 vector to preserve magnitude.
                    const __m128 y)     ///< __m128 vector to preserve sign.
{
  JBM4xF32 ax, sy, m;
  ax.x = jbm_abs_4xf32 (x);
  sy.x = y;
  m.i = _mm_set1_epi32 ((int) JBM_SIGN_BITS_F32);
  ax.i = _mm_or_si128 (ax.i, _mm_and_si128 (sy.i, m.i));
  return ax.x;
}

/**
 * Function to calculate the hypot function (__m128).
 *
 * \return function value vector (__m128).
 */
static inline __m128
jbm_hypot_4xf32 (const __m128 x,        ///< 1st __m128 vector.
                 const __m128 y)        ///< 2nd __m128 vector.
{
  return _mm_sqrt_ps (_mm_fmadd_ps (x, x, _mm_mul_ps (y, y)));
}

/**
 * Function to calculate the rest of a division (__m128).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline __m128
jbm_mod_4xf32 (const __m128 x,  ///< dividend (__m128).
               const __m128 d)  ///< divisor (__m128).
{
  return _mm_fnmadd_ps (_mm_floor_ps (_mm_div_ps (x, d)), d, x);
}

/**
 * Function to implement the standard frexp function (__m128).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m128
jbm_frexp_4xf32 (const __m128 x,        ///< __m128 vector.
                 __m128i *e)    ///< pointer to the extracted exponents vector.
{
  const __m128i b = _mm_set1_epi32 ((int) 0x7f800000u);
  const __m128i zi = _mm_setzero_si128 ();
  JBM4xF32 a, y, y2, z;
  __m128i e4, m1, m2, m3;
  a.x = x;
  y.i = _mm_and_si128 (a.i, b);
  m1 = _mm_cmpeq_epi32 (y.i, b);
  m2 = _mm_cmpeq_epi32 (y.i, zi);
  y2.x = x;
  y2.i = _mm_and_si128 (y2.i, _mm_set1_epi32 ((int) 0x007fffffu));
  m3 = _mm_cmpeq_epi32 (y2.i, zi);
  y2.i = _mm_set1_epi32 ((int) 0x00400000u);
  z.x = _mm_div_ps (x, y2.x);
  z.i = _mm_and_si128 (z.i, b);
  e4 = _mm_blendv_epi8 (_mm_sub_epi32 (_mm_srli_epi32 (y.i, 23),
                                       _mm_set1_epi32 (126)),
                        _mm_sub_epi32 (_mm_srli_epi32 (z.i, 23),
                                       _mm_set1_epi32 (253)), m2);
  y.x = _mm_blendv_ps (y.x, _mm_mul_ps (y2.x, z.x), _mm_castsi128_ps (m2));
  m1 = _mm_or_si128 (m1, _mm_and_si128 (m2, m3));
  e4 = _mm_blendv_epi8 (e4, zi, m1);
  *e = e4;
  return _mm_blendv_ps (_mm_mul_ps (_mm_set1_ps (0.5f), _mm_div_ps (x, y.x)), x,
                        _mm_castsi128_ps (m1));
}

/**
 * Function to calculate a 1st order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, _mm_set1_ps (p[1]), _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_4_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_5_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_6_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_7_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_8_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_9_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_10_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_11_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_12_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_13_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_14_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_15_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_16_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_17_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_18_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_19_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_20_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_21_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_22_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_23_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_24_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_25_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_24_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_26_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_25_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_27_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_26_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_28_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_27_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_polynomial_29_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_polynomial_28_4xf32 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_1_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[1]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_2_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+1st order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_2_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[2]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_3_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_3_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_3_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[3]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_4_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_4_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_4_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_4_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[4]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_5_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_5_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_5_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_5_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_5_4_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[5]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_6_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_6_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_6_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_6_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_6_4_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_6_5_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[6]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_4_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_5_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_7_6_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[7]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_4_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_5_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_6_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_8_7_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[8]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_0_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_1_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_2_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_3_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_4_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_5_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_6_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_7_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_9_8_4xf32 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[9]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_10_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[10]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_11_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[11]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_12_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[12]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_13_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[13]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_14_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[14]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_15_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[15]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_16_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[16]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_17_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[17]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_18_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[18]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_19_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[19]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_20_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[20]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_21_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[21]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_22_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[22]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_23_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[23]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_24_23_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_23_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[24]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_24_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_23_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_23_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_25_24_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_24_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[25]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_25_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_24_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_23_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_23_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_24_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_24_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_26_25_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_25_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[26]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_26_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_25_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_24_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_23_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_23_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_24_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_24_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_25_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_25_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 26),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_27_26_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_26_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[27]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+28th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_27_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_26_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_25_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_24_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_23_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_23_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_24_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_24_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_25_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_25_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 26),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_26_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_26_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 27),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_28_27_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_27_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[28]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+29th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_0_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_polynomial_28_4xf32 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_1_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_1_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_27_4xf32 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_2_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_2_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_26_4xf32 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_3_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_3_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_25_4xf32 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_4_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_4_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_24_4xf32 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_5_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_5_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_23_4xf32 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_6_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_6_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_22_4xf32 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_7_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_7_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_21_4xf32 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_8_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_8_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_20_4xf32 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_9_4xf32 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_9_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_19_4xf32 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_10_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_10_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_18_4xf32 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_11_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_11_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_17_4xf32 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_12_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_12_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_16_4xf32 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_13_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_13_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_15_4xf32 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_14_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_14_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_14_4xf32 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_15_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_15_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_13_4xf32 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_16_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_16_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_12_4xf32 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_17_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_17_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_11_4xf32 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_18_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_18_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_10_4xf32 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_19_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_19_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_9_4xf32 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_20_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_20_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_8_4xf32 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_21_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_21_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_7_4xf32 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_22_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_22_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_6_4xf32 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_23_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_23_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_5_4xf32 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_24_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_24_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_4_4xf32 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_25_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_25_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_3_4xf32 (x, p + 26),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_26_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_26_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_2_4xf32 (x, p + 27),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_27_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_27_4xf32 (x, p),
                     _mm_fmadd_ps (x, jbm_polynomial_1_4xf32 (x, p + 28),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_rational_29_28_4xf32 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_polynomial_28_4xf32 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[29]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m128i).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_exp2n_4xf32 (__m128i e)     ///< exponent vector (__m128i).
{
  __m128 x;
  x = _mm_blendv_ps
    (_mm_castsi128_ps (_mm_sllv_epi32 (_mm_set1_epi32 ((int) 0x00400000u),
                                       _mm_sub_epi32 (_mm_set1_epi32 (-127),
                                                      e))),
     _mm_castsi128_ps (_mm_slli_epi32 (_mm_add_epi32 (e,
                                                      _mm_set1_epi32 (127)),
                                       23)),
     _mm_castsi128_ps (_mm_cmpgt_epi32 (e, _mm_set1_epi32 (-127))));
  x = _mm_blendv_ps (x, _mm_setzero_ps (),
                     _mm_castsi128_ps (_mm_cmplt_epi32 (e,
                                                        _mm_set1_epi32
                                                        (-150))));
  return _mm_blendv_ps (x, _mm_set1_ps (INFINITY),
                        _mm_castsi128_ps (_mm_cmpgt_epi32
                                          (e, _mm_set1_epi32 (127))));
}

/**
 * Function to implement the standard ldexp function (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_ldexp_4xf32 (const __m128 x,        ///< __m128 vector.
                 __m128i e)     ///< exponent vector (__m128i).
{
  return _mm_mul_ps (x, jbm_exp2n_4xf32 (e));
}

/**
 * Function to check small __m128 vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m128
jbm_small_4xf32 (const __m128 x)        ///< __m128d vector.
{
  return _mm_cmplt_ps (jbm_abs_4xf32 (x), _mm_set1_ps (FLT_EPSILON));
}

/**
 * Function to calculate the __m128 vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m128 vector.
 */
static inline __m128
jbm_modmin_4xf32 (const __m128 a,       ///< 1st __m128d vector.
                  const __m128 b)       ///< 2nd __m128d vector.
{
  const __m128 z = _mm_setzero_ps ();
  __m128 aa, ab, y;
  ab = _mm_mul_ps (a, b);
  y = _mm_blendv_ps (a, z, _mm_cmple_ps (ab, z));
  aa = jbm_abs_4xf32 (y);
  ab = jbm_abs_4xf32 (b);
  return _mm_blendv_ps (y, b, _mm_cmpgt_ps (aa, ab));
}

/**
 * Function to interchange 2 __m128 vectors.
 */
static inline void
jbm_change_4xf32 (__m128 *restrict a,   ///< 1st __m128 vector pointer.
                  __m128 *restrict b)   ///< 2nd __m128 vector pointer.
{
  __m128 c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m128 vector.
 *
 * \return __m128 double.
 */
static inline __m128
jbm_dbl_4xf32 (const __m128 x)  ///< __m128d vector.
{
  return _mm_add_ps (x, x);
}

/**
 * Function to calculate the square of the components of a __m128 vector.
 *
 * \return __m128 vector square.
 */
static inline __m128
jbm_sqr_4xf32 (const __m128 x)  ///< __m128 vector.
{
  return _mm_mul_ps (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m128 vectors of 2D points.
 *
 * \return __m128 vector of y-coordinates of the extrapolated points.
 */
static inline __m128
jbm_extrapolate_4xf32 (const __m128 x,
                       ///< __m128 vector of x-coordinates of the extrapolated
                       ///< points.
                       const __m128 x1,
                       ///< __m128 vector of x-coordinates of the 1st points.
                       const __m128 x2,
                       ///< __m128 vector of x-coordinates of the 2nd points.
                       const __m128 y1,
                       ///< __m128 vector of y-coordinates of the 1st points.
                       const __m128 y2)
                     ///< __m128 vector of y-coordinates of the 2nd points.
{
  return _mm_fmadd_ps (_mm_sub_ps (x, x1),
                       _mm_div_ps (_mm_sub_ps (y2, y1),
                                   _mm_sub_ps (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m128 vectors of 2D points.
 *
 * \return __m128 vector of y-coordinates of the interpolated points.
 */
static inline __m128
jbm_interpolate_4xf32 (const __m128 x,
                       ///< __m128 vector of x-coordinates of the interpolated
                       ///< points.
                       const __m128 x1,
                       ///< __m128 vector of x-coordinates of the 1st points.
                       const __m128 x2,
                       ///< __m128 vector of x-coordinates of the 2nd points.
                       const __m128 y1,
                       ///< __m128 vector of y-coordinates of the 1st points.
                       const __m128 y2)
                     ///< __m128 vector of y-coordinates of the 2nd points.
{
  __m128 k;
  k = jbm_extrapolate_4xf32 (x, x1, x2, y1, y2);
  k = _mm_blendv_ps (y1, k, _mm_cmpgt_ps (x, x1));
  return _mm_blendv_ps (y2, k, _mm_cmplt_ps (x, x2));
}

/**
 * Function to calculate the length of a __m128 vector of 2D segments.
 *
 * \return __m128 vector of segment lengths.
 */
static inline __m128
jbm_v2_length_4xf32 (const __m128 x1,
///< __m128 vector of x-coordinates of the 1st points defining the segment.
                     const __m128 y1,
///< __m128 vector of y-coordinates of the 1st points defining the segment.
                     const __m128 x2,
///< __m128 vector of x-coordinates of the 2nd points defining the segment.
                     const __m128 y2)
///< __m128 vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_4xf32 (_mm_sub_ps (x2, x1), _mm_sub_ps (y2, y1));
}

/**
 * Function to calculate the length of a __m128 vector of 3D segments.
 *
 * \return __m128 vector of segment lengths.
 */
static inline __m128
jbm_v3_length_4xf32 (const __m128 x1,
///< __m128 vector of x-coordinates of the 1st points defining the segments.
                     const __m128 y1,
///< __m128 vector of y-coordinates of the 1st points defining the segments.
                     const __m128 z1,
///< __m128 vector of z-coordinates of the 1st points defining the segments.
                     const __m128 x2,
///< __m128 vector of x-coordinates of the 2nd points defining the segments.
                     const __m128 y2,
///< __m128 vector of y-coordinates of the 2nd points defining the segments.
                     const __m128 z2)
///< __m128 vector of z-coordinates of the 2nd points defining the segments.
{
  __m128 dx, dy, dz;
  dx = jbm_sqr_4xf32 (_mm_sub_ps (x2, x1));
  dy = _mm_sub_ps (y2, y1);
  dy = _mm_fmadd_ps (dy, dy, dx);
  dz = _mm_sub_ps (z2, z1);
  return _mm_sqrt_ps (_mm_fmadd_ps (dz, dz, dy));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m128).
 *
 * \return function value.
 */
static inline __m128
jbm_exp2wc_4xf32 (const __m128 x)
                  ///< __m128 vector \f$\in[\frac12,1]\f$.
{
  return jbm_polynomial_5_4xf32 (x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_4xf32 and
 * jbm_exp2n_4xf32 functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_exp2_4xf32 (const __m128 x) ///< __m128 vector.
{
  __m128 y, f;
  y = _mm_floor_ps (x);
  f = _mm_sub_ps (x, y);
  y = jbm_exp2n_4xf32 (_mm_cvtps_epi32 (y));
  return _mm_mul_ps (y, jbm_exp2wc_4xf32 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_4xf32 function
 * (__m128).
 *
 * \return function value.
 */
static inline __m128
jbm_exp_4xf32 (const __m128 x)  ///< __m128 vector.
{
  return jbm_exp2_4xf32 (_mm_mul_ps (x, _mm_set1_ps (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_4xf32
 * function (__m128).
 *
 * \return function value.
 */
static inline __m128
jbm_exp10_4xf32 (const __m128 x)        ///< __m128 vector.
{
  return jbm_exp2_4xf32 (_mm_mul_ps (x, _mm_set1_ps (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_expm1wc_4xf32 (const __m128 x)
///< __m128 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  __m128 x2;
  x2 = jbm_sqr_4xf32 (x);
  x2 = _mm_fmadd_ps (x2, _mm_set1_ps (b4), _mm_set1_ps (b2));
  x2 = _mm_fmadd_ps (x2, x, _mm_set1_ps (b1));
  x2 = _mm_fmadd_ps (x2, x, _mm_set1_ps (1.f));
  return _mm_mul_ps (x, _mm_div_ps (_mm_set1_ps (a1), x2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_4xf32 and
 * jbm_exp_4xf32 functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_expm1_4xf32 (const __m128 x)        ///< __m128 vector.
{
  return _mm_blendv_ps (_mm_sub_ps (jbm_exp_4xf32 (x), _mm_set1_ps (1.f)),
                        jbm_expm1wc_4xf32 (x),
                        _mm_cmplt_ps (jbm_abs_4xf32 (x),
                                      _mm_set1_ps (M_LN2f / 2.f)));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_log2wc_4xf32 (const __m128 x)       ///< __m128 vector.
{
  return jbm_rational_6_3_4xf32 (x, K_LOG2WC_F32);
}

/**
 * Function to calculate the function log_2(x) using jbm_log2wc_4xf32 and
 * jbm_frexp_4xf32 (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_log2_4xf32 (const __m128 x) ///< __m128 vector.
{
  const __m128 z = _mm_setzero_ps ();
  __m128 y;
  __m128i e;
  y = jbm_frexp_4xf32 (x, &e);
  y = _mm_add_ps (jbm_log2wc_4xf32 (y), _mm_cvtepi32_ps (e));
  y = _mm_blendv_ps (_mm_set1_ps (-INFINITY), y, _mm_cmpgt_ps (x, z));
  return _mm_blendv_ps (y, _mm_set1_ps (NAN), _mm_cmplt_ps (x, z));
}

/**
 * Function to calculate the function log(x) using jbm_log2_4xf32 (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_log_4xf32 (const __m128 x)  ///< __m128 vector.
{
  return _mm_mul_ps (jbm_log2_4xf32 (x), _mm_set1_ps (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_4xf32.
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_log10_4xf32 (const __m128 x)        ///< __m128 vector.
{
  return _mm_mul_ps (jbm_log2_4xf32 (x), _mm_set1_ps (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (__m128).
 *
 * \return function value (__m128) (__m128).
 */
static inline __m128
jbm_pown_4xf32 (const __m128 x, ///< __m128 vector.
                const int e)    ///< exponent (int).
{
  __m128 f, xn;
  unsigned int i;
  f = _mm_set1_ps (1.f);
  if (e < 0)
    xn = _mm_div_ps (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_4xf32 (xn))
    if (i & 1)
      f = _mm_mul_ps (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_exp2_4xf32 and
 * jbm_log2_4xf32 functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_pow_4xf32 (const __m128 x,  ///< __m128 vector.
               const float e)   ///< exponent (float).
{
  float f;
  f = floorf (e);
  if (f == e)
    return jbm_pown_4xf32 (x, (int) e);
  return jbm_exp2_4xf32 (_mm_mul_ps (_mm_set1_ps (e), jbm_log2_4xf32 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_4xf32 and
 * jbm_pow_4xf32 functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_cbrt_4xf32 (const __m128 x) ///< __m128 vector.
{
  return jbm_copysign_4xf32 (jbm_pow_4xf32 (jbm_abs_4xf32 (x), 1.f / 3.f), x);
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m128)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_sinwc_4xf32 (const __m128 x)
                 ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm_mul_ps (x, jbm_polynomial_3_4xf32 (jbm_sqr_4xf32 (x), K_SINWC_F32));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m128):
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_coswc_4xf32 (const __m128 x)
                 ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_polynomial_3_4xf32 (jbm_sqr_4xf32 (x), K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_4xf32 approximation (__m128).
 */
static inline void
jbm_sincoswc_4xf32 (const __m128 x,
                    ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m128 *s,  ///< pointer to the sin function value (__m128).
                    __m128 *c)  ///< pointer to the cos function value (__m128).
{
  __m128 s0;
  *s = s0 = jbm_sinwc_4xf32 (x);
  *c = _mm_sqrt_ps (_mm_fnmadd_ps (s0, s0, _mm_set1_ps (1.f)));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_4xf32 and
 * jbm_coswc_4xf32 approximations (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_sin_4xf32 (const __m128 x)  ///< __m128 vector.
{
  const __m128 pi3_2 = _mm_set1_ps (3.f * M_PI_2f);
  const __m128 pi = _mm_set1_ps (M_PIf);
  const __m128 pi_2 = _mm_set1_ps (M_PI_2f);
  const __m128 pi_4 = _mm_set1_ps (M_PI_4f);
  __m128 y, q, l1, l2, m1, m2, m3, y1, y2, y3;
  q = jbm_mod_4xf32 (_mm_add_ps (x, pi_4), _mm_set1_ps (2.f * M_PIf));
  y = _mm_sub_ps (q, pi_4);
  l1 = _mm_cmplt_ps (q, pi);
  l2 = _mm_cmplt_ps (q, pi3_2);
  m1 = _mm_andnot_ps (_mm_cmplt_ps (q, pi_2), l1);
  m2 = _mm_andnot_ps (l1, l2);
  m3 = _mm_andnot_ps (l2, _mm_castsi128_ps (_mm_set1_epi32 (0xffffffff)));
  y1 = _mm_sub_ps (pi_2, y);
  y2 = _mm_sub_ps (pi, y);
  y3 = _mm_sub_ps (pi3_2, y);
  y = _mm_blendv_ps (y, y1, m1);
  y = _mm_blendv_ps (y, y2, m2);
  y = _mm_blendv_ps (y, y3, m3);
  y = _mm_blendv_ps (jbm_sinwc_4xf32 (y), jbm_coswc_4xf32 (y),
                     _mm_or_ps (m1, m3));
  return _mm_blendv_ps (y, jbm_opposite_4xf32 (y), m3);
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_4xf32 and
 * jbm_coswc_4xf32 approximations (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_cos_4xf32 (const __m128 x)  ///< __m128 vector.
{
  const __m128 pi2 = _mm_set1_ps (2.f * M_PIf);
  __m128 y, c;
  y = jbm_mod_4xf32 (x, pi2);
  c = jbm_coswc_4xf32 (_mm_sub_ps (y, pi2));
  c = _mm_blendv_ps (c,
                     jbm_sinwc_4xf32
                     (_mm_sub_ps (y, _mm_set1_ps (3.f * M_PI_2f))),
                     _mm_cmplt_ps (y, _mm_set1_ps (7.f * M_PI_4f)));
  c = _mm_blendv_ps (c,
                     jbm_opposite_4xf32
                     (jbm_coswc_4xf32 (_mm_sub_ps (_mm_set1_ps (M_PIf), y))),
                     _mm_cmplt_ps (y, _mm_set1_ps (5.f * M_PI_4f)));
  c = _mm_blendv_ps (c, jbm_sinwc_4xf32 (_mm_sub_ps (_mm_set1_ps (M_PI_2f), y)),
                     _mm_cmplt_ps (y, _mm_set1_ps (3.f * M_PI_4f)));
  return _mm_blendv_ps (c, jbm_coswc_4xf32 (y),
                        _mm_cmplt_ps (y, _mm_set1_ps (M_PI_4f)));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_sinwc_4xf32 and jbm_coswc_4xf32 approximations (__m128).
 */
static inline void
jbm_sincos_4xf32 (const __m128 x,
                  ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m128 *s,    ///< pointer to the sin function value (__m128).
                  __m128 *c)    ///< pointer to the cos function value (__m128).
{
  const __m128 pi2 = _mm_set1_ps (2.f * M_PIf);
  const __m128 z = _mm_setzero_ps ();
  __m128 y, m, s1, c1, s2, c2;
  y = jbm_mod_4xf32 (x, pi2);
  jbm_sincoswc_4xf32 (_mm_sub_ps (y, pi2), &s1, &c1);
  jbm_sincoswc_4xf32 (_mm_sub_ps (y, _mm_set1_ps (3.f * M_PI_2f)), &c2, &s2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (7.f * M_PI_4f));
  s1 = _mm_blendv_ps (s1, _mm_sub_ps (z, s2), m);
  c1 = _mm_blendv_ps (c1, c2, m);
  jbm_sincoswc_4xf32 (_mm_sub_ps (_mm_set1_ps (M_PIf), y), &s2, &c2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (5.f * M_PI_4f));
  s1 = _mm_blendv_ps (s1, s2, m);
  c1 = _mm_blendv_ps (c1, _mm_sub_ps (z, c2), m);
  jbm_sincoswc_4xf32 (_mm_sub_ps (_mm_set1_ps (M_PI_2f), y), &c2, &s2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (3.f * M_PI_4f));
  s1 = _mm_blendv_ps (s1, s2, m);
  c1 = _mm_blendv_ps (c1, c2, m);
  jbm_sincoswc_4xf32 (y, &s2, &c2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (M_PI_4f));
  *s = _mm_blendv_ps (s1, s2, m);
  *c = _mm_blendv_ps (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_4xf32 function
 * (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_tan_4xf32 (const __m128 x)  ///< __m128 vector.
{
  __m128 s, c;
  jbm_sincos_4xf32 (x, &s, &c);
  return _mm_div_ps (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_atanwc_4xf32 (const __m128 x)
                  ///< __m128 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_ps (x, jbm_rational_5_2_4xf32 (jbm_sqr_4xf32 (x), K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc_4xf32
 * function (__m128).
 *
 * \return function value (in [-pi/2,pi/2]) (__m128).
 */
static inline __m128
jbm_atan_4xf32 (const __m128 x) ///< __m128 vector.
{
  __m128 f, ax, m;
  ax = jbm_abs_4xf32 (x);
  m = _mm_cmpgt_ps (ax, _mm_set1_ps (1.f));
  ax = _mm_blendv_ps (ax, jbm_reciprocal_4xf32 (ax), m);
  f = jbm_atanwc_4xf32 (ax);
  f = _mm_blendv_ps (f, _mm_sub_ps (_mm_set1_ps (M_PI_2f), f), m);
  return jbm_copysign_4xf32 (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_4xf32
 * function (__m128).
 *
 * \return function value (in [-pi,pi]) (__m128).
 */
static inline __m128
jbm_atan2_4xf32 (const __m128 y,        ///< __m128 y component.
                 const __m128 x)        ///< __m128 x component.
{
  const __m128 pi = _mm_set1_ps (M_PIf);
  const __m128 z = _mm_setzero_ps ();
  __m128 f, g;
  f = jbm_atan_4xf32 (_mm_div_ps (y, x));
  g = _mm_add_ps (f, jbm_copysign_4xf32 (pi, y));
  return _mm_blendv_ps (f, g, _mm_cmplt_ps (x, z));
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_4xf32 function
 * (__m128).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline __m128
jbm_asin_4xf32 (const __m128 x) ///< __m128 vector.
{
  return
    jbm_atan_4xf32 (_mm_div_ps
                    (x, _mm_sqrt_ps (_mm_fnmadd_ps (x, x, _mm_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_4xf32 function
 * (__m128).
 *
 * \return function value (in [0,pi]) (__m128).
 */
static inline __m128
jbm_acos_4xf32 (const __m128 x) ///< __m128 vector.
{
  __m128 f;
  f =
    jbm_atan_4xf32 (_mm_div_ps
                    (_mm_sqrt_ps (_mm_fnmadd_ps (x, x, _mm_set1_ps (1.f))), x));
  return _mm_blendv_ps (f, _mm_add_ps (f, _mm_set1_ps (M_PIf)),
                        _mm_cmplt_ps (x, _mm_setzero_ps ()));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_sinh_4xf32 (const __m128 x) ///< __m128 number.
{
  __m128 f;
  f = jbm_exp_4xf32 (x);
  return _mm_mul_ps (_mm_set1_ps (0.5f),
                     _mm_sub_ps (f, jbm_reciprocal_4xf32 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_cosh_4xf32 (const __m128 x) ///< __m128 number.
{
  __m128 f;
  f = jbm_exp_4xf32 (x);
  return _mm_mul_ps (_mm_set1_ps (0.5f),
                     _mm_add_ps (f, jbm_reciprocal_4xf32 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_tanh_4xf32 (const __m128 x) ///< __m128 number.
{
  __m128 f, fi;
  f = jbm_exp_4xf32 (x);
  fi = jbm_reciprocal_4xf32 (f);
  f = _mm_div_ps (_mm_sub_ps (f, fi), _mm_add_ps (f, fi));
  f = _mm_blendv_ps (f, _mm_set1_ps (1.f),
                     _mm_cmpgt_ps (x, _mm_set1_ps (JBM_FLT_MAX_E_EXP)));
  return _mm_blendv_ps (f, _mm_set1_ps (-1.f),
                        _mm_cmplt_ps (x, _mm_set1_ps (-JBM_FLT_MAX_E_EXP)));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_asinh_4xf32 (const __m128 x)        ///< __m128 number.
{
  return
    jbm_log_4xf32 (_mm_add_ps
                   (x, _mm_sqrt_ps (_mm_fmadd_ps (x, x, _mm_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_acosh_4xf32 (const __m128 x)        ///< __m128 number.
{
  return
    jbm_log_4xf32 (_mm_add_ps
                   (x, _mm_sqrt_ps (_mm_fmsub_ps (x, x, _mm_set1_ps (1.f)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_atanh_4xf32 (const __m128 x)        ///< __m128 number.
{
  const __m128 u = _mm_set1_ps (1.f);
  return _mm_mul_ps (_mm_set1_ps (0.5f),
                     jbm_log_4xf32 (_mm_div_ps (_mm_add_ps (u, x),
                                                _mm_sub_ps (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m128)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_erfwc_4xf32 (const __m128 x)
                 ///< __m128 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_ps (x, jbm_polynomial_5_4xf32 (jbm_sqr_4xf32 (x), K_ERFWC_F32));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m128)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_erfcwc_4xf32 (const __m128 x)
                  ///< __m128 vector \f$\in\left[1,\infty\right]\f$.
{
  __m128 f, x2;
  x2 = jbm_sqr_4xf32 (x);
  f = _mm_mul_ps (jbm_rational_8_4_4xf32 (jbm_reciprocal_4xf32 (x),
                                          K_ERFCWC_F32),
                  _mm_div_ps (x, jbm_exp_4xf32 (x2)));
  return _mm_blendv_ps (f, _mm_setzero_ps (),
                        _mm_cmpgt_ps (x, _mm_set1_ps (K_ERFC_MAX_F32)));
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_4xf32 and
 * jbm_erfcwc_4xf32
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_erf_4xf32 (const __m128 x)  ///< __m128 vector.
{
  const __m128 u = _mm_set1_ps (1.f);
  __m128 ax, f;
  ax = jbm_abs_4xf32 (x);
  f = jbm_copysign_4xf32 (_mm_sub_ps (u, jbm_erfcwc_4xf32 (ax)), x);
  return _mm_blendv_ps (f, jbm_erfwc_4xf32 (x), _mm_cmplt_ps (ax, u));

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_4xf32 and
 * jbm_erfcwc_4xf32
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_erfc_4xf32 (const __m128 x) ///< __m128 vector.
{
  const __m128 u2 = _mm_set1_ps (2.f);
  const __m128 u = _mm_set1_ps (1.f);
  __m128 ax, cwc, wc;
  ax = jbm_abs_4xf32 (x);
  cwc = jbm_erfcwc_4xf32 (ax);
  wc = _mm_sub_ps (u, jbm_erfwc_4xf32 (x));
  return
    _mm_blendv_ps
    (_mm_blendv_ps (wc, _mm_sub_ps (u2, cwc), _mm_cmpgt_ps (ax, u)), cwc,
     _mm_cmpgt_ps (x, u));
}

/**
 * Function to calculate the solution of a __m128 vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m128 vector of solution values.
 */
static inline __m128
jbm_solve_quadratic_reduced_4xf32 (__m128 a,
///< __m128 vector of 1st order coefficient of the equations.
                                   __m128 b,
///< __m128 vector of 0th order coefficient of the equations.
                                   const __m128 x1,
///< __m128 vector of left limits of the solution intervals.
                                   const __m128 x2)
///< __m128 vector of right limits of the solution intervals.
{
  __m128 k1, k2;
  k1 = _mm_set1_ps (-0.5f);
  a = _mm_mul_ps (a, k1);
  b = _mm_sqrt_ps (_mm_sub_ps (jbm_sqr_4xf32 (a), b));
  k1 = _mm_add_ps (a, b);
  k2 = _mm_sub_ps (a, b);
  k1 = _mm_blendv_ps (k1, k2, _mm_cmplt_ps (k1, x1));
  return _mm_blendv_ps (k1, k2, _mm_cmpgt_ps (k1, x2));
}

/**
 * Function to calculate the solution of a __m128 vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m128 vector of solution values.
 */
static inline __m128
jbm_solve_quadratic_4xf32 (const __m128 a,
///< __m128 vector of 2nd order coefficient of the equations.
                           const __m128 b,
///< __m128 vector of 1st order coefficient of the equations.
                           const __m128 c,
///< __m128 vector of 0th order coefficient of the equations.
                           const __m128 x1,
///< __m128 vector of left limits of the solution intervals.
                           const __m128 x2)
///< __m128 vector of right limits of the solution intervals.
{
  __m128 k1, k2;
  k1 = jbm_solve_quadratic_reduced_4xf32 (_mm_div_ps (b, a), _mm_div_ps (c, a),
                                          x1, x2);
  k2 = _mm_div_ps (jbm_opposite_4xf32 (c), b);
  return _mm_blendv_ps (k1, k2, jbm_small_4xf32 (a));
}

/**
 * Function to calculate the solution of a __m128 vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m128 vector of solution values.
 */
static inline __m128
jbm_solve_cubic_reduced_4xf32 (const __m128 a,
                               ///< 2nd order coefficient of the equation.
                               const __m128 b,
                               ///< 1st order coefficient of the equation.
                               const __m128 c,
                               ///< 0th order coefficient of the equation.
                               const __m128 x1,
                               ///< left limit of the solution interval.
                               const __m128 x2)
                               ///< right limit of the solution interval.
{
  __m128 a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm_set1_ps (2.f * M_PIf / 3.f);
  c_2 = _mm_set1_ps (0.5f);
  c_3 = _mm_set1_ps (1.f / 3.f);
  a3 = _mm_mul_ps (a, c_3);
  k0 = _mm_mul_ps (a3, a3);
  k1 = _mm_fmsub_ps (b, c_3, k0);
  k0 = _mm_fmsub_ps (_mm_fmsub_ps (b, a3, c), c_2, _mm_mul_ps (a3, k0));
  k3 = _mm_mul_ps (k1, _mm_mul_ps (k1, k1));
  k2 = _mm_fmadd_ps (k0, k0, k3);
  l1 = _mm_sqrt_ps (jbm_opposite_4xf32 (k1));
  l0 = _mm_mul_ps (jbm_acos_4xf32 (_mm_div_ps (k0, k3)), c_3);
  l1 = _mm_add_ps (l1, l1);
  l2 = _mm_fmsub_ps (l1, jbm_cos_4xf32 (k0), a3);
  l3 = _mm_fmsub_ps (l1, jbm_cos_4xf32 (_mm_add_ps (l0, c2p_3)), a3);
  l3 = _mm_blendv_ps (l3, l2,
                      _mm_or_ps (_mm_cmplt_ps (l2, x1), _mm_cmpgt_ps (l2, x2)));
  l4 = _mm_fmsub_ps (l1, jbm_cos_4xf32 (_mm_sub_ps (l0, c2p_3)), a);
  l4 = _mm_blendv_ps (l4, l3,
                      _mm_or_ps (_mm_cmplt_ps (l3, x1), _mm_cmpgt_ps (l3, x2)));
  k1 = _mm_sqrt_ps (k2);
  l5 = _mm_add_ps (k0, k1);
  l5 = jbm_cbrt_4xf32 (k2);
  k0 = _mm_sub_ps (k0, k1);
  l5 = _mm_add_ps (l5, _mm_sub_ps (jbm_cbrt_4xf32 (k0), a3));
  return _mm_blendv_ps (l4, l5, _mm_cmplt_ps (k2, _mm_setzero_ps ()));
}

/**
 * Function to calculate the solution of a __m128 vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m128 vector of solution values.
 */
static inline __m128
jbm_solve_cubic_4xf32 (__m128 a,
///< __m128 vector of 3rd order coefficient of the equations.
                       __m128 b,
///< __m128 vector of 2nd order coefficient of the equations.
                       __m128 c,
///< __m128 vector of 1st order coefficient of the equations.
                       __m128 d,
///< __m128 vector of 0th order coefficient of the equations.
                       __m128 x1,
///< __m128 vector of left limits of the solution intervals.
                       __m128 x2)
///< __m128 vector of right limits of the solution intervals.
{
  return
    _mm_blendv_ps (jbm_solve_cubic_reduced_4xf32 (_mm_div_ps (b, a),
                                                  _mm_div_ps (c, a),
                                                  _mm_div_ps (d, a), x1, x2),
                   jbm_solve_quadratic_4xf32 (b, c, d, x1, x2),
                   jbm_small_4xf32 (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_total_4xf32 (const __m128 d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m128 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm_setzero_ps ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_null_4xf32 (const __m128 d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const __m128 d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm_set1_ps (1.f);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_centred_4xf32 (const __m128 d1,
                                ///< 1st flux limiter function parameter.
                                const __m128 d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm_blendv_ps (_mm_div_ps (d1, d2), _mm_setzero_ps (),
                        jbm_small_4xf32 (d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_superbee_4xf32 (const __m128 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_div_ps (d1, d2);
  r = _mm_max_ps (_mm_min_ps (jbm_dbl_4xf32 (r), _mm_set1_ps (1.f)),
                  _mm_min_ps (r, _mm_set1_ps (2.f)));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_minmod_4xf32 (const __m128 d1,
                               ///< 1st flux limiter function parameter.
                               const __m128 d2)
                             ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_min_ps (_mm_div_ps (d1, d2), _mm_set1_ps (1.f));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_VanLeer_4xf32 (const __m128 d1,
                                ///< 1st flux limiter function parameter.
                                const __m128 d2)
                              ///< 2nd flux limiter function parameter.
{
  __m128 r, k;
  r = _mm_div_ps (d1, d2);
  k = jbm_abs_4xf32 (r);
  r = _mm_div_ps (_mm_add_ps (r, k), _mm_add_ps (_mm_set1_ps (1.f), k));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_VanAlbada_4xf32 (const __m128 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m128 d2)
                                ///< 2nd flux limiter function parameter.
{
  __m128 r, k;
  r = _mm_div_ps (d1, d2);
  k = jbm_sqr_4xf32 (r);
  r = _mm_div_ps (_mm_add_ps (r, k), _mm_add_ps (_mm_set1_ps (1.f), k));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_minsuper_4xf32 (const __m128 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_min_ps (_mm_div_ps (d1, d2), _mm_set1_ps (2.f));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_supermin_4xf32 (const __m128 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128 d2)
                                 ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_div_ps (d1, d2);
  r = _mm_min_ps (jbm_dbl_4xf32 (r), _mm_set1_ps (1.f));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_monotonized_central_4xf32 (const __m128 d1,
///< 1st flux limiter function parameter.
                                            const __m128 d2)
///< 2nd flux limiter function parameter.
{
  __m128 r, rm;
  r = _mm_div_ps (d1, d2);
  rm = _mm_mul_ps (_mm_set1_ps (0.5f), _mm_add_ps (r, _mm_set1_ps (1.f)));
  rm = _mm_blendv_ps (_mm_set1_ps (2.f), rm,
                      _mm_cmplt_ps (r, _mm_set1_ps (3.f)));
  rm = _mm_blendv_ps (rm, jbm_dbl_4xf32 (r),
                      _mm_cmpgt_ps (r, _mm_set1_ps (1.f / 3.f)));
  return _mm_blendv_ps (_mm_setzero_ps (), rm,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_mean_4xf32 (const __m128 d1,
                             ///< 1st flux limiter function parameter.
                             const __m128 d2)
                           ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_mul_ps (_mm_set1_ps (0.5f),
                  _mm_add_ps (_mm_set1_ps (1.f), _mm_div_ps (d1, d2)));
  return _mm_blendv_ps (_mm_setzero_ps (), r,
                        _mm_cmpgt_ps (_mm_mul_ps (d1, d2),
                                      _mm_set1_ps (FLT_EPSILON)));
}

/**
 * Function to do a flux limiter function (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_flux_limiter_4xf32 (const __m128 d1,
                        ///< 1st flux limiter function parameter.
                        const __m128 d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_4xf32 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_4xf32 (d1, d2);
    }
  return jbm_flux_limiter_mean_4xf32 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m128).
 *
 * \return __m128 vector of integral values.
 */
static inline __m128
jbm_integral_4xf32 (__m128 (*f) (__m128),
                    ///< pointer to the function to integrate.
                    const __m128 x1,    ///< left limit of the interval.
                    const __m128 x2)    ///< right limit of the interval.
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
  __m128 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m128 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm_set1_ps (0.5f);
  dx = _mm_mul_ps (h, _mm_sub_ps (x2, x1));
  x = _mm_mul_ps (h, _mm_add_ps (x2, x1));
  k = _mm_set1_ps (a[0]);
  k = _mm_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm_set1_ps (b[i]);
      k2 = _mm_mul_ps (k2, dx);
      f1 = f (_mm_sub_ps (x, k2));
      f2 = f (_mm_add_ps (x, k2));
      h = _mm_set1_ps (a[i]);
      k = _mm_fmadd_ps (h, _mm_add_ps (f1, f2), k);
    }
#endif
  k = _mm_mul_ps (k, dx);
  return k;
}

/**
 * Function to calculate the additive inverse value of a __m128d vector.
 *
 * \return negative value vector (__m128d).
 */
static inline __m128d
jbm_opposite_2xf64 (const __m128d x)    ///< __m128d vector.
{
  JBM2xF64 y;
  y.i = _mm_set1_epi64 ((__m64) JBM_SIGN_BITS_F64);
  return _mm_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m128d vector.
 *
 * \return reciprocal value vector (__m128d).
 */
static inline __m128d
jbm_reciprocal_2xf64 (const __m128d x)  ///< __m128d vector.
{
  return _mm_div_pd (_mm_set1_pd (1.), x);
}

/**
 * Function to calculate the sign of a __m128d vector.
 *
 * \return sign vector (__m128d).
 */
static inline __m128d
jbm_sign_2xf64 (const __m128d x)        ///< __m128d vector.
{
  JBM2xF64 y;
  y.x = x;
  y.i = _mm_and_si128 (y.i, _mm_set1_epi64 ((__m64) JBM_SIGN_BITS_F64));
  y.i = _mm_and_si128 (y.i, _mm_set1_epi64 ((__m64) JBM_1_BITS_F64));
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m128d vector.
 *
 * \return absolute value vector.
 */
static inline __m128d
jbm_abs_2xf64 (const __m128d x)
{
  JBM2xF64 y;
  y.i = _mm_set1_epi64 ((__m64) JBM_SIGN_BITS_F64);
  return _mm_andnot_pd (y.x, x);
}

/**
 * Function to copy the sign of a __m128d vector to another __m128d vector.
 *
 * \return __m128d vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m128d
jbm_copysign_2xf64 (const __m128d x,
///< __m128 vector to preserve magnitude.
                    const __m128d y)    ///< __m128d vector to preserve sign.
{
  JBM2xF64 ax, sy, m;
  ax.x = jbm_abs_2xf64 (x);
  sy.x = y;
  m.i = _mm_set1_epi64 ((__m64) JBM_SIGN_BITS_F64);
  ax.x = _mm_or_pd (ax.x, _mm_and_pd (sy.x, m.x));
  return ax.x;
}

/**
 * Function to calculate the hypot function (__m128d).
 *
 * \return function value vector (__m128d).
 */
static inline __m128d
jbm_hypot_2xf64 (const __m128d x,       ///< 1st __m128d vector.
                 const __m128d y)       ///< 2nd __m128d vector.
{
  return _mm_sqrt_pd (_mm_fmadd_pd (x, x, _mm_mul_pd (y, y)));
}

/**
 * Function to calculate the rest of a division (__m128d).
 *
 * \return rest value (in [0,|divisor|) interval) (__m128d).
 */
static inline __m128d
jbm_mod_2xf64 (const __m128d x, ///< dividend (__m128d).
               const __m128d d) ///< divisor (__m128d).
{
  return _mm_fnmadd_pd (_mm_floor_pd (_mm_div_pd (x, d)), d, x);
}

/**
 * Function to implement the standard frexp function (__m128d).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m128d
jbm_frexp_2xf64 (const __m128d x,       ///< __m128d vector.
                 __m128i *e)    ///< pointer to the extracted exponents vector.
{
  const __m128i b = _mm_set1_epi64 ((__m64) 0x7ff0000000000000ull);
  const __m128i zi = _mm_setzero_si128 ();
  JBM2xF64 a, y, y2, z;
  __m128i e2, m1, m2, m3;
  a.x = x;
  y.i = _mm_and_si128 (a.i, b);
  m1 = _mm_cmpeq_epi64 (y.i, b);
  m2 = _mm_cmpeq_epi64 (y.i, zi);
  y2.x = x;
  y2.i = _mm_and_si128 (y2.i, _mm_set1_epi64 ((__m64) 0x000fffffffffffffull));
  m3 = _mm_cmpeq_epi64 (y2.i, zi);
  y2.i = _mm_set1_epi64 ((__m64) 0x0010000000000000ull);
  z.x = _mm_div_pd (x, y2.x);
  z.i = _mm_and_si128 (z.i, b);
  e2 = _mm_blendv_epi8 (_mm_sub_epi64 (_mm_srli_epi64 (y.i, 52),
                                       _mm_set1_epi64 ((__m64) 1022ll)),
                        _mm_sub_epi64 (_mm_srli_epi64 (z.i, 52),
                                       _mm_set1_epi64 ((__m64) 2044ll)), m2);
  y.x = _mm_blendv_pd (y.x, _mm_mul_pd (y2.x, z.x), _mm_castsi128_pd (m2));
  m1 = _mm_or_si128 (m1, _mm_and_si128 (m2, m3));
  e2 = _mm_blendv_epi8 (e2, zi, m1);
  *e = e2;
  return _mm_blendv_pd (_mm_mul_pd (_mm_set1_pd (0.5), _mm_div_pd (x, y.x)), x,
                        _mm_castsi128_pd (m1));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m128i)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_exp2n_2xf64 (__m128i e)     ///< exponent vector (__m128i).
{
  __m128d x;
  x = _mm_blendv_pd
    (_mm_castsi128_pd
     (_mm_sllv_epi64
      (_mm_set1_epi64 ((__m64) 0x0008000000000000ull),
       _mm_sub_epi64 (_mm_set1_epi64 ((__m64) - 1023ll), e))),
     _mm_castsi128_pd
     (_mm_slli_epi64 (_mm_add_epi64 (e, _mm_set1_epi64 ((__m64) 1023ll)), 52)),
     _mm_castsi128_pd (_mm_cmpgt_epi64 (e, _mm_set1_epi64 ((__m64) - 1023ll))));
  x =
    _mm_blendv_pd
    (x, _mm_setzero_pd (),
     _mm_castsi128_pd (_mm_cmpgt_epi64 (_mm_set1_epi64 ((__m64) - 1074ll), e)));
  return
    _mm_blendv_pd
    (x, _mm_set1_pd (INFINITY),
     _mm_castsi128_pd (_mm_cmpgt_epi64 (e, _mm_set1_epi64 ((__m64) 1023ll))));
}

/**
 * Function to implement the standard ldexp function (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_ldexp_2xf64 (const __m128d x,       ///< __m128d vector.
                 __m128i e)     ///< exponent vector (__m128i).
{
  return _mm_mul_pd (x, jbm_exp2n_2xf64 (e));
}

/**
 * Function to check small __m128d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m128d
jbm_small_2xf64 (const __m128d x)       ///< __m128d vector.
{
  return _mm_cmplt_pd (jbm_abs_2xf64 (x), _mm_set1_pd (FLT_EPSILON));
}

/**
 * Function to calculate the __m128d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m128d vector.
 */
static inline __m128d
jbm_modmin_2xf64 (const __m128d a,      ///< 1st __m128d vector.
                  const __m128d b)      ///< 2nd __m128d vector.
{
  const __m128d z = _mm_setzero_pd ();
  __m128d aa, ab, y;
  ab = _mm_mul_pd (a, b);
  y = _mm_blendv_pd (a, z, _mm_cmple_pd (ab, z));
  aa = jbm_abs_2xf64 (y);
  ab = jbm_abs_2xf64 (b);
  return _mm_blendv_pd (y, b, _mm_cmpgt_pd (aa, ab));
}

/**
 * Function to interchange 2 __m128d numbers.
 */
static inline void
jbm_change_2xf64 (__m128d *restrict a,  ///< 1st __m128d vector pointer.
                  __m128d *restrict b)  ///< 2nd __m128d vector pointer.
{
  __m128d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m128d vector.
 *
 * \return __m128d double.
 */
static inline __m128d
jbm_dbl_2xf64 (const __m128d x) ///< __m128d vector.
{
  return _mm_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m128d vector.
 *
 * \return __m128d vector square.
 */
static inline __m128d
jbm_sqr_2xf64 (const __m128d x) ///< __m128d vector.
{
  return _mm_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m128d vectors of 2D points.
 *
 * \return __m128d vector of y-coordinates of the extrapolated points.
 */
static inline __m128d
jbm_extrapolate_2xf64 (const __m128d x,
                       ///< __m128d vector of x-coordinates of the extrapolated
                       ///< points.
                       const __m128d x1,
                       ///< __m128d vector of x-coordinates of the 1st points.
                       const __m128d x2,
                       ///< __m128d vector of x-coordinates of the 2nd points.
                       const __m128d y1,
                       ///< __m128d vector of y-coordinates of the 1st points.
                       const __m128d y2)
                     ///< __m128d vector of y-coordinates of the 2nd points.
{
  __m128d d;
  d = _mm_sub_pd (x, x1);
  return _mm_fmadd_pd (d, _mm_div_pd (_mm_sub_pd (y2, y1),
                                      _mm_sub_pd (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m128d vectors of 2D points.
 *
 * \return __m128d vector of y-coordinates of the interpolated points.
 */
static inline __m128d
jbm_interpolate_2xf64 (const __m128d x,
                       ///< __m128d vector of x-coordinates of the interpolated
                       ///< points.
                       const __m128d x1,
                       ///< __m128d vector of x-coordinates of the 1st points.
                       const __m128d x2,
                       ///< __m128d vector of x-coordinates of the 2nd points.
                       const __m128d y1,
                       ///< __m128d vector of y-coordinates of the 1st points.
                       const __m128d y2)
                     ///< __m128d vector of y-coordinates of the 2nd points.
{
  __m128d k;
  k = jbm_extrapolate_2xf64 (x, x1, x2, y1, y2);
  k = _mm_blendv_pd (y1, k, _mm_cmpgt_pd (x, x1));
  return _mm_blendv_pd (y2, k, _mm_cmplt_pd (x, x2));
}

/**
 * Function to calculate the length of a __m128d vector of 2D segments.
 *
 * \return __m128d vector of segment lengths.
 */
static inline __m128d
jbm_v2_length_2xf64 (const __m128d x1,
///< __m128d vector of x-coordinates of the 1st points defining the segment.
                     const __m128d y1,
///< __m128d vector of y-coordinates of the 1st points defining the segment.
                     const __m128d x2,
///< __m128d vector of x-coordinates of the 2nd points defining the segment.
                     const __m128d y2)
///< __m128d vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_2xf64 (_mm_sub_pd (x2, x1), _mm_sub_pd (y2, y1));
}

/**
 * Function to calculate the length of a __m128d vector of 3D segments.
 *
 * \return __m128d vector of segment lengths.
 */
static inline __m128d
jbm_v3_length_2xf64 (const __m128d x1,
///< __m128d vector of x-coordinates of the 1st points defining the segments.
                     const __m128d y1,
///< __m128d vector of y-coordinates of the 1st points defining the segments.
                     const __m128d z1,
///< __m128d vector of z-coordinates of the 1st points defining the segments.
                     const __m128d x2,
///< __m128d vector of x-coordinates of the 2nd points defining the segments.
                     const __m128d y2,
///< __m128d vector of y-coordinates of the 2nd points defining the segments.
                     const __m128d z2)
///< __m128d vector of z-coordinates of the 2nd points defining the segments.
{
  __m128d dx, dy, dz;
  dx = jbm_sqr_2xf64 (_mm_sub_pd (x2, x1));
  dy = _mm_sub_pd (y2, y1);
  dy = _mm_fmadd_pd (dy, dy, dx);
  dz = _mm_sub_pd (z2, z1);
  return _mm_sqrt_pd (_mm_fmadd_pd (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 2nd order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_4_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_5_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_6_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_7_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_8_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_9_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_10_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_11_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_12_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_13_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_14_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_15_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_16_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_17_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_18_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_19_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_20_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_21_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_22_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_23_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_24_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_25_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_24_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_26_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_25_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_27_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_26_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_28_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_27_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_29_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_polynomial_28_2xf64 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_1_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_2_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+1st order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_2_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[2]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_3_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_3_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_3_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[3]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_4_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_4_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_4_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_4_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[4]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_5_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_5_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_5_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_5_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_5_4_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[5]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_6_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_6_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_6_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_6_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_6_4_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_6_5_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[6]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_4_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_5_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_7_6_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[7]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_4_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_5_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_6_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_8_7_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[8]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_0_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_1_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_2_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_3_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_4_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_5_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_6_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_7_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_9_8_2xf64 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[9]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_10_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[10]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_11_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[11]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_12_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[12]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_13_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[13]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_14_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[14]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_15_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[15]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_16_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[16]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_17_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[17]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_18_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[18]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_19_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[19]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_20_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[20]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_21_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[21]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_22_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[22]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_23_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[23]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_24_23_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_23_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[24]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_24_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_23_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_23_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_25_24_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_24_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[25]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_25_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_24_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_23_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_23_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_24_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_24_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_26_25_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_25_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[26]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_26_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_25_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_24_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_23_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_23_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_24_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_24_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_25_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_25_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 26),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_27_26_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_26_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[27]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+28th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_27_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_26_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_25_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_24_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_23_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_23_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_24_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_24_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_25_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_25_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 26),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_26_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_26_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 27),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_28_27_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_27_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[28]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+29th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_0_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_polynomial_28_2xf64 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_1_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_1_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_27_2xf64 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_2_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_2_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_26_2xf64 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_3_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_3_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_25_2xf64 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_4_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_4_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_24_2xf64 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_5_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_5_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_23_2xf64 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_6_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_6_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_22_2xf64 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_7_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_7_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_21_2xf64 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_8_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_8_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_20_2xf64 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_9_2xf64 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_9_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_19_2xf64 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_10_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_10_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_18_2xf64 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_11_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_11_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_17_2xf64 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_12_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_12_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_16_2xf64 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_13_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_13_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_15_2xf64 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_14_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_14_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_14_2xf64 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_15_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_15_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_13_2xf64 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_16_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_16_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_12_2xf64 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_17_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_17_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_11_2xf64 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_18_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_18_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_10_2xf64 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_19_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_19_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_9_2xf64 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_20_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_20_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_8_2xf64 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_21_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_21_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_7_2xf64 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_22_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_22_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_6_2xf64 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_23_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_23_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_5_2xf64 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_24_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_24_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_4_2xf64 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_25_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_25_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_3_2xf64 (x, p + 26),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_26_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_26_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_2_2xf64 (x, p + 27),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_27_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_27_2xf64 (x, p),
                     _mm_fmadd_pd (x, jbm_polynomial_1_2xf64 (x, p + 28),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_rational_29_28_2xf64 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_polynomial_28_2xf64 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[29]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_expm1wc_2xf64 (const __m128d x)
///< __m128d vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return _mm_mul_pd (x, jbm_rational_8_2_2xf64 (x, K_EXPM1WC_F64));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m128d).
 *
 * \return function value.
 */
static inline __m128d
jbm_exp2wc_2xf64 (const __m128d x)
                  ///< __m128d vector \f$\in[\frac12,1]\f$.
{
  return jbm_rational_9_4_2xf64 (x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_2xf64 and
 * jbm_exp2n_2xf64 functions.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_exp2_2xf64 (const __m128d x)        ///< __m128d vector.
{
  __m128d y, f, z;
#ifndef __AVX512F__
  __m128d k;
#endif
  __m128i i;
  y = _mm_floor_pd (x);
  f = _mm_sub_pd (x, y);
#ifdef __AVX512F__
  i = _mm_cvtpd_epi64 (y);
  z = jbm_exp2n_2xf64 (i);
#else
  z = _mm_set1_pd (0x0018000000000000ull);
  k = _mm_add_pd (y, z);
  i = _mm_sub_epi64 (_mm_castpd_si128 (k), _mm_castpd_si128 (z));
  z = _mm_blendv_pd (jbm_exp2n_2xf64 (i), _mm_setzero_pd (),
                     _mm_cmplt_pd (y, _mm_set1_pd (-1074.)));
#endif
  return _mm_mul_pd (z, jbm_exp2wc_2xf64 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_2xf64 function.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_exp_2xf64 (const __m128d x) ///< __m128d vector.
{
  return jbm_exp2_2xf64 (_mm_mul_pd (x, _mm_set1_pd (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_2xf64
 * function (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_exp10_2xf64 (const __m128d x)       ///< __m128d vector.
{
  return jbm_exp2_2xf64 (_mm_mul_pd (x, _mm_set1_pd (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_2xf64 and
 * jbm_exp_2xf64 functions (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_expm1_2xf64 (const __m128d x)       ///< __m128d vector.
{
  return _mm_blendv_pd (_mm_sub_pd (jbm_exp_2xf64 (x), _mm_set1_pd (1.)),
                        jbm_expm1wc_2xf64 (x),
                        _mm_cmplt_pd (jbm_abs_2xf64 (x),
                                      _mm_set1_pd (M_LN2 / 2.)));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_log2wc_2xf64 (const __m128d x)      ///< __m128d vector \f$\in[0.5,1]\f$.
{
  return jbm_rational_12_6_2xf64 (x, K_LOG2WC_F64);
}

/**
 * Function to calculate the function log2(x) using jbm_logwc_2xf64 and
 * jbm_frexp_2xf64
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_log2_2xf64 (const __m128d x)        ///< __m128d vector.
{
  __m128d y, z;
  __m128i e;
  y = jbm_log2wc_2xf64 (jbm_frexp_2xf64 (x, &e));
#ifdef __AVX512F__
  z = _mm_cvtepi64_pd (e);
#else
  z = _mm_set1_pd (0x0018000000000000ull);
  e = _mm_add_epi64 (e, _mm_castpd_si128 (z));
  z = _mm_sub_pd (_mm_castsi128_pd (e), z);
#endif
  y = _mm_add_pd (y, z);
  z = _mm_setzero_pd ();
  y = _mm_blendv_pd (y, _mm_set1_pd (-INFINITY), _mm_cmpgt_pd (x, z));
  return _mm_blendv_pd (_mm_set1_pd (NAN), y, _mm_cmplt_pd (x, z));
}

/**
 * Function to calculate the function log(x) using jbm_log2_2xf64 (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_log_2xf64 (const __m128d x) ///< __m128d vector.
{
  return _mm_mul_pd (jbm_log2_2xf64 (x), _mm_set1_pd (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_2xf64 (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_log10_2xf64 (const __m128d x)       ///< __m128d vector.
{
  return _mm_mul_pd (jbm_log2_2xf64 (x), _mm_set1_pd (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (__m128d).
 *
 * \return function value (__m128d) (__m128d).
 */
static inline __m128d
jbm_pown_2xf64 (const __m128d x,        ///< __m128d vector.
                const int e)    ///< exponent (int).
{
  __m128d f, xn;
  unsigned int i;
  f = _mm_set1_pd (1.);
  if (e < 0)
    xn = _mm_div_pd (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_2xf64 (xn))
    if (i & 1)
      f = _mm_mul_pd (f, xn);
  return f;
}

/**
 * Function to calculate the function f32 using the jbm_exp2_2xf64 and
 * jbm_log2_2xf64 functions.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_pow_2xf64 (const __m128d x, ///< __m128d vector.
               const double e)  ///< exponent (__m128d).
{
  double f;
  f = floor (e);
  if (f == e)
    return jbm_pown_2xf64 (x, (int) e);
  return jbm_exp2_2xf64 (_mm_mul_pd (_mm_set1_pd (e), jbm_log2_2xf64 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_2xf64 and
 * jbm_pow_2xf64 functions (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_cbrt_2xf64 (const __m128d x)        ///< __m128d vector.
{
  return jbm_copysign_2xf64 (jbm_pow_2xf64 (jbm_abs_2xf64 (x), 1. / 3.), x);
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m128d)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_sinwc_2xf64 (const __m128d x)
                 ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm_mul_pd (x, jbm_polynomial_6_2xf64 (jbm_sqr_2xf64 (x), K_SINWC_F64));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_coswc_2xf64 (const __m128d x)
                 ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_polynomial_6_2xf64 (jbm_sqr_2xf64 (x), K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_2xf64 approximation (__m128d).
 */
static inline void
jbm_sincoswc_2xf64 (const __m128d x,
                    ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m128d *s,
                    ///< pointer to the f32 function value (__m128d).
                    __m128d *c)
                    ///< pointer to the f32 function value (__m128d).
{
  __m128d s0;
  *s = s0 = jbm_sinwc_2xf64 (x);
  *c = _mm_sqrt_pd (_mm_fnmadd_pd (x, x, _mm_set1_pd (1.)));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_2xf64 and
 * jbm_coswc_2xf64 approximations.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_sin_2xf64 (const __m128d x) ///< __m128d vector.
{
  const __m128d pi2 = _mm_set1_pd (2. * M_PI);
  __m128d y, s;
  y = jbm_mod_2xf64 (x, pi2);
  s = jbm_sinwc_2xf64 (_mm_sub_pd (y, pi2));
  s = _mm_blendv_pd (s,
                     jbm_opposite_2xf64
                     (jbm_coswc_2xf64
                      (_mm_sub_pd (_mm_set1_pd (3. * M_PI_2), y))),
                     _mm_cmplt_pd (y, _mm_set1_pd (7. * M_PI_4)));
  s = _mm_blendv_pd (s, jbm_sinwc_2xf64 (_mm_sub_pd (_mm_set1_pd (M_PI), y)),
                     _mm_cmplt_pd (y, _mm_set1_pd (5. * M_PI_4)));
  s = _mm_blendv_pd (s, jbm_coswc_2xf64 (_mm_sub_pd (_mm_set1_pd (M_PI_2), y)),
                     _mm_cmplt_pd (y, _mm_set1_pd (3. * M_PI_4)));
  return _mm_blendv_pd (s, jbm_sinwc_2xf64 (y),
                        _mm_cmplt_pd (y, _mm_set1_pd (M_PI_4)));
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_2xf64 and
 * jbm_coswc_2xf64 approximations (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_cos_2xf64 (const __m128d x) ///< __m128d vector.
{
  const __m128d pi2 = _mm_set1_pd (2. * M_PI);
  __m128d y, c;
  y = jbm_mod_2xf64 (x, pi2);
  c = jbm_coswc_2xf64 (_mm_sub_pd (y, pi2));
  c = _mm_blendv_pd (c,
                     jbm_sinwc_2xf64
                     (_mm_sub_pd (y, _mm_set1_pd (3. * M_PI_2))),
                     _mm_cmplt_pd (y, _mm_set1_pd (7. * M_PI_4)));
  c = _mm_blendv_pd (c,
                     jbm_opposite_2xf64
                     (jbm_coswc_2xf64 (_mm_sub_pd (_mm_set1_pd (M_PI), y))),
                     _mm_cmplt_pd (y, _mm_set1_pd (5. * M_PI_4)));
  c = _mm_blendv_pd (c, jbm_sinwc_2xf64 (_mm_sub_pd (_mm_set1_pd (M_PI_2), y)),
                     _mm_cmplt_pd (y, _mm_set1_pd (3. * M_PI_4)));
  return _mm_blendv_pd (c, jbm_coswc_2xf64 (y),
                        _mm_cmplt_pd (y, _mm_set1_pd (M_PI_4)));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sinwc_2xf64
 * and jbm_coswc_2xf64 approximations (__m128d).
 */
static inline void
jbm_sincos_2xf64 (const __m128d x,
                  ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m128d *s,   ///< pointer to the f32 function value (__m128d).
                  __m128d *c)   ///< pointer to the f32 function value (__m128d).
{
  const __m128d pi2 = _mm_set1_pd (2. * M_PI);
  const __m128d z = _mm_setzero_pd ();
  __m128d y, m, s1, c1, s2, c2;
  y = jbm_mod_2xf64 (x, pi2);
  jbm_sincoswc_2xf64 (_mm_sub_pd (y, pi2), &s1, &c1);
  jbm_sincoswc_2xf64 (_mm_sub_pd (y, _mm_set1_pd (3. * M_PI_2)), &c2, &s2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (7. * M_PI_4));
  s1 = _mm_blendv_pd (s1, _mm_sub_pd (z, s2), m);
  c1 = _mm_blendv_pd (c1, c2, m);
  jbm_sincoswc_2xf64 (_mm_sub_pd (_mm_set1_pd (M_PI), y), &s2, &c2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (5. * M_PI_4));
  s1 = _mm_blendv_pd (s1, s2, m);
  c1 = _mm_blendv_pd (c1, _mm_sub_pd (z, c2), m);
  jbm_sincoswc_2xf64 (_mm_sub_pd (_mm_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (3. * M_PI_4));
  s1 = _mm_blendv_pd (s1, s2, m);
  c1 = _mm_blendv_pd (c1, c2, m);
  jbm_sincoswc_2xf64 (y, &s2, &c2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (M_PI_4));
  *s = _mm_blendv_pd (s1, s2, m);
  *c = _mm_blendv_pd (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_sinwc_2xf64 and
 * jbm_coswc_2xf64 approximations.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_tan_2xf64 (const __m128d x) ///< __m128d vector.
{
  __m128d s, c;
  jbm_sincos_2xf64 (x, &s, &c);
  return _mm_div_pd (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_atanwc_2xf64 (const __m128d x)
                  ///< __m128d vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_pd (x, jbm_rational_11_5_2xf64 (jbm_sqr_2xf64 (x), K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc_2xf64
 * function (__m128d).
 *
 * \return function value (__m128d in [-pi/2,pi/2]).
 */
static inline __m128d
jbm_atan_2xf64 (const __m128d x)        ///< double number.
{
  __m128d f, ax, m;
  ax = jbm_abs_2xf64 (x);
  m = _mm_cmpgt_pd (ax, _mm_set1_pd (1.));
  ax = _mm_blendv_pd (ax, jbm_reciprocal_2xf64 (ax), m);
  f = jbm_atanwc_2xf64 (ax);
  f = _mm_blendv_pd (f, _mm_sub_pd (_mm_set1_pd (M_PI_2), f), m);
  return jbm_copysign_2xf64 (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_2xf64
 * function (__m128d).
 *
 * \return function value (__m128d in [-pi,pi]).
 */
static inline __m128d
jbm_atan2_2xf64 (const __m128d y,       ///< __m128d y component.
                 const __m128d x)       ///< __m128d x component.
{
  const __m128d pi = _mm_set1_pd (M_PI);
  const __m128d z = _mm_setzero_pd ();
  __m128d f, g;
  f = jbm_atan_2xf64 (_mm_div_pd (y, x));
  g = _mm_add_pd (f, jbm_copysign_2xf64 (pi, y));
  return _mm_blendv_pd (f, g, _mm_cmplt_pd (x, z));
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_2xf64 function
 * (__m128d).
 *
 * \return function value (__m128d in [-pi/2,pi/2]).
 */
static inline __m128d
jbm_asin_2xf64 (const __m128d x)        ///< __m128d number.
{
  return
    jbm_atan_2xf64 (_mm_div_pd
                    (x, _mm_sqrt_pd (_mm_fnmadd_pd (x, x, _mm_set1_pd (1.)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_2xf64 function
 * (__m128d).
 *
 * \return function value (__m128d in [0,pi]).
 */
static inline __m128d
jbm_acos_2xf64 (const __m128d x)        ///< __m128d number.
{
  __m128d f;
  f =
    jbm_atan_2xf64 (_mm_div_pd
                    (_mm_sqrt_pd (_mm_fnmadd_pd (x, x, _mm_set1_pd (1.))), x));
  return _mm_blendv_pd (f, _mm_add_pd (f, _mm_set1_pd (M_PI)),
                        _mm_cmplt_pd (x, _mm_setzero_pd ()));
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_sinh_2xf64 (const __m128d x)        ///< __m128d number.
{
  __m128d f;
  f = jbm_exp_2xf64 (x);
  return _mm_mul_pd (_mm_set1_pd (0.5),
                     _mm_sub_pd (f, jbm_reciprocal_2xf64 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_cosh_2xf64 (const __m128d x)        ///< __m128d number.
{
  __m128d f;
  f = jbm_exp_2xf64 (x);
  return _mm_mul_pd (_mm_set1_pd (0.5),
                     _mm_add_pd (f, jbm_reciprocal_2xf64 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_tanh_2xf64 (const __m128d x)        ///< __m128d number.
{
  __m128d f, fi;
  f = jbm_exp_2xf64 (x);
  fi = jbm_reciprocal_2xf64 (f);
  f = _mm_div_pd (_mm_sub_pd (f, fi), _mm_add_pd (f, fi));
  f = _mm_blendv_pd (f, _mm_set1_pd (1.),
                     _mm_cmpgt_pd (x, _mm_set1_pd (JBM_DBL_MAX_E_EXP)));
  return _mm_blendv_pd (f, _mm_set1_pd (-1.),
                        _mm_cmplt_pd (x, _mm_set1_pd (-JBM_DBL_MAX_E_EXP)));
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_asinh_2xf64 (const __m128d x)       ///< __m128d number.
{
  return
    jbm_log_2xf64 (_mm_add_pd
                   (x, _mm_sqrt_pd (_mm_fmadd_pd (x, x, _mm_set1_pd (1.)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_acosh_2xf64 (const __m128d x)       ///< __m128d number.
{
  return
    jbm_log_2xf64 (_mm_add_pd
                   (x, _mm_sqrt_pd (_mm_fmsub_pd (x, x, _mm_set1_pd (1.)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_atanh_2xf64 (const __m128d x)       ///< __m128d number.
{
  const __m128d u = _mm_set1_pd (1.);
  return _mm_mul_pd (_mm_set1_pd (0.5),
                     jbm_log_2xf64 (_mm_div_pd (_mm_add_pd (u, x),
                                                _mm_sub_pd (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m128d)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_erfwc_2xf64 (const __m128d x)
                 ///< __m128d vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_pd (x, jbm_rational_9_4_2xf64 (jbm_sqr_2xf64 (x), K_ERFWC_F64));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m128d)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_erfcwc_2xf64 (const __m128d x)
                  ///< __m128d vector \f$\in\left[1,\infty\right]\f$.
{
  __m128d f, x2;
  x2 = jbm_sqr_2xf64 (x);
  f = _mm_mul_pd (jbm_rational_18_10_2xf64 (jbm_reciprocal_2xf64 (x),
                                            K_ERFCWC_F64),
                  _mm_div_pd (x, jbm_exp_2xf64 (x2)));
  return
    _mm_blendv_pd (f, _mm_setzero_pd (),
                   _mm_cmpgt_pd (x, _mm_set1_pd (K_ERFC_MAX_F64)));
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_2xf64 and
 * jbm_erfcwc_2xf64
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_erf_2xf64 (const __m128d x) ///< __m128d vector.
{
  const __m128d u = _mm_set1_pd (1.);
  __m128d ax, f;
  ax = jbm_abs_2xf64 (x);
  f = jbm_copysign_2xf64 (_mm_sub_pd (u, jbm_erfcwc_2xf64 (ax)), x);
  return _mm_blendv_pd (f, jbm_erfwc_2xf64 (x), _mm_cmplt_pd (ax, u));

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_2xf64 and
 * jbm_erfcwc_2xf64
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_erfc_2xf64 (const __m128d x)        ///< __m128d vector.
{
  const __m128d u2 = _mm_set1_pd (2.);
  const __m128d u = _mm_set1_pd (1.);
  __m128d ax, cwc, wc;
  ax = jbm_abs_2xf64 (x);
  cwc = jbm_erfcwc_2xf64 (ax);
  wc = _mm_sub_pd (u, jbm_erfwc_2xf64 (x));
  return
    _mm_blendv_pd
    (_mm_blendv_pd (wc, _mm_sub_pd (u2, cwc), _mm_cmpgt_pd (ax, u)), cwc,
     _mm_cmpgt_pd (x, u));
}

/**
 * Function to calculate the solution of a __m128d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m128d vector of solution values.
 */
static inline __m128d
jbm_solve_quadratic_reduced_2xf64 (__m128d a,
///< __m128d vector of 1st order coefficient of the equations.
                                   __m128d b,
///< __m128d vector of 0th order coefficient of the equations.
                                   const __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                                   const __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  __m128d k1, k2;
  k1 = _mm_set1_pd (-0.5);
  a = _mm_mul_pd (a, k1);
  b = _mm_sqrt_pd (_mm_sub_pd (jbm_sqr_2xf64 (a), b));
  k1 = _mm_add_pd (a, b);
  k2 = _mm_sub_pd (a, b);
  k1 = _mm_blendv_pd (k1, k2, _mm_cmplt_pd (k1, x1));
  return _mm_blendv_pd (k1, k2, _mm_cmpgt_pd (k1, x2));
}

/**
 * Function to calculate the solution of a __m128d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m128d vector of solution values.
 */
static inline __m128d
jbm_solve_quadratic_2xf64 (const __m128d a,
///< __m128d vector of 2nd order coefficient of the equations.
                           const __m128d b,
///< __m128d vector of 1st order coefficient of the equations.
                           const __m128d c,
///< __m128d vector of 0th order coefficient of the equations.
                           const __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                           const __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  __m128d k1, k2;
  k1 = jbm_solve_quadratic_reduced_2xf64 (_mm_div_pd (b, a), _mm_div_pd (c, a),
                                          x1, x2);
  k2 = _mm_div_pd (jbm_opposite_2xf64 (c), b);
  return _mm_blendv_pd (k1, k2, jbm_small_2xf64 (a));
}

/**
 * Function to calculate the solution of a __m128d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m128d vector of solution values.
 */
static inline __m128d
jbm_solve_cubic_reduced_2xf64 (const __m128d a,
                               ///< 2nd order coefficient of the equation.
                               const __m128d b,
                               ///< 1st order coefficient of the equation.
                               const __m128d c,
                               ///< 0th order coefficient of the equation.
                               const __m128d x1,
                               ///< left limit of the solution interval.
                               const __m128d x2)
                               ///< right limit of the solution interval.
{
  __m128d a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = _mm_set1_pd (2. * M_PI / 3.);
  c_2 = _mm_set1_pd (0.5);
  c_3 = _mm_set1_pd (1. / 3.);
  a3 = _mm_mul_pd (a, c_3);
  k0 = _mm_mul_pd (a3, a3);
  k1 = _mm_fmsub_pd (b, c_3, k0);
  k0 = _mm_fmsub_pd (_mm_fmsub_pd (b, a3, c), c_2, _mm_mul_pd (a3, k0));
  k3 = _mm_mul_pd (k1, _mm_mul_pd (k1, k1));
  k2 = _mm_fmadd_pd (k0, k0, k3);
  l1 = _mm_sqrt_pd (jbm_opposite_2xf64 (k1));
  l0 = _mm_mul_pd (jbm_acos_2xf64 (_mm_div_pd (k0, k3)), c_3);
  l1 = _mm_add_pd (l1, l1);
  l2 = _mm_fmsub_pd (l1, jbm_cos_2xf64 (k0), a3);
  l3 = _mm_fmsub_pd (l1, jbm_cos_2xf64 (_mm_add_pd (l0, c2p_3)), a3);
  l3 = _mm_blendv_pd (l3, l2,
                      _mm_or_pd (_mm_cmplt_pd (l2, x1), _mm_cmpgt_pd (l2, x2)));
  l4 = _mm_fmsub_pd (l1, jbm_cos_2xf64 (_mm_sub_pd (l0, c2p_3)), a);
  l4 = _mm_blendv_pd (l4, l3,
                      _mm_or_pd (_mm_cmplt_pd (l3, x1), _mm_cmpgt_pd (l3, x2)));
  k1 = _mm_sqrt_pd (k2);
  l5 = _mm_add_pd (k0, k1);
  l5 = jbm_cbrt_2xf64 (k2);
  k0 = _mm_sub_pd (k0, k1);
  l5 = _mm_add_pd (l5, _mm_sub_pd (jbm_cbrt_2xf64 (k0), a3));
  return _mm_blendv_pd (l4, l5, _mm_cmplt_pd (k2, _mm_setzero_pd ()));
}

/**
 * Function to calculate the solution of a __m128d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m128d vector of solution values.
 */
static inline __m128d
jbm_solve_cubic_2xf64 (__m128d a,
///< __m128d vector of 3rd order coefficient of the equations.
                       __m128d b,
///< __m128d vector of 2nd order coefficient of the equations.
                       __m128d c,
///< __m128d vector of 1st order coefficient of the equations.
                       __m128d d,
///< __m128d vector of 0th order coefficient of the equations.
                       __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                       __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  return
    _mm_blendv_pd (jbm_solve_cubic_reduced_2xf64 (_mm_div_pd (b, a),
                                                  _mm_div_pd (c, a),
                                                  _mm_div_pd (d, a), x1, x2),
                   jbm_solve_quadratic_2xf64 (b, c, d, x1, x2),
                   jbm_small_2xf64 (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_total_2xf64 (const __m128d d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const __m128d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_null_2xf64 (const __m128d d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const __m128d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_centred_2xf64 (const __m128d d1,
                                ///< 1st flux limiter function parameter.
                                const __m128d d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm_blendv_pd (_mm_div_pd (d1, d2), _mm_setzero_pd (),
                        jbm_small_2xf64 (d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_superbee_2xf64 (const __m128d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_div_pd (d1, d2);
  r = _mm_max_pd (_mm_min_pd (jbm_dbl_2xf64 (r), _mm_set1_pd (1.)),
                  _mm_min_pd (r, _mm_set1_pd (2.)));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_minmod_2xf64 (const __m128d d1,
                               ///< 1st flux limiter function parameter.
                               const __m128d d2)
                             ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_min_pd (_mm_div_pd (d1, d2), _mm_set1_pd (1.));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_VanLeer_2xf64 (const __m128d d1,
                                ///< 1st flux limiter function parameter.
                                const __m128d d2)
                              ///< 2nd flux limiter function parameter.
{
  __m128d r, k;
  r = _mm_div_pd (d1, d2);
  k = jbm_abs_2xf64 (r);
  r = _mm_div_pd (_mm_add_pd (r, k), _mm_add_pd (_mm_set1_pd (1.), k));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_VanAlbada_2xf64 (const __m128d d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m128d d2)
                                ///< 2nd flux limiter function parameter.
{
  __m128d r, k;
  r = _mm_div_pd (d1, d2);
  k = jbm_sqr_2xf64 (r);
  r = _mm_div_pd (_mm_add_pd (r, k), _mm_add_pd (_mm_set1_pd (1.), k));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_minsuper_2xf64 (const __m128d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_min_pd (_mm_div_pd (d1, d2), _mm_set1_pd (2.));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_supermin_2xf64 (const __m128d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_div_pd (d1, d2);
  r = _mm_min_pd (jbm_dbl_2xf64 (r), _mm_set1_pd (1.));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_monotonized_central_2xf64 (const __m128d d1,
///< 1st flux limiter function parameter.
                                            const __m128d d2)
///< 2nd flux limiter function parameter.
{
  __m128d r, rm;
  r = _mm_div_pd (d1, d2);
  rm = _mm_mul_pd (_mm_set1_pd (0.5), _mm_add_pd (r, _mm_set1_pd (1.)));
  rm = _mm_blendv_pd (_mm_set1_pd (2.), rm, _mm_cmplt_pd (r, _mm_set1_pd (3.)));
  rm = _mm_blendv_pd (rm, jbm_dbl_2xf64 (r),
                      _mm_cmpgt_pd (r, _mm_set1_pd (1. / 3.)));
  return _mm_blendv_pd (_mm_setzero_pd (), rm,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_mean_2xf64 (const __m128d d1,
                             ///< 1st flux limiter function parameter.
                             const __m128d d2)
                           ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_mul_pd (_mm_set1_pd (0.5),
                  _mm_add_pd (_mm_set1_pd (1.), _mm_div_pd (d1, d2)));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (DBL_EPSILON)));
}

/**
 * Function to do a flux limiter function (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_2xf64 (const __m128d d1,
                        ///< 1st flux limiter function parameter.
                        const __m128d d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_2xf64 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_2xf64 (d1, d2);
    }
  return jbm_flux_limiter_mean_2xf64 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m128d).
 *
 * \return __m128d vector of integral values.
 */
static inline __m128d
jbm_integral_2xf64 (__m128d (*f) (__m128d),
                    ///< pointer to the function to integrate.
                    const __m128d x1,   ///< left limit of the interval.
                    const __m128d x2)   ///< right limit of the interval.
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
  __m128d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m128d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm_set1_pd (0.5);
  dx = _mm_mul_pd (h, _mm_sub_pd (x2, x1));
  x = _mm_mul_pd (h, _mm_add_pd (x2, x1));
  k = _mm_set1_pd (a[0]);
  k = _mm_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm_set1_pd (b[i]);
      k2 = _mm_mul_pd (k2, dx);
      f1 = f (_mm_sub_pd (x, k2));
      f2 = f (_mm_add_pd (x, k2));
      h = _mm_set1_pd (a[i]);
      k = _mm_fmadd_pd (h, _mm_add_pd (f1, f2), k);
    }
#endif
  k = _mm_mul_pd (k, dx);
  return k;
}

#ifndef __AVX__

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_add_f32 (float *xr,   ///< result float array.
                   const float *x1,     ///< 1st addend float array.
                   const float *x2,     ///< 1st addend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_add_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] + x2[i];
}

/**
 * Function to subtract 2 float arrays.
 */
static inline void
jbm_array_sub_f32 (float *xr,   ///< result float array.
                   const float *x1,     ///< minuend float array.
                   const float *x2,     ///< subtrahend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_sub_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] - x2[i];
}

/**
 * Function to multiply a float array by a float number.
 */
static inline void
jbm_array_mul1_f32 (float *xr,  ///< result float array.
                    const float *x1,    ///< multiplier float array.
                    const float x2,     ///< multiplicand float number.
                    const unsigned int n)       ///< number of array elements.
{
  __m128 s4;
  unsigned int i, j;
  i = 0;
  j = n >> 2;
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
jbm_array_div1_f32 (float *xr,  ///< result float array.
                    const float *x1,    ///< dividend float array.
                    const float x2,     ///< divisor float number.
                    const unsigned int n)       ///< number of array elements.
{
  __m128 s4;
  unsigned int i, j;
  i = 0;
  j = n >> 2;
  if (j)
    {
      s4 = _mm_set1_ps (x2);
      for (; j > 0; --j, i += 2)
        _mm_store_ps (xr + i, _mm_div_ps (_mm_load_ps (x1 + i), s4));
    }
  for (; i < n; ++i)
    xr[i] = x1[i] / x2;
}

/**
 * Function to multiply 2 float arrays.
 */
static inline void
jbm_array_mul_f32 (float *xr,   ///< result float array.
                   const float *x1,     ///< multiplier float array.
                   const float *x2,     ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_mul_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] * x2[i];
}

/**
 * Function to divide 2 float arrays.
 */
static inline void
jbm_array_div_f32 (float *xr,   ///< result float array.
                   const float *x1,     ///< dividend float array.
                   const float *x2,     ///< divisor float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_div_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to calculate the float of a float array.
 */
static inline void
jbm_array_dbl_f32 (float *xr,   ///< result float array.
                   const float *xd,     ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i, jbm_dbl_4xf32 (_mm_load_ps (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_dbl_f32 (xd[i]);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_sqr_f32 (float *xr,   ///< result float array.
                   const float *xd,     ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i, jbm_sqr_4xf32 (_mm_load_ps (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_sqr_f32 (xd[i]);
}

/**
 * Function to find the highest element of a float array.
 *
 * \return the highest value.
 */
static inline float
jbm_array_max_f32 (const float *xx,     ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  float ax[4] JB_ALIGNED;
  __m128 s4;
  float k;
  unsigned int i, j;
  j = n >> 1;
  if (j)
    {
      s4 = _mm_load_ps (xx);
      i = 4;
      while (--j > 0)
        {
          s4 = _mm_max_ps (s4, _mm_load_ps (xx + i));
          i += 4;
        }
      _mm_store_ps (ax, s4);
      k = fmaxf (fmaxf (ax[0], ax[1]), fmaxf (ax[2], ax[3]));
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
jbm_array_min_f32 (const float *xx,     ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  float ax[4] JB_ALIGNED;
  __m128 s4;
  float k;
  unsigned int i, j;
  j = n >> 2;
  if (j)
    {
      s4 = _mm_load_ps (xx);
      i = 4;
      while (--j > 0)
        {
          s4 = _mm_min_ps (s4, _mm_load_ps (xx + i));
          i += 4;
        }
      _mm_store_ps (ax, s4);
      k = fminf (fminf (ax[0], ax[1]), fminf (ax[2], ax[3]));
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
jbm_array_maxmin_f32 (const float *xx,  ///< float array.
                      float *max,       ///< the highest value.
                      float *min,       ///< the lowest value.
                      const unsigned int n)     ///< number of array elements.
{
  float ax[4] JB_ALIGNED;
  __m128 s4, smax4, smin4;
  float kmax, kmin;
  unsigned int i, j;
  j = n >> 2;
  if (j)
    {
      smax4 = smin4 = _mm_load_ps (xx);
      i = 4;
      while (--j > 0)
        {
          s4 = _mm_load_ps (xx + i);
          smax4 = _mm_max_ps (smax4, s4);
          smin4 = _mm_min_ps (smin4, s4);
          i += 4;
        }
      _mm_store_ps (ax, smax4);
      kmax = fmaxf (fmaxf (ax[0], ax[1]), fmaxf (ax[2], ax[3]));
      _mm_store_ps (ax, smin4);
      kmin = fminf (fminf (ax[0], ax[1]), fminf (ax[2], ax[3]));
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
jbm_array_add_f64 (double *xr,  ///< result double array.
                   const double *x1,    ///< 1st addend double array.
                   const double *x2,    ///< 1st addend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_add_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] + x2[i];
}

/**
 * Function to subtract 2 double arrays.
 */
static inline void
jbm_array_sub_f64 (double *xr,  ///< result double array.
                   const double *x1,    ///< minuend double array.
                   const double *x2,    ///< subtrahend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_sub_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] - x2[i];
}

/**
 * Function to multiply a double array by a double number.
 */
static inline void
jbm_array_mul1_f64 (double *xr, ///< result double array.
                    const double *x1,   ///< multiplier double array.
                    const double x2,    ///< multiplicand double number.
                    const unsigned int n)       ///< number of array elements.
{
  __m128d s2;
  unsigned int i, j;
  i = 0;
  j = n >> 1;
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
jbm_array_div1_f64 (double *xr, ///< result double array.
                    const double *x1,   ///< dividend double array.
                    const double x2,    ///< divisor double number.
                    const unsigned int n)       ///< number of array elements.
{
  __m128d s2;
  unsigned int i, j;
  i = 0;
  j = n >> 1;
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
jbm_array_mul_f64 (double *xr,  ///< result double array.
                   const double *x1,    ///< multiplier double array.
                   const double *x2,    ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_mul_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] * x2[i];
}

/**
 * Function to divide 2 double arrays.
 */
static inline void
jbm_array_div_f64 (double *xr,  ///< result double array.
                   const double *x1,    ///< dividend double array.
                   const double *x2,    ///< divisor double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_div_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to calculate the double of a double array.
 */
static inline void
jbm_array_dbl_f64 (double *xr,  ///< result double array.
                   const double *xd,    ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i, jbm_dbl_2xf64 (_mm_load_pd (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_dbl_f64 (xd[i]);
}

/**
 * Function to calculate the square of a double array.
 */
static inline void
jbm_array_sqr_f64 (double *xr,  ///< result double array.
                   const double *xd,    ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i, jbm_sqr_2xf64 (_mm_load_pd (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_sqr_f64 (xd[i]);
}

/**
 * Function to find the highest element of a double array.
 *
 * \return the highest value.
 */
static inline double
jbm_array_max_f64 (const double *xx,    ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  double ax[2] JB_ALIGNED;
  __m128d s2;
  double k;
  unsigned int i, j;
  j = n >> 1;
  if (j)
    {
      s2 = _mm_load_pd (xx);
      i = 2;
      while (--j > 0)
        {
          s2 = _mm_max_pd (s2, _mm_load_pd (xx + i));
          i += 2;
        }
      _mm_store_pd (ax, s2);
      k = fmax (ax[0], ax[1]);
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
jbm_array_min_f64 (const double *xx,    ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  double ax[2] JB_ALIGNED;
  __m128d s2;
  double k;
  unsigned int i, j;
  j = n >> 1;
  if (j)
    {
      s2 = _mm_load_pd (xx);
      i = 2;
      while (--j > 0)
        {
          s2 = _mm_min_pd (s2, _mm_load_pd (xx + i));
          i += 2;
        }
      _mm_store_pd (ax, s2);
      k = fmin (ax[0], ax[1]);
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
jbm_array_maxmin_f64 (const double *xx, ///< double array.
                      double *max,      ///< the highest value.
                      double *min,      ///< the lowest value.
                      const unsigned int n)     ///< number of array elements.
{
  double ax[2] JB_ALIGNED;
  __m128d s2, smax2, smin2;
  double kmax, kmin;
  unsigned int i, j;
  j = n >> 1;
  if (j)
    {
      smax2 = smin2 = _mm_load_pd (xx);
      i = 2;
      while (--j > 0)
        {
          s2 = _mm_load_pd (xx + i);
          smax2 = _mm_max_pd (smax2, s2);
          smin2 = _mm_min_pd (smin2, s2);
          i += 2;
        }
      _mm_store_pd (ax, smax2);
      kmax = fmax (ax[0], ax[1]);
      _mm_store_pd (ax, smin2);
      kmin = fmin (ax[0], ax[1]);
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
