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
 * \file math_f64.h
 * \brief Header file with useful mathematical functions for double.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2026, Javier Burguete Tolosa.
 */
#ifndef JB_MATH_F64__H
#define JB_MATH_F64__H 1

#define JBM_F64_BIAS 1022ull    ///< bias for doubles.
#define JBM_F64_BITS_1 0x3ff0000000000000ull    ///< 1 bits for doubles.
#define JBM_F64_BITS_ABS 0x7fffffffffffffffull
///< absolute value bits for doubles.
#define JBM_F64_BITS_EXPONENT 0x7ff0000000000000ull
///< exponent bits for doubles.
#define JBM_F64_BITS_MANTISSA 0x000fffffffffffffull
///< mantissa bits for doubles.
#define JBM_F64_BITS_SIGN 0x8000000000000000ull ///< sign bits for doubles.
#define JBM_F64_CBRT2 1.2599210498948731647672106072782284
///< cbrt(2) for doubles.
#define JBM_F64_CBRT4 1.5874010519681994747517056392723083
///< cbrt(4) for doubles.
#define JBM_SQRT_DBL_MIN 1.4916681462400413486581930630925868e-154
///< root square of standard DBL_MIN.
#define JBM_SQRT_DBL_EPSILON 1.4901161193847656250000000000000000e-08
///< root square of standard DBL_EPSILON.
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

///> constants to approximate the cbrt function for doubles.
static const double K_CBRTWC_F64[12] JB_ALIGNED = {
  1.7718686183875175603139544484533900e-01,
  1.2169571213522369065772549976496928e+01,
  1.1256066417598028003232640910156050e+02,
  2.6547553832975422542280207425277638e+02,
  1.7830804339229675842086626245539769e+02,
  2.8519175311160106828576776700724692e+01,
  3.8914609514372227872886598038878661e-01,
  3.0350139138825850517393815412620929e+01,
  1.7243126595509990438386931097781146e+02,
  2.6791347699262659234583097582624045e+02,
  1.1579465236861792653929300030594967e+02,
  1.0109790924525940018717231389567802e+01
};

