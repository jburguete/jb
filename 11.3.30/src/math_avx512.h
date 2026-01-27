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
 * \file math_avx512.h
 * \brief Header file with useful mathematical functions for __m512.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_AVX512__H
#define JB_MATH_AVX512__H 1

#include "math_f32.h"
#include "math_f64.h"

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

// float constants

#define JBM_BIAS_16xF32 _mm512_set1_epi32 (JBM_BIAS_F32)
///< bias for floats.
#define JBM_BITS_1_16xF32 _mm512_set1_epi32 (JBM_BITS_1_F32)
///< 1 bits for floats.
#define JBM_BITS_ABS_16xF32 _mm512_set1_epi32 (JBM_BITS_ABS_F32)
///< absolute value bits for floats.
#define JBM_BITS_EXPONENT_16xF32 _mm512_set1_epi32 (JBM_BITS_EXPONENT_F32)
///< exponent bits for floats.
#define JBM_BITS_MANTISSA_16xF32 _mm512_set1_epi32 (JBM_BITS_MANTISSA_F32)
///< mantissa bits for floats.
#define JBM_BITS_SIGN_16xF32 _mm512_set1_epi32 (JBM_BITS_SIGN_F32)
///< sign bits for floats.
#define JBM_CBRT2_16xF32 _mm512_set1_ps (JBM_CBRT2_F32)
///< cbrt(2) for floats.
#define JBM_CBRT4_16xF32 _mm512_set1_ps (JBM_CBRT4_F32)
///< cbrt(4) for floats.

// double constants

#define JBM_BIAS_8xF64 _mm512_set1_epi64 (JBM_BIAS_F64)
///< bias for doubles.
#define JBM_BITS_1_8xF64 _mm512_set1_epi64 (JBM_BITS_1_F64)
///< 1 bits for doubles.
#define JBM_BITS_ABS_8xF64 _mm512_set1_epi64 (JBM_BITS_ABS_F64)
///< absolute value bits for doubles.
#define JBM_BITS_EXPONENT_8xF64 _mm512_set1_epi64 (JBM_BITS_EXPONENT_F64)
///< exponent bits for doubles.
#define JBM_BITS_MANTISSA_8xF64 _mm512_set1_epi64 (JBM_BITS_MANTISSA_F64)
///< mantissa bits for doubles.
#define JBM_BITS_SIGN_8xF64 _mm512_set1_epi64 (JBM_BITS_SIGN_F64)
///< sign bits for doubles.
#define JBM_CBRT2_8xF64 _mm512_set1_pd (JBM_CBRT2_F64)
///< cbrt(2) for doubles.
#define JBM_CBRT4_8xF64 _mm512_set1_pd (JBM_CBRT4_F64)
///< cbrt(4) for doubles.

///> macro to define types for AVX512
#define JBM_TYPE_512(type) JBM_SIMD_SELECT(type, __m512, __m512d)
///> macro to define loads for AVX512
#define JBM_LOAD_512(type) JBM_SIMD_SELECT(type, _mm512_load_ps, _mm512_load_pd)

///> macro to automatize reduction operations on arrays.
#define JBM_ARRAY_REDUCE_OP(type, op512, op256, op128, op, reduce512, \
                            reduce256, reduce128, initial_value) \
  JBM_TYPE_512 (type) a512, b512, c512, d512; \
  JBM_TYPE_256 (type) a256; \
  JBM_TYPE_128 (type) a128; \
  type a = initial_value; \
  const unsigned int prefetch = sizeof (type) == 4 ? 1024 : 512; \
  unsigned int i, j; \
  i = 0; \
  j = n >> sizeof (type) == 4 ? 6 : 5; \
  if (j) \
    { \
      if (n > prefetch) \
        _mm_prefetch ((const char *) (x + prefetch), _MM_HINT_T0); \
      a512 = JBM_LOAD_512 (type) (x + i); \
      b512 = JBM_LOAD_512 (type) (x + i + sizeof (type) == 4 ? 16 : 8); \
      c512 = JBM_LOAD_512 (type) (x + i + sizeof (type) == 4 ? 32 : 16); \
      d512 = JBM_LOAD_512 (type) (x + i + sizeof (type) == 4 ? 48 : 24); \
      while (--j) \
        { \
          i += sizeof (type) == 4 ? 64 : 32; \
          if (n > i + prefetch) \
            _mm_prefetch ((const char *) (x + i + prefetch), _MM_HINT_T0); \
          a512 = op512 (a512, JBM_LOAD_512 (type) (x + i)); \
          b512 = op512 (b512, \
                        JBM_LOAD_512 (type) (x + i \
                                             + sizeof (type) == 4 ? 16: 8)); \
          c512 = op512 (c512, \
                        JBM_LOAD_512( type) (x + i \
                                             + sizeof (type) == 4 ? 32: 16)); \
          d512 = op512 (d512, \
                        JBM_LOAD_512 (type) (x + i \
                                             + sizeof (type) == 4 ? 48: 24)); \
        } \
      a512 = op512 (a512, b512); \
      c512 = op512 (c512, d512); \
      a = reduce512 (op512 (a512, c512)); \
      i += sizeof (type) == 4 ? 64 : 32; \
    } \
  j = (n - i) >> sizeof (type) == 4 ? 4 : 3; \
  if (j) \
    { \
      a512 = JBM_LOAD_512 (type) (x + i); \
      while (--j) \
        { \
          i += sizeof (type) == 4 ? 16 : 8; \
          a512 = op512 (a512, JBM_LOAD_512 (type) (x + i)); \
        } \
      a = op (a, reduce512 (a512)); \
      i += sizeof (type) == 4 ? 16 : 8; \
    } \
  j = (n - i) >> sizeof (type) == 4 ? 3 : 2; \
  if (j) \
    { \
      a256 = JBM_LOAD_256 (type) (x + i); \
      while (--j) \
        { \
          i += sizeof (type) == 4 ? 8 : 4; \
          a256 = op256 (a256, JBM_LOAD_256 (type) (x + i)); \
        } \
      a = op (a, reduce256 (a256)); \
      i += sizeof (type) == 4 ? 8 : 4; \
    } \
  j = (n - i) >> sizeof (type) == 4 ? 2 : 1; \
  if (j) \
    { \
      a128 = JBM_LOAD_128 (type) (x + i); \
      while (--j) \
        { \
          i += sizeof (type) == 4 ? 4 : 2; \
          a128 = op128 (a128, JBM_LOAD_128 (type) (x + i)); \
        } \
      a = op (a, reduce128 (a128)); \
      i += sizeof (type) == 4 ? 4 : 2; \
    } \
  while (i < n) \
    a = op (a, x[i++]); \
  return a;

// Debug functions

