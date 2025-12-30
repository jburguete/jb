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
 * \file math_f64.h
 * \brief Header file with useful mathematical functions for double.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_F64__H
#define JB_MATH_F64__H 1

/**
 * union to work with bits in double numbers.
 */
typedef union
{
  double x;                     ///< floating point.
  uint64_t i;                   ///< bits.
} JBMF64;

/**
 * Function to calculate the double of a double number.
 *
 * \return double double.
 */
static inline double
jbm_dbl_f64 (const double x)    ///< double number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a double number.
 *
 * \return double square.
 */
static inline double
jbm_sqr_f64 (const double x)    ///< double number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the abs function (double).
 *
 * \return function value (double).
 */
static inline double
jbm_abs_f64 (const double x)    ///< double number.
{
  JBMF64 y;
  y.x = x;
  y.i &= 0x7fffffffffffffffll;
  return y.x;
}

/**
 * Function to calculate the hypot function (double).
 *
 * \return function value (double).
 */
static inline double
jbm_hypot_f64 (const double x,  ///< 1st double number.
               const double y)  ///< 2nd double number.
{
  return sqrt (x * x + y * y);
}

/**
 * Function to calculate the rest of a division (double).
 *
 * \return rest value (in [0,|divisor|) interval).
 */
static inline double
jbm_rest_f64 (const double x,   ///< dividend (double).
              const double d)   ///< divisor (double).
{
  double f;
  f = floor (x / d);
  return x - f * d;
}

/**
 * Function to implement the standard frexp function (double).
 *
 * \return normalize fraction value in [1/2,1).
 */
static inline double
jbm_frexp_f64 (const double x,  ///< double number.
               int *e)          ///< pointer to the extracted exponent.
{
  JBMF64 y, z;
  y.x = x;
  y.i &= 0x7ff0000000000000ll;
  if (y.i == 0x7ff0000000000000ll)
    {
      *e = 0;
      return x;
    }
  if (!y.i)
    {
      y.x = x;
      y.i &= 0x000fffffffffffffll;
      if (!y.i)
        {
          *e = 0;
          return x;
        }
      y.i = 0x0010000000000000ll;
      z.x = x / y.x;
      z.i &= 0x7ff0000000000000ll;
      *e = (int) (z.i >> 52ll) - 2044;
      y.x *= z.x;
    }
  else
    *e = (int) (y.i >> 52ll) - 1022;
  return 0.5 * (x / y.x);
}

/**
 * Function to calculate the function 2^n with n an integer number (int).
 *
 * \return function value (double).
 */
static inline double
jbm_exp2n_f64 (int e)           ///< exponent number (int).
{
  JBMF64 x;
  if (e > 1023)
    return INFINITY;
  if (e < -1074)
    return 0.;
  if (e > -1023)
    x.i = (1023ll + e) << 52ll;
  else
    x.i = 0x0008000000000000ll >> (-e - 1023ll);
  return x.x;
}

/**
 * Function to implement the standard ldexp function (double).
 *
 * \return function value (double).
 */
static inline double
jbm_ldexp_f64 (const double x,  ///< double number.
               int e)           ///< exponent number (int).
{
  return x * jbm_exp2n_f64 (e);
}