///> constants to approximate the exp2 function for doubles.
static const double K_EXP2WC_F64[10] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00,
  3.1551407239906986988161075462448998e-01,
  4.2289506139480013510676407722966894e-02,
  2.9097220880504493516718857680963660e-03,
  8.9138247014634237380720759538597017e-05,
  -3.7763310816086027432232033424382671e-01,
  6.3818323387572650336611671715461333e-02,
  -6.1123950073401656901620418420329687e-03,
  3.3713461650323473290844538223326386e-04,
  -8.7353990679615663678565742889509697e-06
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
static const double K_LOG2WC_F64[12] JB_ALIGNED = {
  1.4426950408889643983725307943209416e+00,
  3.5818518827585966350963342540737895e+00,
  3.1833258001062593493035188475361560e+00,
  1.2104545668341014617194767595925900e+00,
  1.8134549019295317067986922336916947e-01,
  7.0855485595330470841886789076486238e-03,
  2.9827505337174685234055484412584337e+00,
  3.3645552366728262403681178318919831e+00,
  1.7770506106256222990863399015813137e+00,
  4.3839364175537096860513283500899579e-01,
  4.3013314509502503705068655382042025e-02,
  9.9499451799620213965939390879258034e-04
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
static const double K_ATANWC_F64[12] JB_ALIGNED = {
  9.9999999999999175333741345970300904e-01,
  2.2542149400457825740971058915543142e+00,
  1.7793305339181330169566039030240487e+00,
  5.8415770182113540512685410156935423e-01,
  7.3048927300614979638775008950466053e-02,
  2.3235338953272325527617663379700706e-03,
  2.5875482733783421466549992492745531e+00,
  2.4418466250694193902611167000358452e+00,
  1.0234540646127538110215619158279289e+00,
  1.8436960343110222430805160669161968e-01,
  1.1328188703662824068110382426783447e-02,
  1.0227697723521074819475943703005083e-04
};

///> constants to approximate the erf function for doubles.
static const double K_ERFWC_F64[10] JB_ALIGNED = {
  1.1283791670955124335106943301853176e+00,
  1.4215358907595895479893643783186639e-01,
  4.5301425454197853378080730832141851e-02,
  1.8271291768119986238058951208930619e-03,
  1.9486917410599984284130461524131621e-04,
  4.5931367152218931972956975491994269e-01,
  9.3251900173059224054154476261149212e-02,
  1.0581374453686304684622313001028968e-02,
  6.8104328134718397220150693667521712e-04,
  2.0283885897883517557982234839910159e-05
};

///> constants to approximate the erfc function for doubles.
static const double K_ERFCWC_F64[17] JB_ALIGNED = {
  2.7486294922128779952642696244375391e-12,
  -3.5506132520286306834495030249388780e-10,
  5.6418960393139941019288861280278943e-01,
  5.4144585882951546500767884517112505e+00,
  2.6528548490426231658610398872410652e+01,
  7.9627334354869303713508083864793141e+01,
  1.5256375324128094891688194509498466e+02,
  1.7726294788249903636107358753255003e+02,
  1.0039370299360315360645474159604816e+02,
  9.5968792032852963611710206347217227e+00,
  4.7520600135732827406413770378274748e+01,
  1.4593466225085869199568415537574834e+02,
  2.9341718262952295732015629689663292e+02,
  3.8000838046172006313203664738079598e+02,
  2.9054767607693271730056597528079080e+02,
  1.0039308981948263089282517676786553e+02,
  6.8858891678377005958210637899192698e-05
};

///> 1st constant to calculate integrals by the Gauss method (double).
static const double JBM_INTEGRAL_GAUSS_A_F64[JBM_INTEGRAL_GAUSS_N] = {
#if JBM_INTEGRAL_GAUSS_N == 1
  2.
#elif JBM_INTEGRAL_GAUSS_N == 2
  8. / 9.,
  5. / 9.
#elif JBM_INTEGRAL_GAUSS_N == 3
  128. / 225.,
  4.7862867049936646804129151483563819e-1,
  2.3692688505618908751426404071991736e-1
#elif JBM_INTEGRAL_GAUSS_N == 4
  4.1795918367346938775510204081632653e-1,
  3.8183005050511894495036977548897513e-1,
  2.7970539148927666790146777142377958e-1,
  1.2948496616886969327061143267908202e-1
#endif
};

///> 2nd constant to calculate integrals by the Gauss method (double).
static const double JBM_INTEGRAL_GAUSS_B_F64[JBM_INTEGRAL_GAUSS_N] = {
#if JBM_INTEGRAL_GAUSS_N == 1
  0.
#elif JBM_INTEGRAL_GAUSS_N == 2
  0.,
  7.7459666924148340427791481488384306e-1
#elif JBM_INTEGRAL_GAUSS_N == 3
  0.,
  5.3846931010568309103631442070020880e-1,
  9.0617984593866399279762687829939297e-1
#elif JBM_INTEGRAL_GAUSS_N == 4
  0.,
  4.0584515137739716690660641207696146e-1,
  7.4153118559939443986386477328078841e-1,
  9.4910791234275852452618968404785126e-1
#endif
};

/**,,
 * Function to calculate the double of a double number.
 *
 * \return double double.
 */
static inline double
jbm_f64_dbl (const double x)    ///< double number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a double number.
 *
 * \return double square.
 */
static inline double
jbm_f64_sqr (const double x)    ///< double number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the opposite of a double number.
 *
 * \return double opposite.
 */
static inline double
jbm_f64_opposite (const double x)       ///< float number.
{
  return -x;
}

/**
 * Function to calculate the reciprocal of a double number.
 *
 * \return double reciprocal.
 */
static inline double
jbm_f64_reciprocal (const double x)     ///< float number.
{
  return 1. / x;
}

/**
 * Function to calculate the sign of a double number.
 *
 * \return double sign.
 */
static inline double
jbm_f64_sign (const double x)   ///< double number.
{
  JBMF64 y;
  y.x = x;
  y.i &= JBM_F64_BITS_SIGN;
  y.i |= JBM_F64_BITS_1;
  return y.x;
}

/**
 * Function to calculate the abs function (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_abs (const double x)    ///< double number.
{
  JBMF64 y;
  y.x = x;
  y.i &= JBM_F64_BITS_ABS;
  return y.x;
}

/**
 * Function to copy the sign of a double number to another double number.
 *
 * \return double number with magnitud of 1st number and sign of 2nd number.
 */
static inline double
jbm_f64_copysign (const double x,
///< double number to preserve magnitude.
                  const double y)       ///< double number to preserve sign.
{
  JBMF64 ax, sy;
  ax.x = jbm_f64_abs (x);
  sy.x = y;
  ax.i |= sy.i & JBM_F64_BITS_SIGN;
  return ax.x;
}

/**
 * Function to calculate the hypot function (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_hypot (const double x,  ///< 1st double number.
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
jbm_f64_mod (const double x,    ///< dividend (double).
             const double d)    ///< divisor (double).
{
  double r;
  r = floor (x / d);
  return (jbm_f64_abs (r) > 1. / DBL_EPSILON) ? 0.5 * d : x - d * r;
}

/**
 * Function to implement the standard frexp function (double).
 *
 * \return normalize fraction value in [1/2,1).
 */
static inline double
jbm_f64_frexp (const double x,  ///< double number.
               int *e)          ///< pointer to the extracted exponent.
{
  JBMF64 y;
  uint64_t exp;
  y.x = x;
  // check NaN or 0
  exp = y.i & JBM_F64_BITS_ABS;
  if (exp >= JBM_F64_BITS_EXPONENT || !exp)
    {
      *e = 0;
      return x;
    }
  // extract exponent
  exp = y.i >> 52u;
  // subnormal
  if (!exp)
    {
      y.x *= 0x1p52;
      exp = (y.i >> 52u) - 52u;
    }
  // exponent
  *e = (int) exp - JBM_F64_BIAS;
  // mantissa in [0.5,1)
  y.i = (JBM_F64_BIAS << 52u) | (y.i & 0x800fffffffffffffull);
  return y.x;
}

/**
 * Function to calculate the function 2^n with n an integer number (int).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_exp2n (int e)           ///< exponent number (int).
{
  JBMF64 x;
  if (e > 1023)
    return INFINITY;
  if (e < -1074)
    return 0.;
  if (e > -1023)
    x.i = (1023ll + e) << 52;
  else
    x.i = 1ull << (e + 1074);
  return x.x;
}

/**
 * Function to implement the standard ldexp function (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_ldexp (const double x,  ///< double number.
               int e)           ///< exponent number (int).
{
  return x * jbm_f64_exp2n (e);
}

/**
 * Function to calculate a 1st order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_1 (const double x,   ///< double value.
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
jbm_f64_polynomial_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_1 (x, p + 1);
}

/**
 * Function to calculate a 3rd order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_2 (x, p + 1);
}

/**
 * Function to calculate a 4th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_4 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_3 (x, p + 1);
}

/**
 * Function to calculate a 5th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_5 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_4 (x, p + 1);
}

/**
 * Function to calculate a 6th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_6 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_5 (x, p + 1);
}

/**
 * Function to calculate a 7th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_7 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_6 (x, p + 1);
}

/**
 * Function to calculate a 8th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_8 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_7 (x, p + 1);
}

/**
 * Function to calculate a 9th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_9 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_8 (x, p + 1);
}

/**
 * Function to calculate a 10th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_10 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_9 (x, p + 1);
}

/**
 * Function to calculate a 11th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_11 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_10 (x, p + 1);
}

/**
 * Function to calculate a 12th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_12 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_11 (x, p + 1);
}

/**
 * Function to calculate a 13th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_13 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_12 (x, p + 1);
}

/**
 * Function to calculate a 14th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_14 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_13 (x, p + 1);
}

/**
 * Function to calculate a 15th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_15 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_14 (x, p + 1);
}

/**
 * Function to calculate a 16th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_16 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_15 (x, p + 1);
}

/**
 * Function to calculate a 17th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_17 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_16 (x, p + 1);
}

/**
 * Function to calculate a 18th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_18 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_17 (x, p + 1);
}

/**
 * Function to calculate a 19th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_19 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_18 (x, p + 1);
}

/**
 * Function to calculate a 20th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_20 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_19 (x, p + 1);
}

/**
 * Function to calculate a 21th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_21 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_20 (x, p + 1);
}

/**
 * Function to calculate a 22th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_22 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_21 (x, p + 1);
}

/**
 * Function to calculate a 23th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_23 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_22 (x, p + 1);
}

/**
 * Function to calculate a 24th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_24 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_23 (x, p + 1);
}

/**
 * Function to calculate a 25th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_25 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_24 (x, p + 1);
}

/**
 * Function to calculate a 26th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_26 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_25 (x, p + 1);
}

/**
 * Function to calculate a 27th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_27 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_26 (x, p + 1);
}

/**
 * Function to calculate a 28th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_28 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_27 (x, p + 1);
}

/**
 * Function to calculate a 29th order polynomial (double).
 *
 * \return polynomial value.
 */
static inline double
jbm_f64_polynomial_29 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] + x * jbm_f64_polynomial_28 (x, p + 1);
}

