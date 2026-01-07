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
 * \file math_f64.h
 * \brief Header file with useful mathematical functions for double.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_F64__H
#define JB_MATH_F64__H 1

#define JBM_SIGN_BITS_F64 0x8000000000000000ull ///< sign bits for floats.
#define JBM_ABS_BITS_F64 0x7fffffffffffffffull
///< absolute value bits for floats.
#define JBM_1_BITS_F64 0x3ff0000000000000ull    ///< 1 bits for floats.
#define K_ERFC_MAX_F64 2.6543258454250981382470219714223799e+01
///< maximum value for the erfc function for doubles.

/**
 * union to work with bits in double numbers.
 */
typedef union
{
  double x;                     ///< floating point.
  uint64_t i;                   ///< bits.
} JBMF64;

///> constants to approximate the exp2 function for doubles.
static const double K_EXP2WC_F64[10] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00,
  3.1564054107100787724829612737602184e-01,
  4.2328496485552925381481472461658898e-02,
  2.9144694486552778911017645042212518e-03,
  8.9376187765131605698161602150391553e-05,
  -3.7750663948891745844804854530113772e-01,
  6.3769652330111929833453791349073163e-02,
  -6.1042925662459797446640153246910562e-03,
  3.3642891259425901555902575402122192e-04,
  -8.7075910521445930114935052394113016e-06
};

///> constants to approximate the expm1 function for doubles.
static const double K_EXPM1WC_F64[9] JB_ALIGNED = {
  9.9999999999999993131756225544753094e-01,
  5.2362751925574714623141223351286680e-09,
  2.4997827131288932141803009703069477e-02,
  -4.9999999476372473063313242670729915e-01,
  1.0833115784647369469392147246713109e-01,
  -1.2498913129290650446942470995497145e-02,
  6.9426337254263772279528784338739769e-04,
  -7.2344109057014383130981579775388512e-12,
  -1.6504302496667174312202550945210262e-06
};

///> constants to approximate the log2 function for doubles.
static const double K_LOG2WC_F64[13] JB_ALIGNED = {
  -7.5911179965729437730319958809586983e+00,
  -2.1745878660785803613825027728692004e+02,
  -1.0058917531264149861652206772406605e+03,
  -5.7873477140185186880127773331312290e+02,
  1.0933545306794768931296661452224980e+03,
  6.6359295448063739169545607843873237e+02,
  5.2728943972583550052658460060431725e+01,
  5.1560547987698687983064233751657227e+01,
  4.5921448778667653970420954063657282e+02,
  1.1574695428037037391037987187002303e+03,
  9.1842897557335307858293547732027942e+02,
  2.0624219195079475156178217149552980e+02,
  7.9999999999999999784699819782448249e+00
};

///> constants to approximate the sin function for doubles.
static const double K_SINWC_F64[7] JB_ALIGNED = {
  9.9999999999999992623245559878814952e-01,
  -1.6666666666666364330457161520945679e-01,
  8.3333333332914215008249633085432124e-03,
  -1.9841269813722084762022203361124509e-04,
  2.7557309538951511271926821227683747e-06,
  -2.5050236524994045922963213857345587e-08,
  1.5871385373920555663148151326946456e-10
};

///> constants to approximate the cos function for doubles.
static const double K_COSWC_F64[7] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00,
  -4.9999999999999440376457007463735526e-01,
  4.1666666666492450884540915814117855e-02,
  -1.3888888870829588098166703602860110e-03,
  2.4801578693667267346294053050542303e-05,
  -2.7555244202025289575852225476868964e-07,
  2.0630479840880538393750501692926097e-09
};

///> constants to approximate the tan function for doubles.
static const double K_TANWC_F64[7] JB_ALIGNED = {
  1.0000000000000004612317050060239123e+00,
  -1.2829498559754689113788436037817669e-01,
  2.8072015187775594420275940293754057e-03,
  -7.4960804157328679407565426654456978e-06,
  -4.6162831893086258169633220335348348e-01,
  2.3349974495503494702067029119840629e-02,
  -2.0863235499919161595887852209764551e-04
};