/**
 * Function to calculate a 1st order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * p[1];
}

/**
 * Function to calculate a 2nd order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_1_f64 (x, p + 1);
}

/**
 * Function to calculate a 3rd order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_2_f64 (x, p + 1);
}

/**
 * Function to calculate a 4th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_4_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_3_f64 (x, p + 1);
}

/**
 * Function to calculate a 5th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_5_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_4_f64 (x, p + 1);
}

/**
 * Function to calculate a 6th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_6_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_5_f64 (x, p + 1);
}

/**
 * Function to calculate a 7th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_7_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_6_f64 (x, p + 1);
}

/**
 * Function to calculate a 8th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_8_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_7_f64 (x, p + 1);
}

/**
 * Function to calculate a 9th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_9_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_8_f64 (x, p + 1);
}

/**
 * Function to calculate a 10th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_10_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_9_f64 (x, p + 1);
}

/**
 * Function to calculate a 11th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_11_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_10_f64 (x, p + 1);
}

/**
 * Function to calculate a 12th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_12_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_11_f64 (x, p + 1);
}

/**
 * Function to calculate a 13th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_13_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_12_f64 (x, p + 1);
}

/**
 * Function to calculate a 14th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_14_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_13_f64 (x, p + 1);
}

/**
 * Function to calculate a 15th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_15_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_14_f64 (x, p + 1);
}

/**
 * Function to calculate a 16th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_16_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_15_f64 (x, p + 1);
}

/**
 * Function to calculate a 17th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_17_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_16_f64 (x, p + 1);
}

/**
 * Function to calculate a 18th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_18_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_17_f64 (x, p + 1);
}

/**
 * Function to calculate a 19th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_19_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_18_f64 (x, p + 1);
}

/**
 * Function to calculate a 20th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_20_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_19_f64 (x, p + 1);
}

/**
 * Function to calculate a 21th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_21_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_20_f64 (x, p + 1);
}

/**
 * Function to calculate a 22th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_22_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_21_f64 (x, p + 1);
}

/**
 * Function to calculate a 23th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_23_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_22_f64 (x, p + 1);
}

/**
 * Function to calculate a 24th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_24_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_23_f64 (x, p + 1);
}

/**
 * Function to calculate a 25th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_25_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_24_f64 (x, p + 1);
}

/**
 * Function to calculate a 26th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_26_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_25_f64 (x, p + 1);
}

/**
 * Function to calculate a 27th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_27_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_26_f64 (x, p + 1);
}

/**
 * Function to calculate a 28th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_28_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_27_f64 (x, p + 1);
}

/**
 * Function to calculate a 29th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_polynomial_29_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_28_f64 (x, p + 1);
}

/**
 * Function to calculate a 1st order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_1_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * p[1]);
}

/**
 * Function to calculate a 2nd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_2_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_1_f64 (x, p + 1));
}

/**
 * Function to calculate a 2nd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_2_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_1_f64 (x, p) / (1. + x * p[2]);
}

/**
 * Function to calculate a 3rd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_3_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_2_f64 (x, p + 1));
}

/**
 * Function to calculate a 3rd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_3_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 2));
}

/**
 * Function to calculate a 3rd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_3_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_2_f64 (x, p) / (1. + x * p[3]);
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_4_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_3_f64 (x, p + 1));
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_4_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 2));
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_4_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 3));
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_4_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_3_f64 (x, p) / (1. + x * p[4]);
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_5_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_4_f64 (x, p + 1));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_5_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 2));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_5_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 3));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_5_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 4));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_5_4_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_4_f64 (x, p) / (1. + x * p[5]);
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_6_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_5_f64 (x, p + 1));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_6_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 2));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_6_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 3));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_6_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 4));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_6_4_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 5));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_6_5_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_5_f64 (x, p) / (1. + x * p[6]);
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_6_f64 (x, p + 1));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 2));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 3));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 4));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_4_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 5));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_5_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 6));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_7_6_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_6_f64 (x, p) / (1. + x * p[7]);
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_7_f64 (x, p + 1));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 2));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 3));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 4));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_4_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 5));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_5_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 6));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_6_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 7));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_8_7_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_7_f64 (x, p) / (1. + x * p[8]);
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_0_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_8_f64 (x, p + 1));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_1_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 2));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_2_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 3));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_3_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 4));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_4_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 5));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_5_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 6));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_6_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 7));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_7_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 8));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_9_8_f64 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_polynomial_8_f64 (x, p) / (1. + x * p[9]);
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_9_f64 (x, p + 1));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 2));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 3));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 4));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 5));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 6));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 7));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 8));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 9));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_10_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return jbm_polynomial_9_f64 (x, p) / (1. + x * p[10]);
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_10_f64 (x, p + 1));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 2));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 3));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 4));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 5));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 6));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 7));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 8));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 9));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 10));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_11_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_10_f64 (x, p) / (1. + x * p[11]);
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_11_f64 (x, p + 1));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 2));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 3));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 4));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 5));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 6));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 7));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 8));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 9));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 10));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 11));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_12_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_11_f64 (x, p) / (1. + x * p[12]);
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_12_f64 (x, p + 1));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 2));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 3));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 4));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 5));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 6));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 7));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 8));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 9));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 10));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 11));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 12));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_13_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_12_f64 (x, p) / (1. + x * p[13]);
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_13_f64 (x, p + 1));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 2));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 3));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 4));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 5));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 6));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 7));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 8));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 9));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 10));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 11));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 12));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 13));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_14_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_13_f64 (x, p) / (1. + x * p[14]);
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_14_f64 (x, p + 1));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 2));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 3));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 4));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 5));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 6));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 7));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 8));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 9));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 10));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 11));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 12));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 13));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 14));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_15_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_14_f64 (x, p) / (1. + x * p[15]);
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_15_f64 (x, p + 1));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_14_f64 (x, p + 2));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 3));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 4));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 5));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 6));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 7));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 8));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 9));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 10));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 11));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 12));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 13));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 14));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_14_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 15));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_16_15_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_15_f64 (x, p) / (1. + x * p[16]);
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_16_f64 (x, p + 1));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_15_f64 (x, p + 2));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_14_f64 (x, p + 3));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 4));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 5));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 6));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 7));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 8));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 9));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 10));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 11));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 12));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 13));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 14));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_14_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 15));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_15_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_15_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 16));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_17_16_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_16_f64 (x, p) / (1. + x * p[17]);
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_17_f64 (x, p + 1));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_16_f64 (x, p + 2));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_15_f64 (x, p + 3));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_14_f64 (x, p + 4));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 5));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 6));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 7));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 8));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 9));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 10));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 11));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 12));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 13));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 14));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_14_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 15));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_15_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_15_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 16));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_16_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_16_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 17));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_18_17_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_17_f64 (x, p) / (1. + x * p[18]);
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_18_f64 (x, p + 1));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_17_f64 (x, p + 2));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_16_f64 (x, p + 3));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_15_f64 (x, p + 4));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_14_f64 (x, p + 5));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 6));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 7));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 8));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 9));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 10));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 11));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 12));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 13));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 14));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_14_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 15));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_15_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_15_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 16));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_16_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_16_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 17));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_17_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_17_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 18));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_19_18_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_18_f64 (x, p) / (1. + x * p[19]);
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_19_f64 (x, p + 1));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_18_f64 (x, p + 2));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_17_f64 (x, p + 3));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_16_f64 (x, p + 4));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_15_f64 (x, p + 5));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_14_f64 (x, p + 6));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 7));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 8));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 9));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 10));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 11));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 12));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 13));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 14));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_14_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 15));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_15_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_15_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 16));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_16_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_16_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 17));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_17_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_17_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 18));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_18_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_18_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 19));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_20_19_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_19_f64 (x, p) / (1. + x * p[20]);
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_0_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_polynomial_20_f64 (x, p + 1));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_1_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_1_f64 (x, p) / (1. + x * jbm_polynomial_19_f64 (x, p + 2));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_2_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_2_f64 (x, p) / (1. + x * jbm_polynomial_18_f64 (x, p + 3));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_3_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_3_f64 (x, p) / (1. + x * jbm_polynomial_17_f64 (x, p + 4));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_4_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_4_f64 (x, p) / (1. + x * jbm_polynomial_16_f64 (x, p + 5));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_5_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_5_f64 (x, p) / (1. + x * jbm_polynomial_15_f64 (x, p + 6));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_6_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_6_f64 (x, p) / (1. + x * jbm_polynomial_14_f64 (x, p + 7));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_7_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_7_f64 (x, p) / (1. + x * jbm_polynomial_13_f64 (x, p + 8));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_8_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_8_f64 (x, p) / (1. + x * jbm_polynomial_12_f64 (x, p + 9));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_9_f64 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_polynomial_9_f64 (x, p) / (1. + x * jbm_polynomial_11_f64 (x, p + 10));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_10_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_10_f64 (x, p) / (1. + x * jbm_polynomial_10_f64 (x, p + 11));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_11_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_11_f64 (x, p) / (1. + x * jbm_polynomial_9_f64 (x, p + 12));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_12_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_12_f64 (x, p) / (1. + x * jbm_polynomial_8_f64 (x, p + 13));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_13_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_13_f64 (x, p) / (1. + x * jbm_polynomial_7_f64 (x, p + 14));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_14_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_14_f64 (x, p) / (1. + x * jbm_polynomial_6_f64 (x, p + 15));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_15_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_15_f64 (x, p) / (1. + x * jbm_polynomial_5_f64 (x, p + 16));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_16_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_16_f64 (x, p) / (1. + x * jbm_polynomial_4_f64 (x, p + 17));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_17_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_17_f64 (x, p) / (1. + x * jbm_polynomial_3_f64 (x, p + 18));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_18_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_18_f64 (x, p) / (1. + x * jbm_polynomial_2_f64 (x, p + 19));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_19_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_polynomial_19_f64 (x, p) / (1. + x * jbm_polynomial_1_f64 (x, p + 20));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_rational_21_20_f64 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_polynomial_20_f64 (x, p) / (1. + x * p[21]);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2] by the following Taylor' serie:
 * \f$\exp(x)-1\approx\sum_{n=0}^{13}\frac{x^n}{n!}-1\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_expm1wc_f64 (const double x)
                 ///< double number \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const double a1 = 9.9999999999999999866523626874215789e-01;
  const double a3 = 2.4998453858981619674396608301250598e-02;
  const double a4 = -4.9999999999999999933261730198779978e-01;
  const double a5 = 1.0833178719231388723914535942973379e-01;
  const double a6 = -1.2499226929490809837198234785821115e-02;
  const double a7 = 6.9431559947707471609539363612700440e-04;
  const double a9 = -1.6512957626515476078093301716091145e-06;
  double x2;
  x2 = x * x;
  return x * (a1 + x2 * a3)
    / (1. + x * (a4 + x * (a5 + x * (a6 + x * (a7 + x2 * a9)))));
}

/**
 * Function to calculate the well conditionated function exp2(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_exp2wc_f64 (const double x)
                ///< double number \f$\in[\frac12,1]\f$.
{
  const double a[10] = {
    1.0000000000000000000000000000000000e+00,
    3.9258151226411065308244519566769797e-01,
    6.9739515090496080774732642702089028e-02,
    7.1389939701896796745750569911360599e-03,
    4.3218928769569309780629642538603198e-04,
    1.2881240743697500078285902049250544e-05,
    -3.0056566829585495131707842124897699e-01,
    3.7849253684547663274549098885928275e-02,
    -2.3963775757649522517273856260478191e-03,
    6.5338113690142359075446833275740055e-05
  };
  return jbm_rational_9_5_f64 (x, a);
}

/**
 * Function to calculate the function exp2(x) using the jbm_expm1wc_f64 and
 * jbm_exp2n_f64 functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_exp2_f64 (const double x)   ///< double number.
{
  double y, f;
  if (x >= DBL_MAX_EXP)
    return INFINITY;
  y = floor (x);
  f = x - y;
  y = jbm_exp2n_f64 ((int) y);
  return y * jbm_exp2wc_f64 (f);
}

/**
 * Function to calculate the function exp(x) using the jbm_exp2_f64 function
 * (double).
 *
 * \return function value (double).
 */
