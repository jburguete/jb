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

#define JBM_BIAS_F32 126u       ///< bias for doubles.
#define JBM_BITS_1_F32 0x3f800000u      ///< 1 bits for floats.
#define JBM_BITS_ABS_F32 0x7fffffffu    ///< absolute value bits for floats.
#define JBM_BITS_EXPONENT_F32 0x7f800000u       ///< exponent bits for floats.
#define JBM_BITS_MANTISSA_F32 0x007fffffu       ///< mantissa bits for floats.
#define JBM_BITS_SIGN_F32 0x80000000u   ///< sign bits for floats.
#define JBM_CBRT2_F32 1.2599210498948731647672106072782284f
///< cbrt(2) for floats.
#define JBM_CBRT4_F32 1.5874010519681994747517056392723083f
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
  2.8132688093637968574117752066411794e-01f,
  4.2264991917449441654926442583082591e+00f,
  4.7760730828466006553554372713002837e+00f,
  2.7751401404637903290286424751707367e-01f,
  5.6987939521676560148648909944428899e+00f,
  2.8626192174066475246272323033468441e+00f
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
  9.9999999760504756302241449400753504e-01f,
  -4.9999999717106006549133171696466736e-01f,
  8.3333009678974813706145416615163582e-02f,
  -1.3824018653025034464468224979820277e-03f
};

///> constants to approximate the log2 function for floats.
static const float K_LOG2WC_F32[6] JB_ALIGNED = {
  1.4426950746990941502408408968309535e+00f,
  1.4426950746990941502408408884351743e+00f,
  2.6330254369397960945891842219542586e-01f,
  1.4999999999999999999999999941803609e+00f,
  5.9917737484688445514802379024505870e-01f,
  4.9588687423442227574011897067360151e-02f
};

///> constants to approximate the sin function for floats.
static const float K_SINWC_F32[4] JB_ALIGNED = {
  9.9999999621137170651813551799243762e-01f,
  -1.6666648217013864440872675139317178e-01f,
  8.3319121045979028313966593427157820e-03f,
  -1.9488704231982500900496049189921104e-04f
};

///> constants to approximate the cos function for floats.
static const float K_COSWC_F32[4] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00f,
  -4.9999870846822325602310501874299391e-01f,
  4.1654925321646836720323890884061519e-02f,
  -1.3580543033931149031595817724426728e-03f
};

///> constants to approximate the tan function for floats.
static const float K_TANWC_F32[4] JB_ALIGNED = {
  9.9999998349646156349467730608404977e-01f,
  -9.5822169971574177513948945666989727e-02f,
  -4.2915625407941260857947573362446370e-01f,
  9.7240504839179075648313591704150973e-03f
};

///> constants to approximate the atan function for floats.
static const float K_ATANWC_F32[6] JB_ALIGNED = {
  9.9999997743223492718958584889200640e-01f,
  8.9613027544797370455865220090996898e-01f,
  1.3665818586474186116640553814263798e-01f,
  1.2294613740160393652000181078595938e+00f,
  3.4651430540147996480520985780319347e-01f,
  1.2250946873003576900565907391629884e-02f
};

///> constants to approximate the erf function for floats.
static const float K_ERFWC_F32[6] JB_ALIGNED = {
  1.1283791177759701163884135275444845e+00f,
  -3.7612300183946673671736840310307983e-01f,
  1.1279947943148506959517979056018854e-01f,
  -2.6704120227813841593740497984007156e-02f,
  4.9085457111688499409281784493161143e-03f,
  -5.5922790162858827219196038429276713e-04f
};

///> constants to approximate the erfc function for floats.
static const float K_ERFCWC_F32[9] JB_ALIGNED = {
  1.8290194146542917913356616057719952e-06f,
  -7.0866172898970692080852324786870091e-05f,
  5.6536176317590987027823701971432415e-01f,
  1.4115289434634965656268677517651426e+00f,
  1.7091743902793108688917011196329452e+00f,
  2.5211862914366913830059043351052257e+00f,
  3.4178297065132167293519344286253711e+00f,
  1.6746774936252017088026601844798091e+00f,
  6.8342024588967421532528823521524584e-03f
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
  y.i &= JBM_BITS_SIGN_F32;
  y.i |= JBM_BITS_1_F32;
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
  y.i &= JBM_BITS_ABS_F32;
  return y.x;
}

