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
 * \file math_neon.h
 * \brief Header file with useful mathematical functions for ARM NEON.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_NEON__H
#define JB_MATH_NEON__H 1

#include "math_f32.h"
#include "math_f64.h"

/**
 * union to work with bits in 4 packed float numbers.
 */
typedef union
{
  float32x4_t x;                ///< floating point.
  uint32x4_t i;                 ///< bits.
} JBM4xF32;

/**
 * union to work with bits in 2 packed double numbers.
 */
typedef union
{
  float64x2_t x;                ///< floating point.
  uint64x2_t i;                 ///< bits.
} JBM2xF64;

// float constants

#define JBM_4xF32_BIAS vdupq_n_u32 (JBM_F32_BIAS)
///< bias for floats.
#define JBM_4xF32_BITS_1 vdupq_n_u32 (JBM_F32_BITS_1)
///< 1 bits for floats.
#define JBM_4xF32_BITS_EXPONENT vdupq_n_u32 (JBM_F32_BITS_EXPONENT)
///< exponent bits for floats.
#define JBM_4xF32_BITS_MANTISSA vdupq_n_u32 (JBM_F32_BITS_MANTISSA)
///< mantissa bits for floats.
#define JBM_4xF32_BITS_SIGN vdupq_n_u32 (JBM_F32_BITS_SIGN)
///< sign bits for floats.
#define JBM_4xF32_CBRT2 vdupq_n_f32 (JBM_F32_CBRT2)
///< cbrt(2) for floats.
#define JBM_4xF32_CBRT4 vdupq_n_f32 (JBM_F32_CBRT4)
///< cbrt(4) for floats.

// double constants

#define JBM_2xF64_BIAS vdupq_n_u64 (JBM_F64_BIAS)
///< bias for doubles.
#define JBM_2xF64_BITS_1 vdupq_n_u64 (JBM_F64_BITS_1)
///< 1 bits for doubles.
#define JBM_2xF64_BITS_EXPONENT vdupq_n_u64 (JBM_F64_BITS_EXPONENT)
///< exponent bits for doubles.
#define JBM_2xF64_BITS_MANTISSA vdupq_n_u64 (JBM_F64_BITS_MANTISSA)
///< mantissa bits for doubles.
#define JBM_2xF64_BITS_SIGN vdupq_n_u64 (JBM_F64_BITS_SIGN)
///< sign bits for floats.
#define JBM_2xF64_CBRT2 vdupq_n_f64 (JBM_F64_CBRT2)
///< cbrt(2) for doubles.
#define JBM_2xF64_CBRT4 vdupq_n_f64 (JBM_F64_CBRT4)
///< cbrt(4) for doubles.

// Debug functions

/*
static inline void
print_bit32x4_t (FILE *file, const char *label, uint32x4_t x)
{
  unsigned int y[4] JB_ALIGNED;
  unsigned int i;
  vst1q_u32 (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_bit64x2_t (FILE *file, const char *label, uint64x2_t x)
{
  unsigned long long int y[2] JB_ALIGNED;
  unsigned int i;
  vst1q_u64 (y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_uint32x4_t (FILE *file, const char *label, uint32x4_t x)
{
  unsigned int y[4] JB_ALIGNED;
  unsigned int i;
  vst1q_u32 (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%u\n", label, i, y[i]);
}

static inline void
print_uint64x2_t (FILE *file, const char *label, uint64x2_t x)
{
  unsigned long long int y[2] JB_ALIGNED;
  unsigned int i;
  vst1q_u64 (y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_int32x4_t (FILE *file, const char *label, int32x4_t x)
{
  int y[4] JB_ALIGNED;
  unsigned int i;
  vst1q_s32 (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_int64x2_t (FILE *file, const char *label, int64x2_t x)
{
  long long int y[2] JB_ALIGNED;
  unsigned int i;
  vst1q_s64 (y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%lld\n", label, i, y[i]);
}

static inline void
print_float32x4_t (FILE *file, const char *label, float32x4_t x)
{
  float y[4] JB_ALIGNED;
  unsigned int i;
  vst1q_f32 (y, x);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_float64x2_t (FILE *file, const char *label, float64x2_t x)
{
  double y[2] JB_ALIGNED;
  unsigned int i;
  vst1q_f64 (y, x);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}
*/

/**
 * Function to do an integer division by 3 for 32 bits (int32x4_t).
 *
 * \return divided by 3 vector (int32x4_t).
 */
static inline int32x4_t
jbm_4xf32_div3 (int32x4_t x)    ///< int32x4_t vector.
{
  const int32x4_t magic = vdupq_n_s32 (0x55555556);
  int32x2_t even, odd;
  even = vshrn_n_s64 (vmull_s32 (vget_low_s32 (x), vget_low_s32 (magic)), 32);
  odd = vshrn_n_s64 (vmull_s32 (vget_high_s32 (x), vget_high_s32 (magic)), 32);
  return vcombine_s32 (even, odd);
}

#define jbm_4xf32_reduce_add vaddvq_f32
#define jbm_4xf32_reduce_max vmaxvq_f32
#define jbm_4xf32_reduce_min vminvq_f32

/**
 * Function to calculate the maximum and minimum reduction value of a
 * float32x4_t vector.
 */
static inline void
jbm_4xf32_reduce_maxmin (const float32x4_t x,   ///< float32x4_t vector.
                         float *max,
                         ///< pointer to the maximum value (float).
                         float *min)
                         ///< pointer to the minimum value (float).
{
  *max = vmaxvq_f32 (x);
  *min = vminvq_f32 (x);
}

/**
 * Function to calculate the additive inverse value of a float32x4_t vector.
 *
 * \return opposite value vector (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_opposite (const float32x4_t x)        ///< float32x4_t vector.
{
  return vnegq_f32 (x);
}

/**
 * Function to calculate the multiplicative inverse value of a float32x4_t
 * vector.
 *
 * \return reciprocal value vector (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_reciprocal (const float32x4_t x)      ///< float32x4_t vector.
{
  return vdivq_f32 (vdupq_n_f32 (1.f), x);
}

/**
 * Function to calculate the sign of a float32x4_t vector.
 *
 * \return sign vector (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_sign (const float32x4_t x)    ///< float32x4_t vector.
{
  JBM4xF32 y;
  y.x = x;
  y.i = vandq_u32 (y.i, JBM_4xF32_BITS_SIGN);
  y.i = vorrq_u32 (y.i, JBM_4xF32_BITS_1);
  return y.x;
}

/**
 * Function to calculate the absolute value of a float32x4_t vector.
 *
 * \return absolute value vector (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_abs (const float32x4_t x)     ///< float32x4_t vector.
{
  return vabsq_f32 (x);
}

/**
 * Function to copy the sign of a float32x4_t vector to another float32x4_t
 * vector.
 *
 * \return float32x4_t vector with magnitud of 1st vector and sign of 2nd
 * vector.
 */
static inline float32x4_t
jbm_4xf32_copysign (const float32x4_t x,
                    ///< float32x4_t vector to preserve magnitude.
                    const float32x4_t y)
                    ///< float32x4_t vector to preserve sign.
{
  JBM4xF32 mx, my;
  my.x = y;
  my.i = vandq_u32 (my.i, JBM_4xF32_BITS_SIGN);
  mx.x = jbm_4xf32_abs (x);
  mx.i = vorrq_u32 (mx.i, my.i);
  return mx.x;
}

/**
 * Function to calculate the hypot function (float32x4_t).
 *
 * \return function value vector (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_hypot (const float32x4_t x,   ///< 1st float32x4_t vector.
                 const float32x4_t y)   ///< 2nd float32x4_t vector.
{
  return vsqrtq_f32 (vmlaq_f32 (vmulq_f32 (x, x), y, y));
}

/**
 * Function to calculate the rest of a division (float32x4_t).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline float32x4_t
jbm_4xf32_mod (const float32x4_t x,     ///< dividend (float32x4_t).
               const float32x4_t d)     ///< divisor (float32x4_t).
{
  float32x4_t r;
  r = vrndmq_f32 (vdivq_f32 (x, d));
  return
    vbslq_f32 (vcgtq_f32 (jbm_4xf32_abs (r), vdupq_n_f32 (1.f / FLT_EPSILON)),
               vmulq_n_f32 (d, 0.5f), vfmsq_f32 (x, r, d));
}

/**
 * Function to implement the standard frexp function (float32x4_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline float32x4_t
jbm_4xf32_frexp (const float32x4_t x,   ///< float32x4_t vector.
                 int32x4_t *e)  ///< pointer to the extracted exponents vector.
{
  const uint32x4_t zi = vdupq_n_u32 (0);
  const uint32x4_t bias = JBM_4xF32_BIAS;
  const uint32x4_t sign_mask = JBM_4xF32_BITS_SIGN;
  const uint32x4_t mant_mask = JBM_4xF32_BITS_MANTISSA;
  JBM4xF32 y, z;
  uint32x4_t exp, is_z, is_sub, is_nan, is_finite;
  // y=abs(x)
  y.x = jbm_4xf32_abs (x);
  // masks
  is_z = vceqq_u32 (y.i, zi);
  is_nan = vcgtq_u32 (y.i, vdupq_n_u32 (JBM_F32_BITS_EXPONENT - 1));
  is_finite = vbicq_u32 (vdupq_n_u32 (0xffffffff), vorrq_u32 (is_z, is_nan));
  // extract exponent
  exp = vshrq_n_u32 (y.i, 23);
  // subnormals
  is_sub = vandq_u32 (is_finite, vceqq_u32 (exp, zi));
  y.x = vbslq_f32 (is_sub, vmulq_n_f32 (y.x, 0x1p23f), y.x);
  exp = vbslq_u32 (is_sub, vsubq_u32 (vshrq_n_u32 (y.i, 23), vdupq_n_u32 (23)),
                   exp);
  // exponent
  *e = vreinterpretq_s32_u32 (vbslq_u32 (is_finite, vsubq_u32 (exp, bias), zi));
  // build mantissa in [0.5,1)
  z.x = x;
  y.i = vorrq_u32 (vandq_u32 (z.i, sign_mask),
                   vorrq_u32 (vdupq_n_u32 (JBM_F32_BIAS << 23),
                              vandq_u32 (y.i, mant_mask)));
  return vbslq_f32 (is_finite, y.x, x);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (int32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_exp2n (int32x4_t e)   ///< exponent vector (int32x4_t).
{
  const int32x4_t v127 = vdupq_n_s32 (127);
  const int32x4_t v149 = vdupq_n_s32 (149);
  float32x4_t x;
  x = vbslq_f32 (vcgtq_s32 (e, vdupq_n_s32 (-127)),
                 vreinterpretq_f32_s32 (vshlq_n_s32 (vaddq_s32 (e, v127), 23)),
                 vreinterpretq_f32_s32 (vshlq_s32 (vdupq_n_s32 (1),
                                                   vaddq_s32 (v149, e))));
  x = vbslq_f32 (vcltq_s32 (e, vdupq_n_s32 (-150)), vdupq_n_f32 (0.f), x);
  return vbslq_f32 (vcgtq_s32 (e, v127), vdupq_n_f32 (INFINITY), x);
}

/**
 * Function to implement the standard ldexp function (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_ldexp (const float32x4_t x,   ///< float32x4_t vector.
                 int32x4_t e)   ///< exponent vector (int32x4_t).
{
  return vmulq_f32 (x, jbm_4xf32_exp2n (e));
}

/**
 * Function to check small float32x4_t vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline uint32x4_t
jbm_4xf32_small (const float32x4_t x)   ///< float64x2_t vector.
{
  return vcltq_f32 (jbm_4xf32_abs (x), vdupq_n_f32 (FLT_EPSILON));
}

/**
 * Function to calculate the float32x4_t vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin float32x4_t vector.
 */
static inline float32x4_t
jbm_4xf32_modmin (const float32x4_t a,  ///< 1st float64x2_t vector.
                  const float32x4_t b)  ///< 2nd float64x2_t vector.
{
  float32x4_t aa, ab, y, z;
  z = vdupq_n_f32 (0.f);
  ab = vmulq_f32 (a, b);
  y = vbslq_f32 (vclezq_f32 (ab), z, a);
  aa = jbm_4xf32_abs (y);
  ab = jbm_4xf32_abs (b);
  return vbslq_f32 (vcgtq_f32 (aa, ab), b, y);
}

/**
 * Function to interchange 2 float32x4_t vectors.
 */
static inline void
jbm_change_4xf32 (float32x4_t *restrict a,
///< 1st float32x4_t vector pointer.
                  float32x4_t *restrict b)
///< 2nd float32x4_t vector pointer.
{
  float32x4_t c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a float32x4_t vector.
 *
 * \return float32x4_t double.
 */
static inline float32x4_t
jbm_4xf32_dbl (const float32x4_t x)     ///< float64x2_t vector.
{
  return vaddq_f32 (x, x);
}

/**
 * Function to calculate the square of the components of a float32x4_t vector.
 *
 * \return float32x4_t vector square.
 */
static inline float32x4_t
jbm_4xf32_sqr (const float32x4_t x)     ///< float32x4_t vector.
{
  return vmulq_f32 (x, x);
}

/**
 * Function to perform an extrapolation between 2 float32x4_t vectors of 2D points.
 *
 * \return float32x4_t vector of y-coordinates of the extrapolated points.
 */
static inline float32x4_t
jbm_4xf32_extrapolate (const float32x4_t x,
///< float32x4_t vector of x-coordinates of the extrapolated points.
                       const float32x4_t x1,
///< float32x4_t vector of x-coordinates of the 1st points.
                       const float32x4_t x2,
///< float32x4_t vector of x-coordinates of the 2nd points.
                       const float32x4_t y1,
///< float32x4_t vector of y-coordinates of the 1st points.
                       const float32x4_t y2)
///< float32x4_t vector of y-coordinates of the 2nd points.
{
  return vmlaq_f32 (y1, vsubq_f32 (x, x1), vdivq_f32 (vsubq_f32 (y2, y1),
                                                      vsubq_f32 (x2, x1)));
}

/**
 * Function to perform an interpolation between 2 float32x4_t vectors of 2D
 * points.
 *
 * \return float32x4_t vector of y-coordinates of the interpolated points.
 */
static inline float32x4_t
jbm_4xf32_interpolate (const float32x4_t x,
///< float32x4_t vector of x-coordinates of the interpolated points.
                       const float32x4_t x1,
///< float32x4_t vector of x-coordinates of the 1st points.
                       const float32x4_t x2,
///< float32x4_t vector of x-coordinates of the 2nd points.
                       const float32x4_t y1,
///< float32x4_t vector of y-coordinates of the 1st points.
                       const float32x4_t y2)
///< float32x4_t vector of y-coordinates of the 2nd points.
{
  float32x4_t k;
  k = jbm_4xf32_extrapolate (x, x1, x2, y1, y2);
  k = vbslq_f32 (vcgtq_f32 (x, x1), k, y1);
  return vbslq_f32 (vcltq_f32 (x, x2), k, y2);
}

/**
 * Function to calculate the length of a float32x4_t vector of 2D segments.
 *
 * \return float32x4_t vector of segment lengths.
 */
static inline float32x4_t
jbm_4xf32_v2_length (const float32x4_t x1,
///< float32x4_t vector of x-coordinates of the 1st points defining the segment.
                     const float32x4_t y1,
///< float32x4_t vector of y-coordinates of the 1st points defining the segment.
                     const float32x4_t x2,
///< float32x4_t vector of x-coordinates of the 2nd points defining the segment.
                     const float32x4_t y2)
///< float32x4_t vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_4xf32_hypot (vsubq_f32 (x2, x1), vsubq_f32 (y2, y1));
}

/**
 * Function to calculate the length of a float32x4_t vector of 3D segments.
 *
 * \return float32x4_t vector of segment lengths.
 */
static inline float32x4_t
jbm_4xf32_v3_length (const float32x4_t x1,
///< float32x4_t vector of x-coordinates of the 1st points defining the
///< segments.
                     const float32x4_t y1,
///< float32x4_t vector of y-coordinates of the 1st points defining the
///< segments.
                     const float32x4_t z1,
///< float32x4_t vector of z-coordinates of the 1st points defining the
///< segments.
                     const float32x4_t x2,
///< float32x4_t vector of x-coordinates of the 2nd points defining the
///< segments.
                     const float32x4_t y2,
///< float32x4_t vector of y-coordinates of the 2nd points defining the
///< segments.
                     const float32x4_t z2)
///< float32x4_t vector of z-coordinates of the 2nd points defining the
///< segments.
{
  float32x4_t dx, dy, dz;
  dx = jbm_4xf32_sqr (vsubq_f32 (x2, x1));
  dy = vsubq_f32 (y2, y1);
  dy = vmlaq_f32 (dx, dy, dy);
  dz = vsubq_f32 (z2, z1);
  return vsqrtq_f32 (vmlaq_f32 (dy, dz, dz));
}

