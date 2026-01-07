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
 * \file math_f32.h
 * \brief Header file with useful mathematical functions for float.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_F32__H
#define JB_MATH_F32__H 1

#define JBM_SIGN_BITS_F32 0x80000000u   ///< sign bits for floats.
#define JBM_ABS_BITS_F32 0x7fffffffu    ///< absolute value bits for floats.
#define JBM_1_BITS_F32 0x3f800000u      ///< 1 bits for floats.
#define K_ERFC_MAX_F32 9.1945494491346722541126284791161797e+00f
///< maximum value for the erfc function for floats.


/**
 * union to work with bits in float numbers.
 */
typedef union
{
  float x;                      ///< floating point.
  uint32_t i;                   ///< bits.
} JBMF32;

///> constants to approximate the exp2 function for floats.
static const float K_EXP2WC_F32[7] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00f,
  6.9314698914837346684917016547140290e-01f,
  2.4023013440956308242676391175775056e-01f,
  5.5481276897966968388537203873531066e-02f,
  9.6838443044560544231354590034380938e-03f,
  1.2388324045355677384055887692919008e-03f,
  2.1892283510486017398767112458558770e-04f
};

///> constants to approximate the expm1 function for floats.
static const float K_EXPM1WC_F32[4] JB_ALIGNED = {
  9.9999999207421606717913482453758280e-01f,
  -4.9999999428977310694962941770187204e-01f,
  8.3332847103276099896972390679450291e-02f,
  -1.3814355363728248005537576815708276e-03f
};

///> constants to approximate the log2 function for floats.
static const float K_LOG2WC_F32[7] JB_ALIGNED = {
  -5.8126019093483959097406847488994764e+00f,
  -2.5085328503498312245162272841324403e+01f,
  1.7285836631840400109438868826415372e+01f,
  1.3612093781006308045464088763808507e+01f,
  1.2862396202641134787157650225428789e+01f,
  1.8190175154391289373999382294511312e+01f,
  2.8284271247461900976033774491163912e+00f
};

///> constants to approximate the sin function for floats.
static const float K_SINWC_F32[4] JB_ALIGNED = {
  9.9999996965723526744097770291936967e-01f,
  -1.6666620015384683518213796696918514e-01f,
  8.3311026871235773338090114171471276e-03f,
  -1.9420289480683700292660589067195280e-04f
};

///> constants to approximate the cos function for floats.
static const float K_COSWC_F32[4] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00f,
  -4.9999881282902269170048324169403646e-01f,
  4.1655426842414539692022145438909779e-02f,
  -1.3585930685125295856906885364365325e-03f
};

///> constants to approximate the tan function for floats.
static const float K_TANWC_F32[4] JB_ALIGNED = {
  9.9999985933511606311402284687984801e-01f,
  -9.5938128322319518556143392564356824e-02f,
  -4.2927341418055735527664144883477659e-01f,
  9.7660842469747178034168931310690206e-03f
};

///> constants to approximate the atan function for floats.
static const float K_ATANWC0_F32[5] JB_ALIGNED = {
  9.9999903925421116993034432608545796e-01f,
  -3.3326999543161982928331926294640292e-01f,
  1.9872213552368483360193832489717778e-01f,
  -1.3163202894059419306147138806729765e-01f,
  6.4075414341760508278348212748644238e-02f
};

///> constants to approximate the atan function for floats.
static const float K_ATANWC1_F32[7] JB_ALIGNED = {
  7.8539816339744830961566084581987570e-01f,
  1.6466183167433133946190411929937300e+00f,
  1.1541669428615717858835930397326275e+00f,
  2.9362408099131156797938535841869004e-01f,
  1.4599202919039647559944876074415694e+00f,
  8.5842465073233548112000791514018263e-01f,
  1.8595564463442378426405375014481240e-01f
};