/**
 * Function to copy the sign of a float number to another float number.
 *
 * \return float number with magnitud of 1st number and sign of 2nd number.
 */
static inline float
jbm_copysign_f32 (const float x,        ///< float number to preserve magnitude.
                  const float y)        ///< float number to preserve sign.
{
  JBMF32 ax, sy;
  ax.x = jbm_abs_f32 (x);
  sy.x = y;
  ax.i |= sy.i & JBM_BITS_SIGN_F32;
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
jbm_mod_f32 (const float x,     ///< dividend (float).
             const float d)     ///< divisor (float).
{
  float r;
  r = floorf (x / d);
  return (jbm_abs_f32 (r) > 1.f / FLT_EPSILON) ? 0.5f * d : x - d * r;
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
  *e = (int) (exp - JBM_BIAS_F32);
  // mantissa in [0.5,1)
  y.i = (JBM_BIAS_F32 << 23u) | (y.i & 0x807fffffu);
  return y.x;
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
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_cbrtwc_f32 (const float x)
                ///< float number \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_rational_5_3_f32 (x, K_CBRTWC_F32);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_cbrtwc_f32 and
 * jbm_ldexp_f32 functions (float).
 *
 * \return function value (float).
 */
static inline float
jbm_cbrt_f32 (const float x)    ///< float number.
{
  float m;
  int e, e3, r;
  m = jbm_frexp_f32 (jbm_abs_f32 (x), &e);
  e3 = e / 3;
  r = e - 3 * e3;
  e = r >> 31;
  r += e & 3;
  e3 -= e & 1;
  m = jbm_ldexp_f32 (jbm_cbrtwc_f32 (m), e3);
  if (r & 1)
    m *= JBM_CBRT2_F32;
  if (r & 2)
    m *= JBM_CBRT4_F32;
  return jbm_copysign_f32 (m, x);
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
  return jbm_polynomial_5_f32 (x, K_EXP2WC_F32);
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
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (float).
 *
 * \return function value (float).
 */
static inline float
jbm_log2wc_f32 (const float x)  ///< float number.
{
  return x * jbm_rational_5_2_f32 (x, K_LOG2WC_F32);
}

/**
 * Function to calculate the function log2(x) using jbm_log2wc0_f32,
 * jbm_log2wc1_f32 and jbm_frexp_f32 (float).
 *
 * \return function value (float).
 */
static inline float
jbm_log2_f32 (const float x)    ///< float number.
{
  float y;
  int e, m;
  if (x < 0.f)
    return NAN;
  if (x == 0.f)
    return -INFINITY;
  if (!finitef (x))
    return x;
  y = jbm_frexp_f32 (x, &e);
  m = y < M_SQRT1_2f;
  y += (float) m * y;
  e -= m;
  return jbm_log2wc_f32 (y - 1.f) + (float) e;
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
  return jbm_exp2_f32 (e * jbm_log2_f32 (x));
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
  y = x - (float) q *M_PI_2f;
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
  y = x - (float) q *M_PI_2f;
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
  y = x - (float) q *M_PI_2f;
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
 * [-1,1].
 *
 * \return function value (float).
 */
static inline float
jbm_atanwc_f32 (const float x)
                ///< float number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_rational_5_2_f32 (x * x, K_ATANWC_F32);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc_f32 functions
 * (float).
 *
 * \return function value (in [-pi/2,pi/2]) (float).
 */
static inline float
jbm_atan_f32 (const float x)    ///< float number.
{
  float f, ax;
  ax = jbm_abs_f32 (x);
  if (ax > 1.f)
    f = M_PI_2f - jbm_atanwc_f32 (1.f / ax);
  else
    f = jbm_atanwc_f32 (ax);
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
  return jbm_rational_8_4_f32 (1.f / x, K_ERFCWC_F32) * x / jbm_exp_f32 (x * x);
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

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (float).
 *
 * \return integral value (float).
 */
static inline float
jbm_integral_f32 (float (*f) (float),
                  ///< pointer to the function to integrate.
                  const float x1,       ///< left limit of the interval.
                  const float x2)       ///< right limit of the interval.
{
  float k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  float k2;
  unsigned int i;
#endif
  dx = 0.5f *(x2 - x1);
  x = 0.5f *(x1 + x2);
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
