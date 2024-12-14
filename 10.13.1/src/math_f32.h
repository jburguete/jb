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
 * \file math_f32.h
 * \brief Header file with useful mathematical functions for float.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2024, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_F32__H
#define JB_MATH_F32__H 1

/**
 * union to work with bits in float numbers.
 */
typedef union
{
  float x;                      ///< floating point.
  unsigned int i;               ///< bits.
} JBMF32;

/**
 * Function to calculate the abs function (float).
 *
 * \return function value (float).
 */
static inline float
jbm_abs_f32 (const float x)     ///< float number.
{
  JBMF32 y;
  y.x = x;
  y.i &= 0x7fffffff;
  return y.x;
}

/**
 * Function to calculate the hypot function (float).
 *
 * \return function value (float).
 */
static inline float
jbm_hypot_f32 (const float x,   ///< 1st float number.
               const float y)   ///< 2nd float number.
{
  return sqrtf (x * x + y * y);
}

/**
 * Function to calculate the rest of a division (float).
 *
 * \return rest value (in [0,|divisor|) interval) (float).
 */
static inline float
jbm_rest_f32 (const float x,    ///< dividend (float).
              const float d)    ///< divisor (float).
{
  float f;
  f = floorf (x / d);
  return x - f * d;
}

/**
 * Function to implement the standard frexp function (float).
 *
 * \return normalize fraction value in [1/2,1) (float).
 */
