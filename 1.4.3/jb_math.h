/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2014, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 	1. Redistributions of source code must retain the above copyright notice,
 * 		this list of conditions and the following disclaimer.
 *
 * 	2. Redistributions in binary form must reproduce the above copyright notice,
 * 		this list of conditions and the following disclaimer in the
 * 		documentation and/or other materials provided with the distribution.
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
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#ifndef JB_MATH__H
#define JB_MATH__H 1

#include "jb_def.h"
#include <sys/param.h>

/**
 * \def JBM_G
 * \brief Gravity constant
 */
#define JBM_G 9.81
/**
 * \def JBM_INDEX_SORT_FLASH_MIN
 * \brief Minimum number of elements to select the jbm_index_sort_flash_min()
 *   function as default sort method.
 */
#define JBM_INDEX_SORT_FLASH_MIN 32
/**
 * \def JBM_INDEX_SORT_MERGE_MIN
 * \brief Minimum number of elements to select the jbm_index_sort_merge_min()
 *   function as default sort method.
 */
#define JBM_INDEX_SORT_MERGE_MIN 32
/**
 * \def JBM_MAX
 * \brief Macro calculating the maximum number.
 */
#define JBM_MAX(a, b) (((a) > (b))? (a): (b))
/**
 * \def JBM_MIN
 * \brief Macro calculating the minimum number.
 */
#define JBM_MIN(a, b) (((a) < (b))? (a): (b))
/**
 * \def JBM_MODMIN
 * \brief Macro calculating the number with the lower module in the [a, b]
 *   interval (int arguments).
 *   \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 */
#define JBM_MODMIN(a, b) (((a) * (b) <= 0)? 0: (abs(a) < abs(b))? (a): (b))
/**
 * \def JBM_MODMINL
 * \brief Macro calculating the number with the lower module in the [a, b]
 *   interval (long int arguments).
 *   \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 */
#define JBM_MODMINL(a, b) (((a) * (b) <= 0l)? 0l: (labs(a) < labs(b))? (a): (b))
/**
 * \def JBM_MODMINLL
 * \brief Macro calculating the number with the lower module in the [a, b]
 *   interval (long long int arguments).
 *   \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 */
#define JBM_MODMINLL(a, b) (((a) * (b) <= 0L)? 0L: \
	(llabs(a) < llabs(b))? (a): (b))
/**
 * \def JBM_FMODMIN
 * \brief Macro calculating the number with the lower module in the [a, b]
 *   interval (JBDOUBLE arguments).
 *   \f$\mathrm{modmin}(a,b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 */
#if JB_PRECISION < 4
	#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.)? 0.: \
		(fabs(a) < fabs(b))? (a): (b))
#else
	#define JBM_FMODMIN(a, b) (((a) * (b) <= 0.L)? 0.L: \
		(fabsl(a) < fabsl(b))? (a): (b))
#endif
/**
 * \def JBM_SQR
 * \brief Macro calculating the square of a number.
 */
#define JBM_SQR(x) ((x) * (x))
/**
 * \def JBM_DBL
 * \brief Macro calculating the double of a number.
 */
#define JBM_DBL(x) ((x) + (x))
/**
 * \def JBM_EXTRAPOLATE
 * \brief Macro calculating a linear extrapolation.
 */
#define JBM_EXTRAPOLATE(x, x1, x2, y1, y2) \
	((y1) + (x - (x1)) * ((y2) - (y1)) / ((x2) - (x1)))

// Needed in no GNU systems
#if defined(BSD) || defined(sun) || defined(G_OS_WIN32)
	#define exp10(x) (exp(x * M_LN10))
#endif

static inline int _jbm_fcompare(JBDOUBLE a, JBDOUBLE b)
{
#ifdef G_OS_WIN32
	register JBDOUBLE k = a / b;
	if (k < 0.999999) return -1;
	if (k > 1.000001) return 1;
	return 0;
#else
	return a != b;
#endif
}
#if INLINE_JBM_FCOMPARE
	#define jbm_fcompare _jbm_fcompare
#else
	int jbm_fcompare(JBDOUBLE a, JBDOUBLE b);
#endif

static inline int _jbm_max(int a, int b)
{
	#if DEBUG_JBM_MAX
		fprintf(stderr, "JBM max(%d,%d)=%d\n", a, b, JBM_MAX(a, b));
	#endif
	return JBM_MAX(a, b);
}
#if INLINE_JBM_MAX
	#define jbm_max _jbm_max
#else
	int jbm_max(int a, int b);
#endif

static inline int _jbm_min(int a, int b)
{
	#if DEBUG_JBM_MIN
		fprintf(stderr, "JBM min(%d,%d)=%d\n", a, b, JBM_MIN(a, b));
	#endif
	return JBM_MIN(a, b);
}
#if INLINE_JBM_MIN
	#define jbm_min _jbm_min
#else
	int jbm_min(int a, int b);
#endif

static inline long int _jbm_maxl(long int a, long int b)
{
	#if DEBUG_JBM_MAXL
		fprintf(stderr, "JBM maxl(%ld,%ld)=%ld\n", a, b, JBM_MAX(a, b));
	#endif
	return JBM_MAX(a, b);
}
#if INLINE_JBM_MAXL
	#define jbm_maxl _jbm_maxl
#else
	long int jbm_maxl(long int a, long int b);
#endif

static inline long int _jbm_minl(long int a, long int b)
{
	#if DEBUG_JBM_MINL
		fprintf(stderr, "JBM minl(%ld,%ld)=%ld\n", a, b, JBM_MIN(a, b));
	#endif
	return JBM_MIN(a, b);
}
#if INLINE_JBM_MINL
	#define jbm_minl _jbm_minl
#else
	long int jbm_minl(long int a, long int b);
#endif

static inline long long int _jbm_maxll(long long int a, long long int b)
{
	#if DEBUG_JBM_MAXLL
		fprintf(stderr, "JBM maxll(%Ld,%Ld)=%Ld\n", a, b, JBM_MAX(a, b));
	#endif
	return JBM_MAX(a, b);
}
#if INLINE_JBM_MAXLL
	#define jbm_maxll _jbm_maxll
#else
	long long int jbm_maxll(long long int a, long long int b);
#endif

static inline long long int _jbm_minll(long long int a, long long int b)
{
	#if DEBUG_JBM_MINLL
		fprintf(stderr, "JBM minll(%Ld,%Ld)=%Ld\n", a, b, JBM_MIN(a, b));
	#endif
	return JBM_MIN(a, b);
}
#if INLINE_JBM_MINLL
	#define jbm_minll _jbm_minll
#else
	long long int jbm_minll(long long int a, long long int b);
#endif

static inline int _jbm_modmin(int a, int b)
{
	#if DEBUG_JBM_MODMIN
		fprintf(stderr, "JBM modmin(%d,%d)=%d\n", a, b, JBM_MODMIN(a, b));
	#endif
	return JBM_MODMIN(a, b);
}
#if INLINE_JBM_MODMIN
	#define jbm_modmin _jbm_modmin
#else
	int jbm_modmin(int a, int b);
#endif

static inline long int _jbm_modminl(long int a, long int b)
{
	#if DEBUG_JBM_MODMINL
		fprintf(stderr, "JBM modminl(%ld,%ld)=%ld\n", a, b, JBM_MODMINL(a, b));
	#endif
	return JBM_MODMINL(a, b);
}
#if INLINE_JBM_MODMINL
	#define jbm_modminl _jbm_modminl
#else
	long int jbm_modminl(long int a, long int b);
#endif

static inline long long int _jbm_modminll(long long int a, long long int b)
{
	#if DEBUG_JBM_MODMINLL
		fprintf(stderr, "JBM modminll(%Ld,%Ld)=%Ld\n",
			a, b, JBM_MODMINLL(a, b));
	#endif
	return JBM_MODMINLL(a, b);
}
#if INLINE_JBM_MODMINLL
	#define jbm_modminll _jbm_modminll
#else
	long long int jbm_modminll(long long int a, long long int b);
#endif

static inline JBDOUBLE _jbm_fmodmin(JBDOUBLE a, JBDOUBLE b)
{
	#if DEBUG_JBM_FMODMIN
		fprintf(stderr, "JBM fmodmin("FWL","FWL")="FWL"\n",
			a, b, JBM_FMODMIN(a, b));
	#endif
	return JBM_FMODMIN(a, b);
}
#if INLINE_JBM_FMODMIN
	#define jbm_fmodmin _jbm_fmodmin
#else
	JBDOUBLE jbm_fmodmin(JBDOUBLE a, JBDOUBLE b);
#endif

static inline void _jbm_change(int *a, int *b)
{
	register int c;
	#if DEBUG_JBM_CHANGE
		fprintf(stderr, "JBM change a=%d b=%d\n", *a, *b);
	#endif
	JB_CHANGE(*a, *b, c);
	#if DEBUG_JBM_CHANGE
		fprintf(stderr, "JBM change a=%d b=%d\n", *a, *b);
	#endif
}
#if INLINE_JBM_CHANGE
	#define jbm_change _jbm_change
#else
	void jbm_change(int *a, int *b);
#endif

static inline void _jbm_changel(long int *a, long int *b)
{
	register long int c;
	#if DEBUG_JBM_CHANGEL
		fprintf(stderr, "JBM changel a=%ld b=%ld\n", *a, *b);
	#endif
	JB_CHANGE(*a, *b, c);
	#if DEBUG_JBM_CHANGEL
		fprintf(stderr, "JBM changel a=%ld b=%ld\n", *a, *b);
	#endif
}
#if INLINE_JBM_CHANGEL
	#define jbm_changel _jbm_changel
#else
	void jbm_changel(long int *a, long int *b);
#endif

static inline void _jbm_changell(long long int *a, long long int *b)
{
	register long long int c;
	#if DEBUG_JBM_CHANGELL
		fprintf(stderr, "JBM changell a=%Ld b=%Ld\n", *a, *b);
	#endif
	JB_CHANGE(*a, *b, c);
	#if DEBUG_JBM_CHANGELL
		fprintf(stderr, "JBM changell a=%Ld b=%Ld\n", *a, *b);
	#endif
}
#if INLINE_JBM_CHANGELL
	#define jbm_changell _jbm_changell
