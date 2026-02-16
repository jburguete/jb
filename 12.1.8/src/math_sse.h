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

// float constants

#define JBM_4xF32_BIAS _mm_set1_epi32 (JBM_F32_BIAS)
///< bias for floats.
#define JBM_4xF32_BITS_1 _mm_set1_epi32 (JBM_F32_BITS_1)
///< 1 bits for floats.
#define JBM_4xF32_BITS_EXPONENT _mm_set1_epi32 (JBM_F32_BITS_EXPONENT)
///< exponent bits for floats.
#define JBM_4xF32_BITS_MANTISSA _mm_set1_epi32 (JBM_F32_BITS_MANTISSA)
///< mantissa bits for floats.
#define JBM_4xF32_BITS_SIGN _mm_set1_epi32 (JBM_F32_BITS_SIGN)
///< sign bits for floats.
#define JBM_4xF32_CBRT2 _mm_set1_ps (JBM_F32_CBRT2)
///< cbrt(2) for floats.
#define JBM_4xF32_CBRT4 _mm_set1_ps (JBM_F32_CBRT4)
///< cbrt(4) for floats.

// double constants

#define JBM_2xF64_BIAS _mm_set1_epi64x (JBM_F64_BIAS)
///< bias for doubles.
#define JBM_2xF64_BITS_1 _mm_set1_epi64x (JBM_F64_BITS_1)
///< 1 bits for doubles.
#define JBM_2xF64_BITS_EXPONENT _mm_set1_epi64x (JBM_F64_BITS_EXPONENT)
///< exponent bits for doubles.
#define JBM_2xF64_BITS_MANTISSA _mm_set1_epi64x (JBM_F64_BITS_MANTISSA)
///< mantissa bits for doubles.
#define JBM_2xF64_BITS_SIGN _mm_set1_epi64x (JBM_F64_BITS_SIGN)
///< sign bits for floats.
#define JBM_2xF64_CBRT2 _mm_set1_pd (JBM_F64_CBRT2)
///< cbrt(2) for doubles.
#define JBM_2xF64_CBRT4 _mm_set1_pd (JBM_F64_CBRT4)
///< cbrt(4) for doubles.

// Debug functions

