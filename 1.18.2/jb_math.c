/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2018, Javier Burguete Tolosa.
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
 * \copyright Copyright 2005-2018, Javier Burguete Tolosa.
 */
#include "jb_math.h"

/**
 * \fn int jbm_fcompare(JBDOUBLE a, JBDOUBLE b)
 * \brief Function to compare 2 float numbers.
 * \param a
 * \brief 1st JBDOUBLE number.
 * \param b
 * \brief 2nd JBDOUBLE number.
 * \return a!=b on Unix systems, on Microsoft Windows systems 0 if the
 *   difference is lower than the 6th digit else -1 if a < b and 1 if a > b
 */
#if !INLINE_JBM_FCOMPARE
int
jbm_fcompare (JBDOUBLE a, JBDOUBLE b)
{
  return _jbm_fcompare (a, b);
}
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
int
jbm_max (int a, int b)
{
  return _jbm_max (a, b);
}
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
int
jbm_min (int a, int b)
{
  return _jbm_min (a, b);
}
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
long int
jbm_maxl (long int a, long int b)
{
  return _jbm_maxl (a, b);
}
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
long int
jbm_minl (long int a, long int b)
{
  return _jbm_minl (a, b);
}
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
long long int
jbm_maxll (long long int a, long long int b)
{
  return _jbm_maxll (a, b);
}
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
long long int
jbm_minll (long long int a, long long int b)
{
  return _jbm_minll (a, b);
}
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
int
jbm_modmin (int a, int b)
{
  return _jbm_modmin (a, b);
}
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
long int
jbm_modminl (long int a, long int b)
{
  return _jbm_modminl (a, b);
}
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
long long int
jbm_modminll (long long int a, long long int b)
{
  return _jbm_modminll (a, b);
}
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
JBDOUBLE
jbm_fmodmin (JBDOUBLE a, JBDOUBLE b)
{
  return _jbm_fmodmin (a, b);
}
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
void
jbm_change (int *a, int *b)
{
  _jbm_change (a, b);
}
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
void
jbm_changel (long int *a, long int *b)
{
  _jbm_changel (a, b);
}
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
void
jbm_changell (long long int *a, long long int *b)
{
  _jbm_changell (a, b);
}
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
void
jbm_fchange (JBFLOAT * a, JBFLOAT * b)
{
  _jbm_fchange (a, b);
}
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
void
jbm_fchangel (JBDOUBLE * a, JBDOUBLE * b)
{
  _jbm_fchangel (a, b);
}
#endif

/**
 * \fn int jbm_sqr(int x)
 * \brief Function to calculate the square of an int number.
 * \param x
 * \brief int number.
 * \return square.
 */
#if !INLINE_JBM_SQR
int
jbm_sqr (int x)
{
  return _jbm_sqr (x);
}
#endif

/**
 * \fn long int jbm_sqrl(long int x)
 * \brief Function to calculate the square of a long int number.
 * \param x
 * \brief long int number.
 * \return square.
 */
#if !INLINE_JBM_SQRL
long int
jbm_sqrl (long int x)
{
  return _jbm_sqrl (x);
}
#endif

/**
 * \fn long long int jbm_sqrll(long long int x)
 * \brief Function to calculate the square of a long long int number.
 * \param x
 * \brief long long int number.
 * \return square.
 */
#if !INLINE_JBM_SQRLL
long long int
jbm_sqrll (long long int x)
{
  return _jbm_sqrll (x);
}
#endif

/**
 * \fn JBDOUBLE jbm_fsqr(JBDOUBLE x)
 * \brief Function to calculate the square of a JBDOUBLE number.
 * \param x
 * \brief JBDOUBLE number.
 * \return square.
 */
#if !INLINE_JBM_FSQR
JBDOUBLE
jbm_fsqr (JBDOUBLE x)
{
  return _jbm_fsqr (x);
}
#endif

/**
 * \fn int jbm_dbl(int x)
 * \brief Function to calculate the double of an int number.
 * \param x
 * \brief int number.
 * \return double.
 */
#if !INLINE_JBM_DBL
int
jbm_dbl (int x)
{
  return _jbm_dbl (x);
}
#endif

/**
 * \fn long int jbm_dbll(long int x)
 * \brief Function to calculate the double of a long int number.
 * \param x
 * \brief long int number.
 * \return double.
 */
#if !INLINE_JBM_DBLL
long int
jbm_dbll (long int x)
{
  return _jbm_dbll (x);
}
#endif

/**
 * \fn long long int jbm_dblll(long long int x)
 * \brief Function to calculate the double of a long long int number.
 * \param x
 * \brief long long int number.
 * \return double.
 */
#if !INLINE_JBM_DBLLL
long long int
jbm_dblll (long long int x)
{
  return _jbm_dblll (x);
}
#endif

/**
 * \fn JBDOUBLE jbm_fdbl(JBDOUBLE x)
 * \brief Function to calculate the double of a JBDOUBLE number.
 * \param x
 * \brief JBDOUBLE number.
 * \return double.
 */
#if !INLINE_JBM_FDBL
JBDOUBLE
jbm_fdbl (JBDOUBLE x)
{
  return _jbm_fdbl (x);
}
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
{
  return _jbm_extrapolate (x, x1, x2, y1, y2);
}
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
{
  return _jbm_interpolate (x, x1, x2, y1, y2);
}
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
JBDOUBLE
jbm_integral (JBDOUBLE (*f) (JBDOUBLE), JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_integral (f, x1, x2);
}
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
int
jbm_farray_search (JBDOUBLE x, JBFLOAT * fa, int n)
{
  return _jbm_farray_search (x, fa, n);
}
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
int
jbm_farray_search_extended (JBDOUBLE x, JBFLOAT * fa, int n)
{
  return _jbm_farray_search_extended (x, fa, n);
}
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
JBDOUBLE
jbm_farray_max (JBFLOAT * fa, int n)
{
  return _jbm_farray_max (fa, n);
}
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
JBDOUBLE
jbm_farray_min (JBFLOAT * fa, int n)
{
  return _jbm_farray_min (fa, n);
}
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
void
jbm_farray_maxmin (JBFLOAT * fa, int n, JBDOUBLE * max, JBDOUBLE * min)
{
  _jbm_farray_maxmin (fa, n, max, min);
}
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
JBDOUBLE
jbm_farray_interpolate (JBDOUBLE x, JBFLOAT * fa, JBFLOAT * fb, int n)
{
  return _jbm_farray_interpolate (x, fa, fb, n);
}
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
JBFLOAT *jbm_farray_add
    (JBFLOAT * fa, int na, JBFLOAT * fb, int nb, JBFLOAT ** fc, int *nc)
{
  return _jbm_farray_add (fa, na, fb, nb, fc, nc);
}
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
    (JBFLOAT * x, JBFLOAT * y, int n, JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_farray_integral (x, y, n, x1, x2);
}
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
    (JBFLOAT * xa, JBFLOAT * fa, int na, JBFLOAT * xr, JBFLOAT * fr, int nr)
{
  return _jbm_farray_mean_square_error (xa, fa, na, xr, fr, nr);
}
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
    (JBFLOAT * xa, JBFLOAT * fa, int na, JBFLOAT * xr, JBFLOAT * fr, int nr)
{
  return _jbm_farray_root_mean_square_error (xa, fa, na, xr, fr, nr);
}
#endif

/**
 * \fn int jbm_darray_search(JBDOUBLE x, JBDOUBLE *fa, int n)
 * \brief Function to search the interval where a number is in a increasingly
 *   sorted array of JBDOUBLE numbers.
 * \param x
 * \brief number.
 * \param fa
 * \brief array of JBDOUBLE numbers.
 * \param n
 * \brief number of the highest array element.
 * \return interval number.
 */
