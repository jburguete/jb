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
 * \file math.h
 * \brief Header file with useful mathematical functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2024, Javier Burguete Tolosa.
 */
#ifndef JB_MATH__H
#define JB_MATH__H 1

#include "def.h"
#include <math.h>
#include <sys/param.h>
#if JBM_PRECISION > 5
#include <quadmath.h>
#define exp10q(x) (expq(x * M_LN10q))
#endif
#ifdef __SSE4_2__
#include <smmintrin.h>
#endif
#ifdef __AVX__
#include <immintrin.h>
#endif

#ifndef M_PIl
#define M_PIl M_PI              ///< high precision pi number.
#endif
#ifndef M_LN10l
#define M_LN10l M_LN10          ///< high precision ln(10) number.
#endif
#if !HAVE_EXP10
#define exp10(x) (exp(x * M_LN10))
#define exp10l(x) (expl(x * M_LN10l))
#endif
#if HAVE_ALIGNED_ALLOC
#define aligned_free free
#else
#define aligned_alloc(a, s) (g_aligned_alloc(s, 1, a))
#define aligned_free g_aligned_free
#endif

// Selecting the precision of the JBFLOAT and JBDOUBLE types and reading and
// writting formats
/**
 * \def JBFLOAT
 * \brief Real type with lower precision (controlled by JBM_PRECISION).
 * \def JBDOUBLE
 * \brief Real type with higher precision (controlled by JBM_PRECISION).
 * \def FRF
 * \brief Format to read JBFLOAT numbers.
 * \def FWF
 * \brief Format to write JBFLOAT numbers in scientific notation.
 * \def FPF
 * \brief Format to write JBFLOAT numbers in common notation.
 * \def FGF
 * \brief Format to write JBFLOAT numbers in simplified notation.
 * \def FRL
 * \brief Format to read JBDOUBLE numbers.
 * \def FWL
 * \brief Format to write JBDOUBLE numbers in scientific notation.
 * \def FPL
 * \brief Format to write JBDOUBLE numbers in common notation.
 * \def FGL
 * \brief Format to write JBDOUBLE numbers in simplified notation.
 * \def FWF2
 * \brief Format to write a JBFLOAT number in scientific notation with a space.
 * \def FG_LENGTH
 * \brief Maximum string length of JBDOUBLE numbers in simplified notation.
 * \def ACOS
 * \brief Low precision standard acos math function.
 * \def CBRT
 * \brief Low precision standard cbrt math function.
 * \def CEIL
 * \brief Low precision standard ceil math function.
 * \def COS
 * \brief Low precision standard cos math function.
 * \def EXP
 * \brief Low precision standard exp math function.
 * \def EXP10
 * \brief Low precision standard exp10 math function.
 * \def FABS
 * \brief Low precision standard fabs math function.
 * \def FLOOR
 * \brief Low precision standard floor math function.
 * \def FMAX
 * \brief Low precision standard fmax math function.
 * \def FMIN
 * \brief Low precision standard fmin math function.
 * \def HYPOT
 * \brief Low precision standard hypot math function.
 * \def LOG
 * \brief Low precision standard log math function.
 * \def LOG10
 * \brief Low precision standard log10 math function.
 * \def SQRT
 * \brief Low precision standard sqrt math function.
 * \def ACOSL
 * \brief High precision standard acos math function.
 * \def CBRTL
 * \brief High precision standard cbrt math function.
 * \def CEILL
 * \brief High precision standard ceil math function.
 * \def COSL
 * \brief High precision standard cos math function.
 * \def EXPL
 * \brief High precision standard exp math function.
 * \def EXP10L
 * \brief High precision standard exp10 math function.
 * \def FABSL
 * \brief High precision standard fabs math function.
 * \def FLOORL
 * \brief High precision standard floor math function.
 * \def FMAXL
 * \brief High precision standard fmax math function.
 * \def FMINL
 * \brief High precision standard fmin math function.
 * \def HYPOTL
 * \brief High precision standard hypot math function.
 * \def LOGL
 * \brief High precision standard log math function.
 * \def LOG10L
 * \brief High precision standard log10 math function.
 * \def SQRTL
 * \brief High precision standard sqrt math function.
 * \def JBM_EPSILON
 * \brief Low precision epsilon number.
 * \def JB_PI
 * \brief Low precision pi number.
 * \def JBM_EPSILONL
 * \brief High precision epsilon number.
 * \def JB_PIL
 * \brief High precision pi number.
 */
#if JBM_PRECISION == 1
#define JBM_LOW_PRECISION 1
#define JBM_HIGH_PRECISION 1
#elif JBM_PRECISION == 2
#define JBM_LOW_PRECISION 1
#define JBM_HIGH_PRECISION 2
#elif JBM_PRECISION == 3
#define JBM_LOW_PRECISION 2
#define JBM_HIGH_PRECISION 2
#elif JBM_PRECISION == 4
#define JBM_LOW_PRECISION 2
#define JBM_HIGH_PRECISION 3
#elif JBM_PRECISION == 5
#define JBM_LOW_PRECISION 3
#define JBM_HIGH_PRECISION 3
#elif JBM_PRECISION == 6
#define JBM_LOW_PRECISION 3
#define JBM_HIGH_PRECISION 4
#elif JBM_PRECISION == 7
#define JBM_LOW_PRECISION 4
#define JBM_HIGH_PRECISION 4
#else
#error "Unknown precision"
#endif
#if JBM_LOW_PRECISION == 1
#define JBFLOAT float
#define ACOS acos
#define CBRT cbrt
#define CEIL ceil
#define COS cos
#define EXP exp
#define EXP10 exp10
#define FABS fabs
#define FLOOR floor
#define FMAX fmax
#define FMIN fmin
#define HYPOT hypot
#define LOG log
#define LOG10 log10
#define SNPRINTF snprintf
#define SQRT sqrt
#define STRTOF strtof
#define FRF "%e"
#define FWF "%.6e"
#define FPF "%.7g"
#define FGF "%.5g"
#define JBM_EPSILON FLT_EPSILON
#define JB_PI M_PI
#elif JBM_LOW_PRECISION == 2
#define JBFLOAT double
#define ACOS acos
#define CBRT cbrt
#define CEIL ceil
#define COS cos
#define EXP exp
#define EXP10 exp10
#define FABS fabs
#define FLOOR floor
#define FMAX fmax
#define FMIN fmin
#define HYPOT hypot
#define LOG log
#define LOG10 log10
#define SNPRINTF snprintf
#define SQRT sqrt
#define STRTOF strtod
#define FRF "%le"
#define FWF "%.15le"
#define FPF "%.16lg"
#define FGF "%.5lg"
#define JBM_EPSILON DBL_EPSILON
#define JB_PI M_PI
#elif JBM_LOW_PRECISION == 3
#define JBFLOAT long double
#define ACOS acosl
#define CBRT cbrtl
#define CEIL ceill
#define COS cosl
#define EXP expl
#define EXP10 exp10l
#define FABS fabsl
#define FLOOR floorl
#define FMAX fmaxl
#define FMIN fminl
#define HYPOT hypotl
#define LOG logl
#define LOG10 log10l
#define SNPRINTF snprintf
#define SQRT sqrtl
#define STRTOF strtold
#define FRF "%Le"
#define FWF "%.18Le"
#define FPF "%.19Lg"
#define FGF "%.5Lg"
#define JBM_EPSILON LDBL_EPSILON
#define JB_PI M_PIl
#elif JBM_LOW_PRECISION == 4
#define JBFLOAT __float128
#define ACOS acosq
#define CBRT cbrtq
#define CEIL ceilq
#define COS cosq
#define EXP expq
#define EXP10 exp10q
#define FABS fabsq
#define FLOOR floorq
#define FMAX fmaxq
#define FMIN fminq
#define HYPOT hypotq
#define LOG logq
#define LOG10 log10q
#define SNPRINTF quadmath_snprintf
#define SQRT sqrtq
#define STRTOF strtoflt128
#define FRF "%Qe"
#define FWF "%.33Qe"
#define FPF "%.34Qg"
#define FGF "%.5Qg"
#define JBM_EPSILON FLT128_EPSILON
#define JB_PI M_PIq
#endif
#if JBM_HIGH_PRECISION == 1
#define JBDOUBLE float
#define ACOSL acos
#define CBRTL cbrt
#define CEILL ceil
#define COSL cos
#define EXPL exp
#define EXP10L exp10
#define FABSL fabs
#define FLOORL floor
#define FMAXL fmax
#define FMINL fmin
#define HYPOTL hypot
#define LOGL log
#define LOG10L log10
#define SNPRINTFL snprintf
#define SQRTL sqrt
#define STRTOD strtof
#define JBM_EPSILONL FLT_EPSILON
#define JB_PIL M_PI
#define FRL "%f"
#define FWL "%.6e"
#define FPL "%.7g"
#define FGL "%.5g"
#elif JBM_HIGH_PRECISION == 2
#define JBDOUBLE double
#define ACOSL acos
#define CBRTL cbrt
#define CEILL ceil
#define COSL cos
#define EXPL exp
#define EXP10L exp10
#define FABSL fabs
#define FLOORL floor
#define FMAXL fmax
#define FMINL fmin
#define HYPOTL hypot
#define LOGL log
#define LOG10L log10
#define SNPRINTFL snprintf
#define SQRTL sqrt
#define STRTOD strtod
#define JBM_EPSILONL DBL_EPSILON
#define JB_PIL M_PI
#define FRL "%lf"
#define FWL "%.15le"
#define FPL "%.16lg"
#define FGL "%.5lg"
#elif JBM_HIGH_PRECISION == 3
#define JBDOUBLE long double
#define ACOSL acosl
#define CBRTL cbrtl
#define CEILL ceill
#define COSL cosl
#define EXPL expl
#define EXP10L exp10l
#define FABSL fabsl
#define FLOORL floorl
#define FMAXL fmaxl
#define FMINL fminl
#define HYPOTL hypotl
#define LOGL logl
#define LOG10L log10l
#define SNPRINTFL snprintf
#define SQRTL sqrtl
#define STRTOD strtold
#define JBM_EPSILONL LDBL_EPSILON
#define JB_PIL M_PIl
#define FRL "%Lf"
#define FWL "%.18Le"
#define FPL "%.19Lg"
#define FGL "%.5Lg"
#elif JBM_HIGH_PRECISION == 4
#define JBDOUBLE __float128
#define ACOSL acosq
#define CBRTL cbrtq
#define CEILL ceilq
#define COSL cosq
#define EXPL expq
#define EXP10L exp10q
#define FABSL fabsq
#define FLOORL floorq
#define FMAXL fmaxq
#define FMINL fminq
#define HYPOTL hypotq
#define LOGL logq
#define LOG10L log10q
#define SNPRINTFL quadmath_snprintf
#define SQRTL sqrtq
#define STRTOD strtoflt128
#define JBM_EPSILONL FLT128_EPSILON
#define JB_PIL M_PIq
#define FRL "%Qf"
#define FWL "%.33Qe"
#define FPL "%.34Qg"
#define FGL "%.5Qg"
#endif
#define FG_LENGTH 12
#define FWF2 FWF " "

#define JBM_G 9.80665           ///< gravitational constant.
#define JBM_INDEX_SORT_FLASH_CLASS 4
///< number of elements of a class in the jbm_index_sort_flash() function.
#define JBM_INDEX_SORT_FLASH_MIN 40
///< minimum number of elements to select the jbm_index_sort_flash()
///< function as default sort method.
#define JBM_INDEX_SORT_MERGE_MIN 70
///< minimum number of elements to select the jbm_index_sort_merge()
///< function as default sort method.
#define JBM_MAX(a, b) (((a) > (b))? (a): (b))
///< macro calculating the maximum number.
#define JBM_MIN(a, b) (((a) < (b))? (a): (b))
///< macro calculating the minimum number.

/**
 * macro calculating the number with the lower module in the [a, b] interval
 * (int arguments).
 * \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 */
#define JBM_MODMIN(a, b) (((a) * (b) <= 0)? 0: (abs(a) < abs(b))? (a): (b))
/**
 * macro calculating the number with the lower module in the [a, b] interval 
 * (long int arguments).
 * \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 */
#define JBM_MODMINL(a, b) (((a) * (b) <= 0l)? 0l: (labs(a) < labs(b))? (a): (b))
/**
 * macro calculating the number with the lower module in the [a, b] interval 
 * (long long int arguments).
 * \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 */
#define JBM_MODMINLL(a, b) (((a) * (b) <= 0L)? 0L: \
  (llabs(a) < llabs(b))? (a): (b))
/**
 * macro calculating the number with the lower module in the [a, b] interval 
 * (JBFLOAT arguments).
 * \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 */
#if JBM_LOW_PRECISION == 1
#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.f)? 0.f: \
    (FABS(a) < FABS(b))? (a): (b))
#elif JBM_LOW_PRECISION == 2
#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.)? 0.: \
    (FABS(a) < FABS(b))? (a): (b))
#elif JBM_LOW_PRECISION == 3
#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.L)? 0.L: \
    (FABS(a) < FABS(b))? (a): (b))
#elif JBM_LOW_PRECISION == 4
#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.Q)? 0.Q: \
    (FABS(a) < FABS(b))? (a): (b))
#endif

/**
 * macro calculating the number with the lower module in the [a, b] interval 
 * (JBDOUBLE arguments).
 * \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 */
#if JBM_HIGH_PRECISION == 1
#define JBM_FMODMINL(a, b) (((a) * (b) <= 0.f)? 0.f: \
    (FABSL(a) < FABSL(b))? (a): (b))
#elif JBM_HIGH_PRECISION == 2
#define JBM_FMODMINL(a, b) (((a) * (b) <= 0.)? 0.: \
    (FABSL(a) < FABSL(b))? (a): (b))
#elif JBM_HIGH_PRECISION == 3
#define JBM_FMODMINL(a, b) (((a) * (b) <= 0.L)? 0.L: \
    (FABSL(a) < FABSL(b))? (a): (b))
#elif JBM_HIGH_PRECISION == 4
#define JBM_FMODMINL(a, b) (((a) * (b) <= 0.Q)? 0.Q: \
    (FABSL(a) < FABSL(b))? (a): (b))
#endif

#define JBM_SQR(x) ((x) * (x))  ///< macro calculating the square of a number.
#define JBM_DBL(x) ((x) + (x))  ///< macro calculating the double of a number.
#define JBM_EXTRAPOLATE(x, x1, x2, y1, y2) \
  ((y1) + (x - (x1)) * ((y2) - (y1)) / ((x2) - (x1)))
///< macro calculating a linear extrapolation.

///> enum to select the flux limiter type.
enum JBMFluxLimiterType
{
  JBM_FLUX_LIMITER_TYPE_TOTAL = 0,
  JBM_FLUX_LIMITER_TYPE_NULL = 1,
  JBM_FLUX_LIMITER_TYPE_CENTRED = 2,
  JBM_FLUX_LIMITER_TYPE_MINMOD = 3,
  JBM_FLUX_LIMITER_TYPE_SUPERBEE = 4,
  JBM_FLUX_LIMITER_TYPE_VAN_LEER = 5,
  JBM_FLUX_LIMITER_TYPE_VAN_ALBADA = 6,
  JBM_FLUX_LIMITER_TYPE_MINSUPER = 7,
  JBM_FLUX_LIMITER_TYPE_SUPERMIN = 8,
  JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL = 9,
  JBM_FLUX_LIMITER_TYPE_MEAN = 10
};

/**
 * struct to define arrays of JBFLOAT numbers.
 */
typedef struct
{
  JBFLOAT *x;                   ///< array of numbers.
  size_t size;                  ///< memory size of the array.
  unsigned int n;               ///< number of elements.
  unsigned int last;            ///< last element.
  unsigned int alloc;           ///< 1 if x is allocated, 0 otherwise.
} JBMFarray;

void jbm_index_sort_flash (JBFLOAT * x, unsigned int *ni, unsigned int n);

#if JBM_HIGH_PRECISION == JBM_LOW_PRECISION

#define jbm_index_sort_flashl jbm_index_sort_flash

#else

void jbm_index_sort_flashl (JBDOUBLE * x, unsigned int *ni, unsigned int n);

#endif

extern void matrix_print (JBFLOAT *, unsigned int, unsigned int);
extern void farray_print (JBMFarray *);

/**
 * Function to calculate the minimum of 2 int numbers.
 *
 * \return minimum int number.
 */
static inline int
jbm_min (const int a,                 ///< 1st int number.
         const int b)                 ///< 2nd int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to calculate the maximum of 2 int numbers.
 *
 * \return maximum int number.
 */
static inline int
jbm_max (const int a,                 ///< 1st int number.
         const int b)                 ///< 2nd int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the number with the lower module in the [a, b] interval
 * (int arguments).
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin int number.
 */
static inline int
jbm_modmin (const int a,              ///< 1st int number.
            const int b)              ///< 2nd int number.
{
  return JBM_MODMIN (a, b);
}

/**
 * Function to calculate the double of an int number.
 *
 * \return int double.
 */
static inline int
jbm_dbl (const int x)                 ///< unsigned int number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of an int number.
 *
 * \return int square.
 */
static inline int
jbm_sqr (const int x)                 ///< int number.
{
  return JBM_SQR (x);
}

/**
 * Function to interchange 2 int numbers.
 */
static inline void
jbm_change (int *restrict a,    ///< 1st int number pointer. 
            int *restrict b)    ///< 1st int number pointer. 
{
  int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the minimum of 2 unsigned int numbers.
 *
 * \return minimum unsigned int number.
 */
static inline unsigned int
jbm_minu (const unsigned int a,       ///< 1st unsigned int number.
          const unsigned int b)       ///< 2nd unsigned int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to calculate the maximum of 2 unsigned int numbers.
 *
 * \return maximum unsigned int number.
 */
static inline unsigned int
jbm_maxu (const unsigned int a,       ///< 1st unsigned int number.
          const unsigned int b)       ///< 2nd unsigned int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the double of an unsigned int number.
 *
 * \return unsigned int double.
 */
static inline unsigned int
jbm_dblu (const unsigned int x)       ///< unsigned int number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of an unsigned int number.
 *
 * \return unsigned int square.
 */
static inline unsigned int
jbm_sqru (const unsigned int x)       ///< unsigned int number.
{
  return JBM_SQR (x);
}

/**
 * Function to interchange 2 unsigned int numbers.
 */
static inline void
jbm_changeu (unsigned int *restrict a,
             ///< 1st unsigned int number pointer. 
             unsigned int *restrict b)
             ///< 1st unsigned int number pointer. 
{
  unsigned int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the maximum of 2 long int numbers.
 *
 * \return maximum long int number.
 */
static inline long int
jbm_maxl (const long int a,           ///< 1st long int number.
          const long int b)           ///< 2nd long int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the minimum of 2 long int numbers.
 *
 * \return minimum long int number.
 */
static inline long int
jbm_minl (const long int a,           ///< 1st long int number.
          const long int b)           ///< 2nd long int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to calculate the number with the lower module in the [a, b] interval
 * (long int arguments).
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin long int number.
 */
static inline long int
jbm_modminl (const long int a,        ///< 1st long int number.
             const long int b)        ///< 2nd long int number.
{
  return (int) JBM_MODMINL (a, b);
}

/**
 * Function to interchange 2 long int numbers.
 */
static inline void
jbm_changel (long int *restrict a,      ///< 1st long int number pointer. 
             long int *restrict b)      ///< 1st long int number pointer. 
{
  long int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a long int number.
 *
 * \return long int square.
 */
static inline long int
jbm_sqrl (const long int x)           ///< long int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a long int number.
 *
 * \return long int double.
 */
static inline long int
jbm_dbll (const long int x)           ///< long int number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the maximum of 2 unsigned long int numbers.
 *
 * \return maximum unsigned long int number.
 */
static inline unsigned long int
jbm_maxul (const unsigned long int a, ///< 1st unsigned long int number.
           const unsigned long int b) ///< 2nd unsigned long int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the minimum of 2 unsigned long int numbers.
 *
 * \return minimum unsigned long int number.
 */
static inline unsigned long int
jbm_minul (const unsigned long int a, ///< 1st unsigned long int number.
           const unsigned long int b) ///< 2nd unsigned long int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to interchange 2 unsigned long int numbers.
 */
static inline void
jbm_changeul (unsigned long int *restrict a,
              ///< 1st unsigned long int number pointer.
              unsigned long int *restrict b)
              ///< 1st unsigned long int number pointer.
{
  unsigned long int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a unsigned long int number.
 *
 * \return unsigned long int double.
 */
static inline unsigned long int
jbm_dblul (const unsigned long int x) ///< unsigned long int number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a unsigned long int number.
 *
 * \return unsigned long int square.
 */
static inline unsigned long int
jbm_sqrul (const unsigned long int x) ///< unsigned long int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the maximum of 2 long long int numbers.
 *
 * \return maximum long long int number.
 */
static inline long long int
jbm_maxll (const long long int a,     ///< 1st long long int number.
           const long long int b)     ///< 2nd long long int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the minimum of 2 long long int numbers.
 *
 * \return minimum long long int number.
 */
static inline long long int
jbm_minll (const long long int a,     ///< 1st long long int number.
           const long long int b)     ///< 2nd long long int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to calculate the number with the lower module in the [a, b] interval
 * (long long int arguments).
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin long long int number.
 */
static inline long long int
jbm_modminll (const long long int a,  ///< 1st long long int number.
              const long long int b)  ///< 2nd long long int number.
{
  return JBM_MODMINLL (a, b);
}

/**
 * Function to interchange 2 long long int numbers.
 */
static inline void
jbm_changell (long long int *restrict a,
              ///< 1st long long int number pointer. 
              long long int *restrict b)
              ///< 1st long long int number pointer. 
{
  long long int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a long long int number.
 *
 * \return long long int square.
 */
static inline long long int
jbm_sqrll (const long long int x)     ///< long long int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a long long int number.
 *
 * \return long long int double.
 */
static inline long long int
jbm_dblll (const long long int x)     ///< long long int number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the maximum of 2 unsigned long long int numbers.
 *
 * \return maximum unsigned long long int number.
 */
static inline unsigned long long int
jbm_maxull (const unsigned long long int a,   ///< 1st unsigned long long int number.
            const unsigned long long int b)   ///< 2nd unsigned long long int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the minimum of 2 unsigned long long int numbers.
 *
 * \return minimum unsigned long long int number.
 */
static inline unsigned long long int
jbm_minull (const unsigned long long int a,   ///< 1st unsigned long long int number.
            const unsigned long long int b)   ///< 2nd unsigned long long int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to interchange 2 unsigned long long int numbers.
 */
static inline void
jbm_changeull (unsigned long long int *restrict a,
               ///< 1st unsigned long long int number pointer. 
               unsigned long long int *restrict b)
               ///< 1st unsigned long long int number pointer. 
{
  unsigned long long int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a unsigned long long int number.
 *
 * \return unsigned long long int square.
 */
static inline unsigned long long int
jbm_sqrull (const unsigned long long int x)   ///< unsigned long long int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a unsigned long long int number.
 *
 * \return unsigned long long int double.
 */
static inline unsigned long long int
jbm_dblull (const unsigned long long int x)   ///< unsigned long long int number.
{
  return JBM_DBL (x);
}

/**
 * Function to check small JBFLOAT numbers.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline int
jbm_small (const JBFLOAT x)           ///< JBFLOAT number.
{
  if (FABS (x) < JBM_EPSILON)
    return 1;
  return 0;
}

/**
 * Function to calculate the number with the lower module in the [a, b]
 * interval (JBFLOAT arguments).
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin JBFLOAT number.
 */
static inline JBFLOAT
jbm_fmodmin (const JBFLOAT a,         ///< 1st JBFLOAT number.
             const JBFLOAT b)         ///< 2nd JBFLOAT number.
{
  return JBM_FMODMIN (a, b);
}

/**
 * Function to calculate the double of a JBFLOAT number.
 *
 * \return JBFLOAT double.
 */
static inline JBFLOAT
jbm_fdbl (const JBFLOAT x)            ///< JBFLOAT number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a JBFLOAT number.
 *
 * \return JBFLOAT square.
 */
static inline JBFLOAT
jbm_fsqr (const JBFLOAT x)            ///< JBFLOAT number.
{
  return JBM_SQR (x);
}

/**
 * Function to interchange 2 JBFLOAT numbers.
 */
static inline void
jbm_fchange (JBFLOAT *restrict a,       ///< 1st JBFLOAT number pointer.
             JBFLOAT *restrict b)       ///< 2nd JBFLOAT number pointer.
{
  JBFLOAT c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to perform an extrapolation between 2 2D points (JBFLOAT).
 *
 * \return y-coordinate of the extrapolated point.
 */
static inline JBFLOAT
jbm_extrapolate (const JBFLOAT x,     ///< x-coordinate of the extrapolated point.
                 const JBFLOAT x1,    ///< x-coordinate of the 1st point.
                 const JBFLOAT x2,    ///< x-coordinate of the 2nd point.
                 const JBFLOAT y1,    ///< y-coordinate of the 1st point.
                 const JBFLOAT y2)    ///< y-coordinate of the 2nd point.
{
  return JBM_EXTRAPOLATE (x, x1, x2, y1, y2);
}

/**
 * Function to perform an interpolation (the result is bounded) between 2 2D
 * points (JBFLOAT).
 *
 * \return y-coordinate of the interpolated point.
 */
static inline JBFLOAT
jbm_interpolate (const JBFLOAT x,     ///< x-coordinate of the interpolated point.
                 const JBFLOAT x1,    ///< x-coordinate of the 1st point.
                 const JBFLOAT x2,    ///< x-coordinate of the 2nd point.
                 const JBFLOAT y1,    ///< y-coordinate of the 1st point.
                 const JBFLOAT y2)    ///< y-coordinate of the 2nd point.
{
  if (x <= x1)
    return y1;
  if (x >= x2)
    return y2;
  return jbm_extrapolate (x, x1, x2, y1, y2);
}

/**
 * Function to calculate the length of a 2D segment (JBFLOAT).
 *
 * \return segment length.
 */
static inline JBFLOAT
jbm_v2_length (const JBFLOAT x1,
///< x-coordinate of the 1st point defining the segment.
               const JBFLOAT y1,
///< y-coordinate of the 1st point defining the segment.
               const JBFLOAT x2,
///< x-coordinate of the 2nd point defining the segment.
               const JBFLOAT y2)
///< y-coordinate of the 2nd point defining the segment.
{
  return HYPOT (x2 - x1, y2 - y1);
}

/**
 * Function to calculate the length of a 3D segment (JBFLOAT).
 *
 * \return segment length.
 */
static inline JBFLOAT
jbm_v3_length (const JBFLOAT x1,
///< x-coordinate of the 1st point defining the segment.
               const JBFLOAT y1,
///< y-coordinate of the 1st point defining the segment.
               const JBFLOAT z1,
///< z-coordinate of the 1st point defining the segment.
               const JBFLOAT x2,
///< x-coordinate of the 2nd point defining the segment.
               const JBFLOAT y2,
///< y-coordinate of the 2nd point defining the segment.
               const JBFLOAT z2)
///< z-coordinate of the 2nd point defining the segment.
{
  return HYPOT (HYPOT (x2 - x1, y2 - y1), z2 - z1);
}

/**
 * Function to calculate a 1st order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_1 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * p[1];
}

/**
 * Function to calculate a 2nd order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_2 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_1 (x, p + 1);
}

/**
 * Function to calculate a 3rd order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_3 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_2 (x, p + 1);
}

/**
 * Function to calculate a 4th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_4 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_3 (x, p + 1);
}

/**
 * Function to calculate a 5th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_5 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_4 (x, p + 1);
}

/**
 * Function to calculate a 6th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_6 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_5 (x, p + 1);
}

/**
 * Function to calculate a 7th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_7 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_6 (x, p + 1);
}

/**
 * Function to calculate a 8th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_8 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_7 (x, p + 1);
}

/**
 * Function to calculate a 9th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_9 (const JBFLOAT x,    ///< variable.
                  const JBFLOAT *p)   ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_8 (x, p + 1);
}

/**
 * Function to calculate a 10th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_10 (const JBFLOAT x,   ///< variable.
                   const JBFLOAT *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_9 (x, p + 1);
}

/**
 * Function to calculate a 11th order polynomial (JBFLOAT).
 *
 * \return polynomial value.
 */
static inline JBFLOAT
jbm_polynomial_11 (const JBFLOAT x,   ///< variable.
                   const JBFLOAT *p)  ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_10 (x, p + 1);
}

/**
 * Function to calculate the solution of a reduced quadratic equation in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form \f$x^2+a\,x+b=0\f$
 * (JBFLOAT).
 *
 * \return solution value.
 */
static inline JBFLOAT
jbm_solve_quadratic_reduced (JBFLOAT a,
                             ///< 1st order coefficient of the equation.
                             JBFLOAT b,
                             ///< 0th order coefficient of the equation.
                             const JBFLOAT x1,
                             ///< left limit of the solution interval.
                             const JBFLOAT x2)
                             ///< right limit of the solution interval.
{
  JBFLOAT k;
#if JBM_LOW_PRECISION == 1
  a *= -0.5f;
#elif JBM_LOW_PRECISION == 2
  a *= -0.5;
#elif JBM_LOW_PRECISION == 3
  a *= -0.5L;
#elif JBM_LOW_PRECISION == 4
  a *= -0.5Q;
#endif
  b = SQRT (a * a - b);
  k = a + b;
  if (k < x1 || k > x2)
    k = a - b;
  return k;
}

/**
 * Function to calculate the solution of a quadratic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$
 * (JBFLOAT).
 *
 * \return solution value.
 */
static inline JBFLOAT
jbm_solve_quadratic (const JBFLOAT a,
                     ///< 2nd order coefficient of the equation.
                     const JBFLOAT b,
                     ///< 1st order coefficient of the equation.
                     const JBFLOAT c,
                     ///< 0th order coefficient of the equation.
                     const JBFLOAT x1,
                     ///< left limit of the solution interval.
                     const JBFLOAT x2)
                     ///< right limit of the solution interval.
{
  if (jbm_small (a))
    return -c / b;
  return jbm_solve_quadratic_reduced (b / a, c / a, x1, x2);
}

/**
 * Function to calculate the solution of a reduced cubic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$x^3+a\,x^2+b\,x+c=0\f$
 * (JBFLOAT).
 *
 * \return solution value.
 */
static inline JBFLOAT
jbm_solve_cubic_reduced (JBFLOAT a,
                         ///< 2nd order coefficient of the equation.
                         const JBFLOAT b,
                         ///< 1st order coefficient of the equation.
                         const JBFLOAT c,
                         ///< 0th order coefficient of the equation.
                         const JBFLOAT x1,
                         ///< left limit of the solution interval.
                         const JBFLOAT x2)
                         ///< right limit of the solution interval.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c2 = 2.f, c3 = 3.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c2 = 2., c3 = 3.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c2 = 2.L, c3 = 3.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c2 = 2.Q, c3 = 3.Q;
#endif
  JBFLOAT k0, k1, k2;
  a /= c3;
  k0 = a * a;
  k1 = b / c3 - k0;
  k0 = (b * a - c) / c2 - a * k0;
  k2 = k1 * k1 * k1 + k0 * k0;
  if (k2 < c0)
    {
      k1 = SQRT (-k1);
      k0 = ACOS (k0 / (k1 * k1 * k1)) / c3;
      k1 *= c2;
      k2 = k1 * COS (k0) - a;
      if (k2 < x1 || k2 > x2)
        {
          k2 = k1 * COS (k0 + c2 * JB_PI / c3) - a;
          if (k2 < x1 || k2 > x2)
            k2 = k1 * COS (k0 - c2 * JB_PI / c3) - a;
        }
    }
  else
    {
      k1 = SQRT (k2);
      k2 = k0 + k1;
      k2 = CBRT (k2);
      k0 -= k1;
      k2 += CBRT (k0) - a;
    }
  return k2;
}

/**
 * Function to calculate the solution of a cubic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^3+b\,x^2+c\,x+d=0\f$
 * (JBFLOAT).
 *
 * \return solution value.
 */
static inline JBFLOAT
jbm_solve_cubic (const JBFLOAT a,
                 ///< 3rd order coefficient of the equation.
                 const JBFLOAT b,
                 ///< 2nd order coefficient of the equation.
                 const JBFLOAT c,
                 ///< 1st order coefficient of the equation.
                 const JBFLOAT d,
                 ///< 0th order coefficient of the equation.
                 const JBFLOAT x1,
                 ///< left limit of the solution interval.
                 const JBFLOAT x2)
                 ///< right limit of the solution interval.
{
  if (jbm_small (a))
    return jbm_solve_quadratic (b, c, d, x1, x2);
  return jbm_solve_cubic_reduced (b / a, c / a, d / a, x1, x2);
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_total (const JBFLOAT d1 __attribute__((unused)),
///< 1st flux limiter function parameter.
                        const JBFLOAT d2 __attribute__((unused)))
///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  return c0;
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_null (const JBFLOAT d1 __attribute__((unused)),
                       ///< 1st flux limiter function parameter.
                       const JBFLOAT d2 __attribute__((unused)))
///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c1 = 1.Q;
#endif
  return c1;
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_centred (const JBFLOAT d1,
                          ///< 1st flux limiter function parameter.
                          const JBFLOAT d2)
                          ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  if (jbm_small (d2))
    return c0;
  return d1 / d2;
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_superbee (const JBFLOAT d1,
                           ///< 1st flux limiter function parameter.
                           const JBFLOAT d2)
                           ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f, c2 = 2.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1., c2 = 2.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L, c2 = 2.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q, c2 = 2.Q;
#endif
  JBFLOAT r;
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  r = d1 / d2;
  return FMAX (FMIN (r + r, c1), FMIN (r, c2));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_minmod (const JBFLOAT d1,
                         ///< 1st flux limiter function parameter.
                         const JBFLOAT d2)
                         ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q;
#endif
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  return FMIN (d1 / d2, c1);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_VanLeer (const JBFLOAT d1,
                          ///< 1st flux limiter function parameter.
                          const JBFLOAT d2)
                          ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q;
#endif
  JBFLOAT r, k;
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  r = d1 / d2;
  k = FABS (r);
  return (r + k) / (c1 + k);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_VanAlbada (const JBFLOAT d1,
                            ///< 1st flux limiter function parameter.
                            const JBFLOAT d2)
                            ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q;
#endif
  JBFLOAT r, k;
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  r = d1 / d2;
  k = r * r;
  return (r + k) / (c1 + k);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_minsuper (const JBFLOAT d1,
                           ///< 1st flux limiter function parameter.
                           const JBFLOAT d2)
                           ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c2 = 2.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c2 = 2.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c2 = 2.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c2 = 2.Q;
#endif
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  return FMIN (d1 / d2, c2);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_supermin (const JBFLOAT d1,
                           ///< 1st flux limiter function parameter.
                           const JBFLOAT d2)
                           ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q;
#endif
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  return FMIN (jbm_fdbl (d1 / d2), c1);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f\[\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f\] (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_monotonized_central (const JBFLOAT d1,
                                      ///< 1st flux limiter function parameter.
                                      const JBFLOAT d2)
                                      ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f, c2 = 2.f, c3 = 3.f, c05 = 0.5f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1., c2 = 2., c3 = 3., c05 = 0.5;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L, c2 = 2.L, c3 = 3.L, c05 = 0.5L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q, c2 = 2.Q, c3 = 3.Q, c05 = 0.5Q;
#endif
  JBFLOAT k;
  if (d1 * d2 <= JBM_EPSILON)
    return c0;
  k = d1 / d2;
  if (k >= c3)
    return c2;
  if (k <= c1 / c3)
    return k + k;
  return c05 * (k + c1);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_mean (const JBFLOAT d1,
                       ///< 1st flux limiter function parameter.
                       const JBFLOAT d2)
                       ///< 2nd flux limiter function parameter.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f, c05 = 0.5f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1., c05 = 0.5;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L, c05 = 0.5L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q, c05 = 0.5Q;
#endif
  if (jbm_small (d2))
    return c0;
  return c05 * (d1 / d2 + c1);
}

/**
 * Function to do a flux limiter function (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter (const JBFLOAT d1,
                  ///< 1st flux limiter function parameter.
                  const JBFLOAT d2,
                  ///< 2nd flux limiter function parameter.
                  unsigned int type)
                  ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central (d1, d2);
    }
  return jbm_flux_limiter_mean (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (JBFLOAT).
 *
 * The coefficients are:\n
 * - 1 point (2nd order):\n
 * \f$a_0=2,\quad b_0=0\f$\n
 * - 3 points (6th order):\n
 * \f$a_0=\frac{8}{9},\quad b_0=0,\f$\n
 * \f$a_1=\frac{5}{9},\quad b_1=\sqrt{\frac{3}{5}},\f$\n
 * - 5 points (10th order):\n
 * \f$a_0=\frac{128}{225},\quad b_0=0,\f$\n
 * \f$a_1=\frac{15\,\sqrt{70}-21}{50\,\sqrt{70}-200},\quad
 * b_1=\sqrt{\frac{35-\sqrt{280}}{63}},\f$\n
 * \f$a_2=\frac{15\,\sqrt{70}+21}{50\,\sqrt{70}+200},\quad
 * b_2=\sqrt{\frac{35+\sqrt{280}}{63}},\f$\n
 * - 7 points (14th order):\n
 * \f\[b_0=0,\f\]
 * \f\[b_1=\sqrt{\frac{7}{13}-\sqrt{\frac{336}{1859}}\,\cos\left[\frac{1}{3}
 *   \,acos\left(\sqrt{\frac{539}{83349}}\right)\right]},\f\]
 * \f\[b_2=\sqrt{\frac{7}{13}+\sqrt{\frac{336}{1859}}\,\cos\left\{\frac{1}{3}
 *   \,acos\left[\frac{1}{3}\,\left(\pi+\sqrt{\frac{539}{83349}}\right)\right]
 *   \right\}},\f\]
 * \f\[b_3=\sqrt{\frac{7}{13}+\sqrt{\frac{336}{1859}}\,\cos\left\{\frac{1}{3}
 *   \,acos\left[\frac{1}{3}\,\left(\pi-\sqrt{\frac{539}{83349}}\right)\right]
 *   \right\}},\f\]
 * \f\[a_3=\frac{1}{b_3^2}\,\frac{\frac{1}{7}-y_1\,\frac{1}{5}
 *   -y_2\,\left(\frac{1}{5}-y_1\,\frac{1}{3}\right)}
 *   {\left(y_3-y_2\right)\,\left(y_3-y_1\right)},\f\]
 * \f\[a_2=\frac{1}{b_2^2}\,\frac{\frac{1}{5}-y_1\,\frac{1}{3}
 *   -b_3\,\left(y_3-y_1\right)}{y_2-y_1},\f\]
 * \f\[a_1=\frac{1}{b_1^2}\,\left(\frac{1}{3}-b_2-b_3\right),\f\]
 * \f\[a_0=0\f\]
 *
 * \return integral value.
 */
static inline JBFLOAT
jbm_integral (JBFLOAT (*f) (JBFLOAT),
              ///< pointer to the function to integrate.
              const JBFLOAT x1,       ///< left limit of the interval.
              const JBFLOAT x2)       ///< right limit of the interval.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c05 = 0.5f;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2.f };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8.f / 9.f, 5.f / 9.f }, b[2] = { 0.f, 7.7459667e-1f };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128.f / 225.f,
    4.7862867e-1f,
    2.3692689e-1f
  }, b[3] = {
    0.f,
    5.3846931e-1f,
    9.0617985e-1f
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.1795918e-1f,
    3.8183005e-1f,
    2.7970539e-1f,
    1.2948497e-1f
  }, b[4] = {
    0.f,
    4.0584515e-1f,
    7.4153119e-1f,
    9.4910791e-1f
  };
#endif
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c05 = 0.5;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2. };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8. / 9., 5. / 9. },
    b[2] = { 0., 7.745966692414834e-1 };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128. / 225.,
    4.786286704993665e-1,
    2.369268850561891e-1
  }, b[3] = {
    0.,
    5.384693101056831e-1,
    9.061798459386640e-1
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.179591836734694e-1,
    3.818300505051189e-1,
    2.797053914892767e-1,
    1.294849661688697e-1
  }, b[4] = {
    0.,
    4.058451513773972e-1,
    7.415311855993944e-1,
    9.491079123427585e-1
  };
#endif
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c05 = 0.5L;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2.L };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8.L / 9.L, 5.L / 9.L },
    b[2] = { 0.L, 7.7459666924148340428e-1L };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128.L / 225.L,
    4.7862867049936646804e-1L,
    2.3692688505618908751e-1L
  }, b[3] = {
    0.L,
    5.3846931010568309104e-1L,
    9.0617984593866399280e-1L
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.1795918367346938776e-1L,
    3.8183005050511894495e-1L,
    2.7970539148927666790e-1L,
    1.2948496616886969327e-1L
  }, b[4] = {
    0.L,
    4.0584515137739716691e-1L,
    7.4153118559939443986e-1L,
    9.4910791234275852453e-1L
  };
