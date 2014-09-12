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
 * \file jb_math.c
 * \brief Source file with useful mathematical functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#include "jb_math.h"

/**
 * \fn int jbm_fcompare(JBDOUBLE a, JBDOUBLE b)
 * \brief Function to compare 2 float numbers.
 * \param a
 * \brief 1st JBDOUBLE number.
 * \param b
 * \brief 2nd JBDOUBLE number.
 * \return 0 on the difference is lower than the 6th digit, else:
 * 	-1 on a < b, 1 on a > b
 */
#if !INLINE_JBM_FCOMPARE
int jbm_fcompare(JBDOUBLE a, JBDOUBLE b) {return _jbm_fcompare(a, b);}
#endif

/**
 * \fn int jbm_max(int a, int b)
 * \brief Function to calculate the maximum of 2 int numbers.
 * \param a
 * \brief 1st int number.
 * \param b
 * \brief 2nd int number.
 * \return Maximum number.
 */
#if !INLINE_JBM_MAX
int jbm_max(int a, int b) {return _jbm_max(a, b);}
#endif

/**
 * \fn int jbm_min(int a, int b)
 * \brief Function to calculate the minimum of 2 int numbers.
 * \param a
 * \brief 1st int number.
 * \param b
 * \brief 2nd int number.
 * \return Minimum number.
 */
#if !INLINE_JBM_MIN
int jbm_min(int a, int b) {return _jbm_min(a, b);}
#endif

/**
 * \fn long int jbm_maxl(long int a, long int b)
 * \brief Function to calculate the maximum of 2 long int numbers.
 * \param a
 * \brief 1st long int number.
 * \param b
 * \brief 2nd long int number.
 * \return Maximum number.
 */
#if !INLINE_JBM_MAXL
long int jbm_maxl(long int a, long int b) {return _jbm_maxl(a, b);}
#endif

/**
 * \fn long int jbm_minl(long int a, long int b)
 * \brief Function to calculate the minimum of 2 long int numbers.
 * \param a
 * \brief 1st long int number.
 * \param b
 * \brief 2nd long int number.
 * \return Minimum number.
 */
#if !INLINE_JBM_MINL
long int jbm_minl(long int a, long int b) {return _jbm_minl(a, b);}
#endif

/**
 * \fn long long int jbm_maxll(long long int a, long long int b)
 * \brief Function to calculate the maximum of 2 long long int numbers.
 * \param a
 * \brief 1st long long int number.
 * \param b
 * \brief 2nd long long int number.
 * \return Maximum number.
 */
#if !INLINE_JBM_MAXLL
long long int jbm_maxll(long long int a, long long int b)
{return _jbm_maxll(a, b);}
#endif

/**
 * \fn long long int jbm_minll(long long int a, long long int b)
 * \brief Function to calculate the minimum of 2 long long int numbers.
 * \param a
 * \brief 1st long long int number.
 * \param b
 * \brief 2nd long long int number.
 * \return Minimum number.
 */
#if !INLINE_JBM_MINLL
long long int jbm_minll(long long int a, long long int b)
{return _jbm_minll(a, b);}
#endif

/**
 * \fn int jbm_modmin(int a, int b)
 * \brief Function to calculate the number with the lower module in the [a, b]
 *   interval (int arguments).
 *   \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 * \param a
 * \brief 1st int number.
 * \param b
 * \brief 2nd int number.
 * \return Modmin number.
 */
#if !INLINE_JBM_MODMIN
int jbm_modmin(int a, int b) {return _jbm_modmin(a, b);}
#endif

/**
 * \fn int jbm_modminl(long int a, long int b)
 * \brief Function to calculate the number with the lower module in the [a, b]
 *   interval (long int arguments).
 *   \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 * \param a
 * \brief 1st long int number.
 * \param b
 * \brief 2nd long int number.
 * \return Modmin number.
 */
#if !INLINE_JBM_MODMINL
long int jbm_modminl(long int a, long int b) {return _jbm_modminl(a, b);}
#endif

/**
 * \fn int jbm_modminll(long long int a, long long int b)
 * \brief Function to calculate the number with the lower module in the [a, b]
 *   interval (long long int arguments).
 *   \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 * \param a
 * \brief 1st long long int number.
 * \param b
 * \brief 2nd long long int number.
 * \return Modmin number.
 */
#if !INLINE_JBM_MODMINLL
long long int jbm_modminll(long long int a, long long int b)
{return _jbm_modminll(a, b);}
#endif

/**
 * \fn int jbm_fmodmin(JBDOUBLE a, JBDOUBLE b)
 * \brief Function to calculate the number with the lower module in the [a, b]
 *   interval (float arguments).
 *   \f$\mathrm{modmin}(a, b)=\left\{\begin{array}{lc}
 *   0, & a\cdot b\le 0;\\
 *   a, & a,b\ne 0,\;|a|<|b|;\\
 *   b, & a,b\ne 0,\;|a|\ge|b|;
 *   \end{array}\right.\f$.
 * \param a
 * \brief 1st JBDOUBLE number.
 * \param b
 * \brief 2nd JBDOUBLE number.
 * \return Modmin number.
 */
