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
  long long unsigned int i;     ///< bits.
} JBMF64;

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
  y.i &= 0x7fffffffffffffffL;
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
  y.i &= 0x7ff0000000000000L;
  if (y.i == 0x7ff0000000000000L)
    {
      *e = 0;
      return x;
    }
  if (!y.i)
    {
      y.x = x;
      y.i &= 0x000fffffffffffffL;
      if (!y.i)
        {
          *e = 0;
          return x;
        }
      y.i = 0x0010000000000000L;
      z.x = x / y.x;
      z.i &= 0x7ff0000000000000L;
      *e = (int) (z.i >> 52L) - 2044;
      y.x *= z.x;
    }
  else
    *e = (int) (y.i >> 52L) - 1022;
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
    x.i = (1023L + e) << 52L;
  else
    x.i = 0x0008000000000000L >> (-e - 1023L);
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
// Taylor' serie
/*
  const double a[12] = { JBM_1_FACT1, JBM_1_FACT2,
    JBM_1_FACT3, JBM_1_FACT4, JBM_1_FACT5, JBM_1_FACT6, JBM_1_FACT7,
    JBM_1_FACT8, JBM_1_FACT9, JBM_1_FACT10, JBM_1_FACT11, JBM_1_FACT12
  };
  return x * jbm_polynomial_11_f64 (x, a);
*/
// Faster
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
  const double a[11] = {
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
  return jbm_rational_10_5_f64 (x, a);
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
  const double a[15] = {
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
  return jbm_rational_14_7_f64 (x, a);
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
// Taylor' serie
/*
  const double a[8] = { JBM_1_FACT1, -JBM_1_FACT3, JBM_1_FACT5,
    -JBM_1_FACT7, JBM_1_FACT9, -JBM_1_FACT11, JBM_1_FACT13, -JBM_1_FACT15
  };
  return x * jbm_polynomial_7_f64 (x * x, a);
*/
// Faster
  const double a[7] = {
    9.9999999999999999903298528022992608e-01,
    -1.6666666666666655053351577460983916e-01,
    8.3333333333296595862456464924174883e-03,
    -1.9841269836544823130841945764534327e-04,
    2.7557316317701496371521577585751979e-06,
    -2.5051208834780181372040633623490924e-08,
    1.5924807404448211967660639660668199e-10
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
// Taylor' serie
/*
  const double a[9] = { JBM_1_FACT0, -JBM_1_FACT2, JBM_1_FACT4,
    -JBM_1_FACT6, JBM_1_FACT8, -JBM_1_FACT10, JBM_1_FACT12, -JBM_1_FACT14,
    JBM_1_FACT16
  };
  return jbm_polynomial_8_f64 (x * x, a);
*/
// Faster
  const double a[8] = {
    1.0000000000000000000000000000000000e+00,
    -4.9999999999999999993951803557338505e-01,
    4.1666666666666659403140067984185230e-02,
    -1.3888888888886591172439404142742802e-03,
    2.4801587298632131731562671126858188e-05,
    -2.7557317406370546117628828935636779e-07,
    2.0876194438132647163852946046090933e-09,
    -1.1386810444187770618168073556226784e-11
  };
  return jbm_polynomial_7_f64 (x * x, a);
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
// Taylor' serie
/*
  const double a[24] = { 1., -1. / 3., 1. / 5., -1. / 7., 1. / 9.,
    -1. / 11., 1. / 13., -1. / 15., 1. / 17., -1. / 19., 1. / 21., -1. / 23.,
    1. / 25., -1. / 27., 1. / 29., -1. / 31., 1. / 33., -1. / 35., 1. / 37.,
    -1. / 39., 1. / 41., -1. / 43., 1. / 45., -1. / 47.
  };
  return x * jbm_polynomial_23_f64 (x * x, a);
*/
// Faster
  const double a[10] = {
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
  return x * jbm_rational_9_4_f64 (x * x, a);
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
// Taylor' serie
/*
  const double a1[8] = { 1. / 2., -1. / 40., 1. / 288., -1. / 1664., 1. / 8704.,
    -1. / 43008., 1. / 204800., -1. / 950272.
  };
  const double a2[8] = { -1. / 4., 1. / 48., -1. / 320., 1. / 1792.,
    -1. / 9216., 1. / 45056., -1. / 212992., 1. / 983040.
  };
  const double a3[8] = { 1. / 12., -1. / 112., 1. / 704., -1. / 3840.,
    1. / 19456., -1. / 94208., 1. / 442368., -1. / 2031616.
  };
  double x1, x4;
  x1 = x - 1.;
  x4 = x1 * x1;
  x4 *= x4;
  return M_PI_4 + x1 * (jbm_polynomial_7_f64 (x4, a1)
                        + x1 * (jbm_polynomial_7_f64 (x4, a2)
                                + x1 * jbm_polynomial_7_f64 (x4, a3)));
*/
  const double a[17] = {
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
  double x1;
  x1 = x - 1.;
  return jbm_rational_16_8_f64 (x1, a);
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
// Taylor' serie
// Faster
  const double a[10] = {
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
// Taylor' serie
// Faster
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

#endif