#endif
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c05 = 0.5Q;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2.Q };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8.Q / 9.Q, 5.Q / 9.Q },
    b[2] = { 0.Q, 7.7459666924148340427791481488384306e-1Q };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128.Q / 225.Q,
    4.7862867049936646804129151483563819e-1Q,
    2.3692688505618908751426404071991736e-1Q
  }, b[3] = {
    0.Q,
    5.3846931010568309103631442070020880e-1Q,
    9.0617984593866399279762687829939297e-1Q
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.1795918367346938775510204081632653e-1Q,
    3.8183005050511894495036977548897513e-1Q,
    2.7970539148927666790146777142377958e-1Q,
    1.2948496616886969327061143267908202e-1Q
  }, b[4] = {
    0.Q,
    4.0584515137739716690660641207696146e-1Q,
    7.4153118559939443986386477328078841e-1Q,
    9.4910791234275852452618968404785126e-1Q
  };
#endif
#endif
  JBFLOAT k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  JBFLOAT k2;
  unsigned int i;
#endif
  dx = c05 * (x2 - x1);
  x = c05 * (x1 + x2);
  k = a[0] * f (x);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = b[i] * dx;
      k += a[i] * (f (x - k2) + f (x + k2));
    }
#endif
  k *= dx;
  return k;
}

/**
 * Function to check small JBDOUBLE numbers.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline int
jbm_smalll (const JBDOUBLE x)         ///< JBDOUBLE number.
{
  if (FABSL (x) < JBM_EPSILONL)
    return 1;
  return 0;
}

/**
 * Function to calculate the number with the lower module in the [a, b]
 * interval (JBDOUBLE arguments).
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin JBDOUBLE number.
 */
static inline JBDOUBLE
jbm_fmodminl (const JBDOUBLE a,       ///< 1st JBDOUBLE number.
              const JBDOUBLE b)       ///< 2nd JBDOUBLE number.
{
  return JBM_FMODMINL (a, b);
}

/**
 * Function to calculate the double of a JBDOUBLE number.
 *
 * \return JBDOUBLE double.
 */
static inline JBDOUBLE
jbm_fdbll (const JBDOUBLE x)          ///< JBDOUBLE number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the square of a JBDOUBLE number.
 *
 * \return JBDOUBLE square.
 */
static inline JBDOUBLE
jbm_fsqrl (const JBDOUBLE x)          ///< JBDOUBLE number.
{
  return JBM_SQR (x);
}

/**
 * Function to interchange 2 JBDOUBLE numbers.
 */
static inline void
jbm_fchangel (JBDOUBLE *restrict a,     ///< 1st JBDOUBLE number pointer.
              JBDOUBLE *restrict b)     ///< 2nd JBDOUBLE number pointer.
{
  JBDOUBLE c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to perform an extrapolation between 2 2D points (JBDOUBLE).
 *
 * \return y-coordinate of the extrapolated point.
 */
static inline JBDOUBLE
jbm_extrapolatel (const JBDOUBLE x,   ///< x-coordinate of the extrapolated point.
                  const JBDOUBLE x1,  ///< x-coordinate of the 1st point.
                  const JBDOUBLE x2,  ///< x-coordinate of the 2nd point.
                  const JBDOUBLE y1,  ///< y-coordinate of the 1st point.
                  const JBDOUBLE y2)  ///< y-coordinate of the 2nd point.
{
  return JBM_EXTRAPOLATE (x, x1, x2, y1, y2);
}

/**
 * Function to perform an interpolation (the result is bounded) between 2 2D
 * points (JBDOUBLE).
 *
 * \return y-coordinate of the interpolated point.
 */
static inline JBDOUBLE
jbm_interpolatel (const JBDOUBLE x,   ///< x-coordinate of the interpolated point.
                  const JBDOUBLE x1,  ///< x-coordinate of the 1st point.
                  const JBDOUBLE x2,  ///< x-coordinate of the 2nd point.
                  const JBDOUBLE y1,  ///< y-coordinate of the 1st point.
                  const JBDOUBLE y2)  ///< y-coordinate of the 2nd point.
{
  if (x <= x1)
    return y1;
  if (x >= x2)
    return y2;
  return jbm_extrapolatel (x, x1, x2, y1, y2);
}

/**
 * Function to calculate the length of a 2D segment (JBDOUBLE).
 *
 * \return segment length.
 */
static inline JBDOUBLE
jbm_v2_lengthl (const JBDOUBLE x1,
///< x-coordinate of the 1st point defining the segment.
                const JBDOUBLE y1,
///< y-coordinate of the 1st point defining the segment.
                const JBDOUBLE x2,
///< x-coordinate of the 2nd point defining the segment.
                const JBDOUBLE y2)
///< y-coordinate of the 2nd point defining the segment.
{
  return HYPOTL (x2 - x1, y2 - y1);
}

/**
 * Function to calculate the length of a 3D segment (JBDOUBLE).
 *
 * \return segment length.
 */
static inline JBDOUBLE
jbm_v3_lengthl (const JBDOUBLE x1,
///< x-coordinate of the 1st point defining the segment.
                const JBDOUBLE y1,
///< y-coordinate of the 1st point defining the segment.
                const JBDOUBLE z1,
///< z-coordinate of the 1st point defining the segment.
                const JBDOUBLE x2,
///< x-coordinate of the 2nd point defining the segment.
                const JBDOUBLE y2,
///< y-coordinate of the 2nd point defining the segment.
                const JBDOUBLE z2)
///< z-coordinate of the 2nd point defining the segment.
{
  return HYPOTL (HYPOTL (x2 - x1, y2 - y1), z2 - z1);
}

/**
 * Function to calculate a 1st order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_1l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * p[1];
}

/**
 * Function to calculate a 2nd order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_2l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_1l (x, p + 1);
}

/**
 * Function to calculate a 3rd order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_3l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_2l (x, p + 1);
}

/**
 * Function to calculate a 4th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_4l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_3l (x, p + 1);
}

/**
 * Function to calculate a 5th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_5l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_4l (x, p + 1);
}

/**
 * Function to calculate a 6th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_6l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_5l (x, p + 1);
}

/**
 * Function to calculate a 7th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_7l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_6l (x, p + 1);
}

/**
 * Function to calculate a 8th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_8l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_7l (x, p + 1);
}

/**
 * Function to calculate a 9th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_9l (const JBDOUBLE x,  ///< variable.
                   const JBDOUBLE *p) ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_8l (x, p + 1);
}

/**
 * Function to calculate a 10th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_10l (const JBDOUBLE x, ///< variable.
                    const JBDOUBLE *p)        ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_9l (x, p + 1);
}

/**
 * Function to calculate a 11th order polynomial (JBDOUBLE).
 *
 * \return polynomial value.
 */
static inline JBDOUBLE
jbm_polynomial_11l (const JBDOUBLE x, ///< variable.
                    const JBDOUBLE *p)        ///< array of coefficients.
{
  return p[0] + x * jbm_polynomial_10l (x, p + 1);
}

/**
 * Function to calculate the solution of a reduced quadratic equation in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form \f$x^2+a\,x+b=0\f$
 * (JBDOUBLE).
 *
 * \return solution value.
 */
static inline JBDOUBLE
jbm_solve_quadratic_reducedl (JBDOUBLE a,
                              ///< 1st order coefficient of the equation.
                              JBDOUBLE b,
                              ///< 0th order coefficient of the equation.
                              const JBDOUBLE x1,
                              ///< left limit of the solution interval.
                              const JBDOUBLE x2)
                              ///< right limit of the solution interval.
{
  JBDOUBLE k;
#if JBM_HIGH_PRECISION == 1
  a *= -0.5f;
#elif JBM_HIGH_PRECISION == 2
  a *= -0.5;
#elif JBM_HIGH_PRECISION == 3
  a *= -0.5L;
#elif JBM_HIGH_PRECISION == 4
  a *= -0.5Q;
#endif
  b = SQRTL (a * a - b);
  k = a + b;
  if (k < x1 || k > x2)
    k = a - b;
  return k;
}

/**
 * Function to calculate the solution of a quadratic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$
 * (JBDOUBLE).
 *
 * \return solution value.
 */
static inline JBDOUBLE
jbm_solve_quadraticl (const JBDOUBLE a,
                      ///< 2nd order coefficient of the equation.
                      const JBDOUBLE b,
                      ///< 1st order coefficient of the equation.
                      const JBDOUBLE c,
                      ///< 0th order coefficient of the equation.
                      const JBDOUBLE x1,
                      ///< left limit of the solution interval.
                      const JBDOUBLE x2)
                     ///< right limit of the solution interval.
{
  if (jbm_smalll (a))
    return -c / b;
  return jbm_solve_quadratic_reducedl (b / a, c / a, x1, x2);
}

/**
 * Function to calculate the solution of a reduced cubic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$x^3+a\,x^2+b\,x+c=0\f$
 * (JBDOUBLE).
 *
 * \return solution value.
 */
static inline JBDOUBLE
jbm_solve_cubic_reducedl (JBDOUBLE a,
                          ///< 2nd order coefficient of the equation.
                          const JBDOUBLE b,
                          ///< 1st order coefficient of the equation.
                          const JBDOUBLE c,
                          ///< 0th order coefficient of the equation.
                          const JBDOUBLE x1,
                          ///< left limit of the solution interval.
                          const JBDOUBLE x2)
                          ///< right limit of the solution interval.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c2 = 2.f, c3 = 3.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c2 = 2., c3 = 3.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c2 = 2.L, c3 = 3.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c2 = 2.Q, c3 = 3.Q;
#endif
  JBDOUBLE k0, k1, k2;
  a /= c3;
  k0 = a * a;
  k1 = b / c3 - k0;
  k0 = (b * a - c) / c2 - a * k0;
  k2 = k1 * k1 * k1 + k0 * k0;
  if (k2 < c0)
    {
      k1 = SQRTL (-k1);
      k0 = ACOSL (k0 / (k1 * k1 * k1)) / c3;
      k1 *= c2;
      k2 = k1 * COSL (k0) - a;
      if (k2 < x1 || k2 > x2)
        {
          k2 = k1 * COSL (k0 + c2 * JB_PI / c3) - a;
          if (k2 < x1 || k2 > x2)
            k2 = k1 * COSL (k0 - c2 * JB_PI / c3) - a;
        }
    }
  else
    {
      k1 = SQRTL (k2);
      k2 = k0 + k1;
      k2 = CBRTL (k2);
      k0 -= k1;
      k2 += CBRTL (k0) - a;
    }
  return k2;
}

/**
 * Function to calculate the solution of a cubic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^3+b\,x^2+c\,x+d=0\f$
 * (JBDOUBLE).
 *
 * \return solution value.
 */
static inline JBDOUBLE
jbm_solve_cubicl (const JBDOUBLE a,
                  ///< 3rd order coefficient of the equation.
                  const JBDOUBLE b,
                  ///< 2nd order coefficient of the equation.
                  const JBDOUBLE c,
                  ///< 1st order coefficient of the equation.
                  const JBDOUBLE d,
                  ///< 0th order coefficient of the equation.
                  const JBDOUBLE x1,
                  ///< left limit of the solution interval.
                  const JBDOUBLE x2)
                  ///< right limit of the solution interval.
{
  if (jbm_smalll (a))
    return jbm_solve_quadraticl (b, c, d, x1, x2);
  return jbm_solve_cubic_reducedl (b / a, c / a, d / a, x1, x2);
}

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_totall (const JBDOUBLE d1 __attribute__((unused)),
                         ///< 1st flux limiter function parameter.
                         const JBDOUBLE d2 __attribute__((unused)))
                         ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  return c0;
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_nulll (const JBDOUBLE d1 __attribute__((unused)),
                        ///< 1st flux limiter function parameter.
                        const JBDOUBLE d2 __attribute__((unused)))
                        ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c1 = 1.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c1 = 1.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c1 = 1.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c1 = 1.Q;
#endif
  return c1;
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_centredl (const JBDOUBLE d1,
                           ///< 1st flux limiter function parameter.
                           const JBDOUBLE d2)
                           ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  if (jbm_smalll (d2))
    return c0;
  return d1 / d2;
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_superbeel (const JBDOUBLE d1,
                            ///< 1st flux limiter function parameter.
                            const JBDOUBLE d2)
                            ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f, c2 = 2.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1., c2 = 2.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L, c2 = 2.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q, c2 = 2.Q;
#endif
  JBDOUBLE r;
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  r = d1 / d2;
  return FMAXL (FMINL (r + r, c1), FMINL (r, c2));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_minmodl (const JBDOUBLE d1,
                          ///< 1st flux limiter function parameter.
                          const JBDOUBLE d2)
                          ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q;
#endif
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  return FMINL (d1 / d2, c1);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_VanLeerl (const JBDOUBLE d1,
                           ///< 1st flux limiter function parameter.
                           const JBDOUBLE d2)
                           ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q;
#endif
  JBDOUBLE r, k;
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  r = d1 / d2;
  k = FABSL (r);
  return (r + k) / (c1 + k);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_VanAlbadal (const JBDOUBLE d1,
                             ///< 1st flux limiter function parameter.
                             const JBDOUBLE d2)
                             ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q;
#endif
  JBDOUBLE r, k;
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  r = d1 / d2;
  k = r * r;
  return (r + k) / (c1 + k);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_minsuperl (const JBDOUBLE d1,
                            ///< 1st flux limiter function parameter.
                            const JBDOUBLE d2)
                            ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c2 = 2.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c2 = 2.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c2 = 2.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c2 = 2.Q;
#endif
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  return FMINL (d1 / d2, c2);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_superminl (const JBDOUBLE d1,
                            ///< 1st flux limiter function parameter.
                            const JBDOUBLE d2)
                            ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q;
#endif
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  return FMINL (jbm_fdbll (d1 / d2), c1);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f\[\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f\] (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_monotonized_centrall (const JBDOUBLE d1,
                                       ///< 1st flux limiter function parameter.
                                       const JBDOUBLE d2)
                                       ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f, c2 = 2.f, c3 = 3.f, c05 = 0.5f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1., c2 = 2., c3 = 3., c05 = 0.5;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L, c2 = 2.L, c3 = 3.L, c05 = 0.5L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q, c2 = 2.Q, c3 = 3.Q, c05 = 0.5Q;
#endif
  JBDOUBLE k;
  if (d1 * d2 <= JBM_EPSILONL)
    return c0;
  k = d1 / d2;
  if (k >= c3)
    return c2;
  if (k <= c1 / c3)
    return k + k;
  return c05 * (k + c1);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_meanl (const JBDOUBLE d1,
                        ///< 1st flux limiter function parameter.
                        const JBDOUBLE d2)
                        ///< 2nd flux limiter function parameter.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f, c05 = 0.5f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1., c05 = 0.5;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L, c05 = 0.5L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q, c05 = 0.5Q;
#endif
  if (jbm_smalll (d2))
    return c0;
  return c05 * (d1 / d2 + c1);
}

/**
 * Function to do a flux limiter function (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiterl (const JBDOUBLE d1,
                  ///< 1st flux limiter function parameter.
                  const JBDOUBLE d2,
                  ///< 2nd flux limiter function parameter.
                  unsigned int type)
                  ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_totall (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_nulll (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centredl (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbeel (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmodl (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeerl (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbadal (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuperl (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_superminl (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_centrall (d1, d2);
    }
  return jbm_flux_limiter_meanl (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (JBDOUBLE).
 *
 * The coefficients are:\n
 * - 1 point (2nd order):\n
 * \f$a_0=2,\quad b_0=0\f$\n
 * - 3 points (6th order):\n
 * \f$a_0=\frac{8}{9},\quad b_0=0,\f$\n
 * \f$a_1=\frac{5}{9},\quad b_1=\sqrt{\frac{3}{5}},\f$\n
 * - 5 points (10th order):\n
 * \f$a_0=\frac{128}{225},\quad b_0=0,\f$\n
 * \f$a_1=\frac{15\,\sqrt{70}-21}{50\,\sqrt{70}-200},\quad
 * b_1=\sqrt{\frac{35-\sqrt{280}}{63}},\f$\n
 * \f$a_2=\frac{15\,\sqrt{70}+21}{50\,\sqrt{70}+200},\quad
 * b_2=\sqrt{\frac{35+\sqrt{280}}{63}},\f$\n
 * - 7 points (14th order):\n
 * \f\[b_0=0,\f\]
 * \f\[b_1=\sqrt{\frac{7}{13}-\sqrt{\frac{336}{1859}}\,\cos\left[\frac{1}{3}
 *   \,acos\left(\sqrt{\frac{539}{83349}}\right)\right]},\f\]
 * \f\[b_2=\sqrt{\frac{7}{13}+\sqrt{\frac{336}{1859}}\,\cos\left\{\frac{1}{3}
 *   \,acos\left[\frac{1}{3}\,\left(\pi+\sqrt{\frac{539}{83349}}\right)\right]
 *   \right\}},\f\]
 * \f\[b_3=\sqrt{\frac{7}{13}+\sqrt{\frac{336}{1859}}\,\cos\left\{\frac{1}{3}
 *   \,acos\left[\frac{1}{3}\,\left(\pi-\sqrt{\frac{539}{83349}}\right)\right]
 *   \right\}},\f\]
 * \f\[a_3=\frac{1}{b_3^2}\,\frac{\frac{1}{7}-y_1\,\frac{1}{5}
 *   -y_2\,\left(\frac{1}{5}-y_1\,\frac{1}{3}\right)}
 *   {\left(y_3-y_2\right)\,\left(y_3-y_1\right)},\f\]
 * \f\[a_2=\frac{1}{b_2^2}\,\frac{\frac{1}{5}-y_1\,\frac{1}{3}
 *   -b_3\,\left(y_3-y_1\right)}{y_2-y_1},\f\]
 * \f\[a_1=\frac{1}{b_1^2}\,\left(\frac{1}{3}-b_2-b_3\right),\f\]
 * \f\[a_0=0\f\]
 *
 * \return integral value.
 */