static inline double
jbm_exp_f64 (const double x)    ///< double number.
{
  return jbm_exp2_f64 (x * M_LOG2E);
}

/**
 * Function to calculate the function exp10(x) using the jbm_exp2_f64 function
 * (double).
 *
 * \return function value (double).
 */
static inline double
jbm_exp10_f64 (const double x)  ///< double number.
{
  return jbm_exp2_f64 (x * M_LN10 / M_LN2);
}

/**
 * Function to calculate the function expm1(x) using the jbm_expm1wc_f64 and
 * jbm_exp_f64 functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_expm1_f64 (const double x)  ///< double number.
{
  if (jbm_abs_f64 (x) < M_LN2 / 2.)
    return jbm_expm1wc_f64 (x);
  return jbm_exp_f64 (x) - 1.;
}

/**
 * Function to calculate the well conditionated function log2(x) for x in
 * [0.5,1] (double).
 *
 * \return function value (double).
 */
static inline double
jbm_log2wc_f64 (const double x) ///< double number.
{
  const double a[13] = {
    -7.6144437566523277330122254344632089e+00,
    -2.2216066036083139675948990450269623e+02,
    -1.0487893454485878722224361830016331e+03,
    -6.3292000191539709400320414735732946e+02,
    1.1423328866992018050176497846576787e+03,
    7.1160949805923005658001879898775365e+02,
    5.7542066723036829120473876650689667e+01,
    5.2391880990474761440440201350054425e+01,
    4.7397328986324026525670605626943957e+02,
    1.2130522064690253478465102043016199e+03,
    9.7697216021067076796632803027576056e+02,
    2.2259322298850925297348801997399448e+02,
    8.7568967556912456642077265430132946e+00
  };
  return jbm_rational_12_6_f64 (x, a);
}