/**
 * Function to calculate a 1st order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, vdupq_n_f32 (p[1]));
}

/**
 * Function to calculate a 2nd order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_1 (x, p + 1));
}

/**
 * Function to calculate a 3rd order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_2 (x, p + 1));
}

/**
 * Function to calculate a 4th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_4 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_3 (x, p + 1));
}

/**
 * Function to calculate a 5th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_5 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_4 (x, p + 1));
}

/**
 * Function to calculate a 6th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_6 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_5 (x, p + 1));
}

/**
 * Function to calculate a 7th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_7 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_6 (x, p + 1));
}

/**
 * Function to calculate a 8th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_8 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_7 (x, p + 1));
}

/**
 * Function to calculate a 9th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_9 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_8 (x, p + 1));
}

/**
 * Function to calculate a 10th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_10 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_9 (x, p + 1));
}

/**
 * Function to calculate a 11th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_11 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_10 (x, p + 1));
}

/**
 * Function to calculate a 12th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_12 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_11 (x, p + 1));
}

/**
 * Function to calculate a 13th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_13 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_12 (x, p + 1));
}

/**
 * Function to calculate a 14th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_14 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_13 (x, p + 1));
}

/**
 * Function to calculate a 15th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_15 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_14 (x, p + 1));
}

/**
 * Function to calculate a 16th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_16 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_15 (x, p + 1));
}

/**
 * Function to calculate a 17th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_17 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_16 (x, p + 1));
}

/**
 * Function to calculate a 18th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_18 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_17 (x, p + 1));
}

/**
 * Function to calculate a 19th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_19 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_18 (x, p + 1));
}

/**
 * Function to calculate a 20th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_20 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_19 (x, p + 1));
}

/**
 * Function to calculate a 21th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_21 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_20 (x, p + 1));
}

/**
 * Function to calculate a 22th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_22 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_21 (x, p + 1));
}

/**
 * Function to calculate a 23th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_23 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_22 (x, p + 1));
}

/**
 * Function to calculate a 24th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_24 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_23 (x, p + 1));
}

/**
 * Function to calculate a 25th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_25 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_24 (x, p + 1));
}

/**
 * Function to calculate a 26th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_26 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_25 (x, p + 1));
}

/**
 * Function to calculate a 27th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_27 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_26 (x, p + 1));
}

/**
 * Function to calculate a 28th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_28 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_27 (x, p + 1));
}

/**
 * Function to calculate a 29th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_4xf32_polynomial_29 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_4xf32_polynomial_28 (x, p + 1));
}

/**
 * Function to calculate a 0th+1st order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_1_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[1])));
}

/**
 * Function to calculate a 0th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_2_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 1)));
}

/**
 * Function to calculate a 1st+1st order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_2_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[2])));
}

/**
 * Function to calculate a 0th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_3_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 1)));
}

/**
 * Function to calculate a 1st+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_3_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 2)));
}

/**
 * Function to calculate a 1st+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_3_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[3])));
}

/**
 * Function to calculate a 0th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_4_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 1)));
}

/**
 * Function to calculate a 1st+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_4_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_4_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 3)));
}

/**
 * Function to calculate a 1st+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_4_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[4])));
}

/**
 * Function to calculate a 0th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_5_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 1)));
}

/**
 * Function to calculate a 1st+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_5_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_5_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_5_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 4)));
}

/**
 * Function to calculate a 1st+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_5_4 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[5])));
}

/**
 * Function to calculate a 0th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_6_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 1)));
}

/**
 * Function to calculate a 1st+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_6_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_6_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_6_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 4)));
}

/**
 * Function to calculate a 4th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_6_4 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 5)));
}

/**
 * Function to calculate a 1st+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_6_5 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[6])));
}

/**
 * Function to calculate a 0th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 1)));
}

/**
 * Function to calculate a 1st+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 4)));
}

/**
 * Function to calculate a 4th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_4 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 5)));
}

/**
 * Function to calculate a 5th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_5 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 6)));
}

/**
 * Function to calculate a 1st+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_7_6 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[7])));
}

/**
 * Function to calculate a 0th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 1)));
}

/**
 * Function to calculate a 1st+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 4)));
}

/**
 * Function to calculate a 4th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_4 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 5)));
}

/**
 * Function to calculate a 5th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_5 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 6)));
}

/**
 * Function to calculate a 6th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_6 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 7)));
}

/**
 * Function to calculate a 1st+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_8_7 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[8])));
}

/**
 * Function to calculate a 0th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_0 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 1)));
}

/**
 * Function to calculate a 1st+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_1 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_2 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_3 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 4)));
}

/**
 * Function to calculate a 4th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_4 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 5)));
}

/**
 * Function to calculate a 5th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_5 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 6)));
}

/**
 * Function to calculate a 6th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_6 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 7)));
}

/**
 * Function to calculate a 7th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_7 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 8)));
}

/**
 * Function to calculate a 1st+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_9_8 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[9])));
}

/**
 * Function to calculate a 0th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 1)));
}

/**
 * Function to calculate a 1st+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 4)));
}

/**
 * Function to calculate a 4th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 5)));
}

/**
 * Function to calculate a 5th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 6)));
}

/**
 * Function to calculate a 6th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 7)));
}

/**
 * Function to calculate a 7th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 8)));
}

/**
 * Function to calculate a 8th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 9)));
}

/**
 * Function to calculate a 1st+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_10_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[10])));
}

/**
 * Function to calculate a 0th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 1)));
}

/**
 * Function to calculate a 1st+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 4)));
}

/**
 * Function to calculate a 4th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 5)));
}

/**
 * Function to calculate a 5th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 6)));
}

/**
 * Function to calculate a 6th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 7)));
}

/**
 * Function to calculate a 7th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 8)));
}

/**
 * Function to calculate a 8th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 9)));
}

/**
 * Function to calculate a 9th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 10)));
}

/**
 * Function to calculate a 1st+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_11_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[11])));
}

/**
 * Function to calculate a 0th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 1)));
}

/**
 * Function to calculate a 1st+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 4)));
}

/**
 * Function to calculate a 4th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 5)));
}

/**
 * Function to calculate a 5th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 6)));
}

/**
 * Function to calculate a 6th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 7)));
}

/**
 * Function to calculate a 7th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 8)));
}

/**
 * Function to calculate a 8th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 9)));
}

/**
 * Function to calculate a 9th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 10)));
}

/**
 * Function to calculate a 10th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 11)));
}

/**
 * Function to calculate a 1st+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_12_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[12])));
}

/**
 * Function to calculate a 0th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 1)));
}

/**
 * Function to calculate a 1st+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 4)));
}

/**
 * Function to calculate a 4th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 5)));
}

/**
 * Function to calculate a 5th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 6)));
}

/**
 * Function to calculate a 6th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 7)));
}

/**
 * Function to calculate a 7th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 8)));
}

/**
 * Function to calculate a 8th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 9)));
}

/**
 * Function to calculate a 9th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 10)));
}

/**
 * Function to calculate a 10th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 11)));
}

/**
 * Function to calculate a 11th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 12)));
}

/**
 * Function to calculate a 1st+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_13_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[13])));
}

/**
 * Function to calculate a 0th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 1)));
}

/**
 * Function to calculate a 1st+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 4)));
}

/**
 * Function to calculate a 4th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 5)));
}

/**
 * Function to calculate a 5th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 6)));
}

/**
 * Function to calculate a 6th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 7)));
}

/**
 * Function to calculate a 7th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 8)));
}

/**
 * Function to calculate a 8th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 9)));
}

/**
 * Function to calculate a 9th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 10)));
}

/**
 * Function to calculate a 10th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 11)));
}

/**
 * Function to calculate a 11th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 12)));
}

/**
 * Function to calculate a 12th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 13)));
}

/**
 * Function to calculate a 1st+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_14_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[14])));
}

/**
 * Function to calculate a 0th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 1)));
}

/**
 * Function to calculate a 1st+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 4)));
}

/**
 * Function to calculate a 4th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 5)));
}

/**
 * Function to calculate a 5th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 6)));
}

/**
 * Function to calculate a 6th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 7)));
}

/**
 * Function to calculate a 7th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 8)));
}

/**
 * Function to calculate a 8th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 9)));
}

/**
 * Function to calculate a 9th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 10)));
}

/**
 * Function to calculate a 10th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 11)));
}

/**
 * Function to calculate a 11th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 12)));
}

/**
 * Function to calculate a 12th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 13)));
}

/**
 * Function to calculate a 13th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 14)));
}

/**
 * Function to calculate a 1st+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_15_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[15])));
}

/**
 * Function to calculate a 0th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 1)));
}

/**
 * Function to calculate a 1st+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 4)));
}

/**
 * Function to calculate a 4th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 5)));
}

/**
 * Function to calculate a 5th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 6)));
}

/**
 * Function to calculate a 6th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 7)));
}

/**
 * Function to calculate a 7th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 8)));
}

/**
 * Function to calculate a 8th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 9)));
}

/**
 * Function to calculate a 9th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 10)));
}

/**
 * Function to calculate a 10th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 11)));
}

/**
 * Function to calculate a 11th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 12)));
}

/**
 * Function to calculate a 12th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 13)));
}

/**
 * Function to calculate a 13th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 14)));
}

/**
 * Function to calculate a 14th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 15)));
}

/**
 * Function to calculate a 1st+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_16_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[16])));
}

/**
 * Function to calculate a 0th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 1)));
}

/**
 * Function to calculate a 1st+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 4)));
}

/**
 * Function to calculate a 4th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 5)));
}

/**
 * Function to calculate a 5th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 6)));
}

/**
 * Function to calculate a 6th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 7)));
}

/**
 * Function to calculate a 7th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 8)));
}

/**
 * Function to calculate a 8th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 9)));
}

/**
 * Function to calculate a 9th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 10)));
}

/**
 * Function to calculate a 10th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 11)));
}

/**
 * Function to calculate a 11th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 12)));
}

/**
 * Function to calculate a 12th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 13)));
}

/**
 * Function to calculate a 13th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 14)));
}

/**
 * Function to calculate a 14th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 15)));
}

/**
 * Function to calculate a 15th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 16)));
}

/**
 * Function to calculate a 1st+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_17_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[17])));
}

/**
 * Function to calculate a 0th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 1)));
}

/**
 * Function to calculate a 1st+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 4)));
}

/**
 * Function to calculate a 4th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 5)));
}

/**
 * Function to calculate a 5th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 6)));
}

/**
 * Function to calculate a 6th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 7)));
}

/**
 * Function to calculate a 7th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 8)));
}

/**
 * Function to calculate a 8th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 9)));
}

/**
 * Function to calculate a 9th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 10)));
}

/**
 * Function to calculate a 10th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 11)));
}

/**
 * Function to calculate a 11th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 12)));
}

/**
 * Function to calculate a 12th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 13)));
}

/**
 * Function to calculate a 13th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 14)));
}

/**
 * Function to calculate a 14th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 15)));
}

/**
 * Function to calculate a 15th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 16)));
}

/**
 * Function to calculate a 16th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 17)));
}

/**
 * Function to calculate a 1st+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_18_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[18])));
}

/**
 * Function to calculate a 0th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 1)));
}

/**
 * Function to calculate a 1st+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 4)));
}

/**
 * Function to calculate a 4th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 5)));
}

/**
 * Function to calculate a 5th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 6)));
}

/**
 * Function to calculate a 6th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 7)));
}

/**
 * Function to calculate a 7th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 8)));
}

/**
 * Function to calculate a 8th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 9)));
}

/**
 * Function to calculate a 9th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 10)));
}

/**
 * Function to calculate a 10th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 11)));
}

/**
 * Function to calculate a 11th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 12)));
}

/**
 * Function to calculate a 12th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 13)));
}

/**
 * Function to calculate a 13th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 14)));
}

/**
 * Function to calculate a 14th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 15)));
}

/**
 * Function to calculate a 15th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 16)));
}

/**
 * Function to calculate a 16th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 17)));
}

/**
 * Function to calculate a 17th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 18)));
}

/**
 * Function to calculate a 1st+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_19_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[19])));
}

/**
 * Function to calculate a 0th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 1)));
}

/**
 * Function to calculate a 1st+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 4)));
}

/**
 * Function to calculate a 4th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 5)));
}

/**
 * Function to calculate a 5th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 6)));
}

/**
 * Function to calculate a 6th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 7)));
}

/**
 * Function to calculate a 7th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 8)));
}

/**
 * Function to calculate a 8th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 9)));
}

/**
 * Function to calculate a 9th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 10)));
}

/**
 * Function to calculate a 10th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 11)));
}

/**
 * Function to calculate a 11th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 12)));
}

/**
 * Function to calculate a 12th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 13)));
}

/**
 * Function to calculate a 13th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 14)));
}

/**
 * Function to calculate a 14th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 15)));
}

/**
 * Function to calculate a 15th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 16)));
}

/**
 * Function to calculate a 16th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 17)));
}

/**
 * Function to calculate a 17th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 18)));
}

/**
 * Function to calculate a 18th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 19)));
}

/**
 * Function to calculate a 1st+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_20_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[20])));
}

/**
 * Function to calculate a 0th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 1)));
}

/**
 * Function to calculate a 1st+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 4)));
}

/**
 * Function to calculate a 4th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 5)));
}

/**
 * Function to calculate a 5th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 6)));
}

/**
 * Function to calculate a 6th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 7)));
}

/**
 * Function to calculate a 7th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 8)));
}

/**
 * Function to calculate a 8th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 9)));
}

/**
 * Function to calculate a 9th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 10)));
}

/**
 * Function to calculate a 10th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 11)));
}

/**
 * Function to calculate a 11th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 12)));
}

/**
 * Function to calculate a 12th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 13)));
}

/**
 * Function to calculate a 13th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 14)));
}

/**
 * Function to calculate a 14th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 15)));
}

/**
 * Function to calculate a 15th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 16)));
}

/**
 * Function to calculate a 16th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 17)));
}

/**
 * Function to calculate a 17th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 18)));
}

/**
 * Function to calculate a 18th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 19)));
}

/**
 * Function to calculate a 19th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 20)));
}

/**
 * Function to calculate a 1st+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_21_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[21])));
}

/**
 * Function to calculate a 0th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 1)));
}

/**
 * Function to calculate a 1st+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 4)));
}

/**
 * Function to calculate a 4th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 5)));
}

/**
 * Function to calculate a 5th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 6)));
}

/**
 * Function to calculate a 6th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 7)));
}

/**
 * Function to calculate a 7th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 8)));
}

/**
 * Function to calculate a 8th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 9)));
}

/**
 * Function to calculate a 9th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 10)));
}

/**
 * Function to calculate a 10th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 11)));
}

/**
 * Function to calculate a 11th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 12)));
}

/**
 * Function to calculate a 12th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 13)));
}

/**
 * Function to calculate a 13th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 14)));
}

/**
 * Function to calculate a 14th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 15)));
}

/**
 * Function to calculate a 15th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 16)));
}

/**
 * Function to calculate a 16th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 17)));
}

/**
 * Function to calculate a 17th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 18)));
}

/**
 * Function to calculate a 18th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 19)));
}

/**
 * Function to calculate a 19th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 20)));
}

/**
 * Function to calculate a 20th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 21)));
}

/**
 * Function to calculate a 1st+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_22_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[22])));
}

/**
 * Function to calculate a 0th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 1)));
}

/**
 * Function to calculate a 1st+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 4)));
}

/**
 * Function to calculate a 4th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 5)));
}

/**
 * Function to calculate a 5th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 6)));
}

/**
 * Function to calculate a 6th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 7)));
}

/**
 * Function to calculate a 7th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 8)));
}

/**
 * Function to calculate a 8th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 9)));
}

/**
 * Function to calculate a 9th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 10)));
}

/**
 * Function to calculate a 10th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 11)));
}

/**
 * Function to calculate a 11th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 12)));
}

/**
 * Function to calculate a 12th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 13)));
}

/**
 * Function to calculate a 13th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 14)));
}

/**
 * Function to calculate a 14th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 15)));
}

/**
 * Function to calculate a 15th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 16)));
}

/**
 * Function to calculate a 16th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 17)));
}

/**
 * Function to calculate a 17th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 18)));
}

/**
 * Function to calculate a 18th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 19)));
}

/**
 * Function to calculate a 19th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 20)));
}

/**
 * Function to calculate a 20th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 21)));
}

/**
 * Function to calculate a 21th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 22)));
}

/**
 * Function to calculate a 1st+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_23_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[23])));
}

/**
 * Function to calculate a 0th+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_23 (x, p + 1)));
}

/**
 * Function to calculate a 1st+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 4)));
}

/**
 * Function to calculate a 4th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 5)));
}

/**
 * Function to calculate a 5th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 6)));
}

/**
 * Function to calculate a 6th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 7)));
}

/**
 * Function to calculate a 7th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 8)));
}

/**
 * Function to calculate a 8th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 9)));
}

/**
 * Function to calculate a 9th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 10)));
}

/**
 * Function to calculate a 10th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 11)));
}

/**
 * Function to calculate a 11th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 12)));
}

/**
 * Function to calculate a 12th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 13)));
}

/**
 * Function to calculate a 13th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 14)));
}

/**
 * Function to calculate a 14th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 15)));
}

/**
 * Function to calculate a 15th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 16)));
}

/**
 * Function to calculate a 16th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 17)));
}

/**
 * Function to calculate a 17th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 18)));
}

/**
 * Function to calculate a 18th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 19)));
}

/**
 * Function to calculate a 19th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 20)));
}

/**
 * Function to calculate a 20th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 21)));
}

/**
 * Function to calculate a 21th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 22)));
}

/**
 * Function to calculate a 22th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 23)));
}

/**
 * Function to calculate a 1st+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_24_23 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_23 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[24])));
}

/**
 * Function to calculate a 0th+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_24 (x, p + 1)));
}

/**
 * Function to calculate a 1st+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_23 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 4)));
}

/**
 * Function to calculate a 4th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 5)));
}

/**
 * Function to calculate a 5th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 6)));
}

/**
 * Function to calculate a 6th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 7)));
}

/**
 * Function to calculate a 7th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 8)));
}

/**
 * Function to calculate a 8th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 9)));
}

/**
 * Function to calculate a 9th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 10)));
}

/**
 * Function to calculate a 10th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 11)));
}

/**
 * Function to calculate a 11th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 12)));
}

/**
 * Function to calculate a 12th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 13)));
}

/**
 * Function to calculate a 13th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 14)));
}

/**
 * Function to calculate a 14th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 15)));
}

/**
 * Function to calculate a 15th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 16)));
}

/**
 * Function to calculate a 16th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 17)));
}

/**
 * Function to calculate a 17th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 18)));
}

/**
 * Function to calculate a 18th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 19)));
}

/**
 * Function to calculate a 19th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 20)));
}

/**
 * Function to calculate a 20th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 21)));
}

/**
 * Function to calculate a 21th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 22)));
}

/**
 * Function to calculate a 22th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 23)));
}

/**
 * Function to calculate a 23th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_23 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_23 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 24)));
}

/**
 * Function to calculate a 1st+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_25_24 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_24 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[25])));
}

/**
 * Function to calculate a 0th+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_25 (x, p + 1)));
}

/**
 * Function to calculate a 1st+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_24 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_23 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 4)));
}

/**
 * Function to calculate a 4th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 5)));
}

/**
 * Function to calculate a 5th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 6)));
}

/**
 * Function to calculate a 6th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 7)));
}

/**
 * Function to calculate a 7th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 8)));
}

/**
 * Function to calculate a 8th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 9)));
}

/**
 * Function to calculate a 9th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 10)));
}

/**
 * Function to calculate a 10th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 11)));
}

/**
 * Function to calculate a 11th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 12)));
}

/**
 * Function to calculate a 12th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 13)));
}

/**
 * Function to calculate a 13th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 14)));
}

/**
 * Function to calculate a 14th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 15)));
}

/**
 * Function to calculate a 15th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 16)));
}

/**
 * Function to calculate a 16th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 17)));
}

/**
 * Function to calculate a 17th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 18)));
}

/**
 * Function to calculate a 18th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 19)));
}

/**
 * Function to calculate a 19th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 20)));
}

/**
 * Function to calculate a 20th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 21)));
}

/**
 * Function to calculate a 21th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 22)));
}

/**
 * Function to calculate a 22th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 23)));
}

/**
 * Function to calculate a 23th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_23 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_23 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 24)));
}

/**
 * Function to calculate a 24th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_24 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_24 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 25)));
}

/**
 * Function to calculate a 1st+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_26_25 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_25 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[26])));
}

/**
 * Function to calculate a 0th+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_26 (x, p + 1)));
}

/**
 * Function to calculate a 1st+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_25 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_24 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_23 (x, p + 4)));
}

/**
 * Function to calculate a 4th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 5)));
}

/**
 * Function to calculate a 5th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 6)));
}

/**
 * Function to calculate a 6th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 7)));
}

/**
 * Function to calculate a 7th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 8)));
}

/**
 * Function to calculate a 8th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 9)));
}

/**
 * Function to calculate a 9th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 10)));
}

/**
 * Function to calculate a 10th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 11)));
}

/**
 * Function to calculate a 11th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 12)));
}

/**
 * Function to calculate a 12th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 13)));
}

/**
 * Function to calculate a 13th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 14)));
}

/**
 * Function to calculate a 14th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 15)));
}

/**
 * Function to calculate a 15th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 16)));
}

/**
 * Function to calculate a 16th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 17)));
}

/**
 * Function to calculate a 17th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 18)));
}

/**
 * Function to calculate a 18th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 19)));
}

/**
 * Function to calculate a 19th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 20)));
}

/**
 * Function to calculate a 20th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 21)));
}

/**
 * Function to calculate a 21th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 22)));
}

/**
 * Function to calculate a 22th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 23)));
}

/**
 * Function to calculate a 23th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_23 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_23 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 24)));
}

/**
 * Function to calculate a 24th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_24 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_24 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 25)));
}

/**
 * Function to calculate a 25th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_25 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_25 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 26)));
}

/**
 * Function to calculate a 1st+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_27_26 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_26 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[27])));
}

/**
 * Function to calculate a 0th+28th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_27 (x, p + 1)));
}

/**
 * Function to calculate a 1st+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_26 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_25 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_24 (x, p + 4)));
}

/**
 * Function to calculate a 4th+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_23 (x, p + 5)));
}

/**
 * Function to calculate a 5th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 6)));
}

/**
 * Function to calculate a 6th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 7)));
}

/**
 * Function to calculate a 7th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 8)));
}

/**
 * Function to calculate a 8th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 9)));
}

/**
 * Function to calculate a 9th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 10)));
}

/**
 * Function to calculate a 10th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 11)));
}

/**
 * Function to calculate a 11th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 12)));
}

/**
 * Function to calculate a 12th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 13)));
}

/**
 * Function to calculate a 13th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 14)));
}

/**
 * Function to calculate a 14th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 15)));
}

/**
 * Function to calculate a 15th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 16)));
}

/**
 * Function to calculate a 16th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 17)));
}

/**
 * Function to calculate a 17th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 18)));
}

/**
 * Function to calculate a 18th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 19)));
}

/**
 * Function to calculate a 19th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 20)));
}

/**
 * Function to calculate a 20th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 21)));
}

/**
 * Function to calculate a 21th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 22)));
}

/**
 * Function to calculate a 22th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 23)));
}

/**
 * Function to calculate a 23th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_23 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_23 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 24)));
}

/**
 * Function to calculate a 24th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_24 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_24 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 25)));
}

/**
 * Function to calculate a 25th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_25 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_25 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 26)));
}

/**
 * Function to calculate a 26th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_26 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_26 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 27)));
}

/**
 * Function to calculate a 1st+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_28_27 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_27 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[28])));
}

/**
 * Function to calculate a 0th+29th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_0 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_28 (x, p + 1)));
}

/**
 * Function to calculate a 1st+28th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_1 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_1 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_27 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_2 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_2 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_26 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_3 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_3 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_25 (x, p + 4)));
}

/**
 * Function to calculate a 4th+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_4 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_4 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_24 (x, p + 5)));
}

/**
 * Function to calculate a 5th+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_5 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_5 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_23 (x, p + 6)));
}

/**
 * Function to calculate a 6th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_6 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_6 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_22 (x, p + 7)));
}

/**
 * Function to calculate a 7th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_7 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_7 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_21 (x, p + 8)));
}

/**
 * Function to calculate a 8th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_8 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_8 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_20 (x, p + 9)));
}

/**
 * Function to calculate a 9th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_9 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_9 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_19 (x, p + 10)));
}

/**
 * Function to calculate a 10th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_10 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_10 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_18 (x, p + 11)));
}

/**
 * Function to calculate a 11th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_11 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_11 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_17 (x, p + 12)));
}

/**
 * Function to calculate a 12th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_12 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_12 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_16 (x, p + 13)));
}

/**
 * Function to calculate a 13th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_13 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_13 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_15 (x, p + 14)));
}

/**
 * Function to calculate a 14th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_14 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_14 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_14 (x, p + 15)));
}

/**
 * Function to calculate a 15th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_15 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_15 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_13 (x, p + 16)));
}

/**
 * Function to calculate a 16th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_16 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_16 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_12 (x, p + 17)));
}

/**
 * Function to calculate a 17th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_17 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_17 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_11 (x, p + 18)));
}

/**
 * Function to calculate a 18th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_18 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_18 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_10 (x, p + 19)));
}

/**
 * Function to calculate a 19th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_19 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_19 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_9 (x, p + 20)));
}

/**
 * Function to calculate a 20th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_20 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_20 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_8 (x, p + 21)));
}

/**
 * Function to calculate a 21th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_21 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_21 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_7 (x, p + 22)));
}

/**
 * Function to calculate a 22th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_22 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_22 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_6 (x, p + 23)));
}

/**
 * Function to calculate a 23th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_23 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_23 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_5 (x, p + 24)));
}

/**
 * Function to calculate a 24th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_24 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_24 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_4 (x, p + 25)));
}

/**
 * Function to calculate a 25th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_25 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_25 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_3 (x, p + 26)));
}

/**
 * Function to calculate a 26th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_26 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_26 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_2 (x, p + 27)));
}

/**
 * Function to calculate a 27th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_27 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_27 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_4xf32_polynomial_1 (x, p + 28)));
}

/**
 * Function to calculate a 1st+28th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_4xf32_rational_29_28 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_4xf32_polynomial_28 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[29])));
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_cbrtwc (const float32x4_t x)
                  ///< float32x4_t vector \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_4xf32_rational_5_3 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_cbrtwc_4xdbl
 * function (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_cbrt (const float32x4_t x)    ///< float32x4_t vector.
{
  const float32x4_t cbrt2 = JBM_4xF32_CBRT2;
  const float32x4_t cbrt4 = JBM_4xF32_CBRT4;
  const int32x4_t v3 = vdupq_n_s32 (3);
  const int32x4_t v2 = vdupq_n_s32 (2);
  const int32x4_t v1 = vdupq_n_s32 (1);
  float32x4_t y;
  int32x4_t e, e3, r, n;
  y = jbm_4xf32_frexp (jbm_4xf32_abs (x), &e);
  e3 = jbm_4xf32_div3 (e);
  r = vsubq_s32 (e, vmulq_s32 (e3, v3));
  n = vshrq_s32 (r, 31);
  r = vaddq_s32 (r, vandq_s32 (n, v3));
  e3 = vsubq_s32 (e3, vandq_s32 (n, v1));
  y = jbm_4xf32_ldexp (jbm_4xf32_cbrtwc (y), e3);
  y = vbslq_f32 (vceqq_s32 (r, v1), vmulq_f32 (y, cbrt2), y);
  y = vbslq_f32 (vceqq_s32 (r, v2), vmulq_f32 (y, cbrt4), y);
  return jbm_4xf32_copysign (y, x);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (float32x4_t).
 *
 * \return function value.
 */
