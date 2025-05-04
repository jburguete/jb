/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
 *
 * Copyright 2005-2025, Javier Burguete Tolosa.
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
 * \file math_riscv.h
 * \brief Header file with useful mathematical functions for RISCV.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_RISCV__H
#define JB_MATH_RISCV__H 1

/**
 * union to work with bits in 4 packed float numbers.
 */
typedef union
{
  vfloat32m1_t x;               ///< floating point.
  vuint32m1_t i;                ///< bits.
} JBMNxF32;

/**
 * union to work with bits in 2 packed double numbers.
 */
typedef union
{
  vfloat64m1_t x;               ///< floating point.
  vuint64m1_t i;                ///< bits.
} JBMNxF64;

// Debug functions

/*
static inline void
print_vuint32m1_t (FILE *file, const char *label, vuint32m1_t x,
                   const size_t vl)
{
  unsigned int y[vl] JB_ALIGNED;
  unsigned int i;
  __riscv_vse32_v_u32m1 (y, x, vl);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%u\n", label, i, y[i]);
}

static inline void
print_vuint64m1_t (FILE *file, const char *label, vuint64m1_t x,
                   const size_t vl)
{
  unsigned long long int y[vl] JB_ALIGNED;
  unsigned int i;
  __riscv_vse64_v_u64m1 (y, x, vl);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%llu\n", label, i, y[i]);
}

static inline void
print_vint32m1_t (FILE *file, const char *label, vint32m1_t x, const size_t vl)
{
  int y[vl] JB_ALIGNED;
  unsigned int i;
  __riscv_vse32_v_i32m1 (y, x, vl);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%d\n", label, i, y[i]);
}

static inline void
print_vint64m1_t (FILE *file, const char *label, vint64m1_t x, const size_t vl)
{
  long long int y[vl] JB_ALIGNED;
  unsigned int i;
  __riscv_vse64_v_i64m1 (y, x, vl);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%lld\n", label, i, y[i]);
}

static inline void
print_vfloat32m1_t (FILE *file, const char *label, vfloat32m1_t x,
                    const size_t vl)
{
  float y[vl] JB_ALIGNED;
  unsigned int i;
  __riscv_vse32_v_f32m1 (y, x, vl);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%.8g\n", label, i, y[i]);
}

static inline void
print_vfloat64m1_t (FILE *file, const char *label, vfloat64m1_t x,
                    const size_t vl)
{
  double y[vl] JB_ALIGNED;
  unsigned int i;
  __riscv_vse64_v_f64m1 (y, x, vl);
  for (i = 0; i < vl; ++i)
    fprintf (file, "%s[%u]=%.17lg\n", label, i, y[i]);
}
*/

/**
 * Function to calculate the additive inverse value of a vfloat32m1_t vector.
 *
 * \return opposite value vector (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_opposite_nxf32 (const vfloat32m1_t x,       ///< vfloat32m1_t vector.
                    const size_t vl)    ///< vector size.
{
  return __riscv_vfneg_v_f32m1 (x, vl);
}

/**
 * Function to calculate the multiplicative inverse value of a vfloat32m1_t
 * vector.
 *
 * \return reciprocal value vector (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_reciprocal_nxf32 (const vfloat32m1_t x,     ///< vfloat32m1_t vector.
                      const size_t vl)  ///< vector size.
{
  return __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x, vl);
}

/**
 * Function to calculate the absolute value of a vfloat32m1_t vector.
 *
 * \return absolute value vector (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_abs_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< vector size.
{
  return __riscv_vfabs_v_f32m1 (x, vl);
}

/**
 * Function to calculate the hypot function (vfloat32m1_t).
 *
 * \return function value vector (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_hypot_nxf32 (const vfloat32m1_t x,  ///< 1st vfloat32m1_t vector.
                 const vfloat32m1_t y,  ///< 2nd vfloat32m1_t vector.
                 const size_t vl)       ///< vector size.
{
  return __riscv_vfsqrt_v_f32m1 (__riscv_vfmacc_vv_f32m1 (__riscv_vfmul_vv_f32m1 (x, x, vl), y, y, vl),
                         vl);
}

/**
 * Function to calculate the rounding towards negative infinity.
 +
 + \return function value vector (vint32m1_t).
 */
static inline vint32m1_t
jbm_floor_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                 const size_t vl)       ///< vector size.
{
  vint32m1_t i, i1;
  vbool32_t m;
  i = __riscv_vfcvt_rtz_x_f32m1 (x, vl);
  i1 = __riscv_vadd_vx_i32m1 (i, -1);
  m = __riscv_vmflt_vf_f32m1_b32 (x, 0.f, vl);
  return __riscv_vmerge_vvm_i32m1 (i1, i, m, vl);
}

/**
 * Function to calculate the rest of a division (vfloat32m1_t).
 *
 * \return rest value vector (in [0,|divisor|) interval).
 */
static inline vfloat32m1_t
jbm_rest_nxf32 (const vfloat32m1_t x,   ///< dividend (vfloat32m1_t).
                const vfloat32m1_t d,   ///< divisor (vfloat32m1_t).
                const size_t vl)        ///< vector size.
{
  return
    __riscv_vfsub_vv_f32m1 (x,
                    __riscv_vfmul_vv_f32m1 (jbm_floor_nxf32 (__riscv_vfdiv_vv_f32m1 (x, d, vl),
                                                     vl), d, vl), vl);
}

/**
 * Function to implement the standard frexp function (vfloat32m1_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline vfloat32m1_t
jbm_frexp_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                 vint32m1_t * e,        ///< pointer to the extracted exponents vector.
                 const size_t vl)       ///< vector size.
{
  JBMNxF32 a, y, y2, z;
  vint32m1_t en;
  vbool32_t m1, m2, m3;
  a.x = x;
  y.i = __riscv_vand_vx_u32m1 (a.i, 0x7f800000, vl);
  m1 = __riscv_vmfeq_vx_u32m1_b32 (y.i, 0x7f800000, vl);
  m2 = __riscv_vmfeq_vx_u32m1_b32 (y.i, 0, vl);
  y2.x = x;
  y2.i = __riscv_vand_vx_u32m1 (y2.i, 0x007fffff, vl);
  m3 = __riscv_vmfeq_vx_u32m1_b32 (y2.i, 0, vl);
  y2.i = __riscv_vfmv_v_x_u32m1 (0x00400000, vl);
  z.x = __riscv_vfdiv_vv_f32m1 (x, y2.x, vl);
  z.i = __riscv_vand_vx_u32m1 (z.i, 0x7f800000, vl);
  en = __riscv_vmerge_vvm_i32m1 (__riscv_vsub_vx_i32m1 (__riscv_vshra_vi_i32m1 ((vint32m1_t) z.i, 23,
                                                        vl), 253, vl),
                         __riscv_vsub_vx_i32m1 (__riscv_vshra_vi_i32m1 ((vint32m1_t) y.i, 23,
                                                        vl), 126, vl), m2, vl);
  y.x = __riscv_vmerge_vvm_f32m1 (__riscv_vfmul_vv_f32m1 (y2.x, z.x, vl), y.x, m2, vl);
  en = __riscv_vmerge_vvm_i32m1 (__riscv_vmv_v_x_i32m1 (0, vl), en,
                         __riscv_vmor_mm (m1, __riscv_vmand_mm (m2, m3, vl), vl), vl);
  *e = en;
  return __riscv_vmerge_vvm_f32m1 (x, __riscv_vfmul_vf_f32m1 (__riscv_vfdiv_vv_f32m1 (x, y.x, vl), 0.5f,
                                              vl), m1, vl);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (vint32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_exp2n_nxf32 (vint32m1_t e,  ///< exponent vector (vint32m1_t).
                 const size_t vl)       ///< vector size.
{
  vfloat32m1_t x;
  x = __riscv_vmerge_vvm_f32m1
    ((vfloat32m1_t) __riscv_vshla_vi_i32m1 (__riscv_vadd_vx_i32m1 (e, 127, vl), 23, vl),
     (vfloat32m1_t) __riscv_vshra_vv_i32m1 (__riscv_vmv_v_x_i32m1 (0x00400000, vl),
                                    __riscv_vsub_vx_i32m1 (e, 127, vl)),
     vmgt_vx_i32m1_b32 (e, 127, vl));
  x = __riscv_vmerge_vvm_f32m1 (__riscv_vfmv_v_f_f32m1 (0.f, vl), x,
                        vmlt_vx_i32m1_b32 (e, -150, vl), vl);
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfmv_v_f_f32m1 (INFINITY, vl), x,
                           vmgt_vx_i32m1_b32 (e, 127, vl), vl);
}

/**
 * Function to implement the standard ldexp function (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_ldexp_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                 vint32m1_t e,  ///< exponent vector (vint32m1_t).
                 const size_t vl)       ///< vector size.
{
  return __riscv_vfmul_vv_f32m1 (x, jbm_exp2n_nxf32 (e, vl), vl);
}

/**
 * Function to check small vfloat32m1_t vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline vbool32_t
jbm_small_nxf32 (const vfloat32m1_t x,  ///< vfloat64m1_t vector.
                 const size_t vl)       ///< vector size.
{
  return __riscv_vmflt_vf_f32m1_b32 (jbm_abs_nxf32 (x, vl), FLT_EPSILON, vl);
}

/**
 * Function to calculate the vfloat32m1_t vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin vfloat32m1_t vector.
 */
static inline vfloat32m1_t
jbm_modmin_nxf32 (const vfloat32m1_t a, ///< 1st vfloat64m1_t vector.
                  const vfloat32m1_t b, ///< 2nd vfloat64m1_t vector.
                  const size_t vl)      ///< vector size.
{
  vfloat32m1_t aa, ab, y;
  ab = __riscv_vfmul_vv_f32m1 (a, b, vl);
  y = __riscv_vmerge_vfm_f32m1 (a, 0.f, vmfgt_vf_f32m1_b32 (ab, 0.f, vl)), vl;
  aa = jbm_abs_nxf32 (y, vl);
  ab = jbm_abs_nxf32 (b, vl);
  return __riscv_vmerge_vvm_f32m1 (b, y, vmfgt_vv_f32m1_b32 (aa, ab, vl), vl);
}

/**
 * Function to interchange 2 vfloat32m1_t vectors.
 */
static inline void
jbm_change_nxf32 (vfloat32m1_t * restrict a,
///< 1st vfloat32m1_t vector pointer.
                  vfloat32m1_t * restrict b)
///< 2nd vfloat32m1_t vector pointer.
{
  vfloat32m1_t c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a vfloat32m1_t vector.
 *
 * \return vfloat32m1_t double.
 */
static inline vfloat32m1_t
jbm_dbl_nxf32 (const vfloat32m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< vector size.
{
  return __riscv_vfadd_vv_f32m1 (x, x, vl);
}

/**
 * Function to calculate the square of the components of a vfloat32m1_t vector.
 *
 * \return vfloat32m1_t vector square.
 */
static inline vfloat32m1_t
jbm_sqr_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< vector size.
{
  return __riscv_vfmul_vv_f32m1 (x, x, vl);
}

/**
 * Function to perform an extrapolation between 2 vfloat32m1_t vectors of 2D
 * points.
 *
 * \return vfloat32m1_t vector of y-coordinates of the extrapolated points.
 */
static inline vfloat32m1_t
jbm_extrapolate_nxf32 (const vfloat32m1_t x,
///< vfloat32m1_t vector of x-coordinates of the extrapolated points.
                       const vfloat32m1_t x1,
///< vfloat32m1_t vector of x-coordinates of the 1st points.
                       const vfloat32m1_t x2,
///< vfloat32m1_t vector of x-coordinates of the 2nd points.
                       const vfloat32m1_t y1,
///< vfloat32m1_t vector of y-coordinates of the 1st points.
                       const vfloat32m1_t y2,
///< vfloat32m1_t vector of y-coordinates of the 2nd points.
                       const size_t vl) ///< vector size.
{
  return __riscv_vfmacc_vv_f32m1 (y1, __riscv_vfsub_vv_f32m1 (x, x1, vl),
                          __riscv_vfdiv_vv_f32m1 (__riscv_vfsub_vv_f32m1 (y2, y1, vl),
                                          __riscv_vfsub_vv_f32m1 (x2, x1, vl)), vl);
}

/**
 * Function to perform an interpolation between 2 vfloat32m1_t vectors of 2D
 * points.
 *
 * \return vfloat32m1_t vector of y-coordinates of the interpolated points.
 */
static inline vfloat32m1_t
jbm_interpolate_nxf32 (const vfloat32m1_t x,
///< vfloat32m1_t vector of x-coordinates of the interpolated points.
                       const vfloat32m1_t x1,
///< vfloat32m1_t vector of x-coordinates of the 1st points.
                       const vfloat32m1_t x2,
///< vfloat32m1_t vector of x-coordinates of the 2nd points.
                       const vfloat32m1_t y1,
///< vfloat32m1_t vector of y-coordinates of the 1st points.
                       const vfloat32m1_t y2,
///< vfloat32m1_t vector of y-coordinates of the 2nd points.
                       const size_t vl) ///< vector size.
{
  vfloat32m1_t k;
  k = jbm_extrapolate_nxf32 (x, x1, x2, y1, y2, vl);
  k = __riscv_vmerge_vvm_f32m1 (k, y1, vmfgt_vv_f32m1_b32 (x, x1, vl), vl);
  return __riscv_vmerge_vvm_f32m1 (k, y2, __riscv_vmflt_vv_f32m1_b32 (x, x2, vl), vl);
}

/**
 * Function to calculate the length of a vfloat32m1_t vector of 2D segments.
 *
 * \return vfloat32m1_t vector of segment lengths.
 */
static inline vfloat32m1_t
jbm_v2_length_nxf32 (const vfloat32m1_t x1,
///< vfloat32m1_t vector of x-coordinates of the 1st points defining the segment.
                     const vfloat32m1_t y1,
///< vfloat32m1_t vector of y-coordinates of the 1st points defining the segment.
                     const vfloat32m1_t x2,
///< vfloat32m1_t vector of x-coordinates of the 2nd points defining the segment.
                     const vfloat32m1_t y2,
///< vfloat32m1_t vector of y-coordinates of the 2nd points defining the segment.
                     const size_t vl)   ///< vector size.
{
  return jbm_hypot_nxf32 (__riscv_vfsub_vv_f32m1 (x2, x1, vl),
                          __riscv_vfsub_vv_f32m1 (y2, y1, vl), vl);
}

/**
 * Function to calculate the length of a vfloat32m1_t vector of 3D segments.
 *
 * \return vfloat32m1_t vector of segment lengths.
 */
static inline vfloat32m1_t
jbm_v3_length_nxf32 (const vfloat32m1_t x1,
///< vfloat32m1_t vector of x-coordinates of the 1st points defining the
///< segments.
                     const vfloat32m1_t y1,
///< vfloat32m1_t vector of y-coordinates of the 1st points defining the
///< segments.
                     const vfloat32m1_t z1,
///< vfloat32m1_t vector of z-coordinates of the 1st points defining the
///< segments.
                     const vfloat32m1_t x2,
///< vfloat32m1_t vector of x-coordinates of the 2nd points defining the
///< segments.
                     const vfloat32m1_t y2,
///< vfloat32m1_t vector of y-coordinates of the 2nd points defining the
///< segments.
                     const vfloat32m1_t z2,
///< vfloat32m1_t vector of z-coordinates of the 2nd points defining the
///< segments.
                     const size_t vl)   ///< vector size.
{
  vfloat32m1_t dx, dy, dz;
  dx = jbm_sqr_nxf32 (__riscv_vfsub_vv_f32m1 (x2, x1, vl));
  dy = __riscv_vfsub_vv_f32m1 (y2, y1, vl);
  dy = __riscv_vfmacc_vv_f32m1 (dx, dy, dy, vl);
  dz = __riscv_vfsub_vv_f32m1 (z2, z1, vl);
  return __riscv_vfsqrt_v_f32m1 (__riscv_vfmacc_vv_f32m1 (dy, dz, dz, vl), vl);
}

/**
 * Function to calculate a 1st order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32 (p[0], vl), p[1], x, vl);
}

/**
 * Function to calculate a 2nd order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_1_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 3rd order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_2_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 4th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_4_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_3_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 5th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_5_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_4_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 6th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_6_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_5_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 7th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_7_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_6_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 8th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_8_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_7_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 9th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_9_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_8_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 10th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_10_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_9_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 11th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_11_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_10_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 12th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_12_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_11_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 13th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_13_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_12_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 14th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_14_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_13_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 15th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_15_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_14_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 16th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_16_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_15_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 17th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_17_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_16_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 18th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_18_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_17_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 19th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_19_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_18_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 20th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_20_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_19_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 21th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_21_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_20_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 22th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_22_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_21_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 23th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_23_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_22_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 24th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_24_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_23_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 25th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_25_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_24_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 26th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_26_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_25_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 27th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_27_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_26_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 28th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_28_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_27_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 29th order polynomial (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of polynomial values.
 */
static inline vfloat32m1_t
jbm_polynomial_29_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl), x,
                          jbm_polynomial_28_nxf32 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 0th+1st order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_1_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                         __riscv_vfmacc_vf_f32 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[1], x, vl));
}