///> constants to approximate the atan function for doubles.
static const double K_ATANWC0_F64[9] JB_ALIGNED = {
  9.9999999999999892885431242093460277e-01,
  1.7174903583161590067209802801700983e+00,
  8.9269426216044677721608513590021333e-01,
  1.4163984812125930752849445954217019e-01,
  3.2604376971682303874877317516176805e-03,
  2.0508236916492778234757611493054375e+00,
  1.3763021593913388881909503195535988e+00,
  3.3309963863724327431836852841993498e-01,
  2.0896929539022880929863547442741776e-02
};

///> constants to approximate the atan function for doubles.
static const double K_ATANWC1_F64[15] JB_ALIGNED = {
  7.8539816339744830961566084581987570e-01,
  3.1819390432632386792351556735031186e+00,
  5.6964677966558444069447919149247881e+00,
  5.8822520517759730397238177011228731e+00,
  3.7851351983215295278973376585706051e+00,
  1.5176905831213929328267835665386785e+00,
  3.5100316653745272669543117337878952e-01,
  3.6122687412995146191862538761021960e-02,
  3.4147508464519440680261617756430658e+00,
  5.3973800436361466541899660503959920e+00,
  5.0342827275452574948898418914278895e+00,
  2.9701830022488089959827768549032646e+00,
  1.1031195818341327004866979100917678e+00,
  2.3809707240199433412415230949880199e-01,
  2.2996267647112199700778926061335174e-02
};

///> constants to approximate the erf function for doubles.
static const double K_ERFWC_F64[10] JB_ALIGNED = {
  1.1283791670955125741568625140595924e+00,
  1.4214718479810524638176279497276018e-01,
  4.5306179971396543689883989424741560e-02,
  1.8274816817509842381252187433816260e-03,
  1.9503007205367896129061249929141934e-04,
  4.5930799587872320487603920574351491e-01,
  9.3254221872966235149201940728633979e-02,
  1.0583028318143433311571125708187167e-02,
  6.8136985371491773166489869006039550e-04,
  2.0308921409930923466110203520081559e-05
};

///> constants to approximate the erfc function for doubles.
static const double K_ERFCWC_F64[18] JB_ALIGNED = {
  1.4068588995058420500630931809269970e-12,
  -1.8657254388023546730046368391498488e-10,
  5.6418959458019014839484754053233654e-01,
  5.1294066305471415231061307699002670e+00,
  2.4436083010270547455007441627987717e+01,
  7.1632672454207454009508826593082853e+01,
  1.3462437466666864661819982658861665e+02,
  1.5365135045282892598234569796679179e+02,
  8.5382952430678222482826717278555941e+01,
  -1.0223330133812441535391087369889504e-03,
  9.6154203046176108602794395596167761e-05,
  9.0916372218779868333705215738850418e+00,
  4.3811813324931483498593788820195252e+01,
  1.3151169396454863405619902865629433e+02,
  2.5976805958263786606042611434483725e+02,
  3.3130858420391200851618131659470996e+02,
  2.5000691536633340189257291729544458e+02,
  8.5377733066685558638617945305512186e+01
};

/**,,
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
 * Function to calculate the sign of a double number.
 *
 * \return double sign.
 */
static inline double
jbm_sign_f64 (const double x)   ///< double number.
{
  JBMF64 y;
  y.x = x;
  y.i &= JBM_SIGN_BITS_F64;
  y.i |= JBM_1_BITS_F64;
  return y.x;
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
  y.i &= JBM_ABS_BITS_F64;
  return y.x;
}

/**
 * Function to copy the sign of a double number to another double number.
 *
 * \return double number with magnitud of 1st number and sign of 2nd number.
 */
