/* JB - A library with useful mathematical, XML, JSON, GTK and OpenGL functions.
 *
 * Copyright 2005-2023, Javier Burguete Tolosa.
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
 * \file jb_math.h
 * \brief Header file with useful mathematical functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2023, Javier Burguete Tolosa.
 */
#ifndef JB_MATH__H
#define JB_MATH__H 1

#include "jb_def.h"
#include <math.h>
#include <sys/param.h>

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
#define SQRT sqrt
#define FRF "%e"
#define FWF "%.6e"
#define FPF "%.6g"
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
#define SQRT sqrt
#define FRF "%le"
#define FWF "%.13le"
#define FPF "%.13lg"
#define FGF "%.5lg"
#define JBM_EPSILON DBL_EPSILON
#define JB_PI M_PI
#else
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
#define SQRT sqrtl
#define FRF "%Le"
#define FWF "%.17Le"
#define FPF "%.17Lg"
#define FGF "%.5Lg"
#define JBM_EPSILON LDBL_EPSILON
#define JB_PI M_PIl
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
#define SQRTL sqrt
#define JBM_EPSILONL FLT_EPSILON
#define JB_PIL M_PI
#define FRL "%e"
#define FWL "%.6e"
#define FPL "%.6g"
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
#define SQRTL sqrt
#define JBM_EPSILONL DBL_EPSILON
#define JB_PIL M_PI
#define FRL "%le"
#define FWL "%.13le"
#define FPL "%.13lg"
#define FGL "%.5lg"
#else
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
#define SQRTL sqrtl
#define JBM_EPSILONL LDBL_EPSILON
#define JB_PIL M_PIl
#define FRL "%Le"
#define FWL "%.17Le"
#define FPL "%.17Lg"
#define FGL "%.5Lg"
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
#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.)? 0.: \
    (FABS(a) < FABS(b))? (a): (b))
/**
 * macro calculating the number with the lower module in the [a, b] interval 
 * (JBDOUBLE arguments).
 * \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 * 0, & a\cdot b\le 0;\\
 * a, & a,b\ne 0,\;|a|<|b|;\\
 * b, & a,b\ne 0,\;|a|\ge|b|;
 * \end{array}\right.\f$.
 */
#define JBM_FMODMINL(a, b) (((a) * (b) <= 0.L)? 0.L: \
    (FABSL(a) < FABSL(b))? (a): (b))
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

#if JBM_HIGH_PRECISION == JBM_LOW_PRECISION

#if JBM_HIGH_PRECISION < 3

void jbm_index_sort_flash (JBFLOAT * x, unsigned int *ni, int n);

#define jbm_index_sort_flashl jbm_index_sort_flash

#else

void jbm_index_sort_flashl (JBDOUBLE * x, unsigned int *ni, int n);

#define jbm_index_sort_flash jbm_index_sort_flashl

#endif

#else

void jbm_index_sort_flash (JBFLOAT * x, unsigned int *ni, int n);
void jbm_index_sort_flashl (JBDOUBLE * x, unsigned int *ni, int n);

#endif


/**
 * Function to calculate the minimum of 2 int numbers.
 *
 * \return minimum int number.
 */
static inline int
jbm_min (int a,                 ///< 1st int number.
         int b)                 ///< 2nd int number.
{
  return JBM_MIN (a, b);
}

/**
 * Function to calculate the maximum of 2 int numbers.
 *
 * \return maximum int number.
 */
static inline int
jbm_max (int a,                 ///< 1st int number.
         int b)                 ///< 2nd int number.
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
jbm_modmin (int a,              ///< 1st int number.
            int b)              ///< 2nd int number.
{
  return JBM_MODMIN (a, b);
}

/**
 * Function to interchange 2 int numbers.
 */