#if !INLINE_JBM_FMODMIN
JBDOUBLE jbm_fmodmin(JBDOUBLE a, JBDOUBLE b) {return _jbm_fmodmin(a, b);}
#endif

/**
 * \fn void jbm_change(int *a, int *b)
 * \brief Function to interchange 2 int numbers.
 * \param a
 * \brief 1st int number pointer.
 * \param b
 * \brief 2nd int number pointer.
 */
#if !INLINE_JBM_CHANGE
void jbm_change(int *a, int *b) {_jbm_change(a, b);}
#endif

/**
 * \fn void jbm_changel(long int *a, long int *b)
 * \brief Function to interchange 2 long int numbers.
 * \param a
 * \brief 1st long int number pointer.
 * \param b
 * \brief 2nd long int number pointer.
 */
#if !INLINE_JBM_CHANGEL
void jbm_changel(long int *a, long int *b) {_jbm_changel(a, b);}
#endif

/**
 * \fn void jbm_changell(long long int *a, long long int *b)
 * \brief Function to interchange 2 long long int numbers.
 * \param a
 * \brief 1st long long int number pointer.
 * \param b
 * \brief 2nd long long int number pointer.
 */
#if !INLINE_JBM_CHANGELL
void jbm_changell(long long int *a, long long int *b) {_jbm_changell(a, b);}
#endif

/**
 * \fn void jbm_fchange(JBFLOAT *a, JBFLOAT *b)
 * \brief Function to interchange 2 JBFLOAT numbers.
 * \param a
 * \brief 1st JBFLOAT number pointer.
 * \param b
 * \brief 2nd JBFLOAT number pointer.
 */
#if !INLINE_JBM_FCHANGE
void jbm_fchange(JBFLOAT *a, JBFLOAT *b) {_jbm_fchange(a, b);}
#endif

/**
 * \fn void jbm_fchangel(JBDOUBLE *a, JBDOUBLE *b)
 * \brief Function to interchange 2 JBDOUBLE numbers.
 * \param a
 * \brief 1st JBDOUBLE number pointer.
 * \param b
 * \brief 2nd JBDOUBLE number pointer.
 */
#if !INLINE_JBM_FCHANGEL
void jbm_fchangel(JBDOUBLE *a, JBDOUBLE *b) {_jbm_fchangel(a, b);}
#endif

/**
 * \fn int jbm_sqr(int x)
 * \brief Function to calculate the square of an int number.
 * \param x
 * \brief int number.
 * \return square.
 */
#if !INLINE_JBM_SQR
int jbm_sqr(int x) {return _jbm_sqr(x);}
#endif

/**
 * \fn long int jbm_sqrl(long int x)
 * \brief Function to calculate the square of a long int number.
 * \param x
 * \brief long int number.
 * \return square.
 */
#if !INLINE_JBM_SQRL
long int jbm_sqrl(long int x) {return _jbm_sqrl(x);}
#endif

/**
 * \fn long long int jbm_sqrll(long long int x)
 * \brief Function to calculate the square of a long long int number.
 * \param x
 * \brief long long int number.
 * \return square.
 */
#if !INLINE_JBM_SQRLL
long long int jbm_sqrll(long long int x) {return _jbm_sqrll(x);}
#endif

/**
 * \fn JBDOUBLE jbm_fsqr(JBDOUBLE x)
 * \brief Function to calculate the square of a JBDOUBLE number.
 * \param x
 * \brief JBDOUBLE number.
 * \return square.
 */
#if !INLINE_JBM_FSQR
JBDOUBLE jbm_fsqr(JBDOUBLE x) {return _jbm_fsqr(x);}
#endif

/**
 * \fn int jbm_dbl(int x)
 * \brief Function to calculate the double of an int number.
 * \param x
 * \brief int number.
 * \return double.
 */
#if !INLINE_JBM_DBL
int jbm_dbl(int x) {return _jbm_dbl(x);}
#endif

/**
 * \fn long int jbm_dbll(long int x)
 * \brief Function to calculate the double of a long int number.
 * \param x
 * \brief long int number.
 * \return double.
 */
#if !INLINE_JBM_DBLL
long int jbm_dbll(long int x) {return _jbm_dbll(x);}
#endif

/**
 * \fn long long int jbm_dblll(long long int x)
 * \brief Function to calculate the double of a long long int number.
 * \param x
 * \brief long long int number.
 * \return double.
 */
#if !INLINE_JBM_DBLLL
long long int jbm_dblll(long long int x) {return _jbm_dblll(x);}
#endif

/**
 * \fn JBDOUBLE jbm_fdbl(JBDOUBLE x)
 * \brief Function to calculate the double of a JBDOUBLE number.
 * \param x
 * \brief JBDOUBLE number.
 * \return double.
 */
