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

#define JBM_BIAS_F64 1022ull    ///< bias for doubles.
#define JBM_BITS_1_F64 0x3ff0000000000000ull    ///< 1 bits for doubles.
#define JBM_BITS_ABS_F64 0x7fffffffffffffffull
///< absolute value bits for doubles.
#define JBM_BITS_EXPONENT_F64 0x7ff0000000000000ull
///< exponent bits for doubles.
#define JBM_BITS_MANTISSA_F64 0x000fffffffffffffull
///< mantissa bits for doubles.
#define JBM_BITS_SIGN_F64 0x8000000000000000ull ///< sign bits for doubles.
#define JBM_CBRT2_F64 1.2599210498948731647672106072782284
///< cbrt(2) for doubles.
#define JBM_CBRT4_F64 1.5874010519681994747517056392723083
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
  1.7709017894907407556280328796928981e-01,
  1.2182890092250568818971099340972177e+01,
  1.1286935135105014391780893133782318e+02,
  2.6664242380831821248817982415493013e+02,
  1.7938693994970167138939205678076967e+02,
  2.8738927937835771496818720233131912e+01,
  3.9278721683461793783970228634389578e-01,
  3.0400005179172307155471838495766228e+01,
  1.7299908170964877176667480383544008e+02,
  2.6923887415570164407899796074693244e+02,
  1.1655918835436847417609389147503757e+02,
  1.0193261136048862947334642868763900e+01
};

///> constants to approximate the exp2 function for doubles.
static const double K_EXP2WC_F64[10] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00,
  3.1551407239906986990161836306414434e-01,
  4.2289506139480013516843583748639321e-02,
  2.9097220880504493524225778913303119e-03,
  8.9138247014634237418329124940351811e-05,
  -3.7763310816086027430231272580347237e-01,
  6.3818323387572650328910630339061286e-02,
  -6.1123950073401656888797522578033975e-03,
  3.3713461650323473279672696239495238e-04,
  -8.7353990679615663634523256533176600e-06
};

///> constants to approximate the expm1 function for doubles.
static const double K_EXPM1WC_F64[9] JB_ALIGNED = {
  9.9999999999999998748197480381755779e-01,
  4.5955436854531220959733956529189030e-09,
  2.4998024281020062149446078980772396e-02,
  -4.9999999540445628584932405193128658e-01,
  1.0833135531657655290197809188444588e-01,
  -1.2499011757549772672167790794542841e-02,
  6.9427980151543997495834694485294678e-04,
  -6.3517746107717183234505082899986490e-12,
  -1.6507022419188284980521907411786657e-06
};

///> constants to approximate the log2 function for doubles.
static const double K_LOG2WC_F64[13] JB_ALIGNED = {
  1.4426950408889634003153062009652444e+00,
  3.9340897774247799472904340760434672e+00,
  3.9620544436888707854525493127912096e+00,
  1.7977198380552606130854320288725168e+00,
  3.5440034086959546467199534234742921e-01,
  2.3234206036050428286617637709741661e-02,
  1.1472520541168540377701172727173239e-04,
  3.2269032372916887875106519727564103e+00,
  4.0264051521804519530818840470706178e+00,
  2.4336526008443986121268242088477202e+00,
  7.2706865608178231129071918394229629e-01,
  9.6308826082487637572177371513828549e-02,
  3.9698989266925969725860592511745707e-03
};

///> constants to approximate the log2 function for doubles.
static const double K_LOG2WC0_F64[11] JB_ALIGNED = {
  -9.8656044724637514250921556933590351e-10,
  1.4426950160192472953530000694931642e+00,
  3.4003461522521490611370213513381309e+00,
  2.7395236204328072263457780446004574e+00,
  8.5136898384877813595675617686180590e-01,
  7.6752459412026633559154614455226159e-02,
  2.8569405402497283667267438156821747e+00,
  2.9940312444841364757977560693852352e+00,
  1.3848311444261790129755779008566000e+00,
  2.6185432193878896367934072848562480e-01,
  1.3125334743901998745928057098012348e-02
};