#else
	void jbm_changell(long long int *a, long long int *b);
#endif

static inline void _jbm_fchange(JBFLOAT *a, JBFLOAT *b)
{
	register JBDOUBLE c;
	#if DEBUG_JBM_FCHANGE
		fprintf(stderr, "JBM fchange a="FWF"b="FWF"\n", *a, *b);
	#endif
	JB_CHANGE(*a, *b, c);
	#if DEBUG_JBM_FCHANGE
		fprintf(stderr, "JBM fchange a="FWF"b="FWF"\n", *a, *b);
	#endif
}
#if INLINE_JBM_FCHANGE
	#define jbm_fchange _jbm_fchange
#else
	void jbm_fchange(JBFLOAT *a, JBFLOAT *b);
#endif

static inline void _jbm_fchangel(JBDOUBLE *a, JBDOUBLE *b)
{
	register JBDOUBLE c;
	#if DEBUG_JBM_FCHANGEL
		fprintf(stderr, "JBM fchangel a="FWL"b="FWL"\n", *a, *b);
	#endif
	JB_CHANGE(*a, *b, c);
	#if DEBUG_JBM_FCHANGEL
		fprintf(stderr, "JBM fchangel a="FWL"b="FWL"\n", *a, *b);
	#endif
}
#if INLINE_JBM_FCHANGEL
	#define jbm_fchangel _jbm_fchangel
#else
	void jbm_fchangel(JBDOUBLE *a, JBDOUBLE *b);
#endif

static inline int _jbm_sqr(int x)
{
	#if DEBUG_JBM_SQR
		fprintf(stderr, "JBM sqr x=%d x^2=%d\n", x, JBM_SQR(x));
	#endif
	return JBM_SQR(x);
}
#if INLINE_JBM_SQR
	#define jbm_sqr _jbm_sqr
#else
	int jbm_sqr(int x);
#endif

static inline long int _jbm_sqrl(long int x)
{
	#if DEBUG_JBM_SQRL
		fprintf(stderr, "JBM sqrl x=%ld x^2=%ld\n", x, JBM_SQR(x));
	#endif
	return JBM_SQR(x);
}
#if INLINE_JBM_SQRL
	#define jbm_sqrl _jbm_sqrl
#else
	long int jbm_sqrl(long int x);
#endif

static inline long long int _jbm_sqrll(long long int x)
{
	#if DEBUG_JBM_SQRLL
		fprintf(stderr, "JBM sqrll x=%Ld x^2=%Ld\n", x, JBM_SQR(x));
	#endif
	return JBM_SQR(x);
}
#if INLINE_JBM_SQRLL
	#define jbm_sqrll _jbm_sqrll
#else
	long long int jbm_sqrll(long long int x);
#endif

static inline JBDOUBLE _jbm_fsqr(JBDOUBLE x)
{
	#if DEBUG_JBM_FSQR
		fprintf(stderr, "JBM fsqr x="FWL" x^2="FWL"\n", x, JBM_SQR(x));
	#endif
	return JBM_SQR(x);
}
#if INLINE_JBM_FSQR
	#define jbm_fsqr _jbm_fsqr
#else
	JBDOUBLE jbm_fsqr(JBDOUBLE x);
#endif

static inline int _jbm_dbl(int x)
{
	#if DEBUG_JBM_DBL
		fprintf(stderr, "JBM dbl x=%d 2x=%d\n", x, JBM_DBL(x));
	#endif
	return JBM_DBL(x);
}
#if INLINE_JBM_DBL
	#define jbm_dbl _jbm_dbl
#else
	int jbm_dbl(int x);
#endif

static inline long int _jbm_dbll(long int x)
{
	#if DEBUG_JBM_DBLL
		fprintf(stderr, "JBM dbll x=%ld 2x=%ld\n", x, JBM_DBL(x));
	#endif
	return JBM_DBL(x);
}
#if INLINE_JBM_DBLL
	#define jbm_dbll _jbm_dbll
#else
	long int jbm_dbll(long int x);
#endif

static inline long long int _jbm_dblll(long long int x)
{
	#if DEBUG_JBM_dblll
		fprintf(stderr, "JBM dblll x=%Ld 2x=%Ld\n", x, JBM_DBL(x));
	#endif
	return JBM_DBL(x);
}
#if INLINE_JBM_dblll
	#define jbm_dblll _jbm_dblll
#else
	long long int jbm_dblll(long long int x);
#endif

static inline JBDOUBLE _jbm_fdbl(JBDOUBLE x)
{
	#if DEBUG_JBM_FDBL
		fprintf(stderr, "JBM fdbl x="FWL" 2x="FWL"\n", x, JBM_DBL(x));
	#endif
	return JBM_DBL(x);
}
#if INLINE_JBM_FDBL
	#define jbm_fdbl _jbm_fdbl
