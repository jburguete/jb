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
 * \file math_loong.h
 * \brief Header file with useful mathematical functions for vectorial
 * LoongArch (LSX and LASX).
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_LOONG__H
#define JB_MATH_LOONG__H 1

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

#define JBM_4xF32_BIAS __lsx_vreplgr2vr_w (JBM_F32_BIAS)
///< bias for floats.
#define JBM_4xF32_BITS_1 __lsx_vreplgr2vr_w (JBM_F32_BITS_1)
///< 1 bits for floats.
#define JBM_4xF32_BITS_EXPONENT __lsx_vreplgr2vr_w (JBM_F32_BITS_EXPONENT)
///< exponent bits for floats.
#define JBM_4xF32_BITS_MANTISSA __lsx_vreplgr2vr_w (JBM_F32_BITS_MANTISSA)
///< mantissa bits for floats.
#define JBM_4xF32_BITS_SIGN __lsx_vreplgr2vr_w (JBM_F32_BITS_SIGN)
///< sign bits for floats.
#define JBM_4xF32_CBRT2 ((JBM4xF32) \
  { .x = { JBM_F32_CBRT2, JBM_F32_CBRT2, JBM_F32_CBRT2, JBM_F32_CBRT2 }}).x
///< cbrt(2) for floats.
#define JBM_4xF32_CBRT4 ((JBM4xF32) \
  { .x = { JBM_F32_CBRT4, JBM_F32_CBRT4, JBM_F32_CBRT4, JBM_F32_CBRT4  }}).x
///< cbrt(4) for floats.

#define JBM_8xF32_BIAS __lasx_xvreplgr2vr_w (JBM_F32_BIAS)
///< bias for floats.
#define JBM_8xF32_BITS_1 __lasx_xvreplgr2vr_w (JBM_F32_BITS_1)
///< 1 bits for floats.
#define JBM_8xF32_BITS_EXPONENT __lasx_xvreplgr2vr_w (JBM_F32_BITS_EXPONENT)
///< exponent bits for floats.
#define JBM_8xF32_BITS_MANTISSA __lasx_xvreplgr2vr_w (JBM_F32_BITS_MANTISSA)
///< mantissa bits for floats.
#define JBM_8xF32_BITS_SIGN __lasx_xvreplgr2vr_w (JBM_F32_BITS_SIGN)
///< sign bits for floats.
#define JBM_8xF32_CBRT2 ((JBM8xF32) { .x = { \
  JBM_F32_CBRT2, JBM_F32_CBRT2, JBM_F32_CBRT2, JBM_F32_CBRT2, \
  JBM_F32_CBRT2, JBM_F32_CBRT2, JBM_F32_CBRT2, JBM_F32_CBRT2 }}).x
///< cbrt(2) for floats.
#define JBM_8xF32_CBRT4 ((JBM8xF32) { .x = { \
  JBM_F32_CBRT4, JBM_F32_CBRT4, JBM_F32_CBRT4, JBM_F32_CBRT4, \
  JBM_F32_CBRT4, JBM_F32_CBRT4, JBM_F32_CBRT4, JBM_F32_CBRT4  }}).x
///< cbrt(4) for floats.

// double constants

#define JBM_2xF64_BIAS __lsx_vreplgr2vr_d (JBM_F64_BIAS)
///< bias for doubles.
#define JBM_2xF64_BITS_1 __lsx_vreplgr2vr_d (JBM_F64_BITS_1)
///< 1 bits for doubles.
#define JBM_2xF64_BITS_EXPONENT __lsx_vreplgr2vr_d (JBM_F64_BITS_EXPONENT)
///< exponent bits for doubles.
#define JBM_2xF64_BITS_MANTISSA __lsx_vreplgr2vr_d (JBM_F64_BITS_MANTISSA)
///< mantissa bits for doubles.
#define JBM_2xF64_BITS_SIGN __lsx_vreplgr2vr_d (JBM_F64_BITS_SIGN)
///< sign bits for doubles.
#define JBM_2xF64_CBRT2 ((JBM2xF64) \
  {.x = { JBM_F64_CBRT2, JBM_F64_CBRT2, JBM_F64_CBRT2, JBM_F64_CBRT2 }}).x