#if !INLINE_JBM_DARRAY_SEARCH
int
jbm_darray_search (JBDOUBLE x, JBDOUBLE * fa, int n)
{
  return _jbm_darray_search (x, fa, n);
}
#endif

/**
 * \fn int jbm_darray_search_extended(JBDOUBLE x, JBDOUBLE *fa, int n)
 * \brief Function to search the interval where a number is in a increasingly
 *   sorted array of JBDOUBLE numbers.
 * \param x
 * \brief number.
 * \param fa
 * \brief array of JBDOUBLE numbers.
 * \param n
 * \brief number of the highest array element.
 * \return interval number, -1 if x<fa[0] or n if x>fa[n].
 */
#if !INLINE_JBM_DARRAY_SEARCH_EXTENDED
int
jbm_darray_search_extended (JBDOUBLE x, JBDOUBLE * fa, int n)
{
  return _jbm_darray_search_extended (x, fa, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_max(JBDOUBLE *fa, int n)
 * \brief Function to find the highest element of an array of JBDOUBLE numbers.
 * \param fa
 * \brief array of JBDOUBLE numbers.
 * \param n
 * \brief number of the ending array element.
 * \return the highest value.
 */
#if !INLINE_JBM_DARRAY_MAX
JBDOUBLE
jbm_darray_max (JBDOUBLE * fa, int n)
{
  return _jbm_darray_max (fa, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_min(JBDOUBLE *fa, int n)
 * \brief Function to find the lowest element of an array of JBDOUBLE numbers.
 * \param fa
 * \brief array of JBDOUBLE numbers.
 * \param n
 * \brief number of the ending array element.
 * \return the lowest value.
 */
#if !INLINE_JBM_DARRAY_MIN
JBDOUBLE
jbm_darray_min (JBDOUBLE * fa, int n)
{
  return _jbm_darray_min (fa, n);
}
#endif

/**
 * \fn void jbm_darray_maxmin(JBDOUBLE *fa, int n, JBDOUBLE *max, JBDOUBLE *min)
 * \brief Function to find the highest and the lowest elements of an array of
 *   JBDOUBLE numbers.
 * \param fa
 * \brief array of JBDOUBLE numbers.
 * \param n
 * \brief number of the ending array element.
 * \param max
 * \brief the highest value.
 * \param min
 * \brief the lowest value.
 */
#if !INLINE_JBM_DARRAY_MAXMIN
void
jbm_darray_maxmin (JBDOUBLE * fa, int n, JBDOUBLE * max, JBDOUBLE * min)
{
  _jbm_darray_maxmin (fa, n, max, min);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_farray_interpolate(JBDOUBLE x, JBDOUBLE *fa, \
 *   JBFLOAT *fb, int n)
 * \brief Function to calculate the y-coordinate of a 2D point interpolated
 *   between a tabular function defined by 2 arrays of JBDOUBLE numbers.
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
#if !INLINE_JBM_DARRAY_FARRAY_INTERPOLATE
JBDOUBLE jbm_darray_farray_interpolate
    (JBDOUBLE x, JBDOUBLE * fa, JBFLOAT * fb, int n)
{
  return _jbm_darray_farray_interpolate (x, fa, fb, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_interpolate(JBDOUBLE x, JBDOUBLE *fa, JBDOUBLE *fb, \
 *   int n)
 * \brief Function to calculate the y-coordinate of a 2D point interpolated
 *   between a tabular function defined by 2 arrays of JBDOUBLE numbers.
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
#if !INLINE_JBM_DARRAY_INTERPOLATE
JBDOUBLE
jbm_darray_interpolate (JBDOUBLE x, JBDOUBLE * fa, JBDOUBLE * fb, int n)
{
  return _jbm_darray_interpolate (x, fa, fb, n);
}
#endif

/**
 * \fn JBDOUBLE* jbm_darray_add(JBDOUBLE *fa, int na, JBDOUBLE *fb, int nb, \
 *   JBDOUBLE **fc, int *nc)
 * \brief Function to add 2 increasingly sorted arrays of JBDOUBLE numbers.
 * \param fa
 * \brief 1st increasingly sorted array of JBDOUBLE numbers.
 * \param na
 * \brief the highest element number of the 1st array.
 * \param fb
 * \brief 2nd increasingly sorted array of JBDOUBLE numbers.
 * \param nb
 * \brief the highest element number of the 2nd array.
 * \param fc
 * \brief pointer to the resulting increasingly sorted array of JBDOUBLE
 *   numbers.
 * \param nc
 * \brief pointer to the highest element number of the resulting array.
 * \return resulting array.
 */
#if !INLINE_JBM_DARRAY_ADD
JBDOUBLE *jbm_darray_add
    (JBDOUBLE * fa, int na, JBDOUBLE * fb, int nb, JBDOUBLE ** fc, int *nc)
{
  return _jbm_darray_add (fa, na, fb, nb, fc, nc);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_farray_integral(JBDOUBLE *x, JBFLOAT *y, int n, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to integrate a tabular function in an interval.
 * \param x
 * \brief incresingly sorted array of JBDOUBLE numbers defining the
 *   x-coordinates of the tabular function.
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
#if !INLINE_JBM_DARRAY_FARRAY_INTEGRAL
JBDOUBLE jbm_darray_farray_integral
    (JBDOUBLE * x, JBFARRAY * y, int n, JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_darray_integral (x, y, n, x1, x2);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_integral(JBDOUBLE *x, JBDOUBLE *y, int n, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to integrate a tabular function in an interval.
 * \param x
 * \brief incresingly sorted array of JBDOUBLE numbers defining the
 *   x-coordinates of the tabular function.
 * \param y
 * \brief array of JBDOUBLE numbers defining the y-coordinates of the tabular
 *   function.
 * \param n
 * \brief the highest element number of the arrays.
 * \param x1
 * \brief left limit of the integration interval.
 * \param x2
 * \brief right limit of the integration interval.
 * \return integral value.
 */
#if !INLINE_JBM_DARRAY_INTEGRAL
JBDOUBLE jbm_darray_integral
    (JBDOUBLE * x, JBDOUBLE * y, int n, JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_darray_integral (x, y, n, x1, x2);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_mean_square_error(JBDOUBLE *xa, JBDOUBLE *fa, int na, \
 *   JBDOUBLE *xr, JBDOUBLE *fr, int nr)
 * \brief Function to calculate the mean square error between 2 tabular
 *   functions.
 * \param xa
 * \brief incresingly sorted array of JBDOUBLE numbers defining the
 *   x-coordinates of the 1st tabular function.
 * \param fa
 * \brief array of JBDOUBLE numbers defining the y-coordinates of the 1st
 *   tabular function.
 * \param na
 * \brief the highest element number of the arrays defining the 1st tabular
 *   function.
 * \param xr
 * \brief incresingly sorted array of JBDOUBLE numbers defining the
 *   x-coordinates of the 2nd tabular function.
 * \param fr
 * \brief array of JBDOUBLE numbers defining the y-coordinates of the 2nd
 *   tabular function.
 * \param nr
 * \brief the highest element number of the arrays defining the 2nd tabular
 *   function.
 * \return mean square error.
 */
#if !INLINE_JBM_DARRAY_MEAN_SQUARE_ERROR
JBDOUBLE jbm_darray_mean_square_error
    (JBDOUBLE * xa, JBDOUBLE * fa, int na, JBDOUBLE * xr, JBDOUBLE * fr, int nr)
{
  return _jbm_darray_mean_square_error (xa, fa, na, xr, fr, nr);
}
#endif

/**
 * \fn JBDOUBLE jbm_darray_root_mean_square_error(JBDOUBLE *xa, JBDOUBLE *fa, \
 *   int na, JBDOUBLE *xr, JBDOUBLE *fr, int nr)
 * \brief Function to calculate the root mean square error between 2 tabular
 *   functions.
 * \param xa
 * \brief incresingly sorted array of JBDOUBLE numbers defining the
 *   x-coordinates of the 1st tabular function.
 * \param fa
 * \brief array of JBDOUBLE numbers defining the y-coordinates of the 1st
 *   tabular function.
 * \param na
 * \brief the highest element number of the arrays defining the 1st tabular
 *   function.
 * \param xr
 * \brief incresingly sorted array of JBDOUBLE numbers defining the
 *   x-coordinates of the 2nd tabular function.
 * \param fr
 * \brief array of JBDOUBLE numbers defining the y-coordinates of the 2nd
 *   tabular function.
 * \param nr
 * \brief the highest element number of the arrays defining the 2nd tabular
 *   function.
 * \return root mean square error.
 */
#if !INLINE_JBM_DARRAY_ROOT_MEAN_SQUARE_ERROR
JBDOUBLE jbm_darray_root_mean_square_error
    (JBDOUBLE * xa, JBDOUBLE * fa, int na, JBDOUBLE * xr, JBDOUBLE * fr, int nr)
{
  return _jbm_darray_root_mean_square_error (xa, fa, na, xr, fr, nr);
}
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
JBDOUBLE
jbm_v2_length (JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE x2, JBDOUBLE y2)
{
  return _jbm_v2_length (x1, y1, x2, y2);
}
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
JBDOUBLE
jbm_v3_length (JBDOUBLE x1, JBDOUBLE y1, JBDOUBLE z1,
               JBDOUBLE x2, JBDOUBLE y2, JBDOUBLE z2)
{
  return _jbm_v3_length (x1, y1, z1, x2, y2, z2);
}
#endif

/**
 * \fn JBDOUBLE jbm_solve_quadratic_reduced(JBDOUBLE a, JBDOUBLE b, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to calculate the solution of a reduced quadratic equation in
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
#if !INLINE_JBM_SOLVE_QUADRATIC_REDUCED
JBDOUBLE jbm_solve_quadratic_reduced
    (JBDOUBLE a, JBDOUBLE b, JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_solve_quadratic_reduced (a, b, x1, x2);
}
#endif

/**
 * \fn JBDOUBLE jbm_solve_quadratic(JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, \
 *   JBDOUBLE x1, JBDOUBLE x2)
 * \brief Function to calculate the solution of a quadratic equation in an
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
#if !INLINE_JBM_SOLVE_QUADRATIC
JBDOUBLE jbm_solve_quadratic
    (JBDOUBLE a, JBDOUBLE b, JBDOUBLE c, JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_solve_quadratic (a, b, c, x1, x2);
}
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
{
  return _jbm_solve_cubic_reduced (a, b, c, x1, x2);
}
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
JBDOUBLE
jbm_solve_cubic (JBDOUBLE a, JBDOUBLE b, JBDOUBLE c,
                 JBDOUBLE d, JBDOUBLE x1, JBDOUBLE x2)
{
  return _jbm_solve_cubic (a, b, c, d, x1, x2);
}
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
void
jbm_index_sort_insertion (JBFLOAT * x, int *ni, int n)
{
  _jbm_index_sort_insertion (x, ni, n);
}
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
void
jbm_index_sort_interchange (JBFLOAT * x, int *ni, int n)
{
  _jbm_index_sort_interchange (x, ni, n);
}
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
void
jbm_index_sort_merge (JBFLOAT * x, int *ni, int n)
{
  _jbm_index_sort_merge (x, ni, n);
}
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
void
jbm_index_sort_flash (JBFLOAT * x, int *ni, int n)
{
  register int i, j, m = n / 32 + 1;
  int *nj, *nk, *l1, *l2;
  register JBDOUBLE xi, xmin, xmax;
#if DEBUG_JBM_INDEX_SORT_FLASH
  fprintf (stderr, "JBM index flash sort\n");
  for (i = 0; i <= n; ++i)
    fprintf (stderr, "JBM isf i=%d x=" FWF " ni=%d\n", i, x[ni[i]], ni[i]);
  fprintf (stderr, "JBM isf m=%d\n", m);
#endif
  nj = (int *) g_malloc ((n + m + 2) * 2 * sizeof (int));
  nk = nj + n + 1;
  l1 = nk + n + 1;
  l2 = l1 + m + 1;
  j = i = n;
  xmax = xmin = x[ni[i]];
  while (--i >= 0)
    {
      xi = x[ni[i]];
      if (xi > xmax)
        xmax = xi, j = i;
      else if (xi < xmin)
        xmin = xi;
    }
  if (xmax == xmin)
    goto sorted;
  jbm_change (ni, ni + j);
#if DEBUG_JBM_INDEX_SORT_FLASH
  fprintf (stderr, "JBM isf xmin=" FWL " xmax=" FWL "\n", xmin, xmax);
#endif
  i = m;
  l1[i] = 1;
  while (--i >= 0)
    l1[i] = 0;
  for (i = n + 1; --i > 0;)
    {
      j = floor (m * (x[ni[i]] - xmin) / (xmax - xmin));
      nj[i] = j;
      ++l1[j];
    }
  nj[0] = m;
#if DEBUG_JBM_INDEX_SORT_FLASH
  for (i = 0; i <= n; ++i)
    fprintf (stderr, "JBM isf i=%d nj=%d\n", i, nj[i]);
  for (i = 0; i <= n; ++i)
    fprintf (stderr, "JBM isf i=%d x=" FWF " ni=%d\n", i, x[ni[i]], ni[i]);
#endif
  for (i = m, l2[i] = l1[i]; --i >= 0;)
    l2[i] = l2[i + 1] + l1[i];
#if DEBUG_JBM_INDEX_SORT_FLASH
  for (i = 0; i <= m; ++i)
    fprintf (stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
#endif
  for (i = n + 1; --i > 0;)
    nk[--l2[nj[i]]] = ni[i];
#if DEBUG_JBM_INDEX_SORT_FLASH
  for (i = 0; i <= n; ++i)
    fprintf (stderr, "JBM isf i=%d nk=%d\n", i, nk[i]);
#endif
  for (i = n + 1; --i > 0;)
    ni[i] = nk[i];
#if DEBUG_JBM_INDEX_SORT_FLASH
  for (i = 0; i <= n; ++i)
    fprintf (stderr, "JBM isf i=%d ni=%d\n", i, ni[i]);
#endif
  --l2[m];
#if DEBUG_JBM_INDEX_SORT_FLASH
  for (i = 0; i <= m; ++i)
    fprintf (stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
#endif
  i = m;
  do
    {
#if DEBUG_JBM_INDEX_SORT_FLASH
      fprintf (stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
#endif
      j = l1[i] - 1;
      nk = ni + l2[i];
      if (j < JBM_INDEX_SORT_FLASH_MIN)
        jbm_index_sort_insertion (x, nk, j);
      else
        jbm_index_sort_flash (x, nk, j);
#if DEBUG_JBM_INDEX_SORT_FLASH
      fprintf (stderr, "JBM isf i=%d l1=%d l2=%d\n", i, l1[i], l2[i]);
#endif
    }
  while (--i >= 0);
sorted:
  g_free (nj);
#if DEBUG_JBM_INDEX_SORT_FLASH
  for (i = 0; i <= n; ++i)
    fprintf (stderr, "JBM isf i=%d x=" FWF " ni=%d\n", i, x[ni[i]], ni[i]);
  fprintf (stderr, "JBM index flash sort exit\n");
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
void
jbm_index_sort (JBFLOAT * x, int *ni, int n)
{
  _jbm_index_sort (x, ni, n);
}
#endif

/**
 * \fn int jbm_index_sort_extended(JBFLOAT *x, JBFLOAT **xr, int **ni, int n)
 * \brief Function to create a sorted index from the highest to the lowest of an
 *   array of JBFLOAT numbers by the optime method.
 * \param x
 * \brief array of JBFLOAT numbers to sort.
 * \param xr
 * \brief pointer to the array of sorted JBFLOAT numbers elliminating duplicated
 *   numbers.
 * \param ni
 * \brief point to the array of sorted indexes.
 * \param n
 * \brief the highest element number of the array to sort.
 * \return the highest element number of the sorted array.
 */
#if !INLINE_JBM_INDEX_SORT_EXTENDED
int
jbm_index_sort_extended (JBFLOAT * x, JBFLOAT ** xr, int **ni, int n)
{
  return _jbm_index_sort_extended (x, xr, ni, n);
}
#endif

/**
 * \fn void jbm_matrix_solve(JBFLOAT *x, int n)
 * \brief Function to solve a linear equations system stored in a matrix with
 *   format: \f$\left(\begin{array}{cccc|c}
 *   x_{0,0} & x_{0,1} & \cdots & x_{0,n-1} & x_{0,n}\\
 *   x_{1,0} & x_{1,1} & \cdots & x_{1,n-1} & x_{1,n}\\
 *   & & \cdots \\
 *   x_{n-1,0} & x_{n-1,1} & \cdots & x_{n-1,n-1} & x_{n-1,n}
 *   \end{array}\right)\f$.
 *   Results are stored in the n+1-th column:
 *   \f$\left(x_{0,n},\;x_{1,n},\;\cdots,\;x_{n-1,n}\right)\f$.
 *   It modifies the x matrix.
 * \param x
 * \brief matrix storing the linear equations system.
 * \param n
 * \brief number of matrix rows.
 */
#if !INLINE_JBM_MATRIX_SOLVE
void
jbm_matrix_solve (JBFLOAT * x, int n)
{
  _jbm_matrix_solve (x, n);
}
#endif

/**
 * \fn void jbm_matrix_solve_tridiagonal(JBFLOAT *C, JBFLOAT *D, JBFLOAT *E, \
 *   JBFLOAT *H, int n)
 * \brief Function to solve a linear equations system stored in a tridiagonal
 *   matrix with format: \f$\left(\begin{array}{cccc|c}
 *   D_0 & E_0    &         &         & H_0\\
 *   C_0 & D_1    & E_1     &         & H_1\\
 *       & \ddots & \ddots  & \ddots  & \vdots\\
 *       &        & C_{n-2} & D_{n-1} & H_{n-1}
 *   \end{array}\right)\f$.
 *   Results are stored in the H array. It modifies D and H arrays.
 * \param C
 * \brief left diagonal array.
 * \param D
 * \brief central diagonal array.
 * \param E
 * \brief right diagonal array.
 * \param H
 * \brief final column array.
 * \param n
 * \brief number of matrix rows.
 */
#if !INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL
void jbm_matrix_solve_tridiagonal
    (JBFLOAT * C, JBFLOAT * D, JBFLOAT * E, JBFLOAT * H, int n)
{
  _jbm_matrix_solve_tridiagonal (C, D, E, H, n);
}
#endif

/**
 * \fn void jbm_matrix_solve_tridiagonal_zero(JBFLOAT *C, JBFLOAT *D, \
 *   JBFLOAT *E, JBFLOAT *H, int n)
 * \brief Function to solve a linear equations system stored in a tridiagonal
 *   matrix with format: \f$\left(\begin{array}{cccc|c}
 *   D_0 & E_0    &         &         & H_0\\
 *   C_0 & D_1    & E_1     &         & H_1\\
 *       & \ddots & \ddots  & \ddots  & \vdots\\
 *       &        & C_{n-2} & D_{n-1} & H_{n-1}
 *   \end{array}\right)\f$
 *   avoiding zero divisions. Results are stored in the H array. It modifies D
 *   and H arrays.
 * \param C
 * \brief left diagonal array.
 * \param D
 * \brief central diagonal array.
 * \param E
 * \brief right diagonal array.
 * \param H
 * \brief final column array.
 * \param n
 * \brief number of matrix rows.
 */
#if !INLINE_JBM_MATRIX_SOLVE_TRIDIAGONAL_ZERO
void jbm_matrix_solve_tridiagonal_zero
    (JBFLOAT * C, JBFLOAT * D, JBFLOAT * E, JBFLOAT * H, int n)
{
  _jbm_matrix_solve_tridiagonal_zero (C, D, E, H, n);
}
#endif

/**
 * \fn void jbm_matrix_solve_pentadiagonal(JBFLOAT *B, JBFLOAT *C, JBFLOAT *D, \
 *   JBFLOAT *E, JBFLOAT *F, JBFLOAT *H, int n)
 * \brief Function to solve a linear equations system stored in a pentadiagonal
 *   matrix with format: \f$\left(\begin{array}{cccccc|c}
 *   D_0 & E_0    & F_0     &         &         &         & H_0\\
 *   C_0 & D_1    & E_1     & F_1     &         &         & H_1\\
 *   B_0 & C_1    & D_2     & E_2     & F_2     &         & H_2\\
 *       & \ddots & \ddots  & \ddots  & \ddots  & \ddots  & \vdots\\
 *       &        &         & B_{n-3} & C_{n-2} & D_{n-1} & H_{n-1}
 *   \end{array}\right)\f$.
 *   Results are stored in the H array. It modifies C, D, E and H arrays.
 * \param B
 * \brief double-left diagonal array.
 * \param C
 * \brief left diagonal array.
 * \param D
 * \brief central diagonal array.
 * \param E
 * \brief right diagonal array.
 * \param F
 * \brief double-right diagonal array.
 * \param H
 * \brief final column array.
 * \param n
 * \brief number of matrix rows.
 */
#if !INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL
void
jbm_matrix_solve_pentadiagonal (JBFLOAT * B, JBFLOAT * C, JBFLOAT * D,
                                JBFLOAT * E, JBFLOAT * F, JBFLOAT * H, int n)
{
  _jbm_matrix_solve_pentadiagonal (B, C, D, E, F, H, n);
}
#endif

/**
 * \fn void jbm_matrix_solve_pentadiagonal_zero(JBFLOAT *B, JBFLOAT *C, \
 *   JBFLOAT *D, JBFLOAT *E, JBFLOAT *F, JBFLOAT *H, int n)
 * \brief Function to solve a linear equations system stored in a pentadiagonal
 *   matrix with format: \f$\left(\begin{array}{cccccc|c}
 *   D_0 & E_0    & F_0     &         &         &         & H_0\\
 *   C_0 & D_1    & E_1     & F_1     &         &         & H_1\\
 *   B_0 & C_1    & D_2     & E_2     & F_2     &         & H_2\\
 *       & \ddots & \ddots  & \ddots  & \ddots  & \ddots  & \vdots\\
 *       &        &         & B_{n-3} & C_{n-2} & D_{n-1} & H_{n-1}
 *   \end{array}\right)\f$
 *   avoiding zero divisions. Results are stored in the H array. It modifies C,
 *   D, E and H arrays.
 * \param B
 * \brief double-left diagonal array.
 * \param C
 * \brief left diagonal array.
 * \param D
 * \brief central diagonal array.
 * \param E
 * \brief right diagonal array.
 * \param F
 * \brief double-right diagonal array.
 * \param H
 * \brief final column array.
 * \param n
 * \brief number of matrix rows.
 */
#if !INLINE_JBM_MATRIX_SOLVE_PENTADIAGONAL_ZERO
void
jbm_matrix_solve_pentadiagonal_zero (JBFLOAT * B, JBFLOAT * C, JBFLOAT * D,
                                     JBFLOAT * E, JBFLOAT * F, JBFLOAT * H,
                                     int n)
{
  _jbm_matrix_solve_pentadiagonal_zero (B, C, D, E, F, H, n);
}
#endif

/**
 * \fn void jbm_regression(JBFLOAT *x, JBFLOAT *y, int n, JBFLOAT **A, int m)
 * \brief Function to calculate the coefficientes of a polynomial regression
 *   adjusted by minimum squares:
 *   \f$y=A_0+A_1\,x+A_2\,x^2+\cdots\f$.
 * \param x
 * \brief array of point x-coordinates.
 * \param y
 * \brief array of point y-coordinates.
 * \param n
 * \brief points number.
 * \param A
 * \brief pointer to the array of regression coefficients generated by the
 *   function calling to g_malloc.
 * \param m
 * \brief order of the polynomial regression.
 */
#if !INLINE_JBM_REGRESSION
void
jbm_regression (JBFLOAT * x, JBFLOAT * y, int n, JBFLOAT ** A, int m)
{
  _jbm_regression (x, y, n, A, m);
}
#endif

/**
 * \fn void jbm_regression_linear(JBFLOAT *x, JBFLOAT *y, int n, JBDOUBLE *a, \
 *   JBDOUBLE *b)
 * \brief Function to calculate the coefficientes of a linear regression
 *   adjusted by minimum squares:
 *   \f$y=a+b\,x\f$.
 * \param x
 * \brief array of point x-coordinates.
 * \param y
 * \brief array of point y-coordinates.
 * \param n
 * \brief points number.
 * \param a
 * \brief pointer to the 0th order regression coefficient.
 * \param b
 * \brief pointer to the 1st order regression coefficient.
 */
#if !INLINE_JBM_REGRESSION_LINEAR
void jbm_regression_linear
    (JBFLOAT * x, JBFLOAT * y, int n, JBDOUBLE * a, JBDOUBLE * b)
{
  _jbm_regression_linear (x, y, n, a, b);
}
#endif

/**
 * \fn void jbm_regression_exponential(JBFLOAT *x, JBFLOAT *y, int n, \
 *   JBDOUBLE *a, JBDOUBLE *b)
 * \brief Function to calculate the coefficientes of an exponential regression
 *   adjusted by minimum squares:
 *   \f$y=a\,x^b\f$.
 * \param x
 * \brief array of point x-coordinates. It is modified by the function.
 * \param y
 * \brief array of point y-coordinates. It is modified by the function.
 * \param n
 * \brief points number.
 * \param a
 * \brief pointer to the constant parameter regression coefficient.
 * \param b
 * \brief pointer to the exponent regression coefficient.
 */
#if !INLINE_JBM_REGRESSION_EXPONENTIAL
void jbm_regression_exponential
    (JBFLOAT * x, JBFLOAT * y, int n, JBDOUBLE * a, JBDOUBLE * b)
{
  _jbm_regression_exponential (x, y, n, a, b);
}
#endif

/**
 * \fn void jbm_regression_multilinear(JBFLOAT **x, int n, JBFLOAT *a, int m)
 * \brief Function to calculate the coefficientes of a multilinear regression
 *   adjusted by minimum squares:
 *   \f$f=a_0+a_1\,x+a_2\,y+\cdots\f$.
 * \param x
 * \brief array of point coordinates in format:
 *   \f$\left(x_1,\cdots,x_n,y_1,\cdots,y_n,\cdots,f_1,\cdots,f_n\right)\f$.
 * \param n
 * \brief points number.
 * \param a
 * \brief array of regression coefficients.
 * \param m
 * \brief number of variables.
 */
#if !INLINE_JBM_REGRESSION_MULTILINEAR
void
jbm_regression_multilinear (JBFLOAT ** x, int n, JBFLOAT * a, int m)
{
  _jbm_regression_multilinear (x, n, a, m);
}
#endif

/**
 * \fn void jbm_regression_multiexponential(JBFLOAT **x, int n, JBFLOAT *a, \
 *   int m)
 * \brief Function to calculate the coefficientes of a multiexponential
 *   regression adjusted by minimum squares:
 *   \f$f=a_0\,x^{a_1}\,y^{a_2}\cdots\f$.
 * \param x
 * \brief array of point coordinates in format:
 *   \f$\left(x_1,\cdots,x_n,y_1,\cdots,y_n,\cdots,f_1,\cdots,f_n\right)\f$.
 *   It is modified by the function.
 * \param n
 * \brief points number.
 * \param a
 * \brief array of regression coefficients.
 * \param m
 * \brief number of variables.
 */
#if !INLINE_JBM_REGRESSION_MULTIEXPONENTIAL
void
jbm_regression_multiexponential (JBFLOAT ** x, int n, JBFLOAT * a, int m)
{
  _jbm_regression_multilinear (x, n, a, m);
}
#endif

/**
 * \fn void jbm_spline_cubic(JBFLOAT *x, JBFLOAT *y, int n, JBFLOAT **b, \
 *   JBFLOAT **c, JBFLOAT **d)
 * \brief Function to calculate a cubic spline on tabular data.
 * \param x
 * \brief array of point x-coordinates.
 * \param y
 * \brief array of point y-coordinates.
 * \param n
 * \brief number of points.
 * \param b
 * \brief pointer to the array of 1st order spline coefficients. It is generated
 *   by g_malloc.
 * \param c
 * \brief pointer to the array of 2nd order spline coefficients.
 * \param d
 * \brief pointer to the array of 3rd order spline coefficients.
 */
#if !INLINE_JBM_SPLINE_CUBIC
void jbm_spline_cubic
    (JBFLOAT * x, JBFLOAT * y, int n, JBFLOAT ** b, JBFLOAT ** c, JBFLOAT ** d)
{
  _jbm_spline_cubic (x, y, n, b, c, d);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_superbee(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the superbee flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 *   \min\left(1,\,\frac{2\,d_1}{d_2}\right),\,
 *   \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_SUPERBEE
JBDOUBLE
jbm_flux_limiter_superbee (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_superbee (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_VanLeer(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the van Leer flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=
 *   \frac{\frac{d_1}{d_2}+\left|\frac{d_1}{d_2}\right|}
 *   {1+\left|\frac{d_1}{d_2}\right|}\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_VANLEER
JBDOUBLE
jbm_flux_limiter_VanLeer (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_VanLeer (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_VanAlbada(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the van Albada flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\frac{\frac{d_1}{d_2}+\frac{d_1^2}{d_2^2}}
 *   {1+\frac{d_1^2}{d_2^2}}\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_VANALBADA
JBDOUBLE
jbm_flux_limiter_VanAlbada (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_VanAlbada (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_minmod(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the minmod flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 *   \min\left(1,\,\frac{d_1}{d_2}\right)\right]\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_MINMOD
JBDOUBLE
jbm_flux_limiter_minmod (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_minmod (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_supermin(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the supermin flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 *   \min\left(1,\,\frac{2\,d_1}{d_2}\right)\right]\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_SUPERMIN
JBDOUBLE
jbm_flux_limiter_supermin (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_supermin (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_minsuper(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the minsuper flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 *   \min\left(2,\,\frac{d_1}{d_2}\right)\right]\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_MINSUPER
JBDOUBLE
jbm_flux_limiter_minsuper (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_minsuper (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_null(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the null (2nd order upwind) flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=1\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_NULL
JBDOUBLE
jbm_flux_limiter_null (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_null (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_centred(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the centred (2nd order centred) flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\frac{d_1}{d_2}\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_CENTRED
JBDOUBLE
jbm_flux_limiter_centred (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_centred (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_total(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the total (1st order upwind) flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=0\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_TOTAL
JBDOUBLE
jbm_flux_limiter_total (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_total (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_monotonized_central(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the monotonized central flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=\max\left[0,\,
 *   \min\left(2,\,\frac{1+\frac{d_1}{d_2}}{2},\,\frac{2\,d_1}{d_2}\right)
 *   \right]\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_MONOTONIZED_CENTRAL
JBDOUBLE
jbm_flux_limiter_monotonized_central (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_monotonized_central (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE jbm_flux_limiter_mean(JBDOUBLE d1, JBDOUBLE d2)
 * \brief Function to calculate the mean flux limiter:
 *   \f$\psi\left(d_1,\,d_2\right)=
 *   \max\left(0,\,\frac{1+\frac{d_1}{d_2}}{2}\right)\f$.
 * \param d1
 * \brief 1st flux limiter function parameter.
 * \param d2
 * \brief 2nd flux limiter function parameter.
 * \return flux limiter function value.
 */
#if !INLINE_JBM_FLUX_LIMITER_MEAN
JBDOUBLE
jbm_flux_limiter_mean (JBDOUBLE d1, JBDOUBLE d2)
{
  return _jbm_flux_limiter_mean (d1, d2);
}
#endif

/**
 * \fn JBDOUBLE (*jbm_flux_limiter_select(int type))(JBDOUBLE, JBDOUBLE)
 * \brief Function to select a flux limiter function.
 * \param type
 * \brief type of flux limiter function.
 * \return pointer to the flux limiter function.
 */
#if !INLINE_JBM_FLUX_LIMITER_SELECT
JBDOUBLE (*jbm_flux_limiter_select (int type)) (JBDOUBLE, JBDOUBLE)
{
  return _jbm_flux_limiter_select (type);
}
#endif

#if !INLINE_JBM_TRANSVERSAL_SECTION_REGIONS_SORT
void
jbm_transversal_section_regions_sort (int i, int *nj, int *nk, JBFLOAT * l,
                                      JBFLOAT * z, JBFLOAT * x, JBFLOAT * zz,
                                      int *nx)
{
  _jbm_transversal_section_regions_sort (i, nj, nk, l, z, x, zz, nx);
}
#endif

/**
 * \fn int jbm_transversal_section_regions(JBFLOAT *l, JBFLOAT *z, int n, \
 *   JBFLOAT **zz, int **ni, int **nj, int **nij, int *nmin)
 * \brief Function to get the regions of a cross section.
 * \param l
 * \brief array of JBFLOAT numbers with the transversal coordinates of the
 *   points defining the cross section.
 * \param z
 * \brief array of JBFLOAT numbers with the vertical coordinates of the
 *   points defining the cross section.
 * \param n
 * \brief the highest cross section point number.
 * \param zz
 * \brief pointer to the array of JBFLOAT numbers, generated by g_malloc, of the
 *   cross section z-coordinates sorted from the lowest to the highest.
 * \param ni
 * \brief pointer to the array of indexes, generated by g_malloc and sorted by
 *   z-coordinates, of the cross section points.
 * \param nj
 * \brief pointer to the array, generated by g_malloc, of the highest element
 *   number on every j-th region.
 * \param nij
 * \brief pointer to the sorted segments, from the lowest to the highest, on
 *   every j-region.
 * \param nmin
 * \brief index of the lowest riverside point.
 * \return index of the highest riverside point.
*/
#if !INLINE_JBM_TRANSVERSAL_SECTION_REGIONS
int
jbm_transversal_section_regions (JBFLOAT * l, JBFLOAT * z, int n,
                                 JBFLOAT ** zz, int **ni, int **nj, int **nij,
                                 int *nmin)
{
  return _jbm_transversal_section_regions (l, z, n, zz, ni, nj, nij, nmin);
}
#endif

/**
 * \fn int jbm_varray_search(JBDOUBLE x, void *v, int size, int n)
 * \brief Function to find the segment number where a number is in an array of
 *   segments defined in an array of structs.
 * \param x
 * \brief number to search.
 * \param v
 * \brief pointer to the field in JBFLOAT format of the 1st element of the array
 *   of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of structs.
 * \return segement number.
 */
#if !INLINE_JBM_VARRAY_SEARCH
int
jbm_varray_search (JBDOUBLE x, void *v, int size, int n)
{
  return _jbm_varray_search (x, v, size, n);
}
#endif

/**
 * \fn int jbm_varray_search_extended(JBDOUBLE x, void *v, int size, int n)
 * \brief Function to find the segment number where a number is in an array of
 *   segments defined in an array of structs checking if the number is out.
 * \param x
 * \brief number to search.
 * \param v
 * \brief pointer to the field in JBFLOAT format of the 1st element of the array
 *   of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \return segement number, -1 if \f$x<v_0\f$ or \f$n\f$ if \f$x>v_n\f$.
 */
#if !INLINE_JBM_VARRAY_SEARCH_EXTENDED
int
jbm_varray_search_extended (JBDOUBLE x, void *v, int size, int n)
{
  return _jbm_varray_search_extended (x, v, size, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_varray_max(void *va, int size, int n)
 * \brief Function to find the highest value in an array of structs.
 * \param va
 * \brief pointer to the field in JBFLOAT format of the 1st element of the array
 *   of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \return the highest value.
 */
#if !INLINE_JBM_VARRAY_MAX
JBDOUBLE
jbm_varray_max (void *va, int size, int n)
{
  return _jbm_varray_max (va, size, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_varray_min(void *va, int size, int n)
 * \brief Function to find the lowest value in an array of structs.
 * \param va
 * \brief pointer to the field in JBFLOAT format of the 1st element of the array
 *   of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \return the lowest value.
 */
#if !INLINE_JBM_VARRAY_MIN
JBDOUBLE
jbm_varray_min (void *va, int size, int n)
{
  return _jbm_varray_min (va, size, n);
}
#endif

/**
 * \fn void jbm_varray_maxmin(void *va, int size, int n, JBDOUBLE *max, \
 *   JBDOUBLE *min)
 * \brief Function to find the highest value in an array of structs.
 * \param va
 * \brief pointer to the field in JBFLOAT format of the 1st element of the array
 *   of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \param max
 * \brief pointer to the highest value.
 * \param min
 * \brief pointer to the lowest value.
 */
#if !INLINE_JBM_VARRAY_MAXMIN
void
jbm_varray_maxmin (void *va, int size, int n, JBDOUBLE * max, JBDOUBLE * min)
{
  _jbm_varray_maxmin (va, size, n, max, min);
}
#endif

/**
 * \fn JBDOUBLE jbm_varray_mean_square_error(void *xa, void *fa, int sizea, \
 *   int na, void *xr, void *fr, int sizer, int nr)
 * \brief Function to calculate the mean square error between 2 functions
 *   tabulated in 2 arrays of structs.
 * \param xa
 * \brief x-coordinates tabulating the 1st function.
 * \param fa
 * \brief values of the 1st function.
 * \param sizea
 * \brief size of the structs of the 1st array.
 * \param na
 * \brief the highest point number tabulating the 1st function.
 * \param xr
 * \brief x-coordinates tabulating the 2nd function.
 * \param fr
 * \brief values of the 2nd function.
 * \param sizer
 * \brief size of the structs of the 2nd array.
 * \param nr
 * \brief the highest point number tabulating the 2nd function.
 * \return mean square error value.
 */
#if !INLINE_JBM_VARRAY_MEAN_SQUARE_ERROR
JBDOUBLE
jbm_varray_mean_square_error (void *xa, void *fa, int sizea, int na,
                              void *xr, void *fr, int sizer, int nr)
{
  return _jbm_varray_mean_square_error (xa, fa, sizea, na, xr, fr, sizer, nr);
}
#endif

/**
 * \fn JBDOUBLE jbm_varray_root_mean_square_error(void *xa, void *fa, \
 * int sizea, int na, void *xr, void *fr, int sizer, int nr)
 * \brief Function to calculate the root mean square error between 2 functions
 *   tabulated in 2 arrays of structs.
 * \param xa
 * \brief x-coordinates tabulating the 1st function.
 * \param fa
 * \brief values of the 1st function.
 * \param sizea
 * \brief size of the structs of the 1st array.
 * \param na
 * \brief the highest point number tabulating the 1st function.
 * \param xr
 * \brief x-coordinates tabulating the 2nd function.
 * \param fr
 * \brief values of the 2nd function.
 * \param sizer
 * \brief size of the structs of the 2nd array.
 * \param nr
 * \brief the highest point number tabulating the 2nd function.
 * \return root mean square error value.
 */
#if !INLINE_JBM_VARRAY_ROOT_MEAN_SQUARE_ERROR
JBDOUBLE
jbm_varray_root_mean_square_error (void *xa, void *fa, int sizea,
                                   int na, void *xr, void *fr, int sizer,
                                   int nr)
{
  return _jbm_varray_root_mean_square_error
      (xa, fa, sizea, na, xr, fr, sizer, nr);
}
#endif

/**
 * \fn void jbm_varray_solve_tridiagonal(void *C, void *D, void *E, void *H,
 *   int size, int n)
 * \brief Function to solve a tridiagonal linear equations system stored in the
 *   fields of a struct array with format: \f$\left(\begin{array}{cccc|c}
 *   D_0 & E_0    &         &        & H_0\\
 *   C_0 & D_1    & E_1     &        & H_1\\
 *       & \ddots & \ddots  & \ddots & \vdots\\
 *       &        & C_{n-1} & D_n    & H_n
 *   \end{array}\right)\f$.
 *   Results are stored in the H fields. It modifies D and H fields.
 * \param C
 * \brief field address of first element of the struct array containing the left
 *   diagonal equation system values.
 * \param D
 * \brief field addres of first element of the struct array containing the
 *   central diagonal equation system values.
 * \param E
 * \brief field address of first element of the struct array containing the
 *   right diagonal equation system values.
 * \param H
 * \brief field address of first element of the struct array containing the
 *   final equation system values.
 * \param size
 * \brief struct size.
 * \param n
 * \brief the latest struct array element.
 */
#if !INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL
void jbm_varray_solve_tridiagonal
    (void *C, void *D, void *E, void *H, int size, int n)
{
  _jbm_varray_solve_tridiagonal (C, D, E, H, size, n);
}
#endif

/**
 * \fn void jbm_varray_solve_tridiagonal_zero(void *C, void *D, void *E, \
 *   void *H, int size, int n)
 * \brief Function to solve a tridiagonal linear equations system stored in the
 *   fields of a struct array with format: \f$\left(\begin{array}{cccc|c}
 *   D_0 & E_0    &         &        & H_0\\
 *   C_0 & D_1    & E_1     &        & H_1\\
 *       & \ddots & \ddots  & \ddots & \vdots\\
 *       &        & C_{n-1} & D_n    & H_n
 *   \end{array}\right)\f$.
 *   avoiding zero divisions. Results are stored in the H fields. It modifies D
 *   and H fields.
 * \param C
 * \brief field address of first element of the struct array containing the left
 *   diagonal equation system values.
 * \param D
 * \brief field addres of first element of the struct array containing the
 *   central diagonal equation system values.
 * \param E
 * \brief field address of first element of the struct array containing the
 *   right diagonal equation system values.
 * \param H
 * \brief field address of first element of the struct array containing the
 *   final equation system values.
 * \param size
 * \brief struct size.
 * \param n
 * \brief the latest struct array element.
 */
#if !INLINE_JBM_VARRAY_SOLVE_TRIDIAGONAL_ZERO
void jbm_varray_solve_tridiagonal_zero
    (void *C, void *D, void *E, void *H, int size, int n)
{
  _jbm_varray_solve_tridiagonal_zero (C, D, E, H, size, n);
}
#endif

/**
 * \fn int jbm_vdarray_search(JBDOUBLE x, void *v, int size, int n)
 * \brief Function to find the segment number where a number is in an array of
 *   segments defined in an array of structs.
 * \param x
 * \brief number to search.
 * \param v
 * \brief pointer to the field in JBDOUBLE format of the 1st element of the \
 *   array of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of structs.
 * \return segement number.
 */
#if !INLINE_JBM_VDARRAY_SEARCH
int
jbm_vdarray_search (JBDOUBLE x, void *v, int size, int n)
{
  return _jbm_vdarray_search (x, v, size, n);
}
#endif

/**
 * \fn int jbm_vdarray_search_extended(JBDOUBLE x, void *v, int size, int n)
 * \brief Function to find the segment number where a number is in an array of
 *   segments defined in an array of structs checking if the number is out.
 * \param x
 * \brief number to search.
 * \param v
 * \brief pointer to the field in JBDOUBLE format of the 1st element of the
 *   array of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \return segement number, -1 if \f$x<v_0\f$ or \f$n\f$ if \f$x>v_n\f$.
 */
#if !INLINE_JBM_VDARRAY_SEARCH_EXTENDED
int
jbm_vdarray_search_extended (JBDOUBLE x, void *v, int size, int n)
{
  return _jbm_vdarray_search_extended (x, v, size, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_vdarray_max(void *va, int size, int n)
 * \brief Function to find the highest value in an array of structs.
 * \param va
 * \brief pointer to the field in JBDOUBLE format of the 1st element of the
 *   array of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \return the highest value.
 */
#if !INLINE_JBM_VDARRAY_MAX
JBDOUBLE
jbm_vdarray_max (void *va, int size, int n)
{
  return _jbm_vdarray_max (va, size, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_vdarray_min(void *va, int size, int n)
 * \brief Function to find the lowest value in an array of structs.
 * \param va
 * \brief pointer to the field in JBDOUBLE format of the 1st element of the
 *   array of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \return the lowest value.
 */
#if !INLINE_JBM_VDARRAY_MIN
JBDOUBLE
jbm_vdarray_min (void *va, int size, int n)
{
  return _jbm_vdarray_min (va, size, n);
}
#endif

/**
 * \fn void jbm_vdarray_maxmin(void *va, int size, int n, JBDOUBLE *max, \
 *   JBDOUBLE *min)
 * \brief Function to find the highest value in an array of structs.
 * \param va
 * \brief pointer to the field in JBDOUBLE format of the 1st element of the
 *   array of structs.
 * \param size
 * \brief size of the structs.
 * \param n
 * \brief number of the last element of the structs array.
 * \param max
 * \brief pointer to the highest value.
 * \param min
 * \brief pointer to the lowest value.
 */
#if !INLINE_JBM_VDARRAY_MAXMIN
void
jbm_vdarray_maxmin (void *va, int size, int n, JBDOUBLE * max, JBDOUBLE * min)
{
  _jbm_vdarray_maxmin (va, size, n, max, min);
}
#endif

/**
 * \fn JBDOUBLE jbm_vdarray_mean_square_error(void *xa, void *fa, int sizea, \
 *   int na, void *xr, void *fr, int sizer, int nr)
 * \brief Function to calculate the mean square error between 2 functions
 *   tabulated in 2 arrays of structs.
 * \param xa
 * \brief x-coordinates tabulating the 1st function.
 * \param fa
 * \brief values of the 1st function.
 * \param sizea
 * \brief size of the structs of the 1st array.
 * \param na
 * \brief the highest point number tabulating the 1st function.
 * \param xr
 * \brief x-coordinates tabulating the 2nd function.
 * \param fr
 * \brief values of the 2nd function.
 * \param sizer
 * \brief size of the structs of the 2nd array.
 * \param nr
 * \brief the highest point number tabulating the 2nd function.
 * \return mean square error value.
 */
#if !INLINE_JBM_VDARRAY_MEAN_SQUARE_ERROR
JBDOUBLE
jbm_vdarray_mean_square_error (void *xa, void *fa, int sizea, int na,
                               void *xr, void *fr, int sizer, int nr)
{
  return _jbm_vdarray_mean_square_error (xa, fa, sizea, na, xr, fr, sizer, nr);
}
#endif

/**
 * \fn JBDOUBLE jbm_vdarray_root_mean_square_error(void *xa, void *fa, \
 * int sizea, int na, void *xr, void *fr, int sizer, int nr)
 * \brief Function to calculate the root mean square error between 2 functions
 *   tabulated in 2 arrays of structs.
 * \param xa
 * \brief x-coordinates tabulating the 1st function.
 * \param fa
 * \brief values of the 1st function.
 * \param sizea
 * \brief size of the structs of the 1st array.
 * \param na
 * \brief the highest point number tabulating the 1st function.
 * \param xr
 * \brief x-coordinates tabulating the 2nd function.
 * \param fr
 * \brief values of the 2nd function.
 * \param sizer
 * \brief size of the structs of the 2nd array.
 * \param nr
 * \brief the highest point number tabulating the 2nd function.
 * \return root mean square error value.
 */
#if !INLINE_JBM_VDARRAY_ROOT_MEAN_SQUARE_ERROR
JBDOUBLE
jbm_vdarray_root_mean_square_error (void *xa, void *fa, int sizea,
                                    int na, void *xr, void *fr, int sizer,
                                    int nr)
{
  return _jbm_vdarray_root_mean_square_error
      (xa, fa, sizea, na, xr, fr, sizer, nr);
}
#endif

/**
 * \fn void jbm_vdarray_solve_tridiagonal(void *C, void *D, void *E, void *H,
 *   int size, int n)
 * \brief Function to solve a tridiagonal linear equations system stored in the
 *   fields of a struct array with format: \f$\left(\begin{array}{cccc|c}
 *   D_0 & E_0    &         &        & H_0\\
 *   C_0 & D_1    & E_1     &        & H_1\\
 *       & \ddots & \ddots  & \ddots & \vdots\\
 *       &        & C_{n-1} & D_n    & H_n
 *   \end{array}\right)\f$.
 *   Results are stored in the H fields. It modifies D and H fields.
 * \param C
 * \brief field address of first element of the struct array containing the left
 *   diagonal equation system values.
 * \param D
 * \brief field addres of first element of the struct array containing the
 *   central diagonal equation system values.
 * \param E
 * \brief field address of first element of the struct array containing the
 *   right diagonal equation system values.
 * \param H
 * \brief field address of first element of the struct array containing the
 *   final equation system values.
 * \param size
 * \brief struct size.
 * \param n
 * \brief the latest struct array element.
 */
#if !INLINE_JBM_VDARRAY_SOLVE_TRIDIAGONAL
void jbm_vdarray_solve_tridiagonal
    (void *C, void *D, void *E, void *H, int size, int n)
{
  _jbm_vdarray_solve_tridiagonal (C, D, E, H, size, n);
}
#endif

/**
 * \fn void jbm_vdarray_solve_tridiagonal_zero(void *C, void *D, void *E, \
 *   void *H, int size, int n)
 * \brief Function to solve a tridiagonal linear equations system stored in the
 *   fields of a struct array with format: \f$\left(\begin{array}{cccc|c}
 *   D_0 & E_0    &         &        & H_0\\
 *   C_0 & D_1    & E_1     &        & H_1\\
 *       & \ddots & \ddots  & \ddots & \vdots\\
 *       &        & C_{n-1} & D_n    & H_n
 *   \end{array}\right)\f$.
 *   avoiding zero divisions. Results are stored in the H fields. It modifies D
 *   and H fields.
 * \param C
 * \brief field address of first element of the struct array containing the left
 *   diagonal equation system values.
 * \param D
 * \brief field addres of first element of the struct array containing the
 *   central diagonal equation system values.
 * \param E
 * \brief field address of first element of the struct array containing the
 *   right diagonal equation system values.
 * \param H
 * \brief field address of first element of the struct array containing the
 *   final equation system values.
 * \param size
 * \brief struct size.
 * \param n
 * \brief the latest struct array element.
 */
#if !INLINE_JBM_VDARRAY_SOLVE_TRIDIAGONAL_ZERO
void jbm_vdarray_solve_tridiagonal_zero
    (void *C, void *D, void *E, void *H, int size, int n)
{
  _jbm_vdarray_solve_tridiagonal_zero (C, D, E, H, size, n);
}
#endif

/**
 * \fn JBDOUBLE jbm_file_mean_square_error(char *namea, int ixa, int ifa, \
 *   int na, char *namer, int ixr, int ifr, int nr)
 * \brief Function to calculate the mean square error between 2 functions
 *   tabulated in 2 columns data of a file.
 * \param namea
 * \brief name of file where the 1st function is tabulated.
 * \param ixa
 * \brief column number of x-coordinates tabulating the 1st function.
 * \param ifa
 * \brief column number of values tabulating the 1st function.
 * \param na
 * \brief columns number of file tabulating the 1st function.
 * \param namer
 * \brief name of file where the 2nd function is tabulated.
 * \param ixr
 * \brief column number of x-coordinates tabulating the 2nd function.
 * \param ifr
 * \brief column number of values tabulating the 2nd function.
 * \param nr
 * \brief columns number of file tabulating the 2nd function.
 * \return mean square error value.
 */
#if !INLINE_JBM_FILE_MEAN_SQUARE_ERROR
JBDOUBLE
jbm_file_mean_square_error (char *namea, int ixa, int ifa, int na,
                            char *namer, int ixr, int ifr, int nr)
{
  return _jbm_file_mean_square_error (namea, ixa, ifa, na, namer, ixr, ifr, nr);
}
#endif

/**
 * \fn JBDOUBLE jbm_file_root_mean_square_error(char *namea, int ixa, int ifa, \
 *   int na, char *namer, int ixr, int ifr, int nr)
 * \brief Function to calculate the root mean square error between 2 functions
 *   tabulated in 2 columns data of a file.
 * \param namea
 * \brief name of file where the 1st function is tabulated.
 * \param ixa
 * \brief column number of x-coordinates tabulating the 1st function.
 * \param ifa
 * \brief column number of values tabulating the 1st function.
 * \param na
 * \brief columns number of file tabulating the 1st function.
 * \param namer
 * \brief name of file where the 2nd function is tabulated.
 * \param ixr
 * \brief column number of x-coordinates tabulating the 2nd function.
 * \param ifr
 * \brief column number of values tabulating the 2nd function.
 * \param nr
 * \brief columns number of file tabulating the 2nd function.
 * \return root mean square error value.
 */
#if !INLINE_JBM_FILE_ROOT_MEAN_SQUARE_ERROR
JBDOUBLE
jbm_file_root_mean_square_error (char *namea, int ixa, int ifa, int na,
                                 char *namer, int ixr, int ifr, int nr)
{
  return _jbm_file_root_mean_square_error
      (namea, ixa, ifa, na, namer, ixr, ifr, nr);
}
#endif