static inline void
print_m128b32 (FILE *file, const char *label, const __m128i x)
{
  int y[4] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m128b64 (FILE *file, const char *label, const __m128i x)
{
  long long int y[2] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_m128i32 (FILE *file, const char *label, const __m128i x)
{
  int y[4] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m128i64 (FILE *file, const char *label, const __m128i x)
{
  long long int y[2] JB_ALIGNED;
  unsigned int i;
  _mm_store_si128 ((__m128i *) y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%lld\n", label, i, y[i]);
}

static inline void
print_m128 (FILE *file, const char *label, const __m128 x)
{
  float y[4] JB_ALIGNED;
  unsigned int i;
  _mm_store_ps (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m128d (FILE *file, const char *label, const __m128d x)
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

#endif

#ifndef __AVX2__

static inline __m128i
_mm_sllv_epi32 (const __m128i x, const __m128i y)
{
  int32_t ix[4] JB_ALIGNED, iy[4] JB_ALIGNED;
  _mm_store_si128 ((__m128i *) ix, x);
  _mm_store_si128 ((__m128i *) iy, y);
  ix[0] <<= iy[0];
  ix[1] <<= iy[1];
  ix[2] <<= iy[2];
  ix[3] <<= iy[3];
  return _mm_load_si128 ((__m128i *) ix);
}

static inline __m128i
_mm_sllv_epi64 (const __m128i x, const __m128i y)
{
  int64_t ix[2] JB_ALIGNED, iy[2] JB_ALIGNED;
  _mm_store_si128 ((__m128i *) ix, x);
  _mm_store_si128 ((__m128i *) iy, y);
  ix[0] <<= iy[0];
  ix[1] <<= iy[1];
  return _mm_load_si128 ((__m128i *) ix);
}

#endif

#ifndef __AVX512F__

static inline __m128d
_mm_cvtepi64_pd (const __m128i x)
{
  return _mm_cvtepi32_pd (_mm_shuffle_epi32 (x, _MM_SHUFFLE (0, 0, 2, 0)));
}

#endif

/**
 * Function to do an integer division by 3 for 32 bits (__m128i).
 *
 * \return divided by 3 vector (__m128i).
 */
static inline __m128i
jbm_4xf32_div3 (__m128i x)      ///< __m128i vector.
{
  const __m128i magic = _mm_set1_epi32 (0x55555556);
  __m128i even, odd;
  even = _mm_srli_epi64 (_mm_mul_epi32 (x, magic), 32);
  odd = _mm_shuffle_epi32 (x, _MM_SHUFFLE (2, 3, 0, 1));
  odd = _mm_srli_epi64 (_mm_mul_epi32 (odd, magic), 32);
  return _mm_unpacklo_epi32 (_mm_shuffle_epi32 (even, _MM_SHUFFLE (0, 0, 2, 0)),
                             _mm_shuffle_epi32 (odd, _MM_SHUFFLE (0, 0, 2, 0)));
}

/**
 * Function to calculate the additive reduction value of a __m128 vector.
 *
 * \return additive reduction (float).
 */
static inline float
jbm_4xf32_reduce_add (const __m128 x)   ///< __m128 vector.
{
  __m128 y;
  y = _mm_hadd_ps (x, x);
  return _mm_cvtss_f32 (_mm_hadd_ps (y, y));
}

/**
 * Function to calculate the maximum reduction value of a __m128 vector.
 *
 * \return maximum reduction (float).
 */
static inline float
jbm_4xf32_reduce_max (const __m128 x)
{
  __m128 y;
  y = _mm_max_ps (x, _mm_movehl_ps (x, x));
  y = _mm_max_ps (y, _mm_shuffle_ps (y, y, _MM_SHUFFLE (1, 0, 3, 2)));
  return _mm_cvtss_f32 (y);
}

/**
 * Function to calculate the minimum reduction value of a __m128 vector.
 *
 * \return minimum reduction (float).
 */
static inline float
jbm_4xf32_reduce_min (const __m128 x)
{
  __m128 y;
  y = _mm_min_ps (x, _mm_movehl_ps (x, x));
  y = _mm_min_ps (y, _mm_shuffle_ps (y, y, _MM_SHUFFLE (1, 0, 3, 2)));
  return _mm_cvtss_f32 (y);
}

/**
 * Function to calculate the maximum and minimum reduction value of a
 * __m128 vector.
 */
static inline void
jbm_4xf32_reduce_maxmin (const __m128 x,        ///< __m128 vector.
                         float *max,
                         ///< pointer to the maximum value (float).
                         float *min)
                         ///< pointer to the minimum value (float).
{
  __m128 y, z;
  z = _mm_movehl_ps (x, x);
  y = _mm_max_ps (x, z);
  y = _mm_max_ps (y, _mm_shuffle_ps (y, y, _MM_SHUFFLE (1, 0, 3, 2)));
  *max = _mm_cvtss_f32 (y);
  y = _mm_min_ps (x, z);
  y = _mm_min_ps (y, _mm_shuffle_ps (y, y, _MM_SHUFFLE (1, 0, 3, 2)));
  *min = _mm_cvtss_f32 (y);
}

/**
 * Function to calculate the additive inverse value of a __m128 vector.
 *
 * \return opposite value vector (__m128).
 */
static inline __m128
jbm_4xf32_opposite (const __m128 x)     ///< __m128 vector.
{
  JBM4xF32 y;
  y.i = JBM_4xF32_BITS_SIGN;
  return _mm_xor_ps (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m128 vector.
 *
 * \return reciprocal value vector (__m128).
 */
static inline __m128
jbm_4xf32_reciprocal (const __m128 x)   ///< __m128 vector.
{
  return _mm_div_ps (_mm_set1_ps (1.f), x);
}

/**
 * Function to calculate the sign of a __m128 vector.
 *
 * \return sign vector (__m128).
 */
static inline __m128
jbm_4xf32_sign (const __m128 x) ///< __m128 vector.
{
  JBM4xF32 y;
  y.x = x;
  y.i = _mm_and_si128 (y.i, JBM_4xF32_BITS_SIGN);
  y.i = _mm_or_si128 (y.i, JBM_4xF32_BITS_1);
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m128 vector.
 *
 * \return absolute value vector (__m128).
 */
static inline __m128
jbm_4xf32_abs (const __m128 x)  ///< __m128 vector.
{
  JBM4xF32 y;
  y.i = JBM_4xF32_BITS_SIGN;
  return _mm_andnot_ps (y.x, x);
}

/**
 * Function to copy the sign of a __m128 vector to another __m128 vector.
 *
 * \return __m128 vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m128
jbm_4xf32_copysign (const __m128 x,
///< __m128 vector to preserve magnitude.
                    const __m128 y)     ///< __m128 vector to preserve sign.
{
  JBM4xF32 m;
  m.i = JBM_4xF32_BITS_SIGN;
  return _mm_or_ps (jbm_4xf32_abs (x), _mm_and_ps (y, m.x));
}

/**
 * Function to calculate the hypot function (__m128).
 *
 * \return function value vector (__m128).
 */
static inline __m128
jbm_4xf32_hypot (const __m128 x,        ///< 1st __m128 vector.
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
jbm_4xf32_mod (const __m128 x,  ///< dividend (__m128).
               const __m128 d)  ///< divisor (__m128).
{
  __m128 r;
  r = _mm_floor_ps (_mm_div_ps (x, d));
  return _mm_blendv_ps (_mm_fnmadd_ps (r, d, x),
                        _mm_mul_ps (d, _mm_set1_ps (0.5f)),
                        _mm_cmpgt_ps (jbm_4xf32_abs (r),
                                      _mm_set1_ps (1.f / FLT_EPSILON)));
}

/**
 * Function to implement the standard frexp function (__m128).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m128
jbm_4xf32_frexp (const __m128 x,        ///< __m128 vector.
                 __m128i *e)    ///< pointer to the extracted exponents vector.
{
  const __m128i zi = _mm_setzero_si128 ();
  const __m128i bias = JBM_4xF32_BIAS;
  const __m128i sign_mask = JBM_4xF32_BITS_SIGN;
  const __m128i mant_mask = JBM_4xF32_BITS_MANTISSA;
  JBM4xF32 y, z;
  __m128i exp, is_z, is_sub, is_nan, is_finite;
  // y=abs(x)
  y.x = jbm_4xf32_abs (x);
  // masks
  is_z = _mm_cmpeq_epi32 (y.i, zi);
  is_nan = _mm_cmpgt_epi32 (y.i, _mm_set1_epi32 (JBM_F32_BITS_EXPONENT - 1));
  is_finite = _mm_andnot_si128 (_mm_or_si128 (is_z, is_nan),
                                _mm_set1_epi32 (-1));
  // extract exponent
  exp = _mm_srli_epi32 (y.i, 23);
  // subnormals
  is_sub = _mm_and_si128 (is_finite, _mm_cmpeq_epi32 (exp, zi));
  y.x
    = _mm_blendv_ps (y.x, _mm_mul_ps (y.x, _mm_set1_ps (0x1p23f)),
                     _mm_castsi128_ps (is_sub));
  exp
    = _mm_blendv_epi8 (exp, _mm_sub_epi32 (_mm_srli_epi32 (y.i, 23),
                                           _mm_set1_epi32 (23)), is_sub);
  // exponent
  *e = _mm_blendv_epi8 (zi, _mm_sub_epi32 (exp, bias), is_finite);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm_or_si128 (_mm_and_si128 (z.i, sign_mask),
                      _mm_or_si128 (_mm_set1_epi32 (JBM_F32_BIAS << 23),
                                    _mm_and_si128 (y.i, mant_mask)));
  return _mm_blendv_ps (x, y.x, _mm_castsi128_ps (is_finite));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m128i).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_exp2n (const __m128i e)       ///< exponent vector (__m128i).
{
  const __m128i v127 = _mm_set1_epi32 (127);
  __m128 x;
  x = _mm_blendv_ps
    (_mm_castsi128_ps (_mm_sllv_epi32 (_mm_set1_epi32 (1),
                                       _mm_add_epi32 (_mm_set1_epi32 (149),
                                                      e))),
     _mm_castsi128_ps (_mm_slli_epi32 (_mm_add_epi32 (e, v127), 23)),
     _mm_castsi128_ps (_mm_cmpgt_epi32 (e, _mm_set1_epi32 (-127))));
  x = _mm_blendv_ps (x, _mm_setzero_ps (),
                     _mm_castsi128_ps (_mm_cmplt_epi32 (e,
                                                        _mm_set1_epi32
                                                        (-149))));
  return _mm_blendv_ps (x, _mm_set1_ps (INFINITY),
                        _mm_castsi128_ps (_mm_cmpgt_epi32 (e, v127)));
}

/**
 * Function to implement the standard ldexp function (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_ldexp (const __m128 x,        ///< __m128 vector.
                 const __m128i e)       ///< exponent vector (__m128i).
{
  return _mm_mul_ps (x, jbm_4xf32_exp2n (e));
}

/**
 * Function to check small __m128 vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m128
jbm_4xf32_small (const __m128 x)        ///< __m128d vector.
{
  return _mm_cmplt_ps (jbm_4xf32_abs (x), _mm_set1_ps (FLT_EPSILON));
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
jbm_4xf32_modmin (const __m128 a,       ///< 1st __m128d vector.
                  const __m128 b)       ///< 2nd __m128d vector.
{
  const __m128 z = _mm_setzero_ps ();
  __m128 aa, ab, y;
  ab = _mm_mul_ps (a, b);
  y = _mm_blendv_ps (z, a, _mm_cmpgt_ps (ab, z));
  aa = jbm_4xf32_abs (y);
  ab = jbm_4xf32_abs (b);
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
jbm_4xf32_dbl (const __m128 x)  ///< __m128d vector.
{
  return _mm_add_ps (x, x);
}

/**
 * Function to calculate the square of the components of a __m128 vector.
 *
 * \return __m128 vector square.
 */
static inline __m128
jbm_4xf32_sqr (const __m128 x)  ///< __m128 vector.
{
  return _mm_mul_ps (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m128 vectors of 2D points.
 *
 * \return __m128 vector of y-coordinates of the extrapolated points.
 */
static inline __m128
jbm_4xf32_extrapolate (const __m128 x,
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
jbm_4xf32_interpolate (const __m128 x,
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
  k = jbm_4xf32_extrapolate (x, x1, x2, y1, y2);
  k = _mm_blendv_ps (y1, k, _mm_cmpgt_ps (x, x1));
  return _mm_blendv_ps (y2, k, _mm_cmplt_ps (x, x2));
}

/**
 * Function to calculate the length of a __m128 vector of 2D segments.
 *
 * \return __m128 vector of segment lengths.
 */
static inline __m128
jbm_4xf32_v2_length (const __m128 x1,
///< __m128 vector of x-coordinates of the 1st points defining the segment.
                     const __m128 y1,
///< __m128 vector of y-coordinates of the 1st points defining the segment.
                     const __m128 x2,
///< __m128 vector of x-coordinates of the 2nd points defining the segment.
                     const __m128 y2)
///< __m128 vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_4xf32_hypot (_mm_sub_ps (x2, x1), _mm_sub_ps (y2, y1));
}

/**
 * Function to calculate the length of a __m128 vector of 3D segments.
 *
 * \return __m128 vector of segment lengths.
 */
static inline __m128
jbm_4xf32_v3_length (const __m128 x1,
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
  dx = jbm_4xf32_sqr (_mm_sub_ps (x2, x1));
  dy = _mm_sub_ps (y2, y1);
  dy = _mm_fmadd_ps (dy, dy, dx);
  dz = _mm_sub_ps (z2, z1);
  return _mm_sqrt_ps (_mm_fmadd_ps (dz, dz, dy));
}

/**
 * Function to calculate a 1st order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_1 (const __m128 x, ///< __m128 vector.
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
jbm_4xf32_polynomial_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_4 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_5 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_6 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_7 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_8 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_9 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_10 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_11 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_12 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_13 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_14 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_15 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_16 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_17 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_18 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_19 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_20 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_21 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_22 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_23 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_24 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_25 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_24 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_26 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_25 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_27 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_26 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_28 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_27 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m128).
 *
 * \return __m128 vector of polynomial values.
 */
static inline __m128
jbm_4xf32_polynomial_29 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_fmadd_ps (x, jbm_4xf32_polynomial_28 (x, p + 1),
                       _mm_set1_ps (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_1_0 (const __m128 x, ///< __m128 vector.
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
jbm_4xf32_rational_2_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+1st order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_2_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[2]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_3_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_3_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_3_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[3]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_4_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_4_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_4_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_4_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[4]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_5_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_5_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_5_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_5_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_5_4 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[5]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_6_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_6_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_6_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_6_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_6_4 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_6_5 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[6]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_4 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_5 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_7_6 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[7]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_4 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_5 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_6 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_8_7 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[8]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_0 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_1 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_2 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_3 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_4 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_5 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_6 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_7 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_9_8 (const __m128 x, ///< __m128 vector.
                        const float *p) ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[9]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_10_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[10]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_11_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[11]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_12_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[12]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_13_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[13]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_14_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[14]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_15_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[15]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_16_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[16]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_17_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[17]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_18_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[18]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_19_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[19]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_20_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[20]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_21_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[21]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_22_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[22]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_23_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[23]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_24_23 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_23 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[24]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_24 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_23 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_23 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_25_24 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_24 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[25]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_25 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_24 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_23 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_23 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_24 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_24 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_26_25 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_25 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[26]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_26 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_25 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_24 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_23 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_23 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_24 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_24 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_25 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_25 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 26),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_27_26 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_26 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[27]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+28th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_27 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_26 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_25 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_24 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_23 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_23 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_24 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_24 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_25 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_25 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 26),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_26 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_26 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 27),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_28_27 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_27 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[28]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 0th+29th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_0 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (_mm_set1_ps (p[0]),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_28 (x, p + 1),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_1 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_1 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_27 (x, p + 2),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_2 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_2 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_26 (x, p + 3),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_3 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_3 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_25 (x, p + 4),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 4th+25th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_4 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_4 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_24 (x, p + 5),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 5th+24th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_5 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_5 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_23 (x, p + 6),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 6th+23th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_6 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_6 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_22 (x, p + 7),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 7th+22th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_7 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_7 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_21 (x, p + 8),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 8th+21th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_8 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_8 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_20 (x, p + 9),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 9th+20th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_9 (const __m128 x,        ///< __m128 vector.
                         const float *p)        ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_9 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_19 (x, p + 10),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 10th+19th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_10 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_10 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_18 (x, p + 11),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 11th+18th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_11 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_11 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_17 (x, p + 12),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 12th+17th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_12 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_12 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_16 (x, p + 13),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 13th+16th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_13 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_13 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_15 (x, p + 14),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 14th+15th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_14 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_14 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_14 (x, p + 15),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 15th+14th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_15 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_15 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_13 (x, p + 16),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 16th+13th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_16 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_16 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_12 (x, p + 17),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 17th+12th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_17 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_17 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_11 (x, p + 18),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 18th+11th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_18 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_18 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_10 (x, p + 19),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 19th+10th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_19 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_19 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_9 (x, p + 20),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 20th+9th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_20 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_20 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_8 (x, p + 21),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 21th+8th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_21 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_21 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_7 (x, p + 22),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 22th+7th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_22 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_22 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_6 (x, p + 23),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 23th+6th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_23 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_23 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_5 (x, p + 24),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 24th+5th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_24 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_24 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_4 (x, p + 25),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 25th+4th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_25 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_25 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_3 (x, p + 26),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_26 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_26 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_2 (x, p + 27),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_27 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_27 (x, p),
                     _mm_fmadd_ps (x, jbm_4xf32_polynomial_1 (x, p + 28),
                                   _mm_set1_ps (1.f)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128).
 *
 * \return __m128 vector of rational values.
 */
static inline __m128
jbm_4xf32_rational_29_28 (const __m128 x,       ///< __m128 vector.
                          const float *p)       ///< array of coefficients.
{
  return _mm_div_ps (jbm_4xf32_polynomial_28 (x, p),
                     _mm_fmadd_ps (x, _mm_set1_ps (p[29]), _mm_set1_ps (1.f)));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_cbrtwc (const __m128 x)
                  ///< __m128 vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_4xf32_rational_5_3 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_cbrtwc_4xdbl
 * function (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_cbrt (const __m128 x) ///< __m128 vector.
{
  const __m128 cbrt2 = JBM_4xF32_CBRT2;
  const __m128 cbrt4 = JBM_4xF32_CBRT4;
  const __m128i v3 = _mm_set1_epi32 (3);
  const __m128i v2 = _mm_set1_epi32 (2);
  const __m128i v1 = _mm_set1_epi32 (1);
  __m128 y;
  __m128i e, e3, r, n;
  y = jbm_4xf32_frexp (jbm_4xf32_abs (x), &e);
  e3 = jbm_4xf32_div3 (e);
  r = _mm_sub_epi32 (e, _mm_mullo_epi32 (e3, v3));
  n = _mm_srai_epi32 (r, 31);
  r = _mm_add_epi32 (r, _mm_and_si128 (n, v3));
  e3 = _mm_sub_epi32 (e3, _mm_and_si128 (n, v1));
  y = jbm_4xf32_ldexp (jbm_4xf32_cbrtwc (y), e3);
  y = _mm_blendv_ps (y, _mm_mul_ps (y, cbrt2),
                     _mm_castsi128_ps (_mm_cmpeq_epi32 (r, v1)));
  y = _mm_blendv_ps (y, _mm_mul_ps (y, cbrt4),
                     _mm_castsi128_ps (_mm_cmpeq_epi32 (r, v2)));
  return jbm_4xf32_copysign (y, x);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m128).
 *
 * \return function value.
 */
static inline __m128
jbm_4xf32_exp2wc (const __m128 x)
                  ///< __m128 vector \f$\in[\frac12,1]\f$.
{
  return jbm_4xf32_polynomial_5 (x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_4xf32 and
 * jbm_4xf32_exp2n functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_exp2 (const __m128 x) ///< __m128 vector.
{
  __m128 y, f;
  y = _mm_floor_ps (x);
  f = _mm_sub_ps (x, y);
  y = jbm_4xf32_exp2n (_mm_cvtps_epi32 (y));
  return _mm_mul_ps (y, jbm_4xf32_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_4xf32_exp2 function
 * (__m128).
 *
 * \return function value.
 */
static inline __m128
jbm_4xf32_exp (const __m128 x)  ///< __m128 vector.
{
  return jbm_4xf32_exp2 (_mm_mul_ps (x, _mm_set1_ps (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_4xdbl
 * function (__m128).
 *
 * \return function value.
 */
static inline __m128
jbm_4xf32_exp10 (const __m128 x)        ///< __m128 vector.
{
  return jbm_4xf32_exp2 (_mm_mul_ps (x, _mm_set1_ps (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_expm1wc (const __m128 x)
///< __m128 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  __m128 x2;
  x2 = jbm_4xf32_sqr (x);
  x2 = _mm_fmadd_ps (x2, _mm_set1_ps (b4), _mm_set1_ps (b2));
  x2 = _mm_fmadd_ps (x2, x, _mm_set1_ps (b1));
  x2 = _mm_fmadd_ps (x2, x, _mm_set1_ps (1.f));
  return _mm_mul_ps (x, _mm_div_ps (_mm_set1_ps (a1), x2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_4xf32_expm1wc and
 * jbm_4xf32_exp functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_expm1 (const __m128 x)        ///< __m128 vector.
{
  return _mm_blendv_ps (_mm_sub_ps (jbm_4xf32_exp (x), _mm_set1_ps (1.f)),
                        jbm_4xf32_expm1wc (x),
                        _mm_cmplt_ps (jbm_4xf32_abs (x),
                                      _mm_set1_ps (M_LN2f / 2.f)));
}

/**
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_log2wc (const __m128 x)       ///< __m128 vector.
{
  return _mm_mul_ps (x, jbm_4xf32_rational_5_2 (x, K_LOG2WC_F32));
}

/**
 * Function to calculate the function log_2(x) using jbm_4xf32_log2wc and
 * jbm_4xf32_frexp (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_log2 (const __m128 x) ///< __m128 vector.
{
  const __m128 z = _mm_setzero_ps ();
  __m128 y, m;
  __m128i e;
  y = jbm_4xf32_frexp (x, &e);
  m = _mm_cmplt_ps (y, _mm_set1_ps (M_SQRT1_2f));
  y = _mm_add_ps (y, _mm_and_ps (m, y));
  e = _mm_sub_epi32 (e, _mm_and_si128 (_mm_castps_si128 (m),
                                       _mm_set1_epi32 (1)));
  y = _mm_add_ps (jbm_4xf32_log2wc (_mm_sub_ps (y, _mm_set1_ps (1.f))),
                  _mm_cvtepi32_ps (e));
  y = _mm_blendv_ps (y, _mm_set1_ps (-INFINITY), _mm_cmpeq_ps (x, z));
  y = _mm_blendv_ps (y, _mm_set1_ps (NAN), _mm_cmplt_ps (x, z));
  y = _mm_blendv_ps (y, x, _mm_cmpeq_ps (x, _mm_set1_ps (INFINITY)));
  return _mm_blendv_ps (y, x, _mm_cmpunord_ps (x, x));
}

/**
 * Function to calculate the function log(x) using jbm_4xf32_log2 (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_log (const __m128 x)  ///< __m128 vector.
{
  return _mm_mul_ps (jbm_4xf32_log2 (x), _mm_set1_ps (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_4xdbl.
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_log10 (const __m128 x)        ///< __m128 vector.
{
  return _mm_mul_ps (jbm_4xf32_log2 (x), _mm_set1_ps (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (__m128).
 *
 * \return function value (__m128) (__m128).
 */
static inline __m128
jbm_4xf32_pown (const __m128 x, ///< __m128 vector.
                const int e)    ///< exponent (int).
{
  __m128 f, xn;
  unsigned int i;
  f = _mm_set1_ps (1.f);
  if (e < 0)
    xn = _mm_div_ps (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_4xf32_sqr (xn))
    if (i & 1)
      f = _mm_mul_ps (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_4xf32_exp2 and
 * jbm_4xf32_log2 functions (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_pow (const __m128 x,  ///< __m128 vector.
               const __m128 e)  ///< exponent (__m128).
{
  return jbm_4xf32_exp2 (_mm_mul_ps (e, jbm_4xf32_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m128)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_sinwc (const __m128 x)
                 ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm_mul_ps (x, jbm_4xf32_polynomial_3 (jbm_4xf32_sqr (x), K_SINWC_F32));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m128):
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_coswc (const __m128 x)
                 ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_4xf32_polynomial_3 (jbm_4xf32_sqr (x), K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_tanwc (const __m128 x)
                  ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return _mm_mul_ps (x,
                     jbm_4xf32_rational_3_1 (jbm_4xf32_sqr (x), K_TANWC_F32));
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_4xf32_sinwc approximation (__m128).
 */
static inline void
jbm_4xf32_sincoswc (const __m128 x,
                    ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m128 *s,  ///< pointer to the sin function value (__m128).
                    __m128 *c)  ///< pointer to the cos function value (__m128).
{
  *s = jbm_4xf32_sinwc (x);
  *c = jbm_4xf32_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (__m128).
 *
 * \return reduced vector (__m128).
 */
static inline __m128
jbm_4xf32_trig (const __m128 x, ///< __m128 vector.
                __m128i *q)     ///< quadrant (__m128i).
{
  __m128 y;
  y = _mm_round_ps (_mm_mul_ps (x, _mm_set1_ps (1.f / M_PI_2f)),
                    _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  *q = _mm_cvtps_epi32 (y);
  return _mm_fnmadd_ps (y, _mm_set1_ps (M_PI_2f), x);
}

/**
 * Function to calculate the function sin(x) from jbm_4xf32_sinwc and
 * jbm_4xf32_coswc approximations (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_sin (const __m128 x)  ///< __m128 vector.
{
  __m128 y, s, c;
  __m128i q;
  y = jbm_4xf32_trig (x, &q);
  jbm_4xf32_sincoswc (y, &s, &c);
  y = _mm_blendv_ps
    (s, c,
     _mm_castsi128_ps (_mm_slli_epi32 (_mm_and_si128 (q, _mm_set1_epi32 (1)),
                                       31)));
  return
    _mm_xor_ps
    (y, _mm_castsi128_ps (_mm_slli_epi32 (_mm_and_si128 (q, _mm_set1_epi32 (2)),
                                          30)));
}

/**
 * Function to calculate the function cos(x) from jbm_4xf32_sinwc and
 * jbm_4xf32_coswc approximations (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_cos (const __m128 x)  ///< __m128 vector.
{
  const __m128i v1 = _mm_set1_epi32 (1);
  __m128 y, s, c;
  __m128i q;
  y = jbm_4xf32_trig (x, &q);
  jbm_4xf32_sincoswc (y, &s, &c);
  y = _mm_blendv_ps
    (c, s, _mm_castsi128_ps (_mm_slli_epi32 (_mm_and_si128 (q, v1), 31)));
  return
    _mm_xor_ps
    (y, _mm_castsi128_ps
     (_mm_slli_epi32 (_mm_and_si128 (_mm_add_epi32 (q, v1),
                                     _mm_set1_epi32 (2)), 30)));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_4xf32_sinwc and jbm_4xf32_coswc approximations (__m128).
 */
static inline void
jbm_4xf32_sincos (const __m128 x,
                  ///< __m128 vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m128 *s,    ///< pointer to the sin function value (__m128).
                  __m128 *c)    ///< pointer to the cos function value (__m128).
{
  const __m128 pi2 = _mm_set1_ps (2.f * M_PIf);
  const __m128 z = _mm_setzero_ps ();
  __m128 y, m, s1, c1, s2, c2;
  y = jbm_4xf32_mod (x, pi2);
  jbm_4xf32_sincoswc (_mm_sub_ps (y, pi2), &s1, &c1);
  jbm_4xf32_sincoswc (_mm_sub_ps (y, _mm_set1_ps (3.f * M_PI_2f)), &c2, &s2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (7.f * M_PI_4f));
  s1 = _mm_blendv_ps (s1, _mm_sub_ps (z, s2), m);
  c1 = _mm_blendv_ps (c1, c2, m);
  jbm_4xf32_sincoswc (_mm_sub_ps (_mm_set1_ps (M_PIf), y), &s2, &c2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (5.f * M_PI_4f));
  s1 = _mm_blendv_ps (s1, s2, m);
  c1 = _mm_blendv_ps (c1, _mm_sub_ps (z, c2), m);
  jbm_4xf32_sincoswc (_mm_sub_ps (_mm_set1_ps (M_PI_2f), y), &c2, &s2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (3.f * M_PI_4f));
  s1 = _mm_blendv_ps (s1, s2, m);
  c1 = _mm_blendv_ps (c1, c2, m);
  jbm_4xf32_sincoswc (y, &s2, &c2);
  m = _mm_cmplt_ps (y, _mm_set1_ps (M_PI_4f));
  *s = _mm_blendv_ps (s1, s2, m);
  *c = _mm_blendv_ps (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_4xf32_sincos function
 * (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_tan (const __m128 x)  ///< __m128 vector.
{
  __m128 s, c;
  jbm_4xf32_sincos (x, &s, &c);
  return _mm_div_ps (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m128).
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_atanwc (const __m128 x)
                  ///< __m128 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_ps (x, jbm_4xf32_rational_4_2 (jbm_4xf32_sqr (x), K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_4xf32_atanwc
 * function (__m128).
 *
 * \return function value (in [-pi/2,pi/2]) (__m128).
 */
static inline __m128
jbm_4xf32_atan (const __m128 x) ///< __m128 vector.
{
  __m128 f, ax, m;
  ax = jbm_4xf32_abs (x);
  m = _mm_cmpgt_ps (ax, _mm_set1_ps (1.f));
  ax = _mm_blendv_ps (ax, jbm_4xf32_reciprocal (ax), m);
  f = jbm_4xf32_atanwc (ax);
  f = _mm_blendv_ps (f, _mm_sub_ps (_mm_set1_ps (M_PI_2f), f), m);
  return jbm_4xf32_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_4xf32_atan
 * function (__m128).
 *
 * \return function value (in [-pi,pi]) (__m128).
 */
static inline __m128
jbm_4xf32_atan2 (const __m128 y,        ///< __m128 y component.
                 const __m128 x)        ///< __m128 x component.
{
  __m128 f, g;
  f = jbm_4xf32_atan (_mm_div_ps (y, x));
  g = _mm_add_ps (f, jbm_4xf32_copysign (_mm_set1_ps (M_PIf), y));
  return _mm_blendv_ps (f, g, _mm_cmplt_ps (x, _mm_setzero_ps ()));
}

/**
 * Function to calculate the function asin(x) using the jbm_4xf32_atan function
 * (__m128).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline __m128
jbm_4xf32_asin (const __m128 x) ///< __m128 vector.
{
  return
    jbm_4xf32_atan (_mm_div_ps
                    (x, _mm_sqrt_ps (_mm_fnmadd_ps (x, x, _mm_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_4xf32_atan function
 * (__m128).
 *
 * \return function value (in [0,pi]) (__m128).
 */
static inline __m128
jbm_4xf32_acos (const __m128 x) ///< __m128 vector.
{
  __m128 f;
  f =
    jbm_4xf32_atan (_mm_div_ps
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
jbm_4xf32_sinh (const __m128 x) ///< __m128 number.
{
  __m128 f;
  f = jbm_4xf32_exp (x);
  return _mm_mul_ps (_mm_set1_ps (0.5f),
                     _mm_sub_ps (f, jbm_4xf32_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_cosh (const __m128 x) ///< __m128 number.
{
  __m128 f;
  f = jbm_4xf32_exp (x);
  return _mm_mul_ps (_mm_set1_ps (0.5f),
                     _mm_add_ps (f, jbm_4xf32_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_tanh (const __m128 x) ///< __m128 number.
{
  __m128 f, fi;
  f = jbm_4xf32_exp (x);
  fi = jbm_4xf32_reciprocal (f);
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
jbm_4xf32_asinh (const __m128 x)        ///< __m128 number.
{
  return
    jbm_4xf32_log (_mm_add_ps
                   (x, _mm_sqrt_ps (_mm_fmadd_ps (x, x, _mm_set1_ps (1.f)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_acosh (const __m128 x)        ///< __m128 number.
{
  return
    jbm_4xf32_log (_mm_add_ps
                   (x, _mm_sqrt_ps (_mm_fmsub_ps (x, x, _mm_set1_ps (1.f)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_atanh (const __m128 x)        ///< __m128 number.
{
  const __m128 u = _mm_set1_ps (1.f);
  return _mm_mul_ps (_mm_set1_ps (0.5f),
                     jbm_4xf32_log (_mm_div_ps (_mm_add_ps (u, x),
                                                _mm_sub_ps (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m128)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_erfwc (const __m128 x)
                 ///< __m128 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_ps (x, jbm_4xf32_polynomial_5 (jbm_4xf32_sqr (x), K_ERFWC_F32));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m128)
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_erfcwc (const __m128 x)
                  ///< __m128 vector \f$\in\left[1,\infty\right]\f$.
{
  __m128 f, x2;
  x2 = jbm_4xf32_sqr (x);
  f = _mm_mul_ps (jbm_4xf32_rational_7_4 (jbm_4xf32_reciprocal (x),
                                          K_ERFCWC_F32),
                  _mm_div_ps (x, jbm_4xf32_exp (x2)));
  return _mm_blendv_ps (f, _mm_setzero_ps (),
                        _mm_cmpgt_ps (x, _mm_set1_ps (K_ERFC_MAX_F32)));
}

/**
 * Function to calculate the function erf(x) using jbm_4xf32_erfwc and
 * jbm_4xf32_erfcwc.
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_erf (const __m128 x)  ///< __m128 vector.
{
  const __m128 u = _mm_set1_ps (1.f);
  __m128 ax, f;
  ax = jbm_4xf32_abs (x);
  f = jbm_4xf32_copysign (_mm_sub_ps (u, jbm_4xf32_erfcwc (ax)), x);
  return _mm_blendv_ps (f, jbm_4xf32_erfwc (x), _mm_cmplt_ps (ax, u));

}

/**
 * Function to calculate the function erfc(x) using jbm_4xf32_erfwc and
 * jbm_4xdbl_erfcwc.
 *
 * \return function value (__m128).
 */
static inline __m128
jbm_4xf32_erfc (const __m128 x) ///< __m128 vector.
{
  const __m128 u2 = _mm_set1_ps (2.f);
  const __m128 u = _mm_set1_ps (1.f);
  __m128 ax, cwc, wc;
  ax = jbm_4xf32_abs (x);
  cwc = jbm_4xf32_erfcwc (ax);
  wc = _mm_sub_ps (u, jbm_4xf32_erfwc (x));
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
jbm_solve_quadratic_reduced_4xf32 (const __m128 a,
///< __m128 vector of 1st order coefficient of the equations.
                                   const __m128 b,
///< __m128 vector of 0th order coefficient of the equations.
                                   const __m128 x1,
///< __m128 vector of left limits of the solution intervals.
                                   const __m128 x2)
///< __m128 vector of right limits of the solution intervals.
{
  __m128 ka, kb, k1, k2;
  k1 = _mm_set1_ps (-0.5f);
  ka = _mm_mul_ps (a, k1);
  kb = _mm_sqrt_ps (_mm_sub_ps (jbm_4xf32_sqr (ka), b));
  k1 = _mm_add_ps (ka, kb);
  k2 = _mm_sub_ps (ka, kb);
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
jbm_4xf32_solve_quadratic (const __m128 a,
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
  k2 = _mm_div_ps (jbm_4xf32_opposite (c), b);
  return _mm_blendv_ps (k1, k2, jbm_4xf32_small (a));
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
  l1 = _mm_sqrt_ps (jbm_4xf32_opposite (k1));
  l0 = _mm_mul_ps (jbm_4xf32_acos (_mm_div_ps (k0, k3)), c_3);
  l1 = _mm_add_ps (l1, l1);
  l2 = _mm_fmsub_ps (l1, jbm_4xf32_cos (k0), a3);
  l3 = _mm_fmsub_ps (l1, jbm_4xf32_cos (_mm_add_ps (l0, c2p_3)), a3);
  l3 = _mm_blendv_ps (l3, l2,
                      _mm_or_ps (_mm_cmplt_ps (l2, x1), _mm_cmpgt_ps (l2, x2)));
  l4 = _mm_fmsub_ps (l1, jbm_4xf32_cos (_mm_sub_ps (l0, c2p_3)), a);
  l4 = _mm_blendv_ps (l4, l3,
                      _mm_or_ps (_mm_cmplt_ps (l3, x1), _mm_cmpgt_ps (l3, x2)));
  k1 = _mm_sqrt_ps (k2);
  l5 = _mm_add_ps (k0, k1);
  l5 = jbm_4xf32_cbrt (k2);
  k0 = _mm_sub_ps (k0, k1);
  l5 = _mm_add_ps (l5, _mm_sub_ps (jbm_4xf32_cbrt (k0), a3));
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
jbm_4xf32_solve_cubic (const __m128 a,
///< __m128 vector of 3rd order coefficient of the equations.
                       const __m128 b,
///< __m128 vector of 2nd order coefficient of the equations.
                       const __m128 c,
///< __m128 vector of 1st order coefficient of the equations.
                       const __m128 d,
///< __m128 vector of 0th order coefficient of the equations.
                       const __m128 x1,
///< __m128 vector of left limits of the solution intervals.
                       const __m128 x2)
///< __m128 vector of right limits of the solution intervals.
{
  return
    _mm_blendv_ps (jbm_solve_cubic_reduced_4xf32 (_mm_div_ps (b, a),
                                                  _mm_div_ps (c, a),
                                                  _mm_div_ps (d, a), x1, x2),
                   jbm_4xf32_solve_quadratic (b, c, d, x1, x2),
                   jbm_4xf32_small (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m128).
 *
 * \return flux limiter function value.
 */
static inline __m128
jbm_4xf32_flux_limiter_total (const __m128 d1 __attribute__((unused)),
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
jbm_4xf32_flux_limiter_null (const __m128 d1 __attribute__((unused)),
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
jbm_4xf32_flux_limiter_centred (const __m128 d1,
                                ///< 1st flux limiter function parameter.
                                const __m128 d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm_blendv_ps (_mm_div_ps (d1, d2), _mm_setzero_ps (),
                        jbm_4xf32_small (d2));
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
jbm_4xf32_flux_limiter_superbee (const __m128 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128 d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_div_ps (d1, d2);
  r = _mm_max_ps (_mm_min_ps (jbm_4xf32_dbl (r), _mm_set1_ps (1.f)),
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
jbm_4xf32_flux_limiter_minmod (const __m128 d1,
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
jbm_4xf32_flux_limiter_VanLeer (const __m128 d1,
                                ///< 1st flux limiter function parameter.
                                const __m128 d2)
                              ///< 2nd flux limiter function parameter.
{
  __m128 r, k;
  r = _mm_div_ps (d1, d2);
  k = jbm_4xf32_abs (r);
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
jbm_4xf32_flux_limiter_VanAlbada (const __m128 d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m128 d2)
                                ///< 2nd flux limiter function parameter.
{
  __m128 r, k;
  r = _mm_div_ps (d1, d2);
  k = jbm_4xf32_sqr (r);
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
jbm_4xf32_flux_limiter_minsuper (const __m128 d1,
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
jbm_4xf32_flux_limiter_supermin (const __m128 d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128 d2)
                                 ///< 2nd flux limiter function parameter.
{
  __m128 r;
  r = _mm_div_ps (d1, d2);
  r = _mm_min_ps (jbm_4xf32_dbl (r), _mm_set1_ps (1.f));
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
jbm_4xf32_flux_limiter_monotonized_central (const __m128 d1,
///< 1st flux limiter function parameter.
                                            const __m128 d2)
///< 2nd flux limiter function parameter.
{
  __m128 r, rm;
  r = _mm_div_ps (d1, d2);
  rm = _mm_mul_ps (_mm_set1_ps (0.5f), _mm_add_ps (r, _mm_set1_ps (1.f)));
  rm = _mm_blendv_ps (_mm_set1_ps (2.f), rm,
                      _mm_cmplt_ps (r, _mm_set1_ps (3.f)));
  rm = _mm_blendv_ps (rm, jbm_4xf32_dbl (r),
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
jbm_4xf32_flux_limiter_mean (const __m128 d1,
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
jbm_4xf32_flux_limiter (const __m128 d1,
                        ///< 1st flux limiter function parameter.
                        const __m128 d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_4xf32_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_4xf32_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_4xf32_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_4xf32_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_4xf32_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_4xf32_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_4xf32_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_4xf32_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_4xf32_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_4xf32_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_4xf32_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m128).
 *
 * \return __m128 vector of integral values.
 */
static inline __m128
jbm_4xf32_integral (__m128 (*f) (__m128),
                    ///< pointer to the function to integrate.
                    const __m128 x1,    ///< left limit of the interval.
                    const __m128 x2)    ///< right limit of the interval.
{
  __m128 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m128 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm_set1_ps (0.5f);
  dx = _mm_mul_ps (h, _mm_sub_ps (x2, x1));
  x = _mm_mul_ps (h, _mm_add_ps (x2, x1));
  k = _mm_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[0]);
  k = _mm_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm_set1_ps (JBM_INTEGRAL_GAUSS_B_F32[i]);
      k2 = _mm_mul_ps (k2, dx);
      f1 = f (_mm_sub_ps (x, k2));
      f2 = f (_mm_add_ps (x, k2));
      h = _mm_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[i]);
      k = _mm_fmadd_ps (h, _mm_add_ps (f1, f2), k);
    }
#endif
  return _mm_mul_ps (k, dx);
}

/**
 * Function to calculate the additive reduction value of a __m128d vector.
 *
 * \return additive reduction (double).
 */
static inline double
jbm_2xf64_reduce_add (const __m128d x)  ///< __m128d vector.
{
  return _mm_cvtsd_f64 (_mm_hadd_pd (x, x));
}

/**
 * Function to calculate the maximum reduction value of a __m128d vector.
 *
 * \return maximum reduction (double).
 */
static inline double
jbm_2xf64_reduce_max (const __m128d x)  ///< __m128d vector.
{
  return _mm_cvtsd_f64 (_mm_max_pd (x, _mm_unpackhi_pd (x, x)));
}

/**
 * Function to calculate the minimum reduction value of a __m128d vector.
 *
 * \return minimum reduction (double).
 */
static inline double
jbm_2xf64_reduce_min (const __m128d x)  ///< __m128d vector.
{
  return _mm_cvtsd_f64 (_mm_min_pd (x, _mm_unpackhi_pd (x, x)));
}

/**
 * Function to calculate the maximum and minimum reduction value of a
 * __m128d vector.
 */
static inline void
jbm_2xf64_reduce_maxmin (const __m128d x,       ///< __m128d vector.
                         double *max,
                         ///< pointer to the maximum value (double).
                         double *min)
                         ///< pointer to the maximum value (double).
{
  __m128d y = _mm_unpackhi_pd (x, x);
  *max = _mm_cvtsd_f64 (_mm_max_pd (x, y));
  *min = _mm_cvtsd_f64 (_mm_min_pd (x, y));
}

/**
 * Function to calculate the additive inverse value of a __m128d vector.
 *
 * \return negative value vector (__m128d).
 */
static inline __m128d
jbm_2xf64_opposite (const __m128d x)    ///< __m128d vector.
{
  JBM2xF64 y;
  y.i = JBM_2xF64_BITS_SIGN;
  return _mm_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m128d vector.
 *
 * \return reciprocal value vector (__m128d).
 */
static inline __m128d
jbm_2xf64_reciprocal (const __m128d x)  ///< __m128d vector.
{
  return _mm_div_pd (_mm_set1_pd (1.), x);
}

/**
 * Function to calculate the sign of a __m128d vector.
 *
 * \return sign vector (__m128d).
 */
static inline __m128d
jbm_2xf64_sign (const __m128d x)        ///< __m128d vector.
{
  JBM2xF64 y;
  y.x = x;
  y.i = _mm_and_si128 (y.i, JBM_2xF64_BITS_SIGN);
  y.i = _mm_and_si128 (y.i, JBM_2xF64_BITS_1);
  return y.x;
}

/**
 * Function to calculate the absolute value of a __m128d vector.
 *
 * \return absolute value vector.
 */
static inline __m128d
jbm_2xf64_abs (const __m128d x)
{
  JBM2xF64 y;
  y.i = JBM_2xF64_BITS_SIGN;
  return _mm_andnot_pd (y.x, x);
}

/**
 * Function to copy the sign of a __m128d vector to another __m128d vector.
 *
 * \return __m128d vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m128d
jbm_2xf64_copysign (const __m128d x,
///< __m128 vector to preserve magnitude.
                    const __m128d y)    ///< __m128d vector to preserve sign.
{
  JBM2xF64 m;
  m.i = JBM_2xF64_BITS_SIGN;
  return _mm_or_pd (jbm_2xf64_abs (x), _mm_and_pd (y, m.x));
}

/**
 * Function to calculate the hypot function (__m128d).
 *
 * \return function value vector (__m128d).
 */
static inline __m128d
jbm_2xf64_hypot (const __m128d x,       ///< 1st __m128d vector.
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
jbm_2xf64_mod (const __m128d x, ///< dividend (__m128d).
               const __m128d d) ///< divisor (__m128d).
{
  __m128d r;
  r = _mm_floor_pd (_mm_div_pd (x, d));
  return _mm_blendv_pd (_mm_fnmadd_pd (r, d, x),
                        _mm_mul_pd (d, _mm_set1_pd (0.5)),
                        _mm_cmpgt_pd (jbm_2xf64_abs (r),
                                      _mm_set1_pd (1. / DBL_EPSILON)));
}

/**
 * Function to implement the standard frexp function (__m128d).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline __m128d
jbm_2xf64_frexp (const __m128d x,       ///< __m128d vector.
                 __m128i *e)    ///< pointer to the extracted exponents vector.
{
  const __m128i zi = _mm_setzero_si128 ();
  const __m128i bias = JBM_2xF64_BIAS;
  const __m128i sign_mask = JBM_2xF64_BITS_SIGN;
  const __m128i mant_mask = JBM_2xF64_BITS_MANTISSA;
  JBM2xF64 y, z;
  __m128i exp, is_z, is_sub, is_nan, is_finite;
  // y=abs(x)
  y.x = jbm_2xf64_abs (x);
  // masks
  is_z = _mm_cmpeq_epi64 (y.i, zi);
  is_nan = _mm_cmpgt_epi64 (y.i, _mm_set1_epi64x (JBM_F64_BITS_EXPONENT - 1ll));
  is_finite = _mm_andnot_si128 (_mm_or_si128 (is_z, is_nan),
                                _mm_set1_epi64x (-1ll));
  // extract exponent
  exp = _mm_srli_epi64 (y.i, 52);
  // subnormals
  is_sub = _mm_and_si128 (is_finite, _mm_cmpeq_epi64 (exp, zi));
  y.x
    = _mm_blendv_pd (y.x, _mm_mul_pd (y.x, _mm_set1_pd (0x1p52)),
                     _mm_castsi128_pd (is_sub));
  exp
    = _mm_blendv_epi8 (exp, _mm_sub_epi64 (_mm_srli_epi64 (y.i, 52),
                                           _mm_set1_epi64x (52ll)), is_sub);
  // exponent
  *e = _mm_blendv_epi8 (zi, _mm_sub_epi64 (exp, bias), is_finite);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm_or_si128 (_mm_and_si128 (z.i, sign_mask),
                      _mm_or_si128 (_mm_set1_epi64x (JBM_F64_BIAS << 52),
                                    _mm_and_si128 (y.i, mant_mask)));
  return _mm_blendv_pd (x, y.x, _mm_castsi128_pd (is_finite));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m128i)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_exp2n (const __m128i e)       ///< exponent vector (__m128i).
{
  const __m128i v1023 = _mm_set1_epi64x (1023ll);
  __m128d x;
  // normal and subnormal
  x = _mm_blendv_pd
    (_mm_castsi128_pd
     (_mm_slli_epi64 (_mm_add_epi64 (e, v1023), 52)),
     _mm_castsi128_pd
     (_mm_sllv_epi64 (_mm_set1_epi64x (1),
                      _mm_add_epi64 (e, _mm_set1_epi64x (1074ll)))),
     _mm_castsi128_pd (_mm_cmpgt_epi64 (_mm_set1_epi64x (-1022ll), e)));
  // zero
  x = _mm_blendv_pd
    (x, _mm_setzero_pd (),
     _mm_castsi128_pd (_mm_cmpgt_epi64 (_mm_set1_epi64x (-1075ll), e)));
  // infinity
  return
    _mm_blendv_pd (x, _mm_set1_pd (INFINITY),
                   _mm_castsi128_pd (_mm_cmpgt_epi64 (e, v1023)));
}

/**
 * Function to implement the standard ldexp function (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_ldexp (const __m128d x,       ///< __m128d vector.
                 const __m128i e)       ///< exponent vector (__m128i).
{
  return _mm_mul_pd (x, jbm_2xf64_exp2n (e));
}

/**
 * Function to check small __m128d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m128d
jbm_2xf64_small (const __m128d x)       ///< __m128d vector.
{
  return _mm_cmplt_pd (jbm_2xf64_abs (x), _mm_set1_pd (FLT_EPSILON));
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
jbm_2xf64_modmin (const __m128d a,      ///< 1st __m128d vector.
                  const __m128d b)      ///< 2nd __m128d vector.
{
  const __m128d z = _mm_setzero_pd ();
  __m128d aa, ab, y;
  ab = _mm_mul_pd (a, b);
  y = _mm_blendv_pd (a, z, _mm_cmple_pd (ab, z));
  aa = jbm_2xf64_abs (y);
  ab = jbm_2xf64_abs (b);
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
jbm_2xf64_dbl (const __m128d x) ///< __m128d vector.
{
  return _mm_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m128d vector.
 *
 * \return __m128d vector square.
 */
static inline __m128d
jbm_2xf64_sqr (const __m128d x) ///< __m128d vector.
{
  return _mm_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m128d vectors of 2D points.
 *
 * \return __m128d vector of y-coordinates of the extrapolated points.
 */
static inline __m128d
jbm_2xf64_extrapolate (const __m128d x,
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
jbm_2xf64_interpolate (const __m128d x,
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
  k = jbm_2xf64_extrapolate (x, x1, x2, y1, y2);
  k = _mm_blendv_pd (y1, k, _mm_cmpgt_pd (x, x1));
  return _mm_blendv_pd (y2, k, _mm_cmplt_pd (x, x2));
}

/**
 * Function to calculate the length of a __m128d vector of 2D segments.
 *
 * \return __m128d vector of segment lengths.
 */
static inline __m128d
jbm_2xf64_v2_length (const __m128d x1,
///< __m128d vector of x-coordinates of the 1st points defining the segment.
                     const __m128d y1,
///< __m128d vector of y-coordinates of the 1st points defining the segment.
                     const __m128d x2,
///< __m128d vector of x-coordinates of the 2nd points defining the segment.
                     const __m128d y2)
///< __m128d vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_2xf64_hypot (_mm_sub_pd (x2, x1), _mm_sub_pd (y2, y1));
}

/**
 * Function to calculate the length of a __m128d vector of 3D segments.
 *
 * \return __m128d vector of segment lengths.
 */
static inline __m128d
jbm_2xf64_v3_length (const __m128d x1,
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
  dx = jbm_2xf64_sqr (_mm_sub_pd (x2, x1));
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
jbm_2xf64_polynomial_1 (const __m128d x,        ///< __m128d vector.
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
jbm_2xf64_polynomial_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 3rd order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 4th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_4 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 5th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_5 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 6th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_6 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 7th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_7 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 8th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_8 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 9th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_9 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 10th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_10 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 11th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_11 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 12th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_12 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 13th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_13 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 14th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_14 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 15th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_15 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 16th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_16 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 17th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_17 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 18th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_18 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 19th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_19 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 20th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_20 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 21th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_21 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 22th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_22 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 23th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_23 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 24th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_24 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 25th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_25 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_24 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 26th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_26 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_25 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 27th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_27 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_26 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 28th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_28 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_27 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 29th order polynomial (__m128d).
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_2xf64_polynomial_29 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_fmadd_pd (x, jbm_2xf64_polynomial_28 (x, p + 1),
                       _mm_set1_pd (p[0]));
}

/**
 * Function to calculate a 0th+1st order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_1_0 (const __m128d x,        ///< __m128d vector.
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
jbm_2xf64_rational_2_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+1st order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_2_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[2]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_3_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_3_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_3_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[3]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_4_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_4_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_4_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_4_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[4]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_5_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_5_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_5_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_5_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_5_4 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[5]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_6_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_6_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_6_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_6_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_6_4 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_6_5 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[6]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_4 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_5 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_7_6 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[7]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_4 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_5 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_6 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_8_7 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[8]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_0 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_1 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_2 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_3 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_4 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_5 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_6 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_7 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_9_8 (const __m128d x,        ///< __m128d vector.
                        const double *p)        ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[9]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_10_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[10]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_11_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[11]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_12_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[12]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_13_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[13]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_14_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[14]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_15_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[15]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_16_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[16]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_17_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[17]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_18_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[18]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_19_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[19]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_20_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[20]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_21_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[21]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_22_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[22]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_23_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[23]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_24_23 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_23 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[24]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_24 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_23 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_23 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_25_24 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_24 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[25]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_25 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_24 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_23 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_23 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_24 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_24 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_26_25 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_25 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[26]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_26 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_25 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_24 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_23 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_23 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_24 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_24 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_25 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_25 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 26),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_27_26 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_26 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[27]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+28th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_27 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_26 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_25 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_24 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_23 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_23 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_24 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_24 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_25 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_25 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 26),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_26 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_26 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 27),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_28_27 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_27 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[28]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 0th+29th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_0 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (_mm_set1_pd (p[0]),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_28 (x, p + 1),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_1 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_1 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_27 (x, p + 2),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 2nd+27th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_2 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_2 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_26 (x, p + 3),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 3rd+26th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_3 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_3 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_25 (x, p + 4),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 4th+25th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_4 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_4 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_24 (x, p + 5),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 5th+24th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_5 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_5 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_23 (x, p + 6),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 6th+23th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_6 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_6 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_22 (x, p + 7),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 7th+22th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_7 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_7 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_21 (x, p + 8),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 8th+21th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_8 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_8 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_20 (x, p + 9),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 9th+20th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_9 (const __m128d x,       ///< __m128d vector.
                         const double *p)       ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_9 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_19 (x, p + 10),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 10th+19th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_10 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_10 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_18 (x, p + 11),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 11th+18th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_11 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_11 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_17 (x, p + 12),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 12th+17th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_12 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_12 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_16 (x, p + 13),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 13th+16th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_13 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_13 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_15 (x, p + 14),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 14th+15th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_14 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_14 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_14 (x, p + 15),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 15th+14th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_15 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_15 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_13 (x, p + 16),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 16th+13th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_16 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_16 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_12 (x, p + 17),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 17th+12th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_17 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_17 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_11 (x, p + 18),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 18th+11th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_18 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_18 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_10 (x, p + 19),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 19th+10th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_19 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_19 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_9 (x, p + 20),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 20th+9th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_20 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_20 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_8 (x, p + 21),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 21th+8th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_21 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_21 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_7 (x, p + 22),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 22th+7th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_22 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_22 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_6 (x, p + 23),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 23th+6th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_23 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_23 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_5 (x, p + 24),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 24th+5th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_24 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_24 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_4 (x, p + 25),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 25th+4th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_25 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_25 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_3 (x, p + 26),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 26th+3rd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_26 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_26 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_2 (x, p + 27),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 27th+2nd order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_27 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_27 (x, p),
                     _mm_fmadd_pd (x, jbm_2xf64_polynomial_1 (x, p + 28),
                                   _mm_set1_pd (1.)));
}

/**
 * Function to calculate a 1st+28th order rational (__m128d).
 *
 * \return __m128d vector of rational values.
 */
static inline __m128d
jbm_2xf64_rational_29_28 (const __m128d x,      ///< __m128d vector.
                          const double *p)      ///< array of coefficients.
{
  return _mm_div_pd (jbm_2xf64_polynomial_28 (x, p),
                     _mm_fmadd_pd (x, _mm_set1_pd (p[29]), _mm_set1_pd (1.)));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_cbrtwc (const __m128d x)
                  ///< __m128d vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_2xf64_rational_11_6 (x, K_CBRTWC_F64);
}

/**
 * Function to calculate the function cbrt(x) (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_cbrt (const __m128d x)        ///< __m128d vector.
{
  const __m128d cbrt2 = JBM_2xF64_CBRT2;
  const __m128d cbrt4 = JBM_2xF64_CBRT4;
  const __m128i v3 = _mm_set1_epi32 (3);
  const __m128i v2 = _mm_set1_epi64x (2);
  const __m128i v1 = _mm_set1_epi64x (1);
  __m128d y;
  __m128i e, e3, r, n;
  y = jbm_2xf64_frexp (jbm_2xf64_abs (x), &e);
  e3 = _mm_mul_epu32 (e, _mm_set1_epi32 (0x55555556));
  e3 = _mm_srli_epi64 (e3, 32);
  r = _mm_sub_epi32 (e, _mm_mullo_epi32 (e3, v3));
  n = _mm_srai_epi32 (r, 31);
  r = _mm_add_epi32 (r, _mm_and_si128 (n, v3));
  e3 = _mm_sub_epi32 (e3, _mm_and_si128 (n, _mm_set1_epi32 (1)));
  y = jbm_2xf64_ldexp (jbm_2xf64_cbrtwc (y), e3);
  y = _mm_blendv_pd (y, _mm_mul_pd (y, cbrt2),
                     _mm_castsi128_pd (_mm_cmpeq_epi64 (r, v1)));
  y = _mm_blendv_pd (y, _mm_mul_pd (y, cbrt4),
                     _mm_castsi128_pd (_mm_cmpeq_epi64 (r, v2)));
  return jbm_2xf64_copysign (y, x);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_expm1wc (const __m128d x)
///< __m128d vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return _mm_mul_pd (x, jbm_2xf64_rational_8_2 (x, K_EXPM1WC_F64));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (__m128d).
 *
 * \return function value.
 */
static inline __m128d
jbm_2xf64_exp2wc (const __m128d x)
                  ///< __m128d vector \f$\in[\frac12,1]\f$.
{
  return jbm_2xf64_rational_9_4 (x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_2xf64 and
 * jbm_2xf64_exp2n functions.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_exp2 (const __m128d x)        ///< __m128d vector.
{
  __m128d y, f;
  __m128i i;
  y = _mm_floor_pd (x);
  f = _mm_sub_pd (x, y);
#ifdef __AVX512F__
  i = _mm_cvttpd_epi64 (y);
#else
  i = _mm_cvtepi32_epi64 (_mm_cvttpd_epi32 (y));
#endif
  return _mm_mul_pd (jbm_2xf64_exp2n (i), jbm_2xf64_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_2xf64_exp2 function.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_exp (const __m128d x) ///< __m128d vector.
{
  return jbm_2xf64_exp2 (_mm_mul_pd (x, _mm_set1_pd (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_2xf64_exp2
 * function (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_exp10 (const __m128d x)       ///< __m128d vector.
{
  return jbm_2xf64_exp2 (_mm_mul_pd (x, _mm_set1_pd (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_2xf64_expm1wc and
 * jbm_2xf64_exp functions (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_expm1 (const __m128d x)       ///< __m128d vector.
{
  return _mm_blendv_pd (_mm_sub_pd (jbm_2xf64_exp (x), _mm_set1_pd (1.)),
                        jbm_2xf64_expm1wc (x),
                        _mm_cmplt_pd (jbm_2xf64_abs (x),
                                      _mm_set1_pd (M_LN2 / 2.)));
}

/**
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_log2wc (const __m128d x)      ///< __m128d vector \f$\in[0.5,1]\f$.
{
  return _mm_mul_pd (x, jbm_2xf64_rational_11_5 (x, K_LOG2WC_F64));
}

/**
 * Function to calculate the function log2(x) using jbm_2xf64_log2wc and
 * jbm_2xdbl_frexp.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_log2 (const __m128d x)        ///< __m128d vector.
{
  const __m128d z = _mm_setzero_pd ();
  __m128d y, m;
  __m128i e;
  y = jbm_2xf64_frexp (x, &e);
  m = _mm_cmplt_pd (y, _mm_set1_pd (M_SQRT1_2));
  y = _mm_add_pd (y, _mm_and_pd (m, y));
  e = _mm_sub_epi64 (e, _mm_and_si128 (_mm_castpd_si128 (m),
                                       _mm_set1_epi64x (1ll)));
  y = _mm_add_pd (jbm_2xf64_log2wc (_mm_sub_pd (y, _mm_set1_pd (1.))),
                  _mm_cvtepi64_pd (e));
  y = _mm_blendv_pd (y, _mm_set1_pd (-INFINITY), _mm_cmpeq_pd (x, z));
  y = _mm_blendv_pd (y, _mm_set1_pd (NAN), _mm_cmplt_pd (x, z));
  y = _mm_blendv_pd (y, x, _mm_cmpeq_pd (x, _mm_set1_pd (INFINITY)));
  return _mm_blendv_pd (y, x, _mm_cmpunord_pd (x, x));
}

/**
 * Function to calculate the function log(x) using jbm_2xf64_log2 (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_log (const __m128d x) ///< __m128d vector.
{
  return _mm_mul_pd (jbm_2xf64_log2 (x), _mm_set1_pd (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_2xf64_log2 (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_log10 (const __m128d x)       ///< __m128d vector.
{
  return _mm_mul_pd (jbm_2xf64_log2 (x), _mm_set1_pd (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (__m128d).
 *
 * \return function value (__m128d) (__m128d).
 */
static inline __m128d
jbm_2xf64_pown (const __m128d x,        ///< __m128d vector.
                const int e)    ///< exponent (int).
{
  __m128d f, xn;
  unsigned int i;
  f = _mm_set1_pd (1.);
  if (e < 0)
    xn = _mm_div_pd (f, x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_2xf64_sqr (xn))
    if (i & 1)
      f = _mm_mul_pd (f, xn);
  return f;
}

/**
 * Function to calculate the function f64 using the jbm_2xf64_exp2 and
 * jbm_2xf64_log2 functions.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_pow (const __m128d x, ///< __m128d vector.
               const __m128d e) ///< exponent (__m128d).
{
  return jbm_2xf64_exp2 (_mm_mul_pd (e, jbm_2xf64_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (__m128d)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_sinwc (const __m128d x)
                 ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return
    _mm_mul_pd (x, jbm_2xf64_polynomial_6 (jbm_2xf64_sqr (x), K_SINWC_F64));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_coswc (const __m128d x)
                 ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_2xf64_polynomial_6 (jbm_2xf64_sqr (x), K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_2xf64_sinwc approximation (__m128d).
 */
static inline void
jbm_2xf64_sincoswc (const __m128d x,
                    ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    __m128d *s,
                    ///< pointer to the f64 function value (__m128d).
                    __m128d *c)
                    ///< pointer to the f64 function value (__m128d).
{
  *s = jbm_2xf64_sinwc (x);
  *c = jbm_2xf64_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (__m128d).
 *
 * \return reduced vector (__m128d).
 */
static inline __m128d
jbm_2xf64_trig (const __m128d x,        ///< __m128d vector.
                __m128i *q)     ///< quadrant (__m128i).
{
  __m128d y;
  y = _mm_round_pd (_mm_mul_pd (x, _mm_set1_pd (1. / M_PI_2)),
                    _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  *q = _mm_cvtpd_epi64 (y);
  return _mm_fnmadd_pd (y, _mm_set1_pd (M_PI_2), x);
}

/**
 * Function to calculate the function sin(x) from jbm_2xf64_sinwc and
 * jbm_2xf64_coswc approximations.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_sin (const __m128d x) ///< __m128d vector.
{
  const __m128d pi2 = _mm_set1_pd (2. * M_PI);
  __m128d y, s;
  y = jbm_2xf64_mod (x, pi2);
  s = jbm_2xf64_sinwc (_mm_sub_pd (y, pi2));
  s = _mm_blendv_pd (s,
                     jbm_2xf64_opposite
                     (jbm_2xf64_coswc
                      (_mm_sub_pd (_mm_set1_pd (3. * M_PI_2), y))),
                     _mm_cmplt_pd (y, _mm_set1_pd (7. * M_PI_4)));
  s = _mm_blendv_pd (s, jbm_2xf64_sinwc (_mm_sub_pd (_mm_set1_pd (M_PI), y)),
                     _mm_cmplt_pd (y, _mm_set1_pd (5. * M_PI_4)));
  s = _mm_blendv_pd (s, jbm_2xf64_coswc (_mm_sub_pd (_mm_set1_pd (M_PI_2), y)),
                     _mm_cmplt_pd (y, _mm_set1_pd (3. * M_PI_4)));
  return _mm_blendv_pd (s, jbm_2xf64_sinwc (y),
                        _mm_cmplt_pd (y, _mm_set1_pd (M_PI_4)));
}

/**
 * Function to calculate the function cos(x) from jbm_2xf64_sinwc and
 * jbm_2xf64_coswc approximations (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_cos (const __m128d x) ///< __m128d vector.
{
  const __m128d pi2 = _mm_set1_pd (2. * M_PI);
  __m128d y, c;
  y = jbm_2xf64_mod (x, pi2);
  c = jbm_2xf64_coswc (_mm_sub_pd (y, pi2));
  c = _mm_blendv_pd (c,
                     jbm_2xf64_sinwc
                     (_mm_sub_pd (y, _mm_set1_pd (3. * M_PI_2))),
                     _mm_cmplt_pd (y, _mm_set1_pd (7. * M_PI_4)));
  c = _mm_blendv_pd (c,
                     jbm_2xf64_opposite
                     (jbm_2xf64_coswc (_mm_sub_pd (_mm_set1_pd (M_PI), y))),
                     _mm_cmplt_pd (y, _mm_set1_pd (5. * M_PI_4)));
  c = _mm_blendv_pd (c, jbm_2xf64_sinwc (_mm_sub_pd (_mm_set1_pd (M_PI_2), y)),
                     _mm_cmplt_pd (y, _mm_set1_pd (3. * M_PI_4)));
  return _mm_blendv_pd (c, jbm_2xf64_coswc (y),
                        _mm_cmplt_pd (y, _mm_set1_pd (M_PI_4)));
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_2xf64_sinwc
 * and jbm_2xf64_coswc approximations (__m128d).
 */
static inline void
jbm_2xf64_sincos (const __m128d x,
                  ///< __m128d vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  __m128d *s,   ///< pointer to the f64 function value (__m128d).
                  __m128d *c)   ///< pointer to the f64 function value (__m128d).
{
  const __m128d pi2 = _mm_set1_pd (2. * M_PI);
  const __m128d z = _mm_setzero_pd ();
  __m128d y, m, s1, c1, s2, c2;
  y = jbm_2xf64_mod (x, pi2);
  jbm_2xf64_sincoswc (_mm_sub_pd (y, pi2), &s1, &c1);
  jbm_2xf64_sincoswc (_mm_sub_pd (y, _mm_set1_pd (3. * M_PI_2)), &c2, &s2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (7. * M_PI_4));
  s1 = _mm_blendv_pd (s1, _mm_sub_pd (z, s2), m);
  c1 = _mm_blendv_pd (c1, c2, m);
  jbm_2xf64_sincoswc (_mm_sub_pd (_mm_set1_pd (M_PI), y), &s2, &c2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (5. * M_PI_4));
  s1 = _mm_blendv_pd (s1, s2, m);
  c1 = _mm_blendv_pd (c1, _mm_sub_pd (z, c2), m);
  jbm_2xf64_sincoswc (_mm_sub_pd (_mm_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (3. * M_PI_4));
  s1 = _mm_blendv_pd (s1, s2, m);
  c1 = _mm_blendv_pd (c1, c2, m);
  jbm_2xf64_sincoswc (y, &s2, &c2);
  m = _mm_cmplt_pd (y, _mm_set1_pd (M_PI_4));
  *s = _mm_blendv_pd (s1, s2, m);
  *c = _mm_blendv_pd (c1, c2, m);
}

/**
 * Function to calculate the function tan(x) from jbm_2xf64_sinwc and
 * jbm_2xf64_coswc approximations.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_tan (const __m128d x) ///< __m128d vector.
{
  __m128d s, c;
  jbm_2xf64_sincos (x, &s, &c);
  return _mm_div_pd (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m128d).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_atanwc (const __m128d x)
                  ///< __m128d vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_pd (x, jbm_2xf64_rational_11_5 (jbm_2xf64_sqr (x), K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_2xf64_atanwc
 * function (__m128d).
 *
 * \return function value (__m128d in [-pi/2,pi/2]).
 */
static inline __m128d
jbm_2xf64_atan (const __m128d x)        ///< double number.
{
  __m128d f, ax, m;
  ax = jbm_2xf64_abs (x);
  m = _mm_cmpgt_pd (ax, _mm_set1_pd (1.));
  ax = _mm_blendv_pd (ax, jbm_2xf64_reciprocal (ax), m);
  f = jbm_2xf64_atanwc (ax);
  f = _mm_blendv_pd (f, _mm_sub_pd (_mm_set1_pd (M_PI_2), f), m);
  return jbm_2xf64_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_2xf64_atan
 * function (__m128d).
 *
 * \return function value (__m128d in [-pi,pi]).
 */
static inline __m128d
jbm_2xf64_atan2 (const __m128d y,       ///< __m128d y component.
                 const __m128d x)       ///< __m128d x component.
{
  const __m128d pi = _mm_set1_pd (M_PI);
  const __m128d z = _mm_setzero_pd ();
  __m128d f, g;
  f = jbm_2xf64_atan (_mm_div_pd (y, x));
  g = _mm_add_pd (f, jbm_2xf64_copysign (pi, y));
  return _mm_blendv_pd (f, g, _mm_cmplt_pd (x, z));
}

/**
 * Function to calculate the function asin(x) using the jbm_2xf64_atan function
 * (__m128d).
 *
 * \return function value (__m128d in [-pi/2,pi/2]).
 */
static inline __m128d
jbm_2xf64_asin (const __m128d x)        ///< __m128d number.
{
  return
    jbm_2xf64_atan (_mm_div_pd
                    (x, _mm_sqrt_pd (_mm_fnmadd_pd (x, x, _mm_set1_pd (1.)))));
}

/**
 * Function to calculate the function acos(x) using the jbm_2xf64_atan function
 * (__m128d).
 *
 * \return function value (__m128d in [0,pi]).
 */
static inline __m128d
jbm_2xf64_acos (const __m128d x)        ///< __m128d number.
{
  __m128d f;
  f =
    jbm_2xf64_atan (_mm_div_pd
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
jbm_2xf64_sinh (const __m128d x)        ///< __m128d number.
{
  __m128d f;
  f = jbm_2xf64_exp (x);
  return _mm_mul_pd (_mm_set1_pd (0.5),
                     _mm_sub_pd (f, jbm_2xf64_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_cosh (const __m128d x)        ///< __m128d number.
{
  __m128d f;
  f = jbm_2xf64_exp (x);
  return _mm_mul_pd (_mm_set1_pd (0.5),
                     _mm_add_pd (f, jbm_2xf64_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_tanh (const __m128d x)        ///< __m128d number.
{
  __m128d f, fi;
  f = jbm_2xf64_exp (x);
  fi = jbm_2xf64_reciprocal (f);
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
jbm_2xf64_asinh (const __m128d x)       ///< __m128d number.
{
  return
    jbm_2xf64_log (_mm_add_pd
                   (x, _mm_sqrt_pd (_mm_fmadd_pd (x, x, _mm_set1_pd (1.)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_acosh (const __m128d x)       ///< __m128d number.
{
  return
    jbm_2xf64_log (_mm_add_pd
                   (x, _mm_sqrt_pd (_mm_fmsub_pd (x, x, _mm_set1_pd (1.)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_atanh (const __m128d x)       ///< __m128d number.
{
  const __m128d u = _mm_set1_pd (1.);
  return _mm_mul_pd (_mm_set1_pd (0.5),
                     jbm_2xf64_log (_mm_div_pd (_mm_add_pd (u, x),
                                                _mm_sub_pd (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (__m128d)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_erfwc (const __m128d x)
                 ///< __m128d vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm_mul_pd (x, jbm_2xf64_rational_9_4 (jbm_2xf64_sqr (x), K_ERFWC_F64));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (__m128d)
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_erfcwc (const __m128d x)
                  ///< __m128d vector \f$\in\left[1,\infty\right]\f$.
{
  __m128d f, x2;
  x2 = jbm_2xf64_sqr (x);
  f = _mm_mul_pd (jbm_2xf64_rational_16_8 (jbm_2xf64_reciprocal (x),
                                           K_ERFCWC_F64),
                  _mm_div_pd (x, jbm_2xf64_exp (x2)));
  return
    _mm_blendv_pd (f, _mm_setzero_pd (),
                   _mm_cmpgt_pd (x, _mm_set1_pd (K_ERFC_MAX_F64)));
}

/**
 * Function to calculate the function erf(x) using jbm_2xf64_erfwc and
 * jbm_2xf64_erfcwc.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_erf (const __m128d x) ///< __m128d vector.
{
  const __m128d u = _mm_set1_pd (1.);
  __m128d ax, f;
  ax = jbm_2xf64_abs (x);
  f = jbm_2xf64_copysign (_mm_sub_pd (u, jbm_2xf64_erfcwc (ax)), x);
  return _mm_blendv_pd (f, jbm_2xf64_erfwc (x), _mm_cmplt_pd (ax, u));

}

/**
 * Function to calculate the function erfc(x) using jbm_2xf64_erfwc and
 * jbm_2xf64_erfcwc.
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_erfc (const __m128d x)        ///< __m128d vector.
{
  const __m128d u2 = _mm_set1_pd (2.);
  const __m128d u = _mm_set1_pd (1.);
  __m128d ax, cwc, wc;
  ax = jbm_2xf64_abs (x);
  cwc = jbm_2xf64_erfcwc (ax);
  wc = _mm_sub_pd (u, jbm_2xf64_erfwc (x));
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
jbm_solve_quadratic_reduced_2xf64 (const __m128d a,
///< __m128d vector of 1st order coefficient of the equations.
                                   const __m128d b,
///< __m128d vector of 0th order coefficient of the equations.
                                   const __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                                   const __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  __m128d ka, kb, k1, k2;
  k1 = _mm_set1_pd (-0.5);
  ka = _mm_mul_pd (a, k1);
  kb = _mm_sqrt_pd (_mm_sub_pd (jbm_2xf64_sqr (ka), b));
  k1 = _mm_add_pd (ka, kb);
  k2 = _mm_sub_pd (ka, kb);
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
jbm_2xf64_solve_quadratic (const __m128d a,
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
  k2 = _mm_div_pd (jbm_2xf64_opposite (c), b);
  return _mm_blendv_pd (k1, k2, jbm_2xf64_small (a));
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
  l1 = _mm_sqrt_pd (jbm_2xf64_opposite (k1));
  l0 = _mm_mul_pd (jbm_2xf64_acos (_mm_div_pd (k0, k3)), c_3);
  l1 = _mm_add_pd (l1, l1);
  l2 = _mm_fmsub_pd (l1, jbm_2xf64_cos (k0), a3);
  l3 = _mm_fmsub_pd (l1, jbm_2xf64_cos (_mm_add_pd (l0, c2p_3)), a3);
  l3 = _mm_blendv_pd (l3, l2,
                      _mm_or_pd (_mm_cmplt_pd (l2, x1), _mm_cmpgt_pd (l2, x2)));
  l4 = _mm_fmsub_pd (l1, jbm_2xf64_cos (_mm_sub_pd (l0, c2p_3)), a);
  l4 = _mm_blendv_pd (l4, l3,
                      _mm_or_pd (_mm_cmplt_pd (l3, x1), _mm_cmpgt_pd (l3, x2)));
  k1 = _mm_sqrt_pd (k2);
  l5 = _mm_add_pd (k0, k1);
  l5 = jbm_2xf64_cbrt (k2);
  k0 = _mm_sub_pd (k0, k1);
  l5 = _mm_add_pd (l5, _mm_sub_pd (jbm_2xf64_cbrt (k0), a3));
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
jbm_2xf64_solve_cubic (const __m128d a,
///< __m128d vector of 3rd order coefficient of the equations.
                       const __m128d b,
///< __m128d vector of 2nd order coefficient of the equations.
                       const __m128d c,
///< __m128d vector of 1st order coefficient of the equations.
                       const __m128d d,
///< __m128d vector of 0th order coefficient of the equations.
                       const __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                       const __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  return
    _mm_blendv_pd (jbm_solve_cubic_reduced_2xf64 (_mm_div_pd (b, a),
                                                  _mm_div_pd (c, a),
                                                  _mm_div_pd (d, a), x1, x2),
                   jbm_2xf64_solve_quadratic (b, c, d, x1, x2),
                   jbm_2xf64_small (a));
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_2xf64_flux_limiter_total (const __m128d d1 __attribute__((unused)),
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
jbm_2xf64_flux_limiter_null (const __m128d d1 __attribute__((unused)),
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
jbm_2xf64_flux_limiter_centred (const __m128d d1,
                                ///< 1st flux limiter function parameter.
                                const __m128d d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm_blendv_pd (_mm_div_pd (d1, d2), _mm_setzero_pd (),
                        jbm_2xf64_small (d2));
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
jbm_2xf64_flux_limiter_superbee (const __m128d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_div_pd (d1, d2);
  r = _mm_max_pd (_mm_min_pd (jbm_2xf64_dbl (r), _mm_set1_pd (1.)),
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
jbm_2xf64_flux_limiter_minmod (const __m128d d1,
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
jbm_2xf64_flux_limiter_VanLeer (const __m128d d1,
                                ///< 1st flux limiter function parameter.
                                const __m128d d2)
                              ///< 2nd flux limiter function parameter.
{
  __m128d r, k;
  r = _mm_div_pd (d1, d2);
  k = jbm_2xf64_abs (r);
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
jbm_2xf64_flux_limiter_VanAlbada (const __m128d d1,
                                  ///< 1st flux limiter function parameter.
                                  const __m128d d2)
                                ///< 2nd flux limiter function parameter.
{
  __m128d r, k;
  r = _mm_div_pd (d1, d2);
  k = jbm_2xf64_sqr (r);
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
jbm_2xf64_flux_limiter_minsuper (const __m128d d1,
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
jbm_2xf64_flux_limiter_supermin (const __m128d d1,
                                 ///< 1st flux limiter function parameter.
                                 const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_div_pd (d1, d2);
  r = _mm_min_pd (jbm_2xf64_dbl (r), _mm_set1_pd (1.));
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
jbm_2xf64_flux_limiter_monotonized_central (const __m128d d1,
///< 1st flux limiter function parameter.
                                            const __m128d d2)
///< 2nd flux limiter function parameter.
{
  __m128d r, rm;
  r = _mm_div_pd (d1, d2);
  rm = _mm_mul_pd (_mm_set1_pd (0.5), _mm_add_pd (r, _mm_set1_pd (1.)));
  rm = _mm_blendv_pd (_mm_set1_pd (2.), rm, _mm_cmplt_pd (r, _mm_set1_pd (3.)));
  rm = _mm_blendv_pd (rm, jbm_2xf64_dbl (r),
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
jbm_2xf64_flux_limiter_mean (const __m128d d1,
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
jbm_2xf64_flux_limiter (const __m128d d1,
                        ///< 1st flux limiter function parameter.
                        const __m128d d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_2xf64_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_2xf64_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_2xf64_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_2xf64_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_2xf64_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_2xf64_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_2xf64_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_2xf64_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_2xf64_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_2xf64_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_2xf64_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m128d).
 *
 * \return __m128d vector of integral values.
 */
static inline __m128d
jbm_2xf64_integral (__m128d (*f) (__m128d),
                    ///< pointer to the function to integrate.
                    const __m128d x1,   ///< left limit of the interval.
                    const __m128d x2)   ///< right limit of the interval.
{
  __m128d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m128d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm_set1_pd (0.5);
  dx = _mm_mul_pd (h, _mm_sub_pd (x2, x1));
  x = _mm_mul_pd (h, _mm_add_pd (x2, x1));
  k = _mm_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[0]);
  k = _mm_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm_set1_pd (JBM_INTEGRAL_GAUSS_B_F64[i]);
      k2 = _mm_mul_pd (k2, dx);
      f1 = f (_mm_sub_pd (x, k2));
      f2 = f (_mm_add_pd (x, k2));
      h = _mm_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[i]);
      k = _mm_fmadd_pd (h, _mm_add_pd (f1, f2), k);
    }
#endif
  return _mm_mul_pd (k, dx);
}

#ifndef __AVX__

///> macro to automatize operations on one array.
#define JBM_ARRAY_OP(xr, xd, n, type, load128, store128, op128, op) \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  if (n > prefetch + 64 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
	 j > 0; --j) \
      { \
        _mm_prefetch((const char *) (xd + i + prefetch), _MM_HINT_T0); \
        store128 (xr + i, op128 (load128 (xd + i))); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (xd + i))); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (xd + i))); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (xd + i))); \
        i += 16 / sizeof (type); \
      } \
  for (j = (n - i) >> (2 + 8 / sizeof (type)); j > 0; --j) \
    { \
      store128 (xr + i, op128 (load128 (xd + i))); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (xd + i))); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (xd + i))); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (xd + i))); \
      i += 16 / sizeof (type); \
    } \
  for (j = (n - i) >> (8 / sizeof (type)); j > 0; \
       --j, i += 16 / sizeof (type)) \
    store128 (xr + i, op128 (load128 (xd + i))); \
  for (; i < n; ++i) \
    xr[i] = op (xd[i]);

///> macro to automatize operations on one array and one number.
#define JBM_ARRAY_OP1(xr, x1, x2, n, type128, type, load128, store128, set128, \
                      op128, op) \
  const type128 x128 = set128 (x2); \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  if (n > prefetch + 64 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
	 j > 0; --j) \
      { \
        _mm_prefetch((const char *) (x1 + i + prefetch), _MM_HINT_T0); \
        store128 (xr + i, op128 (load128 (x1 + i), x128)); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (x1 + i), x128)); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (x1 + i), x128)); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (x1 + i), x128)); \
        i += 16 / sizeof (type); \
    } \
  for (j = (n - i) >> (2 + 8 / sizeof (type)); j > 0; --j) \
    { \
      store128 (xr + i, op128 (load128 (x1 + i), x128)); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (x1 + i), x128)); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (x1 + i), x128)); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (x1 + i), x128)); \
      i += 16 / sizeof (type); \
    } \
  for (j = (n - i) >> (8 / sizeof (type)); j > 0; \
       --j, i += 16 / sizeof (type)) \
    store128 (xr + i, op128 (load128 (x1 + i), x128)); \
  for (; i < n; ++i) \
    xr[i] = op (x1[i], x2);

///> macro to automatize operations on two arrays.
#define JBM_ARRAY_OP2(xr, x1, x2, n, type, load128, store128, op128, op) \
  const unsigned int prefetch = sizeof (type) == 4 ? 128 : 32; \
  unsigned int i, j; \
  if (n > prefetch + 64 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
	 j > 0; --j) \
      { \
        _mm_prefetch((const char *) (x1 + i + prefetch), _MM_HINT_T0); \
        _mm_prefetch((const char *) (x2 + i + prefetch), _MM_HINT_T0); \
        store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
        i += 16 / sizeof (type); \
        store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
        i += 16 / sizeof (type); \
      } \
  for (j = (n - i) >> (2 + 8 / sizeof (type)); j > 0; --j) \
    { \
      store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
      i += 16 / sizeof (type); \
      store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
      i += 16 / sizeof (type); \
    } \
  for (j = (n - i) >> (8 / sizeof (type)); j > 0; \
       --j, i += 16 / sizeof (type)) \
    store128 (xr + i, op128 (load128 (x1 + i), load128 (x2 + i))); \
  for (; i < n; ++i) \
    xr[i] = op (x1[i], x2[i]);

///> macro to automatize reduction operations on arrays.
#define JBM_ARRAY_REDUCE_OP(x, n, type128, type, load128, op128, op, \
                            reduce128, initial_value) \
  type128 a128, b128, c128, d128; \
  type a = initial_value; \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 64 / sizeof (type)) \
    { \
      j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
      if (j) \
        { \
          _mm_prefetch ((const char *) (x + prefetch), _MM_HINT_T0); \
          a128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          b128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          c128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          d128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          while (--j) \
            { \
              _mm_prefetch ((const char *) (x + i + prefetch), _MM_HINT_T0); \
              a128 = op128 (a128, load128 (x + i)); \
              i += 16 / sizeof (type); \
              b128 = op128 (b128, load128 (x + i)); \
              i += 16 / sizeof (type); \
              c128 = op128 (c128, load128 (x + i)); \
              i += 16 / sizeof (type); \
              d128 = op128 (d128, load128 (x + i)); \
              i += 16 / sizeof (type); \
            } \
          a128 = op128 (a128, b128); \
          c128 = op128 (c128, d128); \
          a = reduce128 (op128 (a128, c128)); \
        } \
    } \
  j = (n - i) >> (2 + 8 / sizeof (type)); \
  if (j) \
    { \
      a128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      b128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      c128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      d128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          a128 = op128 (a128, load128 (x + i)); \
          i += 16 / sizeof (type); \
          b128 = op128 (b128, load128 (x + i)); \
          i += 16 / sizeof (type); \
          c128 = op128 (c128, load128 (x + i)); \
          i += 16 / sizeof (type); \
          d128 = op128 (d128, load128 (x + i)); \
          i += 16 / sizeof (type); \
        } \
      a128 = op128 (a128, b128); \
      c128 = op128 (c128, d128); \
      a = op (a, reduce128 (op128 (a128, c128))); \
    } \
  j = (n - i) >> (8 / sizeof (type)); \
  if (j) \
    { \
      a128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          a128 = op128 (a128, load128 (x + i)); \
          i += 16 / sizeof (type); \
        } \
      a = op (a, reduce128 (a128)); \
    } \
  while (i < n) \
    a = op (a, x[i++]); \
  return a;

///> macro to automatize dot products on arrays.
#define JBM_ARRAY_DOT(x1, x2, n, type128, type, load128, mul128, add128, \
                      ma128, reduce128) \
  type128 a128, b128, c128, d128; \
  type a = (type) 0.; \
  const unsigned int prefetch = sizeof (type) == 4 ? 128 : 32; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 64 / sizeof (type)) \
    { \
      j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
      if (j) \
        { \
          _mm_prefetch ((const char *) (x1 + prefetch), _MM_HINT_T0); \
          _mm_prefetch ((const char *) (x2 + prefetch), _MM_HINT_T0); \
          a128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          b128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          d128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          d128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          while (--j) \
            { \
              _mm_prefetch ((const char *) (x1 + i + prefetch), _MM_HINT_T0); \
              _mm_prefetch ((const char *) (x2 + i + prefetch), _MM_HINT_T0); \
              a128 = ma128 (load128 (x1 + i), load128 (x2 + i), a128); \
              i += 16 / sizeof (type); \
              b128 = ma128 (load128 (x1 + i), load128 (x2 + i), b128); \
              i += 16 / sizeof (type); \
              d128 = ma128 (load128 (x1 + i), load128 (x2 + i), c128); \
              i += 16 / sizeof (type); \
              d128 = ma128 (load128 (x1 + i), load128 (x2 + i), d128); \
              i += 16 / sizeof (type); \
            } \
          a128 = add128 (a128, b128); \
          c128 = add128 (c128, d128); \
          a = reduce128 (add128 (a128, c128)); \
        } \
    } \
  j = (n - i) >> (2 + 8 / sizeof (type)); \
  if (j) \
    { \
      a128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
      i += 16 / sizeof (type); \
      b128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
      i += 16 / sizeof (type); \
      d128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
      i += 16 / sizeof (type); \
      d128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          a128 = ma128 (load128 (x1 + i), load128 (x2 + i), a128); \
          i += 16 / sizeof (type); \
          b128 = ma128 (load128 (x1 + i), load128 (x2 + i), b128); \
          i += 16 / sizeof (type); \
          d128 = ma128 (load128 (x1 + i), load128 (x2 + i), c128); \
          i += 16 / sizeof (type); \
          d128 = ma128 (load128 (x1 + i), load128 (x2 + i), d128); \
          i += 16 / sizeof (type); \
        } \
      a128 = add128 (a128, b128); \
      c128 = add128 (c128, d128); \
      a += reduce128 (add128 (a128, c128)); \
    } \
  j = (n - i) >> (8 / sizeof (type)); \
  if (j) \
    { \
      a128 = mul128 (load128 (x1 + i), load128 (x2 + i)); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          a128 = ma128 (load128 (x1 + i), load128 (x2 + i), a128); \
          i += 16 / sizeof (type); \
        } \
      a += reduce128 (a128); \
    } \
  for (; i < n; ++i) \
    a += JBM_MUL (x1[i], x2[i]); \
  return a;

///> macro to automatize maxmin operations on arrays.
#define JBM_ARRAY_MAXMIN(x, n, type128, type, load128, max128, max, min128, \
                         min, redmax128, redmin128, mx, mn) \
  type128 x128, mxa128, mxb128, mna128, mnb128; \
  type mx = -INFINITY, mn = INFINITY; \
  const unsigned int prefetch = sizeof (type) == 4 ? 256 : 64; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 64 / sizeof (type)) \
    { \
      j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
      if (j) \
        { \
          _mm_prefetch ((const char *) (x + prefetch), _MM_HINT_T0); \
          mxa128 = mna128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          mxb128 = mnb128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          while (--j) \
            { \
              _mm_prefetch ((const char *) (x + i + prefetch), _MM_HINT_T0); \
              x128 = load128 (x + i); \
              mxa128 = max128 (mxa128, x128); \
              mna128 = min128 (mna128, x128); \
              i += 16 / sizeof (type); \
              x128 = load128 (x + i); \
              mxb128 = max128 (mxb128, x128); \
              mnb128 = min128 (mnb128, x128); \
              i += 16 / sizeof (type); \
            } \
          mx = redmax128 (max128 (mxa128, mxb128)); \
          mn = redmin128 (min128 (mna128, mnb128)); \
        } \
    } \
  j = (n - i) >> (2 + 8 / sizeof (type)); \
  if (j) \
    { \
      mxa128 = mna128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      mxb128 = mnb128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          x128 = load128 (x + i); \
          mxa128 = max128 (mxa128, x128); \
          mna128 = min128 (mna128, x128); \
          i += 16 / sizeof (type); \
          x128 = load128 (x + i); \
          mxb128 = max128 (mxb128, x128); \
          mnb128 = min128 (mnb128, x128); \
          i += 16 / sizeof (type); \
        } \
      mx = max (mx, redmax128 (max128 (mxa128, mxb128))); \
      mn = min (mn, redmin128 (min128 (mna128, mnb128))); \
    } \
  j = (n - i) >> (8 / sizeof (type)); \
  if (j) \
    { \
      mxa128 = mna128 = load128 (x + i); \
      i += 16 / sizeof (type); \
      while (--j) \
        { \
          x128 = load128 (x + i); \
          mxa128 = max128 (mxa128, x128); \
          mna128 = min128 (mna128, x128); \
          i += 16 / sizeof (type); \
        } \
      mx = max (mx, redmax128 (mxa128)); \
      mn = min (mn, redmin128 (mna128)); \
    } \
  for (; i < n; ++i) \
    mx = max (mx, x[i]), mn = min (mn, x[i]); \

/**
 * Function to calculate the root square of a float array.
 */
static inline void
jbm_array_f32_sqrt (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, _mm_sqrt_ps,
                sqrtf);
}

/**
 * Function to calculate the double of a float array.
 */
static inline void
jbm_array_f32_dbl (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_dbl,
                jbm_f32_dbl);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_sqr (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_sqr,
                jbm_f32_sqr);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_opposite (float *restrict xr,     ///< result float array.
                        const float *restrict xd,       ///< data float array.
                        const unsigned int n)   ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps,
                jbm_4xf32_opposite, jbm_f32_opposite);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_reciprocal (float *restrict xr,   ///< result float array.
                          const float *restrict xd,     ///< data float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps,
                jbm_4xf32_reciprocal, jbm_f32_reciprocal);
}

/**
 * Function to calculate the abs function of a float array.
 */
static inline void
jbm_array_f32_abs (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_abs,
                jbm_f32_abs);
}

/**
 * Function to calculate the cbrt function of a float array.
 */
static inline void
jbm_array_f32_cbrt (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_cbrt,
                jbm_f32_cbrt);
}

/**
 * Function to calculate the exp2 function a float array.
 */
static inline void
jbm_array_f32_exp2 (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_exp2,
                jbm_f32_exp2);
}

/**
 * Function to calculate the exp function a float array.
 */
static inline void
jbm_array_f32_exp (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_exp,
                jbm_f32_exp);
}

/**
 * Function to calculate the exp10 function a float array.
 */
static inline void
jbm_array_f32_exp10 (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_exp10,
                jbm_f32_exp10);
}

/**
 * Function to calculate the expm1 function a float array.
 */
static inline void
jbm_array_f32_expm1 (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_expm1,
                jbm_f32_expm1);
}

/**
 * Function to calculate the log2 function a float array.
 */
static inline void
jbm_array_f32_log2 (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_log2,
                jbm_f32_log2);
}

/**
 * Function to calculate the log function a float array.
 */
static inline void
jbm_array_f32_log (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_log,
                jbm_f32_log);
}

/**
 * Function to calculate the log10 function a float array.
 */
static inline void
jbm_array_f32_log10 (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_log10,
                jbm_f32_log10);
}

/**
 * Function to calculate the sin function a float array.
 */
static inline void
jbm_array_f32_sin (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_sin,
                jbm_f32_sin);
}

/**
 * Function to calculate the cos function a float array.
 */
static inline void
jbm_array_f32_cos (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_cos,
                jbm_f32_cos);
}

/**
 * Function to calculate the tan function a float array.
 */
static inline void
jbm_array_f32_tan (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_tan,
                jbm_f32_tan);
}

/**
 * Function to calculate the asin function a float array.
 */
static inline void
jbm_array_f32_asin (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_asin,
                jbm_f32_asin);
}

/**
 * Function to calculate the acos function a float array.
 */
static inline void
jbm_array_f32_acos (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_acos,
                jbm_f32_acos);
}

/**
 * Function to calculate the atan function a float array.
 */
static inline void
jbm_array_f32_atan (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_atan,
                jbm_f32_atan);
}

/**
 * Function to calculate the sinh function a float array.
 */
static inline void
jbm_array_f32_sinh (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_sinh,
                jbm_f32_sinh);
}

/**
 * Function to calculate the cosh function a float array.
 */
static inline void
jbm_array_f32_cosh (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_cosh,
                jbm_f32_cosh);
}

/**
 * Function to calculate the tanh function a float array.
 */
static inline void
jbm_array_f32_tanh (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_tanh,
                jbm_f32_tanh);
}

/**
 * Function to calculate the asinh function a float array.
 */
static inline void
jbm_array_f32_asinh (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_asinh,
                jbm_f32_asinh);
}

/**
 * Function to calculate the acosh function a float array.
 */
static inline void
jbm_array_f32_acosh (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_acosh,
                jbm_f32_acosh);
}

/**
 * Function to calculate the atanh function a float array.
 */
static inline void
jbm_array_f32_atanh (float *restrict xr,        ///< result float array.
                     const float *restrict xd,  ///< data float array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_atanh,
                jbm_f32_atanh);
}

/**
 * Function to calculate the erf function a float array.
 */
static inline void
jbm_array_f32_erf (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_erf,
                jbm_f32_erf);
}

/**
 * Function to calculate the erfc function a float array.
 */
static inline void
jbm_array_f32_erfc (float *restrict xr, ///< result float array.
                    const float *restrict xd,   ///< data float array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, _mm_loadu_ps, _mm_storeu_ps, jbm_4xf32_erfc,
                jbm_f32_erfc);
}

/**
 * Function to calculate the sum of the elements of a float array.
 *
 * \return the sum value.
 */
static inline float
jbm_array_f32_sum (const float *x,      ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m128, float, _mm_loadu_ps, _mm_add_ps, JBM_ADD,
                       jbm_4xf32_reduce_add, 0.f);
}

/**
 * Function to find the highest element of a float array.
 *
 * \return the highest value.
 */
static inline float
jbm_array_f32_reduce_max (const float *x,       ///< float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m128, float, _mm_loadu_ps, _mm_max_ps, fmaxf,
                       jbm_4xf32_reduce_max, -INFINITY);
}

/**
 * Function to find the lowest element of a float array.
 *
 * \return the lowest value.
 */
static inline float
jbm_array_f32_reduce_min (const float *x,       ///< float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m128, float, _mm_loadu_ps, _mm_min_ps, fminf,
                       jbm_4xf32_reduce_min, INFINITY);
}

/**
 * Function to find the highest and the lowest elements of a float array.
 */
static inline void
jbm_array_f32_reduce_maxmin (const float *x,    ///< float array.
                             float *max,        ///< the highest value.
                             float *min,        ///< the lowest value.
                             const unsigned int n)
                             ///< number of array elements.
{
  JBM_ARRAY_MAXMIN (x, n, __m128, float, _mm_loadu_ps, _mm_max_ps, fmaxf,
                    _mm_min_ps, fmin, jbm_4xf32_reduce_max,
                    jbm_4xf32_reduce_min, mx, mn);
  *max = mx, *min = mn;
}

/**
 * Function to add 1 float array + 1 number.
 */
static inline void
jbm_array_f32_add1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< addend float array.
                    const float x2,     ///< addend float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, _mm_add_ps, JBM_ADD);
}

/**
 * Function to subtract 1 float array + 1 number.
 */
static inline void
jbm_array_f32_sub1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< minuend float array.
                    const float x2,     ///< subtrahend float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, _mm_sub_ps, JBM_SUB);
}

/**
 * Function to multiply a float array by a float number.
 */
static inline void
jbm_array_f32_mul1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< multiplier float array.
                    const float x2,     ///< multiplicand float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, _mm_mul_ps, JBM_MUL);
}

/**
 * Function to divide a float array by a float number.
 */
static inline void
jbm_array_f32_div1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< dividend float array.
                    const float x2,     ///< divisor float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, _mm_div_ps, JBM_DIV);
}

/**
 * Function to calculate the maximum between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_max1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, _mm_max_ps, fmaxf);
}

/**
 * Function to calculate the minimum between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_min1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, _mm_min_ps, fminf);
}

/**
 * Function to calculate the module between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_mod1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, jbm_4xf32_mod, jbm_f32_mod);
}

/**
 * Function to calculate the pow function between 1 float array + 1 number.
 */
static inline void
jbm_array_f32_pow1 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< float array.
                    const float x2,     ///< float number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_set1_ps, jbm_4xf32_pow, jbm_f32_pow);
}

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_f32_add (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st addend float array.
                   const float *restrict x2,    ///< 2nd addend float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps, _mm_add_ps,
                 JBM_ADD);
}

/**
 * Function to subtract 2 float arrays.
 */
static inline void
jbm_array_f32_sub (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< minuend float array.
                   const float *restrict x2,    ///< subtrahend float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps, _mm_sub_ps,
                 JBM_SUB);
}

/**
 * Function to multiply 2 float arrays.
 */
static inline void
jbm_array_f32_mul (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< multiplier float array.
                   const float *restrict x2,    ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps, _mm_mul_ps,
                 JBM_MUL);
}

/**
 * Function to divide 2 float arrays.
 */
static inline void
jbm_array_f32_div (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< dividend float array.
                   const float *restrict x2,    ///< divisor float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps, _mm_div_ps,
                 JBM_DIV);
}

/**
 * Function to calculate the maximum in 2 float arrays.
 */
static inline void
jbm_array_f32_max (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_max_ps, fmax);
}

/**
 * Function to calculate the minimum in 2 float arrays.
 */
static inline void
jbm_array_f32_min (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps,
                 _mm_min_ps, fmin);
}

/**
 * Function to calculate the module in 2 float arrays.
 */
static inline void
jbm_array_f32_mod (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps,
                 jbm_4xf32_mod, jbm_f32_mod);
}

/**
 * Function to do the pow function in 2 float arrays.
 */
static inline void
jbm_array_f32_pow (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st float array.
                   const float *restrict x2,    ///< 2nd float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, _mm_loadu_ps, _mm_storeu_ps,
                 jbm_4xf32_pow, jbm_f32_pow);
}

/**
 * Function to do the dot product of 2 float arrays.
 *
 * \return dot product (float).
 */
static inline float
jbm_array_f32_dot (const float *restrict x1,    ///< multiplier float array.
                   const float *restrict x2,    ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_DOT (x1, x2, n, __m128, float, _mm_loadu_ps, _mm_mul_ps, _mm_add_ps,
                 _mm_fmadd_ps, jbm_4xf32_reduce_add);
}

/**
 * Function to calculate the root square of a double array.
 */
static inline void
jbm_array_f64_sqrt (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_sqrt_pd,
                sqrt);
}

/**
 * Function to calculate the double of a double array.
 */
static inline void
jbm_array_f64_dbl (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_dbl,
                jbm_f64_dbl);
}

/**
 * Function to calculate the square of a double array.
 */
static inline void
jbm_array_f64_sqr (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_sqr,
                jbm_f64_sqr);
}

/**
 * Function to calculate the opposite of a double array.
 */
static inline void
jbm_array_f64_opposite (double *restrict xr,    ///< result double array.
                        const double *restrict xd,      ///< data double array.
                        const unsigned int n)   ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd,
                jbm_2xf64_opposite, jbm_f64_opposite);
}

/**
 * Function to calculate the reciprocal of a double array.
 */
static inline void
jbm_array_f64_reciprocal (double *restrict xr,  ///< result double array.
                          const double *restrict xd,    ///< data double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd,
                jbm_2xf64_reciprocal, jbm_f64_reciprocal);
}

/**
 * Function to calculate the abs function of a double array.
 */
static inline void
jbm_array_f64_abs (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_abs,
                jbm_f64_abs);
}

/**
 * Function to calculate the cbrt function of a double array.
 */
static inline void
jbm_array_f64_cbrt (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_cbrt,
                jbm_f64_cbrt);
}

/**
 * Function to calculate the exp2 function a double array.
 */
static inline void
jbm_array_f64_exp2 (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_exp2,
                jbm_f64_exp2);
}

/**
 * Function to calculate the exp function a double array.
 */
static inline void
jbm_array_f64_exp (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_exp,
                jbm_f64_exp);
}

/**
 * Function to calculate the exp10 function a double array.
 */
static inline void
jbm_array_f64_exp10 (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_exp10,
                jbm_f64_exp10);
}

/**
 * Function to calculate the expm1 function a double array.
 */
static inline void
jbm_array_f64_expm1 (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_expm1,
                jbm_f64_expm1);
}

/**
 * Function to calculate the log2 function a double array.
 */
static inline void
jbm_array_f64_log2 (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_log2,
                jbm_f64_log2);
}

/**
 * Function to calculate the log function a double array.
 */
static inline void
jbm_array_f64_log (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_log,
                jbm_f64_log);
}

/**
 * Function to calculate the log10 function a double array.
 */
static inline void
jbm_array_f64_log10 (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_log10,
                jbm_f64_log10);
}

/**
 * Function to calculate the sin function a double array.
 */
static inline void
jbm_array_f64_sin (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_sin,
                jbm_f64_sin);
}

/**
 * Function to calculate the cos function a double array.
 */
static inline void
jbm_array_f64_cos (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_cos,
                jbm_f64_cos);
}

/**
 * Function to calculate the tan function a double array.
 */
static inline void
jbm_array_f64_tan (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_tan,
                jbm_f64_tan);
}

/**
 * Function to calculate the asin function a double array.
 */
static inline void
jbm_array_f64_asin (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_asin,
                jbm_f64_asin);
}

/**
 * Function to calculate the acos function a double array.
 */
static inline void
jbm_array_f64_acos (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_acos,
                jbm_f64_acos);
}

/**
 * Function to calculate the atan function a double array.
 */
static inline void
jbm_array_f64_atan (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_atan,
                jbm_f64_atan);
}

/**
 * Function to calculate the sinh function a double array.
 */
static inline void
jbm_array_f64_sinh (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_sinh,
                jbm_f64_sinh);
}

/**
 * Function to calculate the cosh function a double array.
 */
static inline void
jbm_array_f64_cosh (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_cosh,
                jbm_f64_cosh);
}

/**
 * Function to calculate the tanh function a double array.
 */
static inline void
jbm_array_f64_tanh (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_tanh,
                jbm_f64_tanh);
}

/**
 * Function to calculate the asinh function a double array.
 */
static inline void
jbm_array_f64_asinh (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_asinh,
                jbm_f64_asinh);
}

/**
 * Function to calculate the acosh function a double array.
 */
static inline void
jbm_array_f64_acosh (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_acosh,
                jbm_f64_acosh);
}

/**
 * Function to calculate the atanh function a double array.
 */
static inline void
jbm_array_f64_atanh (double *restrict xr,       ///< result double array.
                     const double *restrict xd, ///< data double array.
                     const unsigned int n)      ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_atanh,
                jbm_f64_atanh);
}

/**
 * Function to calculate the erf function a double array.
 */
static inline void
jbm_array_f64_erf (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_erf,
                jbm_f64_erf);
}

/**
 * Function to calculate the erfc function a double array.
 */
static inline void
jbm_array_f64_erfc (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, _mm_loadu_pd, _mm_storeu_pd, jbm_2xf64_erfc,
                jbm_f64_erfc);
}

/**
 * Function to calculate the sum of the elements of a double array.
 *
 * \return the sum value.
 */
static inline double
jbm_array_f64_sum (const double *x,     ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m128d, double, _mm_loadu_pd, _mm_add_pd, JBM_ADD,
                       jbm_2xf64_reduce_add, 0.);
}

/**
 * Function to find the highest element of a double array.
 *
 * \return the highest value.
 */
static inline double
jbm_array_f64_reduce_max (const double *x,      ///< double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m128d, double, _mm_loadu_pd, _mm_max_pd, fmaxf,
                       jbm_2xf64_reduce_max, -INFINITY);
}

/**
 * Function to find the lowest element of a double array.
 *
 * \return the lowest value.
 */
static inline double
jbm_array_f64_reduce_min (const double *x,      ///< double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (x, n, __m128d, double, _mm_loadu_pd, _mm_min_pd, fminf,
                       jbm_2xf64_reduce_min, INFINITY);
}

/**
 * Function to find the highest and the lowest elements of a double array.
 */
static inline void
jbm_array_f64_reduce_maxmin (const double *x,   ///< double array.
                             double *max,       ///< the highest value.
                             double *min,       ///< the lowest value.
                             const unsigned int n)
                             ///< number of array elements.
{
  JBM_ARRAY_MAXMIN (x, n, __m128d, double, _mm_loadu_pd, _mm_max_pd, fmaxf,
                    _mm_min_pd, fmin, jbm_2xf64_reduce_max,
                    jbm_2xf64_reduce_min, mx, mn);
  *max = mx, *min = mn;
}

/**
 * Function to add 1 double array + 1 number.
 */
static inline void
jbm_array_f64_add1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< addend double array.
                    const double x2,    ///< addend double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, _mm_add_pd, JBM_ADD);
}

/**
 * Function to subtract 1 double array - 1 double number.
 */
static inline void
jbm_array_f64_sub1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< minuend double array.
                    const double x2,    ///< subtrahend double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, _mm_sub_pd, JBM_SUB);
}

/**
 * Function to multiply a double array by a double number.
 */
static inline void
jbm_array_f64_mul1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< multiplier double array.
                    const double x2,    ///< multiplicand double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, _mm_mul_pd, JBM_MUL);
}

/**
 * Function to divide a double array by a double number.
 */
static inline void
jbm_array_f64_div1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< dividend double array.
                    const double x2,    ///< divisor double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, _mm_div_pd, JBM_DIV);
}

/**
 * Function to calculate the maximum between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_max1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, _mm_max_pd, fmax);
}

/**
 * Function to calculate the minimum between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_min1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, _mm_min_pd, fmin);
}

/**
 * Function to calculate the module between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_mod1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, jbm_2xf64_mod, jbm_f64_mod);
}

/**
 * Function to calculate the pow function between 1 double array + 1 number.
 */
static inline void
jbm_array_f64_pow1 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< double array.
                    const double x2,    ///< double number.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP1 (xr, x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_storeu_pd,
                 _mm_set1_pd, jbm_2xf64_pow, jbm_f64_pow);
}

/**
 * Function to add 2 double arrays.
 */
static inline void
jbm_array_f64_add (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st addend double array.
                   const double *restrict x2,   ///< 2nd addend double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_add_pd,
                 JBM_ADD);
}

/**
 * Function to subtract 2 double arrays.
 */
static inline void
jbm_array_f64_sub (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< minuend double array.
                   const double *restrict x2,   ///< subtrahend double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_sub_pd,
                 JBM_SUB);
}

/**
 * Function to multiply 2 double arrays.
 */
static inline void
jbm_array_f64_mul (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< multiplier double array.
                   const double *restrict x2,   ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_mul_pd,
                 JBM_MUL);
}

/**
 * Function to divide 2 double arrays.
 */
static inline void
jbm_array_f64_div (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< dividend double array.
                   const double *restrict x2,   ///< divisor double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_div_pd,
                 JBM_DIV);
}

/**
 * Function to calculate the maximum in 2 double arrays.
 */
static inline void
jbm_array_f64_max (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_max_pd,
                 fmax);
}

/**
 * Function to calculate the minimum in 2 double arrays.
 */
static inline void
jbm_array_f64_min (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd, _mm_min_pd,
                 fmin);
}

/**
 * Function to calculate the module in 2 double arrays.
 */
static inline void
jbm_array_f64_mod (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd,
                 jbm_2xf64_mod, jbm_f64_mod);
}

/**
 * Function to do the pow function in 2 double arrays.
 */
static inline void
jbm_array_f64_pow (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st double array.
                   const double *restrict x2,   ///< 2nd double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, _mm_loadu_pd, _mm_storeu_pd,
                 jbm_2xf64_pow, jbm_f64_pow);
}

/**
 * Function to do the dot product of 2 double arrays.
 *
 * \return dot product (double).
 */
static inline double
jbm_array_f64_dot (const double *restrict x1,   ///< multiplier double array.
                   const double *restrict x2,   ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_DOT (x1, x2, n, __m128d, double, _mm_loadu_pd, _mm_mul_pd,
                 _mm_add_pd, _mm_fmadd_pd, jbm_2xf64_reduce_add);
}

#endif

#endif