/**
 * Function to calculate a 0th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_2_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+1st order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_2_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[2], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_3_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_3_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_3_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[3], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_4_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_4_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_4_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_4_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[4], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_5_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_5_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_5_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_5_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_5_4_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[5], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_6_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_6_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_6_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_6_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_6_4_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_6_5_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[6], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_4_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_5_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_7_6_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[7], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_4_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_5_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_6_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_8_7_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[8], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_0_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_1_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_3_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_4_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_5_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_6_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_7_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_9_8_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                        const float *p, ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[9], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_10_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[10], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_11_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[11], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_12_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[12], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_13_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[13], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_14_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[14], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_15_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[15], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_16_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[16], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_17_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[17], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_18_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[18], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_19_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[19], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_20_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[20], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_21_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[21], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_22_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[22], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_23_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[23], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_23_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_24_23_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_23_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[24], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+25th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_24_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_23_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_23_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_23_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_25_24_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_24_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[25], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+26th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_25_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+25th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_24_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_23_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_23_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_23_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_24_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_24_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+25th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_26_25_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_25_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[26], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+27th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_26_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+26th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_25_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+25th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_24_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_23_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_23_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_23_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_24_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_24_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 25th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_25_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_25_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 26, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+26th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_27_26_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_26_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[27], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+28th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_27_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+27th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_26_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+26th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_25_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+25th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_24_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_23_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_23_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_23_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_24_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_24_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 25th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_25_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_25_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 26, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 26th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_26_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_26_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 27, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+27th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_28_27_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_27_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[28], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+29th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_0_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (p[0], vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_28_nxf32 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+28th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_1_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_27_nxf32 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+27th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_2_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_2_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_26_nxf32 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+26th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_3_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_3_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_25_nxf32 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+25th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_4_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_4_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_24_nxf32 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+24th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_5_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_5_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_23_nxf32 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+23th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_6_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_6_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_22_nxf32 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+22th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_7_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_7_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_21_nxf32 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+21th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_8_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_8_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_20_nxf32 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+20th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_9_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                         const float *p,        ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_9_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_19_nxf32 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+19th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_10_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_10_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_18_nxf32 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+18th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_11_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_11_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_17_nxf32 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+17th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_12_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_12_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_16_nxf32 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+16th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_13_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_13_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_15_nxf32 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+15th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_14_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_14_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_14_nxf32 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+14th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_15_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_15_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_13_nxf32 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+13th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_16_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_16_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_12_nxf32 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+12th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_17_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_17_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_11_nxf32 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+11th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_18_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_18_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_10_nxf32 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+10th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_19_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_19_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_9_nxf32 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+9th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_20_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_20_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_8_nxf32 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+8th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_21_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_21_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_7_nxf32 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+7th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_22_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_22_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_6_nxf32 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+6th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_23_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_23_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_5_nxf32 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+5th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_24_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_24_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_4_nxf32 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 25th+4th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_25_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_25_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_3_nxf32 (x, p + 26, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 26th+3rd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_26_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_26_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_2_nxf32 (x, p + 27, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 27th+2nd order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_27_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_27_nxf32 (x, p, vl),
                    __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x,
                                     jbm_polynomial_1_nxf32 (x, p + 28, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+28th order rational (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of rational values.
 */
static inline vfloat32m1_t
jbm_rational_29_28_nxf32 (const vfloat32m1_t x, ///< vfloat32m1_t vector.
                          const float *p,       ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f32m1 (jbm_polynomial_28_nxf32 (x, p, vl),
                    __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), p[29], x, vl),
                    vl);
}

/**
 * Function to calculate the well conditionated function expm1(x) for
 * \f$x\in\left[-\log(2)/2,\log(2)/2\right]\f$ (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_expm1wc_nxf32 (const vfloat32m1_t x,
///< vfloat32m1_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
                   const size_t vl)     ///< array size.
{
  const float a1 = 9.9999999917826835759154742878523887e-01f;
  const float a2 = -4.9999999958913417879577371439261924e-01f;
  const float a3 = 8.3333136366700581865508474051734715e-02f;
  const float a5 = -1.3833464660905326042591440964123531e-03f;
  vfloat32m1_t x2;
  x2 = jbm_sqr_nxf32 (x, vl);
  x2 = __riscv_vfmacc_vf_f32m1 (__riscv_vfmv_v_f_f32m1 (a3, vl), a5, x2, vl);
  x2 = __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (a2, vl), x2, x, vl);
  x2 = __riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x2, x, vl);
  return
    __riscv_vfmul_vv_f32m1 (x, __riscv_vfdiv_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (a1, vl), x2, vl), vl);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (vfloat32m1_t).
 *
 * \return function value.
 */
static inline vfloat32m1_t
jbm_exp2wc_nxf32 (const vfloat32m1_t x,
                  ///< vfloat32m1_t vector \f$\in[\frac12,1]\f$.
                  const size_t vl)      ///< array size.
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
  return jbm_polynomial_6_nxf32 (x, a, vl);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_nxf32 and
 * jbm_exp2n_nxf32 functions (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_exp2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f, y;
  vint32m1_t i;
  i = jbm_floor_nxf32 (x, vl);
  f = __riscv_vfsub_vv_f32m1 (x, vfcvt_f_x_v_i32m1 (i, vl), vl);
  y = jbm_exp2n_nxf32 (i, vl);
  return __riscv_vfmul_vv_f32m1 (y, jbm_exp2wc_nxf32 (f, vl), vl);
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_nxf32 function
 * (vfloat32m1_t).
 *
 * \return function value.
 */
static inline vfloat32m1_t
jbm_exp_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< array size.
{
  return jbm_exp2_nxf32 (__riscv_vfmul_vf_f32m1 (x, M_LOG2Ef, vl), vl);
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_nxf32
 * function (vfloat32m1_t).
 *
 * \return function value.
 */
static inline vfloat32m1_t
jbm_exp10_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                 const size_t vl)       ///< array size.
{
  return jbm_exp2_nxf32 (__riscv_vfmul_vf_f32m1 (x, M_LN10f / M_LN2f, vl), vl);
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_nxf32 and
 * jbm_exp_nxf32 functions (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_expm1_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                 const size_t vl)       ///< array size.
{
  return __riscv_vmerge_vvm_f32m1 (jbm_expm1wc_nxf32 (x, vl),
                           __riscv_vfsub_vf_f32m1 (jbm_exp_nxf32 (x, vl), 1.f, vl),
                           __riscv_vmflt_vf_f32m1 (jbm_abs_nxf32 (x, vl), M_LN2f / 2.f,
                                           vl), vl);
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_log2wc_nxf32 (const vfloat32m1_t x,
                  ///< vfloat32m1_t vector \f$\in[0.5,1]\f$.
                  const size_t vl)      ///< array size.
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
  return jbm_rational_6_3_nxf32 (x, a, vl);
}

/**
 * Function to calculate the function log_2(x) using jbm_log2wc_nxf32 and
 * jbm_frexp_nxf32 (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_log2_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t y;
  vint32m1_t e;
  y = jbm_frexp_nxf32 (x, &e, vl);
  y = __riscv_vfadd_vv_f32m1 (jbm_log2wc_nxf32 (y, vl), vfcvt_f_x_v_i32m1 (e, vl), vl);
  y = __riscv_vmerge_vfm_f32m1 (y, -INFINITY, vmfgt_vf_f32m1_b32 (x, 0.f, vl), vl);
  return __riscv_vmerge_vfm_f32m1 (y, NAN, vmfge_vf_f32m1_b32 (x, 0.f, vl), vl);
}

/**
 * Function to calculate the function log(x) using jbm_log2_nxf32
 * (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_log_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< array size.
{
  return __riscv_vfmul_vf_f32m1 (jbm_log2_nxf32 (x, vl), M_LN2f, vl);
}

/**
 * Function to calculate the function log10(x) using jbm_log2_nxf32.
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_log10_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t vector.
                 const size_t vl)       ///< array size.
{
  return __riscv_vfmul_vf_f32m1 (jbm_log2_nxf32 (x, vl), M_LN2f / M_LN10f, vl);
}

/**
 * Function to calculate the function x^e with e an integer number
 * (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t) (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_pown_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const int e,    ///< exponent (int).
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f, xn;
  unsigned int i;
  f = __riscv_vfmv_v_f_f32m1 (1.f, vl);
  if (e < 0)
    xn = jbm_reciprocal_nxf32 (x, vl);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_nxf32 (xn, vl))
    if (i & 1)
      f = __riscv_vfmul_vv_f32m1 (f, xn, vl);
  return f;
}

/**
 * Function to calculate the function pow using the jbm_exp2_nxf32 and
 * jbm_log2_nxf32 functions (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_pow_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const float e,   ///< exponent (float).
               const size_t vl) ///< array size.
{
  float f;
  f = floorf (e);
  if (f == e)
    return jbm_pown_nxf32 (x, (int) e, vl);
  return jbm_exp2_nxf32 (__riscv_vfmul_vf_f32m1 (jbm_log2_nxf32 (x, vl), e, vl), vl);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_nxf32 and
 * jbm_pow_nxf32 functions (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_cbrt_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f;
  f = jbm_abs_nxf32 (x, vl);
  f = jbm_pow_nxf32 (x, 1.f / 3.f, vl);
  return __riscv_vmerge_vvm_f32m1 (f, jbm_opposite_nxf32 (f, vl),
                           vmfltz_vf_f32m1_b32 (x, 0.f, vl), vl);
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (vfloat32m1_t)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_sinwc_nxf32 (const vfloat32m1_t x,
                 ///< vfloat32m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                 const size_t vl)       ///< array size.
{
  const float a[4] JB_ALIGNED = {
    9.9999999652998170520234859388240338e-01f,
    -1.6666653850132705938945722106817969e-01f,
    8.3322256622392457162205759786691734e-03f,
    -1.9524867674489682553254582414001857e-04f
  };
  return __riscv_vfmul_vv_f32m1 (x, jbm_polynomial_3_nxf32 (jbm_sqr_nxf32 (x, vl),
                                                    a, vl), vl);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (vfloat32m1_t):
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_coswc_nxf32 (const vfloat32m1_t x,
                 ///< vfloat32m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                 const size_t vl)       ///< array size.
{
  const float a[5] JB_ALIGNED = {
    1.0000000000000000000000000000000000e+00f,
    -4.9999999965238906843549904534867220e-01f,
    4.1666653828165636463917247496043632e-02f,
    -1.3887779469291056608109602187665577e-03f,
    2.4484799013341679093941386831846651e-05f
  };
  return jbm_polynomial_4_nxf32 (jbm_sqr_nxf32 (x, vl), a, vl);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_nxf32 approximation (vfloat32m1_t).
 */
static inline void
jbm_sincoswc_nxf32 (const vfloat32m1_t x,
                    ///< vfloat32m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    vfloat32m1_t * s,
                    ///< pointer to the sin function value (vfloat32m1_t).
                    vfloat32m1_t * c,
                    ///< pointer to the cos function value (vfloat32m1_t).
                    const size_t vl)    ///< array size.
{
  vfloat32m1_t s0;
  *s = s0 = jbm_sinwc_nxf32 (x, vl);
  *c = __riscv_vfsqrt_v_f32m1 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl),
                                       jbm_sqr_nxf32 (s0, vl), vl), vl);
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_nxf32 and
 * jbm_coswc_nxf32 approximations (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_sin_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat32m1_t y, s, pi2;
  pi2 = __riscv_vfmv_v_f_f32m1 (2.f * M_PIf, vl);
  y = jbm_rest_nxf32 (x, pi2, vl);
  s = jbm_sinwc_nxf32 (__riscv_vfsub_vv_f32m1 (y, pi2, vl), vl);
  s = __riscv_vmerge_vvm_f32m1
    (jbm_opposite_nxf32
     (jbm_coswc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (3.f * M_PI_2f, vl),
                                       y, vl), vl), vl),
     s, __riscv_vmflt_vf_f32m1_b32 (y, 7.f * M_PI_4f, vl), vl);
  s = __riscv_vmerge_vvm_f32m1
    (jbm_sinwc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PIf, vl), y, vl)),
     s, __riscv_vmflt_vf_f32m1_b32 (y, 5.f * M_PI_4f, vl));
  s = __riscv_vmerge_vvm_f32m1
    (jbm_coswc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PI_2f, vl), y, vl)),
     s, __riscv_vmflt_vf_f32m1_b32 (y, 3.f * M_PI_4f, vl), vl);
  return __riscv_vmerge_vvm_f32m1 (jbm_sinwc_nxf32 (y, vl), s,
                           __riscv_vmflt_vf_f32m1_b32 (y, M_PI_4f, vl), vl);
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_nxf32 and
 * jbm_coswc_nxf32 approximations (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_cos_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat32m1_t y, c, pi2;
  pi2 = __riscv_vfmv_v_f_f32m1 (2.f * M_PIf, vl);
  y = jbm_rest_nxf32 (x, pi2, vl);
  c = jbm_coswc_nxf32 (__riscv_vfsub_vv_f32m1 (y, pi2, vl), vl);
  c = __riscv_vmerge_vvm_f32m1 (jbm_sinwc_nxf32 (__riscv_vfsub_vf_f32m1 (y, 3.f * M_PI_2f, vl),
                                         vl),
                        c, __riscv_vmflt_vf_f32m1_b32 (y, 7.f * M_PI_4f, vl), vl);
  c = __riscv_vmerge_vvm_f32m1
    (jbm_opposite_nxf32
     (jbm_coswc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PIf, vl), y, vl),
                       vl), vl),
     c, __riscv_vmflt_vf_f32m1_b32 (y, 5.f * M_PI_4f, vl), vl);
  c = __riscv_vmerge_vvm_f32m1
    (jbm_sinwc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PI_2f), y, vl), vl),
     c, __riscv_vmflt_vf_f32m1_b32 (y, 3.f * M_PI_4f, vl), vl);
  return __riscv_vmerge_vfm_f32m1 (jbm_coswc_nxf32 (y, vl), c,
                           __riscv_vmflt_vf_f32m1_b32 (y, M_PI_4f, vl), vl);
}