static inline JBDOUBLE
jbm_integrall (JBDOUBLE (*f) (JBDOUBLE),
               ///< pointer to the function to integrate.
               const JBDOUBLE x1,       ///< left limit of the interval.
               const JBDOUBLE x2)       ///< right limit of the interval.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c05 = 0.5f;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBDOUBLE a[1] = { 2.f };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBDOUBLE a[2] = { 8.f / 9.f, 5.f / 9.f }, b[2] = { 0.f, 7.7459667e-1f };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBDOUBLE a[3] = {
    128.f / 225.f,
    4.7862867e-1f,
    2.3692689e-1f
  }, b[3] = {
    0.f,
    5.3846931e-1f,
    9.0617985e-1f
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBDOUBLE a[4] = {
    4.1795918e-1f,
    3.8183005e-1f,
    2.7970539e-1f,
    1.2948497e-1f
  }, b[4] = {
    0.f,
    4.0584515e-1f,
    7.4153119e-1f,
    9.4910791e-1f
  };
#endif
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c05 = 0.5;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBDOUBLE a[1] = { 2. };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBDOUBLE a[2] = { 8. / 9., 5. / 9. },
    b[2] = { 0., 7.745966692414834e-1 };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBDOUBLE a[3] = {
    128. / 225.,
    4.786286704993665e-1,
    2.369268850561891e-1
  }, b[3] = {
    0.,
    5.384693101056831e-1,
    9.061798459386640e-1
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBDOUBLE a[4] = {
    4.179591836734694e-1,
    3.818300505051189e-1,
    2.797053914892767e-1,
    1.294849661688697e-1
  }, b[4] = {
    0.,
    4.058451513773972e-1,
    7.415311855993944e-1,
    9.491079123427585e-1
  };
#endif
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c05 = 0.5L;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBDOUBLE a[1] = { 2.L };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBDOUBLE a[2] = { 8.L / 9.L, 5.L / 9.L },
    b[2] = { 0.L, 7.7459666924148340428e-1L };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBDOUBLE a[3] = {
    128.L / 225.L,
    4.7862867049936646804e-1L,
    2.3692688505618908751e-1L
  }, b[3] = {
    0.L,
    5.3846931010568309104e-1L,
    9.0617984593866399280e-1L
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBDOUBLE a[4] = {
    4.1795918367346938776e-1L,
    3.8183005050511894495e-1L,
    2.7970539148927666790e-1L,
    1.2948496616886969327e-1L
  }, b[4] = {
    0.L,
    4.0584515137739716691e-1L,
    7.4153118559939443986e-1L,
    9.4910791234275852453e-1L
  };
#endif
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c05 = 0.5Q;
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBDOUBLE a[1] = { 2.Q };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBDOUBLE a[2] = { 8.Q / 9.Q, 5.Q / 9.Q },
    b[2] = { 0.Q, 7.7459666924148340427791481488384306e-1Q };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBDOUBLE a[3] = {
    128.Q / 225.Q,
    4.7862867049936646804129151483563819e-1Q,
    2.3692688505618908751426404071991736e-1Q
  }, b[3] = {
    0.Q,
    5.3846931010568309103631442070020880e-1Q,
    9.0617984593866399279762687829939297e-1Q
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBDOUBLE a[4] = {
    4.1795918367346938775510204081632653e-1Q,
    3.8183005050511894495036977548897513e-1Q,
    2.7970539148927666790146777142377958e-1Q,
    1.2948496616886969327061143267908202e-1Q
  }, b[4] = {
    0.Q,
    4.0584515137739716690660641207696146e-1Q,
    7.4153118559939443986386477328078841e-1Q,
    9.4910791234275852452618968404785126e-1Q
  };
#endif
#endif
  JBDOUBLE k, x, dx;
#if JBM_INTEGRAL_GAUSS_N > 1
  JBDOUBLE k2;
  unsigned int i;
#endif
  dx = c05 * (x2 - x1);
  x = c05 * (x1 + x2);
  k = a[0] * f (x);
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = b[i] * dx;
      k += a[i] * (f (x - k2) + f (x + k2));
    }
#endif
  k *= dx;
  return k;
}

#ifdef __SSE4_2__

/**
 * Function to calculate the absolute value of a __m128d vector.
 *
 * \return absolute value vector.
 */
static inline __m128d
jbm_abs_128 (const __m128d x)
{
  return _mm_andnot_pd (_mm_set1_pd (-0.0), x);
}

/**
 * Function to check small __m128d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m128d
jbm_small_128 (const __m128d x)       ///< __m128d vector.
{
  return _mm_cmplt_pd (jbm_abs_128 (x), _mm_set1_pd (FLT_EPSILON));
}

/**
 * Function to calculate the __m128d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m128d vector.
 */
static inline __m128d
jbm_modmin_128 (__m128d a,      ///< 1st __m128d vector.
                const __m128d b)      ///< 2nd __m128d vector.
{
  __m128d aa, ab, z;
  z = _mm_setzero_pd ();
  ab = _mm_mul_pd (a, b);
  a = _mm_blendv_pd (a, z, _mm_cmple_pd (ab, z));
  aa = jbm_abs_128 (a);
  ab = jbm_abs_128 (b);
  return _mm_blendv_pd (a, b, _mm_cmpgt_pd (aa, ab));
}

/**
 * Function to interchange 2 __m128d numbers.
 */
static inline void
jbm_change_128 (__m128d *restrict a,    ///< 1st __m128d vector pointer.
                __m128d *restrict b)    ///< 2nd __m128d vector pointer.
{
  __m128d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m128d vector.
 *
 * \return __m128d double.
 */
static inline __m128d
jbm_dbl_128 (const __m128d x)         ///< __m128d vector.
{
  return _mm_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m128d vector.
 *
 * \return __m128d vector square.
 */
static inline __m128d
jbm_sqr_128 (const __m128d x)         ///< __m128d vector.
{
  return _mm_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m128d vectors of 2D points.
 *
 * \return __m128d vector of y-coordinates of the extrapolated points.
 */
static inline __m128d
jbm_extrapolate_128 (const __m128d x,
                     ///< __m128d vector of x-coordinates of the extrapolated
                     ///< points.
                     const __m128d x1,
                     ///< __m128d vector of x-coordinates of the 1st points.
                     const __m128d x2,
                     ///< __m128d vector of x-coordinates of the 2nd points.
                     const __m128d y1,
                     ///< __m128d vector of y-coordinates of the 1st points.
                     const __m128d y2)
                     ///< __m128d vector of y-coordinates of the 2nd points.
{
  __m128d d;
  d = _mm_sub_pd (x, x1);
#ifdef __AVX__
  return _mm_fmadd_pd (d, _mm_div_pd (_mm_sub_pd (y2, y1),
                                      _mm_sub_pd (x2, x1)), y1);
#else
  d = _mm_mul_pd (d, _mm_div_pd (_mm_sub_pd (y2, y1), _mm_sub_pd (x2, x1)));
  return _mm_add_pd (y1, d);
#endif
}

/**
 * Function to perform an interpolation between 2 __m128d vectors of 2D points.
 *
 * \return __m128d vector of y-coordinates of the interpolated points.
 */
static inline __m128d
jbm_interpolate_128 (const __m128d x,
                     ///< __m128d vector of x-coordinates of the interpolated
                     ///< points.
                     const __m128d x1,
                     ///< __m128d vector of x-coordinates of the 1st points.
                     const __m128d x2,
                     ///< __m128d vector of x-coordinates of the 2nd points.
                     const __m128d y1,
                     ///< __m128d vector of y-coordinates of the 1st points.
                     const __m128d y2)
                     ///< __m128d vector of y-coordinates of the 2nd points.
{
  __m128d k;
  k = jbm_extrapolate_128 (x, x1, x2, y1, y2);
  k = _mm_blendv_pd (y1, k, _mm_cmpgt_pd (x, x1));
  return _mm_blendv_pd (y2, k, _mm_cmplt_pd (x, x2));
}

/**
 * Function to calculate the length of a __m128d vector of 2D segments.
 *
 * \return __m128d vector of segment lengths.
 */
static inline __m128d
jbm_v2_length_128 (const __m128d x1,
///< __m128d vector of x-coordinates of the 1st points defining the segment.
                   const __m128d y1,
///< __m128d vector of y-coordinates of the 1st points defining the segment.
                   const __m128d x2,
///< __m128d vector of x-coordinates of the 2nd points defining the segment.
                   const __m128d y2)
///< __m128d vector of y-coordinates of the 2nd points defining the segment.
{
  __m128d dx, dy;
  dx = _mm_sub_pd (x2, x1);
  dy = _mm_sub_pd (y2, y1);
  return _mm_sqrt_pd (_mm_add_pd (jbm_sqr_128 (dx), jbm_sqr_128 (dy)));
}

/**
 * Function to calculate the length of a __m128d vector of 3D segments.
 *
 * \return __m128d vector of segment lengths.
 */
static inline __m128d
jbm_v3_length_128 (const __m128d x1,
///< __m128d vector of x-coordinates of the 1st points defining the segments.
                   const __m128d y1,
///< __m128d vector of y-coordinates of the 1st points defining the segments.
                   const __m128d z1,
///< __m128d vector of z-coordinates of the 1st points defining the segments.
                   const __m128d x2,
///< __m128d vector of x-coordinates of the 2nd points defining the segments.
                   const __m128d y2,
///< __m128d vector of y-coordinates of the 2nd points defining the segments.
                   const __m128d z2)
///< __m128d vector of z-coordinates of the 2nd points defining the segments.
{
  __m128d dx, dy, dz;
  dx = _mm_sub_pd (x2, x1);
  dx = jbm_sqr_128 (dx);
  dy = _mm_sub_pd (y2, y1);
  dy = jbm_sqr_128 (dy);
  dz = _mm_sub_pd (z2, z1);
  dz = jbm_sqr_128 (dz);
  return _mm_sqrt_pd (_mm_add_pd (dx, _mm_add_pd (dy, dz)));
}

/**
 * Function to calculate a __m128d vector of 1st order polynomials.
 *
 * \return __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_1_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, _mm_set1_pd (p[1]), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]), _mm_mul_pd (x, _mm_set1_pd (p[1])));
#endif
}

/**
 * Function to calculate a const __m128d vector of 2nd order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_2_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_1_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_1_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 3rd order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_3_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_2_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_2_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 4th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_4_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_3_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_3_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 5th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_5_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_4_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_4_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 6th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_6_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_5_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_5_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 7th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_7_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_6_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_6_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 8th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_8_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_7_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_7_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 9th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_9_128 (const __m128d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_8_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_8_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 10th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_10_128 (const __m128d x,       ///< variable.
                       const double *p)       ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_9_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_9_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate a const __m128d vector of 11th order polynomials.
 *
 * \return const __m128d vector of polynomial values.
 */
static inline __m128d
jbm_polynomial_11_128 (const __m128d x,       ///< variable.
                       const double *p)       ///< array of coefficients.
{
#ifdef __AVX__
  return _mm_fmadd_pd (x, jbm_polynomial_10_128 (x, p + 1), _mm_set1_pd (p[0]));
#else
  return _mm_add_pd (_mm_set1_pd (p[0]),
                     _mm_mul_pd (x, jbm_polynomial_10_128 (x, p + 1)));
#endif
}

/**
 * Function to calculate the solution of a __m128d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m128d vector of solution values.
 */
static inline __m128d
jbm_solve_quadratic_reduced_128 (__m128d a,
///< __m128d vector of 1st order coefficient of the equations.
                                 __m128d b,
///< __m128d vector of 0th order coefficient of the equations.
                                 const __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                                 const __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  __m128d k1, k2;
  k1 = _mm_set1_pd (-0.5);
  a = _mm_mul_pd (a, k1);
  b = _mm_sqrt_pd (_mm_sub_pd (jbm_sqr_128 (a), b));
  k1 = _mm_add_pd (a, b);
  k2 = _mm_sub_pd (a, b);
  k1 = _mm_blendv_pd (k1, k2, _mm_cmplt_pd (k1, x1));
  return _mm_blendv_pd (k1, k2, _mm_cmpgt_pd (k1, x2));
}

/**
 * Function to calculate the solution of a __m128d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m128d vector of solution values.
 */
static inline __m128d
jbm_solve_quadratic_128 (const __m128d a,
///< __m128d vector of 2nd order coefficient of the equations.
                         const __m128d b,
///< __m128d vector of 1st order coefficient of the equations.
                         const __m128d c,
///< __m128d vector of 0th order coefficient of the equations.
                         const __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                         const __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  __m128d k1, k2;
  k1 = jbm_solve_quadratic_reduced_128 (_mm_div_pd (b, a), _mm_div_pd (c, a),
                                        x1, x2);
  k2 = _mm_div_pd (_mm_sub_pd (_mm_setzero_pd (), c), b);
  return _mm_blendv_pd (k1, k2, jbm_small_128 (a));
}

/**
 * Function to calculate the solution of a __m128d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m128d vector of solution values.
 */
/*
static inline __m128d
jbm_solve_cubic_reduced_128 (__m128d a,
                             ///< 2nd order coefficient of the equation.
                             __m128d b,
                             ///< 1st order coefficient of the equation.
                             __m128d c,
                             ///< 0th order coefficient of the equation.
                             __m128d x1,
                             ///< left limit of the solution interval.
                             __m128d x2)
                             ///< right limit of the solution interval.
{
  __m128d k0, k1, k2, k3, l0, l1, l2, l3, l4, l5, c0, c1, c3, c2p_3, c_2, c_3;
  c0 = _mm_setzero_pd ();
  c1 = _mm_set1_pd (1.);
  c2p_3 = _mm_set1_pd (2. * M_PI / 3.);
  c_2 = _mm_set1_pd (0.5);
  c_3 = _mm_set1_pd (1. / 3.);
  a = _mm_mul_pd (a, c_3);
  k0 = _mm_mul_pd (a, a);
  k1 = _mm_fmsub_pd (b, c_3, k0);
  k0 = _mm_fmsub_pd (_mm_fmsub_pd (b, a, c), c_2, _mm_mul_pd (a, k0));
  k3 = _mm_mul_pd (k1, _mm_mul_pd (k1, k1));
  k2 = _mm_fmadd_pd (k0, k0, k3);
  l1 = _mm_sqrt_pd (_mm_sub_pd (c0, k1));
  l0 = _mm_mul_pd (_mm_acos_pd (_mm_div_pd (k0 , k3)), c_3);
  l1 = _mm_add_pd (l1, l1);
  l2 = _mm_fmsub_pd (l1, _mm_cos_pd (k0), a);
  l3 = _mm_fmsub_pd (l1, _mm_cos_pd (_mm_add_pd (l0, c2p_3)), a);
  l3 = _mm_blendv_pd (l3, l2,
                      _mm_or_pd (_mm_cmplt (l2, x1), _mm_cmpgt (l2, x2)));
  l4 = _mm_fmsub_pd (l1, _mm_cos_pd (_mm_sub_pd (l0, c2p_3)), a);
  l4 = _mm_blendv_pd (l4, l3,
                      _mm_or_pd (_mm_cmplt (l3, x1), _mm_cmpgt (l3, x2)));
  k1 = _mm_sqrt_pd (k2);
  l5 = _mm_add_pd (k0, k1);
  l5 = _mm_cbrt_pd (k2);
  k0 = _mm_sub_pd (k0, k1);
  l5 = _mm_add_pd (l5, _mm_sub_pd (_mm_cbrt_pd (k0), a));
  return _mm_blendv_pd (l4, l5, _mm_cmplt_pd (k2, c0));
}
*/

/**
 * Function to calculate the solution of a __m128d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m128d vector of solution values.
 */
/*
static inline __m128d
jbm_solve_cubic_128 (__m128d a,
///< __m128d vector of 3rd order coefficient of the equations.
                 __m128d b,
///< __m128d vector of 2nd order coefficient of the equations.
                 __m128d c,
///< __m128d vector of 1st order coefficient of the equations.
                 __m128d d,
///< __m128d vector of 0th order coefficient of the equations.
                         __m128d x1,
///< __m128d vector of left limits of the solution intervals.
                         __m128d x2)
///< __m128d vector of right limits of the solution intervals.
{
  return
    _mm_blendv_pd (jbm_solve_cubic_reduced (_mm_div_pd (b, a),
                                            _mm_div_pd (c, a),
                                            _mm_div_pd (d, a), x1, x2),
                   jbm_solve_quadratic_128 (b, c, d, x1, x2),
		   jbm_small_128 (a));
}
*/

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_total_128 (const __m128d d1 __attribute__((unused)),
                            ///< 1st flux limiter function parameter.
                            const __m128d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_null_128 (const __m128d d1 __attribute__((unused)),
                           ///< 1st flux limiter function parameter.
                           const __m128d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_centred_128 (const __m128d d1,
                              ///< 1st flux limiter function parameter.
                              const __m128d d2)
                              ///< 2nd flux limiter function parameter.
{
  return _mm_blendv_pd (_mm_div_pd (d1, d2), _mm_setzero_pd (),
                        jbm_small_128 (d2));
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_superbee_128 (const __m128d d1,
                               ///< 1st flux limiter function parameter.
                               const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_div_pd (d1, d2);
  r = _mm_max_pd (_mm_min_pd (jbm_dbl_128 (r), _mm_set1_pd (1.)),
                  _mm_min_pd (r, _mm_set1_pd (2.)));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_minmod_128 (const __m128d d1,
                             ///< 1st flux limiter function parameter.
                             const __m128d d2)
                             ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_min_pd (_mm_div_pd (d1, d2), _mm_set1_pd (1.));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_VanLeer_128 (const __m128d d1,
                              ///< 1st flux limiter function parameter.
                              const __m128d d2)
                              ///< 2nd flux limiter function parameter.
{
  __m128d r, k;
  r = _mm_div_pd (d1, d2);
  k = jbm_abs_128 (r);
  r = _mm_div_pd (_mm_add_pd (r, k), _mm_add_pd (_mm_set1_pd (1.), k));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_VanAlbada_128 (const __m128d d1,
                                ///< 1st flux limiter function parameter.
                                const __m128d d2)
                                ///< 2nd flux limiter function parameter.
{
  __m128d r, k;
  r = _mm_div_pd (d1, d2);
  k = jbm_sqr_128 (r);
  r = _mm_div_pd (_mm_add_pd (r, k), _mm_add_pd (_mm_set1_pd (1.), k));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_minsuper_128 (const __m128d d1,
                               ///< 1st flux limiter function parameter.
                               const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_min_pd (_mm_div_pd (d1, d2), _mm_set1_pd (2.));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_supermin_128 (const __m128d d1,
                               ///< 1st flux limiter function parameter.
                               const __m128d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_div_pd (d1, d2);
  r = _mm_min_pd (jbm_dbl_128 (r), _mm_set1_pd (1.));
  return _mm_blendv_pd (_mm_setzero_pd (), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_monotonized_central_128 (const __m128d d1,
///< 1st flux limiter function parameter.
                                          const __m128d d2)
///< 2nd flux limiter function parameter.
{
  __m128d r, rm;
  r = _mm_div_pd (d1, d2);
  rm = _mm_mul_pd (_mm_set1_pd (0.5), _mm_add_pd (r, _mm_set1_pd (1.)));
  rm = _mm_blendv_pd (_mm_set1_pd (2.), rm, _mm_cmplt_pd (r, _mm_set1_pd (3.)));
  rm = _mm_blendv_pd (rm, jbm_dbl_128 (r),
                      _mm_cmpgt_pd (r, _mm_set1_pd (1. / 3.)));
  return _mm_blendv_pd (_mm_set1_pd (0.), rm,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_mean_128 (const __m128d d1,
                           ///< 1st flux limiter function parameter.
                           const __m128d d2)
                           ///< 2nd flux limiter function parameter.
{
  __m128d r;
  r = _mm_mul_pd (_mm_set1_pd (0.5),
                  _mm_add_pd (_mm_set1_pd (1.), _mm_div_pd (d1, d2)));
  return _mm_blendv_pd (_mm_set1_pd (0.), r,
                        _mm_cmpgt_pd (_mm_mul_pd (d1, d2),
                                      _mm_set1_pd (FLT_EPSILON)));
}

/**
 * Function to do a flux limiter function (__m128d).
 *
 * \return flux limiter function value.
 */
static inline __m128d
jbm_flux_limiter_128 (const __m128d d1,
                      ///< 1st flux limiter function parameter.
                      const __m128d d2,
                      ///< 2nd flux limiter function parameter.
                      unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_128 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_128 (d1, d2);
    }
  return jbm_flux_limiter_mean_128 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m128d).
 *
 * \return __m128d vector of integral values.
 */
static inline __m128d
jbm_integral_128 (__m128d (*f) (__m128d),
                  ///< pointer to the function to integrate.
                  const __m128d x1,   ///< left limit of the interval.
                  const __m128d x2)   ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2. };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8. / 9., 5. / 9. },
    b[2] = { 0., 7.745966692414834e-1 };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128. / 225.,
    4.786286704993665e-1,
    2.369268850561891e-1
  }, b[3] = {
    0.,
    5.384693101056831e-1,
    9.061798459386640e-1
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.179591836734694e-1,
    3.818300505051189e-1,
    2.797053914892767e-1,
    1.294849661688697e-1
  }, b[4] = {
    0.,
    4.058451513773972e-1,
    7.415311855993944e-1,
    9.491079123427585e-1
  };
#endif
  __m128d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m128d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm_set1_pd (0.5);
  dx = _mm_mul_pd (h, _mm_sub_pd (x2, x1));
  x = _mm_mul_pd (h, _mm_add_pd (x2, x1));
  k = _mm_set1_pd (a[0]);
  k = _mm_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm_set1_pd (b[i]);
      k2 = _mm_mul_pd (k2, dx);
      f1 = f (_mm_sub_pd (x, k2));
      f2 = f (_mm_add_pd (x, k2));
      h = _mm_set1_pd (a[i]);
#ifdef __AVX__
      k = _mm_fmadd_pd (h, _mm_add_pd (f1, f2), k);
#else
      k = _mm_add_pd (k, _mm_mul_pd (h, _mm_add_pd (f1, f2)));
#endif
    }
#endif
  k = _mm_mul_pd (k, dx);
  return k;
}

#endif

#ifdef __AVX__

/**
 * Function to calculate the absolute value of a __m256d vector.
 *
 * \return absolute value vector.
 */
static inline __m256d
jbm_abs_256 (const __m256d x)
{
  return _mm256_andnot_pd (_mm256_set1_pd (-0.0), x);
}

/**
 * Function to check small __m256d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __m256d
jbm_small_256 (const __m256d x)       ///< __m256d vector.
{
  return _mm256_cmp_pd (jbm_abs_256 (x), _mm256_set1_pd (FLT_EPSILON),
                        _CMP_LT_OS);
}

/**
 * Function to calculate the __m256d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m256d vector.
 */
static inline __m256d
jbm_modmin_256 (__m256d a,      ///< 1st __m256d vector.
                const __m256d b)      ///< 2nd __m256d vector.
{
  __m256d aa, ab, m, z;
  z = _mm256_setzero_pd ();
  ab = _mm256_mul_pd (a, b);
  m = _mm256_cmp_pd (ab, z, _CMP_LE_OS);
  a = _mm256_blendv_pd (a, z, m);
  aa = jbm_abs_256 (a);
  ab = jbm_abs_256 (b);
  m = _mm256_cmp_pd (aa, ab, _CMP_GT_OS);
  return _mm256_blendv_pd (a, b, m);
}

/**
 * Function to interchange 2 __m256d numbers.
 */
static inline void
jbm_change_256 (__m256d *restrict a,    ///< 1st __m256d vector pointer.
                __m256d *restrict b)    ///< 2nd __m256d vector pointer.
{
  __m256d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m256d vector.
 *
 * \return __m256d double.
 */
static inline __m256d
jbm_dbl_256 (const __m256d x)         ///< __m256d vector.
{
  return _mm256_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m256d vector.
 *
 * \return __m256d vector square.
 */
static inline __m256d
jbm_sqr_256 (const __m256d x)         ///< __m256d vector.
{
  return _mm256_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m256d vectors of 2D points.
 *
 * \return __m256d vector of y-coordinates of the extrapolated points.
 */
static inline __m256d
jbm_extrapolate_256 (const __m256d x,
                     ///< __m256d vector of x-coordinates of the extrapolated
                     ///< points.
                     const __m256d x1,
                     ///< __m256d vector of x-coordinates of the 1st points.
                     const __m256d x2,
                     ///< __m256d vector of x-coordinates of the 2nd points.
                     const __m256d y1,
                     ///< __m256d vector of y-coordinates of the 1st points.
                     const __m256d y2)
                     ///< __m256d vector of y-coordinates of the 2nd points.
{
  __m256d d;
  d = _mm256_sub_pd (x, x1);
  return _mm256_fmadd_pd (d, _mm256_div_pd (_mm256_sub_pd (y2, y1),
                                            _mm256_sub_pd (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m256d vectors of 2D points.
 *
 * \return __m256d vector of y-coordinates of the interpolated points.
 */
static inline __m256d
jbm_interpolate_256 (const __m256d x,
                     ///< __m256d vector of x-coordinates of the interpolated
                     ///< points.
                     const __m256d x1,
                     ///< __m256d vector of x-coordinates of the 1st points.
                     const __m256d x2,
                     ///< __m256d vector of x-coordinates of the 2nd points.
                     const __m256d y1,
                     ///< __m256d vector of y-coordinates of the 1st points.
                     const __m256d y2)
                     ///< __m256d vector of y-coordinates of the 2nd points.
{
  __m256d k, m;
  k = jbm_extrapolate_256 (x, x1, x2, y1, y2);
  m = _mm256_cmp_pd (x, x1, _CMP_GT_OS);
  k = _mm256_blendv_pd (y1, k, m);
  m = _mm256_cmp_pd (x, x2, _CMP_LT_OS);
  return _mm256_blendv_pd (y2, k, m);
}

/**
 * Function to calculate the length of a __m256d vector of 2D segments.
 *
 * \return __m256d vector of segment lengths.
 */
static inline __m256d
jbm_v2_length_256 (const __m256d x1,
///< __m256d vector of x-coordinates of the 1st points defining the segment.
                   const __m256d y1,
///< __m256d vector of y-coordinates of the 1st points defining the segment.
                   const __m256d x2,
///< __m256d vector of x-coordinates of the 2nd points defining the segment.
                   const __m256d y2)
///< __m256d vector of y-coordinates of the 2nd points defining the segment.
{
  __m256d dx, dy;
  dx = _mm256_sub_pd (x2, x1);
  dy = _mm256_sub_pd (y2, y1);
  return _mm256_sqrt_pd (_mm256_add_pd (jbm_sqr_256 (dx), jbm_sqr_256 (dy)));
}

/**
 * Function to calculate the length of a __m256d vector of 3D segments.
 *
 * \return __m256d vector of segment lengths.
 */
static inline __m256d
jbm_v3_length_256 (const __m256d x1,
///< __m256d vector of x-coordinates of the 1st points defining the segments.
                   const __m256d y1,
///< __m256d vector of y-coordinates of the 1st points defining the segments.
                   const __m256d z1,
///< __m256d vector of z-coordinates of the 1st points defining the segments.
                   const __m256d x2,
///< __m256d vector of x-coordinates of the 2nd points defining the segments.
                   const __m256d y2,
///< __m256d vector of y-coordinates of the 2nd points defining the segments.
                   const __m256d z2)
///< __m256d vector of z-coordinates of the 2nd points defining the segments.
{
  __m256d dx, dy, dz;
  dx = _mm256_sub_pd (x2, x1);
  dx = jbm_sqr_256 (dx);
  dy = _mm256_sub_pd (y2, y1);
  dy = jbm_sqr_256 (dy);
  dz = _mm256_sub_pd (z2, z1);
  dz = jbm_sqr_256 (dz);
  return _mm256_sqrt_pd (_mm256_add_pd (dx, _mm256_add_pd (dy, dz)));
}

/**
 * Function to calculate a __m256d vector of 1st order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_1_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, _mm256_set1_pd (p[1]), _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 2nd order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_2_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_1_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 3rd order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_3_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_2_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 4th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_4_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_3_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 5th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_5_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_4_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 6th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_6_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_5_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 7th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_7_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_6_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 8th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_8_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_7_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 9th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_9_256 (const __m256d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_8_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 10th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_10_256 (const __m256d x,       ///< variable.
                       const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_9_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate a __m256d vector of 11th order polynomials.
 *
 * \return __m256d vector of polynomial values.
 */
static inline __m256d
jbm_polynomial_11_256 (const __m256d x,       ///< variable.
                       const double *p)       ///< array of coefficients.
{
  return _mm256_fmadd_pd (x, jbm_polynomial_10_256 (x, p + 1),
                          _mm256_set1_pd (p[0]));
}

/**
 * Function to calculate the solution of a __m256d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_quadratic_reduced_256 (__m256d a,
///< __m256d vector of 1st order coefficient of the equations.
                                 __m256d b,
///< __m256d vector of 0th order coefficient of the equations.
                                 const __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                                 const __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  __m256d k1, k2, m;
  k1 = _mm256_set1_pd (-0.5);
  a = _mm256_mul_pd (a, k1);
  b = _mm256_sqrt_pd (_mm256_sub_pd (jbm_sqr_256 (a), b));
  k1 = _mm256_add_pd (a, b);
  k2 = _mm256_sub_pd (a, b);
  m = _mm256_cmp_pd (k1, x1, _CMP_LT_OS);
  k1 = _mm256_blendv_pd (k1, k2, m);
  m = _mm256_cmp_pd (k1, x2, _CMP_GT_OS);
  return _mm256_blendv_pd (k1, k2, m);
}

/**
 * Function to calculate the solution of a __m256d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m256d vector of solution values.
 */
static inline __m256d
jbm_solve_quadratic_256 (const __m256d a,
///< __m256d vector of 2nd order coefficient of the equations.
                         const __m256d b,
///< __m256d vector of 1st order coefficient of the equations.
                         const __m256d c,
///< __m256d vector of 0th order coefficient of the equations.
                         const __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                         const __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  __m256d k1, k2, m;
  m = jbm_small_256 (a);
  k1 = jbm_solve_quadratic_reduced_256 (_mm256_div_pd (b, a),
                                        _mm256_div_pd (c, a), x1, x2);
  k2 = _mm256_div_pd (_mm256_sub_pd (_mm256_setzero_pd (), c), b);
  return _mm256_blendv_pd (k1, k2, m);
}

/**
 * Function to calculate the solution of a __m256d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m256d vector of solution values.
 */
/*
static inline __m256d
jbm_solve_cubic_reduced (__m256d a,
                         ///< 2nd order coefficient of the equation.
                         __m256d b,
                         ///< 1st order coefficient of the equation.
                         __m256d c,
                         ///< 0th order coefficient of the equation.
                         __m256d x1,
                         ///< left limit of the solution interval.
                         __m256d x2)
                         ///< right limit of the solution interval.
{
  __m256d k0, k1, k2;
  a /= 3.;
  k0 = a * a;
  k1 = b / 3. - k0;
  k0 = (b * a - c) / 2. - a * k0;
  k2 = k1 * k1 * k1 + k0 * k0;
  if (k2 < 0.)
    {
      k1 = SQRT (-k1);
      k0 = ACOS (k0 / (k1 * k1 * k1)) / 3.;
      k1 *= 2.;
      k2 = k1 * COS (k0) - a;
      if (k2 < x1 || k2 > x2)
        {
          k2 = k1 * COS (k0 + 2. * JB_PI / 3.) - a;
          if (k2 < x1 || k2 > x2)
            k2 = k1 * COS (k0 - 2. * JB_PI / 3.) - a;
        }
    }
  else
    {
      k1 = SQRT (k2);
      k2 = k0 + k1;
      k2 = CBRT (k2);
      k0 -= k1;
      k2 += CBRT (k0) - a;
    }
  return k2;
}
*/

/**
 * Function to calculate the solution of a __m256d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m256d vector of solution values.
 */
/*
static inline __m256d
jbm_solve_cubic_256 (__m256d a,
///< __m256d vector of 3rd order coefficient of the equations.
                 __m256d b,
///< __m256d vector of 2nd order coefficient of the equations.
                 __m256d c,
///< __m256d vector of 1st order coefficient of the equations.
                 __m256d d,
///< __m256d vector of 0th order coefficient of the equations.
                         __m256d x1,
///< __m256d vector of left limits of the solution intervals.
                         __m256d x2)
///< __m256d vector of right limits of the solution intervals.
{
  __m256d m;
  m = jbm_small_256 (a);
  return
    _mm256_blendv_pd (jbm_solve_cubic_reduced (_mm256_div_pd (b, a),
                                            _mm256_div_pd (c, a),
                                            _mm256_div_pd (d, a), x1, x2),
                   jbm_solve_quadratic_256 (b, c, d, x1, x2), m);
}
*/

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_total_256 (const __m256d d1 __attribute__((unused)),
                            ///< 1st flux limiter function parameter.
                            const __m256d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm256_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_null_256 (const __m256d d1 __attribute__((unused)),
                           ///< 1st flux limiter function parameter.
                           const __m256d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm256_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_centred_256 (const __m256d d1,
                              ///< 1st flux limiter function parameter.
                              const __m256d d2)
                              ///< 2nd flux limiter function parameter.
{
  __m256d m;
  m = jbm_small_256 (d2);
  return _mm256_blendv_pd (_mm256_div_pd (d1, d2), _mm256_setzero_pd (), m);
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_superbee_256 (const __m256d d1,
                               ///< 1st flux limiter function parameter.
                               const __m256d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m256d r, m;
  r = _mm256_div_pd (d1, d2);
  r = _mm256_max_pd (_mm256_min_pd (jbm_dbl_256 (r), _mm256_set1_pd (1.)),
                     _mm256_min_pd (r, _mm256_set1_pd (2.)));
  m = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_setzero_pd (), r, m);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_minmod_256 (const __m256d d1,
                             ///< 1st flux limiter function parameter.
                             const __m256d d2)
                             ///< 2nd flux limiter function parameter.
{
  __m256d r, m;
  r = _mm256_min_pd (_mm256_div_pd (d1, d2), _mm256_set1_pd (1.));
  m = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_setzero_pd (), r, m);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_VanLeer_256 (const __m256d d1,
                              ///< 1st flux limiter function parameter.
                              const __m256d d2)
                              ///< 2nd flux limiter function parameter.
{
  __m256d r, k;
  r = _mm256_div_pd (d1, d2);
  k = jbm_abs_256 (r);
  r = _mm256_div_pd (_mm256_add_pd (r, k),
                     _mm256_add_pd (_mm256_set1_pd (1.), k));
  k = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_setzero_pd (), r, k);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_VanAlbada_256 (const __m256d d1,
                                ///< 1st flux limiter function parameter.
                                const __m256d d2)
                                ///< 2nd flux limiter function parameter.
{
  __m256d r, k;
  r = _mm256_div_pd (d1, d2);
  k = jbm_sqr_256 (r);
  r = _mm256_div_pd (_mm256_add_pd (r, k),
                     _mm256_add_pd (_mm256_set1_pd (1.), k));
  k = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_setzero_pd (), r, k);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_minsuper_256 (const __m256d d1,
                               ///< 1st flux limiter function parameter.
                               const __m256d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m256d r, m;
  r = _mm256_min_pd (_mm256_div_pd (d1, d2), _mm256_set1_pd (2.));
  m = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_setzero_pd (), r, m);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_supermin_256 (const __m256d d1,
                               ///< 1st flux limiter function parameter.
                               const __m256d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m256d r, m;
  r = _mm256_div_pd (d1, d2);
  r = _mm256_min_pd (jbm_dbl_256 (r), _mm256_set1_pd (1.));
  m = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_setzero_pd (), r, m);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_monotonized_central_256 (const __m256d d1,
///< 1st flux limiter function parameter.
                                          const __m256d d2)
///< 2nd flux limiter function parameter.
{
  __m256d r, rm, m;
  r = _mm256_div_pd (d1, d2);
  rm = _mm256_mul_pd (_mm256_set1_pd (0.5),
                      _mm256_add_pd (r, _mm256_set1_pd (1.)));
  m = _mm256_cmp_pd (r, _mm256_set1_pd (3.), _CMP_LT_OS);
  rm = _mm256_blendv_pd (_mm256_set1_pd (2.), rm, m);
  m = _mm256_cmp_pd (r, _mm256_set1_pd (1. / 3.), _CMP_GT_OS);
  rm = _mm256_blendv_pd (rm, jbm_dbl_256 (r), m);
  m = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_set1_pd (0.), rm, m);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_mean_256 (const __m256d d1,
                           ///< 1st flux limiter function parameter.
                           const __m256d d2)
                           ///< 2nd flux limiter function parameter.
{
  __m256d r, m;
  r = _mm256_mul_pd (_mm256_set1_pd (0.5),
                     _mm256_add_pd (_mm256_set1_pd (1.),
                                    _mm256_div_pd (d1, d2)));
  m = _mm256_cmp_pd (_mm256_mul_pd (d1, d2), _mm256_set1_pd (FLT_EPSILON),
                     _CMP_GT_OS);
  return _mm256_blendv_pd (_mm256_set1_pd (0.), r, m);
}

/**
 * Function to do a flux limiter function (__m256d).
 *
 * \return flux limiter function value.
 */
static inline __m256d
jbm_flux_limiter_256 (const __m256d d1,
                      ///< 1st flux limiter function parameter.
                      const __m256d d2,
                      ///< 2nd flux limiter function parameter.
                      unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_256 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_256 (d1, d2);
    }
  return jbm_flux_limiter_mean_256 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m256d).
 *
 * \return __m256d vector of integral values.
 */
static inline __m256d
jbm_integral_256 (__m256d (*f) (__m256d),
                  ///< pointer to the function to integrate.
                  const __m256d x1,   ///< left limit of the interval.
                  const __m256d x2)   ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2. };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8. / 9., 5. / 9. },
    b[2] = { 0., 7.745966692414834e-1 };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128. / 225.,
    4.786286704993665e-1,
    2.369268850561891e-1
  }, b[3] = {
    0.,
    5.384693101056831e-1,
    9.061798459386640e-1
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.179591836734694e-1,
    3.818300505051189e-1,
    2.797053914892767e-1,
    1.294849661688697e-1
  }, b[4] = {
    0.,
    4.058451513773972e-1,
    7.415311855993944e-1,
    9.491079123427585e-1
  };
#endif
  __m256d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m256d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm256_set1_pd (0.5);
  dx = _mm256_mul_pd (h, _mm256_sub_pd (x2, x1));
  x = _mm256_mul_pd (h, _mm256_add_pd (x2, x1));
  k = _mm256_set1_pd (a[0]);
  k = _mm256_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm256_set1_pd (b[i]);
      k2 = _mm256_mul_pd (k2, dx);
      f1 = f (_mm256_sub_pd (x, k2));
      f2 = f (_mm256_add_pd (x, k2));
      h = _mm256_set1_pd (a[i]);
      k = _mm256_fmadd_pd (h, _mm256_add_pd (f1, f2), k);
    }
#endif
  k = _mm256_mul_pd (k, dx);
  return k;
}

#endif

#ifdef __AVX512F__

/**
 * Function to calculate the absolute value of a __m512d vector.
 *
 * \return absolute value vector.
 */
static inline __m512d
jbm_abs_512 (const __m512d x)
{
  return _mm512_andnot_pd (_mm512_set1_pd (-0.0), x);
}

/**
 * Function to check small __m512d vectors.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline __mmask8
jbm_small_512 (const __m512d x)       ///< __m512d vector.
{
  return _mm512_cmp_pd_mask (jbm_abs_512 (x), _mm512_set1_pd (FLT_EPSILON),
                             _CMP_LT_OS);
}

/**
 * Function to calculate the __m512d vector with the components with lower
 * module in the [a, b] interval.
 * \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 *
 * \return modmin __m512d vector.
 */
static inline __m512d
jbm_modmin_512 (__m512d a,      ///< 1st __m512d vector.
                const __m512d b)      ///< 2nd __m512d vector.
{
  __m512d aa, ab, z;
  z = _mm512_setzero_pd ();
  ab = _mm512_mul_pd (a, b);
  a = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (ab, z, _CMP_LE_OS), a, z);
  aa = jbm_abs_512 (a);
  ab = jbm_abs_512 (b);
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (aa, ab, _CMP_GT_OS), a, b);
}

/**
 * Function to interchange 2 __m512d numbers.
 */
static inline void
jbm_change_512 (__m512d *restrict a,    ///< 1st __m512d vector pointer.
                __m512d *restrict b)    ///< 2nd __m512d vector pointer.
{
  __m512d c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the double of a __m512d vector.
 *
 * \return __m512d double.
 */
static inline __m512d
jbm_dbl_512 (const __m512d x)         ///< __m512d vector.
{
  return _mm512_add_pd (x, x);
}

/**
 * Function to calculate the square of the components of a __m512d vector.
 *
 * \return __m512d vector square.
 */
static inline __m512d
jbm_sqr_512 (const __m512d x)         ///< __m512d vector.
{
  return _mm512_mul_pd (x, x);
}

/**
 * Function to perform an extrapolation between 2 __m512d vectors of 2D points.
 *
 * \return __m512d vector of y-coordinates of the extrapolated points.
 */
static inline __m512d
jbm_extrapolate_512 (const __m512d x,
                     ///< __m512d vector of x-coordinates of the extrapolated
                     ///< points.
                     const __m512d x1,
                     ///< __m512d vector of x-coordinates of the 1st points.
                     const __m512d x2,
                     ///< __m512d vector of x-coordinates of the 2nd points.
                     const __m512d y1,
                     ///< __m512d vector of y-coordinates of the 1st points.
                     const __m512d y2)
                     ///< __m512d vector of y-coordinates of the 2nd points.
{
  __m512d d;
  d = _mm512_sub_pd (x, x1);
  return _mm512_fmadd_pd (d, _mm512_div_pd (_mm512_sub_pd (y2, y1),
                                            _mm512_sub_pd (x2, x1)), y1);
}

/**
 * Function to perform an interpolation between 2 __m512d vectors of 2D points.
 *
 * \return __m512d vector of y-coordinates of the interpolated points.
 */
static inline __m512d
jbm_interpolate_512 (const __m512d x,
                     ///< __m512d vector of x-coordinates of the interpolated
                     ///< points.
                     const __m512d x1,
                     ///< __m512d vector of x-coordinates of the 1st points.
                     const __m512d x2,
                     ///< __m512d vector of x-coordinates of the 2nd points.
                     const __m512d y1,
                     ///< __m512d vector of y-coordinates of the 1st points.
                     const __m512d y2)
                     ///< __m512d vector of y-coordinates of the 2nd points.
{
  __m512d k;
  k = jbm_extrapolate_512 (x, x1, x2, y1, y2);
  k = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, x1, _CMP_GT_OS), y1, k);
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (x, x2, _CMP_LT_OS), y2, k);
}

/**
 * Function to calculate the length of a __m512d vector of 2D segments.
 *
 * \return __m512d vector of segment lengths.
 */
static inline __m512d
jbm_v2_length_512 (const __m512d x1,
///< __m512d vector of x-coordinates of the 1st points defining the segment.
                   const __m512d y1,
///< __m512d vector of y-coordinates of the 1st points defining the segment.
                   const __m512d x2,
///< __m512d vector of x-coordinates of the 2nd points defining the segment.
                   const __m512d y2)
///< __m512d vector of y-coordinates of the 2nd points defining the segment.
{
  __m512d dx, dy;
  dx = _mm512_sub_pd (x2, x1);
  dy = _mm512_sub_pd (y2, y1);
  return _mm512_sqrt_pd (_mm512_add_pd (jbm_sqr_512 (dx), jbm_sqr_512 (dy)));
}

/**
 * Function to calculate the length of a __m512d vector of 3D segments.
 *
 * \return __m512d vector of segment lengths.
 */
static inline __m512d
jbm_v3_length_512 (const __m512d x1,
///< __m512d vector of x-coordinates of the 1st points defining the segments.
                   const __m512d y1,
///< __m512d vector of y-coordinates of the 1st points defining the segments.
                   const __m512d z1,
///< __m512d vector of z-coordinates of the 1st points defining the segments.
                   const __m512d x2,
///< __m512d vector of x-coordinates of the 2nd points defining the segments.
                   const __m512d y2,
///< __m512d vector of y-coordinates of the 2nd points defining the segments.
                   const __m512d z2)
///< __m512d vector of z-coordinates of the 2nd points defining the segments.
{
  __m512d dx, dy, dz;
  dx = _mm512_sub_pd (x2, x1);
  dx = jbm_sqr_512 (dx);
  dy = _mm512_sub_pd (y2, y1);
  dy = jbm_sqr_512 (dy);
  dz = _mm512_sub_pd (z2, z1);
  dz = jbm_sqr_512 (dz);
  return _mm512_sqrt_pd (_mm512_add_pd (dx, _mm512_add_pd (dy, dz)));
}

/**
 * Function to calculate a __m512d vector of 1st order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_1_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, _mm512_set1_pd (p[1]), _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 2nd order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_2_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_1_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 3rd order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_3_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_2_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 4th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_4_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_3_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 5th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_5_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_4_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 6th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_6_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_5_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 7th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_7_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_6_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 8th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_8_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_7_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 9th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_9_512 (const __m512d x,        ///< variable.
                      const double *p)        ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_8_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 10th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_10_512 (const __m512d x,       ///< variable.
                       const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_9_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate a __m512d vector of 11th order polynomials.
 *
 * \return __m512d vector of polynomial values.
 */
static inline __m512d
jbm_polynomial_11_512 (const __m512d x,       ///< variable.
                       const double *p)       ///< array of coefficients.
{
  return _mm512_fmadd_pd (x, jbm_polynomial_10_512 (x, p + 1),
                          _mm512_set1_pd (p[0]));
}

/**
 * Function to calculate the solution of a __m512d vector of reduced quadratic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^2+a\,x+b=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_quadratic_reduced_512 (__m512d a,
///< __m512d vector of 1st order coefficient of the equations.
                                 __m512d b,
///< __m512d vector of 0th order coefficient of the equations.
                                 const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                                 const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d k1, k2;
  k1 = _mm512_set1_pd (-0.5);
  a = _mm512_mul_pd (a, k1);
  b = _mm512_sqrt_pd (_mm512_sub_pd (jbm_sqr_512 (a), b));
  k1 = _mm512_add_pd (a, b);
  k2 = _mm512_sub_pd (a, b);
  k1 = _mm512_mask_blend_pd (_mm512_cmp_pd_mask (k1, x1, _CMP_LT_OS), k1, k2);
  return _mm512_mask_blend_pd (_mm512_cmp_pd_mask (k1, x2, _CMP_GT_OS), k1, k2);
}

/**
 * Function to calculate the solution of a __m512d vector of quadratic equations
 * in an interval \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512d vector of solution values.
 */
static inline __m512d
jbm_solve_quadratic_512 (const __m512d a,
///< __m512d vector of 2nd order coefficient of the equations.
                         const __m512d b,
///< __m512d vector of 1st order coefficient of the equations.
                         const __m512d c,
///< __m512d vector of 0th order coefficient of the equations.
                         const __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                         const __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d k1, k2;
  __mmask8 m;
  m = jbm_small_512 (a);
  k1 = jbm_solve_quadratic_reduced_512 (_mm512_div_pd (b, a),
                                        _mm512_div_pd (c, a), x1, x2);
  k2 = _mm512_div_pd (_mm512_sub_pd (_mm512_setzero_pd (), c), b);
  return _mm512_mask_blend_pd (m, k1, k2);
}

/**
 * Function to calculate the solution of a __m512d vector of reduced cubic
 * equations in an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$x^3+a\,x^2+b\,x+c=0\f$.
 *
 * \return __m512d vector of solution values.
 */
/*
static inline __m512d
jbm_solve_cubic_reduced (__m512d a,
                         ///< 2nd order coefficient of the equation.
                         __m512d b,
                         ///< 1st order coefficient of the equation.
                         __m512d c,
                         ///< 0th order coefficient of the equation.
                         __m512d x1,
                         ///< left limit of the solution interval.
                         __m512d x2)
                         ///< right limit of the solution interval.
{
  __m512d k0, k1, k2;
  a /= 3.;
  k0 = a * a;
  k1 = b / 3. - k0;
  k0 = (b * a - c) / 2. - a * k0;
  k2 = k1 * k1 * k1 + k0 * k0;
  if (k2 < 0.)
    {
      k1 = SQRT (-k1);
      k0 = ACOS (k0 / (k1 * k1 * k1)) / 3.;
      k1 *= 2.;
      k2 = k1 * COS (k0) - a;
      if (k2 < x1 || k2 > x2)
        {
          k2 = k1 * COS (k0 + 2. * JB_PI / 3.) - a;
          if (k2 < x1 || k2 > x2)
            k2 = k1 * COS (k0 - 2. * JB_PI / 3.) - a;
        }
    }
  else
    {
      k1 = SQRT (k2);
      k2 = k0 + k1;
      k2 = CBRT (k2);
      k0 -= k1;
      k2 += CBRT (k0) - a;
    }
  return k2;
}
*/

/**
 * Function to calculate the solution of a __m512d vector of cubic equations in
 * an interval \f$\left[x_1,x_2\right]\f$ in the form
 * \f$a\,x^3+b\,x^2+c\,x+d=0\f$.
 *
 * \return __m512d vector of solution values.
 */
/*
static inline __m512d
jbm_solve_cubic_512 (__m512d a,
///< __m512d vector of 3rd order coefficient of the equations.
                 __m512d b,
///< __m512d vector of 2nd order coefficient of the equations.
                 __m512d c,
///< __m512d vector of 1st order coefficient of the equations.
                 __m512d d,
///< __m512d vector of 0th order coefficient of the equations.
                         __m512d x1,
///< __m512d vector of left limits of the solution intervals.
                         __m512d x2)
///< __m512d vector of right limits of the solution intervals.
{
  __m512d m;
  m = jbm_small_512 (a);
  return
    _mm512_blendv_pd (jbm_solve_cubic_reduced (_mm512_div_pd (b, a),
                                            _mm512_div_pd (c, a),
                                            _mm512_div_pd (d, a), x1, x2),
                   jbm_solve_quadratic_512 (b, c, d, x1, x2), m);
}
*/

/**
 * Function to calculate the total (1st order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=0\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_total_512 (const __m512d d1 __attribute__((unused)),
                            ///< 1st flux limiter function parameter.
                            const __m512d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_setzero_pd ();
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_null_512 (const __m512d d1 __attribute__((unused)),
                           ///< 1st flux limiter function parameter.
                           const __m512d d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return _mm512_set1_pd (1.);
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_centred_512 (const __m512d d1,
                              ///< 1st flux limiter function parameter.
                              const __m512d d2)
                              ///< 2nd flux limiter function parameter.
{
  __mmask8 m;
  m = jbm_small_512 (d2);
  return _mm512_mask_blend_pd (m, _mm512_div_pd (d1, d2), _mm512_setzero_pd ());
}

/**
 * Function to calculate the superbee flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_superbee_512 (const __m512d d1,
                               ///< 1st flux limiter function parameter.
                               const __m512d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m512d r;
  __mmask8 m;
  r = _mm512_div_pd (d1, d2);
  r = _mm512_max_pd (_mm512_min_pd (jbm_dbl_512 (r), _mm512_set1_pd (1.)),
                     _mm512_min_pd (r, _mm512_set1_pd (2.)));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_minmod_512 (const __m512d d1,
                             ///< 1st flux limiter function parameter.
                             const __m512d d2)
                             ///< 2nd flux limiter function parameter.
{
  __m512d r;
  __mmask8 m;
  r = _mm512_min_pd (_mm512_div_pd (d1, d2), _mm512_set1_pd (1.));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the van Leer flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 * {1+\left|\frac{d_1}{d_2}\right|}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_VanLeer_512 (const __m512d d1,
                              ///< 1st flux limiter function parameter.
                              const __m512d d2)
                              ///< 2nd flux limiter function parameter.
{
  __m512d r, k;
  __mmask8 m;
  r = _mm512_div_pd (d1, d2);
  k = jbm_abs_512 (r);
  r = _mm512_div_pd (_mm512_add_pd (r, k),
                     _mm512_add_pd (_mm512_set1_pd (1.), k));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_VanAlbada_512 (const __m512d d1,
                                ///< 1st flux limiter function parameter.
                                const __m512d d2)
                                ///< 2nd flux limiter function parameter.
{
  __m512d r, k;
  __mmask8 m;
  r = _mm512_div_pd (d1, d2);
  k = jbm_sqr_512 (r);
  r = _mm512_div_pd (_mm512_add_pd (r, k),
                     _mm512_add_pd (_mm512_set1_pd (1.), k));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_minsuper_512 (const __m512d d1,
                               ///< 1st flux limiter function parameter.
                               const __m512d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m512d r;
  __mmask8 m;
  r = _mm512_min_pd (_mm512_div_pd (d1, d2), _mm512_set1_pd (2.));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_supermin_512 (const __m512d d1,
                               ///< 1st flux limiter function parameter.
                               const __m512d d2)
                               ///< 2nd flux limiter function parameter.
{
  __m512d r;
  __mmask8 m;
  r = _mm512_div_pd (d1, d2);
  r = _mm512_min_pd (jbm_dbl_512 (r), _mm512_set1_pd (1.));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_setzero_pd (), r);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_monotonized_central_512 (const __m512d d1,
///< 1st flux limiter function parameter.
                                          const __m512d d2)
///< 2nd flux limiter function parameter.
{
  __m512d r, rm;
  __mmask8 m;
  r = _mm512_div_pd (d1, d2);
  rm = _mm512_mul_pd (_mm512_set1_pd (0.5),
                      _mm512_add_pd (r, _mm512_set1_pd (1.)));
  m = _mm512_cmp_pd_mask (r, _mm512_set1_pd (3.), _CMP_LT_OS);
  rm = _mm512_mask_blend_pd (m, _mm512_set1_pd (2.), rm);
  m = _mm512_cmp_pd_mask (r, _mm512_set1_pd (1. / 3.), _CMP_GT_OS);
  rm = _mm512_mask_blend_pd (m, rm, jbm_dbl_512 (r));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_set1_pd (0.), rm);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_mean_512 (const __m512d d1,
                           ///< 1st flux limiter function parameter.
                           const __m512d d2)
                           ///< 2nd flux limiter function parameter.
{
  __m512d r;
  __mmask8 m;
  r = _mm512_mul_pd (_mm512_set1_pd (0.5),
                     _mm512_add_pd (_mm512_set1_pd (1.),
                                    _mm512_div_pd (d1, d2)));
  m = _mm512_cmp_pd_mask (_mm512_mul_pd (d1, d2), _mm512_set1_pd (FLT_EPSILON),
                          _CMP_GT_OS);
  return _mm512_mask_blend_pd (m, _mm512_set1_pd (0.), r);
}

/**
 * Function to do a flux limiter function (__m512d).
 *
 * \return flux limiter function value.
 */
static inline __m512d
jbm_flux_limiter_512 (const __m512d d1,
                      ///< 1st flux limiter function parameter.
                      const __m512d d2,
                      ///< 2nd flux limiter function parameter.
                      unsigned int type)
                      ///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin_512 (d1, d2);
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central_512 (d1, d2);
    }
  return jbm_flux_limiter_mean_512 (d1, d2);
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (__m512d).
 *
 * \return __m512d vector of integral values.
 */
static inline __m512d
jbm_integral_512 (__m512d (*f) (__m512d),
                  ///< pointer to the function to integrate.
                  const __m512d x1,   ///< left limit of the interval.
                  const __m512d x2)   ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2. };
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8. / 9., 5. / 9. },
    b[2] = { 0., 7.745966692414834e-1 };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    128. / 225.,
    4.786286704993665e-1,
    2.369268850561891e-1
  }, b[3] = {
    0.,
    5.384693101056831e-1,
    9.061798459386640e-1
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    4.179591836734694e-1,
    3.818300505051189e-1,
    2.797053914892767e-1,
    1.294849661688697e-1
  }, b[4] = {
    0.,
    4.058451513773972e-1,
    7.415311855993944e-1,
    9.491079123427585e-1
  };
#endif
  __m512d k, x, dx, h;
#if JBM_INTEGRAL_GAUSS_N > 1
  __m512d k2, f1, f2;
#endif
  unsigned int i;
  h = _mm512_set1_pd (0.5);
  dx = _mm512_mul_pd (h, _mm512_sub_pd (x2, x1));
  x = _mm512_mul_pd (h, _mm512_add_pd (x2, x1));
  k = _mm512_set1_pd (a[0]);
  k = _mm512_mul_pd (k, f (x));
#if JBM_INTEGRAL_GAUSS_N > 1
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = _mm512_set1_pd (b[i]);
      k2 = _mm512_mul_pd (k2, dx);
      f1 = f (_mm512_sub_pd (x, k2));
      f2 = f (_mm512_add_pd (x, k2));
      h = _mm512_set1_pd (a[i]);
      k = _mm512_fmadd_pd (h, _mm512_add_pd (f1, f2), k);
    }
#endif
  k = _mm512_mul_pd (k, dx);
  return k;
}

#endif

/**
 * Function to init data of a JBMFarray struct.
 */
static inline void
jbm_farray_init (JBMFarray *fa, ///< pointer to the JBMFarray struct.
                 const unsigned int n)   ///< number of array elements.
{
  fa->size = n * sizeof (JBFLOAT);
  fa->n = n;
  fa->last = n - 1;
}

/**
 * Function to create a new JBMFarray struct.
 *
 * \return pointer to the new JBMFarray struct.
 */
static inline JBMFarray*
jbm_farray_new (const unsigned int n)   ///< number of array elements.
{
  JBMFarray *fa;
  fa = (JBMFarray *) malloc (sizeof (JBMFarray));
  jbm_farray_init (fa, n);
#ifdef __AVX512F__
  fa->x = (JBFLOAT *) g_aligned_alloc (fa->size, 1, 64);
#else
#ifdef __AVX__
  fa->x = (JBFLOAT *) g_aligned_alloc (fa->size, 1, 32);
#else
#ifdef __SSE4_2__
  fa->x = (JBFLOAT *) g_aligned_alloc (fa->size, 1, 16);
#else
  fa->x = (JBFLOAT *) malloc (fa->size);
#endif
#endif
#endif
  if (!fa->x)
    {
      free (fa);
      return NULL;
    }
  return fa;
}

/**
 * Function to create a JBMFarray struct from an array of JBFLOAT numbers.
 *
 * \return pointer to the new JBMFarray struct.
 */
static inline JBMFarray*
jbm_farray_create (const JBFLOAT *x,    ///< array of JBFLOAT numbers.
                   const unsigned int n)        ///< number of array elements.
{
  JBMFarray *fa;
  fa = jbm_farray_new (n);
  memcpy (fa->x, x, fa->size);
  return fa;
}

/**
 * Function to set a JBMFarray struct from a JBFLOAT number.
 */
static inline void
jbm_farray_set1 (JBMFarray *fa, ///< pointer to the JBMFarray struct.
                 const JBFLOAT x,       ///< JBFLOAT number.
                 const unsigned int n)  ///< number of array elements.
{
  JBFLOAT *xa;
  unsigned int i;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  jbm_farray_init (fa, n);
  i = 0;
  xa = fa->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xa + i, _mm512_set1_pd (x));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xa + i, _mm256_set1_pd (x));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xa + i, _mm_set1_pd (x));
#endif
#endif
  for (; i < n; ++i)
    xa[i] = x;
}

/**
 * Function to set a JBMFarray struct from an array of JBFLOAT numbers.
 */
static inline void
jbm_farray_set (JBMFarray *fa,  ///< pointer to the JBMFarray struct.
                const JBFLOAT *x,     ///< array of JBFLOAT numbers.
                const unsigned int n)   ///< number of array elements.
{
  jbm_farray_init (fa, n);
  memcpy (fa->x, x, fa->size);
}

/**
 * Function to store a JBMFarray struct on an array of JBFLOAT numbers.
 */
static inline void
jbm_farray_store (JBMFarray *fa,        ///< pointer to the JBMFarray struct.
                  JBFLOAT *x)   ///< array of JBFLOAT numbers.
{
  memcpy (x, fa->x, fa->size);
}

/**
 * Function to free the memory used by a JBMFarray struct.
 */
static inline void
jbm_farray_destroy (JBMFarray * fa)     ///< pointer to the JBWFarray struct.
{
#if (defined(__AVX512F__) || defined(__AVX__) || defined(__SSE4_2__))
  g_aligned_free (fa->x);
#else
  free (fa->x);
#endif
  free (fa);
}

/**
 * Function to add 2 JBMFarray structs.
 */
static inline void
jbm_farray_add (JBMFarray *fr,  ///< result JBMFarray struct.
                const JBMFarray *f1,    ///< 1st addend JBMFarray struct.
                const JBMFarray *f2)    ///< 1st addend JBMFarray struct.
{
  JBFLOAT *xr, *x1, *x2;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  x1 = f1->x;
  x2 = f2->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xr + i, _mm512_add_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xr + i, _mm256_add_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xr + i,
                  _mm_add_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
#endif
#endif
  for (; i < n; ++i)
    xr[i] = x1[i] + x2[i];
}

/**
 * Function to subtract 2 JBMFarray structs.
 */
static inline void
jbm_farray_sub (JBMFarray *fr,  ///< result JBMFarray struct.
                const JBMFarray *f1,    ///< minuend JBMFarray struct.
                const JBMFarray *f2)    ///< subtrahend JBMFarray struct.
{
  JBFLOAT *xr, *x1, *x2;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  x1 = f1->x;
  x2 = f2->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xr + i, _mm512_sub_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xr + i, _mm256_sub_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xr + i,
                  _mm_sub_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
#endif
#endif
  for (; i < n; ++i)
    xr[i] = x1[i] - x2[i];
}

/**
 * Function to multiply a JBMFarray struct by a JBFLOAT number.
 */
static inline void
jbm_farray_mul1 (JBMFarray *fr, ///< result JBMFarray struct.
                 const JBMFarray *f1, ///< multiplier JBMFarray struct.
                 const JBFLOAT x2)    ///< multiplicand JBFLOAT number.
{
  JBFLOAT *xr, *x1;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  __m128d s2;
  unsigned int n2;
#endif
#ifdef __AVX__
  __m256d a4;
  unsigned int n4;
#endif
#ifdef __AVX512F__
  __m512d a8;
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  x1 = f1->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  if (n8)
    {
      a8 = _mm512_set1_pd (x2);
      for (; n8 > 0; --n8, i += 8)
        _mm512_store_pd (xr + i, _mm512_mul_pd (_mm512_load_pd (x1 + i), a8));
     }
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  if (n4)
    {
      a4 = _mm256_set1_pd (x2);
      for (; n4 > 0; --n4, i += 4)
        _mm256_store_pd (xr + i, _mm256_mul_pd (_mm256_load_pd (x1 + i), a4));
     }
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  if (n2)
    {
      s2 = _mm_set1_pd (x2);
      for (; n2 > 0; --n2, i += 2)
        _mm_store_pd (xr + i, _mm_mul_pd (_mm_load_pd (x1 + i), s2));
     }
#endif
#endif
  for (; i < n; ++i)
    xr[i] = x1[i] * x2;
}

/**
 * Function to divide a JBMFarray struct by a JBFLOAT number.
 */
static inline void
jbm_farray_div1 (JBMFarray *fr, ///< result JBMFarray struct.
                 const JBMFarray *f1, ///< dividend JBMFarray struct.
                 const JBFLOAT x2)    ///< divisor JBFLOAT number.
{
  JBFLOAT *xr, *x1;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  __m128d s2;
  unsigned int n2;
#endif
#ifdef __AVX__
  __m256d a4;
  unsigned int n4;
#endif
#ifdef __AVX__
  __m512d a8;
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  x1 = f1->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  if (n8)
    {
      a8 = _mm512_set1_pd (x2);
      for (; n8 > 0; --n8, i += 8)
        _mm512_store_pd (xr + i, _mm512_div_pd (_mm512_load_pd (x1 + i), a8));
     }
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  if (n4)
    {
      a4 = _mm256_set1_pd (x2);
      for (; n4 > 0; --n4, i += 4)
        _mm256_store_pd (xr + i, _mm256_div_pd (_mm256_load_pd (x1 + i), a4));
     }
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  if (n2)
    {
      s2 = _mm_set1_pd (x2);
      for (; n2 > 0; --n2, i += 2)
        _mm_store_pd (xr + i, _mm_div_pd (_mm_load_pd (x1 + i), s2));
     }
#endif
#endif
  for (; i < n; ++i)
    xr[i] = x1[i] / x2;
}

/**
 * Function to multiply 2 JBMFarray structs.
 */
static inline void
jbm_farray_mul (JBMFarray *fr,  ///< result JBMFarray struct.
                const JBMFarray *f1,  ///< multiplier JBMFarray struct.
                const JBMFarray *f2)  ///< multiplicand JBMFarray struct.
{
  JBFLOAT *xr, *x1, *x2;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  x1 = f1->x;
  x2 = f2->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xr + i, _mm512_mul_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xr + i, _mm256_mul_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xr + i,
                  _mm_mul_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
#endif
#endif
  for (; i < n; ++i)
    xr[i] = x1[i] * x2[i];
}

/**
 * Function to divide 2 JBMFarray structs.
 */
static inline void
jbm_farray_div (JBMFarray *fr,  ///< result JBMFarray struct.
                const JBMFarray *f1,  ///< dividend JBMFarray struct.
                const JBMFarray *f2)  ///< divisor JBMFarray struct.
{
  JBFLOAT *xr, *x1, *x2;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  x1 = f1->x;
  x2 = f2->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xr + i, _mm512_div_pd (_mm512_load_pd (x1 + i),
                                            _mm512_load_pd (x2 + i)));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xr + i, _mm256_div_pd (_mm256_load_pd (x1 + i),
                                            _mm256_load_pd (x2 + i)));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xr + i,
                  _mm_div_pd (_mm_load_pd (x1 + i), _mm_load_pd (x2 + i)));
