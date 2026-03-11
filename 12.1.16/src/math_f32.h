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
 * \file math_f32.h
 * \brief Header file with useful mathematical functions for float.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_F32__H
#define JB_MATH_F32__H 1

#define JBM_F32_BIAS 126u       ///< bias for doubles.
#define JBM_F32_BITS_1 0x3f800000u      ///< 1 bits for floats.
#define JBM_F32_BITS_ABS 0x7fffffffu    ///< absolute value bits for floats.
#define JBM_F32_BITS_EXPONENT 0x7f800000u       ///< exponent bits for floats.
#define JBM_F32_BITS_MANTISSA 0x007fffffu       ///< mantissa bits for floats.
#define JBM_F32_BITS_SIGN 0x80000000u   ///< sign bits for floats.
#define JBM_F32_CBRT2 1.2599210498948731647672106072782284f
///< cbrt(2) for floats.
#define JBM_F32_CBRT4 1.5874010519681994747517056392723083f
///< cbrt(4) for floats.
#define JBM_SQRT_FLT_MIN 1.0842021724855044340074528008699417e-19
///< root square of standard FLT_MIN.
#define JBM_SQRT_FLT_EPSILON 3.4526698300124390839884978618400830e-04f
///< root square of standard FLT_EPSILON.
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

///> constants to approximate the cbrt function for floats.
static const float K_CBRTWC_F32[6] JB_ALIGNED = {
  2.8161682735545150103123149112801870e-01f,
  4.2177555825677256686056577661107689e+00f,
  4.7513737599056927748717867424267637e+00f,
  2.7522639784879759608409561827672440e-01f,
  5.6811029731502418980950973715327693e+00f,
  2.8448695945274256424976742464095058e+00f
};

///> constants to approximate the exp2 function for floats.
static const float K_EXP2WC_F32[6] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00f,
  6.9315173882998826643407937907770919e-01f,
  2.4015927146338278980085004236690347e-01f,
  5.5818675964655106403593087638801433e-02f,
  8.9909950919886886681983925206704175e-03f,
  1.8793186499851486932790983959155567e-03f
};

///> constants to approximate the expm1 function for floats.
static const float K_EXPM1WC_F32[4] JB_ALIGNED = {
  9.9999999207421606717913482453758280e-01f,
  -4.9999999428977310694962941770187204e-01f,
  8.3332847103276099896972390679450291e-02f,
  -1.3814355363728248005537576815708276e-03f
};