/**
 * Function to calculate a 1st order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_1_0 (const double x,   ///< double value.
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
jbm_f64_rational_2_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_1 (x, p + 1));
}

/**
 * Function to calculate a 2nd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_2_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_1 (x, p) / (1. + x * p[2]);
}

/**
 * Function to calculate a 3rd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_3_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_2 (x, p + 1));
}

/**
 * Function to calculate a 3rd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_3_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 2));
}

/**
 * Function to calculate a 3rd order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_3_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_2 (x, p) / (1. + x * p[3]);
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_4_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_3 (x, p + 1));
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_4_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 2));
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_4_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 3));
}

/**
 * Function to calculate a 4th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_4_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_3 (x, p) / (1. + x * p[4]);
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_5_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_4 (x, p + 1));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_5_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 2));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_5_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 3));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_5_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 4));
}

/**
 * Function to calculate a 5th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_5_4 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_4 (x, p) / (1. + x * p[5]);
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_6_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_5 (x, p + 1));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_6_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 2));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_6_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 3));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_6_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 4));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_6_4 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 5));
}

/**
 * Function to calculate a 6th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_6_5 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_5 (x, p) / (1. + x * p[6]);
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_6 (x, p + 1));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 2));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 3));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 4));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_4 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 5));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_5 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 6));
}

/**
 * Function to calculate a 7th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_7_6 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_6 (x, p) / (1. + x * p[7]);
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_7 (x, p + 1));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 2));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 3));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 4));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_4 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 5));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_5 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 6));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_6 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 7));
}

/**
 * Function to calculate a 8th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_8_7 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_7 (x, p) / (1. + x * p[8]);
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_0 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_8 (x, p + 1));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_1 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 2));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_2 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 3));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_3 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 4));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_4 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 5));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_5 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 6));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_6 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 7));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_7 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 8));
}

/**
 * Function to calculate a 9th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_9_8 (const double x,   ///< double value.
                      const double *p)  ///< array of coefficients.
{
  return jbm_f64_polynomial_8 (x, p) / (1. + x * p[9]);
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_9 (x, p + 1));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 2));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 3));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 4));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 5));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 6));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 7));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 8));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 9));
}

/**
 * Function to calculate a 10th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_10_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return jbm_f64_polynomial_9 (x, p) / (1. + x * p[10]);
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_10 (x, p + 1));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 2));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 3));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 4));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 5));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 6));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 7));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 8));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 9));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 10));
}

/**
 * Function to calculate a 11th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_11_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_10 (x, p) / (1. + x * p[11]);
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_11 (x, p + 1));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 2));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 3));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 4));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 5));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 6));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 7));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 8));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 9));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 10));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 11));
}

/**
 * Function to calculate a 12th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_12_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_11 (x, p) / (1. + x * p[12]);
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_12 (x, p + 1));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 2));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 3));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 4));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 5));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 6));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 7));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 8));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 9));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 10));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 11));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 12));
}

/**
 * Function to calculate a 13th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_13_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_12 (x, p) / (1. + x * p[13]);
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_13 (x, p + 1));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 2));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 3));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 4));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 5));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 6));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 7));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 8));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 9));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 10));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 11));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 12));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 13));
}

/**
 * Function to calculate a 14th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_14_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_13 (x, p) / (1. + x * p[14]);
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_14 (x, p + 1));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 2));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 3));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 4));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 5));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 6));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 7));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 8));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 9));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 10));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 11));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 12));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 13));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 14));
}

/**
 * Function to calculate a 15th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_15_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_14 (x, p) / (1. + x * p[15]);
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_15 (x, p + 1));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_14 (x, p + 2));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 3));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 4));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 5));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 6));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 7));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 8));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 9));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 10));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 11));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 12));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 13));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 14));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_14 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 15));
}

/**
 * Function to calculate a 16th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_16_15 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_15 (x, p) / (1. + x * p[16]);
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_16 (x, p + 1));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_15 (x, p + 2));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_14 (x, p + 3));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 4));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 5));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 6));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 7));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 8));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 9));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 10));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 11));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 12));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 13));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 14));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_14 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 15));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_15 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_15 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 16));
}

/**
 * Function to calculate a 17th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_17_16 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_16 (x, p) / (1. + x * p[17]);
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_17 (x, p + 1));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_16 (x, p + 2));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_15 (x, p + 3));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_14 (x, p + 4));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 5));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 6));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 7));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 8));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 9));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 10));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 11));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 12));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 13));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 14));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_14 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 15));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_15 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_15 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 16));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_16 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_16 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 17));
}

/**
 * Function to calculate a 18th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_18_17 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_17 (x, p) / (1. + x * p[18]);
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_18 (x, p + 1));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_17 (x, p + 2));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_16 (x, p + 3));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_15 (x, p + 4));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_14 (x, p + 5));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 6));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 7));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 8));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 9));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 10));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 11));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 12));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 13));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 14));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_14 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 15));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_15 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_15 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 16));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_16 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_16 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 17));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_17 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_17 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 18));
}

/**
 * Function to calculate a 19th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_19_18 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_18 (x, p) / (1. + x * p[19]);
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_19 (x, p + 1));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_18 (x, p + 2));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_17 (x, p + 3));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_16 (x, p + 4));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_15 (x, p + 5));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_14 (x, p + 6));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 7));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 8));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 9));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 10));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 11));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 12));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 13));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 14));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_14 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 15));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_15 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_15 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 16));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_16 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_16 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 17));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_17 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_17 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 18));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_18 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_18 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 19));
}

/**
 * Function to calculate a 20th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_20_19 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_19 (x, p) / (1. + x * p[20]);
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_0 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return p[0] / (1. + x * jbm_f64_polynomial_20 (x, p + 1));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_1 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_1 (x, p) / (1. + x * jbm_f64_polynomial_19 (x, p + 2));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_2 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_2 (x, p) / (1. + x * jbm_f64_polynomial_18 (x, p + 3));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_3 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_3 (x, p) / (1. + x * jbm_f64_polynomial_17 (x, p + 4));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_4 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_4 (x, p) / (1. + x * jbm_f64_polynomial_16 (x, p + 5));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_5 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_5 (x, p) / (1. + x * jbm_f64_polynomial_15 (x, p + 6));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_6 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_6 (x, p) / (1. + x * jbm_f64_polynomial_14 (x, p + 7));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_7 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_7 (x, p) / (1. + x * jbm_f64_polynomial_13 (x, p + 8));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_8 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_8 (x, p) / (1. + x * jbm_f64_polynomial_12 (x, p + 9));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_9 (const double x,  ///< double value.
                       const double *p) ///< array of coefficients.
{
  return
    jbm_f64_polynomial_9 (x, p) / (1. + x * jbm_f64_polynomial_11 (x, p + 10));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_10 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_10 (x, p) / (1. + x * jbm_f64_polynomial_10 (x, p + 11));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_11 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_11 (x, p) / (1. + x * jbm_f64_polynomial_9 (x, p + 12));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_12 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_12 (x, p) / (1. + x * jbm_f64_polynomial_8 (x, p + 13));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_13 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_13 (x, p) / (1. + x * jbm_f64_polynomial_7 (x, p + 14));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_14 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_14 (x, p) / (1. + x * jbm_f64_polynomial_6 (x, p + 15));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_15 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_15 (x, p) / (1. + x * jbm_f64_polynomial_5 (x, p + 16));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_16 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_16 (x, p) / (1. + x * jbm_f64_polynomial_4 (x, p + 17));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_17 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_17 (x, p) / (1. + x * jbm_f64_polynomial_3 (x, p + 18));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_18 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_18 (x, p) / (1. + x * jbm_f64_polynomial_2 (x, p + 19));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_19 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return
    jbm_f64_polynomial_19 (x, p) / (1. + x * jbm_f64_polynomial_1 (x, p + 20));
}

/**
 * Function to calculate a 21th order rational (double).
 *
 * \return rational value.
 */