#endif
#endif
  for (; i < n; ++i)
    xr[i] = x1[i] / x2[i];
}

/**
 * Function to calculate the double of a JBMFarray struct.
 */
static inline void
jbm_farray_dbl (JBMFarray *fr,  ///< result JBMFarray struct.
                const JBMFarray *fd)    ///< data JBMFarray struct.
{
  JBFLOAT *xr, *xd;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  xd = fd->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xr + i, jbm_dbl_512 (_mm512_load_pd (xd + i)));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xr + i, jbm_dbl_256 (_mm256_load_pd (xd + i)));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xr + i, jbm_dbl_128 (_mm_load_pd (xd + i)));
#endif
#endif
  for (; i < n; ++i)
    xr[i] = jbm_fdbl (xd[i]);
}

/**
 * Function to calculate the square of a JBMFarray struct.
 */
static inline void
jbm_farray_sqr (JBMFarray *fr,  ///< result JBMFarray struct.
                const JBMFarray *fd)    ///< data JBMFarray struct.
{
  JBFLOAT *xr, *xd;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  unsigned int n2;
#endif
#ifdef __AVX__
  unsigned int n4;
#endif
#ifdef __AVX512F__
  unsigned int n8;
#endif
#endif
  i = 0;
  n = fr->n;
  xr = fr->x;
  xd = fd->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX512F__
  n8 = n >> 3;
  for (; n8 > 0; --n8, i += 8)
    _mm512_store_pd (xr + i, jbm_sqr_512 (_mm512_load_pd (xd + i)));
#endif
#ifdef __AVX__
  n4 = (n - i) >> 2;
  for (; n4 > 0; --n4, i += 4)
    _mm256_store_pd (xr + i, jbm_sqr_256 (_mm256_load_pd (xd + i)));
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  for (; n2 > 0; --n2, i += 2)
    _mm_store_pd (xr + i, jbm_sqr_128 (_mm_load_pd (xd + i)));
#endif
#endif
  for (; i < n; ++i)
    xr[i] = jbm_fsqr (xd[i]);
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * JBMFarray.
 *
 * \return interval number.
 */
static inline unsigned int
jbm_farray_search (const JBMFarray *fa,       ///< JBMFarray struct.
                   const JBFLOAT x)   ///< number to search.
{
  JBFLOAT *xx;
  unsigned int i, j, n;
  n = fa->last;
  xx = fa->x;
  for (i = 0; n - i > 1;)
    {
      j = (i + n) >> 1;
      if (x < xx[j])
        n = j;
      else
        i = j;
    }
  return i;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * array of JBFLOAT numbers.
 * \return interval number, -1 if x<fa[0] or n-1 if x>fa[n-1].
 */
static inline int
jbm_farray_search_extended (const JBMFarray *fa,      ///< JBMFarray struct.
                            const JBFLOAT x)  ///< number to search.
{
  JBFLOAT *xx;
  xx = fa->x;
  if (x < xx[0])
    return -1;
  if (x >= xx[fa->last])
    return  (int) fa->last;
  return (int) jbm_farray_search (fa, x);
}

/**
 * Function to find the highest element of a JBMFarray struct.
 *
 * \return the highest value.
 */
static inline JBFLOAT
jbm_farray_max (const JBMFarray *fa)  ///< JBMFarray struct.
{
  JBFLOAT *xx;
  JBFLOAT k;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  __m128d s2;
  double sx[2];
  unsigned int n2;
#endif
#ifdef __AVX__
  __m256d a4;
  double ax[4];
  unsigned int n4;
#endif
#endif
  n = fa->n;
  xx = fa->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX__
  n4 = n >> 2;
  if (n4)
    {
      a4 = _mm256_load_pd (xx);
      i = 4;
      while (--n4 > 0)
        {
          a4 = _mm256_max_pd (a4, _mm256_load_pd (xx + i));
          i += 4;
        }
      _mm256_store_pd (ax, a4);
      s2 = _mm_max_pd (_mm_load_pd (ax), _mm_load_pd (ax + 2));
      n2 = (n - i) >> 1;
      if (n2)
        {
          s2 = _mm_max_pd (s2, _mm_load_pd (xx + i));
          i += 2;
        }
      _mm_store_pd (sx, s2);
      k = fmax (sx[0], sx[1]);
    }
  else
    {
      k = xx[0];
      i = 1;
    }
#else
#ifdef __SSE4_2__
  n2 = n >> 1;
  if (n2)
    {
      s2 = _mm_load_pd (xx);
      i += 2;
      while (--n2 > 0)
        {
          s2 = _mm_max_pd (s2, _mm_load_pd (xx + i));
          i += 2;
        }
      _mm_store_pd (sx, s2);
      k = fmax (sx[0], sx[1]);
    }
  else
    {
      k = xx[0];
      i = 1;
    }
#else
  k = xx[0];
  i = 1;
#endif
#endif
#else
  k = xx[0];
  i = 1;
#endif
  while (i < n)
    k = FMAX (k, xx[i++]);
  return k;
}

/**
 * Function to find the lowest element of a JBMFarray struct.
 *
 * \return the lowest value.
 */
static inline JBFLOAT
jbm_farray_min (const JBMFarray *fa)  ///< JBMFarray struct.
{
  JBFLOAT *xx;
  JBFLOAT k;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  __m128d s2;
  double sx[2];
  unsigned int n2;
#endif
#ifdef __AVX__
  __m256d a4;
  double ax[4];
  unsigned int n4;
#endif
#endif
  n = fa->n;
  xx = fa->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX__
  n4 = n >> 2;
  if (n4)
    {
      a4 = _mm256_load_pd (xx);
      i = 4;
      while (--n4 > 0)
        {
          a4 = _mm256_min_pd (a4, _mm256_load_pd (xx + i));
          i += 4;
        }
      _mm256_store_pd (ax, a4);
      s2 = _mm_min_pd (_mm_load_pd (ax), _mm_load_pd (ax + 2));
      n2 = (n - i) >> 1;
      if (n2)
        {
          s2 = _mm_min_pd (s2, _mm_load_pd (xx + i));
          i += 2;
        }
      _mm_store_pd (sx, s2);
      k = fmin (sx[0], sx[1]);
    }
  else
    {
      k = xx[0];
      i = 1;
    }
    
#else
#ifdef __SSE4_2__
  n2 = n >> 1;
  if (n2)
    {
      s2 = _mm_load_pd (xx);
      i = 2;
      while (--n2 > 0)
        {
          s2 = _mm_min_pd (s2, _mm_load_pd (xx + i));
          i += 2;
        }
      _mm_store_pd (sx, s2);
      k = fmin (sx[0], sx[1]);
    }
  else
    {
      k = xx[0];
      i = 1;
    }
#else
  k = xx[0];
  i = 1;
#endif
#endif
#else
  k = xx[0];
  i = 1;
#endif
  while (i < n)
    k = FMIN (k, xx[i++]);
  return k;
}

/**
 * Function to find the highest and the lowest elements of a JBMFarray struct.
 */
static inline void
jbm_farray_maxmin (const JBMFarray *fa,       ///< JBMFarray struct.
                   JBFLOAT *max,        ///< the highest value.
                   JBFLOAT *min)        ///< the lowest value.
{
  JBFLOAT *xx;
  JBFLOAT kmax, kmin;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __SSE4_2__
  __m128d s2, smax2, smin2;
  double smax[2], smin[2];
  unsigned int n2;
#endif
#ifdef __AVX__
  __m256d a4, amax4, amin4;
  double amax[4], amin[4];
  unsigned int n4;
#endif
#endif
  n = fa->n;
  xx = fa->x;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX__
  n4 = n >> 2;
  if (n4)
    {
      amax4 = amin4 = _mm256_load_pd (xx);
      i = 4;
      while (--n4 > 0)
        {
          a4 = _mm256_load_pd (xx + i);
          amax4 = _mm256_max_pd (amax4, a4); 
          amin4 = _mm256_min_pd (amin4, a4); 
          i += 4;
        }
      _mm256_store_pd (amax, amax4);
      smax2 = _mm_max_pd (_mm_load_pd (amax), _mm_load_pd (amax + 2));
      _mm256_store_pd (amin, amin4);
      smin2 = _mm_min_pd (_mm_load_pd (amin), _mm_load_pd (amin + 2));
      n2 = (n - i) >> 1;
      if (n2)
        {
          s2 = _mm_load_pd (xx + i);
          smax2 = _mm_max_pd (smax2, s2);
          smin2 = _mm_min_pd (smin2, s2);
          i += 2;
        }
      _mm_store_pd (smax, smax2);
      kmax = fmax (smax[0], smax[1]);
      _mm_store_pd (smin, smin2);
      kmin = fmin (smin[0], smin[1]);
    }
  else
    {
      kmax = xx[0], kmin = xx[0];
      i = 1;
    }
#else
#ifdef __SSE4_2__
  n2 = n >> 1;
  if (n2)
    {
      smax2 = smin2 = _mm_load_pd (xx);
      i = 2;
      while (--n2 > 0)
        {
          s2 = _mm_load_pd (xx + i);
          smax2 = _mm_max_pd (smax2, s2);
          smin2 = _mm_min_pd (smin2, s2);
          i += 2;
        }
      _mm_store_pd (smax, smax2);
      kmax = fmax (smax[0], smax[1]);
      _mm_store_pd (smin, smin2);
      kmin = fmin (smin[0], smin[1]);
    }
  else
    {
      kmax = xx[0], kmin = xx[0];
      i = 1;
    }
#else
  kmax = xx[0], kmin = xx[0];
  i = 1;
#endif
#endif
#else
  kmax = xx[0], kmin = xx[0];
  i = 1;
#endif
  while (i < n)
    {
      if (kmax < xx[i])
        kmax = xx[i];
      else if (kmin > xx[i])
        kmin = xx[i];
      ++i;
    }
  *max = kmax, *min = kmin;
}

/**
 * Function to interchange 2 JBMFarray structs.
 */
static inline void
jbm_farray_change (JBMFarray *restrict fa,      ///< 1st JBMFarray struct.
                   JBMFarray *restrict fb)      ///< 2nd JBMFarray struct.
{
  JBMFarray fc[1];
  size_t s;
  s = sizeof (JBMFarray);
  memcpy (fc, fa, s);
  memcpy (fa, fb, s);
  memcpy (fb, fc, s);
}

/**
 * Function to calculate the y-coordinate of a 2D point interpolated 
 * between a tabular function defined by 2 JBMFarray structs.
 *
 * \return y-coordinate of the interpolated point.
 */
static inline JBFLOAT
jbm_farray_interpolate (const JBMFarray *fa,
///< JBMFarray struct defining the increasingly sorted array of x-coordinates.
                        const JBMFarray *fb,
///< JBMFarray struct defining the array of y-coordinates.
                        const JBFLOAT x)      ///< x-coordinate of the point.
{
  JBFLOAT *fx, *fy;
  unsigned int i;
  i = jbm_farray_search (fa, x);
  fy = fb->x;
  if (i == fa->last)
    return fy[i];
  fx = fa->x;
  return jbm_interpolate (x, fx[i], fx[i + 1], fy[i], fy[i + 1]);
}

/**
 * Function to merge 2 increasingly sorted JBMFarray structs.
 *
 * \return resulting JBMFarray struct.
 */
static inline JBMFarray *
jbm_farray_merge (JBMFarray *restrict fa,
                  ///< pointer to the 1st increasingly sorted JBMFarray struct.
                  JBMFarray *restrict fb)
                  ///< pointer to the 2nd increasingly sorted JBMFarray struct.
{
  JBMFarray *fc;
  JBFLOAT *xa, *xb, *xc;
  unsigned int i, j, k, na, nb;
  na = fa->n;
  nb = fb->n;
  fc = jbm_farray_new (na + nb);
  if (!fc)
    return NULL;
  xa = fa->x;
  xb = fb->x;
  xc = fc->x;
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
  jbm_farray_init (fc, k);
  return fc;
}

/**
 * Function to integrate a tabular function, defined by 2 JBMFarray structs,in
 * an interval.
 *
 * \return integral value.
 */
static inline JBFLOAT
jbm_farray_integral (JBMFarray *restrict fx,
///< incresingly sorted JBMFarray defining the x-coordinates of the tabular
///< function.
                     JBMFarray *restrict fy,
///< JBFarray defining the y-coordinates of the tabular function.
                     JBFLOAT x1,
                     ///< left limit of the integration interval.
                     JBFLOAT x2)
                     ///< right limit of the integration interval.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c05 = 0.5f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c05 = 0.5;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c05 = 0.5L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c05 = 0.5Q;
#endif
  JBFLOAT *x, *y, *yy, *xx;
  JBFLOAT I, y1;
  int i;
  unsigned int n, last;
  n = fx->n;
  y = fy->x;
  if (n == 0)
    {
      I = y[0] * (x2 - x1);
      goto exit1;
    }
  x = fx->x;
  i = jbm_farray_search_extended (fx, x1);
  last = fx->last;
  if (i < 0)
    {
      if (x2 <= x[0])
        {
          I = y[0] * (x2 - x1);
          goto exit1;
        }
      I = y[0] * (x[0] - x1);
      i = 0;
      x1 = x[0];
      y1 = y[0];
      xx = x;
      yy = y;
    }
  else if (i == (int) last)
    {
      I = y[i] * (x2 - x1);
      goto exit1;
    }
  else
    {
      I = c0;
      xx = x + i;
      yy = y + i;
      y1 = jbm_extrapolate (x1, xx[0], xx[1], yy[0], yy[1]);
    }
  if (x2 < xx[1])
    {
      I += c05 * (y1 + jbm_extrapolate (x2, xx[0], xx[1], yy[0], yy[1]))
        * (x2 - x1);
      goto exit1;
    }
  I += c05 * (y1 + yy[1]) * (xx[1] - x1);
  if (++i == (int) last)
    {
      I += yy[1] * (x2 - xx[1]);
      goto exit1;
    }
  while (++i < (int) last && x2 > xx[2])
    {
      ++xx, ++yy;
      I += c05 * (yy[0] + yy[1]) * (xx[1] - xx[0]);
    }
  if (i == (int) last)
    I += yy[2] * (x2 - xx[1]);
  else if (x2 < xx[2])
    I += c05 * (yy[1] + jbm_extrapolate (x2, xx[1], xx[2], yy[1], yy[2]))
      * (x2 - xx[1]);
exit1:
  return I;
}

/**
 * Function to calculate the mean square error between 2 tabular functions
 * (JBFLOAT).
 *
 * \return mean square error.
 */
static inline JBFLOAT
jbm_farray_mean_square_error (JBMFarray * fxa,
///< incresingly sorted JBMFarray struct defining the x-coordinates of the 1st
///< tabular function.
                              JBMFarray * fya,
///< JBMFarray struct defining the y-coordinates of the 1st tabular function.
                              JBMFarray * fxr,
///< incresingly sorted JBMFarray struct defining the x-coordinates of the 2nd
///< tabular function.
                              JBMFarray * fyr)
///< JBMFarray struct defining the y-coordinates of the 2nd tabular function.
{
#if JBM_LOW_PRECISION == 1
  JBFLOAT k = 0.f;
#elif JBM_LOW_PRECISION == 2
  JBFLOAT k = 0.;
#elif JBM_LOW_PRECISION == 3
  JBFLOAT k = 0.L;
#elif JBM_LOW_PRECISION == 4
  JBFLOAT k = 0.Q;
#endif
  JBFLOAT *xa, *ya, *xr, *yr;
  unsigned int i, j, lastr, na;
  lastr = fxr->last;
  na = fxa->n;
  xa = fxa->x;
  ya = fya->x;
  xr = fxr->x;
  yr = fyr->x;
  for (i = 0; i < na && xa[i] < xr[0]; ++i)
    k += jbm_fsqr (ya[i] - yr[0]);
  for (j = 0; i < na; ++i)
    {
      while (j < lastr && xa[i] > xr[j + 1])
        ++j;
      if (j == lastr)
        for (; i < na; ++i)
          k += jbm_fsqr (ya[i] - yr[lastr]);
      else
        k += jbm_fsqr (ya[i] - jbm_extrapolate (xa[i], xr[j], xr[j + 1], yr[j],
                                                yr[j + 1]));
    }
  k /= na;
  return k;
}

/**
 * Function to calculate the root mean square error between 2 tabular functions
 * (JBFLOAT).
 *
 * \return root mean square error.
 */
static inline JBFLOAT
jbm_farray_root_mean_square_error (JBMFarray * fxa,
///< incresingly sorted JBMFarray struct defining the x-coordinates of the 1st
///< tabular function.
                                   JBMFarray * fya,
///< JBMFarray struct defining the y-coordinates of the 1st tabular function.
                                   JBMFarray * fxr,
///< incresingly sorted JBMFarray struct defining the x-coordinates of the 2nd
///< tabular function.
                                   JBMFarray * fyr)
///< JBMFarray struct defining the y-coordinates of the 2nd tabular function.
{
  return SQRT (jbm_farray_mean_square_error (fxa, fya, fxr, fyr));
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the insertion method.
 */
static inline void
jbm_index_sort_insertion (JBFLOAT *restrict x,  ///< array of JBFLOAT numbers.
                          unsigned int *restrict ni,    ///< array of indexes.
                          unsigned int n)       ///< number of array elements.
{
  JBFLOAT xi;
  int j;
  unsigned int i, ii;
  for (i = 0; ++i < n;)
    {
      ii = ni[i];
      xi = x[ii];
      for (j = (int) i; --j >= 0 && x[ni[j]] < xi;)
        ni[j + 1] = ni[j];
      ni[j + 1] = ii;
    }
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the interchange method.
 */
static inline void
jbm_index_sort_interchange (JBFLOAT *restrict x,
                            ///< array of JBFLOAT numbers.
                            unsigned int *restrict ni,  ///< array of indexes.
                            unsigned int n)     ///< number of array elements.
{
  JBFLOAT xi, xj;
  int j;
  unsigned int i;
  for (i = n; --i > 0;)
    {
      xi = x[ni[i]];
      for (j = (int) i; --j >= 0;)
        {
          xj = x[ni[j]];
          if (xj < xi)
            {
              xi = xj;
              jbm_changeu (ni + i, ni + j);
            }
        }
    }
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the merge method.
 */
static inline void
jbm_index_sort_merge (JBFLOAT *restrict x,      ///< array of JBFLOAT numbers.
                      unsigned int *restrict ni,        ///< array of indexes.
                      unsigned int n)   ///< number of the array elements.
{
  unsigned int nn[n];
  unsigned int *ni1, *ni2, *nj, *nk, *nt;
  int k;
  unsigned int i1, i2, j, l, last;
  j = JBM_INDEX_SORT_MERGE_MIN;
  last = n - 1;
  if (last <= j)
    {
      jbm_index_sort_insertion (x, ni, n);
      return;
    }
  k = last / j;
  if (last % j)
    ++k;
  j = last / k;
  if (last % k)
    ++j;
  for (l = 0; l < n - j; l += j)
    jbm_index_sort_insertion (x, ni + l, j);
  if (l < last)
    jbm_index_sort_insertion (x, ni + l, n - l);
  for (nk = ni, nj = nn; j < n; j *= 2)
    {
      for (ni1 = nk, l = 0, k = last / j; (k -= 2) >= 0; ni1 = ni2 + j)
        {
          ni2 = ni1 + j;
          for (i1 = i2 = 0; i1 < j && i2 < j;)
            {
              if (x[ni1[i1]] > x[ni2[i2]])
                nj[l++] = ni1[i1++];
              else
                nj[l++] = ni2[i2++];
            }
          while (i2 < j)
            nj[l++] = ni2[i2++];
          while (i1 < j)
            nj[l++] = ni1[i1++];
        }
      if (k == -1)
        {
          ni2 = ni1 + j;
          for (k = last - l - j, i1 = i2 = 0; i1 < j && k >= (int) i2;)
            {
              if (x[ni1[i1]] > x[ni2[i2]])
                nj[l++] = ni1[i1++];
              else
                nj[l++] = ni2[i2++];
            }
          while (k >= (int) i2)
            nj[l++] = ni2[i2++];
          while (j > i1)
            nj[l++] = ni1[i1++];
        }
      for (; l < n; ++l)
        nj[l] = nk[l];
      nt = nk;
      nk = nj;
      nj = nt;
    }
  if (ni != nk)
    memcpy (ni, nk, l * sizeof (unsigned int));
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the optimal method.
 */
static inline void
jbm_index_sort (JBFLOAT *restrict x,    ///< array of JBFLOAT numbers.
                unsigned int *restrict ni,      ///< array of indexes.
                unsigned int n) ///< number of array elements.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
    ni[i] = i;
  if (n < JBM_INDEX_SORT_FLASH_MIN)
    jbm_index_sort_insertion (x, ni, n);
  else
    jbm_index_sort_flash (x, ni, n);
}

/**
 * Function to create a sorted index from the highest to the lowest of an array
 * of JBFLOAT numbers by the optimal method.
 *
 * \return elements number of the sorted array.
 */
static inline int
jbm_index_sort_extended (JBFLOAT *restrict x,
                         ///< array of JBFLOAT numbers to sort.
                         JBFLOAT **restrict xr,
///< pointer to the array of sorted JBFLOAT numbers elliminating duplicated
///< numbers. It has to be freed with free.
                         unsigned int **restrict ni,
///< point to the array of sorted indexes. It has to be freed with free.
                         unsigned int n)
                         ///< elements number of the array to sort.
{
  unsigned int nk[n], nj[n];
  JBFLOAT k1, k2;
  unsigned int i, j = 0;
  *ni = (unsigned int *) malloc (n * sizeof (unsigned int));
  *xr = (JBFLOAT *) malloc (n * sizeof (JBFLOAT));
  if (!*xr)
    {
      jb_free_null ((void **) ni);
      fprintf (stderr, "JBM index sort extended: no enough memory\n");
      goto index_exit;
    }
  jbm_index_sort (x, nk, n);
  i = n - 1;
  k2 = x[nk[i]];
  nj[i] = 0;
  (*xr)[0] = k2;
  for (; i-- > 0; k2 = k1)
    {
      k1 = x[nk[i]];
      if (k1 != k2)
        (*xr)[++j] = k1;
      nj[i] = j;
    }
  for (i = 0; i < n; ++i)
    (*ni)[nk[i]] = nj[i];
index_exit:
  return j;
}

/**
 * Function to solve a linear equations system stored in a matrix with format:
 * \f$\left(\begin{array}{cccc|c}
 * x_{0,0} & x_{0,1} & \cdots & x_{0,n-1} & x_{0,n}\\
 * x_{1,0} & x_{1,1} & \cdots & x_{1,n-1} & x_{1,n}\\
 * & & \cdots \\
 * x_{n-1,0} & x_{n-1,1} & \cdots & x_{n-1,n-1} & x_{n-1,n}
 * \end{array}\right)\f$.
 * Results are stored in the n+1-th column:
 * \f$\left(x_{0,n},\;x_{1,n},\;\cdots,\;x_{n-1,n}\right)\f$.
 * It modifies the x matrix (JBFLOAT).
 */
static inline void
jbm_matrix_solve (JBFLOAT *x,   ///< matrix storing the linear equations system.
                  unsigned int n)       ///< number of matrix rows.
{
  JBMFarray *fa, *fa2;
  JBFLOAT *f, *g;
  JBFLOAT k1, k2;
  size_t size;
  unsigned int i, j, k, last;
  // Setting n to the number of row elements
  last = n++;
  fa = jbm_farray_new (n);
  fa2 = jbm_farray_new (n);
  // Scaling every equation to reduce rounding effects.
  for (i = n, f = x; --i > 0; f += n)
    {
      jbm_farray_set (fa, f, n);
      jbm_farray_maxmin (fa, &k1, &k2);
      k1 = FMAX (FABS (k1), FABS (k2));
      jbm_farray_div1 (fa, fa, k1);
      jbm_farray_store (fa, f);
    }
  // Gaussian elimination
  for (i = last, f = x; --i > 0; f += n + 1)
    {
      // Obtaining the highest pivot element        
      k1 = FABS (*f);
      for (k = j = i, g = f; j-- > 0;)
        {
          g += n;
          k2 = FABS (*g);
          if (k2 > k1)
            {
              k1 = k2;
              k = j;
            }
        }
      // Interchanging rows
      if (k != i)
        {
          g = f + (i - k) * n;
          size = (i + 2) * sizeof (JBFLOAT);
          memcpy (fa->x, f, size);
          memcpy (f, g, size);
          memcpy (g, fa->x, size);
        }
      // Eliminating column
      for (j = i, g = f + n; j-- > 0; g += n)
        {
          k1 = *g / *f;
          jbm_farray_set (fa, g + 1, i + 1);
          jbm_farray_set (fa2, f + 1, i + 1);
          jbm_farray_mul1 (fa2, fa2, k1);
          jbm_farray_sub (fa, fa, fa2);
          jbm_farray_store (fa, g + 1); 
        }
    }
  // Retrieving solutions
  f = x + n * last - 1;
  for (i = 0; ++i < n; f -= n)
    {
      // Solution
      k1 = *f /= *(f - i);
      // Eliminating column
      for (j = n, g = f - n; --j > i; g -= n)
        *g -= *(g - i) * k1;
    }
  jbm_farray_destroy (fa2);
  jbm_farray_destroy (fa);
}

/**
 * Function to solve a linear equations system stored in a tridiagonal matrix
 * with format: \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &         & H_0\\
 * C_0 & D_1    & E_1     &         & H_1\\
 *     & \ddots & \ddots  & \ddots  & \vdots\\
 *     &        & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * Results are stored in the H array. It modifies D and H arrays (JBFLOAT).
 */
static inline void
jbm_matrix_solve_tridiagonal (JBFLOAT *restrict C,
                              ///< left diagonal array.
                              JBFLOAT *restrict D,
                              ///< central diagonal array.
                              JBFLOAT *restrict E,
                              ///< right diagonal array.
                              JBFLOAT *restrict H,      ///< final column array.
                              unsigned int n)   ///< number of matrix rows.
{
  JBFLOAT k;
  unsigned int i;
  --n;
  for (i = 0; i < n; ++i)
    {
      k = C[i] / D[i];
      D[i + 1] -= k * E[i];
      H[i + 1] -= k * H[i];
    }
  H[i] /= D[i];
  while (i--)
    H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
}

/**
 * Function to solve a linear equations system stored in a tridiagonal matrix
 * with format: \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &         & H_0\\
 * C_0 & D_1    & E_1     &         & H_1\\
 *     & \ddots & \ddots  & \ddots  & \vdots\\
 *     &        & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * avoiding zero divisions. Results are stored in the H array. It modifies D and
 * H arrays (JBFLOAT).
 */
static inline void
jbm_matrix_solve_tridiagonal_zero (JBFLOAT *restrict C,
                                   ///< left diagonal array.
                                   JBFLOAT *restrict D,
                                   ///< central diagonal array.
                                   JBFLOAT *restrict E,
                                   ///< right diagonal array.
                                   JBFLOAT *restrict H,
                                   ///< final column array.
                                   unsigned int n)
                                   ///< number of matrix rows.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT k;
  unsigned int i;
  --n;
  for (i = 0; i < n; ++i)
    if (!jbm_small (D[i]))
      {
        k = C[i] / D[i];
        D[i + 1] -= k * E[i];
        H[i + 1] -= k * H[i];
      }
  if (jbm_small (D[i]))
    H[i] = c0;
  else
    H[i] /= D[i];
  while (i--)
    if (jbm_small (D[i]))
      H[i] = c0;
    else
      H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
}

/**
 * Function to solve a linear equations system stored in a pentadiagonal matrix
 * with format: \f$\left(\begin{array}{cccccc|c}
 * D_0 & E_0    & F_0     &         &         &         & H_0\\
 * C_0 & D_1    & E_1     & F_1     &         &         & H_1\\
 * B_0 & C_1    & D_2     & E_2     & F_2     &         & H_2\\
 *     & \ddots & \ddots  & \ddots  & \ddots  & \ddots  & \vdots\\
 *     &        &         & B_{n-3} & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * Results are stored in the H array. It modifies C, D, E and H arrays 
 * (JBFLOAT).
 */
static inline void
jbm_matrix_solve_pentadiagonal (JBFLOAT *restrict B,
                                ///< double-left diagonal array.
                                JBFLOAT *restrict C,
                                ///< left diagonal array.
                                JBFLOAT *restrict D,
                                ///< central diagonal array.
                                JBFLOAT *restrict E,
                                ///< right diagonal array.
                                JBFLOAT *restrict F,
                                ///< double-right diagonal array.
                                JBFLOAT *restrict H,    ///< final column array.
                                unsigned int n)  ///< number of matrix rows.
{
  JBFLOAT k;
  unsigned int i;
  --n;
  for (i = 0; i < n - 1; ++i)
    {
      k = C[i] / D[i];
      D[i + 1] -= k * E[i];
      E[i + 1] -= k * F[i];
      H[i + 1] -= k * H[i];
      k = B[i] / D[i];
      C[i + 1] -= k * E[i];
      D[i + 2] -= k * F[i];
      H[i + 2] -= k * H[i];
    }
  k = C[i] / D[i];
  D[i + 1] -= k * E[i];
  H[i + 1] -= k * H[i];
  H[i + 1] /= D[i + 1];
  H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
  while (i--)
    H[i] = (H[i] - E[i] * H[i + 1] - F[i] * H[i + 2]) / D[i];
}

/**
 * Function to solve a linear equations system stored in a pentadiagonal matrix
 * with format: \f$\left(\begin{array}{cccccc|c}
 * D_0 & E_0    & F_0     &         &         &         & H_0\\
 * C_0 & D_1    & E_1     & F_1     &         &         & H_1\\
 * B_0 & C_1    & D_2     & E_2     & F_2     &         & H_2\\
 *     & \ddots & \ddots  & \ddots  & \ddots  & \ddots  & \vdots\\
 *     &        &         & B_{n-3} & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * avoiding zero divisions. Results are stored in the H array. It modifies C, D,
 * E and H arrays (JBFLOAT).
 */
static inline void
jbm_matrix_solve_pentadiagonal_zero (JBFLOAT *restrict B,
                                     ///< double-left diagonal array.
                                     JBFLOAT *restrict C,
                                     ///< left diagonal array.
                                     JBFLOAT *restrict D,
                                     ///< central diagonal array.
                                     JBFLOAT *restrict E,
                                     ///< right diagonal array.
                                     JBFLOAT *restrict F,
                                     ///< double-right diagonal array.
                                     JBFLOAT *restrict H,
                                     ///< final column array.
                                     unsigned int n)
                                     ///< number of matrix rows.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT k;
  unsigned int i;
  --n;
  for (i = 0; i < n - 1; ++i)
    if (!jbm_small (D[i]))
      {
        k = C[i] / D[i];
        D[i + 1] -= k * E[i];
        E[i + 1] -= k * F[i];
        H[i + 1] -= k * H[i];
        k = B[i] / D[i];
        C[i + 1] -= k * E[i];
        D[i + 2] -= k * F[i];
        H[i + 2] -= k * H[i];
      }
  if (!jbm_small (D[i]))
    {
      k = C[i] / D[i];
      D[i + 1] -= k * E[i];
      H[i + 1] -= k * H[i];
    }
  if (jbm_small (D[i + 1]))
    H[i + 1] = c0;
  else
    H[i + 1] /= D[i + 1];
  if (jbm_small (D[i]))
    H[i] = c0;
  else
    H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
  while (i--)
    if (jbm_small (D[i]))
      H[i] = c0;
    else
      H[i] = (H[i] - E[i] * H[i + 1] - F[i] * H[i + 2]) / D[i];
}

/**
 * Function to calculate the coefficients of a linear regression adjusted by 
 * minimum squares: \f$y=a+b\,x\f$ (JBFLOAT).
 */
static inline void
jbm_regression_linear (JBMFarray *fx,
                       ///< JBMFarray struct of point x-coordinates.
                       JBMFarray *fy,
                       ///< JBMFarray struct of point y-coordinates.
                       JBFLOAT *a,
                       ///< pointer to the 0th order regression coefficient.
                       JBFLOAT *b)
                       ///< pointer to the 1st order regression coefficient.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT *x, *y;
  JBFLOAT syx, sy, sxx, sx;
  unsigned int i, n;
#if JBM_LOW_PRECISION < 3
#ifdef __AVX__
  double t4[4];
  __m256d x4, y4, syx4, sy4, sxx4, sx4;
  unsigned int n4;
#endif
#ifdef __SSE4_2__
  double t2[2];
  __m128d x2, y2, syx2, sy2, sxx2, sx2;
  unsigned int n2;
#endif
#endif
  x = fx->x;
  y = fy->x;
  n = fx->n;
  i = 0;
  syx = sy = sxx = sx = c0;
#ifdef __SSE4_2__
  sy2 = _mm_setzero_pd ();
  sx2 = _mm_setzero_pd ();
  syx2 = _mm_setzero_pd ();
  sxx2 = _mm_setzero_pd ();
#endif
#ifdef __AVX__
  n4 = n >> 2;
  sy4 = _mm256_setzero_pd ();
  sx4 = _mm256_setzero_pd ();
  syx4 = _mm256_setzero_pd ();
  sxx4 = _mm256_setzero_pd ();
  if (n4)
    {
      for (; n4 > 0; --n4, i += 4)
        {
          y4 = _mm256_load_pd (y + i);
          x4 = _mm256_load_pd (x + i);
          sy4 = _mm256_add_pd (sy4, y4);
          sx4 = _mm256_add_pd (sx4, x4);
          syx4 = _mm256_fmadd_pd (y4, x4, syx4);
          sxx4 = _mm256_fmadd_pd (x4, x4, sxx4);
        }
      _mm256_store_pd (t4, sy4);
      sy2 = _mm_load_pd (t4);
      sy2 = _mm_add_pd (sy2, _mm_load_pd (t4 + 2));
      _mm256_store_pd (t4, sx4);
      sx2 = _mm_load_pd (t4);
      sx2 = _mm_add_pd (sx2, _mm_load_pd (t4 + 2));
      _mm256_store_pd (t4, syx4);
      syx2 = _mm_load_pd (t4);
      syx2 = _mm_add_pd (syx2, _mm_load_pd (t4 + 2));
      _mm256_store_pd (t4, sxx4);
      sxx2 = _mm_load_pd (t4);
      sxx2 = _mm_add_pd (sxx2, _mm_load_pd (t4 + 2));
    }
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  if (n2)
    {
      for (; n2 > 0; --n2, i += 2)
        {
          y2 = _mm_load_pd (y + i);
          x2 = _mm_load_pd (x + i);
          sy2 = _mm_add_pd (sy2, y2);
          sx2 = _mm_add_pd (sx2, x2);
#ifdef __AVX
          syx2 = _mm_fmadd_pd (y2, x2, syx2);
          sxx2 = _mm_fmadd_pd (x2, x2, sxx2);
#else
          syx2 = _mm_add_pd (syx2, _mm_mul_pd (y2, x2));
          sxx2 = _mm_add_pd (sxx2, _mm_mul_pd (x2, x2));
#endif
        }
      _mm_store_pd (t2, sy2);
      sy = t2[0] + t2[1];
      _mm_store_pd (t2, sx2);
      sx = t2[0] + t2[1];
      _mm_store_pd (t2, syx2);
      syx = t2[0] + t2[1];
      _mm_store_pd (t2, sxx2);
      sxx = t2[0] + t2[1];
    }
#endif
  for (; i < n; ++i)
    {
      sy += y[i];
      syx += x[i] * y[i];
      sxx += x[i] * x[i];
      sx += x[i];
    }
  *b = (n * syx - sy * sx) / (n * sxx - sx * sx);
  *a = (sy - *b * sx) / n;
}

/**
 * Function to calculate the coefficients of an exponential regression adjusted
 * by minimum squares: \f$y=a\,x^b\f$ (JBFLOAT). It modifies the x and y arrays.
 */
static inline void
jbm_regression_exponential (JBMFarray *fx,
                            ///< JBMFarray struct of point x-coordinates.
                            JBMFarray *fy,
                            ///< JBMFarray struct of point y-coordinates.
                            JBFLOAT *a,
///< pointer to the constant parameter regression coefficient.
                            JBFLOAT *b)
///< pointer to the exponent regression coefficient.
{
  JBFLOAT *x, *y;
  unsigned int i, n;
  x = fx->x;
  y = fy->x;
  n = fx->n;
  for (i = 0; i < n; ++i)
    x[i] = LOG (x[i]), y[i] = LOG (y[i]);
  jbm_regression_linear (fx, fy, a, b);
  *a = EXP (*a);
}

/**
 * Function to calculate the coefficients of a polynomial regression adjusted
 * by minimum squares: \f$y=A_0+A_1\,x+A_2\,x^2+\cdots\f$ (JBFLOAT).
 */
static inline void
jbm_regression_polynomial (JBMFarray *fx,
                           ///< JBMFarray struct of point x-coordinates.
                           JBMFarray *fy,
                           ///< JBMFarray struct of point y-coordinates.
                           JBMFarray **fA,
///< pointer to the JBMFarray struct of regression coefficients. It has to be
///< freed with free.
                           unsigned int m)
                           ///< order of the polynomial regression.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q;
#endif
  JBMFarray *fxx, *fyx;
  JBFLOAT B[(m + 1) * (m + 2)];
  JBFLOAT *k, *x, *y, *xx, *yx;
  JBFLOAT zx, zy;
  unsigned int i, j, n;
#ifdef __AVX__
  __m256d xx4[m + m + 1], yx4[m + 1];
  __m256d x4, y4, zx4, zy4;
  double t4[4];
  unsigned int n4;
#endif
#ifdef __SSE4_2__
  __m128d xx2[m + m + 1], yx2[m + 1];
  __m128d x2, y2, zx2, zy2;
  double t2[2];
  unsigned int n2;
#endif
  n = m + 1;
  fyx = jbm_farray_new (n);
  jbm_farray_set1 (fyx, c0, n);
  n += m;
  fxx = jbm_farray_new (n);
  jbm_farray_set1 (fxx, c0, n);
  i = 0;
  n = fx->n;
  x = fx->x;
  y = fy->x;
  xx = fxx->x;
  yx = fyx->x;
#ifdef __AVX__
  for (j = 0; j <= m; ++j)
    yx4[j] = xx4[j] = _mm256_setzero_pd ();
  for (; j <= m + m; ++j)
    xx4[j] = _mm256_setzero_pd ();
#endif
#ifdef __SSE4_2__
  for (j = 0; j <= m; ++j)
    yx2[j] = xx2[j] = _mm_setzero_pd ();
  for (; j <= m + m; ++j)
    xx2[j] = _mm_setzero_pd ();
#endif
#ifdef __AVX__
  n4 = n >> 2;
  if (n4)
    {
      for (; n4; --n4, i += 4)
        {
          zx4 = _mm256_set1_pd ((double) c1);
          x4 = _mm256_load_pd (x + i);
          zy4 = y4 = _mm256_load_pd (y + i);
          for (j = 0; j <= m; ++j)
            {
              xx4[j] = _mm256_add_pd (xx4[j], zx4);
              yx4[j] = _mm256_add_pd (yx4[j], zy4);
              zx4 = _mm256_mul_pd (zx4, x4);
              zy4 = _mm256_mul_pd (zy4, y4);
            }
          for (; j <= m + m; ++j)
            {
              xx4[j] = _mm256_add_pd (xx4[j], zx4);
              zx4 = _mm256_mul_pd (zx4, x4);
            }
        }
      for (j = 0; j <= m; ++j)
        {
          _mm256_store_pd (t4, xx4[j]);
          xx2[j] = _mm_add_pd (_mm_load_pd (t4), _mm_load_pd (t4 + 2));
          _mm256_store_pd (t4, yx4[j]);
          yx2[j] = _mm_add_pd (_mm_load_pd (t4), _mm_load_pd (t4 + 2));
        }
      for (; j <= m + m; ++j)
        {
          _mm256_store_pd (t4, xx4[j]);
          xx2[j] = _mm_add_pd (_mm_load_pd (t4), _mm_load_pd (t4 + 2));
        }
    }
#endif
#ifdef __SSE4_2__
  n2 = (n - i) >> 1;
  if (n2)
    {
      for (; n2; --n2, i += 2)
        {
          zx2 = _mm_set1_pd ((double) c1);
          x2 = _mm_load_pd (x + i);
          zy2 = y2 = _mm_load_pd (y + i);
          for (j = 0; j <= m; ++j)
            {
              xx2[j] = _mm_add_pd (xx2[j], zx2);
              yx2[j] = _mm_add_pd (yx2[j], zy2);
              zx2 = _mm_mul_pd (zx2, x2);
              zy2 = _mm_mul_pd (zy2, y2);
            }
          for (; j <= m + m; ++j)
            {
              xx2[j] = _mm_add_pd (xx2[j], zx2);
              zx2 = _mm_mul_pd (zx2, x2);
            }
        }
      for (j = 0; j <= m; ++j)
        {
          _mm_store_pd (t2, xx2[j]);
          xx[j] = t2[0] + t2[1];
          _mm_store_pd (t2, yx2[j]);
          yx[j] = t2[0] + t2[1];
        }
      for (; j <= m + m; ++j)
        {
          _mm_store_pd (t2, xx2[j]);
          xx[j] = t2[0] + t2[1];
        }
    }
#endif
  for (; i < n; ++i)
    {
      for (j = 0, zx = c1, zy = y[i]; j <= m; ++j)
        {
          xx[j] += zx;
          yx[j] += zy;
          zx *= x[i];
          zy *= x[i];
        }
      for (; j <= m + m; ++j)
        {
          xx[j] += zx;
          zx *= x[i];
        }
    }
  for (i = 0, k = B; i <= m; ++i, ++k)
    {
      for (j = 0; j <= m; ++j, ++k)
        *k = xx[j + i];
      *k = yx[i];
    }
  jbm_matrix_solve (B, m + 1);
  *fA = jbm_farray_new (m + 1);
  x = (*fA)->x;
  for (i = 0, k = B + m + 1; i <= m; ++i, k += m + 2)
    x[i] = *k;
  jbm_farray_destroy (fyx);
  jbm_farray_destroy (fxx);
}