/**
 * Function to calculate the functions sin(x) and cos(x) from
 * jbm_sinwc_nxf32 and jbm_coswc_nxf32 approximations (vfloat32m1_t).
 */
static inline void
jbm_sincos_nxf32 (const vfloat32m1_t x,
                  ///< vfloat32m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  vfloat32m1_t * s,
                  ///< pointer to the sin function value (vfloat32m1_t).
                  vfloat32m1_t * c,
                  ///< pointer to the cos function value (vfloat32m1_t).
                  const size_t vl)      ///< array size.
{
  vfloat32m1_t y, pi2, s1, c1, s2, c2;
  vbool32_t m;
  pi2 = __riscv_vfmv_v_f_f32m1 (2.f * M_PIf, vl);
  y = jbm_rest_nxf32 (x, pi2, vl);
  jbm_sincoswc_nxf32 (__riscv_vfsub_vv_f32m1 (y, pi2, vl), &s1, &c1, vl);
  jbm_sincoswc_nxf32 (__riscv_vfsub_vf_f32m1 (y, 3.f * M_PI_2f, vl), &c2, &s2, vl);
  m = __riscv_vmflt_vf_f32m1_b32 (y, 7.f * M_PI_4f, vl);
  s1 = __riscv_vmerge_vvm_f32m1 (jbm_opposite_nxf32 (s2, vl), s1, m, vl);
  c1 = __riscv_vmerge_vvm_f32m1 (c2, c1, m, vl);
  jbm_sincoswc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PIf), y, vl),
                      &s2, &c2, vl);
  m = __riscv_vmflt_vf_f32m1_b32 (y, 5.f * M_PI_4f, vl);
  s1 = __riscv_vmerge_vvm_f32m1 (s2, s1, m, vl);
  c1 = __riscv_vmerge_vvm_f32m1 (jbm_opposite_nxf32 (c2, vl), c1, m, vl);
  jbm_sincoswc_nxf32 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PI_2f), y, vl),
                      &c2, &s2, vl);
  m = __riscv_vmflt_vf_f32m1_b32 (y, 3.f * M_PI_4f, vl);
  s1 = __riscv_vmerge_vvm_f32m1 (s2, s1, m, vl);
  c1 = __riscv_vmerge_vvm_f32m1 (c2, c1, m, vl);
  jbm_sincoswc_nxf32 (y, &s2, &c2, vl);
  m = __riscv_vmflt_vf_f32m1_b32 (y, M_PI_4f, vl);
  *s = __riscv_vmerge_vvm_f32m1 (s2, s1, m, vl);
  *c = __riscv_vmerge_vvm_f32m1 (c2, c1, m, vl);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_nxf32 function
 * (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_tan_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat32m1_t s, c;
  jbm_sincos_nxf32 (x, &s, &c, vl);
  return __riscv_vfdiv_vv_f32m1 (s, c, vl);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_atanwc0_nxf32 (const vfloat32m1_t x,
                   ///< vfloat32m1_t vector \f$\in\left[0,\frac12\right]\f$.
                   const size_t vl)     ///< array size.
{
  const float a[4] JB_ALIGNED = {
    9.9999984048730143841335295268244848e-01f,
    4.9566847198521400589504493089955823e-01f,
    8.2898705878810240458099950004542931e-01f,
    7.6658333542753920209846592962853791e-02f
  };
  return __riscv_vfmul_vv_f32m1 (x, jbm_rational_3_1_nxf32 (jbm_sqr_nxf32 (x, vl),
                                                    a, vl), vl);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (vfloat32m1_t).
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_atanwc1_nxf32 (const vfloat32m1_t x,
                   ///< vfloat32m1_t vector \f$\in\left[\frac12,1\right]\f$.
                   const size_t vl)     ///< array size.
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
  return jbm_rational_7_3_nxf32 (__riscv_vfsub_vf_f32m1 (x, 1.f, vl), a, vl);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_nxf32 and
 * jbm_atanwc1_nxf32 functions (vfloat32m1_t).
 *
 * \return function value (in [-pi/2,pi/2]) (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_atan_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f, ax;
  vbool32_t m;
  ax = jbm_abs_nxf32 (x, vl);
  m = vmfgt_vf_f32m1_b32 (ax, 1.5f, vl);
  ax = __riscv_vmerge_vvm_f32m1 (jbm_reciprocal_nxf32 (ax, vl), ax, m, vl);
  f = __riscv_vmerge_vvm_f32m1 (jbm_atanwc1_nxf32 (ax, vl), jbm_atanwc0_nxf32 (ax, vl),
                        vmfgt_vf_f32m1_b32 (ax, 0.5f, vl), vl);
  f = __riscv_vmerge_vvm_f32m1 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (M_PI_2f, vl), f, vl), f,
                        m, f);
  return __riscv_vmerge_vvm_f32m1 (jbm_opposite_nxf32 (f), f,
                           __riscv_vmflt_vf_f32m1_b32 (x, 0.f, vl), vl);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_nxf32
 * function (vfloat32m1_t).
 *
 * \return function value (in [-pi,pi]) (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_atan2_nxf32 (const vfloat32m1_t y,  ///< vfloat32m1_t y component.
                 const vfloat32m1_t x,  ///< vfloat32m1_t x component.
                 const size_t vl)       ///< array size.
{
  vfloat32m1_t f;
  vbool32_t mx, my;
  f = jbm_atan_nxf32 (__riscv_vfdiv_vv_f32m1 (y, x, vl), vl);
  mx = __riscv_vmflt_vf_f32m1_b32 (x, 0.f, vl);
  my = vmvlt_vf_f32m1_b32 (y, 0.f, vl);
  f = __riscv_vmerge_vvm_f32m1 (__riscv_vfsub_vf_f32m1 (f, M_PIf, vl), f,
                        __riscv_vmand_mm (my, mx, vl), vl);
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfadd_vf_f32m1 (f, M_PIf, vl), f,
                           __riscv_vmand_mm (my, vmnot_m (mx, vl), vl), vl);
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_nxf32 function
 * (vfloat32m1_t).
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline vfloat32m1_t
jbm_asin_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  return
    jbm_atan_nxf32
    (__riscv_vfdiv_vv_f32m1 (x,
                     __riscv_vfsqrt_v_f32m1 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl),
                                                     jbm_sqr_nxf32 (x, vl), vl),
                                     vl), vl), vl);
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_nxf32 function
 * (vfloat32m1_t).
 *
 * \return function value (in [0,pi]) (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_acos_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f;
  f =
    jbm_atan_nxf32 (__riscv_vfdiv_vv_f32m1
                    (__riscv_vfsqrt_v_f32m1 (__riscv_vfsub_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl),
                                                     jbm_sqr_nxf32 (x, vl), vl),
                                     x), vl), vl);
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfadd_vf_f32m1 (f, M_PIf, vl), f,
                           __riscv_vmflt_vf_f32m1 (x, 0.f, vl), vl);
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_sinh_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f;
  f = jbm_exp_nxf32 (x, vl);
  return __riscv_vfmul_vf_f32m1 (__riscv_vfsub_vv_f32m1 (f, jbm_reciprocal_nxf32 (f, vl), vl),
                         0.5f, vl);
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_cosh_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f;
  f = jbm_exp_nxf32 (x, vl);
  return __riscv_vfmul_vf_f32m1 (__riscv_vfadd_vv_f32m1 (f, jbm_reciprocal_nxf32 (f, vl), vl),
                         0.5f, vl);
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_tanh_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t f, fi;
  f = jbm_exp_nxf32 (x, vl);
  fi = jbm_reciprocal_nxf32 (f, vl);
  f = __riscv_vfdiv_vv_f32m1 (__riscv_vfsub_vv_f32m1 (f, fi, vl), __riscv_vfadd_vv_f32m1 (f, fi, vl),
                      vl);
  f = __riscv_vmerge_vvm_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), f,
                        vmfgt_vf_f32m1_b32 (x, JBM_FLT_MAX_E_EXP, vl), vl);
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfmv_v_f_f32m1 (-1.f), f,
                           __riscv_vmflt_vf_f32m1_b32 (x, -JBM_FLT_MAX_E_EXP, vl), vl);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_asinh_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t number.
                 const size_t vl)       ///< array size.
{
  return
    jbm_log_nxf32
    (__riscv_vfadd_vv_f32m1
     (x, __riscv_vfsqrt_v_f32m1 (__riscv_vfmacc_vv_f32m1 (__riscv_vfmv_v_f_f32m1 (1.f, vl), x, x, vl),
                         vl), vl), vl);
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_acosh_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t number.
                 const size_t vl)       ///< array size.
{
  return
    jbm_log_nxf32
    (__riscv_vfadd_vv_f32m1 (x, __riscv_vfsqrt_v_f32m1 (__riscv_vfsub_vf_f32m1 (jbm_sqr_nxf32 (x, vl),
                                                        1.f, vl), vl), vl), vl);
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_atanh_nxf32 (const vfloat32m1_t x,  ///< vfloat32m1_t number.
                 const size_t vl)       ///< array size.
{
  vfloat32m1_t u;
  u = __riscv_vfmv_v_f_f32m1 (1.f);
  return
    __riscv_vfmul_vf_f32m1 (jbm_log_nxf32 (__riscv_vfdiv_vv_f32m1 (__riscv_vfadd_vv_f32m1 (u, x, vl),
                                                   __riscv_vfsub_vv_f32m1 (u, x, vl),
                                                   vl), 0.5f, vl), vl);
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (vfloat32m1_t)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_erfwc_nxf32 (const vfloat32m1_t x,
                 ///< vfloat32m1_t vector \f$\in\left[-1,1\right]\f$.
                 const size_t vl)       ///< array size.
{
  const float a[6] JB_ALIGNED = {
    1.1283791671633124547603970137089329e+00f,
    1.1356247077387072221530473806173895e-01f,
    3.3606359392673594485175487779855494e-02f,
    4.3397545597876753616401102540952801e-01f,
    7.4441296041206635020857929305718177e-02f,
    5.2260592856163505486272407800095742e-03f
  };
  return __riscv_vfmul_vv_f32m1 (x, jbm_rational_5_2_nxf32 (jbm_sqr_nxf32 (x, vl),
                                                    a, vl), vl);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (vfloat32m1_t)
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_erfcwc_nxf32 (const vfloat32m1_t x,
                  ///< vfloat32m1_t vector \f$\in\left[1,\infty\right]\f$.
                  const size_t vl)      ///< array size.
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
  vfloat32m1_t f, x2;
  x2 = jbm_sqr_nxf32 (x, vl);
  f = __riscv_vfdiv_vv_f32m1 (jbm_rational_6_3_nxf32 (jbm_reciprocal_nxf32 (x2, vl), a,
                                              vl),
                      __riscv_vfmul_vv_f32m1 (x, jbm_exp_nxf32 (x2, vl), vl), vl);
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfmv_v_f_f32m1 (0.f), f,
                           vmfgt_vf_f32m1_b32 (x, m, vl), vl);

}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_nxf32 and
 * jbm_erfcwc_nxf32
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_erf_nxf32 (const vfloat32m1_t x,    ///< vfloat32m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat32m1_t ax, u, f;
  ax = jbm_abs_nxf32 (x, vl);
  u = __riscv_vfmv_v_f_f32m1 (1.f, vl);
  f = __riscv_vfmul_vv_f32m1 (__riscv_vfdiv_vv_f32m1 (x, ax, vl),
                      __riscv_vfsub_vv_f32m1 (u, jbm_erfcwc_nxf32 (ax, vl), vl), vl);
  return __riscv_vmerge_vvm_f32m1 (jbm_erfwc_nxf32 (x, vl), f,
                           __riscv_vmflt_vv_f32m1_b32 (ax, u, vl), vl);
}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_nxf32 and
 * jbm_erfcwc_nxf32
 *
 * \return function value (vfloat32m1_t).
 */
static inline vfloat32m1_t
jbm_erfc_nxf32 (const vfloat32m1_t x,   ///< vfloat32m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat32m1_t ax, u, f;
  ax = jbm_abs_nxf32 (x, vl);
  u = __riscv_vfmv_v_f_f32m1 (1.f, vl);
  f = __riscv_vfsub_vv_f32m1 (u,
                      __riscv_vfmul_vv_f32m1 (__riscv_vfdiv_vv_f32m1 (x, ax, vl),
                                      __riscv_vfsub_vv_f32m1 (u,
                                                      jbm_erfcwc_nxf32 (ax, vl),
                                                      vl), vl), vl);
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfsub_vv_f32m1 (u, jbm_erfwc_nxf32 (x, vl), vl), f,
                           __riscv_vmflt_vv_f32m1_b32 (ax, u, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat32m1_t vector of reduced
 * quadratic equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return vfloat32m1_t vector of solution values.
 */
static inline vfloat32m1_t
jbm_solve_quadratic_reduced_nxf32 (vfloat32m1_t a,
///< vfloat32m1_t vector of 1st order coefficient of the equations.
                                   vfloat32m1_t b,
///< vfloat32m1_t vector of 0th order coefficient of the equations.
                                   const vfloat32m1_t x1,
///< vfloat32m1_t vector of left limits of the solution intervals.
                                   const vfloat32m1_t x2,
///< vfloat32m1_t vector of right limits of the solution intervals.
                                   const size_t vl)     ///< array size.
{
  vfloat32m1_t k1, k2;
  a = __riscv_vfmul_vf_f32m1 (a, -0.5f, vl);
  b = __riscv_vfsqrt_v_f32m1 (__riscv_vfsub_vv_f32m1 (jbm_sqr_nxf32 (a, vl), b, vl), vl);
  k1 = __riscv_vfadd_vv_f32m1 (a, b, vl);
  k2 = __riscv_vfsub_vv_f32m1 (a, b, vl);
  k1 = __riscv_vmerge_vvm_f32m1 (k2, k1, __riscv_vmflt_vv_f32m1_b32 (k1, x1, vl), vl);
  return __riscv_vmerge_vvm_f32m1 (k2, k1, vmfgt_vv_f32m1_b32 (k1, x2, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat32m1_t vector of quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return vfloat32m1_t vector of solution values.
 */
static inline vfloat32m1_t
jbm_solve_quadratic_nxf32 (const vfloat32m1_t a,
///< vfloat32m1_t vector of 2nd order coefficient of the equations.
                           const vfloat32m1_t b,
///< vfloat32m1_t vector of 1st order coefficient of the equations.
                           const vfloat32m1_t c,
///< vfloat32m1_t vector of 0th order coefficient of the equations.
                           const vfloat32m1_t x1,
///< vfloat32m1_t vector of left limits of the solution intervals.
                           const vfloat32m1_t x2,
///< vfloat32m1_t vector of right limits of the solution intervals.
                           const size_t vl)     ///< array size.
{
  vfloat32m1_t k1, k2;
  k1 = jbm_solve_quadratic_reduced_nxf32 (__riscv_vfdiv_vv_f32m1 (b, a, vl),
                                          __riscv_vfdiv_vv_f32m1 (c, a, vl),
                                          x1, x2, vl);
  k2 = __riscv_vfdiv_vv_f32m1 (jbm_opposite_nxf32 (c, vl), b, vl);
  return __riscv_vmerge_vvm_f32m1 (k2, k1, jbm_small_nxf32 (a, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat32m1_t vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return vfloat32m1_t vector of solution values.
 */
static inline vfloat32m1_t
jbm_solve_cubic_reduced_nxf32 (const vfloat32m1_t a,
                               ///< 2nd order coefficient of the equation.
                               const vfloat32m1_t b,
                               ///< 1st order coefficient of the equation.
                               const vfloat32m1_t c,
                               ///< 0th order coefficient of the equation.
                               const vfloat32m1_t x1,
                               ///< left limit of the solution interval.
                               const vfloat32m1_t x2,
                               ///< right limit of the solution interval.
                               const size_t vl) ///< array size.
{
  vfloat32m1_t a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2;
  a3 = __riscv_vfmul_vf_f32m1 (a, 1.f / 3.f, vl);
  k0 = jbm_sqr_nxf32 (a3, vl);
  k1 = __riscv_vfsub_vv_f32m1 (k0, __riscv_vfmul_vf_f32m1 (b, 1.f / 3.f, vl), vl);
  k0 = __riscv_vfsub_vv_f32n1
    (__riscv_vfmul_vv_f32m1 (a3, k0, vl),
     __riscv_vfmul_vf_f32m1 (__riscv_vfsub_vv_f32m1 (b,
                                     __riscv_vfmul_vv_f32m1 (a3, c, vl), 0.5f, vl),
                     vl), vl);
  k3 = __riscv_vfmul_vv_f32m1 (k1, jbm_sqr_nxf32 (k1, vl), vl);
  k2 = __riscv_vfmacc_vv_f32m1 (k3, k0, k0, vl);
  l1 = __riscv_vfsqrt_v_f32m1 (jbm_opposite_nxf32 (k1, vl), vl);
  l0 = __riscv_vfmul_vf_f32m1 (jbm_acos_nxf32 (__riscv_vfdiv_vv_f32m1 (k0, k3, vl), vl),
                       1.f / 3.f, vl);
  l1 = jbm_dbl_nxf32 (l1);
  l2 = __riscv_vfsub_vv_f32m1 (a3, __riscv_vfmul_vv_f32m1 (l1, jbm_cos_nxf32 (k0, vl), vl), vl);
  l3 = __riscv_vfsub_vv_f32m1
    (a3, __riscv_vfmul_vv_f32m1
     (l1, jbm_cos_nxf32 (__riscv_vfadd_vf_f32m1 (l0, 2.f * M_PIf / 3.f, vl), vl),
      vl), vl);
  l3 = __riscv_vmerge_vvm_f32m1 (l2, l3,
                         __riscv_vmor_mm (__riscv_vmflt_vv_f32m1_b32 (l2, x1, vl),
                                  vmfgt_vv_f32m1_b32 (l2, x2, vl), vl), vl);
  l4 = __riscv_vfsub_vv_f32m1
    (a, __riscv_vfmul_vv_f32m1
     (l1, jbm_cos_nxf32 (__riscv_vfsub_vf_f32m1 (l0, 2.f * M_PIf / 3.f, vl), vl),
      vl), vl);
  l4 = __riscv_vmerge_vvm_f32m1 (l3, l4,
                         __riscv_vmor_mm (__riscv_vmflt_vv_f32m1_b32 (l3, x1, vl),
                                  vmfgt_vv_f32m1_b32 (l3, x2, vl), vl), vl);
  k1 = __riscv_vfsqrt_v_f32m1 (k2, vl);
  l5 = __riscv_vfadd_vv_f32m1 (k0, k1, vl);
  l5 = jbm_cbrt_nxf32 (k2, vl);
  k0 = __riscv_vfsub_vv_f32m1 (k0, k1, vl);
  l5 = __riscv_vfadd_vv_f32m1 (l5, __riscv_vfsub_vv_f32m1 (jbm_cbrt_nxf32 (k0, vl), a3, vl),
                       vl);
  return __riscv_vmerge_vvm_f32m1 (l5, l4, __riscv_vmflt_vf_f32m1_b32 (k2, 0.f, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat32m1_t vector of cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return vfloat32m1_t vector of solution values.
 */
static inline vfloat32m1_t
jbm_solve_cubic_nxf32 (vfloat32m1_t a,
///< vfloat32m1_t vector of 3rd order coefficient of the equations.
                       vfloat32m1_t b,
///< vfloat32m1_t vector of 2nd order coefficient of the equations.
                       vfloat32m1_t c,
///< vfloat32m1_t vector of 1st order coefficient of the equations.
                       vfloat32m1_t d,
///< vfloat32m1_t vector of 0th order coefficient of the equations.
                       vfloat32m1_t x1,
///< vfloat32m1_t vector of left limits of the solution intervals.
                       vfloat32m1_t x2,
///< vfloat32m1_t vector of right limits of the solution intervals.
                       const size_t vl) ///< array size.
{
  return
    __riscv_vmerge_vvm_f32m1
    (jbm_solve_quadratic_nxf32 (b, c, d, x1, x2, vl),
     jbm_solve_cubic_reduced_nxf32 (__riscv_vfdiv_vv_f32m1 (b, a, vl),
                                    __riscv_vfdiv_vv_f32m1 (c, a, vl),
                                    __riscv_vfdiv_vv_f32m1 (d, a, vl), x1, x2, vl),
     jbm_small_nxf32 (a, vl), vl);

}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_total_nxf32 (const vfloat32m1_t d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const vfloat32m1_t d2 __attribute__((unused)),
                              ///< 2nd flux limiter function parameter.
                              const size_t vl)  ///< array size.
{
  return __riscv_vfmv_v_f_f32m1 (0.f, vl);
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_null_nxf32 (const vfloat32m1_t d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const vfloat32m1_t d2 __attribute__((unused)),
                             ///< 2nd flux limiter function parameter.
                             const size_t vl)   ///< array size.
{
  return __riscv_vfmv_v_f_f32m1 (1.f, vl);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_centred_nxf32 (const vfloat32m1_t d1,
                                ///< 1st flux limiter function parameter.
                                const vfloat32m1_t d2,
                                ///< 2nd flux limiter function parameter.
                                const size_t vl)        ///< array size.
{
  return __riscv_vmerge_vvm_f32m1 (__riscv_vfmv_v_f_f32m1 (0.f, vl),
                           __riscv_vfdiv_vv_f32m1 (d1, d2, vl),
                           jbm_small_nxf32 (d2, vl), vl);
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_superbee_nxf32 (const vfloat32m1_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const vfloat32m1_t d2,
                                 ///< 2nd flux limiter function parameter.
                                 const size_t vl)       ///< array size.
{
  vfloat32m1_t r;
  r = __riscv_vfdiv_vv_f32m1 (d1, d2, vl);
  r = vfmax_vv_f32m1 (vfmin_vf_f32m1 (jbm_dbl_nxf32 (r), 1.f, vl),
                      vfmin_vf_f32m1 (r, 2.f, vl), vl);
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_minmod_nxf32 (const vfloat32m1_t d1,
                               ///< 1st flux limiter function parameter.
                               const vfloat32m1_t d2,
                               ///< 2nd flux limiter function parameter.
                               const size_t vl) ///< array size.
{
  vfloat32m1_t r;
  r = vfmin_vf_f32m1 (__riscv_vfdiv_vv_f32m1 (d1, d2, vl), 1.f, vl);
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_VanLeer_nxf32 (const vfloat32m1_t d1,
                                ///< 1st flux limiter function parameter.
                                const vfloat32m1_t d2,
                                ///< 2nd flux limiter function parameter.
                                const size_t vl)        ///< array size.
{
  vfloat32m1_t r, k;
  r = __riscv_vfdiv_vv_f32m1 (d1, d2, vl);
  k = jbm_abs_nxf32 (r, vl);
  r = __riscv_vfdiv_vv_f32m1 (__riscv_vfadd_vv_f32m1 (r, k, vl), __riscv_vfadd_vf_f32m1 (k, 1.f, vl),
                      vl);
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_VanAlbada_nxf32 (const vfloat32m1_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const vfloat32m1_t d2,
                                  ///< 2nd flux limiter function parameter.
                                  const size_t vl)      ///< array size.
{
  vfloat32m1_t r, k;
  r = __riscv_vfdiv_vv_f32m1 (d1, d2, vl);
  k = jbm_sqr_nxf32 (r, vl);
  r = __riscv_vfdiv_vv_f32m1 (__riscv_vfadd_vv_f32m1 (r, k, vl), __riscv_vfadd_vf_f32m1 (k, 1.f, vl),
                      vl);
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_minsuper_nxf32 (const vfloat32m1_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const vfloat32m1_t d2,
                                 ///< 2nd flux limiter function parameter.
                                 const size_t vl)       ///< array size.
{
  vfloat32m1_t r;
  r = vfmin_vv_f32m1 (__riscv_vfdiv_vv_f32m1 (d1, d2), __riscv_vfmv_v_f_f32m1 (2.f));
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_supermin_nxf32 (const vfloat32m1_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const vfloat32m1_t d2,
                                 ///< 2nd flux limiter function parameter.
                                 const size_t vl)       ///< array size.
{
  vfloat32m1_t r;
  r = __riscv_vfdiv_vv_f32m1 (d1, d2, vl);
  r = vfmin_vf_f32m1 (jbm_dbl_nxf32 (r, vl), 1.f, vl);
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_monotonized_central_nxf32 (const vfloat32m1_t d1,
///< 1st flux limiter function parameter.
                                            const vfloat32m1_t d2,
///< 2nd flux limiter function parameter.
                                            const size_t vl)    ///< array size.
{
  vfloat32m1_t r, rm;
  r = __riscv_vfdiv_vv_f32m1 (d1, d2, vl);
  rm = __riscv_vfmul_vf_f32m1 (__riscv_vfadd_vf_f32m1 (r, 1.f, vl), 0.5f, vl);
  rm = __riscv_vmerge_vfm_f32m1 (rm, 2.f, __riscv_vmflt_vf_f32m1_b32 (r, 3.f, vl), vl);
  rm = __riscv_vmerge_vfm_f32m1 (jbm_dbl_nxf32 (r, vl), rm,
                         vmfgt_vf_f32m1 (r, 1.f / 3.f, vl), vl);
  return __riscv_vmerge_vfm_f32m1 (rm, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_mean_nxf32 (const vfloat32m1_t d1,
                             ///< 1st flux limiter function parameter.
                             const vfloat32m1_t d2,
                             ///< 2nd flux limiter function parameter.
                             const size_t vl)   ///< array size.
{
  vfloat32m1_t r;
  r = __riscv_vfmul_vf_f32m1 (__riscv_vfadd_vf_f32m1 (__riscv_vfdiv_vv_f32m1 (d1, d2, vl), 1.f, vl),
                      0.5f, vl);
  return __riscv_vmerge_vfm_f32m1 (r, 0.f,
                           vmfgt_vf_f32m1 (__riscv_vfmul_vv_f32m1 (d1, d2, vl),
                                           FLT_EPSILON, vl), vl);
}

/**
 * Function to do a flux limiter function (vfloat32m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat32m1_t
jbm_flux_limiter_nxf32 (const vfloat32m1_t d1,
                        ///< 1st flux limiter function parameter.
                        const vfloat32m1_t d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type,
                        ///< type of flux limiter function.
                        const size_t vl)        ///< array size.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_nxf32 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_nxf32 (d1, d2, vl);
    }
  return jbm_flux_limiter_mean_nxf32 (d1, d2, vl);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (vfloat32m1_t).
 *
 * \return vfloat32m1_t vector of integral values.
 */
static inline vfloat32m1_t
jbm_integral_nxf32 (vfloat32m1_t (*f) (const vfloat32m1_t, const size_t),
                    ///< pointer to the function to integrate.
                    const vfloat32m1_t x1,      ///< left limit of the interval.
                    const vfloat32m1_t x2,
                    ///< right limit of the interval.
                    const size_t vl)    ///< array size.
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
  vfloat32m1_t k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  vfloat32m1_t k2, f1, f2;
#endif
  unsigned int i;
  dx = __riscv_vfmul_vf_f32m1 (__riscv_vfsub_vv_f32m1 (x2, x1, vl), 0.5f, vl);
  x = __riscv_vfmul_vf_f32m1 (__riscv_vfadd_vv_f32m1 (x2, x1, vl), 0.5f, vl);
  k = __riscv_vfmul_vf_f32m1 (f (x, vl), a[0], vl);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = __riscv_vfmul_vf_f32m1 (dx, b[i], vl);
      f1 = f (__riscv_vfsub_vv_f32m1 (x, k2, vl), vl);
      f2 = f (__riscv_vfadd_vv_f32m1 (x, k2, vl), vl);
      k = __riscv_vfmacc_vf_f32m1 (k, a[i], __riscv_vfadd_vv_f32m1 (f1, f2, vl), vl);
    }
#endif
  k = __riscv_vfmul_vv_f32m1 (k, dx, vl);
  return k;
}

/**
 * Function to calculate the additive inverse value of a vfloat64m1_t vector.
 *
 * \return negative value vector (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_opposite_nxf64 (const vfloat64m1_t x,       ///< vfloat64m1_t vector.
                    const size_t vl)    ///< vector size.
{
  return __riscv_vfneg_v_f64m1 (x, vl);
}

/**
 * Function to calculate the multiplicative inverse value of a vfloat64m1_t
 * vector.
 *
 * \return reciprocal value vector (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_reciprocal_nxf64 (const vfloat64m1_t x,     ///< vfloat64m1_t vector.
                      const size_t vl)  ///< vector size.
{
  return __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x, vl);
}

/**
 * Function to calculate the absolute value of a vfloat64m1_t vector.
 *
 * \return absolute value vector.
 */
static inline vfloat64m1_t
jbm_abs_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< vector size.
{
  return __riscv_vfabs_v_f64m1 (x, vl);
}

/**
 * Function to calculate the hypot function (vfloat64m1_t).
 *
 * \return function value vector (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_hypot_nxf64 (const vfloat64m1_t x,  ///< 1st vfloat64m1_t vector.
                 const vfloat64m1_t y,  ///< 2nd vfloat64m1_t vector.
                 const size_t vl)       ///< vector size.
{
  return __riscv_vfsqrt_v_f64m1 (__riscv_vfmacc_vv_f64m1 (jbm_sqr_nxf64 (x, vl), y, y, vl), vl);
}

/**
 * Function to calculate the rounding towards negative infinity.
 +
 + \return function value vector (vint64m1_t).
 */
static inline vint64m1_t
jbm_floor_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 const size_t vl)       ///< vector size.
{
  vint64m1_t i, i1;
  vbool64m1_t m;
  i = __riscv_vfcvt_rtz_x_f64m1 (x, vl);
  i1 = __riscv_vadd_vx_i64m1 (i, -1);
  m = __riscv_vmflt_vf_f64m1_b64 (x, 0., vl);
  return __riscv_vmerge_vvm_i64m1 (i1, i, m, vl);
}

/**
 * Function to calculate the rest of a division (vfloat64m1_t).
 *
 * \return rest value (in [0,|divisor|) interval) (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_rest_nxf64 (const vfloat64m1_t x,   ///< dividend (vfloat64m1_t).
                const vfloat64m1_t d,   ///< divisor (vfloat64m1_t).
                const size_t vl)        ///< vector size.
{
  return
    __riscv_vfsub_vv_f64m1 (x,
                    __riscv_vfmul_vv_f64m1 (jbm_floor_nxf64 (__riscv_vfdiv_vv_f64m1 (x, d, vl),
                                                     vl), d, vl), vl);
}

/**
 * Function to implement the standard frexp function (vfloat64m1_t).
 *
 * \return normalized fraction value in [1/2,1).
 */
static inline vfloat64m1_t
jbm_frexp_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 vint64m1_t * e,        ///< pointer to the extracted exponents vector.
                 const size_t vl)       ///< vector size.
{
  JBMNxF64 a, y, y2, z;
  vint64m1_t en;
  vbool64m1_t m1, m2, m3;
  a.x = x;
  b = __riscv_vfmv_v_x_u64m1 ();
  y.i = __riscv_vand_vx_u64m1 (a.i, 0x7ff0000000000000L, vl);
  m1 = __riscv_vmfeq_vx_u64m1_b64 (y.i, 0x7ff0000000000000L, vl);
  m2 = __riscv_vmfeq_vx_u64m1_b64 (y.i, 0L, vl);
  y2.x = x;
  y2.i = __riscv_vand_vx_u64m1 (y2.i, 0x000fffffffffffffL, vl);
  m3 = __riscv_vmfeq_vx_u64m1_b64 (y2.i, 0L, vl);
  y2.i = __riscv_vfmv_v_x_u64m1 (0x0010000000000000L, vl);
  z.x = __riscv_vfdiv_vv_f64m1 (x, y2.x, vl);
  z.i = __riscv_vand_vx_u64m1 (z.i, 0x7ff0000000000000L, vl);
  en = __riscv_vmerge_vvm_i64m1 (__riscv_vsub_vx_i64m1 (__riscv_vshra_vi_i64m1 ((vint64m1_t) z.i, 52,
                                                        vl), 2044L, vl),
                         __riscv_vsub_vx_i64m1 (__riscv_vshra_vi_i64m1 ((vint64m1_t) y.i, 52,
                                                        vl), 1022L, vl), m2,
                         vl);
  y.x = __riscv_vmerge_vvm_f64m1 (__riscv_vfmul_vv_f64m1 (y2.x, z.x, vl), y.x, m2, vl);
  en = __riscv_vmerge_vvm_i64m1 (__riscv_vmv_v_x_i64m1 (0L, vl), en,
                         __riscv_vmor_mm (m1, __riscv_vmand_mm (m2, m3, vl), vl), vl);
  *e = en;
  return __riscv_vmerge_vvm_f64m1 (x, __riscv_vfmul_vf_f64m1 (__riscv_vfdiv_vv_f64m1 (x, y.x, vl), 0.5,
                                              vl), m1, vl);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer vector
 * (vint64m1_t)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_exp2n_nxf64 (vint64m1_t e,  ///< exponent vector (vint64m1_t).
                 const size_t vl)       ///< vector size.
{
  vfloat64m1_t x;
  x = __riscv_vmerge_vvm_f64m1
    ((vfloat64m1_t) __riscv_vshla_vi_i64m1 (__riscv_vadd_vx_i64m1 (e, 1023L, vl), 52, vl),
     (vfloat64m1_t) __riscv_vshra_vv_i64m1 (__riscv_vmv_v_x_i64m1 (0x0008000000000000L, vl),
                                    __riscv_vsub_vx_i64m1 (e, -1023L, vl)),
     vmgt_vx_i64m1_b64 (e, -1023L, vl));
  x = __riscv_vmerge_vvm_f64m1 (__riscv_vfmv_v_f_f64m1 (0., vl), x,
                        vmlt_vx_i64m1_b64 (e, -1074L, vl), vl);
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfmv_v_f_f64m1 (INFINITY, vl), x,
                           vmgt_vx_i64m1_b64 (e, 1023L, vl), vl);
}

/**
 * Function to implement the standard ldexp function (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_ldexp_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 vint64m1_t e,  ///< exponent vector (vint64m1_t).
                 const size_t vl)       ///< vector size.
{
  return __riscv_vfmul_vv_f64m1 (x, jbm_exp2n_nxf64 (e, vl), vl);
}

/**
 * Function to check small vfloat64m1_t vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline vbool64m1_t
jbm_small_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 const size_t vl)       ///< vector size.
{
  return __riscv_vmflt_vf_f64m1_b32 (jbm_abs_nxf64 (x, vl), DBL_EPSILON, vl);
}

/**
 * Function to calculate the vfloat64m1_t vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin vfloat64m1_t vector.
 */
static inline vfloat64m1_t
jbm_modmin_nxf64 (const vfloat64m1_t a, ///< 1st vfloat64m1_t vector.
                  const vfloat64m1_t b, ///< 2nd vfloat64m1_t vector.
                  const size_t vl)      ///< vector size.
{
  vfloat64m1_t aa, ab, y;
  ab = __riscv_vfmul_vv_f64m1 (a, b, vl);
  y = __riscv_vmerge_vfm_f64m1 (a, 0., vmfgt_vf_f64m1_b64 (ab, 0., vl)), vl;
  aa = jbm_abs_nxf64 (y, vl);
  ab = jbm_abs_nxf64 (b, vl);
  return __riscv_vmerge_vvm_f64m1 (b, y, vmfgt_vv_f64m1_b64 (aa, ab, vl), vl);
}

/**
 * Function to interchange 2 vfloat64m1_t numbers.
 */
static inline void
jbm_change_nxf64 (vfloat64m1_t * restrict a,
                  ///< 1st vfloat64m1_t vector pointer.
                  vfloat64m1_t * restrict b)
                  ///< 2nd vfloat64m1_t vector pointer.
{
  vfloat64m1_t c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a vfloat64m1_t vector.
 *
 * \return vfloat64m1_t double.
 */
static inline vfloat64m1_t
jbm_dbl_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< vector size.
{
  return __riscv_vfadd_vv_f64m1 (x, x, vl);
}

/**
 * Function to calculate the square of the components of a vfloat64m1_t vector.
 *
 * \return vfloat64m1_t vector square.
 */
static inline vfloat64m1_t
jbm_sqr_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< vector size.
{
  return __riscv_vfmul_vv_f64m1 (x, x, vl);
}

/**
 * Function to perform an extrapolation between 2 vfloat64m1_t vectors of 2D
 * points.
 *
 * \return vfloat64m1_t vector of y-coordinates of the extrapolated points.
 */
static inline vfloat64m1_t
jbm_extrapolate_nxf64 (const vfloat64m1_t x,
///< vfloat64m1_t vector of x-coordinates of the extrapolated points.
                       const vfloat64m1_t x1,
///< vfloat64m1_t vector of x-coordinates of the 1st points.
                       const vfloat64m1_t x2,
///< vfloat64m1_t vector of x-coordinates of the 2nd points.
                       const vfloat64m1_t y1,
///< vfloat64m1_t vector of y-coordinates of the 1st points.
                       const vfloat64m1_t y2,
///< vfloat64m1_t vector of y-coordinates of the 2nd points.
                       const size_t vl) ///< vector size.
{
  vfloat64m1_t d;
  d = __riscv_vfsub_vv_f64m1 (x, x1, vl);
  return __riscv_vfmacc_vv_f64m1 (y1, d,
                          __riscv_vfdiv_vv_f64m1 (__riscv_vfsub_vv_f64m1 (y2, y1, vl),
                                          __riscv_vfsub_vv_f64m1 (x2, x1, vl), vl), vl);
}

/**
 * Function to perform an interpolation between 2 vfloat64m1_t vectors of 2D
 * points.
 *
 * \return vfloat64m1_t vector of y-coordinates of the interpolated points.
 */
static inline vfloat64m1_t
jbm_interpolate_nxf64 (const vfloat64m1_t x,
///< vfloat64m1_t vector of x-coordinates of the interpolated points.
                       const vfloat64m1_t x1,
///< vfloat64m1_t vector of x-coordinates of the 1st points.
                       const vfloat64m1_t x2,
///< vfloat64m1_t vector of x-coordinates of the 2nd points.
                       const vfloat64m1_t y1,
///< vfloat64m1_t vector of y-coordinates of the 1st points.
                       const vfloat64m1_t y2,
///< vfloat64m1_t vector of y-coordinates of the 2nd points.
                       const size_t vl) ///< vector size.
{
  vfloat64m1_t k;
  k = jbm_extrapolate_nxf64 (x, x1, x2, y1, y2, vl);
  k = __riscv_vmerge_vvm_f64m1 (k, y1, vmfgt_vv_f64m1_b32 (x, x1, vl), vl);
  return __riscv_vmerge_vvm_f64m1 (k, y2, __riscv_vmflt_vv_f64m1_b32 (x, x2, vl), vl);
}

/**
 * Function to calculate the length of a vfloat64m1_t vector of 2D segments.
 *
 * \return vfloat64m1_t vector of segment lengths.
 */
static inline vfloat64m1_t
jbm_v2_length_nxf64 (const vfloat64m1_t x1,
///< vfloat64m1_t vector of x-coordinates of the 1st points defining the
///< segment.
                     const vfloat64m1_t y1,
///< vfloat64m1_t vector of y-coordinates of the 1st points defining the
///< segment.
                     const vfloat64m1_t x2,
///< vfloat64m1_t vector of x-coordinates of the 2nd points defining the
///< segment.
                     const vfloat64m1_t y2,
///< vfloat64m1_t vector of y-coordinates of the 2nd points defining the
///< segment.
                     const size_t vl)   ///< vector size.
{
  return jbm_hypot_nxf64 (__riscv_vfsub_vv_f64m1 (x2, x1, vl),
                          __riscv_vfsub_vv_f64m1 (y2, y1, vl), vl);
}

/**
 * Function to calculate the length of a vfloat64m1_t vector of 3D segments.
 *
 * \return vfloat64m1_t vector of segment lengths.
 */
static inline vfloat64m1_t
jbm_v3_length_nxf64 (const vfloat64m1_t x1,
///< vfloat64m1_t vector of x-coordinates of the 1st points defining the
///< segments.
                     const vfloat64m1_t y1,
///< vfloat64m1_t vector of y-coordinates of the 1st points defining the
///< segments.
                     const vfloat64m1_t z1,
///< vfloat64m1_t vector of z-coordinates of the 1st points defining the
///< segments.
                     const vfloat64m1_t x2,
///< vfloat64m1_t vector of x-coordinates of the 2nd points defining the
///< segments.
                     const vfloat64m1_t y2,
///< vfloat64m1_t vector of y-coordinates of the 2nd points defining the
///< segments.
                     const vfloat64m1_t z2,
///< vfloat64m1_t vector of z-coordinates of the 2nd points defining the
///< segments.
                     const size_t vl)   ///< vector size.
{
  vfloat64m1_t dx, dy, dz;
  dx = jbm_sqr_nxf64 (__riscv_vfsub_vv_f64m1 (x2, x1, vl), vl);
  dy = __riscv_vfsub_vv_f64m1 (y2, y1, vl);
  dy = __riscv_vfmacc_vv_f64m1 (dx, dy, dy, vl);
  dz = __riscv_vfsub_vv_f64m1 (z2, z1, vl);
  return __riscv_vfsqrt_v_f64m1 (__riscv_vfmacc_vv_f64m1 (dy, dz, dz, vl), vl);
}

/**
 * Function to calculate a 1st order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vx_f64m1 (__riscv_vfmv_v_f_f64 (p[0], vl), p[1], x, vl);
}

/**
 * Function to calculate a 2nd order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_1_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 3rd order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_2_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 4th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_4_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_3_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 5th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_5_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_4_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 6th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_6_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_5_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 7th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_7_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_6_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 8th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_8_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_7_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 9th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_9_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_8_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 10th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_10_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_9_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 11th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_11_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_10_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 12th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_12_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_11_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 13th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_13_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_12_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 14th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_14_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_13_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 15th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_15_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_14_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 16th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_16_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_15_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 17th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_17_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_16_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 18th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_18_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_17_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 19th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_19_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_18_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 20th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_20_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_19_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 21th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_21_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_20_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 22th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_22_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_21_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 23th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_23_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_22_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 24th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_24_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_23_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 25th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_25_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_24_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 26th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_26_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_25_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 27th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_27_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_26_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 28th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_28_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_27_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 29th order polynomial (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of polynomial values.
 */
static inline vfloat64m1_t
jbm_polynomial_29_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl), x,
                          jbm_polynomial_28_nxf64 (x, p + 1, vl), vl);
}

/**
 * Function to calculate a 0th+1st order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_1_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                         __riscv_vfmacc_vf_f64 (__riscv_vfmv_v_f_f64m1 (1., vl), p[1], x, vl));
}

/**
 * Function to calculate a 0th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_2_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+1st order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_2_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[2], x, vl), vl);
}

/**
 * Function to calculate a 0th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_3_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_3_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_3_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[3], x, vl), vl);
}

/**
 * Function to calculate a 0th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_4_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_4_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_4_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_4_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[4], x, vl), vl);
}

/**
 * Function to calculate a 0th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_5_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_5_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_5_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_5_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_5_4_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[5], x, vl), vl);
}

/**
 * Function to calculate a 0th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_6_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_6_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_6_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_6_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_6_4_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_6_5_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[6], x, vl), vl);
}

/**
 * Function to calculate a 0th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_4_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_5_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_7_6_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[7], x, vl), vl);
}

/**
 * Function to calculate a 0th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_4_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_5_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_6_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_8_7_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[8], x, vl), vl);
}

/**
 * Function to calculate a 0th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_0_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_1_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_3_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_4_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_5_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_6_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_7_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_9_8_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                        const double *p,        ///< array of coefficients.
                        const size_t vl)        ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[9], x, vl), vl);
}

/**
 * Function to calculate a 0th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_10_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[10], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_11_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[11], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_12_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[12], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_13_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[13], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_14_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[14], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_15_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[15], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_16_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[16], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_17_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[17], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_18_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[18], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_19_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[19], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_20_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[20], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_21_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[21], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_22_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[22], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_23_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[23], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_23_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_24_23_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_23_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[24], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+25th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_24_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_23_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_23_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_23_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_25_24_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_24_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[25], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+26th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_25_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+25th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_24_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_23_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_23_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_23_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_24_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_24_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+25th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_26_25_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_25_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[26], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+27th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_26_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+26th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_25_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+25th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_24_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_23_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_23_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_23_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_24_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_24_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 25th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_25_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_25_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 26, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+26th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_27_26_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_26_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[27], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+28th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_27_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+27th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_26_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+26th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_25_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+25th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_24_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_23_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_23_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_23_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_24_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_24_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 25th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_25_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_25_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 26, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 26th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_26_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_26_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 27, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+27th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_28_27_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_27_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[28], x, vl),
                    vl);
}

/**
 * Function to calculate a 0th+29th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_0_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (p[0], vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_28_nxf64 (x, p + 1, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+28th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_1_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_27_nxf64 (x, p + 2, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 2nd+27th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_2_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_2_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_26_nxf64 (x, p + 3, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 3rd+26th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_3_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_3_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_25_nxf64 (x, p + 4, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 4th+25th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_4_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_4_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_24_nxf64 (x, p + 5, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 5th+24th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_5_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_5_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_23_nxf64 (x, p + 6, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 6th+23th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_6_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_6_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_22_nxf64 (x, p + 7, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 7th+22th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_7_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_7_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_21_nxf64 (x, p + 8, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 8th+21th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_8_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_8_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_20_nxf64 (x, p + 9, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 9th+20th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_9_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                         const double *p,       ///< array of coefficients.
                         const size_t vl)       ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_9_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_19_nxf64 (x, p + 10, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 10th+19th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_10_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_10_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_18_nxf64 (x, p + 11, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 11th+18th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_11_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_11_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_17_nxf64 (x, p + 12, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 12th+17th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_12_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_12_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_16_nxf64 (x, p + 13, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 13th+16th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_13_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_13_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_15_nxf64 (x, p + 14, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 14th+15th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_14_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_14_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_14_nxf64 (x, p + 15, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 15th+14th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_15_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_15_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_13_nxf64 (x, p + 16, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 16th+13th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_16_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_16_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_12_nxf64 (x, p + 17, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 17th+12th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_17_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_17_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_11_nxf64 (x, p + 18, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 18th+11th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_18_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_18_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_10_nxf64 (x, p + 19, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 19th+10th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_19_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_19_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_9_nxf64 (x, p + 20, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 20th+9th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_20_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_20_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_8_nxf64 (x, p + 21, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 21th+8th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_21_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_21_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_7_nxf64 (x, p + 22, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 22th+7th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_22_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_22_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_6_nxf64 (x, p + 23, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 23th+6th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_23_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_23_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_5_nxf64 (x, p + 24, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 24th+5th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_24_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_24_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_4_nxf64 (x, p + 25, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 25th+4th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_25_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_25_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_3_nxf64 (x, p + 26, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 26th+3rd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_26_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_26_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_2_nxf64 (x, p + 27, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 27th+2nd order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_27_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_27_nxf64 (x, p, vl),
                    __riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                                     jbm_polynomial_1_nxf64 (x, p + 28, vl),
                                     vl), vl);
}

/**
 * Function to calculate a 1st+28th order rational (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of rational values.
 */
static inline vfloat64m1_t
jbm_rational_29_28_nxf64 (const vfloat64m1_t x, ///< vfloat64m1_t vector.
                          const double *p,      ///< array of coefficients.
                          const size_t vl)      ///< array size.
{
  return
    __riscv_vfdiv_vv_f64m1 (jbm_polynomial_28_nxf64 (x, p, vl),
                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl), p[29], x, vl),
                    vl);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_expm1wc_nxf64 (const vfloat64m1_t x,
///< vfloat64m1_t vector \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
                   const size_t vl)     ///< array size.
{
  const double a1 = 9.9999999999999999866523626874215789e-01;
  const double a3 = 2.4998453858981619674396608301250598e-02;
  const double a4 = -4.9999999999999999933261730198779978e-01;
  const double a5 = 1.0833178719231388723914535942973379e-01;
  const double a6 = -1.2499226929490809837198234785821115e-02;
  const double a7 = 6.9431559947707471609539363612700440e-04;
  const double a9 = -1.6512957626515476078093301716091145e-06;
  vfloat64m1_t x2;
  x2 = jbm_sqr_nxf64 (x, vl);
  return
    __riscv_vfdiv_vv_f64m1 (__riscv_vfmul_vv_f64m1 (x,
                                    __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (a1, vl),
                                                     a3, x2, vl), vl),
                    __riscv_vfmacc_vv_f64m1
                    (__riscv_vfmv_v_f_f64m1 (1., vl), x,
                     __riscv_vfmacc_vv_f64m1
                     (__riscv_vfmv_v_f_f64m1 (a4), x,
                      __riscv_vfmacc_vv_f64m1
                      (__riscv_vfmv_v_f_f64m1 (a5), x,
                       __riscv_vfmacc_vv_f64m1
                       (__riscv_vfmv_v_f_f64m1 (a6), x,
                        __riscv_vfmacc_vf_f64m1 (__riscv_vfmv_v_f_f64m1 (a7), a9, x2, vl), vl),
                       vl), vl), vl), vl);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x in
 * \f$\in\left[\frac12\;,1\right]\f$ (vfloat64m1_t).
 *
 * \return function value.
 */
static inline vfloat64m1_t
jbm_exp2wc_nxf64 (const vfloat64m1_t x,
                  ///< vfloat64m1_t vector \f$\in[\frac12,1]\f$.
                  const size_t vl)      ///< array size.
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
  return jbm_rational_10_5_nxf64 (x, a, vl);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_nxf64 and
 * jbm_exp2n_nxf64 functions.
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_exp2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f, y;
  vint64m1_t i;
  i = jbm_floor_nxf64 (x, vl);
  f = __riscv_vfsub_vv_f64m1 (x, vfcvt_f_x_v_i64m1 (i, vl), vl);
  y = jbm_exp2n_nxf64 (i, vl);
  return __riscv_vfmul_vv_f64m1 (y, jbm_exp2wc_nxf64 (f, vl), vl);
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_nxf64 function.
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_exp_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< array size.
{
  return jbm_exp2_nxf64 (__riscv_vfmul_vf_f64m1 (x, M_LOG2E, vl), vl);
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_nxf64
 * function (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_exp10_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 const size_t vl)       ///< array size.
{
  return jbm_exp2_nxf64 (__riscv_vfmul_vf_f64m1 (x, M_LN10 / M_LN2, vl), vl);
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_nxf64 and
 * jbm_exp_nxf64 functions (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_expm1_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 const size_t vl)       ///< array size.
{
  return __riscv_vmerge_vvm_f64m1 (jbm_expm1wc_nxf64 (x, vl),
                           __riscv_vfsub_vf_f64m1 (jbm_exp_nxf64 (x, vl), 1., vl),
                           __riscv_vmflt_vf_f64m1 (jbm_abs_nxf64 (x, vl), M_LN2 / 2.,
                                           vl), vl);
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_log2wc_nxf64 (const vfloat64m1_t x,
///< vfloat64m1_t vector \f$\in[0.5,1]\f$.
                  const size_t vl)      ///< array size.
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
  return jbm_rational_14_7_nxf64 (x, a, vl);
}

/**
 * Function to calculate the function log2(x) using jbm_logwc_nxf64 and
 * jbm_frexp_nxf64
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_log2_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t y;
  vint64m1_t e;
  y = jbm_frexp_nxf64 (x, &e, vl);
  y = __riscv_vfadd_vv_f64m1 (jbm_log2wc_nxf64 (y, vl), vfcvt_f_x_v_i64m1 (e, vl), vl);
  y = __riscv_vmerge_vfm_f64m1 (y, -INFINITY, vmfgt_vf_f64m1_b64 (x, 0., vl), vl);
  return __riscv_vmerge_vfm_f64m1 (y, NAN, vmfge_vf_f64m1_b64 (x, 0., vl), vl);
}

/**
 * Function to calculate the function log(x) using jbm_log2_nxf64
 * (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_log_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< array size.
{
  return __riscv_vfmul_vf_f64m1 (jbm_log2_nxf64 (x, vl), M_LN2, vl);
}

/**
 * Function to calculate the function log10(x) using jbm_log2_nxf64
 * (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_log10_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t vector.
                 const size_t vl)       ///< array size.
{
  return __riscv_vfmul_vf_f64m1 (jbm_log2_nxf64 (x, vl), M_LN2 / M_LN10, vl);
}

/**
 * Function to calculate the function x^e with e an integer number
 * (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t) (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_pown_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                int e,          ///< exponent (int).
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f, xn;
  unsigned int i;
  f = __riscv_vfmv_v_f_f64m1 (1., vl);
  if (e < 0)
    xn = jbm_reciprocal_nxf64 (x, vl);
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1, xn = jbm_sqr_nxf64 (xn, vl))
    if (i & 1)
      f = __riscv_vfmul_vv_f64m1 (f, xn, vl);
  return f;
}

/**
 * Function to calculate the function f32 using the jbm_exp2_nxf64 and
 * jbm_log2_nxf64 functions.
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_pow_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const double e,  ///< exponent (vfloat64m1_t).
               const size_t vl) ///< array size.
{
  double f;
  f = floor (e);
  if (f == e)
    return jbm_pown_nxf64 (x, (int) e, vl);
  return jbm_exp2_nxf64 (__riscv_vfmul_vf_f64m1 (jbm_log2_nxf64 (x, vl), e, vl), vl);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_nxf64 and
 * jbm_pow_nxf64 functions (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_cbrt_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f;
  f = jbm_pow_nxf64 (jbm_abs_nxf64 (x, vl), 1. / 3., vl);
  return __riscv_vmerge_vvm_f64m1 (f, jbm_opposite_nxf64 (f, vl),
                           vmfltz_vf_f64m1_b64 (x, 0., vl), vl);
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] (vfloat64m1_t)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_sinwc_nxf64 (const vfloat64m1_t x,
                 ///< vfloat64m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                 const size_t vl)       ///< array size.
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
  return __riscv_vfmul_vv_f64m1 (x, jbm_polynomial_6_nxf64 (jbm_sqr_nxf64 (x, vl),
                                                    a, vl), vl);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_coswc_nxf64 (const vfloat64m1_t x,
                 ///< vfloat64m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                 const size_t vl)       ///< array size.
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
  return jbm_polynomial_7_nxf64 (jbm_sqr_nxf64 (x, vl), a, vl);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_nxf64 approximation (vfloat64m1_t).
 */
static inline void
jbm_sincoswc_nxf64 (const vfloat64m1_t x,
                    ///< vfloat64m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                    vfloat64m1_t * s,
                    ///< pointer to the f32 function value (vfloat64m1_t).
                    vfloat64m1_t * c,
                    ///< pointer to the f32 function value (vfloat64m1_t).
                    const size_t vl)    ///< array size.
{
  vfloat64m1_t s0;
  *s = s0 = jbm_sinwc_nxf64 (x, vl);
  *c = __riscv_vfsqrt_v_f64m1 (__riscv_vfsub_vv_f64 (__riscv_vfmv_v_f_f64m1 (1., vl),
                                     jbm_sqr_nxf64 (x, vl), vl), vl);
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_nxf64 and
 * jbm_coswc_nxf64 approximations.
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_sin_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat64m1_t y, s, pi2;
  pi2 = __riscv_vfmv_v_f_f64m1 (2. * M_PI, vl);
  y = jbm_rest_nxf64 (x, pi2, vl);
  s = jbm_sinwc_nxf64 (__riscv_vfsub_vv_f64m1 (y, pi2, vl), vl);
  s = __riscv_vmerge_vvm_f64m1
    (jbm_opposite_nxf64
     (jbm_coswc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (3. * M_PI_2, vl),
                                       y, vl), vl), vl),
     s, __riscv_vmflt_vf_f64m1_b64 (y, 7. * M_PI_4, vl), vl);
  s = __riscv_vmerge_vvm_f64m1
    (jbm_sinwc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI, vl), y, vl)),
     s, __riscv_vmflt_vf_f64m1_b64 (y, 5. * M_PI_4, vl));
  s = __riscv_vmerge_vvm_f64m1
    (jbm_coswc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI_2, vl), y, vl)),
     s, __riscv_vmflt_vf_f64m1_b64 (y, 3. * M_PI_4, vl), vl);
  return __riscv_vmerge_vvm_f64m1 (jbm_sinwc_nxf64 (y, vl), s,
                           __riscv_vmflt_vf_f64m1_b64 (y, M_PI_4, vl), vl);
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_nxf64 and
 * jbm_coswc_nxf64 approximations (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_cos_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat64m1_t y, c, pi2;
  pi2 = __riscv_vfmv_v_f_f64m1 (2. * M_PI, vl);
  y = jbm_rest_nxf64 (x, pi2, vl);
  c = jbm_coswc_nxf64 (__riscv_vfsub_vv_f64m1 (y, pi2, vl), vl);
  c = __riscv_vmerge_vvm_f64m1 (jbm_sinwc_nxf64 (__riscv_vfsub_vf_f64m1 (y, 3. * M_PI_2, vl),
                                         vl),
                        c, __riscv_vmflt_vf_f64m1_b64 (y, 7. * M_PI_4, vl), vl);
  c = __riscv_vmerge_vvm_f64m1
    (jbm_opposite_nxf64
     (jbm_coswc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI, vl), y, vl),
                       vl), vl),
     c, __riscv_vmflt_vf_f64m1_b64 (y, 5. * M_PI_4, vl), vl);
  c = __riscv_vmerge_vvm_f64m1
    (jbm_sinwc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI_2), y, vl), vl),
     c, __riscv_vmflt_vf_f64m1_b64 (y, 3. * M_PI_4, vl), vl);
  return __riscv_vmerge_vfm_f64m1 (jbm_coswc_nxf64 (y, vl), c,
                           __riscv_vmflt_vf_f64m1_b64 (y, M_PI_4, vl), vl);
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sinwc_nxf64
 * and jbm_coswc_nxf64 approximations (vfloat64m1_t).
 */
static inline void
jbm_sincos_nxf64 (const vfloat64m1_t x,
                  ///< vfloat64m1_t vector \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  vfloat64m1_t * s,
                  ///< pointer to the f32 function value (vfloat64m1_t).
                  vfloat64m1_t * c,
                  ///< pointer to the f32 function value (vfloat64m1_t).
                  const size_t vl)      ///< array size.
{
  vfloat64m1_t y, pi2, s1, c1, s2, c2;
  vbool64m1_t m;
  pi2 = __riscv_vfmv_v_f_f64m1 (2. * M_PIf, vl);
  y = jbm_rest_nxf64 (x, pi2, vl);
  jbm_sincoswc_nxf64 (__riscv_vfsub_vv_f64m1 (y, pi2, vl), &s1, &c1, vl);
  jbm_sincoswc_nxf64 (__riscv_vfsub_vf_f64m1 (y, 3. * M_PI_2, vl), &c2, &s2, vl);
  m = __riscv_vmflt_vf_f64m1_b64 (y, 7. * M_PI_4f, vl);
  s1 = __riscv_vmerge_vvm_f64m1 (jbm_opposite_nxf64 (s2, vl), s1, m, vl);
  c1 = __riscv_vmerge_vvm_f64m1 (c2, c1, m, vl);
  jbm_sincoswc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI), y, vl),
                      &s2, &c2, vl);
  m = __riscv_vmflt_vf_f64m1_b64 (y, 5. * M_PI_4, vl);
  s1 = __riscv_vmerge_vvm_f64m1 (s2, s1, m, vl);
  c1 = __riscv_vmerge_vvm_f64m1 (jbm_opposite_nxf64 (c2, vl), c1, m, vl);
  jbm_sincoswc_nxf64 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI_2), y, vl),
                      &c2, &s2, vl);
  m = __riscv_vmflt_vf_f64m1_b64 (y, 3. * M_PI_4f, vl);
  s1 = __riscv_vmerge_vvm_f64m1 (s2, s1, m, vl);
  c1 = __riscv_vmerge_vvm_f64m1 (c2, c1, m, vl);
  jbm_sincoswc_nxf64 (y, &s2, &c2, vl);
  m = __riscv_vmflt_vf_f64m1_b64 (y, M_PI_4, vl);
  *s = __riscv_vmerge_vvm_f64m1 (s2, s1, m, vl);
  *c = __riscv_vmerge_vvm_f64m1 (c2, c1, m, vl);
}