static inline double
jbm_f64_rational_21_20 (const double x, ///< double value.
                        const double *p)        ///< array of coefficients.
{
  return jbm_f64_polynomial_20 (x, p) / (1. + x * p[21]);
}

/**
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_cbrtwc (const double x)
                ///< double number \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_f64_rational_11_6 (x, K_CBRTWC_F64);
}

/**
 * Function to calculate the function cbrt(x) using the jbm_f64_abs and
 * jbm_f64_pow functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_cbrt (const double x)   ///< double number.
{
  double m;
  int e, e3, r;
  m = jbm_f64_frexp (jbm_f64_abs (x), &e);
  e3 = e / 3;
  r = e - 3 * e3;
  e = r >> 31;
  r += e & 3;
  e3 -= e & 1;
  m = jbm_f64_ldexp (jbm_f64_cbrtwc (m), e3);
  if (r & 1)
    m *= JBM_F64_CBRT2;
  if (r & 2)
    m *= JBM_F64_CBRT4;
  return jbm_f64_copysign (m, x);
}

/**
 * Function to calculate the well conditionated function exp2(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_exp2wc (const double x)
                ///< double number \f$\in[\frac12,1]\f$.
{
  return jbm_f64_rational_9_4 (x, K_EXP2WC_F64);
}

/**
 * Function to calculate the function exp2(x) using the jbm_f64_exp2wc and
 * jbm_f64_exp2n functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_exp2 (const double x)   ///< double number.
{
  double y, f;
  if (x >= DBL_MAX_EXP)
    return INFINITY;
  y = floor (x);
  f = x - y;
  y = jbm_f64_exp2n ((int) y);
  return y * jbm_f64_exp2wc (f);
}

/**
 * Function to calculate the function exp(x) using the jbm_f64_exp2 function
 * (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_exp (const double x)    ///< double number.
{
  return jbm_f64_exp2 (x * M_LOG2E);
}

/**
 * Function to calculate the function exp10(x) using the jbm_f64_exp2 function
 * (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_exp10 (const double x)  ///< double number.
{
  return jbm_f64_exp2 (x * M_LN10 / M_LN2);
}

/**
 * Function to calculate the well conditionated function expm1(x) for x in
 * [-log(2)/2,log(2)/2].
 *
 * \return function value (double).
 */