static inline float
jbm_frexp_f32 (const float x,   ///< float number.
               int *e)          ///< pointer to the extracted exponent.
{
  JBMF32 y, z;
  y.x = x;
  y.i &= 0x7f800000;
  if (y.i == 0x7f800000)
    {
      *e = 0;
      return x;
    }
  if (!y.i)
    {
      y.x = x;
      y.i &= 0x007fffff;
      if (!y.i)
        {
          *e = 0;
          return x;
        }
      y.i = 0x00400000;
      z.x = x / y.x;
      z.i &= 0x7f800000;
      *e = (int) (z.i >> 23) - 253;
      y.x *= z.x;
    }
  else
    *e = (int) (y.i >> 23) - 126;
  return 0.5f * (x / y.x);
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer number (int).
 *
 * \return function value (float).
 */
static inline float
jbm_exp2n_f32 (int e)           ///< exponent number (int).
{
  JBMF32 x;
  if (e > 127)
    return INFINITY;
  if (e < -150)
    return 0.f;
  if (e > -127)
    x.i = (127 + e) << 23;
  else
    x.i = 0x00400000 >> (-e - 127);
  return x.x;
}

/**
 * Function to implement the standard ldexp function (float).
 *
 * \return function value (float).
 */
static inline float
jbm_ldexp_f32 (const float x,   ///< float number.
               int e)           ///< exponent number (int).
{
  return x * jbm_exp2n_f32 (e);
}

/**
 * Function to calculate a 1st order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * p[1];
}

/**
 * Function to calculate a 2nd order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_1_f32 (x, p + 1);
}

/**
 * Function to calculate a 3rd order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_2_f32 (x, p + 1);
}

/**
 * Function to calculate a 4th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_4_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_3_f32 (x, p + 1);
}

/**
 * Function to calculate a 5th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_5_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_4_f32 (x, p + 1);
}

/**
 * Function to calculate a 6th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_6_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_5_f32 (x, p + 1);
}

/**
 * Function to calculate a 7th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_7_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_6_f32 (x, p + 1);
}

/**
 * Function to calculate a 8th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_8_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_7_f32 (x, p + 1);
}

/**
 * Function to calculate a 9th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_9_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_8_f32 (x, p + 1);
}

/**
 * Function to calculate a 10th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_10_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_9_f32 (x, p + 1);
}

/**
 * Function to calculate a 11th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_11_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_10_f32 (x, p + 1);
}

/**
 * Function to calculate a 12th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_12_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_11_f32 (x, p + 1);
}

/**
 * Function to calculate a 13th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_13_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_12_f32 (x, p + 1);
}

/**
 * Function to calculate a 14th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_14_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_13_f32 (x, p + 1);
}

/**
 * Function to calculate a 15th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_15_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_14_f32 (x, p + 1);
}

/**
 * Function to calculate a 16th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_16_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_15_f32 (x, p + 1);
}

/**
 * Function to calculate a 17th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_17_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_16_f32 (x, p + 1);
}

/**
 * Function to calculate a 18th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_18_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_17_f32 (x, p + 1);
}

/**
 * Function to calculate a 19th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_19_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_18_f32 (x, p + 1);
}

/**
 * Function to calculate a 20th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_20_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_19_f32 (x, p + 1);
}

/**
 * Function to calculate a 21th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_21_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_20_f32 (x, p + 1);
}

/**
 * Function to calculate a 22th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_22_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_21_f32 (x, p + 1);
}

/**
 * Function to calculate a 23th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_polynomial_23_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_22_f32 (x, p + 1);
}

/**
 * Function to calculate a 24th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_polynomial_24_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_23_f32 (x, p + 1);
}

/**
 * Function to calculate a 25th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_polynomial_25_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_24_f32 (x, p + 1);
}

/**
 * Function to calculate a 26th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_polynomial_26_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_25_f32 (x, p + 1);
}

/**
 * Function to calculate a 27th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_polynomial_27_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_26_f32 (x, p + 1);
}

/**
 * Function to calculate a 28th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_polynomial_28_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_27_f32 (x, p + 1);
}

/**
 * Function to calculate a 29th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_polynomial_29_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_polynomial_28_f32 (x, p + 1);
}

/**
 * Function to calculate a 1st order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_1_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * p[1]);
}

/**
 * Function to calculate a 2nd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_2_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_1_f32 (x, p + 1));
}

/**
 * Function to calculate a 2nd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_2_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_1_f32 (x, p) / (1.f + x * p[2]);
}

/**
 * Function to calculate a 3rd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_3_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_2_f32 (x, p + 1));
}

/**
 * Function to calculate a 3rd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_3_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 2));
}

/**
 * Function to calculate a 3rd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_3_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_2_f32 (x, p) / (1.f + x * p[3]);
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_4_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_3_f32 (x, p + 1));
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_4_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 2));
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_4_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 3));
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_4_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_3_f32 (x, p) / (1.f + x * p[4]);
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_5_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_4_f32 (x, p + 1));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_5_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 2));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_5_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 3));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_5_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 4));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_5_4_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_4_f32 (x, p) / (1.f + x * p[5]);
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_6_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_5_f32 (x, p + 1));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_6_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 2));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_6_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 3));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_6_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 4));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_6_4_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 5));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_6_5_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_5_f32 (x, p) / (1.f + x * p[6]);
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_6_f32 (x, p + 1));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 2));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 3));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 4));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_4_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 5));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_5_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 6));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_7_6_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_6_f32 (x, p) / (1.f + x * p[7]);
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_7_f32 (x, p + 1));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 2));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 3));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 4));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_4_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 5));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_5_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 6));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_6_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 7));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_8_7_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_7_f32 (x, p) / (1.f + x * p[8]);
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_0_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_8_f32 (x, p + 1));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_1_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 2));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_2_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 3));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_3_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 4));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_4_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 5));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_5_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 6));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_6_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 7));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_7_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 8));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_9_8_f32 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_polynomial_8_f32 (x, p) / (1.f + x * p[9]);
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_9_f32 (x, p + 1));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 2));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 3));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 4));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 5));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 6));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 7));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 8));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 9));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_10_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return jbm_polynomial_9_f32 (x, p) / (1.f + x * p[10]);
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_10_f32 (x, p + 1));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 2));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 3));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 4));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 5));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 6));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 7));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 8));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 9));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 10));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_11_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_10_f32 (x, p) / (1.f + x * p[11]);
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_11_f32 (x, p + 1));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 2));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 3));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 4));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 5));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 6));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 7));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 8));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 9));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 10));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 11));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_12_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_11_f32 (x, p) / (1.f + x * p[12]);
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_12_f32 (x, p + 1));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 2));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 3));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 4));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 5));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 6));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 7));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 8));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 9));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 10));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 11));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 12));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_13_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_12_f32 (x, p) / (1.f + x * p[13]);
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_13_f32 (x, p + 1));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 2));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 3));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 4));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 5));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 6));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 7));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 8));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 9));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 10));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 11));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 12));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 13));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_14_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_13_f32 (x, p) / (1.f + x * p[14]);
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_14_f32 (x, p + 1));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 2));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 3));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 4));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 5));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 6));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 7));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 8));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 9));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 10));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 11));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 12));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 13));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 14));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_15_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_14_f32 (x, p) / (1.f + x * p[15]);
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_15_f32 (x, p + 1));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_14_f32 (x, p + 2));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 3));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 4));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 5));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 6));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 7));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 8));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 9));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 10));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 11));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 12));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 13));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 14));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_14_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 15));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_16_15_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_15_f32 (x, p) / (1.f + x * p[16]);
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_16_f32 (x, p + 1));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_15_f32 (x, p + 2));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_14_f32 (x, p + 3));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 4));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 5));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 6));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 7));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 8));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 9));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 10));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 11));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 12));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 13));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 14));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_14_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 15));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_15_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_15_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 16));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_17_16_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_16_f32 (x, p) / (1.f + x * p[17]);
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_17_f32 (x, p + 1));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_16_f32 (x, p + 2));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_15_f32 (x, p + 3));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_14_f32 (x, p + 4));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 5));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 6));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 7));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 8));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 9));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 10));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 11));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 12));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 13));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 14));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_14_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 15));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_15_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_15_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 16));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_16_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_16_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 17));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_18_17_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_17_f32 (x, p) / (1.f + x * p[18]);
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_18_f32 (x, p + 1));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_17_f32 (x, p + 2));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_16_f32 (x, p + 3));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_15_f32 (x, p + 4));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_14_f32 (x, p + 5));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 6));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 7));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 8));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 9));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 10));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 11));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 12));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 13));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 14));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_14_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 15));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_15_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_15_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 16));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_16_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_16_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 17));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_17_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_17_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 18));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_19_18_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_18_f32 (x, p) / (1.f + x * p[19]);
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_19_f32 (x, p + 1));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_18_f32 (x, p + 2));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_17_f32 (x, p + 3));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_16_f32 (x, p + 4));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_15_f32 (x, p + 5));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_14_f32 (x, p + 6));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 7));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 8));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 9));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 10));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 11));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 12));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 13));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 14));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_14_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 15));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_15_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_15_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 16));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_16_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_16_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 17));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_17_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_17_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 18));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_18_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_18_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 19));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_20_19_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_19_f32 (x, p) / (1.f + x * p[20]);
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_0_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_polynomial_20_f32 (x, p + 1));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_1_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_1_f32 (x, p) / (1.f + x * jbm_polynomial_19_f32 (x, p + 2));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_2_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_2_f32 (x, p) / (1.f + x * jbm_polynomial_18_f32 (x, p + 3));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_3_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_3_f32 (x, p) / (1.f + x * jbm_polynomial_17_f32 (x, p + 4));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_4_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_4_f32 (x, p) / (1.f + x * jbm_polynomial_16_f32 (x, p + 5));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_5_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_5_f32 (x, p) / (1.f + x * jbm_polynomial_15_f32 (x, p + 6));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_6_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_6_f32 (x, p) / (1.f + x * jbm_polynomial_14_f32 (x, p + 7));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_7_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_7_f32 (x, p) / (1.f + x * jbm_polynomial_13_f32 (x, p + 8));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_8_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_8_f32 (x, p) / (1.f + x * jbm_polynomial_12_f32 (x, p + 9));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_9_f32 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_polynomial_9_f32 (x, p) / (1.f + x * jbm_polynomial_11_f32 (x, p + 10));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_10_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_10_f32 (x,
                           p) / (1.f + x * jbm_polynomial_10_f32 (x, p + 11));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_11_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_11_f32 (x, p) / (1.f + x * jbm_polynomial_9_f32 (x, p + 12));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_12_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_12_f32 (x, p) / (1.f + x * jbm_polynomial_8_f32 (x, p + 13));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_13_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_13_f32 (x, p) / (1.f + x * jbm_polynomial_7_f32 (x, p + 14));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_14_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_14_f32 (x, p) / (1.f + x * jbm_polynomial_6_f32 (x, p + 15));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_15_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_15_f32 (x, p) / (1.f + x * jbm_polynomial_5_f32 (x, p + 16));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_16_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_16_f32 (x, p) / (1.f + x * jbm_polynomial_4_f32 (x, p + 17));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_17_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_17_f32 (x, p) / (1.f + x * jbm_polynomial_3_f32 (x, p + 18));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_18_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_18_f32 (x, p) / (1.f + x * jbm_polynomial_2_f32 (x, p + 19));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_19_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_polynomial_19_f32 (x, p) / (1.f + x * jbm_polynomial_1_f32 (x, p + 20));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_rational_21_20_f32 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_polynomial_20_f32 (x, p) / (1.f + x * p[21]);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] by the following Taylor' serie:
 * \f$\exp(x)-1\approx\sum_{n=0}^7\frac{x^n}{n!}-1\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_expm1wc_f32 (const float x)
                 ///< float number \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
// Taylor' serie
/*
  const float a[7] = { JBM_1_FACT1f, JBM_1_FACT2f,
    JBM_1_FACT3f, JBM_1_FACT4f, JBM_1_FACT5f, JBM_1_FACT6f, JBM_1_FACT7f
  };
  return x * jbm_polynomial_6_f32 (x, a);
*/
// Faster
  const float a1 = 9.9999999917826835759154742878523887e-01f;
  const float a2 = -4.9999999958913417879577371439261924e-01f;
  const float a3 = 8.3333136366700581865508474051734715e-02f;
  const float a5 = -1.3833464660905326042591440964123531e-03f;
  return x * a1 / (1.f + x * (a2 + x * (a3 + x * x * a5)));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_exp2wc_f32 (const float x)
                ///< float number \f$\in\left[\frac12,\;1\right]\f$.
{
  const float a[7] = {
    1.0000000000000000000000000000000000e+00f,
    6.9314686072833467549614190619455902e-01f,
    2.4023118169610183345256217102144910e-01f,
    5.5478530109176099769719280450854577e-02f,
    9.6865061954622047550464877418812215e-03f,
    1.2383545075613684860722656859898531e-03f,
    2.1856676336381804045788890526617381e-04f
  };
  return jbm_polynomial_6_f32 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expwc_f32 and
 * jbm_exp2n_f32 functions (float).
 *
 * \return function value (float).
 */
static inline float
jbm_exp2_f32 (const float x)    ///< float number.
{
  float y, f;
  if (x >= FLT_MAX_EXP)
    return INFINITY;
  y = floorf (x);
  f = x - y;
  y = jbm_exp2n_f32 ((int) y);
  return y * jbm_exp2wc_f32 (f);
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_f32 function
 * (float).
 *
 * \return function value (float).
 */
static inline float
jbm_exp_f32 (const float x)     ///< float number.
{
  return jbm_exp2_f32 (x * M_LOG2Ef);
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_f32 function
 * (float).
 *
 * \return function value (float).
 */
static inline float
jbm_exp10_f32 (const float x)   ///< float number.
{
  return jbm_exp2_f32 (x * M_LN10f / M_LN2f);
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_f32 and
 * jbm_exp_f32 functions.
 *
 * \return function value (float).
 */
static inline float
jbm_expm1_f32 (const float x)   ///< float number.
{
  if (jbm_abs_f32 (x) < M_LN2f / 2.f)
    return jbm_expm1wc_f32 (x);
  return jbm_exp_f32 (x) - 1.f;
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (float).
 *
 * \return function value (float).
 */
static inline float
jbm_log2wc_f32 (const float x)  ///< float number.
{
  const float a[7] = {
    -5.7614734502501607747654602917594776e+00,
    -2.3619900574486177423704274945198131e+01,
    1.6942914690062891037195707459711629e+01,
    1.2438459334673447161274027777245978e+01,
    1.2423302678466295723498856823510141e+01,
    1.6996336524406058588262995830668668e+01,
    2.5612174224694665867539204628212066e+00
  };
  return jbm_rational_6_3_f32 (x, a);
}

/**
 * Function to calculate the function log_2(x) using jbm_log2wc_f32 and
 * jbm_frexp_f32 (float).
 *
 * \return function value (float).
 */
static inline float
jbm_log2_f32 (const float x)    ///< float number.
{
  float y;
  int e;
  if (x < 0.f)
    return NAN;
  if (x <= 0.f)
    return -INFINITY;
  y = jbm_frexp_f32 (x, &e);
  return jbm_log2wc_f32 (y) + (float) e;
}

/**
 * Function to calculate the function log(x) using jbm_log2_f32 (float).
 *
 * \return function value (float).
 */
static inline float
jbm_log_f32 (const float x)     ///< float number.
{
  return jbm_log2_f32 (x) * M_LN2f;
}

/**
 * Function to calculate the function log10(x) using jbm_log2_f32 (float).
 *
 * \return function value (float).
 */
static inline float
jbm_log10_f32 (const float x)   ///< float number.
{
  return jbm_log2_f32 (x) * M_LN2f / M_LN10f;
}

/**
 * Function to calculate the function x^e with e an integer number.
 *
 * \return function value (float).
 */
static inline float
jbm_pown_f32 (const float x,    ///< float number.
              const int e)      ///< exponent (int).
{
  float f, xn;
  unsigned int i;
  f = 1.f;
  if (e < 0)
    xn = 1.f / x;
  else
    xn = x;
  for (i = (unsigned int) abs (e); i; i >>= 1)
    {
      if (i & 1)
        f *= xn;
      xn *= xn;
    }
  return f;
}

/**
 * Function to calculate the function pow using the jbm_exp2_f32 and
 * jbm_log2_f32 functions.
 *
 * \return function value (float).
 */
static inline float
jbm_pow_f32 (const float x,     ///< float number.
             const float e)     ///< exponent (float).
{
  float f;
  f = floorf (e);
  if (f == e)
    return jbm_pown_f32 (x, (int) e);
  return jbm_exp2_f32 (e * jbm_log2_f32 (x));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_f32 and
 * jbm_pow_f32 functions (float).
 *
 * \return function value (float).
 */
static inline float
jbm_cbrt_f32 (const float x)    ///< float number.
{
  float f;
  f = jbm_pow_f32 (jbm_abs_f32 (x), 1.f / 3.f);
  if (x < 0.f)
    f = -f;
  return f;
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] by the following Taylor' serie:
 * \f$\sin(x)\approx\sum_{n=0}^4\frac{(-1)^n\,x^{2\,n+1}}{(2\,n+1)!}\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_sinwc_f32 (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
// Taylor' serie
/*
  const float a[5] = { JBM_1_FACT1f, -JBM_1_FACT3f, JBM_1_FACT5f,
    -JBM_1_FACT7f, JBM_1_FACT9f
  };
  return x * jbm_polynomial_4_f32 (x * x, a);
*/
// Faster
  const float a[4] = {
    9.9999999652998170520234859388240338e-01f,
    -1.6666653850132705938945722106817969e-01f,
    8.3322256622392457162205759786691734e-03f,
    -1.9524867674489682553254582414001857e-04f
  };
  return x * jbm_polynomial_3_f32 (x * x, a);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] by the following Taylor' serie:
 * \f$\cos(x)\approx\sum_{n=0}^4\frac{(-1)^n\,x^{2\,n}}{(2\,n)!}\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_coswc_f32 (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
// Taylor' serie
/*
  const float a[5] = { JBM_1_FACT0f, -JBM_1_FACT2f, JBM_1_FACT4f,
    -JBM_1_FACT6f, JBM_1_FACT8f
  };
  return jbm_polynomial_4_f32 (x * x, a);
*/
// Faster
  const float a[5] = {
    1.0000000000000000000000000000000000e+00f,
    -4.9999999965238906843549904534867220e-01f,
    4.1666653828165636463917247496043632e-02f,
    -1.3887779469291056608109602187665577e-03f,
    2.4484799013341679093941386831846651e-05f
  };
  return jbm_polynomial_4_f32 (x * x, a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_f32 approximation (float).
 */
static inline void
jbm_sincoswc_f32 (const float x,
                  ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  float *s,     ///< pointer to the sin function value (float).
                  float *c)     ///< pointer to the cos function value (float).
{
  float s0;
  *s = s0 = jbm_sinwc_f32 (x);
  *c = sqrtf (1.f - s0 * s0);
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_f32 and
 * jbm_coswc_f32 approximations (float).
 *
 * \return function value (float).
 */
static inline float
jbm_sin_f32 (const float x)     ///< float number.
{
  float y;
  y = jbm_rest_f32 (x, 2.f * M_PIf);
  if (y < M_PI_4f)
    return jbm_sinwc_f32 (y);
  if (y < 3.f * M_PI_4f)
    return jbm_coswc_f32 (M_PI_2f - y);
  if (y < 5.f * M_PI_4f)
    return jbm_sinwc_f32 (M_PIf - y);
  if (y < 7.f * M_PI_4f)
    return -jbm_coswc_f32 (3.f * M_PI_2f - y);
  return jbm_sinwc_f32 (y - 2.f * M_PIf);
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_f32 and
 * jbm_coswc_f32 approximations (float).
 *
 * \return function value (float).
 */
static inline float
jbm_cos_f32 (const float x)     ///< float number.
{
  float y;
  y = jbm_rest_f32 (x, 2.f * M_PIf);
  if (y < M_PI_4f)
    return jbm_coswc_f32 (y);
  if (y < 3.f * M_PI_4f)
    return jbm_sinwc_f32 (M_PI_2f - y);
  if (y < 5.f * M_PI_4f)
    return -jbm_coswc_f32 (M_PIf - y);
  if (y < 7.f * M_PI_4f)
    return jbm_sinwc_f32 (y - 3.f * M_PI_2f);
  return jbm_coswc_f32 (y - 2.f * M_PIf);
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sincoswc_f32
 * approximation (float).
 */
static inline void
jbm_sincos_f32 (const float x,
                ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                float *s,       ///< pointer to the sin function value (float).
                float *c)       ///< pointer to the cos function value (float).
{
  float y;
  y = jbm_rest_f32 (x, 2.f * M_PIf);
  if (y < M_PI_4f)
    jbm_sincoswc_f32 (y, s, c);
  else if (y < 3.f * M_PI_4f)
    jbm_sincoswc_f32 (M_PI_2f - y, c, s);
  else if (y < 5.f * M_PI_4f)
    {
      jbm_sincoswc_f32 (M_PIf - y, s, c);
      *c = -(*c);
    }
  else if (y < 7.f * M_PI_4f)
    {
      jbm_sincoswc_f32 (y - 3.f * M_PI_2f, c, s);
      *s = -(*s);
    }
  else
    jbm_sincoswc_f32 (y - 2.f * M_PIf, s, c);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_f32 function
 * (float).
 *
 * \return function value (float).
 */
static inline float
jbm_tan_f32 (const float x)     ///< float number.
{
  float s, c;
  jbm_sincos_f32 (x, &s, &c);
  return s / c;
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] by the following Taylor' serie:
 * \f$atan(x)\approx\sum_{i=0}^9\frac{(-1)^{2\,n}\,x^{2\,n+1}}{2\,n+1}\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_atanwc0_f32 (const float x)
                 ///< float number \f$\in\left[0,\frac12\right]\f$.
{
// Taylor' serie
/*
  const float a[10] = { 1.f, -1.f / 3.f, 1.f / 5.f, -1.f / 7.f,
    1.f / 9.f, -1.f / 11.f, 1.f / 13.f, -1.f / 15.f, 1.f / 17.f, -1.f / 19.f
  };
  return x * jbm_polynomial_9_f32 (x * x, a);
*/
// Faster
  const float a[4] = {
    9.9999984048730143841335295268244848e-01f,
    4.9566847198521400589504493089955823e-01f,
    8.2898705878810240458099950004542931e-01f,
    7.6658333542753920209846592962853791e-02f
  };
  return x * jbm_rational_3_1_f32 (x * x, a);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2] by the following Taylor' serie:
 * \f$atan(1+x)\approx
 * \frac{\pi}{4}
 * +\frac{x}{2}
 * -\frac{x^2}{4}
 * +\frac{x^3}{12}
 * -\frac{x^5}{40}
 * +\frac{x^6}{48}
 * -\frac{x^7}{112}
 * +\frac{x^9}{288}
 * -\frac{x^{10}}{320}
 * +\frac{x^{11}}{704}
 * -\frac{x^{13}}{1664}\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_atanwc1_f32 (const float x)
                 ///< float number \f$\in\left[\frac12,1\right]\f$.
{
// Taylor' serie
/*
  const float a1[4] = { 1.f / 2.f, -1.f / 40.f, 1.f / 288.f, -1.f / 1664.f };
  const float a2[4] = { -1.f / 4.f, 1.f / 48.f, -1.f / 320.f, 1.f / 1792.f };
  const float a3[4] = { 1.f / 12.f, -1.f / 112.f, 1.f / 704.f, -1.f / 3840.f };
  float x1, x4;
  x1 = x - 1.f;
  x4 = x1 * x1;
  x4 *= x4;
  return M_PI_4f + x1 * (jbm_polynomial_3_f32 (x4, a1)
                         + x1 * (jbm_polynomial_3_f32 (x4, a2)
                                 + x1 * jbm_polynomial_3_f32 (x4, a3)));
*/
// Faster
  const float a[8] = {
    7.8539816255139945753131801776549671e-01f,
    1.5745201941534749424905726297312445e+00f,
    1.0480101799785619330373271236286859e+00f,
    2.5928000609503906398597815174946580e-01f,
    1.3681216008010664678472144108090419e+00f,
    7.8170438323723224777454800430939851e-01f,
    1.6186088663013176341397431580496626e-01f,
    6.2512302543463204942783713123096548e-04f
  };
  return jbm_rational_7_3_f32 (x - 1.f, a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_f32 and
 * jbm_atanwc1_f32 functions (float).
 *
 * \return function value (in [-pi/2,pi/2]) (float).
 */
static inline float
jbm_atan_f32 (const float x)    ///< float number.
{
  float f, ax;
  ax = jbm_abs_f32 (x);
  if (ax > 1.5f)
    {
      ax = 1.f / ax;
      if (ax > 0.5f)
        f = M_PI_2f - jbm_atanwc1_f32 (ax);
      else
        f = M_PI_2f - jbm_atanwc0_f32 (ax);
    }
  else
    {
      if (ax > 0.5f)
        f = jbm_atanwc1_f32 (ax);
      else
        f = jbm_atanwc0_f32 (ax);
    }
  if (x < 0.f)
    f = -f;
  return f;
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_f32
 * function (float).
 *
 * \return function value (in [-pi,pi]) (float).
 */
static inline float
jbm_atan2_f32 (const float y,   ///< float y component.
               const float x)   ///< float x component.
{
  float f;
  f = jbm_atan_f32 (y / x);
  if (x < 0.f)
    {
      if (y < 0.f)
        f -= M_PIf;
      else
        f += M_PIf;
    }
  return f;
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_f32 function
 * (float).
 *
 * \return function value (in [-pi/2,pi/2]) (float).
 */
static inline float
jbm_asin_f32 (const float x)    ///< float number.
{
  return jbm_atan_f32 (x / sqrtf (1.f - x * x));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_f32 function
 * (float).
 *
 * \return function value (in [0,pi]) (float).
 */
static inline float
jbm_acos_f32 (const float x)    ///< float number.
{
  float f;
  f = jbm_atan_f32 (sqrtf (1.f - x * x) / x);
  if (x < 0.f)
    f += M_PIf;
  return f;
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_sinh_f32 (const float x)    ///< float number.
{
  float f;
  f = jbm_exp_f32 (x);
  return 0.5f * (f - 1.f / f);
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_cosh_f32 (const float x)    ///< float number.
{
  float f;
  f = jbm_exp_f32 (x);
  return 0.5f * (f + 1.f / f);
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_tanh_f32 (const float x)    ///< float number.
{
  float f, fi;
  if (x > JBM_FLT_MAX_E_EXP)
    return 1.f;
  if (x < -JBM_FLT_MAX_E_EXP)
    return -1.f;
  f = jbm_exp_f32 (x);
  fi = 1.f / f;
  return (f - fi) / (f + fi);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_asinh_f32 (const float x)   ///< float number.
{
  return jbm_log_f32 (x + sqrtf (x * x + 1.f));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_acosh_f32 (const float x)   ///< float number.
{
  return jbm_log_f32 (x + sqrtf (x * x - 1.f));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_atanh_f32 (const float x)   ///< float number.
{
  return 0.5f * jbm_log_f32 ((1.f + x) / (1.f - x));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] by the following Taylor' serie:
 * \f$erf(x)\approx\frac{2}{\sqrt{\pi}}\,
 * \sum_{i=0}^8\frac{(-1)^n\,x^{2\,n+1}}{n!\,(2\,n+1)}\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_erfwc_f32 (const float x)
               ///< float number \f$\in\left[-1,1\right]\f$.
{
// Taylor' serie
// Faster
  const float a[6] = {
    1.1283791671633124547603970137089329e+00f,
    1.1356247077387072221530473806173895e-01f,
    3.3606359392673594485175487779855494e-02f,
    4.3397545597876753616401102540952801e-01f,
    7.4441296041206635020857929305718177e-02f,
    5.2260592856163505486272407800095742e-03f
  };
  return x * jbm_rational_5_2_f32 (x * x, a);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ by the following Taylor' serie:
 * \f$erfc(x)\approx\frac{x\,\exp\left(-\frac{1}{x^2}\right)}{\sqrt{\pi}}\,
 * \sum_{i=0}^8\frac{(-1)^n\,x^{2\,n+1}}{n!\,(2\,n+1)}\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_erfcwc_f32 (const float x)
                ///< float number \f$\in\left[1,\infty\right]\f$.
{
// Taylor' serie
// Faster
  const float a[7] = {
    5.6418091764636642421399952962410440e-01,
    2.3259215523506370130840763503668292e+00,
    1.7480917193581656978658253659192661e+00,
    1.2835716481660171242272557816263124e-01,
    4.6220051294746234636042153676346028e+00,
    4.6697994386130441831194770859452481e+00,
    8.5584393582117540916415181581091126e-01
  };
  float x2;
  if (x > 1.0019834265884623367967105586324901e+01f)
    return 0.f;
  x2 = x * x;
  return jbm_rational_6_3_f32 (1.f / x2, a) / (x * jbm_exp_f32 (x2));
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_f32 and
 * jbm_erfcwc_f32
 *
 * \return function value (float).
 */
static inline float
jbm_erf_f32 (const float x)     ///< float number.
{
  float ax;
  ax = jbm_abs_f32 (x);
  if (ax > 1.f)
    return x / ax * (1.f - jbm_erfcwc_f32 (ax));
  return jbm_erfwc_f32 (x);
}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_f32 and
 * jbm_erfcwc_f32
 *
 * \return function value (float).
 */
static inline float
jbm_erfc_f32 (const float x)    ///< float number.
{
  float ax;
  ax = jbm_abs_f32 (x);
  if (ax > 1.f)
    return 1.f - x / ax * (1.f - jbm_erfcwc_f32 (ax));
  return 1.f - jbm_erfwc_f32 (x);
}

#endif