///< cbrt(2) for doubles.
#define JBM_2xF64_CBRT4 ((JBM2xF64) \
  {.x = { JBM_F64_CBRT4, JBM_F64_CBRT4, JBM_F64_CBRT4, JBM_F64_CBRT4 }}).x
///< cbrt(4) for doubles.

#define JBM_4xF64_BIAS __lasx_xvreplgr2vr_d (JBM_F64_BIAS)
///< bias for doubles.
#define JBM_4xF64_BITS_1 __lasx_xvreplgr2vr_d (JBM_F64_BITS_1)
///< 1 bits for doubles.
#define JBM_4xF64_BITS_EXPONENT __lasx_xvreplgr2vr_d (JBM_F64_BITS_EXPONENT)
///< exponent bits for doubles.
#define JBM_4xF64_BITS_MANTISSA __lasx_xvreplgr2vr_d (JBM_F64_BITS_MANTISSA)
///< mantissa bits for doubles.
#define JBM_4xF64_BITS_SIGN __lasx_xvreplgr2vr_d (JBM_F64_BITS_SIGN)
///< sign bits for doubles.
#define JBM_4xF64_CBRT2 ((JBM4xF64) \
  {.x = { JBM_F64_CBRT2, JBM_F64_CBRT2, JBM_F64_CBRT2, JBM_F64_CBRT2 }}).x
///< cbrt(2) for doubles.
#define JBM_4xF64_CBRT4 ((JBM4xF64) \
  {.x = { JBM_F64_CBRT4, JBM_F64_CBRT4, JBM_F64_CBRT4, JBM_F64_CBRT4 }}).x
///< cbrt(4) for doubles.

// Debug functions

