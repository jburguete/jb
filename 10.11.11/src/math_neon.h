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
 * \file math_neon.h
 * \brief Header file with useful mathematical functions for ARM NEON.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2024, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_NEON__H
#define JB_MATH_NEON__H 1

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

// Debug functions

/*
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
 * Function to calculate the additive inverse value of a float32x4_t vector.
 *
 * \return opposite value vector (float32x4_t).
 */
static inline float32x4_t
jbm_opposite_4xf32 (const float32x4_t x)     ///< float32x4_t vector.
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
jbm_reciprocal_4xf32 (const float32x4_t x)   ///< float32x4_t vector.
{
  return vdivq_f32 (vdupq_n_f32 (1.f), x);
}

/**
 * Function to calculate the absolute value of a float32x4_t vector.
 *
 * \return absolute value vector (float32x4_t).
 */
static inline float32x4_t
jbm_abs_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  return vabsq_f32 (x);
}

/**
 * Function to calculate the hypot function (float32x4_t).
 *
 * \return function value vector (float32x4_t).
 */
static inline float32x4_t
jbm_hypot_4xf32 (const float32x4_t x,        ///< 1st float32x4_t vector.
                 const float32x4_t y)        ///< 2nd float32x4_t vector.
{
  return vsqrtq_f32 (vmlaq_f32 (vmulq_f32 (x, x), y, y));
}

/**
 * Function to calculate the rest of a division (float32x4_t).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline float32x4_t
jbm_rest_4xf32 (const float32x4_t x, ///< dividend (float32x4_t).
                const float32x4_t d) ///< divisor (float32x4_t).
{
  return vmlsq_f32 (x, vrndmq_f32 (vdivq_f32 (x, d)), d);
}

/**
 * Function to implement the standard frexp function (float32x4_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline float32x4_t
jbm_frexp_4xf32 (const float32x4_t x,        ///< float32x4_t vector.
                 int32x4_t *e)    ///< pointer to the extracted exponents vector.
{
  JBM4xF32 a, y, y2, z;
  uint32x4_t b, m1, m2, m3;
  int32x4_t e4;
  a.x = x;
  b = vdupq_n_u32 (0x7f800000);
  y.i = vandq_u32 (a.i, b);
  m1 = vceqq_u32 (y.i, b);
  m2 = vceqzq_u32 (y.i);
  y2.x = x;
  y2.i = vandq_u32 (y2.i, vdupq_n_u32 (0x007fffff));
  m3 = vceqzq_u32 (y2.i);
  y2.i = vdupq_n_u32 (0x00400000);
  z.x = vdivq_f32 (x, y2.x);
  z.i = vandq_u32 (z.i, b);
  e4 = vbslq_s32 (m2,
                  vsubq_s32 (vshrq_n_s32 (vreinterpretq_s32_u32 (z.i), 23),
                             vdupq_n_s32 (253)),
                  vsubq_s32 (vshrq_n_s32 (vreinterpretq_s32_u32 (y.i), 23),
                             vdupq_n_s32 (126)));
  y.x = vbslq_f32 (m2, vmulq_f32 (y2.x, z.x), y.x);
  e4 = vbslq_s32 (vorrq_u32 (m1, vandq_u32 (m2, m3)), vdupq_n_s32 (0), e4);
  *e = e4;
  return vbslq_f32 (m1, x, vmulq_f32 (vdupq_n_f32 (0.5f), vdivq_f32 (x, y.x)));
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (int32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_exp2n_4xf32 (int32x4_t e)     ///< exponent vector (int32x4_t).
{
  float32x4_t x;
  int32x4_t k127, kn127;
  k127 = vdupq_n_s32(127);
  kn127 = vdupq_n_s32(-127);
  x = vbslq_f32 (vcgtq_s32 (e, kn127),
                 vreinterpretq_f32_s32 (vshlq_n_s32 (vaddq_s32 (e, k127), 23)),
                 vreinterpretq_f32_s32 (vshlq_s32 (vdupq_n_s32 (0x00400000),
                                                   vsubq_s32 (kn127, e))));
  x = vbslq_f32 (vcltq_s32 (e, vdupq_n_s32 (-150)), vdupq_n_f32 (0.f), x);
  return vbslq_f32 (vcgtq_s32 (e, k127), vdupq_n_f32 (INFINITY), x);
}

/**
 * Function to implement the standard ldexp function (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_ldexp_4xf32 (const float32x4_t x,        ///< float32x4_t vector.
                 int32x4_t e)     ///< exponent vector (int32x4_t).
{
  return vmulq_f32 (x, jbm_exp2n_4xf32 (e));
}

/**
 * Function to check small float32x4_t vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline uint32x4_t
jbm_small_4xf32 (const float32x4_t x)        ///< float64x2_t vector.
{
  return vcltq_f32 (jbm_abs_4xf32 (x), vdupq_n_f32 (FLT_EPSILON));
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
jbm_modmin_4xf32 (const float32x4_t a,       ///< 1st float64x2_t vector.
                  const float32x4_t b)       ///< 2nd float64x2_t vector.
{
  float32x4_t aa, ab, y, z;
  z = vdupq_n_f32 (0.f);
  ab = vmulq_f32 (a, b);
  y = vbslq_f32 (vclezq_f32 (ab), z, a); 
  aa = jbm_abs_4xf32 (y);
  ab = jbm_abs_4xf32 (b);
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
jbm_dbl_4xf32 (const float32x4_t x)  ///< float64x2_t vector.
{
  return vaddq_f32 (x, x);
}

/**
 * Function to calculate the square of the components of a float32x4_t vector.
 *
 * \return float32x4_t vector square.
 */
static inline float32x4_t
jbm_sqr_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  return vmulq_f32 (x, x);
}

/**
 * Function to perform an extrapolation between 2 float32x4_t vectors of 2D points.
 *
 * \return float32x4_t vector of y-coordinates of the extrapolated points.
 */
static inline float32x4_t
jbm_extrapolate_4xf32 (const float32x4_t x,
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
jbm_interpolate_4xf32 (const float32x4_t x,
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
  k = jbm_extrapolate_4xf32 (x, x1, x2, y1, y2);
  k = vbslq_f32 (vcgtq_f32 (x, x1), k, y1);
  return vbslq_f32 (vcltq_f32 (x, x2), k, y2);
}

/**
 * Function to calculate the length of a float32x4_t vector of 2D segments.
 *
 * \return float32x4_t vector of segment lengths.
 */
static inline float32x4_t
jbm_v2_length_4xf32 (const float32x4_t x1,
///< float32x4_t vector of x-coordinates of the 1st points defining the segment.
                     const float32x4_t y1,
///< float32x4_t vector of y-coordinates of the 1st points defining the segment.
                     const float32x4_t x2,
///< float32x4_t vector of x-coordinates of the 2nd points defining the segment.
                     const float32x4_t y2)
///< float32x4_t vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_4xf32 (vsubq_f32 (x2, x1), vsubq_f32 (y2, y1));
}

/**
 * Function to calculate the length of a float32x4_t vector of 3D segments.
 *
 * \return float32x4_t vector of segment lengths.
 */
static inline float32x4_t
jbm_v3_length_4xf32 (const float32x4_t x1,
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
  dx = jbm_sqr_4xf32 (vsubq_f32 (x2, x1));
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
jbm_polynomial_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
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
jbm_polynomial_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_1_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 3rd order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_2_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 4th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_4_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_3_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 5th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_5_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_4_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 6th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_6_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_5_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 7th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_7_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_6_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 8th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_8_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_7_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 9th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_9_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_8_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 10th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_10_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_9_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 11th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_11_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_10_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 12th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_12_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_11_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 13th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_13_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_12_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 14th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_14_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_13_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 15th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_15_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_14_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 16th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_16_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_15_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 17th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_17_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_16_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 18th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_18_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_17_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 19th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_19_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_18_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 20th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_20_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_19_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 21th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_21_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_20_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 22th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_22_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_21_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 23th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_23_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_22_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 24th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_24_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_23_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 25th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_25_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_24_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 26th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_26_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_25_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 27th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_27_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_26_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 28th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_28_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_27_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 29th order polynomial (float32x4_t).
 *
 * \return float32x4_t vector of polynomial values.
 */
static inline float32x4_t
jbm_polynomial_29_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vmlaq_f32 (vdupq_n_f32 (p[0]), x, jbm_polynomial_28_4xf32 (x, p + 1));
}