/**
 * Function to calculate the function tan(x) from jbm_sinwc_nxf64 and
 * jbm_coswc_nxf64 approximations.
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_tan_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat64m1_t s, c;
  jbm_sincos_nxf64 (x, &s, &c, vl);
  return __riscv_vfdiv_vv_f64m1 (s, c, vl);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_atanwc0_nxf64 (const vfloat64m1_t x,
                   ///< vfloat64m1_t vector \f$\in\left[0,\frac12\right]\f$.
                   const size_t vl)     ///< array size.
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
  return __riscv_vfmul_vv_f64m1 (x, jbm_rational_9_4_nxf64 (jbm_sqr_nxf64 (x, vl),
                                                    a, vl), vl);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_atanwc1_nxf64 (const vfloat64m1_t x,
                   ///< vfloat64m1_t vector \f$\in\left[\frac12,1\right]\f$.
                   const size_t vl)     ///< array size.
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
  return jbm_rational_16_8_nxf64 (__riscv_vfsub_vf_f64m1 (x, 1., vl), a, vl);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_nxf64 and
 * jbm_atanwc1_nxf64 functions (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t in [-pi/2,pi/2]).
 */
static inline vfloat64m1_t
jbm_atan_nxf64 (const vfloat64m1_t x,   ///< double number.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f, ax;
  vbool64m1_t m;
  ax = jbm_abs_nxf64 (x, vl);
  m = vmfgt_vf_f64m1_b64 (ax, 1.5, vl);
  ax = __riscv_vmerge_vvm_f64m1 (jbm_reciprocal_nxf64 (ax, vl), ax, m, vl);
  f = __riscv_vmerge_vvm_f64m1 (jbm_atanwc1_nxf64 (ax, vl), jbm_atanwc0_nxf64 (ax, vl),
                        vmfgt_vf_f64m1_b64 (ax, 0.5, vl), vl);
  f = __riscv_vmerge_vvm_f64m1 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (M_PI_2, vl), f, vl), f,
                        m, f);
  return __riscv_vmerge_vvm_f64m1 (jbm_opposite_nxf64 (f), f,
                           __riscv_vmflt_vf_f64m1_b64 (x, 0.f, vl), vl);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_nxf64
 * function (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t in [-pi,pi]).
 */