///> constants to approximate the log2 function for floats.
static const float K_LOG2WC_F32[6] JB_ALIGNED = {
  1.4426951529555164969605209744468021e+00f,
  1.4426951529555164969605209743644314e+00f,
  2.6312807435912334781338175103472592e-01f,
  1.4999999999999999999999999999429020e+00f,
  5.9905808071036012299119764734054704e-01f,
  4.9529040355180061495598823689372438e-02f
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
static const float K_ATANWC_F32[5] JB_ALIGNED = {
  9.9999344141922174695617361891716596e-01f,
  6.4385756541743753577375369722421555e-01f,
  3.8510709957453959724953159191991714e-02f,
  9.7706766891101603756449801731535272e-01f,
  1.6498179745978740793920160451925031e-01f
};

///> constants to approximate the erf function for floats.
static const float K_ERFWC_F32[6] JB_ALIGNED = {
  1.1283784919510739327628580200615436e+00f,
  -3.7611318100522544117602567901875638e-01f,
  1.1275154994006366753249155585410039e-01f,
  -2.6604377545274638479638916888391479e-02f,
  4.8156337717701657220587137152241101e-03f,
  -5.2732416269281702052305864111100410e-04f
};

///> constants to approximate the erfc function for floats.
static const float K_ERFCWC_F32[8] JB_ALIGNED = {
  7.7690584241365709132585914534206076e-06f,
  -2.5632969841208072919442336440351380e-04f,
  5.6775139264722068298456180902877633e-01f,
  1.7169762668275923940430913021669125e+00f,
  2.2828798090490570652996329155227896e+00f,
  3.0922244695518132415406880925535143e+00f,
  4.3103157478118860726883750838543111e+00f,
  2.2792519808931957401789064037092762e+00f
};

///> 1st constant to calculate integrals by the Gauss method (float).
static const float JBM_INTEGRAL_GAUSS_A_F32[JBM_INTEGRAL_GAUSS_N] = {
#if JBM_INTEGRAL_GAUSS_N == 1
  2.f
#elif JBM_INTEGRAL_GAUSS_N == 2
  8.f / 9.f,
  5.f / 9.f
#elif JBM_INTEGRAL_GAUSS_N == 3
  128.f / 225.f,
  4.7862867049936646804129151483563819e-1f,
  2.3692688505618908751426404071991736e-1f
#elif JBM_INTEGRAL_GAUSS_N == 4
  4.1795918367346938775510204081632653e-1f,
  3.8183005050511894495036977548897513e-1f,
  2.7970539148927666790146777142377958e-1f,
  1.2948496616886969327061143267908202e-1f
#endif
};

///> 2nd constant to calculate integrals by the Gauss method (float).
static const float JBM_INTEGRAL_GAUSS_B_F32[JBM_INTEGRAL_GAUSS_N] = {
#if JBM_INTEGRAL_GAUSS_N == 1
  0.f
#elif JBM_INTEGRAL_GAUSS_N == 2
  0.f,
  7.7459666924148340427791481488384306e-1f
#elif JBM_INTEGRAL_GAUSS_N == 3
  0.f,
  5.3846931010568309103631442070020880e-1f,
  9.0617984593866399279762687829939297e-1f
#elif JBM_INTEGRAL_GAUSS_N == 4
  0.f,
  4.0584515137739716690660641207696146e-1f,
  7.4153118559939443986386477328078841e-1f,
  9.4910791234275852452618968404785126e-1f
#endif
};

/**
 * Function to calculate the double of a float number.
 *
 * \return float double.
 */
static inline float
jbm_f32_dbl (const float x)     ///< float number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a float number.
 *
 * \return float square.
 */
static inline float
jbm_f32_sqr (const float x)     ///< float number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the opposite of a float number.
 *
 * \return float opposite.
 */
static inline float
jbm_f32_opposite (const float x)        ///< float number.
{
  return -x;
}

/**
 * Function to calculate the reciprocal of a float number.
 *
 * \return float reciprocal.
 */
static inline float
jbm_f32_reciprocal (const float x)      ///< float number.
{
  return 1.f / x;
}

/**
 * Function to calculate the sign of a float number.
 *
 * \return float sign.
 */
static inline float
jbm_f32_sign (const float x)    ///< float number.
{
  JBMF32 y;
  y.x = x;
  y.i &= JBM_F32_BITS_SIGN;
  y.i |= JBM_F32_BITS_1;
  return y.x;
}

/**
 * Function to calculate the abs function (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_abs (const float x)     ///< float number.
{
  JBMF32 y;
  y.x = x;
  y.i &= JBM_F32_BITS_ABS;
  return y.x;
}

/**
 * Function to copy the sign of a float number to another float number.
 *
 * \return float number with magnitud of 1st number and sign of 2nd number.
 */
static inline float
jbm_f32_copysign (const float x,        ///< float number to preserve magnitude.
                  const float y)        ///< float number to preserve sign.
{
  JBMF32 ax, sy;
  ax.x = jbm_f32_abs (x);
  sy.x = y;
  ax.i |= sy.i & JBM_F32_BITS_SIGN;
  return ax.x;
}

/**
 * Function to calculate the hypot function (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_hypot (const float x,   ///< 1st float number.
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
jbm_f32_mod (const float x,     ///< dividend (float).
             const float d)     ///< divisor (float).
{
  float r;
  r = floorf (x / d);
  return (jbm_f32_abs (r) > 1.f / FLT_EPSILON) ? 0.5f * d : x - d * r;
}

/**
 * Function to implement the standard frexp function (float).
 *
 * \return normalize fraction value in [1/2,1) (float).
 */
static inline float
jbm_f32_frexp (const float x,   ///< float number.
               int *e)          ///< pointer to the extracted exponent.
{
  JBMF32 y;
  uint32_t exp;
  y.x = x;
  exp = y.i & 0x7fffffffu;
  // check NaN or 0
  if (exp >= 0x7f800000u || !exp)
    {
      *e = 0;
      return x;
    }
  // extract exponent
  exp = y.i >> 23u;
  // subnormal
  if (!exp)
    {
      y.x *= 0x1p23f;
      exp = (y.i >> 23u) - 23u;
    }
  // exponent
  *e = (int) (exp - JBM_F32_BIAS);
  // mantissa in [0.5,1)
  y.i = (JBM_F32_BIAS << 23u) | (y.i & 0x807fffffu);
  return y.x;
}

/**
 * Function to calculate the function \f$2^n\f$ with n an integer number (int).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_exp2n (int e)           ///< exponent number (int).
{
  JBMF32 x;
  if (e > 127)
    return INFINITY;
  if (e < -149)
    return 0.f;
  if (e > -127)
    x.i = (127 + e) << 23;
  else
    x.i = 1u << (e + 149);
  return x.x;
}

/**
 * Function to implement the standard ldexp function (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_ldexp (const float x,   ///< float number.
               int e)           ///< exponent number (int).
{
  return x * jbm_f32_exp2n (e);
}

/**
 * Function to calculate a 1st order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_1 (const float x,    ///< float value.
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
jbm_f32_polynomial_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_1 (x, p + 1);
}

/**
 * Function to calculate a 3rd order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_2 (x, p + 1);
}

/**
 * Function to calculate a 4th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_4 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_3 (x, p + 1);
}

/**
 * Function to calculate a 5th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_5 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_4 (x, p + 1);
}

/**
 * Function to calculate a 6th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_6 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_5 (x, p + 1);
}

/**
 * Function to calculate a 7th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_7 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_6 (x, p + 1);
}

/**
 * Function to calculate a 8th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_8 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_7 (x, p + 1);
}

/**
 * Function to calculate a 9th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_9 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_8 (x, p + 1);
}

/**
 * Function to calculate a 10th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_10 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_9 (x, p + 1);
}

/**
 * Function to calculate a 11th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_11 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_10 (x, p + 1);
}

/**
 * Function to calculate a 12th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_12 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_11 (x, p + 1);
}

/**
 * Function to calculate a 13th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_13 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_12 (x, p + 1);
}

/**
 * Function to calculate a 14th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_14 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_13 (x, p + 1);
}

/**
 * Function to calculate a 15th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_15 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_14 (x, p + 1);
}

/**
 * Function to calculate a 16th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_16 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_15 (x, p + 1);
}

/**
 * Function to calculate a 17th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_17 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_16 (x, p + 1);
}

/**
 * Function to calculate a 18th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_18 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_17 (x, p + 1);
}

/**
 * Function to calculate a 19th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_19 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_18 (x, p + 1);
}

/**
 * Function to calculate a 20th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_20 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_19 (x, p + 1);
}

/**
 * Function to calculate a 21th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_21 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_20 (x, p + 1);
}

/**
 * Function to calculate a 22th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_22 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_21 (x, p + 1);
}

/**
 * Function to calculate a 23th order polynomial (float).
 *
 * \return polynomial value (float).
 */
static inline float
jbm_f32_polynomial_23 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_22 (x, p + 1);
}