/**
 * Function to calculate the coefficients of a multilinear regression adjusted 
 * by minimum squares: \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$ (JBFLOAT).
 */
static inline void
jbm_regression_multilinear (JBFLOAT **restrict x,
///< array of arrays of point coordinates in format:
///< \f$[f_0,\cdots,f_n],[x_0,\cdots,x_n],[y_0,\cdots,y_n],\cdots\f$.
                            unsigned int n,     ///< points number.
                            JBFLOAT *restrict a,
                            ///< array of regression coefficients.
                            unsigned int m)     ///< number of variables.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT c[(m + 1) * (m + 2)];
  JBFLOAT *d, *xj, *xk;
  int i, j, k;
  ++m;
  for (j = (int) m; --j > 0;)
    {
      for (k = (int) m; --k >= j;)
        {
          d = c + (m + 1) * j + k;
          xj = x[j];
          xk = x[k];
          for (*d = c0, i = (int) n; --i >= 0;)
            *d += xj[i] * xk[i];
        }
      d = c + (m + 1) * j + m;
      xj = x[j];
      xk = x[0];
      for (*d = c0, i = (int) n; --i >= 0;)
        *d += xj[i] * xk[i];
    }
  for (k = (int) m; --k > 0;)
    {
      d = c + k;
      xk = x[k];
      for (*d = c0, i = (int) n; --i >= 0;)
        *d += xk[i];
    }
  d = c + m;
  xk = x[0];
  for (*d = c0, i = (int) n; --i >= 0;)
    *d += xk[i];
  c[0] = n;
  for (j = (int) m; --j > 0;)
    for (k = (int) j; --k >= 0;)
      c[(m + 1) * j + k] = c[(m + 1) * k + j];
  jbm_matrix_solve (c, m);
  for (i = 0, d = c + m; ++i <= (int) m; ++a, d += m + 1)
    *a = *d;
}