#if !INLINE_JBM_FDBL
JBDOUBLE jbm_fdbl(JBDOUBLE x) {return _jbm_fdbl(x);}
#endif

/**
 * \fn JBDOUBLE jbm_extrapolate(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, \
 *   JBDOUBLE y1, JBDOUBLE y2)
 * \brief Function to perform an extrapolation between 2 2D points.
 * \param x
 * \brief x-coordinate of the extrapolated point.
 * \param x1
 * \brief x-coordinate of the 1st point.
 * \param x2
 * \brief x-coordinate of the 2nd point.
 * \param y1
 * \brief y-coordinate of the 1st point.
 * \param y2
 * \brief y-coordinate of the 2nd point.
 * \return y-coordinate of the extrapolated point.
 */
#if !INLINE_JBM_EXTRAPOLATE
JBDOUBLE jbm_extrapolate
	(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, JBDOUBLE y1, JBDOUBLE y2)
{return _jbm_extrapolate(x, x1, x2, y1, y2);}
#endif

/**
 * \fn JBDOUBLE jbm_interpolate(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, \
 *   JBDOUBLE y1, JBDOUBLE y2)
 * \brief Function to perform an interpolation between 2 2D points.
 * \param x
 * \brief x-coordinate of the interpolated point.
 * \param x1
 * \brief x-coordinate of the 1st point.
 * \param x2
 * \brief x-coordinate of the 2nd point.
 * \param y1
 * \brief y-coordinate of the 1st point.
 * \param y2
 * \brief y-coordinate of the 2nd point.
 * \return y-coordinate of the interpolated point.
 */
#if !INLINE_JBM_INTERPOLATE
JBDOUBLE jbm_interpolate
	(JBDOUBLE x, JBDOUBLE x1, JBDOUBLE x2, JBDOUBLE y1, JBDOUBLE y2)
{return _jbm_interpolate(x, x1, x2, y1, y2);}
#endif

/**
 * \fn JBDOUBLE jbm_integral(JBDOUBLE (*f)(JBDOUBLE), JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to approximate an integral defined in an interval.
 * \param f
 * \brief pointer to the function to integrate.
 * \param x1
 * \brief left limit of the interval.
 * \param x2
 * \brief right limit of the interval.
 * \return integral value.
 */
#if !INLINE_JBM_INTEGRAL
JBDOUBLE jbm_integral(JBDOUBLE (*f)(JBDOUBLE), JBDOUBLE x1, JBDOUBLE x2)
{return _jbm_integral(f, x1, x2);}
#endif

/**
 * \fn int jbm_farray_search(JBDOUBLE x, JBFLOAT *fa, int n)
 * \brief Function to search the interval where a number is in a increasingly
 *   sorted array of JBFLOAT numbers.
 * \param x
 * \brief number.
 * \param fa
 * \brief array of JBFLOAT numbers.
 * \param n
 * \brief number of the highest array element.
 * \return interval number.
 */
#if !INLINE_JBM_FARRAY_SEARCH
int jbm_farray_search(JBDOUBLE x, JBFLOAT *fa, int n)
{return _jbm_farray_search(x, fa, n);}
#endif

/**
 * \fn int jbm_farray_search_extended(JBDOUBLE x, JBFLOAT *fa, int n)
 * \brief Function to search the interval where a number is in a increasingly
 *   sorted array of JBFLOAT numbers.
 * \param x
 * \brief number.
 * \param fa
 * \brief array of JBFLOAT numbers.
 * \param n
 * \brief number of the highest array element.
 * \return interval number, -1 if x<fa[0] or n if x>fa[n].
 */
#if !INLINE_JBM_FARRAY_SEARCH_EXTENDED
int jbm_farray_search_extended(JBDOUBLE x, JBFLOAT *fa, int n)
{return _jbm_farray_search_extended(x, fa, n);}
#endif

/**
 * \fn JBDOUBLE jbm_farray_max(JBFLOAT *fa, int n)
 * \brief Function to find the highest element of an array of JBFLOAT numbers.
 * \param fa
 * \brief array of JBFLOAT numbers.
 * \param n
 * \brief number of the ending array element.
 * \return the highest value.
 */
#if !INLINE_JBM_FARRAY_MAX
JBDOUBLE jbm_farray_max(JBFLOAT *fa, int n) {return _jbm_farray_max(fa, n);}
#endif

/**
 * \fn JBDOUBLE jbm_farray_min(JBFLOAT *fa, int n)
 * \brief Function to find the lowest element of an array of JBFLOAT numbers.
 * \param fa
 * \brief array of JBFLOAT numbers.
 * \param n
 * \brief number of the ending array element.
 * \return the lowest value.
 */
#if !INLINE_JBM_FARRAY_MIN
JBDOUBLE jbm_farray_min(JBFLOAT *fa, int n) {return _jbm_farray_min(fa, n);}
#endif