static inline vfloat64m1_t
jbm_atan2_nxf64 (const vfloat64m1_t y,  ///< vfloat64m1_t y component.
                 const vfloat64m1_t x,  ///< vfloat64m1_t x component.
                 const size_t vl)       ///< array size.
{
  vfloat64m1_t f;
  vbool64m1_t mx, my;
  f = jbm_atan_nxf64 (__riscv_vfdiv_vv_f64m1 (y, x, vl), vl);
  mx = __riscv_vmflt_vf_f64m1_b64 (x, 0., vl);
  my = vmvlt_vf_f64m1_b64 (y, 0., vl);
  f = __riscv_vmerge_vvm_f64m1 (__riscv_vfsub_vf_f64m1 (f, M_PI, vl), f,
                        __riscv_vmand_mm (my, mx, vl), vl);
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfadd_vf_f64m1 (f, M_PI, vl), f,
                           __riscv_vmand_mm (my, vmnot_m (mx, vl), vl), vl);
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_nxf64 function
 * (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t in [-pi/2,pi/2]).
 */
static inline vfloat64m1_t
jbm_asin_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t number.
                const size_t vl)        ///< array size.
{
  return
    jbm_atan_nxf64
    (__riscv_vfdiv_vv_f64m1 (x,
                     __riscv_vfsqrt_v_f64m1 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl),
                                                     jbm_sqr_nxf64 (x, vl), vl),
                                     vl), vl), vl);
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_nxf64 function
 * (vfloat64m1_t).
 *
 * \return function value (vfloat64m1_t in [0,pi]).
 */