/**
 * Function to calculate the coefficients of a multiexponential regression 
 * adjusted by minimum squares: \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$ (JBFLOAT).
 */
static inline void
jbm_regression_multiexponential (JBFLOAT **restrict x,
///< array of arrays of point coordinates in format:
///< \f$[f_0,\cdots,f_n],[x_0,\cdots,x_n],[y_0,\cdots,y_n],\cdots\f$. It is
///< modified by the function.
                                 unsigned int n, ///< points number.
                                 JBFLOAT *restrict a,
///< array of regression coefficients.
                                 unsigned int m) ///< number of variables.
{
  JBFLOAT *c;
  int i, j;
  for (j = (int) m + 1; --j >= 0;)
    for (i = (int) n, c = x[j]; --i >= 0;)
      c[i] = LOG (c[i]);
  jbm_regression_multilinear (x, n, a, m);
  a[0] = EXP (a[0]);
}

/**
 * Function to calculate a cubic spline on tabular data (JBFLOAT).
 */
static inline void
jbm_spline_cubic (JBFLOAT *restrict x,
                  ///< array of point x-coordinates.
                  JBFLOAT *restrict y,
                  ///< array of point y-coordinates.
                  unsigned int n,       ///< number of points.
                  JBFLOAT **restrict b,
///< pointer to the array of 1st order spline coefficients. It is generated by
///< malloc.
                  JBFLOAT **restrict c,
///< pointer to the array of 2nd order spline coefficients.
                  JBFLOAT **restrict d)
///< pointer to the array of 3rd order spline coefficients.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f, c3 = 3.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1., c3 = 3.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L, c3 = 3.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q, c3 = 3.Q;
#endif
  JBFLOAT *B, *C, *D, *E, *F, *H;
  JBFLOAT dx;
  unsigned int i, j, m;
  --n;
  m = 3 * n;
  B = (JBFLOAT *) malloc (6 * (m - 1) * sizeof (JBFLOAT));
  C = B + m - 2;
  D = C + m - 1;
  E = D + m;
  F = E + m - 1;
  H = F + m - 2;
  dx = x[1] - x[0];
  B[0] = B[1] = D[3] = E[2] = E[3] = F[3] = H[1] = H[2] = H[3] = c0;
  C[0] = C[1] = C[2] = c1;
  F[1] = F[2] = -c1;
  D[0] = dx;
  D[1] = D[0] + dx;
  D[2] = D[1] + dx;
  E[0] = D[0] * dx;
  E[1] = c3 * E[0];
  F[0] = E[0] * dx;
  H[0] = y[1] - y[0];
  for (i = n - 1; --i > 0;)
    {
      j = 3 * i + 1;
      dx = x[i + 1] - x[i];
      B[j - 2] = D[j + 2] = F[j] = F[j + 1] = F[j + 2] = H[j + 1] = H[j + 2]
        = c0;
      B[j - 1] = B[j] = c1;
      E[j + 1] = E[j + 2] = -c1;
      C[j - 1] = dx;
      C[j] = C[j - 1] + dx;
      C[j + 1] = C[j] + dx;
      D[j] = C[j - 1] * dx;
      D[j + 1] = c3 * D[j];
      E[j] = D[j] * dx;
      H[j] = y[i + 1] - y[i];
    }
  j = 3 * n - 2;
  dx = x[n] - x[n - 1];
  B[j - 2] = B[j - 1] = C[j] = H[j + 1] = c0;
  D[j + 1] = c1;
  C[j - 1] = dx;
  D[j] = dx * dx;
  E[j] = D[j] * dx;
  H[j] = y[n] - y[n - 1];
  jbm_matrix_solve_pentadiagonal (B, C, D, E, F, H, m);
  *b = (JBFLOAT *) malloc (3 * n * sizeof (JBFLOAT));
  *c = *b + n;
  *d = *c + n;
  for (i = n; i-- > 0;)
    {
      j = 3 * i;
      (*b)[i] = H[j];
      (*c)[i] = H[j + 1];
      (*d)[i] = H[j + 2];
    }
  free (B);
}

/**
 * Function to sort transversal regions.
 */
static inline void
jbm_transversal_section_regions_sort (unsigned int i,   ///< level index.
                                      unsigned int nj,  ///< number of points.
                                      unsigned int *restrict nk,
                                      ///< array of region indices.
                                      JBFLOAT *restrict l,
                                      ///< array of longitudinal coordinates.
                                      JBFLOAT *restrict z,
                                      ///< array of vertical coordinates.
                                      JBFLOAT *restrict zz)
                                      ///< array of levels.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c05 = 0.5f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c05 = 0.5;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c05 = 0.5L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c05 = 0.5Q;
#endif
  JBFLOAT x[nj];
  unsigned int nx[nj], na[nj];
  JBFLOAT t;
  int j, k;
  t = c05 * (zz[i] + zz[i + 1]);
  for (j = nj; --j >= 0;)
    {
      na[j] = k = nk[j];
      x[j] = jbm_extrapolate (t, z[k], z[k + 1], l[k], l[k + 1]);
    }
  jbm_index_sort (x, nx, nj);
  for (j = nj; --j >= 0;)
    *(nk++) = na[nx[j]];
}

/**
 * Function to get the regions of a cross section (JBFLOAT).
 *
 * \return index of the highest riverside point.
 */
static inline int
jbm_transversal_section_regions (JBFLOAT *restrict l,
///< array of JBFLOAT numbers with the transversal coordinates of the points
///< defining the cross section.
                                 JBFLOAT *restrict z,
///< array of JBFLOAT numbers with the vertical coordinates of the points 
///< defining the cross section.
                                 unsigned int n,
///< the highest cross section point number.
                                 JBFLOAT **restrict zz,
///< pointer to the array of JBFLOAT numbers, generated by malloc, of the 
///< cross section z-coordinates sorted from the lowest to the highest.
                                 unsigned int **restrict ni,
///< pointer to the array of indexes, generated by malloc and sorted by
///< z-coordinates, of the cross section points.
                                 unsigned int **restrict nj,
///< pointer to the array, generated by malloc, of the highest element number 
///< on every j-th region.
                                 unsigned int **restrict nij,
///< pointer to the sorted segments, from the lowest to the highest, on every
///< j-region.
                                 int *restrict nmin)
///< index of the lowest riverside point.
{
  unsigned int *nk;
  unsigned int i, j, k, nmax;
  nmax = i = jbm_index_sort_extended (z, zz, ni, n);
  if (!i)
    goto exit1;
  --n;
  *nj = (unsigned int *) malloc (n * (i + 1) * sizeof (unsigned int));
  if (!*nj)
    {
      free (*zz);
      free (*ni);
      i = 0;
      goto exit1;
    }
  *nij = *nj + n;
  while (i-- > 0)
    (*nj)[i] = 0;
  for (i = 0; i < n; ++i)
    {
      if ((*ni)[i + 1] > (*ni)[i])
        j = (*ni)[i + 1], k = (*ni)[i];
      else
        j = (*ni)[i], k = (*ni)[i + 1];
      while (j-- > k)
        (*nij)[n * j + (*nj)[j]++] = i;
    }
  *nmin = jbm_min ((*ni)[0], (*ni)[n]);
  for (i = 0, nk = *nij; i < nmax; ++i, nk += n)
    jbm_transversal_section_regions_sort (i, (*nj)[i], nk + 1, l, z, *zz);
exit1:
  return i;
}

/**
 * Function to find the segment number where a number is in an array of segments
 * defined in an array of structs (JBFLOAT).
 *
 * \return segment number.
 */
static inline int
jbm_varray_search (JBFLOAT x,   ///< number to search.
                   void *v,
///< pointer to the field in JBFLOAT format of the 1st element of the array of
///< structs.
                   int size,    ///< size in bytes of the structs.
                   int n)       ///< number of structs.
{
  int i, j;
  for (i = 0; n - i > 1;)
    {
      j = (i + n) >> 1;
      if (x <= *(JBFLOAT *) ((char *) v + j * size))
        n = j;
      else
        i = j;
    }
  return i;
}

/**
 * Function to find the segment number where a number is in an array of segments
 * defined in an array of structs checking if the number is out (JBFLOAT).
 *
 * \return segment number, -1 if \f$x<v_0\f$ or \f$n\f$ if \f$x>v_n\f$.
 */
static inline int
jbm_varray_search_extended (JBFLOAT x,  ///< number to search.
                            void *v,
///< pointer to the field in JBFLOAT format of the 1st element of the array of
///< structs.
                            int size,   ///< size in bytes of the structs.
                            int n)      ///< number of structs.
{
  int i;
  if (x < *(JBFLOAT *) v)
    i = -1;
  else if (x >= *(JBFLOAT *) ((char *) v + n * size))
    i = n;
  else
    i = jbm_varray_search (x, v, size, n);
  return i;
}

/**
 * \brief Function to find the highest value in an array of structs (JBFLOAT).
 *
 * \return the highest value.
 */
static inline JBFLOAT
jbm_varray_max (void *v,
///< pointer to the field in JBFLOAT format of the 1st element of the array of
///< structs.
                int size,       ///< size in bytes of the structs.
                int n)          ///< number of structs.
{
  int i;
  JBFLOAT k;
  k = *(JBFLOAT *) v;
  for (i = 0; ++i <= n;)
    k = FMAX (k, *(JBFLOAT *) (v = (char *) v + size));
  return k;
}

/**
 * \brief Function to find the lowest value in an array of structs (JBFLOAT).
 *
 * \return the lowest value.
 */
static inline JBFLOAT
jbm_varray_min (void *v,
///< pointer to the field in JBFLOAT format of the 1st element of the array of
///< structs.
                int size,       ///< size in bytes of the structs.
                int n)          ///< number of structs.
{
  int i;
  JBFLOAT k;
  k = *(JBFLOAT *) v;
  for (i = 0; ++i <= n;)
    k = FMIN (k, *(JBFLOAT *) (v = (char *) v + size));
  return k;
}

/**
 * Function to find the highest and the lowest values in an array of structs
 * (JBFLOAT).
 */
static inline void
jbm_varray_maxmin (void *v,
///< pointer to the field in JBFLOAT format of the 1st element of the array of
///< structs.
                   int size,    ///< size in bytes of the structs.
                   int n,       ///< number of structs.
                   JBFLOAT *max,        ///< pointer to the highest value.
                   JBFLOAT *min)        ///< pointer to the lowest value.
{
  int i;
  JBFLOAT kmax, kmin;
  kmax = kmin = *(JBFLOAT *) v;
  for (i = 0; ++i <= n;)
    {
      v = (char *) v + size;
      if (kmax < *(JBFLOAT *) v)
        kmax = *(JBFLOAT *) v;
      else if (kmin > *(JBFLOAT *) v)
        kmin = *(JBFLOAT *) v;
    }
  *max = kmax, *min = kmin;
}

/**
 * Function to calculate the mean square error between 2 functions tabulated in
 * 2 arrays of structs (JBFLOAT).
 *
 * \return mean square error value.
 */
static inline JBFLOAT
jbm_varray_mean_square_error (void *restrict xa,
///< x-coordinates tabulating the 1st function.
                              void *restrict fa,
///< values of the 1st function.
                              int sizea,
///< size of the structs of the 1st array.
                              int na,
///< the highest point number tabulating the 1st function.
                              void *restrict xr,
///< x-coordinates tabulating the 2nd function.
                              void *restrict fr,
///< values of the 2nd function.
                              int sizer,
///< size of the structs of the 2nd array.
                              int nr)
///< the highest point number tabulating the 2nd function.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT k, k2;
  int i, j;
  k = c0;
  for (i = 0; i <= na && *(JBFLOAT *) xa < *(JBFLOAT *) xr;
       ++i, xa = (char *) xa + sizea, fa = (char *) fa + sizea)
    k += jbm_fsqr (*(JBFLOAT *) fa - *(JBFLOAT *) fr);
  for (j = 0; i <= na; ++i, xa = (char *) xa + sizea, fa = (char *) fa + sizea)
    {
      while (j < nr && *(JBFLOAT *) xa > *(JBFLOAT *) ((char *) xr + sizer))
        ++j, xr = (char *) xr + sizer, fr = (char *) fr + sizer;
      if (j == nr)
        {
          for (; i <= na;
               ++i, xa = (char *) xa + sizea, fa = (char *) fa + sizea)
            k += jbm_fsqr (*(JBFLOAT *) fa - *(JBFLOAT *) fr);
        }
      else
        {

          k2 = jbm_extrapolate (*(JBFLOAT *) xa,
                                *(JBFLOAT *) xr,
                                *(JBFLOAT *) ((char *) xr + sizer),
                                *(JBFLOAT *) fr,
                                *(JBFLOAT *) ((char *) fr + sizer));
          k += jbm_fsqr (*(JBFLOAT *) fa - k2);
        }
    }
  k /= na + 1;
  return k;
}