/**
 * \fn void jbm_farray_maxmin(JBFLOAT *fa, int n, JBDOUBLE *max, JBDOUBLE *min)
 * \brief Function to find the highest and the lowest elements of an array of
 *   JBFLOAT numbers.
 * \param fa
 * \brief array of JBFLOAT numbers.
 * \param n
 * \brief number of the ending array element.
 * \param max
 * \brief the highest value.
 * \param min
 * \brief the lowest value.
 */
#if !INLINE_JBM_FARRAY_MAXMIN
void jbm_farray_maxmin(JBFLOAT *fa, int n, JBDOUBLE *max, JBDOUBLE *min)
{_jbm_farray_maxmin(fa, n, max, min);}
#endif

/**
 * \fn JBDOUBLE jbm_farray_interpolate(JBDOUBLE x, JBFLOAT *fa, JBFLOAT *fb, \
 *   int n)
 * \brief Function to calculate the y-coordinate of a 2D point interpolated
 *   between a tabular function defined by 2 arrays of JBFLOAT numbers.
 * \param x
 * \brief x-coordinate of the point.
 * \param fa
 * \brief increasingly sorted array of x-coordinates of the tabular function.
 * \param fb
 * \brief array of y-coordinates of the tabular function.
 * \param n
 * \brief the highest element number of the arrays.
 * \return y-coordinate of the interpolated point.
 */
#if !INLINE_JBM_FARRAY_INTERPOLATE
JBDOUBLE jbm_farray_interpolate(JBDOUBLE x, JBFLOAT *fa, JBFLOAT *fb, int n)
{return _jbm_farray_interpolate(x, fa, fb, n);}
#endif

/**
 * \fn JBFLOAT* jbm_farray_add(JBFLOAT *fa, int na, JBFLOAT *fb, int nb, \
 *   JBFLOAT **fc, int *nc)
 * \brief Function to add 2 increasingly sorted arrays of JBFLOAT numbers.
 * \param fa
 * \brief 1st increasingly sorted array of JBFLOAT numbers.
 * \param na
 * \brief the highest element number of the 1st array.
 * \param fb
 * \brief 2nd increasingly sorted array of JBFLOAT numbers.
 * \param nb
 * \brief the highest element number of the 2nd array.
 * \param fc
 * \brief pointer to the resulting increasingly sorted array of JBFLOAT numbers.
 * \param nc
 * \brief pointer to the highest element number of the resulting array.
 * \return resulting array.
 */
#if !INLINE_JBM_FARRAY_ADD
JBFLOAT* jbm_farray_add
	(JBFLOAT *fa, int na, JBFLOAT *fb, int nb, JBFLOAT **fc, int *nc)
{return _jbm_farray_add(fa, na, fb, nb, fc, nc);}
#endif

/**
 * \fn JBDOUBLE jbm_farray_integral(JBFLOAT *x, JBFLOAT *y, int n, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to integrate a tabular function in an interval.
 * \param x
 * \brief incresingly sorted array of JBFLOAT numbers defining the x-coordinates
 *   of the tabular function.
 * \param y
 * \brief array of JBFLOAT numbers defining the y-coordinates of the tabular
 *   function.
 * \param n
 * \brief the highest element number of the arrays.
 * \param x1
 * \brief left limit of the integration interval.
 * \param x2
 * \brief right limit of the integration interval.
 * \return integral value.
 */
#if !INLINE_JBM_FARRAY_INTEGRAL
JBDOUBLE jbm_farray_integral
	(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE x1, JBDOUBLE x2)
{return _jbm_farray_integral(x, y, n, x1, x2);}
#endif

/**
 * \fn JBDOUBLE jbm_farray_mean_square_error(JBFLOAT *xa, JBFLOAT *fa, int na, \
 *   JBFLOAT *xr, JBFLOAT *fr, int nr)
 * \brief Function to calculate the mean square error between 2 tabular
 *   functions.
 * \param xa
 * \brief incresingly sorted array of JBFLOAT numbers defining the x-coordinates
 *   of the 1st tabular function.
 * \param fa
 * \brief array of JBFLOAT numbers defining the y-coordinates of the 1st tabular
 *   function.
 * \param na
 * \brief the highest element number of the arrays defining the 1st tabular
 *   function.
 * \param xr
 * \brief incresingly sorted array of JBFLOAT numbers defining the x-coordinates
 *   of the 2nd tabular function.
 * \param fr
 * \brief array of JBFLOAT numbers defining the y-coordinates of the 2nd tabular
 *   function.
 * \param nr
 * \brief the highest element number of the arrays defining the 2nd tabular
 *   function.
 * \return mean square error.
 */
#if !INLINE_JBM_FARRAY_MEAN_SQUARE_ERROR
JBDOUBLE jbm_farray_mean_square_error
	(JBFLOAT *xa, JBFLOAT *fa, int na, JBFLOAT *xr, JBFLOAT *fr, int nr)
{return _jbm_farray_mean_square_error(xa, fa, na, xr, fr, nr);}
#endif