/**
 * Function to calculate a 24th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_f32_polynomial_24 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_23 (x, p + 1);
}

/**
 * Function to calculate a 25th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_f32_polynomial_25 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_24 (x, p + 1);
}

/**
 * Function to calculate a 26th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_f32_polynomial_26 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_25 (x, p + 1);
}

/**
 * Function to calculate a 27th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_f32_polynomial_27 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_26 (x, p + 1);
}

/**
 * Function to calculate a 28th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_f32_polynomial_28 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_27 (x, p + 1);
}

/**
 * Function to calculate a 29th order polynomial (float).
 *
 * \return polynomial value.
 */
static inline float
jbm_f32_polynomial_29 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] + x * jbm_f32_polynomial_28 (x, p + 1);
}

/**
 * Function to calculate a 1st order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_1_0 (const float x,    ///< float value.
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
jbm_f32_rational_2_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_1 (x, p + 1));
}

/**
 * Function to calculate a 2nd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_2_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_1 (x, p) / (1.f + x * p[2]);
}

/**
 * Function to calculate a 3rd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_3_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_2 (x, p + 1));
}

/**
 * Function to calculate a 3rd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_3_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 2));
}

/**
 * Function to calculate a 3rd order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_3_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_2 (x, p) / (1.f + x * p[3]);
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_4_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_3 (x, p + 1));
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_4_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 2));
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_4_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 3));
}

/**
 * Function to calculate a 4th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_4_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_3 (x, p) / (1.f + x * p[4]);
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_5_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_4 (x, p + 1));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_5_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 2));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_5_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 3));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_5_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 4));
}

/**
 * Function to calculate a 5th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_5_4 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_4 (x, p) / (1.f + x * p[5]);
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_6_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_5 (x, p + 1));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_6_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 2));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_6_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 3));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_6_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 4));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_6_4 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 5));
}

/**
 * Function to calculate a 6th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_6_5 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_5 (x, p) / (1.f + x * p[6]);
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_6 (x, p + 1));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 2));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 3));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 4));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_4 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 5));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_5 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 6));
}

/**
 * Function to calculate a 7th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_7_6 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_6 (x, p) / (1.f + x * p[7]);
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_7 (x, p + 1));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 2));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 3));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 4));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_4 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 5));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_5 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 6));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_6 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 7));
}

/**
 * Function to calculate a 8th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_8_7 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_7 (x, p) / (1.f + x * p[8]);
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_0 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_8 (x, p + 1));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_1 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 2));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_2 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 3));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_3 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 4));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_4 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 5));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_5 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 6));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_6 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 7));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_7 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 8));
}

/**
 * Function to calculate a 9th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_9_8 (const float x,    ///< float value.
                      const float *p)   ///< array of coefficients (float).
{
  return jbm_f32_polynomial_8 (x, p) / (1.f + x * p[9]);
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_9 (x, p + 1));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 2));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 3));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 4));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 5));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 6));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 7));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 8));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 9));
}

/**
 * Function to calculate a 10th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_10_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return jbm_f32_polynomial_9 (x, p) / (1.f + x * p[10]);
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_10 (x, p + 1));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 2));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 3));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 4));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 5));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 6));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 7));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 8));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 9));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 10));
}

/**
 * Function to calculate a 11th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_11_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_10 (x, p) / (1.f + x * p[11]);
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_11 (x, p + 1));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 2));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 3));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 4));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 5));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 6));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 7));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 8));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 9));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 10));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 11));
}

/**
 * Function to calculate a 12th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_12_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_11 (x, p) / (1.f + x * p[12]);
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_12 (x, p + 1));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 2));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 3));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 4));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 5));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 6));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 7));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 8));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 9));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 10));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 11));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 12));
}

/**
 * Function to calculate a 13th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_13_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_12 (x, p) / (1.f + x * p[13]);
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_13 (x, p + 1));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 2));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 3));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 4));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 5));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 6));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 7));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 8));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 9));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 10));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 11));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 12));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 13));
}

/**
 * Function to calculate a 14th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_14_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_13 (x, p) / (1.f + x * p[14]);
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_14 (x, p + 1));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 2));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 3));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 4));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 5));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 6));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 7));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 8));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 9));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 10));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 11));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 12));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 13));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 14));
}

/**
 * Function to calculate a 15th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_15_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_14 (x, p) / (1.f + x * p[15]);
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_15 (x, p + 1));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_14 (x, p + 2));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 3));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 4));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 5));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 6));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 7));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 8));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 9));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 10));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 11));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 12));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 13));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 14));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_14 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 15));
}

/**
 * Function to calculate a 16th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_16_15 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_15 (x, p) / (1.f + x * p[16]);
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_16 (x, p + 1));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_15 (x, p + 2));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_14 (x, p + 3));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 4));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 5));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 6));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 7));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 8));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 9));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 10));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 11));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 12));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 13));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 14));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_14 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 15));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_15 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_15 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 16));
}

/**
 * Function to calculate a 17th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_17_16 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_16 (x, p) / (1.f + x * p[17]);
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_17 (x, p + 1));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_16 (x, p + 2));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_15 (x, p + 3));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_14 (x, p + 4));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 5));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 6));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 7));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 8));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 9));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 10));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 11));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 12));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 13));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 14));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_14 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 15));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_15 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_15 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 16));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_16 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_16 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 17));
}

/**
 * Function to calculate a 18th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_18_17 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_17 (x, p) / (1.f + x * p[18]);
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_18 (x, p + 1));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_17 (x, p + 2));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_16 (x, p + 3));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_15 (x, p + 4));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_14 (x, p + 5));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 6));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 7));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 8));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 9));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 10));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 11));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 12));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 13));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 14));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_14 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 15));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_15 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_15 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 16));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_16 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_16 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 17));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_17 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_17 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 18));
}

/**
 * Function to calculate a 19th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_19_18 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_18 (x, p) / (1.f + x * p[19]);
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_19 (x, p + 1));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_18 (x, p + 2));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_17 (x, p + 3));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_16 (x, p + 4));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_15 (x, p + 5));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_14 (x, p + 6));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 7));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 8));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 9));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 10));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 11));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 12));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 13));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 14));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_14 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 15));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_15 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_15 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 16));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_16 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_16 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 17));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_17 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_17 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 18));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_18 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_18 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 19));
}

/**
 * Function to calculate a 20th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_20_19 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_19 (x, p) / (1.f + x * p[20]);
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_0 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return p[0] / (1.f + x * jbm_f32_polynomial_20 (x, p + 1));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_1 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_1 (x, p) / (1.f + x * jbm_f32_polynomial_19 (x, p + 2));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_2 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_2 (x, p) / (1.f + x * jbm_f32_polynomial_18 (x, p + 3));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_3 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_3 (x, p) / (1.f + x * jbm_f32_polynomial_17 (x, p + 4));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_4 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_4 (x, p) / (1.f + x * jbm_f32_polynomial_16 (x, p + 5));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_5 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_5 (x, p) / (1.f + x * jbm_f32_polynomial_15 (x, p + 6));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_6 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_6 (x, p) / (1.f + x * jbm_f32_polynomial_14 (x, p + 7));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_7 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_7 (x, p) / (1.f + x * jbm_f32_polynomial_13 (x, p + 8));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_8 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_8 (x, p) / (1.f + x * jbm_f32_polynomial_12 (x, p + 9));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_9 (const float x,   ///< float value.
                       const float *p)  ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_9 (x, p) / (1.f + x * jbm_f32_polynomial_11 (x, p + 10));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_10 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_10 (x,
                           p) / (1.f + x * jbm_f32_polynomial_10 (x, p + 11));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_11 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_11 (x, p) / (1.f + x * jbm_f32_polynomial_9 (x, p + 12));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_12 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_12 (x, p) / (1.f + x * jbm_f32_polynomial_8 (x, p + 13));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_13 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_13 (x, p) / (1.f + x * jbm_f32_polynomial_7 (x, p + 14));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_14 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_14 (x, p) / (1.f + x * jbm_f32_polynomial_6 (x, p + 15));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_15 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_15 (x, p) / (1.f + x * jbm_f32_polynomial_5 (x, p + 16));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_16 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_16 (x, p) / (1.f + x * jbm_f32_polynomial_4 (x, p + 17));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_17 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_17 (x, p) / (1.f + x * jbm_f32_polynomial_3 (x, p + 18));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_18 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_18 (x, p) / (1.f + x * jbm_f32_polynomial_2 (x, p + 19));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_19 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return
    jbm_f32_polynomial_19 (x, p) / (1.f + x * jbm_f32_polynomial_1 (x, p + 20));
}

/**
 * Function to calculate a 21th order rational (float).
 *
 * \return rational value (float).
 */