///> constants to approximate the log2 function for doubles.
static const double K_LOG2WC1_F64[10] JB_ALIGNED = {
  1.4426950408889633033511165725432726e+00,
  3.0439380750680127896677972119234157e+00,
  2.1287888578084798408722665565989615e+00,
  5.4661675769065208333326817742871622e-01,
  3.7048308248094166409536845126776830e-02,
  2.6098970945325016715136012043678928e+00,
  2.4471792087342613102137441017878813e+00,
  9.8250977077711119073121987538435570e-01,
  1.5368268926460432106994474957536483e-01,
  5.8201663100744709086985256825699201e-03
};

///> constants to approximate the sin function for doubles.
static const double K_SINWC_F64[7] JB_ALIGNED = {
  9.9999999999999999638490506447936854e-01,
  -1.6666666666666610713132095208361431e-01,
  8.3333333333191441563311738314429030e-03,
  -1.9841269827744157680503754905956699e-04,
  2.7557313073441011131852516374919192e-06,
  -2.5050670514345959789246022087832333e-08,
  1.5892076263028681605918258260670047e-10
};

///> constants to approximate the cos function for doubles.
static const double K_COSWC_F64[7] JB_ALIGNED = {
  1.0000000000000000000000000000000000e+00,
  -4.9999999999999368651478571950117907e-01,
  4.1666666666476457549341347660474251e-02,
  -1.3888888869667454809227923621981333e-03,
  2.4801578324327464671557752083161680e-05,
  -2.7555190838688067112761653724311995e-07,
  2.0627608547456674277551789050821916e-09
};

///> constants to approximate the tan function for doubles.
static const double K_TANWC_F64[7] JB_ALIGNED = {
  1.0000000000000000205462792587525005e+00,
  -1.2828441766604482950135329812071721e-01,
  2.8060237532407522573691307479436472e-03,
  -7.4846551012908828764481043516721762e-06,
  -4.6161775099937511329718943479302982e-01,
  2.3345274086291880796631872592367604e-02,
  -2.0846318486878152670267373941563686e-04
};

///> constants to approximate the atan function for doubles.
static const double K_ATANWC_F64[12] JB_ALIGNED = {
  9.9999999999999985870843292065029446e-01,
  2.2754411572471551828162136686654731e+00,
  1.8171072276989387289911739893430888e+00,
  6.0534130759893142328736018142030845e-01,
  7.7107874068077455316074839848785278e-02,
  2.5101809299950351513821696115884500e-03,
  2.6087744905804309833115977333748266e+00,
  2.4866987245628990276822416348749415e+00,
  1.0553431270954066798125186404621584e+00,
  1.9312013183081734118835006936614130e-01,
  1.2102855360695459066998438099063785e-02,
  1.1200475539943974889859792912805235e-04
};

///> constants to approximate the erf function for doubles.
static const double K_ERFWC_F64[10] JB_ALIGNED = {
  1.1283791670955125711644718314231982e+00,
  1.4214948685639330933670523193129193e-01,
  4.5303699868490152966413083228291383e-02,
  1.8272773390588544105672540731190414e-03,
  1.9494929536421951368254941503966526e-04,
  4.5931003602476158664405182295251949e-01,
  9.3252703987685874663536172223913071e-02,
  1.0582137247624881770452836907969160e-02,
  6.8120160809641603037661024237800140e-04,
  2.0296358224704959863844721648437636e-05
};