/**
 * \fn JBDOUBLE jbm_farray_root_mean_square_error(JBFLOAT *xa, JBFLOAT *fa, \
 *   int na, JBFLOAT *xr, JBFLOAT *fr, int nr)
 * \brief Function to calculate the root mean square error between 2 tabular
 *   functions.
 * \param xa
 * \brief incresingly sorted array of JBFLOAT numbers defining the x-coordinates
 *   of the 1st tabular function.
 * \param fa
 * \brief array of JBFLOAT numbers defining the y-coordinates of the 1st tabular
 *   function.
 * \param na
 * \brief the highest element number of the arrays defining the 1st tabular
 *   function.
 * \param xr
 * \brief incresingly sorted array of JBFLOAT numbers defining the x-coordinates
 *   of the 2nd tabular function.
 * \param fr
 * \brief array of JBFLOAT numbers defining the y-coordinates of the 2nd tabular
 *   function.
 * \param nr
 * \brief the highest element number of the arrays defining the 2nd tabular
 *   function.
 * \return root mean square error.
 */
#if !INLINE_JBM_FARRAY_ROOT_MEAN_SQUARE_ERROR
JBDOUBLE jbm_farray_root_mean_square_error
	(JBFLOAT *xa, JBFLOAT *fa, int na, JBFLOAT *xr, JBFLOAT *fr, int nr)
{return _jbm_farray_root_mean_square_error(xa, fa, na, xr, fr, nr);}
#endif

/**
 * \fn JBDOUBLE jbm_v2_length(JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE x2, \
 *   JBDOUBLE y2)
 * \brief Function to calculate the length of a 2D segement.
 * \param x1
 * \brief x-coordinate of the 1st point defining the segemnt.
 * \param y1
 * \brief y-coordinate of the 1st point defining the segemnt.
 * \param x2
 * \brief x-coordinate of the 2nd point defining the segemnt.
 * \param y2
 * \brief y-coordinate of the 2nd point defining the segemnt.
 * \return segement length.
 */
#if !INLINE_JBM_V2_LENGTH
JBDOUBLE jbm_v2_length(JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE x2, JBDOUBLE y2)
{return _jbm_v2_length(x1, y1, x2, y2);}
#endif

/**
 * \fn JBDOUBLE jbm_v3_length(JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE z1, \
 *   JBDOUBLE x2, JBDOUBLE y2, JBDOUBLE z2)
 * \brief Function to calculate the length of a 3D segement.
 * \param x1
 * \brief x-coordinate of the 1st point defining the segemnt.
 * \param y1
 * \brief y-coordinate of the 1st point defining the segemnt.
 * \param z1
 * \brief z-coordinate of the 1st point defining the segemnt.
 * \param x2
 * \brief x-coordinate of the 2nd point defining the segemnt.
 * \param y2
 * \brief y-coordinate of the 2nd point defining the segemnt.
 * \param z2
 * \brief z-coordinate of the 2nd point defining the segemnt.
 * \return segement length.
 */
#if !INLINE_JBM_V3_LENGTH
JBDOUBLE jbm_v3_length(JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE z1,
	JBDOUBLE x2, JBDOUBLE y2, JBDOUBLE z2)
{return _jbm_v3_length(x1, y1, z1, x2, y2, z2);}
#endif

/**
 * \fn JBDOUBLE jbm_solve_cuadratic_reduced(JBDOUBLE a, JBDOUBLE b, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to calculate the solution of a reduced cuadratic equation in
 *   an interval.
 * \param a
 * \brief 1st order coefficient of the equation.
 * \param b
 * \brief 0th order coefficient of the equation.
 * \param x1
 * \brief left limit of the solution interval.
 * \param x2
 * \brief right limit of the solution interval.
 * \return solution value.
 */
#if !INLINE_JBM_SOLVE_CUADRATIC_REDUCED
JBDOUBLE jbm_solve_cuadratic_reduced
	(JBDOUBLE a, JBDOUBLE b, JBDOUBLE x1, JBDOUBLE x2)
{return _jbm_solve_cuadratic_reduced(a, b, x1, x2);}
#endif

/**
 * \fn JBDOUBLE jbm_solve_cuadratic(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to calculate the solution of a cuadratic equation in an
 *   interval.
 * \param a
 * \brief 2nd order coefficient of the equation.
 * \param b
 * \brief 1st order coefficient of the equation.
 * \param c
 * \brief 0th order coefficient of the equation.
 * \param x1
 * \brief left limit of the solution interval.
 * \param x2
 * \brief right limit of the solution interval.
 * \return solution value.
 */
#if !INLINE_JBM_SOLVE_CUADRATIC
JBDOUBLE jbm_solve_cuadratic
	(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, JBDOUBLE x1, JBDOUBLE x2)
{return _jbm_solve_cuadratic(a, b, c, x1, x2);}
#endif