/**
 * Function to calculate the root mean square error between 2 functions
 * tabulated in 2 arrays of structs (JBFLOAT).
 *
 * \return root mean square error value.
 */
static inline JBFLOAT
jbm_varray_root_mean_square_error (void *restrict xa,
///< x-coordinates tabulating the 1st function.
                                   void *restrict fa,
///< values of the 1st function.
                                   int sizea,
///< size of the structs of the 1st array.
                                   int na,
///< the highest point number tabulating the 1st function.
                                   void *restrict xr,
///< x-coordinates tabulating the 2nd function.
                                   void *fr,
///< values of the 2nd function.
                                   int sizer,
///< size of the structs of the 2nd array.
                                   int nr)
///< the highest point number tabulating the 2nd function.
{
  return SQRT
    (jbm_varray_mean_square_error (xa, fa, na, sizea, xr, fr, nr, sizer));
}

/**
 * Function to solve a tridiagonal linear equations system stored in the fields
 * of a struct array with format:
 * \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &        & H_0\\
 * C_0 & D_1    & E_1     &        & H_1\\
 *     & \ddots & \ddots  & \ddots & \vdots\\
 *     &        & C_{n-1} & D_n    & H_n
 * \end{array}\right)\f$.
 * Results are stored in the H fields. It modifies D and H fields (JBFLOAT).
 */
static inline void
jbm_varray_solve_tridiagonal (void *restrict C,
///< field address of first element of the struct array containing the left
///< diagonal equation system values.
                              void *restrict D,
///< field addres of first element of the struct array containing the central
///< diagonal equation system values.
                              void *restrict E,
///< field address of first element of the struct array containing the right
///< diagonal equation system values.
                              void *restrict H,
///< field address of first element of the struct array containing the final
///< equation system values.
                              unsigned int size,        ///< struct size.
                              unsigned int n)
                              ///< the latest struct array element.
{
  JBFLOAT *CC, *DD, *EE, *HH;
  JBFLOAT k;
  unsigned int i;
  DD = (JBFLOAT *) D;
  HH = (JBFLOAT *) H;
  for (i = 0; ++i <= n; C = (char *) C + size, E = (char *) E + size)
    {
      CC = (JBFLOAT *) C;
      EE = (JBFLOAT *) E;
      k = *CC / *DD;
      D = (char *) D + size;
      DD = (JBFLOAT *) D;
      *DD -= k ** EE;
      k *= *HH;
      H = (char *) H + size;
      HH = (JBFLOAT *) H;
      *HH -= k;
    }
  *HH /= *DD;
  while (--i > 0)
    {
      E = (char *) E - size;
      EE = (JBFLOAT *) E;
      k = *EE ** HH;
      D = (char *) D - size;
      DD = (JBFLOAT *) D;
      H = (char *) H - size;
      HH = (JBFLOAT *) H;
      *HH = (*HH - k) / *DD;
    }
}

/**
 * Function to solve a tridiagonal linear equations system stored in the fields
 * of a struct array with format:
 * \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &        & H_0\\
 * C_0 & D_1    & E_1     &        & H_1\\
 *     & \ddots & \ddots  & \ddots & \vdots\\
 *     &        & C_{n-1} & D_n    & H_n
 * \end{array}\right)\f$.
 * avoiding zero divisions. Results are stored in the H fields. It modifies D
 * and H fields (JBFLOAT).
 */
static inline void
jbm_varray_solve_tridiagonal_zero (void *restrict C,
///< field address of first element of the struct array containing the left
///< diagonal equation system values.
                                   void *restrict D,
///< field addres of first element of the struct array containing the central
///< diagonal equation system values.
                                   void *restrict E,
///< field address of first element of the struct array containing the right
///< diagonal equation system values.
                                   void *restrict H,
///< field address of first element of the struct array containing the final
///< equation system values.
                                   unsigned int size,   ///< struct size.
                                   unsigned int n)
                                   ///< the latest struct array element.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT *CC, *DD, *EE, *HH;
  JBFLOAT k;
  unsigned int i;
  DD = (JBFLOAT *) D;
  HH = (JBFLOAT *) H;
  for (i = 0; ++i <= n; C = (char *) C + size, E = (char *) E + size)
    {
      CC = (JBFLOAT *) C;
      EE = (JBFLOAT *) E;
      if (jbm_small (*DD))
        {
          D = (char *) D + size;
          H = (char *) H + size;
          DD = (JBFLOAT *) D;
          HH = (JBFLOAT *) H;
        }
      else
        {
          k = *CC / *DD;
          D = (char *) D + size;
          DD = (JBFLOAT *) D;
          *DD -= k ** EE;
          k *= *HH;
          H = (char *) H + size;
          HH = (JBFLOAT *) H;
          *HH -= k;
        }
    }
  if (jbm_small (*DD))
    *HH = c0;
  else
    *HH /= *DD;
  while (--i > 0)
    {
      E = (char *) E - size;
      EE = (JBFLOAT *) E;
      k = *EE ** HH;
      D = (char *) D - size;
      DD = (JBFLOAT *) D;
      H = (char *) H - size;
      HH = (JBFLOAT *) H;
      if (jbm_small (*DD))
        *HH = c0;
      else
        *HH = (*HH - k) / *DD;
    }
}

/**
 * Function to get a JBFLOAT number on a string.
 *
 * \return 1 on success, 0 on error.
 */
static inline int
jbm_get_float (char *str,       ///< string.
               JBFLOAT *x)      ///< pointer to the JBFLOAT number.
{
#if JBM_LOW_PRECISION < 4
  return sscanf (str, FRF, x);
#else
  char buffer[JB_BUFFER_SIZE];
  int i;
  i = sscanf (str, "%512s", buffer);
  *x = STRTOF (buffer, NULL);
  return i;
#endif
}

/**
 * Function to read a JBFLOAT number on a file.
 *
 * \return 1 on success, 0 on error.
 */
static inline int
jbm_read_float (FILE *file,     ///< file.
                JBFLOAT *x)     ///< pointer to the JBFLOAT number.
{
#if JBM_LOW_PRECISION < 4
  return fscanf (file, FRF, x);
#else
  char buffer[JB_BUFFER_SIZE];
  int i;
  i = fscanf (file, "%512s", buffer);
  *x = STRTOF (buffer, NULL);
  return i;
#endif
}

/**
 * Function to calculate the mean square error between 2 functions tabulated in
 * 2 columns data of 2 files (JBFLOAT).
 *
 * \return mean square error value.
 */
static inline JBFLOAT
jbm_file_mean_square_error (char *namea,
///< name of file where the 1st function is tabulated.
                            int ixa,
///< column number of x-coordinates tabulating the 1st function.
                            int ifa,
///< column number of values tabulating the 1st function.
                            int na,
///< columns number of file tabulating the 1st function.
                            char *namer,
///< name of file where the 2nd function is tabulated.
                            int ixr,
///< column number of x-coordinates tabulating the 2nd function.
                            int ifr,
///< column number of values tabulating the 2nd function.
                            int nr)