static inline vfloat64m1_t
jbm_acos_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f;
  f =
    jbm_atan_nxf64 (__riscv_vfdiv_vv_f64m1
                    (__riscv_vfsqrt_v_f64m1 (__riscv_vfsub_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1., vl),
                                                     jbm_sqr_nxf64 (x, vl), vl),
                                     x), vl), vl);
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfadd_vf_f64m1 (f, M_PI, vl), f,
                           __riscv_vmflt_vf_f64m1 (x, 0., vl), vl);
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_sinh_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f;
  f = jbm_exp_nxf64 (x, vl);
  return __riscv_vfmul_vf_f64m1 (__riscv_vfsub_vv_f64m1 (f, jbm_reciprocal_nxf64 (f, vl), vl),
                         0.5, vl);
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_cosh_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f;
  f = jbm_exp_nxf64 (x, vl);
  return __riscv_vfmul_vf_f64m1 (__riscv_vfadd_vv_f64m1 (f, jbm_reciprocal_nxf64 (f, vl), vl),
                         0.5, vl);
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_tanh_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t number.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t f, fi;
  f = jbm_exp_nxf64 (x, vl);
  fi = jbm_reciprocal_nxf64 (f, vl);
  f = __riscv_vfdiv_vv_f64m1 (__riscv_vfsub_vv_f64m1 (f, fi, vl), __riscv_vfadd_vv_f64m1 (f, fi, vl),
                      vl);
  f = __riscv_vmerge_vvm_f64m1 (__riscv_vfmv_v_f_f64m1 (1.f, vl), f,
                        vmfgt_vf_f64m1_b64 (x, JBM_FLT_MAX_E_EXP, vl), vl);
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfmv_v_f_f64m1 (-1.f), f,
                           __riscv_vmflt_vf_f64m1_b64 (x, -JBM_FLT_MAX_E_EXP, vl), vl);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_asinh_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t number.
                 const size_t vl)       ///< array size.
{
  return
    jbm_log_nxf64
    (__riscv_vfadd_vv_f64m1
     (x, __riscv_vfsqrt_v_f64m1 (__riscv_vfmacc_vv_f64m1 (__riscv_vfmv_v_f_f64m1 (1.f, vl), x, x, vl),
                         vl), vl), vl);
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_acosh_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t number.
                 const size_t vl)       ///< array size.
{
  return
    jbm_log_nxf64
    (__riscv_vfadd_vv_f64m1 (x, __riscv_vfsqrt_v_f64m1 (__riscv_vfsub_vf_f64m1 (jbm_sqr_nxf64 (x, vl),
                                                        1., vl), vl), vl), vl);
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_atanh_nxf64 (const vfloat64m1_t x,  ///< vfloat64m1_t number.
                 const size_t vl)       ///< array size.
{
  vfloat64m1_t u;
  u = __riscv_vfmv_v_f_f64m1 (1.);
  return
    __riscv_vfmul_vf_f64m1 (jbm_log_nxf64 (__riscv_vfdiv_vv_f64m1 (__riscv_vfadd_vv_f64m1 (u, x, vl),
                                                   __riscv_vfsub_vv_f64m1 (u, x, vl),
                                                   vl), 0.5, vl), vl);
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] (vfloat64m1_t)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_erfwc_nxf64 (const vfloat64m1_t x,
                 ///< vfloat64m1_t vector \f$\in\left[-1,1\right]\f$.
                 const size_t vl)       ///< array size.
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
  return __riscv_vfmul_vv_f64m1 (x, jbm_rational_9_4_nxf64 (jbm_sqr_nxf64 (x, vl), a,
                                                    vl), vl);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ (vfloat64m1_t)
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_erfcwc_nxf64 (const vfloat64m1_t x,
                  ///< vfloat64m1_t vector \f$\in\left[1,\infty\right]\f$.
                  const size_t vl)      ///< array size.
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
  vfloat64m1_t f, x2;
  x2 = jbm_sqr_nxf64 (x, vl);
  f = __riscv_vfdiv_vv_f64m1 (jbm_rational_19_9_nxf64 (jbm_reciprocal_nxf64 (x2, vl), a,
                                               vl),
                      __riscv_vfmul_vv_f64m1 (x, jbm_exp_nxf64 (x2, vl), vl), vl);
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfmv_v_f_f64m1 (0., vl), f,
                           vmfgt_vf_f64m1 (x, m, vl), vl);
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_nxf64 and
 * jbm_erfcwc_nxf64
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_erf_nxf64 (const vfloat64m1_t x,    ///< vfloat64m1_t vector.
               const size_t vl) ///< array size.
{
  vfloat64m1_t ax, u, f;
  ax = jbm_abs_nxf64 (x, vl);
  u = __riscv_vfmv_v_f_f64m1 (1., vl);
  f = __riscv_vfmul_vv_f64m1 (__riscv_vfdiv_vv_f64m1 (x, ax, vl),
                      __riscv_vfsub_vv_f64m1 (u, jbm_erfcwc_nxf64 (ax, vl), vl), vl);
  return __riscv_vmerge_vvm_f64m1 (jbm_erfwc_nxf64 (x, vl), f,
                           __riscv_vmflt_vv_f64m1_b64 (ax, u, vl), vl);
}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_nxf64 and
 * jbm_erfcwc_nxf64
 *
 * \return function value (vfloat64m1_t).
 */