static inline double
jbm_copysign_f64 (const double x,
///< double number to preserve magnitude.
                  const double y)       ///< double number to preserve sign.
{
  JBMF64 ax, sy;
  ax.x = jbm_abs_f64 (x);
  sy.x = y;
  ax.i |= sy.i & JBM_SIGN_BITS_F64;
  return ax.x;
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
jbm_mod_f64 (const double x,   ///< dividend (double).
             const double d)   ///< divisor (double).
{
  return x - d * floor (x / d);
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
  y.i &= 0x7ff0000000000000ull;
  if (y.i == 0x7ff0000000000000ull)
    {
      *e = 0;
      return x;
    }
  if (!y.i)
    {
      y.x = x;
      y.i &= 0x000fffffffffffffull;
      if (!y.i)
        {
          *e = 0;
          return x;
        }
      y.i = 0x0010000000000000ull;
      z.x = x / y.x;
      z.i &= 0x7ff0000000000000ull;
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
    x.i = 0x0008000000000000ull >> (-e - 1023ll);
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
 * Function to calculate the well conditionated function exp2(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_exp2wc_f64 (const double x)
                ///< double number \f$\in[\frac12,1]\f$.
{
  return jbm_rational_9_4_f64 (x, K_EXP2WC_F64);
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
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2].
 *
 * \return function value (double).
 */
static inline double
jbm_expm1wc_f64 (const double x)
                 ///< double number \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return x * jbm_rational_8_2_f64 (x, K_EXPM1WC_F64);
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
  return jbm_rational_12_6_f64 (x, K_LOG2WC_F64);
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
  return jbm_copysign_f64 (jbm_pow_f64 (jbm_abs_f64 (x), 1. / 3.), x);
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (double).
 */
static inline double
jbm_sinwc_f64 (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_polynomial_6_f64 (x * x, K_SINWC_F64);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (double).
 */
static inline double
jbm_coswc_f64 (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_polynomial_6_f64 (x * x, K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (double).
 */
static inline double
jbm_tanwc_f64 (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_rational_6_3_f64 (x * x, K_TANWC_F64);
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
  *s = jbm_sinwc_f64 (x);
  *c = jbm_coswc_f64 (x);
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
  int q;
  y = x * 1. / M_PI_2;
  q = (int) nearbyint (y);
  y = x - (double) q * M_PI_2;
  q &= 3;
  y = (q & 1) ? jbm_coswc_f64 (y) : jbm_sinwc_f64 (y);
  return (q & 2) ? -y : y;
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
  int q;
  y = x * 1. / M_PI_2;
  q = (int) nearbyint (y);
  y = x - (double) q * M_PI_2;
  y = (q & 1) ? jbm_sinwc_f64 (y) : jbm_coswc_f64 (y);
  return ((q + 1) & 2) ? -y : y;
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
  double y, sr, cr;
  int q;
  y = x * 1. / M_PI_2;
  q = (int) nearbyint (y);
  y = x - (double) q * M_PI_2;
  jbm_sincoswc_f64 (y, &sr, &cr);
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
 * Function to calculate the function tan(x) from jbm_sincos_f64.
 *
 * \return function value (double).
 */
static inline double
jbm_tan_f64 (const double x)    ///< double number.
{
  double y;
  int q;
  y = x * 1. / M_PI_2;
  q = (int) nearbyint (y);
  y = jbm_tanwc_f64 (x - (double) q * M_PI_2);
  return (q & 1) ? -1. / y : y;
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1/2,1/2].
 *
 * \return function value (double).
 */
static inline double
jbm_atanwc0_f64 (const double x)
                 ///< double number \f$\in\left[0,\frac12\right]\f$.
{
  return x * jbm_rational_8_4_f64 (x * x, K_ATANWC0_F64);
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [1/2,3/2].
 *
 * \return function value (double).
 */
static inline double
jbm_atanwc1_f64 (const double x)
                 ///< double number \f$\in\left[\frac12,1\right]\f$.
{
  return jbm_rational_14_7_f64 (x - 1., K_ATANWC1_F64);
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
  return jbm_copysign_f64 (f, x);
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
    f += jbm_copysign_f64 (M_PI, y);
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
 * [-1,1].
 *
 * \return function value (double).
 */
static inline double
jbm_erfwc_f64 (const double x)
             ///< double number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_rational_9_4_f64 (x * x, K_ERFWC_F64);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_erfcwc_f64 (const double x)
                ///< double number \f$\in\left[1,\infty\right]\f$.
{
  if (x > K_ERFC_MAX_F64)
    return 0.;
  return
    jbm_rational_17_10_f64 (1. / x, K_ERFCWC_F64) * x / jbm_exp_f64 (x * x);
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
    return jbm_sign_f64 (x) * (1. - jbm_erfcwc_f64 (ax));
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
  if (x > 1.)
    return jbm_erfcwc_f64 (x);
  if (x < -1.)
    return 2. - jbm_erfcwc_f64 (-x);
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