/**
 * Function to calculate a 0th+1st order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_1_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
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
jbm_rational_2_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+1st order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_2_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[2])));
}

/**
 * Function to calculate a 0th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_3_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_3_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 1st+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_3_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[3])));
}

/**
 * Function to calculate a 0th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_4_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_4_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_4_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 1st+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_4_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[4])));
}

/**
 * Function to calculate a 0th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_5_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_5_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_5_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_5_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 1st+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_5_4_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[5])));
}

/**
 * Function to calculate a 0th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_6_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_6_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_6_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_6_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_6_4_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 1st+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_6_5_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[6])));
}

/**
 * Function to calculate a 0th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_4_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_5_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 1st+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_7_6_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[7])));
}

/**
 * Function to calculate a 0th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_4_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_5_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_6_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 1st+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_8_7_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[8])));
}

/**
 * Function to calculate a 0th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_0_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_1_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_2_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_3_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_4_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_5_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_6_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_7_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 1st+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_9_8_4xf32 (const float32x4_t x,    ///< float32x4_t vector.
                        const float *p) ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[9])));
}

/**
 * Function to calculate a 0th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 1st+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_10_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[10])));
}

/**
 * Function to calculate a 0th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 1st+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_11_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[11])));
}

/**
 * Function to calculate a 0th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 1st+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_12_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[12])));
}

/**
 * Function to calculate a 0th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 1st+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_13_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[13])));
}

/**
 * Function to calculate a 0th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 1st+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_14_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[14])));
}

/**
 * Function to calculate a 0th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 1st+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_15_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[15])));
}

/**
 * Function to calculate a 0th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 1st+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_16_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[16])));
}

/**
 * Function to calculate a 0th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 1st+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_17_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[17])));
}

/**
 * Function to calculate a 0th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 1st+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_18_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[18])));
}

/**
 * Function to calculate a 0th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 1st+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_19_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[19])));
}

/**
 * Function to calculate a 0th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 1st+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_20_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[20])));
}

/**
 * Function to calculate a 0th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 1st+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_21_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[21])));
}

/**
 * Function to calculate a 0th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 1st+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_22_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[22])));
}

/**
 * Function to calculate a 0th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 1st+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_23_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[23])));
}

/**
 * Function to calculate a 0th+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_23_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 22th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 23)));
}

/**
 * Function to calculate a 1st+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_24_23_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_23_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[24])));
}

/**
 * Function to calculate a 0th+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_24_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_23_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 22th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 23)));
}

/**
 * Function to calculate a 23th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_23_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_23_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 24)));
}

/**
 * Function to calculate a 1st+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_25_24_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_24_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[25])));
}

/**
 * Function to calculate a 0th+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_25_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_24_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_23_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 22th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 23)));
}

/**
 * Function to calculate a 23th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_23_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_23_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 24)));
}

/**
 * Function to calculate a 24th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_24_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_24_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 25)));
}

/**
 * Function to calculate a 1st+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_26_25_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_25_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[26])));
}

/**
 * Function to calculate a 0th+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_26_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_25_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_24_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_23_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 22th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 23)));
}

/**
 * Function to calculate a 23th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_23_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_23_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 24)));
}

/**
 * Function to calculate a 24th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_24_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_24_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 25)));
}

/**
 * Function to calculate a 25th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_25_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_25_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 26)));
}

/**
 * Function to calculate a 1st+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_27_26_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_26_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[27])));
}

/**
 * Function to calculate a 0th+28th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_27_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_26_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_25_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_24_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_23_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 22th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 23)));
}

/**
 * Function to calculate a 23th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_23_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_23_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 24)));
}

/**
 * Function to calculate a 24th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_24_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_24_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 25)));
}

/**
 * Function to calculate a 25th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_25_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_25_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 26)));
}

/**
 * Function to calculate a 26th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_26_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_26_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 27)));
}

/**
 * Function to calculate a 1st+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_28_27_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_27_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[28])));
}

/**
 * Function to calculate a 0th+29th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_0_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (vdupq_n_f32 (p[0]),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_28_4xf32 (x, p + 1)));
}

/**
 * Function to calculate a 1st+28th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_1_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_1_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_27_4xf32 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+27th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_2_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_2_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_26_4xf32 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+26th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_3_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_3_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_25_4xf32 (x, p + 4)));
}

/**
 * Function to calculate a 4th+25th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_4_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_4_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_24_4xf32 (x, p + 5)));
}

/**
 * Function to calculate a 5th+24th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_5_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_5_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_23_4xf32 (x, p + 6)));
}

/**
 * Function to calculate a 6th+23th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_6_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_6_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_22_4xf32 (x, p + 7)));
}

/**
 * Function to calculate a 7th+22th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_7_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_7_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_21_4xf32 (x, p + 8)));
}

/**
 * Function to calculate a 8th+21th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_8_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_8_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_20_4xf32 (x, p + 9)));
}

/**
 * Function to calculate a 9th+20th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_9_4xf32 (const float32x4_t x,   ///< float32x4_t vector.
                         const float *p)        ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_9_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_19_4xf32 (x, p + 10)));
}

/**
 * Function to calculate a 10th+19th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_10_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_10_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_18_4xf32 (x, p + 11)));
}

/**
 * Function to calculate a 11th+18th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_11_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_11_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_17_4xf32 (x, p + 12)));
}

/**
 * Function to calculate a 12th+17th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_12_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_12_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_16_4xf32 (x, p + 13)));
}

/**
 * Function to calculate a 13th+16th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_13_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_13_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_15_4xf32 (x, p + 14)));
}

/**
 * Function to calculate a 14th+15th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_14_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_14_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_14_4xf32 (x, p + 15)));
}

/**
 * Function to calculate a 15th+14th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_15_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_15_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_13_4xf32 (x, p + 16)));
}

/**
 * Function to calculate a 16th+13th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_16_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_16_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_12_4xf32 (x, p + 17)));
}

/**
 * Function to calculate a 17th+12th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_17_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_17_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_11_4xf32 (x, p + 18)));
}

/**
 * Function to calculate a 18th+11th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_18_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_18_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_10_4xf32 (x, p + 19)));
}

/**
 * Function to calculate a 19th+10th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_19_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_19_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_9_4xf32 (x, p + 20)));
}

/**
 * Function to calculate a 20th+9th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_20_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_20_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_8_4xf32 (x, p + 21)));
}

/**
 * Function to calculate a 21th+8th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_21_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_21_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_7_4xf32 (x, p + 22)));
}

/**
 * Function to calculate a 22th+7th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_22_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_22_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_6_4xf32 (x, p + 23)));
}

/**
 * Function to calculate a 23th+6th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_23_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_23_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_5_4xf32 (x, p + 24)));
}

/**
 * Function to calculate a 24th+5th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_24_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_24_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_4_4xf32 (x, p + 25)));
}

/**
 * Function to calculate a 25th+4th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_25_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_25_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_3_4xf32 (x, p + 26)));
}

/**
 * Function to calculate a 26th+3rd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_26_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_26_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_2_4xf32 (x, p + 27)));
}

/**
 * Function to calculate a 27th+2nd order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_27_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_27_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x,
                               jbm_polynomial_1_4xf32 (x, p + 28)));
}

/**
 * Function to calculate a 1st+28th order rational (float32x4_t).
 *
 * \return float32x4_t vector of rational values.
 */