/**
 * \fn JBDOUBLE jbm_solve_cubic_reduced(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to calculate the solution of a reduced cubic equation in an
 *   interval.
 * \param a
 * \brief 2nd order coefficient of the equation.
 * \param b
 * \brief 1st order coefficient of the equation.
 * \param c
 * \brief 0th order coefficient of the equation.
 * \param x1
 * \brief left limit of the solution interval.
 * \param x2
 * \brief right limit of the solution interval.
 * \return solution value.
 */
#if !INLINE_JBM_SOLVE_CUBIC_REDUCED
JBDOUBLE jbm_solve_cubic_reduced
	(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, JBDOUBLE x1, JBDOUBLE x2)
{return _jbm_solve_cubic_reduced(a, b, c, x1, x2);}
#endif

/**
 * \fn JBDOUBLE jbm_solve_cubic(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, \
 *   JBDOUBLE d, JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to calculate the solution of a reduced cubic equation in an
 *   interval.
 * \param a
 * \brief 3rd order coefficient of the equation.
 * \param b
 * \brief 2nd order coefficient of the equation.
 * \param c
 * \brief 1st order coefficient of the equation.
 * \param d
 * \brief 0th order coefficient of the equation.
 * \param x1
 * \brief left limit of the solution interval.
 * \param x2
 * \brief right limit of the solution interval.
 * \return solution value.
 */
#if !INLINE_JBM_SOLVE_CUBIC
JBDOUBLE jbm_solve_cubic(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c,
	JBDOUBLE d, JBDOUBLE x1, JBDOUBLE x2)
{return _jbm_solve_cubic(a, b, c, d, x1, x2);}
#endif

/**
 * \fn void jbm_index_sort_insertion(JBFLOAT *x, int *ni, int n)
 * \brief Function to sort from the highest to the lowest the indexes of an
 *   array of JBFLOAT numbers by the insertion method.
 * \param x
 * \brief array of JBFLOAT numbers.
 * \param ni
 * \brief array of indexes.
 * \param n
 * \brief the highest element number of the arrays.
 */
#if !INLINE_JBM_INDEX_SORT_INSERTION
void jbm_index_sort_insertion(JBFLOAT *x, int *ni, int n)
{_jbm_index_sort_insertion(x, ni, n);}
#endif

/**
 * \fn void jbm_index_sort_interchange(JBFLOAT *x, int *ni, int n)
 * \brief Function to sort from the highest to the lowest the indexes of an
 *   array of JBFLOAT numbers by the interchange method.
 * \param x
 * \brief array of JBFLOAT numbers.
 * \param ni
 * \brief array of indexes.
 * \param n
 * \brief the highest element number of the arrays.
 */
#if !INLINE_JBM_INDEX_SORT_INTERCHANGE
void jbm_index_sort_interchange(JBFLOAT *x, int *ni, int n)
{_jbm_index_sort_interchange(x, ni, n);}
#endif

/**
 * \fn void jbm_index_sort_merge(JBFLOAT *x, int *ni, int n)
 * \brief Function to sort from the highest to the lowest the indexes of an
 *   array of JBFLOAT numbers by the merge method.
 * \param x
 * \brief array of JBFLOAT numbers.
 * \param ni
 * \brief array of indexes.
 * \param n
 * \brief the highest element number of the arrays.
 */
#if !INLINE_JBM_INDEX_SORT_MERGE
void jbm_index_sort_merge(JBFLOAT *x, int *ni, int n)
{_jbm_index_sort_merge(x, ni, n);}
#endif

#if JBM_INDEX_SORT_FLASH
/**
 * \fn void jbm_index_sort_flash(JBFLOAT *x, int *ni, int n)
 * \brief Function to sort from the highest to the lowest the indexes of an
 *   array of JBFLOAT numbers by the flash method.
 * \param x
 * \brief array of JBFLOAT numbers.
 * \param ni
 * \brief array of indexes.
 * \param n
 * \brief the highest element number of the arrays.
 */