/**
 * Function to calculate the function log_2(x) using jbm_log2wc_f64 and
 * jbm_frexp_f64
 *
 * \return function value (double).
 */
static inline double
jbm_log2_f64 (const double x)   ///< double number.
{
  double y;
  int e;
  if (x < 0.)
    return NAN;
  if (x <= 0.)
    return -INFINITY;
  y = jbm_frexp_f64 (x, &e);
  return jbm_log2wc_f64 (y) + (double) e;
}

/**
 * Function to calculate the function log(x) using jbm_log2_f64 (double).
 *
 * \return function value (double).
 */
static inline double
jbm_log_f64 (const double x)    ///< double number.
{
  return jbm_log2_f64 (x) * M_LN2;
}

/**
 * Function to calculate the function log10(x) using jbm_log2_f64 (double).
 *
 * \return function value (double).
 */
static inline double
jbm_log10_f64 (const double x)  ///< double number.
{
  return jbm_log2_f64 (x) * M_LN2 / M_LN10;
}

/**
 * Function to calculate the function x^e with e an integer number (double).
 *
 * \return function value (double).
 */
static inline double
jbm_pown_f64 (const double x,   ///< double number.
              const int e)      ///< exponent (int).
{
  double f, xn;
  unsigned int i;
  f = 1.;
  if (e < 0)
    xn = 1. / x;
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
 * Function to calculate the function pow using the jbm_exp2_f64 and
 * jbm_log2_f64 functions.
 *
 * \return function value (double).
 */
static inline double
jbm_pow_f64 (const double x,    ///< double number.
             const double e)    ///< exponent (double).
{
  double f;
  f = floor (e);
  if (f == e)
    return jbm_pown_f64 (x, (int) e);
  return jbm_exp2_f64 (e * jbm_log2_f64 (x));
}

/**
 * Function to calculate the function cbrt(x) using the jbm_abs_f64 and
 * jbm_pow_f64 functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_cbrt_f64 (const double x)   ///< double number.
{
  double f;
  f = jbm_pow_f64 (jbm_abs_f64 (x), 1. / 3.);
  if (x < 0.)
    f = -f;
  return f;
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4] by the following Taylor' serie:
 * \f$\sin(x)\approx\sum_{n=0}^7\frac{(-1)^n\,x^{2\,n+1}}{(2\,n+1)!}\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_sinwc_f64 (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const double a[7] = {
    9.9999999999999992623266375181361270e-01,
    -1.6666666666666364329466834698152866e-01,
    8.3333333332914213336391196384413774e-03,
    -1.9841269813721985829832380684607579e-04,
    2.7557309538924391028721730017499636e-06,
    -2.5050236521504840191928711158545970e-08,
    1.5871385203522377107357378411672352e-10
  };
  return x * jbm_polynomial_6_f64 (x * x, a);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4] by the following Taylor' serie:
 * \f$\cos(x)\approx\sum_{n=0}^8\frac{(-1)^n\,x^{2\,n}}{(2\,n)!}\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_coswc_f64 (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  const double a[7] = {
    1.0000000000000000000000000000000000e+00,
    -4.9999999999999440386007503451907815e-01,
    4.1666666666492452770576068098346687e-02,
    -1.3888888870829706370885000466597981e-03,
    2.4801578693699793599283647186616510e-05,
    -2.7555244206161966770970412627633901e-07,
    2.0630480041002573029755920195103607e-09
  };
  return jbm_polynomial_6_f64 (x * x, a);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_sinwc_f64 approximation (double).
 */
static inline void
jbm_sincoswc_f64 (const double x,
                  ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  double *s,    ///< pointer to the sin function value (double).
                  double *c)    ///< pointer to the cos function value (double).
{
  double s0;
  *s = s0 = jbm_sinwc_f64 (x);
  *c = sqrt (1. - s0 * s0);
}

/**
 * Function to calculate the function sin(x) from jbm_sinwc_f64 and
 * jbm_coswc_f64 approximations (double).
 *
 * \return function value (double).
 */
static inline double
jbm_sin_f64 (const double x)    ///< double number.
{
  double y;
  y = jbm_rest_f64 (x, 2. * M_PI);
  if (y < M_PI_4)
    return jbm_sinwc_f64 (y);
  if (y < 3. * M_PI_4)
    return jbm_coswc_f64 (M_PI_2 - y);
  if (y < 5. * M_PI_4)
    return jbm_sinwc_f64 (M_PI - y);
  if (y < 7. * M_PI_4)
    return -jbm_coswc_f64 (3. * M_PI_2 - y);
  return jbm_sinwc_f64 (y - 2. * M_PI);
}

/**
 * Function to calculate the function cos(x) from jbm_sinwc_f64 and
 * jbm_coswc_f64 approximations (double).
 *
 * \return function value (double).
 */
static inline double
jbm_cos_f64 (const double x)    ///< double number.
{
  double y;
  y = jbm_rest_f64 (x, 2. * M_PI);
  if (y < M_PI_4)
    return jbm_coswc_f64 (y);
  if (y < 3. * M_PI_4)
    return jbm_sinwc_f64 (M_PI_2 - y);
  if (y < 5. * M_PI_4)
    return -jbm_coswc_f64 (M_PI - y);
  if (y < 7. * M_PI_4)
    return jbm_sinwc_f64 (y - 3. * M_PI_2);
  return jbm_coswc_f64 (y - 2. * M_PI);
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_sinwc_f64 and
 * jbm_coswc_f64 approximations (double).
 */
static inline void
jbm_sincos_f64 (const double x,
                ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                double *s,      ///< pointer to the sin function value (double).
                double *c)      ///< pointer to the cos function value (double).
{
  double y;
  y = jbm_rest_f64 (x, 2. * M_PI);
  if (y < M_PI_4)
    jbm_sincoswc_f64 (y, s, c);
  else if (y < 3. * M_PI_4)
    jbm_sincoswc_f64 (M_PI_2 - y, c, s);
  else if (y < 5. * M_PI_4)
    {
      jbm_sincoswc_f64 (M_PI - y, s, c);
      *c = -(*c);
    }
  else if (y < 7. * M_PI_4)
    {
      jbm_sincoswc_f64 (y - 3. * M_PI_2, c, s);
      *s = -(*s);
    }
  else
    jbm_sincoswc_f64 (y - 2. * M_PI, s, c);
}

/**
 * Function to calculate the function tan(x) from jbm_sincos_f64.
 *
 * \return function value (double).
 */
static inline double
jbm_tan_f64 (const double x)    ///< double number.
{
  double s, c;
  jbm_sincos_f64 (x, &s, &c);
  return s / c;
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2] by the following Taylor' serie:
 * \f$atan(x)\approx\sum_{i=0}^{23}\frac{(-1)^{2\,n}\,x^{2\,n+1}}{2\,n+1}\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_atanwc0_f64 (const double x)
                 ///< double number \f$\in\left[0,\frac12\right]\f$.
{
  const double a[9] = {
    9.9999999999999844420074944778995293e-01,
    1.7145251561246992004730367697284941e+00,
    8.8907286003634523094686311114666379e-01,
    1.4060174161577778291037471387701890e-01,
    3.2209259411733092528958853122919037e-03,
    2.0478584894577125439666422658485729e+00,
    1.3716923565430806798963303278057845e+00,
    3.3111797144718403623004820983836274e-01,
    2.0695224867062360013320488091923373e-02
  };
  return x * jbm_rational_8_4_f64 (x * x, a);
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
 * -\frac{x^{13}}{1664}
 * +\frac{x^{14}}{1792}
 * -\frac{x^{15}}{3840}
 * +\frac{x^{17}}{8704}
 * -\frac{x^{18}}{9216}
 * +\frac{x^{19}}{19456}
 * -\frac{x^{21}}{43008}
 * +\frac{x^{22}}{45056}
 * -\frac{x^{23}}{94208}
 * +\frac{x^{25}}{204800}
 * -\frac{x^{26}}{212992}
 * +\frac{x^{27}}{442368}
 * -\frac{x^{29}}{950272}
 * +\frac{x^{30}}{983040}
 * -\frac{x^{31}}{2031616}\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_atanwc1_f64 (const double x)
                 ///< double number \f$\in\left[\frac12,1\right]\f$.
{
  const double a[15] = {
    7.8539816339744833436088579936018742e-01,
    3.1342142099514395388471002673907000e+00,
    5.5277934725852236992845279692924433e+00,
    5.6263250451240657954974051237443046e+00,
    3.5691455509277955220247611399499359e+00,
    1.4107283585708358398299324713616932e+00,
    3.2151962700481652797614358117736801e-01,
    3.2589220524981137827650710783366171e-02,
    3.3539857014134666583111698527339982e+00,
    5.2213015168502519821785083384778283e+00,
    4.8011792673505617312282819628830639e+00,
    2.7939745600131054592325655642624428e+00,
    1.0235922021818812559622152968277950e+00,
    2.1789610776449610917832370393938996e-01,
    2.0746688622354119059430410067838464e-02
  };
  double x1;
  x1 = x - 1.;
  return jbm_rational_14_7_f64 (x1, a);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc0_f64 and
 * jbm_atanwc1_f64 functions (double).
 *
 * \return function value (in [-pi/2,pi/2]) (double).
 */
static inline double
jbm_atan_f64 (const double x)   ///< double number.
{
  double f, ax;
  ax = jbm_abs_f64 (x);
  if (ax > 1.5)
    {
      ax = 1. / ax;
      if (ax > 0.5)
        f = M_PI_2 - jbm_atanwc1_f64 (ax);
      else
        f = M_PI_2 - jbm_atanwc0_f64 (ax);
    }
  else
    {
      if (ax > 0.5)
        f = jbm_atanwc1_f64 (ax);
      else
        f = jbm_atanwc0_f64 (ax);
    }
  if (x < 0.)
    f = -f;
  return f;
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_atan_f64
 * function (double).
 *
 * \return function value (in [-pi,pi]) (double).
 */
static inline double
jbm_atan2_f64 (const double y,  ///< double y component.
               const double x)  ///< double x component.
{
  double f;
  f = jbm_atan_f64 (y / x);
  if (x < 0.)
    {
      if (y < 0.)
        f -= M_PI;
      else
        f += M_PI;
    }
  return f;
}

/**
 * Function to calculate the function asin(x) using the jbm_atan_f64 function.
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline double
jbm_asin_f64 (const double x)   ///< double number.
{
  return jbm_atan_f64 (x / sqrt (1. - x * x));
}

/**
 * Function to calculate the function acos(x) using the jbm_atan_f64 function.
 *
 * \return function value (in [0,pi]).
 */
static inline double
jbm_acos_f64 (const double x)   ///< double number.
{
  double f;
  f = jbm_atan_f64 (sqrt (1. - x * x) / x);
  if (x < 0.)
    f += M_PI;
  return f;
}

/**
 * Function to calculate the function sinh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_sinh_f64 (const double x)   ///< double number.
{
  double f;
  f = jbm_exp_f64 (x);
  return 0.5 * (f - 1. / f);
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_cosh_f64 (const double x)   ///< double number.
{
  double f;
  f = jbm_exp_f64 (x);
  return 0.5 * (f + 1. / f);
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_tanh_f64 (const double x)   ///< double number.
{
  double f, fi;
  if (x > JBM_DBL_MAX_E_EXP)
    return 1.f;
  if (x < -JBM_DBL_MAX_E_EXP)
    return -1.;
  f = jbm_exp_f64 (x);
  fi = 1. / f;
  return (f - fi) / (f + fi);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_asinh_f64 (const double x)  ///< double number.
{
  return jbm_log_f64 (x + sqrt (x * x + 1.));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_acosh_f64 (const double x)  ///< double number.
{
  return jbm_log_f64 (x + sqrt (x * x - 1.));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_atanh_f64 (const double x)  ///< double number.
{
  return 0.5 * jbm_log_f64 ((1. + x) / (1. - x));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1] by the following Taylor' serie:
 * \f$erf(x)\approx\frac{2}{\sqrt{\pi}}\,
 * \sum_{i=0}^8\frac{(-1)^n\,x^{2\,n+1}}{n!\,(2\,n+1)}\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_erfwc_f64 (const double x)
             ///< double number \f$\in\left[-1,1\right]\f$.
{
  const double a[10] = {
    1.1283791670955125741568625140595922e+00,
    1.4214718479810524638147731873568913e-01,
    4.5306179971396543690828467584139032e-02,
    1.8274816817509842382146606482513749e-03,
    1.9503007205367896131960034397311431e-04,
    4.5930799587872320487578620901568015e-01,
    9.3254221872966235149954630460053812e-02,
    1.0583028318143433311926587801872070e-02,
    6.8136985371491773172778301792791972e-04,
    2.0308921409930923470618470733464236e-05
  };
  return x * jbm_rational_9_4_f64 (x * x, a);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$ by the following Taylor' serie:
 * \f$erfc(x)\approx\frac{x\,\exp\left(-\frac{1}{x^2}\right)}{\sqrt{\pi}}\,
 * \sum_{i=0}^8\frac{(-1)^n\,x^{2\,n+1}}{n!\,(2\,n+1)}\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_erfcwc_f64 (const double x)
                ///< double number \f$\in\left[1,\infty\right]\f$.
{
  const double a[20] = {
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
  double x2;
  if (x > 2.7213293210812948815313823864674587e+01)
    return 0.;
  x2 = x * x;
  return jbm_rational_19_9_f64 (1. / x2, a) / (x * jbm_exp_f64 (x2));
}

/**
 * Function to calculate the function erf(x) using jbm_erfwc_f64 and
 * jbm_erfcwc_f64 functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_erf_f64 (const double x)    ///< double number.
{
  double ax;
  ax = jbm_abs_f64 (x);
  if (ax > 1.)
    return x / ax * (1. - jbm_erfcwc_f64 (ax));
  return jbm_erfwc_f64 (x);
}

/**
 * Function to calculate the function erfc(x) using jbm_erfwc_f64 and
 * jbm_erfcwc_f64 functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_erfc_f64 (const double x)   ///< double number.
{
  double ax;
  ax = jbm_abs_f64 (x);
  if (ax > 1.)
    return 1. - x / ax * (1. - jbm_erfcwc_f64 (ax));
  return 1. - jbm_erfwc_f64 (x);
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * double.
 *
 * \return interval number.
 */
static inline unsigned int
jbm_array_search_f64 (const double *xx, ///< double array.
                      const double x,   ///< number to search.
                      const unsigned int n)     ///< number of array elements.
{
  unsigned int i, j, n1;
  n1 = n - 1;
  for (i = 0; n1 - i > 1;)
    {
      j = (i + n1) >> 1;
      if (x < xx[j])
        n1 = j;
      else
        i = j;
    }
  return i;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * array of double numbers.
 * \return interval number, -1 if x<fa[0] or n-1 if x>fa[n-1].
 */
static inline int
jbm_array_search_extended_f64 (const double *xx,        ///< double array.
                               const double x,  ///< number to search.
                               const unsigned int n)
                               ///< number of array elements.
{
  unsigned int n1;
  if (x < xx[0])
    return -1;
  n1 = n - 1;
  if (x >= xx[n1])
    return (int) n1;
  return (int) jbm_array_search_f64 (xx, x, n);
}

/**
 * Function to interchange 2 double arrays.
 */
static inline void
jbm_array_change_f64 (double **restrict fa,     ///< 1st double array.
                      double **restrict fb)     ///< 2nd double array.
{
  double *fc;
  fc = *fa;
  *fa = *fb;
  *fb = fc;
}

/**
 * Function to merge 2 increasingly sorted double arrays.
 *
 * \return resulting double array.
 */
static inline double *
jbm_array_merge_f64 (const double *xa,
                     ///< pointer to the 1st increasingly sorted double array.
                     const unsigned int na,
                     ///< number of elements of the 1st array.
                     const double *xb,
                     ///< pointer to the 2nd increasingly sorted double array.
                     const unsigned int nb,
                     ///< number of elements of the 2nd array.
                     unsigned int *nc)
                     ///< pointer to the number of elements of the new array.
{
  double *xc;
  unsigned int i, j, k;
  xc = (double *) malloc ((na + nb) * sizeof (double));
  if (!xc)
    return NULL;
  for (i = j = k = 0; i < na || j < nb; ++k)
    {
      if (i >= na)
        xc[k] = xb[j++];
      else if (j >= nb)
        xc[k] = xa[i++];
      else if (xa[i] > xb[j])
        xc[k] = xb[j++];
      else if (xa[i] < xb[j])
        xc[k] = xa[i++];
      else
        xc[k] = xa[i++], j++;
    }
  xc = (double *) realloc (xc, k * sizeof (double));
  *nc = k;
  return xc;
}

#if !defined(__SSE4_2__) && !defined(__ARM_NEON__) && !defined(__riscv_vector)

/**
 * Function to add 2 double arrays.
 */
static inline void
jbm_array_add_f64 (double *xr,  ///< result double array.
                   const double *x1,    ///< 1st addend double array.
                   const double *x2,    ///< 1st addend double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  double k;
  unsigned int i;
  k = xx[0];
  for (i = 0; ++i < n;)
    k = fmax (k, xx[i]);
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
  double k;
  unsigned int i;
  k = xx[0];
  for (i = 0; ++i < n;)
    k = fmin (k, xx[i]);
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
  double kmax, kmin;
  unsigned int i;
  kmax = kmin = xx[0];
  for (i = 0; ++i < n;)
    kmax = fmax (kmax, xx[i]), kmin = fmin (kmin, xx[i]);
  *max = kmax, *min = kmin;
}

#endif

#endif