static inline void
jbm_change (int *restrict a,  ///< 1st int number pointer. 
            int *restrict b)  ///< 1st int number pointer. 
{
  int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of an int number.
 *
 * \return int square.
 */
static inline int
jbm_sqr (int x)                 ///< int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of an unsigned int number.
 *
 * \return unsigned int double.
 */
static inline unsigned int
jbm_dblu (unsigned int x)       ///< unsigned int number.
{
  return JBM_DBL (x);
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
 * Function to calculate the square of an unsigned int number.
 *
 * \return unsigned int square.
 */
static inline unsigned int
jbm_sqru (unsigned int x)       ///< unsigned int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the maximum of 2 long int numbers.
 *
 * \return maximum long int number.
 */
static inline long int
jbm_maxl (long int a,           ///< 1st long int number.
          long int b)           ///< 2nd long int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the minimum of 2 long int numbers.
 *
 * \return minimum long int number.
 */
static inline long int
jbm_minl (long int a,           ///< 1st long int number.
          long int b)           ///< 2nd long int number.
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
jbm_modminl (long int a,        ///< 1st long int number.
             long int b)        ///< 2nd long int number.
{
  return (int) JBM_MODMINL (a, b);
}

/**
 * Function to interchange 2 long int numbers.
 */
static inline void
jbm_changel (long int *restrict a,    ///< 1st long int number pointer. 
             long int *restrict b)    ///< 1st long int number pointer. 
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
jbm_sqrl (long int x)           ///< long int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a long int number.
 *
 * \return long int double.
 */
static inline long int
jbm_dbll (long int x)           ///< long int number.
{
  return JBM_DBL (x);
}

/**
 * Function to interchange 2 long unsigned int numbers.
 */
static inline void
jbm_changeul (long unsigned int *restrict a,
              ///< 1st long unsigned int number pointer.
              long unsigned int *restrict b)
              ///< 1st long unsigned int number pointer.
{
  long unsigned int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a long unsigned int number.
 *
 * \return long unsigned int square.
 */
static inline long unsigned int
jbm_sqrul (long unsigned int x) ///< long unsigned int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a long unsigned int number.
 *
 * \return long unsigned int double.
 */
static inline long unsigned int
jbm_dblul (long unsigned int x) ///< long unsigned int number.
{
  return JBM_DBL (x);
}

/**
 * Function to calculate the maximum of 2 long long int numbers.
 *
 * \return maximum long long int number.
 */
static inline long long int
jbm_maxll (long long int a,     ///< 1st long long int number.
           long long int b)     ///< 2nd long long int number.
{
  return JBM_MAX (a, b);
}

/**
 * Function to calculate the minimum of 2 long long int numbers.
 *
 * \return minimum long long int number.
 */
static inline long long int
jbm_minll (long long int a,     ///< 1st long long int number.
           long long int b)     ///< 2nd long long int number.
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
jbm_modminll (long long int a,  ///< 1st long long int number.
              long long int b)  ///< 2nd long long int number.
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
jbm_sqrll (long long int x)     ///< long long int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a long long int number.
 *
 * \return long long int double.
 */
static inline long long int
jbm_dblll (long long int x)     ///< long long int number.
{
  return JBM_DBL (x);
}

/**
 * Function to interchange 2 long long unsigned int numbers.
 */
static inline void
jbm_changeull (long long unsigned int *restrict a,
               ///< 1st long long unsigned int number pointer. 
               long long unsigned int *restrict b)
               ///< 1st long long unsigned int number pointer. 
{
  long long unsigned int c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a long long unsigned int number.
 *
 * \return long long unsigned int square.
 */
static inline long long unsigned int
jbm_sqrull (long long unsigned int x)   ///< long long unsigned int number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a long long unsigned int number.
 *
 * \return long long unsigned int double.
 */
static inline long long unsigned int
jbm_dblull (long long unsigned int x)   ///< long long unsigned int number.
{
  return JBM_DBL (x);
}

/**
 * Function to check small JBFLOAT numbers.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline int
jbm_small (JBFLOAT x)           ///< JBFLOAT number.
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
jbm_fmodmin (JBFLOAT a,         ///< 1st JBFLOAT number.
             JBFLOAT b)         ///< 2nd JBFLOAT number.
{
  return JBM_FMODMIN (a, b);
}

/**
 * Function to interchange 2 JBFLOAT numbers.
 */
static inline void
jbm_fchange (JBFLOAT *restrict a,    ///< 1st JBFLOAT number pointer.
             JBFLOAT *restrict b)    ///< 2nd JBFLOAT number pointer.
{
  JBFLOAT c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a JBFLOAT number.
 *
 * \return JBFLOAT square.
 */
static inline JBFLOAT
jbm_fsqr (JBFLOAT x)            ///< JBFLOAT number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a JBFLOAT number.
 *
 * \return JBFLOAT double.
 */
static inline JBFLOAT
jbm_fdbl (JBFLOAT x)            ///< JBFLOAT number.
{
  return JBM_DBL (x);
}

/**
 * Function to perform an extrapolation between 2 2D points (JBFLOAT).
 *
 * \return y-coordinate of the extrapolated point.
 */
static inline JBFLOAT
jbm_extrapolate (JBFLOAT x,     ///< x-coordinate of the extrapolated point.
                 JBFLOAT x1,    ///< x-coordinate of the 1st point.
                 JBFLOAT x2,    ///< x-coordinate of the 2nd point.
                 JBFLOAT y1,    ///< y-coordinate of the 1st point.
                 JBFLOAT y2)    ///< y-coordinate of the 2nd point.
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
jbm_interpolate (JBFLOAT x,     ///< x-coordinate of the interpolated point.
                 JBFLOAT x1,    ///< x-coordinate of the 1st point.
                 JBFLOAT x2,    ///< x-coordinate of the 2nd point.
                 JBFLOAT y1,    ///< y-coordinate of the 1st point.
                 JBFLOAT y2)    ///< y-coordinate of the 2nd point.
{
  JBFLOAT k;
  if (x <= x1)
    k = y1;
  else if (x >= x2)
    k = y2;
  else
    k = jbm_extrapolate (x, x1, x2, y1, y2);
  return k;
}

/**
 * Function to calculate the length of a 2D segment (JBFLOAT).
 *
 * \return segment length.
 */
static inline JBFLOAT
jbm_v2_length (JBFLOAT x1,
///< x-coordinate of the 1st point defining the segment.
               JBFLOAT y1,
///< y-coordinate of the 1st point defining the segment.
               JBFLOAT x2,
///< x-coordinate of the 2nd point defining the segment.
               JBFLOAT y2)
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
jbm_v3_length (JBFLOAT x1,
///< x-coordinate of the 1st point defining the segment.
               JBFLOAT y1,
///< y-coordinate of the 1st point defining the segment.
               JBFLOAT z1,
///< z-coordinate of the 1st point defining the segment.
               JBFLOAT x2,
///< x-coordinate of the 2nd point defining the segment.
               JBFLOAT y2,
///< y-coordinate of the 2nd point defining the segment.
               JBFLOAT z2)
///< z-coordinate of the 2nd point defining the segment.
{
  return HYPOT (HYPOT (x2 - x1, y2 - y1), z2 - z1);
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
                             JBFLOAT x1,
                             ///< left limit of the solution interval.
                             JBFLOAT x2)
                             ///< right limit of the solution interval.
{
  JBFLOAT k;
  a /= 2.;
  b = SQRT (a * a - b);
  k = b - a;
  if (k < x1 || k > x2)
    k = -b - a;
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
jbm_solve_quadratic (JBFLOAT a,
                     ///< 2nd order coefficient of the equation.
                     JBFLOAT b,
                     ///< 1st order coefficient of the equation.
                     JBFLOAT c,
                     ///< 0th order coefficient of the equation.
                     JBFLOAT x1,
                     ///< left limit of the solution interval.
                     JBFLOAT x2)
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
                         JBFLOAT b,
                         ///< 1st order coefficient of the equation.
                         JBFLOAT c,
                         ///< 0th order coefficient of the equation.
                         JBFLOAT x1,
                         ///< left limit of the solution interval.
                         JBFLOAT x2)
                         ///< right limit of the solution interval.
{
  JBFLOAT k0, k1, k2;
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
      k2 += CBRT (k0);
      k2 -= a;
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
jbm_solve_cubic (JBFLOAT a,
                 ///< 3rd order coefficient of the equation.
                 JBFLOAT b,
                 ///< 2nd order coefficient of the equation.
                 JBFLOAT c,
                 ///< 1st order coefficient of the equation.
                 JBFLOAT d,
                 ///< 0th order coefficient of the equation.
                 JBFLOAT x1,
                 ///< left limit of the solution interval.
                 JBFLOAT x2)
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
jbm_flux_limiter_total (JBFLOAT d1 __attribute__((unused)),
///< 1st flux limiter function parameter.
                        JBFLOAT d2 __attribute__((unused)))
///< 2nd flux limiter function parameter.
{
  return 0.;
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_null (JBFLOAT d1 __attribute__((unused)),
                       ///< 1st flux limiter function parameter.
                       JBFLOAT d2 __attribute__((unused)))
///< 2nd flux limiter function parameter.
{
  return 1.;
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_centred (JBFLOAT d1,
                          ///< 1st flux limiter function parameter.
                          JBFLOAT d2)
                          ///< 2nd flux limiter function parameter.
{
  if (jbm_small (d2))
    return 0.;
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
jbm_flux_limiter_superbee (JBFLOAT d1,
                           ///< 1st flux limiter function parameter.
                           JBFLOAT d2)
                           ///< 2nd flux limiter function parameter.
{
  JBFLOAT r;
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  r = d1 / d2;
  return FMAX (FMIN (r + r, 1.), FMIN (r, 2.));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_minmod (JBFLOAT d1,
                         ///< 1st flux limiter function parameter.
                         JBFLOAT d2)
                         ///< 2nd flux limiter function parameter.
{
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  return FMIN (d1 / d2, 1.);
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
jbm_flux_limiter_VanLeer (JBFLOAT d1,
                          ///< 1st flux limiter function parameter.
                          JBFLOAT d2)
                          ///< 2nd flux limiter function parameter.
{
  JBFLOAT r, k;
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  r = d1 / d2;
  k = FABS (r);
  return (r + k) / (1. + k);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_VanAlbada (JBFLOAT d1,
                            ///< 1st flux limiter function parameter.
                            JBFLOAT d2)
                            ///< 2nd flux limiter function parameter.
{
  JBFLOAT r, k;
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  r = d1 / d2;
  k = r * r;
  return (r + k) / (1. + k);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_minsuper (JBFLOAT d1,
                           ///< 1st flux limiter function parameter.
                           JBFLOAT d2)
                           ///< 2nd flux limiter function parameter.
{
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  return FMIN (d1 / d2, 2.);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_supermin (JBFLOAT d1,
                           ///< 1st flux limiter function parameter.
                           JBFLOAT d2)
                           ///< 2nd flux limiter function parameter.
{
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  return FMIN (jbm_fdbl (d1 / d2), 1.);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_monotonized_central (JBFLOAT d1,
                                      ///< 1st flux limiter function parameter.
                                      JBFLOAT d2)
                                      ///< 2nd flux limiter function parameter.
{
  JBFLOAT k;
  if (d1 * d2 <= JBM_EPSILON)
    return 0.;
  k = d1 / d2;
  if (k >= 3.)
    return 2.;
  if (k <= 1. / 3.)
    return k + k;
  return 0.5 * (k + 1.);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (JBFLOAT).
 *
 * \return flux limiter function value.
 */
static inline JBFLOAT
jbm_flux_limiter_mean (JBFLOAT d1,
                       ///< 1st flux limiter function parameter.
                       JBFLOAT d2)
                       ///< 2nd flux limiter function parameter.
{
  if (jbm_small (d2))
    return 0.;
  return 0.5 * (d1 / d2 + 1.);
}

/**
 * Function to select a flux limiter function (JBFLOAT).
 *
 * \return pointer to the flux limiter function.
 */
static inline JBFLOAT (*jbm_flux_limiter_select (int type)) (JBFLOAT, JBFLOAT)
///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_total;
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_null;
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centred;
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmod;
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbee;
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeer;
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbada;
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuper;
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_supermin;
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_central;
    case JBM_FLUX_LIMITER_TYPE_MEAN:
      return jbm_flux_limiter_mean;
    }
  return NULL;
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (JBFLOAT).
 *
 * \return integral value.
 */
static inline JBFLOAT
jbm_integral (JBFLOAT (*f) (JBFLOAT),
              ///< pointer to the function to integrate.
              JBFLOAT x1,       ///< left limit of the interval.
              JBFLOAT x2)       ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBFLOAT a[1] = { 2.L }, b[1];
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBFLOAT a[2] = { 8. / 9.L, 5. / 9.L }, b[2] = {
    0., 0.7745966692414833770358531L
  };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBFLOAT a[3] = {
    0.5688888888888888888888889L,
    0.4786286704993664680412915L,
    0.2369268850561890875142640L
  }, b[3] = {
    0.L, 0.5384693101056830910363144L, 0.9061798459386639927976269L
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBFLOAT a[4] = {
    0.4179591836734693877551020L,
    0.3818300505051189449503698L,
    0.2797053914892766679014678L,
    0.1294849661688696932706114L
  }, b[4] = {
    0.L, 0.4058451513773971669066064L,
    0.7415311855993944398638648L, 0.9491079123427585245261897L
  };
#endif
  JBFLOAT k, k2, x, dx;
  int i;
  dx = 0.5L * (x2 - x1);
  x = 0.5L * (x1 + x2);
  k = a[0] * dx * f (x);
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = b[i] * dx;
      k += a[i] * dx * (f (x - k2) + f (x + k2));
    }
  return k;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * array of JBFLOAT numbers.
 *
 * \return interval number.
 */
static inline int
jbm_farray_search (JBFLOAT x,   ///< number to search.
                   JBFLOAT * fa,        ///< array of JBFLOAT numbers.
                   int n)       ///< number of the highest array element.
{
  int i, j;
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
 * array of JBFLOAT numbers.
 * \return interval number, -1 if x<fa[0] or n if x>fa[n].
 */
static inline int
jbm_farray_search_extended (JBFLOAT x,  ///< number to search.
                            JBFLOAT * fa,       ///< array of JBFLOAT numbers.
                            int n)
                            ///< number of the highest array element.
{
  int i;
  if (x < fa[0])
    i = -1;
  else if (x >= fa[n])
    i = n;
  else
    i = jbm_farray_search (x, fa, n);
  return i;
}

/**
 * Function to find the highest element of an array of JBFLOAT numbers.
 *
 * \return the highest value.
 */
static inline JBFLOAT
jbm_farray_max (JBFLOAT * fa,   ///< array of JBFLOAT numbers.
                int n)          ///< number of the ending array element.
{
  JBFLOAT k;
  int i;
  k = fa[0];
  for (i = 0; ++i <= n;)
    k = FMAX (k, fa[i]);
  return k;
}

/**
 * Function to find the lowest element of an array of JBFLOAT numbers.
 *
 * \return the lowest value.
 */
static inline JBFLOAT
jbm_farray_min (JBFLOAT * fa,   ///< array of JBFLOAT numbers.
                int n)          ///< number of the ending array element.
{
  JBFLOAT k;
  int i;
  k = fa[0];
  for (i = 0; ++i <= n;)
    k = FMIN (k, fa[i]);
  return k;
}

/**
 * Function to find the highest and the lowest elements of an array of JBFLOAT
 * numbers.
 */
static inline void
jbm_farray_maxmin (JBFLOAT * fa,        ///< array of JBFLOAT numbers.
                   int n,       ///< number of the ending array element.
                   JBFLOAT * max,       ///< the highest value.
                   JBFLOAT * min)       ///< the lowest value.
{
  JBFLOAT kmax, kmin;
  int i;
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
 * Function to interchange 2 arrays of JBFLOAT numbers.
 */
static inline void
jbm_farray_change (JBFLOAT *restrict fa,
                   ///< 1st array of JBFLOAT numbers.
                   JBFLOAT *restrict fb,
                   ///< 2nd array of JBFLOAT numbers.
                   int n)       ///< the highest element number of the arrays.
{
  JBFLOAT *fc;
  int n1;
  n1 = n + 1;
  fc = (JBFLOAT *) malloc (n1 * sizeof (JBFLOAT));
  memcpy (fc, fa, n1);
  memcpy (fa, fb, n1);
  memcpy (fb, fc, n1);
  free (fc);
}

/**
 * Function to calculate the y-coordinate of a 2D point interpolated 
 * between a tabular function defined by 2 arrays of JBFLOAT numbers.
 *
 * \return y-coordinate of the interpolated point.
 */
static inline JBFLOAT
jbm_farray_interpolate (JBFLOAT x,      ///< x-coordinate of the point.
                        JBFLOAT * fa,
///< increasingly sorted array of x-coordinates of the tabular function.
                        JBFLOAT * fb,
///< array of y-coordinates of the tabular function.
                        int n)  ///< the highest element number of the arrays.
{
  JBFLOAT k;
  int i;
  i = jbm_farray_search (x, fa, n);
  if (i == n)
    k = fb[i];
  else
    k = jbm_interpolate (x, fa[i], fa[i + 1], fb[i], fb[i + 1]);
  return k;
}

/**
 * Function to merge 2 increasingly sorted arrays of JBFLOAT numbers.
 *
 * \return resulting array.
 */
static inline JBFLOAT *
jbm_farray_merge (JBFLOAT *restrict fa,
                  ///< 1st increasingly sorted array of JBFLOAT numbers.
                  int na,
                  ///< the highest element number of the 1st array.
                  JBFLOAT *restrict fb,
                  ///< 2nd increasingly sorted array of JBFLOAT numbers.
                  int nb,
                  ///< the highest element number of the 2nd array.
                  JBFLOAT ** fc,
///< pointer to the resulting increasingly sorted array of JBFLOAT numbers.
                  int *nc)
///< pointer to the highest element number of the resulting array.
{
  JBFLOAT *restrict x;
  int i, j, k;
  x = (JBFLOAT *) g_try_malloc ((na + nb + 2) * sizeof (JBFLOAT));
  if (!x)
    return 0;
  for (i = j = k = 0; i <= na || j <= nb; ++k)
    {
      if (fa[i] > fb[j])
        x[k] = fb[j++];
      else if (fa[i] < fb[j])
        x[k] = fa[i++];
      else
        x[k] = fa[i++], j++;
    }
  *fc = (JBFLOAT *) jb_realloc (x, k * sizeof (JBFLOAT));
  *nc = --k;
  return *fc;
}

/**
 * Function to integrate a tabular function (JBFLOAT) in an interval.
 *
 * \return integral value.
 */
static inline JBFLOAT
jbm_farray_integral (JBFLOAT *restrict x,
///< incresingly sorted array of JBFLOAT numbers defining the x-coordinates of
///< the tabular function.
                     JBFLOAT *restrict y,
///< array of JBFLOAT numbers defining the y-coordinates of the tabular
///< function.
                     int n,     ///< the highest element number of the arrays.
                     JBFLOAT x1,
                     ///< left limit of the integration interval.
                     JBFLOAT x2)
                     ///< right limit of the integration interval.
{
  JBFLOAT *yy, *xx;
  JBFLOAT I, y1;
  int i;
  if (n == 0)
    {
      I = y[0] * (x2 - x1);
      goto exit1;
    }
  i = jbm_farray_search_extended (x1, x, n);
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
  else if (i == n)
    {
      I = y[i] * (x2 - x1);
      goto exit1;
    }
  else
    {
      I = 0.;
      xx = x + i;
      yy = y + i;
      y1 = jbm_extrapolate (x1, xx[0], xx[1], yy[0], yy[1]);
    }
  if (x2 < xx[1])
    {
      I += 0.5 * (y1 + jbm_extrapolate (x2, xx[0], xx[1], yy[0], yy[1]))
        * (x2 - x1);
      goto exit1;
    }
  I += 0.5 * (y1 + yy[1]) * (xx[1] - x1);
  if (++i == n)
    {
      I += yy[1] * (x2 - xx[1]);
      goto exit1;
    }
  while (++i < n && x2 > xx[2])
    {
      ++xx, ++yy;
      I += 0.5 * (yy[0] + yy[1]) * (xx[1] - xx[0]);
    }
  if (i == n)
    I += yy[2] * (x2 - xx[1]);
  else if (x2 < xx[2])
    I += 0.5 * (yy[1] + jbm_extrapolate (x2, xx[1], xx[2], yy[1], yy[2]))
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
jbm_farray_mean_square_error (JBFLOAT *restrict xa,
///< incresingly sorted array of JBFLOAT numbers defining the x-coordinates
///< of the 1st tabular function.
                              JBFLOAT *restrict fa,
///< array of JBFLOAT numbers defining the y-coordinates of the 1st tabular
///< function.
                              int na,
///< the highest element number of the arrays defining the 1st tabular
///< function.
                              JBFLOAT *restrict xr,
///< incresingly sorted array of JBFLOAT numbers defining the x-coordinates
///< of the 2nd tabular function.
                              JBFLOAT *restrict fr,
///< array of JBFLOAT numbers defining the y-coordinates of the 2nd tabular
///< function.
                              int nr)
///< the highest element number of the arrays defining the 2nd tabular
///< function.
{
  JBFLOAT k = 0.;
  int i, j;
  for (i = 0; i <= na && xa[i] < xr[0]; ++i)
    k += jbm_fsqr (fa[i] - fr[0]);
  for (j = 0; i <= na; ++i)
    {
      while (j < nr && xa[i] > xr[j + 1])
        ++j;
      if (j == nr)
        for (; i <= na; ++i)
          k += jbm_fsqr (fa[i] - fr[nr]);
      else
        k += jbm_fsqr (fa[i] - jbm_extrapolate (xa[i], xr[j], xr[j + 1], fr[j],
                                                fr[j + 1]));
    }
  k /= na + 1;
  return k;
}

/**
 * Function to calculate the root mean square error between 2 tabular functions
 * (JBFLOAT).
 *
 * \return root mean square error.
 */
static inline JBFLOAT
jbm_farray_root_mean_square_error (JBFLOAT *restrict xa,
///< incresingly sorted array of JBFLOAT numbers defining the x-coordinates
///< of the 1st tabular function.
                                   JBFLOAT *restrict fa,
///< array of JBFLOAT numbers defining the y-coordinates of the 1st tabular
///< function.
                                   int na,
///< the highest element number of the arrays defining the 1st tabular
///< function.
                                   JBFLOAT *restrict xr,
///< incresingly sorted array of JBFLOAT numbers defining the x-coordinates
///< of the 2nd tabular function.
                                   JBFLOAT *restrict fr,
///< array of JBFLOAT numbers defining the y-coordinates of the 2nd tabular
///< function.
                                   int nr)
///< the highest element number of the arrays defining the 2nd tabular
///< function.
{
  return SQRT (jbm_farray_mean_square_error (xa, fa, na, xr, fr, nr));
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the insertion method.
 */
static inline void
jbm_index_sort_insertion (JBFLOAT *restrict x,
                          ///< array of JBFLOAT numbers.
                          unsigned int *restrict ni,  ///< array of indexes.
                          int n)
                          ///< the highest element number of the arrays.
{
  JBFLOAT xi;
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
 * JBFLOAT numbers by the interchange method.
 */
static inline void
jbm_index_sort_interchange (JBFLOAT *restrict x,
                            ///< array of JBFLOAT numbers.
                            unsigned int *restrict ni,
                            ///< array of indexes.
                            int n)
                            ///< the highest element number of the arrays.
{
  JBFLOAT xi, xj;
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
 * JBFLOAT numbers by the merge method.
 */
static inline void
jbm_index_sort_merge (JBFLOAT *restrict x,   ///< array of JBFLOAT numbers.
                      unsigned int *restrict ni,      ///< array of indexes.
                      int n)    ///< the highest element number of the arrays.
{
  unsigned int nn[n + 1];
  unsigned int *ni1, *ni2, *nj, *nk, *nt;
  int j, i1, i2, k, l;
  j = JBM_INDEX_SORT_MERGE_MIN;
  if (n <= j)
    {
      jbm_index_sort_insertion (x, ni, n);
      return;
    }
  k = n / j;
  if (n % j)
    ++k;
  j = n / k;
  if (n % k)
    ++j;
  for (l = 0; l <= n - j; l += j)
    jbm_index_sort_insertion (x, ni + l, j - 1);
  if (l < n)
    jbm_index_sort_insertion (x, ni + l, n - l);
  for (nk = ni, nj = nn; j <= n; j *= 2)
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
    memcpy (ni, nk, l * sizeof (unsigned int));
}

/**
 * Function to sort from the highest to the lowest the indexes of an array of
 * JBFLOAT numbers by the optimal method.
 */
static inline void
jbm_index_sort (JBFLOAT *restrict x, ///< array of JBFLOAT numbers.
                unsigned int *restrict ni,    ///< array of indexes.
                int n)          ///< the highest element number of the arrays.
{
  int i;
  for (i = n + 1; --i >= 0;)
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
 * \return the highest element number of the sorted array.
 */
static inline int
jbm_index_sort_extended (JBFLOAT *restrict x,
                         ///< array of JBFLOAT numbers to sort.
                         JBFLOAT **restrict xr,
///< pointer to the array of sorted JBFLOAT numbers elliminating duplicated
///< numbers. It has to be freed with g_free.
                         int **restrict ni,
///< point to the array of sorted indexes. It has to be freed with g_free.
                         int n)
///< the highest element number of the array to sort.
{
  unsigned int nk[n + 1], nj[n + 1];
  JBFLOAT k1, k2;
  int i, j = 0;
  *ni = (int *) g_try_malloc ((n + 1) * sizeof (int));
  *xr = (JBFLOAT *) g_try_malloc ((n + 1) * sizeof (JBFLOAT));
  if (!*xr)
    {
      jb_free_null ((void **) ni);
      fprintf (stderr, "JBM index sort extended: no enough memory\n");
      goto index_exit;
    }
  jbm_index_sort (x, nk, n);
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
 * It modifies the x matrix (JBFLOAT).
 */
static inline void
jbm_matrix_solve (JBFLOAT * x,  ///< matrix storing the linear equations system.
                  int n)        ///< number of matrix rows.
{
  JBFLOAT *f, *g;
  JBFLOAT k1, k2;
  int i, j, k;
  // Setting n to the number of row elements
  ++n;
  // Scaling every equation to reduce rounding effects.
  for (i = n, f = x; --i > 0;)
    {
      jbm_farray_maxmin (f, n, &k1, &k2);
      k1 = FMAX (FABS (k1), FABS (k2));
      for (j = n; --j >= 0; ++f)
        *f /= k1;
    }
  // Gaussian elimination
  for (i = n - 1, f = x; --i > 0; f += n + 1)
    {
      // Obtaining the highest pivot element        
      k1 = FABS (*f);
      for (k = j = i, g = f; --j >= 0;)
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
          jbm_farray_change (g + j, f + j, i + 1);
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
 * Results are stored in the H array. It modifies D and H arrays (JBFLOAT).
 */
static inline void
jbm_matrix_solve_tridiagonal (JBFLOAT *restrict C,
                              ///< left diagonal array.
                              JBFLOAT *restrict D,
                              ///< central diagonal array.
                              JBFLOAT *restrict E,
                              ///< right diagonal array.
                              JBFLOAT *restrict H,   ///< final column array.
                              int n)    ///< number of matrix rows.
{
  JBFLOAT k;
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
                                   int n)       ///< number of matrix rows.
{
  JBFLOAT k;
  int i;
  for (i = 0; i < n; ++i)
    if (!jbm_small (D[i]))
      {
        k = C[i] / D[i];
        D[i + 1] -= k * E[i];
        H[i + 1] -= k * H[i];
      }
  if (jbm_small (D[i]))
    H[i] = 0.;
  else
    H[i] /= D[i];
  while (i--)
    if (jbm_small (D[i]))
      H[i] = 0.;
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
                                JBFLOAT *restrict H, ///< final column array.
                                int n)  ///< number of matrix rows.
{
  JBFLOAT k;
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
                                     int n)     ///< number of matrix rows.
{
  JBFLOAT k;
  int i;
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
    H[i + 1] = 0.;
  else
    H[i + 1] /= D[i + 1];
  if (jbm_small (D[i]))
    H[i] = 0.;
  else
    H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
  while (i--)
    if (jbm_small (D[i]))
      H[i] = 0.;
    else
      H[i] = (H[i] - E[i] * H[i + 1] - F[i] * H[i + 2]) / D[i];
}

/**
 * Function to calculate the coefficientes of a polynomial regression adjusted
 * by minimum squares: \f$y=A_0+A_1\,x+A_2\,x^2+\cdots\f$ (JBFLOAT).
 */
static inline void
jbm_regression_polynomial (JBFLOAT *restrict x,
                           ///< array of point x-coordinates.
                           JBFLOAT *restrict y,
                           ///< array of point y-coordinates.
                           int n,       ///< points number.
                           JBFLOAT ** A,
///< pointer to the array of regression coefficients generated by the function
///< calling to g_malloc.
                           int m)       ///< order of the polynomial regression.
{
  JBFLOAT xx[m + m + 1], yx[m + 1], B[(m + 1) * (m + 2)];
  JBFLOAT *k;
  JBFLOAT zx, zy;
  int i, j;
  for (j = m + m; --j > m;)
    xx[j] = 0.;
  for (; j >= 0; --j)
    xx[j] = yx[j] = 0.;
  for (i = n; --i >= 0;)
    {
      for (j = 0, zx = 1., zy = y[i]; j <= m; ++j)
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
  jbm_matrix_solve (B, m + 1);
  *A = (JBFLOAT *) g_malloc ((m + 1) * sizeof (JBFLOAT));
  for (i = 0, k = B; i <= m; ++i, k += m + 1)
    (*A)[i] = *k;
}

/**
 * Function to calculate the coefficientes of a linear regression adjusted by 
 * minimum squares: \f$y=a+b\,x\f$ (JBFLOAT).
 */
static inline void
jbm_regression_linear (JBFLOAT *restrict x,
                       ///< array of point x-coordinates.
                       JBFLOAT *restrict y,
                       ///< array of point y-coordinates.
                       int n,   ///< points number.
                       JBFLOAT * a,
                       ///< pointer to the 0th order regression coefficient.
                       JBFLOAT * b)
                       ///< pointer to the 1st order regression coefficient.
{
  JBFLOAT syx, sy, sxx, sx;
  int i;
  syx = sy = sxx = sx = 0.;
  for (i = 0; i <= n; ++i)
    {
      sy += y[i];
      syx += x[i] * y[i];
      sxx += x[i] * x[i];
      sy += x[i];
    }
  *b = (n * syx - sy * sx) / (n * sxx - sx * sx);
  *a = (sy - *b * sx) / n;
}

/**
 * Function to calculate the coefficientes of an exponential regression adjusted
 * by minimum squares: \f$y=a\,x^b\f$ (JBFLOAT).
 */
static inline void
jbm_regression_exponential (JBFLOAT *restrict x,
///< array of point x-coordinates. It is modified by the function.
                            JBFLOAT *restrict y,
///< array of point y-coordinates. It is modified by the function.
                            int n,      ///< points number.
                            JBFLOAT * a,
///< pointer to the constant parameter regression coefficient.
                            JBFLOAT * b)
///< pointer to the exponent regression coefficient.
{
  int i;
  for (i = n; i-- >= 0;)
    x[i] = LOG (x[i]), y[i] = LOG (y[i]);
  jbm_regression_linear (x, y, n, a, b);
  *a = EXP (*a);
}

/**
 * Function to calculate the coefficientes of a multilinear regression adjusted 
 * by minimum squares: \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$ (JBFLOAT).
 */
static inline void
jbm_regression_multilinear (JBFLOAT **restrict x,
///< array of point coordinates in format:
///< \f$\left(x_1,\cdots,x_n,y_1,\cdots,y_n,\cdots,f_1,\cdots,f_n\right)\f$.
                            int n,      ///< points number.
                            JBFLOAT *restrict a,
                            ///< array of regression coefficients.
                            int m)      ///< number of variables.
{
  JBFLOAT c[(m + 1) * (m + 2)];
  JBFLOAT *d, *xj, *xk;
  int i, j, k;
  ++m;
  for (j = m; --j > 0;)
    {
      for (k = m; --k >= j;)
        {
          d = c + (m + 1) * j + k;
          xj = x[j];
          xk = x[k];
          for (*d = 0., i = n + 1; --i >= 0;)
            *d += *(xj++) ** (xk++);
        }
      d = c + (m + 1) * j + m;
      xj = x[j];
      xk = x[0];
      for (*d = 0., i = n + 1; --i >= 0;)
        *d += *(xj++) ** (xk++);
    }
  for (k = m; --k > 0;)
    {
      d = c + k;
      xk = x[k];
      for (*d = 0., i = n + 1; --i >= 0;)
        *d += *(xk++);
    }
  d = c + m;
  xk = x[0];
  for (*d = 0., i = n + 1; --i >= 0;)
    *d += *(xk++);
  c[0] = n + 1;
  for (j = m; --j > 0;)
    for (k = j; --k >= 0;)
      c[(m + 1) * j + k] = c[(m + 1) * k + j];
  jbm_matrix_solve (c, m);
  for (i = 0, d = c + m; ++i <= m; ++a, d += m + 1)
    *a = *d;
}

/**
 * Function to calculate the coefficientes of a multiexponential regression 
 * adjusted by minimum squares: \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$ (JBFLOAT).
 */
static inline void
jbm_regression_multiexponential (JBFLOAT **restrict x,
///< array of point coordinates in format:
///< \f$\left(x_1,\cdots,x_n,y_1,\cdots,y_n,\cdots,f_1,\cdots,f_n\right)\f$. It
///< is modified by the function.
                                 int n, ///< points number.
                                 JBFLOAT *restrict a,
///< array of regression coefficients.
                                 int m) ///< number of variables.
{
  JBFLOAT *c;
  int i, j;
  for (j = m + 1; --j >= 0;)
    for (i = n + 1, c = x[j]; --i >= 0;)
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
                  int n,        ///< number of points.
                  JBFLOAT **restrict b,
///< pointer to the array of 1st order spline coefficients. It is generated by
///< g_malloc.
                  JBFLOAT **restrict c,
///< pointer to the array of 2nd order spline coefficients.
                  JBFLOAT **restrict d)
///< pointer to the array of 3rd order spline coefficients.
{
  JBFLOAT *B, *C, *D, *E, *F, *H;
  JBFLOAT dx;
  int i, j, m;
  --n;
  m = 3 * n;
  B = (JBFLOAT *) g_malloc (6 * (m - 1) * sizeof (JBFLOAT));
  C = B + m - 2;
  D = C + m - 1;
  E = D + m;
  F = E + m - 1;
  H = F + m - 2;
  dx = x[1] - x[0];
  B[0] = B[1] = D[3] = E[2] = E[3] = F[3] = H[1] = H[2] = H[3] = 0.;
  C[0] = C[1] = C[2] = 1.;
  F[1] = F[2] = -1.;
  D[0] = dx;
  D[1] = D[0] + dx;
  D[2] = D[1] + dx;
  E[0] = D[0] * dx;
  E[1] = 3 * E[0];
  F[0] = E[0] * dx;
  H[0] = y[1] - y[0];
  for (i = n - 1; --i > 0;)
    {
      j = 3 * i + 1;
      dx = x[i + 1] - x[i];
      B[j - 2] = D[j + 2] = F[j] = F[j + 1] = F[j + 2] = H[j + 1] = H[j + 2]
        = 0.;
      B[j - 1] = B[j] = 1.;
      E[j + 1] = E[j + 2] = -1.;
      C[j - 1] = dx;
      C[j] = C[j - 1] + dx;
      C[j + 1] = C[j] + dx;
      D[j] = C[j - 1] * dx;
      D[j + 1] = 3 * D[j];
      E[j] = D[j] * dx;
      H[j] = y[i + 1] - y[i];
    }
  j = 3 * n - 2;
  dx = x[n] - x[n - 1];
  B[j - 2] = B[j - 1] = C[j] = H[j + 1] = 0.;
  D[j + 1] = 1.;
  C[j - 1] = dx;
  D[j] = dx * dx;
  E[j] = D[j] * dx;
  H[j] = y[n] - y[n - 1];
  jbm_matrix_solve_pentadiagonal (B, C, D, E, F, H, m - 1);
  *b = (JBFLOAT *) g_malloc (3 * n * sizeof (JBFLOAT));
  *c = *b + n;
  *d = *c + n;
  for (i = n; --i >= 0;)
    {
      j = 3 * i;
      (*b)[i] = H[j];
      (*c)[i] = H[j + 1];
      (*d)[i] = H[j + 2];
    }
  g_free (B);
}

/**
 * Function to sort transversal regions.
 */
static inline void
jbm_transversal_section_regions_sort (int i,    ///< level index.
                                      int nj,   ///< number of points.
                                      int *restrict nk,
                                      ///< array of region indices.
                                      JBFLOAT *restrict l,
                                      ///< array of longitudinal coordinates.
                                      JBFLOAT *restrict z,
                                      ///< array of vertical coordinates.
                                      JBFLOAT *restrict zz)
                                      ///< array of levels.
{
  JBFLOAT x[nj];
  unsigned int nx[nj], na[nj];
  int j, k;
  JBDOUBLE t;
  t = 0.5 * (zz[i] + zz[i + 1]);
  for (j = nj; --j >= 0;)
    {
      na[j] = k = nk[j];
      x[j] = jbm_extrapolate (t, z[k], z[k + 1], l[k], l[k + 1]);
    }
  jbm_index_sort (x, nx, nj - 1);
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
                                 int n,
///< the highest cross section point number.
                                 JBFLOAT **restrict zz,
///< pointer to the array of JBFLOAT numbers, generated by g_malloc, of the 
///< cross section z-coordinates sorted from the lowest to the highest.
                                 int **restrict ni,
///< pointer to the array of indexes, generated by g_malloc and sorted by
///< z-coordinates, of the cross section points.
                                 int **restrict nj,
///< pointer to the array, generated by g_malloc, of the highest element number 
///< on every j-th region.
                                 int **restrict nij,
///< pointer to the sorted segments, from the lowest to the highest, on every
///< j-region.
                                 int *restrict nmin)
///< index of the lowest riverside point.
{
  int *nk;
  int nmax;
  int i = 0, j, k;
  nmax = i = jbm_index_sort_extended (z, zz, ni, n);
  if (!i)
    goto exit1;
  *nj = (int *) g_try_malloc (n * (i + 1) * sizeof (int));
  if (!*nj)
    {
      g_free (*zz);
      g_free (*ni);
      i = 0;
      goto exit1;
    }
  *nij = *nj + n;
  while (--i >= 0)
    (*nj)[i] = 0;
  for (i = 0; i < n; ++i)
    {
      if ((*ni)[i + 1] > (*ni)[i])
        j = (*ni)[i + 1], k = (*ni)[i];
      else
        j = (*ni)[i], k = (*ni)[i + 1];
      while (--j >= k)
        (*nij)[n * j + (*nj)[j]++] = i;
    }
  *nmin = jbm_min ((*ni)[0], (*ni)[n]);
  for (i = 0, nk = *nij; i < nmax; ++i, nk += n)
    jbm_transversal_section_regions_sort (i, (*nj)[i], nk, l, z, *zz);
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
                   JBFLOAT * max,       ///< pointer to the highest value.
                   JBFLOAT * min)       ///< pointer to the lowest value.
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
  JBFLOAT k = 0., k2;
  int i, j;
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
                              int size, ///< struct size.
                              int n)    ///< the latest struct array element.
{
  JBFLOAT *CC, *DD, *EE, *HH;
  JBDOUBLE k;
  int i;
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
                                   int size,    ///< struct size.
                                   int n)
                                   ///< the latest struct array element.
{
  JBFLOAT *CC, *DD, *EE, *HH;
  JBDOUBLE k;
  int i;
  DD = (JBFLOAT *) D;
  HH = (JBFLOAT *) H;
  for (i = 0; ++i <= n; C = (char *) C + size, E = (char *) E + size)
    {
      CC = (JBFLOAT *) C;
      EE = (JBFLOAT *) E;
      if (jbm_small (*DD))
        D = (char *) D + size, H = (char *) H + size;
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
    *HH = 0.;
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
        *HH = 0.;
      else
        *HH = (*HH - k) / *DD;
    }
}

/**
 * Function to calculate the mean square error between 2 functions tabulated in
 * 2 columns data of a file (JBFLOAT).
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
  JBFLOAT aa[na], ar[nr];
  FILE *filea, *filer;
  JBFLOAT k, xa, fa, xr1, fr1, xr2, fr2;
  int i, j, endr;
  endr = i = 0;
  k = 0.;
  filea = fopen (namea, "r");
  if (!filea)
    goto exit_mse;
  filer = fopen (namer, "r");
  if (!filer)
    goto exit_mse;
  for (j = 0; j < nr; ++j)
    if (fscanf (filer, FRF, ar + j) != 1)
      goto exit_mse;
  xr1 = ar[ixr - 1];
  fr1 = ar[ifr - 1];
  for (j = 0; j < nr; ++j)
    if (fscanf (filer, FRF, ar + j) != 1)
      endr = 1;
  xr2 = ar[ixr - 1];
  fr2 = ar[ifr - 1];
  for (i = 0; !endr; ++i)
    {
      for (j = 0; j < na; ++j)
        if (fscanf (filea, FRF, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      while (xa > xr2)
        {
          xr1 = xr2;
          fr1 = fr2;
          for (j = 0; j < nr; ++j)
            if (fscanf (filer, FRF, ar + j) != 1)
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
        if (fscanf (filea, FRF, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      k += jbm_fsqr (fa - fr1);
    }
exit_mse:
  if (i == 0)
    return 0.;
  return k / i;
}

/**
 * Function to calculate the root mean square error between 2 functions
 * tabulated in 2 columns data of a file (JBFLOAT).
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
 * Function to check small JBDOUBLE numbers.
 *
 * \return 1 on small number, 0 otherwise.
 */
static inline int
jbm_smalll (JBDOUBLE x)         ///< JBDOUBLE number.
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
jbm_fmodminl (JBDOUBLE a,       ///< 1st JBDOUBLE number.
              JBDOUBLE b)       ///< 2nd JBDOUBLE number.
{
  return JBM_FMODMINL (a, b);
}

/**
 * Function to interchange 2 JBDOUBLE numbers.
 */
static inline void
jbm_fchangel (JBDOUBLE *restrict a,  ///< 1st JBDOUBLE number pointer.
              JBDOUBLE *restrict b)  ///< 2nd JBDOUBLE number pointer.
{
  JBDOUBLE c;
  JB_CHANGE (*a, *b, c);
}

/**
 * Function to calculate the square of a JBDOUBLE number.
 *
 * \return JBDOUBLE square.
 */
static inline JBDOUBLE
jbm_fsqrl (JBDOUBLE x)          ///< JBDOUBLE number.
{
  return JBM_SQR (x);
}

/**
 * Function to calculate the double of a JBDOUBLE number.
 *
 * \return JBDOUBLE double.
 */
static inline JBDOUBLE
jbm_fdbll (JBDOUBLE x)          ///< JBDOUBLE number.
{
  return JBM_DBL (x);
}

/**
 * Function to perform an extrapolation between 2 2D points (JBDOUBLE).
 *
 * \return y-coordinate of the extrapolated point.
 */
static inline JBDOUBLE
jbm_extrapolatel (JBDOUBLE x,   ///< x-coordinate of the extrapolated point.
                  JBDOUBLE x1,  ///< x-coordinate of the 1st point.
                  JBDOUBLE x2,  ///< x-coordinate of the 2nd point.
                  JBDOUBLE y1,  ///< y-coordinate of the 1st point.
                  JBDOUBLE y2)  ///< y-coordinate of the 2nd point.
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
jbm_interpolatel (JBDOUBLE x,   ///< x-coordinate of the interpolated point.
                  JBDOUBLE x1,  ///< x-coordinate of the 1st point.
                  JBDOUBLE x2,  ///< x-coordinate of the 2nd point.
                  JBDOUBLE y1,  ///< y-coordinate of the 1st point.
                  JBDOUBLE y2)  ///< y-coordinate of the 2nd point.
{
  JBDOUBLE k;
  if (x <= x1)
    k = y1;
  else if (x >= x2)
    k = y2;
  else
    k = jbm_extrapolatel (x, x1, x2, y1, y2);
  return k;
}

/**
 * Function to calculate the length of a 2D segment (JBDOUBLE).
 *
 * \return segment length.
 */
static inline JBDOUBLE
jbm_v2_lengthl (JBDOUBLE x1,
///< x-coordinate of the 1st point defining the segment.
                JBDOUBLE y1,
///< y-coordinate of the 1st point defining the segment.
                JBDOUBLE x2,
///< x-coordinate of the 2nd point defining the segment.
                JBDOUBLE y2)
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
jbm_v3_lengthl (JBDOUBLE x1,
///< x-coordinate of the 1st point defining the segment.
                JBDOUBLE y1,
///< y-coordinate of the 1st point defining the segment.
                JBDOUBLE z1,
///< z-coordinate of the 1st point defining the segment.
                JBDOUBLE x2,
///< x-coordinate of the 2nd point defining the segment.
                JBDOUBLE y2,
///< y-coordinate of the 2nd point defining the segment.
                JBDOUBLE z2)
///< z-coordinate of the 2nd point defining the segment.
{
  return HYPOTL (HYPOTL (x2 - x1, y2 - y1), z2 - z1);
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
                              JBDOUBLE x1,
                              ///< left limit of the solution interval.
                              JBDOUBLE x2)
                              ///< right limit of the solution interval.
{
  JBDOUBLE k;
  a /= 2.L;
  b = SQRTL (a * a - b);
  k = b - a;
  if (k < x1 || k > x2)
    k = -b - a;
  return k;
}

/**
 * Function to calculate the solution of a quadratic equation in an interval
 * \f$\left[x_1,x_2\right]\f$ in the form \f$a\,x^2+a\,x+b=0\f$
 * (JBDOUBLE).
 *
 * \return solution value.
 */
static inline JBDOUBLE
jbm_solve_quadraticl (JBDOUBLE a,
                      ///< 2nd order coefficient of the equation.
                      JBDOUBLE b,
                      ///< 1st order coefficient of the equation.
                      JBDOUBLE c,
                      ///< 0th order coefficient of the equation.
                      JBDOUBLE x1,
                      ///< left limit of the solution interval.
                      JBDOUBLE x2)
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
                          JBDOUBLE b,
                          ///< 1st order coefficient of the equation.
                          JBDOUBLE c,
                          ///< 0th order coefficient of the equation.
                          JBDOUBLE x1,
                          ///< left limit of the solution interval.
                          JBDOUBLE x2)
                          ///< right limit of the solution interval.
{
  JBDOUBLE k0, k1, k2;
  a /= 3.L;
  k0 = a * a;
  k1 = b / 3.L - k0;
  k0 = (b * a - c) / 2.L - a * k0;
  k2 = k1 * k1 * k1 + k0 * k0;
  if (k2 < 0.L)
    {
      k1 = SQRTL (-k1);
      k0 = ACOSL (k0 / (k1 * k1 * k1)) / 3.L;
      k1 *= 2.L;
      k2 = k1 * COSL (k0) - a;
      if (k2 < x1 || k2 > x2)
        {
          k2 = k1 * COSL (k0 + 2.L * M_PIl / 3.L) - a;
          if (k2 < x1 || k2 > x2)
            k2 = k1 * COSL (k0 - 2.L * M_PIl / 3.L) - a;
        }
    }
  else
    {
      k1 = SQRTL (k2);
      k2 = k0 + k1;
      k2 = CBRTL (k2);
      k0 -= k1;
      k2 += CBRTL (k0);
      k2 -= a;
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
jbm_solve_cubicl (JBDOUBLE a,
                  ///< 3rd order coefficient of the equation.
                  JBDOUBLE b,
                  ///< 2nd order coefficient of the equation.
                  JBDOUBLE c,
                  ///< 1st order coefficient of the equation.
                  JBDOUBLE d,
                  ///< 0th order coefficient of the equation.
                  JBDOUBLE x1,
                  ///< left limit of the solution interval.
                  JBDOUBLE x2)
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
jbm_flux_limiter_totall (JBDOUBLE d1 __attribute__((unused)),
                         ///< 1st flux limiter function parameter.
                         JBDOUBLE d2 __attribute__((unused)))
///< 2nd flux limiter function parameter.
{
  return 0.L;
}

/**
 * Function to calculate the null (2nd order upwind) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=1\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_nulll (JBDOUBLE d1 __attribute__((unused)),
                        ///< 1st flux limiter function parameter.
                        JBDOUBLE d2 __attribute__((unused)))
  ///< 2nd flux limiter function parameter.
{
  return 1.L;
}

/**
 * Function to calculate the centred (2nd order centred) flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_centredl (JBDOUBLE d1,
                           ///< 1st flux limiter function parameter.
                           JBDOUBLE d2)
                           ///< 2nd flux limiter function parameter.
{
  if (jbm_smalll (d2))
    return 0.L;
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
jbm_flux_limiter_superbeel (JBDOUBLE d1,
                            ///< 1st flux limiter function parameter.
                            JBDOUBLE d2)
                            ///< 2nd flux limiter function parameter.
{
  JBDOUBLE r;
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  r = d1 / d2;
  return FMAXL (FMINL (r + r, 1.L), FMINL (r, 2.L));
}

/**
 * Function to calculate the minmod flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_minmodl (JBDOUBLE d1,
                          ///< 1st flux limiter function parameter.
                          JBDOUBLE d2)
                          ///< 2nd flux limiter function parameter.
{
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  return FMINL (d1 / d2, 1.L);
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
jbm_flux_limiter_VanLeerl (JBDOUBLE d1,
                           ///< 1st flux limiter function parameter.
                           JBDOUBLE d2)
                           ///< 2nd flux limiter function parameter.
{
  JBDOUBLE r, k;
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  r = d1 / d2;
  k = FABSL (r);
  return (r + k) / (1.L + k);
}

/**
 * Function to calculate the van Albada flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 * {1+\frac{d_1^2}{d_2^2}}\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_VanAlbadal (JBDOUBLE d1,
                             ///< 1st flux limiter function parameter.
                             JBDOUBLE d2)
                             ///< 2nd flux limiter function parameter.
{
  JBDOUBLE r, k;
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  r = d1 / d2;
  k = r * r;
  return (r + k) / (1.L + k);
}

/**
 * Function to calculate the minsuper flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_minsuperl (JBDOUBLE d1,
                            ///< 1st flux limiter function parameter.
                            JBDOUBLE d2)
                            ///< 2nd flux limiter function parameter.
{
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  return FMINL (d1 / d2, 2.L);
}

/**
 * Function to calculate the supermin flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_superminl (JBDOUBLE d1,
                            ///< 1st flux limiter function parameter.
                            JBDOUBLE d2)
                            ///< 2nd flux limiter function parameter.
{
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  return FMINL (jbm_fdbll (d1 / d2), 1.L);
}

/**
 * Function to calculate the monotonized central flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 * \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 * \right]\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_monotonized_centrall (JBDOUBLE d1,
                                       ///< 1st flux limiter function parameter.
                                       JBDOUBLE d2)
                                       ///< 2nd flux limiter function parameter.
{
  JBDOUBLE k;
  if (d1 * d2 <= JBM_EPSILONL)
    return 0.L;
  k = d1 / d2;
  if (k >= 3.L)
    return 2.L;
  if (k <= 1.L / 3.L)
    return k + k;
  return 0.5L * (k + 1.L);
}

/**
 * Function to calculate the mean flux limiter:
 * \f$\psi\left(d_1,\,d_2\right)=
 * \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$ (JBDOUBLE).
 *
 * \return flux limiter function value.
 */
static inline JBDOUBLE
jbm_flux_limiter_meanl (JBDOUBLE d1,
                        ///< 1st flux limiter function parameter.
                        JBDOUBLE d2)
                        ///< 2nd flux limiter function parameter.
{
  if (jbm_smalll (d2))
    return 0.L;
  return 0.5L * (d1 / d2 + 1.L);
}

/**
 * Function to select a flux limiter function (JBDOUBLE).
 *
 * \return pointer to the flux limiter function.
 */
static inline JBDOUBLE
  (*jbm_flux_limiter_selectl (int type)) (JBDOUBLE, JBDOUBLE)
///< type of flux limiter function.
{
  switch (type)
    {
    case JBM_FLUX_LIMITER_TYPE_TOTAL:
      return jbm_flux_limiter_totall;
    case JBM_FLUX_LIMITER_TYPE_NULL:
      return jbm_flux_limiter_nulll;
    case JBM_FLUX_LIMITER_TYPE_CENTRED:
      return jbm_flux_limiter_centredl;
    case JBM_FLUX_LIMITER_TYPE_MINMOD:
      return jbm_flux_limiter_minmodl;
    case JBM_FLUX_LIMITER_TYPE_SUPERBEE:
      return jbm_flux_limiter_superbeel;
    case JBM_FLUX_LIMITER_TYPE_VAN_LEER:
      return jbm_flux_limiter_VanLeerl;
    case JBM_FLUX_LIMITER_TYPE_VAN_ALBADA:
      return jbm_flux_limiter_VanAlbadal;
    case JBM_FLUX_LIMITER_TYPE_MINSUPER:
      return jbm_flux_limiter_minsuperl;
    case JBM_FLUX_LIMITER_TYPE_SUPERMIN:
      return jbm_flux_limiter_superminl;
    case JBM_FLUX_LIMITER_TYPE_MONOTONIZED_CENTRAL:
      return jbm_flux_limiter_monotonized_centrall;
    case JBM_FLUX_LIMITER_TYPE_MEAN:
      return jbm_flux_limiter_meanl;
    }
  return NULL;
}

/**
 * Function to approximate an integral of a function with the Gauss method
 * defined in an interval (JBDOUBLE).
 *
 * \return integral value.
 */
static inline JBDOUBLE
jbm_integrall (JBDOUBLE (*f) (JBDOUBLE),
///< pointer to the function to integrate.
               JBDOUBLE x1,     ///< left limit of the interval.
               JBDOUBLE x2)     ///< right limit of the interval.
{
#if JBM_INTEGRAL_GAUSS_N == 1
  const JBDOUBLE a[1] = { 2.L }, b[1];
#elif JBM_INTEGRAL_GAUSS_N == 2
  const JBDOUBLE a[2] = { 8. / 9.L, 5. / 9.L }, b[2] = {
    0., 0.7745966692414833770358531L
  };
#elif JBM_INTEGRAL_GAUSS_N == 3
  const JBDOUBLE a[3] = {
    0.5688888888888888888888889L,
    0.4786286704993664680412915L,
    0.2369268850561890875142640L
  }, b[3] = {
    0.L, 0.5384693101056830910363144L, 0.9061798459386639927976269L
  };
#elif JBM_INTEGRAL_GAUSS_N == 4
  const JBDOUBLE a[4] = {
    0.4179591836734693877551020L,
    0.3818300505051189449503698L,
    0.2797053914892766679014678L,
    0.1294849661688696932706114L
  }, b[4] = {
    0.L, 0.4058451513773971669066064L,
    0.7415311855993944398638648L, 0.9491079123427585245261897L
  };
#endif
  JBDOUBLE k, k2, x, dx;
  int i;
  dx = 0.5L * (x2 - x1);
  x = 0.5L * (x1 + x2);
  k = a[0] * dx * f (x);
  for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
    {
      k2 = b[i] * dx;
      k += a[i] * dx * (f (x - k2) + f (x + k2));
    }
  return k;
}

/**
 * Function to search the interval where a number is in a increasingly sorted
 * array of JBDOUBLE numbers.
 *
 * \return interval number.
 */
static inline int
jbm_darray_search (JBDOUBLE x,  ///< number to search.
                   JBDOUBLE * fa,       ///< array of JBDOUBLE numbers.
                   int n)       ///< number of the highest array element.
{
  int i, j;
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
                            JBDOUBLE * fa,      ///< array of JBDOUBLE numbers.
                            int n)
                            ///< number of the highest array element.
{
  int i;
  if (x < fa[0])
    i = -1;
  else if (x >= fa[n])
    i = n;
  else
    i = jbm_darray_search (x, fa, n);
  return i;
}

/**
 * Function to find the highest element of an array of JBDOUBLE numbers.
 *
 * \return the highest value.
 */
static inline JBDOUBLE
jbm_darray_max (JBDOUBLE * fa,  ///< array of JBDOUBLE numbers.
                int n)          ///< number of the ending array element.
{
  JBDOUBLE k;
  int i;
  k = fa[0];
  for (i = 0; ++i <= n;)
    k = FMAXL (k, fa[i]);
  return k;
}

/**
 * Function to find the lowest element of an array of JBDOUBLE numbers.
 *
 * \return the lowest value.
 */
static inline JBDOUBLE
jbm_darray_min (JBDOUBLE * fa,  ///< array of JBDOUBLE numbers.
                int n)          ///< number of the ending array element.
{
  JBDOUBLE k;
  int i;
  k = fa[0];
  for (i = 0; ++i <= n;)
    k = FMINL (k, fa[i]);
  return k;
}

/**
 * Function to find the highest and the lowest elements of an array of JBDOUBLE
 * numbers.
 */
static inline void
jbm_darray_maxmin (JBDOUBLE * fa,       ///< array of JBDOUBLE numbers.
                   int n,       ///< number of the ending array element.
                   JBDOUBLE * max,      ///< the highest value.
                   JBDOUBLE * min)      ///< the lowest value.
{
  JBDOUBLE kmax, kmin;
  int i;
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
                   int n)       ///< the highest element number of the arrays.
{
  JBDOUBLE *fc;
  int n1;
  n1 = n + 1;
  fc = (JBDOUBLE *) malloc (n1 * sizeof (JBDOUBLE));
  memcpy (fc, fa, n1);
  memcpy (fa, fb, n1);
  memcpy (fb, fc, n1);
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
                        JBDOUBLE *restrict fx,
///< increasingly sorted array of x-coordinates of the tabular function.
                        JBDOUBLE *restrict fy,
///< array of y-coordinates of the tabular function.
                        int n)  ///< the highest element number of the arrays.
{
  JBDOUBLE k;
  int i;
  i = jbm_darray_search (x, fx, n);
  if (i == n)
    k = fy[i];
  else
    k = jbm_interpolatel (x, fx[i], fx[i + 1], fy[i], fy[i + 1]);
  return k;
}

/**
 * Function to calculate the y-coordinate of a 2D point interpolated between a
 * tabular function defined by 2 arrays of JBDOUBLE (x coordinates) and
 * JBFLOAT (y coordinates) numbers.
 *
 * \return y-coordinate of the interpolated point.
 */
static inline JBFLOAT
jbm_darray_farray_interpolate (JBDOUBLE x,      ///< x-coordinate of the point.
                               JBDOUBLE *restrict fx,
///< increasingly sorted array of x-coordinates of the tabular function.
                               JBFLOAT *restrict fy,
///< array of y-coordinates of the tabular function.
                               int n)
///< the highest element number of the arrays.
{
  JBFLOAT k;
  int i;
  i = jbm_darray_search (x, fx, n);
  if (i == n)
    k = fy[i];
  else
    k = jbm_interpolate (x, fx[i], fx[i + 1], fy[i], fy[i + 1]);
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
                  int na,
                  ///< the highest element number of the 1st array.
                  JBDOUBLE *restrict fb,
                  ///< 2nd increasingly sorted array of JBDOUBLE numbers.
                  int nb,
                  ///< the highest element number of the 2nd array.
                  JBDOUBLE ** fc,
///< pointer to the resulting increasingly sorted array of JBDOUBLE numbers.
                  int *nc)
///< pointer to the highest element number of the resulting array.
{
  JBDOUBLE *restrict x;
  int i, j, k;
  x = (JBDOUBLE *) g_try_malloc ((na + nb + 2) * sizeof (JBDOUBLE));
  if (!x)
    return 0;
  for (i = j = k = 0; i <= na || j <= nb; ++k)
    {
      if (fa[i] > fb[j])
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
                     int n,     ///< the highest element number of the arrays.
                     JBDOUBLE x1,
                     ///< left limit of the integration interval.
                     JBDOUBLE x2)
                     ///< right limit of the integration interval.
{
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
  else if (i == n)
    {
      I = y[i] * (x2 - x1);
      goto exit1;
    }
  else
    {
      I = 0.L;
      xx = x + i;
      yy = y + i;
      y1 = jbm_extrapolatel (x1, xx[0], xx[1], yy[0], yy[1]);
    }
  if (x2 < xx[1])
    {
      I += 0.5L * (y1 + jbm_extrapolatel (x2, xx[0], xx[1], yy[0], yy[1]))
        * (x2 - x1);
      goto exit1;
    }
  I += 0.5L * (y1 + yy[1]) * (xx[1] - x1);
  if (++i == n)
    {
      I += yy[1] * (x2 - xx[1]);
      goto exit1;
    }
  while (++i < n && x2 > xx[2])
    {
      ++xx, ++yy;
      I += 0.5L * (yy[0] + yy[1]) * (xx[1] - xx[0]);
    }
  if (i == n)
    I += yy[2] * (x2 - xx[1]);
  else if (x2 < xx[2])
    I += 0.5L * (yy[1] + jbm_extrapolatel (x2, xx[1], xx[2], yy[1], yy[2]))
      * (x2 - xx[1]);
exit1:
  return I;
}

/**
 * Function to integrate a tabular function (JBDOUBLE in, x JBFLOAT in y) in an
 * interval.
 *
 * \return integral value.
 */
static inline JBFLOAT
jbm_darray_farray_integral (JBDOUBLE *restrict x,
///< incresingly sorted array of JBDOUBLE numbers defining the x-coordinates of 
///< the tabular function.
                            JBFLOAT *restrict y,
///< array of JBFLOAT numbers defining the y-coordinates of the tabular
///< function.
                            int n,
                            ///< the highest element number of the arrays.
                            JBDOUBLE x1,
                            ///< left limit of the integration interval.
                            JBDOUBLE x2)
                            ///< right limit of the integration interval.
{
  JBDOUBLE *xx;
  JBFLOAT *yy;
  JBFLOAT I, y1;
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
  else if (i == n)
    {
      I = y[i] * (x2 - x1);
      goto exit1;
    }
  else
    {
      I = 0.;
      xx = x + i;
      yy = y + i;
      y1 = jbm_extrapolate (x1, xx[0], xx[1], yy[0], yy[1]);
    }
  if (x2 < xx[1])
    {
      I += 0.5 * (y1 + jbm_extrapolate (x2, xx[0], xx[1], yy[0], yy[1]))
        * (x2 - x1);
      goto exit1;
    }
  I += 0.5 * (y1 + yy[1]) * (xx[1] - x1);
  if (++i == n)
    {
      I += yy[1] * (x2 - xx[1]);
      goto exit1;
    }
  while (++i < n && x2 > xx[2])
    {
      ++xx, ++yy;
      I += 0.5 * (yy[0] + yy[1]) * (xx[1] - xx[0]);
    }
  if (i == n)
    I += yy[2] * (x2 - xx[1]);
  else if (x2 < xx[2])
    I += 0.5 * (yy[1] + jbm_extrapolate (x2, xx[1], xx[2], yy[1], yy[2]))
      * (x2 - xx[1]);
exit1:
  return I;
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
  JBDOUBLE k = 0.L;
  int i, j;
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
                           unsigned int *restrict ni, ///< array of indexes.
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
jbm_index_sort_mergel (JBDOUBLE *restrict x, ///< array of JBDOUBLE numbers.
                       unsigned int *restrict ni,     ///< array of indexes.
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
jbm_index_sortl (JBDOUBLE *restrict x,       ///< array of JBDOUBLE numbers.
                 unsigned int *restrict ni,   ///< array of indexes.
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
///< numbers. It has to be freed with g_free.
                          int **restrict ni,
///< point to the array of sorted indexes. It has to be freed with g_free.
                          int n)
///< the highest element number of the array to sort.
{
  unsigned int nk[n + 1], nj[n + 1];
  JBDOUBLE k1, k2;
  int i, j = 0;
  *ni = (int *) g_try_malloc ((n + 1) * sizeof (int));
  *xr = (JBDOUBLE *) g_try_malloc ((n + 1) * sizeof (JBDOUBLE));
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
jbm_matrix_solvel (JBDOUBLE * x,
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
          jbm_darray_change (g + j, f + j, i + 1);
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
                               JBDOUBLE *restrict H, ///< final column array.
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
    H[i] = 0.L;
  else
    H[i] /= D[i];
  while (i--)
    if (jbm_smalll (D[i]))
      H[i] = 0.L;
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
    H[i + 1] = 0.L;
  else
    H[i + 1] /= D[i + 1];
  if (jbm_smalll (D[i]))
    H[i] = 0.L;
  else
    H[i] = (H[i] - E[i] * H[i + 1]) / D[i];
  while (i--)
    if (jbm_smalll (D[i]))
      H[i] = 0.L;
    else
      H[i] = (H[i] - E[i] * H[i + 1] - F[i] * H[i + 2]) / D[i];
}

/**
 * Function to calculate the coefficientes of a polynomial regression adjusted
 * by minimum squares: \f$y=A_0+A_1\,x+A_2\,x^2+\cdots\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_polynomiall (JBDOUBLE *restrict x,
                            ///< array of point x-coordinates.
                            JBDOUBLE *restrict y,
                            ///< array of point y-coordinates.
                            int n,      ///< points number.
                            JBDOUBLE ** A,
///< pointer to the array of regression coefficients generated by the function
///< calling to g_malloc.
                            int m)      ///< order of the polynomial regression.
{
  JBDOUBLE xx[m + m + 1], yx[m + 1], B[(m + 1) * (m + 2)];
  JBDOUBLE *k;
  JBDOUBLE zx, zy;
  int i, j;
  *A = (JBDOUBLE *) g_malloc ((m + 1) * sizeof (JBDOUBLE));
  for (j = m + m; --j > m;)
    xx[j] = 0.L;
  for (; j >= 0; --j)
    xx[j] = yx[j] = 0.L;
  for (i = n; --i >= 0;)
    {
      for (j = 0, zx = 1.L, zy = y[i]; j <= m; ++j)
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
 * Function to calculate the coefficientes of a linear regression adjusted by 
 * minimum squares: \f$y=a+b\,x\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_linearl (JBDOUBLE *restrict x,
                        ///< array of point x-coordinates.
                        JBDOUBLE *restrict y,
                        ///< array of point y-coordinates.
                        int n,  ///< points number.
                        JBDOUBLE * a,
                        ///< pointer to the 0th order regression coefficient.
                        JBDOUBLE * b)
                        ///< pointer to the 1st order regression coefficient.
{
  JBDOUBLE syx, sy, sxx, sx;
  int i;
  syx = sy = sxx = sx = 0.L;
  for (i = 0; i <= n; ++i)
    {
      sy += y[i];
      syx += x[i] * y[i];
      sxx += x[i] * x[i];
      sy += x[i];
    }
  *b = (n * syx - sy * sx) / (n * sxx - sx * sx);
  *a = (sy - *b * sx) / n;
}

/**
 * Function to calculate the coefficientes of an exponential regression adjusted
 * by minimum squares: \f$y=a\,x^b\f$ (JBDOUBLE).
 */
static inline void
jbm_regression_exponentiall (JBDOUBLE *restrict x,
///< array of point x-coordinates. It is modified by the function.
                             JBDOUBLE *restrict y,
///< array of point y-coordinates. It is modified by the function.
                             int n,     ///< points number.
                             JBDOUBLE * a,
///< pointer to the constant parameter regression coefficient.
                             JBDOUBLE * b)
///< pointer to the exponent regression coefficient.
{
  int i;
  for (i = n; i-- >= 0;)
    x[i] = LOGL (x[i]), y[i] = LOGL (y[i]);
  jbm_regression_linearl (x, y, n, a, b);
  *a = EXPL (*a);
}

/**
 * Function to calculate the coefficientes of a multilinear regression adjusted 
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
          for (*d = 0., i = n + 1; --i >= 0;)
            *d += *(xj++) ** (xk++);
        }
      d = c + (m + 1) * j + m;
      xj = x[j];
      xk = x[0];
      for (*d = 0., i = n + 1; --i >= 0;)
        *d += *(xj++) ** (xk++);
    }
  for (k = m; --k > 0;)
    {
      d = c + k;
      xk = x[k];
      for (*d = 0., i = n + 1; --i >= 0;)
        *d += *(xk++);
    }
  d = c + m;
  xk = x[0];
  for (*d = 0., i = n + 1; --i >= 0;)
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
 * Function to calculate the coefficientes of a multiexponential regression 
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
                   JBDOUBLE * y,
                   ///< array of point y-coordinates.
                   int n,       ///< number of points.
                   JBDOUBLE **restrict b,
///< pointer to the array of 1st order spline coefficients. It is generated by
///< g_malloc.
                   JBDOUBLE **restrict c,
///< pointer to the array of 2nd order spline coefficients.
                   JBDOUBLE **restrict d)
///< pointer to the array of 3rd order spline coefficients.
{
  JBDOUBLE *B, *C, *D, *E, *F, *H;
  JBDOUBLE dx;
  int i, j, m;
  --n;
  m = 3 * n;
  B = (JBDOUBLE *) g_malloc (6 * (m - 1) * sizeof (JBDOUBLE));
  C = B + m - 2;
  D = C + m - 1;
  E = D + m;
  F = E + m - 1;
  H = F + m - 2;
  dx = x[1] - x[0];
  B[0] = B[1] = D[3] = E[2] = E[3] = F[3] = H[1] = H[2] = H[3] = 0.L;
  C[0] = C[1] = C[2] = 1.L;
  F[1] = F[2] = -1.L;
  D[0] = dx;
  D[1] = D[0] + dx;
  D[2] = D[1] + dx;
  E[0] = D[0] * dx;
  E[1] = 3 * E[0];
  F[0] = E[0] * dx;
  H[0] = y[1] - y[0];
  for (i = n - 1; --i > 0;)
    {
      j = 3 * i + 1;
      dx = x[i + 1] - x[i];
      B[j - 2] = D[j + 2] = F[j] = F[j + 1] = F[j + 2] = H[j + 1] = H[j + 2]
        = 0.L;
      B[j - 1] = B[j] = 1.L;
      E[j + 1] = E[j + 2] = -1.L;
      C[j - 1] = dx;
      C[j] = C[j - 1] + dx;
      C[j + 1] = C[j] + dx;
      D[j] = C[j - 1] * dx;
      D[j + 1] = 3 * D[j];
      E[j] = D[j] * dx;
      H[j] = y[i + 1] - y[i];
    }
  j = 3 * n - 2;
  dx = x[n] - x[n - 1];
  B[j - 2] = B[j - 1] = C[j] = H[j + 1] = 0.L;
  D[j + 1] = 1.L;
  C[j - 1] = dx;
  D[j] = dx * dx;
  E[j] = D[j] * dx;
  H[j] = y[n] - y[n - 1];
  jbm_matrix_solve_pentadiagonall (B, C, D, E, F, H, m - 1);
  *b = (JBDOUBLE *) g_malloc (3 * n * sizeof (JBDOUBLE));
  *c = *b + n;
  *d = *c + n;
  for (i = n; --i >= 0;)
    {
      j = 3 * i;
      (*b)[i] = H[j];
      (*c)[i] = H[j + 1];
      (*d)[i] = H[j + 2];
    }
  g_free (B);
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
                    JBDOUBLE * max,     ///< pointer to the highest value.
                    JBDOUBLE * min)     ///< pointer to the lowest value.
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
  JBDOUBLE k = 0., k2;
  int i, j;
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
    *HH = 0.L;
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
        *HH = 0.L;
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
  JBDOUBLE aa[na], ar[nr];
  FILE *filea, *filer;
  JBDOUBLE k, xa, fa, xr1, fr1, xr2, fr2;
  int i, j, endr;
  endr = i = 0;
  k = 0.L;
  filea = fopen (namea, "r");
  if (!filea)
    goto exit_mse;
  filer = fopen (namer, "r");
  if (!filer)
    goto exit_mse;
  for (j = 0; j < nr; ++j)
    if (fscanf (filer, FRL, ar + j) != 1)
      goto exit_mse;
  xr1 = ar[ixr - 1];
  fr1 = ar[ifr - 1];
  for (j = 0; j < nr; ++j)
    if (fscanf (filer, FRL, ar + j) != 1)
      endr = 1;
  xr2 = ar[ixr - 1];
  fr2 = ar[ifr - 1];
  for (i = 0; !endr; ++i)
    {
      for (j = 0; j < na; ++j)
        if (fscanf (filea, FRL, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      while (xa > xr2)
        {
          xr1 = xr2;
          fr1 = fr2;
          for (j = 0; j < nr; ++j)
            if (fscanf (filer, FRL, ar + j) != 1)
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
        if (fscanf (filea, FRL, aa + j) != 1)
          goto exit_mse;
      xa = aa[ixa - 1];
      fa = aa[ifa - 1];
      k += jbm_fsqrl (fa - fr1);
    }
exit_mse:
  if (i == 0)
    return 0.L;
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