static inline void
print_m512b32 (FILE *file, const char *label, __m512i x)
{
  int y[16] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi32 (y, x);
  for (i = 0; i < 16; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m512b64 (FILE *file, const char *label, __m512i x)
{
  long long int y[8] JB_ALIGNED;
  unsigned int i;
  _mm512_store_epi64 (y, x);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

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

/**
 * Function to calculate the additive reduction value of a __m512 vector.
 *
 * \return additive reduction (float).
 */
static inline float
jbm_reduce_add_16xf32 (const __m512 x)  ///< __m512 vector.
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  return jbm_reduce_add_8xf32 (_mm256_add_ps (h, l));
}

/**
 * Function to calculate the maximum reduction value of a __m512 vector.
 *
 * \return maximum reduction (float).
 */
static inline float
jbm_reduce_max_16xf32 (const __m512 x)  ///< __m512 vector.
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  return jbm_reduce_max_8xf32 (_mm256_max_ps (h, l));
}

/**
 * Function to calculate the minimum reduction value of a __m512 vector.
 *
 * \return minimum reduction (float).
 */
static inline float
jbm_reduce_min_16xf32 (const __m512 x)  ///< __m512 vector.
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  return jbm_reduce_min_8xf32 (_mm256_min_ps (h, l));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m512
 * vector.
 */
static inline void
jbm_reduce_maxmin_16xf32 (const __m512 x,      ///< __m512 vector.
                          float *max,  ///< pointer to the maximum value
                          float *min)  ///< pointer to the minimum value
{
  __m256 h, l;
  h = _mm512_extractf32x8_ps (x, 1);
  l = _mm512_castps512_ps256 (x);
  *max = jbm_reduce_max_8xf32 (_mm256_max_ps (h, l));
  *min = jbm_reduce_min_8xf32 (_mm256_min_ps (h, l));
}

/**
 * Function to calculate the additive inverse value of a __m512 vector.
 *
 * \return opposite value vector (__m512).
 */
static inline __m512
jbm_opposite_16xf32 (const __m512 x)    ///< __m512 vector.
{
  JBM16xF32 y;
  y.i = JBM_BITS_SIGN_16xF32;
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
 * Function to calculate the sign of a __m512 vector.
 *
 * \return sign vector (__m512).
 */
static inline __m512
jbm_sign_16xf32 (const __m512 x)        ///< __m512 vector.
{
  JBM16xF32 y;
  y.x = x;
  y.i = _mm512_and_epi32 (y.i, JBM_BITS_SIGN_16xF32);
  y.i = _mm512_or_epi32 (y.i, JBM_BITS_1_16xF32);
  return y.x;
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
  y.i = JBM_BITS_SIGN_16xF32;
  return _mm512_andnot_ps (y.x, x);
}

/**
 * Function to copy the sign of a __m512 vector to another __m512 vector.
 *
 * \return __m512 vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m512
jbm_copysign_16xf32 (const __m512 x,
///< __m512 vector to preserve magnitude.
                     const __m512 y)    ///< __m512 vector to preserve sign.
{
  JBM16xF32 m;
  m.i = JBM_BITS_SIGN_16xF32;
  return _mm512_or_ps (jbm_abs_16xf32 (x), _mm512_and_ps (y, m.x));
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
jbm_mod_16xf32 (const __m512 x, ///< dividend (__m512).
                const __m512 d) ///< divisor (__m512).
{
  __m512 r;
  r = _mm512_floor_ps (_mm512_div_ps (x, d));
  return
    _mm512_mask_blend_ps
    (_mm512_cmp_ps_mask (jbm_abs_16xf32 (r), _mm512_set1_ps (1.f / FLT_EPSILON),
                         _CMP_GT_OQ),
     _mm512_fnmadd_ps (r, d, x), _mm512_mul_ps (d, _mm512_set1_ps (0.5f)));
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
  const __m512i zi = _mm512_setzero_epi32 ();
  const __m512i bias = JBM_BIAS_16xF32;
  const __m512i abs_mask = JBM_BITS_ABS_16xF32;
  const __m512i exp_mask = JBM_BITS_EXPONENT_16xF32;
  const __m512i sign_mask = JBM_BITS_SIGN_16xF32;
  const __m512i mant_mask = JBM_BITS_MANTISSA_16xF32;
  JBM16xF32 y, z;
  __m512i exp;
  __mmask16 is_z, is_sub, is_nan, is_finite;
  // y(x)=abs(x)
  y.x = x;
  y.i = _mm512_and_si512 (y.i, abs_mask);
  // masks
  is_z = _mm512_cmpeq_epu32_mask (y.i, zi);
  is_nan = _mm512_cmpge_epu32_mask (y.i, exp_mask);
  is_finite = ~(is_z | is_nan);
  // extract exponent
  exp = _mm512_maskz_srli_epi32 (is_finite, y.i, 23);
  // subnormals
  is_sub = _mm512_cmpeq_epu32_mask (exp, zi) & is_finite;
  y.x = _mm512_mask_mul_ps (y.x, is_sub, y.x, _mm512_set1_ps (0x1p23f));
  exp
    = _mm512_mask_mov_epi32
      (exp, is_sub, _mm512_sub_epi32 (_mm512_srli_epi32 (y.i, 23),
                                      _mm512_set1_epi32 (23)));
  // exponent
  *e = _mm512_mask_sub_epi32 (zi, is_finite, exp, bias);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm512_or_epi32 (_mm512_and_epi32 (z.i, sign_mask),
                         _mm512_or_epi32 (_mm512_set1_epi32 (JBM_BIAS_F32
                                                             << 23),
                                          _mm512_and_epi32 (y.i, mant_mask)));
  return _mm512_mask_mov_ps (x, is_finite, y.x);
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
  x = _mm512_mask_mov_ps (x, _mm512_cmpgt_epi32_mask (_mm512_set1_epi32 (-150),
                                                      e),
                          _mm512_setzero_ps ());
  return
    _mm512_mask_mov_ps (x, _mm512_cmpgt_epi32_mask (e, _mm512_set1_epi32 (127)),
                        _mm512_set1_ps (INFINITY));
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
  const __m512 z = _mm512_setzero_ps ();
  __m512 aa, ab, y;
  ab = _mm512_mul_ps (a, b);
  y = _mm512_mask_mov_ps (z, _mm512_cmp_ps_mask (ab, z, _CMP_GT_OS), a);
  aa = jbm_abs_16xf32 (y);
  ab = jbm_abs_16xf32 (b);
  return _mm512_mask_mov_ps (y, _mm512_cmp_ps_mask (aa, ab, _CMP_GT_OS), b);
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
  return _mm512_fmadd_ps (_mm512_sub_ps (x, x1),
                          _mm512_div_ps (_mm512_sub_ps (y2, y1),
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
  k = _mm512_mask_mov_ps (y1, _mm512_cmp_ps_mask (x, x1, _CMP_GT_OS), k);
  return _mm512_mask_mov_ps (y2, _mm512_cmp_ps_mask (x, x2, _CMP_LT_OS), k);
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
  dx = jbm_sqr_16xf32 (_mm512_sub_ps (x2, x1));
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
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_cbrtwc_16xf32 (const __m512 x)
                   ///< __m512 vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_rational_5_3_16xf32 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_cbrtwc_16xf32
 * function (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_cbrt_16xf32 (const __m512 x)        ///< __m512 vector.
{
  const __m512 cbrt2 = JBM_CBRT2_16xF32;
  const __m512 cbrt4 = JBM_CBRT4_16xF32;
  const __m256i v3 = _mm256_set1_epi16 (3);
  const __m512i v2 = _mm512_set1_epi16 (2);
  const __m512i v1 = _mm512_set1_epi16 (1);
  __m512 y;
  __m512i e32, r512;
  __m256i e, e3, r;
  y = jbm_frexp_16xf32 (jbm_abs_16xf32 (x), &e32);
  e = _mm512_cvtepi32_epi16 (e32);
  e3 = _mm256_mulhi_epi16 (e, _mm256_set1_epi16 (0x5556));
  r = _mm256_sub_epi16 (e, _mm256_mullo_epi16 (e3, v3));
  r512 = _mm512_castsi256_si512 (r);
  y = jbm_ldexp_16xf32 (jbm_cbrtwc_16xf32 (y), _mm512_cvtepi16_epi32 (e3));
  y = _mm512_mask_mul_ps (y, _mm512_test_epi16_mask (r512, v1), y, cbrt2);
  y = _mm512_mask_mul_ps (y, _mm512_test_epi16_mask (r512, v2), y, cbrt4);
  return jbm_copysign_16xf32 (y, x);
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
  return jbm_polynomial_5_16xf32 (x, K_EXP2WC_F32);
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
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_expm1wc_16xf32 (const __m512 x)
///< __m512 vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  __m512 x2;
  x2 = jbm_sqr_16xf32 (x);
  x2 = _mm512_fmadd_ps (x2, _mm512_set1_ps (b4), _mm512_set1_ps (b2));
  x2 = _mm512_fmadd_ps (x2, x, _mm512_set1_ps (b1));
  x2 = _mm512_fmadd_ps (x2, x, _mm512_set1_ps (1.f));
  return _mm512_mul_ps (x, _mm512_div_ps (_mm512_set1_ps (a1), x2));
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
  return _mm512_mul_ps (x,  jbm_rational_5_2_16xf32 (x, K_LOG2WC_F32));
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
  const __m512 z = _mm512_setzero_ps ();
  __m512 y;
  __m512i e;
  __mmask16 m;
  y = jbm_frexp_16xf32 (x, &e);
  m = _mm512_cmplt_ps_mask (y, _mm512_set1_ps (M_SQRT1_2f));
  y = _mm512_add_ps (y, _mm512_maskz_mov_ps (m, y));
  e = _mm512_sub_epi32 (e, _mm512_maskz_set1_epi32 (m, 1));
  y = _mm512_add_ps (jbm_log2wc_16xf32 (_mm512_sub_ps (y,
                                        _mm512_set1_ps (1.f))),
                     _mm512_cvtepi32_ps (e));
  y = _mm512_mask_mov_ps (y, _mm512_cmpeq_ps_mask (x, z),
                          _mm512_set1_ps (-INFINITY));
  y = _mm512_mask_mov_ps (y, _mm512_cmplt_ps_mask (x, z), _mm512_set1_ps (NAN));
  return
    _mm512_mask_mov_ps (y, _mm512_cmp_ps_mask (x, x, _CMP_ORD_Q) ^ 0xffff, x);
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
                 const int e)   ///< exponent (int).
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
  return
    jbm_exp2_16xf32 (_mm512_mul_ps (_mm512_set1_ps (e), jbm_log2_16xf32 (x)));
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
  return
    _mm512_mul_ps (x,
                   jbm_polynomial_3_16xf32 (jbm_sqr_16xf32 (x), K_SINWC_F32));
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
  return jbm_polynomial_3_16xf32 (jbm_sqr_16xf32 (x), K_COSWC_F32);
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
  *s = jbm_sinwc_16xf32 (x);
  *c = jbm_coswc_16xf32 (x);
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
  const __m512 pi3_2 = _mm512_set1_ps (3.f * M_PI_2f);
  const __m512 pi = _mm512_set1_ps (M_PIf);
  const __m512 pi_2 = _mm512_set1_ps (M_PI_2f);
  const __m512 pi_4 = _mm512_set1_ps (M_PI_4f);
  __m512 y, q, s;
  q = jbm_mod_16xf32 (_mm512_add_ps (x, pi_4), _mm512_set1_ps (2.f * M_PIf));
  y = _mm512_sub_ps (q, pi_4);
  s = jbm_opposite_16xf32 (jbm_coswc_16xf32 (_mm512_sub_ps (pi3_2, y)));
  s = _mm512_mask_mov_ps (s, _mm512_cmp_ps_mask (q, pi3_2, _CMP_LT_OS),
                          jbm_sinwc_16xf32 (_mm512_sub_ps (pi, y)));
  s = _mm512_mask_mov_ps (s, _mm512_cmp_ps_mask (q, pi, _CMP_LT_OS),
                          jbm_coswc_16xf32 (_mm512_sub_ps (pi_2, y)));
  return _mm512_mask_mov_ps (s, _mm512_cmp_ps_mask (q, pi_2, _CMP_LT_OS),
                             jbm_sinwc_16xf32 (y));
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
  const __m512 pi2 = _mm512_set1_ps (2.f * M_PIf);
  __m512 y, c;
  y = jbm_mod_16xf32 (x, pi2);
  c = _mm512_mask_blend_ps (_mm512_cmp_ps_mask (y,
                                                _mm512_set1_ps (7.f * M_PI_4f),
                                                _CMP_LT_OS),
                            jbm_coswc_16xf32 (_mm512_sub_ps (y, pi2)),
                            jbm_sinwc_16xf32
                            (_mm512_sub_ps (y,
                                            _mm512_set1_ps (3.f * M_PI_2f))));
  c = _mm512_mask_mov_ps (c, _mm512_cmp_ps_mask (y,
                                                 _mm512_set1_ps (5.f * M_PI_4f),
                                                 _CMP_LT_OS),
                          jbm_opposite_16xf32
                          (jbm_coswc_16xf32
                           (_mm512_sub_ps (_mm512_set1_ps (M_PIf), y))));
  c = _mm512_mask_mov_ps (c,
                          _mm512_cmp_ps_mask (y, _mm512_set1_ps (3.f * M_PI_4f),
                                              _CMP_LT_OS),
                          jbm_sinwc_16xf32 (_mm512_sub_ps
                                            (_mm512_set1_ps (M_PI_2f), y)));
  return _mm512_mask_mov_ps (c, _mm512_cmp_ps_mask (y, _mm512_set1_ps (M_PI_4f),
                                                    _CMP_LT_OS),
                             jbm_coswc_16xf32 (y));
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
  const __m512 pi2 = _mm512_set1_ps (2.f * M_PIf);
  const __m512 z = _mm512_setzero_ps ();
  __m512 y, s1, c1, s2, c2;
  __mmask16 m;
  y = jbm_mod_16xf32 (x, pi2);
  jbm_sincoswc_16xf32 (_mm512_sub_ps (y, pi2), &s1, &c1);
  jbm_sincoswc_16xf32 (_mm512_sub_ps (y, _mm512_set1_ps (3.f * M_PI_2f)), &c2,
                       &s2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (7.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm512_mask_mov_ps (s1, m, _mm512_sub_ps (z, s2));
  c1 = _mm512_mask_mov_ps (c1, m, c2);
  jbm_sincoswc_16xf32 (_mm512_sub_ps (_mm512_set1_ps (M_PIf), y), &s2, &c2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (5.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm512_mask_mov_ps (s1, m, s2);
  c1 = _mm512_mask_mov_ps (c1, m, _mm512_sub_ps (z, c2));
  jbm_sincoswc_16xf32 (_mm512_sub_ps (_mm512_set1_ps (M_PI_2f), y), &c2, &s2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (3.f * M_PI_4f), _CMP_LT_OS);
  s1 = _mm512_mask_mov_ps (s1, m, s2);
  c1 = _mm512_mask_mov_ps (c1, m, c2);
  jbm_sincoswc_16xf32 (y, &s2, &c2);
  m = _mm512_cmp_ps_mask (y, _mm512_set1_ps (M_PI_4f), _CMP_LT_OS);
  *s = _mm512_mask_mov_ps (s1, m, s2);
  *c = _mm512_mask_mov_ps (c1, m, c2);
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
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (__m512).
 *
 * \return function value (__m512).
 */
static inline __m512
jbm_atanwc_16xf32 (const __m512 x)
                   ///< __m512 vector \f$\in\left[-1,1\right]\f$.
{
  return
    _mm512_mul_ps (x,
                   jbm_rational_5_2_16xf32 (jbm_sqr_16xf32 (x), K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc_16xf32
 * function (__m512).
 *
 * \return function value (in [-pi/2,pi/2]) (__m512).
 */
static inline __m512
jbm_atan_16xf32 (const __m512 x)        ///< __m512 vector.
{
  __m512 f, ax;
  __mmask16 m;
  ax = jbm_abs_16xf32 (x);
  m = _mm512_cmp_ps_mask (ax, _mm512_set1_ps (1.f), _CMP_GT_OS);
  ax = _mm512_mask_mov_ps (ax, m, jbm_reciprocal_16xf32 (ax));
  f = jbm_atanwc_16xf32 (ax);
  f = _mm512_mask_mov_ps (f, m, _mm512_sub_ps (_mm512_set1_ps (M_PI_2f), f));
  return jbm_copysign_16xf32 (f, x);
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
  __m512 f, g;
  f = jbm_atan_16xf32 (_mm512_div_ps (y, x));
  g = _mm512_add_ps (f, jbm_copysign_16xf32 (_mm512_set1_ps (M_PIf), y));
  return
    _mm512_mask_mov_ps (f, _mm512_cmp_ps_mask (x, _mm512_setzero_ps (),
                                               _CMP_LT_OS), g);
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
  return _mm512_mask_mov_ps (f, _mm512_cmp_ps_mask (x, _mm512_setzero_ps (),
                                                    _CMP_LT_OS),
                             _mm512_add_ps (f, _mm512_set1_ps (M_PIf)));
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
  f = _mm512_mask_mov_ps
    (f, _mm512_cmp_ps_mask (x, _mm512_set1_ps (JBM_FLT_MAX_E_EXP), _CMP_GT_OS),
     _mm512_set1_ps (1.f));
  return
    _mm512_mask_mov_ps
    (f, _mm512_cmp_ps_mask (x, _mm512_set1_ps (-JBM_FLT_MAX_E_EXP), _CMP_LT_OS),
     _mm512_set1_ps (-1.f));
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
  const __m512 u = _mm512_set1_ps (1.f);
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
  return
    _mm512_mul_ps (x,
                   jbm_polynomial_5_16xf32 (jbm_sqr_16xf32 (x), K_ERFWC_F32));
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
  __m512 f, x2;
  x2 = jbm_sqr_16xf32 (x);
  f = _mm512_mul_ps (jbm_rational_8_4_16xf32 (jbm_reciprocal_16xf32 (x),
                                              K_ERFCWC_F32),
                     _mm512_div_ps (x, jbm_exp_16xf32 (x2)));
  return
    _mm512_mask_mov_ps (f, _mm512_cmp_ps_mask (x,
                                               _mm512_set1_ps (K_ERFC_MAX_F32),
                                               _CMP_GT_OS),
                        _mm512_setzero_ps ());
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
  const __m512 u = _mm512_set1_ps (1.f);
  const __m512 ax = jbm_abs_16xf32 (x);
  return
    _mm512_mask_blend_ps (_mm512_cmp_ps_mask (ax, u, _CMP_LT_OS),
                          jbm_copysign_16xf32 (_mm512_sub_ps (u,
                                               jbm_erfcwc_16xf32 (ax)), x),
                          jbm_erfwc_16xf32 (x));
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
  const __m512 u2 = _mm512_set1_ps (2.f);
  const __m512 u = _mm512_set1_ps (1.f);
  __m512 ax, cwc, wc;
  ax = jbm_abs_16xf32 (x);
  cwc = jbm_erfcwc_16xf32 (ax);
  wc = _mm512_sub_ps (u, jbm_erfwc_16xf32 (x));
  return
    _mm512_mask_mov_ps
    (_mm512_mask_mov_ps
     (wc, _mm512_cmp_ps_mask (ax, u, _CMP_GT_OS), _mm512_sub_ps (u2, cwc)),
     _mm512_cmp_ps_mask (x, u, _CMP_GT_OS), cwc);
}

/**
 * Function to calculate the solution of a __m512 vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_quadratic_reduced_16xf32 (const __m512 a,
///< __m512 vector of 1st order coefficient of the equations.
                                    const __m512 b,
///< __m512 vector of 0th order coefficient of the equations.
                                    const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                                    const __m512 x2)
///< __m512 vector of right limits of the solution intervals.
{
  __m512 ka, kb, k1, k2;
  k1 = _mm512_set1_ps (-0.5f);
  ka = _mm512_mul_ps (a, k1);
  kb = _mm512_sqrt_ps (_mm512_sub_ps (jbm_sqr_16xf32 (ka), b));
  k1 = _mm512_add_ps (ka, kb);
  k2 = _mm512_sub_ps (ka, kb);
  k1 = _mm512_mask_mov_ps (k1, _mm512_cmp_ps_mask (k1, x1, _CMP_LT_OS), k2);
  return _mm512_mask_mov_ps (k1, _mm512_cmp_ps_mask (k1, x2, _CMP_GT_OS), k2);
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
  return _mm512_mask_mov_ps (k1, jbm_small_16xf32 (a), k2);
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
  l3 = _mm512_mask_mov_ps (l3, _mm512_cmp_ps_mask (l2, x1, _CMP_LT_OS)
                               | _mm512_cmp_ps_mask (l2, x2, _CMP_GT_OS), l2);
  l4 = _mm512_fmsub_ps (l1, jbm_cos_16xf32 (_mm512_sub_ps (l0, c2p_3)), a);
  l4 = _mm512_mask_mov_ps (l4, _mm512_cmp_ps_mask (l3, x1, _CMP_LT_OS)
                               | _mm512_cmp_ps_mask (l3, x2, _CMP_GT_OS), l3);
  k1 = _mm512_sqrt_ps (k2);
  l5 = _mm512_add_ps (k0, k1);
  l5 = jbm_cbrt_16xf32 (k2);
  k0 = _mm512_sub_ps (k0, k1);
  l5 = _mm512_add_ps (l5, _mm512_sub_ps (jbm_cbrt_16xf32 (k0), a3));
  return _mm512_mask_mov_ps (l4, _mm512_cmp_ps_mask (k2, _mm512_setzero_ps (),
                                                     _CMP_LT_OS), l5);
}

/**
 * Function to calculate the solution of a __m512 vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512 vector of solution values.
 */
static inline __m512
jbm_solve_cubic_16xf32 (const __m512 a,
///< __m512 vector of 3rd order coefficient of the equations.
                        const __m512 b,
///< __m512 vector of 2nd order coefficient of the equations.
                        const __m512 c,
///< __m512 vector of 1st order coefficient of the equations.
                        const __m512 d,
///< __m512 vector of 0th order coefficient of the equations.
                        const __m512 x1,
///< __m512 vector of left limits of the solution intervals.
                        const __m512 x2)
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
    _mm512_mask_mov_ps (_mm512_set1_ps (2.f),
                         _mm512_cmp_ps_mask (r, _mm512_set1_ps (3.f),
                                              _CMP_LT_OS), rm);

  rm =
    _mm512_mask_mov_ps (rm, _mm512_cmp_ps_mask (r, _mm512_set1_ps (1.f / 3.f),
                                                _CMP_GT_OS),
                        jbm_dbl_16xf32 (r));
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_ps (_mm512_setzero_ps (),
                             _mm512_cmp_ps_mask (_mm512_mul_ps (d1, d2),
                                                 _mm512_set1_ps (FLT_EPSILON),
                                                 _CMP_GT_OS), r);
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
  __m512 k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512 k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_ps (0.5f);
  dx = _mm512_mul_ps (h, _mm512_sub_ps (x2, x1));
  x = _mm512_mul_ps (h, _mm512_add_ps (x2, x1));
  k = _mm512_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[0]);
  k = _mm512_mul_ps (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_ps (JBM_INTEGRAL_GAUSS_B_F32[i]);
      k2 = _mm512_mul_ps (k2, dx);
      f1 = f (_mm512_sub_ps (x, k2));
      f2 = f (_mm512_add_ps (x, k2));
      h = _mm512_set1_ps (JBM_INTEGRAL_GAUSS_A_F32[i]);
      k = _mm512_fmadd_ps (h, _mm512_add_ps (f1, f2), k);
    }
#endif
  return _mm512_mul_ps (k, dx);
}

/**
 * Function to calculate the additive reduction value of a __m512d vector.
 *
 * \return additive reduction (double).
 */
static inline double
jbm_reduce_add_8xf64 (const __m512d x)  ///< __m512d vector.
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  return jbm_reduce_add_4xf64 (_mm256_add_pd (h, l));
}

/**
 * Function to calculate the maximum reduction value of a __m512d vector.
 *
 * \return maximum reduction (double).
 */
static inline double
jbm_reduce_max_8xf64 (const __m512d x)  ///< __m512d vector.
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  return jbm_reduce_max_4xf64 (_mm256_max_pd (h, l));
}

/**
 * Function to calculate the minimum reduction value of a __m512d vector.
 *
 * \return minimum reduction (double).
 */
static inline double
jbm_reduce_min_8xf64 (const __m512d x)  ///< __m512d vector.
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  return jbm_reduce_min_4xf64 (_mm256_min_pd (h, l));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m512d
 * vector.
 */
static inline void
jbm_reduce_maxmin_8xf64 (const __m512d x,       ///< __m512d vector.
                         double *max,   ///< pointer to the maximum value
                         double *min)   ///< pointer to the minimum value
{
  __m256d h, l;
  h = _mm512_extractf64x4_pd (x, 1);
  l = _mm512_castpd512_pd256 (x);
  *max = jbm_reduce_max_4xf64 (_mm256_max_pd (h, l));
  *min = jbm_reduce_min_4xf64 (_mm256_min_pd (h, l));
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
  y.i = JBM_BITS_SIGN_8xF64;
  return _mm512_xor_pd (x, y.x);
}

/**
 * Function to calculate the multiplicative inverse value of a __m512d vector.
 *
 * \return reciprocal value vector (__m512d).
 */
static inline __m512d
jbm_reciprocal_8xf64 (const __m512d x)  ///< __m512d vector.
{
  return _mm512_div_pd (_mm512_set1_pd (1.), x);
}

/**
 * Function to calculate the sign of a __m512d vector.
 *
 * \return sign vector (__m512d).
 */
static inline __m512d
jbm_sign_8xf64 (const __m512d x)        ///< __m512d vector.
{
  JBM8xF64 y;
  y.x = x;
  y.i = _mm512_and_epi64 (y.i, JBM_BITS_SIGN_8xF64);
  y.i = _mm512_or_epi64 (y.i, JBM_BITS_1_8xF64);
  return y.x;
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
  y.i = JBM_BITS_SIGN_8xF64;
  return _mm512_andnot_pd (y.x, x);
}

/**
 * Function to copy the sign of a __m512d vector to another __m512d vector.
 *
 * \return __m512d vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m512d
jbm_copysign_8xf64 (const __m512d x,
///< __m512d vector to preserve magnitude.
                    const __m512d y)    ///< __m512d vector to preserve sign.
{
  JBM8xF64 m;
  m.i = JBM_BITS_SIGN_8xF64;
  return _mm512_or_pd (jbm_abs_8xf64 (x), _mm512_and_pd (y, m.x));
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
jbm_mod_8xf64 (const __m512d x, ///< dividend (__m512d).
               const __m512d d) ///< divisor (__m512d).
{
  __m512d r;
  r = _mm512_floor_pd (_mm512_div_pd (x, d));
  return
    _mm512_mask_blend_pd
    (_mm512_cmp_pd_mask (jbm_abs_8xf64 (r), _mm512_set1_pd (1. / DBL_EPSILON),
                         _CMP_GT_OQ),
     _mm512_fnmadd_pd (r, d, x), _mm512_mul_pd (d, _mm512_set1_pd (0.5)));
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
  const __m512i zi = _mm512_setzero_si512 ();
  const __m512i bias = JBM_BIAS_8xF64;
  const __m512i abs_mask = JBM_BITS_ABS_8xF64;
  const __m512i exp_mask = JBM_BITS_EXPONENT_8xF64;
  const __m512i sign_mask = JBM_BITS_SIGN_8xF64;
  const __m512i mant_mask = JBM_BITS_MANTISSA_8xF64;
  JBM8xF64 y, z;
  __m512i exp;
  __mmask16 is_z, is_sub, is_nan, is_finite;
  // y(x)=abs(x)
  y.x = x;
  y.i = _mm512_and_si512 (y.i, abs_mask);
  // masks
  is_z = _mm512_cmpeq_epu64_mask (y.i, zi);
  is_nan = _mm512_cmpge_epu64_mask (y.i, exp_mask);
  is_finite = ~(is_z | is_nan);
  // extract exponent
  exp = _mm512_maskz_srli_epi64 (is_finite, y.i, 52);
  // subnormals
  is_sub = _mm512_cmpeq_epu64_mask (exp, zi) & is_finite;
  y.x = _mm512_mask_mul_pd (y.x, is_sub, y.x, _mm512_set1_pd (0x1p52));
  exp
    = _mm512_mask_mov_epi64
      (exp, is_sub, _mm512_sub_epi64 (_mm512_srli_epi64 (y.i, 52),
                                      _mm512_set1_epi64 (52ll)));
  // exponent
  *e = _mm512_mask_sub_epi64 (zi, is_finite, exp, bias);
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = _mm512_or_epi64 (_mm512_and_epi64 (z.i, sign_mask),
                         _mm512_or_epi64 (_mm512_set1_epi64 (JBM_BIAS_F64
                                                             << 52),
                                          _mm512_and_epi64 (y.i, mant_mask)));
  return _mm512_mask_mov_pd (x, is_finite, y.x);
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
  const __m512i v1074 = _mm512_set1_epi64 (1074ll);
  const __m512i v1023 = _mm512_set1_epi64 (1023ll);
  const __m512i vn1023 = _mm512_set1_epi64 (-1023ll);
  const __m512i vn1074 = _mm512_set1_epi64 (-1074ll);
  __m512d x;
  __mmask16 is_norm;
  is_norm = _mm512_cmpgt_epi64_mask (e, vn1023);
  x =
    _mm512_mask_blend_pd
    (is_norm, _mm512_setzero_pd (),
     _mm512_castsi512_pd (_mm512_slli_epi64 (_mm512_add_epi64 (e,
                                                               v1023), 52)));
  x =
    _mm512_mask_mov_pd
    (x, _mm512_cmpgt_epi64_mask (e, vn1074) & ~is_norm,
     _mm512_castsi512_pd
     (_mm512_sllv_epi64 (_mm512_set1_epi64 (1ll),
                         _mm512_add_epi64 (e, v1074))));
  return
    _mm512_mask_mov_pd (x, _mm512_cmpgt_epi64_mask (e, v1023),
                        _mm512_set1_pd (INFINITY));
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
  y = _mm512_mask_mov_pd (a, _mm512_cmp_pd_mask (z, ab, _CMP_GT_OS), z);
  aa = jbm_abs_8xf64 (y);
  ab = jbm_abs_8xf64 (b);
  return _mm512_mask_mov_pd (y, _mm512_cmp_pd_mask (aa, ab, _CMP_GT_OS), b);
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
  k = _mm512_mask_mov_pd (y1, _mm512_cmp_pd_mask (x, x1, _CMP_GT_OS), k);
  return _mm512_mask_mov_pd (y2, _mm512_cmp_pd_mask (x, x2, _CMP_LT_OS), k);
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
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_cbrtwc_8xf64 (const __m512d x)
                  ///< __m512d vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_rational_11_6_8xf64 (x, K_CBRTWC_F64);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_cbrtwc_8xf32
 * function (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_cbrt_8xf64 (const __m512d x)        ///< __m512d vector.
{
  const __m512d cbrt2 = JBM_CBRT2_8xF64;
  const __m512d cbrt4 = JBM_CBRT4_8xF64;
  const __m512i v3 = _mm512_set1_epi32 (3);
  const __m512i v2 = _mm512_set1_epi64 (2);
  const __m512i v1 = _mm512_set1_epi64 (1);
  __m512d y;
  __m512i e, e3, r, n;
  y = jbm_frexp_8xf64 (jbm_abs_8xf64 (x), &e);
  e3 = _mm512_mul_epu32 (e, _mm512_set1_epi32 (0x55555556));
  e3 = _mm512_srli_epi64 (e3, 32);
  r = _mm512_sub_epi32 (e, _mm512_mullo_epi32 (e3, v3));
  n = _mm512_srai_epi32 (r, 31);
  r = _mm512_add_epi32 (r, _mm512_and_si512 (n, v3));
  e3 = _mm512_sub_epi32 (e3, _mm512_and_si512 (n, _mm512_set1_epi32 (1)));
  y = jbm_ldexp_8xf64 (jbm_cbrtwc_8xf64 (y), e3);
  y = _mm512_mask_mul_pd (y, _mm512_cmpeq_epi64_mask (r, v1), y, cbrt2);
  y = _mm512_mask_mul_pd (y, _mm512_cmpeq_epi64_mask (r, v2), y, cbrt4);
  return jbm_copysign_8xf64 (y, x);
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
  return _mm512_mul_pd (x, jbm_rational_8_2_8xf64 (x, K_EXPM1WC_F64));
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
  return jbm_rational_9_4_8xf64 (x, K_EXP2WC_F64);
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
  return _mm512_mul_pd (jbm_exp2n_8xf64 (_mm512_cvtpd_epi64 (y)),
                        jbm_exp2wc_8xf64 (f));
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
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_log2wc_8xf64 (const __m512d x)      ///< __m512d vector.
{
  return _mm512_mul_pd (x, jbm_rational_12_6_8xf64 (x, K_LOG2WC_F64));
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
  const __m512d z = _mm512_setzero_pd ();
  __m512d y;
  __m512i e;
  __mmask16 m;
  y = jbm_frexp_8xf64 (x, &e);
  m = _mm512_cmplt_pd_mask (y, _mm512_set1_pd (M_SQRT1_2));
  y = _mm512_add_pd (y, _mm512_maskz_mov_pd (m, y));
  e = _mm512_sub_epi64 (e, _mm512_maskz_set1_epi64 (m, 1));
  y = _mm512_add_pd (jbm_log2wc_8xf64 (_mm512_sub_pd (y,
                                       _mm512_set1_pd (1.))),
                     _mm512_cvtepi64_pd (e));
  y = _mm512_mask_mov_pd (y, _mm512_cmpeq_pd_mask (x, z),
                          _mm512_set1_pd (-INFINITY));
  y = _mm512_mask_mov_pd (y, _mm512_cmplt_pd_mask (x, z), _mm512_set1_pd (NAN));
  return
    _mm512_mask_mov_pd (y, _mm512_cmp_pd_mask (x, x, _CMP_ORD_Q) ^ 0xffff, x);
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
                const int e)    ///< exponent (int).
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
  return
    jbm_exp2_8xf64 (_mm512_mul_pd (_mm512_set1_pd (e), jbm_log2_8xf64 (x)));
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
  return
    _mm512_mul_pd (x, jbm_polynomial_6_8xf64 (jbm_sqr_8xf64 (x), K_SINWC_F64));
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
  return jbm_polynomial_6_8xf64 (jbm_sqr_8xf64 (x), K_COSWC_F64);
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
  *s = jbm_sinwc_8xf64 (x);
  *c = jbm_coswc_8xf64 (x);
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
  const __m512d pi2 = _mm512_set1_pd (2. * M_PI);
  __m512d y, s;
  y = jbm_mod_8xf64 (x, pi2);
  s = jbm_sinwc_8xf64 (_mm512_sub_pd (y, pi2));
  s = _mm512_mask_mov_pd (s,
                          _mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4),
                                              _CMP_LT_OS),
                          jbm_opposite_8xf64
                          (jbm_coswc_8xf64
                           (_mm512_sub_pd (_mm512_set1_pd (3. * M_PI_2),
                                           y))));
  s =
    _mm512_mask_mov_pd (s, _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4),
                                              _CMP_LT_OS),
                        jbm_sinwc_8xf64 (_mm512_sub_pd (_mm512_set1_pd (M_PI),
                                                        y)));
  s =
    _mm512_mask_mov_pd (s, _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4),
                                               _CMP_LT_OS),
                        jbm_coswc_8xf64 (_mm512_sub_pd (_mm512_set1_pd (M_PI_2),
                                                        y)));
  return _mm512_mask_mov_pd (s, _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4),
                                                   _CMP_LT_OS),
                             jbm_sinwc_8xf64 (y));
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
  const __m512d pi2 = _mm512_set1_pd (2. * M_PI);
  __m512d y, c;
  y = jbm_mod_8xf64 (x, pi2);
  c = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4),
                                                _CMP_LT_OS),
                            jbm_coswc_8xf64 (_mm512_sub_pd (y, pi2)),
                            jbm_sinwc_8xf64
                            (_mm512_sub_pd (y, _mm512_set1_pd (3. * M_PI_2))));
  c = _mm512_mask_mov_pd (c,
                          _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4),
                                              _CMP_LT_OS),
                          jbm_opposite_8xf64
                          (jbm_coswc_8xf64
                           (_mm512_sub_pd (_mm512_set1_pd (M_PI), y))));
  c = _mm512_mask_mov_pd (c,
                          _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4),
                                              _CMP_LT_OS),
                          jbm_sinwc_8xf64 (_mm512_sub_pd
                                           (_mm512_set1_pd (M_PI_2), y)));
  return _mm512_mask_mov_pd (c, _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4),
                                                   _CMP_LT_OS),
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
  const __m512d pi2 = _mm512_set1_pd (2. * M_PI);
  const __m512d z = _mm512_setzero_pd ();
  __m512d y, s1, c1, s2, c2;
  __mmask16 m;
  y = jbm_mod_8xf64 (x, pi2);
  jbm_sincoswc_8xf64 (_mm512_sub_pd (y, pi2), &s1, &c1);
  jbm_sincoswc_8xf64 (_mm512_sub_pd (y, _mm512_set1_pd (3. * M_PI_2)), &c2,
                      &s2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (7. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_mov_pd (s1, m, _mm512_sub_pd (z, s2));
  c1 = _mm512_mask_mov_pd (c1, m, c2);
  jbm_sincoswc_8xf64 (_mm512_sub_pd (_mm512_set1_pd (M_PI), y), &s2, &c2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (5. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_mov_pd (s1, m, s2);
  c1 = _mm512_mask_mov_pd (c1, m, _mm512_sub_pd (z, c2));
  jbm_sincoswc_8xf64 (_mm512_sub_pd (_mm512_set1_pd (M_PI_2), y), &c2, &s2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (3. * M_PI_4), _CMP_LT_OS);
  s1 = _mm512_mask_mov_pd (s1, m, s2);
  c1 = _mm512_mask_mov_pd (c1, m, c2);
  jbm_sincoswc_8xf64 (y, &s2, &c2);
  m = _mm512_cmp_pd_mask (y, _mm512_set1_pd (M_PI_4), _CMP_LT_OS);
  *s = _mm512_mask_mov_pd (s1, m, s2);
  *c = _mm512_mask_mov_pd (c1, m, c2);
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
 * [-1,1] (__m512d).
 *
 * \return function value (__m512d).
 */
static inline __m512d
jbm_atanwc_8xf64 (const __m512d x)
                  ///< __m512d vector \f$\in\left[0,\frac12\right]\f$.
{
  return
    _mm512_mul_pd (x,
                   jbm_rational_11_5_8xf64 (jbm_sqr_8xf64 (x), K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc_8xf64
 * function (__m512d).
 *
 * \return function value (__m512d in [-pi/2,pi/2]).
 */
static inline __m512d
jbm_atan_8xf64 (const __m512d x)        ///< double number.
{
  __m512d f, ax;
  __mmask16 m;
  ax = jbm_abs_8xf64 (x);
  m = _mm512_cmp_pd_mask (ax, _mm512_set1_pd (1.), _CMP_GT_OS);
  ax = _mm512_mask_mov_pd (ax, m, jbm_reciprocal_8xf64 (ax));
  f = jbm_atanwc_8xf64 (ax);
  f = _mm512_mask_mov_pd (f, m, _mm512_sub_pd (_mm512_set1_pd (M_PI_2), f));
  return jbm_copysign_8xf64 (f, x);

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
  const __m512d pi = _mm512_set1_pd (M_PI);
  const __m512d z = _mm512_setzero_pd ();
  __m512d f, g;
  f = jbm_atan_8xf64 (_mm512_div_pd (y, x));
  g = _mm512_add_pd (f, jbm_copysign_8xf64 (pi, y));
  return _mm512_mask_mov_pd (f, _mm512_cmp_pd_mask (x, z, _CMP_LT_OS), g);
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
  return _mm512_mask_mov_pd (f, _mm512_cmp_pd_mask (x, _mm512_setzero_pd (),
                                                   _CMP_LT_OS),
                             _mm512_add_pd (f, _mm512_set1_pd (M_PI)));
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
  f = _mm512_mask_mov_pd
    (f, _mm512_cmp_pd_mask (x, _mm512_set1_pd (JBM_DBL_MAX_E_EXP), _CMP_GT_OS),
     _mm512_set1_pd (1.));
  return _mm512_mask_mov_pd
    (f, _mm512_cmp_pd_mask (x, _mm512_set1_pd (-JBM_DBL_MAX_E_EXP), _CMP_LT_OS),
     _mm512_set1_pd (-1.));
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
  return
    _mm512_mul_pd (x, jbm_rational_9_4_8xf64 (jbm_sqr_8xf64 (x), K_ERFWC_F64));
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
  __m512d f, x2;
  x2 = jbm_sqr_8xf64 (x);
  f = _mm512_mul_pd (jbm_rational_18_10_8xf64 (jbm_reciprocal_8xf64 (x),
                                               K_ERFCWC_F64),
                     _mm512_div_pd (x, jbm_exp_8xf64 (x2)));
  return
    _mm512_mask_mov_pd (f, _mm512_cmp_pd_mask (x,
                                               _mm512_set1_pd (K_ERFC_MAX_F64),
                                               _CMP_GT_OS),
                        _mm512_setzero_pd ());
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
  const __m512d u = _mm512_set1_pd (1.);
  __m512d ax;
  ax = jbm_abs_8xf64 (x);
  return
    _mm512_mask_blend_pd (_mm512_cmp_pd_mask (ax, u, _CMP_LT_OS),
                          jbm_copysign_8xf64 (_mm512_sub_pd (u,
                                              jbm_erfcwc_8xf64 (ax)), x),
                          jbm_erfwc_8xf64 (x));
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
  const __m512d u2 = _mm512_set1_pd (2.);
  const __m512d u = _mm512_set1_pd (1.);
  __m512d ax, cwc, wc;
  ax = jbm_abs_8xf64 (x);
  cwc = jbm_erfcwc_8xf64 (ax);
  wc = _mm512_sub_pd (u, jbm_erfwc_8xf64 (x));
  return
    _mm512_mask_mov_pd
    (_mm512_mask_mov_pd
     (wc, _mm512_cmp_pd_mask (ax, u, _CMP_GT_OS), _mm512_sub_pd (u2, cwc)),
     _mm512_cmp_pd_mask (x, u, _CMP_GT_OS), cwc);
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
  k1 = _mm512_mask_mov_pd (k1, _mm512_cmp_pd_mask (k1, x1, _CMP_LT_OS), k2);
  return _mm512_mask_mov_pd (k1, _mm512_cmp_pd_mask (k1, x2, _CMP_GT_OS), k2);
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
  return _mm512_mask_mov_pd (k1, jbm_small_8xf64 (a), k2);
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
  l3 = _mm512_mask_mov_pd (l3, _mm512_cmp_pd_mask (l2, x1, _CMP_LT_OS)
                               | _mm512_cmp_pd_mask (l2, x2, _CMP_GT_OS), l2);
  l4 = _mm512_fmsub_pd (l1, jbm_cos_8xf64 (_mm512_sub_pd (l0, c2p_3)), a);
  l4 = _mm512_mask_mov_pd (l4, _mm512_cmp_pd_mask (l3, x1, _CMP_LT_OS)
                               | _mm512_cmp_pd_mask (l3, x2, _CMP_GT_OS), l3);
  k1 = _mm512_sqrt_pd (k2);
  l5 = _mm512_add_pd (k0, k1);
  l5 = jbm_cbrt_8xf64 (k2);
  k0 = _mm512_sub_pd (k0, k1);
  l5 = _mm512_add_pd (l5, _mm512_sub_pd (jbm_cbrt_8xf64 (k0), a3));
  return _mm512_mask_mov_pd (l4, _mm512_cmp_pd_mask (k2, _mm512_setzero_pd (),
                                                     _CMP_LT_OS), l5);

}

/**
 * Function to calculate the solution of a __m512d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_cubic_8xf64 (const __m512d a,
///< __m512d vector of 3rd order coefficient of the equations.
                       const __m512d b,
///< __m512d vector of 2nd order coefficient of the equations.
                       const __m512d c,
///< __m512d vector of 1st order coefficient of the equations.
                       const __m512d d,
///< __m512d vector of 0th order coefficient of the equations.
                       const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                       const __m512d x2)
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  rm = _mm512_mask_mov_pd (_mm512_set1_pd (2.),
                           _mm512_cmp_pd_mask (r, _mm512_set1_pd (3.),
                                               _CMP_LT_OS), rm);
  rm = _mm512_mask_mov_pd (rm, _mm512_cmp_pd_mask (r, _mm512_set1_pd (1. / 3.),
                                                   _CMP_GT_OS),
                           jbm_dbl_8xf64 (r));
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  return _mm512_mask_mov_pd (_mm512_setzero_pd (),
                             _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2),
                                                 _mm512_set1_pd (DBL_EPSILON),
                                                 _CMP_GT_OS), r);
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
  __m512d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_pd (0.5);
  dx = _mm512_mul_pd (h, _mm512_sub_pd (x2, x1));
  x = _mm512_mul_pd (h, _mm512_add_pd (x2, x1));
  k = _mm512_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[0]);
  k = _mm512_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_pd (JBM_INTEGRAL_GAUSS_B_F64[i]);
      k2 = _mm512_mul_pd (k2, dx);
      f1 = f (_mm512_sub_pd (x, k2));
      f2 = f (_mm512_add_pd (x, k2));
      h = _mm512_set1_pd (JBM_INTEGRAL_GAUSS_A_F64[i]);
      k = _mm512_fmadd_pd (h, _mm512_add_pd (f1, f2), k);
    }
#endif
  k = _mm512_mul_pd (k, dx);
  return k;
}

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_add_f32 (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< 1st addend float array.
                   const float *restrict x2,    ///< 1st addend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 4; j > 0; --j, i += 16)
    _mm512_store_ps (xr + i, _mm512_add_ps (_mm512_load_ps (x1 + i),
                                            _mm512_load_ps (x2 + i)));
  for (j = (n - i) >> 3; j > 0; --j, i += 8)
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
jbm_array_sub_f32 (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< minuend float array.
                   const float *restrict x2,    ///< subtrahend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 4; j > 0; --j, i += 16)
    _mm512_store_ps (xr + i, _mm512_sub_ps (_mm512_load_ps (x1 + i),
                                            _mm512_load_ps (x2 + i)));
  for (j = (n - i) >> 3; j > 0; --j, i += 8)
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
jbm_array_mul1_f32 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< multiplier float array.
                    const float x2,     ///< multiplicand float number.
                    const unsigned int n)       ///< number of array elements.
{
  __m512 a16;
  __m256 a8;
  __m128 s4;
  unsigned int i, j;
  i = 0;
  j = n >> 4;
  if (j)
    {
      a16 = _mm512_set1_ps (x2);
      for (; j > 0; --j, i += 16)
        _mm512_store_ps (xr + i, _mm512_mul_ps (_mm512_load_ps (x1 + i), a16));
    }
  j = (n - i) >> 3;
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
jbm_array_div1_f32 (float *restrict xr, ///< result float array.
                    const float *restrict x1,   ///< dividend float array.
                    const float x2,     ///< divisor float number.
                    const unsigned int n)       ///< number of array elements.
{
  __m512 a16;
  __m256 a8;
  __m128 s4;
  unsigned int i, j;
  i = 0;
  j = n >> 4;
  if (j)
    {
      a16 = _mm512_set1_ps (x2);
      for (; j > 0; --j, i += 16)
        _mm512_store_ps (xr + i, _mm512_div_ps (_mm512_load_ps (x1 + i), a16));
    }
  j = (n - i) >> 3;
  if (j)
    {
      a8 = _mm256_set1_ps (x2);
      for (; j > 0; --j, i += 8)
        _mm256_store_ps (xr + i, _mm256_div_ps (_mm256_load_ps (x1 + i), a8));
    }
  j = (n - i) >> 2;
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
jbm_array_mul_f32 (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< multiplier float array.
                   const float *restrict x2,    ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 4; j > 0; --j, i += 16)
    _mm512_store_ps (xr + i, _mm512_mul_ps (_mm512_load_ps (x1 + i),
                                            _mm512_load_ps (x2 + i)));
  for (j = (n - i) >> 3; j > 0; --j, i += 8)
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
jbm_array_div_f32 (float *restrict xr,  ///< result float array.
                   const float *restrict x1,    ///< dividend float array.
                   const float *restrict x2,    ///< divisor float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 4; j > 0; --j, i += 16)
    _mm512_store_ps (xr + i, _mm512_div_ps (_mm512_load_ps (x1 + i),
                                            _mm512_load_ps (x2 + i)));
  for (j = (n - i) >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, _mm256_div_ps (_mm256_load_ps (x1 + i),
                                            _mm256_load_ps (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i,
                  _mm_div_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to do the dot product of 2 float arrays.
 *
 * \return dot product (float).
 */
static inline float
jbm_array_dot_f32 (const float *restrict x1,    ///< multiplier float array.
                   const float *restrict x2,    ///< multiplicand float array.
                   const unsigned int n)        ///< number of array elements.
{
  __m512 a512;
  __m256 a256;
  __m128 a128;
  float a32 = 0.;
  unsigned int i, j;
  i = 0;
  j = n >> 4;
  if (j)
    {
      a512 = _mm512_mul_ps (_mm512_load_ps (x1 + i), _mm512_load_ps (x2 + i));
      while (--j)
        {
          i += 16;
          a512 = _mm512_fmadd_ps (_mm512_load_ps (x1 + i),
                                  _mm512_load_ps (x2 + i), a512);
        }
      a32 = jbm_reduce_add_16xf32 (a512);
      i += 16;
    }
  j = (n - i) >> 3;
  if (j)
    {
      a256 = _mm256_mul_ps (_mm256_load_ps (x1 + i), _mm256_load_ps (x2 + i));
      while (--j)
        {
          i += 8;
          a256 = _mm256_fmadd_ps (_mm256_load_ps (x1 + i),
                                  _mm256_load_ps (x2 + i), a256);
        }
      a32 += jbm_reduce_add_8xf32 (a256);
      i += 8;
    }
  j = (n - i) >> 2;
  if (j)
    {
      a128 = _mm_mul_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i));
      while (--j)
        {
          i += 4;
          a128
            = _mm_fmadd_ps (_mm_load_ps (x1 + i), _mm_load_ps (x2 + i), a128);
        }
      a32 += jbm_reduce_add_4xf32 (a128);
      i += 4;
    }
  for (; i < n; ++i)
    a32 += x1[i] * x2[i];
  return a32;
}

/**
 * Function to calculate the double of a float array.
 */
static inline void
jbm_array_dbl_f32 (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 4; j > 0; --j, i += 16)
    _mm512_store_ps (xr + i, jbm_dbl_16xf32 (_mm512_load_ps (xd + i)));
  for (j = (n - i) >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, jbm_dbl_8xf32 (_mm256_load_ps (xd + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm_store_ps (xr + i, jbm_dbl_4xf32 (_mm_load_ps (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_dbl_f32 (xd[i]);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_sqr_f32 (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 4; j > 0; --j, i += 16)
    _mm512_store_ps (xr + i, jbm_sqr_16xf32 (_mm512_load_ps (xd + i)));
  for (j = (n - i) >> 3; j > 0; --j, i += 8)
    _mm256_store_ps (xr + i, jbm_sqr_8xf32 (_mm256_load_ps (xd + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
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
jbm_array_max_f32 (const float *x,      ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (float, _mm512_max_ps, _mm256_max_ps, _mm_max_ps, fmaxf,
                       jbm_reduce_max_16xf32, jbm_reduce_max_8xf32,
                       jbm_reduce_max_4xf32, -INFINITY);
}

/**
 * Function to find the lowest element of a float array.
 *
 * \return the lowest value.
 */
static inline float
jbm_array_min_f32 (const float *x,      ///< float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (float, _mm512_min_ps, _mm256_min_ps, _mm_min_ps, fminf,
                       jbm_reduce_min_16xf32, jbm_reduce_min_8xf32,
                       jbm_reduce_min_4xf32, INFINITY);
}

/**
 * Function to find the highest and the lowest elements of a float array.
 */
static inline void
jbm_array_maxmin_f32 (const float *x,   ///< float array.
                      float *max,       ///< the highest value.
                      float *min,       ///< the lowest value.
                      const unsigned int n)     ///< number of array elements.
{
  __m512 max512, min512; 
  __m256 max256, min256;
  __m128 max128, min128;
  double max32 = -INFINITY;
  double min32 = INFINITY;
  unsigned int i, j;
  i = 0;
  j = n >> 4;
  if (j)
    {
      max512 = min512 = _mm512_load_ps (x + i);
      while (--j)
        {
          i += 16;
          max512 = _mm512_max_ps (max512, _mm512_load_ps (x + i));
          min512 = _mm512_min_ps (min512, _mm512_load_ps (x + i));
        }
      max32 = jbm_reduce_max_16xf32 (max512);
      min32 = jbm_reduce_min_16xf32 (min512);
      i += 16;
    }
  j = (n - i) >> 3;
  if (j)
    {
      max256 = min256 = _mm256_load_ps (x + i);
      while (--j)
        {
          i += 8;
          max256 = _mm256_max_ps (max256, _mm256_load_ps (x + i));
          min256 = _mm256_min_ps (min256, _mm256_load_ps (x + i));
        }
      max32 = fmaxf (max32, jbm_reduce_max_8xf32 (max256));
      min32 = fminf (min32, jbm_reduce_min_8xf32 (min256));
      i += 8;
    }
  j = (n - i) >> 2;
  if (j)
    {
      max128 = min128 = _mm_load_ps (x + i);
      while (--j)
        {
          i += 4;
          max128 = _mm_max_ps (max128, _mm_load_ps (x + i));
          min128 = _mm_min_ps (min128, _mm_load_ps (x + i));
        }
      max32 = fmaxf (max32, jbm_reduce_max_4xf32 (max128));
      min32 = fminf (min32, jbm_reduce_min_4xf32 (min128));
      i += 4;
    }
  while (i < n)
    {
      max32 = fmaxf (max32, x[i]);
      min32 = fminf (min32, x[i++]);
    }
  *max = max32, *min = min32;
}

/**
 * Function to add 2 double arrays.
 */
static inline void
jbm_array_add_f64 (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< 1st addend double array.
                   const double *restrict x2,   ///< 1st addend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm512_store_pd (xr + i, _mm512_add_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
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
jbm_array_sub_f64 (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< minuend double array.
                   const double *restrict x2,   ///< subtrahend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm512_store_pd (xr + i, _mm512_sub_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
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
jbm_array_mul1_f64 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< multiplier double array.
                    const double x2,    ///< multiplicand double number.
                    const unsigned int n)       ///< number of array elements.
{
  __m512d a8;
  __m256d a4;
  __m128d s2;
  unsigned int i, j;
  i = 0;
  j = n >> 3;
  if (j)
    {
      a8 = _mm512_set1_pd (x2);
      for (; j > 0; --j, i += 8)
        _mm512_store_pd (xr + i, _mm512_mul_pd (_mm512_load_pd (x1 + i), a8));
    }
  j = (n - i) >> 2;
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
jbm_array_div1_f64 (double *restrict xr,        ///< result double array.
                    const double *restrict x1,  ///< dividend double array.
                    const double x2,    ///< divisor double number.
                    const unsigned int n)       ///< number of array elements.
{
  __m512d a8;
  __m256d a4;
  __m128d s2;
  unsigned int i, j;
  i = 0;
  j = n >> 3;
  if (j)
    {
      a8 = _mm512_set1_pd (x2);
      for (; j > 0; --j, i += 8)
        _mm512_store_pd (xr + i, _mm512_div_pd (_mm512_load_pd (x1 + i), a8));
    }
  j = (n - i) >> 2;
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
jbm_array_mul_f64 (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< multiplier double array.
                   const double *restrict x2,   ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm512_store_pd (xr + i, _mm512_mul_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
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
jbm_array_div_f64 (double *restrict xr, ///< result double array.
                   const double *restrict x1,   ///< dividend double array.
                   const double *restrict x2,   ///< divisor double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm512_store_pd (xr + i, _mm512_div_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, _mm256_div_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i,
                  _mm_div_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to do the dot product of 2 double arrays.
 *
 * \return dot product (double).
 */
static inline double
jbm_array_dot_f64 (const double *restrict x1,   ///< multiplier double array.
                   const double *restrict x2,   ///< multiplicand double array.
                   const unsigned int n)        ///< number of array elements.
{
  __m512d a512;
  __m256d a256;
  __m128d a128;
  double a64 = 0.;
  unsigned int i, j;
  i = 0;
  j = n >> 3;
  if (j)
    {
      a512 = _mm512_mul_pd (_mm512_load_pd (x1 + i), _mm512_load_pd (x2 + i));
      while (--j)
        {
          i += 8;
          a512 = _mm512_fmadd_pd (_mm512_load_pd (x1 + i),
                                  _mm512_load_pd (x2 + i), a512);
        }
      a64 += jbm_reduce_add_8xf64 (a512);
      i += 8;
    }
  j = (n - i) >> 2;
  if (j)
    {
      a256 = _mm256_mul_pd (_mm256_load_pd (x1 + i), _mm256_load_pd (x2 + i));
      while (--j)
        {
          i += 4;
          a256 = _mm256_fmadd_pd (_mm256_load_pd (x1 + i),
                                  _mm256_load_pd (x2 + i), a256);
        }
      a64 += jbm_reduce_add_4xf64 (a256);
      i += 4;
    }
  j = (n - i) >> 1;
  if (j)
    {
      a128 = _mm_mul_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i));
      while (--j)
        {
          i += 2;
          a128
            = _mm_fmadd_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i), a128);
        }
      a64 += jbm_reduce_add_2xf64 (a128);
      i += 2;
    }
  for (; i < n; ++i)
    a64 += x1[i] * x2[i];
  return a64;
}

/**
 * Function to calculate the double of a double array.
 */
static inline void
jbm_array_dbl_f64 (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm512_store_pd (xr + i, jbm_dbl_8xf64 (_mm512_load_pd (xd + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, jbm_dbl_4xf64 (_mm256_load_pd (xd + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
    _mm_store_pd (xr + i, jbm_dbl_2xf64 (_mm_load_pd (xd + i)));
  for (; i < n; ++i)
    xr[i] = jbm_dbl_f64 (xd[i]);
}

/**
 * Function to calculate the square of a double array.
 */
static inline void
jbm_array_sqr_f64 (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i, j;
  for (i = 0, j = n >> 3; j > 0; --j, i += 8)
    _mm512_store_pd (xr + i, jbm_sqr_8xf64 (_mm512_load_pd (xd + i)));
  for (j = (n - i) >> 2; j > 0; --j, i += 4)
    _mm256_store_pd (xr + i, jbm_sqr_4xf64 (_mm256_load_pd (xd + i)));
  for (j = (n - i) >> 1; j > 0; --j, i += 2)
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
jbm_array_max_f64 (const double *x,     ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (double, _mm512_max_pd, _mm256_max_pd, _mm_max_pd, fmax,
                       jbm_reduce_max_8xf64, jbm_reduce_max_4xf64,
                       jbm_reduce_max_2xf64, -INFINITY);
}

/**
 * Function to find the lowest element of a double array.
 *
 * \return the lowest value.
 */
static inline double
jbm_array_min_f64 (const double *x,     ///< double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_REDUCE_OP (double, _mm512_min_pd, _mm256_min_pd, _mm_min_pd, fmin,
                       jbm_reduce_min_8xf64, jbm_reduce_min_4xf64,
                       jbm_reduce_min_2xf64, INFINITY);
}

/**
 * Function to find the highest and the lowest elements of a double array.
 */
static inline void
jbm_array_maxmin_f64 (const double *x, ///< double array.
                      double *max,      ///< the highest value.
                      double *min,      ///< the lowest value.
                      const unsigned int n)     ///< number of array elements.
{
  __m512d max512 = _mm512_set1_pd (-INFINITY);
  __m512d min512 = _mm512_set1_pd (INFINITY);
  __m256d max256 = _mm256_set1_pd (-INFINITY);
  __m256d min256 = _mm256_set1_pd (INFINITY);
  __m128d max128 = _mm_set1_pd (-INFINITY);
  __m128d min128 = _mm_set1_pd (INFINITY);
  double max64 = -INFINITY;
  double min64 = INFINITY;
  unsigned int i, j;
  i = 0;
  j = n >> 3;
  if (j)
    {
      do
        {
          max512 = _mm512_max_pd (max512, _mm512_load_pd (x + i));
          min512 = _mm512_min_pd (min512, _mm512_load_pd (x + i));
          i += 8;
        }
      while (--j);
      max64 = fmax (max64, jbm_reduce_max_8xf64 (max512));
      min64 = fmin (min64, jbm_reduce_min_8xf64 (min512));
    }
  j = (n - i) >> 2;
  if (j)
    {
      do
        {
          max256 = _mm256_max_pd (max256, _mm256_load_pd (x + i));
          min256 = _mm256_min_pd (min256, _mm256_load_pd (x + i));
          i += 4;
        }
      while (--j);
      max64 = fmax (max64, jbm_reduce_max_4xf64 (max256));
      min64 = fmin (min64, jbm_reduce_min_4xf64 (min256));
    }
  j = (n - i) >> 1;
  if (j)
    {
      do
        {
          max128 = _mm_max_pd (max128, _mm_load_pd (x + i));
          min128 = _mm_min_pd (min128, _mm_load_pd (x + i));
          i += 2;
        }
      while (--j);
      max64 = fmax (max64, jbm_reduce_max_2xf64 (max128));
      min64 = fmin (min64, jbm_reduce_min_2xf64 (min128));
    }
  while (i < n)
    {
      max64 = fmax (max64, x[i]);
      min64 = fmin (min64, x[i++]);
    }
  *max = max64, *min = min64;
}

#endif