static inline double
jbm_f64_expm1wc (const double x)
                 ///< double number \f$\in\left[-\log(2)/2,\log(2)/2\right]\f$.
{
  return x * jbm_f64_rational_8_2 (x, K_EXPM1WC_F64);
}

/**
 * Function to calculate the function expm1(x) using the jbm_f64_expm1wc and
 * jbm_f64_exp functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_expm1 (const double x)  ///< double number.
{
  if (jbm_f64_abs (x) < M_LN2 / 2.)
    return jbm_f64_expm1wc (x);
  return jbm_f64_exp (x) - 1.;
}

/**
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_log2wc (const double x) ///< double number.
{
  return x * jbm_f64_rational_11_5 (x, K_LOG2WC_F64);
}

/**
 * Function to calculate the function log2(x) using jbm_f64_log2wc and
 * jbm_f64_frexp.
 *
 * \return function value (double).
 */
static inline double
jbm_f64_log2 (const double x)   ///< double number.
{
  double y;
  int e;
  if (x < 0.)
    return NAN;
  if (x == 0.)
    return -INFINITY;
  if (!finite (x))
    return x;
  y = jbm_f64_frexp (x, &e);
  if (y < M_SQRT1_2)
    {
      y *= 2.;
      e -= 1;
    }
  return jbm_f64_log2wc (y - 1.) + (double) e;
}