static inline vfloat64m1_t
jbm_erfc_nxf64 (const vfloat64m1_t x,   ///< vfloat64m1_t vector.
                const size_t vl)        ///< array size.
{
  vfloat64m1_t ax, u, f;
  ax = jbm_abs_nxf64 (x, vl);
  u = __riscv_vfmv_v_f_f64m1 (1.f, vl);
  f = __riscv_vfsub_vv_f64m1 (u,
                      __riscv_vfmul_vv_f64m1 (__riscv_vfdiv_vv_f64m1 (x, ax, vl),
                                      __riscv_vfsub_vv_f64m1 (u,
                                                      jbm_erfcwc_nxf64 (ax, vl),
                                                      vl), vl), vl);
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfsub_vv_f64m1 (u, jbm_erfwc_nxf64 (x, vl), vl), f,
                           __riscv_vmflt_vv_f64m1_b64 (ax, u, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat64m1_t vector of reduced
 * quadratic equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return vfloat64m1_t vector of solution values.
 */
static inline vfloat64m1_t
jbm_solve_quadratic_reduced_nxf64 (vfloat64m1_t a,
///< vfloat64m1_t vector of 1st order coefficient of the equations.
                                   vfloat64m1_t b,
///< vfloat64m1_t vector of 0th order coefficient of the equations.
                                   const vfloat64m1_t x1,
///< vfloat64m1_t vector of left limits of the solution intervals.
                                   const vfloat64m1_t x2,
///< vfloat64m1_t vector of right limits of the solution intervals.
                                   const size_t vl)     ///< array size.
{
  vfloat64m1_t k1, k2;
  a = __riscv_vfmul_vf_f64m1 (a, -0.5f, vl);
  b = __riscv_vfsqrt_v_f64m1 (__riscv_vfsub_vv_f64m1 (jbm_sqr_nxf64 (a, vl), b, vl), vl);
  k1 = __riscv_vfadd_vv_f64m1 (a, b, vl);
  k2 = __riscv_vfsub_vv_f64m1 (a, b, vl);
  k1 = __riscv_vmerge_vvm_f64m1 (k2, k1, __riscv_vmflt_vv_f64m1_b64 (k1, x1, vl), vl);
  return __riscv_vmerge_vvm_f64m1 (k2, k1, vmfgt_vv_f64m1_b64 (k1, x2, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat64m1_t vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return vfloat64m1_t vector of solution values.
 */
static inline vfloat64m1_t
jbm_solve_quadratic_nxf64 (const vfloat64m1_t a,
///< vfloat64m1_t vector of 2nd order coefficient of the equations.
                           const vfloat64m1_t b,
///< vfloat64m1_t vector of 1st order coefficient of the equations.
                           const vfloat64m1_t c,
///< vfloat64m1_t vector of 0th order coefficient of the equations.
                           const vfloat64m1_t x1,
///< vfloat64m1_t vector of left limits of the solution intervals.
                           const vfloat64m1_t x2,
///< vfloat64m1_t vector of right limits of the solution intervals.
                           const size_t vl)     ///< array size.
{
  vfloat64m1_t k1, k2;
  k1 = jbm_solve_quadratic_reduced_nxf64 (__riscv_vfdiv_vv_f64m1 (b, a, vl),
                                          __riscv_vfdiv_vv_f64m1 (c, a, vl),
                                          x1, x2, vl);
  k2 = __riscv_vfdiv_vv_f64m1 (jbm_opposite_nxf64 (c, vl), b, vl);
  return __riscv_vmerge_vvm_f64m1 (k2, k1, jbm_small_nxf64 (a, vl), vl);
}

/**
 * Function to calculate the solution of a vfloat64m1_t vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return vfloat64m1_t vector of solution values.
 */
static inline vfloat64m1_t
jbm_solve_cubic_reduced_nxf64 (const vfloat64m1_t a,
                               ///< 2nd order coefficient of the equation.
                               const vfloat64m1_t b,
                               ///< 1st order coefficient of the equation.
                               const vfloat64m1_t c,
                               ///< 0th order coefficient of the equation.
                               const vfloat64m1_t x1,
                               ///< left limit of the solution interval.
                               const vfloat64m1_t x2,
                               ///< right limit of the solution interval.
                               const size_t vl) ///< array size.
{
  vfloat64m1_t a3, k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c2p_3, c_2;
  a3 = __riscv_vfmul_vf_f64m1 (a, 1. / 3., vl);
  k0 = jbm_sqr_nxf64 (a3, vl);
  k1 = __riscv_vfsub_vv_f64m1 (k0, __riscv_vfmul_vf_f64m1 (b, 1. / 3., vl), vl);
  k0 = __riscv_vfsub_vv_f64n1
    (__riscv_vfmul_vv_f64m1 (a3, k0, vl),
     __riscv_vfmul_vf_f64m1 (__riscv_vfsub_vv_f64m1 (b,
                                     __riscv_vfmul_vv_f64m1 (a3, c, vl), 0.5, vl),
                     vl), vl);
  k3 = __riscv_vfmul_vv_f64m1 (k1, jbm_sqr_nxf64 (k1, vl), vl);
  k2 = __riscv_vfmacc_vv_f64m1 (k3, k0, k0, vl);
  l1 = __riscv_vfsqrt_v_f64m1 (jbm_opposite_nxf64 (k1, vl), vl);
  l0 = __riscv_vfmul_vf_f64m1 (jbm_acos_nxf64 (__riscv_vfdiv_vv_f64m1 (k0, k3, vl), vl),
                       1. / 3., vl);
  l1 = jbm_dbl_nxf64 (l1);
  l2 = __riscv_vfsub_vv_f64m1 (a3, __riscv_vfmul_vv_f64m1 (l1, jbm_cos_nxf64 (k0, vl), vl), vl);
  l3 = __riscv_vfsub_vv_f64m1
    (a3, __riscv_vfmul_vv_f64m1
     (l1, jbm_cos_nxf64 (__riscv_vfadd_vf_f64m1 (l0, 2. * M_PI / 3., vl), vl), vl), vl);
  l3 = __riscv_vmerge_vvm_f64m1 (l2, l3,
                         __riscv_vmor_mm (__riscv_vmflt_vv_f64m1_b64 (l2, x1, vl),
                                  vmfgt_vv_f64m1_b64 (l2, x2, vl), vl), vl);
  l4 = __riscv_vfsub_vv_f64m1
    (a, __riscv_vfmul_vv_f64m1
     (l1, jbm_cos_nxf64 (__riscv_vfsub_vf_f64m1 (l0, 2. * M_PI / 3., vl), vl), vl), vl);
  l4 = __riscv_vmerge_vvm_f64m1 (l3, l4,
                         __riscv_vmor_mm (__riscv_vmflt_vv_f64m1_b64 (l3, x1, vl),
                                  vmfgt_vv_f64m1_b64 (l3, x2, vl), vl), vl);
  k1 = __riscv_vfsqrt_v_f64m1 (k2, vl);
  l5 = __riscv_vfadd_vv_f64m1 (k0, k1, vl);
  l5 = jbm_cbrt_nxf64 (k2, vl);
  k0 = __riscv_vfsub_vv_f64m1 (k0, k1, vl);
  l5 = __riscv_vfadd_vv_f64m1 (l5, __riscv_vfsub_vv_f64m1 (jbm_cbrt_nxf64 (k0, vl), a3, vl),
                       vl);
  return __riscv_vmerge_vvm_f64m1 (l5, l4, __riscv_vmflt_vf_f64m1_b64 (k2, 0., vl), vl);
}

/**
 * Function to calculate the solution of a vfloat64m1_t vector of cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return vfloat64m1_t vector of solution values.
 */
static inline vfloat64m1_t
jbm_solve_cubic_nxf64 (vfloat64m1_t a,
///< vfloat64m1_t vector of 3rd order coefficient of the equations.
                       vfloat64m1_t b,
///< vfloat64m1_t vector of 2nd order coefficient of the equations.
                       vfloat64m1_t c,
///< vfloat64m1_t vector of 1st order coefficient of the equations.
                       vfloat64m1_t d,
///< vfloat64m1_t vector of 0th order coefficient of the equations.
                       vfloat64m1_t x1,
///< vfloat64m1_t vector of left limits of the solution intervals.
                       vfloat64m1_t x2,
///< vfloat64m1_t vector of right limits of the solution intervals.
                       const size_t vl) ///< array size.
{
  return
    __riscv_vmerge_vvm_f64m1 (jbm_small_nxf64 (a, vl),
                      jbm_solve_quadratic_nxf64 (b, c, d, x1, x2, vl),
                      jbm_solve_cubic_reduced_nxf64 (__riscv_vfdiv_vv_f64m1 (b, a, vl),
                                                     __riscv_vfdiv_vv_f64m1 (c, a, vl),
                                                     __riscv_vfdiv_vv_f64m1 (d, a, vl),
                                                     x1, x2, vl), vl);
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_total_nxf64 (const vfloat64m1_t d1 __attribute__((unused)),
                              ///< 1st flux limiter function parameter.
                              const vfloat64m1_t d2 __attribute__((unused)),
                              ///< 2nd flux limiter function parameter.
                              const size_t vl)  ///< array size.
{
  return __riscv_vfmv_v_f_f64m1 (0., vl);
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_null_nxf64 (const vfloat64m1_t d1 __attribute__((unused)),
                             ///< 1st flux limiter function parameter.
                             const vfloat64m1_t d2 __attribute__((unused)),
                             ///< 2nd flux limiter function parameter.
                             const size_t vl)   ///< array size.
{
  return __riscv_vfmv_v_f_f64m1 (1., vl);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_centred_nxf64 (const vfloat64m1_t d1,
                                ///< 1st flux limiter function parameter.
                                const vfloat64m1_t d2,
                                ///< 2nd flux limiter function parameter.
                                const size_t vl)        ///< array size.
{
  return __riscv_vmerge_vvm_f64m1 (__riscv_vfmv_v_f_f64m1 (0., vl), __riscv_vfdiv_vv_f64m1 (d1, d2, vl),
                           jbm_small_nxf64 (d2, vl), vl);
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_superbee_nxf64 (const vfloat64m1_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const vfloat64m1_t d2,
                                 ///< 2nd flux limiter function parameter.
                                 const size_t vl)       ///< array size.
{
  vfloat64m1_t r;
  r = __riscv_vfdiv_vv_f64m1 (d1, d2, vl);
  r = vfmax_vv_f64m1 (vfmin_vf_f64m1 (jbm_dbl_nxf64 (r, vl), 1., vl),
                      vfmin_vf_f64m1 (r, 2., vl), vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0., vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                                  DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_minmod_nxf64 (const vfloat64m1_t d1,
                               ///< 1st flux limiter function parameter.
                               const vfloat64m1_t d2,
                               ///< 2nd flux limiter function parameter.
                               const size_t vl) ///< array size.
{
  vfloat64m1_t r;
  r = vfmin_vf_f64m1 (__riscv_vfdiv_vv_f64m1 (d1, d2), 1., vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0., vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                                  DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_VanLeer_nxf64 (const vfloat64m1_t d1,
                                ///< 1st flux limiter function parameter.
                                const vfloat64m1_t d2,
                                ///< 2nd flux limiter function parameter.
                                const size_t vl)        ///< array size.
{
  vfloat64m1_t r, k;
  r = __riscv_vfdiv_vv_f64m1 (d1, d2, vl);
  k = jbm_abs_nxf64 (r, vl);
  r = __riscv_vfdiv_vv_f64m1 (__riscv_vfadd_vv_f64m1 (r, k, vl), __riscv_vfadd_vf_f64m1 (k, 1., vl),
                      vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0., vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                                  DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_VanAlbada_nxf64 (const vfloat64m1_t d1,
                                  ///< 1st flux limiter function parameter.
                                  const vfloat64m1_t d2,
                                  ///< 2nd flux limiter function parameter.
                                  const size_t vl)      ///< array size.
{
  vfloat64m1_t r, k;
  r = __riscv_vfdiv_vv_f64m1 (d1, d2, vl);
  k = jbm_sqr_nxf64 (r, vl);
  r = __riscv_vfdiv_vv_f64m1 (__riscv_vfadd_vv_f64m1 (r, k, vl), __riscv_vfadd_vf_f64m1 (k, 1., vl),
                      vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0., vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                                  DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_minsuper_nxf64 (const vfloat64m1_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const vfloat64m1_t d2,
                                 ///< 2nd flux limiter function parameter.
                                 const size_t vl)       ///< array size.
{
  vfloat64m1_t r;
  r = vfmin_vf_f64m1 (__riscv_vfdiv_vv_f64m1 (d1, d2, vl), 2., vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0., vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                                  DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_supermin_nxf64 (const vfloat64m1_t d1,
                                 ///< 1st flux limiter function parameter.
                                 const vfloat64m1_t d2,
                                 ///< 2nd flux limiter function parameter.
                                 const size_t vl)       ///< array size.
{
  vfloat64m1_t r;
  r = __riscv_vfdiv_vv_f64m1 (d1, d2, vl);
  r = vfmin_vf_f64m1 (jbm_dbl_nxf64 (r, vl), 1., vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0., vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                                  DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_monotonized_central_nxf64 (const vfloat64m1_t d1,
///< 1st flux limiter function parameter.
                                            const vfloat64m1_t d2,
///< 2nd flux limiter function parameter.
                                            const size_t vl)    ///< array size.
{
  vfloat64m1_t r, rm;
  r = __riscv_vfdiv_vv_f64m1 (d1, d2, vl);
  rm = __riscv_vfmul_vf_f64m1 (__riscv_vfadd_vf_f64m1 (r, 1., vl), 0.5, vl);
  rm = __riscv_vmerge_vfm_f64m1 (rm, 2., __riscv_vmflt_vf_f64m1_b64 (r, 3., vl), vl);
  rm = __riscv_vmerge_vfm_f64m1 (jbm_dbl_nxf64 (r, vl), rm,
                         vmfgt_vf_f64m1 (r, 1. / 3., vl), vl);
  return __riscv_vmerge_vfm_f64m1 (rm, 0.,
                           vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                           DBL_EPSILON, vl), vl);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_mean_nxf64 (const vfloat64m1_t d1,
                             ///< 1st flux limiter function parameter.
                             const vfloat64m1_t d2,
                             ///< 2nd flux limiter function parameter.
                             const size_t vl)   ///< array size.
{
  vfloat64m1_t r;
  r = __riscv_vfmul_vf_f64m1 (__riscv_vfadd_vf_f64m1 (__riscv_vfdiv_vv_f64m1 (d1, d2, vl), 1., vl), 0.5,
                      vl);
  return __riscv_vmerge_vfm_f64m1 (r, 0.,
                           vmfgt_vf_f64m1 (__riscv_vfmul_vv_f64m1 (d1, d2, vl),
                                           DBL_EPSILON, vl), vl);
}

/**
 * Function to do a flux limiter function (vfloat64m1_t).
 *
 * \return flux limiter function value.
 */
static inline vfloat64m1_t
jbm_flux_limiter_nxf64 (const vfloat64m1_t d1,
                        ///< 1st flux limiter function parameter.
                        const vfloat64m1_t d2,
                        ///< 2nd flux limiter function parameter.
                        unsigned int type,
                        ///< type of flux limiter function.
                        const size_t vl)        ///< array size.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_nxf64 (d1, d2, vl);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_nxf64 (d1, d2, vl);
    }
  return jbm_flux_limiter_mean_nxf64 (d1, d2, vl);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (vfloat64m1_t).
 *
 * \return vfloat64m1_t vector of integral values.
 */
static inline vfloat64m1_t
jbm_integral_nxf64 (vfloat64m1_t (*f) (vfloat64m1_t),
                    ///< pointer to the function to integrate.
                    const vfloat64m1_t x1,      ///< left limit of the interval.
                    const vfloat64m1_t x2,      ///< right limit of the interval.
                    const size_t vl)    ///< array size.
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
  vfloat64m1_t k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  vfloat64m1_t k2, f1, f2;
#endif
  unsigned int i;
  dx = __riscv_vfmul_vf_f64m1 (__riscv_vfsub_vv_f64m1 (x2, x1, vl), 0.5, vl);
  x = __riscv_vfmul_vf_f64m1 (__riscv_vfadd_vv_f64m1 (x2, x1, vl), 0.5, vl);
  k = __riscv_vfmul_vf_f64m1 (f (x, vl), a[0], vl);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = __riscv_vfmul_vf_f64m1 (dx, b[i], vl);
      f1 = f (__riscv_vfsub_vv_f64m1 (x, k2, vl), vl);
      f2 = f (__riscv_vfadd_vv_f64m1 (x, k2, vl), vl);
      k = __riscv_vfmacc_vf_f64m1 (k, a[i], __riscv_vfadd_vv_f64m1 (f1, f2, vl), vl);
    }
#endif
  k = __riscv_vfmul_vv_f64m1 (k, dx, vl);
  return k;
}

#endif