///> constants to approximate the erf function for floats.
static const float K_ERFWC_F32[6] JB_ALIGNED = {
  1.1283786955787322785383552822487291e+00f,
  -3.7611545986844245635123519453797306e-01f,
  1.1276050635989995712054030014993988e-01f,
  -2.6620399798452970529801484639501365e-02f,
  4.8289810842467084094201565645850194e-03f,
  -5.3153040626864784605842470317016624e-04f
};

///> constants to approximate the erfc function for floats.
static const float K_ERFCWC_F32[8] JB_ALIGNED = {
  7.8641920312765702734759760789729972e-06f,
  -2.5900983748853296588083203014934053e-04f,
  5.6778191042361772203996927852363952e-01f,
  1.7186322997519315173086187937209682e+00f,
  2.2871101150702461568924875202130306e+00f,
  3.0954889481375803718539754306506051e+00f,
  4.3166224756116566856837227415104566e+00f,
  2.2835126241068129527775558422360409e+00f
};

/**
 * Function to calculate the double of a float number.
 *
 * \return float double.
 */
static inline float
jbm_dbl_f32 (const float x)     ///< float number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a float number.
 *
 * \return float square.
 */
static inline float
jbm_sqr_f32 (const float x)     ///< float number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the sign of a float number.
 *
 * \return float sign.
 */
static inline float
jbm_sign_f32 (const float x)    ///< float number.
{
  JBMF32 y;
  y.x = x;
  y.i &= JBM_SIGN_BITS_F32;
  y.i |= JBM_1_BITS_F32;
  return y.x;
}

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
  y.i &= JBM_ABS_BITS_F32;
  return y.x;
}

/**
 * Function to copy the sign of a float number to another float number.
 *
 * \return float number with magnitud of 1st number and sign of 2nd number.
 */