static inline float32x4_t
jbm_rational_29_28_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
                          const float *p)       ///< array of coefficients.
{
  return vdivq_f32 (jbm_polynomial_28_4xf32 (x, p),
                    vmlaq_f32 (vdupq_n_f32 (1.f), x, vdupq_n_f32 (p[29])));
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_expm1wc_4xf32 (const float32x4_t x)
///< float32x4_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = 9.9999999917826835759154742878523887e-01f;
  const float a2 = -4.9999999958913417879577371439261924e-01f;
  const float a3 = 8.3333136366700581865508474051734715e-02f;
  const float a5 = -1.3833464660905326042591440964123531e-03f;
  float32x4_t x2;
  x2 = jbm_sqr_4xf32 (x);
  x2 = vmlaq_f32 (vdupq_n_f32 (a3), x2, vdupq_n_f32 (a5));
  x2 = vmlaq_f32 (vdupq_n_f32 (a2), x2, x);
  x2 = vmlaq_f32 (vdupq_n_f32 (1.f), x2, x);
  return vmulq_f32 (x, vdivq_f32 (vdupq_n_f32 (a1), x2));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (float32x4_t).
 *
 * \return function value.
 */
static inline float32x4_t
jbm_exp2wc_4xf32 (const float32x4_t x)
                  ///< float32x4_t vector \f$\in[\frac12,1]\f$.
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
  return jbm_polynomial_6_4xf32 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_4xf32 and
 * jbm_exp2n_4xf32 functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_exp2_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  float32x4_t y, f;
  y = vrndmq_f32 (x);
  f = vsubq_f32 (x, y);
  y = jbm_exp2n_4xf32 (vcvtq_s32_f32 (y));
  return vmulq_f32 (y, jbm_exp2wc_4xf32 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_4xf32 function
 * (float32x4_t).
 *
 * \return function value.
 */
static inline float32x4_t
jbm_exp_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  return jbm_exp2_4xf32 (vmulq_f32 (x, vdupq_n_f32 (M_LOG2Ef)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_4xf32
 * function (float32x4_t).
 *
 * \return function value.
 */
static inline float32x4_t
jbm_exp10_4xf32 (const float32x4_t x)        ///< float32x4_t vector.
{
  return jbm_exp2_4xf32 (vmulq_f32 (x, vdupq_n_f32 (M_LN10f / M_LN2f)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_4xf32 and
 * jbm_exp_4xf32 functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_expm1_4xf32 (const float32x4_t x)        ///< float32x4_t vector.
{
  return vbslq_f32 (vcltq_f32 (jbm_abs_4xf32 (x),
                               vdupq_n_f32 (M_LN2f / 2.f)),
                    jbm_expm1wc_4xf32 (x),
                    vsubq_f32 (jbm_exp_4xf32 (x), vdupq_n_f32 (1.f)));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_log2wc_4xf32 (const float32x4_t x)
///< float32x4_t vector \f$\in[0.5,1]\f$.
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
  return jbm_rational_6_3_4xf32 (x, a);
}

/**
 * Function to calculate the function log_2(x) using jbm_log2wc_4xf32 and
 * jbm_frexp_4xf32 (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_log2_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  float32x4_t y;
  int32x4_t e;
  y = jbm_frexp_4xf32 (x, &e);
  y = vaddq_f32 (jbm_log2wc_4xf32 (y), vcvtq_f32_s32 (e));
  y = vbslq_f32 (vcgtzq_f32 (x), y, vdupq_n_f32 (-INFINITY));
  return vbslq_f32 (vcltzq_f32 (x), vdupq_n_f32 (NAN), y);
}

/**
 * Function to calculate the function log(x) using jbm_log2_4xf32 (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_log_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  return vmulq_f32 (jbm_log2_4xf32 (x), vdupq_n_f32 (M_LN2f));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_4xf32.
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_log10_4xf32 (const float32x4_t x)        ///< float32x4_t vector.
{
  return vmulq_f32 (jbm_log2_4xf32 (x), vdupq_n_f32 (M_LN2f / M_LN10f));
}

/**
 * Function to calculate the function x^e with e an integer number (float32x4_t).
 *
 * \return function value (float32x4_t) (float32x4_t).
 */
static inline float32x4_t
jbm_pown_4xf32 (const float32x4_t x, ///< float32x4_t vector.
                int e)          ///< exponent (int).
{
  float32x4_t f, xn;
  unsigned int i;
  f = vdupq_n_f32 (1.f);
  if (e < 0)
    xn = jbm_reciprocal_4xf32 (x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_4xf32 (xn))
    if (i & 1)
      f = vmulq_f32 (f, xn);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_exp2_4xf32 and
 * jbm_log2_4xf32 functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_pow_4xf32 (const float32x4_t x,  ///< float32x4_t vector.
               const float e)   ///< exponent (float).
{
  float f;
  f = floorf (e);
  if (f == e)
    return jbm_pown_4xf32 (x, (int) e);
  return jbm_exp2_4xf32 (vmulq_f32 (vdupq_n_f32 (e), jbm_log2_4xf32 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_4xf32 and
 * jbm_pow_4xf32 functions (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_cbrt_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  float32x4_t f;
  f = jbm_abs_4xf32 (x);
  f = jbm_pow_4xf32 (x, 1.f / 3.f);
  return vbslq_f32 (vcltzq_f32 (x), f, jbm_opposite_4xf32 (f));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (float32x4_t)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_sinwc_4xf32 (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const float a[4] JB_ALIGNED = {
    9.9999999652998170520234859388240338e-01f,
    -1.6666653850132705938945722106817969e-01f,
    8.3322256622392457162205759786691734e-03f,
    -1.9524867674489682553254582414001857e-04f
  };
  return vmulq_f32 (x, jbm_polynomial_3_4xf32 (jbm_sqr_4xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (float32x4_t):
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_coswc_4xf32 (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const float a[5] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00f,
    -4.9999999965238906843549904534867220e-01f,
    4.1666653828165636463917247496043632e-02f,
    -1.3887779469291056608109602187665577e-03f,
    2.4484799013341679093941386831846651e-05f
  };
  return jbm_polynomial_4_4xf32 (jbm_sqr_4xf32 (x), a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_4xf32 approximation (float32x4_t).
 */
static inline void
jbm_sincoswc_4xf32 (const float32x4_t x,
                    ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    float32x4_t *s,  ///< pointer to the sin function value (float32x4_t).
                    float32x4_t *c)  ///< pointer to the cos function value (float32x4_t).
{
  float32x4_t s0;
  *s = s0 = jbm_sinwc_4xf32 (x);
  *c = vsqrtq_f32 (vmlsq_f32 (vdupq_n_f32 (1.f), s0, s0));
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_4xf32 and
 * jbm_coswc_4xf32 approximations (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_sin_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  float32x4_t y, s, pi2;
  pi2 = vdupq_n_f32 (2.f * M_PIf);
  y = jbm_rest_4xf32 (x, pi2);
  s = jbm_sinwc_4xf32 (vsubq_f32 (y, pi2));
  s = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (7.f * M_PI_4f)),
                 jbm_opposite_4xf32
                 (jbm_coswc_4xf32 (vsubq_f32 (vdupq_n_f32 (3.f * M_PI_2f),
                                              y))), s);
  s = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (5.f * M_PI_4f)),
                 jbm_sinwc_4xf32 (vsubq_f32 (vdupq_n_f32 (M_PIf), y)), s);
  s = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (3.f * M_PI_4f)),
                 jbm_coswc_4xf32 (vsubq_f32 (vdupq_n_f32 (M_PI_2f), y)), s);
  return vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (M_PI_4f)),
                    jbm_sinwc_4xf32 (y), s);
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_4xf32 and
 * jbm_coswc_4xf32 approximations (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_cos_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  float32x4_t y, c, pi2;
  pi2 = vdupq_n_f32 (2.f * M_PIf);
  y = jbm_rest_4xf32 (x, pi2);
  c = jbm_coswc_4xf32 (vsubq_f32 (y, pi2));
  c = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (7.f * M_PI_4f)),
                 jbm_sinwc_4xf32 (vsubq_f32 (y, vdupq_n_f32 (3.f * M_PI_2f))),
                 c);
  c = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (5.f * M_PI_4f)),
                 jbm_opposite_4xf32
                 (jbm_coswc_4xf32 (vsubq_f32 (vdupq_n_f32 (M_PIf), y))), c);
  c = vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (3.f * M_PI_4f)),
                 jbm_sinwc_4xf32 (vsubq_f32 (vdupq_n_f32 (M_PI_2f), y)), c);
  return vbslq_f32 (vcltq_f32 (y, vdupq_n_f32 (M_PI_4f)),
                    jbm_coswc_4xf32 (y), c);
                        
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_sinwc_4xf32 and jbm_coswc_4xf32 approximations (float32x4_t).
 */
static inline void
jbm_sincos_4xf32 (const float32x4_t x,
                  ///< float32x4_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  float32x4_t *s,
		  ///< pointer to the sin function value (float32x4_t).
                  float32x4_t *c)
                  ///< pointer to the cos function value (float32x4_t).
{
  float32x4_t y, pi2, s1, c1, s2, c2;
  uint32x4_t m;
  pi2 = vdupq_n_f32 (2.f * M_PIf);
  y = jbm_rest_4xf32 (x, pi2);
  jbm_sincoswc_4xf32 (vsubq_f32 (y, pi2), &s1, &c1);
  jbm_sincoswc_4xf32 (vsubq_f32 (y, vdupq_n_f32 (3.f * M_PI_2f)), &c2, &s2);
  m = vcltq_f32 (y, vdupq_n_f32 (7.f * M_PI_4f));
  s1 = vbslq_f32 (m, jbm_opposite_4xf32 (s2), s1);
  c1 = vbslq_f32 (m, c2, c1);
  jbm_sincoswc_4xf32 (vsubq_f32 (vdupq_n_f32 (M_PIf), y), &s2, &c2);
  m = vcltq_f32 (y, vdupq_n_f32 (5.f * M_PI_4f));
  s1 = vbslq_f32 (m, s2, s1);
  c1 = vbslq_f32 (m, jbm_opposite_4xf32 (c2), c1);
  jbm_sincoswc_4xf32 (vsubq_f32 (vdupq_n_f32 (M_PI_2f), y), &c2, &s2);
  m = vcltq_f32 (y, vdupq_n_f32 (3.f * M_PI_4f));
  s1 = vbslq_f32 (m, s2, s1);
  c1 = vbslq_f32 (m, c2, c1);
  jbm_sincoswc_4xf32 (y, &s2, &c2);
  m = vcltq_f32 (y, vdupq_n_f32 (M_PI_4f));
  *s = vbslq_f32 (m, s2, s1);
  *c = vbslq_f32 (m, c2, c1);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_4xf32 function
 * (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_tan_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  float32x4_t s, c;
  jbm_sincos_4xf32 (x, &s, &c);
  return vdivq_f32 (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_atanwc0_4xf32 (const float32x4_t x)
                   ///< float32x4_t vector \f$\in\left[0,\frac12\right]\f$.
{
  const float a[4] JB_ALIGNED = {
    9.9999984048730143841335295268244848e-01f,
    4.9566847198521400589504493089955823e-01f,
    8.2898705878810240458099950004542931e-01f,
    7.6658333542753920209846592962853791e-02f
  };
  return vmulq_f32 (x, jbm_rational_3_1_4xf32 (jbm_sqr_4xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (float32x4_t).
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_atanwc1_4xf32 (const float32x4_t x)
                   ///< float32x4_t vector \f$\in\left[\frac12,1\right]\f$.
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
  return jbm_rational_7_3_4xf32 (vsubq_f32 (x, vdupq_n_f32 (1.f)), a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_4xf32 and
 * jbm_atanwc1_4xf32 functions (float32x4_t).
 *
 * \return function value (in [-pi/2,pi/2]) (float32x4_t).
 */
static inline float32x4_t
jbm_atan_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  float32x4_t f, ax;
  uint32x4_t m;
  ax = jbm_abs_4xf32 (x);
  m = vcgtq_f32 (ax, vdupq_n_f32 (1.5f));
  ax = vbslq_f32 (m, jbm_reciprocal_4xf32 (ax), ax);
  f = vbslq_f32 (vcgtq_f32 (ax, vdupq_n_f32 (0.5f)),
                 jbm_atanwc1_4xf32 (ax), jbm_atanwc0_4xf32 (ax));
  f = vbslq_f32 (m, vsubq_f32 (vdupq_n_f32 (M_PI_2f), f), f);
  return vbslq_f32 (vcltzq_f32 (x), jbm_opposite_4xf32 (f), f); 
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_4xf32
 * function (float32x4_t).
 *
 * \return function value (in [-pi,pi]) (float32x4_t).
 */
static inline float32x4_t
jbm_atan2_4xf32 (const float32x4_t y,        ///< float32x4_t y component.
                 const float32x4_t x)        ///< float32x4_t x component.
{
  float32x4_t f, pi;
  uint32x4_t mx, my;
  pi = vdupq_n_f32 (M_PIf);
  f = jbm_atan_4xf32 (vdivq_f32 (y, x));
  mx = vcltzq_f32 (x);
  my = vcltzq_f32 (y);
  f = vbslq_f32 (vandq_u32 (my, mx), vsubq_f32 (f, pi), f);
  return vbslq_f32 (vbicq_u32 (my, mx), vaddq_f32 (f, pi), f);
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_4xf32 function
 * (float32x4_t).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline float32x4_t
jbm_asin_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  return
    jbm_atan_4xf32 (vdivq_f32
                    (x, vsqrtq_f32 (vfmsq_f32 (vdupq_n_f32 (1.f), x, x))));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_4xf32 function
 * (float32x4_t).
 *
 * \return function value (in [0,pi]) (float32x4_t).
 */
static inline float32x4_t
jbm_acos_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  float32x4_t f;
  f =
    jbm_atan_4xf32 (vdivq_f32
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
jbm_sinh_4xf32 (const float32x4_t x) ///< float32x4_t number.
{
  float32x4_t f;
  f = jbm_exp_4xf32 (x);
  return vmulq_f32 (vdupq_n_f32 (0.5f),
                     vsubq_f32 (f, jbm_reciprocal_4xf32 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_cosh_4xf32 (const float32x4_t x) ///< float32x4_t number.
{
  float32x4_t f;
  f = jbm_exp_4xf32 (x);
  return vmulq_f32 (vdupq_n_f32 (0.5f),
                     vaddq_f32 (f, jbm_reciprocal_4xf32 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_tanh_4xf32 (const float32x4_t x) ///< float32x4_t number.
{
  float32x4_t f, fi;
  f = jbm_exp_4xf32 (x);
  fi = jbm_reciprocal_4xf32 (f);
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
jbm_asinh_4xf32 (const float32x4_t x)        ///< float32x4_t number.
{
  return
    jbm_log_4xf32 (vaddq_f32
                   (x, vsqrtq_f32 (vmlaq_f32 (vdupq_n_f32 (1.f), x, x))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_acosh_4xf32 (const float32x4_t x)        ///< float32x4_t number.
{
  return
    jbm_log_4xf32 (vaddq_f32 (x, vsqrtq_f32 (vmlsq_f32 (vdupq_n_f32 (1.f),
                                                        x, x))));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_atanh_4xf32 (const float32x4_t x)        ///< float32x4_t number.
{
  float32x4_t u;
  u = vdupq_n_f32 (1.f);
  return vmulq_f32 (vdupq_n_f32 (0.5f),
                     jbm_log_4xf32 (vdivq_f32 (vaddq_f32 (u, x),
                                                vsubq_f32 (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (float32x4_t)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_erfwc_4xf32 (const float32x4_t x)
                 ///< float32x4_t vector \f$\in\left[-1,1\right]\f$.
{
  const float a[6] JB_ALIGNED = {
    1.1283791671633124547603970137089329e+00f,
    1.1356247077387072221530473806173895e-01f,
    3.3606359392673594485175487779855494e-02f,
    4.3397545597876753616401102540952801e-01f,
    7.4441296041206635020857929305718177e-02f,
    5.2260592856163505486272407800095742e-03f
  };
  return vmulq_f32 (x, jbm_rational_5_2_4xf32 (jbm_sqr_4xf32 (x), a));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (float32x4_t)
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_erfcwc_4xf32 (const float32x4_t x)
                  ///< float32x4_t vector \f$\in\left[1,\infty\right]\f$.
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
  float32x4_t f, x2;
  x2 = jbm_sqr_4xf32 (x);
  f = vdivq_f32 (jbm_rational_6_3_4xf32 (jbm_reciprocal_4xf32 (x2), a),
                  vmulq_f32 (x, jbm_exp_4xf32 (x2)));
  return vbslq_f32 (vcgtq_f32 (x, vdupq_n_f32 (m)), vdupq_n_f32 (0.f), f);
                        
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_4xf32 and
 * jbm_erfcwc_4xf32
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_erf_4xf32 (const float32x4_t x)  ///< float32x4_t vector.
{
  float32x4_t ax, u, f;
  ax = jbm_abs_4xf32 (x);
  u = vdupq_n_f32 (1.f);
  f = vmulq_f32 (vdivq_f32 (x, ax), vsubq_f32 (u, jbm_erfcwc_4xf32 (ax)));
  return vbslq_f32 (vcltq_f32 (ax, u), jbm_erfwc_4xf32 (x), f);

}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_4xf32 and
 * jbm_erfcwc_4xf32
 *
 * \return function value (float32x4_t).
 */
static inline float32x4_t
jbm_erfc_4xf32 (const float32x4_t x) ///< float32x4_t vector.
{
  float32x4_t ax, u, f;
  ax = jbm_abs_4xf32 (x);
  u = vdupq_n_f32 (1.f);
  f = vsubq_f32 (u, vmulq_f32 (vdivq_f32 (x, ax),
                                 vsubq_f32 (u, jbm_erfcwc_4xf32 (ax))));
  return vbslq_f32 (vcltq_f32 (ax, u), vsubq_f32 (u, jbm_erfwc_4xf32 (x)), f);
                        
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
  b = vsqrtq_f32 (vsubq_f32 (jbm_sqr_4xf32 (a), b));
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
jbm_solve_quadratic_4xf32 (const float32x4_t a,
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
  k2 = vdivq_f32 (jbm_opposite_4xf32 (c), b);
  return vbslq_f32 (jbm_small_4xf32 (a), k2, k1);
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
  l1 = vsqrtq_f32 (jbm_opposite_4xf32 (k1));
  l0 = vmulq_f32 (jbm_acos_4xf32 (vdivq_f32 (k0, k3)), c_3);
  l1 = vaddq_f32 (l1, l1);
  l2 = vmlsq_f32 (a3, l1, jbm_cos_4xf32 (k0));
  l3 = vmlsq_f32 (a3, l1, jbm_cos_4xf32 (vaddq_f32 (l0, c2p_3)));
  l3 = vbslq_f32 (vorrq_u32 (vcltq_f32 (l2, x1), vcgtq_f32 (l2, x2)), l2, l3);
  l4 = vmlsq_f32 (a, l1, jbm_cos_4xf32 (vsubq_f32 (l0, c2p_3)));
  l4 = vbslq_f32 (vorrq_u32 (vcltq_f32 (l3, x1), vcgtq_f32 (l3, x2)), l3, l4);
  k1 = vsqrtq_f32 (k2);
  l5 = vaddq_f32 (k0, k1);
  l5 = jbm_cbrt_4xf32 (k2);
  k0 = vsubq_f32 (k0, k1);
  l5 = vaddq_f32 (l5, vsubq_f32 (jbm_cbrt_4xf32 (k0), a3));
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
jbm_solve_cubic_4xf32 (float32x4_t a,
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
    vbslq_f32 (jbm_small_4xf32 (a),
               jbm_solve_quadratic_4xf32 (b, c, d, x1, x2),
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
jbm_flux_limiter_total_4xf32 (const float32x4_t d1 __attribute__((unused)),
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
jbm_flux_limiter_null_4xf32 (const float32x4_t d1 __attribute__((unused)),
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
jbm_flux_limiter_centred_4xf32 (const float32x4_t d1,
                                ///< 1st flux limiter function parameter.
                                const float32x4_t d2)
                              ///< 2nd flux limiter function parameter.
{
  return vbslq_f32 (jbm_small_4xf32 (d2),
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
jbm_flux_limiter_superbee_4xf32 (const float32x4_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float32x4_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vdivq_f32 (d1, d2);
  r = vmaxq_f32 (vminq_f32 (jbm_dbl_4xf32 (r), vdupq_n_f32 (1.f)),
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
jbm_flux_limiter_minmod_4xf32 (const float32x4_t d1,
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
jbm_flux_limiter_VanLeer_4xf32 (const float32x4_t d1,
                                ///< 1st flux limiter function parameter.
                                const float32x4_t d2)
                              ///< 2nd flux limiter function parameter.
{
  float32x4_t r, k;
  r = vdivq_f32 (d1, d2);
  k = jbm_abs_4xf32 (r);
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
jbm_flux_limiter_VanAlbada_4xf32 (const float32x4_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const float32x4_t d2)
                                ///< 2nd flux limiter function parameter.
{
  float32x4_t r, k;
  r = vdivq_f32 (d1, d2);
  k = jbm_sqr_4xf32 (r);
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
jbm_flux_limiter_minsuper_4xf32 (const float32x4_t d1,
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
jbm_flux_limiter_supermin_4xf32 (const float32x4_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float32x4_t d2)
                                 ///< 2nd flux limiter function parameter.
{
  float32x4_t r;
  r = vdivq_f32 (d1, d2);
  r = vminq_f32 (jbm_dbl_4xf32 (r), vdupq_n_f32 (1.f));
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
jbm_flux_limiter_monotonized_central_4xf32 (const float32x4_t d1,
///< 1st flux limiter function parameter.
                                            const float32x4_t d2)
///< 2nd flux limiter function parameter.
{
  float32x4_t r, rm;
  r = vdivq_f32 (d1, d2);
  rm = vmulq_f32 (vdupq_n_f32 (0.5f), vaddq_f32 (r, vdupq_n_f32 (1.f)));
  rm = vbslq_f32 (vcltq_f32 (r, vdupq_n_f32 (3.f)), rm, vdupq_n_f32 (2.f));
  rm = vbslq_f32 (vcgtq_f32 (r, vdupq_n_f32 (1.f / 3.f)),
                  jbm_dbl_4xf32 (r), rm);
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
jbm_flux_limiter_mean_4xf32 (const float32x4_t d1,
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
jbm_flux_limiter_4xf32 (const float32x4_t d1,
                        ///< 1st flux limiter function parameter.
                        const float32x4_t d2,
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
 * defined in an interval (float32x4_t).
 *
 * \return float32x4_t vector of integral values.
 */
static inline float32x4_t
jbm_integral_4xf32 (float32x4_t (*f) (float32x4_t),
                    ///< pointer to the function to integrate.
                    const float32x4_t x1,    ///< left limit of the interval.
                    const float32x4_t x2)    ///< right limit of the interval.
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

/**
 * Function to calculate the additive inverse value of a float64x2_t vector.
 *
 * \return negative value vector (float64x2_t).
 */
static inline float64x2_t
jbm_opposite_2xf64 (const float64x2_t x)    ///< float64x2_t vector.
{
  return vnegq_f64(x);
}

/**
 * Function to calculate the multiplicative inverse value of a float64x2_t vector.
 *
 * \return reciprocal value vector (float64x2_t).
 */
static inline float64x2_t
jbm_reciprocal_2xf64 (const float64x2_t x)  ///< float64x2_t vector.
{
  return vdivq_f64 (vdupq_n_f64 (1.), x);
}

/**
 * Function to calculate the absolute value of a float64x2_t vector.
 *
 * \return absolute value vector.
 */
static inline float64x2_t
jbm_abs_2xf64 (const float64x2_t x)
{
  return vabsq_f64 (x);
}

/**
 * Function to calculate the hypot function (float64x2_t).
 *
 * \return function value vector (float64x2_t).
 */
static inline float64x2_t
jbm_hypot_2xf64 (const float64x2_t x,       ///< 1st float64x2_t vector.
                 const float64x2_t y)       ///< 2nd float64x2_t vector.
{
  return vsqrtq_f64 (vmlaq_f64 (vmulq_f64 (x, x), y, y));
}

/**
 * Function to calculate the rest of a division (float64x2_t).
 *
 * \return rest value (in [0,|divisor|) interval) (float64x2_t).
 */
static inline float64x2_t
jbm_rest_2xf64 (const float64x2_t x,        ///< dividend (float64x2_t).
                const float64x2_t d)        ///< divisor (float64x2_t).
{
  return vmlsq_f64 (x, vrndmq_f64 (vdivq_f64 (x, d)), d);
}

/**
 * Function to implement the standard frexp function (float64x2_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline float64x2_t
jbm_frexp_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
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
jbm_exp2n_2xf64 (int64x2_t e)     ///< exponent vector (int64x2_t).
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
jbm_ldexp_2xf64 (const float64x2_t x,       ///< float64x2_t vector.
                 int64x2_t e)     ///< exponent vector (int64x2_t).
{
  return vmulq_f64 (x, jbm_exp2n_2xf64 (e));
}

/**
 * Function to check small float64x2_t vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline uint64x2_t
jbm_small_2xf64 (const float64x2_t x)       ///< float64x2_t vector.
{
  return vcltq_f64 (jbm_abs_2xf64 (x), vdupq_n_f64 (FLT_EPSILON));
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
jbm_modmin_2xf64 (const float64x2_t a,      ///< 1st float64x2_t vector.
                  const float64x2_t b)      ///< 2nd float64x2_t vector.
{
  float64x2_t aa, ab, y, z;
  z = vdupq_n_f64 (0.);
  ab = vmulq_f64 (a, b);
  y = vbslq_f64 (vcleq_f64 (ab, z), z, a); 
  aa = jbm_abs_2xf64 (y);
  ab = jbm_abs_2xf64 (b);
  return vbslq_f64 (vcgtq_f64 (aa, ab), b, y);
}

/**
 * Function to interchange 2 float64x2_t numbers.
 */
static inline void
jbm_change_2xf64 (float64x2_t *restrict a,  ///< 1st float64x2_t vector pointer.
                  float64x2_t *restrict b)  ///< 2nd float64x2_t vector pointer.
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
jbm_dbl_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  return vaddq_f64 (x, x);
}

/**
 * Function to calculate the square of the components of a float64x2_t vector.
 *
 * \return float64x2_t vector square.
 */
static inline float64x2_t
jbm_sqr_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  return vmulq_f64 (x, x);
}

/**
 * Function to perform an extrapolation between 2 float64x2_t vectors of 2D points.
 *
 * \return float64x2_t vector of y-coordinates of the extrapolated points.
 */
static inline float64x2_t
jbm_extrapolate_2xf64 (const float64x2_t x,
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
  return vmlaq_f64 (y1, d, vdivq_f64 (vsubq_f64 (y2, y1),
                                      vsubq_f64 (x2, x1)));
}

/**
 * Function to perform an interpolation between 2 float64x2_t vectors of 2D points.
 *
 * \return float64x2_t vector of y-coordinates of the interpolated points.
 */
static inline float64x2_t
jbm_interpolate_2xf64 (const float64x2_t x,
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
  k = jbm_extrapolate_2xf64 (x, x1, x2, y1, y2);
  k = vbslq_f64 (vcgtq_f64 (x, x1), k, y1);
  return vbslq_f64 (vcltq_f64 (x, x2), k, y2);
}

/**
 * Function to calculate the length of a float64x2_t vector of 2D segments.
 *
 * \return float64x2_t vector of segment lengths.
 */
static inline float64x2_t
jbm_v2_length_2xf64 (const float64x2_t x1,
///< float64x2_t vector of x-coordinates of the 1st points defining the segment.
                     const float64x2_t y1,
///< float64x2_t vector of y-coordinates of the 1st points defining the segment.
                     const float64x2_t x2,
///< float64x2_t vector of x-coordinates of the 2nd points defining the segment.
                     const float64x2_t y2)
///< float64x2_t vector of y-coordinates of the 2nd points defining the segment.
{
  return jbm_hypot_2xf64 (vsubq_f64 (x2, x1), vsubq_f64 (y2, y1));
}

/**
 * Function to calculate the length of a float64x2_t vector of 3D segments.
 *
 * \return float64x2_t vector of segment lengths.
 */
static inline float64x2_t
jbm_v3_length_2xf64 (const float64x2_t x1,
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
  dx = jbm_sqr_2xf64 (vsubq_f64 (x2, x1));
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
jbm_polynomial_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
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
jbm_polynomial_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_1_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 3rd order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_2_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 4th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_4_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_3_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 5th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_5_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_4_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 6th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_6_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_5_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 7th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_7_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_6_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 8th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_8_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_7_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 9th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_9_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_8_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 10th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_10_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_9_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 11th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_11_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_10_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 12th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_12_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_11_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 13th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_13_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_12_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 14th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_14_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_13_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 15th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_15_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_14_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 16th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_16_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_15_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 17th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_17_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_16_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 18th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_18_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_17_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 19th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_19_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_18_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 20th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_20_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_19_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 21th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_21_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_20_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 22th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_22_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_21_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 23th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_23_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_22_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 24th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_24_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_23_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 25th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_25_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_24_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 26th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_26_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_25_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 27th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_27_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_26_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 28th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_28_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_27_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 29th order polynomial (float64x2_t).
 *
 * \return float64x2_t vector of polynomial values.
 */
static inline float64x2_t
jbm_polynomial_29_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vmlaq_f64 (vdupq_n_f64 (p[0]), x, jbm_polynomial_28_2xf64 (x, p + 1));
}

/**
 * Function to calculate a 0th+1st order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_1_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
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
jbm_rational_2_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+1st order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_2_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[2])));
}

/**
 * Function to calculate a 0th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_3_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_3_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 1st+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_3_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[3])));
}

/**
 * Function to calculate a 0th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_4_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_4_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_4_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 1st+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_4_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[4])));
}

/**
 * Function to calculate a 0th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_5_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_5_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_5_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_5_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 1st+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_5_4_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[5])));
}

/**
 * Function to calculate a 0th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_6_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_6_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_6_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_6_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_6_4_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 1st+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_6_5_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[6])));
}

/**
 * Function to calculate a 0th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_4_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_5_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 1st+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_7_6_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[7])));
}

/**
 * Function to calculate a 0th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_4_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_5_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_6_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 1st+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_8_7_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[8])));
}

/**
 * Function to calculate a 0th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_0_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_1_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_2_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_3_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_4_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_5_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_6_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_7_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 1st+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_9_8_2xf64 (const float64x2_t x,    ///< float64x2_t vector.
                        const double *p)        ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[9])));
}

/**
 * Function to calculate a 0th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 1st+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_10_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[10])));
}

/**
 * Function to calculate a 0th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 1st+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_11_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[11])));
}

/**
 * Function to calculate a 0th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 1st+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_12_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[12])));
}

/**
 * Function to calculate a 0th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 1st+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_13_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[13])));
}

/**
 * Function to calculate a 0th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 1st+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_14_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[14])));
}

/**
 * Function to calculate a 0th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 1st+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_15_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[15])));
}

/**
 * Function to calculate a 0th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 1st+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_16_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[16])));
}

/**
 * Function to calculate a 0th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 1st+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_17_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[17])));
}

/**
 * Function to calculate a 0th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 1st+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_18_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[18])));
}

/**
 * Function to calculate a 0th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 1st+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_19_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[19])));
}

/**
 * Function to calculate a 0th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 1st+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_20_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[20])));
}

/**
 * Function to calculate a 0th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 1st+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_21_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[21])));
}

/**
 * Function to calculate a 0th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 1st+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_22_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[22])));
}

/**
 * Function to calculate a 0th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 1st+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_23_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[23])));
}

/**
 * Function to calculate a 0th+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_23_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 22th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 23)));
}

/**
 * Function to calculate a 1st+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_24_23_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_23_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[24])));
}

/**
 * Function to calculate a 0th+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_24_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_23_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 22th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 23)));
}

/**
 * Function to calculate a 23th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_23_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_23_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 24)));
}

/**
 * Function to calculate a 1st+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_25_24_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_24_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[25])));
}

/**
 * Function to calculate a 0th+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_25_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_24_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_23_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 22th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 23)));
}

/**
 * Function to calculate a 23th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_23_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_23_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 24)));
}

/**
 * Function to calculate a 24th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_24_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_24_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 25)));
}

/**
 * Function to calculate a 1st+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_26_25_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_25_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[26])));
}

/**
 * Function to calculate a 0th+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_26_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_25_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_24_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_23_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 22th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 23)));
}

/**
 * Function to calculate a 23th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_23_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_23_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 24)));
}

/**
 * Function to calculate a 24th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_24_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_24_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 25)));
}

/**
 * Function to calculate a 25th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_25_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_25_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 26)));
}

/**
 * Function to calculate a 1st+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_27_26_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_26_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[27])));
}

/**
 * Function to calculate a 0th+28th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_27_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_26_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_25_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_24_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_23_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 22th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 23)));
}

/**
 * Function to calculate a 23th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_23_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_23_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 24)));
}

/**
 * Function to calculate a 24th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_24_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_24_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 25)));
}

/**
 * Function to calculate a 25th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_25_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_25_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 26)));
}

/**
 * Function to calculate a 26th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_26_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_26_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 27)));
}

/**
 * Function to calculate a 1st+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_28_27_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_27_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[28])));
}

/**
 * Function to calculate a 0th+29th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_0_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (vdupq_n_f64 (p[0]),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_28_2xf64 (x, p + 1)));
}

/**
 * Function to calculate a 1st+28th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_1_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_1_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_27_2xf64 (x, p + 2)));
}

/**
 * Function to calculate a 2nd+27th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_2_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_2_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_26_2xf64 (x, p + 3)));
}

/**
 * Function to calculate a 3rd+26th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_3_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_3_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_25_2xf64 (x, p + 4)));
}

/**
 * Function to calculate a 4th+25th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_4_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_4_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_24_2xf64 (x, p + 5)));
}

/**
 * Function to calculate a 5th+24th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_5_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_5_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_23_2xf64 (x, p + 6)));
}

/**
 * Function to calculate a 6th+23th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_6_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_6_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_22_2xf64 (x, p + 7)));
}

/**
 * Function to calculate a 7th+22th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_7_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_7_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_21_2xf64 (x, p + 8)));
}

/**
 * Function to calculate a 8th+21th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_8_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_8_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_20_2xf64 (x, p + 9)));
}

/**
 * Function to calculate a 9th+20th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_9_2xf64 (const float64x2_t x,   ///< float64x2_t vector.
                         const double *p)       ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_9_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_19_2xf64 (x, p + 10)));
}

/**
 * Function to calculate a 10th+19th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_10_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_10_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_18_2xf64 (x, p + 11)));
}

/**
 * Function to calculate a 11th+18th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_11_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_11_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_17_2xf64 (x, p + 12)));
}

/**
 * Function to calculate a 12th+17th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_12_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_12_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_16_2xf64 (x, p + 13)));
}

/**
 * Function to calculate a 13th+16th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_13_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_13_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_15_2xf64 (x, p + 14)));
}

/**
 * Function to calculate a 14th+15th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_14_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_14_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_14_2xf64 (x, p + 15)));
}

/**
 * Function to calculate a 15th+14th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_15_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_15_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_13_2xf64 (x, p + 16)));
}

/**
 * Function to calculate a 16th+13th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_16_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_16_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_12_2xf64 (x, p + 17)));
}

/**
 * Function to calculate a 17th+12th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_17_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_17_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_11_2xf64 (x, p + 18)));
}

/**
 * Function to calculate a 18th+11th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_18_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_18_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_10_2xf64 (x, p + 19)));
}

/**
 * Function to calculate a 19th+10th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_19_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_19_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_9_2xf64 (x, p + 20)));
}

/**
 * Function to calculate a 20th+9th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_20_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_20_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_8_2xf64 (x, p + 21)));
}

/**
 * Function to calculate a 21th+8th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_21_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_21_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_7_2xf64 (x, p + 22)));
}

/**
 * Function to calculate a 22th+7th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_22_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_22_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_6_2xf64 (x, p + 23)));
}

/**
 * Function to calculate a 23th+6th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_23_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_23_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_5_2xf64 (x, p + 24)));
}

/**
 * Function to calculate a 24th+5th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_24_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_24_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_4_2xf64 (x, p + 25)));
}

/**
 * Function to calculate a 25th+4th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_25_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_25_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_3_2xf64 (x, p + 26)));
}

/**
 * Function to calculate a 26th+3rd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_26_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_26_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_2_2xf64 (x, p + 27)));
}

/**
 * Function to calculate a 27th+2nd order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_27_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_27_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x,
                               jbm_polynomial_1_2xf64 (x, p + 28)));
}

/**
 * Function to calculate a 1st+28th order rational (float64x2_t).
 *
 * \return float64x2_t vector of rational values.
 */
static inline float64x2_t
jbm_rational_29_28_2xf64 (const float64x2_t x,  ///< float64x2_t vector.
                          const double *p)      ///< array of coefficients.
{
  return vdivq_f64 (jbm_polynomial_28_2xf64 (x, p),
                    vmlaq_f64 (vdupq_n_f64 (1.), x, vdupq_n_f64 (p[29])));
}
/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_expm1wc_2xf64 (const float64x2_t x)
///< float64x2_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const double a1 = 9.9999999999999999866523626874215789e-01;
  const double a3 = 2.4998453858981619674396608301250598e-02;
  const double a4 = -4.9999999999999999933261730198779978e-01;
  const double a5 = 1.0833178719231388723914535942973379e-01;
  const double a6 = -1.2499226929490809837198234785821115e-02;
  const double a7 = 6.9431559947707471609539363612700440e-04;
  const double a9 = -1.6512957626515476078093301716091145e-06;
  float64x2_t x2;
  x2 = jbm_sqr_2xf64 (x);
  return
    vdivq_f64 (vmulq_f64 (x,
                          vmlaq_f64 (vdupq_n_f64 (a1), x2, vdupq_n_f64 (a3))),
               vmlaq_f64
               (vdupq_n_f64 (1.), x,
                vmlaq_f64
                (vdupq_n_f64 (a4), x,
                 vmlaq_f64
                 (vdupq_n_f64 (a5), x,
                  vmlaq_f64
                  (vdupq_n_f64 (a6), x,
                   vmlaq_f64 (vdupq_n_f64 (a7), x2, vdupq_n_f64 (a9)))))));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (float64x2_t).
 *
 * \return function value.
 */
static inline float64x2_t
jbm_exp2wc_2xf64 (const float64x2_t x)
                  ///< float64x2_t vector \f$\in[\frac12,1]\f$.
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
  return jbm_rational_10_5_2xf64 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_2xf64 and
 * jbm_exp2n_2xf64 functions.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_exp2_2xf64 (const float64x2_t x)        ///< float64x2_t vector.
{
  float64x2_t y, f, z;
  int64x2_t i;
  y = vrndmq_f64 (x);
  f = vsubq_f64 (x, y);
  i = vcvtq_s64_f64 (y);
  z = jbm_exp2n_2xf64 (i);
  return vmulq_f64 (z, jbm_exp2wc_2xf64 (f));
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_2xf64 function.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_exp_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  return jbm_exp2_2xf64 (vmulq_f64 (x, vdupq_n_f64 (M_LOG2E)));
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_2xf64
 * function (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_exp10_2xf64 (const float64x2_t x)       ///< float64x2_t vector.
{
  return jbm_exp2_2xf64 (vmulq_f64 (x, vdupq_n_f64 (M_LN10 / M_LN2)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_2xf64 and
 * jbm_exp_2xf64 functions (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_expm1_2xf64 (const float64x2_t x)       ///< float64x2_t vector.
{
  return vbslq_f64 (vcltq_f64 (jbm_abs_2xf64 (x),
                               vdupq_n_f64 (M_LN2 / 2.)),
                    jbm_expm1wc_2xf64 (x),
                    vsubq_f64 (jbm_exp_2xf64 (x), vdupq_n_f64 (1.)));
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_log2wc_2xf64 (const float64x2_t x)
///< float64x2_t vector \f$\in[0.5,1]\f$.
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
  return jbm_rational_14_7_2xf64 (x, a);
}

/**
 * Function to calculate the function log2(x) using jbm_logwc_2xf64 and
 * jbm_frexp_2xf64
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_log2_2xf64 (const float64x2_t x)        ///< float64x2_t vector.
{
  float64x2_t y;
  int64x2_t e;
  y = jbm_log2wc_2xf64 (jbm_frexp_2xf64 (x, &e));
  y = vaddq_f64 (y, vcvtq_f64_s64 (e));
  y = vbslq_f64 (vcgtzq_f64 (x), vdupq_n_f64 (-INFINITY), y);
  return vbslq_f64 (vcltzq_f64 (x), y, vdupq_n_f64 (NAN));
}

/**
 * Function to calculate the function log(x) using jbm_log2_2xf64 (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_log_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  return vmulq_f64 (jbm_log2_2xf64 (x), vdupq_n_f64 (M_LN2));
}

/**
 * Function to calculate the function log10(x) using jbm_log2_2xf64 (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_log10_2xf64 (const float64x2_t x)       ///< float64x2_t vector.
{
  return vmulq_f64 (jbm_log2_2xf64 (x), vdupq_n_f64 (M_LN2 / M_LN10));
}

/**
 * Function to calculate the function x^e with e an integer number (float64x2_t).
 *
 * \return function value (float64x2_t) (float64x2_t).
 */
static inline float64x2_t
jbm_pown_2xf64 (const float64x2_t x,        ///< float64x2_t vector.
                int e)          ///< exponent (int).
{
  float64x2_t f, xn;
  unsigned int i;
  f = vdupq_n_f64 (1.);
  if (e < 0)
    xn = jbm_reciprocal_2xf64 (x);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_2xf64 (xn))
    if (i & 1)
      f = vmulq_f64 (f, xn);
  return f;
}

/**
 * Function to calculate the function f32 using the jbm_exp2_2xf64 and
 * jbm_log2_2xf64 functions.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_pow_2xf64 (const float64x2_t x, ///< float64x2_t vector.
               const double e)  ///< exponent (float64x2_t).
{
  double f;
  f = floor (e);
  if (f == e)
    return jbm_pown_2xf64 (x, (int) e);
  return jbm_exp2_2xf64 (vmulq_f64 (vdupq_n_f64 (e), jbm_log2_2xf64 (x)));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_2xf64 and
 * jbm_pow_2xf64 functions (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_cbrt_2xf64 (const float64x2_t x)        ///< float64x2_t vector.
{
  float64x2_t f;
  f = jbm_abs_2xf64 (x);
  f = jbm_pow_2xf64 (x, 1. / 3.);
  return vbslq_f64 (vcltzq_f64 (x), f, jbm_opposite_2xf64 (f));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (float64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_sinwc_2xf64 (const float64x2_t x)
                 ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
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
  return vmulq_f64 (x, jbm_polynomial_6_2xf64 (jbm_sqr_2xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_coswc_2xf64 (const float64x2_t x)
                 ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
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
  return jbm_polynomial_7_2xf64 (jbm_sqr_2xf64 (x), a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_2xf64 approximation (float64x2_t).
 */
static inline void
jbm_sincoswc_2xf64 (const float64x2_t x,
                    ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    float64x2_t *s,
                    ///< pointer to the f32 function value (float64x2_t).
                    float64x2_t *c)
                    ///< pointer to the f32 function value (float64x2_t).
{
  float64x2_t s0;
  *s = s0 = jbm_sinwc_2xf64 (x);
  *c = vsqrtq_f64 (vmlsq_f64 (vdupq_n_f64 (1.), x, x)); 
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_2xf64 and
 * jbm_coswc_2xf64 approximations.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_sin_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  float64x2_t y, s, pi2;
  pi2 = vdupq_n_f64 (2. * M_PI);
  y = jbm_rest_2xf64 (x, pi2);
  s = jbm_sinwc_2xf64 (vsubq_f64 (y, pi2));
  s = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (7. * M_PI_4)),
                 jbm_opposite_2xf64
                 (jbm_coswc_2xf64
                  (vsubq_f64 (vdupq_n_f64 (3. * M_PI_2), y))), s);
  s = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (5. * M_PI_4)),
                 jbm_sinwc_2xf64 (vsubq_f64 (vdupq_n_f64 (M_PI), y)), s);
  s = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (3. * M_PI_4)),
                 jbm_coswc_2xf64 (vsubq_f64 (vdupq_n_f64 (M_PI_2), y)), s);
  return vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (M_PI_4)),
                    jbm_sinwc_2xf64 (y), s);
                        
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_2xf64 and
 * jbm_coswc_2xf64 approximations (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_cos_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  float64x2_t y, c, pi2;
  pi2 = vdupq_n_f64 (2. * M_PI);
  y = jbm_rest_2xf64 (x, pi2);
  c = jbm_coswc_2xf64 (vsubq_f64 (y, pi2));
  c = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (7. * M_PI_4)),
                 jbm_sinwc_2xf64 (vsubq_f64 (y, vdupq_n_f64 (3. * M_PI_2))), c);
  c = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (5. * M_PI_4)),
                 jbm_opposite_2xf64
                 (jbm_coswc_2xf64 (vsubq_f64 (vdupq_n_f64 (M_PI), y))), c);
  c = vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (3. * M_PI_4)),
                 jbm_sinwc_2xf64 (vsubq_f64 (vdupq_n_f64 (M_PI_2), y)), c);
  return vbslq_f64 (vcltq_f64 (y, vdupq_n_f64 (M_PI_4)),
                    jbm_coswc_2xf64 (y), c);
                        
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sinwc_2xf64
 * and jbm_coswc_2xf64 approximations (float64x2_t).
 */
static inline void
jbm_sincos_2xf64 (const float64x2_t x,
                  ///< float64x2_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  float64x2_t *s,
                  ///< pointer to the f32 function value (float64x2_t).
                  float64x2_t *c)
                  ///< pointer to the f32 function value (float64x2_t).
{
  float64x2_t y, pi2, s1, c1, s2, c2;
  uint64x2_t m;
  pi2 = vdupq_n_f64 (2. * M_PI);
  y = jbm_rest_2xf64 (x, pi2);
  jbm_sincoswc_2xf64 (vsubq_f64 (y, pi2), &s1, &c1);
  jbm_sincoswc_2xf64 (vsubq_f64 (y, vdupq_n_f64 (3. * M_PI_2)), &c2, &s2);
  m = vcltq_f64 (y, vdupq_n_f64 (7. * M_PI_4));
  s1 = vbslq_f64 (m, jbm_opposite_2xf64 (s2), s1);
  c1 = vbslq_f64 (m, c2, c1);
  jbm_sincoswc_2xf64 (vsubq_f64 (vdupq_n_f64 (M_PI), y), &s2, &c2);
  m = vcltq_f64 (y, vdupq_n_f64 (5. * M_PI_4));
  s1 = vbslq_f64 (m, s2, s1);
  c1 = vbslq_f64 (m, jbm_opposite_2xf64 (c2), c1);
  jbm_sincoswc_2xf64 (vsubq_f64 (vdupq_n_f64 (M_PI_2), y), &c2, &s2);
  m = vcltq_f64 (y, vdupq_n_f64 (3. * M_PI_4));
  s1 = vbslq_f64 (m, s2, s1);
  c1 = vbslq_f64 (m, c2, c1);
  jbm_sincoswc_2xf64 (y, &s2, &c2);
  m = vcltq_f64 (y, vdupq_n_f64 (M_PI_4));
  *s = vbslq_f64 (m, s2, s1);
  *c = vbslq_f64 (m, c2, c1);
}

/**
 * Function to calculate the function tan(x) from jbm_sinwc_2xf64 and
 * jbm_coswc_2xf64 approximations.
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_tan_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  float64x2_t s, c;
  jbm_sincos_2xf64 (x, &s, &c);
  return vdivq_f64 (s, c);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_atanwc0_2xf64 (const float64x2_t x)
                   ///< float64x2_t vector \f$\in\left[0,\frac12\right]\f$.
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
  return vmulq_f64 (x, jbm_rational_9_4_2xf64 (jbm_sqr_2xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (float64x2_t).
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_atanwc1_2xf64 (const float64x2_t x)
                   ///< float64x2_t vector \f$\in\left[\frac12,1\right]\f$.
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
  return jbm_rational_16_8_2xf64 (vsubq_f64 (x, vdupq_n_f64 (1.)), a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_2xf64 and
 * jbm_atanwc1_2xf64 functions (float64x2_t).
 *
 * \return function value (float64x2_t in [-pi/2,pi/2]).
 */
static inline float64x2_t
jbm_atan_2xf64 (const float64x2_t x)        ///< double number.
{
  float64x2_t f, ax;
  uint64x2_t m;
  ax = jbm_abs_2xf64 (x);
  m = vcgtq_f64 (ax, vdupq_n_f64 (1.5));
  ax = vbslq_f64 (m, jbm_reciprocal_2xf64 (ax), ax);
  f = vbslq_f64 (vcgtq_f64 (ax, vdupq_n_f64 (0.5)),
                 jbm_atanwc1_2xf64 (ax), jbm_atanwc0_2xf64 (ax));
  f = vbslq_f64 (m, vsubq_f64 (vdupq_n_f64 (M_PI_2), f), f);
  return vbslq_f64 (vcltzq_f64 (x), jbm_opposite_2xf64 (f), f);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_2xf64
 * function (float64x2_t).
 *
 * \return function value (float64x2_t in [-pi,pi]).
 */
static inline float64x2_t
jbm_atan2_2xf64 (const float64x2_t y,       ///< float64x2_t y component.
                 const float64x2_t x)       ///< float64x2_t x component.
{
  float64x2_t f, pi;
  uint64x2_t mx, my;
  pi = vdupq_n_f64 (M_PI);
  f = jbm_atan_2xf64 (vdivq_f64 (y, x));
  mx = vcltzq_f64 (x);
  my = vcltzq_f64 (y);
  f = vbslq_f64 (vandq_u64 (my, mx), vsubq_f64 (f, pi), f);
  return vbslq_f64 (vbicq_u64 (my, mx), vaddq_f64 (f, pi), f);
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_2xf64 function
 * (float64x2_t).
 *
 * \return function value (float64x2_t in [-pi/2,pi/2]).
 */
static inline float64x2_t
jbm_asin_2xf64 (const float64x2_t x)        ///< float64x2_t number.
{
  return
    jbm_atan_2xf64 (vdivq_f64(x, vsqrtq_f64 (vfmsq_f64 (vdupq_n_f64 (1.),
                                                        x, x)))); 
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_2xf64 function
 * (float64x2_t).
 *
 * \return function value (float64x2_t in [0,pi]).
 */
static inline float64x2_t
jbm_acos_2xf64 (const float64x2_t x)        ///< float64x2_t number.
{
  float64x2_t f;
  f =
    jbm_atan_2xf64 (vdivq_f64
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
jbm_sinh_2xf64 (const float64x2_t x)        ///< float64x2_t number.
{
  float64x2_t f;
  f = jbm_exp_2xf64 (x);
  return vmulq_f64 (vdupq_n_f64 (0.5),
                     vsubq_f64 (f, jbm_reciprocal_2xf64 (f)));
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_cosh_2xf64 (const float64x2_t x)        ///< float64x2_t number.
{
  float64x2_t f;
  f = jbm_exp_2xf64 (x);
  return vmulq_f64 (vdupq_n_f64 (0.5),
                     vaddq_f64 (f, jbm_reciprocal_2xf64 (f)));
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_tanh_2xf64 (const float64x2_t x)        ///< float64x2_t number.
{
  float64x2_t f, fi;
  f = jbm_exp_2xf64 (x);
  fi = jbm_reciprocal_2xf64 (f);
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
jbm_asinh_2xf64 (const float64x2_t x)       ///< float64x2_t number.
{
  return
    jbm_log_2xf64 (vaddq_f64
                   (x, vsqrtq_f64 (vmlaq_f64 (x, x, vdupq_n_f64 (1.)))));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_acosh_2xf64 (const float64x2_t x)       ///< float64x2_t number.
{
  return
    jbm_log_2xf64 (vaddq_f64
                   (x, vsqrtq_f64 (vmlsq_f64 (vdupq_n_f64 (1.), x, x)))); 
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_atanh_2xf64 (const float64x2_t x)       ///< float64x2_t number.
{
  float64x2_t u;
  u = vdupq_n_f64 (1.);
  return vmulq_f64 (vdupq_n_f64 (0.5),
                    jbm_log_2xf64 (vdivq_f64 (vaddq_f64 (u, x),
                                              vsubq_f64 (u, x))));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (float64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_erfwc_2xf64 (const float64x2_t x)
                 ///< float64x2_t vector \f$\in\left[-1,1\right]\f$.
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
  return vmulq_f64 (x, jbm_rational_9_4_2xf64 (jbm_sqr_2xf64 (x), a));
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (float64x2_t)
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_erfcwc_2xf64 (const float64x2_t x)
                  ///< float64x2_t vector \f$\in\left[1,\infty\right]\f$.
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
  float64x2_t f, x2;
  x2 = jbm_sqr_2xf64 (x);
  f = vdivq_f64 (jbm_rational_19_9_2xf64 (jbm_reciprocal_2xf64 (x2), a),
                  vmulq_f64 (x, jbm_exp_2xf64 (x2)));
  return vbslq_f64 (vcgtq_f64 (x, vdupq_n_f64 (m)), vdupq_n_f64 (0.), f);
                        
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_2xf64 and
 * jbm_erfcwc_2xf64
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_erf_2xf64 (const float64x2_t x) ///< float64x2_t vector.
{
  float64x2_t ax, u, f;
  ax = jbm_abs_2xf64 (x);
  u = vdupq_n_f64 (1.);
  f = vmulq_f64 (vdivq_f64 (x, ax), vsubq_f64 (u, jbm_erfcwc_2xf64 (ax)));
  return vbslq_f64 (vcltq_f64 (ax, u), jbm_erfwc_2xf64 (x), f);
}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_2xf64 and
 * jbm_erfcwc_2xf64
 *
 * \return function value (float64x2_t).
 */
static inline float64x2_t
jbm_erfc_2xf64 (const float64x2_t x)        ///< float64x2_t vector.
{
  float64x2_t ax, u, f;
  ax = jbm_abs_2xf64 (x);
  u = vdupq_n_f64 (1.);
  f = vsubq_f64 (u, vmulq_f64 (vdivq_f64 (x, ax),
                                 vsubq_f64 (u, jbm_erfcwc_2xf64 (ax))));
  return vbslq_f64 (vcltq_f64 (ax, u), vsubq_f64 (u, jbm_erfwc_2xf64 (x)), f);
                        
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
  b = vsqrtq_f64 (vsubq_f64 (jbm_sqr_2xf64 (a), b));
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
jbm_solve_quadratic_2xf64 (const float64x2_t a,
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
  k2 = vdivq_f64 (jbm_opposite_2xf64 (c), b);
  return vbslq_f64 (jbm_small_2xf64 (a), k2, k1);
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
  l1 = vsqrtq_f64 (jbm_opposite_2xf64 (k1));
  l0 = vmulq_f64 (jbm_acos_2xf64 (vdivq_f64 (k0, k3)), c_3);
  l1 = vaddq_f64 (l1, l1);
  l2 = vmlsq_f64 (a3, l1, jbm_cos_2xf64 (k0));
  l3 = vmlsq_f64 (a3, l1, jbm_cos_2xf64 (vaddq_f64 (l0, c2p_3)));
  l3 = vbslq_f64 (vorrq_u64 (vcltq_f64 (l2, x1), vcgtq_f64 (l2, x2)), l2, l3);
  l4 = vmlsq_f64 (a, l1, jbm_cos_2xf64 (vsubq_f64 (l0, c2p_3)));
  l4 = vbslq_f64 (vorrq_u64 (vcltq_f64 (l3, x1), vcgtq_f64 (l3, x2)), l3, l4);
  k1 = vsqrtq_f64 (k2);
  l5 = vaddq_f64 (k0, k1);
  l5 = jbm_cbrt_2xf64 (k2);
  k0 = vsubq_f64 (k0, k1);
  l5 = vaddq_f64 (l5, vsubq_f64 (jbm_cbrt_2xf64 (k0), a3));
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
jbm_solve_cubic_2xf64 (float64x2_t a,
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
    vbslq_f64 (jbm_small_2xf64 (a),
               jbm_solve_quadratic_2xf64 (b, c, d, x1, x2),
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
jbm_flux_limiter_total_2xf64 (const float64x2_t d1 __attribute__((unused)),
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
jbm_flux_limiter_null_2xf64 (const float64x2_t d1 __attribute__((unused)),
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
jbm_flux_limiter_centred_2xf64 (const float64x2_t d1,
                                ///< 1st flux limiter function parameter.
                                const float64x2_t d2)
                              ///< 2nd flux limiter function parameter.
{
  return vbslq_f64 (jbm_small_2xf64 (d2), vdupq_n_f64 (0.), vdivq_f64 (d1, d2));
                        
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
jbm_flux_limiter_superbee_2xf64 (const float64x2_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float64x2_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vdivq_f64 (d1, d2);
  r = vmaxq_f64 (vminq_f64 (jbm_dbl_2xf64 (r), vdupq_n_f64 (1.)),
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
jbm_flux_limiter_minmod_2xf64 (const float64x2_t d1,
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
jbm_flux_limiter_VanLeer_2xf64 (const float64x2_t d1,
                                ///< 1st flux limiter function parameter.
                                const float64x2_t d2)
                              ///< 2nd flux limiter function parameter.
{
  float64x2_t r, k;
  r = vdivq_f64 (d1, d2);
  k = jbm_abs_2xf64 (r);
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
jbm_flux_limiter_VanAlbada_2xf64 (const float64x2_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const float64x2_t d2)
                                ///< 2nd flux limiter function parameter.
{
  float64x2_t r, k;
  r = vdivq_f64 (d1, d2);
  k = jbm_sqr_2xf64 (r);
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
jbm_flux_limiter_minsuper_2xf64 (const float64x2_t d1,
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
jbm_flux_limiter_supermin_2xf64 (const float64x2_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const float64x2_t d2)
                               ///< 2nd flux limiter function parameter.
{
  float64x2_t r;
  r = vdivq_f64 (d1, d2);
  r = vminq_f64 (jbm_dbl_2xf64 (r), vdupq_n_f64 (1.));
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
jbm_flux_limiter_monotonized_central_2xf64 (const float64x2_t d1,
///< 1st flux limiter function parameter.
                                            const float64x2_t d2)
///< 2nd flux limiter function parameter.
{
  float64x2_t r, rm;
  r = vdivq_f64 (d1, d2);
  rm = vmulq_f64 (vdupq_n_f64 (0.5), vaddq_f64 (r, vdupq_n_f64 (1.)));
  rm = vbslq_f64 (vcltq_f64 (r, vdupq_n_f64 (3.)), vdupq_n_f64 (2.), rm);
  rm = vbslq_f64 (vcgtq_f64 (r, vdupq_n_f64 (1. / 3.)), rm, jbm_dbl_2xf64 (r));
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
jbm_flux_limiter_mean_2xf64 (const float64x2_t d1,
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
jbm_flux_limiter_2xf64 (const float64x2_t d1,
                        ///< 1st flux limiter function parameter.
                        const float64x2_t d2,
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
 * defined in an interval (float64x2_t).
 *
 * \return float64x2_t vector of integral values.
 */
static inline float64x2_t
jbm_integral_2xf64 (float64x2_t (*f) (float64x2_t),
                    ///< pointer to the function to integrate.
                    const float64x2_t x1,   ///< left limit of the interval.
                    const float64x2_t x2)   ///< right limit of the interval.
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

#endif