void jbm_index_sort_flash(JBFLOAT *x, int *ni, int n)
{
	register int i, j, m = n / 32 + 1;
	int *nj, *nk, *l1, *l2;
	register JBDOUBLE xi, xmin, xmax;
	#if DEBUG_JBM_INDEX_SORT_FLASH
		fprintf(stderr, "JBM index flash sort\n");
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isf i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
		fprintf(stderr, "JBM isf m=%d\n", m);
	#endif
	nj = (int*)g_malloc((n + m + 2) * 2 * sizeof(int));
	nk =nj + n + 1;
	l1 =nk + n + 1;
	l2 =l1 + m + 1;
	j = i = n;
	xmax = xmin = x[ni[i]];
	while (--i >= 0)
	{
		xi = x[ni[i]];
		if (xi > xmax) xmax = xi, j = i; else if (xi < xmin) xmin = xi;
	}
	if (xmax == xmin) goto sorted;
	jbm_change(ni, ni + j);
	#if DEBUG_JBM_INDEX_SORT_FLASH
		fprintf(stderr, "JBM isf xmin="FWL" xmax="FWL"\n", xmin, xmax);
	#endif
	i = m;
	l1[i] = 1;
	while (--i >= 0) l1[i] = 0;
	for (i = n + 1; --i > 0;)
	{
		j = floor(m * (x[ni[i]] - xmin) / (xmax - xmin));
		nj[i] = j;
		++l1[j];
	}
	nj[0] = m;
	#if DEBUG_JBM_INDEX_SORT_FLASH
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isf i=%d nj=%d\n", i, nj[i]);
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isf i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
	#endif
	for (i = m, l2[i] = l1[i]; --i >= 0;) l2[i] = l2[i + 1] + l1[i];
	#if DEBUG_JBM_INDEX_SORT_FLASH
		for (i = 0; i <= m; ++i)
			fprintf(stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
	#endif
	for (i = n + 1; --i > 0;) nk[--l2[nj[i]]] = ni[i];
	#if DEBUG_JBM_INDEX_SORT_FLASH
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isf i=%d nk=%d\n", i, nk[i]);
	#endif
	for (i = n + 1; --i > 0;) ni[i] = nk[i];
	#if DEBUG_JBM_INDEX_SORT_FLASH
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isf i=%d ni=%d\n", i, ni[i]);
	#endif
	--l2[m];
	#if DEBUG_JBM_INDEX_SORT_FLASH
		for (i = 0; i <= m; ++i)
			fprintf(stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
	#endif
	i = m;
	do
	{
		#if DEBUG_JBM_INDEX_SORT_FLASH
			fprintf(stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
		#endif
		j = l1[i] - 1;
		nk = ni + l2[i];
		if (j < JBM_INDEX_SORT_FLASH_MIN) jbm_index_sort_insertion(x, nk, j);
		else jbm_index_sort_flash(x, nk, j);
		#if DEBUG_JBM_INDEX_SORT_FLASH
			fprintf(stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
		#endif
	}
	while (--i >= 0);
sorted:
	g_free(nj);
	#if DEBUG_JBM_INDEX_SORT_FLASH
		for (i = 0; i <= n; ++i)
			fprintf(stderr, "JBM isf i=%d x="FWF" ni=%d\n", i, x[ni[i]], ni[i]);
		fprintf(stderr, "JBM index flash sort exit\n");
	#endif
	return;
}
#endif

/**
 * \fn void jbm_index_sort(JBFLOAT *x, int *ni, int n)
 * \brief Function to sort from the highest to the lowest the indexes of an
 *   array of JBFLOAT numbers by the optime method.
 * \param x
 * \brief array of JBFLOAT numbers.
 * \param ni
 * \brief array of indexes.
 * \param n
 * \brief the highest element number of the arrays.
 */
#if !INLINE_JBM_INDEX_SORT
void jbm_index_sort(JBFLOAT *x, int *ni, int n) {_jbm_index_sort(x, ni, n);}
#endif

#if !INLINE_JBM_INDEX_SORT_EXTENDED
int jbm_index_sort_extended(JBFLOAT *x, JBFLOAT **xr, int **ni, int n)
{return _jbm_index_sort_extended(x, xr, ni, n);}
#endif

#if !INLINE_JBM_SOLVE_MATRIX
void jbm_solve_matrix(JBFLOAT *x, int n) {_jbm_solve_matrix(x, n);}
#endif

#if !INLINE_JBM_SOLVE_TRIDIAGONAL_MATRIX
void jbm_solve_tridiagonal_matrix
	(JBFLOAT *C, JBFLOAT *D, JBFLOAT *E, JBFLOAT *iu, int n)
{_jbm_solve_tridiagonal_matrix(C, D, E, iu, n);}
#endif

#if !INLINE_JBM_SOLVE_TRIDIAGONAL_MATRIX_ZERO
void jbm_solve_tridiagonal_matrix_zero
	(JBFLOAT *C, JBFLOAT *D, JBFLOAT *E, JBFLOAT *iu, int n)
{_jbm_solve_tridiagonal_matrix_zero(C, D, E, iu, n);}
#endif

#if !INLINE_JBM_SOLVE_PENTADIAGONAL_MATRIX
void jbm_solve_pentadiagonal_matrix
	(JBFLOAT *B, JBFLOAT *C, JBFLOAT *D, JBFLOAT *E, JBFLOAT *F, JBFLOAT *iu, int n)
{_jbm_solve_pentadiagonal_matrix(B, C, D, E, F, iu, n);}
#endif

#if !INLINE_JBM_SOLVE_TRIDIAGONAL_VARRAY
void jbm_solve_tridiagonal_varray(void *v, int size, int n)
{_jbm_solve_tridiagonal_varray(v, size, n);}
#endif

#if !INLINE_JBM_SOLVE_TRIDIAGONAL_VARRAY_ZERO
void jbm_solve_tridiagonal_varray_zero(void *v, int size, int n)
{_jbm_solve_tridiagonal_varray_zero(v, size, n);}
#endif

#if !INLINE_JBM_REGRESSION
void jbm_regression(JBFLOAT *x, JBFLOAT *y, int n, JBFLOAT **A, int m)
{_jbm_regression(x, y, n, A, m);}
#endif

#if !INLINE_JBM_SPLINE_CUBIC
void jbm_spline_cubic
	(JBFLOAT *x, JBFLOAT *y, int n, JBFLOAT **b, JBFLOAT **c, JBFLOAT **d)
{_jbm_spline_cubic(x, y, n, b, c, d);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_SUPERBEE
JBDOUBLE jbm_flux_limiter_superbee(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_superbee(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_VANLEER
JBDOUBLE jbm_flux_limiter_VanLeer(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_VanLeer(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_VANALBADA
JBDOUBLE jbm_flux_limiter_VanAlbada(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_VanAlbada(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_MINMOD
JBDOUBLE jbm_flux_limiter_minmod(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_minmod(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_SUPERMIN
JBDOUBLE jbm_flux_limiter_supermin(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_supermin(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_MINSUPER
JBDOUBLE jbm_flux_limiter_minsuper(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_minsuper(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_NULL
JBDOUBLE jbm_flux_limiter_null(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_null(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_CENTERED
JBDOUBLE jbm_flux_limiter_centered(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_centered(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_TOTAL
JBDOUBLE jbm_flux_limiter_total(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_total(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_BURGUETE
JBDOUBLE jbm_flux_limiter_Burguete(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_Burguete(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_MEAN
JBDOUBLE jbm_flux_limiter_mean(JBDOUBLE d1, JBDOUBLE d2)
{return _jbm_flux_limiter_mean(d1, d2);}
#endif

#if !INLINE_JBM_FLUX_LIMITER_SELECT
JBDOUBLE(*jbm_flux_limiter_select(int type))(JBDOUBLE, JBDOUBLE)
{return _jbm_flux_limiter_select(type);}
#endif

#if !INLINE_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
void jbm_transversal_section_regions_sort
	(int i, int *nj, int *nk, JBFLOAT *l, JBFLOAT *z, JBFLOAT *x, JBFLOAT *zz, int *nx)
{_jbm_transversal_section_regions_sort(i, nj, nk, l, z, x, zz, nx);}
#endif

#if !INLINE_JBM_TRANSVERSAL_SECTION_REGIONS
int jbm_transversal_section_regions(JBFLOAT *l, JBFLOAT *z, int n,
	JBFLOAT **zz, int **ni, int **nj, int **nij, int *nmin)
{return _jbm_transversal_section_regions(l, z, n, zz, ni, nj, nij, nmin);}
#endif

#if !INLINE_JBM_REGRESSION_LINEAR
void jbm_regression_linear(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE *a, JBDOUBLE *b)
{_jbm_regression_linear(x, y, n, a, b);}
#endif

#if !INLINE_JBM_REGRESSION_EXPONENTIAL
void jbm_regression_exponential(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE *a, JBDOUBLE *b)
{_jbm_regression_exponential(x, y, n, a, b);}
#endif

#if !INLINE_JBM_REGRESSION_MULTILINEAR
void jbm_regression_multilinear(JBFLOAT **x, int n, JBFLOAT *a, int m)
{_jbm_regression_multilinear(x, n, a, m);}
#endif

#if !INLINE_JBM_VARRAY_SEARCH
int jbm_varray_search(JBDOUBLE x, void *v, int size, int n)
{return _jbm_varray_search(x, v, size, n);}
#endif

#if !INLINE_JBM_VARRAY_SEARCH_EXTENDED
int jbm_varray_search_extended(JBDOUBLE x, void *v, int size, int n)
{return _jbm_varray_search_extended(x, v, size, n);}
#endif

#if !INLINE_JBM_VARRAY_MAX
JBDOUBLE jbm_varray_max(void *va, int size, int n)
{return _jbm_varray_max(va, size, n);}
#endif

#if !INLINE_JBM_VARRAY_MIN
JBDOUBLE jbm_varray_min(void *va, int size, int n)
{return _jbm_varray_min(va, size, n);}
#endif

#if !INLINE_JBM_VARRAY_MAXMIN
void jbm_varray_maxmin(void *va, int size, int n, JBDOUBLE *max, JBDOUBLE *min)
{_jbm_varray_maxmin(va, size, n, max, min);}
#endif

#if !INLINE_JBM_VARRAY_MEAN_SQUARE_ERROR
JBDOUBLE jbm_varray_mean_square_error
	(void *xa, void *fa, int sizea, int na, void *xr, void *fr, int sizer, int nr)
{return _jbm_varray_mean_square_error(xa, fa, sizea, na, xr, fr, sizer, nr);}
#endif

#if !INLINE_JBM_FILE_MEAN_SQUARE_ERROR
JBDOUBLE jbm_file_mean_square_error
	(char *namea, int ixa, int ifa, int na, char *namer, int ixr, int ifr, int nr)
{return _jbm_file_mean_square_error(namea, ixa, ifa, na, namer, ixr, ifr, nr);}
#endif