/**
 * Function to calculate the function log(x) using jbm_f64_log2 (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_log (const double x)    ///< double number.
{
  return jbm_f64_log2 (x) * M_LN2;
}

/**
 * Function to calculate the function log10(x) using jbm_f64_log2 (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_log10 (const double x)  ///< double number.
{
  return jbm_f64_log2 (x) * M_LN2 / M_LN10;
}

/**
 * Function to calculate the function x^e with e an integer number (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_pown (const double x,   ///< double number.
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
 * Function to calculate the function pow using the jbm_f64_exp2 and
 * jbm_f64_log2 functions.
 *
 * \return function value (double).
 */
static inline double
jbm_f64_pow (const double x,    ///< double number.
             const double e)    ///< exponent (double).
{
  return jbm_f64_exp2 (e * jbm_f64_log2 (x));
}

/**
 * Function to calculate the well conditionated function sin(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (double).
 */
static inline double
jbm_f64_sinwc (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_f64_polynomial_6 (x * x, K_SINWC_F64);
}

/**
 * Function to calculate the well conditionated function cos(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (double).
 */
static inline double
jbm_f64_coswc (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return jbm_f64_polynomial_6 (x * x, K_COSWC_F64);
}

/**
 * Function to calculate the well conditionated function tan(x) for x in
 * [-pi/4,pi/4].
 *
 * \return function value (double).
 */
static inline double
jbm_f64_tanwc (const double x)
               ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
{
  return x * jbm_f64_rational_6_3 (x * x, K_TANWC_F64);
}

/**
 * Function to calculate the well conditionated functions sin(x) and cos(x) for
 * x in [-pi/4,pi/4] from jbm_f64_sinwc approximation (double).
 */
static inline void
jbm_f64_sincoswc (const double x,
                  ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                  double *s,    ///< pointer to the sin function value (double).
                  double *c)    ///< pointer to the cos function value (double).
{
  *s = jbm_f64_sinwc (x);
  *c = jbm_f64_coswc (x);
}

/**
 * Function to calculate reduction to \f$2\,\pi\f$ in trigonometric functions
 * (double).
 *
 * \return reduced value (double).
 */
static inline double
jbm_f64_trig (const double x,   ///< double number.
              int64_t *q)       ///< quadrant.
{
  *q = (int64_t) nearbyint (x * 1. / M_PI_2);
  return x - ((double) *q) * M_PI_2;
}