static inline float
jbm_copysign_f32 (const float x,    ///< float number to preserve magnitude.
                  const float y)    ///< float number to preserve sign.
{
  JBMF32 ax, sy;
  ax.x = jbm_abs_f32 (x);
  sy.x = y;
  ax.i |= sy.i & JBM_SIGN_BITS_F32;
  return ax.x;
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
jbm_mod_f32 (const float x,    ///< dividend (float).
             const float d)    ///< divisor (float).
{
  return x - d * floorf (x / d);
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
  y.i &= 0x7f800000u;
  if (y.i == 0x7f800000u)
    {
      *e = 0;
      return x;
    }
  if (!y.i)
    {
      y.x = x;
      y.i &= 0x007fffffu;
      if (!y.i)
        {
          *e = 0;
          return x;
        }
      y.i = 0x00400000u;
      z.x = x / y.x;
      z.i &= 0x7f800000u;
      *e = (int) (z.i >> 23u) - 253;
      y.x *= z.x;
    }
  else
    *e = (int) (y.i >> 23u) - 126;
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
    x.i = 0x00400000u >> (-e - 127);
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
 * Function to calculate the well conditionated function exp2(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_exp2wc_f32 (const float x)
                ///< float number \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_polynomial_6_f32 (x, K_EXP2WC_F32);
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
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2].
 *
 * \return function value (float).
 */
static inline float
jbm_expm1wc_f32 (const float x)
                 ///< float number \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  return x * a1 / (1.f + x * (b1 + x * (b2 + x * x * b4)));
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
  return jbm_rational_6_3_f32 (x, K_LOG2WC_F32);
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
  return jbm_copysign_f32 (jbm_pow_f32 (jbm_abs_f32 (x), 1.f / 3.f), x);
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float).
 */
static inline float
jbm_sinwc_f32 (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_polynomial_3_f32 (x * x, K_SINWC_F32);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float).
 */
static inline float
jbm_coswc_f32 (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_polynomial_3_f32 (x * x, K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float).
 */
static inline float
jbm_tanwc_f32 (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_rational_3_1_f32 (x * x, K_TANWC_F32);
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
  *s = jbm_sinwc_f32 (x);
  *c = jbm_coswc_f32 (x);
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
  int q;
  y = x * 1.f / M_PI_2f;
  q = (int) nearbyintf (y);
  y = x - (float) q * M_PI_2f;
  q &= 3;
  y = (q & 1) ? jbm_coswc_f32 (y) : jbm_sinwc_f32 (y);
  return (q & 2) ? -y : y;
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
  int q;
  y = x * 1.f / M_PI_2f;
  q = (int) nearbyintf (y);
  y = x - (float) q * M_PI_2f;
  q &= 3;
  y = (q & 1) ? jbm_sinwc_f32 (y) : jbm_coswc_f32 (y);
  return ((q + 1) & 2) ? -y : y;
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
  float y, sr, cr;
  int q;
  y = x * 1.f / M_PI_2f;
  q = (int) (y + jbm_copysign_f32 (0.5f, x));
  y = x - (float) q * M_PI_2f;
  q &= 3;
  jbm_sincoswc_f32 (y, &sr, &cr);
  switch (q)
    {
    case 0:
      *s = sr;
      *c = cr;
      break;
    case 1:
      *s = cr;
      *c = -sr;
      break;
    case 2:
      *s = -sr;
      *c = -cr;
      break;
    default:
      *s = -cr;
      *c = sr;
    }
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
  float y;
  int q;
  y = x * 1.f / M_PI_2f;
  q = (int) nearbyintf (y);
  y = jbm_tanwc_f32 (x - (float) q * M_PI_2f);
  return (q & 1) ? -1.f / y : y;
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2].
 *
 * \return function value (float).
 */
static inline float
jbm_atanwc0_f32 (const float x)
                 ///< float number \f$\in\left[0,\frac12\right]\f$.
{
  return x * jbm_polynomial_4_f32 (x * x, K_ATANWC0_F32);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2].
 *
 * \return function value (float).
 */
static inline float
jbm_atanwc1_f32 (const float x)
                 ///< float number \f$\in\left[\frac12,1\right]\f$.
{
  return jbm_rational_6_3_f32 (x - 1.f, K_ATANWC1_F32);
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
  return jbm_copysign_f32 (f, x);
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
    f += jbm_copysign_f32 (M_PIf, y);
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
 * [-1,1].
 *
 * \return function value (float).
 */
static inline float
jbm_erfwc_f32 (const float x)
               ///< float number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_polynomial_5_f32 (x * x, K_ERFWC_F32);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_erfcwc_f32 (const float x)
                ///< float number \f$\in\left[1,\infty\right]\f$.
{
  if (x > K_ERFC_MAX_F32)
    return 0.f;
  return jbm_rational_7_4_f32 (1.f / x, K_ERFCWC_F32) * x / jbm_exp_f32 (x * x);
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
    return jbm_copysign_f32 (1.f - jbm_erfcwc_f32 (ax), x);
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
  if (x > 1.f)
    return jbm_erfcwc_f32 (x);
  if (x < -1.f)
    return 2.f - jbm_erfcwc_f32 (-x);
  return 1.f - jbm_erfwc_f32 (x);
}

#if !defined(__SSE4_2__) && !defined(__ARM_NEON__) && !defined(__riscv_vector)

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_add_f32 (float *xr,   ///< result float array.
                   const float *x1,     ///< 1st addend float array.
                   const float *x2,     ///< 1st addend float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  unsigned int i;
  for (i = 0; i < n; ++i)
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
  float k;
  unsigned int i;
  k = xx[0];
  for (i = 0; ++i < n;)
    k = fmaxf (k, xx[i]);
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
  float k;
  unsigned int i;
  k = xx[0];
  for (i = 0; ++i < n;)
    k = fminf (k, xx[i]);
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
  float kmax, kmin;
  unsigned int i;
  kmax = kmin = xx[0];
  for (i = 0; ++i < n;)
    kmax = fmaxf (kmax, xx[i]), kmin = fminf (kmin, xx[i]);
  *max = kmax, *min = kmin;
}

#endif

#endif