static inline float
jbm_f32_rational_21_20 (const float x,  ///< float value.
                        const float *p) ///< array of coefficients (float).
{
  return jbm_f32_polynomial_20 (x, p) / (1.f + x * p[21]);
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_cbrtwc (const float x)
                ///< float number \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_f32_rational_5_3 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_f32_cbrtwc and
 * jbm_f32_ldexp functions (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_cbrt (const float x)    ///< float number.
{
  float m;
  int e, e3, r;
  m = jbm_f32_frexp (jbm_f32_abs (x), &e);
  e3 = e / 3;
  r = e - 3 * e3;
  e = r >> 31;
  r += e & 3;
  e3 -= e & 1;
  m = jbm_f32_ldexp (jbm_f32_cbrtwc (m), e3);
  if (r & 1)
    m *= JBM_F32_CBRT2;
  if (r & 2)
    m *= JBM_F32_CBRT4;
  return jbm_f32_copysign (m, x);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_exp2wc (const float x)
                ///< float number \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_f32_polynomial_5 (x, K_EXP2WC_F32);
}

/**
 * Function to calculate the function exp2(x) using the jbm_f32_expwc and
 * jbm_f32_exp2n functions (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_exp2 (const float x)    ///< float number.
{
  float y, f;
  if (x >= FLT_MAX_EXP)
    return INFINITY;
  y = floorf (x);
  f = x - y;
  y = jbm_f32_exp2n ((int) y);
  return y * jbm_f32_exp2wc (f);
}

/**
 * Function to calculate the function exp(x) using the jbm_f32_exp2 function
 * (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_exp (const float x)     ///< float number.
{
  return jbm_f32_exp2 (x * M_LOG2Ef);
}

/**
 * Function to calculate the function exp10(x) using the jbm_f32_exp2 function
 * (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_exp10 (const float x)   ///< float number.
{
  return jbm_f32_exp2 (x * M_LN10f / M_LN2f);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2].
 *
 * \return function value (float).
 */
static inline float
jbm_f32_expm1wc (const float x)
                 ///< float number \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  const float a1 = K_EXPM1WC_F32[0];
  const float b1 = K_EXPM1WC_F32[1];
  const float b2 = K_EXPM1WC_F32[2];
  const float b4 = K_EXPM1WC_F32[3];
  return x * a1 / (1.f + x * (b1 + x * (b2 + x * x * b4)));
}

/**
 * Function to calculate the function expm1(x) using the jbm_f32_expm1wc and
 * jbm_f32_exp functions.
 *
 * \return function value (float).
 */
static inline float
jbm_f32_expm1 (const float x)   ///< float number.
{
  if (jbm_f32_abs (x) < M_LN2f / 2.f)
    return jbm_f32_expm1wc (x);
  return jbm_f32_exp (x) - 1.f;
}

/**
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_log2wc (const float x)  ///< float number.
{
  return x * jbm_f32_rational_5_2 (x, K_LOG2WC_F32);
}

/**
 * Function to calculate the function log2(x) using jbm_log2wc0_f32,
 * jbm_f32_log2wc and jbm_f32_frexp (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_log2 (const float x)    ///< float number.
{
  float y;
  int e, m;
  if (x < 0.f)
    return NAN;
  if (x == 0.f)
    return -INFINITY;
  if (!finitef (x))
    return x;
  y = jbm_f32_frexp (x, &e);
  m = y < M_SQRT1_2f;
  y += (float) m *y;
  e -= m;
  return jbm_f32_log2wc (y - 1.f) + (float) e;
}

/**
 * Function to calculate the function log(x) using jbm_f32_log2 (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_log (const float x)     ///< float number.
{
  return jbm_f32_log2 (x) * M_LN2f;
}

/**
 * Function to calculate the function log10(x) using jbm_f32_log2 (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_log10 (const float x)   ///< float number.
{
  return jbm_f32_log2 (x) * M_LN2f / M_LN10f;
}

/**
 * Function to calculate the function x^e with e an integer number.
 *
 * \return function value (float).
 */
static inline float
jbm_f32_pown (const float x,    ///< float number.
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
 * Function to calculate the function pow using the jbm_f32_exp2 and
 * jbm_f32_log2 functions.
 *
 * \return function value (float).
 */
static inline float
jbm_f32_pow (const float x,     ///< float number.
             const float e)     ///< exponent (float).
{
  return jbm_f32_exp2 (e * jbm_f32_log2 (x));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float).
 */
static inline float
jbm_f32_sinwc (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_f32_polynomial_3 (x * x, K_SINWC_F32);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float).
 */
static inline float
jbm_f32_coswc (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_f32_polynomial_3 (x * x, K_COSWC_F32);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (float).
 */
static inline float
jbm_f32_tanwc (const float x)
               ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_f32_rational_3_1 (x * x, K_TANWC_F32);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_f32_sinwc approximation (float).
 */
static inline void
jbm_f32_sincoswc (const float x,
                  ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  float *s,     ///< pointer to the sin function value (float).
                  float *c)     ///< pointer to the cos function value (float).
{
  *s = jbm_f32_sinwc (x);
  *c = jbm_f32_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (float).
 *
 * \return reduced value (float).
 */
static inline float
jbm_f32_trig (const float x,    ///< float number.
              int32_t *q)       ///< quadrant.
{
  *q = (int32_t) nearbyintf (x * 1.f / M_PI_2f);
  return x - ((float) *q) * M_PI_2f;
}

/**
 * Function to calculate the function sin(x) from jbm_f32_sinwc and
 * jbm_f32_coswc approximations (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_sin (const float x)     ///< float number.
{
  float y;
  int32_t q;
  y = jbm_f32_trig (x, &q);
  y = (q & 1) ? jbm_f32_coswc (y) : jbm_f32_sinwc (y);
  return (q & 2) ? -y : y;
}

/**
 * Function to calculate the function cos(x) from jbm_f32_sinwc and
 * jbm_f32_coswc approximations (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_cos (const float x)     ///< float number.
{
  float y;
  int32_t q;
  y = jbm_f32_trig (x, &q);
  q &= 3;
  y = (q & 1) ? jbm_f32_sinwc (y) : jbm_f32_coswc (y);
  return ((q + 1) & 2) ? -y : y;
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_f32_sincoswc
 * approximation (float).
 */
static inline void
jbm_f32_sincos (const float x,
                ///< float number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                float *s,       ///< pointer to the sin function value (float).
                float *c)       ///< pointer to the cos function value (float).
{
  float y, sr, cr;
  int32_t q;
  y = jbm_f32_trig (x, &q);
  jbm_f32_sincoswc (y, &sr, &cr);
  switch (q & 3)
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
 * Function to calculate the function tan(x) from jbm_f32_sincos function
 * (float).
 *
 * \return function value (float).
 */
static inline float
jbm_f32_tan (const float x)     ///< float number.
{
  float y;
  int32_t q;
  y = jbm_f32_tanwc (jbm_f32_trig (x, &q));
  return (q & 1) ? -1.f / y : y;
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1,1].
 *
 * \return function value (float).
 */
static inline float
jbm_f32_atanwc (const float x)
                ///< float number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_f32_rational_4_2 (x * x, K_ATANWC_F32);
}

/**
 * Function to calculate the function atan(x) using the jbm_f32_atanwc functions
 * (float).
 *
 * \return function value (in [-pi/2,pi/2]) (float).
 */
static inline float
jbm_f32_atan (const float x)    ///< float number.
{
  float f, ax;
  ax = jbm_f32_abs (x);
  if (ax > 1.f)
    f = M_PI_2f - jbm_f32_atanwc (1.f / ax);
  else
    f = jbm_f32_atanwc (ax);
  return jbm_f32_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_f32_atan
 * function (float).
 *
 * \return function value (in [-pi,pi]) (float).
 */
static inline float
jbm_f32_atan2 (const float y,   ///< float y component.
               const float x)   ///< float x component.
{
  float f;
  f = jbm_f32_atan (y / x);
  if (x < 0.f)
    f += jbm_f32_copysign (M_PIf, y);
  return f;
}

/**
 * Function to calculate the function asin(x) using the jbm_f32_atan function
 * (float).
 *
 * \return function value (in [-pi/2,pi/2]) (float).
 */
static inline float
jbm_f32_asin (const float x)    ///< float number.
{
  return jbm_f32_atan (x / sqrtf (1.f - x * x));
}

/**
 * Function to calculate the function acos(x) using the jbm_f32_atan function
 * (float).
 *
 * \return function value (in [0,pi]) (float).
 */
static inline float
jbm_f32_acos (const float x)    ///< float number.
{
  float f;
  f = jbm_f32_atan (sqrtf (1.f - x * x) / x);
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
jbm_f32_sinh (const float x)    ///< float number.
{
  float f;
  f = jbm_f32_exp (x);
  return 0.5f * (f - 1.f / f);
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_f32_cosh (const float x)    ///< float number.
{
  float f;
  f = jbm_f32_exp (x);
  return 0.5f * (f + 1.f / f);
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_f32_tanh (const float x)    ///< float number.
{
  float f, fi;
  if (x > JBM_FLT_MAX_E_EXP)
    return 1.f;
  if (x < -JBM_FLT_MAX_E_EXP)
    return -1.f;
  f = jbm_f32_exp (x);
  fi = 1.f / f;
  return (f - fi) / (f + fi);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_f32_asinh (const float x)   ///< float number.
{
  return jbm_f32_log (x + sqrtf (x * x + 1.f));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_f32_acosh (const float x)   ///< float number.
{
  return jbm_f32_log (x + sqrtf (x * x - 1.f));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (float).
 */
static inline float
jbm_f32_atanh (const float x)   ///< float number.
{
  return 0.5f * jbm_f32_log ((1.f + x) / (1.f - x));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1].
 *
 * \return function value (float).
 */
static inline float
jbm_f32_erfwc (const float x)
               ///< float number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_f32_polynomial_5 (x * x, K_ERFWC_F32);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$.
 *
 * \return function value (float).
 */
static inline float
jbm_f32_erfcwc (const float x)
                ///< float number \f$\in\left[1,\infty\right]\f$.
{
  if (x > K_ERFC_MAX_F32)
    return 0.f;
  return jbm_f32_rational_7_4 (1.f / x, K_ERFCWC_F32) * x / jbm_f32_exp (x * x);
}

/**
 * Function to calculate the function erf(x) using jbm_f32_erfwc and
 * jbm_f32_erfcwc
 *
 * \return function value (float).
 */
static inline float
jbm_f32_erf (const float x)     ///< float number.
{
  float ax;
  ax = jbm_f32_abs (x);
  if (ax > 1.f)
    return jbm_f32_copysign (1.f - jbm_f32_erfcwc (ax), x);
  return jbm_f32_erfwc (x);
}

/**
 * Function to calculate the function erfc(x) using jbm_f32_erfwc and
 * jbm_f32_erfcwc.
 *
 * \return function value (float).
 */
static inline float
jbm_f32_erfc (const float x)    ///< float number.
{
  if (x > 1.f)
    return jbm_f32_erfcwc (x);
  if (x < -1.f)
    return 2.f - jbm_f32_erfcwc (-x);
  return 1.f - jbm_f32_erfwc (x);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (float).
 *
 * \return integral value (float).
 */
static inline float
jbm_f32_integral (float (*f) (float),
                  ///< pointer to the function to integrate.
                  const float x1,       ///< left limit of the interval.
                  const float x2)       ///< right limit of the interval.
{
  float k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  float k2;
  unsigned int i;
#endif
  dx = 0.5f * (x2 - x1);
  x = 0.5f * (x1 + x2);
  k = JBM_INTEGRAL_GAUSS_A_F32[0] * f (x);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = JBM_INTEGRAL_GAUSS_B_F32[i] * dx;
      k += JBM_INTEGRAL_GAUSS_A_F32[i] * (f (x - k2) + f (x + k2));
    }
#endif
  return k * dx;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * float.
 *
 * \return interval number.
 */
static inline unsigned int
jbm_array_f32_search (const float *xx,  ///< float array.
                      const float x,    ///< number to search.
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
 * array of float numbers.
 * \return interval number, -1 if x<fa[0] or n-1 if x>fa[n-1].
 */
static inline int
jbm_array_f32_search_extended (const float *xx, ///< float array.
                               const float x,   ///< number to search.
                               const unsigned int n)
                               ///< number of array elements.
{
  unsigned int n1;
  if (x < xx[0])
    return -1;
  n1 = n - 1;
  if (x >= xx[n1])
    return (int) n1;
  return (int) jbm_array_f32_search (xx, x, n);
}

/**
 * Function to interchange 2 float arrays.
 */
static inline void
jbm_array_f32_change (float **restrict fa,      ///< 1st float array.
                      float **restrict fb)      ///< 2nd float array.
{
  float *fc;
  fc = *fa;
  *fa = *fb;
  *fb = fc;
}

/**
 * Function to merge 2 increasingly sorted float arrays.
 *
 * \return resulting float array.
 */
static inline float *
jbm_array_f32_merge (const float *xa,
                     ///< pointer to the 1st increasingly sorted float array.
                     const unsigned int na,
                     ///< number of elements of the 1st array.
                     const float *xb,
                     ///< pointer to the 2nd increasingly sorted float array.
                     const unsigned int nb,
                     ///< number of elements of the 2nd array.
                     unsigned int *nc)
                     ///< pointer to the number of elements of the new array.
{
  float *xc;
  unsigned int i, j, k;
  xc = (float *) malloc ((na + nb) * sizeof (float));
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
  xc = (float *) realloc (xc, k * sizeof (float));
  *nc = k;
  return xc;
}

#if !defined(__SSE4_2__) && !defined(__ARM_NEON) && !defined(__riscv_vector)

/**
 * Function to add 2 float arrays.
 */
static inline void
jbm_array_f32_add (float *xr,   ///< result float array.
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
jbm_array_f32_sub (float *xr,   ///< result float array.
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
jbm_array_f32_mul1 (float *xr,  ///< result float array.
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
jbm_array_f32_div1 (float *xr,  ///< result float array.
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
jbm_array_f32_mul (float *xr,   ///< result float array.
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
jbm_array_f32_div (float *xr,   ///< result float array.
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
jbm_array_f32_dbl (float *xr,   ///< result float array.
                   const float *xd,     ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
    xr[i] = jbm_f32_dbl (xd[i]);
}

/**
 * Function to calculate the square of a float array.
 */
static inline void
jbm_array_f32_sqr (float *xr,   ///< result float array.
                   const float *xd,     ///< data float array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
    xr[i] = jbm_f32_sqr (xd[i]);
}

/**
 * Function to find the highest element of a float array.
 *
 * \return the highest value.
 */
static inline float
jbm_array_f32_max (const float *xx,     ///< float array.
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
jbm_array_f32_min (const float *xx,     ///< float array.
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
jbm_array_f32_maxmin (const float *xx,  ///< float array.
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