/**
 * Function to calculate the function sin(x) from jbm_f64_sinwc and
 * jbm_f64_coswc approximations (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_sin (const double x)    ///< double number.
{
  double y;
  int64_t q;
  y = jbm_f64_trig (x, &q);
  y = (q & 1) ? jbm_f64_coswc (y) : jbm_f64_sinwc (y);
  return (q & 2) ? -y : y;
}

/**
 * Function to calculate the function cos(x) from jbm_f64_sinwc and
 * jbm_f64_coswc approximations (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_cos (const double x)    ///< double number.
{
  double y;
  int64_t q;
  y = jbm_f64_trig (x, &q);
  q &= 3;
  y = (q & 1) ? jbm_f64_sinwc (y) : jbm_f64_coswc (y);
  return ((q + 1) & 2) ? -y : y;
}

/**
 * Function to calculate the functions sin(x) and cos(x) from jbm_f64_sinwc and
 * jbm_f64_coswc approximations (double).
 */
static inline void
jbm_f64_sincos (const double x,
                ///< double number \f$\in\left[-\pi/4,\pi/4\right]\f$.
                double *s,      ///< pointer to the sin function value (double).
                double *c)      ///< pointer to the cos function value (double).
{
  double y, sr, cr;
  int64_t q;
  y = jbm_f64_trig (x, &q);
  jbm_f64_sincoswc (y, &sr, &cr);
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
 * Function to calculate the function tan(x) from jbm_f64_sincos.
 *
 * \return function value (double).
 */
static inline double
jbm_f64_tan (const double x)    ///< double number.
{
  double y;
  int64_t q;
  y = jbm_f64_tanwc (jbm_f64_trig (x, &q));
  return (q & 1) ? -1. / y : y;
}

/**
 * Function to calculate the well conditionated function atan(x) for x in
 * [-1,1].
 *
 * \return function value (double).
 */
static inline double
jbm_f64_atanwc (const double x)
                 ///< double number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_f64_rational_11_5 (x * x, K_ATANWC_F64);
}

/**
 * Function to calculate the function atan(x) using the jbm_f64_atanwc function
 * (double).
 *
 * \return function value (in [-pi/2,pi/2]) (double).
 */
static inline double
jbm_f64_atan (const double x)   ///< double number.
{
  double f, ax;
  ax = jbm_f64_abs (x);
  if (ax > 1.)
    f = M_PI_2 - jbm_f64_atanwc (1. / ax);
  else
    f = jbm_f64_atanwc (ax);
  return jbm_f64_copysign (f, x);
}

/**
 * Function to calculate the function atan2(y,x) using the jbm_f64_atan
 * function (double).
 *
 * \return function value (in [-pi,pi]) (double).
 */
static inline double
jbm_f64_atan2 (const double y,  ///< double y component.
               const double x)  ///< double x component.
{
  double f;
  f = jbm_f64_atan (y / x);
  if (x < 0.)
    f += jbm_f64_copysign (M_PI, y);
  return f;
}

/**
 * Function to calculate the function asin(x) using the jbm_f64_atan function.
 *
 * \return function value (in [-pi/2,pi/2]).
 */
static inline double
jbm_f64_asin (const double x)   ///< double number.
{
  return jbm_f64_atan (x / sqrt (1. - x * x));
}

/**
 * Function to calculate the function acos(x) using the jbm_f64_atan function.
 *
 * \return function value (in [0,pi]).
 */
static inline double
jbm_f64_acos (const double x)   ///< double number.
{
  double f;
  f = jbm_f64_atan (sqrt (1. - x * x) / x);
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
jbm_f64_sinh (const double x)   ///< double number.
{
  double f;
  f = jbm_f64_exp (x);
  return 0.5 * (f - 1. / f);
}

/**
 * Function to calculate the function cosh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_f64_cosh (const double x)   ///< double number.
{
  double f;
  f = jbm_f64_exp (x);
  return 0.5 * (f + 1. / f);
}

/**
 * Function to calculate the function tanh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_f64_tanh (const double x)   ///< double number.
{
  double f, fi;
  if (x > JBM_DBL_MAX_E_EXP)
    return 1.f;
  if (x < -JBM_DBL_MAX_E_EXP)
    return -1.;
  f = jbm_f64_exp (x);
  fi = 1. / f;
  return (f - fi) / (f + fi);
}

/**
 * Function to calculate the function asinh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_f64_asinh (const double x)  ///< double number.
{
  return jbm_f64_log (x + sqrt (x * x + 1.));
}

/**
 * Function to calculate the function acosh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_f64_acosh (const double x)  ///< double number.
{
  return jbm_f64_log (x + sqrt (x * x - 1.));
}

/**
 * Function to calculate the function atanh(x)
 *
 * \return function value (double).
 */
static inline double
jbm_f64_atanh (const double x)  ///< double number.
{
  return 0.5 * jbm_f64_log ((1. + x) / (1. - x));
}

/**
 * Function to calculate the well conditionated function erf(x) for x in
 * [-1,1].
 *
 * \return function value (double).
 */
static inline double
jbm_f64_erfwc (const double x)
             ///< double number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_f64_rational_9_4 (x * x, K_ERFWC_F64);
}