static inline void
print_m128b32 (FILE *file, const char *label, __m128i x)
{
  int y[4];
  unsigned int i;
  __lsx_vst (x, y, 0);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m128b64 (FILE *file, const char *label, __m128i x)
{
  long long int y[2];
  unsigned int i;
  __lsx_vst (x, y, 0);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_m128i32 (FILE *file, const char *label, __m128i x)
{
  int y[4];
  unsigned int i;
  __lsx_vst (x, y, 0);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m128i64 (FILE *file, const char *label, __m128i x)
{
  long long int y[2];
  unsigned int i;
  __lsx_vst (x, y, 0);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_m128 (FILE *file, const char *label, __m128 x)
{
  float y[4];
  unsigned int i;
  __lsx_vst ((__m128i) x, y, 0);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m128d (FILE *file, const char *label, __m128d x)
{
  double y[2];
  unsigned int i;
  __lsx_vst ((__m128i) x, y, 0);
  for (i = 0; i < 2; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

static inline void
print_m256b32 (FILE *file, const char *label, __m256i x)
{
  int y[8];
  unsigned int i;
  __lasx_xvst (x, y, 0);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%08x\n", label, i, y[i]);
}

static inline void
print_m256b64 (FILE *file, const char *label, __m256i x)
{
  long long int y[4];
  unsigned int i;
  __lasx_xvst (x, y, 0);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%016llx\n", label, i, y[i]);
}

static inline void
print_m256i32 (FILE *file, const char *label, __m256i x)
{
  int y[8];
  unsigned int i;
  __lasx_xvst (x, y, 0);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_m256i64 (FILE *file, const char *label, __m256i x)
{
  long long int y[4];
  unsigned int i;
  __lasx_xvst (x, y, 0);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_m256 (FILE *file, const char *label, __m256 x)
{
  float y[8];
  unsigned int i;
  __lasx_xvst ((__m256i) x, y, 0);
  for (i = 0; i < 8; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_m256d (FILE *file, const char *label, __m256d x)
{
  double y[4];
  unsigned int i;
  __lasx_xvst ((__m256i) x, y, 0);
  for (i = 0; i < 4; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}

/**
 * Function to calculate the additive reduction value of a __m128 vector.
 *
 * \return additive reduction (float).
 */
static inline float
jbm_4xf32_reduce_add (const __m128 x)   ///< __m128 vector.
{
  JBM4xF32 y;
  y.x = __lsx_vfadd_s (x, (__m128) __lsx_vshuf4i_w ((__m128i) x, 0x4e));
  y.x = __lsx_vfadd_s (y.x, (__m128) __lsx_vshuf4i_w ((__m128i) y.x, 0xb1));
  return y.x[0];
}

/**
 * Function to calculate the maximum reduction value of a __m128 vector.
 *
 * \return maximum reduction (float).
 */
static inline float
jbm_4xf32_reduce_max (const __m128 x)
{
  JBM4xF32 y;
  y.x = __lsx_vfmax_s (x, (__m128) __lsx_vshuf4i_w ((__m128i) x, 0x4e));
  y.x = __lsx_vfmax_s (y.x, (__m128) __lsx_vshuf4i_w ((__m128i) y.x, 0xb1));
  return y.x[0];
}

/**
 * Function to calculate the minimum reduction value of a __m128 vector.
 *
 * \return minimum reduction (float).
 */
static inline float
jbm_4xf32_reduce_min (const __m128 x)
{
  JBM4xF32 y;
  y.x = __lsx_vfmin_s (x, (__m128) __lsx_vshuf4i_w ((__m128i) x, 0x4e));
  y.x = __lsx_vfmin_s (y.x, (__m128) __lsx_vshuf4i_w ((__m128i) y.x, 0xb1));
  return y.x[0];
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
  JBM4xF32 y, z;
  z.x = (__m128) __lsx_vshuf4i_w ((__m128i) x, 0x4e);
  y.x = __lsx_vfmax_s (x, z.x);
  y.x = __lsx_vfmax_s (y.x, (__m128) __lsx_vshuf4i_w ((__m128i) y.x, 0xb1));
  *max = y.x[0];
  y.x = __lsx_vfmin_s (x, z.x);
  y.x = __lsx_vfmin_s (y.x, (__m128) __lsx_vshuf4i_w ((__m128i) y.x, 0xb1));
  *min = y.x[0];
}

/**
 * Function to calculate the additive inverse value of a __m128 vector.
 *
 * \return opposite value vector (__m128).
 */
static inline __m128
jbm_4xf32_opposite (const __m128 x)     ///< __m128 vector.
{
  return (__m128) __lsx_vbitrevi_w ((__m128i) x, 31);
}

/**
 * Function to calculate the multiplicative inverse value of a __m128 vector.
 *
 * \return reciprocal value vector (__m128).
 */
static inline __m128
jbm_4xf32_reciprocal (const __m128 x)   ///< __m128 vector.
{
  return __lsx_vfrecip_s (x);
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
  return (__m128) __lsx_vbitsel_v ((__m128i) x, (__m128i) y,
                                   JBM_4xF32_BITS_SIGN);
}

/**
 * Function to calculate the sign of a __m128 vector.
 *
 * \return sign vector (__m128).
 */
static inline __m128
jbm_4xf32_sign (const __m128 x) ///< __m128 vector.
{
  return jbm_4xf32_copysign ((__m128) JBM_4xF32_BITS_1, x);
}

/**
 * Function to calculate the absolute value of a __m128 vector.
 *
 * \return absolute value vector (__m128).
 */
static inline __m128
jbm_4xf32_abs (const __m128 x)  ///< __m128 vector.
{
  return (__m128) __lsx_vbitclri_w ((__m128i) x, 31);
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
  return __lsx_vfsqrt_s (__lsx_vfmadd_s (x, x, __lsx_vfmul_s (y, y)));
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
  const JBM4xF32 half = {.x = {0.5f, 0.5f, 0.5f, 0.5f} };
  const JBM4xF32 eps = {.x = {0x1p23, 0x1p23, 0x1p23, 0x1p23}};
  __m128 r, rem;
  __m128i mask;
  r = __lsx_vfrintrm_s (__lsx_vfdiv_s (x, d));
  rem = __lsx_vfnmsub_s (r, d, x);
  mask = __lsx_vfcmp_clt_s (eps.x, jbm_4xf32_abs (r));
  return (__m128) __lsx_vbitsel_v ((__m128i) rem,
                                   (__m128i) __lsx_vfmul_s (d, half.x), mask);
}

/**
 * Function to implement the standard frexp function (__m128).
 *
 * \return normalized fraction value in [1/2,1) (__m128).
 */
static inline __m128
jbm_4xf32_frexp (const __m128 x,        ///< __m128 vector.
                 __m128i *e)    ///< pointer to the extracted exponents vector.
{
  const __m128i zi = __lsx_vldi (0);
  const __m128i vbias = __lsx_vreplgr2vr_w ((int32_t) (JBM_F32_BIAS << 23u));
  JBM4xF32 y;
  __m128i exp, is_sub, is_finite, lz, y_sub, exp_sub;
  // y=abs(x)
  y.x = jbm_4xf32_abs (x);
  // mask
  is_finite
    = __lsx_vslt_wu (__lsx_vsub_w (y.i, __lsx_vreplgr2vr_w (1)),
                     __lsx_vreplgr2vr_w ((int32_t)
                                         (JBM_F32_BITS_EXPONENT - 1u)));
  // extract exponent
  exp = __lsx_vsrli_w (y.i, 23);
  // subnormals
  is_sub = __lsx_vand_v (is_finite, __lsx_vseq_w (exp, zi));
  lz = __lsx_vclz_w (y.i);
  y_sub = __lsx_vsll_w (y.i, __lsx_vsub_w (lz, __lsx_vreplgr2vr_w (8)));
  exp_sub = __lsx_vsub_w (__lsx_vreplgr2vr_w (9), lz);
  y.i = __lsx_vbitsel_v (y.i, y_sub, is_sub);
  exp = __lsx_vbitsel_v (exp, exp_sub, is_sub);
  // exponent
  *e = __lsx_vand_v (is_finite, __lsx_vsub_w (exp, JBM_4xF32_BIAS));
  // build mantissa in [0.5,1)
  y.i = __lsx_vbitsel_v (vbias, y.i, JBM_4xF32_BITS_MANTISSA);
  y.x = jbm_4xf32_copysign (y.x, x);
  return (__m128) __lsx_vbitsel_v ((__m128i) x, y.i, is_finite);
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
  return __lsx_vfscaleb_s ((__m128) JBM_4xF32_BITS_1, e);
}

/**
 * Function to calculate the additive reduction value of a __m128d vector.
 *
 * \return additive reduction (double).
 */
static inline double
jbm_2xf64_reduce_add (const __m128d x)  ///< __m128d vector.
{
  JBM2xF64 y;
  y.x = __lsx_vfadd_d (x, (__m128d) __lsx_vshuf4i_w ((__m128i) x, 0x4e));
  return y.x;
}

/**
 * Function to calculate the maximum reduction value of a __m128d vector.
 *
 * \return maximum reduction (double).
 */
static inline double
jbm_2xf64_reduce_max (const __m128d x)  ///< __m128d vector.
{
  JBM2xF64 y;
  y.x = __lsx_vfmax_d (x, (__m128d) __lsx_vshuf4i_w ((__m128i) x, 0x4e));
  return y.x;
}

/**
 * Function to calculate the minimum reduction value of a __m128d vector.
 *
 * \return minimum reduction (double).
 */
static inline double
jbm_2xf64_reduce_min (const __m128d x)  ///< __m128d vector.
{
  JBM2xF64 y;
  y.x = __lsx_vfmin_d (x, (__m128d) __lsx_vshuf4i_w ((__m128i) x, 0x4e));
  return y.x;
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
                         ///< pointer to the minimum value (double).
{
  JBM2xF64 y, z;
  z.x = (__m128d) __lsx_vshuf4i_w ((__m128i) x, 0x4e);
  y.x = __lsx_vfmax_d (x, z.x);
  *max = y.x;
  y.x = __lsx_vfmin_d (x, z.x);
  *min = y.x;
}

/**
 * Function to calculate the additive inverse value of a __m128d vector.
 *
 * \return negative value vector (__m128d).
 */
static inline __m128d
jbm_2xf64_opposite (const __m128d x)    ///< __m128d vector.
{
  return (__m128d) __lsx_vbitrevi_d ((__m128i) x, 63);
}

/**
 * Function to calculate the multiplicative inverse value of a __m128d vector.
 *
 * \return reciprocal value vector (__m128d).
 */
static inline __m128d
jbm_2xf64_reciprocal (const __m128d x)  ///< __m128d vector.
{
  return __lsx_vfrecip_d (x);
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
  return (__m128d) __lsx_vbitsel_v ((__m128i) x, (__m128i) y,
                                    JBM_2xF64_BITS_SIGN);
}

/**
 * Function to calculate the sign of a __m128d vector.
 *
 * \return sign vector (__m128d).
 */
static inline __m128d
jbm_2xf64_sign (const __m128d x)        ///< __m128d vector.
{
  return jbm_2xf64_copysign ((__m128d) JBM_2xF64_BITS_1, x);
}

/**
 * Function to calculate the absolute value of a __m128d vector.
 *
 * \return absolute value vector.
 */
static inline __m128d
jbm_2xf64_abs (const __m128d x)
{
  return (__m128d) __lsx_vbitclri_d ((__m128i) x, 63);
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
  return __lsx_vfsqrt_d (__lsx_vfmadd_d (x, x, __lsx_vfmul_d (y, y)));
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
  const JBM2xF64 half = {.x = {0.5, 0.5} };
  const JBM2xF64 eps = {.x = {0x1p52, 0x1p52} };
  __m128d r, rem;
  __m128i mask;
  r = __lsx_vfrintrm_d (__lsx_vfdiv_d (x, d));
  rem = __lsx_vfnmsub_d (r, d, x);
  mask = __lsx_vfcmp_clt_d (eps.x, jbm_2xf64_abs (r));
  return (__m128d) __lsx_vbitsel_v ((__m128i) rem,
                                    (__m128i) __lsx_vfmul_d (d, half.x), mask);
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
  const __m128i zi = __lsx_vldi (0);
  const __m128i vbias = __lsx_vreplgr2vr_d ((int64_t) JBM_F64_BIAS << 52);
  JBM2xF64 y;
  __m128i exp, is_sub, is_finite, lz, y_sub, exp_sub;
  // y=abs(x)
  y.x = jbm_2xf64_abs (x);
  // mask
  is_finite
    = __lsx_vslt_du (__lsx_vsub_d (y.i, __lsx_vreplgr2vr_d (1ll)),
                     __lsx_vreplgr2vr_d ((int64_t)
                                         (JBM_F64_BITS_EXPONENT - 1ull)));
  // extract exponent
  exp = __lsx_vsrli_d (y.i, 52);
  // subnormals
  is_sub = __lsx_vand_v (is_finite, __lsx_vseq_d (exp, zi));
  lz = __lsx_vclz_d (y.i);
  y_sub = __lsx_vsll_d (y.i, __lsx_vsub_d (lz, __lsx_vreplgr2vr_d (11ll)));
  exp_sub = __lsx_vsub_d (__lsx_vreplgr2vr_d (12ll), lz);
  y.i = __lsx_vbitsel_v (y.i, y_sub, is_sub);
  exp = __lsx_vbitsel_v (exp, exp_sub, is_sub);
  // exponent
  *e = __lsx_vand_v (is_finite, __lsx_vsub_d (exp, JBM_2xF64_BIAS));
  // build mantissa in [0.5,1)
  y.i = __lsx_vbitsel_v (vbias, y.i, JBM_2xF64_BITS_MANTISSA);
  y.x = jbm_2xf64_copysign (y.x, x);
  return (__m128d) __lsx_vbitsel_v ((__m128i) x, y.i, is_finite);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m128i).
 *
 * \return function value (__m128d).
 */
static inline __m128d
jbm_2xf64_exp2n (const __m128i e)       ///< exponent vector (__m128i).
{
  return __lsx_vfscaleb_d ((__m128d) JBM_2xF64_BITS_1, e);
}

/**
 * Function to calculate the additive reduction value of a __m256 vector.
 *
 * \return additive reduction (float).
 */
static inline float
jbm_8xf32_reduce_add (const __m256 x)   ///< __m256 vector.
{
  __m256 h = (__m256) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  return jbm_4xf32_reduce_add ((__m128) __lasx_xvfadd_s (x, h));
}

/**
 * Function to calculate the maximum reduction value of a __m256 vector.
 *
 * \return maximum reduction (float).
 */
static inline float
jbm_8xf32_reduce_max (const __m256 x)   ///< __m256 vector.
{
  __m256 h = (__m256) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  return jbm_4xf32_reduce_max ((__m128) __lasx_xvfmax_s (x, h));
}

/**
 * Function to calculate the minimum reduction value of a __m256 vector.
 *
 * \return minimum reduction (float).
 */
static inline float
jbm_8xf32_reduce_min (const __m256 x)   ///< __m256 vector.
{
  __m256 h = (__m256) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  return jbm_4xf32_reduce_min ((__m128) __lasx_xvfmin_s (x, h));
}

/**
 * Function to calculate the maximum and minimum reduction value of a __m256
 * vector.
 */
static inline void
jbm_8xf32_reduce_maxmin (const __m256 x,        ///< __m256 vector.
                         float *max,    ///< pointer to the maximum value
                         float *min)    ///< pointer to the minimum value
{
  __m256 h = (__m256) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  *max = jbm_4xf32_reduce_max ((__m128) __lasx_xvfmax_s (x, h));
  *min = jbm_4xf32_reduce_min ((__m128) __lasx_xvfmin_s (x, h));
}

/**
 * Function to calculate the additive inverse value of a __m256 vector.
 *
 * \return opposite value vector (__m256).
 */
static inline __m256
jbm_8xf32_opposite (const __m256 x)     ///< __m256 vector.
{
  return (__m256) __lasx_xvbitrevi_w ((__m256i) x, 31);
}

/**
 * Function to calculate the multiplicative inverse value of a __m256 vector.
 *
 * \return reciprocal value vector (__m256).
 */
static inline __m256
jbm_8xf32_reciprocal (const __m256 x)   ///< __m256 vector.
{
  return __lasx_xvfrecip_s (x);
}

/**
 * Function to copy the sign of a __m256 vector to another __m256 vector.
 *
 * \return __m256 vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m256
jbm_8xf32_copysign (const __m256 x,
///< __m256 vector to preserve magnitude.
                    const __m256 y)     ///< __m256 vector to preserve sign.
{
  return (__m256) __lasx_xvbitsel_v ((__m256i) x, (__m256i) y,
                                     JBM_8xF32_BITS_SIGN);
}

/**
 * Function to calculate the sign of a __m256 vector.
 *
 * \return sign vector (__m256).
 */
static inline __m256
jbm_8xf32_sign (const __m256 x) ///< __m256 vector.
{
  return jbm_8xf32_copysign ((__m256) JBM_8xF32_BITS_1, x);
}

/**
 * Function to calculate the absolute value of a __m256 vector.
 *
 * \return absolute value vector (__m256).
 */
static inline __m256
jbm_8xf32_abs (const __m256 x)  ///< __m256 vector.
{
  return (__m256) __lasx_xvbitclri_w ((__m256i) x, 31);
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
  return __lasx_xvfsqrt_s (__lasx_xvfmadd_s (x, x, __lasx_xvfmul_s (y, y)));
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
  const JBM8xF32 half = {.x = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f}
  };
  const JBM8xF32 eps = {.x
    = {0x1p23, 0x1p23, 0x1p23, 0x1p23, 0x1p23, 0x1p23, 0x1p23, 0x1p23}
  };
  __m256 r, rem;
  __m256i mask;
  r = __lasx_xvfrintrm_s (__lasx_xvfdiv_s (x, d));
  rem = __lasx_xvfnmsub_s (r, d, x);
  mask = __lasx_xvfcmp_clt_s (eps.x, jbm_8xf32_abs (r));
  return (__m256)
    __lasx_xvbitsel_v ((__m256i) rem,
                       (__m256i) __lasx_xvfmul_s (d, half.x), mask);
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
  const __m256i zi = __lasx_xvldi (0);
  const __m256i vbias = __lasx_xvreplgr2vr_w ((int32_t) (JBM_F32_BIAS << 23u));
  JBM8xF32 y;
  __m256i exp, is_sub, is_finite, lz, y_sub, exp_sub;
  // y=abs(x)
  y.x = jbm_8xf32_abs (x);
  // mask
  is_finite
    = __lasx_xvslt_wu (__lasx_xvsub_w (y.i, __lasx_xvreplgr2vr_w (1)),
                       __lasx_xvreplgr2vr_w ((int32_t)
                                             (JBM_F32_BITS_EXPONENT - 1u)));
  // extract exponent
  exp = __lasx_xvsrli_w (y.i, 23);
  // subnormals
  is_sub = __lasx_xvand_v (is_finite, __lasx_xvseq_w (exp, zi));
  lz = __lasx_xvclz_w (y.i);
  y_sub = __lasx_xvsll_w (y.i, __lasx_xvsub_w (lz, __lasx_xvreplgr2vr_w (8)));
  exp_sub = __lasx_xvsub_w (__lasx_xvreplgr2vr_w (9), lz);
  y.i = __lasx_xvbitsel_v (y.i, y_sub, is_sub);
  exp = __lasx_xvbitsel_v (exp, exp_sub, is_sub);
  // exponent
  *e = __lasx_xvand_v (is_finite, __lasx_xvsub_w (exp, JBM_8xF32_BIAS));
  // build mantissa in [0.5,1)
  y.i = __lasx_xvbitsel_v (vbias, y.i, JBM_8xF32_BITS_MANTISSA);
  y.x = jbm_8xf32_copysign (y.x, x);
  return (__m256) __lasx_xvbitsel_v ((__m256i) x, y.i, is_finite);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m256i).
 *
 * \return function value (__m256).
 */
static inline __m256
jbm_8xf32_exp2n (const __m256i e)       ///< exponent vector (__m256i).
{
  return __lasx_xvfscaleb_s ((__m256) JBM_8xF32_BITS_1, e);
}

/**
 * Function to calculate the additive reduction value of a __m256d vector.
 *
 * \return additive reduction (double).
 */
static inline double
jbm_4xf64_reduce_add (const __m256d x)  ///< __m256d vector.
{
  __m256d h = (__m256d) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  return jbm_2xf64_reduce_add ((__m128d) __lasx_xvfadd_d (x, h));
}

/**
 * Function to calculate the maximum reduction value of a __m256d vector.
 *
 * \return maximum reduction (double).
 */
static inline double
jbm_4xf64_reduce_max (const __m256d x)  ///< __m256d vector.
{
  __m256d h = (__m256d) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  return jbm_2xf64_reduce_max ((__m128d) __lasx_xvfmax_d (x, h));
}

/**
 * Function to calculate the minimum reduction value of a __m256d vector.
 *
 * \return minimum reduction (double).
 */
static inline double
jbm_4xf64_reduce_min (const __m256d x)  ///< __m256d vector.
{
  __m256d h = (__m256d) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  return jbm_2xf64_reduce_min ((__m128d) __lasx_xvfmin_d (x, h));
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
  __m256d h = (__m256d) __lasx_xvpermi_q ((__m256i) x, (__m256i) x, 0x01);
  *max = jbm_2xf64_reduce_max ((__m128d) __lasx_xvfmax_d (x, h));
  *min = jbm_2xf64_reduce_min ((__m128d) __lasx_xvfmin_d (x, h));
}

/**
 * Function to calculate the additive inverse value of a __m256d vector.
 *
 * \return negative value vector (__m256d).
 */
static inline __m256d
jbm_4xf64_opposite (const __m256d x)    ///< __m256d vector.
{
  return (__m256d) __lasx_xvbitrevi_d ((__m256i) x, 63);
}

/**
 * Function to calculate the multiplicative inverse value of a __m256d vector.
 *
 * \return reciprocal value vector (__m256d).
 */
static inline __m256d
jbm_4xf64_reciprocal (const __m256d x)  ///< __m256d vector.
{
  return __lasx_xvfrecip_d (x);
}

/**
 * Function to copy the sign of a __m256d vector to another __m256d vector.
 *
 * \return __m256d vector with magnitud of 1st vector and sign of 2nd vector.
 */
static inline __m256d
jbm_4xf64_copysign (const __m256d x,
///< __m256d vector to preserve magnitude.
                    const __m256d y)    ///< __m256d vector to preserve sign.
{
  return (__m256d) __lasx_xvbitsel_v ((__m256i) x, (__m256i) y,
                                      JBM_4xF64_BITS_SIGN);
}

/**
 * Function to calculate the sign of a __m256d vector.
 *
 * \return sign vector (__m256d).
 */
static inline __m256d
jbm_4xf64_sign (const __m256d x)        ///< __m256d vector.
{
  return jbm_4xf64_copysign ((__m256d) JBM_4xF64_BITS_1, x);
}

/**
 * Function to calculate the absolute value of a __m256d vector.
 *
 * \return absolute value vector.
 */
static inline __m256d
jbm_4xf64_abs (const __m256d x)
{
  return (__m256d) __lasx_xvbitclri_d ((__m256i) x, 63);
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
  return __lasx_xvfsqrt_d (__lasx_xvfmadd_d (x, x, __lasx_xvfmul_d (y, y)));
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
  const JBM4xF64 half = {.x = {0.5, 0.5, 0.5, 0.5} };
  const JBM4xF64 eps = {.x = {0x1p52, 0x1p52, 0x1p52, 0x1p52} };
  __m256d r, rem;
  __m256i mask;
  r = __lasx_xvfrintrm_d (__lasx_xvfdiv_d (x, d));
  rem = __lasx_xvfnmsub_d (r, d, x);
  mask = __lasx_xvfcmp_clt_d (eps.x, jbm_4xf64_abs (r));
  return (__m256d)
    __lasx_xvbitsel_v ((__m256i) rem,
                       (__m256i) __lasx_xvfmul_d (d, half.x), mask);
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
  const __m256i zi = __lasx_xvldi (0);
  const __m256i vbias = __lasx_xvreplgr2vr_d ((int64_t) JBM_F64_BIAS << 52);
  JBM4xF64 y;
  __m256i exp, is_sub, is_finite, lz, y_sub, exp_sub;
  // y=abs(x)
  y.x = jbm_4xf64_abs (x);
  // mask
  is_finite
    = __lasx_xvslt_du (__lasx_xvsub_d (y.i, __lasx_xvreplgr2vr_d (1ll)),
                       __lasx_xvreplgr2vr_d ((int64_t)
                                             (JBM_F64_BITS_EXPONENT - 1ull)));
  // extract exponent
  exp = __lasx_xvsrli_d (y.i, 52);
  // subnormals
  is_sub = __lasx_xvand_v (is_finite, __lasx_xvseq_d (exp, zi));
  lz = __lasx_xvclz_d (y.i);
  y_sub
    = __lasx_xvsll_d (y.i, __lasx_xvsub_d (lz, __lasx_xvreplgr2vr_d (11ll)));
  exp_sub = __lasx_xvsub_d (__lasx_xvreplgr2vr_d (12ll), lz);
  y.i = __lasx_xvbitsel_v (y.i, y_sub, is_sub);
  exp = __lasx_xvbitsel_v (exp, exp_sub, is_sub);
  // exponent
  *e = __lasx_xvand_v (is_finite, __lasx_xvsub_d (exp, JBM_4xF64_BIAS));
  // build mantissa in [0.5,1)
  y.i = __lasx_xvbitsel_v (vbias, y.i, JBM_4xF64_BITS_MANTISSA);
  y.x = jbm_4xf64_copysign (y.x, x);
  return (__m256d) __lasx_xvbitsel_v ((__m256i) x, y.i, is_finite);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (__m256i).
 *
 * \return function value (__m256d).
 */
static inline __m256d
jbm_4xf64_exp2n (const __m256i e)       ///< exponent vector (__m256i).
{
  return __lasx_xvfscaleb_d ((__m256d) JBM_4xF64_BITS_1, e);
}

#endif