///> constants to approximate the erfc function for doubles.
static const double K_ERFCWC_F64[19] JB_ALIGNED = {
  -3.6382310996720797851359441800814861e-14,
  5.9126949126438024241881443611486605e-12,
  5.6418958311227301915293621212983918e-01,
  6.3598477235724536750554320242202250e+00,
  3.7181364735581268496297440281312934e+01,
  1.3726250191485137648460000181010659e+02,
  3.4005444424960143520726358603822598e+02,
  5.6204031558086500764997336389876214e+02,
  5.7680275106946896024024425166175226e+02,
  2.8973230280471713604164936581040851e+02,
  5.7950275843277239994154362107923086e-05,
  1.1272536554546287769171249846918402e+01,
  6.6402254137638716276896126046772887e+01,
  2.4892769605698426054239068753824440e+02,
  6.3518229914533682498081965745526239e+02,
  1.1121954253127529010217685456691661e+03,
  1.2920652939776306418405829974326507e+03,
  9.0372831789398722557778230970431824e+02,
  2.8973290438600766459605944875366805e+02
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
  y.i &= JBM_BITS_SIGN_F64;
  y.i |= JBM_BITS_1_F64;
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
  y.i &= JBM_BITS_ABS_F64;
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
  ax.i |= sy.i & JBM_BITS_SIGN_F64;
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
jbm_mod_f64 (const double x,    ///< dividend (double).
             const double d)    ///< divisor (double).
{
  double r;
  r = floor (x / d);
  return (jbm_abs_f64 (r) > 1. / DBL_EPSILON) ? 0.5 * d : x - d * r;
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
  JBMF64 y;
  uint64_t exp;
  y.x = x;
  // check NaN or 0
  exp = y.i & JBM_BITS_ABS_F64;
  if (exp >= JBM_BITS_EXPONENT_F64 || !exp)
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
  *e = (int) exp - JBM_BIAS_F64;
  // mantissa in [0.5,1)
  y.i = (JBM_BIAS_F64 << 52u) | (y.i & 0x800fffffffffffffull);
  return y.x;
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
 * Function to calculate the well conditionated function cbrt(x) for x
 * \f$\in\left[\frac12\;,1\right]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_cbrtwc_f64 (const double x)
                ///< double number \f$\in\left[\frac12,\;1\right]\f$.
{
  return jbm_rational_11_6_f64 (x, K_CBRTWC_F64);
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
  double m;
  int e, e3, r;
  m = jbm_frexp_f64 (jbm_abs_f64 (x), &e);
  e3 = e / 3;
  r = e - 3 * e3;
  e = r >> 31;
  r += e & 3;
  e3 -= e & 1;
  m = jbm_ldexp_f64 (jbm_cbrtwc_f64 (m), e3);
  if (r & 1)
    m *= JBM_CBRT2_F64;
  if (r & 2)
    m *= JBM_CBRT4_F64;
  return jbm_copysign_f64 (m, x);
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
 * Function to calculate the well conditionated function log2(1+x) for x in
 * \f$[\sqrt{0.5}-1,\sqrt{2}-1]\f$ (double).
 *
 * \return function value (double).
 */
static inline double
jbm_log2wc_f64 (const double x) ///< double number.
{
  return x * jbm_rational_12_6_f64 (x, K_LOG2WC_F64);
}

/**
 * Function to calculate the function log2(x) using jbm_log2wc_f64 and
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
  if (x == 0.)
    return -INFINITY;
  if (!finite (x))
    return x;
  y = jbm_frexp_f64 (x, &e);
  if (y < M_SQRT1_2)
    {
      y *= 2.;
      e -= 1;
    }
  return jbm_log2wc_f64 (y - 1.) + (double) e;
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
  return jbm_exp2_f64 (e * jbm_log2_f64 (x));
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
  y = x - (double) q *M_PI_2;
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
  y = x - (double) q *M_PI_2;
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
  y = x - (double) q *M_PI_2;
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
 * [-1,1].
 *
 * \return function value (double).
 */
static inline double
jbm_atanwc_f64 (const double x)
                 ///< double number \f$\in\left[-1,1\right]\f$.
{
  return x * jbm_rational_11_5_f64 (x * x, K_ATANWC_F64);
}

/**
 * Function to calculate the function atan(x) using the jbm_atanwc_f64 function
 * (double).
 *
 * \return function value (in [-pi/2,pi/2]) (double).
 */
static inline double
jbm_atan_f64 (const double x)   ///< double number.
{
  double f, ax;
  ax = jbm_abs_f64 (x);
  if (ax > 1.)
    f = M_PI_2 - jbm_atanwc_f64 (1. / ax);
  else
    f = jbm_atanwc_f64 (ax);
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
    jbm_rational_18_10_f64 (1. / x, K_ERFCWC_F64) * x / jbm_exp_f64 (x * x);
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
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (double).
 *
 * \return integral value (double).
 */
static inline double
jbm_integral_f64 (double (*f) (double),
                  ///< pointer to the function to integrate.
                  const double x1,       ///< left limit of the interval.
                  const double x2)       ///< right limit of the interval.
{
  double k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  double k2;
  unsigned int i;
#endif
  dx = 0.5f *(x2 - x1);
  x = 0.5f *(x1 + x2);
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