/**
 * Function to calculate the well conditionated function erfc(x) for
 * \f$x\in[1,\infty]\f$.
 *
 * \return function value (double).
 */
static inline double
jbm_f64_erfcwc (const double x)
                ///< double number \f$\in\left[1,\infty\right]\f$.
{
  if (x > K_ERFC_MAX_F64)
    return 0.;
  return jbm_f64_rational_16_8 (1. / x, K_ERFCWC_F64) * x / jbm_f64_exp (x * x);
}

/**
 * Function to calculate the function erf(x) using jbm_f64_erfwc and
 * jbm_f64_erfcwc functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_erf (const double x)    ///< double number.
{
  double ax;
  ax = jbm_f64_abs (x);
  if (ax > 1.)
    return jbm_f64_sign (x) * (1. - jbm_f64_erfcwc (ax));
  return jbm_f64_erfwc (x);
}

/**
 * Function to calculate the function erfc(x) using jbm_f64_erfwc and
 * jbm_f64_erfcwc functions (double).
 *
 * \return function value (double).
 */
static inline double
jbm_f64_erfc (const double x)   ///< double number.
{
  if (x > 1.)
    return jbm_f64_erfcwc (x);
  if (x < -1.)
    return 2. - jbm_f64_erfcwc (-x);
  return 1. - jbm_f64_erfwc (x);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (double).
 *
 * \return integral value (double).
 */
static inline double
jbm_f64_integral (double (*f) (double),
                  ///< pointer to the function to integrate.
                  const double x1,      ///< left limit of the interval.
                  const double x2)      ///< right limit of the interval.
{
  double k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  double k2;
  unsigned int i;
#endif
  dx = 0.5f * (x2 - x1);
  x = 0.5f * (x1 + x2);
  k = JBM_INTEGRAL_GAUSS_A_F64[0] * f (x);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = JBM_INTEGRAL_GAUSS_B_F64[i] * dx;
      k += JBM_INTEGRAL_GAUSS_A_F64[i] * (f (x - k2) + f (x + k2));
    }
#endif
  return k * dx;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * double.
 *
 * \return interval number.
 */
static inline unsigned int
jbm_array_f64_search (const double *xx, ///< double array.
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
jbm_array_f64_search_extended (const double *xx,        ///< double array.
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
  return (int) jbm_array_f64_search (xx, x, n);
}

/**
 * Function to interchange 2 double arrays.
 */
static inline void
jbm_array_f64_change (double **restrict fa,     ///< 1st double array.
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
jbm_array_f64_merge (const double *xa,
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

#if !defined(__SSE4_2__) && !defined(__ARM_NEON) && !defined(__riscv_vector)

/**
 * Function to add 2 double arrays.
 */
static inline void
jbm_array_f64_add (double *xr,  ///< result double array.
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
jbm_array_f64_sub (double *xr,  ///< result double array.
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
jbm_array_f64_mul1 (double *xr, ///< result double array.
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
jbm_array_f64_div1 (double *xr, ///< result double array.
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
jbm_array_f64_mul (double *xr,  ///< result double array.
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
jbm_array_f64_div (double *xr,  ///< result double array.
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
jbm_array_f64_dbl (double *xr,  ///< result double array.
                   const double *xd,    ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
    xr[i] = jbm_f64_dbl (xd[i]);
}

/**
 * Function to calculate the square of a double array.
 */
static inline void
jbm_array_f64_sqr (double *xr,  ///< result double array.
                   const double *xd,    ///< data double array.
                   const unsigned int n)        ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
    xr[i] = jbm_f64_sqr (xd[i]);
}

/**
 * Function to find the highest element of a double array.
 *
 * \return the highest value.
 */
static inline double
jbm_array_f64_max (const double *xx,    ///< double array.
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
jbm_array_f64_min (const double *xx,    ///< double array.
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
jbm_array_f64_maxmin (const double *xx, ///< double array.
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