static inline float32x4_t
jbm_4xf32_exp2wc (const float32x4_t x)
                  ///< float32x4_t vector \f$\in[\frac12,1]\f$.
{
  return jbm_4xf32_polynomial_5 (x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_4xf32 and
 * jbm_4xf32_exp2n functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_exp2 (const float32x4_t x)    ///< float32x4_t vector.
{
  float32x4_t y, f;
  y = vrndmq_f32 (x);
  f = vsubq_f32 (x, y);
  y = jbm_4xf32_exp2n (vcvtq_s32_f32 (y));
  return vmulq_f32 (y, jbm_4xf32_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_4xf32_exp2 function
 * (float32x4_t).
 *
 * \return function value.
 */
static inline float32x4_t
jbm_4xf32_exp (const float32x4_t x)     ///< float32x4_t vector.
{
  return jbm_4xf32_exp2 (vmulq_f32 (x, vdupq_n_f32 (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_4xf32_exp2
 * function (float32x4_t).
 *
 * \return function value.
 */
static inline float32x4_t
jbm_4xf32_exp10 (const float32x4_t x)   ///< float32x4_t vector.
{
  return jbm_4xf32_exp2 (vmulq_f32 (x, vdupq_n_f32 (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_expm1wc (const float32x4_t x)
///< float32x4_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  float32x4_t x2;
  x2 = jbm_4xf32_sqr (x);
  x2 = vmlaq_f32 (vdupq_n_f32 (b2), x2, vdupq_n_f32 (b4));
  x2 = vmlaq_f32 (vdupq_n_f32 (b1), x2, x);
  x2 = vmlaq_f32 (vdupq_n_f32 (1.f), x2, x);
  return vmulq_f32 (x, vdivq_f32 (vdupq_n_f32 (a1), x2));
}

/**
 * Function to calculate the function expm1(x) using the jbm_4xf32_expm1wc and
 * jbm_4xf32_exp functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_expm1 (const float32x4_t x)   ///< float32x4_t vector.
{
  return vbslq_f32 (vcltq_f32 (jbm_4xf32_abs (x),
                               vdupq_n_f32 (M_LN2f / 2.f)),
                    jbm_4xf32_expm1wc (x),
                    vsubq_f32 (jbm_4xf32_exp (x), vdupq_n_f32 (1.f)));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_log2wc (const float32x4_t x)
///< float32x4_t vector \f$\in[0.5,1]\f$.
{
  return jbm_4xf32_rational_5_2 (x, K_LOG2WC_F32);
}

/**
 * Function to calculate the function log_2(x) using jbm_4xf32_log2wc and
 * jbm_4xf32_frexp (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_log2 (const float32x4_t x)    ///< float32x4_t vector.
{
  const float32x4_t z = vdupq_n_f32 (0.f);
  float32x4_t y;
  int32x4_t e;
  uint32x4_t m;
  y = jbm_4xf32_frexp (x, &e);
  m = vcltq_f32 (y, vdupq_n_f32 (M_SQRT1_2f));
  y = vbslq_f32 (m, vaddq_f32 (y, y), y);
  e = vbslq_s32 (m, vsubq_s32 (e, vdupq_n_s32 (1)), e);
  y = vaddq_f32 (jbm_4xf32_log2wc (vsubq_f32 (y, vdupq_n_f32 (1.f))),
                 vcvtq_f32_s32 (e));
  y = vbslq_f32 (vceqq_f32 (x, z), vdupq_n_f32 (-INFINITY), y);
  y = vbslq_f32 (vcltq_f32 (x, z), vdupq_n_f32 (NAN), y);
  y = vbslq_f32 (vceqq_f32 (x, vdupq_n_f32 (-INFINITY)), x, y);
  return vbslq_f32 (vceqq_f32 (x, x), y, x);
}

/**
 * Function to calculate the function log(x) using jbm_4xf32_log2 (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_log (const float32x4_t x)     ///< float32x4_t vector.
{
  return vmulq_f32 (jbm_4xf32_log2 (x), vdupq_n_f32 (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_4xf32_log2.
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_log10 (const float32x4_t x)   ///< float32x4_t vector.
{
  return vmulq_f32 (jbm_4xf32_log2 (x), vdupq_n_f32 (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (float32x4_t).
 *
 * \return function value (float32x4_t) (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_pown (const float32x4_t x,    ///< float32x4_t vector.
                int e)          ///< exponent (int).
{
  float32x4_t f, xn;
  unsigned int i;
  f = vdupq_n_f32 (1.f);
  if (e < 0)
    xn = jbm_4xf32_reciprocal (x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_4xf32_sqr (xn))
    if (i & 1)
      f = vmulq_f32 (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_4xf32_exp2 and
 * jbm_4xf32_log2 functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_pow (const float32x4_t x,     ///< float32x4_t vector.
               const float32x4_t e)     ///< exponent (float32x4_t).
{
  return jbm_4xf32_exp2 (vmulq_f32 (e, jbm_4xf32_log2 (x)));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (float32x4_t)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_sinwc (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return vmulq_f32 (x, jbm_4xf32_polynomial_3 (jbm_4xf32_sqr (x), K_SINWC_F32));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (float32x4_t):
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_coswc (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_4xf32_polynomial_3 (jbm_4xf32_sqr (x), K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_tanwc (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return vmulq_f32 (x, jbm_4xf32_rational_3_1 (jbm_4xf32_sqr (x), K_TANWC_F32));
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_4xf32_sinwc approximation (float32x4_t).
 */
static inline void
jbm_4xf32_sincoswc (const float32x4_t x,
                    ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    float32x4_t *s,
                    ///< pointer to the sin function value (float32x4_t).
                    float32x4_t *c)
                    ///< pointer to the cos function value (float32x4_t).
{
  *s = jbm_4xf32_sinwc (x);
  *c = jbm_4xf32_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (float32x4_t).
 *
 * \return reduced vector (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_trig (const float32x4_t x,    ///< float32x4_t vector.
                int32x4_t *q)   ///< quadrant (float32x4_ti).
{
  float32x4_t y;
  y = vrndnq_f32 (vmulq_n_f32 (x, 1.f / M_PI_2f));
  *q = vcvtq_s32_f32 (y);
  return vfmsq_f32 (x, y, vdupq_n_f32 (M_PI_2f));
}

/**
 * Function to calculate the function sin(x) from jbm_4xf32_sinwc and
 * jbm_4xf32_coswc approximations (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_sin (const float32x4_t x)     ///< float32x4_t vector.
{
  const float32x4_t pi2 = vdupq_n_f32 (2.f * M_PIf);
  float32x4_t y, s;
  y = jbm_4xf32_mod1 (x, 2.f * M_PIf);
  s = jbm_4xf32_sinwc (vsubq_f32 (y, pi2));
  s = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (7.f * M_PI_4f)),
                 jbm_4xf32_opposite
                 (jbm_4xf32_coswc (vsubq_f32 (vdupq_n_f32 (3.f * M_PI_2f),
                                              y))), s);
  s = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (5.f * M_PI_4f)),
                 jbm_4xf32_sinwc (vsubq_f32 (vdupq_n_f32 (M_PIf), y)), s);
  s = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (3.f * M_PI_4f)),
                 jbm_4xf32_coswc (vsubq_f32 (vdupq_n_f32 (M_PI_2f), y)), s);
  return vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (M_PI_4f)),
                    jbm_4xf32_sinwc (y), s);
}

/**
 * Function to calculate the function cos(x) from jbm_4xf32_sinwc and
 * jbm_4xf32_coswc approximations (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_cos (const float32x4_t x)     ///< float32x4_t vector.
{
  const float32x4_t pi2 = vdupq_n_f32 (2.f * M_PIf);
  float32x4_t y, c;
  y = jbm_4xf32_mod1 (x, 2.f * M_PIf);
  c = jbm_4xf32_coswc (vsubq_f32 (y, pi2));
  c = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (7.f * M_PI_4f)),
                 jbm_4xf32_sinwc (vsubq_f32 (y, vdupq_n_f32 (3.f * M_PI_2f))),
                 c);
  c = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (5.f * M_PI_4f)),
                 jbm_4xf32_opposite
                 (jbm_4xf32_coswc (vsubq_f32 (vdupq_n_f32 (M_PIf), y))), c);
  c = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (3.f * M_PI_4f)),
                 jbm_4xf32_sinwc (vsubq_f32 (vdupq_n_f32 (M_PI_2f), y)), c);
  return vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (M_PI_4f)),
                    jbm_4xf32_coswc (y), c);

}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_4xf32_sinwc and jbm_4xf32_coswc approximations (float32x4_t).
 */
static inline void
jbm_4xf32_sincos (const float32x4_t x,
                  ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  float32x4_t *s,
                  ///< pointer to the sin function value (float32x4_t).
                  float32x4_t *c)
                  ///< pointer to the cos function value (float32x4_t).
{
  const float32x4_t pi2 = vdupq_n_f32 (2.f * M_PIf);
  float32x4_t y, s1, c1, s2, c2;
  uint32x4_t m;
  y = jbm_4xf32_mod1 (x, 2.f * M_PIf);
  jbm_4xf32_sincoswc (vsubq_f32 (y, pi2), &s1, &c1);
  jbm_4xf32_sincoswc (vsubq_f32 (y, vdupq_n_f32 (3.f * M_PI_2f)), &c2, &s2);
  m = vcltq_f32 (y, vdupq_n_f32 (7.f * M_PI_4f));
  s1 = vbslq_f32 (m, jbm_4xf32_opposite (s2), s1);
  c1 = vbslq_f32 (m, c2, c1);
  jbm_4xf32_sincoswc (vsubq_f32 (vdupq_n_f32 (M_PIf), y), &s2, &c2);
  m = vcltq_f32 (y, vdupq_n_f32 (5.f * M_PI_4f));
  s1 = vbslq_f32 (m, s2, s1);
  c1 = vbslq_f32 (m, jbm_4xf32_opposite (c2), c1);
  jbm_4xf32_sincoswc (vsubq_f32 (vdupq_n_f32 (M_PI_2f), y), &c2, &s2);
  m = vcltq_f32 (y, vdupq_n_f32 (3.f * M_PI_4f));
  s1 = vbslq_f32 (m, s2, s1);
  c1 = vbslq_f32 (m, c2, c1);
  jbm_4xf32_sincoswc (y, &s2, &c2);
  m = vcltq_f32 (y, vdupq_n_f32 (M_PI_4f));
  *s = vbslq_f32 (m, s2, s1);
  *c = vbslq_f32 (m, c2, c1);
}

/**
 * Function to calculate the function tan(x) from jbm_4xf32_sincos function
 * (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_tan (const float32x4_t x)     ///< float32x4_t vector.
{
  float32x4_t s, c;
  jbm_4xf32_sincos (x, &s, &c);
  return vdivq_f32 (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_atanwc (const float32x4_t x)
                  ///< float32x4_t vector \f$\in\left[-1,1\right]\f$.
{
  return
    vmulq_f32 (x, jbm_4xf32_rational_4_2 (jbm_4xf32_sqr (x), K_ATANWC_F32));
}

/**
 * Function to calculate the function atan(x) using the jbm_4xf32_atanwc
 * function (float32x4_t).
 *
 * \return function value (in [-pi/2,pi/2]) (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_atan (const float32x4_t x)    ///< float32x4_t vector.
{
  float32x4_t f, ax;
  uint32x4_t m;
  ax = jbm_4xf32_abs (x);
  m = vcgtq_f32 (ax, vdupq_n_f32 (1.f));
  ax = vbslq_f32 (m, jbm_4xf32_reciprocal (ax), ax);
  f = jbm_4xf32_atanwc (ax);
  f = vbslq_f32 (m, vsubq_f32 (vdupq_n_f32 (M_PI_2f), f), f);
  return jbm_4xf32_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_4xf32_atan
 * function (float32x4_t).
 *
 * \return function value (in [-pi,pi]) (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_atan2 (const float32x4_t y,   ///< float32x4_t y component.
                 const float32x4_t x)   ///< float32x4_t x component.
{
  float32x4_t f, pi;
  uint32x4_t mx, my;
  pi = vdupq_n_f32 (M_PIf);
  f = jbm_4xf32_atan (vdivq_f32 (y, x));
  mx = vcltzq_f32 (x);
  my = vcltzq_f32 (y);
  f = vbslq_f32 (vandq_u32 (my, mx), vsubq_f32 (f, pi), f);
  return vbslq_f32 (vbicq_u32 (my, mx), vaddq_f32 (f, pi), f);
}

/**
 * Function to calculate the function asin(x) using the jbm_4xf32_atan function
 * (float32x4_t).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline float32x4_t
jbm_4xf32_asin (const float32x4_t x)    ///< float32x4_t vector.
{
  return
    jbm_4xf32_atan (vdivq_f32
                    (x, vsqrtq_f32 (vfmsq_f32 (vdupq_n_f32 (1.f), x, x))));
}

/**
 * Function to calculate the function acos(x) using the jbm_4xf32_atan function
 * (float32x4_t).
 *
 * \return function value (in [0,pi]) (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_acos (const float32x4_t x)    ///< float32x4_t vector.
{
  float32x4_t f;
  f =
    jbm_4xf32_atan (vdivq_f32
                    (vsqrtq_f32 (vfmsq_f32 (vdupq_n_f32 (1.f), x, x)), x));
  return vbslq_f32 (vcltq_f32 (x, vdupq_n_f32 (0.f)),
                    vaddq_f32 (f, vdupq_n_f32 (M_PIf)), f);

}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_sinh (const float32x4_t x)    ///< float32x4_t number.
{
  float32x4_t f;
  f = jbm_4xf32_exp (x);
  return vmulq_f32 (vdupq_n_f32 (0.5f),
                    vsubq_f32 (f, jbm_4xf32_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_cosh (const float32x4_t x)    ///< float32x4_t number.
{
  float32x4_t f;
  f = jbm_4xf32_exp (x);
  return vmulq_f32 (vdupq_n_f32 (0.5f),
                    vaddq_f32 (f, jbm_4xf32_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_tanh (const float32x4_t x)    ///< float32x4_t number.
{
  float32x4_t f, fi;
  f = jbm_4xf32_exp (x);
  fi = jbm_4xf32_reciprocal (f);
  f = vdivq_f32 (vsubq_f32 (f, fi), vaddq_f32 (f, fi));
  f = vbslq_f32 (vcgtq_f32 (x, vdupq_n_f32 (JBM_FLT_MAX_E_EXP)),
                 vdupq_n_f32 (1.f), f);
  return vbslq_f32 (vcltq_f32 (x, vdupq_n_f32 (-JBM_FLT_MAX_E_EXP)),
                    vdupq_n_f32 (-1.f), f);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_asinh (const float32x4_t x)   ///< float32x4_t number.
{
  return
    jbm_4xf32_log (vaddq_f32
                   (x, vsqrtq_f32 (vmlaq_f32 (vdupq_n_f32 (1.f), x, x))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_acosh (const float32x4_t x)   ///< float32x4_t number.
{
  return
    jbm_4xf32_log
    (vaddq_f32 (x, vsqrtq_f32 (jbm_4xf32_opposite (vmlsq_f32 (vdupq_n_f32 (1.f),
                                                              x, x)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_atanh (const float32x4_t x)   ///< float32x4_t number.
{
  float32x4_t u;
  u = vdupq_n_f32 (1.f);
  return vmulq_f32 (vdupq_n_f32 (0.5f),
                    jbm_4xf32_log (vdivq_f32 (vaddq_f32 (u, x),
                                              vsubq_f32 (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (float32x4_t)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_erfwc (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-1,1\right]\f$.
{
  return vmulq_f32 (x, jbm_4xf32_polynomial_5 (jbm_4xf32_sqr (x), K_ERFWC_F32));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (float32x4_t)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_erfcwc (const float32x4_t x)
                  ///< float32x4_t vector \f$\in\left[1,\infty\right]\f$.
{
  float32x4_t f, x2;
  x2 = jbm_4xf32_sqr (x);
  f = vmulq_f32 (jbm_4xf32_rational_7_4 (jbm_4xf32_reciprocal (x),
                                         K_ERFCWC_F32),
                 vdivq_f32 (x, jbm_4xf32_exp (x2)));
  return vbslq_f32 (vcgtq_f32 (x, vdupq_n_f32 (K_ERFC_MAX_F32)),
                    vdupq_n_f32 (0.f), f);

}

/**
 * Function to calculate the function erf(x) using jbm_4xf32_erfwc and
 * jbm_4xf32_erfcwc
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_erf (const float32x4_t x)     ///< float32x4_t vector.
{
  float32x4_t ax, u, f;
  ax = jbm_4xf32_abs (x);
  u = vdupq_n_f32 (1.f);
  f = vmulq_f32 (vdivq_f32 (x, ax), vsubq_f32 (u, jbm_4xf32_erfcwc (ax)));
  return vbslq_f32 (vcltq_f32 (ax, u), jbm_4xf32_erfwc (x), f);

}

/**
 * Function to calculate the function erfc(x) using jbm_4xf32_erfwc and
 * jbm_4xf32_erfcwc
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_4xf32_erfc (const float32x4_t x)    ///< float32x4_t vector.
{
  float32x4_t ax, u, f;
  ax = jbm_4xf32_abs (x);
  u = vdupq_n_f32 (1.f);
  f = vsubq_f32 (u, vmulq_f32 (vdivq_f32 (x, ax),
                               vsubq_f32 (u, jbm_4xf32_erfcwc (ax))));
  return vbslq_f32 (vcltq_f32 (ax, u), vsubq_f32 (u, jbm_4xf32_erfwc (x)), f);

}

/**
 * Function to calculate the solution of a float32x4_t vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return float32x4_t vector of solution values.
 */
static inline float32x4_t
jbm_solve_quadratic_reduced_4xf32 (float32x4_t a,
///< float32x4_t vector of 1st order coefficient of the equations.
                                   float32x4_t b,
///< float32x4_t vector of 0th order coefficient of the equations.
                                   const float32x4_t x1,
///< float32x4_t vector of left limits of the solution intervals.
                                   const float32x4_t x2)
///< float32x4_t vector of right limits of the solution intervals.
{
  float32x4_t k1, k2;
  k1 = vdupq_n_f32 (-0.5f);
  a = vmulq_f32 (a, k1);
  b = vsqrtq_f32 (vsubq_f32 (jbm_4xf32_sqr (a), b));
  k1 = vaddq_f32 (a, b);
  k2 = vsubq_f32 (a, b);
  k1 = vbslq_f32 (vcltq_f32 (k1, x1), k2, k1);
  return vbslq_f32 (vcgtq_f32 (k1, x2), k2, k1);
}

/**
 * Function to calculate the solution of a float32x4_t vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return float32x4_t vector of solution values.
 */
static inline float32x4_t
jbm_4xf32_solve_quadratic (const float32x4_t a,
///< float32x4_t vector of 2nd order coefficient of the equations.
                           const float32x4_t b,
///< float32x4_t vector of 1st order coefficient of the equations.
                           const float32x4_t c,
///< float32x4_t vector of 0th order coefficient of the equations.
                           const float32x4_t x1,
///< float32x4_t vector of left limits of the solution intervals.
                           const float32x4_t x2)
///< float32x4_t vector of right limits of the solution intervals.
{
  float32x4_t k1, k2;
  k1 = jbm_solve_quadratic_reduced_4xf32 (vdivq_f32 (b, a), vdivq_f32 (c, a),
                                          x1, x2);
  k2 = vdivq_f32 (jbm_4xf32_opposite (c), b);
  return vbslq_f32 (jbm_4xf32_small (a), k2, k1);
}

/**
 * Function to calculate the solution of a float32x4_t vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return float32x4_t vector of solution values.
 */
static inline float32x4_t
jbm_solve_cubic_reduced_4xf32 (const float32x4_t a,
                               ///< 2nd order coefficient of the equation.
                               const float32x4_t b,
                               ///< 1st order coefficient of the equation.
                               const float32x4_t c,
                               ///< 0th order coefficient of the equation.
                               const float32x4_t x1,
                               ///< left limit of the solution interval.
                               const float32x4_t x2)
                               ///< right limit of the solution interval.
{
  float32x4_t a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = vdupq_n_f32 (2.f * M_PIf / 3.f);
  c_2 = vdupq_n_f32 (0.5f);
  c_3 = vdupq_n_f32 (1.f / 3.f);
  a3 = vmulq_f32 (a, c_3);
  k0 = vmulq_f32 (a3, a3);
  k1 = vmlsq_f32 (k0, b, c_3);
  k0 = vmlsq_f32 (vmulq_f32 (a3, k0), vmlsq_f32 (b, a3, c), c_2);
  k3 = vmulq_f32 (k1, vmulq_f32 (k1, k1));
  k2 = vmlaq_f32 (k3, k0, k0);
  l1 = vsqrtq_f32 (jbm_4xf32_opposite (k1));
  l0 = vmulq_f32 (jbm_4xf32_acos (vdivq_f32 (k0, k3)), c_3);
  l1 = vaddq_f32 (l1, l1);
  l2 = vmlsq_f32 (a3, l1, jbm_4xf32_cos (k0));
  l3 = vmlsq_f32 (a3, l1, jbm_4xf32_cos (vaddq_f32 (l0, c2p_3)));
  l3 = vbslq_f32 (vorrq_u32 (vcltq_f32 (l2, x1), vcgtq_f32 (l2, x2)), l2, l3);
  l4 = vmlsq_f32 (a, l1, jbm_4xf32_cos (vsubq_f32 (l0, c2p_3)));
  l4 = vbslq_f32 (vorrq_u32 (vcltq_f32 (l3, x1), vcgtq_f32 (l3, x2)), l3, l4);
  k1 = vsqrtq_f32 (k2);
  l5 = vaddq_f32 (k0, k1);
  l5 = jbm_4xf32_cbrt (k2);
  k0 = vsubq_f32 (k0, k1);
  l5 = vaddq_f32 (l5, vsubq_f32 (jbm_4xf32_cbrt (k0), a3));
  return vbslq_f32 (vcltzq_f32 (k2), l5, l4);
}

/**
 * Function to calculate the solution of a float32x4_t vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return float32x4_t vector of solution values.
 */
static inline float32x4_t
jbm_4xf32_solve_cubic (float32x4_t a,
///< float32x4_t vector of 3rd order coefficient of the equations.
                       float32x4_t b,
///< float32x4_t vector of 2nd order coefficient of the equations.
                       float32x4_t c,
///< float32x4_t vector of 1st order coefficient of the equations.
                       float32x4_t d,
///< float32x4_t vector of 0th order coefficient of the equations.
                       float32x4_t x1,
///< float32x4_t vector of left limits of the solution intervals.
                       float32x4_t x2)
///< float32x4_t vector of right limits of the solution intervals.
{
  return
    vbslq_f32 (jbm_4xf32_small (a),
               jbm_4xf32_solve_quadratic (b, c, d, x1, x2),
               jbm_solve_cubic_reduced_4xf32 (vdivq_f32 (b, a),
                                              vdivq_f32 (c, a),
                                              vdivq_f32 (d, a), x1, x2));

}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_total (const float32x4_t d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const float32x4_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return vdupq_n_f32 (0.f);
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_null (const float32x4_t d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const float32x4_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return vdupq_n_f32 (1.f);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_centred (const float32x4_t d1,
                                ///< 1st flux limiter function parameter.
                                const float32x4_t d2)
                              ///< 2nd flux limiter function parameter.
{
  return vbslq_f32 (jbm_4xf32_small (d2),
                    vdupq_n_f32 (0.f), vdivq_f32 (d1, d2));

}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_superbee (const float32x4_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float32x4_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vdivq_f32 (d1, d2);
  r = vmaxq_f32 (vminq_f32 (jbm_4xf32_dbl (r), vdupq_n_f32 (1.f)),
                 vminq_f32 (r, vdupq_n_f32 (2.f)));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_minmod (const float32x4_t d1,
                               ///< 1st flux limiter function parameter.
                               const float32x4_t d2)
                             ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vminq_f32 (vdivq_f32 (d1, d2), vdupq_n_f32 (1.f));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_VanLeer (const float32x4_t d1,
                                ///< 1st flux limiter function parameter.
                                const float32x4_t d2)
                              ///< 2nd flux limiter function parameter.
{
  float32x4_t r, k;
  r = vdivq_f32 (d1, d2);
  k = jbm_4xf32_abs (r);
  r = vdivq_f32 (vaddq_f32 (r, k), vaddq_f32 (vdupq_n_f32 (1.f), k));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_VanAlbada (const float32x4_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const float32x4_t d2)
                                ///< 2nd flux limiter function parameter.
{
  float32x4_t r, k;
  r = vdivq_f32 (d1, d2);
  k = jbm_4xf32_sqr (r);
  r = vdivq_f32 (vaddq_f32 (r, k), vaddq_f32 (vdupq_n_f32 (1.f), k));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_minsuper (const float32x4_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float32x4_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vminq_f32 (vdivq_f32 (d1, d2), vdupq_n_f32 (2.f));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_supermin (const float32x4_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float32x4_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vdivq_f32 (d1, d2);
  r = vminq_f32 (jbm_4xf32_dbl (r), vdupq_n_f32 (1.f));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_monotonized_central (const float32x4_t d1,
///< 1st flux limiter function parameter.
                                            const float32x4_t d2)
///< 2nd flux limiter function parameter.
{
  float32x4_t r, rm;
  r = vdivq_f32 (d1, d2);
  rm = vmulq_f32 (vdupq_n_f32 (0.5f), vaddq_f32 (r, vdupq_n_f32 (1.f)));
  rm = vbslq_f32 (vcltq_f32 (r, vdupq_n_f32 (3.f)), rm, vdupq_n_f32 (2.f));
  rm = vbslq_f32 (vcgtq_f32 (r, vdupq_n_f32 (1.f / 3.f)),
                  jbm_4xf32_dbl (r), rm);
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    rm, vdupq_n_f32 (0.f));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter_mean (const float32x4_t d1,
                             ///< 1st flux limiter function parameter.
                             const float32x4_t d2)
                           ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vmulq_f32 (vdupq_n_f32 (0.5f),
                 vaddq_f32 (vdupq_n_f32 (1.f), vdivq_f32 (d1, d2)));
  return vbslq_f32 (vcgtq_f32 (vmulq_f32 (d1, d2), vdupq_n_f32 (FLT_EPSILON)),
                    r, vdupq_n_f32 (0.f));
}

/**
 * Function to do a flux limiter function (float32x4_t).
 *
 * \return flux limiter function value.
 */
static inline float32x4_t
jbm_4xf32_flux_limiter (const float32x4_t d1,
                        ///< 1st flux limiter function parameter.
                        const float32x4_t d2,
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
 * defined in an interval (float32x4_t).
 *
 * \return float32x4_t vector of integral values.
 */
static inline float32x4_t
jbm_4xf32_integral (float32x4_t (*f) (float32x4_t),
                    ///< pointer to the function to integrate.
                    const float32x4_t x1,       ///< left limit of the interval.
                    const float32x4_t x2)       ///< right limit of the interval.
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
  float32x4_t k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  float32x4_t k2, f1, f2;
#endif
  unsigned int i;
  h = vdupq_n_f32 (0.5f);
  dx = vmulq_f32 (h, vsubq_f32 (x2, x1));
  x = vmulq_f32 (h, vaddq_f32 (x2, x1));
  k = vdupq_n_f32 (a[0]);
  k = vmulq_f32 (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = vdupq_n_f32 (b[i]);
      k2 = vmulq_f32 (k2, dx);
      f1 = f (vsubq_f32 (x, k2));
      f2 = f (vaddq_f32 (x, k2));
      h = vdupq_n_f32 (a[i]);
      k = vmlaq_f32 (k, h, vaddq_f32 (f1, f2));
    }
#endif
  k = vmulq_f32 (k, dx);
  return k;
}

#define jbm_2xf64_reduce_add vaddvq_f64
#define jbm_2xf64_reduce_max vmaxvq_f64
#define jbm_2xf64_reduce_min vminvq_f64

/**
 * Function to calculate the maximum and minimum reduction value of a
 * float64x2_t vector.
 */
static inline void
jbm_2xf64_reduce_maxmin (const float64x2_t x,   ///< float64x2_t vector.
                         float *max,
                         ///< pointer to the maximum value (float).
                         float *min)
                         ///< pointer to the minimum value (float).
{
  *max = vmaxvq_f64 (x);
  *min = vminvq_f64 (x);
}

/**
 * Function to calculate the additive inverse value of a float64x2_t vector.
 *
 * \return negative value vector (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_opposite (const float64x2_t x)        ///< float64x2_t vector.
{
  return vnegq_f64 (x);
}

/**
 * Function to calculate the multiplicative inverse value of a float64x2_t vector.
 *
 * \return reciprocal value vector (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_reciprocal (const float64x2_t x)      ///< float64x2_t vector.
{
  return vdivq_f64 (vdupq_n_f64 (1.), x);
}

/**
 * Function to calculate the absolute value of a float64x2_t vector.
 *
 * \return absolute value vector.
 */
static inline float64x2_t
jbm_2xf64_abs (const float64x2_t x)     ///< float64x2_t vector.
{
  return vabsq_f64 (x);
}

/**
 * Function to calculate the hypot function (float64x2_t).
 *
 * \return function value vector (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_hypot (const float64x2_t x,   ///< 1st float64x2_t vector.
                 const float64x2_t y)   ///< 2nd float64x2_t vector.
{
  return vsqrtq_f64 (vmlaq_f64 (vmulq_f64 (x, x), y, y));
}

/**
 * Function to calculate the rest of a division (float64x2_t) by a double.
 *
 * \return rest value (in [0,|divisor|) interval) (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_mod1 (const float64x2_t x,    ///< dividend (float64x2_t).
                const double d) ///< divisor (float64x2_t).
{
  float64x2_t r;
  r = vrndmq_f64 (vmulq_f64 (x, 1. / d));
  return
    vbslq_f64 (vcgtq_f64 (jbm_2xf64_abs (r), vdupq_n_f64 (1. / DBL_EPSILON)),
               vmulq_n_f64 (d, 0.5), vfmsq_f64 (x, r, d));
}

/**
 * Function to calculate the rest of a division (float64x2_t).
 *
 * \return rest value (in [0,|divisor|) interval) (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_mod (const float64x2_t x,     ///< dividend (float64x2_t).
               const float64x2_t d)     ///< divisor (float64x2_t).
{
  return vmlsq_f64 (x, vrndmq_f64 (vdivq_f64 (x, d)), d);
}

/**
 * Function to implement the standard frexp function (float64x2_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline float64x2_t
jbm_2xf64_frexp (const float64x2_t x,   ///< float64x2_t vector.
                 int64x2_t *e)  ///< pointer to the extracted exponents vector.
{
  JBM2xF64 a, y, y2, z;
  uint64x2_t b, m1, m2, m3;
  int64x2_t e2;
  a.x = x;
  b = vdupq_n_u64 (0x7ff0000000000000L);
  y.i = vandq_u64 (a.i, b);
  m1 = vceqq_u64 (y.i, b);
  m2 = vceqzq_u64 (y.i);
  y2.x = x;
  y2.i = vandq_u64 (y2.i, vdupq_n_u64 (0x000fffffffffffffL));
  m3 = vceqzq_u64 (y2.i);
  y2.i = vdupq_n_u64 (0x0010000000000000L);
  z.x = vdivq_f64 (x, y2.x);
  z.i = vandq_u64 (z.i, b);
  e2 = vbslq_s64 (m2,
                  vsubq_s64 (vshrq_n_s64 (vreinterpretq_s64_u64 (z.i), 52),
                             vdupq_n_s64 (2044L)),
                  vsubq_s64 (vshrq_n_s64 (vreinterpretq_s64_u64 (y.i), 52),
                             vdupq_n_s64 (1022L)));
  y.x = vbslq_f64 (m2, vmulq_f64 (y2.x, z.x), y.x);
  e2 = vbslq_s64 (vorrq_u64 (m1, vandq_u64 (m2, m3)), vdupq_n_s64 (0L), e2);
  *e = e2;
  return vbslq_f64 (m1, x, vmulq_f64 (vdupq_n_f64 (0.5), vdivq_f64 (x, y.x)));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (int64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_exp2n (int64x2_t e)   ///< exponent vector (int64x2_t).
{
  float64x2_t x;
  x = vbslq_f64
    (vcgtq_s64 (e, vdupq_n_s64 (-1023L)),
     vreinterpretq_f64_s64 (vshlq_n_s64 (vaddq_s64 (e, vdupq_n_s64 (1023L)),
                                         52)),
     vreinterpretq_f64_s64 (vshlq_s64 (vdupq_n_s64 (0x0008000000000000L),
                                       vsubq_s64 (vdupq_n_s64 (-1023L), e))));
  x = vbslq_f64 (vcgtq_s64 (vdupq_n_s64 (-1074L), e), vdupq_n_f64 (0.), x);
  return
    vbslq_f64 (vcgtq_s64 (e, vdupq_n_s64 (1023L)), vdupq_n_f64 (INFINITY), x);
}

/**
 * Function to implement the standard ldexp function (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_ldexp (const float64x2_t x,   ///< float64x2_t vector.
                 int64x2_t e)   ///< exponent vector (int64x2_t).
{
  return vmulq_f64 (x, jbm_2xf64_exp2n (e));
}

/**
 * Function to check small float64x2_t vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline uint64x2_t
jbm_2xf64_small (const float64x2_t x)   ///< float64x2_t vector.
{
  return vcltq_f64 (jbm_2xf64_abs (x), vdupq_n_f64 (DBL_EPSILON));
}

/**
 * Function to calculate the float64x2_t vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin float64x2_t vector.
 */
static inline float64x2_t
jbm_2xf64_modmin (const float64x2_t a,  ///< 1st float64x2_t vector.
                  const float64x2_t b)  ///< 2nd float64x2_t vector.
{
  float64x2_t aa, ab, y, z;
  z = vdupq_n_f64 (0.);
  ab = vmulq_f64 (a, b);
  y = vbslq_f64 (vcleq_f64 (ab, z), z, a);
  aa = jbm_2xf64_abs (y);
  ab = jbm_2xf64_abs (b);
  return vbslq_f64 (vcgtq_f64 (aa, ab), b, y);
}

/**
 * Function to interchange 2 float64x2_t numbers.
 */
static inline void
jbm_change_2xf64 (float64x2_t *restrict a,      ///< 1st float64x2_t vector pointer.
                  float64x2_t *restrict b)      ///< 2nd float64x2_t vector pointer.
{
  float64x2_t c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a float64x2_t vector.
 *
 * \return float64x2_t double.
 */
static inline float64x2_t
jbm_2xf64_dbl (const float64x2_t x)     ///< float64x2_t vector.
{
  return vaddq_f64 (x, x);
}

/**
 * Function to calculate the square of the components of a float64x2_t vector.
 *
 * \return float64x2_t vector square.
 */
static inline float64x2_t
jbm_2xf64_sqr (const float64x2_t x)     ///< float64x2_t vector.
{
  return vmulq_f64 (x, x);
}

/**
 * Function to perform an extrapolation between 2 float64x2_t vectors of 2D points.
 *
 * \return float64x2_t vector of y-coordinates of the extrapolated points.
 */
static inline float64x2_t
jbm_2xf64_extrapolate (const float64x2_t x,
///< float64x2_t vector of x-coordinates of the extrapolated points.
                       const float64x2_t x1,
///< float64x2_t vector of x-coordinates of the 1st points.
                       const float64x2_t x2,
///< float64x2_t vector of x-coordinates of the 2nd points.
                       const float64x2_t y1,
///< float64x2_t vector of y-coordinates of the 1st points.
                       const float64x2_t y2)
///< float64x2_t vector of y-coordinates of the 2nd points.
{
  float64x2_t d;
  d = vsubq_f64 (x, x1);
  return vmlaq_f64 (y1, d, vdivq_f64 (vsubq_f64 (y2, y1), vsubq_f64 (x2, x1)));
}

/**
 * Function to perform an interpolation between 2 float64x2_t vectors of 2D points.
 *
 * \return float64x2_t vector of y-coordinates of the interpolated points.
 */
static inline float64x2_t
jbm_2xf64_interpolate (const float64x2_t x,
                       ///< float64x2_t vector of x-coordinates of the interpolated
                       ///< points.
                       const float64x2_t x1,
                       ///< float64x2_t vector of x-coordinates of the 1st points.
                       const float64x2_t x2,
                       ///< float64x2_t vector of x-coordinates of the 2nd points.
                       const float64x2_t y1,
                       ///< float64x2_t vector of y-coordinates of the 1st points.
                       const float64x2_t y2)
                     ///< float64x2_t vector of y-coordinates of the 2nd points.
{
  float64x2_t k;
  k = jbm_2xf64_extrapolate (x, x1, x2, y1, y2);
  k = vbslq_f64 (vcgtq_f64 (x, x1), k, y1);
  return vbslq_f64 (vcltq_f64 (x, x2), k, y2);
}

/**
 * Function to calculate the length of a float64x2_t vector of 2D segments.
 *
 * \return float64x2_t vector of segment lengths.
 */
static inline float64x2_t
jbm_2xf64_v2_length (const float64x2_t x1,
///< float64x2_t vector of x-coordinates of the 1st points defining the segment.
                     const float64x2_t y1,
///< float64x2_t vector of y-coordinates of the 1st points defining the segment.
                     const float64x2_t x2,
///< float64x2_t vector of x-coordinates of the 2nd points defining the segment.
                     const float64x2_t y2)
///< float64x2_t vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_2xf64_hypot (vsubq_f64 (x2, x1), vsubq_f64 (y2, y1));
}

/**
 * Function to calculate the length of a float64x2_t vector of 3D segments.
 *
 * \return float64x2_t vector of segment lengths.
 */
static inline float64x2_t
jbm_2xf64_v3_length (const float64x2_t x1,
///< float64x2_t vector of x-coordinates of the 1st points defining the segments.
                     const float64x2_t y1,
///< float64x2_t vector of y-coordinates of the 1st points defining the segments.
                     const float64x2_t z1,
///< float64x2_t vector of z-coordinates of the 1st points defining the segments.
                     const float64x2_t x2,
///< float64x2_t vector of x-coordinates of the 2nd points defining the segments.
                     const float64x2_t y2,
///< float64x2_t vector of y-coordinates of the 2nd points defining the segments.
                     const float64x2_t z2)
///< float64x2_t vector of z-coordinates of the 2nd points defining the segments.
{
  float64x2_t dx, dy, dz;
  dx = jbm_2xf64_sqr (vsubq_f64 (x2, x1));
  dy = vsubq_f64 (y2, y1);
  dy = vmlaq_f64 (dx, dy, dy);
  dz = vsubq_f64 (z2, z1);
  return vsqrtq_f64 (vmlaq_f64 (dy, dz, dz));
}

/**
 * Function to calculate a 1st order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, vdupq_n_f64 (p[1]));
}

/**
 * Function to calculate a 2nd order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_1 (x, p + 1));
}

/**
 * Function to calculate a 3rd order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_2 (x, p + 1));
}

/**
 * Function to calculate a 4th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_4 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_3 (x, p + 1));
}

/**
 * Function to calculate a 5th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_5 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_4 (x, p + 1));
}

/**
 * Function to calculate a 6th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_6 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_5 (x, p + 1));
}

/**
 * Function to calculate a 7th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_7 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_6 (x, p + 1));
}

/**
 * Function to calculate a 8th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_8 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_7 (x, p + 1));
}

/**
 * Function to calculate a 9th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_9 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_8 (x, p + 1));
}

/**
 * Function to calculate a 10th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_10 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_9 (x, p + 1));
}

/**
 * Function to calculate a 11th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_11 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_10 (x, p + 1));
}

/**
 * Function to calculate a 12th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_12 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_11 (x, p + 1));
}

/**
 * Function to calculate a 13th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_13 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_12 (x, p + 1));
}

/**
 * Function to calculate a 14th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_14 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_13 (x, p + 1));
}

/**
 * Function to calculate a 15th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_15 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_14 (x, p + 1));
}

/**
 * Function to calculate a 16th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_16 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_15 (x, p + 1));
}

/**
 * Function to calculate a 17th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_17 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_16 (x, p + 1));
}

/**
 * Function to calculate a 18th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_18 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_17 (x, p + 1));
}

/**
 * Function to calculate a 19th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_19 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_18 (x, p + 1));
}

/**
 * Function to calculate a 20th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_20 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_19 (x, p + 1));
}

/**
 * Function to calculate a 21th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_21 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_20 (x, p + 1));
}

/**
 * Function to calculate a 22th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_22 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_21 (x, p + 1));
}

/**
 * Function to calculate a 23th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_23 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_22 (x, p + 1));
}

/**
 * Function to calculate a 24th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_24 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_23 (x, p + 1));
}

/**
 * Function to calculate a 25th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_25 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_24 (x, p + 1));
}

/**
 * Function to calculate a 26th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_26 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_25 (x, p + 1));
}

/**
 * Function to calculate a 27th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_27 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_26 (x, p + 1));
}

/**
 * Function to calculate a 28th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_28 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_27 (x, p + 1));
}

/**
 * Function to calculate a 29th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_2xf64_polynomial_29 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_2xf64_polynomial_28 (x, p + 1));
}

/**
 * Function to calculate a 0th+1st order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_1_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[1])));
}

/**
 * Function to calculate a 0th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_2_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 1)));
}

/**
 * Function to calculate a 1st+1st order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_2_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[2])));
}

/**
 * Function to calculate a 0th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_3_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 1)));
}

/**
 * Function to calculate a 1st+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_3_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 2)));
}

/**
 * Function to calculate a 1st+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_3_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[3])));
}

/**
 * Function to calculate a 0th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_4_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 1)));
}

/**
 * Function to calculate a 1st+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_4_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_4_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 3)));
}

/**
 * Function to calculate a 1st+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_4_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[4])));
}

/**
 * Function to calculate a 0th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_5_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 1)));
}

/**
 * Function to calculate a 1st+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_5_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_5_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_5_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 4)));
}

/**
 * Function to calculate a 1st+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_5_4 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[5])));
}

/**
 * Function to calculate a 0th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_6_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 1)));
}

/**
 * Function to calculate a 1st+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_6_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_6_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_6_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 4)));
}

/**
 * Function to calculate a 4th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_6_4 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 5)));
}

/**
 * Function to calculate a 1st+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_6_5 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[6])));
}

/**
 * Function to calculate a 0th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 1)));
}

/**
 * Function to calculate a 1st+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 4)));
}

/**
 * Function to calculate a 4th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_4 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 5)));
}

/**
 * Function to calculate a 5th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_5 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 6)));
}

/**
 * Function to calculate a 1st+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_7_6 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[7])));
}

/**
 * Function to calculate a 0th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 1)));
}

/**
 * Function to calculate a 1st+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 4)));
}

/**
 * Function to calculate a 4th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_4 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 5)));
}

/**
 * Function to calculate a 5th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_5 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 6)));
}

/**
 * Function to calculate a 6th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_6 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 7)));
}

/**
 * Function to calculate a 1st+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_8_7 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[8])));
}

/**
 * Function to calculate a 0th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_0 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 1)));
}

/**
 * Function to calculate a 1st+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_1 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_2 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_3 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 4)));
}

/**
 * Function to calculate a 4th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_4 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 5)));
}

/**
 * Function to calculate a 5th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_5 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 6)));
}

/**
 * Function to calculate a 6th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_6 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 7)));
}

/**
 * Function to calculate a 7th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_7 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 8)));
}

/**
 * Function to calculate a 1st+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_9_8 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[9])));
}

/**
 * Function to calculate a 0th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 1)));
}

/**
 * Function to calculate a 1st+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 4)));
}

/**
 * Function to calculate a 4th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 5)));
}

/**
 * Function to calculate a 5th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 6)));
}

/**
 * Function to calculate a 6th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 7)));
}

/**
 * Function to calculate a 7th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 8)));
}

/**
 * Function to calculate a 8th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 9)));
}

/**
 * Function to calculate a 1st+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_10_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[10])));
}

/**
 * Function to calculate a 0th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 1)));
}

/**
 * Function to calculate a 1st+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 4)));
}

/**
 * Function to calculate a 4th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 5)));
}

/**
 * Function to calculate a 5th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 6)));
}

/**
 * Function to calculate a 6th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 7)));
}

/**
 * Function to calculate a 7th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 8)));
}

/**
 * Function to calculate a 8th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 9)));
}

/**
 * Function to calculate a 9th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 10)));
}

/**
 * Function to calculate a 1st+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_11_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[11])));
}

/**
 * Function to calculate a 0th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 1)));
}

/**
 * Function to calculate a 1st+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 4)));
}

/**
 * Function to calculate a 4th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 5)));
}

/**
 * Function to calculate a 5th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 6)));
}

/**
 * Function to calculate a 6th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 7)));
}

/**
 * Function to calculate a 7th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 8)));
}

/**
 * Function to calculate a 8th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 9)));
}

/**
 * Function to calculate a 9th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 10)));
}

/**
 * Function to calculate a 10th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 11)));
}

/**
 * Function to calculate a 1st+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_12_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[12])));
}

/**
 * Function to calculate a 0th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 1)));
}

/**
 * Function to calculate a 1st+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 4)));
}

/**
 * Function to calculate a 4th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 5)));
}

/**
 * Function to calculate a 5th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 6)));
}

/**
 * Function to calculate a 6th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 7)));
}

/**
 * Function to calculate a 7th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 8)));
}

/**
 * Function to calculate a 8th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 9)));
}

/**
 * Function to calculate a 9th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 10)));
}

/**
 * Function to calculate a 10th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 11)));
}

/**
 * Function to calculate a 11th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 12)));
}

/**
 * Function to calculate a 1st+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_13_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[13])));
}

/**
 * Function to calculate a 0th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 1)));
}

/**
 * Function to calculate a 1st+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 4)));
}

/**
 * Function to calculate a 4th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 5)));
}

/**
 * Function to calculate a 5th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 6)));
}

/**
 * Function to calculate a 6th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 7)));
}

/**
 * Function to calculate a 7th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 8)));
}

/**
 * Function to calculate a 8th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 9)));
}

/**
 * Function to calculate a 9th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 10)));
}

/**
 * Function to calculate a 10th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 11)));
}

/**
 * Function to calculate a 11th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 12)));
}

/**
 * Function to calculate a 12th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 13)));
}

/**
 * Function to calculate a 1st+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_14_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[14])));
}

/**
 * Function to calculate a 0th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 1)));
}

/**
 * Function to calculate a 1st+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 4)));
}

/**
 * Function to calculate a 4th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 5)));
}

/**
 * Function to calculate a 5th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 6)));
}

/**
 * Function to calculate a 6th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 7)));
}

/**
 * Function to calculate a 7th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 8)));
}

/**
 * Function to calculate a 8th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 9)));
}

/**
 * Function to calculate a 9th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 10)));
}

/**
 * Function to calculate a 10th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 11)));
}

/**
 * Function to calculate a 11th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 12)));
}

/**
 * Function to calculate a 12th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 13)));
}

/**
 * Function to calculate a 13th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 14)));
}

/**
 * Function to calculate a 1st+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_15_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[15])));
}

/**
 * Function to calculate a 0th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 1)));
}

/**
 * Function to calculate a 1st+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 4)));
}

/**
 * Function to calculate a 4th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 5)));
}

/**
 * Function to calculate a 5th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 6)));
}

/**
 * Function to calculate a 6th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 7)));
}

/**
 * Function to calculate a 7th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 8)));
}

/**
 * Function to calculate a 8th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 9)));
}

/**
 * Function to calculate a 9th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 10)));
}

/**
 * Function to calculate a 10th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 11)));
}

/**
 * Function to calculate a 11th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 12)));
}

/**
 * Function to calculate a 12th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 13)));
}

/**
 * Function to calculate a 13th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 14)));
}

/**
 * Function to calculate a 14th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 15)));
}

/**
 * Function to calculate a 1st+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_16_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[16])));
}

/**
 * Function to calculate a 0th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 1)));
}

/**
 * Function to calculate a 1st+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 4)));
}

/**
 * Function to calculate a 4th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 5)));
}

/**
 * Function to calculate a 5th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 6)));
}

/**
 * Function to calculate a 6th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 7)));
}

/**
 * Function to calculate a 7th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 8)));
}

/**
 * Function to calculate a 8th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 9)));
}

/**
 * Function to calculate a 9th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 10)));
}

/**
 * Function to calculate a 10th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 11)));
}

/**
 * Function to calculate a 11th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 12)));
}

/**
 * Function to calculate a 12th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 13)));
}

/**
 * Function to calculate a 13th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 14)));
}

/**
 * Function to calculate a 14th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 15)));
}

/**
 * Function to calculate a 15th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 16)));
}

/**
 * Function to calculate a 1st+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_17_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[17])));
}

/**
 * Function to calculate a 0th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 1)));
}

/**
 * Function to calculate a 1st+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 4)));
}

/**
 * Function to calculate a 4th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 5)));
}

/**
 * Function to calculate a 5th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 6)));
}

/**
 * Function to calculate a 6th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 7)));
}

/**
 * Function to calculate a 7th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 8)));
}

/**
 * Function to calculate a 8th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 9)));
}

/**
 * Function to calculate a 9th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 10)));
}

/**
 * Function to calculate a 10th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 11)));
}

/**
 * Function to calculate a 11th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 12)));
}

/**
 * Function to calculate a 12th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 13)));
}

/**
 * Function to calculate a 13th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 14)));
}

/**
 * Function to calculate a 14th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 15)));
}

/**
 * Function to calculate a 15th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 16)));
}

/**
 * Function to calculate a 16th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 17)));
}

/**
 * Function to calculate a 1st+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_18_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[18])));
}

/**
 * Function to calculate a 0th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 1)));
}

/**
 * Function to calculate a 1st+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 4)));
}

/**
 * Function to calculate a 4th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 5)));
}

/**
 * Function to calculate a 5th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 6)));
}

/**
 * Function to calculate a 6th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 7)));
}

/**
 * Function to calculate a 7th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 8)));
}

/**
 * Function to calculate a 8th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 9)));
}

/**
 * Function to calculate a 9th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 10)));
}

/**
 * Function to calculate a 10th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 11)));
}

/**
 * Function to calculate a 11th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 12)));
}

/**
 * Function to calculate a 12th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 13)));
}

/**
 * Function to calculate a 13th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 14)));
}

/**
 * Function to calculate a 14th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 15)));
}

/**
 * Function to calculate a 15th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 16)));
}

/**
 * Function to calculate a 16th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 17)));
}

/**
 * Function to calculate a 17th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 18)));
}

/**
 * Function to calculate a 1st+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_19_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[19])));
}

/**
 * Function to calculate a 0th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 1)));
}

/**
 * Function to calculate a 1st+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 4)));
}

/**
 * Function to calculate a 4th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 5)));
}

/**
 * Function to calculate a 5th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 6)));
}

/**
 * Function to calculate a 6th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 7)));
}

/**
 * Function to calculate a 7th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 8)));
}

/**
 * Function to calculate a 8th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 9)));
}

/**
 * Function to calculate a 9th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 10)));
}

/**
 * Function to calculate a 10th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 11)));
}

/**
 * Function to calculate a 11th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 12)));
}

/**
 * Function to calculate a 12th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 13)));
}

/**
 * Function to calculate a 13th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 14)));
}

/**
 * Function to calculate a 14th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 15)));
}

/**
 * Function to calculate a 15th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 16)));
}

/**
 * Function to calculate a 16th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 17)));
}

/**
 * Function to calculate a 17th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 18)));
}

/**
 * Function to calculate a 18th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 19)));
}

/**
 * Function to calculate a 1st+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_20_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[20])));
}

/**
 * Function to calculate a 0th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 1)));
}

/**
 * Function to calculate a 1st+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 4)));
}

/**
 * Function to calculate a 4th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 5)));
}

/**
 * Function to calculate a 5th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 6)));
}

/**
 * Function to calculate a 6th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 7)));
}

/**
 * Function to calculate a 7th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 8)));
}

/**
 * Function to calculate a 8th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 9)));
}

/**
 * Function to calculate a 9th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 10)));
}

/**
 * Function to calculate a 10th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 11)));
}

/**
 * Function to calculate a 11th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 12)));
}

/**
 * Function to calculate a 12th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 13)));
}

/**
 * Function to calculate a 13th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 14)));
}

/**
 * Function to calculate a 14th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 15)));
}

/**
 * Function to calculate a 15th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 16)));
}

/**
 * Function to calculate a 16th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 17)));
}

/**
 * Function to calculate a 17th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 18)));
}

/**
 * Function to calculate a 18th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 19)));
}

/**
 * Function to calculate a 19th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 20)));
}

/**
 * Function to calculate a 1st+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_21_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[21])));
}

/**
 * Function to calculate a 0th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 1)));
}

/**
 * Function to calculate a 1st+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 4)));
}

/**
 * Function to calculate a 4th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 5)));
}

/**
 * Function to calculate a 5th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 6)));
}

/**
 * Function to calculate a 6th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 7)));
}

/**
 * Function to calculate a 7th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 8)));
}

/**
 * Function to calculate a 8th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 9)));
}

/**
 * Function to calculate a 9th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 10)));
}

/**
 * Function to calculate a 10th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 11)));
}

/**
 * Function to calculate a 11th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 12)));
}

/**
 * Function to calculate a 12th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 13)));
}

/**
 * Function to calculate a 13th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 14)));
}

/**
 * Function to calculate a 14th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 15)));
}

/**
 * Function to calculate a 15th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 16)));
}

/**
 * Function to calculate a 16th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 17)));
}

/**
 * Function to calculate a 17th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 18)));
}

/**
 * Function to calculate a 18th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 19)));
}

/**
 * Function to calculate a 19th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 20)));
}

/**
 * Function to calculate a 20th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 21)));
}

/**
 * Function to calculate a 1st+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_22_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[22])));
}

/**
 * Function to calculate a 0th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 1)));
}

/**
 * Function to calculate a 1st+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 4)));
}

/**
 * Function to calculate a 4th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 5)));
}

/**
 * Function to calculate a 5th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 6)));
}

/**
 * Function to calculate a 6th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 7)));
}

/**
 * Function to calculate a 7th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 8)));
}

/**
 * Function to calculate a 8th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 9)));
}

/**
 * Function to calculate a 9th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 10)));
}

/**
 * Function to calculate a 10th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 11)));
}

/**
 * Function to calculate a 11th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 12)));
}

/**
 * Function to calculate a 12th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 13)));
}

/**
 * Function to calculate a 13th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 14)));
}

/**
 * Function to calculate a 14th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 15)));
}

/**
 * Function to calculate a 15th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 16)));
}

/**
 * Function to calculate a 16th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 17)));
}

/**
 * Function to calculate a 17th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 18)));
}

/**
 * Function to calculate a 18th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 19)));
}

/**
 * Function to calculate a 19th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 20)));
}

/**
 * Function to calculate a 20th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 21)));
}

/**
 * Function to calculate a 21th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 22)));
}

/**
 * Function to calculate a 1st+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_23_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[23])));
}

/**
 * Function to calculate a 0th+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_23 (x, p + 1)));
}

/**
 * Function to calculate a 1st+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 4)));
}

/**
 * Function to calculate a 4th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 5)));
}

/**
 * Function to calculate a 5th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 6)));
}

/**
 * Function to calculate a 6th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 7)));
}

/**
 * Function to calculate a 7th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 8)));
}

/**
 * Function to calculate a 8th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 9)));
}

/**
 * Function to calculate a 9th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 10)));
}

/**
 * Function to calculate a 10th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 11)));
}

/**
 * Function to calculate a 11th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 12)));
}

/**
 * Function to calculate a 12th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 13)));
}

/**
 * Function to calculate a 13th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 14)));
}

/**
 * Function to calculate a 14th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 15)));
}

/**
 * Function to calculate a 15th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 16)));
}

/**
 * Function to calculate a 16th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 17)));
}

/**
 * Function to calculate a 17th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 18)));
}

/**
 * Function to calculate a 18th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 19)));
}

/**
 * Function to calculate a 19th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 20)));
}

/**
 * Function to calculate a 20th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 21)));
}

/**
 * Function to calculate a 21th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 22)));
}

/**
 * Function to calculate a 22th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 23)));
}

/**
 * Function to calculate a 1st+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_24_23 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_23 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[24])));
}

/**
 * Function to calculate a 0th+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_24 (x, p + 1)));
}

/**
 * Function to calculate a 1st+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_23 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 4)));
}

/**
 * Function to calculate a 4th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 5)));
}

/**
 * Function to calculate a 5th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 6)));
}

/**
 * Function to calculate a 6th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 7)));
}

/**
 * Function to calculate a 7th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 8)));
}

/**
 * Function to calculate a 8th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 9)));
}

/**
 * Function to calculate a 9th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 10)));
}

/**
 * Function to calculate a 10th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 11)));
}

/**
 * Function to calculate a 11th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 12)));
}

/**
 * Function to calculate a 12th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 13)));
}

/**
 * Function to calculate a 13th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 14)));
}

/**
 * Function to calculate a 14th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 15)));
}

/**
 * Function to calculate a 15th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 16)));
}

/**
 * Function to calculate a 16th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 17)));
}

/**
 * Function to calculate a 17th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 18)));
}

/**
 * Function to calculate a 18th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 19)));
}

/**
 * Function to calculate a 19th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 20)));
}

/**
 * Function to calculate a 20th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 21)));
}

/**
 * Function to calculate a 21th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 22)));
}

/**
 * Function to calculate a 22th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 23)));
}

/**
 * Function to calculate a 23th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_23 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_23 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 24)));
}

/**
 * Function to calculate a 1st+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_25_24 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_24 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[25])));
}

/**
 * Function to calculate a 0th+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_25 (x, p + 1)));
}

/**
 * Function to calculate a 1st+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_24 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_23 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 4)));
}

/**
 * Function to calculate a 4th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 5)));
}

/**
 * Function to calculate a 5th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 6)));
}

/**
 * Function to calculate a 6th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 7)));
}

/**
 * Function to calculate a 7th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 8)));
}

/**
 * Function to calculate a 8th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 9)));
}

/**
 * Function to calculate a 9th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 10)));
}

/**
 * Function to calculate a 10th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 11)));
}

/**
 * Function to calculate a 11th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 12)));
}

/**
 * Function to calculate a 12th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 13)));
}

/**
 * Function to calculate a 13th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 14)));
}

/**
 * Function to calculate a 14th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 15)));
}

/**
 * Function to calculate a 15th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 16)));
}

/**
 * Function to calculate a 16th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 17)));
}

/**
 * Function to calculate a 17th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 18)));
}

/**
 * Function to calculate a 18th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 19)));
}

/**
 * Function to calculate a 19th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 20)));
}

/**
 * Function to calculate a 20th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 21)));
}

/**
 * Function to calculate a 21th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 22)));
}

/**
 * Function to calculate a 22th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 23)));
}

/**
 * Function to calculate a 23th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_23 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_23 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 24)));
}

/**
 * Function to calculate a 24th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_24 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_24 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 25)));
}

/**
 * Function to calculate a 1st+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_26_25 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_25 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[26])));
}

/**
 * Function to calculate a 0th+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_26 (x, p + 1)));
}

/**
 * Function to calculate a 1st+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_25 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_24 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_23 (x, p + 4)));
}

/**
 * Function to calculate a 4th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 5)));
}

/**
 * Function to calculate a 5th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 6)));
}

/**
 * Function to calculate a 6th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 7)));
}

/**
 * Function to calculate a 7th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 8)));
}

/**
 * Function to calculate a 8th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 9)));
}

/**
 * Function to calculate a 9th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 10)));
}

/**
 * Function to calculate a 10th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 11)));
}

/**
 * Function to calculate a 11th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 12)));
}

/**
 * Function to calculate a 12th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 13)));
}

/**
 * Function to calculate a 13th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 14)));
}

/**
 * Function to calculate a 14th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 15)));
}

/**
 * Function to calculate a 15th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 16)));
}

/**
 * Function to calculate a 16th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 17)));
}

/**
 * Function to calculate a 17th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 18)));
}

/**
 * Function to calculate a 18th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 19)));
}

/**
 * Function to calculate a 19th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 20)));
}

/**
 * Function to calculate a 20th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 21)));
}

/**
 * Function to calculate a 21th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 22)));
}

/**
 * Function to calculate a 22th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 23)));
}

/**
 * Function to calculate a 23th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_23 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_23 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 24)));
}

/**
 * Function to calculate a 24th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_24 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_24 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 25)));
}

/**
 * Function to calculate a 25th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_25 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_25 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 26)));
}

/**
 * Function to calculate a 1st+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_27_26 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_26 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[27])));
}

/**
 * Function to calculate a 0th+28th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_27 (x, p + 1)));
}

/**
 * Function to calculate a 1st+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_26 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_25 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_24 (x, p + 4)));
}

/**
 * Function to calculate a 4th+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_23 (x, p + 5)));
}

/**
 * Function to calculate a 5th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 6)));
}

/**
 * Function to calculate a 6th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 7)));
}

/**
 * Function to calculate a 7th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 8)));
}

/**
 * Function to calculate a 8th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 9)));
}

/**
 * Function to calculate a 9th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 10)));
}

/**
 * Function to calculate a 10th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 11)));
}

/**
 * Function to calculate a 11th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 12)));
}

/**
 * Function to calculate a 12th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 13)));
}

/**
 * Function to calculate a 13th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 14)));
}

/**
 * Function to calculate a 14th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 15)));
}

/**
 * Function to calculate a 15th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 16)));
}

/**
 * Function to calculate a 16th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 17)));
}

/**
 * Function to calculate a 17th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 18)));
}

/**
 * Function to calculate a 18th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 19)));
}

/**
 * Function to calculate a 19th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 20)));
}

/**
 * Function to calculate a 20th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 21)));
}

/**
 * Function to calculate a 21th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 22)));
}

/**
 * Function to calculate a 22th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 23)));
}

/**
 * Function to calculate a 23th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_23 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_23 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 24)));
}

/**
 * Function to calculate a 24th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_24 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_24 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 25)));
}

/**
 * Function to calculate a 25th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_25 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_25 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 26)));
}

/**
 * Function to calculate a 26th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_26 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_26 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 27)));
}

/**
 * Function to calculate a 1st+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_28_27 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_27 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[28])));
}

/**
 * Function to calculate a 0th+29th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_0 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_28 (x, p + 1)));
}

/**
 * Function to calculate a 1st+28th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_1 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_1 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_27 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_2 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_2 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_26 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_3 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_3 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_25 (x, p + 4)));
}

/**
 * Function to calculate a 4th+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_4 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_4 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_24 (x, p + 5)));
}

/**
 * Function to calculate a 5th+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_5 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_5 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_23 (x, p + 6)));
}

/**
 * Function to calculate a 6th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_6 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_6 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_22 (x, p + 7)));
}

/**
 * Function to calculate a 7th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_7 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_7 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_21 (x, p + 8)));
}

/**
 * Function to calculate a 8th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_8 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_8 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_20 (x, p + 9)));
}

/**
 * Function to calculate a 9th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_9 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_9 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_19 (x, p + 10)));
}

/**
 * Function to calculate a 10th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_10 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_10 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_18 (x, p + 11)));
}

/**
 * Function to calculate a 11th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_11 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_11 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_17 (x, p + 12)));
}

/**
 * Function to calculate a 12th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_12 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_12 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_16 (x, p + 13)));
}

/**
 * Function to calculate a 13th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_13 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_13 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_15 (x, p + 14)));
}

/**
 * Function to calculate a 14th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_14 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_14 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_14 (x, p + 15)));
}

/**
 * Function to calculate a 15th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_15 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_15 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_13 (x, p + 16)));
}

/**
 * Function to calculate a 16th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_16 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_16 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_12 (x, p + 17)));
}

/**
 * Function to calculate a 17th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_17 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_17 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_11 (x, p + 18)));
}

/**
 * Function to calculate a 18th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_18 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_18 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_10 (x, p + 19)));
}

/**
 * Function to calculate a 19th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_19 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_19 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_9 (x, p + 20)));
}

/**
 * Function to calculate a 20th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_20 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_20 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_8 (x, p + 21)));
}

/**
 * Function to calculate a 21th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_21 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_21 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_7 (x, p + 22)));
}

/**
 * Function to calculate a 22th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_22 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_22 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_6 (x, p + 23)));
}

/**
 * Function to calculate a 23th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_23 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_23 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_5 (x, p + 24)));
}

/**
 * Function to calculate a 24th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_24 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_24 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_4 (x, p + 25)));
}

/**
 * Function to calculate a 25th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_25 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_25 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_3 (x, p + 26)));
}

/**
 * Function to calculate a 26th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_26 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_26 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_2 (x, p + 27)));
}

/**
 * Function to calculate a 27th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_27 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_27 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_2xf64_polynomial_1 (x, p + 28)));
}

/**
 * Function to calculate a 1st+28th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_2xf64_rational_29_28 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_2xf64_polynomial_28 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[29])));
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_expm1wc (const float64x2_t x)
///< float64x2_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return vmulq_f64 (x, jbm_2xf64_rational_8_2 (x, K_EXPM1WC_F64));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (float64x2_t).
 *
 * \return function value.
 */
static inline float64x2_t
jbm_2xf64_exp2wc (const float64x2_t x)
                  ///< float64x2_t vector \f$\in[\frac12,1]\f$.
{
  return jbm_2xf64_rational_9_4 (x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_2xf64 and
 * jbm_2xf64_exp2n functions.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_exp2 (const float64x2_t x)    ///< float64x2_t vector.
{
  float64x2_t y, f, z;
  int64x2_t i;
  y = vrndmq_f64 (x);
  f = vsubq_f64 (x, y);
  i = vcvtq_s64_f64 (y);
  z = jbm_2xf64_exp2n (i);
  return vmulq_f64 (z, jbm_2xf64_exp2wc (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_2xf64_exp2 function.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_exp (const float64x2_t x)     ///< float64x2_t vector.
{
  return jbm_2xf64_exp2 (vmulq_f64 (x, vdupq_n_f64 (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_2xf64_exp2
 * function (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_exp10 (const float64x2_t x)   ///< float64x2_t vector.
{
  return jbm_2xf64_exp2 (vmulq_f64 (x, vdupq_n_f64 (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_2xf64_expm1wc and
 * jbm_2xf64_exp functions (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_expm1 (const float64x2_t x)   ///< float64x2_t vector.
{
  return vbslq_f64 (vcltq_f64 (jbm_2xf64_abs (x),
                               vdupq_n_f64 (M_LN2 / 2.)),
                    jbm_2xf64_expm1wc (x),
                    vsubq_f64 (jbm_2xf64_exp (x), vdupq_n_f64 (1.)));
}

/**
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_log2wc (const float64x2_t x)
///< float64x2_t vector \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$.
{
  return vmulq_f64 (x, jbm_2xf64_rational_11_5 (x, K_LOG2WC_F64));
}

/**
 * Function to calculate the function log2(x) using jbm_logwc_2xf64 and
 * jbm_2xf64_frexp
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_log2 (const float64x2_t x)    ///< float64x2_t vector.
{
  float64x2_t y;
  int64x2_t e;
  y = jbm_2xf64_log2wc (jbm_2xf64_frexp (x, &e));
  y = vaddq_f64 (y, vcvtq_f64_s64 (e));
  y = vbslq_f64 (vcgtzq_f64 (x), vdupq_n_f64 (-INFINITY), y);
  return vbslq_f64 (vcltzq_f64 (x), y, vdupq_n_f64 (NAN));
}

/**
 * Function to calculate the function log(x) using jbm_2xf64_log2 (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_log (const float64x2_t x)     ///< float64x2_t vector.
{
  return vmulq_f64 (jbm_2xf64_log2 (x), vdupq_n_f64 (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_2xf64_log2 (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_log10 (const float64x2_t x)   ///< float64x2_t vector.
{
  return vmulq_f64 (jbm_2xf64_log2 (x), vdupq_n_f64 (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (float64x2_t).
 *
 * \return function value (float64x2_t) (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_pown (const float64x2_t x,    ///< float64x2_t vector.
                int e)          ///< exponent (int).
{
  float64x2_t f, xn;
  unsigned int i;
  f = vdupq_n_f64 (1.);
  if (e < 0)
    xn = jbm_2xf64_reciprocal (x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_2xf64_sqr (xn))
    if (i & 1)
      f = vmulq_f64 (f, xn);
  return f;
}

/**
 * Function to calculate the function f64 using the jbm_2xf64_exp2 and
 * jbm_2xf64_log2 functions.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_pow (const float64x2_t x,     ///< float64x2_t vector.
               const float64x2_t e)  ///< exponent (float64x2_t).
{
  return jbm_2xf64_exp2 (vmulq_f64 (e, jbm_2xf64_log2 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_2xf64_abs and
 * jbm_2xf64_pow functions (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_cbrt (const float64x2_t x)    ///< float64x2_t vector.
{
  float64x2_t f;
  f = jbm_2xf64_pow (jbm_2xf64_abs (x), vdupq_n_f64 (1. / 3.));
  return vbslq_f64 (vcltzq_f64 (x), f, jbm_2xf64_opposite (f));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (float64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_sinwc (const float64x2_t x)
                 ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return vmulq_f64 (x, jbm_2xf64_polynomial_6 (jbm_2xf64_sqr (x), K_SINWC_F64));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_coswc (const float64x2_t x)
                 ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_2xf64_polynomial_6 (jbm_2xf64_sqr (x), K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_2xf64_sinwc approximation (float64x2_t).
 */
static inline void
jbm_2xf64_sincoswc (const float64x2_t x,
                    ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    float64x2_t *s,
                    ///< pointer to the f64 function value (float64x2_t).
                    float64x2_t *c)
                    ///< pointer to the f64 function value (float64x2_t).
{
  *s = jbm_2xf64_sinwc (x);
  *c = jbm_2xf64_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (float64x2_t).
 *
 * \return reduced vector (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_trig (const float64x2_t x,    ///< float64x2_t vector.
                int64x2_t *q)   ///< quadrant (float64x2_ti).
{
  float64x2_t y;
  y = vrndnq_f64 (vmulq_f64 (x, vdupq_n_f64 (1. / M_PI_2)));
  *q = vcvtq_s64_f64 (y);
  return vfmsq_f64 (x, y, vdupq_n_f64 (M_PI_2));
}

/**
 * Function to calculate the function sin(x) from jbm_2xf64_sinwc and
 * jbm_2xf64_coswc approximations.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_sin (const float64x2_t x)     ///< float64x2_t vector.
{
  const float64x2_t pi2 = vdupq_n_f64 (2. * M_PI);
  float64x2_t y, s;
  y = jbm_2xf64_mod1 (x, 2. * M_PI);
  s = jbm_2xf64_sinwc (vsubq_f64 (y, pi2));
  s = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (7. * M_PI_4)),
                 jbm_2xf64_opposite
                 (jbm_2xf64_coswc
                  (vsubq_f64 (vdupq_n_f64 (3. * M_PI_2), y))), s);
  s = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (5. * M_PI_4)),
                 jbm_2xf64_sinwc (vsubq_f64 (vdupq_n_f64 (M_PI), y)), s);
  s = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (3. * M_PI_4)),
                 jbm_2xf64_coswc (vsubq_f64 (vdupq_n_f64 (M_PI_2), y)), s);
  return vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (M_PI_4)),
                    jbm_2xf64_sinwc (y), s);
}

/**
 * Function to calculate the function cos(x) from jbm_2xf64_sinwc and
 * jbm_2xf64_coswc approximations (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_cos (const float64x2_t x)     ///< float64x2_t vector.
{
  const float64x2_t pi2 = vdupq_n_f64 (2. * M_PI);
  float64x2_t y, c;
  y = jbm_2xf64_mod1 (x, 2. * M_PI);
  c = jbm_2xf64_coswc (vsubq_f64 (y, pi2));
  c = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (7. * M_PI_4)),
                 jbm_2xf64_sinwc (vsubq_f64 (y, vdupq_n_f64 (3. * M_PI_2))), c);
  c = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (5. * M_PI_4)),
                 jbm_2xf64_opposite
                 (jbm_2xf64_coswc (vsubq_f64 (vdupq_n_f64 (M_PI), y))), c);
  c = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (3. * M_PI_4)),
                 jbm_2xf64_sinwc (vsubq_f64 (vdupq_n_f64 (M_PI_2), y)), c);
  return vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (M_PI_4)),
                    jbm_2xf64_coswc (y), c);

}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_2xf64_sinwc
 * and jbm_2xf64_coswc approximations (float64x2_t).
 */
static inline void
jbm_2xf64_sincos (const float64x2_t x,
                  ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  float64x2_t *s,
                  ///< pointer to the f64 function value (float64x2_t).
                  float64x2_t *c)
                  ///< pointer to the f64 function value (float64x2_t).
{
  const float64x2_t pi2 = vdupq_n_f64 (2. * M_PI);
  float64x2_t y, s1, c1, s2, c2;
  uint64x2_t m;
  y = jbm_2xf64_mod1 (x, 2. * M_PI);
  jbm_2xf64_sincoswc (vsubq_f64 (y, pi2), &s1, &c1);
  jbm_2xf64_sincoswc (vsubq_f64 (y, vdupq_n_f64 (3. * M_PI_2)), &c2, &s2);
  m = vcltq_f64 (y, vdupq_n_f64 (7. * M_PI_4));
  s1 = vbslq_f64 (m, jbm_2xf64_opposite (s2), s1);
  c1 = vbslq_f64 (m, c2, c1);
  jbm_2xf64_sincoswc (vsubq_f64 (vdupq_n_f64 (M_PI), y), &s2, &c2);
  m = vcltq_f64 (y, vdupq_n_f64 (5. * M_PI_4));
  s1 = vbslq_f64 (m, s2, s1);
  c1 = vbslq_f64 (m, jbm_2xf64_opposite (c2), c1);
  jbm_2xf64_sincoswc (vsubq_f64 (vdupq_n_f64 (M_PI_2), y), &c2, &s2);
  m = vcltq_f64 (y, vdupq_n_f64 (3. * M_PI_4));
  s1 = vbslq_f64 (m, s2, s1);
  c1 = vbslq_f64 (m, c2, c1);
  jbm_2xf64_sincoswc (y, &s2, &c2);
  m = vcltq_f64 (y, vdupq_n_f64 (M_PI_4));
  *s = vbslq_f64 (m, s2, s1);
  *c = vbslq_f64 (m, c2, c1);
}

/**
 * Function to calculate the function tan(x) from jbm_2xf64_sinwc and
 * jbm_2xf64_coswc approximations.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_tan (const float64x2_t x)     ///< float64x2_t vector.
{
  float64x2_t s, c;
  jbm_2xf64_sincos (x, &s, &c);
  return vdivq_f64 (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in [-1,1]
 * (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_atanwc (const float64x2_t x)
                  ///< float64x2_t vector \f$\in\left[-1,1\right]\f$.
{
  return
    vmulq_f64 (x, jbm_2xf64_rational_11_5 (jbm_2xf64_sqr (x), K_ATANWC_F64));
}

/**
 * Function to calculate the function atan(x) using the jbm_2xf64_atanwc
 * function (float64x2_t).
 *
 * \return function value (float64x2_t in [-pi/2,pi/2]).
 */
static inline float64x2_t
jbm_2xf64_atan (const float64x2_t x)    ///< double number.
{
  float64x2_t f, ax;
  uint64x2_t m;
  ax = jbm_2xf64_abs (x);
  m = vcgtq_f64 (ax, vdupq_n_f64 (1.));
  ax = vbslq_f64 (m, jbm_2xf64_reciprocal (ax), ax);
  f = jbm_2xf64_atanwc (ax);
  f = vbslq_f64 (m, vsubq_f64 (vdupq_n_f64 (M_PI_2), f), f);
  return vbslq_f64 (vcltzq_f64 (x), jbm_2xf64_opposite (f), f);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_2xf64_atan
 * function (float64x2_t).
 *
 * \return function value (float64x2_t in [-pi,pi]).
 */
static inline float64x2_t
jbm_2xf64_atan2 (const float64x2_t y,   ///< float64x2_t y component.
                 const float64x2_t x)   ///< float64x2_t x component.
{
  float64x2_t f, pi;
  uint64x2_t mx, my;
  pi = vdupq_n_f64 (M_PI);
  f = jbm_2xf64_atan (vdivq_f64 (y, x));
  mx = vcltzq_f64 (x);
  my = vcltzq_f64 (y);
  f = vbslq_f64 (vandq_u64 (my, mx), vsubq_f64 (f, pi), f);
  return vbslq_f64 (vbicq_u64 (my, mx), vaddq_f64 (f, pi), f);
}

/**
 * Function to calculate the function asin(x) using the jbm_2xf64_atan function
 * (float64x2_t).
 *
 * \return function value (float64x2_t in [-pi/2,pi/2]).
 */
static inline float64x2_t
jbm_2xf64_asin (const float64x2_t x)    ///< float64x2_t number.
{
  return
    jbm_2xf64_atan (vdivq_f64 (x, vsqrtq_f64 (vfmsq_f64 (vdupq_n_f64 (1.),
                                                         x, x))));
}

/**
 * Function to calculate the function acos(x) using the jbm_2xf64_atan function
 * (float64x2_t).
 *
 * \return function value (float64x2_t in [0,pi]).
 */
static inline float64x2_t
jbm_2xf64_acos (const float64x2_t x)    ///< float64x2_t number.
{
  float64x2_t f;
  f =
    jbm_2xf64_atan (vdivq_f64
                    (vsqrtq_f64 (vfmsq_f64 (vdupq_n_f64 (1.), x, x)), x));
  return vbslq_f64 (vcltq_f64 (x, vdupq_n_f64 (0.)),
                    vaddq_f64 (f, vdupq_n_f64 (M_PI)), f);

}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_sinh (const float64x2_t x)    ///< float64x2_t number.
{
  float64x2_t f;
  f = jbm_2xf64_exp (x);
  return vmulq_f64 (vdupq_n_f64 (0.5), vsubq_f64 (f, jbm_2xf64_reciprocal (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_cosh (const float64x2_t x)    ///< float64x2_t number.
{
  float64x2_t f;
  f = jbm_2xf64_exp (x);
  return vmulq_f64 (vdupq_n_f64 (0.5), vaddq_f64 (f, jbm_2xf64_reciprocal (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_tanh (const float64x2_t x)    ///< float64x2_t number.
{
  float64x2_t f, fi;
  f = jbm_2xf64_exp (x);
  fi = jbm_2xf64_reciprocal (f);
  f = vdivq_f64 (vsubq_f64 (f, fi), vaddq_f64 (f, fi));
  f = vbslq_f64 (vcgtq_f64 (x, vdupq_n_f64 (JBM_DBL_MAX_E_EXP)),
                 vdupq_n_f64 (1.), f);
  return vbslq_f64 (vcltq_f64 (x, vdupq_n_f64 (-JBM_DBL_MAX_E_EXP)),
                    vdupq_n_f64 (-1.), f);

}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_asinh (const float64x2_t x)   ///< float64x2_t number.
{
  return
    jbm_2xf64_log (vaddq_f64
                   (x, vsqrtq_f64 (vmlaq_f64 (vdupq_n_f64 (1.), x, x))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_acosh (const float64x2_t x)   ///< float64x2_t number.
{
  return
    jbm_2xf64_log
    (vaddq_f64 (x, vsqrtq_f64 (jbm_2xf64_opposite (vmlsq_f64 (vdupq_n_f64 (1.),
                                                              x, x)))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_atanh (const float64x2_t x)   ///< float64x2_t number.
{
  float64x2_t u;
  u = vdupq_n_f64 (1.);
  return vmulq_f64 (vdupq_n_f64 (0.5),
                    jbm_2xf64_log (vdivq_f64 (vaddq_f64 (u, x),
                                              vsubq_f64 (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (float64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_erfwc (const float64x2_t x)
                 ///< float64x2_t vector \f$\in\left[-1,1\right]\f$.
{
  return vmulq_f64 (x, jbm_2xf64_rational_9_4 (jbm_2xf64_sqr (x), K_ERFWC_F64));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (float64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_erfcwc (const float64x2_t x)
                  ///< float64x2_t vector \f$\in\left[1,\infty\right]\f$.
{
  float64x2_t f, x2;
  x2 = jbm_2xf64_sqr (x);
  f = vmulq_f64 (jbm_2xf64_rational_16_8 (jbm_2xf64_reciprocal (x),
                                          K_ERFCWC_F64),
                 vdivq_f64 (x, jbm_2xf64_exp (x2)));
  return vbslq_f64 (vcgtq_f64 (x, vdupq_n_f64 (K_ERFC_MAX_F64)),
                    vdupq_n_f64 (0.), f);

}

/**
 * Function to calculate the function erf(x) using jbm_2xf64_erfwc and
 * jbm_2xf64_erfcwc
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_erf (const float64x2_t x)     ///< float64x2_t vector.
{
  float64x2_t ax, u, f;
  ax = jbm_2xf64_abs (x);
  u = vdupq_n_f64 (1.);
  f = vmulq_f64 (vdivq_f64 (x, ax), vsubq_f64 (u, jbm_2xf64_erfcwc (ax)));
  return vbslq_f64 (vcltq_f64 (ax, u), jbm_2xf64_erfwc (x), f);
}

/**
 * Function to calculate the function erfc(x) using jbm_2xf64_erfwc and
 * jbm_2xf64_erfcwc
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_2xf64_erfc (const float64x2_t x)    ///< float64x2_t vector.
{
  float64x2_t ax, u, f;
  ax = jbm_2xf64_abs (x);
  u = vdupq_n_f64 (1.);
  f = vsubq_f64 (u, vmulq_f64 (vdivq_f64 (x, ax),
                               vsubq_f64 (u, jbm_2xf64_erfcwc (ax))));
  return vbslq_f64 (vcltq_f64 (ax, u), vsubq_f64 (u, jbm_2xf64_erfwc (x)), f);

}

/**
 * Function to calculate the solution of a float64x2_t vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return float64x2_t vector of solution values.
 */
static inline float64x2_t
jbm_solve_quadratic_reduced_2xf64 (float64x2_t a,
///< float64x2_t vector of 1st order coefficient of the equations.
                                   float64x2_t b,
///< float64x2_t vector of 0th order coefficient of the equations.
                                   const float64x2_t x1,
///< float64x2_t vector of left limits of the solution intervals.
                                   const float64x2_t x2)
///< float64x2_t vector of right limits of the solution intervals.
{
  float64x2_t k1, k2;
  k1 = vdupq_n_f64 (-0.5);
  a = vmulq_f64 (a, k1);
  b = vsqrtq_f64 (vsubq_f64 (jbm_2xf64_sqr (a), b));
  k1 = vaddq_f64 (a, b);
  k2 = vsubq_f64 (a, b);
  k1 = vbslq_f64 (vcltq_f64 (k1, x1), k2, k1);
  return vbslq_f64 (vcgtq_f64 (k1, x2), k2, k1);
}

/**
 * Function to calculate the solution of a float64x2_t vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return float64x2_t vector of solution values.
 */
static inline float64x2_t
jbm_2xf64_solve_quadratic (const float64x2_t a,
///< float64x2_t vector of 2nd order coefficient of the equations.
                           const float64x2_t b,
///< float64x2_t vector of 1st order coefficient of the equations.
                           const float64x2_t c,
///< float64x2_t vector of 0th order coefficient of the equations.
                           const float64x2_t x1,
///< float64x2_t vector of left limits of the solution intervals.
                           const float64x2_t x2)
///< float64x2_t vector of right limits of the solution intervals.
{
  float64x2_t k1, k2;
  k1 = jbm_solve_quadratic_reduced_2xf64 (vdivq_f64 (b, a), vdivq_f64 (c, a),
                                          x1, x2);
  k2 = vdivq_f64 (jbm_2xf64_opposite (c), b);
  return vbslq_f64 (jbm_2xf64_small (a), k2, k1);
}

/**
 * Function to calculate the solution of a float64x2_t vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return float64x2_t vector of solution values.
 */
static inline float64x2_t
jbm_solve_cubic_reduced_2xf64 (const float64x2_t a,
                               ///< 2nd order coefficient of the equation.
                               const float64x2_t b,
                               ///< 1st order coefficient of the equation.
                               const float64x2_t c,
                               ///< 0th order coefficient of the equation.
                               const float64x2_t x1,
                               ///< left limit of the solution interval.
                               const float64x2_t x2)
                               ///< right limit of the solution interval.
{
  float64x2_t a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2, c_3;
  c2p_3 = vdupq_n_f64 (2. * M_PI / 3.);
  c_2 = vdupq_n_f64 (0.5);
  c_3 = vdupq_n_f64 (1. / 3.);
  a3 = vmulq_f64 (a, c_3);
  k0 = vmulq_f64 (a3, a3);
  k1 = vmlsq_f64 (k0, b, c_3);
  k0 = vmlsq_f64 (vmulq_f64 (a3, k0), vmlsq_f64 (c, b, a3), c_2);
  k3 = vmulq_f64 (k1, vmulq_f64 (k1, k1));
  k2 = vmlaq_f64 (k0, k0, k3);
  l1 = vsqrtq_f64 (jbm_2xf64_opposite (k1));
  l0 = vmulq_f64 (jbm_2xf64_acos (vdivq_f64 (k0, k3)), c_3);
  l1 = vaddq_f64 (l1, l1);
  l2 = vmlsq_f64 (a3, l1, jbm_2xf64_cos (k0));
  l3 = vmlsq_f64 (a3, l1, jbm_2xf64_cos (vaddq_f64 (l0, c2p_3)));
  l3 = vbslq_f64 (vorrq_u64 (vcltq_f64 (l2, x1), vcgtq_f64 (l2, x2)), l2, l3);
  l4 = vmlsq_f64 (a, l1, jbm_2xf64_cos (vsubq_f64 (l0, c2p_3)));
  l4 = vbslq_f64 (vorrq_u64 (vcltq_f64 (l3, x1), vcgtq_f64 (l3, x2)), l3, l4);
  k1 = vsqrtq_f64 (k2);
  l5 = vaddq_f64 (k0, k1);
  l5 = jbm_2xf64_cbrt (k2);
  k0 = vsubq_f64 (k0, k1);
  l5 = vaddq_f64 (l5, vsubq_f64 (jbm_2xf64_cbrt (k0), a3));
  return vbslq_f64 (vcltzq_f64 (k2), l5, l4);
}

/**
 * Function to calculate the solution of a float64x2_t vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return float64x2_t vector of solution values.
 */
static inline float64x2_t
jbm_2xf64_solve_cubic (float64x2_t a,
///< float64x2_t vector of 3rd order coefficient of the equations.
                       float64x2_t b,
///< float64x2_t vector of 2nd order coefficient of the equations.
                       float64x2_t c,
///< float64x2_t vector of 1st order coefficient of the equations.
                       float64x2_t d,
///< float64x2_t vector of 0th order coefficient of the equations.
                       float64x2_t x1,
///< float64x2_t vector of left limits of the solution intervals.
                       float64x2_t x2)
///< float64x2_t vector of right limits of the solution intervals.
{
  return
    vbslq_f64 (jbm_2xf64_small (a),
               jbm_2xf64_solve_quadratic (b, c, d, x1, x2),
               jbm_solve_cubic_reduced_2xf64 (vdivq_f64 (b, a),
                                              vdivq_f64 (c, a),
                                              vdivq_f64 (d, a), x1, x2));

}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_total (const float64x2_t d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const float64x2_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return vdupq_n_f64 (0.);
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_null (const float64x2_t d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const float64x2_t d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return vdupq_n_f64 (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_centred (const float64x2_t d1,
                                ///< 1st flux limiter function parameter.
                                const float64x2_t d2)
                              ///< 2nd flux limiter function parameter.
{
  return vbslq_f64 (jbm_2xf64_small (d2), vdupq_n_f64 (0.), vdivq_f64 (d1, d2));

}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_superbee (const float64x2_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float64x2_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vdivq_f64 (d1, d2);
  r = vmaxq_f64 (vminq_f64 (jbm_2xf64_dbl (r), vdupq_n_f64 (1.)),
                 vminq_f64 (r, vdupq_n_f64 (2.)));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_minmod (const float64x2_t d1,
                               ///< 1st flux limiter function parameter.
                               const float64x2_t d2)
                             ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vminq_f64 (vdivq_f64 (d1, d2), vdupq_n_f64 (1.));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_VanLeer (const float64x2_t d1,
                                ///< 1st flux limiter function parameter.
                                const float64x2_t d2)
                              ///< 2nd flux limiter function parameter.
{
  float64x2_t r, k;
  r = vdivq_f64 (d1, d2);
  k = jbm_2xf64_abs (r);
  r = vdivq_f64 (vaddq_f64 (r, k), vaddq_f64 (vdupq_n_f64 (1.), k));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_VanAlbada (const float64x2_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const float64x2_t d2)
                                ///< 2nd flux limiter function parameter.
{
  float64x2_t r, k;
  r = vdivq_f64 (d1, d2);
  k = jbm_2xf64_sqr (r);
  r = vdivq_f64 (vaddq_f64 (r, k), vaddq_f64 (vdupq_n_f64 (1.), k));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_minsuper (const float64x2_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float64x2_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vminq_f64 (vdivq_f64 (d1, d2), vdupq_n_f64 (2.));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_supermin (const float64x2_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float64x2_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vdivq_f64 (d1, d2);
  r = vminq_f64 (jbm_2xf64_dbl (r), vdupq_n_f64 (1.));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_monotonized_central (const float64x2_t d1,
///< 1st flux limiter function parameter.
                                            const float64x2_t d2)
///< 2nd flux limiter function parameter.
{
  float64x2_t r, rm;
  r = vdivq_f64 (d1, d2);
  rm = vmulq_f64 (vdupq_n_f64 (0.5), vaddq_f64 (r, vdupq_n_f64 (1.)));
  rm = vbslq_f64 (vcltq_f64 (r, vdupq_n_f64 (3.)), vdupq_n_f64 (2.), rm);
  rm = vbslq_f64 (vcgtq_f64 (r, vdupq_n_f64 (1. / 3.)), rm, jbm_2xf64_dbl (r));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    rm, vdupq_n_f64 (0.));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter_mean (const float64x2_t d1,
                             ///< 1st flux limiter function parameter.
                             const float64x2_t d2)
                           ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vmulq_f64 (vdupq_n_f64 (0.5),
                 vaddq_f64 (vdupq_n_f64 (1.), vdivq_f64 (d1, d2)));
  return vbslq_f64 (vcgtq_f64 (vmulq_f64 (d1, d2), vdupq_n_f64 (DBL_EPSILON)),
                    r, vdupq_n_f64 (0.));
}

/**
 * Function to do a flux limiter function (float64x2_t).
 *
 * \return flux limiter function value.
 */
static inline float64x2_t
jbm_2xf64_flux_limiter (const float64x2_t d1,
                        ///< 1st flux limiter function parameter.
                        const float64x2_t d2,
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
 * defined in an interval (float64x2_t).
 *
 * \return float64x2_t vector of integral values.
 */
static inline float64x2_t
jbm_2xf64_integral (float64x2_t (*f) (float64x2_t),
                    ///< pointer to the function to integrate.
                    const float64x2_t x1,       ///< left limit of the interval.
                    const float64x2_t x2)       ///< right limit of the interval.
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
  float64x2_t k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  float64x2_t k2, f1, f2;
#endif
  unsigned int i;
  h = vdupq_n_f64 (0.5);
  dx = vmulq_f64 (h, vsubq_f64 (x2, x1));
  x = vmulq_f64 (h, vaddq_f64 (x2, x1));
  k = vdupq_n_f64 (a[0]);
  k = vmulq_f64 (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = vdupq_n_f64 (b[i]);
      k2 = vmulq_f64 (k2, dx);
      f1 = f (vsubq_f64 (x, k2));
      f2 = f (vaddq_f64 (x, k2));
      h = vdupq_n_f64 (a[i]);
      k = vmlaq_f64 (k, h, vaddq_f64 (f1, f2));
    }
#endif
  k = vmulq_f64 (k, dx);
  return k;
}

///> macro to automatize operations on one array.
#define JBM_ARRAY_OP(xr, xd, n, type, load128, store128, op128, op) \
  const unsigned int prefetch = sizeof (type) == 4 ? 64 : 32; \
  unsigned int i, j; \
  if (n > prefetch + 64 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
         j > 0; --j) \
      { \
        __builtin_prefetch((const char *) (xd + i + prefetch)); \
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
  const unsigned int prefetch = sizeof (type) == 4 ? 64 : 32; \
  unsigned int i, j; \
  if (n > prefetch + 64 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
         j > 0; --j) \
      { \
        __builtin_prefetch((const char *) (x1 + i + prefetch)); \
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
  const unsigned int prefetch = sizeof (type) == 4 ? 32 : 16; \
  unsigned int i, j; \
  if (n > prefetch + 64 / sizeof (type)) \
    for (i = 0, \
         j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
         j > 0; --j) \
      { \
        __builtin_prefetch((const char *) (x1 + i + prefetch)); \
        __builtin_prefetch((const char *) (x2 + i + prefetch)); \
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
  const unsigned int prefetch = sizeof (type) == 4 ? 64 : 32; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 64 / sizeof (type)) \
    { \
      j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
      if (j) \
        { \
          __builtin_prefetch ((const char *) (x + prefetch)); \
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
              __builtin_prefetch ((const char *) (x + i + prefetch)); \
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
  const unsigned int prefetch = sizeof (type) == 4 ? 32 : 16; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 64 / sizeof (type)) \
    { \
      j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
      if (j) \
        { \
          __builtin_prefetch ((const char *) (x1 + prefetch)); \
          __builtin_prefetch ((const char *) (x2 + prefetch)); \
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
              __builtin_prefetch ((const char *) (x1 + i + prefetch)); \
              __builtin_prefetch ((const char *) (x2 + i + prefetch)); \
              a128 = ma128 (a128, load128 (x1 + i), load128 (x2 + i)); \
              i += 16 / sizeof (type); \
              b128 = ma128 (b128, load128 (x1 + i), load128 (x2 + i)); \
              i += 16 / sizeof (type); \
              d128 = ma128 (c128, load128 (x1 + i), load128 (x2 + i)); \
              i += 16 / sizeof (type); \
              d128 = ma128 (d128, load128 (x1 + i), load128 (x2 + i)); \
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
          a128 = ma128 (a128, load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          b128 = ma128 (b128, load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          d128 = ma128 (c128, load128 (x1 + i), load128 (x2 + i)); \
          i += 16 / sizeof (type); \
          d128 = ma128 (d128, load128 (x1 + i), load128 (x2 + i)); \
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
          a128 = ma128 (a128, load128 (x1 + i), load128 (x2 + i)); \
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
  const unsigned int prefetch = sizeof (type) == 4 ? 64 : 32; \
  unsigned int i, j; \
  i = 0; \
  if (n > prefetch + 64 / sizeof (type)) \
    { \
      j = (n - prefetch - 64 / sizeof (type)) >> (2 + 8 / sizeof (type)); \
      if (j) \
        { \
          __builtin_prefetch ((const char *) (x + prefetch)); \
          mxa128 = mna128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          mxb128 = mnb128 = load128 (x + i); \
          i += 16 / sizeof (type); \
          while (--j) \
            { \
              __builtin_prefetch ((const char *) (x + i + prefetch)); \
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, vsqrtq_f32, sqrtf);
}

/**
 * Function to calculate the double of a float array.
 */
static inline void
jbm_array_f32_dbl (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_dbl,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_sqr,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_opposite,
                jbm_f32_opposite);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_reciprocal (float *restrict xr,   ///< result float array.
                          const float *restrict xd,     ///< data float array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_reciprocal,
                jbm_f32_reciprocal);
}

/**
 * Function to calculate the abs function of a float array.
 */
static inline void
jbm_array_f32_abs (float *restrict xr,  ///< result float array.
                   const float *restrict xd,    ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_abs,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_cbrt,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_exp2,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_exp,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_exp10,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_expm1,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_log2,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_log,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_log10,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_sin,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_cos,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_tan,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_asin,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_acos,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_atan,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_sinh,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_cosh,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_tanh,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_asinh,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_acosh,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_atanh,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_erf,
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
  JBM_ARRAY_OP (xr, xd, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_erfc,
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
  JBM_ARRAY_REDUCE_OP (x, n, float32x4_t, float, vld1q_f32, vaddq_f32, JBM_ADD,
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
  JBM_ARRAY_REDUCE_OP (x, n, float32x4_t, float, vld1q_f32, vmaxq_f32, fmaxf,
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
  JBM_ARRAY_REDUCE_OP (x, n, float32x4_t, float, vld1q_f32, vminq_f32, fminf,
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
  JBM_ARRAY_MAXMIN (x, n, float32x4_t, float, vld1q_f32, vmaxq_f32, fmaxf,
                    vminq_f32, fmin, jbm_4xf32_reduce_max, jbm_4xf32_reduce_min,
                    mx, mn);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, vaddq_f32, JBM_ADD);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, vsubq_f32, JBM_SUB);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, vmulq_f32, JBM_MUL);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, vdivq_f32, JBM_DIV);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, vmaxq_f32, fmaxf);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, vminq_f32, fminf);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, jbm_4xf32_mod, jbm_f32_mod);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float32x4_t, float, vld1q_f32, vst1q_f32,
                 vdupq_n_f32, jbm_4xf32_pow, jbm_f32_pow);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, vaddq_f32,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, vsubq_f32,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, vmulq_f32,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, vdivq_f32,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, vmaxq_f32, fmax);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, vminq_f32, fmin);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_mod,
                 jbm_f32_mod);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, float, vld1q_f32, vst1q_f32, jbm_4xf32_pow,
                 jbm_f32_pow);
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
  JBM_ARRAY_DOT (x1, x2, n, float32x4_t, float, vld1q_f32, vmulq_f32, vaddq_f32,
                 vmlaq_f32, jbm_4xf32_reduce_add);
}

/**
 * Function to calculate the root square of a double array.
 */
static inline void
jbm_array_f64_sqrt (double *restrict xr,        ///< result double array.
                    const double *restrict xd,  ///< data double array.
                    const unsigned int n)       ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, vsqrtq_f64, sqrt);
}

/**
 * Function to calculate the double of a double array.
 */
static inline void
jbm_array_f64_dbl (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_dbl,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_sqr,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_opposite,
                jbm_f64_opposite);
}

/**
 * Function to calculate the reciprocal of a double array.
 */
static inline void
jbm_array_f64_reciprocal (double *restrict xr,  ///< result double array.
                          const double *restrict xd,    ///< data double array.
                          const unsigned int n) ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_reciprocal,
                jbm_f64_reciprocal);
}

/**
 * Function to calculate the abs function of a double array.
 */
static inline void
jbm_array_f64_abs (double *restrict xr, ///< result double array.
                   const double *restrict xd,   ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_abs,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_cbrt,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_exp2,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_exp,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_exp10,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_expm1,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_log2,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_log,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_log10,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_sin,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_cos,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_tan,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_asin,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_acos,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_atan,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_sinh,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_cosh,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_tanh,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_asinh,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_acosh,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_atanh,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_erf,
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
  JBM_ARRAY_OP (xr, xd, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_erfc,
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
  JBM_ARRAY_REDUCE_OP (x, n, float64x2_t, double, vld1q_f64, vaddq_f64, JBM_ADD,
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
  JBM_ARRAY_REDUCE_OP (x, n, float64x2_t, double, vld1q_f64, vmaxq_f64, fmaxf,
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
  JBM_ARRAY_REDUCE_OP (x, n, float64x2_t, double, vld1q_f64, vminq_f64, fminf,
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
  JBM_ARRAY_MAXMIN (x, n, float64x2_t, double, vld1q_f64, vmaxq_f64, fmaxf,
                    vminq_f64, fmin, jbm_2xf64_reduce_max, jbm_2xf64_reduce_min,
                    mx, mn);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, vaddq_f64, JBM_ADD);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, vsubq_f64, JBM_SUB);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, vmulq_f64, JBM_MUL);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, vdivq_f64, JBM_DIV);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, vmaxq_f64, fmax);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, vminq_f64, fmin);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, jbm_2xf64_mod, jbm_f64_mod);
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
  JBM_ARRAY_OP1 (xr, x1, x2, n, float64x2_t, double, vld1q_f64, vst1q_f64,
                 vdupq_n_f64, jbm_2xf64_pow, jbm_f64_pow);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, vaddq_f64,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, vsubq_f64,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, vmulq_f64,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, vdivq_f64,
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, vmaxq_f64, fmax);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, vminq_f64, fmin);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_mod,
                 jbm_f64_mod);
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
  JBM_ARRAY_OP2 (xr, x1, x2, n, double, vld1q_f64, vst1q_f64, jbm_2xf64_pow,
                 jbm_f64_pow);
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
  JBM_ARRAY_DOT (x1, x2, n, float64x2_t, double, vld1q_f64, vmulq_f64,
                 vaddq_f64, vmlaq_f64, jbm_2xf64_reduce_add);
}

#endif