#else
	JBDOUBLE jbm_fdbl(JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_extrapolate
	(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, JBDOUBLE y1, JBDOUBLE y2)
{
	#if DEBUG_JBM_EXTRAPOLATE
		fprintf(stderr, "JBM extrapolate x="FWL" x1="FWL" x2="FWL"\n",
			x, x1, x2);
		fprintf(stderr, "JBM y1="FWL" y2="FWL"\n", y1, y2);
		fprintf(stderr, "JBM extrapolation="FWL"\n",
			JBM_EXTRAPOLATE(x, x1, x2, y1, y2));
	#endif
	return JBM_EXTRAPOLATE(x, x1, x2, y1, y2);
}
#if INLINE_JBM_EXTRAPOLATE
	#define jbm_extrapolate _jbm_extrapolate
#else
	JBDOUBLE jbm_extrapolate
		(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, JBDOUBLE y1, JBDOUBLE y2);
#endif

static inline JBDOUBLE _jbm_interpolate
	(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, JBDOUBLE y1, JBDOUBLE y2)
{
	register JBDOUBLE k;
	#if DEBUG_JBM_INTERPOLATE
		fprintf(stderr, "JBM interpolate x="FWL" x1="FWL" x2="FWL"\n",
			x, x1, x2);
		fprintf(stderr, "JBM y1="FWL" y2="FWL"\n", y1, y2);
	#endif
	if (x <= x1) k = y1;
	else if (x >= x2) k = y2;
	else k = jbm_extrapolate(x, x1, x2, y1, y2);
	#if DEBUG_JBM_INTERPOLATE
		fprintf(stderr, "JBM interpolation="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_INTERPOLATE
	#define jbm_interpolate _jbm_interpolate
#else
	JBDOUBLE jbm_interpolate
		(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, JBDOUBLE y1, JBDOUBLE y2);
#endif

static inline JBDOUBLE _jbm_integral
	(JBDOUBLE (*f)(JBDOUBLE), JBDOUBLE x1, JBDOUBLE x2)
{
	register int i;
	register JBDOUBLE k, k2, x, dx;

	// Calculate the integral of a function with the Gauss method

#if JBM_INTEGRAL_GAUSS_N == 1
	JBDOUBLE a[1] = {2.L}, b[1];
#elif JBM_INTEGRAL_GAUSS_N == 2
	JBDOUBLE a[2] ={8./9.L, 5./9.L}, b[2]={0., 0.7745966692414833770358531L};
#elif JBM_INTEGRAL_GAUSS_N == 3
	JBDOUBLE a[3]=
	{
		0.5688888888888888888888889L,
		0.4786286704993664680412915L,
		0.2369268850561890875142640L
	},
	b[3]=
	{
		0.L,
		0.5384693101056830910363144L,
		0.9061798459386639927976269L
	};
#elif JBM_INTEGRAL_GAUSS_N == 4
	JBDOUBLE a[4]=
	{
		0.4179591836734693877551020L,
		0.3818300505051189449503698L,
		0.2797053914892766679014678L,
		0.1294849661688696932706114L
	},
	b[4]=
	{
		0.L,
		0.4058451513773971669066064L,
		0.7415311855993944398638648L,
		0.9491079123427585245261897L
	};
#endif
	dx = 0.5L * (x2 - x1);
	x = 0.5L * (x1 + x2);
	k = a[0] * dx * f(x);
	for (i = JBM_INTEGRAL_GAUSS_N; --i > 0;)
	{
		k2 = b[i] * dx;
		k += a[i] * dx * (f(x - k2) + f(x + k2));
	}
	return k;
}
#if INLINE_JBM_INTEGRAL
	#define jbm_integral _jbm_integral
#else
	JBDOUBLE jbm_integral
		(JBDOUBLE (*f)(JBDOUBLE), JBDOUBLE x1, JBDOUBLE x2);
#endif

static inline int _jbm_farray_search(JBDOUBLE x, JBFLOAT *fa, int n)
{
	register int i, j;
	#if DEBUG_JBM_FARRAY_SEARCH
		fprintf(stderr, "JBM float array search\n");
	#endif
	for (i = 0; n - i > 1;)
	{
		j = (i + n) >> 1;
		if (x <= fa[j]) n = j; else i = j;
	}
	#if DEBUG_JBM_FARRAY_SEARCH
		fprintf(stderr, "JBM float array search i=%d\n", i);
	#endif
	return i;
}
#if INLINE_JBM_FARRAY_SEARCH
	#define jbm_farray_search _jbm_farray_search
#else
	int jbm_farray_search(JBDOUBLE, JBFLOAT*, int);
#endif

static inline int _jbm_farray_search_extended(JBDOUBLE x, JBFLOAT *fa, int n)
{
	register int i;
	#if DEBUG_JBM_FARRAY_SEARCH_EXTENDED
		fprintf(stderr, "JBM float array search_extended\n");
	#endif
	if (x < fa[0]) i = -1;
	else if (x >= fa[n]) i = n;
	else i = jbm_farray_search(x, fa, n);
	#if DEBUG_JBM_FARRAY_SEARCH_EXTENDED
		fprintf(stderr, "JBM float array search_extended i=%d\n", i);
	#endif
	return i;
}
#if INLINE_JBM_FARRAY_SEARCH_EXTENDED
	#define jbm_farray_search_extended _jbm_farray_search_extended
#else
	int jbm_farray_search_extended(JBDOUBLE, JBFLOAT*, int);
#endif

static inline JBDOUBLE _jbm_farray_max(JBFLOAT *fa, int n)
{
	register int i;
	register JBDOUBLE k;
	#if DEBUG_JBM_FARRAY_MAX
		fprintf(stderr, "JBM float array max\n");
	#endif
	k = *fa;
	for (i = 0; ++i <= n;) k = fmaxl(k, *(++fa));
	#if DEBUG_JBM_FARRAY_MAX
		fprintf(stderr, "JBM float array max="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_FARRAY_MAX
	#define jbm_farray_max _jbm_farray_max
#else
	JBDOUBLE jbm_farray_max(JBFLOAT*, int);
#endif

static inline JBDOUBLE _jbm_farray_min(JBFLOAT *fa, int n)
{
	register int i;
	register JBDOUBLE k;
	#if DEBUG_JBM_FARRAY_MIN
		fprintf(stderr, "JBM float array min\n");
	#endif
	k = *fa;
	for (i = 0; ++i <= n;) k = fminl(k, *(++fa));
	#if DEBUG_JBM_FARRAY_MIN
		fprintf(stderr, "JBM float array min="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_FARRAY_MIN
	#define jbm_farray_min _jbm_farray_min
#else
	JBDOUBLE jbm_farray_min(JBFLOAT*, int);
#endif

static inline void _jbm_farray_maxmin
	(JBFLOAT *fa, int n, JBDOUBLE *max, JBDOUBLE *min)
{
	register int i;
	register JBDOUBLE kmax, kmin;
	#if DEBUG_JBM_FARRAY_MAXMIN
		fprintf(stderr, "JBM float array maxmin\n");
	#endif
	kmax = kmin = *fa;
	for (i = 0; ++i <= n;)
	{
		++fa;
		if (kmax < *fa) kmax = *fa; else if (kmin > *fa) kmin = *fa;
	}
	*max = kmax, *min = kmin;
	#if DEBUG_JBM_FARRAY_MAXMIN
		fprintf(stderr, "JBM float array max="FWL" min="FWL"\n", kmax, kmin);
	#endif
}
#if INLINE_JBM_FARRAY_MAXMIN
	#define jbm_farray_maxmin _jbm_farray_maxmin
#else
	void jbm_farray_maxmin(JBFLOAT*, int, JBDOUBLE*, JBDOUBLE*);
#endif

static inline JBDOUBLE _jbm_farray_interpolate
	(JBDOUBLE x, JBFLOAT *fa, JBFLOAT *fb, int n)
{
	register int i;
	register JBDOUBLE k;
	#if DEBUG_JBM_FARRAY_INTERPOLATE
		fprintf(stderr, "JBM float array interpolate\n");
	#endif
	i = jbm_farray_search(x, fa, n);
	if (i == n) k = fb[i];
	else k = jbm_interpolate(x, fa[i], fa[i + 1], fb[i], fb[i + 1]);
	#if DEBUG_JBM_FARRAY_INTERPOLATE
		fprintf(stderr, "JBM float array interpolate k="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_FARRAY_INTERPOLATE
	#define jbm_farray_interpolate _jbm_farray_interpolate
#else
	JBDOUBLE jbm_farray_interpolate(JBDOUBLE, JBFLOAT*, JBFLOAT*, int);
#endif

static inline JBFLOAT* _jbm_farray_add
	(JBFLOAT *fa, int na, JBFLOAT *fb, int nb, JBFLOAT **fc, int *nc)
{
	register int i, j, k;
	register JBFLOAT *x;
	#if DEBUG_JBM_FARRAY_ADD
		fprintf(stderr, "JBM float array add: start\n");
	#endif
	*fc = x = (JBFLOAT*)g_try_malloc((na + nb + 2) * sizeof(JBFLOAT));
	if (!x) return 0;
	for (i = j = k = 0; i <= na || j <= nb;)
	{
		if (*fa > *fb)
		{
			++j;
			*x = *(fb++);
		}
		else if (*fa < *fb)
		{
			++i;
			*x = *(fa++);
		}
		else
		{
			++i;
			++j;
			++fa;
			*x = *(fb++);
		}
		++k;
		++x;
	}
	*fc = (JBFLOAT*)jb_try_realloc(*fc, k * sizeof(JBFLOAT));
	*nc = --k;
	#if DEBUG_JBM_FARRAY_ADD
		fprintf(stderr, "JBM float array add: end\n");
	#endif
	return *fc;
}
#if INLINE_JBM_FARRAY_ADD
	#define jbm_farray_add _jbm_farray_add
#else
	JBFLOAT* jbm_farray_add(JBFLOAT*, int, JBFLOAT*, int, JBFLOAT**, int*);
#endif

static inline JBDOUBLE _jbm_farray_integral
	(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE x1, JBDOUBLE x2)
{
	register int i;
	register JBFLOAT *yy, *xx;
	register JBDOUBLE I, y1;

	#if DEBUG_JBM_FARRAY_INTEGRAL
		fprintf(stderr, "JBM float array integral: start\n");
	#endif
	if (n == 0)
	{
		I = y[0] * (x2 - x1);
		goto exit1;
	}
	i = jbm_farray_search_extended(x1, x, n);
	if (i < 0)
	{
		i = 0;
		I = y[0] * (x2 - x1);
		x1 = x[0];
		y1 = y[0];
		xx = x;
		yy = y;
		#if DEBUG_JBM_FARRAY_INTEGRAL
			fprintf(stderr, "JBMFI a I="FWL"\n", I);
		#endif
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
		y1 = jbm_extrapolate(x1, xx[0], xx[1], yy[0], yy[1]);
		#if DEBUG_JBM_FARRAY_INTEGRAL
			fprintf(stderr, "JBMFI b I="FWL"\n", I);
		#endif
	}
	if (x2 < xx[1])
	{
		I += 0.5 * (y1 + jbm_extrapolate(x2, xx[0], xx[1], yy[0], yy[1]))
			* (x2 - x1);
		#if DEBUG_JBM_FARRAY_INTEGRAL
			fprintf(stderr, "JBMFI c I="FWL"\n", I);
		#endif
		goto exit1;
	}
	I += 0.5 * (y1 + yy[1]) * (xx[1] - x1);
	#if DEBUG_JBM_FARRAY_INTEGRAL
		fprintf(stderr, "JBMFI d I="FWL"\n", I);
	#endif
	if (++i == n)
	{
		I += yy[1] * (x2 - xx[1]);
		#if DEBUG_JBM_FARRAY_INTEGRAL
			fprintf(stderr, "JBMFI e I="FWL"\n", I);
		#endif
		goto exit1;
	}
	while (++i < n && x2 > xx[2])
	{
		++xx, ++yy;
		I += 0.5 * (yy[0] + yy[1]) * (xx[1] - xx[0]);
		#if DEBUG_JBM_FARRAY_INTEGRAL
			fprintf(stderr, "JBMFI i=%d I="FWL"\n", i, I);
		#endif
	}
	if (i == n) I += yy[2] * (x2 - xx[1]);
	else if (x2 < xx[2]) I += 0.5 * (yy[1]
		+ jbm_extrapolate(x2, xx[1], xx[2], yy[1], yy[2])) * (x2 - xx[1]);
exit1:
	#if DEBUG_JBM_FARRAY_INTEGRAL
		fprintf(stderr, "JBMFI I="FWL"\n", I);
		fprintf(stderr, "JBM float array integral: end\n");
	#endif
	return I;
}
#if INLINE_JBM_FARRAY_INTEGRAL
	#define jbm_farray_integral _jbm_farray_integral
#else
	JBDOUBLE jbm_farray_integral(JBFLOAT*, JBFLOAT*, int, JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_farray_mean_square_error
	(JBFLOAT *xa, JBFLOAT *fa, int na, JBFLOAT *xr, JBFLOAT *fr, int nr)
{
	register int i, j;
	JBDOUBLE k = 0.;
	#if DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM float array mean square error\n");
	#endif
	for (i = 0; i <= na && xa[i] < xr[0]; ++i) k += jbm_fsqr(fa[i] - fr[0]);
	#if DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBMFMSE i=%d k="FWL"\n", i, k);
	#endif
	for (j = 0; i <= na; ++i)
	{
		while (j < nr && xa[i] > xr[j+1]) ++j;
		#if DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMFMSE j=%d\n", j);
		#endif
		if (j == nr) for (; i<=na; ++i) k += jbm_fsqr(fa[i] - fr[nr]);
		else k += jbm_fsqr
			(fa[i] - jbm_extrapolate(xa[i], xr[j], xr[j+1], fr[j], fr[j+1]));
		#if DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMFMSE i=%d j=%d k="FWL"\n", i, j, k);
		#endif
	}
	k /= na + 1;
	#if DEBUG_JBM_FARRAY_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM float array mean square error="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_FARRAY_MEAN_SQUARE_ERROR
	#define jbm_farray_mean_square_error _jbm_farray_mean_square_error
#else
	JBDOUBLE jbm_farray_mean_square_error
		(JBFLOAT*, JBFLOAT*, int, JBFLOAT*, JBFLOAT*, int);
#endif

static inline JBDOUBLE _jbm_farray_root_mean_square_error
	(JBFLOAT *xa, JBFLOAT *fa, int na, JBFLOAT *xr, JBFLOAT *fr, int nr)
{
	JBDOUBLE k = 0.;
	#if DEBUG_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM float array root_mean square error\n");
	#endif
	k = sqrt(jbm_farray_mean_square_error(xa, fa, na, xr, fr, nr));
	#if DEBUG_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM float array root_mean square error="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR
	#define jbm_farray_root_mean_square_error _jbm_farray_root_mean_square_error
#else
	JBDOUBLE jbm_farray_root_mean_square_error
		(JBFLOAT*, JBFLOAT*, int, JBFLOAT*, JBFLOAT*, int);
#endif

static inline JBDOUBLE _jbm_v2_length
	(JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE x2, JBDOUBLE y2)
{
	return sqrtl(jbm_fsqr(x2 - x1) + jbm_fsqr(y2 - y1));
}
#if INLINE_JBM_V2_LENGTH
	#define jbm_v2_length _jbm_v2_length
#else
	JBDOUBLE jbm_v2_length(JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_v3_length(JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE z1,
	JBDOUBLE x2, JBDOUBLE y2, JBDOUBLE z2)
{
	return sqrtl(jbm_fsqr(x2 - x1) + jbm_fsqr(y2 - y1) + jbm_fsqr(z2 - z1));
}
#if INLINE_JBM_V3_LENGTH
	#define jbm_v3_length _jbm_v3_length
#else
	JBDOUBLE jbm_v3_length
		(JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_solve_cuadratic_reduced
	(JBDOUBLE a, JBDOUBLE b, JBDOUBLE x1, JBDOUBLE x2)
{
	register JBDOUBLE k;
	#if DEBUG_JBM_SOLVE_CUADRATIC_REDUCED
		fprintf(stderr,
			"JBM Solve cuadratic reduced\na="FWL" b="FWL" x1="FWL" x2="FWL"\n",
			a, b, x1, x2);
	#endif
	a /= 2.L;
	b = sqrtl(a * a - b);
	k = b - a;
	if (k < x1 || k > x2) k = -b - a;
	#if DEBUG_JBM_SOLVE_CUADRATIC_REDUCED
		fprintf(stderr, "JBM Solve cuadratic reduced solution="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_SOLVE_CUADRATIC_REDUCED
	#define jbm_solve_cuadratic_reduced _jbm_solve_cuadratic_reduced
#else
	JBDOUBLE jbm_solve_cuadratic_reduced
		(JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_solve_cuadratic
	(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, JBDOUBLE x1, JBDOUBLE x2)
{
	register JBDOUBLE k;
	#if DEBUG_JBM_SOLVE_CUADRATIC
		fprintf(stderr,
			"JBM solve cuadratic\na="FWL" b="FWL" c="FWL"\nx1="FWL" x2="FWL"\n",
			a, b, c, x1, x2);
	#endif
	if (a == 0.L) k = -c / b;
	else k = jbm_solve_cuadratic_reduced(b / a, c / a, x1, x2);
	#if DEBUG_JBM_SOLVE_CUADRATIC
		fprintf(stderr, "JBM solve cuadratic solution="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_SOLVE_CUADRATIC
	#define jbm_solve_cuadratic _jbm_solve_cuadratic
#else
	JBDOUBLE jbm_solve_cuadratic(JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_solve_cubic_reduced
	(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, JBDOUBLE x1, JBDOUBLE x2)
{
	JBDOUBLE k0, k1, k2;
	#if DEBUG_JBM_SOLVE_CUBIC_REDUCED
		fprintf(stderr,
		"JBM solve cubic reduced\na="FWL" b="FWL" c="FWL"\nx1="FWL" x2="FWL"\n",
			a, b, c, x1, x2);
	#endif
	a /= 3.L;
	k0 = a * a;
	k1 = b / 3.L - k0;
	k0 = (b * a - c) / 2.L -a * k0;
	k2 = k1 * k1 * k1 + k0 * k0;
	if (k2 < 0.L)
	{
		k1 = sqrtl(-k1);
		k0 = acosl(k0 / (k1 * k1 * k1)) / 3.L;
		k1 *= 2.L;
		k2 = k1 * cosl(k0) - a;
		if (k2 < x1 || k2 > x2)
		{
			k2 = k1 * cosl(k0 + 2.L * M_PIl / 3.L) - a;
			if (k2 < x1 || k2 > x2) k2 = k1 * cosl(k0 - 2.L * M_PIl / 3.L) - a;
		}
	}
	else
	{
		k1 = sqrtl(k2);
		k2 = k0 + k1;
		if (k2 < 0.L) k2 = -powl(-k2, 1.L/3.L); else k2 = powl(k2, 1.L/3.L);
		k0 -= k1;
		if (k0 < 0.L) k2 -= powl(-k0, 1.L/3.L); else k2 += powl(k0, 1.L/3.L);
		k2 -= a;
	}
	#if DEBUG_JBM_SOLVE_CUBIC_REDUCED
		fprintf(stderr, "JBM solve cubic reduced solution="FWL"\n", k2);
	#endif
	return k2;
}
#if INLINE_JBM_SOLVE_CUBIC_REDUCED
	#define jbm_solve_cubic_reduced _jbm_solve_cubic_reduced
#else
	JBDOUBLE jbm_solve_cubic_reduced(JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_solve_cubic(JBDOUBLE a, JBDOUBLE b,
	JBDOUBLE c, JBDOUBLE d, JBDOUBLE x1, JBDOUBLE x2)
{
	register JBDOUBLE k;
	#if DEBUG_JBM_SOLVE_CUBIC
		fprintf(stderr,
		"JBM solve cubic\na="FWL" b="FWL" c="FWL" d="FWL"\nx1="FWL" x2="FWL"\n",
			a, b, c, d, x1, x2);
	#endif
	if (a == 0.) k = jbm_solve_cuadratic(b, c, d, x1, x2);
	else k = jbm_solve_cubic_reduced(b / a, c / a, d / a, x1, x2);
	#if DEBUG_JBM_SOLVE_CUBIC
		fprintf(stderr, "JBM solve cubic solution="FWL"\n", k);
	#endif
	return k;
}
#if INLINE_JBM_SOLVE_CUBIC
	#define jbm_solve_cubic _jbm_solve_cubic
#else
	JBDOUBLE jbm_solve_cubic
		(JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE);
#endif

static inline void _jbm_index_sort_insertion(JBFLOAT *x, int *ni, int n)
{
	register int i, j, ii;
	register JBDOUBLE xi;
	#if DEBUG_JBM_INDEX_SORT_INSERTION
		fprintf(stderr, "JBM index sort insertion\n");
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isi i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
	#endif
	for (i = 0; ++i <= n;)
	{
		ii = ni[i];
		xi = x[ii];
		for (j = i; --j >= 0 && x[ni[j]] < xi;) ni[j + 1] = ni[j];
		ni[j + 1] = ii;
	}
	#if DEBUG_JBM_INDEX_SORT_INSERTION
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isi i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
		fprintf(stderr, "JBM index sort insertion exit\n");
	#endif
}
#if INLINE_JBM_INDEX_SORT_INSERTION
	#define jbm_index_sort_insertion _jbm_index_sort_insertion
#else
	void jbm_index_sort_insertion(JBFLOAT*, int*, int);
#endif

static inline void _jbm_index_sort_interchange(JBFLOAT *x, int *ni, int n)
{
	register int i, j;
	register JBDOUBLE xi, xj;
	#if DEBUG_JBM_INDEX_SORT_INTERCHANGE
		fprintf(stderr, "JBM index sort interchange\n");
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isi i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
	#endif
	for (i = n + 1; --i > 0;)
	{
		xi = x[ni[i]];
		for (j = i; --j >= 0;)
		{
			xj = x[ni[j]];
			if (xj < xi)
			{
				xi = xj;
				jbm_change(ni + i, ni + j);
			}
		}
	}
	#if DEBUG_JBM_INDEX_SORT_INTERCHANGE
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isi i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
		fprintf(stderr, "JBM index sort interchange exit\n");
	#endif
}
#if INLINE_JBM_INDEX_SORT_INTERCHANGE
	#define jbm_index_sort_interchange _jbm_index_sort_interchange
#else
	void jbm_index_sort_interchange(JBFLOAT*, int*, int);
#endif

static inline void _jbm_index_sort_merge(JBFLOAT *x, int *ni, int n)
{
	int i, j, i1, i2, k, l;
	int *ni1, *ni2, *nj, *nk, *nt, nn[n + 1];
	#if DEBUG_JBM_INDEX_SORT_MERGE
		fprintf(stderr, "JBM index sort merge\n");
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM ism i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
	#endif
	j=JBM_INDEX_SORT_MERGE_MIN;
	for (i = 0; i <= n - j; i += j) jbm_index_sort_insertion(x, ni + i, j - 1);
	if (i < n) jbm_index_sort_insertion(x, ni + i, n - i);
	#if DEBUG_JBM_INDEX_SORT_MERGE
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM ism i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
	#endif
	++n;
	for (nk = ni, nj = nn; j <= n; j *= 2)
	{
		for (ni1 = nk, l = 0, k = n / j; (k -= 2) >= 0; ni1 = ni2 + j)
		{
			ni2 = ni1 + j;
			for (i1 = i2 = 0; i1 < j && i2 < j;)
			{
				if (x[ni1[i1]] > x[ni2[i2]]) nj[l++] = ni1[i1++];
				else nj[l++] = ni2[i2++];
			}
			while (i2 < j) nj[l++] = ni2[i2++];
			while (i1 < j) nj[l++] = ni1[i1++];
		}
		if (k == -1)
		{
			ni2 = ni1 + j;
			for (k = n - l - j, i1 = i2 = 0; i1 < j && i2 < k;)
			{
				if (x[ni1[i1]] > x[ni2[i2]]) nj[l++] = ni1[i1++];
				else nj[l++] = ni2[i2++];
			}
			while (i2 < k) nj[l++] = ni2[i2++];
			while (i1 < j) nj[l++] = ni1[i1++];
		}
		for (; l < n; ++l) nj[l] = nk[l];
		nt = nk;
		nk = nj;
		nj = nt;
	}
	if (ni != nj) memcpy(ni, nj, n * sizeof(int));
	#if DEBUG_JBM_INDEX_SORT_MERGE
		for (i=0; i<=n; ++i)
			fprintf(stderr, "JBM ism i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
		fprintf(stderr, "JBM index sort merge exit\n");
	#endif
}
#if INLINE_JBM_INDEX_SORT_MERGE
	#define jbm_index_sort_merge _jbm_index_sort_merge
#else
	void jbm_index_sort_merge(JBFLOAT*, int*, int);
#endif

#if JBM_INDEX_SORT_FLASH
	void jbm_index_sort_flash(JBFLOAT *x, int *ni, int n);
#endif

static inline void _jbm_index_sort(JBFLOAT *x, int *ni, int n)
{
	register int i;
	#if DEBUG_JBM_INDEX_SORT
		fprintf(stderr, "JBM index sort\n");
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM is i=%d x="FWF"\n", i, x[i]);
	#endif
	for (i = n + 1; --i >= 0;) ni[i] = i;
	if (n < JBM_INDEX_SORT_FLASH_MIN) jbm_index_sort_insertion(x, ni, n);
	else jbm_index_sort_flash(x, ni, n);
	#if DEBUG_JBM_INDEX_SORT
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM is i=%d x="FWF" ni=%d\n", i, x[i], ni[i]);
		fprintf(stderr, "JBM index sort\n");
	#endif
}
#if INLINE_JBM_INDEX_SORT
	#define jbm_index_sort _jbm_index_sort
#else
	void jbm_index_sort(JBFLOAT*, int*, int);
#endif

static inline int _jbm_index_sort_extended
 (JBFLOAT *x, JBFLOAT **xr, int **ni, int n)
{
	register int i, j = 0;
	register JBDOUBLE k1, k2;
	int nk[n + 1], nj[n + 1];
	#if DEBUG_JBM_INDEX_SORT_EXTENDED
		fprintf(stderr, "JBM index sort extended: start\n");
	#endif
	*ni = (int*)g_try_malloc((n + 1) * sizeof(int));
	*xr = (JBFLOAT*)g_try_malloc((n + 1) * sizeof(JBFLOAT));
	if (! *xr)
	{
		jb_free_null((void**)ni);
		fprintf(stderr, "JBM index sort extended: no enough memory\n");
		goto index_exit;
	}
	jbm_index_sort(x, nk, n);
	i = n;
	k2 = x[nk[i]];
	nj[i] = 0;
	(*xr)[0] = k2;
	for (; --i >= 0; k2 = k1)
	{
		k1 = x[nk[i]];
		if (k1 != k2) (*xr)[++j] = k1;
		nj[i] = j;
	}
	#if DEBUG_JBM_INDEX_SORT_EXTENDED
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM ise i=%d nj=%d\n", i, nj[i]);
		for (i = 0; i <= j; ++i)
			fprintf(stderr, "JBM ise i=%d xr="FWF"\n", i, (*xr)[i]);
	#endif
	for (i = n + 1; --i >= 0;) (*ni)[nk[i]] = nj[i];
	#if DEBUG_JBM_INDEX_SORT_EXTENDED
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM ise i=%d ni=%d\n", i, (*ni)[i]);
	#endif
index_exit:
	#if DEBUG_JBM_INDEX_SORT_EXTENDED
		fprintf(stderr, "JBM index sort extended: end\n");
	#endif
	return j;
}
#if INLINE_JBM_INDEX_SORT_EXTENDED
	#define jbm_index_sort_extended _jbm_index_sort_extended
#else
	int jbm_index_sort_extended(JBFLOAT*, JBFLOAT**, int**, int);
#endif

static inline void _jbm_solve_matrix(JBFLOAT *x, int n)
{
	register int i, j, k;
	JBDOUBLE k1, k2;
	JBFLOAT *f, *g;
	++n;
	for (i = n, f = x; --i > 0;)
	{
		jbm_farray_maxmin(f, n, &k1, &k2);
		k1 = fmaxl(fabsl(k1), fabsl(k2));
		for (j = n; --j >= 0; ++f) *f /= k1;
	}
	for (i = n - 1, f = x; --i > 0; f += n + 1)
	{
		k1 = fabsl(*f);
		for (k = j = i, g = f; --j >=0 ;)
		{
			g += n;
			k2 = fabsl(*g);
			if (k2 > k1)
			{
				k1 = k2;
				k = j;
			}
		}
		if (k != i)
		{
			g = f + (i - k) * n;
			for (j = i + 2; --j >= 0;) jbm_fchange(g + j, f + j);
		}
		for (j = i, g = f + n; --j >= 0; g += n)
		{
			k1 = *g / *f;
			for (k = i + 2; --k > 0;) g[k] -= k1 * f[k];
		}
	}
	f = x + n * (n - 1) - 1;
	for (i = 0; ++i < n; f -= n)
	{
		k1 = *f /= *(f-i);
		for (j = n, g = f - n; --j > i; g -= n) *g -= *(g - i) * k1;
	}
}
#if INLINE_JBM_SOLVE_MATRIX
	#define jbm_solve_matrix _jbm_solve_matrix
#else
	void jbm_solve_matrix(JBFLOAT*, int);
#endif

static inline void _jbm_solve_tridiagonal_matrix
	(JBFLOAT *C, JBFLOAT *D, JBFLOAT *E, JBFLOAT *H, int n)
{
	register int i;
	register JBDOUBLE k;
	for (i = 0; ++i <= n;)
	{
		k = *(C++) / *(D++);
		*D -= k * *(E++);
		k *= *(H++);
		*H -= k;
	}
	*H /= *D;
	while (--i > 0)
	{
		--H;
		*H = (*H - *(--E) * *(H + 1)) / *(--D);
	}
}
#if INLINE_JBM_SOLVE_TRIDIAGONAL_MATRIX
	#define jbm_solve_tridiagonal_matrix _jbm_solve_tridiagonal_matrix
#else
	void jbm_solve_tridiagonal_matrix
		(JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbm_solve_tridiagonal_matrix_zero
	(JBFLOAT *C, JBFLOAT *D, JBFLOAT *E, JBFLOAT *H, int n)
{
	register int i;
	register JBDOUBLE k;
	for (i = 0; ++i <= n;)
	{
		if (*D != 0.)
		{
			k = *(C++) / *(D++);
			*D -= k * *(E++);
			k *= *(H++);
			*H -= k;
		}
		else ++C, ++D, ++E, ++H;
	}
	if (*D != 0.) *H /= *D; else *H = 0.;
	while (--i > 0)
	{
		--H, --D, --E;
		if (*D != 0.) *H = (*H - *E * *(H + 1)) / *D; else *H = 0.;
	}
}
#if INLINE_JBM_SOLVE_TRIDIAGONAL_MATRIX_ZERO
	#define jbm_solve_tridiagonal_matrix_zero _jbm_solve_tridiagonal_matrix_zero
#else
	void jbm_solve_tridiagonal_matrix_zero
		(JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbm_solve_pentadiagonal_matrix(JBFLOAT *B, JBFLOAT *C,
	JBFLOAT *D, JBFLOAT *E, JBFLOAT *F, JBFLOAT *H, int n)
{
	register int i;
	register JBDOUBLE k;
	for (i = n - 1; --i > 0; ++B, ++C, ++D, ++E, ++F, ++H)
	{
		k = *C / *D;
		*(D + 1) -= k * *E;
		*(E + 1) -= k * *F;
		*(H + 1) -= k * *H;
		k = *B / *D;
		*(C + 1) -= k * *E;
		*(D + 2) -= k * *F;
		*(H + 2) -= k * *H;
	}
	k = *C / *D;
	*(++D) -= k * *E;
	*(H+1) -= k * *H;
	*(++H) /= *D;
	--H;
	*H = (*H - *(E--) * *(H + 1)) / *(--D);
	for (i = n - 1; --i > 0;)
	{
		--H;
		*H = (*H - *(E--) * *(H + 1) - *(--F) * *(H + 2)) / *(--D);
	}
}
#if INLINE_JBM_SOLVE_PENTADIAGONAL_MATRIX
	#define jbm_solve_pentadiagonal_matrix _jbm_solve_pentadiagonal_matrix
#else
	void jbm_solve_pentadiagonal_matrix
		(JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbm_solve_tridiagonal_varray(void *v, int size, int n)
{

/*
	Resuelve una estructura tridiagonal de forma:
		(v)0 (v+2)0                                 (v+3)0
		(v)0 (v+1)1 v(+2)1                          (v+3)1

		                   (v)n-2 (v+1)n-1 (v+2)n-1 (v+3)n-1
		                            (v)n-1 (v+1)n   (v+3)n
	La solución se almacena en v+3
	Modifica los campos v+1, v+2, v+3
*/

	int i;
	register JBDOUBLE k;
	register JBFLOAT *C, *CC;
	for (i=0; ++i<=n;)
	{
		C=(JBFLOAT*)v;
		v+=size;
		CC=(JBFLOAT*)v;
		k = *C / *(C+1);
		*(CC+1) -= k * *(C+2);
		*(CC+3) -= k * *(C+3);
	}
	*(CC+3) /= *(CC+1);
	while (--i>0)
	{
		C=(JBFLOAT*)v;
		v-=size;
		CC=(JBFLOAT*)v;
		*(CC+3) = (*(CC+3) - *(CC+2) * *(C+3)) / *(CC+1);
	}
}

#if INLINE_JBM_SOLVE_TRIDIAGONAL_VARRAY
	#define jbm_solve_tridiagonal_varray _jbm_solve_tridiagonal_varray
#else
	void jbm_solve_tridiagonal_varray(void*, int, int);
#endif

static inline void _jbm_solve_tridiagonal_varray_zero(void *v, int size, int n)
{

/*
	Resuelve una estructura tridiagonal de forma:
		(v)0 (v+2)0                                 (v+3)0
		(v)0 (v+1)1 v(+2)1                          (v+3)1

		                   (v)n-2 (v+1)n-1 (v+2)n-1 (v+3)n-1
		                            (v)n-1 (v+1)n   (v+3)n
	evitando divisiones por 0. La solución se almacena en v+3
	Modifica los campos v+1, v+2, v+3
*/

	int i;
	register JBDOUBLE k;
	register JBFLOAT *C, *CC;
	for (i=0; ++i<=n;)
	{
		C=(JBFLOAT*)v;
		v+=size;
		CC=(JBFLOAT*)v;
		if (*(C+1) != 0.)
		{
			k = *C / *(C+1);
			*(CC+1) -= k * *(C+2);
			*(CC+3) -= k * *(C+3);
		}
	}
	if (*(CC+1) != 0.) *(CC+3) /= *(CC+1);
	while (--i>0)
	{
		C=(JBFLOAT*)v;
		v-=size;
		CC=(JBFLOAT*)v;
		if (*(CC+1) != 0.) *(CC+3) = (*(CC+3) - *(CC+2) * *(C+3)) / *(CC+1);
		else *(CC+3) = 0.;
	}
}

#if INLINE_JBM_SOLVE_TRIDIAGONAL_VARRAY_ZERO
	#define jbm_solve_tridiagonal_varray_zero _jbm_solve_tridiagonal_varray_zero
#else
	void jbm_solve_tridiagonal_varray_zero(void*, int, int);
#endif

static inline void _jbm_regression
	(JBFLOAT *x,JBFLOAT *y,int n,JBFLOAT **A,int m)
{
	JBFLOAT *B;
	JBDOUBLE xx[m+m+1], yx[m+1];
	register int i,j;
	register JBFLOAT *k;
	register JBDOUBLE zx, zy;
	*A = (JBFLOAT*)g_malloc((m+1) * sizeof(JBFLOAT));
	B=(JBFLOAT*)g_malloc((m+1)*(m+2)*sizeof(JBFLOAT));
	for (j=m; j>=0; --j) xx[j]=yx[j]=0.;
	for (j=m+m; --j>m;) xx[j]=0.;
	for (i=n; --i>=0;)
	{
		for (j=0, zx=1., zy=y[i]; j<=m; ++j)
		{
			yx[j]+=zy;
			xx[j]+=zx;
			zx*=x[i];
			zy*=x[i];
		}
		for (; j<=m+m; ++j)
		{
			xx[j]+=zx;
			zx*=x[i];
		}
	}
	for (i=0, k=B; i<=m; ++i, ++k)
	{
		for (j=0; j<=m; ++j, ++k) *k = xx[j+i];
		*k = yx[i];
	}
	jbm_solve_matrix(B,m+1);
	for (i=0, k=B; i<=m; ++i, k+=m+1)
	{
		(*A)[i] = *k;
		printf("i=%d A="FWF"\n",i,*k);
	}
	g_free(B);
}

#if INLINE_JBM_REGRESSION
	#define jbm_regression _jbm_regression
#else
	void jbm_regression(JBFLOAT*,JBFLOAT*,int,JBFLOAT**,int);
#endif

static inline void _jbm_spline_cubic
	(JBFLOAT *x,JBFLOAT *y,int n,JBFLOAT **b,JBFLOAT **c,JBFLOAT **d)
{
	register int i,j,m;
	register JBFLOAT dx;
	JBFLOAT *B,*C,*D,*E,*F,*H;
	m=3*(n-1);
	B=(JBFLOAT*)g_malloc(6*(m-1)*sizeof(JBFLOAT));
	C=B+m-2;
	D=C+m-1;
	E=D+m;
	F=E+m-1;
	H=F+m-2;
	dx=x[1]-x[0];
	B[0]=B[1]=D[3]=E[2]=E[3]=F[3]=H[1]=H[2]=H[3]=0.;
	C[0]=C[1]=C[2]=1.;
	F[1]=F[2]=-1.;
	D[0]=dx;
	D[1]=D[0]+dx;
	D[2]=D[1]+dx;
	E[0]=D[0]*dx;
	E[1]=3*E[0];
	F[0]=E[0]*dx;
	H[0]=y[1]-y[0];
	for (i=n-2; --i>0;)
	{
		j=3*i+1;
		dx=x[i+1]-x[i];
		B[j-2]=D[j+2]=F[j]=F[j+1]=F[j+2]=H[j+1]=H[j+2]=0.;
		B[j-1]=B[j]=1.;
		E[j+1]=E[j+2]=-1.;
		C[j-1]=dx;
		C[j]=C[j-1]+dx;
		C[j+1]=C[j]+dx;
		D[j]=C[j-1]*dx;
		D[j+1]=3*D[j];
		E[j]=D[j]*dx;
		H[j]=y[i+1]-y[i];
	}
	j=3*n-5;
	dx=x[n-1]-x[n-2];
	B[j-2]=B[j-1]=C[j]=H[j+1]=0.;
	D[j+1]=1.;
	C[j-1]=dx;
	D[j]=dx*dx;
	E[j]=D[j]*dx;
	H[j]=y[n-1]-y[n-2];
	jbm_solve_pentadiagonal_matrix(B,C,D,E,F,H,m-1);
	*b = (JBFLOAT*)g_malloc(3 * (n-1) * sizeof(JBFLOAT));
	*c = *b + n - 1;
	*d = *c + n - 1;
	for (i=n-1; --i>=0;)
	{
		j=3*i;
		(*b)[i]=H[j];
		(*c)[i]=H[++j];
		(*d)[i]=H[++j];
	}
	g_free(B);
}

#if INLINE_JBM_SPLINE_CUBIC
	#define jbm_spline_cubic _jbm_spline_cubic
#else
	void jbm_spline_cubic(JBFLOAT*,JBFLOAT*,int,JBFLOAT**,JBFLOAT**,JBFLOAT**);
#endif

static inline JBDOUBLE _jbm_flux_limiter_superbee(JBDOUBLE d1, JBDOUBLE d2)
{
	register JBDOUBLE r;
	if (d1*d2<=0.) return 0.;
	r=d1/d2;
	return fmaxl(fminl(r+r, 1.), fminl(r, 2.));
}

#if INLINE_JBM_FLUX_LIMITER_SUPERBEE
	#define jbm_flux_limiter_superbee _jbm_flux_limiter_superbee
#else
	JBDOUBLE jbm_flux_limiter_superbee(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_VanLeer(JBDOUBLE d1, JBDOUBLE d2)
{
	register JBDOUBLE r, k;
	if (d1*d2<=0.) return 0.;
	r=d1/d2;
	k=fabsl(r);
	return (r+k)/(1.+k);
}

#if INLINE_JBM_FLUX_LIMITER_VANLEER
	#define jbm_flux_limiter_VanLeer _jbm_flux_limiter_VanLeer
#else
	JBDOUBLE jbm_flux_limiter_VanLeer(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_VanAlbada(JBDOUBLE d1, JBDOUBLE d2)
{
	register JBDOUBLE r, k;
	if (d1*d2<=0.) return 0.;
	r=d1/d2;
	k=r*r;
	return (r+k)/(1.+k);
}

#if INLINE_JBM_FLUX_LIMITER_VANALBADA
	#define jbm_flux_limiter_VanAlbada _jbm_flux_limiter_VanAlbada
#else
	JBDOUBLE jbm_flux_limiter_VanAlbada(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_minmod(JBDOUBLE d1, JBDOUBLE d2)
{
	if (d1*d2<=0.) return 0.;
	return fminl(d1/d2, 1.);
}

#if INLINE_JBM_FLUX_LIMITER_MINMOD
	#define jbm_flux_limiter_minmod _jbm_flux_limiter_minmod
#else
	JBDOUBLE jbm_flux_limiter_minmod(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_supermin(JBDOUBLE d1, JBDOUBLE d2)
{
	if (d1*d2<=0.) return 0.;
	return fminl(jbm_fdbl(d1/d2), 1.);
}

#if INLINE_JBM_FLUX_LIMITER_SUPERMIN
	#define jbm_flux_limiter_supermin _jbm_flux_limiter_supermin
#else
	JBDOUBLE jbm_flux_limiter_supermin(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_minsuper(JBDOUBLE d1, JBDOUBLE d2)
{
	if (d1*d2<=0.) return 0.;
	return fminl(d1/d2, 2.);
}

#if INLINE_JBM_FLUX_LIMITER_MINSUPER
	#define jbm_flux_limiter_minsuper _jbm_flux_limiter_minsuper
#else
	JBDOUBLE jbm_flux_limiter_minsuper(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_null(JBDOUBLE d1, JBDOUBLE d2)
{
	return 1.;
}

#if INLINE_JBM_FLUX_LIMITER_NULL
	#define jbm_flux_limiter_null _jbm_flux_limiter_null
#else
	JBDOUBLE jbm_flux_limiter_null(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_centered(JBDOUBLE d1, JBDOUBLE d2)
{
	if (d2==0.) return 0.;
	return d1/d2;
}

#if INLINE_JBM_FLUX_LIMITER_CENTERED
	#define jbm_flux_limiter_centered _jbm_flux_limiter_centered
#else
	JBDOUBLE jbm_flux_limiter_centered(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_total(JBDOUBLE d1, JBDOUBLE d2)
{
	return 0.;
}

#if INLINE_JBM_FLUX_LIMITER_TOTAL
	#define jbm_flux_limiter_total _jbm_flux_limiter_total
#else
	JBDOUBLE jbm_flux_limiter_total(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_Burguete(JBDOUBLE d1, JBDOUBLE d2)
{
	register JBDOUBLE k;
	if (d1*d2<=0.) return 0.;
	k=d1/d2;
	if (k>=3.) return 2.;
	if (k<=1./3.) return k+k;
	return 0.5*(k+1.);
}

#if INLINE_JBM_FLUX_LIMITER_BURGUETE
	#define jbm_flux_limiter_Burguete _jbm_flux_limiter_Burguete
#else
	JBDOUBLE jbm_flux_limiter_Burguete(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE _jbm_flux_limiter_mean(JBDOUBLE d1, JBDOUBLE d2)
{
	if (d2==0.) return 0.;
	return 0.5*(d1/d2+1.);
}

#if INLINE_JBM_FLUX_LIMITER_MEAN
	#define jbm_flux_limiter_mean _jbm_flux_limiter_mean
#else
	JBDOUBLE jbm_flux_limiter_mean(JBDOUBLE, JBDOUBLE);
#endif

static inline JBDOUBLE
	(*_jbm_flux_limiter_select(int type))(JBDOUBLE, JBDOUBLE)
{
	switch (type)
	{
	case 0:
		return jbm_flux_limiter_superbee;
	case 1:
		return jbm_flux_limiter_VanLeer;
	case 2:
		return jbm_flux_limiter_VanAlbada;
	case 3:
		return jbm_flux_limiter_minmod;
	case 4:
		return jbm_flux_limiter_supermin;
	case 5:
		return jbm_flux_limiter_minsuper;
	case 6:
		return jbm_flux_limiter_null;
	case 7:
		return jbm_flux_limiter_centered;
	case 8:
		return jbm_flux_limiter_total;
	case 9:
		return jbm_flux_limiter_Burguete;
	}
	return jbm_flux_limiter_mean;
}

#if INLINE_JBM_FLUX_LIMITER_SELECT
	#define jbm_flux_limiter_select _jbm_flux_limiter_select
#else
	JBDOUBLE (*jbm_flux_limiter_select(int))(JBDOUBLE, JBDOUBLE);
#endif

static inline void _jbm_transversal_section_regions_sort
	(int i, int nj, int *nk, JBFLOAT *l, JBFLOAT *z, JBFLOAT *zz)
{
	register int j, k;
	register JBDOUBLE t;
	int nx[nj], na[nj];
	JBFLOAT x[nj];
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
		fprintf(stderr, "JBM transversal section regions sort: start\n");
	#endif
	t=0.5*(zz[i]+zz[i+1]);
	for (j=nj; --j>=0;)
	{
		na[j]=k=nk[j];
		x[j]=jbm_extrapolate(t, z[k], z[k+1], l[k], l[k+1]);
		#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
			fprintf(stderr, "JBM tsrs j=%d k=%d x="FWF"\n", j, k, x[j]);
		#endif
	}
	jbm_index_sort(x, nx, nj-1);
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
		for (j=0; j<nj; ++j) fprintf(stderr, "JBM tsrs i=%d nx=%d\n", j, nx[j]);
	#endif
	for (j=nj; --j>=0;) *(nk++)=na[nx[j]];
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
		fprintf(stderr, "JBM transversal section regions sort: end\n");
	#endif
}

#if INLINE_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
	#define jbm_transversal_section_regions_sort \
		_jbm_transversal_section_regions_sort
#else
	void jbm_transversal_section_regions_sort
		(int, int*, int*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, int*);
#endif

static inline int _jbm_transversal_section_regions(JBFLOAT *l, JBFLOAT *z, int n,
	JBFLOAT **zz, int **ni, int **nj, int **nij, int *nmin)
{

/*
	Obtención de las regiones de un transversal
	
Entradas:
	l, z: farrays de puntos que definen el transversal
	n: Número de los farrays (de 0 a n)

Salidas:
	Devuelve el número de regiones (de 0 a n-1)
	zz: farray ordenado de menor a mayor con las coordenadas z del transversal
	ni: Índices (ordenados en z) de los puntos del transversal
	nj: Número de elementos (de 0 a nj-1) de cada región j
	nij: Segmentos ordenados de menor a mayor de cada región j
	nmin: Punto de orilla mínima

Deben liberarse: zz, ni, nj
*/

	register int i=0, j, k;
	int nmax, *nk;
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
		fprintf(stderr, "JBM transversal section regions: start\n");
	#endif
	nmax = i = jbm_index_sort_extended(z, zz, ni, n);
	if (!i) goto exit1;
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
		fprintf(stderr, "JBM tsr n=%d\n", i);
		for (j=0; j<=n; ++j) fprintf(stderr, "JBM tsr i=%d ni=%d\n", j, (*ni)[j]);
		for (j=0; j<=i; ++j)
			fprintf(stderr, "JBM tsr i=%d z="FWF"\n", j, (*zz)[j]);
	#endif
	*nj=(int*)g_try_malloc(n*(i+1)*sizeof(int));
	if (!*nj)
	{
		g_free(*zz);
		g_free(*ni);
		i=0;
		goto exit1;
	}
	*nij=*nj+n;
	while (--i>=0) (*nj)[i]=0;
	for (i=0; i<n; ++i)
	{
		if ((*ni)[i+1] > (*ni)[i]) j=(*ni)[i+1], k=(*ni)[i];
		else j=(*ni)[i], k=(*ni)[i+1];
		while (--j>=k) (*nij)[n*j+(*nj)[j]++]=i;
	}
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
		for (i=0; i<nmax; ++i)
		{
			fprintf(stderr, "JBM tsr i=%d (*nj)=%d\n", i, (*nj)[i]);
			for (j=0; j<(*nj)[i]; ++j)
				fprintf(stderr, "JBM tsr i=%d j=%d nij=%d\n", i, j, (*nij)[n*i+j]);
		}
	#endif
	*nmin=jbm_min((*ni)[0], (*ni)[n]);
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
		fprintf(stderr, "JBM tsr n0=%d nn=%d nmax=%d nmin=%d\n",
			(*ni)[0], (*ni)[n], nmax, *nmin);
	#endif
	for (i=0, nk=*nij; i<nmax; ++i, nk+=n)
		jbm_transversal_section_regions_sort(i, (*nj)[i], nk, l, z, *zz);

	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
		for (i=0; i<=n; ++i)
			fprintf(stderr, "JBM tsr i=%d ni=%d\n", i, (*ni)[i]);
		for (i=0; i<=nmax; ++i)
			fprintf(stderr, "JBM tsr i=%d z="FWF"\n", i, (*zz)[i]);
		for (i=0; i<nmax; ++i)
			fprintf(stderr, "JBM tsr i=%d nj=%d\n", i, (*nj)[i]);
		for (i=0, nk=*nij; i<nmax; ++i, nk+=n) for (j=0; j<(*nj)[i]; ++j)
			fprintf(stderr, "JBM tsr i=%d j=%d nij=%d\n", i, j, nk[j]);
	#endif

exit1:
	#if DEBUG_JBM_TRANSVERSAL_SECTION_REGIONS
		fprintf(stderr, "JBM transversal section regions: end\n");
	#endif
	return i;
}

#if INLINE_JBM_TRANSVERSAL_SECTION_REGIONS
	#define jbm_transversal_section_regions _jbm_transversal_section_regions
#else
	int jbm_transversal_section_regions
		(JBFLOAT*, JBFLOAT*, int, JBFLOAT**, int**, int**, int**, int*);
#endif

/* Regresión lineal: obtiene los coeficientes a y b de la regresión y=a+bx */

static inline void
	_jbm_regression_linear(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE *a, JBDOUBLE *b)
{
	register int i;
	register JBDOUBLE syx, sy, sxx, sx;
	syx=sy=sxx=sx=0.;
	++n;
	for (i=n; --i>=0; ++x, ++y)
	{
		sy += *y;
		syx += *x * *y;
		sxx += *x * *x;
		sy += *x;
	}
	*b = (n * syx - sy * sx) / (n * sxx - sx * sx);
	*a = (sy - *b * sx) / n;
}

#if INLINE_JBM_REGRESSION_LINEAR
	#define jbm_regression_linear _jbm_regression_linear
#else
	void jbm_regression_linear(JBFLOAT*, JBFLOAT*, int, JBFLOAT*, JBFLOAT*);
#endif

/*
	Regresión exponencial: obtiene los coeficientes a y b de la regresión y=ax^b
	Modifica las matrices x, y
*/

static inline void
	_jbm_regression_exponential(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE *a, JBDOUBLE *b)
{
	register int i;
	for (i=n+1; --i>=0;) x[i]=log(x[i]), y[i]=log(y[i]);
	jbm_regression_linear(x, y, n, a, b);
	*a = exp(*a);
}

#if INLINE_JBM_REGRESSION_EXPONENTIAL
	#define jbm_regression_exponential _jbm_regression_exponential
#else
	void jbm_regression_exponential(JBFLOAT*, JBFLOAT*, int, JBFLOAT*, JBFLOAT*);
#endif

static inline void _jbm_regression_multilinear(JBFLOAT **x, int n, JBFLOAT *a, int m)
{
	register int i, j, k;
	JBFLOAT *c, *d, *xj, *xk;
	++m;
	c=(JBFLOAT*)g_malloc(m*(m+1)*sizeof(JBFLOAT));
	for (j=m; --j>0;)
	{
		for (k=m; --k>=j;)
		{
			d=c+(m+1)*j+k;
			xj=x[j];
			xk=x[k];
			for (*d = 0., i=n+1; --i>=0;) *d += *(xj++) * *(xk++);
		}
		d=c+(m+1)*j+m;
		xj=x[j];
		xk=x[0];
		for (*d = 0., i=n+1; --i>=0;) *d += *(xj++) * *(xk++);
	}
	for (k=m; --k>0;)
	{
		d=c+k;
		xk=x[k];
		for (*d = 0., i=n+1; --i>=0;) *d += *(xk++);
	}
	d=c+m;
	xk=x[0];
	for (*d = 0., i=n+1; --i>=0;) *d += *(xk++);
	c[0]=n+1;
	for (j=m; --j>0;) for (k=j; --k>=0;) c[(m+1)*j+k]=c[(m+1)*k+j];
	jbm_solve_matrix(c, m);
	for (i=0, d=c+m; ++i<=m; ++a, d+=m+1) *a = *d;
	g_free(c);
}

#if INLINE_JBM_REGRESSION_MULTILINEAR
	#define jbm_regression_multilinear _jbm_regression_multilinear
#else
	void jbm_regression_multilinear(JBFLOAT **x, int n, JBFLOAT *a, int m);
#endif

static inline void
	_jbm_regression_multiexponential(JBFLOAT **x, int n, JBFLOAT *a, int m)
{
	register int i, j;
	JBFLOAT *c;
	for (j=m+1; --j>=0;) for (i=n+1, c=x[j]; --i>=0; ++c) *c = log(*c);
	jbm_regression_multilinear(x, n, a, m);
	a[0]=exp(a[0]);
}

#if INLINE_JBM_REGRESSION_MULTIEXPONENTIAL
	#define jbm_regression_multiexponential _jbm_regression_multiexponential
#else
	void jbm_regression_multiexponential(JBFLOAT **x, int n, JBFLOAT *a, int m);
#endif

/* varray: array de tipo struct de tamaño size de elementos 0 a n */

static inline int _jbm_varray_search(JBDOUBLE x, void *v, int size, int n)
{

/*
	Búsqueda del intervalo en el que se sitúa x en un varray ordenado de menor
	a mayor
*/
	register int i, j;
	#if DEBUG_JBM_VARRAY_SEARCH
		fprintf(stderr, "JBM varray search\n");
	#endif
	for (i=0; n-i>1;)
	{
		j=(i+n)>>1;
		if (x<=*(JBFLOAT*)(v+j*size)) n=j; else i=j;
	}
	#if DEBUG_JBM_VARRAY_SEARCH
		fprintf(stderr, "JBM varray search i=%d\n", i);
	#endif
	return i;
}

#if INLINE_JBM_VARRAY_SEARCH
	#define jbm_varray_search _jbm_varray_search
#else
	int jbm_varray_search(JBDOUBLE, void*, int, int);
#endif

static inline int _jbm_varray_search_extended(JBDOUBLE x, void *v, int size, int n)
{

/*
	Búsqueda del intervalo en el que se sitúa x en un varray ordenado de menor
	a mayor: develve -1 si x<v0, n si x>=vn
*/

	register int i;
	#if DEBUG_JBM_VARRAY_SEARCH_EXTENDED
		fprintf(stderr, "JBM varray search_extended\n");
	#endif
	if (x<*(JBFLOAT*)v) i=-1;
	else if (x>=*(JBFLOAT*)(v+n*size)) i=n;
	else i=jbm_varray_search(x, v, size, n);
	#if DEBUG_JBM_VARRAY_SEARCH_EXTENDED
		fprintf(stderr, "JBM varray search_extended i=%d\n", i);
	#endif
	return i;
}

#if INLINE_JBM_VARRAY_SEARCH_EXTENDED
	#define jbm_varray_search_extended _jbm_varray_search_extended
#else
	int jbm_varray_search_extended(JBDOUBLE, void*, int, int);
#endif

static inline JBDOUBLE _jbm_varray_max(void *v, int size, int n)
{
	register int i;
	register JBDOUBLE k;
	#if DEBUG_JBM_VARRAY_MAX
		fprintf(stderr, "JBM varray max\n");
	#endif
	k = *(JBFLOAT*)v;
	for (i=0; ++i<=n;) k = fmaxl(k, *(JBFLOAT*)(v += size));
	#if DEBUG_JBM_VARRAY_MAX
		fprintf(stderr, "JBM varray max="FWL"\n", k);
	#endif
	return k;
}

#if INLINE_JBM_VARRAY_MAX
	#define jbm_varray_max _jbm_varray_max
#else
	JBDOUBLE jbm_varray_max(void*, int, int);
#endif

static inline JBDOUBLE _jbm_varray_min(void *v, int size, int n)
{
	register int i;
	register JBDOUBLE k;
	#if DEBUG_JBM_VARRAY_MIN
		fprintf(stderr, "JBM varray min\n");
	#endif
	k = *(JBFLOAT*)v;
	for (i=0; ++i<=n;) k = fminl(k, *(JBFLOAT*)(v += size));
	#if DEBUG_JBM_VARRAY_MIN
		fprintf(stderr, "JBM varray min="FWL"\n", k);
	#endif
	return k;
}

#if INLINE_JBM_VARRAY_MIN
	#define jbm_varray_min _jbm_varray_min
#else
	JBDOUBLE jbm_varray_min(void*, int, int);
#endif

static inline void
	_jbm_varray_maxmin(void *v, int size, int n, JBDOUBLE *max, JBDOUBLE *min)
{
	register int i;
	register JBDOUBLE kmax, kmin;
	#if DEBUG_JBM_VARRAY_MAXMIN
		fprintf(stderr, "JBM varray maxmin\n");
	#endif
	kmax = kmin = *(JBFLOAT*)v;
	for (i=0; ++i<=n;)
	{
		v+=size;
		if (kmax < *(JBFLOAT*)v) kmax = *(JBFLOAT*)v;
		else if (kmin > *(JBFLOAT*)v) kmin = *(JBFLOAT*)v;
	}
	*max=kmax, *min=kmin;
	#if DEBUG_JBM_VARRAY_MAXMIN
		fprintf(stderr, "JBM varray max="FWL" min="FWL"\n", kmax, kmin);
	#endif
}

#if INLINE_JBM_VARRAY_MAXMIN
	#define jbm_varray_maxmin _jbm_varray_maxmin
#else
	void jbm_varray_maxmin(void*, int, int, JBDOUBLE*, JBDOUBLE*);
#endif

static inline JBDOUBLE _jbm_varray_mean_square_error
	(void *xa, void *fa, int sizea, int na, void *xr, void *fr, int sizer, int nr)
{
	register int i, j;
	JBDOUBLE k=0., k2;
	#if DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM varray mean square error\n");
	#endif
	for (i=0; i<=na && *(JBFLOAT*)xa<*(JBFLOAT*)xr; ++i, xa+=sizea, fa+=sizea)
	{
		k += jbm_fsqr(*(JBFLOAT*)fa - *(JBFLOAT*)fr);
		#if DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMVMSE i=%d fa="FWF" fr="FWF" k="FWL"\n",
				i, *(JBFLOAT*)fa, *(JBFLOAT*)fr, k);
		#endif
	}
	for (j=0; i<=na; ++i, xa+=sizea, fa+=sizea)
	{
		while (j<nr && *(JBFLOAT*)xa>*(JBFLOAT*)(xr+sizer))
			++j, xr+=sizer, fr+=sizer;
		#if DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMVMSE j=%d\n", j);
		#endif
		if (j==nr)
		{
			for (; i<=na; ++i, xa+=sizea, fa+=sizea)
			{
				k += jbm_fsqr(*(JBFLOAT*)fa - *(JBFLOAT*)fr);
				#if DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
					fprintf(stderr, "JBMVMSE i=%d fa="FWF" fr="FWF" k="FWL"\n",
						i, *(JBFLOAT*)fa, *(JBFLOAT*)fr, k);
				#endif
			}
		}
		else
		{
			
			k2 =jbm_extrapolate(*(JBFLOAT*)xa, *(JBFLOAT*)xr, *(JBFLOAT*)(xr+sizer),
				*(JBFLOAT*)fr, *(JBFLOAT*)(fr+sizer));
			k += jbm_fsqr(*(JBFLOAT*)fa - k2);
			#if DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
				fprintf(stderr, "JBMVMSE xa="FWF" xr="FWF" xr2="FWF"\n",
					*(JBFLOAT*)xa, *(JBFLOAT*)xr, *(JBFLOAT*)(xr+sizer));
				fprintf(stderr, "JBMVMSE k2="FWL" yr="FWF" yr2="FWF"\n",
					k2, *(JBFLOAT*)fr, *(JBFLOAT*)(fr+sizer));
				fprintf(stderr, "JBMVMSE i=%d j=%d k="FWL"\n", i, j, k);
			#endif
		}
	}
	k=sqrt(k/(na+1));
	#if DEBUG_JBM_VARRAY_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM varray mean square error="FWL"\n", k);
	#endif
	return k;
}

#if INLINE_JBM_VARRAY_MEAN_SQUARE_ERROR
	#define jbm_varray_mean_square_error _jbm_varray_mean_square_error
#else
	JBDOUBLE jbm_varray_mean_square_error
		(void*, void*, int, int, void*, void*, int, int);
#endif

static inline JBDOUBLE _jbm_file_mean_square_error
	(char *namea, int ixa, int ifa, int na, char *namer, int ixr, int ifr, int nr)
{
	int i, j, endr;
	JBDOUBLE k, xa, fa, xr1, fr1, xr2, fr2, aa[na], ar[nr];
	FILE *filea, *filer;
	#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM file mean square error\n");
	#endif
	endr=i=0;
	k=0.;
	filea=fopen(namea, "r");
	if (!filea) goto exit_mse;
	filer=fopen(namer, "r");
	if (!filer) goto exit_mse;
	for (j=0; j<nr; ++j)
		if (fscanf(filer, FRL, ar+j)!=1) goto exit_mse;
	xr1=ar[ixr-1];
	fr1=ar[ifr-1];
	#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBMFMSE xr1="FWL" fr1="FWL"\n", xr1, fr1);
	#endif
	for (j=0; j<nr; ++j)
		if (fscanf(filer, FRL, ar+j)!=1) endr=1;
	xr2=ar[ixr-1];
	fr2=ar[ifr-1];
	#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBMFMSE xr2="FWL" fr2="FWL"\n", xr2, fr2);
	#endif
	for (i=0; !endr; ++i)
	{
		for (j=0; j<na; ++j)
			if (fscanf(filea, FRL, aa+j)!=1) goto exit_mse;
		xa=aa[ixa-1];
		fa=aa[ifa-1];
		#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMFMSE xa="FWL" fa="FWL"\n", xa, fa);
		#endif
		while (xa>xr2)
		{
			xr1=xr2;
			fr1=fr2;
			for (j=0; j<nr; ++j) if (fscanf(filer, FRL, ar+j)!=1)
			{
				endr=1;
				goto end_filer;
			}
			xr2=ar[ixr-1];
			fr2=ar[ifr-1];
			#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
				fprintf(stderr, "JBMFMSE xr2="FWL" fr2="FWL"\n", xr2, fr2);
			#endif
		}
end_filer:
		if (!endr && xa>xr1)
			k+=jbm_fsqr(fa-jbm_extrapolate(xa, xr1, xr2, fr1, fr2));
		else k+=jbm_fsqr(fa-fr1);
		#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMFMSE k="FWL"\n", k);
		#endif
	}
	for (; 1; ++i)
	{
		for (j=0; j<na; ++j)
			if (fscanf(filea, FRL, aa+j)!=1) goto exit_mse;
		xa=aa[ixa-1];
		fa=aa[ifa-1];
		k+=jbm_fsqr(fa-fr1);
		#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
			fprintf(stderr, "JBMFMSE xa="FWL" fa="FWL"\n", xa, fa);
		#endif
	}
exit_mse:
	#if DEBUG_JBM_FILE_MEAN_SQUARE_ERROR
		fprintf(stderr, "JBM file mean square error="FWL" i=%d\n", (JBDOUBLE)sqrt(k/i), i);
	#endif
	if (i==0) return 0.;
	return sqrt(k/i);
}

#if INLINE_JBM_FILE_MEAN_SQUARE_ERROR
	#define jbm_file_mean_square_error _jbm_file_mean_square_error
#else
	JBDOUBLE jbm_file_mean_square_error(char*, int, int, int, char*, int, int, int);
#endif

#endif