///< columns number of file tabulating the 2nd function.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q;
#endif
  JBFLOAT aa[na], ar[nr];
  FILE *filea, *filer;
  JBFLOAT k, xa, fa, xr1, fr1, xr2, fr2;
  int i, j, endr;
  endr = i = 0;
  k = c0;
  filea = fopen (namea, "r");
  if (!filea)
    goto exit_mse;
  filer = fopen (namer, "r");
  if (!filer)
    goto exit_mse;
  for (j = 0; j < nr; ++j)
    if (jbm_read_float (filer, ar + j) != 1)
      goto exit_mse;
  xr1 = ar[ixr - 1];
  fr1 = ar[ifr - 1];
  for (j = 0; j < nr; ++j)
    if (jbm_read_float (filer, ar + j) != 1)
      endr = 1;
  xr2 = ar[ixr - 1];
  fr2 = ar[ifr - 1];
  for (i = 0; !endr; ++i)
    {
      for (j = 0; j < nr; ++j)
        if (jbm_read_float (filer, ar + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      while (xa > xr2)
        {
          xr1 = xr2;
          fr1 = fr2;
          for (j = 0; j < nr; ++j)
            if (jbm_read_float (filer, ar + j) != 1)
              {
                endr = 1;
                goto end_filer;
              }
          xr2 = ar[ixr - 1];
          fr2 = ar[ifr - 1];
        }
    end_filer:
      if (!endr && xa > xr1)
        k += jbm_fsqr (fa - jbm_extrapolate (xa, xr1, xr2, fr1, fr2));
      else
        k += jbm_fsqr (fa - fr1);
    }
  for (; 1; ++i)
    {
      for (j = 0; j < na; ++j)
        if (jbm_read_float (filea, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      k += jbm_fsqr (fa - fr1);
    }
exit_mse:
  if (i == 0)
    return c0;
  return k / i;
}

/**
 * Function to calculate the root mean square error between 2 functions
 * tabulated in 2 columns data of 2 files (JBFLOAT).
 *
 * \return root mean square error value.
 */
static inline JBFLOAT
jbm_file_root_mean_square_error (char *namea,
///< name of file where the 1st function is tabulated.
                                 int ixa,
///< column number of x-coordinates tabulating the 1st function.
                                 int ifa,
///< column number of values tabulating the 1st function.
                                 int na,
///< columns number of file tabulating the 1st function.
                                 char *namer,
///< name of file where the 2nd function is tabulated.
                                 int ixr,
///< column number of x-coordinates tabulating the 2nd function.
                                 int ifr,
///< column number of values tabulating the 2nd function.
                                 int nr)
///< columns number of file tabulating the 2nd function.
{
  return SQRT
    (jbm_file_mean_square_error (namea, ixa, ifa, na, namer, ixr, ifr, nr));
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * array of JBDOUBLE numbers.
 *
 * \return interval number.
 */
static inline unsigned int
jbm_darray_search (JBDOUBLE x,  ///< number to search.
                   JBDOUBLE *fa,        ///< array of JBDOUBLE numbers.
                   unsigned int n)
                   ///< number of the highest array element.
{
  unsigned int i, j;
  for (i = 0; n - i > 1;)
    {
      j = (i + n) >> 1;
      if (x <= fa[j])
        n = j;
      else
        i = j;
    }
  return i;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * array of JBDOUBLE numbers.
 * \return interval number, -1 if x<fa[0] or n if x>fa[n].
 */
static inline int
jbm_darray_search_extended (JBDOUBLE x, ///< number to search.
                            JBDOUBLE *fa,       ///< array of JBDOUBLE numbers.
                            unsigned int n)
                            ///< number of the highest array element.
{
  int i;
  if (x < fa[0])
    i = -1;
  else if (x >= fa[n])
    i = (int) n;
  else
    i = (int) jbm_darray_search (x, fa, n);
  return i;
}

/**
 * Function to find the highest element of an array of JBDOUBLE numbers.
 *
 * \return the highest value.
 */
static inline JBDOUBLE
jbm_darray_max (JBDOUBLE *fa,   ///< array of JBDOUBLE numbers.
                unsigned int n) ///< number of the ending array element.
{
  JBDOUBLE k;
  unsigned int i;
  k = fa[0];
  for (i = 0; ++i <= n;)
    k = FMAX (k, fa[i]);
  return k;
}

/**
 * Function to find the lowest element of an array of JBDOUBLE numbers.
 *
 * \return the lowest value.
 */
static inline JBDOUBLE
jbm_darray_min (JBDOUBLE *fa,    ///< array of JBDOUBLE numbers.
                unsigned int n)  ///< number of the ending array element.
{
  JBDOUBLE k;
  unsigned int i;
  k = fa[0];
  for (i = 0; ++i <= n;)
    k = FMIN (k, fa[i]);
  return k;
}

/**
 * Function to find the highest and the lowest elements of an array of JBDOUBLE
 * numbers.
 */
static inline void
jbm_darray_maxmin (JBDOUBLE *fa, ///< array of JBDOUBLE numbers.
                   unsigned int n,      ///< number of the ending array element.
                   JBDOUBLE *max,       ///< the highest value.
                   JBDOUBLE *min)       ///< the lowest value.
{
  JBDOUBLE kmax, kmin;
  unsigned int i;
  kmax = kmin = fa[0];
  for (i = 0; ++i <= n;)
    {
      if (kmax < fa[i])
        kmax = fa[i];
      else if (kmin > fa[i])
        kmin = fa[i];
    }
  *max = kmax, *min = kmin;
}

/**
 * Function to interchange 2 arrays of JBDOUBLE numbers.
 */
static inline void
jbm_darray_change (JBDOUBLE *restrict fa,
                   ///< 1st array of JBDOUBLE numbers.
                   JBDOUBLE *restrict fb,
                   ///< 2nd array of JBDOUBLE numbers.
                   unsigned int n)
                   ///< the highest element number of the arrays.
{
  JBDOUBLE *restrict fc;
  size_t s;
  s = (n + 1) * sizeof (JBDOUBLE);
  fc = (JBDOUBLE *) malloc (s);
  memcpy (fc, fa, s);
  memcpy (fa, fb, s);
  memcpy (fb, fc, s);
  free (fc);
}

/**
 * Function to calculate the y-coordinate of a 2D point interpolated 
 * between a tabular function defined by 2 arrays of JBDOUBLE numbers.
 *
 * \return y-coordinate of the interpolated point.
 */
static inline JBDOUBLE
jbm_darray_interpolate (JBDOUBLE x,     ///< x-coordinate of the point.
                        JBDOUBLE *fa,
///< increasingly sorted array of x-coordinates of the tabular function.
                        JBDOUBLE *fb,
///< array of y-coordinates of the tabular function.
                        unsigned int n)
///< the highest element number of the arrays.
{
  JBDOUBLE k;
  unsigned int i;
  i = jbm_darray_search (x, fa, n);
  if (i == n)
    k = fb[i];
  else
    k = jbm_interpolatel (x, fa[i], fa[i + 1], fb[i], fb[i + 1]);
  return k;
}

/**
 * Function to merge 2 increasingly sorted arrays of JBDOUBLE numbers.
 *
 * \return resulting array.
 */
static inline JBDOUBLE *
jbm_darray_merge (JBDOUBLE *restrict fa,
                  ///< 1st increasingly sorted array of JBDOUBLE numbers.
                  unsigned int na,
                  ///< the highest element number of the 1st array.
                  JBDOUBLE *restrict fb,
                  ///< 2nd increasingly sorted array of JBDOUBLE numbers.
                  unsigned int nb,
                  ///< the highest element number of the 2nd array.
                  JBDOUBLE **fc,
///< pointer to the resulting increasingly sorted array of JBDOUBLE numbers.
                  unsigned int *nc)
                  ///< the highest element number of the resulting array.
{
  JBDOUBLE *restrict x;
  unsigned int i, j, k;
  x = (JBDOUBLE *) malloc ((na + nb + 2) * sizeof (JBDOUBLE));
  if (!x)
    return NULL;
  for (i = j = k = 0; i <= na || j <= nb; ++k)
    {
      if (i > na)
        x[k] = fb[j++];
      else if (j > nb)
        x[k] = fa[i++];
      else if (fa[i] > fb[j])
        x[k] = fb[j++];
      else if (fa[i] < fb[j])
        x[k] = fa[i++];
      else
        x[k] = fa[i++], j++;
    }
  *fc = (JBDOUBLE *) jb_realloc (x, k * sizeof (JBDOUBLE));
  *nc = --k;
  return *fc;
}

/**
 * Function to integrate a tabular function (JBDOUBLE) in an interval.
 *
 * \return integral value.
 */
static inline JBDOUBLE
jbm_darray_integral (JBDOUBLE *restrict x,
///< incresingly sorted array of JBDOUBLE numbers defining the x-coordinates of
///< the tabular function.
                     JBDOUBLE *restrict y,
///< array of JBDOUBLE numbers defining the y-coordinates of the tabular
///< function.
                     unsigned int n,
                     ///< the highest element number of the arrays.
                     JBDOUBLE x1,
                     ///< left limit of the integration interval.
                     JBDOUBLE x2)
                     ///< right limit of the integration interval.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c05 = 0.5f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c05 = 0.5;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c05 = 0.5L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c05 = 0.5Q;
#endif
  JBDOUBLE *yy, *xx;
  JBDOUBLE I, y1;
  int i;
  if (n == 0)
    {
      I = y[0] * (x2 - x1);
      goto exit1;
    }
  i = jbm_darray_search_extended (x1, x, n);
  if (i < 0)
    {
      if (x2 <= x[0])
        {
          I = y[0] * (x2 - x1);
          goto exit1;
        }
      I = y[0] * (x[0] - x1);
      i = 0;
      x1 = x[0];
      y1 = y[0];
      xx = x;
      yy = y;
    }
  else if (i == (int) n)
    {
      I = y[i] * (x2 - x1);
      goto exit1;
    }
  else
    {
      I = c0;
      xx = x + i;
      yy = y + i;
      y1 = jbm_extrapolatel (x1, xx[0], xx[1], yy[0], yy[1]);
    }
  if (x2 < xx[1])
    {
      I += c05 * (y1 + jbm_extrapolatel (x2, xx[0], xx[1], yy[0], yy[1]))
        * (x2 - x1);
      goto exit1;
    }
  I += c05 * (y1 + yy[1]) * (xx[1] - x1);
  if (++i == (int) n)
    {
      I += yy[1] * (x2 - xx[1]);
      goto exit1;
    }
  while (++i < (int) n && x2 > xx[2])
    {
      ++xx, ++yy;
      I += c05 * (yy[0] + yy[1]) * (xx[1] - xx[0]);
    }
  if (i == (int) n)
    I += yy[2] * (x2 - xx[1]);
  else if (x2 < xx[2])
    I += c05 * (yy[1] + jbm_extrapolatel (x2, xx[1], xx[2], yy[1], yy[2]))
      * (x2 - xx[1]);
exit1:
  return I;
}

/**
 * Function to get a JBFLOAT number on a string.
 *
 * \return 1 on success, 0 on error.
 */
static inline int
jbm_get_double (const char *str,      ///< string.
                JBDOUBLE *x)    ///< pointer to the JBDOUBLE number.
{
#if JBM_HIGH_PRECISION < 4
  return sscanf (str, FRL, x);
#else
  char buffer[JB_BUFFER_SIZE];
  int i;
  i = sscanf (str, "%512s", buffer);
  *x = STRTOD (str, NULL);
  return i;
#endif
}

/**
 * Function to read a JBFLOAT number on a file.
 *
 * \return 1 on success, 0 on error.
 */
static inline int
jbm_read_double (FILE *file,    ///< file.
                 JBDOUBLE *x)   ///< pointer to the JBDOUBLE number.
{
#if JBM_HIGH_PRECISION < 4
  return fscanf (file, FRL, x);
#else
  char buffer[JB_BUFFER_SIZE];
  int i;
  i = fscanf (file, "%512s", buffer);
  *x = STRTOD (buffer, NULL);
  return i;
#endif
}

/**
 * Function to calculate the mean square error between 2 tabular functions
 * (JBDOUBLE).
 *
 * \return mean square error.
 */
static inline JBDOUBLE
jbm_darray_mean_square_error (JBDOUBLE *restrict xa,
///< incresingly sorted array of JBDOUBLE numbers defining the x-coordinates
///< of the 1st tabular function.
                              JBDOUBLE *restrict fa,
///< array of JBDOUBLE numbers defining the y-coordinates of the 1st tabular
///< function.
                              unsigned int na,
///< the highest element number of the arrays defining the 1st tabular
///< function.
                              JBDOUBLE *restrict xr,
///< incresingly sorted array of JBDOUBLE numbers defining the x-coordinates
///< of the 2nd tabular function.
                              JBDOUBLE *restrict fr,
///< array of JBDOUBLE numbers defining the y-coordinates of the 2nd tabular
///< function.
                              unsigned int nr)
///< the highest element number of the arrays defining the 2nd tabular
///< function.
{
#if JBM_HIGH_PRECISION == 1
  JBDOUBLE k = 0.f;
#elif JBM_HIGH_PRECISION == 2
  JBDOUBLE k = 0.;
#elif JBM_HIGH_PRECISION == 3
  JBDOUBLE k = 0.L;
#elif JBM_HIGH_PRECISION == 4
  JBDOUBLE k = 0.Q;
#endif
  unsigned int i, j;
  for (i = 0; i <= na && xa[i] < xr[0]; ++i)
    k += jbm_fsqrl (fa[i] - fr[0]);
  for (j = 0; i <= na; ++i)
    {
      while (j < nr && xa[i] > xr[j + 1])
        ++j;
      if (j == nr)
        for (; i <= na; ++i)
          k += jbm_fsqrl (fa[i] - fr[nr]);
      else
        k += jbm_fsqrl (fa[i] - jbm_extrapolatel (xa[i], xr[j], xr[j + 1],
                                                  fr[j], fr[j + 1]));
    }
  k /= na + 1;
  return k;
}

/**
 * Function to calculate the root mean square error between 2 tabular functions
 * (JBDOUBLE).
 *
 * \return root mean square error.
 */
static inline JBDOUBLE
jbm_darray_root_mean_square_error (JBDOUBLE *restrict xa,
///< incresingly sorted array of JBDOUBLE numbers defining the x-coordinates
///< of the 1st tabular function.
                                   JBDOUBLE *restrict fa,
///< array of JBDOUBLE numbers defining the y-coordinates of the 1st tabular
///< function.
                                   int na,
///< the highest element number of the arrays defining the 1st tabular
///< function.
                                   JBDOUBLE *restrict xr,
///< incresingly sorted array of JBDOUBLE numbers defining the x-coordinates
///< of the 2nd tabular function.
                                   JBDOUBLE *restrict fr,
///< array of JBDOUBLE numbers defining the y-coordinates of the 2nd tabular
///< function.
                                   int nr)
///< the highest element number of the arrays defining the 2nd tabular
///< function.
{
  return SQRTL (jbm_darray_mean_square_error (xa, fa, na, xr, fr, nr));
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBDOUBLE numbers by the insertion method.
 */
static inline void
jbm_index_sort_insertionl (JBDOUBLE *restrict x,
                           ///< array of JBDOUBLE numbers.
                           unsigned int *restrict ni,   ///< array of indexes.
                           int n)
                           ///< the highest element number of the arrays.
{
  JBDOUBLE xi;
  int i, j, ii;
  for (i = 0; ++i <= n;)
    {
      ii = ni[i];
      xi = x[ii];
      for (j = i; --j >= 0 && x[ni[j]] < xi;)
        ni[j + 1] = ni[j];
      ni[j + 1] = ii;
    }
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBDOUBLE numbers by the interchange method.
 */
static inline void
jbm_index_sort_interchangel (JBDOUBLE *restrict x,
                             ///< array of JBDOUBLE numbers.
                             unsigned int *restrict ni,
                             ///< array of indexes.
                             int n)
                             ///< the highest element number of the arrays.
{
  JBDOUBLE xi, xj;
  int i, j;
  for (i = n + 1; --i > 0;)
    {
      xi = x[ni[i]];
      for (j = i; --j >= 0;)
        {
          xj = x[ni[j]];
          if (xj < xi)
            {
              xi = xj;
              jbm_changeu (ni + i, ni + j);
            }
        }
    }
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBDOUBLE numbers by the merge method.
 */
static inline void
jbm_index_sort_mergel (JBDOUBLE *restrict x,    ///< array of JBDOUBLE numbers.
                       unsigned int *restrict ni,       ///< array of indexes.
                       int n)   ///< the highest element number of the arrays.
{
  unsigned int nn[n + 1];
  unsigned int *ni1, *ni2, *nj, *nk, *nt;
  int j, i1, i2, k, l;
  j = JBM_INDEX_SORT_MERGE_MIN;
  if (n <= j)
    {
      jbm_index_sort_insertionl (x, ni, n);
      return;
    }
  k = n / j;
  if (n % j)
    ++k;
  j = n / k;
  if (n % k)
    ++j;
  for (l = 0; l <= n - j; l += j)
    jbm_index_sort_insertionl (x, ni + l, j - 1);
  if (l < n)
    jbm_index_sort_insertionl (x, ni + l, n - l);
  for (nk = ni, nj = nn; j <= (int) n; j *= 2)
    {
      for (ni1 = nk, l = 0, k = n / j; (k -= 2) >= 0; ni1 = ni2 + j)
        {
          ni2 = ni1 + j;
          for (i1 = i2 = 0; i1 < j && i2 < j;)
            {
              if (x[ni1[i1]] > x[ni2[i2]])
                nj[l++] = ni1[i1++];
              else
                nj[l++] = ni2[i2++];
            }
          while (i2 < j)
            nj[l++] = ni2[i2++];
          while (i1 < j)
            nj[l++] = ni1[i1++];
        }
      if (k == -1)
        {
          ni2 = ni1 + j;
          for (k = n - l - j, i1 = i2 = 0; i1 < j && i2 <= k;)
            {
              if (x[ni1[i1]] > x[ni2[i2]])
                nj[l++] = ni1[i1++];
              else
                nj[l++] = ni2[i2++];
            }
          while (i2 <= k)
            nj[l++] = ni2[i2++];
          while (i1 < j)
            nj[l++] = ni1[i1++];
        }
      for (; l <= n; ++l)
        nj[l] = nk[l];
      nt = nk;
      nk = nj;
      nj = nt;
    }
  if (ni != nk)
    memcpy (ni, nk, l * sizeof (int));
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBDOUBLE numbers by the optimal method.
 */
static inline void
jbm_index_sortl (JBDOUBLE *restrict x,  ///< array of JBDOUBLE numbers.
                 unsigned int *restrict ni,     ///< array of indexes.
                 int n)         ///< the highest element number of the arrays.
{
  int i;
  for (i = n + 1; --i >= 0;)
    ni[i] = i;
  if (n < JBM_INDEX_SORT_FLASH_MIN)
    jbm_index_sort_insertionl (x, ni, n);
  else
    jbm_index_sort_flashl (x, ni, n);
}

/**
 * Function to create a sorted index from the highest to the lowest of an array
 * of JBDOUBLE numbers by the optimal method.
 *
 * \return the highest element number of the sorted array.
 */
static inline int
jbm_index_sort_extendedl (JBDOUBLE *restrict x,
                          ///< array of JBDOUBLE numbers to sort.
                          JBDOUBLE **restrict xr,
///< pointer to the array of sorted JBDOUBLE numbers elliminating duplicated
///< numbers. It has to be freed with free.
                          int **restrict ni,
///< point to the array of sorted indexes. It has to be freed with free.
                          int n)
///< the highest element number of the array to sort.
{
  unsigned int nk[n + 1], nj[n + 1];
  JBDOUBLE k1, k2;
  int i, j = 0;
  *ni = (int *) malloc ((n + 1) * sizeof (int));
  *xr = (JBDOUBLE *) malloc ((n + 1) * sizeof (JBDOUBLE));
  if (!*xr)
    {
      jb_free_null ((void **) ni);
      fprintf (stderr, "JBM index sort extended: no enough memory\n");
      goto index_exit;
    }
  jbm_index_sortl (x, nk, n);
  i = n;
  k2 = x[nk[i]];
  nj[i] = 0;
  (*xr)[0] = k2;
  for (; --i >= 0; k2 = k1)
    {
      k1 = x[nk[i]];
      if (k1 != k2)
        (*xr)[++j] = k1;
      nj[i] = j;
    }
  for (i = n + 1; --i >= 0;)
    (*ni)[nk[i]] = nj[i];
index_exit:
  return j;
}

/**
 * Function to solve a linear equations system stored in a matrix with format:
 * \f$\left(\begin{array}{cccc|c}
 * x_{0,0} & x_{0,1} & \cdots & x_{0,n-1} & x_{0,n}\\
 * x_{1,0} & x_{1,1} & \cdots & x_{1,n-1} & x_{1,n}\\
 * & & \cdots \\
 * x_{n-1,0} & x_{n-1,1} & \cdots & x_{n-1,n-1} & x_{n-1,n}
 * \end{array}\right)\f$.
 * Results are stored in the n+1-th column:
 * \f$\left(x_{0,n},\;x_{1,n},\;\cdots,\;x_{n-1,n}\right)\f$.
 * It modifies the x matrix (JBDOUBLE).
 */
static inline void
jbm_matrix_solvel (JBDOUBLE *x,
///< matrix storing the linear equations system.
                   int n)       ///< number of matrix rows.
{
  JBDOUBLE *f, *g;
  JBDOUBLE k1, k2;
  int i, j, k;
  // Setting n to the number of row elements
  ++n;
  // Scaling every equation to reduce rounding effects.
  for (i = n, f = x; --i > 0;)
    {
      jbm_darray_maxmin (f, n, &k1, &k2);
      k1 = FMAXL (FABSL (k1), FABSL (k2));
      for (j = n; --j >= 0; ++f)
        *f /= k1;
    }
  // Gaussian elimination
  for (i = n - 1, f = x; --i > 0; f += n + 1)
    {
      // Obtaining the highest pivot element        
      k1 = FABSL (*f);
      for (k = j = i, g = f; --j >= 0;)
        {
          g += n;
          k2 = FABSL (*g);
          if (k2 > k1)
            {
              k1 = k2;
              k = j;
            }
        }
      // Interchanging rows
      if (k != i)
        {
          g = f + (i - k) * n;
          jbm_darray_change (g, f, i + 1);
        }
      // Eliminating column
      for (j = i, g = f + n; --j >= 0; g += n)
        {
          k1 = *g / *f;
          for (k = i + 2; --k > 0;)
            g[k] -= k1 * f[k];
        }
    }
  // Retrieving solutions
  f = x + n * (n - 1) - 1;
  for (i = 0; ++i < n; f -= n)
    {
      // Solution
      k1 = *f /= *(f - i);
      // Eliminating column
      for (j = n, g = f - n; --j > i; g -= n)
        *g -= *(g - i) * k1;
    }
}

/**
 * Function to solve a linear equations system stored in a tridiagonal matrix
 * with format: \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &         & H_0\\
 * C_0 & D_1    & E_1     &         & H_1\\
 *     & \ddots & \ddots  & \ddots  & \vdots\\
 *     &        & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * Results are stored in the H array. It modifies D and H arrays (JBDOUBLE).
 */
static inline void
jbm_matrix_solve_tridiagonall (JBDOUBLE *restrict C,
                               ///< left diagonal array.
                               JBDOUBLE *restrict D,
                               ///< central diagonal array.
                               JBDOUBLE *restrict E,
                               ///< right diagonal array.
                               JBDOUBLE *restrict H,    ///< final column array.
                               int n)   ///< number of matrix rows.
{
  JBDOUBLE k;
  int i;
  for (i = 0; i < n; ++i)
    {
      k = C[i] / D[i];
      D[i + 1] -= k * E[i];
      H[i + 1] -= k * H[i];
    }
  H[i] /= D[i];
  while (i--)
    H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
}

/**
 * Function to solve a linear equations system stored in a tridiagonal matrix
 * with format: \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &         & H_0\\
 * C_0 & D_1    & E_1     &         & H_1\\
 *     & \ddots & \ddots  & \ddots  & \vdots\\
 *     &        & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * avoiding zero divisions. Results are stored in the H array. It modifies D and
 * H arrays (JBDOUBLE).
 */
static inline void
jbm_matrix_solve_tridiagonal_zerol (JBDOUBLE *restrict C,
                                    ///< left diagonal array.
                                    JBDOUBLE *restrict D,
                                    ///< central diagonal array.
                                    JBDOUBLE *restrict E,
                                    ///< right diagonal array.
                                    JBDOUBLE *restrict H,
                                    ///< final column array.
                                    int n)      ///< number of matrix rows.
{
#if JBM_HIGH_PRECISION == 1
  JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE k;
  int i;
  for (i = 0; i < n; ++i)
    if (!jbm_smalll (D[i]))
      {
        k = C[i] / D[i];
        D[i + 1] -= k * E[i];
        H[i + 1] -= k * H[i];
      }
  if (jbm_smalll (D[i]))
    H[i] = c0;
  else
    H[i] /= D[i];
  while (i--)
    if (jbm_smalll (D[i]))
      H[i] = c0;
    else
      H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
}

/**
 * Function to solve a linear equations system stored in a pentadiagonal matrix
 * with format: \f$\left(\begin{array}{cccccc|c}
 * D_0 & E_0    & F_0     &         &         &         & H_0\\
 * C_0 & D_1    & E_1     & F_1     &         &         & H_1\\
 * B_0 & C_1    & D_2     & E_2     & F_2     &         & H_2\\
 *     & \ddots & \ddots  & \ddots  & \ddots  & \ddots  & \vdots\\
 *     &        &         & B_{n-3} & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * Results are stored in the H array. It modifies C, D, E and H arrays 
 * (JBDOUBLE).
 */
static inline void
jbm_matrix_solve_pentadiagonall (JBDOUBLE *restrict B,
                                 ///< double-left diagonal array.
                                 JBDOUBLE *restrict C,
                                 ///< left diagonal array.
                                 JBDOUBLE *restrict D,
                                 ///< central diagonal array.
                                 JBDOUBLE *restrict E,
                                 ///< right diagonal array.
                                 JBDOUBLE *restrict F,
                                 ///< double-right diagonal array.
                                 JBDOUBLE *restrict H,
                                 ///< final column array.
                                 int n) ///< number of matrix rows.
{
  JBDOUBLE k;
  int i;
  for (i = 0; i < n - 1; ++i)
    {
      k = C[i] / D[i];
      D[i + 1] -= k * E[i];
      E[i + 1] -= k * F[i];
      H[i + 1] -= k * H[i];
      k = B[i] / D[i];
      C[i + 1] -= k * E[i];
      D[i + 2] -= k * F[i];
      H[i + 2] -= k * H[i];
    }
  k = C[i] / D[i];
  D[i + 1] -= k * E[i];
  H[i + 1] -= k * H[i];
  H[i + 1] /= D[i + 1];
  H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
  while (i--)
    H[i] = (H[i] - E[i] * H[i + 1] - F[i] * H[i + 2]) / D[i];
}

/**
 * Function to solve a linear equations system stored in a pentadiagonal matrix
 * with format: \f$\left(\begin{array}{cccccc|c}
 * D_0 & E_0    & F_0     &         &         &         & H_0\\
 * C_0 & D_1    & E_1     & F_1     &         &         & H_1\\
 * B_0 & C_1    & D_2     & E_2     & F_2     &         & H_2\\
 *     & \ddots & \ddots  & \ddots  & \ddots  & \ddots  & \vdots\\
 *     &        &         & B_{n-3} & C_{n-2} & D_{n-1} & H_{n-1}
 * \end{array}\right)\f$.
 * avoiding zero divisions. Results are stored in the H array. It modifies C, D,
 * E and H arrays (JBDOUBLE).
 */
static inline void
jbm_matrix_solve_pentadiagonal_zerol (JBDOUBLE *restrict B,
                                      ///< double-left diagonal array.
                                      JBDOUBLE *restrict C,
                                      ///< left diagonal array.
                                      JBDOUBLE *restrict D,
                                      ///< central diagonal array.
                                      JBDOUBLE *restrict E,
                                      ///< right diagonal array.
                                      JBDOUBLE *restrict F,
                                      ///< double-right diagonal array.
                                      JBDOUBLE *restrict H,
                                      ///< final column array.
                                      int n)    ///< number of matrix rows.
{
#if JBM_HIGH_PRECISION == 1
  JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE k;
  int i;
  for (i = 0; i < n - 1; ++i)
    if (!jbm_smalll (D[i]))
      {
        k = C[i] / D[i];
        D[i + 1] -= k * E[i];
        E[i + 1] -= k * F[i];
        H[i + 1] -= k * H[i];
        k = B[i] / D[i];
        C[i + 1] -= k * E[i];
        D[i + 2] -= k * F[i];
        H[i + 2] -= k * H[i];
      }
  if (!jbm_smalll (D[i]))
    {
      k = C[i] / D[i];
      D[i + 1] -= k * E[i];
      H[i + 1] -= k * H[i];
    }
  if (jbm_smalll (D[i + 1]))
    H[i + 1] = c0;
  else
    H[i + 1] /= D[i + 1];
  if (jbm_smalll (D[i]))
    H[i] = c0;
  else
    H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
  while (i--)
    if (jbm_smalll (D[i]))
      H[i] = c0;
    else
      H[i] = (H[i] - E[i] * H[i + 1] - F[i] * H[i + 2]) / D[i];
}

/**
 * Function to calculate the coefficients of a linear regression adjusted by 
 * minimum squares: \f$y=a+b\,x\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_linearl (JBDOUBLE *restrict x,
                        ///< array of point x-coordinates.
                        JBDOUBLE *restrict y,
                        ///< array of point y-coordinates.
                        unsigned int n, ///< points number.
                        JBDOUBLE *a,
                        ///< pointer to the 0th order regression coefficient.
                        JBDOUBLE *b)
                        ///< pointer to the 1st order regression coefficient.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE syx, sy, sxx, sx;
  unsigned int i;
  ++n;
  syx = sy = sxx = sx = c0;
  for (i = 0; i < n; ++i)
    {
      sy += y[i];
      syx += x[i] * y[i];
      sxx += x[i] * x[i];
      sx += x[i];
    }
  *b = (n * syx - sy * sx) / (n * sxx - sx * sx);
  *a = (sy - *b * sx) / n;
}

/**
 * Function to calculate the coefficients of a polynomial regression adjusted
 * by minimum squares: \f$y=A_0+A_1\,x+A_2\,x^2+\cdots\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_polynomiall (JBDOUBLE *restrict x,
                            ///< array of point x-coordinates.
                            JBDOUBLE *restrict y,
                            ///< array of point y-coordinates.
                            int n,      ///< points number.
                            JBDOUBLE **A,
///< pointer to the array of regression coefficients generated by the function
///< calling to malloc.
                            int m)      ///< order of the polynomial regression.
{
#if JBM_LOW_PRECISION == 1
  const JBFLOAT c0 = 0.f, c1 = 1.f;
#elif JBM_LOW_PRECISION == 2
  const JBFLOAT c0 = 0., c1 = 1.;
#elif JBM_LOW_PRECISION == 3
  const JBFLOAT c0 = 0.L, c1 = 1.L;
#elif JBM_LOW_PRECISION == 4
  const JBFLOAT c0 = 0.Q, c1 = 1.Q;
#endif
  JBDOUBLE xx[m + m + 1], yx[m + 1], B[(m + 1) * (m + 2)];
  JBDOUBLE *k;
  JBDOUBLE zx, zy;
  int i, j;
  *A = (JBDOUBLE *) malloc ((m + 1) * sizeof (JBDOUBLE));
  for (j = m + m; --j > m;)
    xx[j] = c0;
  for (; j >= 0; --j)
    xx[j] = yx[j] = c0;
  for (i = n; --i >= 0;)
    {
      for (j = 0, zx = c1, zy = y[i]; j <= m; ++j)
        {
          yx[j] += zy;
          xx[j] += zx;
          zx *= x[i];
          zy *= x[i];
        }
      for (; j <= m + m; ++j)
        {
          xx[j] += zx;
          zx *= x[i];
        }
    }
  for (i = 0, k = B; i <= m; ++i, ++k)
    {
      for (j = 0; j <= m; ++j, ++k)
        *k = xx[j + i];
      *k = yx[i];
    }
  jbm_matrix_solvel (B, m + 1);
  for (i = 0, k = B; i <= m; ++i, k += m + 1)
    (*A)[i] = *k;
}

/**
 * Function to calculate the coefficients of an exponential regression adjusted
 * by minimum squares: \f$y=a\,x^b\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_exponentiall (JBDOUBLE *restrict x,
///< array of point x-coordinates. It is modified by the function.
                             JBDOUBLE *restrict y,
///< array of point y-coordinates. It is modified by the function.
                             int n,     ///< points number.
                             JBDOUBLE *a,
///< pointer to the constant parameter regression coefficient.
                             JBDOUBLE *b)
///< pointer to the exponent regression coefficient.
{
  int i;
  for (i = n; i-- >= 0;)
    x[i] = LOGL (x[i]), y[i] = LOGL (y[i]);
  jbm_regression_linearl (x, y, n, a, b);
  *a = EXPL (*a);
}

/**
 * Function to calculate the coefficients of a multilinear regression adjusted 
 * by minimum squares: \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_multilinearl (JBDOUBLE **restrict x,
///< array of point coordinates in format:
///< \f$\left(x_1,\cdots,x_n,y_1,\cdots,y_n,\cdots,f_1,\cdots,f_n\right)\f$.
                             int n,     ///< points number.
                             JBDOUBLE *restrict a,
///< array of regression coefficients.
                             int m)     ///< number of variables.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE c[(m + 1) * (m + 2)];
  JBDOUBLE *d, *xj, *xk;
  int i, j, k;
  ++m;
  for (j = m; --j > 0;)
    {
      for (k = m; --k >= j;)
        {
          d = c + (m + 1) * j + k;
          xj = x[j];
          xk = x[k];
          for (*d = c0, i = n + 1; --i >= 0;)
            *d += *(xj++) ** (xk++);
        }
      d = c + (m + 1) * j + m;
      xj = x[j];
      xk = x[0];
      for (*d = c0, i = n + 1; --i >= 0;)
        *d += *(xj++) ** (xk++);
    }
  for (k = m; --k > 0;)
    {
      d = c + k;
      xk = x[k];
      for (*d = c0, i = n + 1; --i >= 0;)
        *d += *(xk++);
    }
  d = c + m;
  xk = x[0];
  for (*d = c0, i = n + 1; --i >= 0;)
    *d += *(xk++);
  c[0] = n + 1;
  for (j = m; --j > 0;)
    for (k = j; --k >= 0;)
      c[(m + 1) * j + k] = c[(m + 1) * k + j];
  jbm_matrix_solvel (c, m);
  for (i = 0, d = c + m; ++i <= m; ++a, d += m + 1)
    *a = *d;
}

/**
 * Function to calculate the coefficients of a multiexponential regression 
 * adjusted by minimum squares: \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_multiexponentiall (JBDOUBLE **restrict x,
///< array of point coordinates in format:
///< \f$\left(x_1,\cdots,x_n,y_1,\cdots,y_n,\cdots,f_1,\cdots,f_n\right)\f$. It
///< is modified by the function.
                                  int n,        ///< points number.
                                  JBDOUBLE *restrict a,
///< array of regression coefficients.
                                  int m)        ///< number of variables.
{
  JBDOUBLE *c;
  int i, j;
  for (j = m + 1; --j >= 0;)
    for (i = n + 1, c = x[j]; --i >= 0;)
      c[i] = LOGL (c[i]);
  jbm_regression_multilinearl (x, n, a, m);
  a[0] = EXPL (a[0]);
}

/**
 * Function to calculate a cubic spline on tabular data (JBDOUBLE).
 */
static inline void
jbm_spline_cubicl (JBDOUBLE *restrict x,
                   ///< array of point x-coordinates.
                   JBDOUBLE *y,
                   ///< array of point y-coordinates.
                   int n,       ///< number of points.
                   JBDOUBLE **restrict b,
///< pointer to the array of 1st order spline coefficients. It is generated by
///< malloc.
                   JBDOUBLE **restrict c,
///< pointer to the array of 2nd order spline coefficients.
                   JBDOUBLE **restrict d)
///< pointer to the array of 3rd order spline coefficients.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f, c1 = 1.f, c3 = 3.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0., c1 = 1., c3 = 3.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L, c1 = 1.L, c3 = 3.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q, c1 = 1.Q, c3 = 3.Q;
#endif
  JBDOUBLE *B, *C, *D, *E, *F, *H;
  JBDOUBLE dx;
  int i, j, m;
  --n;
  m = 3 * n;
  B = (JBDOUBLE *) malloc (6 * (m - 1) * sizeof (JBDOUBLE));
  C = B + m - 2;
  D = C + m - 1;
  E = D + m;
  F = E + m - 1;
  H = F + m - 2;
  dx = x[1] - x[0];
  B[0] = B[1] = D[3] = E[2] = E[3] = F[3] = H[1] = H[2] = H[3] = c0;
  C[0] = C[1] = C[2] = c1;
  F[1] = F[2] = -c1;
  D[0] = dx;
  D[1] = D[0] + dx;
  D[2] = D[1] + dx;
  E[0] = D[0] * dx;
  E[1] = c3 * E[0];
  F[0] = E[0] * dx;
  H[0] = y[1] - y[0];
  for (i = n - 1; --i > 0;)
    {
      j = 3 * i + 1;
      dx = x[i + 1] - x[i];
      B[j - 2] = D[j + 2] = F[j] = F[j + 1] = F[j + 2] = H[j + 1] = H[j + 2]
        = c0;
      B[j - 1] = B[j] = c1;
      E[j + 1] = E[j + 2] = -c1;
      C[j - 1] = dx;
      C[j] = C[j - 1] + dx;
      C[j + 1] = C[j] + dx;
      D[j] = C[j - 1] * dx;
      D[j + 1] = c3 * D[j];
      E[j] = D[j] * dx;
      H[j] = y[i + 1] - y[i];
    }
  j = 3 * n - 2;
  dx = x[n] - x[n - 1];
  B[j - 2] = B[j - 1] = C[j] = H[j + 1] = c0;
  D[j + 1] = c1;
  C[j - 1] = dx;
  D[j] = dx * dx;
  E[j] = D[j] * dx;
  H[j] = y[n] - y[n - 1];
  jbm_matrix_solve_pentadiagonall (B, C, D, E, F, H, m - 1);
  *b = (JBDOUBLE *) malloc (3 * n * sizeof (JBDOUBLE));
  *c = *b + n;
  *d = *c + n;
  for (i = n; i-- > 0;)
    {
      j = 3 * i;
      (*b)[i] = H[j];
      (*c)[i] = H[j + 1];
      (*d)[i] = H[j + 2];
    }
  free (B);
}

/**
 * Function to find the segment number where a number is in an array of segments
 * defined in an array of structs (JBDOUBLE).
 *
 * \return segment number.
 */
static inline int
jbm_varray_searchl (JBDOUBLE x, ///< number to search.
                    void *v,
///< pointer to the field in JBDOUBLE format of the 1st element of the array of
///< structs.
                    int size,   ///< size in bytes of the structs.
                    int n)      ///< number of structs.
{
  int i, j;
  for (i = 0; n - i > 1;)
    {
      j = (i + n) >> 1;
      if (x <= *(JBDOUBLE *) ((char *) v + j * size))
        n = j;
      else
        i = j;
    }
  return i;
}

/**
 * Function to find the segment number where a number is in an array of segments
 * defined in an array of structs checking if the number is out (JBDOUBLE).
 *
 * \return segment number, -1 if \f$x<v_0\f$ or \f$n\f$ if \f$x>v_n\f$.
 */
static inline int
jbm_varray_search_extendedl (JBDOUBLE x,        ///< number to search.
                             void *v,
///< pointer to the field in JBDOUBLE format of the 1st element of the array of
///< structs.
                             int size,  ///< size in bytes of the structs.
                             int n)     ///< number of structs.
{
  int i;
  if (x < *(JBDOUBLE *) v)
    i = -1;
  else if (x >= *(JBDOUBLE *) ((char *) v + n * size))
    i = n;
  else
    i = jbm_varray_search (x, v, size, n);
  return i;
}

/**
 * \brief Function to find the highest value in an array of structs (JBDOUBLE).
 *
 * \return the highest value.
 */
static inline JBDOUBLE
jbm_varray_maxl (void *v,
///< pointer to the field in JBDOUBLE format of the 1st element of the array of
///< structs.
                 int size,      ///< size in bytes of the structs.
                 int n)         ///< number of structs.
{
  int i;
  JBDOUBLE k;
  k = *(JBDOUBLE *) v;
  for (i = 0; ++i <= n;)
    k = FMAXL (k, *(JBDOUBLE *) (v = (char *) v + size));
  return k;
}

/**
 * \brief Function to find the lowest value in an array of structs (JBDOUBLE).
 *
 * \return the lowest value.
 */
static inline JBDOUBLE
jbm_varray_minl (void *v,
///< pointer to the field in JBDOUBLE format of the 1st element of the array of
///< structs.
                 int size,      ///< size in bytes of the structs.
                 int n)         ///< number of structs.
{
  int i;
  JBDOUBLE k;
  k = *(JBDOUBLE *) v;
  for (i = 0; ++i <= n;)
    k = FMINL (k, *(JBDOUBLE *) (v = (char *) v + size));
  return k;
}

/**
 * Function to find the highest and the lowest values in an array of structs
 * (JBDOUBLE).
 */
static inline void
jbm_varray_maxminl (void *v,
///< pointer to the field in JBDOUBLE format of the 1st element of the array of
///< structs.
                    int size,   ///< size in bytes of the structs.
                    int n,      ///< number of structs.
                    JBDOUBLE *max,      ///< pointer to the highest value.
                    JBDOUBLE *min)      ///< pointer to the lowest value.
{
  int i;
  JBDOUBLE kmax, kmin;
  kmax = kmin = *(JBDOUBLE *) v;
  for (i = 0; ++i <= n;)
    {
      v = (char *) v + size;
      if (kmax < *(JBDOUBLE *) v)
        kmax = *(JBDOUBLE *) v;
      else if (kmin > *(JBDOUBLE *) v)
        kmin = *(JBDOUBLE *) v;
    }
  *max = kmax, *min = kmin;
}

/**
 * Function to calculate the mean square error between 2 functions tabulated in
 * 2 arrays of structs (JBDOUBLE).
 *
 * \return mean square error value.
 */
static inline JBDOUBLE
jbm_varray_mean_square_errorl (void *restrict xa,
///< x-coordinates tabulating the 1st function.
                               void *restrict fa,
///< values of the 1st function.
                               int sizea,
///< size of the structs of the 1st array.
                               int na,
///< the highest point number tabulating the 1st function.
                               void *restrict xr,
///< x-coordinates tabulating the 2nd function.
                               void *restrict fr,
///< values of the 2nd function.
                               int sizer,
///< size of the structs of the 2nd array.
                               int nr)
///< the highest point number tabulating the 2nd function.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE k, k2;
  int i, j;
  k = c0;
  for (i = 0; i <= na && *(JBDOUBLE *) xa < *(JBDOUBLE *) xr;
       ++i, xa = (char *) xa + sizea, fa = (char *) fa + sizea)
    k += jbm_fsqr (*(JBDOUBLE *) fa - *(JBDOUBLE *) fr);
  for (j = 0; i <= na; ++i, xa = (char *) xa + sizea, fa = (char *) fa + sizea)
    {
      while (j < nr && *(JBDOUBLE *) xa > *(JBDOUBLE *) ((char *) xr + sizer))
        ++j, xr = (char *) xr + sizer, fr = (char *) fr + sizer;
      if (j == nr)
        {
          for (; i <= na;
               ++i, xa = (char *) xa + sizea, fa = (char *) fa + sizea)
            k += jbm_fsqrl (*(JBDOUBLE *) fa - *(JBDOUBLE *) fr);
        }
      else
        {

          k2 = jbm_extrapolatel (*(JBDOUBLE *) xa,
                                 *(JBDOUBLE *) xr,
                                 *(JBDOUBLE *) ((char *) xr + sizer),
                                 *(JBDOUBLE *) fr,
                                 *(JBDOUBLE *) ((char *) fr + sizer));
          k += jbm_fsqrl (*(JBDOUBLE *) fa - k2);
        }
    }
  k /= na + 1;
  return k;
}

/**
 * Function to calculate the root mean square error between 2 functions
 * tabulated in 2 arrays of structs (JBDOUBLE).
 *
 * \return root mean square error value.
 */
static inline JBDOUBLE
jbm_varray_root_mean_square_errorl (void *restrict xa,
///< x-coordinates tabulating the 1st function.
                                    void *restrict fa,
///< values of the 1st function.
                                    int sizea,
///< size of the structs of the 1st array.
                                    int na,
///< the highest point number tabulating the 1st function.
                                    void *restrict xr,
///< x-coordinates tabulating the 2nd function.
                                    void *restrict fr,
///< values of the 2nd function.
                                    int sizer,
///< size of the structs of the 2nd array.
                                    int nr)
///< the highest point number tabulating the 2nd function.
{
  return SQRTL
    (jbm_varray_mean_square_errorl (xa, fa, na, sizea, xr, fr, nr, sizer));
}

/**
 * Function to solve a tridiagonal linear equations system stored in the fields
 * of a struct array with format:
 * \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &        & H_0\\
 * C_0 & D_1    & E_1     &        & H_1\\
 *     & \ddots & \ddots  & \ddots & \vdots\\
 *     &        & C_{n-1} & D_n    & H_n
 * \end{array}\right)\f$.
 * Results are stored in the H fields. It modifies D and H fields (JBDOUBLE).
 */
static inline void
jbm_varray_solve_tridiagonall (void *restrict C,
///< field address of first element of the struct array containing the left
///< diagonal equation system values.
                               void *restrict D,
///< field addres of first element of the struct array containing the central
///< diagonal equation system values.
                               void *restrict E,
///< field address of first element of the struct array containing the right
///< diagonal equation system values.
                               void *restrict H,
///< field address of first element of the struct array containing the final
///< equation system values.
                               int size,        ///< struct size.
                               int n)   ///< the latest struct array element.
{
  JBDOUBLE *CC, *DD, *EE, *HH;
  JBDOUBLE k;
  int i;
  DD = (JBDOUBLE *) D;
  HH = (JBDOUBLE *) H;
  for (i = 0; ++i <= n; C = (char *) C + size, E = (char *) E + size)
    {
      CC = (JBDOUBLE *) C;
      EE = (JBDOUBLE *) E;
      k = *CC / *DD;
      D = (char *) D + size;
      DD = (JBDOUBLE *) D;
      *DD -= k ** EE;
      k *= *HH;
      H = (char *) H + size;
      HH = (JBDOUBLE *) H;
      *HH -= k;
    }
  *HH /= *DD;
  while (--i > 0)
    {
      E = (char *) E - size;
      EE = (JBDOUBLE *) E;
      k = *EE ** HH;
      D = (char *) D - size;
      DD = (JBDOUBLE *) D;
      H = (char *) H - size;
      HH = (JBDOUBLE *) H;
      *HH = (*HH - k) / *DD;
    }
}

/**
 * Function to solve a tridiagonal linear equations system stored in the fields
 * of a struct array with format:
 * \f$\left(\begin{array}{cccc|c}
 * D_0 & E_0    &         &        & H_0\\
 * C_0 & D_1    & E_1     &        & H_1\\
 *     & \ddots & \ddots  & \ddots & \vdots\\
 *     &        & C_{n-1} & D_n    & H_n
 * \end{array}\right)\f$.
 * avoiding zero divisions. Results are stored in the H fields. It modifies D
 * and H fields (JBDOUBLE).
 */
static inline void
jbm_varray_solve_tridiagonal_zerol (void *restrict C,
///< field address of first element of the struct array containing the left
///< diagonal equation system values.
                                    void *restrict D,
///< field addres of first element of the struct array containing the central
///< diagonal equation system values.
                                    void *restrict E,
///< field address of first element of the struct array containing the right
///< diagonal equation system values.
                                    void *restrict H,
///< field address of first element of the struct array containing the final
///< equation system values.
                                    int size,   ///< struct size.
                                    int n)
                                    ///< the latest struct array element.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE *CC, *DD, *EE, *HH;
  JBDOUBLE k;
  int i;
  DD = (JBDOUBLE *) D;
  HH = (JBDOUBLE *) H;
  for (i = 0; ++i <= n; C = (char *) C + size, E = (char *) E + size)
    {
      CC = (JBDOUBLE *) C;
      EE = (JBDOUBLE *) E;
      if (jbm_small (*DD))
        D = (char *) D + size, H = (char *) H + size;
      else
        {
          k = *CC / *DD;
          D = (char *) D + size;
          DD = (JBDOUBLE *) D;
          *DD -= k ** EE;
          k *= *HH;
          H = (char *) H + size;
          HH = (JBDOUBLE *) H;
          *HH -= k;
        }
    }
  if (jbm_small (*DD))
    *HH = c0;
  else
    *HH /= *DD;
  while (--i > 0)
    {
      E = (char *) E - size;
      EE = (JBDOUBLE *) E;
      k = *EE ** HH;
      D = (char *) D - size;
      DD = (JBDOUBLE *) D;
      H = (char *) H - size;
      HH = (JBDOUBLE *) H;
      if (jbm_smalll (*DD))
        *HH = c0;
      else
        *HH = (*HH - k) / *DD;
    }
}

/**
 * Function to calculate the mean square error between 2 functions tabulated in
 * 2 columns data of a file (JBDOUBLE).
 *
 * \return mean square error value.
 */
static inline JBDOUBLE
jbm_file_mean_square_errorl (char *namea,
///< name of file where the 1st function is tabulated.
                             int ixa,
///< column number of x-coordinates tabulating the 1st function.
                             int ifa,
///< column number of values tabulating the 1st function.
                             int na,
///< columns number of file tabulating the 1st function.
                             char *namer,
///< name of file where the 2nd function is tabulated.
                             int ixr,
///< column number of x-coordinates tabulating the 2nd function.
                             int ifr,
///< column number of values tabulating the 2nd function.
                             int nr)
///< columns number of file tabulating the 2nd function.
{
#if JBM_HIGH_PRECISION == 1
  const JBDOUBLE c0 = 0.f;
#elif JBM_HIGH_PRECISION == 2
  const JBDOUBLE c0 = 0.;
#elif JBM_HIGH_PRECISION == 3
  const JBDOUBLE c0 = 0.L;
#elif JBM_HIGH_PRECISION == 4
  const JBDOUBLE c0 = 0.Q;
#endif
  JBDOUBLE aa[na], ar[nr];
  FILE *filea, *filer;
  JBDOUBLE k, xa, fa, xr1, fr1, xr2, fr2;
  int i, j, endr;
  endr = i = 0;
  k = c0;
  filea = fopen (namea, "r");
  if (!filea)
    goto exit_mse;
  filer = fopen (namer, "r");
  if (!filer)
    goto exit_mse;
  for (j = 0; j < nr; ++j)
    if (jbm_read_double (filer, ar + j) != 1)
      goto exit_mse;
  xr1 = ar[ixr - 1];
  fr1 = ar[ifr - 1];
  for (j = 0; j < nr; ++j)
    if (jbm_read_double (filer, ar + j) != 1)
      endr = 1;
  xr2 = ar[ixr - 1];
  fr2 = ar[ifr - 1];
  for (i = 0; !endr; ++i)
    {
      for (j = 0; j < na; ++j)
        if (jbm_read_double (filea, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      while (xa > xr2)
        {
          xr1 = xr2;
          fr1 = fr2;
          for (j = 0; j < nr; ++j)
            if (jbm_read_double (filer, ar + j) != 1)
              {
                endr = 1;
                goto end_filer;
              }
          xr2 = ar[ixr - 1];
          fr2 = ar[ifr - 1];
        }
    end_filer:
      if (!endr && xa > xr1)
        k += jbm_fsqrl (fa - jbm_extrapolatel (xa, xr1, xr2, fr1, fr2));
      else
        k += jbm_fsqrl (fa - fr1);
    }
  for (; 1; ++i)
    {
      for (j = 0; j < na; ++j)
        if (jbm_read_double (filea, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      k += jbm_fsqrl (fa - fr1);
    }
exit_mse:
  if (i == 0)
    return c0;
  return k / i;
}

/**
 * Function to calculate the root mean square error between 2 functions
 * tabulated in 2 columns data of a file (JBDOUBLE).
 *
 * \return root mean square error value.
 */
static inline JBDOUBLE
jbm_file_root_mean_square_errorl (char *namea,
///< name of file where the 1st function is tabulated.
                                  int ixa,
///< column number of x-coordinates tabulating the 1st function.
                                  int ifa,
///< column number of values tabulating the 1st function.
                                  int na,
///< columns number of file tabulating the 1st function.
                                  char *namer,
///< name of file where the 2nd function is tabulated.
                                  int ixr,
///< column number of x-coordinates tabulating the 2nd function.
                                  int ifr,
///< column number of values tabulating the 2nd function.
                                  int nr)
///< columns number of file tabulating the 2nd function.
{
  return SQRTL
    (jbm_file_mean_square_errorl (namea, ixa, ifa, na, namer, ixr, ifr, nr));
}

#endif
